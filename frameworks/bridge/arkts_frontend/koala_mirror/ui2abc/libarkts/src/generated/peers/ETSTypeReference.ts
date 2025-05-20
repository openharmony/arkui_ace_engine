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

import { ETSTypeReferencePart } from "./ETSTypeReferencePart"
import { Es2pandaAstNodeType } from "./../Es2pandaEnums"
import { Identifier } from "./Identifier"
import { TypeNode } from "./TypeNode"
export class ETSTypeReference extends TypeNode {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 72)
        super(pointer)
    }
    static createETSTypeReference(part?: ETSTypeReferencePart): ETSTypeReference {
        return new ETSTypeReference(global.generatedEs2panda._CreateETSTypeReference(global.context, passNode(part)))
    }
    static updateETSTypeReference(original?: ETSTypeReference, part?: ETSTypeReferencePart): ETSTypeReference {
        return new ETSTypeReference(global.generatedEs2panda._UpdateETSTypeReference(global.context, passNode(original), passNode(part)))
    }
    get part(): ETSTypeReferencePart | undefined {
        return unpackNode(global.generatedEs2panda._ETSTypeReferencePart(global.context, this.peer))
    }
    get baseName(): Identifier | undefined {
        return unpackNode(global.generatedEs2panda._ETSTypeReferenceBaseNameConst(global.context, this.peer))
    }
}
export function isETSTypeReference(node: object | undefined): node is ETSTypeReference {
    return node instanceof ETSTypeReference
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_ETS_TYPE_REFERENCE)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_ETS_TYPE_REFERENCE, (peer: KNativePointer) => new ETSTypeReference(peer))
}