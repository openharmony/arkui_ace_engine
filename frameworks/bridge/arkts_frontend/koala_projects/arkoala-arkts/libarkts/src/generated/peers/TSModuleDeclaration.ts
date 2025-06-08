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
import { Expression } from "./Expression"
export class TSModuleDeclaration extends Statement {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 122)
        super(pointer)
        console.warn("Warning: stub node TSModuleDeclaration")
    }
    static createTSModuleDeclaration(name: Expression | undefined, body: Statement | undefined, declare: boolean, _global: boolean): TSModuleDeclaration {
        return new TSModuleDeclaration(global.generatedEs2panda._CreateTSModuleDeclaration(global.context, passNode(name), passNode(body), declare, _global))
    }
    static updateTSModuleDeclaration(original: TSModuleDeclaration | undefined, name: Expression | undefined, body: Statement | undefined, declare: boolean, _global: boolean): TSModuleDeclaration {
        return new TSModuleDeclaration(global.generatedEs2panda._UpdateTSModuleDeclaration(global.context, passNode(original), passNode(name), passNode(body), declare, _global))
    }
    get name(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._TSModuleDeclarationNameConst(global.context, this.peer))
    }
    get body(): Statement | undefined {
        return unpackNode(global.generatedEs2panda._TSModuleDeclarationBodyConst(global.context, this.peer))
    }
    get global(): boolean {
        return global.generatedEs2panda._TSModuleDeclarationGlobalConst(global.context, this.peer)
    }
    get isExternalOrAmbient(): boolean {
        return global.generatedEs2panda._TSModuleDeclarationIsExternalOrAmbientConst(global.context, this.peer)
    }
}
export function isTSModuleDeclaration(node: AstNode): node is TSModuleDeclaration {
    return node instanceof TSModuleDeclaration
}
if (!nodeByType.has(122)) {
    nodeByType.set(122, TSModuleDeclaration)
}