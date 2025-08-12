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
export class TSArrayType extends TypeNode {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 102)
        super(pointer)
    }
    static createTSArrayType(elementType?: TypeNode): TSArrayType {
        return new TSArrayType(global.generatedEs2panda._CreateTSArrayType(global.context, passNode(elementType)))
    }
    static updateTSArrayType(original?: TSArrayType, elementType?: TypeNode): TSArrayType {
        return new TSArrayType(global.generatedEs2panda._UpdateTSArrayType(global.context, passNode(original), passNode(elementType)))
    }
    get elementType(): TypeNode | undefined {
        return unpackNode(global.generatedEs2panda._TSArrayTypeElementTypeConst(global.context, this.peer))
    }
}
export function isTSArrayType(node: object | undefined): node is TSArrayType {
    return node instanceof TSArrayType
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_TS_ARRAY_TYPE)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_TS_ARRAY_TYPE, (peer: KNativePointer) => new TSArrayType(peer))
}