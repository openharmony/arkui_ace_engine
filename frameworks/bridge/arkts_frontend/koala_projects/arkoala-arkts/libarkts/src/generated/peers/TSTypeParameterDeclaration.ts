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
import { TSTypeParameter } from "./TSTypeParameter"
export class TSTypeParameterDeclaration extends Expression {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 118)
        super(pointer)
        console.warn("Warning: stub node TSTypeParameterDeclaration")
    }
    static createTSTypeParameterDeclaration(params: readonly TSTypeParameter[], requiredParams: number): TSTypeParameterDeclaration {
        return new TSTypeParameterDeclaration(global.generatedEs2panda._CreateTSTypeParameterDeclaration(global.context, passNodeArray(params), params.length, requiredParams))
    }
    static updateTSTypeParameterDeclaration(original: TSTypeParameterDeclaration | undefined, params: readonly TSTypeParameter[], requiredParams: number): TSTypeParameterDeclaration {
        return new TSTypeParameterDeclaration(global.generatedEs2panda._UpdateTSTypeParameterDeclaration(global.context, passNode(original), passNodeArray(params), params.length, requiredParams))
    }
    get params(): readonly TSTypeParameter[] {
        return unpackNodeArray(global.generatedEs2panda._TSTypeParameterDeclarationParamsConst(global.context, this.peer))
    }
    /** @deprecated */
    addParam(param: TSTypeParameter): this {
        global.generatedEs2panda._TSTypeParameterDeclarationAddParam(global.context, this.peer, passNode(param))
        return this
    }
    get requiredParams(): number {
        return global.generatedEs2panda._TSTypeParameterDeclarationRequiredParamsConst(global.context, this.peer)
    }
}
export function isTSTypeParameterDeclaration(node: AstNode): node is TSTypeParameterDeclaration {
    return node instanceof TSTypeParameterDeclaration
}
if (!nodeByType.has(118)) {
    nodeByType.set(118, TSTypeParameterDeclaration)
}