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

import { AssignmentExpression, Expression } from "../../generated"
import { isSameNativeObject } from "../peers/ArktsObject"
import { updateNodeByNode } from "../utilities/private"
import { Es2pandaAstNodeType, Es2pandaTokenType } from "../../generated/Es2pandaEnums"

export function createAssignmentExpression(
    left: Expression | undefined,
    right: Expression | undefined,
    assignmentOperator: Es2pandaTokenType
): AssignmentExpression {
    return AssignmentExpression.create1AssignmentExpression(
        Es2pandaAstNodeType.AST_NODE_TYPE_ASSIGNMENT_EXPRESSION,
        left,
        right,
        assignmentOperator,
    )
}

export function updateAssignmentExpression(
    original: AssignmentExpression,
    left: Expression | undefined,
    right: Expression | undefined,
    assignmentOperator: Es2pandaTokenType
): AssignmentExpression {
    if (isSameNativeObject(left, original.left)
        && isSameNativeObject(right, original.right)
        && isSameNativeObject(assignmentOperator, original.operatorType)
    ) {
        return original
    }
    return updateNodeByNode(
        createAssignmentExpression(left, right, assignmentOperator),
        original
    )
}
