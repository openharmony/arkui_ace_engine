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
export class ForUpdateStatement extends LoopStatement {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 33)
        super(pointer)
        console.warn("Warning: stub node ForUpdateStatement")
    }
    static createForUpdateStatement(init?: AstNode, test?: Expression, update?: Expression, body?: Statement): ForUpdateStatement {
        return new ForUpdateStatement(global.generatedEs2panda._CreateForUpdateStatement(global.context, passNode(init), passNode(test), passNode(update), passNode(body)))
    }
    get init(): AstNode | undefined {
        return unpackNode(global.generatedEs2panda._ForUpdateStatementInitConst(global.context, this.peer))
    }
    get test(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._ForUpdateStatementTestConst(global.context, this.peer))
    }
    get update(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._ForUpdateStatementUpdateConst(global.context, this.peer))
    }
    get body(): Statement | undefined {
        return unpackNode(global.generatedEs2panda._ForUpdateStatementBodyConst(global.context, this.peer))
    }
}
export function isForUpdateStatement(node: AstNode): node is ForUpdateStatement {
    return node instanceof ForUpdateStatement
}
if (!nodeByType.has(33)) {
    nodeByType.set(33, ForUpdateStatement)
}