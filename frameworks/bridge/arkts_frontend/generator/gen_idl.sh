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

USE_LINTER=0

CUR_PATH=$(dirname $0)
OHOS_DIR=$(realpath ${CUR_PATH}/../../../../../../..)

TMP_DIR=${OHOS_DIR}/out/libace_c_api_generated
INT_INF="${TMP_DIR}/interface"
IDL_DIR="${TMP_DIR}/idl"
ETS_DIR=${DTS_DIR_ARG:=${INT_INF}/api/arkui/component,${INT_INF}/api/global}
BASE_DIR="${INT_INF}/api" # ,${INT_INF}/kits,${INT_INF}/arkts"

if [[ ! -d $IDLIZE_PATH && "x$IDLIZE_VER" == "x" ]]; then
    echo "Please define IDLIZE_PATH environment that points to idlize source directory."
    echo "Or define IDLIZE_VER environment that points to version in repository."
    lv=`npm view @idlizer/etsgen dist-tags.latest`
    nv=`npm view @idlizer/etsgen dist-tags.next`
    echo "Latest version: ${lv} Next version: ${nv}"
    exit 1
fi

if [[ ! -d ${OHOS_DIR}/interface/sdk-js/build-tools/arkui_transformer/node_modules ]]; then
    echo "Run build/prebuilts_download.py script first!"
    exit 1
fi

if [[ ! -d $IDLIZE_PATH ]]; then
    TOIDL="npx --yes @idlizer/etsgen@$IDLIZE_VER --ets2idl"
    LINTER="npx --yes @idlizer/idlinter@$IDLIZE_VER"
else
    TOIDL="node $IDLIZE_PATH/etsgen --ets2idl"
    LINTER="node $IDLIZE_PATH/idlinter"
fi

rm -rf ${TMP_DIR}
mkdir -p ${TMP_DIR}

echo "Preprocessing SDK..."

# Step 1
node ${OHOS_DIR}/interface/sdk-js/build-tools/handleApiFiles.js --type ets2 \
    --path ${OHOS_DIR}/interface/sdk-js --output ${INT_INF}

# Step 2
pushd ${OHOS_DIR}/interface/sdk-js/build-tools/arkui_transformer
if [[ ! -f build/arkui_transformer.js ]]; then
    npm run compile:arkui
fi
node . --input-dir ${INT_INF}/api/@internal/component/ets/ --target-dir ${INT_INF}/api/arkui/component/ --use-memo-m3
popd

echo "Generating IDL..."

${TOIDL} \
    --base-dir ${BASE_DIR} --input-dir ${ETS_DIR} --output-dir ${IDL_DIR} \
    --ignore-default-config --options-file $CUR_PATH/etsgen-config.json

cp $CUR_PATH/idl-sdk-other/* ${IDL_DIR}
cp $CUR_PATH/idl-custom/* ${IDL_DIR}

if [[ $USE_LINTER == 1 ]]; then
    echo "Run linter..."
    $LINTER --check ${IDL_DIR}
fi
