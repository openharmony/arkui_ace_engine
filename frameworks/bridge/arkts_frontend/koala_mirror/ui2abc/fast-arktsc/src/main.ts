/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

import { program } from "commander"
import * as fs from "fs"
import * as path from "path"
import * as child_process from "child_process"
import { minimatch } from 'minimatch'
import { resolveConfig, section, log, relativeOrDot, getConfigFullDirname } from "./resolve-config"

const readdirSyncRecursive: (dir: string) => string[] = (dir: string) =>
    fs.readdirSync(dir).reduce((files: string[], file: string) => {
        const name = path.join(dir, file)
        return fs.lstatSync(name).isDirectory() ? [...files, ...readdirSyncRecursive(name)] : [...files, name]
    }, [])

export const options = program
    .option('--config <path>', 'Path to configuration file')
    .option('--compiler <path>', 'Path to compiler')
    .option('--compiler-flags <path>', 'Flags to compiler')
    .option('--link-name <path>', 'Path to final linked file', "all")

    .option('--group-by <size>', 'Group files by groups before passing them to compiler')
    .option('--simultaneous', 'Use simultaneous compilation')

    .option('--output-dir <path>', 'Path to output dir (only used by AOT compilation)')
    .option('--aot-libs <libs>', 'Comma-separated AOT libraries to include')
    .option('--only-aot <file>', 'AOT an .abc taking --aot-libs into account')
    .option('--aot-target <arm|arm64|x86|x86_64>', 'Compilation target for AOT')

    .parse()
    .opts()

if (options.onlyAot)
    mainAot(path.resolve(options.onlyAot))
else
    main(options.config, options.linkName)



function findMatching(base: string, include: string[], exclude: string[]): string[] {
    return readdirSyncRecursive(base)
        .map(it => path.resolve(it))
        .filter(it => include.some(value => minimatch(it, path.join(base, value), {matchBase: true})))
        .filter(it => !exclude.some(value => minimatch(it, path.join(base, value), {matchBase: true})))
}

function getFileGroup(
    files: string[],
    groupBy: number,
    fileIndex: number
) {
    const firstId = fileIndex - fileIndex % groupBy
    const selectedFiles = files.slice(firstId, firstId + groupBy)
    return selectedFiles
}

function getFileGroupAsString(
    files: string[],
    groupBy: number,
    fileIndex: number,
    separator: string,
    prefix: string,
) {
    return `${prefix}${getFileGroup(files, groupBy, fileIndex).join(separator)}`
}

function produceNinjafile(
    compiler: string,
    files: string[],
    config: string,
    linkPath: string,
): string {
    // We have no Panda SDK for macOS.
    const tools_prefix =  process.platform == "darwin" ? "echo " : ""
    let result: string[] = []
    let basename = path.basename(compiler)
    let linker = compiler.replace(basename, 'arklink')

    const passFlags = [
        options.simultaneous ? '--simultaneous' : '',
    ].filter(it => it != '').join(' ')

    let linker_prefix = `
rule arkts_linker
    command = ${tools_prefix}${linker} --output $out -- @$out.rsp
    rspfile = $out.rsp
    rspfile_content = $in_newline
    description = "Linking ARKTS $out"
`

    let compiler_prefix = `
rule arkts_compiler
    command = ${tools_prefix}${compiler} ${options.compilerFlags ?? ''} --ets-module --arktsconfig ${path.resolve(config)} --output $out ${passFlags} @$out.rsp
    rspfile = $out.rsp
    rspfile_content = $in
    description = "Compiling ARKTS $out"
`

    const groupBy = Number(options.groupBy ?? (options.simultaneous ? files.length : 1))
    const groupOutputs: string[] = []
    const oneGroup = groupBy >= files.length

    let index = 0
    for (var i = 0; i < files.length; i += groupBy) {
        const output = oneGroup ? linkPath : `${linkPath}_${index}.abc`
        groupOutputs.push(output)

        result.push(
`
build ${output}: arkts_compiler ${getFileGroupAsString(files, groupBy, i, ' ', '')}
`

        )
        ++index
    }

    if (!oneGroup) {
        result.push(`build ${linkPath}: arkts_linker ${groupOutputs.join(' ')}\n`)
        result.push(`build link: phony ${linkPath}\n`)
        result.push(`build all: phony link\n`)
    } else {
        result.push(`build all: phony ${linkPath}\n`)
    }
    result.push("default all\n")

    return compiler_prefix + '\n' + linker_prefix + '\n' + result.join('')
}

function main(configPath: string, linkName: string) {
    const config = JSON.parse(fs.readFileSync(configPath, 'utf8'))
    const baseDir = path.resolve(path.dirname(configPath))
    const include = (config.include as string[]).map(it => it.replace('\\.', '.'))
    const exclude = config.exclude ? (config.exclude as string[]).map(it => it.replace('\\.', '.')) : []
    const outDir = path.resolve(getConfigFullDirname(), config.compilerOptions?.outDir ?? ".")
    const baseUrl = path.resolve(getConfigFullDirname(), config.compilerOptions?.baseUrl ?? ".")

    fs.mkdirSync(outDir, { recursive: true })
    const [firstConfigPath, intermediateOutDirs] = resolveConfig(configPath, options.restartStages)
    const linkPath = path.resolve(process.cwd(), linkName)
    log(`computed location of linked .abc: ${linkPath}`)

    const files = findMatching(baseDir, include, exclude)
    if (files.length == 0) {
        throw new Error(`No files matching include "${include.join(",")}" exclude "${exclude.join(",")}"`)
    }

    let ninja = produceNinjafile(path.resolve(options.compiler), files, firstConfigPath, linkPath)
    fs.writeFileSync(`${outDir}/build.ninja`, ninja)
}


// Improve: move all AOT stuff away from here
function archDir(): string {
    const arch = process.arch
    let sdkArch = "";
    switch (arch) {
        case "x64":
            sdkArch = ""
            break
        case "arm64":
            sdkArch = "arm64"
            break
        default: throw new Error(`Unexpected arch: ${arch}`)

    }
    const platform = process.platform
    let sdkPlatform = ""
    switch (platform) {
        case "linux": sdkPlatform = "linux"
            break
        case "win32": sdkPlatform = "windows"
            break
        case "darwin": sdkPlatform = "macos"
            break
        default: throw new Error(`Unsupported platform ${platform}`)
    }
    const suffix = "host_tools"
    return [sdkPlatform, sdkArch, suffix].filter(it => it != "").join("_")
}

function mainAot(abc: string) {
    let sdk = options.sdk ?? path.resolve(path.join(__dirname, '..', '..', '..', 'incremental', 'tools', 'panda', 'node_modules', '@panda', 'sdk'))
    let aot = path.join(sdk, archDir(), 'bin', 'ark_aot')
    let stdlib = path.resolve(path.join(sdk, "ets", "etsstdlib.abc"))
    const aotLibs = abc.indexOf("etsstdlib") == -1 ? [stdlib] : []
    if (options.aotLibs) aotLibs.push(... options.aotLibs.split(","))
    let args: string[] = []
    if (process.platform == "darwin") {
        // No tools on macOS, just echo
        args.push(aot)
        aot = "echo"
    }
    let dir = options.outputDir ?? path.dirname(abc)
    let result = path.join(dir, path.basename(abc).replace('.abc', '.an'))
    args.push(... options.aotTarget ? [`--compiler-cross-arch=${options.aotTarget}`] : [])
    args.push(... [
        `--load-runtimes=ets`,
        `--boot-panda-files=${aotLibs.map(it => path.resolve(it)).concat(abc).join(':')}`,
        `--paoc-panda-files=${abc}`,
        `--paoc-output=${result}`
    ])
    console.log(`AOT compile ${abc} to ${result}...`)
    console.log(`Launch ${aot} ${args.join(" ")}`)
    const child = child_process.spawn(aot, args)
    child.stdout.on('data', (data) => {
        process.stdout.write(data);
    })
    child.stderr.on('data', (data) => {
        process.stderr.write(data);
    })
    child.on('close', (code) => {
        if (code != 0)
            console.log(`Command ${aot} ${args.join(" ")} failed with return code ${code}`)
        else
            console.log(`Produced AOT file ${result}: ${Math.round(fs.statSync(result).size / 1024 / 1024)}M`)
        process.exit(code!)
    })
    child.on('exit', (code, signal) => {
        if (signal) {
            console.log(`Received signal: ${signal} from '${aot} ${args.join(' ')}'`)
            process.exit(1)
        }
    })
}
