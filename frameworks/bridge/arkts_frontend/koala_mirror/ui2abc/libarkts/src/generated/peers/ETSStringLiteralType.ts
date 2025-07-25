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
export class ETSStringLiteralType extends TypeNode {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 66)
        super(pointer)
    }
    static createETSStringLiteralType(value: string): ETSStringLiteralType {
        return new ETSStringLiteralType(global.generatedEs2panda._CreateETSStringLiteralType(global.context, value))
    }
    static updateETSStringLiteralType(original: ETSStringLiteralType | undefined, value: string): ETSStringLiteralType {
        return new ETSStringLiteralType(global.generatedEs2panda._UpdateETSStringLiteralType(global.context, passNode(original), value))
    }
}
export function isETSStringLiteralType(node: object | undefined): node is ETSStringLiteralType {
    return node instanceof ETSStringLiteralType
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_ETS_STRING_LITERAL_TYPE)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_ETS_STRING_LITERAL_TYPE, (peer: KNativePointer) => new ETSStringLiteralType(peer))
}