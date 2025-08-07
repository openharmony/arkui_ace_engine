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
import { Es2pandaImportKinds } from "./../Es2pandaEnums"
import { Statement } from "./Statement"
import { StringLiteral } from "./StringLiteral"
export class ImportDeclaration extends Statement {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 39)
        super(pointer)
    }
    static createImportDeclaration(source: StringLiteral | undefined, specifiers: readonly AstNode[], importKinds: Es2pandaImportKinds): ImportDeclaration {
        return new ImportDeclaration(global.generatedEs2panda._CreateImportDeclaration(global.context, passNode(source), passNodeArray(specifiers), specifiers.length, importKinds))
    }
    static updateImportDeclaration(original: ImportDeclaration | undefined, source: StringLiteral | undefined, specifiers: readonly AstNode[], importKinds: Es2pandaImportKinds): ImportDeclaration {
        return new ImportDeclaration(global.generatedEs2panda._UpdateImportDeclaration(global.context, passNode(original), passNode(source), passNodeArray(specifiers), specifiers.length, importKinds))
    }
    get source(): StringLiteral | undefined {
        return unpackNode(global.generatedEs2panda._ImportDeclarationSource(global.context, this.peer))
    }
    get specifiers(): readonly AstNode[] {
        return unpackNodeArray(global.generatedEs2panda._ImportDeclarationSpecifiers(global.context, this.peer))
    }
    get isTypeKind(): boolean {
        return global.generatedEs2panda._ImportDeclarationIsTypeKindConst(global.context, this.peer)
    }
}
export function isImportDeclaration(node: object | undefined): node is ImportDeclaration {
    return node instanceof ImportDeclaration
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_IMPORT_DECLARATION)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_IMPORT_DECLARATION, (peer: KNativePointer) => new ImportDeclaration(peer))
}