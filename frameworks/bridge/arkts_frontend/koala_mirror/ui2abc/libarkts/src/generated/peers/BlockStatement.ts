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
export class BlockStatement extends Statement {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 7)
        super(pointer)
    }
    static createBlockStatement(statementList: readonly Statement[]): BlockStatement {
        return new BlockStatement(global.generatedEs2panda._CreateBlockStatement(global.context, passNodeArray(statementList), statementList.length))
    }
    static updateBlockStatement(original: BlockStatement | undefined, statementList: readonly Statement[]): BlockStatement {
        return new BlockStatement(global.generatedEs2panda._UpdateBlockStatement(global.context, passNode(original), passNodeArray(statementList), statementList.length))
    }
    get statements(): readonly Statement[] {
        return unpackNodeArray(global.generatedEs2panda._BlockStatementStatements(global.context, this.peer))
    }
    /** @deprecated */
    setStatements(statementList: readonly Statement[]): this {
        global.generatedEs2panda._BlockStatementSetStatements(global.context, this.peer, passNodeArray(statementList), statementList.length)
        return this
    }
    /** @deprecated */
    addStatement(stmt?: Statement): this {
        global.generatedEs2panda._BlockStatementAddStatement(global.context, this.peer, passNode(stmt))
        return this
    }
    /** @deprecated */
    addStatements(stmts: readonly Statement[]): this {
        global.generatedEs2panda._BlockStatementAddStatements(global.context, this.peer, passNodeArray(stmts), stmts.length)
        return this
    }
    /** @deprecated */
    addTrailingBlock(stmt?: AstNode, trailingBlock?: BlockStatement): this {
        global.generatedEs2panda._BlockStatementAddTrailingBlock(global.context, this.peer, passNode(stmt), passNode(trailingBlock))
        return this
    }
}
export function isBlockStatement(node: object | undefined): node is BlockStatement {
    return node instanceof BlockStatement
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_BLOCK_STATEMENT)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_BLOCK_STATEMENT, (peer: KNativePointer) => new BlockStatement(peer))
}