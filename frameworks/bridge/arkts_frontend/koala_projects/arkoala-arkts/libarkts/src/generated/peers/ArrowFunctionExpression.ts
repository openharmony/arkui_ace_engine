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
import { ScriptFunction } from "./ScriptFunction"
import { TypeNode } from "./TypeNode"
import { AnnotationUsage } from "./AnnotationUsage"
export class ArrowFunctionExpression extends Expression {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 0)
        super(pointer)
        console.warn("Warning: stub node ArrowFunctionExpression")
    }
    static createArrowFunctionExpression(func?: ScriptFunction): ArrowFunctionExpression {
        return new ArrowFunctionExpression(global.generatedEs2panda._CreateArrowFunctionExpression(global.context, passNode(func)))
    }
    static updateArrowFunctionExpression(original?: ArrowFunctionExpression, func?: ScriptFunction): ArrowFunctionExpression {
        return new ArrowFunctionExpression(global.generatedEs2panda._UpdateArrowFunctionExpression(global.context, passNode(original), passNode(func)))
    }
    static create1ArrowFunctionExpression(other?: ArrowFunctionExpression): ArrowFunctionExpression {
        return new ArrowFunctionExpression(global.generatedEs2panda._CreateArrowFunctionExpression1(global.context, passNode(other)))
    }
    static update1ArrowFunctionExpression(original?: ArrowFunctionExpression, other?: ArrowFunctionExpression): ArrowFunctionExpression {
        return new ArrowFunctionExpression(global.generatedEs2panda._UpdateArrowFunctionExpression1(global.context, passNode(original), passNode(other)))
    }
    get function(): ScriptFunction | undefined {
        return unpackNode(global.generatedEs2panda._ArrowFunctionExpressionFunctionConst(global.context, this.peer))
    }
    get annotations(): readonly AnnotationUsage[] {
        return unpackNodeArray(global.generatedEs2panda._ArrowFunctionExpressionAnnotationsConst(global.context, this.peer))
    }
    /** @deprecated */
    setAnnotations(annotations: readonly AnnotationUsage[]): this {
        global.generatedEs2panda._ArrowFunctionExpressionSetAnnotations(global.context, this.peer, passNodeArray(annotations), annotations.length)
        return this
    }
}
export function isArrowFunctionExpression(node: AstNode): node is ArrowFunctionExpression {
    return node instanceof ArrowFunctionExpression
}
if (!nodeByType.has(0)) {
    nodeByType.set(0, ArrowFunctionExpression)
}