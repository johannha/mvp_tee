pragma solidity 0.5.16;

contract Hellodata {
    address public owner;
    uint256 internal _dataCount;
    string public testString;
    mapping(uint256 => DataBatch) public dataMap;

    struct DataBatch {
        string _signature;
        uint16 _data; // value might be temperature in celsius stored as an int
    }

    constructor() public {
        owner = msg.sender;
        _dataCount = 0;
        testString = "constructed";
    }

    function addData(string memory _signature, uint16 _data) public {
        dataMap[_dataCount] = DataBatch(_signature, _data);
        _dataCount += 1;
    }

    function setString(string memory _input) public {
        testString = _input;
    }
}
