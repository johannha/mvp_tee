# Working with Asylo

###Recommended to work with preconfigured Docker Image:

Installation and run with: `docker run -it --rm gcr.io/asylo-framework/asylo`

###Running the hello world example

Make sure you are in the directory including the WORKSPACE file to run bazel successfully!

local path: /Users/johannHartmann 1/Documents/Code/mvp_tee/tee

```bash
docker run -it --rm \
    -v bazel-cache:/root/.cache/bazel \
    -v "/Users/johannHartmann 1/Documents/Code/mvp_tee/tee":/opt/my-project \
    -v "/Users/johannhartmann 1/Documents/Code/mvp_tee/workload_generator/output":/wg/output \
    -v "/Users/johannhartmann 1/Documents/Code/mvp_tee/tee/output":/tee/output \
    -w /opt/my-project \
    gcr.io/asylo-framework/asylo \
    bazel run //hello_world:hello_world_sgx_sim
```

This is loading the enclave in simulation mode.

###Running enclave on real SGX hardware

```bash
docker run -it --rm \
    -v bazel-cache:/root/.cache/bazel \
    -v "${MY_PROJECT}":/opt/my-project \
    -v /var/run/aesmd/aesm.socket:/var/run/aesmd/aesm.socket \
    -w /opt/my-project \
    --device=/dev/isgx \
    gcr.io/asylo-framework/asylo \
    bazel run //hello_world:hello_world_sgx_sim -- --names="${NAMES}"
```
