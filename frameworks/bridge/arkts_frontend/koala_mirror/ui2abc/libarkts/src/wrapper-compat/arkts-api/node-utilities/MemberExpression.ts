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

import { isSameNativeObject } from '../../../arkts-api/peers/ArktsObject';
import { AstNode } from '../peers/AstNode';
import { MemberExpression } from '../to-be-generated/MemberExpression';
import { attachModifiers, updateThenAttach } from '../utilities/private';
import { Es2pandaMemberExpressionKind } from '../../../generated/Es2pandaEnums';

export function updateMemberExpression(
    original: MemberExpression,
    object: AstNode,
    property: AstNode,
    kind: Es2pandaMemberExpressionKind,
    computed: boolean,
    optional: boolean
): MemberExpression {
    if (
        isSameNativeObject(object, original.object) &&
        isSameNativeObject(property, original.property) &&
        isSameNativeObject(kind, original.kind) &&
        isSameNativeObject(computed, original.computed) &&
        isSameNativeObject(optional, original.optional)
    ) {
        return original;
    }

    const update = updateThenAttach(MemberExpression.update, attachModifiers);
    return update(original, object, property, kind, computed, optional);
}
