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

import { AnnotatedExpression } from "./AnnotatedExpression"
import { TypeNode } from "./TypeNode"
import { Decorator } from "./Decorator"
import { ValidationInfo } from "./ValidationInfo"
export class Identifier extends AnnotatedExpression {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 36)
        super(pointer)
        console.warn("Warning: stub node Identifier")
    }
    static createIdentifier(): Identifier {
        return new Identifier(global.generatedEs2panda._CreateIdentifier(global.context))
    }
    static updateIdentifier(original?: Identifier): Identifier {
        return new Identifier(global.generatedEs2panda._UpdateIdentifier(global.context, passNode(original)))
    }
    static create1Identifier(name: string): Identifier {
        return new Identifier(global.generatedEs2panda._CreateIdentifier1(global.context, name))
    }
    static update1Identifier(original: Identifier | undefined, name: string): Identifier {
        return new Identifier(global.generatedEs2panda._UpdateIdentifier1(global.context, passNode(original), name))
    }
    static create2Identifier(name: string, typeAnnotation?: TypeNode): Identifier {
        return new Identifier(global.generatedEs2panda._CreateIdentifier2(global.context, name, passNode(typeAnnotation)))
    }
    static update2Identifier(original: Identifier | undefined, name: string, typeAnnotation?: TypeNode): Identifier {
        return new Identifier(global.generatedEs2panda._UpdateIdentifier2(global.context, passNode(original), name, passNode(typeAnnotation)))
    }
    get name(): string {
        return unpackString(global.generatedEs2panda._IdentifierNameConst(global.context, this.peer))
    }
    /** @deprecated */
    setName(newName: string): this {
        global.generatedEs2panda._IdentifierSetName(global.context, this.peer, newName)
        return this
    }
    get decorators(): readonly Decorator[] {
        return unpackNodeArray(global.generatedEs2panda._IdentifierDecoratorsConst(global.context, this.peer))
    }
    get isErrorPlaceHolder(): boolean {
        return global.generatedEs2panda._IdentifierIsErrorPlaceHolderConst(global.context, this.peer)
    }
    get isOptional(): boolean {
        return global.generatedEs2panda._IdentifierIsOptionalConst(global.context, this.peer)
    }
    /** @deprecated */
    setOptional(optional_arg: boolean): this {
        global.generatedEs2panda._IdentifierSetOptional(global.context, this.peer, optional_arg)
        return this
    }
    get isReference(): boolean {
        return global.generatedEs2panda._IdentifierIsReferenceConst(global.context, this.peer)
    }
    get isTdz(): boolean {
        return global.generatedEs2panda._IdentifierIsTdzConst(global.context, this.peer)
    }
    /** @deprecated */
    setTdz(): this {
        global.generatedEs2panda._IdentifierSetTdz(global.context, this.peer)
        return this
    }
    /** @deprecated */
    setAccessor(): this {
        global.generatedEs2panda._IdentifierSetAccessor(global.context, this.peer)
        return this
    }
    get isAccessor(): boolean {
        return global.generatedEs2panda._IdentifierIsAccessorConst(global.context, this.peer)
    }
    /** @deprecated */
    setMutator(): this {
        global.generatedEs2panda._IdentifierSetMutator(global.context, this.peer)
        return this
    }
    get isMutator(): boolean {
        return global.generatedEs2panda._IdentifierIsMutatorConst(global.context, this.peer)
    }
    get isReceiver(): boolean {
        return global.generatedEs2panda._IdentifierIsReceiverConst(global.context, this.peer)
    }
    get isPrivateIdent(): boolean {
        return global.generatedEs2panda._IdentifierIsPrivateIdentConst(global.context, this.peer)
    }
    /** @deprecated */
    setPrivate(isPrivate: boolean): this {
        global.generatedEs2panda._IdentifierSetPrivate(global.context, this.peer, isPrivate)
        return this
    }
    get isIgnoreBox(): boolean {
        return global.generatedEs2panda._IdentifierIsIgnoreBoxConst(global.context, this.peer)
    }
    /** @deprecated */
    setIgnoreBox(): this {
        global.generatedEs2panda._IdentifierSetIgnoreBox(global.context, this.peer)
        return this
    }
    get isAnnotationDecl(): boolean {
        return global.generatedEs2panda._IdentifierIsAnnotationDeclConst(global.context, this.peer)
    }
    /** @deprecated */
    setAnnotationDecl(): this {
        global.generatedEs2panda._IdentifierSetAnnotationDecl(global.context, this.peer)
        return this
    }
    get isAnnotationUsage(): boolean {
        return global.generatedEs2panda._IdentifierIsAnnotationUsageConst(global.context, this.peer)
    }
    /** @deprecated */
    setAnnotationUsage(): this {
        global.generatedEs2panda._IdentifierSetAnnotationUsage(global.context, this.peer)
        return this
    }
    get typeAnnotation(): TypeNode | undefined {
        return unpackNode(global.generatedEs2panda._IdentifierTypeAnnotationConst(global.context, this.peer))
    }
    /** @deprecated */
    setTsTypeAnnotation(typeAnnotation: TypeNode): this {
        global.generatedEs2panda._IdentifierSetTsTypeAnnotation(global.context, this.peer, passNode(typeAnnotation))
        return this
    }
}
export function isIdentifier(node: AstNode): node is Identifier {
    return node instanceof Identifier
}
if (!nodeByType.has(36)) {
    nodeByType.set(36, Identifier)
}