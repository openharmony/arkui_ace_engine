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

import { LabelPair } from '../../../generated/peers/LabelPair';
import { BlockStatement, CatchClause, Statement, TryStatement } from '../../../generated';
import { isSameNativeObject } from '../../../arkts-api/peers/ArktsObject';
import { attachModifiers, updateThenAttach } from '../utilities/private';

export function updateTryStatement(
    original: TryStatement,
    block: BlockStatement | undefined,
    catchClauses: readonly CatchClause[],
    finalizer: BlockStatement | undefined,
    finalizerInsertionsLabelPair: readonly LabelPair[],
    finalizerInsertionsStatement: readonly Statement[]
): TryStatement {
    if (
        isSameNativeObject(block, original.block) &&
        isSameNativeObject(catchClauses, original.catchClauses) &&
        isSameNativeObject(finalizer, original.finallyBlock)
        /* Improve: no getter for finalizerInsertionsLabelPair */
        /* Improve: no getter for finalizerInsertionsStatement */
    ) {
        return original;
    }

    const update = updateThenAttach(TryStatement.updateTryStatement, attachModifiers);
    return update(original, block, catchClauses, finalizer, finalizerInsertionsLabelPair, finalizerInsertionsStatement);
}
