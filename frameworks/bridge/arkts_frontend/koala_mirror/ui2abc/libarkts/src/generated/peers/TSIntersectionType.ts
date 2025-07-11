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
import { Expression } from "./Expression"
import { TypeNode } from "./TypeNode"
export class TSIntersectionType extends TypeNode {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 113)
        super(pointer)
    }
    static createTSIntersectionType(types: readonly Expression[]): TSIntersectionType {
        return new TSIntersectionType(global.generatedEs2panda._CreateTSIntersectionType(global.context, passNodeArray(types), types.length))
    }
    static updateTSIntersectionType(original: TSIntersectionType | undefined, types: readonly Expression[]): TSIntersectionType {
        return new TSIntersectionType(global.generatedEs2panda._UpdateTSIntersectionType(global.context, passNode(original), passNodeArray(types), types.length))
    }
    get types(): readonly Expression[] {
        return unpackNodeArray(global.generatedEs2panda._TSIntersectionTypeTypesConst(global.context, this.peer))
    }
}
export function isTSIntersectionType(node: object | undefined): node is TSIntersectionType {
    return node instanceof TSIntersectionType
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_TS_INTERSECTION_TYPE)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_TS_INTERSECTION_TYPE, (peer: KNativePointer) => new TSIntersectionType(peer))
}