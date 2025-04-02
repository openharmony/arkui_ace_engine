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

OHOS_DIR=${OHOS_DIR_ARG:=../../../../../../..}

if [[ ! -d $IDLIZE_PATH && "x$IDLIZE_VER" == "x" ]]; then
    echo "Please define IDLIZE_PATH environment that points to idlize source directory."
    echo "Or define IDLIZE_VER environment that points to version in repository."
    lv=`npm view @idlizer/arkgen dist-tags.latest`
    nv=`npm view @idlizer/arkgen dist-tags.next`
    echo "Latest version: ${lv} Next version: ${nv}"
    exit 1
fi

DEST_DIR=${DEST_DIR_ARG:=.}
DTS_DIR=${DTS_DIR_ARG:=${OHOS_DIR}/interface/sdk-js/api/@internal/component/ets,${OHOS_DIR}/interface/sdk-js/api/global}
TMP_DIR=${TMP_DIR_ARG:=${OHOS_DIR}/out/libace_c_api_generated}
if [[ ! -d $IDLIZE_PATH ]]; then
    GENERATOR=${GENERATOR_ARG:=npx --yes @idlizer/arkgen@$IDLIZE_VER --dts2peer}
else
    # Use the below to run generator from your idlize workspace
    GENERATOR=${GENERATOR_ARG:=node $IDLIZE_PATH/arkgen/lib/index.js --dts2peer}
fi

API_VER=${API_VER:=99}

echo "Generating C API from ${DTS_DIR} to ${DEST_DIR} with ${GENERATOR}"

${GENERATOR} \
    --output-dir ${TMP_DIR} \
    --input-dir ${DTS_DIR} \
    --generator-target libace \
    --libace-destination ${DEST_DIR} \
    --api-version ${API_VER}
