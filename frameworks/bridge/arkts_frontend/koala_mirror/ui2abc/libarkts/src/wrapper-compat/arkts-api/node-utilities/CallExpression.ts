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

import { TypeNode } from '../../../generated';
import { isSameNativeObject } from '../../../arkts-api/peers/ArktsObject';
import { AstNode } from '../peers/AstNode';
import { CallExpression } from '../types';
import { attachModifiers, updateThenAttach } from '../utilities/private';

export function updateCallExpression(
    original: CallExpression,
    expression: AstNode,
    typeArguments: readonly TypeNode[] | undefined,
    args: readonly AstNode[] | undefined,
    isOptional?: boolean,
    trailingComma?: boolean
): CallExpression {
    if (
        isSameNativeObject(expression, original.expression) &&
        isSameNativeObject(typeArguments, original.typeArguments) &&
        isSameNativeObject(args, original.arguments)
    ) {
        return original;
    }

    const update = updateThenAttach(
        CallExpression.update,
        attachModifiers,
        (node: CallExpression, original: CallExpression) =>
            !!original.trailingBlock ? node.setTralingBlock(original.trailingBlock) : node
    );
    return update(original, expression, typeArguments, args, isOptional, trailingComma);
}
