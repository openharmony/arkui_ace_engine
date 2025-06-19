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

import { TypedAstNode } from "./TypedAstNode"
import { Literal } from "./Literal"
import { TypeNode } from "./TypeNode"
import { AnnotatedExpression } from "./AnnotatedExpression"
export class Expression extends TypedAstNode {
     constructor(pointer: KNativePointer) {
        super(pointer)
        console.warn("Warning: stub node Expression")
    }
    get isGrouped(): boolean {
        return global.generatedEs2panda._ExpressionIsGroupedConst(global.context, this.peer)
    }
    /** @deprecated */
    setGrouped(): this {
        global.generatedEs2panda._ExpressionSetGrouped(global.context, this.peer)
        return this
    }
    get isLiteral(): boolean {
        return global.generatedEs2panda._ExpressionIsLiteralConst(global.context, this.peer)
    }
    get isTypeNode(): boolean {
        return global.generatedEs2panda._ExpressionIsTypeNodeConst(global.context, this.peer)
    }
    get isAnnotatedExpression(): boolean {
        return global.generatedEs2panda._ExpressionIsAnnotatedExpressionConst(global.context, this.peer)
    }
}
export function isExpression(node: AstNode): node is Expression {
    return node instanceof Expression
}