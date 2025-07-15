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

import { ArrayExpression, Expression } from '../../../generated';
import { isSameNativeObject } from '../../../arkts-api/peers/ArktsObject';
import { attachModifiers, updateThenAttach } from '../utilities/private';

export function updateArrayExpression(original: ArrayExpression, elements: readonly Expression[]): ArrayExpression {
    if (isSameNativeObject(elements, original.elements)) {
        return original;
    }
    const update = updateThenAttach(
        ArrayExpression.updateArrayExpression,
        attachModifiers,
        attachOptionalAndDeclaration
    );
    return update(original, elements);
}

function attachOptionalAndDeclaration(node: ArrayExpression, original: ArrayExpression): ArrayExpression {
    if (node.isDeclaration) {
        node.setDeclaration();
    }
    node.setOptional(original.isOptional);
    return node;
}
