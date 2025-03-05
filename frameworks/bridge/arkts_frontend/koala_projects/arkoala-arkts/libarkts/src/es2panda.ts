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
import { global } from "./arkts-api/static/global"
import { Command } from "commander"
import { isNumber, throwError, withWarning, filterSource } from "./utils"
import { Es2pandaContextState } from "./generated/Es2pandaEnums"
import { AstNode, Config, Context, EtsScript, proceedToState } from "./arkts-api"

function parseCommandLineArgs() {
    const commander = new Command()
        .option('--file, <char>', 'Path to file to be compiled')
        .option('--arktsconfig, <char>', 'Path to arkts configuration file')
        .option('--ets-module', 'Do nothing, legacy compatibility')
        .option('--output, <char>', 'The name of result file')
        .option('--dump-plugin-ast', 'Dump ast before and after each plugin')
        .option('--restart-stages', 'Restart the compiler to proceed to next stage')
        .parse(process.argv)
        .opts()

    const restOptions = commander.args

    const filePath = path.resolve(commander.file)
    const configPath = path.resolve(commander.arktsconfig)
    const outputPath = path.resolve(commander.output)
    if (!fs.existsSync(filePath)) {
        throw new Error(`File path doesn't exist: ${filePath}`)
    }
    if (!fs.existsSync(configPath)) {
        throw new Error(`Arktsconfig path doesn't exist: ${configPath}`)
    }

    const dumpAst = commander.dumpPluginAst ?? false
    const restartStages = commander.restartStages ?? false

    return { filePath, configPath, outputPath, dumpAst, restartStages }
}

function insertPlugin(pluginsByState: Map<Es2pandaContextState, (ast: AstNode) => void>, state: Es2pandaContextState, dumpAst: boolean): AstNode {
    proceedToState(state)
    const script = EtsScript.fromContext()
    if (script === undefined) {
        throwError(`Failed to receive ast from es2panda`)
    }

    if (dumpAst) {
        console.log(`BEFORE ${stateName(state)}:`)
        console.log(filterSource(script.dumpSrc()))
    }

    const transform = pluginsByState.get(state)
    transform?.(script)

    if (dumpAst) {
        console.log(`AFTER ${stateName(state)}:`)
        console.log(filterSource(script.dumpSrc()))
    }

    return script
}

function restartCompilerUptoState(ast: AstNode, state: Es2pandaContextState, restart: boolean) {
    if (restart) {
        const srcText = filterSource(ast.dumpSrc())
        global.es2panda._DestroyContext(global.context)
        global.context = Context.createFromString(srcText).peer
    }
    proceedToState(state)
}

const defaultPandaSdk = "../../../incremental/tools/panda/node_modules/@panda/sdk"
function invokeWithPlugins(
    configPath: string,
    filePath: string,
    outputPath: string,
    pluginsByState: Map<Es2pandaContextState, (ast: AstNode) => void>,
    dumpAst: boolean,
    restart: boolean
): void {
    const source = fs.readFileSync(filePath).toString()
    const sdk = process.env.PANDA_SDK_PATH ?? withWarning(
        defaultPandaSdk,
        `PANDA_SDK_PATH not set, assuming ${defaultPandaSdk}`
    )
    const stdlib = `${sdk}/ets/stdlib`

    global.filePath = filePath
    global.config = Config.create([
        '_',
        '--arktsconfig',
        configPath,
        filePath,
        '--extension',
        'sts',
        '--stdlib',
        stdlib,
        '--output',
        outputPath
    ]).peer
    fs.mkdirSync(path.dirname(outputPath), {recursive: true})
    global.context = Context.createFromString(source).peer

    console.log("PLUGINS: ", pluginsByState.size, pluginsByState)

    if (pluginsByState.size == 0 ) {
        proceedToState(Es2pandaContextState.ES2PANDA_STATE_BIN_GENERATED)
        return
    }

    // ComponentTransformer
    const parsedTransform = insertPlugin(pluginsByState, Es2pandaContextState.ES2PANDA_STATE_PARSED, dumpAst)
    setAllParents(parsedTransform)
    // TODO: Normally we need just to proceed to a given state,
    //  but the compiler crashes now, so we restart
    restartCompilerUptoState(parsedTransform, Es2pandaContextState.ES2PANDA_STATE_CHECKED, restart)

    // BuilderLambdaTransformer
    const checkedTransform = insertPlugin(pluginsByState, Es2pandaContextState.ES2PANDA_STATE_CHECKED, dumpAst)
    setAllParents(checkedTransform)
    restartCompilerUptoState(checkedTransform, Es2pandaContextState.ES2PANDA_STATE_BIN_GENERATED, restart)
}

function setAllParents(ast: AstNode) {
    global.es2panda._AstNodeUpdateAll(global.context, ast.peer)
}

function loadPlugin(configDir: string, jsonPlugin: any) {
    const pluginPath = jsonPlugin.transform ?? throwError(`arktsconfig plugins objects should specify transform`)
    /** TODO: read and pass plugin options */
    const plugin = (pluginPath.startsWith(".") || pluginPath.startsWith("/")) ?
        path.resolve(configDir, pluginPath) : pluginPath

    const pluginFunction: (config?: any) => any = require(plugin).default(jsonPlugin)
    return pluginFunction
}

function selectPlugins(configDir: string, plugins: any[], stage: string): ((arg: AstNode) => AstNode) | undefined {
    const selected = plugins
        .filter(it => (it.stage == stage))
        .map(it => loadPlugin(configDir, it))
    if (selected.length == 0) {
        return undefined
    }
    return (ast: AstNode) => selected.reduce(
        (it, transform) => transform(it),
        ast
    )
}

function stateName(value: Es2pandaContextState): string {
    return Es2pandaContextState[value].substring("ES2PANDA_STATE_".length)
}

function readAndSortPlugins(configDir: string, plugins: any[]) {
    const pluginsByState = new Map<Es2pandaContextState, (ast: AstNode) => void>()

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
    const { filePath, configPath, outputPath, dumpAst, restartStages } = parseCommandLineArgs()
    const arktsconfig = JSON.parse(fs.readFileSync(configPath).toString())
    const configDir = path.dirname(configPath)
    const compilerOptions = arktsconfig.compilerOptions ?? throwError(`arktsconfig should specify compilerOptions`)
    const plugins = compilerOptions.plugins ?? []

    const pluginsByState = readAndSortPlugins(configDir, plugins)

    invokeWithPlugins(configPath, filePath, outputPath, pluginsByState, dumpAst, restartStages)
}

main()
