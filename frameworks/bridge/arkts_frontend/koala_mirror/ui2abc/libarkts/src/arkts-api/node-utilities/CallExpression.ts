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

import { BlockStatement, CallExpression, Expression, TSTypeParameterInstantiation } from "../../generated"
import { isSameNativeObject } from "../peers/ArktsObject"
import { updateNodeByNode } from "../utilities/private"

export function createCallExpression(
    callee: Expression | undefined,
    _arguments: readonly Expression[],
    typeParams: TSTypeParameterInstantiation | undefined,
    optional_arg: boolean = false,
    trailingComma: boolean = false,
    trailingBlock: BlockStatement | undefined = undefined,
): CallExpression {
    const res = CallExpression.createCallExpression(
        callee,
        _arguments,
        typeParams,
        optional_arg,
        trailingComma,
    )
    if (trailingBlock) {
        res.setTrailingBlock(trailingBlock)
    }
    return res
}

export function updateCallExpression(
    original: CallExpression,
    callee: Expression | undefined,
    _arguments: readonly Expression[],
    typeParams: TSTypeParameterInstantiation | undefined,
    optional_arg: boolean = false,
    trailingComma: boolean = false,
    trailingBlock: BlockStatement | undefined = undefined,
): CallExpression {
    if (isSameNativeObject(callee, original.callee)
        && isSameNativeObject(_arguments, original.arguments)
        && isSameNativeObject(typeParams, original.typeParams)
        && isSameNativeObject(optional_arg, original.isOptional)
        && isSameNativeObject(trailingComma, original.hasTrailingComma)
        && isSameNativeObject(trailingBlock, original.trailingBlock)
    ) {
        return original
    }
    return updateNodeByNode(
        createCallExpression(callee, _arguments, typeParams, optional_arg, trailingComma, trailingBlock),
        original
    )
}