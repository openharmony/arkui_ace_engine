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
export class ETSTuple extends TypeNode {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 81)
        super(pointer)
    }
    static createETSTuple(): ETSTuple {
        return new ETSTuple(global.generatedEs2panda._CreateETSTuple(global.context))
    }
    static updateETSTuple(original?: ETSTuple): ETSTuple {
        return new ETSTuple(global.generatedEs2panda._UpdateETSTuple(global.context, passNode(original)))
    }
    static create1ETSTuple(size: number): ETSTuple {
        return new ETSTuple(global.generatedEs2panda._CreateETSTuple1(global.context, size))
    }
    static update1ETSTuple(original: ETSTuple | undefined, size: number): ETSTuple {
        return new ETSTuple(global.generatedEs2panda._UpdateETSTuple1(global.context, passNode(original), size))
    }
    static create2ETSTuple(typeList: readonly TypeNode[]): ETSTuple {
        return new ETSTuple(global.generatedEs2panda._CreateETSTuple2(global.context, passNodeArray(typeList), typeList.length))
    }
    static update2ETSTuple(original: ETSTuple | undefined, typeList: readonly TypeNode[]): ETSTuple {
        return new ETSTuple(global.generatedEs2panda._UpdateETSTuple2(global.context, passNode(original), passNodeArray(typeList), typeList.length))
    }
    get tupleSize(): number {
        return global.generatedEs2panda._ETSTupleGetTupleSizeConst(global.context, this.peer)
    }
    get tupleTypeAnnotationsList(): readonly TypeNode[] {
        return unpackNodeArray(global.generatedEs2panda._ETSTupleGetTupleTypeAnnotationsList(global.context, this.peer))
    }
    /** @deprecated */
    setTypeAnnotationsList(typeNodeList: readonly TypeNode[]): this {
        global.generatedEs2panda._ETSTupleSetTypeAnnotationsList(global.context, this.peer, passNodeArray(typeNodeList), typeNodeList.length)
        return this
    }
}
export function isETSTuple(node: object | undefined): node is ETSTuple {
    return node instanceof ETSTuple
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_ETS_TUPLE)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_ETS_TUPLE, (peer: KNativePointer) => new ETSTuple(peer))
}