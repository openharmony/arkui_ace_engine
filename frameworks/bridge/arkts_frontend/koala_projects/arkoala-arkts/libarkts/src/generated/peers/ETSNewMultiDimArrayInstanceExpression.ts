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
export class ETSNewMultiDimArrayInstanceExpression extends Expression {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 76)
        super(pointer)
        console.warn("Warning: stub node ETSNewMultiDimArrayInstanceExpression")
    }
    static createETSNewMultiDimArrayInstanceExpression(typeReference: TypeNode | undefined, dimensions: readonly Expression[]): ETSNewMultiDimArrayInstanceExpression {
        return new ETSNewMultiDimArrayInstanceExpression(global.generatedEs2panda._CreateETSNewMultiDimArrayInstanceExpression(global.context, passNode(typeReference), passNodeArray(dimensions), dimensions.length))
    }
    static updateETSNewMultiDimArrayInstanceExpression(original: ETSNewMultiDimArrayInstanceExpression | undefined, typeReference: TypeNode | undefined, dimensions: readonly Expression[]): ETSNewMultiDimArrayInstanceExpression {
        return new ETSNewMultiDimArrayInstanceExpression(global.generatedEs2panda._UpdateETSNewMultiDimArrayInstanceExpression(global.context, passNode(original), passNode(typeReference), passNodeArray(dimensions), dimensions.length))
    }
    static create1ETSNewMultiDimArrayInstanceExpression(other?: ETSNewMultiDimArrayInstanceExpression): ETSNewMultiDimArrayInstanceExpression {
        return new ETSNewMultiDimArrayInstanceExpression(global.generatedEs2panda._CreateETSNewMultiDimArrayInstanceExpression1(global.context, passNode(other)))
    }
    static update1ETSNewMultiDimArrayInstanceExpression(original?: ETSNewMultiDimArrayInstanceExpression, other?: ETSNewMultiDimArrayInstanceExpression): ETSNewMultiDimArrayInstanceExpression {
        return new ETSNewMultiDimArrayInstanceExpression(global.generatedEs2panda._UpdateETSNewMultiDimArrayInstanceExpression1(global.context, passNode(original), passNode(other)))
    }
    get typeReference(): TypeNode | undefined {
        return unpackNode(global.generatedEs2panda._ETSNewMultiDimArrayInstanceExpressionTypeReferenceConst(global.context, this.peer))
    }
    get dimensions(): readonly Expression[] {
        return unpackNodeArray(global.generatedEs2panda._ETSNewMultiDimArrayInstanceExpressionDimensionsConst(global.context, this.peer))
    }
}
export function isETSNewMultiDimArrayInstanceExpression(node: AstNode): node is ETSNewMultiDimArrayInstanceExpression {
    return node instanceof ETSNewMultiDimArrayInstanceExpression
}
if (!nodeByType.has(76)) {
    nodeByType.set(76, ETSNewMultiDimArrayInstanceExpression)
}