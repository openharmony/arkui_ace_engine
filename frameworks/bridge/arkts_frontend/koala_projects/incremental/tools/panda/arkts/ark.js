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
const fs = require("fs")
const { formatCommand,
    extractArgs,
    DEFAULT_DRIVER_FLAGS,
    PANDA_SDK,
    ARCH_TOOLS,
    getUsage,
    checkForHelp } = require('./common')

const ARK_BOOT_FILE_SEP = ":"
const ARK_OBJ_FILE_EXT = ".abc"

ark_path = process.env.ARK_PATH
ark_path = ark_path ?? path.join(PANDA_SDK, ARCH_TOOLS, 'bin', 'ark')

const ARGS_SPEC = [
    {
        flag: '--ark-bin',
        help: 'Path to ark binary',
        domain: 'string',
        default: ark_path
    },
    {
        flag: '--ark-ets-stdlib',
        help: 'ETS stdlib to use for launch',
        domain: 'string',
        default: path.join(PANDA_SDK, 'ets', 'etsstdlib.abc')
    },
    {
        flag: '--ark-boot-files',
        help: 'Boot panda files to use (either list of files separated by `:` or a single directory)',
        domain: 'string',
        default: ''
    },
    {
        flag: '--ark-entry-point',
        help: 'Entry point function in format like `ETSGLOBAL::main`',
        domain: 'string',
        default: 'ETSGLOBAL::main'
    },
    ...DEFAULT_DRIVER_FLAGS,
]
const USAGE = getUsage("This runs ark to load and run panda bytecode", ARGS_SPEC)

checkForHelp(USAGE)
const { recognized: args, unknown: rest } = extractArgs(ARGS_SPEC, process.argv.slice(2))

const arkBootFiles =
    args.flag('--ark-boot-files')
    .split(ARK_BOOT_FILE_SEP)
    .flatMap(filePath => fs.statSync(filePath).isDirectory()
        ? fs.readdirSync(filePath, {recursive: true, withFileTypes: true})
            .filter(it => path.parse(it.name).ext === ARK_OBJ_FILE_EXT)
            .map(it => path.join(it.path, it.name))
        : filePath)
    .join(ARK_BOOT_FILE_SEP)

let cmd = [
    args.flag('--ark-bin'),
    '--load-runtimes=ets',
    '--boot-panda-files',
    args.flag('--ark-ets-stdlib') + ':' + arkBootFiles,
    ...rest,
    args.flag('--ark-entry-point'),
]
if (args.flag('--driver-log') === 'info') {
    console.log(formatCommand(cmd.join(' '), process.cwd()))
}
// console.log(`start ${cmd.join(' ')}`)
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
