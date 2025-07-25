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
import { Es2pandaTokenType } from "./../Es2pandaEnums"
import { Expression } from "./Expression"
export class UpdateExpression extends Expression {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 149)
        super(pointer)
    }
    static createUpdateExpression(argument: Expression | undefined, updateOperator: Es2pandaTokenType, isPrefix: boolean): UpdateExpression {
        return new UpdateExpression(global.generatedEs2panda._CreateUpdateExpression(global.context, passNode(argument), updateOperator, isPrefix))
    }
    static updateUpdateExpression(original: UpdateExpression | undefined, argument: Expression | undefined, updateOperator: Es2pandaTokenType, isPrefix: boolean): UpdateExpression {
        return new UpdateExpression(global.generatedEs2panda._UpdateUpdateExpression(global.context, passNode(original), passNode(argument), updateOperator, isPrefix))
    }
    get operatorType(): Es2pandaTokenType {
        return global.generatedEs2panda._UpdateExpressionOperatorTypeConst(global.context, this.peer)
    }
    get argument(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._UpdateExpressionArgument(global.context, this.peer))
    }
    get isPrefix(): boolean {
        return global.generatedEs2panda._UpdateExpressionIsPrefixConst(global.context, this.peer)
    }
}
export function isUpdateExpression(node: object | undefined): node is UpdateExpression {
    return node instanceof UpdateExpression
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_UPDATE_EXPRESSION)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_UPDATE_EXPRESSION, (peer: KNativePointer) => new UpdateExpression(peer))
}