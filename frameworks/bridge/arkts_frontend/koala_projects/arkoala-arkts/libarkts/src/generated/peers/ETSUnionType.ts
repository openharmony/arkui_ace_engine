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
export class ETSUnionType extends TypeNode {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 73)
        super(pointer)
        console.warn("Warning: stub node ETSUnionType")
    }
    static createETSUnionType(types: readonly TypeNode[]): ETSUnionType {
        return new ETSUnionType(global.generatedEs2panda._CreateETSUnionTypeIr(global.context, passNodeArray(types), types.length))
    }
    static updateETSUnionType(original: ETSUnionType | undefined, types: readonly TypeNode[]): ETSUnionType {
        return new ETSUnionType(global.generatedEs2panda._UpdateETSUnionTypeIr(global.context, passNode(original), passNodeArray(types), types.length))
    }
    get types(): readonly TypeNode[] {
        return unpackNodeArray(global.generatedEs2panda._ETSUnionTypeIrTypesConst(global.context, this.peer))
    }
}
export function isETSUnionType(node: AstNode): node is ETSUnionType {
    return node instanceof ETSUnionType
}
if (!nodeByType.has(73)) {
    nodeByType.set(73, ETSUnionType)
}