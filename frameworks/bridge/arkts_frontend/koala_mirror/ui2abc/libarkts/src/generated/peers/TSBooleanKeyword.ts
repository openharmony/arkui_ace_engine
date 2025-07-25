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
export class TSBooleanKeyword extends TypeNode {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 93)
        super(pointer)
    }
    static createTSBooleanKeyword(): TSBooleanKeyword {
        return new TSBooleanKeyword(global.generatedEs2panda._CreateTSBooleanKeyword(global.context))
    }
    static updateTSBooleanKeyword(original?: TSBooleanKeyword): TSBooleanKeyword {
        return new TSBooleanKeyword(global.generatedEs2panda._UpdateTSBooleanKeyword(global.context, passNode(original)))
    }
}
export function isTSBooleanKeyword(node: object | undefined): node is TSBooleanKeyword {
    return node instanceof TSBooleanKeyword
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_TS_BOOLEAN_KEYWORD)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_TS_BOOLEAN_KEYWORD, (peer: KNativePointer) => new TSBooleanKeyword(peer))
}