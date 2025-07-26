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
import { StyleTransformer } from "./style-transformer"
import { EtsFirstArgTransformer } from "./ets-first-arg-transformer"
import { BuilderLambdaTransformer } from "./builder-lambda-transformer"
import { InstantiateFactoryHelper } from "./instantiate-factory-helper"

export interface TransformerOptions {
    trace?: boolean,
}

export default function checkedTransformer(
    userPluginOptions?: TransformerOptions
): arkts.ProgramTransformer {
    console.log("CHECKED: ", userPluginOptions)
    return (program: arkts.Program, _compilationOptions: arkts.CompilationOptions, context: arkts.PluginContext) => {
        [
            new InstantiateFactoryHelper(),
            new EtsFirstArgTransformer(),
            new StyleTransformer(),
            new BuilderLambdaTransformer()
        ]
        .reduce((node: arkts.AstNode, transformer) => transformer.visitor(node), program.astNode)
    }
}
