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

import { Identifier, TSTypeAliasDeclaration, TSTypeParameterDeclaration, TypeNode } from '../../../generated';
import { isSameNativeObject } from '../../../arkts-api/peers/ArktsObject';
import { attachModifiers, updateThenAttach } from '../utilities/private';

export function updateTSTypeAliasDeclaration(
    original: TSTypeAliasDeclaration,
    id?: Identifier,
    typeParams?: TSTypeParameterDeclaration,
    typeAnnotation?: TypeNode
): TSTypeAliasDeclaration {
    if (
        isSameNativeObject(id, original.id) &&
        isSameNativeObject(typeParams, original.typeParams) &&
        isSameNativeObject(typeAnnotation, original.typeAnnotation)
    ) {
        return original;
    }

    const update = updateThenAttach(
        TSTypeAliasDeclaration.updateTSTypeAliasDeclaration,
        attachModifiers,
        (node: TSTypeAliasDeclaration, original: TSTypeAliasDeclaration) => node.setAnnotations(original.annotations)
    );
    return update(original, id, typeParams, typeAnnotation);
}
