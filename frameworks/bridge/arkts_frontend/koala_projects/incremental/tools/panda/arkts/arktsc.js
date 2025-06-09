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

es2panda_path = process.env.ES2PANDA_PATH
es2panda_path = es2panda_path !== undefined ? es2panda_path : path.join(PANDA_SDK, ARCH_TOOLS, 'bin', 'es2panda')
stdlib_path = process.env.ETS_STDLIB_PATH
stdlib_path = stdlib_path !== undefined ? stdlib_path : path.join(PANDA_SDK, 'ets', 'stdlib')

const ARGS_SPEC = [
    {
        flag: '--es2panda-bin',
        help: 'Path to es2panda binary',
        domain: 'string',
        default: es2panda_path
    },
    {
        flag: '--es2panda-stdlib',
        help: 'Path to es2panda stdlib directory',
        domain: 'string',
        default: stdlib_path
    },
    ...DEFAULT_DRIVER_FLAGS,
]
const USAGE = getUsage("This runs es2panda to compile ts/arkts files to panda bytecode", ARGS_SPEC)

checkForHelp(USAGE)
const { recognized: args, unknown: rest } = extractArgs(ARGS_SPEC, process.argv.slice(2))
let cmd = [
    args.flag('--es2panda-bin'),
    '--stdlib', args.flag('--es2panda-stdlib'),
    '--extension', 'ets',
    '--list-files',
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
child.on('exit', (code, signal) => {
    if (signal) {
        console.log(`Received signal: ${signal} from '${formatCommand(cmd.join(' '), process.cwd())}'`)
        process.exit(1)
    }
})

