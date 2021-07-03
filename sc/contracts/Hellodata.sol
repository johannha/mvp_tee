pragma solidity 0.5.16;

contract Hellodata {
    address public owner;
    uint256 internal _dataCount;

    struct Data {
        string _signature;
        uint16 _data; // value might be temperature in celsius stored as an int
    }

    mapping(uint256 => Data) public dataMap;

    constructor() public {
        owner = msg.sender;
        _dataCount = 0;
    }

    function addData(string memory _signature, uint16 _data) public {
        dataMap[_dataCount] = Data(_signature, _data);
        _dataCount++;
    }
}
