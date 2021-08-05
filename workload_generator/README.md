# Workload Generator

A push-based python script for creating workload batches. In current version the output is written directly in output directory.

## Dependencies

Run `pip3 install -r requirements.txt` to install dependencies

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

## Compile Protobuf

SRC_DIR="/Users/johannHartmann\ 1/Documents/Code/mvp_tee/workload_generator"
DST_DIR="/Users/johannHartmann\ 1/Documents/Code/mvp_tee/buffer_compiler/bin/python"

```
./protoc -I=/Users/johannHartmann\ 1/Documents/Code/mvp_tee/buffer_compiler/bin  --python_out=/Users/johannHartmann\ 1/Documents/Code/mvp_tee/buffer_compiler/bin/python /Users/johannHartmann\ 1/Documents/Code/mvp_tee/buffer_compiler/bin/rawData.proto
```

Compiling c++

```
./protoc -I=/Users/johannHartmann\ 1/Documents/Code/mvp_tee/buffer_compiler/bin  --cpp_out=/Users/johannHartmann\ 1/Documents/Code/mvp_tee/buffer_compiler/bin/cpp /Users/johannHartmann\ 1/Documents/Code/mvp_tee/buffer_compiler/bin/dataC.proto
```

Compiling JS

```
./protoc -I=/Users/johannHartmann\ 1/Documents/Code/mvp_tee/buffer_compiler/bin  --js_out=import_style=commonjs,binary:. /Users/johannHartmann\ 1/Documents/Code/mvp_tee/buffer_compiler/bin/dataJS.proto
```
