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

import { AnnotationUsage } from "./AnnotationUsage"
import { Decorator } from "./Decorator"
import { Es2pandaAstNodeType } from "./../Es2pandaEnums"
import { Es2pandaVariableDeclarationKind } from "./../Es2pandaEnums"
import { Statement } from "./Statement"
import { VariableDeclarator } from "./VariableDeclarator"
export class VariableDeclaration extends Statement {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 150)
        super(pointer)
    }
    static createVariableDeclaration(kind: Es2pandaVariableDeclarationKind, declarators: readonly VariableDeclarator[]): VariableDeclaration {
        return new VariableDeclaration(global.generatedEs2panda._CreateVariableDeclaration(global.context, kind, passNodeArray(declarators), declarators.length))
    }
    static updateVariableDeclaration(original: VariableDeclaration | undefined, kind: Es2pandaVariableDeclarationKind, declarators: readonly VariableDeclarator[]): VariableDeclaration {
        return new VariableDeclaration(global.generatedEs2panda._UpdateVariableDeclaration(global.context, passNode(original), kind, passNodeArray(declarators), declarators.length))
    }
    get declarators(): readonly VariableDeclarator[] {
        return unpackNodeArray(global.generatedEs2panda._VariableDeclarationDeclaratorsConst(global.context, this.peer))
    }
    get kind(): Es2pandaVariableDeclarationKind {
        return global.generatedEs2panda._VariableDeclarationKindConst(global.context, this.peer)
    }
    get decorators(): readonly Decorator[] {
        return unpackNodeArray(global.generatedEs2panda._VariableDeclarationDecoratorsConst(global.context, this.peer))
    }
    get annotations(): readonly AnnotationUsage[] {
        return unpackNodeArray(global.generatedEs2panda._VariableDeclarationAnnotations(global.context, this.peer))
    }
    /** @deprecated */
    setAnnotations(annotations: readonly AnnotationUsage[]): this {
        global.generatedEs2panda._VariableDeclarationSetAnnotations(global.context, this.peer, passNodeArray(annotations), annotations.length)
        return this
    }
}
export function isVariableDeclaration(node: object | undefined): node is VariableDeclaration {
    return node instanceof VariableDeclaration
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_VARIABLE_DECLARATION)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_VARIABLE_DECLARATION, (peer: KNativePointer) => new VariableDeclaration(peer))
}