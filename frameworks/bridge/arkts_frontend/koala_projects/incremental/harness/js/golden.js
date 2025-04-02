/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

const path = require("path")
const process = require("process")

function goldenSetup(resDir, testDir) {
    const root = path.resolve(".", resDir)
    const testRoot = path.resolve(testDir)
    if (root != testRoot) {
        process.env.KOALAUI_RESOURCE_ROOT = root
    }
    process.env.KOALAUI_TEST_ROOT = path.relative(root, testRoot)
    const argGenGolden = "--gen-golden"
    for (let str of process.argv) {
        if (str.startsWith(argGenGolden)) {
            process.env.KOALAUI_TEST_GOLDEN_GEN_DIR = path.relative(root, path.resolve(testRoot, "test", "resources", "golden"))
            if (str.length > argGenGolden.length + 1) {
                const gdir = str.substring(argGenGolden.length + 1);
                if (gdir.length > 0 && gdir != "true") {
                    process.env.KOALAUI_TEST_GOLDEN_GEN_DIR = path.relative(root, path.resolve(gdir))
                }
            }
            break
        }
    }
}

exports.goldenSetup = goldenSetup
