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

import { Expression } from "./Expression"
export class SequenceExpression extends Expression {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 60)
        super(pointer)
        console.warn("Warning: stub node SequenceExpression")
    }
    static createSequenceExpression(sequence_arg: readonly Expression[]): SequenceExpression {
        return new SequenceExpression(global.generatedEs2panda._CreateSequenceExpression(global.context, passNodeArray(sequence_arg), sequence_arg.length))
    }
    static updateSequenceExpression(original: SequenceExpression | undefined, sequence_arg: readonly Expression[]): SequenceExpression {
        return new SequenceExpression(global.generatedEs2panda._UpdateSequenceExpression(global.context, passNode(original), passNodeArray(sequence_arg), sequence_arg.length))
    }
    get sequence(): readonly Expression[] {
        return unpackNodeArray(global.generatedEs2panda._SequenceExpressionSequenceConst(global.context, this.peer))
    }
}
export function isSequenceExpression(node: AstNode): node is SequenceExpression {
    return node instanceof SequenceExpression
}
if (!nodeByType.has(60)) {
    nodeByType.set(60, SequenceExpression)
}