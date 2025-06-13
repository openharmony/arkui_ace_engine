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
import { Es2pandaScriptFunctionFlags } from "./../Es2pandaEnums"
import { TSTypeParameterDeclaration } from "./TSTypeParameterDeclaration"
import { Expression } from "./Expression"
import { TSInterfaceDeclaration } from "./TSInterfaceDeclaration"
export class ETSFunctionType extends TypeNode {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 66)
        super(pointer)
        console.warn("Warning: stub node ETSFunctionType")
    }
    static createETSFunctionType(signature: FunctionSignature | undefined, funcFlags: Es2pandaScriptFunctionFlags): ETSFunctionType {
        return new ETSFunctionType(global.generatedEs2panda._CreateETSFunctionTypeIr(global.context, passNode(signature), funcFlags))
    }
    static updateETSFunctionType(original: ETSFunctionType | undefined, signature: FunctionSignature | undefined, funcFlags: Es2pandaScriptFunctionFlags): ETSFunctionType {
        return new ETSFunctionType(global.generatedEs2panda._UpdateETSFunctionTypeIr(global.context, passNode(original), passNode(signature), funcFlags))
    }
    get typeParams(): TSTypeParameterDeclaration | undefined {
        return unpackNode(global.generatedEs2panda._ETSFunctionTypeIrTypeParamsConst(global.context, this.peer))
    }
    get params(): readonly Expression[] {
        return unpackNodeArray(global.generatedEs2panda._ETSFunctionTypeIrParamsConst(global.context, this.peer))
    }
    get returnType(): TypeNode | undefined {
        return unpackNode(global.generatedEs2panda._ETSFunctionTypeIrReturnTypeConst(global.context, this.peer))
    }
    get functionalInterface(): TSInterfaceDeclaration | undefined {
        return unpackNode(global.generatedEs2panda._ETSFunctionTypeIrFunctionalInterfaceConst(global.context, this.peer))
    }
    /** @deprecated */
    setFunctionalInterface(functionalInterface: TSInterfaceDeclaration): this {
        global.generatedEs2panda._ETSFunctionTypeIrSetFunctionalInterface(global.context, this.peer, passNode(functionalInterface))
        return this
    }
    get flags(): Es2pandaScriptFunctionFlags {
        return global.generatedEs2panda._ETSFunctionTypeIrFlags(global.context, this.peer)
    }
    get isThrowing(): boolean {
        return global.generatedEs2panda._ETSFunctionTypeIrIsThrowingConst(global.context, this.peer)
    }
    get isRethrowing(): boolean {
        return global.generatedEs2panda._ETSFunctionTypeIrIsRethrowingConst(global.context, this.peer)
    }
    get isExtensionFunction(): boolean {
        return global.generatedEs2panda._ETSFunctionTypeIrIsExtensionFunctionConst(global.context, this.peer)
    }
}
export function isETSFunctionType(node: AstNode): node is ETSFunctionType {
    return node instanceof ETSFunctionType
}
if (!nodeByType.has(66)) {
    nodeByType.set(66, ETSFunctionType)
}