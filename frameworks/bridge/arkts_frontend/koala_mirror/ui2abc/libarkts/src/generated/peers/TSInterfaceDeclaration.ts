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
import { ClassDeclaration } from "./ClassDeclaration"
import { Decorator } from "./Decorator"
import { Es2pandaAstNodeType } from "./../Es2pandaEnums"
import { Identifier } from "./Identifier"
import { TSInterfaceBody } from "./TSInterfaceBody"
import { TSInterfaceHeritage } from "./TSInterfaceHeritage"
import { TSTypeParameterDeclaration } from "./TSTypeParameterDeclaration"
import { TypedStatement } from "./TypedStatement"
export class TSInterfaceDeclaration extends TypedStatement {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 131)
        super(pointer)
    }
    static createTSInterfaceDeclaration(_extends: readonly TSInterfaceHeritage[], id: AstNode | undefined, typeParams: AstNode | undefined, body: AstNode | undefined, isStatic: boolean, isExternal: boolean): TSInterfaceDeclaration {
        return new TSInterfaceDeclaration(global.generatedEs2panda._CreateTSInterfaceDeclaration(global.context, passNodeArray(_extends), _extends.length, passNode(id), passNode(typeParams), passNode(body), isStatic, isExternal))
    }
    static updateTSInterfaceDeclaration(original: TSInterfaceDeclaration | undefined, _extends: readonly TSInterfaceHeritage[], id: AstNode | undefined, typeParams: AstNode | undefined, body: AstNode | undefined, isStatic: boolean, isExternal: boolean): TSInterfaceDeclaration {
        return new TSInterfaceDeclaration(global.generatedEs2panda._UpdateTSInterfaceDeclaration(global.context, passNode(original), passNodeArray(_extends), _extends.length, passNode(id), passNode(typeParams), passNode(body), isStatic, isExternal))
    }
    get body(): TSInterfaceBody | undefined {
        return unpackNode(global.generatedEs2panda._TSInterfaceDeclarationBody(global.context, this.peer))
    }
    get id(): Identifier | undefined {
        return unpackNode(global.generatedEs2panda._TSInterfaceDeclarationId(global.context, this.peer))
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
        return unpackNode(global.generatedEs2panda._TSInterfaceDeclarationTypeParams(global.context, this.peer))
    }
    get extends(): readonly TSInterfaceHeritage[] {
        return unpackNodeArray(global.generatedEs2panda._TSInterfaceDeclarationExtends(global.context, this.peer))
    }
    get decorators(): readonly Decorator[] {
        return unpackNodeArray(global.generatedEs2panda._TSInterfaceDeclarationDecoratorsConst(global.context, this.peer))
    }
    get anonClass(): ClassDeclaration | undefined {
        return unpackNode(global.generatedEs2panda._TSInterfaceDeclarationGetAnonClass(global.context, this.peer))
    }
    /** @deprecated */
    setAnonClass(anonClass?: ClassDeclaration): this {
        global.generatedEs2panda._TSInterfaceDeclarationSetAnonClass(global.context, this.peer, passNode(anonClass))
        return this
    }
    get annotations(): readonly AnnotationUsage[] {
        return unpackNodeArray(global.generatedEs2panda._TSInterfaceDeclarationAnnotations(global.context, this.peer))
    }
    /** @deprecated */
    setAnnotations(annotations: readonly AnnotationUsage[]): this {
        global.generatedEs2panda._TSInterfaceDeclarationSetAnnotations(global.context, this.peer, passNodeArray(annotations), annotations.length)
        return this
    }
}
export function isTSInterfaceDeclaration(node: object | undefined): node is TSInterfaceDeclaration {
    return node instanceof TSInterfaceDeclaration
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_TS_INTERFACE_DECLARATION)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_TS_INTERFACE_DECLARATION, (peer: KNativePointer) => new TSInterfaceDeclaration(peer))
}