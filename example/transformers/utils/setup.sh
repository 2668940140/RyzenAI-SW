#!/usr/bin/bash

export TRANSFORMERS_ROOT=$(pwd)
conda env create --file=env.yaml
conda activate ryzenai-transformers