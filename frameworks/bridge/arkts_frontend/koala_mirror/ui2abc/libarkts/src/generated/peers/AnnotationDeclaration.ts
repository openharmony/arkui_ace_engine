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
import { Expression } from "./Expression"
import { Identifier } from "./Identifier"
import { Statement } from "./Statement"
export class AnnotationDeclaration extends Statement {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 1)
        super(pointer)
    }
    static create1AnnotationDeclaration(expr: Expression | undefined, properties: readonly AstNode[]): AnnotationDeclaration {
        return new AnnotationDeclaration(global.generatedEs2panda._CreateAnnotationDeclaration1(global.context, passNode(expr), passNodeArray(properties), properties.length))
    }
    static updateAnnotationDeclaration(original?: AnnotationDeclaration, expr?: Expression): AnnotationDeclaration {
        return new AnnotationDeclaration(global.generatedEs2panda._UpdateAnnotationDeclaration(global.context, passNode(original), passNode(expr)))
    }
    static update1AnnotationDeclaration(original: AnnotationDeclaration | undefined, expr: Expression | undefined, properties: readonly AstNode[]): AnnotationDeclaration {
        return new AnnotationDeclaration(global.generatedEs2panda._UpdateAnnotationDeclaration1(global.context, passNode(original), passNode(expr), passNodeArray(properties), properties.length))
    }
    get internalName(): string {
        return unpackString(global.generatedEs2panda._AnnotationDeclarationInternalNameConst(global.context, this.peer))
    }
    /** @deprecated */
    setInternalName(internalName: string): this {
        global.generatedEs2panda._AnnotationDeclarationSetInternalName(global.context, this.peer, internalName)
        return this
    }
    get expr(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._AnnotationDeclarationExpr(global.context, this.peer))
    }
    get properties(): readonly AstNode[] {
        return unpackNodeArray(global.generatedEs2panda._AnnotationDeclarationProperties(global.context, this.peer))
    }
    /** @deprecated */
    addProperties(properties: readonly AstNode[]): this {
        global.generatedEs2panda._AnnotationDeclarationAddProperties(global.context, this.peer, passNodeArray(properties), properties.length)
        return this
    }
    get isSourceRetention(): boolean {
        return global.generatedEs2panda._AnnotationDeclarationIsSourceRetentionConst(global.context, this.peer)
    }
    get isBytecodeRetention(): boolean {
        return global.generatedEs2panda._AnnotationDeclarationIsBytecodeRetentionConst(global.context, this.peer)
    }
    get isRuntimeRetention(): boolean {
        return global.generatedEs2panda._AnnotationDeclarationIsRuntimeRetentionConst(global.context, this.peer)
    }
    /** @deprecated */
    setSourceRetention(): this {
        global.generatedEs2panda._AnnotationDeclarationSetSourceRetention(global.context, this.peer)
        return this
    }
    /** @deprecated */
    setBytecodeRetention(): this {
        global.generatedEs2panda._AnnotationDeclarationSetBytecodeRetention(global.context, this.peer)
        return this
    }
    /** @deprecated */
    setRuntimeRetention(): this {
        global.generatedEs2panda._AnnotationDeclarationSetRuntimeRetention(global.context, this.peer)
        return this
    }
    get baseName(): Identifier | undefined {
        return unpackNode(global.generatedEs2panda._AnnotationDeclarationGetBaseNameConst(global.context, this.peer))
    }
    get annotations(): readonly AnnotationUsage[] {
        return unpackNodeArray(global.generatedEs2panda._AnnotationDeclarationAnnotations(global.context, this.peer))
    }
    /** @deprecated */
    setAnnotations(annotations: readonly AnnotationUsage[]): this {
        global.generatedEs2panda._AnnotationDeclarationSetAnnotations(global.context, this.peer, passNodeArray(annotations), annotations.length)
        return this
    }
}
export function isAnnotationDeclaration(node: object | undefined): node is AnnotationDeclaration {
    return node instanceof AnnotationDeclaration
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_ANNOTATION_DECLARATION)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_ANNOTATION_DECLARATION, (peer: KNativePointer) => new AnnotationDeclaration(peer))
}