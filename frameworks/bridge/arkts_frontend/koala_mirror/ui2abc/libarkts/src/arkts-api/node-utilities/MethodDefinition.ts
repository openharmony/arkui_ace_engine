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

import { ETSFunctionType, Expression, FunctionSignature, MethodDefinition } from "../../generated"
import {
    Es2pandaMethodDefinitionKind,
    Es2pandaModifierFlags,
    Es2pandaScriptFunctionFlags
} from "../../generated/Es2pandaEnums"
import { isSameNativeObject } from "../peers/ArktsObject"
import { updateNodeByNode } from "../utilities/private"

export function createMethodDefinition(
    kind: Es2pandaMethodDefinitionKind,
    key: Expression | undefined,
    value: Expression | undefined,
    modifiers: Es2pandaModifierFlags,
    isComputed: boolean,
    overloads?: readonly MethodDefinition[]
): MethodDefinition {
    const res = MethodDefinition.createMethodDefinition(
        kind,
        key,
        value,
        modifiers,
        isComputed,
    )
    if (overloads) {
        res.setOverloads(overloads)
    }
    return res
}

export function updateMethodDefinition(
    original: MethodDefinition,
    kind: Es2pandaMethodDefinitionKind,
    key: Expression | undefined,
    value: Expression | undefined,
    modifiers: Es2pandaModifierFlags,
    isComputed: boolean,
    overloads?: readonly MethodDefinition[]
): MethodDefinition {
    if (isSameNativeObject(kind, original.kind)
        && isSameNativeObject(key, original.key)
        && isSameNativeObject(value, original.value)
        && isSameNativeObject(modifiers, original.modifierFlags)
        && isSameNativeObject(isComputed, original.isComputed)
        && isSameNativeObject(overloads, original.overloads)
    ) {
        return original
    }
    return updateNodeByNode(
        createMethodDefinition(
            kind,
            key,
            value,
            modifiers,
            isComputed,
            overloads,
        ),
        original
    )
}
