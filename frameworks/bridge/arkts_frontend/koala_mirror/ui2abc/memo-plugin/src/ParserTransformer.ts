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

import * as arkts from "@koalaui/libarkts"
import { factory } from "./MemoFactory"

const ignore = [
    "@koalaui/compat",
    "@koalaui/common",
    "@koalaui/runtime/annotations",

    "@koalaui/runtime.internals",
    "@koalaui/runtime.index",

    "@koalaui/runtime.states.State",
    "@koalaui/runtime.tree.ReadonlyTreeNode",
    "@koalaui/runtime.tree.IncrementalNode",
    "@koalaui/runtime.states.Disposable",
    "@koalaui/runtime.states.Dependency",
    "@koalaui/runtime.states.Journal",
]

export interface TransformerOptions {
    contextImport?: string,
    stableForTests?: boolean
}

export default function memoParserTransformer(
    userPluginOptions?: TransformerOptions
) {
    return (program: arkts.Program, options: arkts.CompilationOptions, context: arkts.PluginContext) => {
        const restart = options.restart
        if (restart) {
            console.log("Parser transformer of memo plugin does nothing with restart mode enabled")
            return
        }

        if (ignore.some(it => program.moduleName.startsWith(it)) || program.moduleName == "") {
            /* Some files should not be processed by plugin actually */
            return
        }

        const module = program.ast as arkts.ETSModule
        program.setAst(
            arkts.factory.updateETSModule(
                module,
                [
                    factory.createContextTypesImportDeclaration(userPluginOptions?.stableForTests ?? false, userPluginOptions?.contextImport),
                    ...module.statements,
                ],
                module.ident,
                module.getNamespaceFlag(),
                module.program,
            )
        )
    }
}
