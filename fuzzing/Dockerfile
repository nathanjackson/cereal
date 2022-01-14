FROM ubuntu:20.04 as builder

RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y cmake g++ libboost-dev \
        libboost-serialization-dev

ADD ./ /cereal
WORKDIR /cereal
RUN rm -rf build && mkdir build
WORKDIR /cereal/build
RUN cmake -DCMAKE_BUILD_TYPE=Debug -DBUILD_UNIT_TESTS=OFF .. && \
    make -j$(grep -c processor /proc/cpuinfo)

FROM ubuntu:20.04

RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y libc6-dbg && \
    rm -rf /var/lib/apt/lists/*

COPY --from=builder /cereal/build/fuzzing/symmetry_fuzz_test /

