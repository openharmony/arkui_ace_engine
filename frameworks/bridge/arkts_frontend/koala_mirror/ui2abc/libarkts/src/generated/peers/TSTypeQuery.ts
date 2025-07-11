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
export class TSTypeQuery extends TypeNode {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 137)
        super(pointer)
    }
    static createTSTypeQuery(exprName?: Expression): TSTypeQuery {
        return new TSTypeQuery(global.generatedEs2panda._CreateTSTypeQuery(global.context, passNode(exprName)))
    }
    static updateTSTypeQuery(original?: TSTypeQuery, exprName?: Expression): TSTypeQuery {
        return new TSTypeQuery(global.generatedEs2panda._UpdateTSTypeQuery(global.context, passNode(original), passNode(exprName)))
    }
    get exprName(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._TSTypeQueryExprNameConst(global.context, this.peer))
    }
}
export function isTSTypeQuery(node: object | undefined): node is TSTypeQuery {
    return node instanceof TSTypeQuery
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_TS_TYPE_QUERY)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_TS_TYPE_QUERY, (peer: KNativePointer) => new TSTypeQuery(peer))
}