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
export class BlockStatement extends Statement {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 7)
        super(pointer)
        console.warn("Warning: stub node BlockStatement")
    }
    static createBlockStatement(statementList: readonly Statement[]): BlockStatement {
        return new BlockStatement(global.generatedEs2panda._CreateBlockStatement(global.context, passNodeArray(statementList), statementList.length))
    }
    static updateBlockStatement(original: BlockStatement | undefined, statementList: readonly Statement[]): BlockStatement {
        return new BlockStatement(global.generatedEs2panda._UpdateBlockStatement(global.context, passNode(original), passNodeArray(statementList), statementList.length))
    }
    get statements(): readonly Statement[] {
        return unpackNodeArray(global.generatedEs2panda._BlockStatementStatementsConst(global.context, this.peer))
    }
    /** @deprecated */
    setStatements(statementList: readonly Statement[]): this {
        global.generatedEs2panda._BlockStatementSetStatements(global.context, this.peer, passNodeArray(statementList), statementList.length)
        return this
    }
    /** @deprecated */
    addTrailingBlock(stmt: AstNode, trailingBlock: BlockStatement): this {
        global.generatedEs2panda._BlockStatementAddTrailingBlock(global.context, this.peer, passNode(stmt), passNode(trailingBlock))
        return this
    }
}
export function isBlockStatement(node: AstNode): node is BlockStatement {
    return node instanceof BlockStatement
}
if (!nodeByType.has(7)) {
    nodeByType.set(7, BlockStatement)
}