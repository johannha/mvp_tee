import express from "express";
import { scAddresses, addresses, abi } from "./addresses.mjs";
import dataJS from "./dataJS_pb.js";
import Web3 from "web3";
import * as fs from "fs";

// set up express
const client = express();
const port = 3000;

// set up web3
const rpcServer = "HTTP://127.0.0.1:7545";
const web3 = new Web3(rpcServer);

// get balance of account
async function getBalance(accountNumber) {
  let bal = 0;
  await web3.eth.getBalance(addresses[accountNumber], (err, wei) => {
    bal = web3.utils.fromWei(wei, "ether");
  });
  console.log(bal);
  return bal;
}

// trigger smart contract methods
async function setString(value) {
  let contract = new web3.eth.Contract(abi[1], scAddresses[1], {
    from: addresses[1],
    gas: 6721975,
  });
  contract.methods
    .setString(value)
    .send({ from: addresses[1] })
    .on("receipt", (hash) => {
      console.log(hash);
      return "String set";
    });
}

async function setData() {
  //read from file
  let rawData = fs.readFileSync("../tee/output/0.bin");
  let parsedObject = dataJS.teeData.deserializeBinary(rawData);

  let signature = parsedObject.getSignature();
  let mid = parsedObject.getMid();
  let pavg = parseInt(parsedObject.getPavg());
  let iend = parseInt(parsedObject.getIend());

  console.log("The received Power: " + parsedObject.getPavg());
  console.log(typeof pavg);

  // add to smart contract
  let contract = new web3.eth.Contract(abi[1], scAddresses[1], {
    from: addresses[1],
    gas: 6721975,
  });
  contract.methods
    .addData(signature, mid, pavg, iend)
    .send({ from: addresses[1] })
    .on("receipt", (hash) => {
      console.log(hash);
    });
}

async function readString() {
  let temp;
  let contract = new web3.eth.Contract(abi[1], scAddresses[1]);
  await contract.methods.testString().call((err, result) => {
    console.log(`Test String = ${result}`);
    temp = result;
  });
  return temp;
}

async function readDataMap() {
  let temp;
  let contract = new web3.eth.Contract(abi[1], scAddresses[1]);
  await contract.methods.dataMap(1).call((err, result) => {
    console.log(result);
    temp = result;
  });
  return temp;
}

// client requests

client.get("/bal/1", async (req, res) => {
  let result = await getBalance(1);
  res.send(result);
});

client.get("/get/testString", (req, res) => {
  readString().then((value) => res.send(value));
});

client.get("/get/dataMap", (req, res) => {
  readDataMap().then((value) => res.send(value));
});

client.get("/set/string", (req, res) => {
  setString("new one").then((value) => res.send(value));
});

client.get("/push/data", (req, res) => {
  setData().then(() => res.send("New data added"));
});

client.listen(port, () => {
  console.log(`Example app listening at http://localhost:${port}`);
});