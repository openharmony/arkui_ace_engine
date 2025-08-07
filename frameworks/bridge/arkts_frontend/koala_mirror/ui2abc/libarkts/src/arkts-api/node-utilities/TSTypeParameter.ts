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

import { Identifier, TSTypeParameter, TypeNode } from "../../generated"
import { Es2pandaModifierFlags } from "../../generated/Es2pandaEnums"
import { isSameNativeObject } from "../peers/ArktsObject"
import { updateNodeByNode } from "../utilities/private"

export function updateTSTypeParameter(
    original: TSTypeParameter,
    name: Identifier | undefined,
    constraint: TypeNode | undefined,
    defaultType: TypeNode | undefined,
    flags: Es2pandaModifierFlags
): TSTypeParameter {
    if (isSameNativeObject(name, original.name)
        && isSameNativeObject(constraint, original.constraint)
        && isSameNativeObject(defaultType, original.defaultType)
        && isSameNativeObject(flags, original.modifierFlags)
    ) {
        return original
    }
    return updateNodeByNode(
        TSTypeParameter.create1TSTypeParameter(name, constraint, defaultType, flags),
        original
    )
}