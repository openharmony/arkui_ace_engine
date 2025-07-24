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
import { TypeNode } from "./TypeNode"
export class TSThisType extends TypeNode {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 116)
        super(pointer)
    }
    static createTSThisType(): TSThisType {
        return new TSThisType(global.generatedEs2panda._CreateTSThisType(global.context))
    }
    static updateTSThisType(original?: TSThisType): TSThisType {
        return new TSThisType(global.generatedEs2panda._UpdateTSThisType(global.context, passNode(original)))
    }
}
export function isTSThisType(node: object | undefined): node is TSThisType {
    return node instanceof TSThisType
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_TS_THIS_TYPE)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_TS_THIS_TYPE, (peer: KNativePointer) => new TSThisType(peer))
}