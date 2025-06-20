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

export interface TransformerOptions {
    contextImport?: string,
    stableForTests?: boolean
}

export default function memoParserTransformer(
    userPluginOptions?: TransformerOptions
) {
    return (program: arkts.Program, options: arkts.CompilationOptions, context: arkts.PluginContext) => {
        if (userPluginOptions?.contextImport && options) {
            /* Some files should not be processed by plugin actually */
            if (options.name.startsWith('@koalaui/common') || options.name.startsWith('@koalaui/compat')) return
            if (options.name.startsWith('@koalaui/runtime.internals') || options.name.startsWith('@koalaui/runtime/annotations')) return
        }
        return arkts.updateETSModuleByStatements(
            program.astNode,
            [
                factory.createContextTypesImportDeclaration(userPluginOptions?.stableForTests ?? false, userPluginOptions?.contextImport),
                ...program.astNode.statements,
            ]
        )
    }
}
