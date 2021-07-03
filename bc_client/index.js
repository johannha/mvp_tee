import express from "express";
import addresses from "./addresses.js";
import Web3 from "web3";

// set up express
const client = express();
const port = 3000;

// set up web3
const rpcServer = "HTTP://127.0.0.1:7545";
const scAddress = "0x972b22f4bdBd8bF43DCB88788bCA1D64B78AA9Fa";
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

client.get("/bal/1", async (req, res) => {
  let result = await getBalance(1);
  res.send(result);
});

client.listen(port, () => {
  console.log(`Example app listening at http://localhost:${port}`);
});
