#!/bin/bash
# Copyright (c) 2025 Huawei Device Co., Ltd.
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

execute_script() {
    local working_dir="$1"
    local script_path="$2"
    shift 2
    local original_dir=$(pwd)
    cd "$working_dir" || {
        echo "错误: 无法进入工作目录 $working_dir"
        return 1
    }
    "$script_path" "$@"
    local result=$?
    cd "$original_dir"

    return $result
}

# arkoala-arkts preprocess
execute_script "./arkoala-arkts" "../tools/annotate.py" "." "annotate-config.json"
execute_script "./arkoala-arkts" "../../arkoala/process_arkoala.py" "."
# runtime preprocess
execute_script "./incremental/runtime" "../../tools/annotate.py" "." "annotate-config.json"
# regenerate all gni files
execute_script "./arkoala-arkts" "../tools/gen_gni.py" "--json" "arktsconfig-gn.json" "--output" "components.gni" "--gn-tool" "../../../../../../../../prebuilts/build-tools/linux-x86/bin/gn"
execute_script "./incremental/runtime" "../../tools/gen_gni.py" "--json" "arktsconfig-gn.json" "--output" "runtime.gni" "--gn-tool" "../../../../../../../../../prebuilts/build-tools/linux-x86/bin/gn"
execute_script "./incremental/common" "../../tools/gen_gni.py" "--json" "arktsconfig.json" "--output" "common.gni" "--gn-tool" "../../../../../../../../../prebuilts/build-tools/linux-x86/bin/gn"
execute_script "./incremental/compat" "../../tools/gen_gni.py" "--json" "arktsconfig.json" "--output" "compat.gni" "--gn-tool" "../../../../../../../../../prebuilts/build-tools/linux-x86/bin/gn"
execute_script "./interop" "../tools/gen_gni.py" "--json" "arktsconfig.json" "--output" "interop.gni" "--gn-tool" "../../../../../../../../prebuilts/build-tools/linux-x86/bin/gn"
