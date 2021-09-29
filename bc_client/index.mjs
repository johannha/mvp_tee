import express from "express";
import { scAddresses, addresses, abi } from "./addresses.mjs";
import dataJS from "./dataJS_pb.js";
import Web3 from "web3";
import * as fs from "fs";

// set up express
const client = express();
const port = 3000;

// data read
var dataCount = 0;

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

function watchFs() {
  console.log(scAddresses[1]);
  fs.watch("../tee/output/", (event, filename) => {
    if (event === "rename") {
      console.log(`${filename} file changed`);
      forwardData(String(filename));
    }
  });
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

async function forwardData(data) {
  //read from file

  let rawData = fs.readFileSync(`../tee/output/${data}`);

  let parsedObject = dataJS.teeData.deserializeBinary(rawData);

  let signature = "0x" + parsedObject.getSignature();
  let mid = String(parsedObject.getMid());
  let pavg = parseInt(parsedObject.getPavg());
  let iend = parseInt(parsedObject.getIend());

  console.log("String: " + signature);
  // hex string to byte array
  let iend_string = String(iend);
  //let signature_byte = web3.utils.hexToBytes(signature);
  let signature_byte = hexToBytes(signature);
  console.log(signature_byte);

  console.log("The received Power: " + parsedObject.getPavg());

  // add to smart contract
  let contract = new web3.eth.Contract(abi[1], scAddresses[1], {
    from: addresses[1],
    gas: 6721975,
  });
  contract.methods
    .addData(signature_byte, mid, pavg, iend_string)
    .send({ from: addresses[1] })
    .on("receipt", (hash) => {
      console.log(hash);
      return 0;
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

// helper
function hexToBytes(hex) {
  for (var bytes = [], c = 0; c < hex.length; c += 2)
    bytes.push(parseInt(hex.substr(c, 2), 16));
  return bytes;
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
  setString("Message from blockchain client").then((value) => res.send(value));
});

client.get("/watch/fs", (req, res) => {
  res.send("BC is now watching FS and forwards messages to Blockchain.");
  watchFs();
});

client.listen(port, () => {
  console.log(`Example app listening at http://localhost:${port}`);
  watchFs();
  console.log("BC is now watching FS and forwards messages to Blockchain.");
});
