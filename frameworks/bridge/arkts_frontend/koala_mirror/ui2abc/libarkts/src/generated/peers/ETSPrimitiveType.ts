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
import { Es2pandaPrimitiveType } from "./../Es2pandaEnums"
import { TypeNode } from "./TypeNode"
export class ETSPrimitiveType extends TypeNode {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 69)
        super(pointer)
    }
    static createETSPrimitiveType(type: Es2pandaPrimitiveType): ETSPrimitiveType {
        return new ETSPrimitiveType(global.generatedEs2panda._CreateETSPrimitiveType(global.context, type))
    }
    static updateETSPrimitiveType(original: ETSPrimitiveType | undefined, type: Es2pandaPrimitiveType): ETSPrimitiveType {
        return new ETSPrimitiveType(global.generatedEs2panda._UpdateETSPrimitiveType(global.context, passNode(original), type))
    }
    get primitiveType(): Es2pandaPrimitiveType {
        return global.generatedEs2panda._ETSPrimitiveTypeGetPrimitiveTypeConst(global.context, this.peer)
    }
}
export function isETSPrimitiveType(node: object | undefined): node is ETSPrimitiveType {
    return node instanceof ETSPrimitiveType
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_ETS_PRIMITIVE_TYPE)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_ETS_PRIMITIVE_TYPE, (peer: KNativePointer) => new ETSPrimitiveType(peer))
}