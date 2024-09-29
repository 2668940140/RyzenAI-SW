#!/bin/bash

# This sets up the env of XRT
source ~/scripts/xilinx-setup.sh

set -e

# Check if CONDA_PREFIX is set
if [[ -z "$CONDA_PREFIX" ]]; then
    conda activate ryzenai-transformers
fi

# Set the root directory for the dependency
CWD="$(pwd)"
AIERT_CMAKE_PATH="$CWD/ext/aie-rt/driver/src"
AIECTRL_CMAKE_PATH="$CWD/ext/aie_controller"
DD_CMAKE_PATH="$CWD/ext/DynamicDispatch"
XRT_DIR="$CWD/third_party/xrt-ipu"

# Check if the directories exist
for DIR in "$AIERT_CMAKE_PATH" "$AIECTRL_CMAKE_PATH" "$DD_CMAKE_PATH" "$XRT_DIR"; do
    if [[ ! -d "$DIR" ]]; then
        echo "Error: Directory $DIR does not exist."
        exit 1
    fi
done

# Invoke cmake to build and install the dependencies
cmake -S "$AIERT_CMAKE_PATH" -B build_aiert -DXAIENGINE_BUILD_SHARED=OFF -DCMAKE_INSTALL_PREFIX="$CONDA_PREFIX"
cmake --build build_aiert --target install --config Release

cmake -S "$AIECTRL_CMAKE_PATH" -B build_aiectrl -DCMAKE_PREFIX_PATH="$CONDA_PREFIX" -DCMAKE_INSTALL_PREFIX="$CONDA_PREFIX"
cmake --build build_aiectrl --target install --config Release

# This needs the XRT package to be installed and XRT env to be set
cmake -S "$DD_CMAKE_PATH" -B build_dd -DCMAKE_PREFIX_PATH="$CONDA_PREFIX" -DCMAKE_INSTALL_PREFIX="$CONDA_PREFIX"
cmake --build build_dd --target install --config Release

echo "Build and installation completed successfully."
