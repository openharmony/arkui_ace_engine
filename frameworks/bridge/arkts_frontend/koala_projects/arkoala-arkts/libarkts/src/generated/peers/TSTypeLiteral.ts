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
export class TSTypeLiteral extends TypeNode {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 103)
        super(pointer)
        console.warn("Warning: stub node TSTypeLiteral")
    }
    static createTSTypeLiteral(members: readonly AstNode[]): TSTypeLiteral {
        return new TSTypeLiteral(global.generatedEs2panda._CreateTSTypeLiteral(global.context, passNodeArray(members), members.length))
    }
    static updateTSTypeLiteral(original: TSTypeLiteral | undefined, members: readonly AstNode[]): TSTypeLiteral {
        return new TSTypeLiteral(global.generatedEs2panda._UpdateTSTypeLiteral(global.context, passNode(original), passNodeArray(members), members.length))
    }
    get members(): readonly AstNode[] {
        return unpackNodeArray(global.generatedEs2panda._TSTypeLiteralMembersConst(global.context, this.peer))
    }
}
export function isTSTypeLiteral(node: AstNode): node is TSTypeLiteral {
    return node instanceof TSTypeLiteral
}
if (!nodeByType.has(103)) {
    nodeByType.set(103, TSTypeLiteral)
}