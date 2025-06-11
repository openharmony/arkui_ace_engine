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
import { ETSTypeReferencePart } from "./ETSTypeReferencePart"
import { Identifier } from "./Identifier"
export class ETSTypeReference extends TypeNode {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 71)
        super(pointer)
        console.warn("Warning: stub node ETSTypeReference")
    }
    static createETSTypeReference(part?: ETSTypeReferencePart): ETSTypeReference {
        return new ETSTypeReference(global.generatedEs2panda._CreateETSTypeReference(global.context, passNode(part)))
    }
    static updateETSTypeReference(original?: ETSTypeReference, part?: ETSTypeReferencePart): ETSTypeReference {
        return new ETSTypeReference(global.generatedEs2panda._UpdateETSTypeReference(global.context, passNode(original), passNode(part)))
    }
    get part(): ETSTypeReferencePart | undefined {
        return unpackNode(global.generatedEs2panda._ETSTypeReferencePartConst(global.context, this.peer))
    }
}
export function isETSTypeReference(node: AstNode): node is ETSTypeReference {
    return node instanceof ETSTypeReference
}
if (!nodeByType.has(71)) {
    nodeByType.set(71, ETSTypeReference)
}