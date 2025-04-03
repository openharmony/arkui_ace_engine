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

import { Statement } from "./Statement"
import { Identifier } from "./Identifier"
export class ImportNamespaceSpecifier extends Statement {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 42)
        super(pointer)
        console.warn("Warning: stub node ImportNamespaceSpecifier")
    }
    static createImportNamespaceSpecifier(local?: Identifier): ImportNamespaceSpecifier {
        return new ImportNamespaceSpecifier(global.generatedEs2panda._CreateImportNamespaceSpecifier(global.context, passNode(local)))
    }
    static updateImportNamespaceSpecifier(original?: ImportNamespaceSpecifier, local?: Identifier): ImportNamespaceSpecifier {
        return new ImportNamespaceSpecifier(global.generatedEs2panda._UpdateImportNamespaceSpecifier(global.context, passNode(original), passNode(local)))
    }
    get local(): Identifier | undefined {
        return unpackNode(global.generatedEs2panda._ImportNamespaceSpecifierLocalConst(global.context, this.peer))
    }
}
export function isImportNamespaceSpecifier(node: AstNode): node is ImportNamespaceSpecifier {
    return node instanceof ImportNamespaceSpecifier
}
if (!nodeByType.has(42)) {
    nodeByType.set(42, ImportNamespaceSpecifier)
}