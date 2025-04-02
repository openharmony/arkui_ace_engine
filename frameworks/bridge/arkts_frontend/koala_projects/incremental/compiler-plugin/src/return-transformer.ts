/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

import * as ts from '@koalaui/ets-tsc';
import { ScopedVisitor } from "./ScopedVisitor"
import { FunctionKind, isFunctionOrMethod, isMemoKind, isThis, isThisStable, isVoidOrNotSpecified, runtimeIdentifier, RuntimeNames } from './util'

export class ReturnTransformer extends ScopedVisitor<ts.TypeNode | undefined> {
    constructor(
        public typechecker: ts.TypeChecker,
        public sourceFile: ts.SourceFile,
        public functionTable: Map<ts.SignatureDeclarationBase, FunctionKind>,
        ctx: ts.TransformationContext
    ) {
        super(functionTable, ctx)
    }

    visitor(node: ts.Node): ts.Node {
        if (isFunctionOrMethod(node)) {
            const kind = this.declarationKind(node)
            return this.withFunctionScope(kind, node.type, () => this.visitEachChild(node))
        }
        if (ts.isReturnStatement(node) && isMemoKind(this.currentKind())) {
            // visit children of the return expression before attaching it to the AST
            const expression = node.expression ? this.visitEachChild(node.expression) : undefined
            if (expression && ts.isCallExpression(expression)) {
                const synthetic = expression.expression
                if (ts.isIdentifier(synthetic) && ts.idText(synthetic) == RuntimeNames.SYNTHETIC_RETURN_MARK) {
                    return ts.factory.updateReturnStatement(node, expression.arguments[0])
                }
            }
            const functionReturnType = this.functionScopes.peek()?.data
            if (isVoidOrNotSpecified(functionReturnType))
                return ts.factory.createBlock([
                    ts.factory.createExpressionStatement(createScopeRecacheExpression(expression)),
                    ts.factory.updateReturnStatement(node, undefined)
                ])

            if (isThis(functionReturnType) && isThisStable(this.typechecker, this.sourceFile, functionReturnType))
                return ts.factory.createBlock([
                    ts.factory.createExpressionStatement(createScopeRecacheExpression()),
                    ts.factory.updateReturnStatement(node, ts.factory.createThis())
                ])
            
            return ts.factory.updateReturnStatement(node, createScopeRecacheExpression(expression))
        }
        return this.visitEachChild(node)
    }
}

function createScopeRecacheExpression(expression?: ts.Expression): ts.Expression {
    return ts.factory.createCallExpression(
        ts.factory.createPropertyAccessExpression(
            runtimeIdentifier(RuntimeNames.SCOPE),
            runtimeIdentifier(RuntimeNames.INTERNAL_VALUE_NEW)
        ),
        undefined,
        expression ? [expression] : undefined
    )
}
