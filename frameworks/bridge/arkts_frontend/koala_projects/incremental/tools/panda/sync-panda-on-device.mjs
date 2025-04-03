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
import url from "url"

import { execCmd } from "../../../arkoala/ohos-sdk/scripts/utils.mjs"
import { ohConf } from "../../../arkoala/ohos-sdk/scripts/ohconf.mjs"

const __dirname = path.dirname(url.fileURLToPath(import.meta.url))

const OHCONF = ohConf(path.join(__dirname, "../../../arkoala/ohos-sdk/.ohconf.json"))
const HDC = OHCONF.hdcPath()

async function execHDC(args, options = {}) {
    return execCmd(HDC, [...args], {
        ...options,
        shell: false
    })
}

console.log("> Connected device:")
let out = await execHDC(['list', 'targets'], { instantLogging: true }) + ""
if (out.indexOf("Empty") !== -1) {
    console.log("> Error: no connection to a device")
    process.exit(-1)
}

console.log("> Mount device for write:")
await execHDC(['hdc', 'target', 'mount'], { instantLogging: true })

let arch = "arm64"
out = await execHDC(['shell', 'file', '/system/lib64']) + ""
if (out.indexOf("No such file") !== -1) {
    out = await execHDC(['shell', 'file', '/system/lib']) + ""
    if (out.indexOf("No such file") !== -1) {
        console.log("> Error: cannot detect device arch")
        process.exit(-1)
    }
    arch = "arm32"
}

console.log("> Device arch: " + arch)

const LIB_ARCH = arch === "arm32" ? "lib" : "lib64"

const PANDA_LIB_ROOT = path.join(__dirname, `node_modules/@panda/sdk/ohos_${arch}/lib`)
const PANDA_ETS_ROOT = path.join(__dirname, `node_modules/@panda/sdk/ets`)

const SEND_RULES = [
    {
        root: PANDA_LIB_ROOT,
        src: "libetsnative.so",
        dst: `/system/${LIB_ARCH}/ndk/libetsnative.z.so`
    },
    {
        root: PANDA_LIB_ROOT,
        src: "libets_interop_js_napi.so",
        dst: `/system/${LIB_ARCH}/module/libets_interop_js_napi.z.so`
    },
    {
        root: PANDA_LIB_ROOT,
        src: ".so",
        dst: `/system/${LIB_ARCH}`
    },
    {
        root: PANDA_ETS_ROOT,
        src: "etsstdlib.abc",
        dst: "/system/etc/etsstdlib.abc"
    }
]

const RULE_APPLIED = (fileName, rule) => fileName.endsWith(rule.src)

const SEND_FILE = async fileName => {
    const rule = SEND_RULES.filter(rule => RULE_APPLIED(fileName, rule))[0]
    console.log("> Send " + fileName + " to " + rule.dst)
    await execHDC(['hdc', 'file', 'send', path.join(rule.root, fileName), rule.dst], { instantLogging: true })
}


for (const file of fs.readdirSync(PANDA_LIB_ROOT)) {
    if (file.endsWith(".so"))
        await SEND_FILE(file)
}

await SEND_FILE("etsstdlib.abc")

console.log("> Reboot device...")
await execHDC(['hdc', 'shell', 'reboot'], { instantLogging: true })
