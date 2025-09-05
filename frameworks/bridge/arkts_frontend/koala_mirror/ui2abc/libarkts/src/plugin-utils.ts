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

import {
    Es2pandaContextState,
    PluginContext,
    ImportStorage,
    setBaseOverloads,
    arktsGlobal,
    ChainExpressionFilter,
    ProgramTransformer,
    Program,
    inferVoidReturnType,
    ProgramProvider,
    CompilationOptions
} from "./arkts-api"
import { AstNode } from "./reexport-for-generated"

export interface RunTransformerHooks {
    onProgramTransformStart?(options: CompilationOptions, program: Program): void
    onProgramTransformEnd?(options: CompilationOptions, program: Program): void
}

class ASTCache {
    processedPrograms = new Set<string>()
    constructor() { }
    find(program: Program): boolean {
        return this.processedPrograms.has(program.absoluteName)
    }
    update(program: Program) {
        this.processedPrograms.add(program.absoluteName)
    }
}

export function runTransformerOnProgram(program: Program, options: CompilationOptions, transform: ProgramTransformer | undefined, pluginContext: PluginContext, hooks: RunTransformerHooks = {}) {
    // Perform some additional actions before the transformation start
    hooks.onProgramTransformStart?.(options, program)

    // Save currently existing imports in the program
    const importStorage = new ImportStorage(program, options.stage == Es2pandaContextState.ES2PANDA_STATE_PARSED)

    // Run some common plugins that should be run before plugin usage and depends on the current stage
    stageSpecificPreFilters(program, options.stage)

    // Run the plugin itself
    transform?.(program, options, pluginContext)

    // Run some common plugins that should be run after plugin usage and depends on the current stage
    stageSpecificPostFilters(program, options.stage)

    // Update internal import information based on import modification by plugin
    importStorage.update()

    // Perform some additional actions after the transformation end
    hooks.onProgramTransformEnd?.(options, program)
}

export function runTransformer(prog: Program, state: Es2pandaContextState, restart: boolean, transform: ProgramTransformer | undefined, pluginContext: PluginContext, hooks: RunTransformerHooks = {}) {
    // Program provider used to provide programs to transformer dynamically relative to inserted imports
    const provider = new ProgramProvider(prog)

    // The first program provided by program provider is the main program
    let currentProgram = provider.next()
    let isMainProgram = true

    while (currentProgram) {
        // Options passed to plugin and hooks
        const options: CompilationOptions = {
            isMainProgram,
            stage: state,
            restart,
        }

        runTransformerOnProgram(currentProgram, options, transform, pluginContext, hooks)

        // The first program is always the main program, so break here if should not proceed external sources
        if (restart) break
        isMainProgram = false

        // Proceed to the next program
        currentProgram = provider.next()
    }
}

function setAllParents(ast: AstNode) {
    arktsGlobal.es2panda._AstNodeUpdateAll(arktsGlobal.context, ast.peer)
}

function stageSpecificPreFilters(program: Program, state: Es2pandaContextState) {
    if (state == Es2pandaContextState.ES2PANDA_STATE_CHECKED) {
        inferVoidReturnType(program)
    }
}

function stageSpecificPostFilters(program: Program, state: Es2pandaContextState) {
    if (state == Es2pandaContextState.ES2PANDA_STATE_CHECKED) {
        program.setAst(new ChainExpressionFilter().visitor(program.ast))
    }
}
