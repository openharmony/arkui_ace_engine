#!/bin/bash
# Copyright (C) 2026 Huawei Device Co., Ltd.
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

# Build libarkoala_native_ani.so stub library for TDD testing on Linux host

# Get script directory (absolute path)
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
STUB_SRC="${SCRIPT_DIR}/arkoala_native_ani_stub.cpp"

# Find arkcompiler directory (relative to ace_engine)
ACE_ENGINE_DIR="$(cd "${SCRIPT_DIR}/../../../../../.." && pwd)"
WORKSPACE_ROOT="$(cd "${ACE_ENGINE_DIR}/../../../.." && pwd)"
OUT_DIR="${WORKSPACE_ROOT}/arkcompiler/runtime_core/static_core/out/lib"
OUT_SO="${OUT_DIR}/libarkoala_native_ani.so"

echo "=== Building ANI stub library ==="
echo "Source: $STUB_SRC"
echo "Output: $OUT_SO"

# Check if stub source exists
if [ ! -f "$STUB_SRC" ]; then
    echo "✗ Error: Stub source not found: $STUB_SRC"
    exit 1
fi

# Create output directory if needed
mkdir -p "$OUT_DIR"

# Compile
cd "$OUT_DIR"
g++ -shared -fPIC -o "$OUT_SO" \
    -I../../plugins/ets/runtime/ani/ \
    "$STUB_SRC"

if [ $? -eq 0 ]; then
    echo "✓ Stub library built successfully"
    file "$OUT_SO"
else
    echo "✗ Build failed"
    exit 1
fi
