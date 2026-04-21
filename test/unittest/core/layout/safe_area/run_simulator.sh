#!/bin/bash
# Copyright (c) 2026 Huawei Device Co., Ltd.
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

# =============================================================================
# ignoreLayoutSafeArea Layout Scheduling Simulator - One-Click Runner
# =============================================================================
#
# Usage:
#   ./run_simulator.sh              # Default: run JS version with node
#   ./run_simulator.sh --ts         # Run TS version with npx ts-node
#   ./run_simulator.sh --data <path> # Use a custom JSON data file
#
# Files:
#   ignore_layout_simulator.ts      - TypeScript simulator source (requires ts-node)
#   ignore_layout_simulator.js      - JavaScript simulator source (runs with plain Node.js)
#   ignore_layout_test_data.json    - Test case data (22 NodeConfig trees + known-correct expectations)
#
# Prerequisites:
#   - node (>= 14)       : Required for JS mode
#   - npx + ts-node       : Required for TS mode (npm install -g ts-node typescript)
#
# Examples:
#   chmod +x run_simulator.sh
#   ./run_simulator.sh                                    # Quick run
#   ./run_simulator.sh --ts                               # TS mode
#   ./run_simulator.sh --data /tmp/my_test_data.json      # Custom data
#   ./run_simulator.sh --ts --data /tmp/my_test_data.json # TS + custom data
# =============================================================================

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"

USE_TS=false
CUSTOM_DATA=""

while [[ $# -gt 0 ]]; do
    case "$1" in
        --ts)
            USE_TS=true
            shift
            ;;
        --data)
            CUSTOM_DATA="$2"
            shift 2
            ;;
        -h|--help)
            awk 'NR>1 && /^# /{print} NR>3 && !/^#/{exit}' "$0" | sed 's/^# \?//'
            exit 0
            ;;
        *)
            echo "Unknown option: $1"
            echo "Run with --help for usage."
            exit 1
            ;;
    esac
done

DATA_FILE="${CUSTOM_DATA:-${SCRIPT_DIR}/ignore_layout_test_data.json}"

if [[ ! -f "$DATA_FILE" ]]; then
    echo "Error: JSON data file not found: $DATA_FILE"
    exit 1
fi

if $USE_TS; then
    SIMULATOR="${SCRIPT_DIR}/ignore_layout_simulator.ts"
    if [[ ! -f "$SIMULATOR" ]]; then
        echo "Error: TS simulator not found: $SIMULATOR"
        exit 1
    fi
    if ! command -v npx &>/dev/null; then
        echo "Error: npx not found. Install Node.js first."
        exit 1
    fi
    echo "=== Running TS simulator (ts-node) ==="
    echo "  Simulator : $SIMULATOR"
    echo "  Data      : $DATA_FILE"
    echo ""
    npx ts-node "$SIMULATOR" "$DATA_FILE"
else
    SIMULATOR="${SCRIPT_DIR}/ignore_layout_simulator.js"
    if [[ ! -f "$SIMULATOR" ]]; then
        echo "Error: JS simulator not found: $SIMULATOR"
        exit 1
    fi
    if ! command -v node &>/dev/null; then
        echo "Error: node not found. Install Node.js first."
        exit 1
    fi
    echo "=== Running JS simulator (node) ==="
    echo "  Simulator : $SIMULATOR"
    echo "  Data      : $DATA_FILE"
    echo ""
    node "$SIMULATOR" "$DATA_FILE"
fi
