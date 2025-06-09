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

const child_process = require('child_process')
const path = require('node:path')

const TOOLS_PANDA_ROOT = path.join(__dirname, "..")
const PANDA_SDK = path.join(TOOLS_PANDA_ROOT, "node_modules/@panda/sdk")
const ARCH_TOOLS = (() => {
    const arch = process.arch
    let sdkArch = "";
    switch (arch) {
        case "x64": sdkArch = "";
            break;
        case "arm64": sdkArch = "arm64";
            break;
        default: throw new Error("Unexpected arch: ", arch);

    }
    const p = process.platform
    let sdkPlatform = ""
    switch (p) {
        case "linux": sdkPlatform = "linux"
            break;
        case "win32": sdkPlatform = "windows"
            break;
        case "darwin": sdkPlatform = "macos"
            break;
        default: throw new Error(`Unsupported platform ${p}`)
    }
    const suffix = "host_tools"
    return [sdkPlatform, sdkArch, suffix].filter(it => it != "").join("_")
})()
const DEFAULT_DRIVER_FLAGS = [
    {
        flag: '--driver-log',
        help: 'Define verbosity for output',
        domain: ['default', 'info'],
        default: 'default'
    },
]

function getUsage(usage, args) {
    let strings = [
        usage,
        "All arguments (except ones that are captured by the script) are passed to the underlying tool.",
        "",
        "Flags:",
    ]
    for (const arg of args) {
        strings.push(`${arg.flag} [${arg.domain}] Default: '${arg.default}'`)
        strings.push(`    ${arg.help}`)
    }
    return strings.join('\n')
}
function checkForHelp(usage) {
    if (process.argv.length === 3 &&
        (process.argv.includes('-h') || process.argv.includes('--help'))) {
        console.log(usage)
        process.exit(1)
    }
}

class Recognized {
    constructor(recognized) {
        this.recognized = recognized
    }

    flag(name) {
        const found = this.recognized.get(name)
        if (!found) {
            throw new Error(`Flag ${name} not specified`)
        }
        return found
    }
}

function extractArgs(argsSpec, args) {
    let flags = args
    const parsed = []
    function parseArg(flag) {
        if (flags.length === 0) {
            parsed.push({ type: 'flag', value: flag })
        } else {
            const peek = flags[0]
            if (!peek.startsWith('--')) {
                const top = flags.shift()
                parsed.push({ type: 'option', value: [flag, top] })
            } else {
                parsed.push({ type: 'flag', value: flag })
            }
        }
    }
    function parseVal(val) {
        parsed.push({ type: 'value', value: val });
    }
    function parseArgs() {
        if (!flags || flags.length === 0) {
            return
        }

        const top = flags.shift()
        if (top.startsWith('--')) {
            parseArg(top)
        } else {
            parseVal(top)
        }
        parseArgs()
    }

    function classify(flag) {
        const { type, value } = flag
        if (type === 'value') {
            return { type: 'unknown', value: [value] }
        } else {
            if (type === 'flag') {
                const found = argsSpec.find((el) => el.flag === value)
                if (found) {
                    return { type: 'recognized', flag: value, value: true, spec: found }
                } else {
                    return { type: 'unknown', value: [value] }
                }
            } else {
                const [f, arg] = value
                const found = argsSpec.find((el) => el.flag === f)
                if (found) {
                    return { type: 'recognized', flag: f, value: arg, spec: found }
                } else {
                    return { type: 'unknown', value: [f, arg] }
                }
            }
        }
    }

    function validate(c) {
        const { flag, value, spec } = c
        const domain = spec.domain
        if (Array.isArray(domain)) {
            if (!domain.includes(value)) {
                return `Flag ${flag} with ${value} is invalid, possible values are: ${domain}`
            }
        } else if (typeof value !== domain) {
            return `Flag ${flag} with ${value} is invalid, type must be ${domain}`
        }
        return null
    }

    parseArgs()
    const classified = parsed.map(classify)
    classified.filter(c => c.type == 'recognized').forEach(c => {
        const result = validate(c)
        if (result !== null) {
            throw new Error(result)
        }
    })

    let unknown = []
    let recognized = new Map()
    classified.forEach(r => {
        switch (r.type) {
            case 'unknown':
                unknown.push(...r.value)
                break
            case 'recognized':
                recognized.set(r.flag, r.value)
        }
    })

    argsSpec.forEach(s => {
        const { flag, default: default_ } = s
        if (!recognized.has(flag)) {
            recognized.set(flag, default_)
        }
    })

    return { recognized: new Recognized(recognized), unknown }
}

function formatCommand(cmd, cwd) {
    const c = typeof cmd === "string" ? cmd : cmd.join(' ')
    return `$ ${cwd}> ` + c
}

module.exports = {
    extractArgs,
    formatCommand,
    getUsage,
    checkForHelp,
    TOOLS_PANDA_ROOT,
    PANDA_SDK,
    ARCH_TOOLS,
    DEFAULT_DRIVER_FLAGS
}
