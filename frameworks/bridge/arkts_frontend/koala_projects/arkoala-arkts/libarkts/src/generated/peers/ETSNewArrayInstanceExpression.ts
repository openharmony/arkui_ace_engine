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
import { TypeNode } from "./TypeNode"
export class ETSNewArrayInstanceExpression extends Expression {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 75)
        super(pointer)
        console.warn("Warning: stub node ETSNewArrayInstanceExpression")
    }
    static createETSNewArrayInstanceExpression(typeReference?: TypeNode, dimension?: Expression): ETSNewArrayInstanceExpression {
        return new ETSNewArrayInstanceExpression(global.generatedEs2panda._CreateETSNewArrayInstanceExpression(global.context, passNode(typeReference), passNode(dimension)))
    }
    static updateETSNewArrayInstanceExpression(original?: ETSNewArrayInstanceExpression, typeReference?: TypeNode, dimension?: Expression): ETSNewArrayInstanceExpression {
        return new ETSNewArrayInstanceExpression(global.generatedEs2panda._UpdateETSNewArrayInstanceExpression(global.context, passNode(original), passNode(typeReference), passNode(dimension)))
    }
    get typeReference(): TypeNode | undefined {
        return unpackNode(global.generatedEs2panda._ETSNewArrayInstanceExpressionTypeReferenceConst(global.context, this.peer))
    }
    get dimension(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._ETSNewArrayInstanceExpressionDimensionConst(global.context, this.peer))
    }
    /** @deprecated */
    setDimension(dimension: Expression): this {
        global.generatedEs2panda._ETSNewArrayInstanceExpressionSetDimension(global.context, this.peer, passNode(dimension))
        return this
    }
}
export function isETSNewArrayInstanceExpression(node: AstNode): node is ETSNewArrayInstanceExpression {
    return node instanceof ETSNewArrayInstanceExpression
}
if (!nodeByType.has(75)) {
    nodeByType.set(75, ETSNewArrayInstanceExpression)
}