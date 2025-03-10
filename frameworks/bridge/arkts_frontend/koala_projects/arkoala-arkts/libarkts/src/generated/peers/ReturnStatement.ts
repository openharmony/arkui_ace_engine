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
export class ReturnStatement extends Statement {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 58)
        super(pointer)
        console.warn("Warning: stub node ReturnStatement")
    }
    static createReturnStatement(): ReturnStatement {
        return new ReturnStatement(global.generatedEs2panda._CreateReturnStatement(global.context))
    }
    static updateReturnStatement(original?: ReturnStatement): ReturnStatement {
        return new ReturnStatement(global.generatedEs2panda._UpdateReturnStatement(global.context, passNode(original)))
    }
    static create1ReturnStatement(argument?: Expression): ReturnStatement {
        return new ReturnStatement(global.generatedEs2panda._CreateReturnStatement1(global.context, passNode(argument)))
    }
    static update1ReturnStatement(original?: ReturnStatement, argument?: Expression): ReturnStatement {
        return new ReturnStatement(global.generatedEs2panda._UpdateReturnStatement1(global.context, passNode(original), passNode(argument)))
    }
    get argument(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._ReturnStatementArgumentConst(global.context, this.peer))
    }
    /** @deprecated */
    setArgument(arg: Expression): this {
        global.generatedEs2panda._ReturnStatementSetArgument(global.context, this.peer, passNode(arg))
        return this
    }
}
export function isReturnStatement(node: AstNode): node is ReturnStatement {
    return node instanceof ReturnStatement
}
if (!nodeByType.has(58)) {
    nodeByType.set(58, ReturnStatement)
}