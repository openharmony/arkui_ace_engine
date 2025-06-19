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
import { spawnSync } from "child_process"
import { lazy } from "../utils.mjs"
import { ohProjectConf } from "../ohconf.mjs"

const LZ_OHCONF = lazy(ohConfPath => ohProjectConf(ohConfPath))
const LZ_VERBOSE = lazy(verbose => verbose)

function checkOptions(options, mandatoryOptions) {
    for (let opt of mandatoryOptions) {
        if (!(opt in options)) {
            throw new Error(`'${opt}' is not set`)
        }
    }
}

function exec(binary, args) {
    if (LZ_VERBOSE()) {
        console.log(`> ${binary} ${args.join(' ')}`)
    }

    let stdio = LZ_VERBOSE() ? ['inherit', 'inherit', 'inherit'] : void 0
    let res = spawnSync(binary, args, { encoding: 'utf8', stdio })
    if (res.status != 0) {
        throw new Error(`Failed to compile '${binary} ${args.join(' ')}'`)
    }
}

function compileFile(options) {
    checkOptions(options, ['source', 'output', 'demo_app', 'arktsconfig'])

    let source_dir = path.join(LZ_OHCONF().path("app_ets_src"), 'ets', options.demo_app, 'ets')
    let dest_dir = LZ_OHCONF().path("app_ets_dst")
    let output_abc = path.join(dest_dir, options.output)
    let binary = LZ_OHCONF().path("ets_frontend")
    let opt_level = options.opt_level || 0

    let args = [
        `--gen-stdlib=${options.gen_stdlib}`,
        '--extension=ets',
        `--output=${output_abc}`,
        `--opt-level=${opt_level}`,
        `--arktsconfig=${options.arktsconfig}`,
        path.join(source_dir, options.source)
    ]

    exec(binary, args, LZ_VERBOSE())
}

function aotFiles(options) {
    checkOptions(options, ['files'])

    let files = options.files
    let boot_files = options.boot_files || []
    let dest_dir = LZ_OHCONF().path("app_ets_dst")
    let binary = LZ_OHCONF().path("ets_aot")
    let location = LZ_OHCONF().path("aot_location")

    for (let file of files) {
        let is_boot = boot_files.includes(file)

        let input_file = path.join(dest_dir, file)
        let output_file = path.join(dest_dir, path.parse(file).name + '.an')


        let args = [
            '--load-runtimes=ets',
            `--boot-panda-files=${boot_files.map(f => path.join(dest_dir, f)).join(':')}`,
            `--paoc-panda-files=${input_file}`,
            '--compiler-cross-arch=arm64'
        ]

        if (is_boot) {
            args = args.concat([
                `--paoc-boot-output=${output_file}`,
                `--paoc-boot-location=${location}`
            ])
        } else {
            args = args.concat([
                `--paoc-output=${output_file}`,
                `--paoc-location=${location}`,
                `--paoc-boot-panda-locations=${boot_files.map(f => path.join(location, f)).join(':')}`
            ])
        }

        exec(binary, args, LZ_VERBOSE())
    }
}

function getEnv(v) {
    let value = process.env[v]
    if (!value) {
        throw new Error(`'${v}' env is not set`)
    }
    return value
}

export function compile(options) {
    LZ_OHCONF(options.ohConf)
    LZ_VERBOSE(options.verbose)

    let demo_app = getEnv('DEMO_APP')

    const arktsconfig = path.join(LZ_OHCONF().path("app_ets_dst"), 'arktsconfig.json')
    const stdlib_escompat_src = path.join(LZ_OHCONF().path("panda_sdk"), 'ets', 'stdlib', 'escompat')
    const stdlib_std_src = path.join(LZ_OHCONF().path("panda_sdk"), 'ets', 'stdlib', 'std')
    fs.writeFileSync(arktsconfig, `{"compilerOptions": {"paths": {"escompat": ["${stdlib_escompat_src}"], "std": ["${stdlib_std_src}"]}}}`)

    compileFile({
        source: 'index.ets',
        output: 'etsstdlib.abc',
        gen_stdlib: true,
        demo_app: demo_app,
        arktsconfig: arktsconfig
    })

    compileFile({
        source: 'index.ets',
        output: 'index.abc',
        gen_stdlib: false,
        demo_app: demo_app,
        arktsconfig: arktsconfig
    })

    aotFiles({
        files: ['etsstdlib.abc', 'index.abc'],
        boot_files: ['etsstdlib.abc']
    })
}
