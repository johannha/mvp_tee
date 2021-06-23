import argparse
import json

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
    def __init__(self, data):
        self.data = [data]


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
        print(json_array[1])  # remove after usage

        # create Batch
        for x in range(args.batchesTotal):
