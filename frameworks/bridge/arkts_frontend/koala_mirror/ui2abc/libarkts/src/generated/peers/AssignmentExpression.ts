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
    KNativePointer,
    nodeByType,
    ArktsObject,
    unpackString
} from "../../reexport-for-generated"

import { CodeGen } from "./CodeGen"
import { Es2pandaAstNodeType } from "./../Es2pandaEnums"
import { Es2pandaTokenType } from "./../Es2pandaEnums"
import { Expression } from "./Expression"
export class AssignmentExpression extends Expression {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 159)
        super(pointer)
    }
    static create1AssignmentExpression(type: Es2pandaAstNodeType, left: Expression | undefined, right: Expression | undefined, assignmentOperator: Es2pandaTokenType): AssignmentExpression {
        return new AssignmentExpression(global.generatedEs2panda._CreateAssignmentExpression1(global.context, type, passNode(left), passNode(right), assignmentOperator))
    }
    static updateAssignmentExpression(original: AssignmentExpression | undefined, left: Expression | undefined, right: Expression | undefined, assignmentOperator: Es2pandaTokenType): AssignmentExpression {
        return new AssignmentExpression(global.generatedEs2panda._UpdateAssignmentExpression(global.context, passNode(original), passNode(left), passNode(right), assignmentOperator))
    }
    static update1AssignmentExpression(original: AssignmentExpression | undefined, type: Es2pandaAstNodeType, left: Expression | undefined, right: Expression | undefined, assignmentOperator: Es2pandaTokenType): AssignmentExpression {
        return new AssignmentExpression(global.generatedEs2panda._UpdateAssignmentExpression1(global.context, passNode(original), type, passNode(left), passNode(right), assignmentOperator))
    }
    get left(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._AssignmentExpressionLeft(global.context, this.peer))
    }
    get right(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._AssignmentExpressionRight(global.context, this.peer))
    }
    /** @deprecated */
    setRight(expr?: Expression): this {
        global.generatedEs2panda._AssignmentExpressionSetRight(global.context, this.peer, passNode(expr))
        return this
    }
    /** @deprecated */
    setLeft(expr?: Expression): this {
        global.generatedEs2panda._AssignmentExpressionSetLeft(global.context, this.peer, passNode(expr))
        return this
    }
    get result(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._AssignmentExpressionResult(global.context, this.peer))
    }
    get operatorType(): Es2pandaTokenType {
        return global.generatedEs2panda._AssignmentExpressionOperatorTypeConst(global.context, this.peer)
    }
    /** @deprecated */
    setResult(expr?: Expression): this {
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
    get convertibleToAssignmentPatternRight(): boolean {
        return global.generatedEs2panda._AssignmentExpressionConvertibleToAssignmentPatternRight(global.context, this.peer)
    }
    /** @deprecated */
    compilePattern(pg?: CodeGen): this {
        global.generatedEs2panda._AssignmentExpressionCompilePatternConst(global.context, this.peer, passNode(pg))
        return this
    }
}
export function isAssignmentExpression(node: object | undefined): node is AssignmentExpression {
    return node instanceof AssignmentExpression
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_ASSIGNMENT_EXPRESSION)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_ASSIGNMENT_EXPRESSION, (peer: KNativePointer) => new AssignmentExpression(peer))
}