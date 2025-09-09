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

import { BlockStatement, Statement } from '../../../generated';
import { isSameNativeObject } from '../../../arkts-api/peers/ArktsObject';
import { attachModifiers, updateThenAttach } from '../utilities/private';

export function updateBlockStatement(original: BlockStatement, statementList: readonly Statement[]): BlockStatement {
    if (isSameNativeObject(statementList, original.statements)) {
        return original;
    }

    const update = updateThenAttach(BlockStatement.updateBlockStatement, attachModifiers);
    return update(original, statementList);
}
