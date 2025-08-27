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

import {
    global,
    passNode,
    passNodeArray,
    unpackNonNullableNode,
    unpackNode,
    unpackNodeArray,
    assertValidPeer,
    AstNode,
    Es2pandaAstNodeType,
    KNativePointer,
    nodeByType,
    ArktsObject,
    unpackString
} from "../../reexport-for-generated"

import { Expression } from "./Expression"
import { Es2pandaTokenType } from "./../Es2pandaEnums"
export class AssignmentExpression extends Expression {
     constructor(pointer: KNativePointer) {
        super(pointer)
        console.warn("Warning: stub node AssignmentExpression")
    }
    get left(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._AssignmentExpressionLeftConst(global.context, this.peer))
    }
    get right(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._AssignmentExpressionRightConst(global.context, this.peer))
    }
    /** @deprecated */
    setRight(expr: Expression): this {
        global.generatedEs2panda._AssignmentExpressionSetRight(global.context, this.peer, passNode(expr))
        return this
    }
    /** @deprecated */
    setLeft(expr: Expression): this {
        global.generatedEs2panda._AssignmentExpressionSetLeft(global.context, this.peer, passNode(expr))
        return this
    }
    get result(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._AssignmentExpressionResultConst(global.context, this.peer))
    }
    get operatorType(): Es2pandaTokenType {
        return global.generatedEs2panda._AssignmentExpressionOperatorTypeConst(global.context, this.peer)
    }
    /** @deprecated */
    setResult(expr: Expression): this {
        global.generatedEs2panda._AssignmentExpressionSetResult(global.context, this.peer, passNode(expr))
        return this
    }
    get isLogicalExtended(): boolean {
        return global.generatedEs2panda._AssignmentExpressionIsLogicalExtendedConst(global.context, this.peer)
    }
    /** @deprecated */
    setIgnoreConstAssign(): this {
        global.generatedEs2panda._AssignmentExpressionSetIgnoreConstAssign(global.context, this.peer)
        return this
    }
    get isIgnoreConstAssign(): boolean {
        return global.generatedEs2panda._AssignmentExpressionIsIgnoreConstAssignConst(global.context, this.peer)
    }
}
export function isAssignmentExpression(node: AstNode): node is AssignmentExpression {
    return node instanceof AssignmentExpression
}