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
    ETSModule,
    ProgramProvider
} from "./arkts-api"
import { AstNode } from "./reexport-for-generated"

export interface RunTransformerContext {
    isMainProgram: boolean
}

export interface RunTransformerHooks {
    onProgramTransformStart?(ctx: RunTransformerContext): void
    onProgramTransformEnd?(ctx: RunTransformerContext): boolean
}

export function runTransformer(prog: Program, state: Es2pandaContextState, transform: ProgramTransformer, pluginContext: PluginContext, hooks: RunTransformerHooks = {}) {
    // Visit deps
    const provider = new ProgramProvider({ program: prog, name: `${arktsGlobal.packageName}.${arktsGlobal.filePathFromPackageRoot}` })
    let currentProgram = provider.next()

    while (currentProgram) {
        const runCtx: RunTransformerContext = {
            isMainProgram: currentProgram.program.peer == prog.peer
        }

        hooks.onProgramTransformStart?.(runCtx)

        const ast = currentProgram.program.ast as ETSModule
        const importStorage = new ImportStorage(currentProgram.program, state == Es2pandaContextState.ES2PANDA_STATE_PARSED)
        stageSpecificPreFilters(ast, state)

        transform?.(currentProgram.program, { isMainProgram: runCtx.isMainProgram, name: currentProgram.name, stage: state }, pluginContext)

        stageSpecificPostFilters(ast, state)
        setBaseOverloads(ast)
        importStorage.update()
        setAllParents(ast)

        const willStop = hooks.onProgramTransformEnd?.(runCtx) === false
        if (willStop) break

        currentProgram = provider.next()
    }
}

function setAllParents(ast: AstNode) {
    arktsGlobal.es2panda._AstNodeUpdateAll(arktsGlobal.context, ast.peer)
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
