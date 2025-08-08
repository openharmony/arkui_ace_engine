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

CUR_PATH=$(dirname $0)
OHOS_DIR=$(realpath ${CUR_PATH}/../../../../../../..)

if [[ ! -d $IDLIZE_PATH && "x$IDLIZE_VER" == "x" ]]; then
    echo "Please define IDLIZE_PATH environment that points to idlize source directory."
    echo "Or define IDLIZE_VER environment that points to version in repository."
    lv=`npm view @idlizer/arkgen dist-tags.latest`
    nv=`npm view @idlizer/arkgen dist-tags.next`
    echo "Latest version: ${lv} Next version: ${nv}"
    exit 1
fi

TMP_DIR=${TMP_DIR_ARG:=${OHOS_DIR}/out/libace_c_api_generated}
IDL_DIR="${TMP_DIR}/idl"
DEST_DIR="${TMP_DIR}/gen"
rm -rf ${DEST_DIR}
if [[ ! -d $IDL_DIR ]]; then
    echo "IDL files are not found! Run gen_idl.sh first."
    exit 1
fi
if [[ ! -d $IDLIZE_PATH ]]; then
    GENERATOR=${GENERATOR_ARG:=npx --yes @idlizer/arkgen@$IDLIZE_VER --idl2peer}
else
    # Use the below to run generator from your idlize workspace
    GENERATOR=${GENERATOR_ARG:=node $IDLIZE_PATH/arkgen/lib/index.js --idl2peer}
fi

API_VER=${API_VER:=99}

CONFIGS=${CUR_PATH}/arkgen-config.json,${CUR_PATH}/arkgen-idl-config.json,${CUR_PATH}/arkgen-config-arkui.json

echo "Generating C API from ${ETS_DIR} to ${DEST_DIR} with ${GENERATOR}"

${GENERATOR} \
    --ignore-default-config \
    --options-file ${CONFIGS} \
    --reference-names ${CUR_PATH}/ets-sdk.refs.json \
    --use-memo-m3 \
    --language arkts \
    --only-integrated \
    --arkts-extension .ets \
    --output-dir ${DEST_DIR} \
    --base-dir ${IDL_DIR} \
    --input-files $(find ${IDL_DIR} -type f) \
    --api-version ${API_VER}


NATIVE_DIR=${OHOS_DIR}/foundation/arkui/ace_engine/frameworks/core/interfaces/native

# Copy native C API part
cp ${DEST_DIR}/libace/generated/interface/arkoala_api_generated.h ${NATIVE_DIR}/generated/interface/
cp ${DEST_DIR}/libace/generated/interface/arkoala-macros.h ${NATIVE_DIR}/generated/interface/
${OHOS_DIR}/prebuilts/build-tools/linux-x86/bin/gn format --stdin <${DEST_DIR}/libace/generated/interface/node_interface.gni | uniq | sed 's/include_generated_sources = false/include_generated_sources = true/' >${NATIVE_DIR}/generated/interface/node_interface.gni
sed '/SetDummyLogger/d' <${DEST_DIR}/libace/implementation/all_modifiers.cpp >${NATIVE_DIR}/implementation/all_modifiers.cpp
cp ${DEST_DIR}/libace/utility/generated/converter_generated.h ${NATIVE_DIR}/utility/generated/

GEN_DIR=${OHOS_DIR}/foundation/arkui/generated/frameworks/core/interfaces/native
if [[ -d ${GEN_DIR} ]]; then
    cp -r ${DEST_DIR}/libace/generated ${GEN_DIR}/
    cp -r ${DEST_DIR}/libace/implementation ${GEN_DIR}/
    cp -r ${DEST_DIR}/libace/utility ${GEN_DIR}/
    ${OHOS_DIR}/prebuilts/build-tools/linux-x86/bin/gn format --stdin <${DEST_DIR}/libace/generated/interface/node_interface.gni | uniq >${GEN_DIR}/generated/interface/node_interface.gni
fi

# Copy TS part
TS_DIR=${CUR_PATH}/../koala_mirror
mkdir -p ${TS_DIR}
cp -r ${DEST_DIR}/sig/arkoala-arkts ${TS_DIR}/
