/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

import * as ts from '@koalaui/ets-tsc'
import { AbstractVisitor } from "./AbstractVisitor"
import { asString, CallTable, isBuilder, isGlobalBuilder, prependMemoComment } from './utils'
import { Void, getDeclarationsByNode, prependComment } from './ApiUtils'


export class CustomBuilderTransformer extends AbstractVisitor {

    public globalFunctions: string[] = []

	constructor(
		sourceFile: ts.SourceFile,
        ctx: ts.TransformationContext,
        private typechecker: ts.TypeChecker,
        private callTable: CallTable
	) {
        super(sourceFile, ctx)
    }

    refersToGlobalBuilder(call: ts.CallExpression): boolean {
        const originalCall = ts.getOriginalNode(call) as ts.CallExpression
        return this.callTable.globalBuilderCalls.has(originalCall)
    }

    refersToBuilderMethod(callee: ts.Expression): boolean {
        if (ts.isPropertyAccessExpression(callee)) {
            const declarations = getDeclarationsByNode(this.typechecker, callee.name)
            if (declarations.length == 0) return false
            const firstDeclaration = declarations[0]
            if (ts.isMethodDeclaration(firstDeclaration) &&
                isBuilder(firstDeclaration)
            ) return true
        }
        return false
    }

    isBuilderCall(node: ts.CallExpression): boolean {
        const callee = node.expression
        return this.refersToBuilderMethod(callee) ||
               this.refersToGlobalBuilder(node)
    }

    parentIsStatement(node: ts.CallExpression) {
        const original = ts.getOriginalNode(node)
        return (ts.isExpressionStatement(original.parent) || !original.parent)
    }

    private wrapInMemoLambda(node: ts.CallExpression): ts.Expression {
        const lambda = ts.factory.createArrowFunction(
            undefined,
            undefined,
            [],
            Void(),
            ts.factory.createToken(ts.SyntaxKind.EqualsGreaterThanToken),
            node
        )
        return prependMemoComment(
            // This is an expression so make sure memo is a separate line
            prependComment(lambda, " ")
        )
    }

    private wrapPropertyInMemoLambdaCall(node: ts.PropertyAccessExpression): ts.Expression {
        const lambda = ts.factory.createArrowFunction(
            undefined,
            undefined,
            [],
            undefined,
            ts.factory.createToken(ts.SyntaxKind.EqualsGreaterThanToken),
            ts.factory.createCallExpression(node, undefined, undefined)
        )
        return prependMemoComment(
            // This is an expression so make sure memo is a separate line
            prependComment(lambda, " ")
        )
    }

    visitor(beforeChildren: ts.Node): ts.Node {
        const node = this.visitEachChild(beforeChildren)

        if (ts.isCallExpression(node) &&
            this.isBuilderCall(node) &&
            !this.parentIsStatement(node)
        ) {
            return this.wrapInMemoLambda(node)
        }

        return node
    }
}
