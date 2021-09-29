pragma solidity 0.5.16;

contract Hellodata {
    struct DataBatch {
        bytes _signature;
        string MId;
        uint16 PAvg;
        string IEnd;
        bool verified;
    }

    address public owner;
    // results from taking last 20 bytes of Keccak-256 hashed public key 0xce22f625047a7c4175686930ff9e8b3f801f76c6
    address internal verifier = 0xcE22f625047a7c4175686930ff9e8b3f801F76C6;
    uint256 internal _dataCount;
    string public testString;
    mapping(uint256 => DataBatch) public dataMap;

    constructor() public {
        owner = msg.sender;
        _dataCount = 0;
        testString = "constructed";
    }

    function verifySignature(bytes memory _signature, bytes32 _hash)
        internal
        view
        returns (bool)
    {
        return recover(_hash, _signature) == verifier;
    }

    function hashString(string memory _input) internal pure returns (bytes32) {
        return sha256(abi.encodePacked(_input));
    }

    function addData(
        bytes memory _signature,
        string memory _MId,
        uint16 _PAvg,
        string memory _IEnd
    ) public {
        bytes memory _movedSignature;
        // bring signature in form
        for (uint256 i = 4; i < _signature.length; i++) {
            _movedSignature[i - 4] = _signature[i];
        }
        bytes32 _hash = hashString(_IEnd);
        bool _verified = false;
        _verified = verifySignature(_movedSignature, _hash);
        dataMap[_dataCount] = DataBatch(
            _movedSignature,
            _MId,
            _PAvg,
            _IEnd,
            _verified
        );
        _dataCount += 1;
    }

    function setString(string memory _input) public {
        testString = _input;
    }

    function recover(bytes32 hash, bytes memory sig)
        internal
        pure
        returns (address)
    {
        bytes32 r;
        bytes32 s;
        uint8 v;

        // Check the signature length
        if (sig.length != 65) {
            return (address(0));
        }

        // Divide the signature in r, s and v variables
        // ecrecover takes the signature parameters, and the only way to get them
        // currently is to use assembly.
        // solium-disable-next-line security/no-inline-assembly
        assembly {
            r := mload(add(sig, 32))
            s := mload(add(sig, 64))
            v := byte(0, mload(add(sig, 96)))
        }

        // Version of signature should be 27 or 28, but 0 and 1 are also possible versions
        if (v < 27) {
            v += 27;
        }

        // If the version is correct return the signer address
        if (v != 27 && v != 28) {
            return (address(0));
        } else {
            // solium-disable-next-line arg-overflow
            return ecrecover(hash, v, r, s);
        }
    }
}
