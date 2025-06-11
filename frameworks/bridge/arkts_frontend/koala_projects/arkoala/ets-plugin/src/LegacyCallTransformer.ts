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
import { asString, CallTable } from './utils'
import { Importer } from './Importer'

export class LegacyCallTransformer extends AbstractVisitor {
    static parameterName = "elementId"
    static page = "page"
    static line = "line"
    static LegacyNode = "LegacyNode"

	constructor(
		sourceFile: ts.SourceFile,
        ctx: ts.TransformationContext,
        private importer: Importer,
        private callTable: CallTable
	) {
        super(sourceFile, ctx)
    }

    isLegacyStructCall(call: ts.CallExpression): boolean {
        const originalCall = ts.getOriginalNode(call) as ts.CallExpression
        return this.callTable.legacyCalls.has(originalCall)
    }

    createLambda(name: ts.Identifier): ts.Expression {
        const locationObject = ts.factory.createObjectLiteralExpression(
            [
                ts.factory.createPropertyAssignment(
                    ts.factory.createIdentifier(LegacyCallTransformer.page),
                    // TODO: entry/src/main/ets/pages/LocalPage.ets
                    ts.factory.createStringLiteral("")
                ),
                ts.factory.createPropertyAssignment(
                    ts.factory.createIdentifier(LegacyCallTransformer.line),
                    // TODO: provide line number
                    ts.factory.createNumericLiteral("0")
                )
            ],
            false
        )
        const emptyLambda = ts.factory.createArrowFunction(
            undefined,
            undefined,
            [],
            undefined,
            ts.factory.createToken(ts.SyntaxKind.EqualsGreaterThanToken),
            ts.factory.createBlock(
                [],
                false
            )
        )
        const emptyObject = ts.factory.createObjectLiteralExpression(
            [],
            false
        )
        const elementIdParameter = ts.factory.createParameterDeclaration(
            undefined,
            undefined,
            ts.factory.createIdentifier(LegacyCallTransformer.parameterName),
            undefined,
            ts.factory.createKeywordTypeNode(ts.SyntaxKind.NumberKeyword),
            undefined
        )
        const newExpression = ts.factory.createNewExpression(
            name,
            undefined,
            [
                ts.factory.createIdentifier("undefined"),
                emptyObject,
                ts.factory.createIdentifier("undefined"),
                ts.factory.createIdentifier(LegacyCallTransformer.parameterName),
                emptyLambda,
                locationObject
            ]
        )
        return ts.factory.createArrowFunction(
            undefined,
            undefined,
            [ elementIdParameter ],
            undefined,
            ts.factory.createToken(ts.SyntaxKind.EqualsGreaterThanToken),
            newExpression
        )
    }

    transformLegacyCall(node: ts.CallExpression): ts.CallExpression {
        const name = node.expression as ts.Identifier
        const instanceLambda = this.createLambda(name)
        return ts.factory.createCallExpression(
            ts.factory.createIdentifier(
                this.importer.withAdaptorImport(LegacyCallTransformer.LegacyNode)
            ),
            undefined,
            [ instanceLambda ],
        )
    }

    visitor(beforeChildren: ts.Node): ts.Node {
        const node = this.visitEachChild(beforeChildren)

        if (ts.isExpressionStatement(node) &&
            ts.isCallExpression(node.expression) &&
            ts.isIdentifier(node.expression.expression) &&
            this.isLegacyStructCall(node.expression)
        ) {
            return this.transformLegacyCall(node.expression)
        }

        return node
    }
}
