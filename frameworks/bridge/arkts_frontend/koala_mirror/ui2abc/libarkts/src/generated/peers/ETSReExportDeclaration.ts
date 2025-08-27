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

import { ETSImportDeclaration } from "./ETSImportDeclaration"
import { Es2pandaAstNodeType } from "./../Es2pandaEnums"
import { Statement } from "./Statement"
export class ETSReExportDeclaration extends Statement {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 57)
        super(pointer)
    }
    get eTSImportDeclarations(): ETSImportDeclaration | undefined {
        return unpackNode(global.generatedEs2panda._ETSReExportDeclarationGetETSImportDeclarations(global.context, this.peer))
    }
    get programPath(): string {
        return unpackString(global.generatedEs2panda._ETSReExportDeclarationGetProgramPathConst(global.context, this.peer))
    }
}
export function isETSReExportDeclaration(node: object | undefined): node is ETSReExportDeclaration {
    return node instanceof ETSReExportDeclaration
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_REEXPORT_STATEMENT)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_REEXPORT_STATEMENT, (peer: KNativePointer) => new ETSReExportDeclaration(peer))
}