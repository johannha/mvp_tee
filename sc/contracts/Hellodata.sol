pragma solidity 0.5.16;

contract Hellodata {
    struct DataBatch {
        string _signature;
        string MId;
        uint16 PAvg;
        uint64 IEnd;
    }

    address public owner;
    uint256 internal _dataCount;
    string public testString;
    mapping(uint256 => DataBatch) public dataMap;

    constructor() public {
        owner = msg.sender;
        _dataCount = 0;
        testString = "constructed";
    }

    function addData(
        string memory _signature,
        string memory _MId,
        uint16 _PAvg,
        uint64 _IEnd
    ) public {
        dataMap[_dataCount] = DataBatch(_signature, _MId, _PAvg, _IEnd);
        _dataCount += 1;
    }

    function setString(string memory _input) public {
        testString = _input;
    }
}
