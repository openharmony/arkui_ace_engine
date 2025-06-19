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

import { Literal } from "./Literal"
export class NullLiteral extends Literal {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 50)
        super(pointer)
        console.warn("Warning: stub node NullLiteral")
    }
    static createNullLiteral(): NullLiteral {
        return new NullLiteral(global.generatedEs2panda._CreateNullLiteral(global.context))
    }
    static updateNullLiteral(original?: NullLiteral): NullLiteral {
        return new NullLiteral(global.generatedEs2panda._UpdateNullLiteral(global.context, passNode(original)))
    }
}
export function isNullLiteral(node: AstNode): node is NullLiteral {
    return node instanceof NullLiteral
}
if (!nodeByType.has(50)) {
    nodeByType.set(50, NullLiteral)
}