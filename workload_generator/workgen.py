import argparse
import json
import time
import hashlib

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

        return parser.parse_args()

    except:
        print("Problem with input parameters")

# -------------------------- Command Line Arguments -------------------------- #


class Batch:
    data = []
    hashPrep = ""


def writeJSON(content):
    with open(("./output/" + str(x) + ".json"), "x") as ex:
        ex.write(content)

# TODO implement hash function


def hashBatch(valueChain):
    encoded = valueChain.encode()
    result = hashlib.sha256(encoded).hexdigest()


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

            # create JSON object
            tempJSON = json.dumps(tempBatch.data)

            # write to Output Directory
            # writeJSON(tempJSON)

            print("HashPrep Value of this batch" + tempBatch.hashPrep)
            tempBatch.data = []
            tempBatch.hashPrep = ""

            # add delay to get desired throughput
            time.sleep(60/int(args.throughput))
            print("Number of batch: " + str(x))
            print("Index Number: " + str(dataIndex))
