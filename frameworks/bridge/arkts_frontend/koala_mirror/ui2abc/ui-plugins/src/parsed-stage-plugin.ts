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

export default function parsedTransformer(
    userPluginOptions?: ComponentTransformerOptions
) {
    const imports = new Importer()
    const structTable = new StructTable()
    return (program: arkts.Program) => [
            new StructRecorder(structTable),
            new ComponentTransformer(imports, structTable, userPluginOptions),
            new AnnotationsTransformer(),
            new CallTransformer(imports, userPluginOptions),
            new ImportsTransformer(program, imports)
        ]
        .reduce((node: arkts.AstNode, transformer) => transformer.visitor(node), program.astNode)
}
