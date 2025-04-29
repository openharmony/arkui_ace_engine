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
import { Es2pandaAstNodeType } from "./../Es2pandaEnums"
import { ScriptFunction } from "./ScriptFunction"
import { Statement } from "./Statement"
export class FunctionDeclaration extends Statement {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 34)
        super(pointer)
    }
    static createFunctionDeclaration(func: ScriptFunction | undefined, annotations: readonly AnnotationUsage[], isAnonymous: boolean): FunctionDeclaration {
        return new FunctionDeclaration(global.generatedEs2panda._CreateFunctionDeclaration(global.context, passNode(func), passNodeArray(annotations), annotations.length, isAnonymous))
    }
    static updateFunctionDeclaration(original: FunctionDeclaration | undefined, func: ScriptFunction | undefined, annotations: readonly AnnotationUsage[], isAnonymous: boolean): FunctionDeclaration {
        return new FunctionDeclaration(global.generatedEs2panda._UpdateFunctionDeclaration(global.context, passNode(original), passNode(func), passNodeArray(annotations), annotations.length, isAnonymous))
    }
    static update1FunctionDeclaration(original: FunctionDeclaration | undefined, func: ScriptFunction | undefined, isAnonymous: boolean): FunctionDeclaration {
        return new FunctionDeclaration(global.generatedEs2panda._UpdateFunctionDeclaration1(global.context, passNode(original), passNode(func), isAnonymous))
    }
    get function(): ScriptFunction | undefined {
        return unpackNode(global.generatedEs2panda._FunctionDeclarationFunction(global.context, this.peer))
    }
    get isAnonymous(): boolean {
        return global.generatedEs2panda._FunctionDeclarationIsAnonymousConst(global.context, this.peer)
    }
    get annotations(): readonly AnnotationUsage[] {
        return unpackNodeArray(global.generatedEs2panda._FunctionDeclarationAnnotations(global.context, this.peer))
    }
    /** @deprecated */
    setAnnotations(annotations: readonly AnnotationUsage[]): this {
        global.generatedEs2panda._FunctionDeclarationSetAnnotations(global.context, this.peer, passNodeArray(annotations), annotations.length)
        return this
    }
}
export function isFunctionDeclaration(node: object | undefined): node is FunctionDeclaration {
    return node instanceof FunctionDeclaration
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_FUNCTION_DECLARATION)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_FUNCTION_DECLARATION, (peer: KNativePointer) => new FunctionDeclaration(peer))
}