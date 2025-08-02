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

import { ClassDefinition } from "./ClassDefinition"
import { Decorator } from "./Decorator"
import { Es2pandaAstNodeType } from "./../Es2pandaEnums"
import { Statement } from "./Statement"
export class ClassDeclaration extends Statement {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 15)
        super(pointer)
    }
    static createClassDeclaration(def?: ClassDefinition): ClassDeclaration {
        return new ClassDeclaration(global.generatedEs2panda._CreateClassDeclaration(global.context, passNode(def)))
    }
    static updateClassDeclaration(original?: ClassDeclaration, def?: ClassDefinition): ClassDeclaration {
        return new ClassDeclaration(global.generatedEs2panda._UpdateClassDeclaration(global.context, passNode(original), passNode(def)))
    }
    get definition(): ClassDefinition | undefined {
        return unpackNode(global.generatedEs2panda._ClassDeclarationDefinition(global.context, this.peer))
    }
    get decorators(): readonly Decorator[] {
        return unpackNodeArray(global.generatedEs2panda._ClassDeclarationDecoratorsConst(global.context, this.peer))
    }
}
export function isClassDeclaration(node: object | undefined): node is ClassDeclaration {
    return node instanceof ClassDeclaration
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_CLASS_DECLARATION)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_CLASS_DECLARATION, (peer: KNativePointer) => new ClassDeclaration(peer))
}