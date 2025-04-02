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
import { FunctionTransformer } from "./FunctionTransformer"
import { PositionalIdTracker } from "./utils"
import { ParameterTransformer } from "./ParameterTransformer"
import { ReturnTransformer } from "./ReturnTranformer"
import { EtsglobalRemover } from "./EtsglobalRemover"

export interface TransformerOptions {
    trace?: boolean,
    removeEtsglobal?: boolean
}

export default function memoTransformer(
    userPluginOptions?: TransformerOptions
) {
    return (node0: arkts.EtsScript) => {
        const node = (userPluginOptions?.removeEtsglobal ? new EtsglobalRemover().visitor(node0) : node0) as arkts.EtsScript
        const positionalIdTracker = new PositionalIdTracker(arkts.getFileName(), false)
        const parameterTransformer = new ParameterTransformer(positionalIdTracker)
        const returnTransformer = new ReturnTransformer()
        const functionTransformer = new FunctionTransformer(positionalIdTracker, parameterTransformer, returnTransformer)
        return functionTransformer.visitor(
            arkts.factory.updateEtsScript(
                node,
                [
                    ...node.getChildren().filter(it => arkts.isEtsImportDeclaration(it)),
                    factory.createContextTypesImportDeclaration(),
                    ...node.getChildren().filter(it => !arkts.isEtsImportDeclaration(it)),
                ]
            )
        )
    }
}
