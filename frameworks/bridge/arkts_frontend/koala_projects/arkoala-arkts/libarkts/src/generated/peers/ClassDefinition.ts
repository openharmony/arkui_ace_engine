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

import { TypedAstNode } from "./TypedAstNode"
import { Identifier } from "./Identifier"
import { TSTypeParameterDeclaration } from "./TSTypeParameterDeclaration"
import { TSTypeParameterInstantiation } from "./TSTypeParameterInstantiation"
import { TSClassImplements } from "./TSClassImplements"
import { MethodDefinition } from "./MethodDefinition"
import { Expression } from "./Expression"
import { Es2pandaClassDefinitionModifiers } from "./../Es2pandaEnums"
import { Es2pandaModifierFlags } from "./../Es2pandaEnums"
import { TSEnumDeclaration } from "./TSEnumDeclaration"
import { ClassDeclaration } from "./ClassDeclaration"
import { FunctionExpression } from "./FunctionExpression"
import { AnnotationUsage } from "./AnnotationUsage"
export class ClassDefinition extends TypedAstNode {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 14)
        super(pointer)
        console.warn("Warning: stub node ClassDefinition")
    }
    static createClassDefinition(ident: Identifier | undefined, typeParams: TSTypeParameterDeclaration | undefined, superTypeParams: TSTypeParameterInstantiation | undefined, _implements: readonly TSClassImplements[], ctor: MethodDefinition | undefined, superClass: Expression | undefined, body: readonly AstNode[], modifiers: Es2pandaClassDefinitionModifiers, flags: Es2pandaModifierFlags): ClassDefinition {
        return new ClassDefinition(global.generatedEs2panda._CreateClassDefinition(global.context, passNode(ident), passNode(typeParams), passNode(superTypeParams), passNodeArray(_implements), _implements.length, passNode(ctor), passNode(superClass), passNodeArray(body), body.length, modifiers, flags))
    }
    static updateClassDefinition(original: ClassDefinition | undefined, ident: Identifier | undefined, typeParams: TSTypeParameterDeclaration | undefined, superTypeParams: TSTypeParameterInstantiation | undefined, _implements: readonly TSClassImplements[], ctor: MethodDefinition | undefined, superClass: Expression | undefined, body: readonly AstNode[], modifiers: Es2pandaClassDefinitionModifiers, flags: Es2pandaModifierFlags): ClassDefinition {
        return new ClassDefinition(global.generatedEs2panda._UpdateClassDefinition(global.context, passNode(original), passNode(ident), passNode(typeParams), passNode(superTypeParams), passNodeArray(_implements), _implements.length, passNode(ctor), passNode(superClass), passNodeArray(body), body.length, modifiers, flags))
    }
    static create1ClassDefinition(ident: Identifier | undefined, body: readonly AstNode[], modifiers: Es2pandaClassDefinitionModifiers, flags: Es2pandaModifierFlags): ClassDefinition {
        return new ClassDefinition(global.generatedEs2panda._CreateClassDefinition1(global.context, passNode(ident), passNodeArray(body), body.length, modifiers, flags))
    }
    static update1ClassDefinition(original: ClassDefinition | undefined, ident: Identifier | undefined, body: readonly AstNode[], modifiers: Es2pandaClassDefinitionModifiers, flags: Es2pandaModifierFlags): ClassDefinition {
        return new ClassDefinition(global.generatedEs2panda._UpdateClassDefinition1(global.context, passNode(original), passNode(ident), passNodeArray(body), body.length, modifiers, flags))
    }
    static create2ClassDefinition(ident: Identifier | undefined, modifiers: Es2pandaClassDefinitionModifiers, flags: Es2pandaModifierFlags): ClassDefinition {
        return new ClassDefinition(global.generatedEs2panda._CreateClassDefinition2(global.context, passNode(ident), modifiers, flags))
    }
    static update2ClassDefinition(original: ClassDefinition | undefined, ident: Identifier | undefined, modifiers: Es2pandaClassDefinitionModifiers, flags: Es2pandaModifierFlags): ClassDefinition {
        return new ClassDefinition(global.generatedEs2panda._UpdateClassDefinition2(global.context, passNode(original), passNode(ident), modifiers, flags))
    }
    get ident(): Identifier | undefined {
        return unpackNode(global.generatedEs2panda._ClassDefinitionIdentConst(global.context, this.peer))
    }
    /** @deprecated */
    setIdent(ident: Identifier): this {
        global.generatedEs2panda._ClassDefinitionSetIdent(global.context, this.peer, passNode(ident))
        return this
    }
    get internalName(): string {
        return unpackString(global.generatedEs2panda._ClassDefinitionInternalNameConst(global.context, this.peer))
    }
    /** @deprecated */
    setInternalName(internalName: string): this {
        global.generatedEs2panda._ClassDefinitionSetInternalName(global.context, this.peer, internalName)
        return this
    }
    get super(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._ClassDefinitionSuperConst(global.context, this.peer))
    }
    /** @deprecated */
    setSuper(superClass: Expression): this {
        global.generatedEs2panda._ClassDefinitionSetSuper(global.context, this.peer, passNode(superClass))
        return this
    }
    get isGlobal(): boolean {
        return global.generatedEs2panda._ClassDefinitionIsGlobalConst(global.context, this.peer)
    }
    get isLocal(): boolean {
        return global.generatedEs2panda._ClassDefinitionIsLocalConst(global.context, this.peer)
    }
    get isExtern(): boolean {
        return global.generatedEs2panda._ClassDefinitionIsExternConst(global.context, this.peer)
    }
    get isFromExternal(): boolean {
        return global.generatedEs2panda._ClassDefinitionIsFromExternalConst(global.context, this.peer)
    }
    get isInner(): boolean {
        return global.generatedEs2panda._ClassDefinitionIsInnerConst(global.context, this.peer)
    }
    get isGlobalInitialized(): boolean {
        return global.generatedEs2panda._ClassDefinitionIsGlobalInitializedConst(global.context, this.peer)
    }
    get isClassDefinitionChecked(): boolean {
        return global.generatedEs2panda._ClassDefinitionIsClassDefinitionCheckedConst(global.context, this.peer)
    }
    get isAnonymous(): boolean {
        return global.generatedEs2panda._ClassDefinitionIsAnonymousConst(global.context, this.peer)
    }
    get isNamespaceTransformed(): boolean {
        return global.generatedEs2panda._ClassDefinitionIsNamespaceTransformedConst(global.context, this.peer)
    }
    get isModule(): boolean {
        return global.generatedEs2panda._ClassDefinitionIsModuleConst(global.context, this.peer)
    }
    /** @deprecated */
    setGlobalInitialized(): this {
        global.generatedEs2panda._ClassDefinitionSetGlobalInitialized(global.context, this.peer)
        return this
    }
    /** @deprecated */
    setInnerModifier(): this {
        global.generatedEs2panda._ClassDefinitionSetInnerModifier(global.context, this.peer)
        return this
    }
    /** @deprecated */
    setClassDefinitionChecked(): this {
        global.generatedEs2panda._ClassDefinitionSetClassDefinitionChecked(global.context, this.peer)
        return this
    }
    /** @deprecated */
    setAnonymousModifier(): this {
        global.generatedEs2panda._ClassDefinitionSetAnonymousModifier(global.context, this.peer)
        return this
    }
    /** @deprecated */
    setNamespaceTransformed(): this {
        global.generatedEs2panda._ClassDefinitionSetNamespaceTransformed(global.context, this.peer)
        return this
    }
    get modifiers(): Es2pandaClassDefinitionModifiers {
        return global.generatedEs2panda._ClassDefinitionModifiersConst(global.context, this.peer)
    }
    /** @deprecated */
    setModifiers(modifiers: Es2pandaClassDefinitionModifiers): this {
        global.generatedEs2panda._ClassDefinitionSetModifiers(global.context, this.peer, modifiers)
        return this
    }
    /** @deprecated */
    addProperties(body: readonly AstNode[]): this {
        global.generatedEs2panda._ClassDefinitionAddProperties(global.context, this.peer, passNodeArray(body), body.length)
        return this
    }
    get body(): readonly AstNode[] {
        return unpackNodeArray(global.generatedEs2panda._ClassDefinitionBodyConst(global.context, this.peer))
    }
    /** @deprecated */
    setCtor(ctor: MethodDefinition): this {
        global.generatedEs2panda._ClassDefinitionSetCtor(global.context, this.peer, passNode(ctor))
        return this
    }
    get implements(): readonly TSClassImplements[] {
        return unpackNodeArray(global.generatedEs2panda._ClassDefinitionImplementsConst(global.context, this.peer))
    }
    get typeParams(): TSTypeParameterDeclaration | undefined {
        return unpackNode(global.generatedEs2panda._ClassDefinitionTypeParamsConst(global.context, this.peer))
    }
    /** @deprecated */
    setTypeParams(typeParams: TSTypeParameterDeclaration): this {
        global.generatedEs2panda._ClassDefinitionSetTypeParams(global.context, this.peer, passNode(typeParams))
        return this
    }
    get superTypeParams(): TSTypeParameterInstantiation | undefined {
        return unpackNode(global.generatedEs2panda._ClassDefinitionSuperTypeParamsConst(global.context, this.peer))
    }
    get localTypeCounter(): number {
        return global.generatedEs2panda._ClassDefinitionLocalTypeCounter(global.context, this.peer)
    }
    get localIndex(): number {
        return global.generatedEs2panda._ClassDefinitionLocalIndexConst(global.context, this.peer)
    }
    get localPrefix(): string {
        return unpackString(global.generatedEs2panda._ClassDefinitionLocalPrefixConst(global.context, this.peer))
    }
    /** @deprecated */
    setOrigEnumDecl(enumDecl: TSEnumDeclaration): this {
        global.generatedEs2panda._ClassDefinitionSetOrigEnumDecl(global.context, this.peer, passNode(enumDecl))
        return this
    }
    get origEnumDecl(): TSEnumDeclaration | undefined {
        return unpackNode(global.generatedEs2panda._ClassDefinitionOrigEnumDeclConst(global.context, this.peer))
    }
    get getAnonClass(): ClassDeclaration | undefined {
        return unpackNode(global.generatedEs2panda._ClassDefinitionGetAnonClass(global.context, this.peer))
    }
    /** @deprecated */
    setAnonClass(anonClass: ClassDeclaration): this {
        global.generatedEs2panda._ClassDefinitionSetAnonClass(global.context, this.peer, passNode(anonClass))
        return this
    }
    get annotations(): readonly AnnotationUsage[] {
        return unpackNodeArray(global.generatedEs2panda._ClassDefinitionAnnotationsConst(global.context, this.peer))
    }
    /** @deprecated */
    setAnnotations(annotations: readonly AnnotationUsage[]): this {
        global.generatedEs2panda._ClassDefinitionSetAnnotations(global.context, this.peer, passNodeArray(annotations), annotations.length)
        return this
    }
}
export function isClassDefinition(node: AstNode): node is ClassDefinition {
    return node instanceof ClassDefinition
}
if (!nodeByType.has(14)) {
    nodeByType.set(14, ClassDefinition)
}