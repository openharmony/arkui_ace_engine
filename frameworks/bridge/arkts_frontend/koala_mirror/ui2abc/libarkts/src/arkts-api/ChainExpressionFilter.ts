/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

import { BlockStatement, ChainExpression, Expression, isChainExpression, isMemberExpression, MemberExpression } from "src/generated";
import { AbstractVisitor } from "./AbstractVisitor";
import { AstNode } from "./peers/AstNode"
import { factory } from "./factory/nodeFactory";
import { Es2pandaTokenType, Es2pandaVariableDeclarationKind, Es2pandaVariableDeclaratorFlag } from "src/generated/Es2pandaEnums";


export class ChainExpressionFilter extends AbstractVisitor {
    static counter = 0
    transformChainExpression(node: ChainExpression): Expression {
        const expression = node.expression
        if (expression == undefined) return node
        if (!isMemberExpression(expression)) return node
        return this.transformMemberExpression(expression)
    }
    transformMemberExpression(expression: MemberExpression): Expression {
        const temporaryVarName = `chaintmp%%_${ChainExpressionFilter.counter++}`
        return factory.createBlockExpression(
            [
                factory.createVariableDeclaration(
                    Es2pandaVariableDeclarationKind.VARIABLE_DECLARATION_KIND_LET,
                    [
                        factory.createVariableDeclarator(
                            Es2pandaVariableDeclaratorFlag.VARIABLE_DECLARATOR_FLAG_LET,
                            factory.createIdentifier(temporaryVarName),
                            expression.object
                        )
                    ],
                    undefined
                ),
                factory.createExpressionStatement(
                    factory.createConditionalExpression(
                        factory.createBinaryExpression(
                            factory.createIdentifier(temporaryVarName, undefined),
                            factory.createUndefinedLiteral(),
                            Es2pandaTokenType.TOKEN_TYPE_PUNCTUATOR_STRICT_EQUAL
                        ),
                        factory.createUndefinedLiteral(),
                        factory.createMemberExpression(
                            factory.createIdentifier(temporaryVarName, undefined),
                            expression.property,
                            expression.kind,
                            expression.isComputed,
                            false
                        )
                    )
                )
            ]
        )
    }


    visitor(beforeChildren: BlockStatement): BlockStatement
    visitor(beforeChildren: AstNode): AstNode {
        const node = this.visitEachChild(beforeChildren)
        if (isChainExpression(node)) {
            return this.transformChainExpression(node)
        }
        if (isMemberExpression(node) && node.isOptional) {
            return this.transformMemberExpression(node)
        }
        return node
    }
}