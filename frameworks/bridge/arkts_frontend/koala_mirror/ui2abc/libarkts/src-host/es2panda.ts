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
import { checkSDK, arktsGlobal as global, metaDatabase, runTransformer, CompilationOptions, findStdlib, Program, dumpProgramSrcFormatted, rebindContext, recheckContext } from "@koalaui/libarkts"
import { CheckedBackFilter, PluginContextImpl } from "@koalaui/libarkts"
import { Command } from "commander"
import { filterSource, isNumber, throwError } from "@koalaui/libarkts"
import { Es2pandaContextState } from "@koalaui/libarkts"
import { Options, Config, Context, createETSModuleFromContext, proceedToState, ProgramTransformer, dumpProgramInfo, dumpArkTsConfigInfo, collectDependencies } from "@koalaui/libarkts"
import { ProgramInfo, compileWithCache } from "@koalaui/libarkts"

interface CommandLineOptions {
    files: string[]
    configPath: string
    outputs: string[]
    dumpAst: boolean
    restartStages: boolean
    stage: number
    useCache: boolean,
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
        .option('--restart-stages', 'Restart the compiler to proceed to next stage')
        .option('--stage <int>', 'Stage of multistage compilation (from 0 to number of plugins in arktsconfig + 1)')
        .option('--cache', 'Use AST chaches')
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
    const restartStages = cliOptions.restartStages ?? false
    const stage = cliOptions.stage ?? 0
    const useCache = cliOptions.cache ?? false
    const simultaneous = cliOptions.simultaneous ?? false

    return { files, configPath, outputs, dumpAst, restartStages, stage, useCache, simultaneous }
}

function insertPlugin(
    transform: ProgramTransformer,
    state: Es2pandaContextState,
    pluginName: string,
    dumpAst: boolean,
    restart: boolean,
    pluginContext: PluginContextImpl,
) {
    global.profiler.curPlugin = pluginName
    global.profiler.transformStarted()

    runTransformer(global.compilerContext.program, state, restart, transform, pluginContext, {
        onProgramTransformStart(options: CompilationOptions, program: Program) {
            if (dumpAst) {
                console.log(`BEFORE ${pluginName}:`)
                dumpProgramSrcFormatted(program)
            }
            if (!options.isMainProgram) global.profiler.transformDepStarted()
        },
        onProgramTransformEnd(options: CompilationOptions, program: Program) {
            if (!options.isMainProgram) global.profiler.transformDepEnded(state, pluginName)
            if (dumpAst) {
                console.log(`AFTER ${pluginName}:`)
                dumpProgramSrcFormatted(program)
            }
        }
    })

    global.profiler.transformEnded(state, pluginName)
    global.profiler.curPlugin = ""

    if (!restart) {
        if (state == Es2pandaContextState.ES2PANDA_STATE_BOUND) {
            rebindContext()
        }
        if (state == Es2pandaContextState.ES2PANDA_STATE_CHECKED) {
            recheckContext()
        }
    }
}

function restartCompiler(source: string, configPath: string, filePath: string, stdlib: string, outputPath: string, verbose: boolean = true) {
    if (verbose) {
        console.log(`restarting with config ${configPath}, file ${filePath}`)
    }
    const module = createETSModuleFromContext()
    if (module == undefined) throw new Error(`Cannot restart compiler for ${source}`)
    const filterTransform = new CheckedBackFilter()
    const srcText = filterSource(
        filterTransform.visitor(module)
        .dumpSrc()
    )
    //global.es2panda._DestroyContext(global.context)
    //global.es2panda._DestroyConfig(global.config)

    global.filePath = filePath
    global.config = Config.create([
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
    ]).peer
    global.compilerContext = Context.createFromString(srcText)
}

function invokeWithPlugins(
    configPath: string,
    filePath: string,
    outputPath: string,
    pluginsByState: Map<Es2pandaContextState, ProgramTransformer[]>,
    dumpAst: boolean,
    restart: boolean,
    stage: number,
    pluginNames: string[],
    pluginContext: PluginContextImpl
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

    pluginNames.push(`_proceed_to_binary`)
    let pluginsApplied = 0

    let terminate = false

    const restartProcedure = (state: Es2pandaContextState) => {
        if (restart) {
            const ext = path.extname(configPath)
            const newConfigPath = `${configPath.substring(0, configPath.length - pluginNames[pluginsApplied].length - ext.length)}${pluginNames[pluginsApplied + 1]}${ext}`
            const newFilePath = path.resolve(global.arktsconfig!.outDir, pluginNames[pluginsApplied], path.relative(global.arktsconfig!.baseUrl, global.filePath))
            if (fs.existsSync(metaDatabase(filePath))) {
                fs.copyFileSync(metaDatabase(filePath), metaDatabase(newFilePath))
            }
            if (pluginsApplied == stage) {
                generateDeclFromCurrentContext(newFilePath)
                terminate = true
                return
            }
            pluginsApplied++
            const before = Date.now()
            restartCompiler(fs.readFileSync(filePath, 'utf-8'), newConfigPath, newFilePath, stdlib, outputPath)
            const after = Date.now()
            configPath = newConfigPath
            filePath = newFilePath
            const options = Options.createOptions(new Config(global.config))
            global.arktsconfig = options.getArkTsConfig()
            proceedToState(state)
            global.profiler.restarted(after - before)
        } else {
            pluginsApplied++
        }
    }

    proceedToState(Es2pandaContextState.ES2PANDA_STATE_PARSED)

    const options = Options.createOptions(new Config(global.config))
    global.arktsconfig = options.getArkTsConfig()

    console.log("COMPILATION STARTED")
    dumpArkTsConfigInfo(global.arktsconfig)
    dumpProgramInfo(compilerContext.program)

    global.profiler.curContextState = Es2pandaContextState.ES2PANDA_STATE_PARSED
    pluginsByState.get(Es2pandaContextState.ES2PANDA_STATE_PARSED)?.forEach(plugin => {
        if (!terminate) {
            insertPlugin(plugin, Es2pandaContextState.ES2PANDA_STATE_PARSED, pluginNames[pluginsApplied], dumpAst, restart, pluginContext)
            restartProcedure(Es2pandaContextState.ES2PANDA_STATE_PARSED)
        }
    })

    if (!terminate) {
        proceedToState(Es2pandaContextState.ES2PANDA_STATE_BOUND)
        global.profiler.curContextState = Es2pandaContextState.ES2PANDA_STATE_BOUND
    }

    pluginsByState.get(Es2pandaContextState.ES2PANDA_STATE_BOUND)?.forEach(plugin => {
        if (!terminate) {
            insertPlugin(plugin, Es2pandaContextState.ES2PANDA_STATE_BOUND, pluginNames[pluginsApplied], dumpAst, restart, pluginContext)
            restartProcedure(Es2pandaContextState.ES2PANDA_STATE_BOUND)
        }
    })

    if (!terminate) {
        proceedToState(Es2pandaContextState.ES2PANDA_STATE_CHECKED)
        global.profiler.curContextState = Es2pandaContextState.ES2PANDA_STATE_CHECKED
    }

    pluginsByState.get(Es2pandaContextState.ES2PANDA_STATE_CHECKED)?.forEach(plugin => {
        if (!terminate) {
            insertPlugin(plugin, Es2pandaContextState.ES2PANDA_STATE_CHECKED, pluginNames[pluginsApplied], dumpAst, restart, pluginContext)
            restartProcedure(Es2pandaContextState.ES2PANDA_STATE_CHECKED)
        }
    })

    if (!terminate) {
        global.profiler.curContextState = Es2pandaContextState.ES2PANDA_STATE_BIN_GENERATED
        proceedToState(Es2pandaContextState.ES2PANDA_STATE_BIN_GENERATED)
    }

    global.profiler.compilationEnded()
    global.profiler.report()
    global.profiler.reportToFile(true)

    compilerContext.destroy()
    compilerConfig.destroy()
}

function invokeSimultaneous(
    configPath: string,
    filePaths: string[],
    outputPaths: string[],
    pluginsByState: Map<Es2pandaContextState, ProgramTransformer[]>,
    dumpAst: boolean,
    pluginNames: string[],
    pluginContext: PluginContextImpl
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

    pluginNames.push(`_proceed_to_binary`)
    let pluginsApplied = 0

    let terminate = false

    proceedToState(Es2pandaContextState.ES2PANDA_STATE_PARSED)

    // listPrograms(compilerContext.program).forEach(
    //     program => {
    //         console.log(program.absoluteName)
    //         console.log("IS GEN", global.generatedEs2panda._ProgramIsGenAbcForExternalConst(compilerContext.peer, program.peer))
    //     }
    // )

    const options = Options.createOptions(new Config(global.config))
    global.arktsconfig = options.getArkTsConfig()

    console.log("COMPILATION STARTED")

    dumpArkTsConfigInfo(global.arktsconfig)
    dumpProgramInfo(compilerContext.program)

    pluginsByState.get(Es2pandaContextState.ES2PANDA_STATE_PARSED)?.forEach(plugin => {
        if (!terminate) {
            insertPlugin(plugin, Es2pandaContextState.ES2PANDA_STATE_PARSED, pluginNames[pluginsApplied], dumpAst, false, pluginContext)
            pluginsApplied++
        }
    })

    if (!terminate) {
        proceedToState(Es2pandaContextState.ES2PANDA_STATE_BOUND)
    }
    pluginsByState.get(Es2pandaContextState.ES2PANDA_STATE_BOUND)?.forEach(plugin => {
        if (!terminate) {
            insertPlugin(plugin, Es2pandaContextState.ES2PANDA_STATE_BOUND, pluginNames[pluginsApplied], dumpAst, false, pluginContext)
            pluginsApplied++
        }
    })
    if (!terminate) {
        proceedToState(Es2pandaContextState.ES2PANDA_STATE_CHECKED)
    }

    pluginsByState.get(Es2pandaContextState.ES2PANDA_STATE_CHECKED)?.forEach(plugin => {
        if (!terminate) {
            insertPlugin(plugin, Es2pandaContextState.ES2PANDA_STATE_CHECKED, pluginNames[pluginsApplied], dumpAst, false, pluginContext)
            pluginsApplied++
        }
    })

    if (!terminate) {
        proceedToState(Es2pandaContextState.ES2PANDA_STATE_BIN_GENERATED)
    }

    global.profiler.compilationEnded()
    global.profiler.report()
    global.profiler.reportToFile(true)

    compilerContext.destroy()
    compilerConfig.destroy()
}

function generateDeclFromCurrentContext(filePath: string) {
    proceedToState(Es2pandaContextState.ES2PANDA_STATE_PARSED)
    console.log(`Emitting to ${filePath}`)
    let out = [
        filterSource(
            new CheckedBackFilter()
                .visitor(global.compilerContext!.program.ast)
                .dumpSrc()
        ),
    ].join('\n')
    fs.mkdirSync(path.dirname(filePath), { recursive: true })
    fs.writeFileSync(filePath, out)
}

function loadPlugin(configDir: string, jsonPlugin: any) {
    const pluginPath = jsonPlugin.transform ?? throwError(`arktsconfig plugins objects should specify transform`)
    /** Improve: read and pass plugin options */
    const plugin = (pluginPath.startsWith(".") || pluginPath.startsWith("/")) ?
        path.resolve(configDir, pluginPath) : pluginPath
    const pluginFunction: (config?: any) => any = require(plugin)(jsonPlugin)
    return pluginFunction
}

function selectPlugins(configDir: string, plugins: any[], stage: string): ProgramTransformer[] | undefined {
    const selected = plugins
        .filter(it => (it.stage == stage))
        .map(it => loadPlugin(configDir, it))
    if (selected.length == 0) {
        return undefined
    }
    return selected
}

function stateName(value: Es2pandaContextState): string {
    return Es2pandaContextState[value].substring("ES2PANDA_STATE_".length)
}

function readAndSortPlugins(configDir: string, plugins: any[]) {
    const pluginsByState = new Map<Es2pandaContextState, ProgramTransformer[]>()

    Object.values(Es2pandaContextState)
        .filter(isNumber)
        .forEach(it => {
            const selected = selectPlugins(configDir, plugins, stateName(it).toLowerCase())
            if (selected) {
                pluginsByState.set(it, selected)
            }
        })

    return pluginsByState
}

export function main() {
    checkSDK()
    const { files, configPath, outputs, dumpAst, restartStages, stage, useCache, simultaneous } = parseCommandLineArgs()
    if (files.length != outputs.length) {
        reportErrorAndExit("Different length of inputs and outputs")
    }
    const arktsconfig = JSON.parse(fs.readFileSync(configPath).toString())
    const configDir = path.dirname(configPath)
    const compilerOptions = arktsconfig.compilerOptions ?? throwError(`arktsconfig should specify compilerOptions`)
    const plugins = compilerOptions.plugins ?? []
    const pluginNames = plugins.map((it: any) => `${it.name}-${it.stage}`)
    const pluginContext = new PluginContextImpl()
    const pluginsByState = readAndSortPlugins(configDir, plugins)

    if (useCache) {
        const filesWithDependencies = collectDependencies(files, configPath)
        const onlyDependencies = filesWithDependencies.filter(it => !files.includes(it))
        const compilationUnits: ProgramInfo[] = []
        files.forEach((it, index) => {
            compilationUnits.push(
                {
                    absoluteName: it,
                    output: outputs[index]
                }
            )
        })
        onlyDependencies.forEach(it => {
            compilationUnits.push(
                {
                    absoluteName: it,
                    output: undefined
                }
            )
        })
        compileWithCache(
            configPath,
            compilationUnits.reverse(),
            pluginsByState.get(Es2pandaContextState.ES2PANDA_STATE_PARSED),
            pluginsByState.get(Es2pandaContextState.ES2PANDA_STATE_CHECKED)
        )
    } else if (simultaneous) {
        invokeSimultaneous(configPath, files, outputs, pluginsByState, dumpAst, pluginNames, pluginContext)
    }else {
        for (var i = 0; i < files.length; i++) {
            invokeWithPlugins(configPath, files[i], outputs[i], pluginsByState, dumpAst, restartStages, stage, pluginNames, pluginContext)
        }
    }
}

function reportErrorAndExit(message: string): never {
    console.error(message)
    process.exit(1)
}

main()
