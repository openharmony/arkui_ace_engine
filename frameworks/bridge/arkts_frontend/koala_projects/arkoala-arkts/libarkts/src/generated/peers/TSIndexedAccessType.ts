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
export class TSIndexedAccessType extends TypeNode {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 129)
        super(pointer)
        console.warn("Warning: stub node TSIndexedAccessType")
    }
    static createTSIndexedAccessType(objectType?: TypeNode, indexType?: TypeNode): TSIndexedAccessType {
        return new TSIndexedAccessType(global.generatedEs2panda._CreateTSIndexedAccessType(global.context, passNode(objectType), passNode(indexType)))
    }
    static updateTSIndexedAccessType(original?: TSIndexedAccessType, objectType?: TypeNode, indexType?: TypeNode): TSIndexedAccessType {
        return new TSIndexedAccessType(global.generatedEs2panda._UpdateTSIndexedAccessType(global.context, passNode(original), passNode(objectType), passNode(indexType)))
    }
    get objectType(): TypeNode | undefined {
        return unpackNode(global.generatedEs2panda._TSIndexedAccessTypeObjectTypeConst(global.context, this.peer))
    }
    get indexType(): TypeNode | undefined {
        return unpackNode(global.generatedEs2panda._TSIndexedAccessTypeIndexTypeConst(global.context, this.peer))
    }
}
export function isTSIndexedAccessType(node: AstNode): node is TSIndexedAccessType {
    return node instanceof TSIndexedAccessType
}
if (!nodeByType.has(129)) {
    nodeByType.set(129, TSIndexedAccessType)
}