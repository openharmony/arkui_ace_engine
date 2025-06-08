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

import {
    ClassDeclaration,
    ClassDefinition,
} from "../../generated"
import { isSameNativeObject } from "../peers/ArktsObject"
import { updateNodeByNode } from "../utilities/private"
import { Es2pandaModifierFlags } from "../../generated/Es2pandaEnums"

export function createClassDeclaration(
    def?: ClassDefinition,
    modifierFlags?: Es2pandaModifierFlags,
): ClassDeclaration {
    const res = ClassDeclaration.createClassDeclaration(
        def,
    )
    if (modifierFlags) {
        res.modifierFlags = modifierFlags
    }
    return res
}

export function updateClassDeclaration(
    original: ClassDeclaration,
    def?: ClassDefinition,
    modifierFlags?: Es2pandaModifierFlags,
): ClassDeclaration {
    if (isSameNativeObject(def, original.definition)
        && isSameNativeObject(modifierFlags, original.modifierFlags)
    ) {
        return original
    }
    return updateNodeByNode(
        createClassDeclaration(
            def,
            modifierFlags,
        ),
        original
    )
}
