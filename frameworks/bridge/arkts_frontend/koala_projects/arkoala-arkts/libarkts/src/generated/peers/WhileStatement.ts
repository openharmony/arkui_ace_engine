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

import { LoopStatement } from "./LoopStatement"
import { Expression } from "./Expression"
import { Statement } from "./Statement"
export class WhileStatement extends LoopStatement {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 151)
        super(pointer)
        console.warn("Warning: stub node WhileStatement")
    }
    static createWhileStatement(test?: Expression, body?: Statement): WhileStatement {
        return new WhileStatement(global.generatedEs2panda._CreateWhileStatement(global.context, passNode(test), passNode(body)))
    }
    static updateWhileStatement(original?: WhileStatement, test?: Expression, body?: Statement): WhileStatement {
        return new WhileStatement(global.generatedEs2panda._UpdateWhileStatement(global.context, passNode(original), passNode(test), passNode(body)))
    }
    get test(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._WhileStatementTestConst(global.context, this.peer))
    }
    get body(): Statement | undefined {
        return unpackNode(global.generatedEs2panda._WhileStatementBodyConst(global.context, this.peer))
    }
}
export function isWhileStatement(node: AstNode): node is WhileStatement {
    return node instanceof WhileStatement
}
if (!nodeByType.has(151)) {
    nodeByType.set(151, WhileStatement)
}