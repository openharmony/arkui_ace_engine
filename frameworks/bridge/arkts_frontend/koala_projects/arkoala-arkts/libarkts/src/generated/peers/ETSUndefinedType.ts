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
export class ETSUndefinedType extends TypeNode {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 63)
        super(pointer)
        console.warn("Warning: stub node ETSUndefinedType")
    }
    static createETSUndefinedType(): ETSUndefinedType {
        return new ETSUndefinedType(global.generatedEs2panda._CreateETSUndefinedTypeIr(global.context))
    }
    static updateETSUndefinedType(original?: ETSUndefinedType): ETSUndefinedType {
        return new ETSUndefinedType(global.generatedEs2panda._UpdateETSUndefinedTypeIr(global.context, passNode(original)))
    }
}
export function isETSUndefinedType(node: AstNode): node is ETSUndefinedType {
    return node instanceof ETSUndefinedType
}
if (!nodeByType.has(63)) {
    nodeByType.set(63, ETSUndefinedType)
}