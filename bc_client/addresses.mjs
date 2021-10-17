const addresses = {
  1: "0x83C068d68CFf5E64D67053BcA9FCa9e4639EeE0c",
  2: "0x97E3d4e893e9DC6DFE63395e84Aef05D6b684dB6",
  3: "0x4d1D50b601C4744345E1e88Cb25676319F76A674",
  4: "0x45C0947a8794612eFCC4Faeb881288dF7C9fB029",
};

const scAddresses = {
  1: "0x8DCCa8436d16a7EEa4A1B0fdA57feA5ED3813b07",
};

const abi = {
  1: [
    {
      inputs: [],
      payable: false,
      stateMutability: "nonpayable",
      type: "constructor",
    },
    {
      constant: true,
      inputs: [
        {
          internalType: "uint256",
          name: "",
          type: "uint256",
        },
      ],
      name: "dataMap",
      outputs: [
        {
          internalType: "string",
          name: "_signature",
          type: "string",
        },
        {
          internalType: "string",
          name: "MId",
          type: "string",
        },
        {
          internalType: "uint16",
          name: "PAvg",
          type: "uint16",
        },
        {
          internalType: "string",
          name: "IEnd",
          type: "string",
        },
        {
          internalType: "bool",
          name: "verified",
          type: "bool",
        },
      ],
      payable: false,
      stateMutability: "view",
      type: "function",
    },
    {
      constant: true,
      inputs: [],
      name: "owner",
      outputs: [
        {
          internalType: "address",
          name: "",
          type: "address",
        },
      ],
      payable: false,
      stateMutability: "view",
      type: "function",
    },
    {
      constant: true,
      inputs: [],
      name: "signLength",
      outputs: [
        {
          internalType: "uint256",
          name: "",
          type: "uint256",
        },
      ],
      payable: false,
      stateMutability: "view",
      type: "function",
    },
    {
      constant: true,
      inputs: [],
      name: "testString",
      outputs: [
        {
          internalType: "string",
          name: "",
          type: "string",
        },
      ],
      payable: false,
      stateMutability: "view",
      type: "function",
    },
    {
      constant: false,
      inputs: [
        {
          internalType: "string",
          name: "_signature",
          type: "string",
        },
        {
          internalType: "string",
          name: "_MId",
          type: "string",
        },
        {
          internalType: "uint16",
          name: "_PAvg",
          type: "uint16",
        },
        {
          internalType: "string",
          name: "_IEnd",
          type: "string",
        },
      ],
      name: "addData",
      outputs: [],
      payable: false,
      stateMutability: "nonpayable",
      type: "function",
    },
    {
      constant: false,
      inputs: [
        {
          internalType: "string",
          name: "_input",
          type: "string",
        },
      ],
      name: "setString",
      outputs: [],
      payable: false,
      stateMutability: "nonpayable",
      type: "function",
    },
  ],
};

export { abi, scAddresses, addresses };
