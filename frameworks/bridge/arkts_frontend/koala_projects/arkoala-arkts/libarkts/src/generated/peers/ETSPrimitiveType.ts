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
import { Es2pandaPrimitiveType } from "./../Es2pandaEnums"
export class ETSPrimitiveType extends TypeNode {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 68)
        super(pointer)
        console.warn("Warning: stub node ETSPrimitiveType")
    }
    static createETSPrimitiveType(type: Es2pandaPrimitiveType): ETSPrimitiveType {
        return new ETSPrimitiveType(global.generatedEs2panda._CreateETSPrimitiveType(global.context, type))
    }
    static updateETSPrimitiveType(original: ETSPrimitiveType | undefined, type: Es2pandaPrimitiveType): ETSPrimitiveType {
        return new ETSPrimitiveType(global.generatedEs2panda._UpdateETSPrimitiveType(global.context, passNode(original), type))
    }
    get getPrimitiveType(): Es2pandaPrimitiveType {
        return global.generatedEs2panda._ETSPrimitiveTypeGetPrimitiveTypeConst(global.context, this.peer)
    }
}
export function isETSPrimitiveType(node: AstNode): node is ETSPrimitiveType {
    return node instanceof ETSPrimitiveType
}
if (!nodeByType.has(68)) {
    nodeByType.set(68, ETSPrimitiveType)
}