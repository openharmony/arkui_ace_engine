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

export default function parsedTransformer(
    userPluginOptions?: ComponentTransformerOptions
) {
    console.log(`PARSED: ${userPluginOptions}`)
    return (node: arkts.ETSModule) => [
            new ComponentTransformer(userPluginOptions),
            new AnnotationsTransformer()
        ]
        .reduce((node: arkts.AstNode, transformer) => transformer.visitor(node), node)
}
