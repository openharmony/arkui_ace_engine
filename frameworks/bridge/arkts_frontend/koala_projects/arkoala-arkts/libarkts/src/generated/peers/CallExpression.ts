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

import { MaybeOptionalExpression } from "./MaybeOptionalExpression"
import { Expression } from "./Expression"
import { TSTypeParameterInstantiation } from "./TSTypeParameterInstantiation"
import { BlockStatement } from "./BlockStatement"
export class CallExpression extends MaybeOptionalExpression {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 10)
        super(pointer)
        console.warn("Warning: stub node CallExpression")
    }
    static createCallExpression(callee: Expression | undefined, _arguments: readonly Expression[], typeParams: TSTypeParameterInstantiation | undefined, optional_arg: boolean, trailingComma: boolean): CallExpression {
        return new CallExpression(global.generatedEs2panda._CreateCallExpression(global.context, passNode(callee), passNodeArray(_arguments), _arguments.length, passNode(typeParams), optional_arg, trailingComma))
    }
    static create1CallExpression(other?: CallExpression): CallExpression {
        return new CallExpression(global.generatedEs2panda._CreateCallExpression1(global.context, passNode(other)))
    }
    static update1CallExpression(original?: CallExpression, other?: CallExpression): CallExpression {
        return new CallExpression(global.generatedEs2panda._UpdateCallExpression1(global.context, passNode(original), passNode(other)))
    }
    get callee(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._CallExpressionCalleeConst(global.context, this.peer))
    }
    /** @deprecated */
    setCallee(callee: Expression): this {
        global.generatedEs2panda._CallExpressionSetCallee(global.context, this.peer, passNode(callee))
        return this
    }
    get typeParams(): TSTypeParameterInstantiation | undefined {
        return unpackNode(global.generatedEs2panda._CallExpressionTypeParamsConst(global.context, this.peer))
    }
    get arguments(): readonly Expression[] {
        return unpackNodeArray(global.generatedEs2panda._CallExpressionArgumentsConst(global.context, this.peer))
    }
    get hasTrailingComma(): boolean {
        return global.generatedEs2panda._CallExpressionHasTrailingCommaConst(global.context, this.peer)
    }
    /** @deprecated */
    setTypeParams(typeParams: TSTypeParameterInstantiation): this {
        global.generatedEs2panda._CallExpressionSetTypeParams(global.context, this.peer, passNode(typeParams))
        return this
    }
    /** @deprecated */
    setTrailingBlock(block: BlockStatement): this {
        global.generatedEs2panda._CallExpressionSetTrailingBlock(global.context, this.peer, passNode(block))
        return this
    }
    get trailingBlock(): BlockStatement | undefined {
        return unpackNode(global.generatedEs2panda._CallExpressionTrailingBlockConst(global.context, this.peer))
    }
    /** @deprecated */
    setIsTrailingBlockInNewLine(isNewLine: boolean): this {
        global.generatedEs2panda._CallExpressionSetIsTrailingBlockInNewLine(global.context, this.peer, isNewLine)
        return this
    }
    get isTrailingBlockInNewLine(): boolean {
        return global.generatedEs2panda._CallExpressionIsTrailingBlockInNewLineConst(global.context, this.peer)
    }
    get isETSConstructorCall(): boolean {
        return global.generatedEs2panda._CallExpressionIsETSConstructorCallConst(global.context, this.peer)
    }
}
export function isCallExpression(node: AstNode): node is CallExpression {
    return node instanceof CallExpression
}
if (!nodeByType.has(10)) {
    nodeByType.set(10, CallExpression)
}