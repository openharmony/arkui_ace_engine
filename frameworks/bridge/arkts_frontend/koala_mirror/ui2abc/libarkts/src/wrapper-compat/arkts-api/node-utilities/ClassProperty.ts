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

import { ClassProperty, Expression, TypeNode } from '../../../generated';
import { isSameNativeObject } from '../../../arkts-api/peers/ArktsObject';
import { updateThenAttach } from '../utilities/private';
import { classPropertySetOptional, hasModifierFlag } from '../utilities/public';
import { Es2pandaModifierFlags } from '../../../generated/Es2pandaEnums';

export function updateClassProperty(
    original: ClassProperty,
    key: Expression | undefined,
    value: Expression | undefined,
    typeAnnotation: TypeNode | undefined,
    modifiers: Es2pandaModifierFlags,
    isComputed: boolean
): ClassProperty {
    if (
        isSameNativeObject(key, original.key) &&
        isSameNativeObject(value, original.value) &&
        isSameNativeObject(typeAnnotation, original.typeAnnotation) &&
        isSameNativeObject(modifiers, original.modifiers) &&
        isSameNativeObject(isComputed, original.isComputed)
    ) {
        return original;
    }

    const update = updateThenAttach(
        ClassProperty.updateClassProperty,
        (node: ClassProperty, original: ClassProperty) => node.setAnnotations(original.annotations),
        (node: ClassProperty, original: ClassProperty) => {
            if (hasModifierFlag(original, Es2pandaModifierFlags.MODIFIER_FLAGS_OPTIONAL)) {
                return classPropertySetOptional(node, true);
            }
            return node;
        }
    );
    return update(original, key, value, typeAnnotation, modifiers, isComputed);
}
