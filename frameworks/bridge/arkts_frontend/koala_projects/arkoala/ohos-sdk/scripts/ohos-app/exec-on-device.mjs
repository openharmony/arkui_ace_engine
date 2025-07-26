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

import fs from "fs"
import path from "path"
import {
    ohProjectConf,
    PROJECT_MOD_APP
} from "../ohconf.mjs"
import { execCmd, lazy, relativePath, splitLines, assertExists } from "../utils.mjs"
import { platformName } from "../oh-sdk-utils.mjs"

const LZ_OHCONF = lazy(ohConfPath => ohProjectConf(ohConfPath))
const LZ_HDC = lazy(() => LZ_OHCONF().hdcPath())
const LZ_HDC_OPTIONS = lazy(hdcExtraOpts => hdcExtraOpts ? hdcExtraOpts.split(" ") : [])
const LZ_OPTIONS = lazy(options => options)

function init(options) {
    LZ_OHCONF(options.ohConf)
    LZ_HDC_OPTIONS(options.hdcExtraOpts)
    LZ_OPTIONS(options)
}

async function execHDC(args, options = {}) {
    return execCmd(LZ_HDC(), [...LZ_HDC_OPTIONS(), ...args],
        {
            ...options,
            shell: false,
            logCmdArgs: LZ_OPTIONS().verbose
        })
}

export async function recvImages(options) {
    init(options)

    const mod = options.mod
    const dst = options.recvImages

    const home = `/data/app/el2/100/base/${LZ_OHCONF().bundleName()}/haps/${LZ_OHCONF().moduleName(mod)}/files`
    const out = await execHDC(['shell', `find ${home} -name *.png`])
    if (out) {
        fs.mkdirSync(dst, { recursive: true })
        for (const imagePath of splitLines(out)) {
            console.log("> RecvImage:", imagePath)
            const relPath = relativePath(home, imagePath)
            const dstPath = path.join(dst, relPath)
            fs.mkdirSync(path.dirname(dstPath), { recursive: true })
            await execHDC(['file', 'recv', imagePath, dstPath])
        }
    }
}

export async function recvLogs(options) {
    init(options)

    const mod = options.mod
    const dst = options.recvLogs

    const home = `/data/app/el2/100/base/${LZ_OHCONF().bundleName()}/files/logs`
    const out = await execHDC(['shell', `find ${home} -name *.log`])
    if (out) {
        fs.mkdirSync(dst, { recursive: true })
        for (const logPath of splitLines(out)) {
            console.log("> RecvLog:", logPath)
            const relPath = relativePath(home, logPath)
            const dstPath = path.join(dst, relPath)
            fs.mkdirSync(path.dirname(dstPath), { recursive: true })
            await execHDC(['file', 'recv', logPath, dstPath])
        }
    }
}

export async function install(options) {
    init(options)

    const mod = options.mod

    const hap = LZ_OHCONF().hapPath(mod)
    assertExists(hap, "signed hap not found (use 'oh-sign' command)")

    const out = await execHDC(["install", "-r", hap])
    console.log(out)
    if (out?.includes("error") !== -1) {
        await uninstall(options)

        console.log(`> Install ${LZ_OHCONF().bundleName()}`)
        await execHDC(['install', '-r', hap], { instantLogging: true })
    }
}

export async function uninstall(options) {
    init(options)

    console.log(`> Uninstall ${LZ_OHCONF().bundleName()}`)
    await execHDC(['uninstall', LZ_OHCONF().bundleName()])
}

export async function run(options) {
    init(options)

    const mod = options.mod
    const timeout = options.runTimeout ? parseInt(options.runTimeout) : -1
    const extraOptions = options.extra
    const verbose = options.verbose

    if (mod === PROJECT_MOD_APP) {
        await execHDC(['shell', 'aa', 'start', '-a', LZ_OHCONF().abilityName(mod), '-b', LZ_OHCONF().bundleName()], { instantLogging: true })
    } else {
        let testFailed = false
        let stoppedByTimeout = false
        const timer = timeout > 0 ? setTimeout(() => {
            console.log(`> Warning: stop by timeout: ${LZ_OHCONF().bundleName()}`)
            stoppedByTimeout = true
            execHDC(['shell', 'aa', 'force-stop', LZ_OHCONF().bundleName()], { instantLogging: true })
        }, timeout) : undefined
        try {
            const startTime = Date.now()
            const golden = mod === "test-gen-golden"
            let out = await execHDC([
                'shell', 'aa', 'test',
                '-m', `${LZ_OHCONF().moduleName(mod)}`,
                '-s', 'unittest', 'OpenHarmonyTestRunner',
                '-s', 'koalaGenerateGolden', golden.toString(),
                '-s', 'timeout', '10000',
                '-b', LZ_OHCONF().bundleName(),
                extraOptions
            ], { instantLogging: verbose })
            if (out) {
                const testLog = path.join(LZ_OHCONF().root, "test.log")
                fs.writeFileSync(testLog, out)
                console.log(out)
                console.log("> Time: " + Math.round((Date.now() - startTime) / 1000) + " seconds")

                let reason = ""
                if (out.search(/OHOS_REPORT_RESULT/gi) === -1)
                    reason += "no OHOS_REPORT_RESULT; "

                if (out.search(/OHOS_REPORT_CODE:\s*-1/gi) !== -1)
                    reason += "OHOS_REPORT_CODE: -1; "

                if (out.search(/OHOS_REPORT_STATUS_CODE:\s*-1/gi) !== -1)
                    reason += "OHOS_REPORT_STATUS_CODE: -1; "

                if (out.search(/TestFinished-ResultCode:\s*-1/gi) !== -1)
                    reason += "TestFinished-ResultCode: -1; "

                if (out.search(/error:\s*failed to start user test/gi) !== -1)
                    reason += "failed to start user test; "

                if (reason !== "") {
                    console.error(`> TESTS FAILED: ${reason}`)
                    testFailed = true
                }
                else {
                    console.log("> TESTS PASSED")
                }
            }
        } finally {
            clearTimeout(timer)
            if (stoppedByTimeout || testFailed) {
                process.exit(1)
            }
        }
    }
}

export async function checkDevice(options) {
    init(options)

    const out = await execHDC(['list', 'targets']) + ""
    if (out) {
        if (options.listDevices)
            console.log(out)

        if (out.indexOf("Empty") !== -1) {
            if (platformName() === "linux") {
                console.error(
                    "> Error: no connection to a device\n" +
                    "> Hint: execute the following commands to repair:\n" +
                    `$ sudo ${LZ_HDC()} kill server\n` +
                    "$ sudo rm /tmp/.HDCServer.pid\n" +
                    "$ sudo pkill hdc\n" +
                    `$ ${LZ_HDC()} start server\n` +
                    `$ ${LZ_HDC()} list targets`)
            } else {
                console.error("> Error: no connection to a device")
            }
            process.exit(1)
        }
    }
}
