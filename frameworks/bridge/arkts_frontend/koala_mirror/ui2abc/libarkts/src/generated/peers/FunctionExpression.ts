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
import { Identifier } from "./Identifier"
import { ScriptFunction } from "./ScriptFunction"
export class FunctionExpression extends Expression {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 35)
        super(pointer)
    }
    static create1FunctionExpression(namedExpr?: Identifier, func?: ScriptFunction): FunctionExpression {
        return new FunctionExpression(global.generatedEs2panda._CreateFunctionExpression1(global.context, passNode(namedExpr), passNode(func)))
    }
    static updateFunctionExpression(original?: FunctionExpression, func?: ScriptFunction): FunctionExpression {
        return new FunctionExpression(global.generatedEs2panda._UpdateFunctionExpression(global.context, passNode(original), passNode(func)))
    }
    static update1FunctionExpression(original?: FunctionExpression, namedExpr?: Identifier, func?: ScriptFunction): FunctionExpression {
        return new FunctionExpression(global.generatedEs2panda._UpdateFunctionExpression1(global.context, passNode(original), passNode(namedExpr), passNode(func)))
    }
    get function(): ScriptFunction | undefined {
        return unpackNode(global.generatedEs2panda._FunctionExpressionFunction(global.context, this.peer))
    }
    get isAnonymous(): boolean {
        return global.generatedEs2panda._FunctionExpressionIsAnonymousConst(global.context, this.peer)
    }
    get id(): Identifier | undefined {
        return unpackNode(global.generatedEs2panda._FunctionExpressionId(global.context, this.peer))
    }
}
export function isFunctionExpression(node: object | undefined): node is FunctionExpression {
    return node instanceof FunctionExpression
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_FUNCTION_EXPRESSION)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_FUNCTION_EXPRESSION, (peer: KNativePointer) => new FunctionExpression(peer))
}