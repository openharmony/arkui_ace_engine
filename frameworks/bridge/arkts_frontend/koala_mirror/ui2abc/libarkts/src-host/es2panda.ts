/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

import * as fs from "node:fs"
import * as path from "node:path"
import { checkSDK, arktsGlobal as global, findStdlib, DumpingHooks, listPrograms } from "@koalaui/libarkts"
import { PluginEntry, PluginInitializer, CompilationOptions, Program } from "@koalaui/libarkts"
import { Command } from "commander"
import { throwError } from "@koalaui/libarkts"
import { Es2pandaContextState } from "@koalaui/libarkts"
import { Options, Config, Context, proceedToState, dumpProgramInfo, dumpArkTsConfigInfo } from "@koalaui/libarkts"

interface CommandLineOptions {
    files: string[]
    configPath: string
    outputs: string[]
    dumpAst: boolean
    simultaneous: boolean
}

function parseCommandLineArgs(): CommandLineOptions {
    const commander = new Command()
        .argument('[file]', 'Path to files to be compiled')
        .option('--file, <char>', 'Path to file to be compiled (deprecated)')
        .option('--arktsconfig, <char>', 'Path to arkts configuration file')
        .option('--ets-module', 'Do nothing, legacy compatibility')
        .option('--output, <char>', 'The name of result file')
        .option('--dump-plugin-ast', 'Dump ast before and after each plugin')
        .option('--simultaneous', 'Use "simultaneous" mode of compilation')
        .parse(process.argv)

    const cliOptions = commander.opts()
    const cliArgs = commander.args
    const fileArg = cliOptions.file ?? cliArgs[0]
    if (!fileArg) {
        reportErrorAndExit(`Either --file option or file argument is required`)
    }
    const files = fileArg.split(':').map((it: string) => path.resolve(it))
    const configPath = path.resolve(cliOptions.arktsconfig)
    const outputArg = cliOptions.output
    const outputs = outputArg.split(':').map((it: string) => path.resolve(it))
    files.forEach((it: string) => {
        if (!fs.existsSync(it)) {
            reportErrorAndExit(`File path doesn't exist: ${it}`)
        }
    })
    if (!fs.existsSync(configPath)) {
        reportErrorAndExit(`Arktsconfig path doesn't exist: ${configPath}`)
    }

    const dumpAst = cliOptions.dumpPluginAst ?? false
    const simultaneous = cliOptions.simultaneous ?? false

    return { files, configPath, outputs, dumpAst, simultaneous }
}

function insertPlugin(
    pluginEntry: PluginEntry,
    state: Es2pandaContextState,
    dumpAst: boolean,
) {
    const pluginName = `${pluginEntry.name}-${Es2pandaContextState[state].substring(`ES2PANDA_STATE_`.length).toLowerCase()}`
    global.profiler.curPlugin = pluginName
    global.profiler.transformStarted()

    const hooks = new DumpingHooks(state, pluginName, dumpAst)

    if (state == Es2pandaContextState.ES2PANDA_STATE_PARSED) {
        pluginEntry.parsed?.(hooks)
    }

    if (state == Es2pandaContextState.ES2PANDA_STATE_CHECKED) {
        pluginEntry.checked?.(hooks)
    }

    global.profiler.transformEnded(state, pluginName)
    global.profiler.curPlugin = ""
}

function invokeWithPlugins(
    configPath: string,
    filePath: string,
    outputPath: string,
    pluginsByState: Map<Es2pandaContextState, PluginEntry[]>,
    dumpAst: boolean,
): void {
    const stdlib = findStdlib()
    global.profiler.compilationStarted(filePath)

    global.filePath = filePath
    const compilerConfig = Config.create([
        '_',
        '--arktsconfig',
        configPath,
        filePath,
        '--extension',
        'ets',
        '--stdlib',
        stdlib,
        '--output',
        outputPath
    ])
    global.config = compilerConfig.peer
    if (!global.configIsInitialized())
        throw new Error(`Wrong config: path=${configPath} file=${filePath} stdlib=${stdlib} output=${outputPath}`)
    fs.mkdirSync(path.dirname(outputPath), {recursive: true})
    const compilerContext = Context.createFromFile(filePath, configPath, stdlib, outputPath)!
    global.compilerContext = compilerContext

    proceedToState(Es2pandaContextState.ES2PANDA_STATE_PARSED)

    const options = Options.createOptions(new Config(global.config))
    global.arktsconfig = options.getArkTsConfig()

    console.log("COMPILATION STARTED")
    dumpArkTsConfigInfo(global.arktsconfig)
    dumpProgramInfo(compilerContext.program)

    global.profiler.curContextState = Es2pandaContextState.ES2PANDA_STATE_PARSED
    pluginsByState.get(Es2pandaContextState.ES2PANDA_STATE_PARSED)?.forEach(plugin => {
        insertPlugin(plugin, Es2pandaContextState.ES2PANDA_STATE_PARSED, dumpAst)
    })

    global.profiler.curContextState = Es2pandaContextState.ES2PANDA_STATE_CHECKED
    proceedToState(Es2pandaContextState.ES2PANDA_STATE_CHECKED)

    pluginsByState.get(Es2pandaContextState.ES2PANDA_STATE_CHECKED)?.forEach(plugin => {
        insertPlugin(plugin, Es2pandaContextState.ES2PANDA_STATE_CHECKED, dumpAst)
    })

    global.profiler.curContextState = Es2pandaContextState.ES2PANDA_STATE_BIN_GENERATED
    proceedToState(Es2pandaContextState.ES2PANDA_STATE_BIN_GENERATED)

    global.profiler.compilationEnded()
    global.profiler.report()
    global.profiler.reportToFile(true)

    compilerContext.destroy()
    compilerConfig.destroy()
}

function dumpCompilationInfo() {
    if (global.arktsconfig) {
        dumpArkTsConfigInfo(global.arktsconfig)
    } else {
        console.log("No arktsconfig")
    }
    const programs = listPrograms(global.compilerContext.program)
    const programsForCodegeneration = programs.filter(it => it.isGenAbcForExternal)
    console.log(`Programs for codegeneration        : ${programsForCodegeneration.length}`)
    console.log(`External programs passed to plugins: ${programs.length - programsForCodegeneration.length - 1}`) // -1 for "empty" main program
}

function invokeSimultaneous(
    configPath: string,
    filePaths: string[],
    outputPaths: string[],
    pluginsByState: Map<Es2pandaContextState, PluginEntry[]>,
    dumpAst: boolean,
): void {
    const stdlib = findStdlib()

    const compilerConfig = Config.create([
        '_',
        '--simultaneous',
        '--arktsconfig',
        configPath,
        '--extension',
        'ets',
        '--stdlib',
        stdlib,
        '--output',
        outputPaths[0],
        filePaths[0]
    ])
    global.config = compilerConfig.peer
    if (!global.configIsInitialized())
        throw new Error(`Wrong config: path=${configPath}`)

    const compilerContext = Context.createContextGenerateAbcForExternalSourceFiles(filePaths)
    global.compilerContext = compilerContext
    global.isContextGenerateAbcForExternalSourceFiles = true

    proceedToState(Es2pandaContextState.ES2PANDA_STATE_PARSED)

    const options = Options.createOptions(new Config(global.config))
    global.arktsconfig = options.getArkTsConfig()

    pluginsByState.get(Es2pandaContextState.ES2PANDA_STATE_PARSED)?.forEach(plugin => {
        insertPlugin(plugin, Es2pandaContextState.ES2PANDA_STATE_PARSED, dumpAst)
    })

    dumpCompilationInfo()
    
    proceedToState(Es2pandaContextState.ES2PANDA_STATE_CHECKED)

    pluginsByState.get(Es2pandaContextState.ES2PANDA_STATE_CHECKED)?.forEach(plugin => {
        insertPlugin(plugin, Es2pandaContextState.ES2PANDA_STATE_CHECKED, dumpAst)
    })

    proceedToState(Es2pandaContextState.ES2PANDA_STATE_BIN_GENERATED)

    global.profiler.compilationEnded()
    global.profiler.report()
    global.profiler.reportToFile(true)

    compilerContext.destroy()
    compilerConfig.destroy()
}

function loadPlugin(configDir: string, transform: string) {
    /** Improve: read and pass plugin options */
    const plugin = (transform.startsWith(".") || transform.startsWith("/")) ?
        path.resolve(configDir, transform) : transform
    const pluginEntry = require(plugin)
    if (!pluginEntry.init) {
        throw new Error(`init is not specified in plugin ${transform}`)
    }
    if (typeof (pluginEntry.init) !== 'function') {
        throw new Error(`init is not a function in plugin ${transform}`)
    }
    return pluginEntry.init
}

function stateFromString(stateName: string): Es2pandaContextState {
    switch (stateName) {
        case "parsed": return Es2pandaContextState.ES2PANDA_STATE_PARSED
        case "checked": return Es2pandaContextState.ES2PANDA_STATE_CHECKED
        default: throw new Error(`Invalid state name: ${stateName}`)
    }
}

function readAndSortPlugins(configDir: string, plugins: any[]) {
    const pluginsByState = new Map<Es2pandaContextState, PluginEntry[]>()
    const pluginInitializers = new Map<string, PluginInitializer>()
    const pluginParsedStageOptions = new Map<string, Object>()
    const pluginCheckedStageOptions = new Map<string, Object>()

    plugins.forEach(it => {
        const transform = it.transform
        if (!transform) {
            throwError(`arktsconfig plugins objects should specify transform`)
        }
        const state = stateFromString(it.state)
        if (!pluginInitializers.has(it.transform)) {
            pluginInitializers.set(it.transform, loadPlugin(configDir, it.transform))
        }
        if (!pluginsByState.has(state)) {
            pluginsByState.set(state, [])
        }
        if (state == Es2pandaContextState.ES2PANDA_STATE_PARSED) {
            pluginParsedStageOptions.set(it.transform, it)
        }
        if (state == Es2pandaContextState.ES2PANDA_STATE_CHECKED) {
            pluginCheckedStageOptions.set(it.transform, it)
        }
    })

    pluginInitializers.forEach((pluginInit, pluginTransform) => {
        const parsedJson = pluginParsedStageOptions.get(pluginTransform)
        const checkedJson = pluginCheckedStageOptions.get(pluginTransform)
        const plugin = pluginInit(parsedJson, checkedJson)
        if (parsedJson && plugin.parsed) {
            pluginsByState.get(Es2pandaContextState.ES2PANDA_STATE_PARSED)?.push(plugin)
        }
        if (checkedJson && plugin.checked) {
            pluginsByState.get(Es2pandaContextState.ES2PANDA_STATE_CHECKED)?.push(plugin)
        }
    })

    return pluginsByState
}

export function main() {
    checkSDK()
    const { files, configPath, outputs, dumpAst, simultaneous } = parseCommandLineArgs()
    if (files.length != outputs.length) {
        reportErrorAndExit("Different length of inputs and outputs")
    }
    const arktsconfig = JSON.parse(fs.readFileSync(configPath).toString())
    const configDir = path.dirname(configPath)
    const compilerOptions = arktsconfig.compilerOptions ?? throwError(`arktsconfig should specify compilerOptions`)
    const plugins = compilerOptions.plugins ?? []
    const pluginsByState = readAndSortPlugins(configDir, plugins)

    if (simultaneous) {
        invokeSimultaneous(configPath, files, outputs, pluginsByState, dumpAst)
    } else {
        for (var i = 0; i < files.length; i++) {
            invokeWithPlugins(configPath, files[i], outputs[i], pluginsByState, dumpAst)
        }
    }
}

function reportErrorAndExit(message: string): never {
    console.error(message)
    process.exit(1)
}

main()
