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

import { ObjectExpression, Property } from '../../../generated';
import { isSameNativeObject } from '../../../arkts-api/peers/ArktsObject';
import { attachModifiers, updateThenAttach } from '../utilities/private';
import { Es2pandaAstNodeType } from '../../../generated/Es2pandaEnums';

export function updateObjectExpression(
    original: ObjectExpression,
    nodeType: Es2pandaAstNodeType,
    properties: Property[],
    trailingComma: boolean
): ObjectExpression {
    if (
        isSameNativeObject(properties, original.properties)
        /* Improve: no getter for nodeType */
        /* Improve: no getter for trailingComma */
    ) {
        return original;
    }

    const update = updateThenAttach(ObjectExpression.updateObjectExpression, attachModifiers);
    return update(original, nodeType, properties, trailingComma);
}
