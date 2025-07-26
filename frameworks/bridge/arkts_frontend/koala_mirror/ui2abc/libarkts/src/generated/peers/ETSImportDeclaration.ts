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
import { Es2pandaId } from "./../Es2pandaEnums"
import { Es2pandaImportFlags } from "./../Es2pandaEnums"
import { Es2pandaImportKinds } from "./../Es2pandaEnums"
import { ImportDeclaration } from "./ImportDeclaration"
import { StringLiteral } from "./StringLiteral"
export class ETSImportDeclaration extends ImportDeclaration {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 79)
        super(pointer)
    }
    static createETSImportDeclaration(importPath: StringLiteral | undefined, specifiers: readonly AstNode[], importKinds: Es2pandaImportKinds): ETSImportDeclaration {
        return new ETSImportDeclaration(global.generatedEs2panda._CreateETSImportDeclaration(global.context, passNode(importPath), passNodeArray(specifiers), specifiers.length, importKinds))
    }
    static updateETSImportDeclaration(original: ETSImportDeclaration | undefined, importPath: StringLiteral | undefined, specifiers: readonly AstNode[], importKinds: Es2pandaImportKinds): ETSImportDeclaration {
        return new ETSImportDeclaration(global.generatedEs2panda._UpdateETSImportDeclaration(global.context, passNode(original), passNode(importPath), passNodeArray(specifiers), specifiers.length, importKinds))
    }
    /** @deprecated */
    setImportMetadata(importFlags: Es2pandaImportFlags, lang: Es2pandaId, resolvedSource: string, declPath: string, ohmUrl: string): this {
        global.generatedEs2panda._ETSImportDeclarationSetImportMetadata(global.context, this.peer, importFlags, lang, resolvedSource, declPath, ohmUrl)
        return this
    }
    get declPath(): string {
        return unpackString(global.generatedEs2panda._ETSImportDeclarationDeclPathConst(global.context, this.peer))
    }
    get ohmUrl(): string {
        return unpackString(global.generatedEs2panda._ETSImportDeclarationOhmUrlConst(global.context, this.peer))
    }
    get isValid(): boolean {
        return global.generatedEs2panda._ETSImportDeclarationIsValidConst(global.context, this.peer)
    }
    get isPureDynamic(): boolean {
        return global.generatedEs2panda._ETSImportDeclarationIsPureDynamicConst(global.context, this.peer)
    }
    get assemblerName(): string {
        return unpackString(global.generatedEs2panda._ETSImportDeclarationAssemblerName(global.context, this.peer))
    }
    get resolvedSource(): string {
        return unpackString(global.generatedEs2panda._ETSImportDeclarationResolvedSourceConst(global.context, this.peer))
    }
}
export function isETSImportDeclaration(node: object | undefined): node is ETSImportDeclaration {
    return node instanceof ETSImportDeclaration
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_ETS_IMPORT_DECLARATION)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_ETS_IMPORT_DECLARATION, (peer: KNativePointer) => new ETSImportDeclaration(peer))
}