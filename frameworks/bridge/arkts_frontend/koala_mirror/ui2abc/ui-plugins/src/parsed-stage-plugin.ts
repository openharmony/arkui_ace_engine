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
import * as path from "node:path"
import { ComponentTransformer, ComponentTransformerOptions } from './component-transformer'
import { AnnotationsTransformer } from "./annotation-translator"
import { CallTransformer } from "./call-transformer"
import { Importer } from "./utils"
import { ImportsTransformer } from "./imports-transformer"
import { StructRecorder, StructsResolver, StructTable } from "./struct-recorder"
import { StructCallRewriter } from "./struct-call-rewriter"
import { ClassTransformer } from "./class-transformer"


export default function parsedTransformer(
    userPluginOptions?: ComponentTransformerOptions
): arkts.ProgramTransformer {
    return (program: arkts.Program, compilationOptions: arkts.CompilationOptions, context: arkts.PluginContext) => {
        const restart = compilationOptions.restart
        const importer = new Importer()
        let resolver = context.parameter<StructsResolver>("structsTable")
        if (!resolver) {
            resolver = new StructsResolver(restart)
            context.setParameter("structsTable", resolver)
        }
        
        // TODO: this logic is completely wrong, and need to be fully rethought.
        const newFileIfRestart = () => path.resolve(arkts.global.arktsconfig!.outDir, "ui-parsed", path.relative(arkts.global.arktsconfig!.baseUrl, arkts.global.filePath))
        const currentFile = restart ? newFileIfRestart() : arkts.global.filePath
        const structs = resolver.getOrCreateTable(currentFile, restart)
        context.setParameter("importer", importer)

        const transformers: arkts.AbstractVisitor[] = [
            new StructRecorder(structs, restart),
            new StructCallRewriter(structs, importer),
            new ClassTransformer(importer),
            new ComponentTransformer(importer, userPluginOptions),
            new AnnotationsTransformer(),
            new CallTransformer(importer, userPluginOptions),
            new ImportsTransformer(importer)
        ]
        const result = transformers.reduce((node: arkts.AstNode, transformer: arkts.AbstractVisitor) => transformer.visitor(node), program.ast)
        program.setAst(result as arkts.ETSModule)
    }
}
