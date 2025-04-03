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

import { TypedAstNode } from "./TypedAstNode"
import { Es2pandaTSSignatureDeclarationKind } from "./../Es2pandaEnums"
import { FunctionSignature } from "./FunctionSignature"
import { TSTypeParameterDeclaration } from "./TSTypeParameterDeclaration"
import { Expression } from "./Expression"
import { TypeNode } from "./TypeNode"
export class TSSignatureDeclaration extends TypedAstNode {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 106)
        super(pointer)
        console.warn("Warning: stub node TSSignatureDeclaration")
    }
    static createTSSignatureDeclaration(kind: Es2pandaTSSignatureDeclarationKind, signature?: FunctionSignature): TSSignatureDeclaration {
        return new TSSignatureDeclaration(global.generatedEs2panda._CreateTSSignatureDeclaration(global.context, kind, passNode(signature)))
    }
    static updateTSSignatureDeclaration(original: TSSignatureDeclaration | undefined, kind: Es2pandaTSSignatureDeclarationKind, signature?: FunctionSignature): TSSignatureDeclaration {
        return new TSSignatureDeclaration(global.generatedEs2panda._UpdateTSSignatureDeclaration(global.context, passNode(original), kind, passNode(signature)))
    }
    get typeParams(): TSTypeParameterDeclaration | undefined {
        return unpackNode(global.generatedEs2panda._TSSignatureDeclarationTypeParamsConst(global.context, this.peer))
    }
    get params(): readonly Expression[] {
        return unpackNodeArray(global.generatedEs2panda._TSSignatureDeclarationParamsConst(global.context, this.peer))
    }
    get returnTypeAnnotation(): TypeNode | undefined {
        return unpackNode(global.generatedEs2panda._TSSignatureDeclarationReturnTypeAnnotationConst(global.context, this.peer))
    }
    get kind(): Es2pandaTSSignatureDeclarationKind {
        return global.generatedEs2panda._TSSignatureDeclarationKindConst(global.context, this.peer)
    }
}
export function isTSSignatureDeclaration(node: AstNode): node is TSSignatureDeclaration {
    return node instanceof TSSignatureDeclaration
}
if (!nodeByType.has(106)) {
    nodeByType.set(106, TSSignatureDeclaration)
}