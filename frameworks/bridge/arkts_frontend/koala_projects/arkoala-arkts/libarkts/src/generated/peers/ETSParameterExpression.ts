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
import { AnnotatedExpression } from "./AnnotatedExpression"
import { Identifier } from "./Identifier"
import { SpreadElement } from "./SpreadElement"
import { TypeNode } from "./TypeNode"
import { AnnotationUsage } from "./AnnotationUsage"
export class ETSParameterExpression extends Expression {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 79)
        super(pointer)
        console.warn("Warning: stub node ETSParameterExpression")
    }
    static createETSParameterExpression(identOrSpread: AnnotatedExpression | undefined, isOptional: boolean): ETSParameterExpression {
        return new ETSParameterExpression(global.generatedEs2panda._CreateETSParameterExpression(global.context, passNode(identOrSpread), isOptional))
    }
    static updateETSParameterExpression(original: ETSParameterExpression | undefined, identOrSpread: AnnotatedExpression | undefined, isOptional: boolean): ETSParameterExpression {
        return new ETSParameterExpression(global.generatedEs2panda._UpdateETSParameterExpression(global.context, passNode(original), passNode(identOrSpread), isOptional))
    }
    static create1ETSParameterExpression(identOrSpread?: AnnotatedExpression, initializer?: Expression): ETSParameterExpression {
        return new ETSParameterExpression(global.generatedEs2panda._CreateETSParameterExpression1(global.context, passNode(identOrSpread), passNode(initializer)))
    }
    static update1ETSParameterExpression(original?: ETSParameterExpression, identOrSpread?: AnnotatedExpression, initializer?: Expression): ETSParameterExpression {
        return new ETSParameterExpression(global.generatedEs2panda._UpdateETSParameterExpression1(global.context, passNode(original), passNode(identOrSpread), passNode(initializer)))
    }
    /** @deprecated */
    setIdent(ident: Identifier): this {
        global.generatedEs2panda._ETSParameterExpressionSetIdent(global.context, this.peer, passNode(ident))
        return this
    }
    /** @deprecated */
    setLexerSaved(s: string): this {
        global.generatedEs2panda._ETSParameterExpressionSetLexerSaved(global.context, this.peer, s)
        return this
    }
    /** @deprecated */
    setTypeAnnotation(typeNode: TypeNode): this {
        global.generatedEs2panda._ETSParameterExpressionSetTypeAnnotation(global.context, this.peer, passNode(typeNode))
        return this
    }
    get isOptional(): boolean {
        return global.generatedEs2panda._ETSParameterExpressionIsOptionalConst(global.context, this.peer)
    }
    /** @deprecated */
    setOptional(value: boolean): this {
        global.generatedEs2panda._ETSParameterExpressionSetOptional(global.context, this.peer, value)
        return this
    }
    /** @deprecated */
    setInitializer(initExpr: Expression): this {
        global.generatedEs2panda._ETSParameterExpressionSetInitializer(global.context, this.peer, passNode(initExpr))
        return this
    }
    get isRestParameter(): boolean {
        return global.generatedEs2panda._ETSParameterExpressionIsRestParameterConst(global.context, this.peer)
    }
    get getRequiredParams(): number {
        return global.generatedEs2panda._ETSParameterExpressionGetRequiredParamsConst(global.context, this.peer)
    }
    /** @deprecated */
    setRequiredParams(value: number): this {
        global.generatedEs2panda._ETSParameterExpressionSetRequiredParams(global.context, this.peer, value)
        return this
    }
    get annotations(): readonly AnnotationUsage[] {
        return unpackNodeArray(global.generatedEs2panda._ETSParameterExpressionAnnotationsConst(global.context, this.peer))
    }
    /** @deprecated */
    setAnnotations(annotations: readonly AnnotationUsage[]): this {
        global.generatedEs2panda._ETSParameterExpressionSetAnnotations(global.context, this.peer, passNodeArray(annotations), annotations.length)
        return this
    }
}
export function isETSParameterExpression(node: AstNode): node is ETSParameterExpression {
    return node instanceof ETSParameterExpression
}
if (!nodeByType.has(79)) {
    nodeByType.set(79, ETSParameterExpression)
}