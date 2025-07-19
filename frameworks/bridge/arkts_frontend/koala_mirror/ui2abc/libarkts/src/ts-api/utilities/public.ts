/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

import { global } from "../../arkts-api/static/global"
import { throwError } from "../../utils"
import * as ts from "../."
import { KNativePointer, nullptr } from "@koalaui/interop"
import { unpackNonNullableNode } from "../../arkts-api"

export { proceedToState, startChecker } from "../../arkts-api"

// Improve: like in arkts utils
export function getDecl(node: ts.Node): ts.Node | undefined {
    if (node.node === undefined) {
        throwError('there is no arkts pair of ts node (unable to getDecl)')
    }
    let decl: KNativePointer = node.node.peer
    decl = global.es2panda._AstNodeVariableConst(global.context, decl)
    if (decl === nullptr) {
        return undefined
    }
    decl = global.es2panda._VariableDeclaration(global.context, decl)
    if (decl === nullptr) {
        return undefined
    }
    decl = global.es2panda._DeclNode(global.context, decl)
    if (decl === nullptr) {
        return undefined
    }
    return ts.unpackNode(unpackNonNullableNode(decl))
}

// Improve: like in arkts utils
export function getOriginalNode(node: ts.Node): ts.Node {
    if (node.node === undefined) {
        // Improve: fix this
        throwError('there is no arkts pair of ts node (unable to getOriginalNode)')
    }
    if (node.node.originalPeer === nullptr) {
        return node
    }
    return ts.unpackNode(unpackNonNullableNode(node.node.originalPeer))
}
