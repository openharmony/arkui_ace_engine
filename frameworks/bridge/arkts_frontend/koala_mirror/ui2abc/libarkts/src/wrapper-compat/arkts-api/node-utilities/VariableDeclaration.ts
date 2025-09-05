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

import { KInt } from '@koalaui/interop';
import { isSameNativeObject } from '../../../arkts-api/peers/ArktsObject';
import { VariableDeclaration, VariableDeclarator } from '../types';
import { attachModifiers, updateThenAttach } from '../utilities/private';
import { Es2pandaVariableDeclarationKind } from '../../../generated/Es2pandaEnums';

export function updateVariableDeclaration(
    original: VariableDeclaration,
    modifiers: KInt,
    kind: Es2pandaVariableDeclarationKind,
    declarators: readonly VariableDeclarator[]
): VariableDeclaration {
    if (
        isSameNativeObject(modifiers, original.modifiers) &&
        isSameNativeObject(kind, original.declarationKind) &&
        isSameNativeObject(declarators, original.declarators)
    ) {
        return original;
    }

    const update = updateThenAttach(
        VariableDeclaration.update,
        attachModifiers,
        (node: VariableDeclaration, original: VariableDeclaration) => node.setAnnotations(original.annotations)
    );
    return update(original, modifiers, kind, declarators);
}
