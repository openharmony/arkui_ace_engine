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
import { checkSDK, arktsGlobal as global, ImportStorage } from "@koalaui/libarkts"
import { CheckedBackFilter, ChainExpressionFilter, PluginContext, PluginContextImpl } from "@koalaui/libarkts"
import { Command } from "commander"
import { filterSource, isNumber, throwError, withWarning } from "@koalaui/libarkts"
import { Es2pandaContextState } from "@koalaui/libarkts"
import { AstNode, Config, Context, createETSModuleFromContext, inferVoidReturnType, listPrograms, proceedToState, ProgramTransformer, rebindSubtree, recheckSubtree, setBaseOverloads } from "@koalaui/libarkts"

function parseCommandLineArgs() {
    const commander = new Command()
        .argument('[file]', 'Path to file to be compiled')
        .option('--file, <char>', 'Path to file to be compiled (deprecated)')
        .option('--arktsconfig, <char>', 'Path to arkts configuration file')
        .option('--ets-module', 'Do nothing, legacy compatibility')
        .option('--output, <char>', 'The name of result file')
        .option('--dump-plugin-ast', 'Dump ast before and after each plugin')
        .option('--restart-stages', 'Restart the compiler to proceed to next stage')
        .option('--stage <int>', 'Stage of multistage compilation (from 0 to number of plugins in arktsconfig + 1)')
        .parse(process.argv)

    const cliOptions = commander.opts()
    const cliArgs = commander.args
    const filePathArg = cliOptions.file ?? cliArgs[0]
    if (!filePathArg) {
        reportErrorAndExit(`Either --file option or file argument is required`)
    }
    const filePath = path.resolve(filePathArg)
    const configPath = path.resolve(cliOptions.arktsconfig)
    const outputPath = path.resolve(cliOptions.output)
    if (!fs.existsSync(filePath)) {
        reportErrorAndExit(`File path doesn't exist: ${filePath}`)
    }
    if (!fs.existsSync(configPath)) {
        reportErrorAndExit(`Arktsconfig path doesn't exist: ${configPath}`)
    }

    const dumpAst = cliOptions.dumpPluginAst ?? false
    const restartStages = cliOptions.restartStages ?? false
    const stage = cliOptions.stage ?? 0

    return { filePath, configPath, outputPath, dumpAst, restartStages, stage }
}

function insertPlugin(
    source: string,
    transform: ProgramTransformer,
    state: Es2pandaContextState,
    dumpAst: boolean, restart: boolean,
    context: PluginContext,
    updateWith?: (node: AstNode) => void
): AstNode {
    proceedToState(state)
    const script = createETSModuleFromContext()
    // Or this: const script = createETSModuleFromSource(source)
    if (script === undefined) {
        throw new Error(`Failed to receive AST from es2panda for ${source}`)
    }

    if (dumpAst) {
        console.log(`BEFORE ${stateName(state)}:`)
        console.log(filterSource(script.dumpSrc()))
    }

    const beforeTransform = Date.now()

    if (!restart) {
        const programs = listPrograms(global.compilerContext.program)
        programs.forEach((program, index) => {
            if (index == 0) {
                return
            }
            const ast = program.program.astNode
            const importStorage = new ImportStorage(program.program, state == Es2pandaContextState.ES2PANDA_STATE_PARSED)
            stageSpecificPreFilters(ast, state)
            
            transform?.(program.program, { isMainProgram: false, name: program.name, stage: state }, context)

            stageSpecificPostFilters(ast, state)
            setBaseOverloads(ast)
            if (!restart) {
                importStorage.update()
            }
            setAllParents(ast)
        })
    }

    const importStorage = new ImportStorage(global.compilerContext.program, state == Es2pandaContextState.ES2PANDA_STATE_PARSED)
    if (!restart) stageSpecificPreFilters(script, state)

    transform?.(global.compilerContext.program, { isMainProgram: true, name: `${global.packageName}.${global.filePathFromPackageRoot}`, stage: state }, context)

    const afterTransform = Date.now()
    global.profiler.transformTime += afterTransform - beforeTransform

    if (dumpAst) {
        console.log(`AFTER ${stateName(state)}:`)
        if (restart) {
            console.log(filterSource(script.dumpSrc()))
        } else {
            console.log(script.dumpSrc())
        }
    }

    if (!restart) stageSpecificPostFilters(script, state)
    setBaseOverloads(script)
    if (!restart) {
        importStorage.update()
    }
    setAllParents(script)

    if (!restart) {
        console.log("UPDATE...")
        updateWith?.(script)
        console.log("DONE!")
    }
    return script
}

function stageSpecificPreFilters(script: AstNode, state: Es2pandaContextState) {
    if (state == Es2pandaContextState.ES2PANDA_STATE_CHECKED) {
        inferVoidReturnType(script)
    }
}

function stageSpecificPostFilters(script: AstNode, state: Es2pandaContextState) {
    if (state == Es2pandaContextState.ES2PANDA_STATE_CHECKED) {
        new ChainExpressionFilter().visitor(script)
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
    global.es2panda._DestroyContext(global.context)
    global.es2panda._DestroyConfig(global.config)

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

const defaultPandaSdk = "../../../incremental/tools/panda/node_modules/@panda/sdk"
function invokeWithPlugins(
    configPath: string,
    packageName: string,
    baseUrl: string,
    outDir: string,
    filePath: string,
    outputPath: string,
    pluginsByState: Map<Es2pandaContextState, ProgramTransformer[]>,
    dumpAst: boolean,
    restart: boolean,
    stage: number,
    pluginNames: string[],
): void {
    const source = fs.readFileSync(filePath).toString()
    const sdk = process.env.PANDA_SDK_PATH ?? withWarning(
        defaultPandaSdk,
        `PANDA_SDK_PATH not set, assuming ${defaultPandaSdk}`
    )
    const stdlib = `${sdk}/ets/stdlib`

    global.filePath = filePath
    global.packageName = packageName
    global.filePathFromPackageRoot = path.relative(path.join(path.dirname(configPath), baseUrl), filePath)
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
    if (!global.configIsInitialized())
        throw new Error(`Wrong config: path=${configPath} file=${filePath} stdlib=${stdlib} output=${outputPath}`)
    fs.mkdirSync(path.dirname(outputPath), {recursive: true})
    global.compilerContext = Context.createFromString(source)

    // console.log("PLUGINS: ", pluginsByState.size, pluginsByState)

    pluginNames.push(`_proceed_to_binary`)
    let pluginsApplied = 0

    const restartProcedure = () => {
        if (restart) {
            const before = Date.now()
            const ext = path.extname(configPath)
            const newConfigPath = `${configPath.substring(0, configPath.length - pluginNames[pluginsApplied].length - ext.length)}${pluginNames[pluginsApplied + 1]}${ext}`
            const newFilePath = path.resolve(outDir, pluginNames[pluginsApplied], global.filePathFromPackageRoot)
            if (pluginsApplied == stage) {
                // uncomment if switch to dets generator
                // restartCompiler(configPath, filePath, stdlib, outputPath, false)
                generateDeclFromCurrentContext(newFilePath)
            }
            pluginsApplied++
            restartCompiler(source, newConfigPath, newFilePath, stdlib, outputPath)
            configPath = newConfigPath
            filePath = newFilePath
            const after = Date.now()
            global.profiler.restartTime += after - before
        }
    }

    const context = new PluginContextImpl()

    pluginsByState.get(Es2pandaContextState.ES2PANDA_STATE_PARSED)?.forEach(plugin => {
        insertPlugin(source, plugin, Es2pandaContextState.ES2PANDA_STATE_PARSED, dumpAst, restart, context)
        restartProcedure()
    })

    pluginsByState.get(Es2pandaContextState.ES2PANDA_STATE_BOUND)?.forEach(plugin => {
        insertPlugin(source, plugin, Es2pandaContextState.ES2PANDA_STATE_BOUND, dumpAst, restart, context, rebindSubtree)
        restartProcedure()
    })

    pluginsByState.get(Es2pandaContextState.ES2PANDA_STATE_CHECKED)?.forEach(plugin => {
        insertPlugin(source, plugin, Es2pandaContextState.ES2PANDA_STATE_CHECKED, dumpAst, restart, context, recheckSubtree)
        restartProcedure()
    })
    proceedToState(Es2pandaContextState.ES2PANDA_STATE_BIN_GENERATED)
}

const exportsFromInitialFile: string[] = []

function generateDeclFromCurrentContext(filePath: string): never {
    proceedToState(Es2pandaContextState.ES2PANDA_STATE_PARSED)
    console.log(`Emitting to ${filePath}`)
    const filterTransform = new CheckedBackFilter()
    let out = [
        filterSource(
            filterTransform.visitor(global.compilerContext.program.astNode)
            .dumpSrc()
        ),
        ...exportsFromInitialFile
    ].join('\n')
    fs.mkdirSync(path.dirname(filePath), { recursive: true })
    fs.writeFileSync(filePath, out)
    process.exit(0)
}

function setAllParents(ast: AstNode) {
    global.es2panda._AstNodeUpdateAll(global.context, ast.peer)
}

function loadPlugin(configDir: string, jsonPlugin: any) {
    const pluginPath = jsonPlugin.transform ?? throwError(`arktsconfig plugins objects should specify transform`)
    /** TODO: read and pass plugin options */
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
            if (selected) pluginsByState.set(
                it,
                selected
            )
        })

    return pluginsByState
}

export function main() {
    const before = Date.now()
    checkSDK()
    const { filePath, configPath, outputPath, dumpAst, restartStages, stage } = parseCommandLineArgs()
    const arktsconfig = JSON.parse(fs.readFileSync(configPath).toString())
    const configDir = path.dirname(configPath)
    const compilerOptions = arktsconfig.compilerOptions ?? throwError(`arktsconfig should specify compilerOptions`)
    const packageName = compilerOptions.package ?? ""
    const baseUrl = compilerOptions.baseUrl ?? "."
    const outDir = path.resolve(path.dirname(configPath), compilerOptions.outDir ?? ".")
    const plugins = compilerOptions.plugins ?? []
    const pluginNames = plugins.map((it: any) => `${it.name}-${it.stage}`)

    const pluginsByState = readAndSortPlugins(configDir, plugins)

    invokeWithPlugins(configPath, packageName, baseUrl, outDir, filePath, outputPath, pluginsByState, dumpAst, restartStages, stage, pluginNames)

    const after = Date.now()
    global.profiler.totalTime = after - before
    global.profiler.report()
}

function reportErrorAndExit(message: string): never {
    console.error(message)
    process.exit(1)
}

main()
