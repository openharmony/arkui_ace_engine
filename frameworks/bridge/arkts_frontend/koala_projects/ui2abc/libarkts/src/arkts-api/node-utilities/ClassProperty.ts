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

import { AnnotationUsage, ClassProperty, Expression, TypeNode } from "../../generated"
import { Es2pandaModifierFlags } from "../../generated/Es2pandaEnums"
import { isSameNativeObject } from "../peers/ArktsObject"
import { updateNodeByNode } from "../utilities/private"

export function createClassProperty(
    key: Expression | undefined,
    value: Expression | undefined,
    typeAnnotation: TypeNode | undefined,
    modifiers: Es2pandaModifierFlags,
    isComputed: boolean,
    annotations?: readonly AnnotationUsage[],
): ClassProperty {
    const res = ClassProperty.createClassProperty(
        key,
        value,
        typeAnnotation,
        modifiers,
        isComputed,
    )
    if (annotations) {
        res.setAnnotations(annotations)
    }
    return res
}

export function updateClassProperty(
    original: ClassProperty,
    key: Expression | undefined,
    value: Expression | undefined,
    typeAnnotation: TypeNode | undefined,
    modifiers: Es2pandaModifierFlags,
    isComputed: boolean,
    annotations?: readonly AnnotationUsage[],
): ClassProperty {
    if (isSameNativeObject(key, original.key)
        && isSameNativeObject(value, original.value)
        && isSameNativeObject(typeAnnotation, original.typeAnnotation)
        && isSameNativeObject(modifiers, original.modifierFlags)
        && isSameNativeObject(isComputed, original.isComputed)
        && isSameNativeObject(annotations, original.annotations)
    ) {
        return original
    }
    return updateNodeByNode(
        createClassProperty(key, value, typeAnnotation, modifiers, isComputed, annotations),
        original
    )
}
