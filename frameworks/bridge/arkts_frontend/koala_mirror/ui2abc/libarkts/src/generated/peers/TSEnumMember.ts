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
import { Statement } from "./Statement"
export class TSEnumMember extends Statement {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 88)
        super(pointer)
    }
    static create1TSEnumMember(key: Expression | undefined, init: Expression | undefined, isGenerated: boolean): TSEnumMember {
        return new TSEnumMember(global.generatedEs2panda._CreateTSEnumMember1(global.context, passNode(key), passNode(init), isGenerated))
    }
    static updateTSEnumMember(original?: TSEnumMember, key?: Expression, init?: Expression): TSEnumMember {
        return new TSEnumMember(global.generatedEs2panda._UpdateTSEnumMember(global.context, passNode(original), passNode(key), passNode(init)))
    }
    static update1TSEnumMember(original: TSEnumMember | undefined, key: Expression | undefined, init: Expression | undefined, isGenerated: boolean): TSEnumMember {
        return new TSEnumMember(global.generatedEs2panda._UpdateTSEnumMember1(global.context, passNode(original), passNode(key), passNode(init), isGenerated))
    }
    get key(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._TSEnumMemberKey(global.context, this.peer))
    }
    get init(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._TSEnumMemberInit(global.context, this.peer))
    }
    get isGenerated(): boolean {
        return global.generatedEs2panda._TSEnumMemberIsGeneratedConst(global.context, this.peer)
    }
    get name(): string {
        return unpackString(global.generatedEs2panda._TSEnumMemberNameConst(global.context, this.peer))
    }
}
export function isTSEnumMember(node: object | undefined): node is TSEnumMember {
    return node instanceof TSEnumMember
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_TS_ENUM_MEMBER)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_TS_ENUM_MEMBER, (peer: KNativePointer) => new TSEnumMember(peer))
}