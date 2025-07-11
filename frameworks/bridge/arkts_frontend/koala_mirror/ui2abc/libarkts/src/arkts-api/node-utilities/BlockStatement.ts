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

import { BlockStatement, Statement } from "../../generated"
import { isSameNativeObject } from "../peers/ArktsObject"
import { updateNodeByNode } from "../utilities/private"

export function createBlockStatement(statements: readonly Statement[]): BlockStatement {
    return BlockStatement.createBlockStatement(statements)
}

export function updateBlockStatement(original: BlockStatement, statements: readonly Statement[]): BlockStatement {
    if (isSameNativeObject(statements, original.statements)) {
        return original
    }
    return updateNodeByNode(BlockStatement.createBlockStatement(statements), original)
}
