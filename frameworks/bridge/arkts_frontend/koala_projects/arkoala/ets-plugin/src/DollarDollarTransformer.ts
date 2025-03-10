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

import * as ts from "@koalaui/ets-tsc"
import { AbstractVisitor } from "./AbstractVisitor"
import { DollarDollar, isDefined } from "./utils"
import {
    isComponentMethodCall,
    isInitializerObject,
    dollarDollarViablePasses
} from "./arkui-knowledge-base/dollar-dollar-viable-passes"

type Initialization = { parameter: string, type: ts.TypeNode, initializer: ts.Expression }

export class DollarDollarTransformer extends AbstractVisitor {
    private static callExpressionName(node: ts.CallExpression | ts.EtsComponentExpression): string | undefined {
        if (!ts.isIdentifier(node.expression)) {
            return undefined
        }
        return ts.idText(node.expression)
    }

    static isDollarDollar(node: ts.CallExpression): boolean {
        if (!ts.isIdentifier(node.expression)) {
            return false
        }
        if (node.arguments.length !== 1) {
            return false
        }
        if (ts.idText(node.expression) !== DollarDollar) {
            return false
        }
        return true
    }

    visitor(beforeChildren: ts.Node): ts.Node {
        const node = this.visitEachChild(beforeChildren)
        if (ts.isCallExpression(node)) {
            // TODO componentMethodCallInitializations
        }

        if (ts.isEtsComponentExpression(node)) {
            return DollarDollarTransformer.componentCallInitializations(node)
                .map(it =>
                    (node: ts.EtsComponentExpression | ts.CallExpression) =>
                        DollarDollarTransformer.addOnChanged(node, it)
                )
                .reduce(
                    (addTo, add) => add(addTo),
                    node as ts.EtsComponentExpression | ts.CallExpression
                )
        }
        return node
    }

    static addOnChanged(node: ts.EtsComponentExpression | ts.CallExpression, initialization: Initialization): ts.CallExpression {
        return ts.factory.createCallExpression(
            ts.factory.createPropertyAccessExpression(
                node,
                `_onChangeEvent_${initialization.parameter}`,
            ),
            undefined,
            [
                ts.factory.createArrowFunction(
                    undefined,
                    undefined,
                    [
                        ts.factory.createParameterDeclaration(
                            undefined,
                            undefined,
                            initialization.parameter,
                            undefined,
                            initialization.type
                        )
                    ],
                    ts.factory.createKeywordTypeNode(ts.SyntaxKind.VoidKeyword),
                    ts.factory.createToken(ts.SyntaxKind.EqualsGreaterThanToken),
                    ts.factory.createBlock(
                        [
                            ts.factory.createExpressionStatement(
                                ts.factory.createAssignment(
                                    initialization.initializer,
                                    ts.factory.createIdentifier(initialization.parameter)
                                )
                            )
                        ],
                        false
                    )
                )
            ]
        )
    }

    static componentCallInitializations(node: ts.EtsComponentExpression): Initialization[] {
        const singleArgument = node.arguments[0]
        if (singleArgument === undefined) {
            return []
        }
        if (!ts.isObjectLiteralExpression(singleArgument)) {
            return []
        }

        const viablePasses = dollarDollarViablePasses
            .filter(isInitializerObject)
            .filter(it => it.component === DollarDollarTransformer.callExpressionName(node))

        return singleArgument.properties
            .filter(ts.isPropertyAssignment)
            .map(it => {
                if (!ts.isIdentifier(it.name)) {
                    return undefined
                }
                return {
                    name: ts.idText(it.name),
                    initializer: it.initializer
                }
            })
            .filter(isDefined)
            .map(initialization => {
                const viablePass = viablePasses
                    .find(it => it.parameter === initialization.name)
                if (viablePass === undefined) {
                    return undefined
                }
                if (!ts.isCallExpression(initialization.initializer)) {
                    return undefined
                }
                if (!DollarDollarTransformer.isDollarDollar(initialization.initializer)) {
                    return undefined
                }
                return {
                    parameter: initialization.name,
                    type: viablePass.type,
                    initializer: initialization.initializer.arguments[0]
                }
            })
            .filter(isDefined)
    }

    static componentMethodCallInitializations(node: ts.CallExpression, collected: Initialization[] = []): Initialization[] {
        if (!ts.isPropertyAccessExpression(node.expression)) {
            return []
        }
        if (ts.isEtsComponentExpression(node.expression.expression)) {
            return collected
        }
        if (!ts.isCallExpression(node.expression.expression)) {
            return []
        }
        return this.componentMethodCallInitializations(
            node.expression.expression,
            collected.concat(
                DollarDollarTransformer.callInitializations(node)
            )
        )
    }

    static callInitializations(node: ts.CallExpression): Initialization[] {
        if (!ts.isIdentifier(node.expression)) {
            return []
        }
        const firstArgument = node.arguments[0]
        if (firstArgument === undefined) {
            return []
        }
        if (!ts.isCallExpression(firstArgument)) {
            return []
        }
        if (!DollarDollarTransformer.isDollarDollar(firstArgument)) {
            return []
        }
        const method = ts.idText(node.expression)
        return dollarDollarViablePasses
            .filter(isComponentMethodCall) // TODO: bindSheet too
            .filter(it => it.method === method)
            .map(it => ({
                parameter: it.parameter,
                type: it.type,
                initializer: firstArgument.arguments[0]
            }))
    }

    static argumentIfDollarDollarCall(node: ts.Expression): ts.Expression {
        if (!ts.isCallExpression(node)) {
            return node
        }
        if (!DollarDollarTransformer.isDollarDollar(node)) {
            return node
        }
        return node.arguments[0]
    }
}
