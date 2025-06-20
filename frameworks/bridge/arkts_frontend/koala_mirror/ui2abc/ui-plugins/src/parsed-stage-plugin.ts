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

import * as arkts from "@koalaui/libarkts"
import { ComponentTransformer, ComponentTransformerOptions } from './component-transformer'
import { AnnotationsTransformer } from "./annotation-translator"
import { CallTransformer } from "./call-transformer"
import { Importer } from "./utils"
import { ImportsTransformer } from "./imports-transformer"
import { StructRecorder, StructTable } from "./struct-recorder"
import { StructCallRewriter } from "./struct-call-rewriter"


export default function parsedTransformer(
    userPluginOptions?: ComponentTransformerOptions
): arkts.ProgramTransformer {
    return (program: arkts.Program, _compilationOptions: arkts.CompilationOptions, context: arkts.PluginContext) => {
        const importer = new Importer()
        const structTable = new StructTable()
        context.setParameter("structTable", structTable)
        const tranformers: arkts.AbstractVisitor[] = [
            new StructRecorder(structTable),
            new ComponentTransformer(importer, userPluginOptions),
            new StructCallRewriter(importer, structTable),
            new AnnotationsTransformer(),
            new CallTransformer(importer, userPluginOptions),
            new ImportsTransformer(importer)
        ]
        tranformers.reduce((node: arkts.AstNode, transformer: arkts.AbstractVisitor) => transformer.visitor(node), program.astNode)
    }
}
