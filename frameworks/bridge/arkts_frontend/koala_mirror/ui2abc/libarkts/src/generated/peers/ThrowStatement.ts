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
import { Expression } from "./Expression"
import { Statement } from "./Statement"
export class ThrowStatement extends Statement {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 146)
        super(pointer)
    }
    static createThrowStatement(argument?: Expression): ThrowStatement {
        return new ThrowStatement(global.generatedEs2panda._CreateThrowStatement(global.context, passNode(argument)))
    }
    static updateThrowStatement(original?: ThrowStatement, argument?: Expression): ThrowStatement {
        return new ThrowStatement(global.generatedEs2panda._UpdateThrowStatement(global.context, passNode(original), passNode(argument)))
    }
    get argument(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._ThrowStatementArgumentConst(global.context, this.peer))
    }
}
export function isThrowStatement(node: object | undefined): node is ThrowStatement {
    return node instanceof ThrowStatement
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_THROW_STATEMENT)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_THROW_STATEMENT, (peer: KNativePointer) => new ThrowStatement(peer))
}