/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

import path from "path"
import chalk from "chalk"
import { OHSDK, SCRIPTS_DIR } from "./common.mjs"
import { copyDirSync } from "../../ohos-sdk/scripts/utils.mjs"

function log(msg) {
    console.log(chalk.green(msg))
}

async function main() {

    const componentSrc = path.join(SCRIPTS_DIR, "../fake-ohos-declarations/component")
    const componentDst = path.join(OHSDK, `HarmonyOS-NEXT-DB1/openharmony/ets/component`)

    const apiSrc = path.join(SCRIPTS_DIR, "../fake-ohos-declarations/api")
    const apiDst = path.join(OHSDK, `HarmonyOS-NEXT-DB1/openharmony/ets/api`)

    console.log(OHSDK)

    console.log(chalk.green(`> Copying from '${componentSrc}' to '${componentDst}'`))
    copyDirSync(componentSrc, componentDst)

    console.log(chalk.green(`> Copying from '${apiSrc}' to '${apiDst}'`))
    copyDirSync(apiSrc, apiDst)
}

await main()
