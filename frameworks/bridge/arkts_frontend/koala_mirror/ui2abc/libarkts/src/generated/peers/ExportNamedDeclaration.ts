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
import { ExportSpecifier } from "./ExportSpecifier"
import { Statement } from "./Statement"
import { StringLiteral } from "./StringLiteral"
export class ExportNamedDeclaration extends Statement {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 28)
        super(pointer)
    }
    static createExportNamedDeclaration(source: StringLiteral | undefined, specifiers: readonly ExportSpecifier[]): ExportNamedDeclaration {
        return new ExportNamedDeclaration(global.generatedEs2panda._CreateExportNamedDeclaration(global.context, passNode(source), passNodeArray(specifiers), specifiers.length))
    }
    static updateExportNamedDeclaration(original: ExportNamedDeclaration | undefined, source: StringLiteral | undefined, specifiers: readonly ExportSpecifier[]): ExportNamedDeclaration {
        return new ExportNamedDeclaration(global.generatedEs2panda._UpdateExportNamedDeclaration(global.context, passNode(original), passNode(source), passNodeArray(specifiers), specifiers.length))
    }
    static create1ExportNamedDeclaration(decl: AstNode | undefined, specifiers: readonly ExportSpecifier[]): ExportNamedDeclaration {
        return new ExportNamedDeclaration(global.generatedEs2panda._CreateExportNamedDeclaration1(global.context, passNode(decl), passNodeArray(specifiers), specifiers.length))
    }
    static update1ExportNamedDeclaration(original: ExportNamedDeclaration | undefined, decl: AstNode | undefined, specifiers: readonly ExportSpecifier[]): ExportNamedDeclaration {
        return new ExportNamedDeclaration(global.generatedEs2panda._UpdateExportNamedDeclaration1(global.context, passNode(original), passNode(decl), passNodeArray(specifiers), specifiers.length))
    }
    static create2ExportNamedDeclaration(decl?: AstNode): ExportNamedDeclaration {
        return new ExportNamedDeclaration(global.generatedEs2panda._CreateExportNamedDeclaration2(global.context, passNode(decl)))
    }
    static update2ExportNamedDeclaration(original?: ExportNamedDeclaration, decl?: AstNode): ExportNamedDeclaration {
        return new ExportNamedDeclaration(global.generatedEs2panda._UpdateExportNamedDeclaration2(global.context, passNode(original), passNode(decl)))
    }
    get decl(): AstNode | undefined {
        return unpackNode(global.generatedEs2panda._ExportNamedDeclarationDeclConst(global.context, this.peer))
    }
    get source(): StringLiteral | undefined {
        return unpackNode(global.generatedEs2panda._ExportNamedDeclarationSourceConst(global.context, this.peer))
    }
    get specifiers(): readonly ExportSpecifier[] {
        return unpackNodeArray(global.generatedEs2panda._ExportNamedDeclarationSpecifiersConst(global.context, this.peer))
    }
    /** @deprecated */
    replaceSpecifiers(specifiers: readonly ExportSpecifier[]): this {
        global.generatedEs2panda._ExportNamedDeclarationReplaceSpecifiers(global.context, this.peer, passNodeArray(specifiers), specifiers.length)
        return this
    }
}
export function isExportNamedDeclaration(node: object | undefined): node is ExportNamedDeclaration {
    return node instanceof ExportNamedDeclaration
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_EXPORT_NAMED_DECLARATION)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_EXPORT_NAMED_DECLARATION, (peer: KNativePointer) => new ExportNamedDeclaration(peer))
}