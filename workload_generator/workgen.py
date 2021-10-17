import argparse
import json
import time
import hashlib

from six import indexbytes
import rawData_pb2
from ecdsa import SigningKey, NIST256p
from ecdsa.util import sigencode_der, sigdecode_der

# Example call: "python3 workgen.py -s 5 -a 3 -t 60" --> generates 3 batches, containing 5 objects with a throughput of 60 batches/min

# -------------------------- Command Line Arguments -------------------------- #


def checkArg():

    parser = argparse.ArgumentParser()

    try:
        # -s Batch Size -a batches Total -t Throughput
        parser.add_argument("-s", "--batchSize",
                            help="Batch Size (Objects/Batch)")
        parser.add_argument("-a", "--batchesTotal",
                            help="Amount of total Batches")
        parser.add_argument("-t", "--throughput", help="Throughput of batches")

        args = parser.parse_args()

        if(int(args.batchSize) <= 0 or int(args.batchesTotal) <= 0 or int(args.throughput) <= 0):
            raise ValueError("Input parameters must be greater than 0")

        return args

    except Exception as error:
        print("Problem with input parameters: " + repr(error))


# keys
signKey = "665345f0a9f342eaac09c209161d25de60233b77834b4db3ece0406758d00a54"
verifyKey = "27023bef190183c43e1798a343ac70d53a32f95ba482360f1b7688b94cffa9b7351b4a67b82d880690531d106383cf742d30bc0aca3700c53329c99a5227c820"

signer = SigningKey.from_string(bytes.fromhex(
    signKey), curve=NIST256p, hashfunc=hashlib.sha256)

print("Der signing key: " + signer.to_der().hex())


def serialize(batch):

    print(batch)

    result = batch.SerializeToString()

    with open(("./output/" + str(x) + ".bin"), "wb") as ex:
        ex.write(result)


def hashBatch(valueChain):
    encoded = valueChain.encode()
    result = hashlib.sha256(encoded).hexdigest()
    return result


def signHash(hash):
    return signer.sign_deterministic((str.encode(hash)), sigencode=sigencode_der).hex()


# ----------------------------------- Main ----------------------------------- #
if __name__ == "__main__":

    args = checkArg()
    print("Batch Size: {}, Total Batches: {}, Throughput: {}".format(
        args.batchSize,
        args.batchesTotal,
        args.throughput,
    ))

    hashPrep = ""

    # read JSON workload
    with open("data_sample_2020-07-01.json", "r") as workload:

        json_array = json.load(workload)

        dataIndex = 0

        for x in range(int(args.batchesTotal)):

            tempBatch = rawData_pb2.rawData()

            # create Batch
            for y in range(int(args.batchSize)):

                tempData = rawData_pb2.IoTData()

                tempData.MId = (json_array[dataIndex].get('MId'))
                tempData.IDur = (json_array[dataIndex].get('IDur'))
                tempData.IEnd = (json_array[dataIndex].get('IEnd'))
                tempData.PAvg = (json_array[dataIndex].get('PAvg'))
                tempData.EIn = (json_array[dataIndex].get('EIn'))
                tempData.EOut = (json_array[dataIndex].get('EOut'))

                tempBatch.data.append(tempData)

                # append values to hashPrep
                # for value in json_array[dataIndex].values():
                #     hashPrep = hashPrep + str(value)
                hashPrep = hashPrep + str(json_array[dataIndex].get('IEnd'))
                dataIndex += 1

            # hash Values
            print("Hash prep: " + hashPrep)
            tempBatch.hash = hashBatch(hashPrep)

            # sign hash
            tempBatch.signature = signHash(hashPrep)

            # creates full batch and writes it to direcory
            serialize(tempBatch)

            # clean tempBatch
            hashPrep = ""
            tempBatch = None
            tempData = None

            # add delay to get desired throughput
            time.sleep(60/int(args.throughput))
            print("Number of batch: " + str(x))
            print("Index Number: " + str(dataIndex))
