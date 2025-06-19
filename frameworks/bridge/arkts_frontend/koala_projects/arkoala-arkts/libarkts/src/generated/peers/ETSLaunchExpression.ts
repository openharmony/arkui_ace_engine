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
import { CallExpression } from "./CallExpression"
export class ETSLaunchExpression extends Expression {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 74)
        super(pointer)
        console.warn("Warning: stub node ETSLaunchExpression")
    }
    static createETSLaunchExpression(expr?: CallExpression): ETSLaunchExpression {
        return new ETSLaunchExpression(global.generatedEs2panda._CreateETSLaunchExpression(global.context, passNode(expr)))
    }
    static updateETSLaunchExpression(original?: ETSLaunchExpression, expr?: CallExpression): ETSLaunchExpression {
        return new ETSLaunchExpression(global.generatedEs2panda._UpdateETSLaunchExpression(global.context, passNode(original), passNode(expr)))
    }
    get call(): CallExpression | undefined {
        return unpackNode(global.generatedEs2panda._ETSLaunchExpressionCallConst(global.context, this.peer))
    }
}
export function isETSLaunchExpression(node: AstNode): node is ETSLaunchExpression {
    return node instanceof ETSLaunchExpression
}
if (!nodeByType.has(74)) {
    nodeByType.set(74, ETSLaunchExpression)
}