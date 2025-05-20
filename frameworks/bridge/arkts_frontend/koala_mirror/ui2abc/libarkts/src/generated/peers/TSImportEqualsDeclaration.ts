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
import { Expression } from "./Expression"
import { Identifier } from "./Identifier"
import { Statement } from "./Statement"
export class TSImportEqualsDeclaration extends Statement {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 124)
        super(pointer)
    }
    static createTSImportEqualsDeclaration(id: Identifier | undefined, moduleReference: Expression | undefined, isExport: boolean): TSImportEqualsDeclaration {
        return new TSImportEqualsDeclaration(global.generatedEs2panda._CreateTSImportEqualsDeclaration(global.context, passNode(id), passNode(moduleReference), isExport))
    }
    static updateTSImportEqualsDeclaration(original: TSImportEqualsDeclaration | undefined, id: Identifier | undefined, moduleReference: Expression | undefined, isExport: boolean): TSImportEqualsDeclaration {
        return new TSImportEqualsDeclaration(global.generatedEs2panda._UpdateTSImportEqualsDeclaration(global.context, passNode(original), passNode(id), passNode(moduleReference), isExport))
    }
    get id(): Identifier | undefined {
        return unpackNode(global.generatedEs2panda._TSImportEqualsDeclarationIdConst(global.context, this.peer))
    }
    get moduleReference(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._TSImportEqualsDeclarationModuleReferenceConst(global.context, this.peer))
    }
    get isExport(): boolean {
        return global.generatedEs2panda._TSImportEqualsDeclarationIsExportConst(global.context, this.peer)
    }
}
export function isTSImportEqualsDeclaration(node: object | undefined): node is TSImportEqualsDeclaration {
    return node instanceof TSImportEqualsDeclaration
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_TS_IMPORT_EQUALS_DECLARATION)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_TS_IMPORT_EQUALS_DECLARATION, (peer: KNativePointer) => new TSImportEqualsDeclaration(peer))
}