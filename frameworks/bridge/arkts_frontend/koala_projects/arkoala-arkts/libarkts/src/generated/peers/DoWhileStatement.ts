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
import { Statement } from "./Statement"
import { Expression } from "./Expression"
export class DoWhileStatement extends LoopStatement {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 24)
        super(pointer)
        console.warn("Warning: stub node DoWhileStatement")
    }
    static createDoWhileStatement(body?: Statement, test?: Expression): DoWhileStatement {
        return new DoWhileStatement(global.generatedEs2panda._CreateDoWhileStatement(global.context, passNode(body), passNode(test)))
    }
    static updateDoWhileStatement(original?: DoWhileStatement, body?: Statement, test?: Expression): DoWhileStatement {
        return new DoWhileStatement(global.generatedEs2panda._UpdateDoWhileStatement(global.context, passNode(original), passNode(body), passNode(test)))
    }
    get body(): Statement | undefined {
        return unpackNode(global.generatedEs2panda._DoWhileStatementBodyConst(global.context, this.peer))
    }
    get test(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._DoWhileStatementTestConst(global.context, this.peer))
    }
}
export function isDoWhileStatement(node: AstNode): node is DoWhileStatement {
    return node instanceof DoWhileStatement
}
if (!nodeByType.has(24)) {
    nodeByType.set(24, DoWhileStatement)
}