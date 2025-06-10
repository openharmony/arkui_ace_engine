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

import { ensureExists, ohConf } from "../ohconf.mjs"
import { execCmd, lazy } from "../utils.mjs"
import { testOhConf } from "./common.mjs"

const LZ_OHCONF = lazy(ohConfPath => ohConf(ohConfPath))

export async function build(options) {
    const tests = LZ_OHCONF(options.ohConf).value('test', true)
    const cwd = process.cwd()

    for (const test of tests) {
        ensureExists(test)
        const conf = testOhConf(test)
        const buildCommands = conf.value('build')

        process.chdir(test)
        console.log(`> Building tests at '${test}'...`)
        for (const cmd of buildCommands) {
            console.log(`> ...command: ${cmd}`)
            const split = cmd.split(" ")
            const cmdName = split[0]
            const cmdArgs = split.splice(1)
            await execCmd(cmdName, cmdArgs, { instantLogging: true })
        }
    }
    process.chdir(cwd)
}
