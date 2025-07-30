/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

import { Es2pandaAstNodeType } from "../../generated/Es2pandaEnums"
import { ArrayExpression, Expression } from "../../generated"
import { isSameNativeObject } from "../peers/ArktsObject"
import { updateNodeByNode } from "../../reexport-for-generated"

export function createArrayExpression(
    elements: readonly Expression[]
): ArrayExpression {
    return ArrayExpression.create1ArrayExpression(
        Es2pandaAstNodeType.AST_NODE_TYPE_ARRAY_EXPRESSION,
        elements,
        false
    )
}

export function updateArrayExpression(
    original: ArrayExpression,
    elements: readonly Expression[]
): ArrayExpression {
    if (isSameNativeObject(original.elements, elements)) {
        return original
    }
    return updateNodeByNode(
        createArrayExpression(elements),
        original
    )
}
