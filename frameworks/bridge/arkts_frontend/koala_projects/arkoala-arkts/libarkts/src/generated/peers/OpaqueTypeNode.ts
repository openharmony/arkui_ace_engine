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
export class OpaqueTypeNode extends TypeNode {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 153)
        super(pointer)
        console.warn("Warning: stub node OpaqueTypeNode")
    }
    static create1OpaqueTypeNode(): OpaqueTypeNode {
        return new OpaqueTypeNode(global.generatedEs2panda._CreateOpaqueTypeNode1(global.context))
    }
    static update1OpaqueTypeNode(original?: OpaqueTypeNode): OpaqueTypeNode {
        return new OpaqueTypeNode(global.generatedEs2panda._UpdateOpaqueTypeNode1(global.context, passNode(original)))
    }
}
export function isOpaqueTypeNode(node: AstNode): node is OpaqueTypeNode {
    return node instanceof OpaqueTypeNode
}
if (!nodeByType.has(153)) {
    nodeByType.set(153, OpaqueTypeNode)
}