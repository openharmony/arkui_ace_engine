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
        .option('--generate-decl', 'Generate declaration files')
        .option('--decl-arktsconfig, <char>', 'Path to arkts configutation file for the binary compilation')
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
    const generateDecl = commander.generateDecl ?? false
    const dConfigPath = path.resolve(commander.declArktsconfig ?? commander.arktsconfig)

    return { filePath, configPath, outputPath, dumpAst, restartStages, generateDecl, dConfigPath }
}

function insertPlugin(plugin: (ast: AstNode) => void, state: Es2pandaContextState, dumpAst: boolean): AstNode {
    proceedToState(state)
    const script = EtsScript.fromContext()
    if (script === undefined) {
        throwError(`Failed to receive ast from es2panda`)
    }

    if (dumpAst) {
        console.log(`BEFORE ${stateName(state)}:`)
        console.log(filterSource(script.dumpSrc()))
    }

    const transform = plugin
    transform?.(script)

    if (dumpAst) {
        console.log(`AFTER ${stateName(state)}:`)
        console.log(filterSource(script.dumpSrc()))
    }

    setAllParents(script)
    return script
}

function restartCompiler() {
    console.log("restarting")
    const ast = EtsScript.fromContext()
    const srcText = filterSource(ast.dumpSrc())
    global.es2panda._DestroyContext(global.context)
    global.compilerContext = Context.createFromString(srcText)
}

function restartCompilerWithConfig(configPath: string, filePath: string, stdlib: string, outputPath: string) {
    console.log("restarting with another config")
    const srcText = filterSource(EtsScript.fromContext().dumpSrc())
    global.es2panda._DestroyContext(global.context)
    global.es2panda._DestroyConfig(global.config)
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
    global.compilerContext = Context.createFromString(srcText)
}

const defaultPandaSdk = "../../../incremental/tools/panda/node_modules/@panda/sdk"
function invokeWithPlugins(
    configPath: string,
    filePath: string,
    outputPath: string,
    pluginsByState: Map<Es2pandaContextState, ((ast: AstNode) => void)[]>,
    dumpAst: boolean,
    restart: boolean,
    generateDecl: boolean,
    dConfigPath: string,
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
    global.compilerContext = Context.createFromString(source)

    console.log("PLUGINS: ", pluginsByState.size, pluginsByState)

    if (pluginsByState.size == 0) {
        proceedToState(Es2pandaContextState.ES2PANDA_STATE_BIN_GENERATED)
        return
    }

    pluginsByState.get(Es2pandaContextState.ES2PANDA_STATE_PARSED)?.forEach(plugin => {
        insertPlugin(plugin, Es2pandaContextState.ES2PANDA_STATE_PARSED, dumpAst)
        if (restart) {
            restartCompiler()
        }
    })

    pluginsByState.get(Es2pandaContextState.ES2PANDA_STATE_CHECKED)?.forEach(plugin => {
        insertPlugin(plugin, Es2pandaContextState.ES2PANDA_STATE_CHECKED, dumpAst)
        // TODO: Normally we need just to proceed to a given state,
        //  but the compiler crashes now, so we restart
        if (restart) {
            restartCompiler()
        }
    })

    if (configPath !== dConfigPath) {
        proceedToState(Es2pandaContextState.ES2PANDA_STATE_PARSED)
        restartCompilerWithConfig(dConfigPath, filePath, stdlib, outputPath)
    }

    if (generateDecl) {
        proceedToState(Es2pandaContextState.ES2PANDA_STATE_PARSED)
        generateDeclFromCurrentContext(filePath)
    }

    proceedToState(Es2pandaContextState.ES2PANDA_STATE_BIN_GENERATED)
}

function generateDeclFromCurrentContext(filePath: string) {
    const ext = path.extname(filePath)
    const dir = path.basename(path.dirname(filePath))

    let declFile = ""
    if (dir == "sts") { // temporary workaround (sts dir -> dsts dir)
        fs.mkdirSync(path.join(path.dirname(path.dirname(filePath)), 'dsts'), { recursive: true })
        declFile = path.join(path.dirname(path.dirname(filePath)), 'dsts', path.basename(filePath))
    } else { // extension change (.sts -> .d.sts, .ets -> .d.ets)
        declFile = path.join(path.dirname(filePath), `${path.basename(filePath, ext)}.d${ext}`)
    }
    console.log(`Emiting declaration file to`, declFile)

    let out = filterSource(global.compilerContext.program.astNode.dumpSrc())

    // TODO: exports are lost on visiting
    const exportAstNodes = ["class", "abstract class", "interface", "@interface", "type"]
    exportAstNodes.forEach((astNodeText) => {
            out = out.replaceAll(`\n${astNodeText}`, `\nexport ${astNodeText}`)
        }
    )

    fs.writeFileSync(declFile,
        out
        .replaceAll("\nexport abstract class ETSGLOBAL", "\nabstract class ETSGLOBAL")
    )
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

function selectPlugins(configDir: string, plugins: any[], stage: string): ((arg: AstNode) => AstNode)[] | undefined {
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
    const pluginsByState = new Map<Es2pandaContextState, ((ast: AstNode) => void)[]>()

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
    const { filePath, configPath, outputPath, dumpAst, restartStages, generateDecl, dConfigPath } = parseCommandLineArgs()
    const arktsconfig = JSON.parse(fs.readFileSync(configPath).toString())
    const configDir = path.dirname(configPath)
    const compilerOptions = arktsconfig.compilerOptions ?? throwError(`arktsconfig should specify compilerOptions`)
    const plugins = compilerOptions.plugins ?? []

    const pluginsByState = readAndSortPlugins(configDir, plugins)

    invokeWithPlugins(configPath, filePath, outputPath, pluginsByState, dumpAst, restartStages, generateDecl, dConfigPath)
}

main()
