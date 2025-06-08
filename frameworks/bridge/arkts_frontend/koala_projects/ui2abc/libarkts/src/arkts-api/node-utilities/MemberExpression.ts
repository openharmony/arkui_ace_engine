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

import { Expression, MemberExpression } from "../../generated"
import { isSameNativeObject } from "../peers/ArktsObject"
import { updateNodeByNode } from "../utilities/private"
import { Es2pandaMemberExpressionKind } from "../../generated/Es2pandaEnums"

export function updateMemberExpression(
    original: MemberExpression,
    object_arg: Expression | undefined,
    property: Expression | undefined,
    kind: Es2pandaMemberExpressionKind,
    computed: boolean,
    optional_arg: boolean
): MemberExpression {
    if (isSameNativeObject(object_arg, original.object)
        && isSameNativeObject(property, original.property)
        && isSameNativeObject(kind, original.kind)
        && isSameNativeObject(computed, original.isComputed)
        && isSameNativeObject(optional_arg, original.isOptional)
    ) {
        return original
    }
    return updateNodeByNode(
        MemberExpression.createMemberExpression(object_arg, property, kind, computed, optional_arg),
        original
    )
}
