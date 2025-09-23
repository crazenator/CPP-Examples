FROM gcc:latest

# Install required libraries
RUN apt-get update && \
    apt-get install -y \
    libpcap-dev \
    cmake \
    ninja-build \
    gdb

# Clean-up to reduce image size
RUN rm -rf /var/lib/apt/lists/*


# Create working directory
WORKDIR /workspace

# Copy required files
ARG SOURCE_CODE_DIR="./src"
COPY ${SOURCE_CODE_DIR} ${SOURCE_CODE_DIR}
COPY CMakeLists.txt .

ARG APPLICATION="PcapUtility"
ENV APPLICATION=${APPLICATION}

# Remove previous build files
RUN rm -rf ./build

# Build application
RUN cmake -S . -B build -G Ninja \
    && cmake --build build

# Default command
# CMD [ "sh", "-c", "${APPLICATION}" ]
