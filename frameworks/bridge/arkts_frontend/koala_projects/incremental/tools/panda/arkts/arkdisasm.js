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
const path = require("node:path")
const { formatCommand,
    extractArgs,
    DEFAULT_DRIVER_FLAGS,
    PANDA_SDK,
    ARCH_TOOLS,
    getUsage,
    checkForHelp } = require('./common')

const ARGS_SPEC = [
    {
        flag: '--arkdisasm-bin',
        help: 'Path to arkdisasm binary',
        domain: 'string',
        default: path.join(PANDA_SDK, ARCH_TOOLS, 'bin', 'ark_disasm')
    },
    ...DEFAULT_DRIVER_FLAGS,
]
const USAGE = getUsage("This runs ark_disasm to disassemble .abc file", ARGS_SPEC)

checkForHelp(USAGE)
const { recognized: args, unknown: rest } = extractArgs(ARGS_SPEC, process.argv.slice(2))
if (rest.length === 1) {
    rest.push(rest[0] + ".disasm")
}
let cmd = [
    args.flag('--arkdisasm-bin'),
    ...rest
]
if (args.flag('--driver-log') === 'info') {
    console.log(formatCommand(cmd.join(' '), process.cwd()))
}
const child = child_process.spawn(cmd[0], [...cmd.slice(1)])
child.stdout.on('data', (data) => {
    process.stdout.write(data);
})
child.stderr.on('data', (data) => {
    process.stderr.write(data);
})
child.on('close', (code) => {
    if (code) {
        if (args.flag('--driver-log') === 'info') {
            console.log(`Command ${formatCommand(cmd.join(' '), process.cwd())} failed with return code ${code}`)
        }
        process.exit(code)
    }
})
