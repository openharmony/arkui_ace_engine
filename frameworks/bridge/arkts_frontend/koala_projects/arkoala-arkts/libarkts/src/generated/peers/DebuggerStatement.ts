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
export class DebuggerStatement extends Statement {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 21)
        super(pointer)
        console.warn("Warning: stub node DebuggerStatement")
    }
    static createDebuggerStatement(): DebuggerStatement {
        return new DebuggerStatement(global.generatedEs2panda._CreateDebuggerStatement(global.context))
    }
    static updateDebuggerStatement(original?: DebuggerStatement): DebuggerStatement {
        return new DebuggerStatement(global.generatedEs2panda._UpdateDebuggerStatement(global.context, passNode(original)))
    }
}
export function isDebuggerStatement(node: AstNode): node is DebuggerStatement {
    return node instanceof DebuggerStatement
}
if (!nodeByType.has(21)) {
    nodeByType.set(21, DebuggerStatement)
}