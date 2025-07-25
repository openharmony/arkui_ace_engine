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
import { Statement } from "./Statement"
export class ExportDefaultDeclaration extends Statement {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 27)
        super(pointer)
    }
    static createExportDefaultDeclaration(decl: AstNode | undefined, exportEquals: boolean): ExportDefaultDeclaration {
        return new ExportDefaultDeclaration(global.generatedEs2panda._CreateExportDefaultDeclaration(global.context, passNode(decl), exportEquals))
    }
    static updateExportDefaultDeclaration(original: ExportDefaultDeclaration | undefined, decl: AstNode | undefined, exportEquals: boolean): ExportDefaultDeclaration {
        return new ExportDefaultDeclaration(global.generatedEs2panda._UpdateExportDefaultDeclaration(global.context, passNode(original), passNode(decl), exportEquals))
    }
    get decl(): AstNode | undefined {
        return unpackNode(global.generatedEs2panda._ExportDefaultDeclarationDecl(global.context, this.peer))
    }
    get isExportEquals(): boolean {
        return global.generatedEs2panda._ExportDefaultDeclarationIsExportEqualsConst(global.context, this.peer)
    }
}
export function isExportDefaultDeclaration(node: object | undefined): node is ExportDefaultDeclaration {
    return node instanceof ExportDefaultDeclaration
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_EXPORT_DEFAULT_DECLARATION)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_EXPORT_DEFAULT_DECLARATION, (peer: KNativePointer) => new ExportDefaultDeclaration(peer))
}