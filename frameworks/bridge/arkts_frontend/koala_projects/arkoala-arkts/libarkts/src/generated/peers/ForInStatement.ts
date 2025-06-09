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
export class ForInStatement extends LoopStatement {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 31)
        super(pointer)
        console.warn("Warning: stub node ForInStatement")
    }
    static createForInStatement(left?: AstNode, right?: Expression, body?: Statement): ForInStatement {
        return new ForInStatement(global.generatedEs2panda._CreateForInStatement(global.context, passNode(left), passNode(right), passNode(body)))
    }
    static updateForInStatement(original?: ForInStatement, left?: AstNode, right?: Expression, body?: Statement): ForInStatement {
        return new ForInStatement(global.generatedEs2panda._UpdateForInStatement(global.context, passNode(original), passNode(left), passNode(right), passNode(body)))
    }
    get left(): AstNode | undefined {
        return unpackNode(global.generatedEs2panda._ForInStatementLeftConst(global.context, this.peer))
    }
    get right(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._ForInStatementRightConst(global.context, this.peer))
    }
    get body(): Statement | undefined {
        return unpackNode(global.generatedEs2panda._ForInStatementBodyConst(global.context, this.peer))
    }
}
export function isForInStatement(node: AstNode): node is ForInStatement {
    return node instanceof ForInStatement
}
if (!nodeByType.has(31)) {
    nodeByType.set(31, ForInStatement)
}