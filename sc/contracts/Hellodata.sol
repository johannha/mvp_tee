pragma solidity 0.5.16;

contract Hellodata {
    struct DataBatch {
        string _signature;
        string MId;
        uint16 PAvg;
        string IEnd;
        bool verified;
    }

    address public owner;
    // results from taking last 20 bytes of Keccak-256 hashed public key 0xce22f625047a7c4175686930ff9e8b3f801f76c6
    address internal verifier = 0xcE22f625047a7c4175686930ff9e8b3f801F76C6;
    uint256 internal _dataCount;
    bool public signLength;
    string public testString;
    mapping(uint256 => DataBatch) public dataMap;

    constructor() public {
        owner = msg.sender;
        _dataCount = 0;
        testString = "constructed";
    }

    function verifySignature(bytes32 _hash) internal returns (bool) {
        return
            recover(
                _hash,
                hex"c28abc60813ae2c08599072f95774cb3380ccaaba2f23c93ee58a29eeb830e14c110703671eaaf5d859c4674a3ea6b9de8a20779394d8df533ab60623d4be08101"
            ) == verifier;
    }

    function hashString(string memory _input) internal pure returns (bytes32) {
        return sha256(abi.encodePacked(_input));
    }

    function addData(
        string memory _signature,
        string memory _MId,
        uint16 _PAvg,
        string memory _IEnd
    ) public {
        bytes32 _hash = hashString(_IEnd);
        bool _verified = false;
        //bytes memory _toHex = fromHex(_signature);
        _verified = verifySignature(_hash);
        dataMap[_dataCount] = DataBatch(
            _signature,
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
        returns (address)
    {
        bytes32 r;
        bytes32 s;
        uint8 v;

        // Check the signature length
        if (sig.length != 65) {
            signLength = true;
            return (address(0));
        }

        // Divide the signature in r, s and v variables
        // ecrecover takes the signature parameters, and the only way to get them
        // currently is to use assembly.
        // solium-disable-next-line security/no-inline-assembly

        signLength = true;
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

    // helper method
    function fromHexChar(uint8 c) internal pure returns (uint8) {
        if (bytes1(c) >= bytes1("0") && bytes1(c) <= bytes1("9")) {
            return c - uint8(bytes1("0"));
        }
        if (bytes1(c) >= bytes1("a") && bytes1(c) <= bytes1("f")) {
            return 10 + c - uint8(bytes1("a"));
        }
        if (bytes1(c) >= bytes1("A") && bytes1(c) <= bytes1("F")) {
            return 10 + c - uint8(bytes1("A"));
        }
    }

    function fromHex(string memory s) internal returns (bytes memory) {
        bytes memory ss = bytes(s);

        require(ss.length % 2 == 0); // length must be even
        bytes memory r = new bytes(ss.length / 2);
        for (uint256 i = 0; i < ss.length / 2; ++i) {
            r[i] = bytes1(
                fromHexChar(uint8(ss[2 * i])) *
                    16 +
                    fromHexChar(uint8(ss[2 * i + 1]))
            );
        }

        return r;
    }
}
