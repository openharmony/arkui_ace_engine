/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

import { ohProjectConf } from "./../ohconf.mjs"
import { execCmd, lazy, platformPath } from "../utils.mjs"

const LZ_OHCONF = lazy(ohConfPath => ohProjectConf(ohConfPath))
const LZ_HDC = lazy(() => LZ_OHCONF().hdcPath())
const LZ_HDC_OPTIONS = lazy(hdcExtraOpts => hdcExtraOpts ? hdcExtraOpts.split(" ") : [])

async function execHDC(args, options = {}) {
    return execCmd(LZ_HDC(), [...LZ_HDC_OPTIONS(), ...args], {
        ...options,
        instantLogging: true,
    })
}

export async function getPID(bundleName = LZ_OHCONF().bundleName()) {
    const out = await execHDC(["shell", `ps -ef | awk '$NF=="${bundleName}" {print $2}'`])
    return out  
}

export async function logByPID(pid) {
    await execHDC(["shell", `hilog -P ${pid}`])
}

export async function allLog() {
    await execHDC(["shell", "hilog"])
}

export async function log(options) {
    const { all, bundleName } = options
    if (all) {
        await allLog()
    } else {
        const pid = await getPID(bundleName)
        await logByPID(pid)
    }
}