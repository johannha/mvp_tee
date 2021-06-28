# Workload Generator

A push-based python script for creating workload batches. In current version the output is written directly in output directory.

## Arguments

| Name          | flag | Description                           |
| ------------- | :--: | :------------------------------------ |
| Batch Size    | `-s` | Set objects/ batch                    |
| Total Batches | `-a` | Set total amount of batches generated |
| Throughput    | `-t` | Set amount of batches/ minute         |

## Example call

Generate 3 batches including 5 objects with a throughput of 60 batches/ minute:

```
python3 workgen.py -s 5 -a 3 -t 60
```

Clear output folder:

```
python3 deleteOutput.py
```
