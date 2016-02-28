#!/bin/bash

SOURCE_PATH="${1}"

BUILD_SCRIPT="${SOURCE_PATH}/tools/build.sh"
RUN_SCRIPT="${SOURCE_PATH}/tools/run.sh"

BUILD_TYPE="${2}"
VALUES_TYPE="${3}"
TIME_STEPS="${4}"
GRID_DIMENSION="${5}"
PRINT_MESSAGE="${6}"
PARALLEL_GRID="${7}"
PARALLEL_BUFFER="${8}"
EXECUTABLE="${9}"
NUMBER_PROCESSES="${10}"

BUILD_DIR=$(pwd)
BUILD_DIR="${BUILD_DIR}/${BUILD_TYPE}"

${BUILD_SCRIPT} ${SOURCE_PATH} ${BUILD_DIR} ${BUILD_TYPE} ${VALUES_TYPE} ${TIME_STEPS} ${GRID_DIMENSION} ${PRINT_MESSAGE} ${PARALLEL_GRID} ${PARALLEL_BUFFER}

STATUS_CODE=$?

if [ $STATUS_CODE -ne 0 ]; then
  echo "Build failed"
  exit 1
fi


${RUN_SCRIPT} ${BUILD_DIR} ${EXECUTABLE} ${PARALLEL_GRID} ${NUMBER_PROCESSES}

STATUS_CODE=$?

if [ $STATUS_CODE -ne 0 ]; then
  echo "Run failed"
  exit 1
fi

exit 0
