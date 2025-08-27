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

import { TypeNode } from "./TypeNode"
import { Expression } from "./Expression"
export class TSTypePredicate extends TypeNode {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 120)
        super(pointer)
        console.warn("Warning: stub node TSTypePredicate")
    }
    static createTSTypePredicate(parameterName: Expression | undefined, typeAnnotation: TypeNode | undefined, asserts: boolean): TSTypePredicate {
        return new TSTypePredicate(global.generatedEs2panda._CreateTSTypePredicate(global.context, passNode(parameterName), passNode(typeAnnotation), asserts))
    }
    static updateTSTypePredicate(original: TSTypePredicate | undefined, parameterName: Expression | undefined, typeAnnotation: TypeNode | undefined, asserts: boolean): TSTypePredicate {
        return new TSTypePredicate(global.generatedEs2panda._UpdateTSTypePredicate(global.context, passNode(original), passNode(parameterName), passNode(typeAnnotation), asserts))
    }
    get parameterName(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._TSTypePredicateParameterNameConst(global.context, this.peer))
    }
    get typeAnnotation(): TypeNode | undefined {
        return unpackNode(global.generatedEs2panda._TSTypePredicateTypeAnnotationConst(global.context, this.peer))
    }
    get asserts(): boolean {
        return global.generatedEs2panda._TSTypePredicateAssertsConst(global.context, this.peer)
    }
}
export function isTSTypePredicate(node: AstNode): node is TSTypePredicate {
    return node instanceof TSTypePredicate
}
if (!nodeByType.has(120)) {
    nodeByType.set(120, TSTypePredicate)
}