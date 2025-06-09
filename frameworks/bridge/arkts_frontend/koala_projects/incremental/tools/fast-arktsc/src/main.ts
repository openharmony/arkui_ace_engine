#!/usr/bin/env node

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

const readdirSyncRecursive: (dir: string) => string[] = (dir: string) =>
    fs.readdirSync(dir).reduce((files: string[], file: string) => {
        const name = path.join(dir, file)
        return fs.lstatSync(name).isDirectory() ? [...files, ...readdirSyncRecursive(name)] : [...files, name]
    }, [])

const options = program
    .option('--input-files <path>', 'Path to input file(s), comma separated')
    .option('--output-dir <path>', 'Path to output dir')
    .option('--compiler <path>', 'Path to compiler')
    .option('--link-name <path>', 'Name of combined link-name.abc', "all")
    .option('--target <ninja|make>', 'Target build system', "ninja")
    .option('--file-option', 'When provided pass the source as --file <path> rather than a free option')
    .option('--aot-libs <libs>', 'Comma-separated AOT libraries to include')
    .option('--only-aot <file>', 'AOT an .abc taking --aot-libs into account')
    .option('--aot-target <arm|arm64|x86|x86_64>', 'Compilation target for AOT')

    .parse()
    .opts()

if (options.onlyAot)
    mainAot(path.resolve(options.onlyAot))
else
    main(options.inputFiles, path.resolve(options.outputDir), options.linkName, options.target)

function findMatching(base: string, include: string[], exclude: string[]): string[] {
    return readdirSyncRecursive(base)
        .map(it => path.resolve(it))
        .filter(it => include.some(value => minimatch(it, path.join(base, value), {matchBase: true})))
        .filter(it => !exclude.some(value => minimatch(it, path.join(base, value), {matchBase: true})))
}

function producePairs(files: string[],
                      baseDir: string,
                      rootDir: string | undefined,
                      buildDir: string | undefined): { input: string, output: string }[] {
    return files.map(srcFile => {
        const fileBuildDir = buildDir
            ? path.join(buildDir, path.relative(rootDir ?? baseDir, path.dirname(srcFile)))
            : path.dirname(srcFile)
        fs.mkdirSync(fileBuildDir, {recursive: true})
        return {
            input: srcFile,
            output: `${path.join(fileBuildDir, path.basename(srcFile).replace(path.extname(srcFile), ".abc"))}`
        }
    })
}

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

function produceMakefile(compiler: string,
                         files: {input: string, output: string}[],
                         outputDir: string,
                         config: string,
                         linkName: string): string {
    let result: string[] = []
    let all: string[] = []
    result.push("default: all")
    let basename = path.basename(compiler)
    let linker = compiler.replace(basename, 'arklink')

    files.forEach(it => {
        all.push(it.output)
        result.push(`${it.output}: ${it.input}`)
        result.push(`\t${compiler} --ets-module --arktsconfig ${path.resolve(config)} ${options.fileOption ? "--file" : ""} ${it.input} --output ${it.output}`)
    })
    result.push(`compile: ${all.join(' ')}`)
    result.push(`link: compile`)
    result.push(`\t${linker} --output ${outputDir}/${linkName}.abc -- ${all.join(' ')}`)
    result.push(`all: link`)
    return result.join('\n')
}

function produceNinjafile(compiler: string,
                          files: {input: string, output: string}[],
                          outputDir: string,
                          config: string,
                          linkName: string
                        ): string {
    // We have no Panda SDK for macOS.
    const tools_prefix =  process.platform == "darwin" ? "echo " : ""
    let result: string[] = []
    let all: string[] = []
    let basename = path.basename(compiler)
    let linker = compiler.replace(basename, 'arklink')
    const groupSize = 100;

    let prefix = `
rule arkts_compiler
    command = ${tools_prefix}${compiler} --ets-module --arktsconfig ${path.resolve(config)} ${options.fileOption ? "--file" : ""} $in --output $out
    description = "Compiling ARKTS $out"
rule arkts_linker
    command = ${tools_prefix}${linker} --output $out -- $in
    description = "Linking ARKTS $out"`
    files.forEach(it => {
        all.push(it.output)
        result.push(`build ${it.output}: arkts_compiler ${it.input}\n`)
    })
    result.push(`build compile: phony ${all.join(' ')}`)

    if (all.length <= groupSize) {
        result.push(`build ${outputDir}/${linkName}.abc: arkts_linker ${all.join(' ')}\n`)
    } else {
        // If too much file, divide into groups avoid 'posix_spawn: Argument list too long' issue
        const allParts = []

        for (let i = 0; i < all.length; i += groupSize) {
            const batch = all.slice(i, i + groupSize)
            const partName:string = `${outputDir}/${linkName}.part${allParts.length + 1}.abc`
            allParts.push(partName);

            result.push(`build ${partName}: arkts_linker ${batch.join(' ')}\n`)
        }
        result.push(`build ${outputDir}/${linkName}.abc: arkts_linker ${allParts.join(' ')}`)
    }

    result.push(`build link: phony ${outputDir}/${linkName}.abc`)
    result.push(`build all: phony link`)
    result.push("default all\n")
    return prefix + '\n' + result.join('\n')
}

function main(inputFile: string, outputDir: string, linkName: string, target: string) {
    let config = JSON.parse(fs.readFileSync(inputFile, 'utf8'))
    let baseDir = path.resolve(path.dirname(inputFile))
    let include = (config.include as string[]).map(it => it.replace('\\.', '.'))
    let exclude = config.exclude ? (config.exclude as string[]).map(it => it.replace('\\.', '.')) : []
    const buildDir = config.compilerOptions.outDir ? (path.resolve(config.compilerOptions.outDir)) : undefined
    const rootDir = config.compilerOptions.rootDir ? (path.resolve(config.compilerOptions.rootDir)) : undefined
    const files = producePairs(findMatching(baseDir, include, exclude), baseDir, rootDir, buildDir)
    if (files.length == 0) {
        throw new Error(`No files matching include "${include.join(",")}" exclude "${exclude.join(",")}"`)
    }
    fs.mkdirSync(outputDir, { recursive: true })
    if (target == 'make') {
        let maker = produceMakefile(path.resolve(options.compiler), files, outputDir, inputFile, linkName)
        fs.writeFileSync(`${outputDir}/Makefile`, maker)
    } else {
        let ninja = produceNinjafile(path.resolve(options.compiler), files, outputDir, inputFile, linkName)
        fs.writeFileSync(`${outputDir}/build.ninja`, ninja)
    }
}

function mainAot(abc: string) {
    let sdk = options.sdk ?? path.resolve(path.join(__dirname, '..', '..', 'panda', 'node_modules', '@panda', 'sdk'))
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
        process.exit(code ?? undefined)
    })
    child.on('exit', (code, signal) => {
        if (signal) {
            console.log(`Received signal: ${signal} from '${aot} ${args.join(' ')}'`)
            process.exit(1)
        }
    })
}
