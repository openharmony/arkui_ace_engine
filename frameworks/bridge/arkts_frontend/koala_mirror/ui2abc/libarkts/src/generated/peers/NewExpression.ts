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
export class NewExpression extends Expression {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 49)
        super(pointer)
    }
    static createNewExpression(callee: Expression | undefined, _arguments: readonly Expression[]): NewExpression {
        return new NewExpression(global.generatedEs2panda._CreateNewExpression(global.context, passNode(callee), passNodeArray(_arguments), _arguments.length))
    }
    static updateNewExpression(original: NewExpression | undefined, callee: Expression | undefined, _arguments: readonly Expression[]): NewExpression {
        return new NewExpression(global.generatedEs2panda._UpdateNewExpression(global.context, passNode(original), passNode(callee), passNodeArray(_arguments), _arguments.length))
    }
    get callee(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._NewExpressionCalleeConst(global.context, this.peer))
    }
    get arguments(): readonly Expression[] {
        return unpackNodeArray(global.generatedEs2panda._NewExpressionArgumentsConst(global.context, this.peer))
    }
}
export function isNewExpression(node: object | undefined): node is NewExpression {
    return node instanceof NewExpression
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_NEW_EXPRESSION)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_NEW_EXPRESSION, (peer: KNativePointer) => new NewExpression(peer))
}