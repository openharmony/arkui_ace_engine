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

import { AnnotatedExpression } from "./AnnotatedExpression"
import { Es2pandaAstNodeType } from "./../Es2pandaEnums"
import { Expression } from "./Expression"
import { TypeNode } from "./TypeNode"
export class TSTypeAssertion extends AnnotatedExpression {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 140)
        super(pointer)
    }
    static createTSTypeAssertion(typeAnnotation?: TypeNode, expression?: Expression): TSTypeAssertion {
        return new TSTypeAssertion(global.generatedEs2panda._CreateTSTypeAssertion(global.context, passNode(typeAnnotation), passNode(expression)))
    }
    static updateTSTypeAssertion(original?: TSTypeAssertion, typeAnnotation?: TypeNode, expression?: Expression): TSTypeAssertion {
        return new TSTypeAssertion(global.generatedEs2panda._UpdateTSTypeAssertion(global.context, passNode(original), passNode(typeAnnotation), passNode(expression)))
    }
    get expression(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._TSTypeAssertionGetExpressionConst(global.context, this.peer))
    }
    get typeAnnotation(): TypeNode | undefined {
        return unpackNode(global.generatedEs2panda._TSTypeAssertionTypeAnnotationConst(global.context, this.peer))
    }
    /** @deprecated */
    setTsTypeAnnotation(typeAnnotation?: TypeNode): this {
        global.generatedEs2panda._TSTypeAssertionSetTsTypeAnnotation(global.context, this.peer, passNode(typeAnnotation))
        return this
    }
}
export function isTSTypeAssertion(node: object | undefined): node is TSTypeAssertion {
    return node instanceof TSTypeAssertion
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_TS_TYPE_ASSERTION)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_TS_TYPE_ASSERTION, (peer: KNativePointer) => new TSTypeAssertion(peer))
}