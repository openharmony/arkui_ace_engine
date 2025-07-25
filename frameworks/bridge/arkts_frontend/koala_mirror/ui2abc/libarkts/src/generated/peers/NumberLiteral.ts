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
import { Literal } from "./Literal"
export class NumberLiteral extends Literal {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 52)
        super(pointer)
    }
    static createNumberLiteral(value: number): AstNode {
        return new NumberLiteral(global.generatedEs2panda._CreateNumberLiteral(global.context, value))
    }
    static updateNumberLiteral(original: AstNode | undefined, value: number): AstNode {
        return new NumberLiteral(global.generatedEs2panda._UpdateNumberLiteral(global.context, passNode(original), value))
    }
    static update1NumberLiteral(original: AstNode | undefined, value: number): AstNode {
        return new NumberLiteral(global.generatedEs2panda._UpdateNumberLiteral1(global.context, passNode(original), value))
    }
    static update2NumberLiteral(original: AstNode | undefined, value: number): AstNode {
        return new NumberLiteral(global.generatedEs2panda._UpdateNumberLiteral2(global.context, passNode(original), value))
    }
    static update3NumberLiteral(original: AstNode | undefined, value: number): AstNode {
        return new NumberLiteral(global.generatedEs2panda._UpdateNumberLiteral3(global.context, passNode(original), value))
    }
    get str(): string {
        return unpackString(global.generatedEs2panda._NumberLiteralStrConst(global.context, this.peer))
    }
}
export function isNumberLiteral(node: object | undefined): node is NumberLiteral {
    return node instanceof NumberLiteral
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_NUMBER_LITERAL)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_NUMBER_LITERAL, (peer: KNativePointer) => new NumberLiteral(peer))
}