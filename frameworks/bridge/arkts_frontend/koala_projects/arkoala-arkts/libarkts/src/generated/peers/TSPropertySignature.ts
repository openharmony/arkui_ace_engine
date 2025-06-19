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

import { AnnotatedAstNode } from "./AnnotatedAstNode"
import { Expression } from "./Expression"
import { TypeNode } from "./TypeNode"
export class TSPropertySignature extends AnnotatedAstNode {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 104)
        super(pointer)
        console.warn("Warning: stub node TSPropertySignature")
    }
    static createTSPropertySignature(key: Expression | undefined, typeAnnotation: TypeNode | undefined, computed: boolean, optional_arg: boolean, readonly_arg: boolean): TSPropertySignature {
        return new TSPropertySignature(global.generatedEs2panda._CreateTSPropertySignature(global.context, passNode(key), passNode(typeAnnotation), computed, optional_arg, readonly_arg))
    }
    static updateTSPropertySignature(original: TSPropertySignature | undefined, key: Expression | undefined, typeAnnotation: TypeNode | undefined, computed: boolean, optional_arg: boolean, readonly_arg: boolean): TSPropertySignature {
        return new TSPropertySignature(global.generatedEs2panda._UpdateTSPropertySignature(global.context, passNode(original), passNode(key), passNode(typeAnnotation), computed, optional_arg, readonly_arg))
    }
    get key(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._TSPropertySignatureKeyConst(global.context, this.peer))
    }
    get computed(): boolean {
        return global.generatedEs2panda._TSPropertySignatureComputedConst(global.context, this.peer)
    }
    get optional(): boolean {
        return global.generatedEs2panda._TSPropertySignatureOptionalConst(global.context, this.peer)
    }
    get readonly(): boolean {
        return global.generatedEs2panda._TSPropertySignatureReadonlyConst(global.context, this.peer)
    }
    get typeAnnotation(): TypeNode | undefined {
        return unpackNode(global.generatedEs2panda._TSPropertySignatureTypeAnnotationConst(global.context, this.peer))
    }
    /** @deprecated */
    setTsTypeAnnotation(typeAnnotation: TypeNode): this {
        global.generatedEs2panda._TSPropertySignatureSetTsTypeAnnotation(global.context, this.peer, passNode(typeAnnotation))
        return this
    }
}
export function isTSPropertySignature(node: AstNode): node is TSPropertySignature {
    return node instanceof TSPropertySignature
}
if (!nodeByType.has(104)) {
    nodeByType.set(104, TSPropertySignature)
}