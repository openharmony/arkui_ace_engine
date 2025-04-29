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

import { ETSImportDeclaration, StringLiteral } from "../../generated"
import { isSameNativeObject } from "../peers/ArktsObject"
import { passNode, passNodeArray, unpackNonNullableNode, updateNodeByNode } from "../utilities/private"
import { AstNode } from "../peers/AstNode"
import { Es2pandaImportFlags, Es2pandaImportKinds } from "../../generated/Es2pandaEnums"
import { global } from "../static/global"
import { Program } from "../peers/Program"

export function createETSImportDeclaration(
    source: StringLiteral | undefined,
    specifiers: readonly AstNode[],
    importKind: Es2pandaImportKinds,
    program: Program,
    flags: Es2pandaImportFlags
): ETSImportDeclaration {
    const res = unpackNonNullableNode(
        global.es2panda._ETSParserBuildImportDeclaration(
            global.context,
            importKind,
            passNodeArray(specifiers),
            specifiers.length,
            passNode(source),
            program.peer,
            flags
        )
    )
    global.es2panda._InsertETSImportDeclarationAndParse(global.context, global.compilerContext.program.peer, res.peer)
    return new ETSImportDeclaration(res.peer)
}

export function updateETSImportDeclaration(
    original: ETSImportDeclaration,
    source: StringLiteral | undefined,
    specifiers: readonly AstNode[],
    importKind: Es2pandaImportKinds
) {
    if (isSameNativeObject(source, original.source)
        && isSameNativeObject(specifiers, original.specifiers)
        /* no getter for importKind */
    ) {
        /* TODO: probably should set importMetadata, but no getter provided yet */
        return original
    }
    return updateNodeByNode(
        ETSImportDeclaration.createETSImportDeclaration(source, specifiers, importKind),
        original
    )
}
