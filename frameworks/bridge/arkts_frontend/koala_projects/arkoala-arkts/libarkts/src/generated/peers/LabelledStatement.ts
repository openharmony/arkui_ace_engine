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
import { Identifier } from "./Identifier"
export class LabelledStatement extends Statement {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 44)
        super(pointer)
        console.warn("Warning: stub node LabelledStatement")
    }
    static createLabelledStatement(ident?: Identifier, body?: Statement): LabelledStatement {
        return new LabelledStatement(global.generatedEs2panda._CreateLabelledStatement(global.context, passNode(ident), passNode(body)))
    }
    static updateLabelledStatement(original?: LabelledStatement, ident?: Identifier, body?: Statement): LabelledStatement {
        return new LabelledStatement(global.generatedEs2panda._UpdateLabelledStatement(global.context, passNode(original), passNode(ident), passNode(body)))
    }
    get body(): Statement | undefined {
        return unpackNode(global.generatedEs2panda._LabelledStatementBodyConst(global.context, this.peer))
    }
    get ident(): Identifier | undefined {
        return unpackNode(global.generatedEs2panda._LabelledStatementIdentConst(global.context, this.peer))
    }
}
export function isLabelledStatement(node: AstNode): node is LabelledStatement {
    return node instanceof LabelledStatement
}
if (!nodeByType.has(44)) {
    nodeByType.set(44, LabelledStatement)
}