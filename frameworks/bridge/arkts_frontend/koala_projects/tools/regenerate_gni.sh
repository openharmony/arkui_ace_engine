#!/bin/bash

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
