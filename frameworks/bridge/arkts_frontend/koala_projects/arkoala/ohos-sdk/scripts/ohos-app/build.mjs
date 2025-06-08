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

import path from "path"
import fs from "fs"
import { ohProjectConf } from "./../ohconf.mjs"
import { execCmd, lazy, platformPath } from "../utils.mjs"

const LZ_OHCONF = lazy(ohConfPath => ohProjectConf(ohConfPath))

const LZ_TOOLS = lazy(() => {
    const tools = platformPath(process.env["DEVECO_TOOLS_HOME"])
    if (!fs.existsSync(tools)) {
        console.error("> Error: DEVECO_TOOLS_HOME env variable is not set (find it here: <DEVECO>/tools)")
        process.exit(1)
    }
    return tools
})

export async function build(options) {
    process.env["DEVECO_SDK_HOME"] = platformPath(process.env["DEVECO_SDK_HOME"])

    LZ_OHCONF(options.ohConf)

    const extraOptions = options.extraOptions ? options.extraOptions.split(",") : []

    if (options.installOhpmDeps || options.installOhpmDepsOnly) {
        console.log("> Installing ohpm deps...")
        await execCmd("bash",
            [`"${path.join(LZ_TOOLS(), "ohpm/bin/ohpm")}"`,
            "install",
            "--all",
            "--strict_ssl",
            "false",
            ...extraOptions],
            { instantLogging: true, logCmdArgs: options.verbose }
        )

        if (options.installOhpmDepsOnly)
            return
    }

    console.log("> Building...")
    await execCmd("node",
        [`"${path.join(LZ_TOOLS(), "hvigor/bin/hvigorw.js")}"`,
            "--mode", "module",
            "-p", `module=${LZ_OHCONF().moduleName()}@${options.mod === "app" ? "default" : "ohosTest"}`,
            "-p", "product=default",
            "-p", "requiredDeviceType=default",
            "--no-parallel", "--no-incremental", "--no-daemon",
            "assembleHap",
            ...extraOptions],
        { instantLogging: true, logCmdArgs: options.verbose }
    )
}
