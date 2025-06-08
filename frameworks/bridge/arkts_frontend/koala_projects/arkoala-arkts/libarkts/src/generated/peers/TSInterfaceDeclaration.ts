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

import { TypedStatement } from "./TypedStatement"
import { TSInterfaceHeritage } from "./TSInterfaceHeritage"
import { TSInterfaceBody } from "./TSInterfaceBody"
import { Identifier } from "./Identifier"
import { TSTypeParameterDeclaration } from "./TSTypeParameterDeclaration"
import { Decorator } from "./Decorator"
import { ClassDeclaration } from "./ClassDeclaration"
import { AnnotationUsage } from "./AnnotationUsage"
export class TSInterfaceDeclaration extends TypedStatement {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 130)
        super(pointer)
        console.warn("Warning: stub node TSInterfaceDeclaration")
    }
    static createTSInterfaceDeclaration(_extends: readonly TSInterfaceHeritage[], id: AstNode | undefined, typeParams: AstNode | undefined, body: AstNode | undefined, isStatic: boolean, isExternal: boolean): TSInterfaceDeclaration {
        return new TSInterfaceDeclaration(global.generatedEs2panda._CreateTSInterfaceDeclaration(global.context, passNodeArray(_extends), _extends.length, passNode(id), passNode(typeParams), passNode(body), isStatic, isExternal))
    }
    static updateTSInterfaceDeclaration(original: TSInterfaceDeclaration | undefined, _extends: readonly TSInterfaceHeritage[], id: AstNode | undefined, typeParams: AstNode | undefined, body: AstNode | undefined, isStatic: boolean, isExternal: boolean): TSInterfaceDeclaration {
        return new TSInterfaceDeclaration(global.generatedEs2panda._UpdateTSInterfaceDeclaration(global.context, passNode(original), passNodeArray(_extends), _extends.length, passNode(id), passNode(typeParams), passNode(body), isStatic, isExternal))
    }
    get body(): TSInterfaceBody | undefined {
        return unpackNode(global.generatedEs2panda._TSInterfaceDeclarationBodyConst(global.context, this.peer))
    }
    get id(): Identifier | undefined {
        return unpackNode(global.generatedEs2panda._TSInterfaceDeclarationIdConst(global.context, this.peer))
    }
    get internalName(): string {
        return unpackString(global.generatedEs2panda._TSInterfaceDeclarationInternalNameConst(global.context, this.peer))
    }
    /** @deprecated */
    setInternalName(internalName: string): this {
        global.generatedEs2panda._TSInterfaceDeclarationSetInternalName(global.context, this.peer, internalName)
        return this
    }
    get isStatic(): boolean {
        return global.generatedEs2panda._TSInterfaceDeclarationIsStaticConst(global.context, this.peer)
    }
    get isFromExternal(): boolean {
        return global.generatedEs2panda._TSInterfaceDeclarationIsFromExternalConst(global.context, this.peer)
    }
    get typeParams(): TSTypeParameterDeclaration | undefined {
        return unpackNode(global.generatedEs2panda._TSInterfaceDeclarationTypeParamsConst(global.context, this.peer))
    }
    get extends(): readonly TSInterfaceHeritage[] {
        return unpackNodeArray(global.generatedEs2panda._TSInterfaceDeclarationExtendsConst(global.context, this.peer))
    }
    get decorators(): readonly Decorator[] {
        return unpackNodeArray(global.generatedEs2panda._TSInterfaceDeclarationDecoratorsConst(global.context, this.peer))
    }
    get getAnonClass(): ClassDeclaration | undefined {
        return unpackNode(global.generatedEs2panda._TSInterfaceDeclarationGetAnonClassConst(global.context, this.peer))
    }
    /** @deprecated */
    setAnonClass(anonClass: ClassDeclaration): this {
        global.generatedEs2panda._TSInterfaceDeclarationSetAnonClass(global.context, this.peer, passNode(anonClass))
        return this
    }
    get annotations(): readonly AnnotationUsage[] {
        return unpackNodeArray(global.generatedEs2panda._TSInterfaceDeclarationAnnotationsConst(global.context, this.peer))
    }
    /** @deprecated */
    setAnnotations(annotations: readonly AnnotationUsage[]): this {
        global.generatedEs2panda._TSInterfaceDeclarationSetAnnotations(global.context, this.peer, passNodeArray(annotations), annotations.length)
        return this
    }
}
export function isTSInterfaceDeclaration(node: AstNode): node is TSInterfaceDeclaration {
    return node instanceof TSInterfaceDeclaration
}
if (!nodeByType.has(130)) {
    nodeByType.set(130, TSInterfaceDeclaration)
}