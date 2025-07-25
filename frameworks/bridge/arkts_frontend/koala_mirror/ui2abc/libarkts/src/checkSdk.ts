/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import * as fs from "fs"
import * as path from "path"

function reportErrorAndExit(message: string): never {
    console.error(message)
    process.exit(1)
}

export function checkSDK() {
    const panda = process.env.PANDA_SDK_PATH
    if (!panda)
        reportErrorAndExit(`Variable PANDA_SDK_PATH is not set, please fix`)
    if (!fs.existsSync(path.join(panda, 'package.json')))
        reportErrorAndExit(`Variable PANDA_SDK_PATH not points to SDK`)
    const packageJson = JSON.parse(fs.readFileSync(path.join(panda, 'package.json')).toString())
    const version = packageJson.version as string
    if (!version)
        reportErrorAndExit(`version is unknown`)
    const packageJsonOur = JSON.parse(fs.readFileSync(path.join(__dirname, '..', 'package.json')).toString())
    const expectedVersion = packageJsonOur.config.panda_sdk_version
    if (expectedVersion && expectedVersion != "next" && version != expectedVersion)
        console.log(`WARNING: Panda SDK version "${version}" doesn't match expected "${expectedVersion}"`)
    else
        console.log(`Use Panda ${version}`)
}
