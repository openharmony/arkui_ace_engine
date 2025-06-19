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
import { Expression } from "./Expression"
export class TSParenthesizedType extends TypeNode {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 107)
        super(pointer)
        console.warn("Warning: stub node TSParenthesizedType")
    }
    static createTSParenthesizedType(type?: TypeNode): TSParenthesizedType {
        return new TSParenthesizedType(global.generatedEs2panda._CreateTSParenthesizedType(global.context, passNode(type)))
    }
    static updateTSParenthesizedType(original?: TSParenthesizedType, type?: TypeNode): TSParenthesizedType {
        return new TSParenthesizedType(global.generatedEs2panda._UpdateTSParenthesizedType(global.context, passNode(original), passNode(type)))
    }
    get type(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._TSParenthesizedTypeTypeConst(global.context, this.peer))
    }
}
export function isTSParenthesizedType(node: AstNode): node is TSParenthesizedType {
    return node instanceof TSParenthesizedType
}
if (!nodeByType.has(107)) {
    nodeByType.set(107, TSParenthesizedType)
}