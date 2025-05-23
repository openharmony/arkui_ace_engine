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
import { Es2pandaTSSignatureDeclarationKind } from "./../Es2pandaEnums"
import { Expression } from "./Expression"
import { FunctionSignature } from "./FunctionSignature"
import { TSTypeParameterDeclaration } from "./TSTypeParameterDeclaration"
import { TypeNode } from "./TypeNode"
import { TypedAstNode } from "./TypedAstNode"
export class TSSignatureDeclaration extends TypedAstNode {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 107)
        super(pointer)
    }
    static createTSSignatureDeclaration(kind: Es2pandaTSSignatureDeclarationKind, signature?: FunctionSignature): TSSignatureDeclaration {
        return new TSSignatureDeclaration(global.generatedEs2panda._CreateTSSignatureDeclaration(global.context, kind, passNode(signature)))
    }
    static updateTSSignatureDeclaration(original: TSSignatureDeclaration | undefined, kind: Es2pandaTSSignatureDeclarationKind, signature?: FunctionSignature): TSSignatureDeclaration {
        return new TSSignatureDeclaration(global.generatedEs2panda._UpdateTSSignatureDeclaration(global.context, passNode(original), kind, passNode(signature)))
    }
    get typeParams(): TSTypeParameterDeclaration | undefined {
        return unpackNode(global.generatedEs2panda._TSSignatureDeclarationTypeParams(global.context, this.peer))
    }
    get params(): readonly Expression[] {
        return unpackNodeArray(global.generatedEs2panda._TSSignatureDeclarationParamsConst(global.context, this.peer))
    }
    get returnTypeAnnotation(): TypeNode | undefined {
        return unpackNode(global.generatedEs2panda._TSSignatureDeclarationReturnTypeAnnotation(global.context, this.peer))
    }
    get kind(): Es2pandaTSSignatureDeclarationKind {
        return global.generatedEs2panda._TSSignatureDeclarationKindConst(global.context, this.peer)
    }
}
export function isTSSignatureDeclaration(node: object | undefined): node is TSSignatureDeclaration {
    return node instanceof TSSignatureDeclaration
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_TS_SIGNATURE_DECLARATION)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_TS_SIGNATURE_DECLARATION, (peer: KNativePointer) => new TSSignatureDeclaration(peer))
}