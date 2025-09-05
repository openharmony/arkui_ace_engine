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

import { TSInterfaceDeclaration, TSInterfaceHeritage } from '../../../generated';
import { isSameNativeObject } from '../../../arkts-api/peers/ArktsObject';
import { AstNode } from '../peers/AstNode';
import { attachModifiers, updateThenAttach } from '../utilities/private';

export function updateTSInterfaceDeclaration(
    original: TSInterfaceDeclaration,
    _extends: readonly TSInterfaceHeritage[],
    id: AstNode | undefined,
    typeParams: AstNode | undefined,
    body: AstNode | undefined,
    isStatic: boolean,
    isExternal: boolean
): TSInterfaceDeclaration {
    if (
        isSameNativeObject(_extends, original.extends) &&
        isSameNativeObject(id, original.id) &&
        isSameNativeObject(typeParams, original.typeParams) &&
        isSameNativeObject(body, original.body) &&
        isSameNativeObject(isStatic, original.isStatic) &&
        isSameNativeObject(isExternal, original.isFromExternal)
    ) {
        return original;
    }

    const update = updateThenAttach(
        TSInterfaceDeclaration.updateTSInterfaceDeclaration,
        attachModifiers,
        (node: TSInterfaceDeclaration, original: TSInterfaceDeclaration) => node.setAnnotations(original.annotations)
    );
    return update(original, _extends, id, typeParams, body, isStatic, isExternal);
}
