#!/usr/bin/env bash
set -euo pipefail
# Optional ASan/UBSan run. Regular builds use capi_page_text_test, which is
# included in linux_unittest_capi and the host unittest group.
repo=$(cd "$(dirname "$0")/../../../.." && pwd)
oh_root=$(cd "$repo/../../.." && pwd)
out=${PAGE_TEXT_TEST_OUT:-/tmp/arkui-page-text-tests}
mkdir -p "$out"
gtest="$oh_root/third_party/googletest/googletest"
# Compile the original getter verbatim; the other node_utils functions require
# platform-only headers. The product build verifies the complete source file.
python3 "$repo/test/unittest/capi/utils/extract_page_text_error_getter.py" \
  "$repo/interfaces/native/node/node_utils.cpp" "$out/original_error_getter.cpp"
g++ -std=c++17 -g -O1 -fsanitize=address,undefined -fno-omit-frame-pointer -pthread \
  -I"$repo" -I"$repo/frameworks" -I"$repo/interfaces/native" \
  -I"$repo/interfaces/inner_api/ace_kit/include" -I"$oh_root/third_party/bounds_checking_function/include" \
  -I"$gtest/include" -I"$gtest" \
  "$repo/interfaces/native/ui_info_collection.cpp" "$repo/interfaces/native/ui_json_wrapper.cpp" \
  "$repo/interfaces/native/native_error_message_wrapper.cpp" "$out/original_error_getter.cpp" \
  "$repo/frameworks/core/interfaces/native/utility/error_message_manager.cpp" \
  "$repo/test/unittest/capi/utils/page_text_capi_test.cpp" \
  "$gtest/src/gtest-all.cc" "$gtest/src/gtest_main.cc" \
  -Wl,--wrap=malloc -Wl,--wrap=realloc -o "$out/page_text_test"
"$out/page_text_test" --gtest_filter='PageTextCapiTest.*:PageTextJsonTest.*:UIJsonWrapperTest.*' \
  --gtest_output="xml:$out/page_text_test.xml"
