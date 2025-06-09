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

import { ImportDeclaration } from "./ImportDeclaration"
import { ImportSource } from "./ImportSource"
import { Es2pandaImportKinds } from "./../Es2pandaEnums"
import { StringLiteral } from "./StringLiteral"
export class ETSImportDeclaration extends ImportDeclaration {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 78)
        super(pointer)
        console.warn("Warning: stub node ETSImportDeclaration")
    }
    static createETSImportDeclaration(source: ImportSource | undefined, specifiers: readonly AstNode[], importKind: Es2pandaImportKinds): ETSImportDeclaration {
        return new ETSImportDeclaration(global.generatedEs2panda._CreateETSImportDeclaration(global.context, passNode(source), passNodeArray(specifiers), specifiers.length, importKind))
    }
    static updateETSImportDeclaration(original: ETSImportDeclaration | undefined, source: ImportSource | undefined, specifiers: readonly AstNode[], importKind: Es2pandaImportKinds): ETSImportDeclaration {
        return new ETSImportDeclaration(global.generatedEs2panda._UpdateETSImportDeclaration(global.context, passNode(original), passNode(source), passNodeArray(specifiers), specifiers.length, importKind))
    }
    get hasDecl(): boolean {
        return global.generatedEs2panda._ETSImportDeclarationHasDeclConst(global.context, this.peer)
    }
    get isPureDynamic(): boolean {
        return global.generatedEs2panda._ETSImportDeclarationIsPureDynamicConst(global.context, this.peer)
    }
    get assemblerName(): string {
        return unpackString(global.generatedEs2panda._ETSImportDeclarationAssemblerNameConst(global.context, this.peer))
    }
    get source(): StringLiteral | undefined {
        return unpackNode(global.generatedEs2panda._ETSImportDeclarationSourceConst(global.context, this.peer))
    }
    get resolvedSource(): StringLiteral | undefined {
        return unpackNode(global.generatedEs2panda._ETSImportDeclarationResolvedSourceConst(global.context, this.peer))
    }
}
export function isETSImportDeclaration(node: AstNode): node is ETSImportDeclaration {
    return node instanceof ETSImportDeclaration
}
if (!nodeByType.has(78)) {
    nodeByType.set(78, ETSImportDeclaration)
}