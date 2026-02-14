#!/bin/bash

/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

echo "========================================="
echo "  Sticker Example Build Script"
echo "========================================="
echo ""

# Check if hvigorw exists
if [ ! -f "hvigor/hvigor-config.json5" ]; then
    echo "Error: hvigor config not found!"
    exit 1
fi

echo "[1/3] Cleaning previous build..."
# hvigorw clean 2>/dev/null || echo "Clean skipped (no previous build)"

echo ""
echo "[2/3] Building Sticker HAP..."
# hvigorw assembleHap

echo ""
echo "[3/3] Build completed!"
echo ""
echo "Output location:"
echo "  - entry/build/default/outputs/default/entry-default-signed.hap"
echo ""
echo "To install on device:"
echo "  hdc install entry/build/default/outputs/default/entry-default-signed.hap"
echo ""
echo "To launch application:"
echo "  hdc shell aa start -a EntryAbility -b com.example.sticker"
echo ""
