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
export class TSNonNullExpression extends Expression {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 99)
        super(pointer)
        console.warn("Warning: stub node TSNonNullExpression")
    }
    static createTSNonNullExpression(expr?: Expression): TSNonNullExpression {
        return new TSNonNullExpression(global.generatedEs2panda._CreateTSNonNullExpression(global.context, passNode(expr)))
    }
    static updateTSNonNullExpression(original?: TSNonNullExpression, expr?: Expression): TSNonNullExpression {
        return new TSNonNullExpression(global.generatedEs2panda._UpdateTSNonNullExpression(global.context, passNode(original), passNode(expr)))
    }
    get expr(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._TSNonNullExpressionExprConst(global.context, this.peer))
    }
    /** @deprecated */
    setExpr(expr: Expression): this {
        global.generatedEs2panda._TSNonNullExpressionSetExpr(global.context, this.peer, passNode(expr))
        return this
    }
}
export function isTSNonNullExpression(node: AstNode): node is TSNonNullExpression {
    return node instanceof TSNonNullExpression
}
if (!nodeByType.has(99)) {
    nodeByType.set(99, TSNonNullExpression)
}