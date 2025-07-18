/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { Config } from "./peers/Config"
import { CompilationOptions, PluginContextImpl, ProgramTransformer } from "./plugins"
import { findStdlib, proceedToState, recheckContext } from "./utilities/public"
import { global } from "./static/global"
import { passString, passStringArray } from "./utilities/private"
import { Context } from "./peers/Context"
import { Es2pandaContextState } from "../generated/Es2pandaEnums"
import { Program } from "../generated"
import { runTransformerOnProgram } from "../plugin-utils"
import { ProgramProvider } from "./ProgramProvider"
import { Options } from "./peers/Options"

export interface ProgramInfo {
    /**
     * Input to compile (absolute file path)
     */
    absoluteName: string
    /**
     * Location of output (undefined for external sources)
     */
    output: string | undefined
}

export function getProgramsForPluginApplication(
    programs: ProgramInfo[],
) {
    const programsForCodeGeneration = programs
        .filter(it => it.output != undefined)
        .map(it => it.absoluteName)
    // Generally, it would be ok to return just the list above,
    // but for experimental purpose let's filter programs that
    // are mentioned as both codegeneration and caching
    const programsForCaching = new Set(
        programs
        .filter(it => it.output == undefined)
        .map(it => it.absoluteName)
    )
    return programsForCodeGeneration.filter(it => !programsForCaching.has(it))
}

export function compileWithCache(
    configPath: string,
    orderedPrograms: ProgramInfo[],
    parsedPlugins: ProgramTransformer[] | undefined,
    checkedPlugins: ProgramTransformer[] | undefined,
) {
    if (orderedPrograms.length == 0) {
        console.log("No files to compile")
        return
    }
    const globalConfig = Config.create(
        [
            '_', '--arktsconfig', configPath, '--extension', 'ets', '--stdlib', findStdlib(),
            orderedPrograms[0].absoluteName // Putting some file here to avoid "Fatal error: Unresolved module name"
        ]
    )
    console.log(orderedPrograms)
    const globalContext = global.es2panda._CreateGlobalContext(
        globalConfig.peer,
        passStringArray(orderedPrograms.map(it => it.absoluteName)),
        orderedPrograms.length,
        false
    )

    const programsForPluginApplication = getProgramsForPluginApplication(
        orderedPrograms
    )

    orderedPrograms.forEach((it) => {
        console.log(">>>", "considering", it.absoluteName)
        const args = ['_', '--arktsconfig', configPath, '--extension', 'ets', '--stdlib', findStdlib()]
        if (it.output) {
            args.push('--output', it.output, it.absoluteName)
        }
        const config = Config.create(
            args
        )
        const isExternalProgram = (it.output == undefined)
        const context = global.es2panda._CreateCacheContextFromFile(
            config.peer,
            passString(it.absoluteName),
            globalContext,
            isExternalProgram,
        )

        global.config = config.peer
        global.compilerContext = new Context(context)
        const options = Options.createOptions(new Config(global.config))
        global.arktsconfig = options.getArkTsConfig()

        function applyPlugins(plugins: ProgramTransformer[] | undefined, state: Es2pandaContextState) {
            plugins?.forEach(plugin => {
                const program = new Program(global.es2panda._ContextProgram(context))
                const provider = new ProgramProvider(program)
                let currentProgram = provider.next()
                let isFirstProgram = true
                while (currentProgram) {
                    if (
                        (!isExternalProgram && programsForPluginApplication.includes(currentProgram.absoluteName)) ||
                        (isExternalProgram && currentProgram.absoluteName == it.absoluteName)
                     ) {
                        const options: CompilationOptions = {
                            isMainProgram: isFirstProgram,
                            stage: state,
                            restart: false,
                        }
                        runTransformerOnProgram(
                            currentProgram,
                            options,
                            plugin,
                            new PluginContextImpl(),
                        )
                    }
                    currentProgram = provider.next()
                    isFirstProgram = false
                }
                if (state == Es2pandaContextState.ES2PANDA_STATE_CHECKED) {
                    recheckContext(context)
                }
            })
        }

        function proceedToParsed() {
            proceedToState(Es2pandaContextState.ES2PANDA_STATE_PARSED)
        }

        function applyParsedPlugins() {
            applyPlugins(parsedPlugins, Es2pandaContextState.ES2PANDA_STATE_PARSED)
        }

        function proceedToChecked() {
            proceedToState(Es2pandaContextState.ES2PANDA_STATE_CHECKED)
        }

        function applyCheckedPlugins() {
            applyPlugins(checkedPlugins, Es2pandaContextState.ES2PANDA_STATE_CHECKED)
        }

        function proceedToFinalState() {
            if (isExternalProgram) {
                proceedToState(Es2pandaContextState.ES2PANDA_STATE_LOWERED)
            } else {
                proceedToState(Es2pandaContextState.ES2PANDA_STATE_BIN_GENERATED)
            }
        }

        function cleanup() {
            global.es2panda._DestroyContext(
                context
            )
            global.es2panda._DestroyConfig(
                config.peer
            )
        }

        const operations = [
            proceedToParsed,
            applyParsedPlugins,
            proceedToChecked,
            applyCheckedPlugins,
            proceedToFinalState,
            cleanup,
        ]

        operations.forEach(operation => {
            console.log('>>>', operation.name)
            operation()
            console.log('>>>', operation.name, 'OK')
        })
    })

    global.es2panda._DestroyGlobalContext(
        globalContext
    )
    global.es2panda._DestroyConfig(
        globalConfig.peer
    )
}
