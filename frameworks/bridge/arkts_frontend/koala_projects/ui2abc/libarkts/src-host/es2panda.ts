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
import { checkSDK, arktsGlobal as global, ImportStorage, ETSModule, ProgramProvider, metaDatabase, runTransformer, RunTransformerContext, Profiler } from "@koalaui/libarkts"
import { CheckedBackFilter, ChainExpressionFilter, PluginContext, PluginContextImpl } from "@koalaui/libarkts"
import { Command } from "commander"
import { filterSource, isNumber, throwError, withWarning } from "@koalaui/libarkts"
import { Es2pandaContextState } from "@koalaui/libarkts"
import { AstNode, Config, Context, createETSModuleFromContext, inferVoidReturnType, proceedToState, ProgramTransformer, rebindSubtree, recheckSubtree, setBaseOverloads } from "@koalaui/libarkts"

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
        .option('--enable-report', 'Enable profiler report')
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
    const enableReport = cliOptions.enableReport ?? false

    return { filePath, configPath, outputPath, dumpAst, restartStages, stage, enableReport }
}

function insertPlugin(
    source: string,
    transform: ProgramTransformer,
    state: Es2pandaContextState,
    pluginName: string,
    dumpAst: boolean, 
    restart: boolean,
    context: PluginContext,
    profiler?: Profiler,
    updateWith?: (node: AstNode) => void
): AstNode {
    proceedToState(state, profiler)
    const script = createETSModuleFromContext()
    // Or this: const script = createETSModuleFromSource(source)
    if (script === undefined) {
        throw new Error(`Failed to receive AST from es2panda for ${source}`)
    }

    if (dumpAst) {
        console.log(`BEFORE ${stateName(state)}:`)
        console.log(filterSource(script.dumpSrc()))
    }

    runTransformer(global.compilerContext.program, state, transform, context, {
        onProgramTransformStart(ctx: RunTransformerContext) {
            profiler?.transformStarted(state, pluginName)
            if (!ctx.isMainProgram) profiler?.transformDepStarted()
        },
        onProgramTransformEnd(ctx: RunTransformerContext) {
            profiler?.transformEnded(state, pluginName)
            if (!ctx.isMainProgram) profiler?.transformDepEnded(state, pluginName)
            return !restart
        }
    })

    if (dumpAst) {
        console.log(`AFTER ${stateName(state)}:`)
        if (restart) {
            console.log(filterSource(script.dumpSrc()))
        } else {
            console.log(script.dumpSrc())
        }
    }

    if (!restart) {
        updateWith?.(script)
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
    profiler?: Profiler
): void {
    profiler?.compilationStarted(filePath)

    const source = fs.readFileSync(filePath).toString()
    const sdk = process.env.PANDA_SDK_PATH ?? withWarning(
        defaultPandaSdk,
        `PANDA_SDK_PATH not set, assuming ${defaultPandaSdk}`
    )
    const stdlib = `${sdk}/ets/stdlib`

    global.filePath = filePath
    global.outDir = outDir
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

    // TODO: this logic is completely wrong, and need to be fully rethought.
    if (restart) {
        const newFilePath = path.resolve(outDir, pluginNames[0], global.filePathFromPackageRoot)
        global.newFilePath = newFilePath
    }

    const restartProcedure = (state: Es2pandaContextState) => {
        if (restart) {
            const ext = path.extname(configPath)
            const newConfigPath = `${configPath.substring(0, configPath.length - pluginNames[pluginsApplied].length - ext.length)}${pluginNames[pluginsApplied + 1]}${ext}`
            const newFilePath = path.resolve(outDir, pluginNames[pluginsApplied], global.filePathFromPackageRoot)
            global.newFilePath = newFilePath
            if (fs.existsSync(metaDatabase(filePath))) {
                fs.copyFileSync(metaDatabase(filePath), metaDatabase(newFilePath))
            }
            if (pluginsApplied == stage) {
                // uncomment if switch to dets generator
                // restartCompiler(configPath, filePath, stdlib, outputPath, false)
                generateDeclFromCurrentContext(newFilePath, profiler)
            }
            pluginsApplied++
            const before = Date.now()
            restartCompiler(source, newConfigPath, newFilePath, stdlib, outputPath)
            const after = Date.now()
            configPath = newConfigPath
            filePath = newFilePath
            profiler?.restarted(after - before)
        }
    }

    const context = new PluginContextImpl()

    context.setParameter("restart", restart)

    pluginsByState.get(Es2pandaContextState.ES2PANDA_STATE_PARSED)?.forEach(plugin => {
        insertPlugin(source, plugin, Es2pandaContextState.ES2PANDA_STATE_PARSED, pluginNames[pluginsApplied], dumpAst, restart, context, profiler)
        restartProcedure(Es2pandaContextState.ES2PANDA_STATE_PARSED)
    })

    pluginsByState.get(Es2pandaContextState.ES2PANDA_STATE_BOUND)?.forEach(plugin => {
        insertPlugin(source, plugin, Es2pandaContextState.ES2PANDA_STATE_BOUND, pluginNames[pluginsApplied], dumpAst, restart, context, profiler, rebindSubtree)
        restartProcedure(Es2pandaContextState.ES2PANDA_STATE_BOUND)
    })

    pluginsByState.get(Es2pandaContextState.ES2PANDA_STATE_CHECKED)?.forEach(plugin => {
        insertPlugin(source, plugin, Es2pandaContextState.ES2PANDA_STATE_CHECKED, pluginNames[pluginsApplied], dumpAst, restart, context, profiler, recheckSubtree)
        restartProcedure(Es2pandaContextState.ES2PANDA_STATE_CHECKED)
    })
    proceedToState(Es2pandaContextState.ES2PANDA_STATE_BIN_GENERATED, profiler)

    profiler?.compilationEnded()
    profiler?.report()
    profiler?.reportToFile(true)
}

const exportsFromInitialFile: string[] = []

function generateDeclFromCurrentContext(filePath: string, profiler?: Profiler): never {
    proceedToState(Es2pandaContextState.ES2PANDA_STATE_PARSED, profiler)
    console.log(`Emitting to ${filePath}`)
    let out = [
        filterSource(
            new CheckedBackFilter()
                .visitor(global.compilerContext.program.ast)
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
            if (selected) {
                pluginsByState.set(it, selected)
            }
        })

    return pluginsByState
}

export function main() {
    checkSDK()
    const { filePath, configPath, outputPath, dumpAst, restartStages, stage, enableReport } = parseCommandLineArgs()
    const arktsconfig = JSON.parse(fs.readFileSync(configPath).toString())
    const configDir = path.dirname(configPath)
    const compilerOptions = arktsconfig.compilerOptions ?? throwError(`arktsconfig should specify compilerOptions`)
    const packageName = compilerOptions.package ?? ""
    const baseUrl = compilerOptions.baseUrl ?? "."
    const outDir = path.resolve(path.dirname(configPath), compilerOptions.outDir ?? ".")
    const plugins = compilerOptions.plugins ?? []
    const pluginNames = plugins.map((it: any) => `${it.name}-${it.stage}`)

    const pluginsByState = readAndSortPlugins(configDir, plugins)

    invokeWithPlugins(configPath, packageName, baseUrl, outDir, filePath, outputPath, pluginsByState, dumpAst, restartStages, stage, pluginNames, enableReport ? new Profiler() : undefined)
}

function reportErrorAndExit(message: string): never {
    console.error(message)
    process.exit(1)
}

main()
