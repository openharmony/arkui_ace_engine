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

OHOS_DIR=$(readlink -f ${OHOS_DIR_ARG:=../../../../../../..})

if [[ ! -d $IDLIZE_PATH && "x$IDLIZE_VER" == "x" ]]; then
    echo "Please define IDLIZE_PATH environment that points to idlize source directory."
    echo "Or define IDLIZE_VER environment that points to version in repository."
    lv=`npm view @azanat/idlize dist-tags.latest`
    nv=`npm view @azanat/idlize dist-tags.next`
    echo "Latest version: ${lv} Next version: ${nv}"
    exit 1
fi

DEST_DIR=${DEST_DIR_ARG:=../../../../test}
DTS_DIR=${DTS_DIR_ARG:=${OHOS_DIR}/interface/sdk-js/api/@internal/component/ets,${OHOS_DIR}/interface/sdk-js/api/global}
TMP_DIR=${TMP_DIR_ARG:=${OHOS_DIR}/out/libace_c_api_generated}
if [[ ! -d $IDLIZE_PATH ]]; then
    GENERATOR=${GENERATOR_ARG:=npx --yes @azanat/idlize@$IDLIZE_VER --dts2peer}
else
    # Use the below to run generator from your idlize workspace
    GENERATOR=${GENERATOR_ARG:=node $IDLIZE_PATH/lib/index.js --dts2peer}
fi

API_VER=${API_VER:=99}

echo "Generating C API from ${DTS_DIR} to ${DEST_DIR} with ${GENERATOR}"

#TMP_DIR=`mktemp -d`
#OUT_DIR=${DEST_DIR}
OUT_DIR=${TMP_DIR}

${GENERATOR} \
    --ace-types ace_types.json5 \
    --output-dir ${TMP_DIR} \
    --input-dir ${DTS_DIR} \
    --generator-target libaceut \
    --libace-destination ${OUT_DIR} \
    --api-version ${API_VER}

# Re-format everything
cp ../../../../.clang-format ${OUT_DIR}
pushd ${OUT_DIR}/unittest/capi/modifiers/generated/ >/dev/null
${OHOS_DIR}/prebuilts/build-tools/linux-x86/bin/gn format modifiers.gni
${OHOS_DIR}/prebuilts/clang/ohos/linux-x86_64/llvm/bin/clang-format -i *.cpp *.h
popd >/dev/null
rm ${OUT_DIR}/.clang-format
# Copy only changed files
rsync -cqr ${OUT_DIR}/ ${DEST_DIR}
rm -rf ${TMP_DIR}
