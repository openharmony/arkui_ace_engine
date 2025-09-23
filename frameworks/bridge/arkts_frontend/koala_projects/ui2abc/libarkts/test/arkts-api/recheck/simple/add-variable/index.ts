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

import * as arkts from "../../../../../src/arkts-api"

export function addVariableDeclaration(node: arkts.ClassDefinition) {
    return arkts.factory.updateClassDefinition(
        node,
        node.ident,
        node.typeParams,
        node.superTypeParams,
        node.implements,
        undefined,
        node.super,
        [
            ...node.body.map((node: arkts.AstNode) => {
                if (!arkts.isMethodDefinition(node)) {
                    return node
                }
                if (node.id?.name != "f") {
                    return node
                }
                if (!arkts.isFunctionExpression(node.value)) {
                    return node
                }
                const func = node.value.function
                if (!func || !arkts.isBlockStatement(func.body)) {
                    return node
                }
                return arkts.factory.updateMethodDefinition(
                    node,
                    node.kind,
                    node.key,
                    arkts.factory.updateFunctionExpression(
                        node.value,
                        node.id,
                        arkts.factory.updateScriptFunction(
                            func,
                            arkts.factory.updateBlockStatement(
                                func.body,
                                [
                                    arkts.factory.createVariableDeclaration(
                                        arkts.Es2pandaVariableDeclarationKind.VARIABLE_DECLARATION_KIND_CONST,
                                        [
                                            arkts.factory.createVariableDeclarator(
                                                arkts.Es2pandaVariableDeclaratorFlag.VARIABLE_DECLARATOR_FLAG_CONST,
                                                arkts.factory.createIdentifier("x"),
                                                arkts.factory.createBinaryExpression(
                                                    arkts.factory.createNumberLiteral(1),
                                                    arkts.factory.createNumberLiteral(4),
                                                    arkts.Es2pandaTokenType.TOKEN_TYPE_PUNCTUATOR_PLUS,
                                                ),
                                            ),
                                        ],
                                    ),
                                    ...func.body.statements,
                                ],
                            ),
                            func.typeParams,
                            func.params,
                            func.returnTypeAnnotation,
                            func.hasReceiver,
                            func.flags,
                            func.modifierFlags,
                            func.id,
                            func.annotations,
                        ),
                    ),
                    node.modifierFlags,
                    node.isComputed,
                    node.overloads,
                )
            })
        ],
        node.modifiers,
        node.modifierFlags
    )
}
