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
import { Es2pandaTSIndexSignatureKind } from "./../Es2pandaEnums"
import { Expression } from "./Expression"
import { TypeNode } from "./TypeNode"
import { TypedAstNode } from "./TypedAstNode"
export class TSIndexSignature extends TypedAstNode {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 136)
        super(pointer)
    }
    static createTSIndexSignature(param: Expression | undefined, typeAnnotation: TypeNode | undefined, readonly_arg: boolean): TSIndexSignature {
        return new TSIndexSignature(global.generatedEs2panda._CreateTSIndexSignature(global.context, passNode(param), passNode(typeAnnotation), readonly_arg))
    }
    static updateTSIndexSignature(original: TSIndexSignature | undefined, param: Expression | undefined, typeAnnotation: TypeNode | undefined, readonly_arg: boolean): TSIndexSignature {
        return new TSIndexSignature(global.generatedEs2panda._UpdateTSIndexSignature(global.context, passNode(original), passNode(param), passNode(typeAnnotation), readonly_arg))
    }
    get param(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._TSIndexSignatureParamConst(global.context, this.peer))
    }
    get typeAnnotation(): TypeNode | undefined {
        return unpackNode(global.generatedEs2panda._TSIndexSignatureTypeAnnotationConst(global.context, this.peer))
    }
    get readonly(): boolean {
        return global.generatedEs2panda._TSIndexSignatureReadonlyConst(global.context, this.peer)
    }
    get kind(): Es2pandaTSIndexSignatureKind {
        return global.generatedEs2panda._TSIndexSignatureKindConst(global.context, this.peer)
    }
}
export function isTSIndexSignature(node: object | undefined): node is TSIndexSignature {
    return node instanceof TSIndexSignature
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_TS_INDEX_SIGNATURE)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_TS_INDEX_SIGNATURE, (peer: KNativePointer) => new TSIndexSignature(peer))
}