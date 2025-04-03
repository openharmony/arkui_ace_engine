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

import { Statement } from "./Statement"
import { Expression } from "./Expression"
export class ExpressionStatement extends Statement {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 30)
        super(pointer)
        console.warn("Warning: stub node ExpressionStatement")
    }
    static createExpressionStatement(expr?: Expression): ExpressionStatement {
        return new ExpressionStatement(global.generatedEs2panda._CreateExpressionStatement(global.context, passNode(expr)))
    }
    static updateExpressionStatement(original?: ExpressionStatement, expr?: Expression): ExpressionStatement {
        return new ExpressionStatement(global.generatedEs2panda._UpdateExpressionStatement(global.context, passNode(original), passNode(expr)))
    }
    get getExpression(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._ExpressionStatementGetExpressionConst(global.context, this.peer))
    }
    /** @deprecated */
    setExpression(expr: Expression): this {
        global.generatedEs2panda._ExpressionStatementSetExpression(global.context, this.peer, passNode(expr))
        return this
    }
}
export function isExpressionStatement(node: AstNode): node is ExpressionStatement {
    return node instanceof ExpressionStatement
}
if (!nodeByType.has(30)) {
    nodeByType.set(30, ExpressionStatement)
}