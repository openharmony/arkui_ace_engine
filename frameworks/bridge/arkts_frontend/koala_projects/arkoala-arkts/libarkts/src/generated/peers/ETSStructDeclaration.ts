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

import { ClassDeclaration } from "./ClassDeclaration"
import { ClassDefinition } from "./ClassDefinition"
export class ETSStructDeclaration extends ClassDeclaration {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 83)
        super(pointer)
        console.warn("Warning: stub node ETSStructDeclaration")
    }
    static createETSStructDeclaration(def?: ClassDefinition): ETSStructDeclaration {
        return new ETSStructDeclaration(global.generatedEs2panda._CreateETSStructDeclaration(global.context, passNode(def)))
    }
    static updateETSStructDeclaration(original?: ETSStructDeclaration, def?: ClassDefinition): ETSStructDeclaration {
        return new ETSStructDeclaration(global.generatedEs2panda._UpdateETSStructDeclaration(global.context, passNode(original), passNode(def)))
    }
}
export function isETSStructDeclaration(node: AstNode): node is ETSStructDeclaration {
    return node instanceof ETSStructDeclaration
}
if (!nodeByType.has(83)) {
    nodeByType.set(83, ETSStructDeclaration)
}