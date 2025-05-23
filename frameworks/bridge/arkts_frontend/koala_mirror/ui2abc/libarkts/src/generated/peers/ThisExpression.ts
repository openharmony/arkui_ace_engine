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
export class ThisExpression extends Expression {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 144)
        super(pointer)
    }
    static createThisExpression(): ThisExpression {
        return new ThisExpression(global.generatedEs2panda._CreateThisExpression(global.context))
    }
    static updateThisExpression(original?: ThisExpression): ThisExpression {
        return new ThisExpression(global.generatedEs2panda._UpdateThisExpression(global.context, passNode(original)))
    }
}
export function isThisExpression(node: object | undefined): node is ThisExpression {
    return node instanceof ThisExpression
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_THIS_EXPRESSION)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_THIS_EXPRESSION, (peer: KNativePointer) => new ThisExpression(peer))
}