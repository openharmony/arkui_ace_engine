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
export class TSUnionType extends TypeNode {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 102)
        super(pointer)
        console.warn("Warning: stub node TSUnionType")
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
export function isTSUnionType(node: AstNode): node is TSUnionType {
    return node instanceof TSUnionType
}
if (!nodeByType.has(102)) {
    nodeByType.set(102, TSUnionType)
}