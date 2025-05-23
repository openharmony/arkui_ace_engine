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
export class ETSNewMultiDimArrayInstanceExpression extends Expression {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 77)
        super(pointer)
    }
    static createETSNewMultiDimArrayInstanceExpression(typeReference: TypeNode | undefined, dimensions: readonly Expression[]): ETSNewMultiDimArrayInstanceExpression {
        return new ETSNewMultiDimArrayInstanceExpression(global.generatedEs2panda._CreateETSNewMultiDimArrayInstanceExpression(global.context, passNode(typeReference), passNodeArray(dimensions), dimensions.length))
    }
    static updateETSNewMultiDimArrayInstanceExpression(original: ETSNewMultiDimArrayInstanceExpression | undefined, typeReference: TypeNode | undefined, dimensions: readonly Expression[]): ETSNewMultiDimArrayInstanceExpression {
        return new ETSNewMultiDimArrayInstanceExpression(global.generatedEs2panda._UpdateETSNewMultiDimArrayInstanceExpression(global.context, passNode(original), passNode(typeReference), passNodeArray(dimensions), dimensions.length))
    }
    static update1ETSNewMultiDimArrayInstanceExpression(original?: ETSNewMultiDimArrayInstanceExpression, other?: ETSNewMultiDimArrayInstanceExpression): ETSNewMultiDimArrayInstanceExpression {
        return new ETSNewMultiDimArrayInstanceExpression(global.generatedEs2panda._UpdateETSNewMultiDimArrayInstanceExpression1(global.context, passNode(original), passNode(other)))
    }
    get typeReference(): TypeNode | undefined {
        return unpackNode(global.generatedEs2panda._ETSNewMultiDimArrayInstanceExpressionTypeReference(global.context, this.peer))
    }
    get dimensions(): readonly Expression[] {
        return unpackNodeArray(global.generatedEs2panda._ETSNewMultiDimArrayInstanceExpressionDimensions(global.context, this.peer))
    }
    /** @deprecated */
    clearPreferredType(): this {
        global.generatedEs2panda._ETSNewMultiDimArrayInstanceExpressionClearPreferredType(global.context, this.peer)
        return this
    }
}
export function isETSNewMultiDimArrayInstanceExpression(node: object | undefined): node is ETSNewMultiDimArrayInstanceExpression {
    return node instanceof ETSNewMultiDimArrayInstanceExpression
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_ETS_NEW_MULTI_DIM_ARRAY_INSTANCE_EXPRESSION)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_ETS_NEW_MULTI_DIM_ARRAY_INSTANCE_EXPRESSION, (peer: KNativePointer) => new ETSNewMultiDimArrayInstanceExpression(peer))
}