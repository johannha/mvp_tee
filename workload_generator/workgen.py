import argparse
import json
import time
import hashlib

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

# -------------------------- Command Line Arguments -------------------------- #


class Batch:
    data = []
    hashPrep = ""
    resultHash = ""


def writeJSON(data, hash):

    batchConstruct = {"hash": hash, "data": data}

    tempJSON = json.dumps(batchConstruct, indent=4)

    with open(("./output/" + str(x) + ".json"), "x") as ex:
        ex.write(tempJSON)


def hashBatch(valueChain):
    encoded = valueChain.encode()
    result = hashlib.sha256(encoded).hexdigest()
    return result


# ----------------------------------- Main ----------------------------------- #
if __name__ == "__main__":

    args = checkArg()
    print("Batch Size: {}, Total Batches: {}, Throughput: {}".format(
        args.batchSize,
        args.batchesTotal,
        args.throughput,
    ))

    # read JSON workload
    with open("data_sample_2020-07-01.json", "r") as workload:

        json_array = json.load(workload)

        dataIndex = 0
        tempBatch = Batch()

        for x in range(int(args.batchesTotal)):

            # create Batch
            for y in range(int(args.batchSize)):
                tempBatch.data.append(json_array[dataIndex])

                # append values to hashPrep
                for value in json_array[dataIndex].values():
                    tempBatch.hashPrep = tempBatch.hashPrep + str(value)
                dataIndex += 1

            # hashValues()
            tempBatch.resultHash = hashBatch(tempBatch.hashPrep)

            # creates full batch and writes it to direcory
            writeJSON(tempBatch.data, tempBatch.resultHash)

            # clean tempBatch
            tempBatch.data = []
            tempBatch.hashPrep = ""
            tempBatch.resultHash = ""

            # add delay to get desired throughput
            time.sleep(60/int(args.throughput))
            print("Number of batch: " + str(x))
            print("Index Number: " + str(dataIndex))
