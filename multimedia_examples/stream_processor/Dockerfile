FROM gcc:latest

# Install dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    pkg-config \
    libavformat-dev \
    libavcodec-dev \
    libavutil-dev \
    libswscale-dev \
    libavfilter-dev \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace

# Copy source code
ARG SOURCE_CODE="./src"
COPY ${SOURCE_CODE} ${SOURCE_CODE}
COPY CMakeLists.txt .

# Build application
#RUN rm -rf ./build \
#    && cmake -S . -B build \
#    && cmake --build build
