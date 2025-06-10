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
export class TSNamedTupleMember extends TypeNode {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 134)
        super(pointer)
        console.warn("Warning: stub node TSNamedTupleMember")
    }
    static createTSNamedTupleMember(label: Expression | undefined, elementType: TypeNode | undefined, optional_arg: boolean): TSNamedTupleMember {
        return new TSNamedTupleMember(global.generatedEs2panda._CreateTSNamedTupleMember(global.context, passNode(label), passNode(elementType), optional_arg))
    }
    static updateTSNamedTupleMember(original: TSNamedTupleMember | undefined, label: Expression | undefined, elementType: TypeNode | undefined, optional_arg: boolean): TSNamedTupleMember {
        return new TSNamedTupleMember(global.generatedEs2panda._UpdateTSNamedTupleMember(global.context, passNode(original), passNode(label), passNode(elementType), optional_arg))
    }
    get label(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._TSNamedTupleMemberLabelConst(global.context, this.peer))
    }
    get elementType(): TypeNode | undefined {
        return unpackNode(global.generatedEs2panda._TSNamedTupleMemberElementTypeConst(global.context, this.peer))
    }
    get isOptional(): boolean {
        return global.generatedEs2panda._TSNamedTupleMemberIsOptionalConst(global.context, this.peer)
    }
}
export function isTSNamedTupleMember(node: AstNode): node is TSNamedTupleMember {
    return node instanceof TSNamedTupleMember
}
if (!nodeByType.has(134)) {
    nodeByType.set(134, TSNamedTupleMember)
}