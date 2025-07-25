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

import { ETSTypeReference } from "./ETSTypeReference"
import { Es2pandaAstNodeType } from "./../Es2pandaEnums"
import { Es2pandaModifierFlags } from "./../Es2pandaEnums"
import { TypeNode } from "./TypeNode"
export class ETSWildcardType extends TypeNode {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 68)
        super(pointer)
    }
    static createETSWildcardType(typeReference: ETSTypeReference | undefined, flags: Es2pandaModifierFlags): ETSWildcardType {
        return new ETSWildcardType(global.generatedEs2panda._CreateETSWildcardType(global.context, passNode(typeReference), flags))
    }
    static updateETSWildcardType(original: ETSWildcardType | undefined, typeReference: ETSTypeReference | undefined, flags: Es2pandaModifierFlags): ETSWildcardType {
        return new ETSWildcardType(global.generatedEs2panda._UpdateETSWildcardType(global.context, passNode(original), passNode(typeReference), flags))
    }
    get typeReference(): ETSTypeReference | undefined {
        return unpackNode(global.generatedEs2panda._ETSWildcardTypeTypeReference(global.context, this.peer))
    }
}
export function isETSWildcardType(node: object | undefined): node is ETSWildcardType {
    return node instanceof ETSWildcardType
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_ETS_WILDCARD_TYPE)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_ETS_WILDCARD_TYPE, (peer: KNativePointer) => new ETSWildcardType(peer))
}