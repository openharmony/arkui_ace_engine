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
import { Expression } from "./Expression"
export class TSImportEqualsDeclaration extends Statement {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 123)
        super(pointer)
        console.warn("Warning: stub node TSImportEqualsDeclaration")
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
export function isTSImportEqualsDeclaration(node: AstNode): node is TSImportEqualsDeclaration {
    return node instanceof TSImportEqualsDeclaration
}
if (!nodeByType.has(123)) {
    nodeByType.set(123, TSImportEqualsDeclaration)
}