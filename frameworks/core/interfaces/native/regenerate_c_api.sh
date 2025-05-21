#!/bin/bash
# Copyright (c) 2024 Huawei Device Co., Ltd.
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

DTS_DIR_ARG=$1
DEST_DIR_ARG=$2
TMP_DIR_ARG=$3
GENERATOR_ARG=$4
OHOS_DIR_ARG=$5

OHOS_DIR=$(realpath ${OHOS_DIR_ARG:=../../../../../../..})

if [[ ! -d $IDLIZE_PATH && "x$IDLIZE_VER" == "x" ]]; then
    echo "Please define IDLIZE_PATH environment that points to idlize source directory."
    echo "Or define IDLIZE_VER environment that points to version in repository."
    lv=`npm view @idlizer/arkgen dist-tags.latest`
    nv=`npm view @idlizer/arkgen dist-tags.next`
    echo "Latest version: ${lv} Next version: ${nv}"
    exit 1
fi

DEST_DIR=$(realpath ${DEST_DIR_ARG:=.})
TMP_DIR=${TMP_DIR_ARG:=${OHOS_DIR}/out/libace_c_api_generated}
INT_INF="${TMP_DIR}/interface"
IDL_DIR="${TMP_DIR}/idl"
ETS_DIR=${DTS_DIR_ARG:=${INT_INF}/api/arkui/component,${INT_INF}/api/global}
BASE_DIR="${INT_INF}/api,${INT_INF}/kits,${INT_INF}/arkts"
if [[ ! -d $IDLIZE_PATH ]]; then
#    PREPROCESSOR="npx @idlizer/dtsgen@$IDLIZE_VER --run-preprocessor"
    TOIDL="npx --yes @idlizer/etsgen@$IDLIZE_VER --ets2idl"
    GENERATOR=${GENERATOR_ARG:=npx --yes @idlizer/arkgen@$IDLIZE_VER --idl2peer}
else
    # Use the below to run generator from your idlize workspace
#    PREPROCESSOR="node $IDLIZE_PATH/dtsgen --run-preprocessor"
    TOIDL="node $IDLIZE_PATH/etsgen --ets2idl"
    GENERATOR=${GENERATOR_ARG:=node $IDLIZE_PATH/arkgen/lib/index.js --idl2peer}
fi

PREPROCESSOR1="node ${OHOS_DIR}/interface/sdk-js/build-tools/handleApiFiles.js --type ets2"

API_VER=${API_VER:=99}

echo "Preprocessing SDK..."

rm -rf ${TMP_DIR}
mkdir -p ${TMP_DIR}

${PREPROCESSOR1} \
    --path ${OHOS_DIR}/interface/sdk-js --output ${INT_INF}
#    --input-dir ${OHOS_DIR}/interface/sdk-js --output-dir ${INT_INF}

pushd ${OHOS_DIR}/interface/sdk-js/build-tools/arkui_transformer
npm run compile:arkui
node . --input-dir ${INT_INF}/api/@internal/component/ets/ --target-dir ${INT_INF}/api/arkui/component/
popd

echo "Generating IDL..."
${TOIDL} \
    --base-dir ${INT_INF}/api --input-dir ${ETS_DIR} --output-dir ${IDL_DIR}

echo "Generating C API from ${ETS_DIR} to ${DEST_DIR} with ${GENERATOR}"

${GENERATOR} \
    --output-dir ${TMP_DIR} \
    --base-dir ${IDL_DIR} \
    --input-files $(find ${IDL_DIR} -type f) \
    --generator-target libace \
    --libace-destination ${DEST_DIR} \
    --api-version ${API_VER}
