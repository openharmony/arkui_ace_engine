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

import { Identifier } from '../../../generated';
import { isSameNativeObject } from '../../../arkts-api/peers/ArktsObject';
import { VariableDeclarator } from '../types';
import { attachModifiers, updateThenAttach } from '../utilities/private';
import { Es2pandaVariableDeclaratorFlag } from '../../../generated/Es2pandaEnums';
import { AstNode } from '../peers/AstNode';

export function updateVariableDeclarator(
    original: VariableDeclarator,
    flag: Es2pandaVariableDeclaratorFlag,
    name: Identifier,
    initializer: AstNode | undefined
): VariableDeclarator {
    if (
        isSameNativeObject(name, original.name) &&
        isSameNativeObject(initializer, original.initializer)
        /* Improve: no getter for flag */
    ) {
        return original;
    }

    const update = updateThenAttach(VariableDeclarator.update, attachModifiers);
    return update(original, flag, name, initializer);
}
