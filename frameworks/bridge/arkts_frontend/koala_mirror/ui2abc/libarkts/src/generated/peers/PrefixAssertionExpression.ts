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
import { TypeNode } from "./TypeNode"
export class PrefixAssertionExpression extends Expression {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 54)
        super(pointer)
    }
    static createPrefixAssertionExpression(expr?: Expression, type?: TypeNode): PrefixAssertionExpression {
        return new PrefixAssertionExpression(global.generatedEs2panda._CreatePrefixAssertionExpression(global.context, passNode(expr), passNode(type)))
    }
    static updatePrefixAssertionExpression(original?: PrefixAssertionExpression, expr?: Expression, type?: TypeNode): PrefixAssertionExpression {
        return new PrefixAssertionExpression(global.generatedEs2panda._UpdatePrefixAssertionExpression(global.context, passNode(original), passNode(expr), passNode(type)))
    }
    get expr(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._PrefixAssertionExpressionExprConst(global.context, this.peer))
    }
    get type(): TypeNode | undefined {
        return unpackNode(global.generatedEs2panda._PrefixAssertionExpressionTypeConst(global.context, this.peer))
    }
}
export function isPrefixAssertionExpression(node: object | undefined): node is PrefixAssertionExpression {
    return node instanceof PrefixAssertionExpression
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_PREFIX_ASSERTION_EXPRESSION)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_PREFIX_ASSERTION_EXPRESSION, (peer: KNativePointer) => new PrefixAssertionExpression(peer))
}