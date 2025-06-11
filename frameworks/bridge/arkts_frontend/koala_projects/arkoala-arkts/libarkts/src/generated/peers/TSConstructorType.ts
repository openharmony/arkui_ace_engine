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
import { FunctionSignature } from "./FunctionSignature"
import { TSTypeParameterDeclaration } from "./TSTypeParameterDeclaration"
import { Expression } from "./Expression"
export class TSConstructorType extends TypeNode {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 125)
        super(pointer)
        console.warn("Warning: stub node TSConstructorType")
    }
    static createTSConstructorType(signature: FunctionSignature | undefined, abstract: boolean): TSConstructorType {
        return new TSConstructorType(global.generatedEs2panda._CreateTSConstructorType(global.context, passNode(signature), abstract))
    }
    static updateTSConstructorType(original: TSConstructorType | undefined, signature: FunctionSignature | undefined, abstract: boolean): TSConstructorType {
        return new TSConstructorType(global.generatedEs2panda._UpdateTSConstructorType(global.context, passNode(original), passNode(signature), abstract))
    }
    get typeParams(): TSTypeParameterDeclaration | undefined {
        return unpackNode(global.generatedEs2panda._TSConstructorTypeTypeParamsConst(global.context, this.peer))
    }
    get params(): readonly Expression[] {
        return unpackNodeArray(global.generatedEs2panda._TSConstructorTypeParamsConst(global.context, this.peer))
    }
    get returnType(): TypeNode | undefined {
        return unpackNode(global.generatedEs2panda._TSConstructorTypeReturnTypeConst(global.context, this.peer))
    }
    get abstract(): boolean {
        return global.generatedEs2panda._TSConstructorTypeAbstractConst(global.context, this.peer)
    }
}
export function isTSConstructorType(node: AstNode): node is TSConstructorType {
    return node instanceof TSConstructorType
}
if (!nodeByType.has(125)) {
    nodeByType.set(125, TSConstructorType)
}