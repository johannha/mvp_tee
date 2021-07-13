# Working with Asylo 

###Recommended to work with preconfigured Docker Image:

Installation and run with: `docker run -it --rm gcr.io/asylo-framework/asylo`


###Running the hello world example 

Make sure you are in the directory including the WORKSPACE file to run bazel successfully!

```bash
docker run -it --rm \
    -v bazel-cache:/root/.cache/bazel \
    -v "${MY_PROJECT}":/opt/my-project \
    -w /opt/my-project \
    gcr.io/asylo-framework/asylo \
    bazel run //hello_world:hello_world_sgx_sim -- --words="Bürostuhl,Fensterbrett"
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



