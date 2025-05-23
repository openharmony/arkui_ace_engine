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

import { Es2pandaAstNodeType } from "./../Es2pandaEnums"
import { Expression } from "./Expression"
export class ETSNewClassInstanceExpression extends Expression {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 78)
        super(pointer)
    }
    static createETSNewClassInstanceExpression(typeReference: Expression | undefined, _arguments: readonly Expression[]): ETSNewClassInstanceExpression {
        return new ETSNewClassInstanceExpression(global.generatedEs2panda._CreateETSNewClassInstanceExpression(global.context, passNode(typeReference), passNodeArray(_arguments), _arguments.length))
    }
    static updateETSNewClassInstanceExpression(original: ETSNewClassInstanceExpression | undefined, typeReference: Expression | undefined, _arguments: readonly Expression[]): ETSNewClassInstanceExpression {
        return new ETSNewClassInstanceExpression(global.generatedEs2panda._UpdateETSNewClassInstanceExpression(global.context, passNode(original), passNode(typeReference), passNodeArray(_arguments), _arguments.length))
    }
    static update1ETSNewClassInstanceExpression(original?: ETSNewClassInstanceExpression, other?: ETSNewClassInstanceExpression): ETSNewClassInstanceExpression {
        return new ETSNewClassInstanceExpression(global.generatedEs2panda._UpdateETSNewClassInstanceExpression1(global.context, passNode(original), passNode(other)))
    }
    get typeRef(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._ETSNewClassInstanceExpressionGetTypeRefConst(global.context, this.peer))
    }
    get arguments(): readonly Expression[] {
        return unpackNodeArray(global.generatedEs2panda._ETSNewClassInstanceExpressionGetArguments(global.context, this.peer))
    }
    /** @deprecated */
    setArguments(_arguments: readonly Expression[]): this {
        global.generatedEs2panda._ETSNewClassInstanceExpressionSetArguments(global.context, this.peer, passNodeArray(_arguments), _arguments.length)
        return this
    }
    /** @deprecated */
    addToArgumentsFront(expr?: Expression): this {
        global.generatedEs2panda._ETSNewClassInstanceExpressionAddToArgumentsFront(global.context, this.peer, passNode(expr))
        return this
    }
}
export function isETSNewClassInstanceExpression(node: object | undefined): node is ETSNewClassInstanceExpression {
    return node instanceof ETSNewClassInstanceExpression
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_ETS_NEW_CLASS_INSTANCE_EXPRESSION)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_ETS_NEW_CLASS_INSTANCE_EXPRESSION, (peer: KNativePointer) => new ETSNewClassInstanceExpression(peer))
}