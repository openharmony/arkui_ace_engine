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

import { CallExpression } from "./CallExpression"
import { Expression } from "./Expression"
import { TSTypeParameterInstantiation } from "./TSTypeParameterInstantiation"
export class DirectEvalExpression extends CallExpression {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 23)
        super(pointer)
        console.warn("Warning: stub node DirectEvalExpression")
    }
    static createDirectEvalExpression(callee: Expression | undefined, _arguments: readonly Expression[], typeParams: TSTypeParameterInstantiation | undefined, optional_arg: boolean, parserStatus: number): DirectEvalExpression {
        return new DirectEvalExpression(global.generatedEs2panda._CreateDirectEvalExpression(global.context, passNode(callee), passNodeArray(_arguments), _arguments.length, passNode(typeParams), optional_arg, parserStatus))
    }
    static updateDirectEvalExpression(original: DirectEvalExpression | undefined, callee: Expression | undefined, _arguments: readonly Expression[], typeParams: TSTypeParameterInstantiation | undefined, optional_arg: boolean, parserStatus: number): DirectEvalExpression {
        return new DirectEvalExpression(global.generatedEs2panda._UpdateDirectEvalExpression(global.context, passNode(original), passNode(callee), passNodeArray(_arguments), _arguments.length, passNode(typeParams), optional_arg, parserStatus))
    }
}
export function isDirectEvalExpression(node: AstNode): node is DirectEvalExpression {
    return node instanceof DirectEvalExpression
}
if (!nodeByType.has(23)) {
    nodeByType.set(23, DirectEvalExpression)
}