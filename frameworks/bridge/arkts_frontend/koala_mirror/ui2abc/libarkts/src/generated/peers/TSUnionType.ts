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
export class TSUnionType extends TypeNode {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 103)
        super(pointer)
    }
    static createTSUnionType(types: readonly TypeNode[]): TSUnionType {
        return new TSUnionType(global.generatedEs2panda._CreateTSUnionType(global.context, passNodeArray(types), types.length))
    }
    static updateTSUnionType(original: TSUnionType | undefined, types: readonly TypeNode[]): TSUnionType {
        return new TSUnionType(global.generatedEs2panda._UpdateTSUnionType(global.context, passNode(original), passNodeArray(types), types.length))
    }
    get types(): readonly TypeNode[] {
        return unpackNodeArray(global.generatedEs2panda._TSUnionTypeTypesConst(global.context, this.peer))
    }
}
export function isTSUnionType(node: object | undefined): node is TSUnionType {
    return node instanceof TSUnionType
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_TS_UNION_TYPE)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_TS_UNION_TYPE, (peer: KNativePointer) => new TSUnionType(peer))
}