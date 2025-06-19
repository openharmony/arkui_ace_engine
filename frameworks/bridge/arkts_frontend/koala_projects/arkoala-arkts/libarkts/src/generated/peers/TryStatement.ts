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
import { BlockStatement } from "./BlockStatement"
import { CatchClause } from "./CatchClause"
export class TryStatement extends Statement {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 146)
        super(pointer)
        console.warn("Warning: stub node TryStatement")
    }
    get finallyBlock(): BlockStatement | undefined {
        return unpackNode(global.generatedEs2panda._TryStatementFinallyBlockConst(global.context, this.peer))
    }
    get block(): BlockStatement | undefined {
        return unpackNode(global.generatedEs2panda._TryStatementBlockConst(global.context, this.peer))
    }
    get hasFinalizer(): boolean {
        return global.generatedEs2panda._TryStatementHasFinalizerConst(global.context, this.peer)
    }
    get catchClauses(): readonly CatchClause[] {
        return unpackNodeArray(global.generatedEs2panda._TryStatementCatchClausesConst(global.context, this.peer))
    }
    get finallyCanCompleteNormally(): boolean {
        return global.generatedEs2panda._TryStatementFinallyCanCompleteNormallyConst(global.context, this.peer)
    }
    /** @deprecated */
    setFinallyCanCompleteNormally(finallyCanCompleteNormally: boolean): this {
        global.generatedEs2panda._TryStatementSetFinallyCanCompleteNormally(global.context, this.peer, finallyCanCompleteNormally)
        return this
    }
}
export function isTryStatement(node: AstNode): node is TryStatement {
    return node instanceof TryStatement
}
if (!nodeByType.has(146)) {
    nodeByType.set(146, TryStatement)
}