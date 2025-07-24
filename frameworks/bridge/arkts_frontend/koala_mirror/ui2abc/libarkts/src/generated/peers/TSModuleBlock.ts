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
export class TSModuleBlock extends Statement {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 115)
        super(pointer)
    }
    static createTSModuleBlock(statements: readonly Statement[]): TSModuleBlock {
        return new TSModuleBlock(global.generatedEs2panda._CreateTSModuleBlock(global.context, passNodeArray(statements), statements.length))
    }
    static updateTSModuleBlock(original: TSModuleBlock | undefined, statements: readonly Statement[]): TSModuleBlock {
        return new TSModuleBlock(global.generatedEs2panda._UpdateTSModuleBlock(global.context, passNode(original), passNodeArray(statements), statements.length))
    }
    get statements(): readonly Statement[] {
        return unpackNodeArray(global.generatedEs2panda._TSModuleBlockStatementsConst(global.context, this.peer))
    }
}
export function isTSModuleBlock(node: object | undefined): node is TSModuleBlock {
    return node instanceof TSModuleBlock
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_TS_MODULE_BLOCK)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_TS_MODULE_BLOCK, (peer: KNativePointer) => new TSModuleBlock(peer))
}