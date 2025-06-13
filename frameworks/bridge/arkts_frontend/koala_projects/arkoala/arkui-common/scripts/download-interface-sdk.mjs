/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

import * as fs from "node:fs"
import { execSync } from "node:child_process"
import path from "node:path"
import { fileURLToPath } from 'url'

const __filename = fileURLToPath(import.meta.url)
const __dirname = path.dirname(__filename)

const sdkInfo = JSON.parse(fs.readFileSync(path.join(__dirname, "ohos-sdk.json")))

const dir = "./interface_sdk-js"

if (!fs.existsSync(dir)) {
    console.log("> Downloading sdk")
    execSync("git clone https://gitee.com/openharmony/interface_sdk-js.git") || process.exit(1)
}

const hash = execSync(`cd ${dir} && git rev-parse HEAD`).toString().trim()
if (hash !== sdkInfo.hash) {
    console.log("> interface_sdk-js HEAD...")
    execSync(`cd ${dir} && git fetch origin && git checkout ${sdkInfo.hash}`)
} else {
    console.log("> interface_sdk-js HEAD: " + hash.substring(0, 9))
}
