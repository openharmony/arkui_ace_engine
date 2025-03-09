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

import * as arkts from "@koalaui/libarkts"
import { RuntimeNames } from "./utils"

export class factory {
    // Importing
    static createContextTypeImportSpecifier(): arkts.ImportSpecifier {
        return arkts.factory.createImportSpecifier(
            arkts.factory.createIdentifier(RuntimeNames.CONTEXT_TYPE),
            arkts.factory.createIdentifier(RuntimeNames.CONTEXT_TYPE),
        )
    }
    static createIdTypeImportSpecifier(): arkts.ImportSpecifier {
        return arkts.factory.createImportSpecifier(
            arkts.factory.createIdentifier(RuntimeNames.ID_TYPE),
            arkts.factory.createIdentifier(RuntimeNames.ID_TYPE),
        )
    }
    static createContextTypesImportDeclaration(): arkts.EtsImportDeclaration {
        return arkts.factory.createImportDeclaration(
            arkts.factory.createStringLiteral(RuntimeNames.CONTEXT_TYPE_DEFAULT_IMPORT),
            [factory.createContextTypeImportSpecifier(), factory.createIdTypeImportSpecifier()],
            arkts.Es2pandaImportKinds.IMPORT_KINDS_TYPE,
            true,
        )
    }

    // Parameters
    static createContextParameter(): arkts.ETSParameterExpression {
        return arkts.factory.createParameterDeclaration(
            arkts.factory.createIdentifier(
                RuntimeNames.CONTEXT,
                arkts.factory.createTypeReference(
                    arkts.factory.createTypeReferencePart(
                        arkts.factory.createIdentifier(RuntimeNames.CONTEXT_TYPE)
                    )
                )
            ),
            undefined
        )
    }
    static createIdParameter(): arkts.ETSParameterExpression {
        return arkts.factory.createParameterDeclaration(
            arkts.factory.createIdentifier(RuntimeNames.ID,
                arkts.factory.createTypeReference(
                    arkts.factory.createTypeReferencePart(
                        arkts.factory.createIdentifier(RuntimeNames.ID_TYPE)
                    )
                )
            ),
            undefined
        )
    }
    static createHiddenParameters(): arkts.ETSParameterExpression[] {
        return [factory.createContextParameter(), factory.createIdParameter()]
    }
    static updateFunctionTypeWithMemoParameters(type: arkts.ETSFunctionType): arkts.ETSFunctionType {
        return arkts.factory.updateFunctionType(
            type,
            arkts.factory.createFunctionSignature(
                undefined,
                [...factory.createHiddenParameters(), ...type.params],
                type.returnType,
                false,
            ),
            arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_ARROW,
        )
    }

    // Arguments
    static createContextArgument(): arkts.AstNode {
        return arkts.factory.createIdentifier(RuntimeNames.CONTEXT)
    }
    static createIdArgument(hash: arkts.NumberLiteral | arkts.StringLiteral): arkts.AstNode {
        return arkts.factory.createBinaryExpression(
            arkts.factory.createIdentifier(RuntimeNames.ID),
            hash,
            arkts.Es2pandaTokenType.TOKEN_TYPE_PUNCTUATOR_PLUS,
        )
    }
    static createHiddenArguments(hash: arkts.NumberLiteral | arkts.StringLiteral): arkts.AstNode[] {
        return [factory.createContextArgument(), factory.createIdArgument(hash)]
    }

    // Memo parameters
    static createMemoParameterIdentifier(name: string): arkts.Identifier {
        return arkts.factory.createIdentifier(`${RuntimeNames.PARAMETER}_${name}`)
    }
    static createMemoParameterDeclarator(id: number, name: string): arkts.VariableDeclarator {
        return arkts.factory.createVariableDeclarator(
            arkts.Es2pandaVariableDeclaratorFlag.VARIABLE_DECLARATOR_FLAG_CONST,
            factory.createMemoParameterIdentifier(name),
            arkts.factory.createCallExpression(
                arkts.factory.createMemberExpression(
                    arkts.factory.createIdentifier(RuntimeNames.SCOPE),
                    arkts.factory.createIdentifier(RuntimeNames.INTERNAL_PARAMETER_STATE),
                    arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_PROPERTY_ACCESS,
                    false,
                    false
                ),
                undefined,
                [
                    arkts.factory.createNumericLiteral(id),
                    arkts.factory.createIdentifier(name),
                ],
            )
        )
    }
    static createMemoParameterAccess(name: string): arkts.MemberExpression {
        return arkts.factory.createMemberExpression(
            factory.createMemoParameterIdentifier(name),
            arkts.factory.createIdentifier(RuntimeNames.VALUE),
            arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_GETTER,
            false,
            false,
        )
    }
    static createMemoParameterAccessMemoWithScope(name: string, hash: arkts.NumberLiteral | arkts.StringLiteral, passArgs?: arkts.AstNode[]): arkts.CallExpression {
        const updatedArgs = passArgs ? passArgs : []
        return arkts.factory.createCallExpression(
            arkts.factory.createMemberExpression(
                factory.createMemoParameterIdentifier(name),
                arkts.factory.createIdentifier(RuntimeNames.VALUE),
                arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_GETTER,
                false,
                false,
            ),
            undefined,
            [...factory.createHiddenArguments(hash), ...updatedArgs],
        )
    }
    static createMemoParameterAccessMemoWithoutScope(name: string, hash: arkts.NumberLiteral | arkts.StringLiteral, passArgs?: arkts.AstNode[]): arkts.CallExpression {
        const updatedArgs = passArgs ? passArgs : []
        return arkts.factory.createCallExpression(
            arkts.factory.createIdentifier(name),
            undefined,
            [...factory.createHiddenArguments(hash), ...updatedArgs],
        )
    }
    static createMemoParameterAccessCall(name: string, hash: arkts.NumberLiteral | arkts.StringLiteral, passArgs?: arkts.AstNode[]): arkts.CallExpression {
        const updatedArgs = passArgs ? passArgs : []
        return arkts.factory.createCallExpression(
            arkts.factory.createMemberExpression(
                factory.createMemoParameterIdentifier(name),
                arkts.factory.createIdentifier(RuntimeNames.VALUE),
                arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_GETTER,
                false,
                false,
            ),
            undefined,
            [...updatedArgs],
        )
    }

    // Recache
    static createScopeDeclaration(returnTypeAnnotation: arkts.TypeNode | undefined, hash: arkts.NumberLiteral | arkts.StringLiteral, cnt: number): arkts.VariableDeclaration {
        return arkts.factory.createVariableDeclaration(
            0,
            arkts.Es2pandaVariableDeclarationKind.VARIABLE_DECLARATION_KIND_CONST,
            [
                arkts.factory.createVariableDeclarator(
                    arkts.Es2pandaVariableDeclaratorFlag.VARIABLE_DECLARATOR_FLAG_CONST,
                    arkts.factory.createIdentifier(RuntimeNames.SCOPE),
                    arkts.factory.createCallExpression(
                        arkts.factory.createMemberExpression(
                            arkts.factory.createIdentifier(RuntimeNames.CONTEXT),
                            arkts.factory.createIdentifier(RuntimeNames.INTERNAL_SCOPE),
                            arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_PROPERTY_ACCESS,
                            false,
                            false
                        ),
                        returnTypeAnnotation ? [returnTypeAnnotation] : [arkts.factory.createPrimitiveType(arkts.Es2pandaPrimitiveType.PRIMITIVE_TYPE_VOID)],
                        [
                            factory.createIdArgument(hash),
                            arkts.factory.createNumericLiteral(cnt)
                        ],
                    )
                )
            ]
        )
    }
    static createRecacheCall(arg?: arkts.AstNode): arkts.CallExpression {
        return arkts.factory.createCallExpression(
            arkts.factory.createMemberExpression(
                arkts.factory.createIdentifier(RuntimeNames.SCOPE),
                arkts.factory.createIdentifier(RuntimeNames.INTERNAL_VALUE_NEW),
                arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_PROPERTY_ACCESS,
                false,
                false
            ),
            undefined,
            arg ? [arg] : undefined,
        )
    }
    static createSyntheticReturnStatement(): arkts.ReturnStatement {
        return arkts.factory.createReturnStatement(
            arkts.factory.createMemberExpression(
                arkts.factory.createIdentifier(RuntimeNames.SCOPE),
                arkts.factory.createIdentifier(RuntimeNames.INTERNAL_VALUE),
                arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_NONE,
                false,
                false,
            ),
        )
    }
    static createIfStatementWithSyntheticReturnStatement(syntheticReturnStatement: arkts.ReturnStatement): arkts.IfStatement {
        return arkts.factory.createIfStatement(
            arkts.factory.createMemberExpression(
                arkts.factory.createIdentifier(RuntimeNames.SCOPE),
                arkts.factory.createIdentifier(RuntimeNames.INTERNAL_VALUE_OK),
                arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_NONE,
                false,
                false,
            ),
            syntheticReturnStatement,
        )
    }

    // Compute
    static createLambdaWrapper(node: arkts.Expression): arkts.ArrowFunctionExpression {
        return arkts.factory.createArrowFunction(
            arkts.factory.createScriptFunction(
                arkts.factory.createBlock([
                    arkts.factory.createReturnStatement(node)
                ]),
                arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_ARROW,
                arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_NONE,
                false,
                undefined,
                [],
                undefined,
                undefined,
            )
        )
    }
    static createComputeExpression(hash: arkts.NumberLiteral | arkts.StringLiteral, node: arkts.Expression): arkts.CallExpression {
        return arkts.factory.createCallExpression(
            arkts.factory.createMemberExpression(
                arkts.factory.createIdentifier(RuntimeNames.CONTEXT),
                arkts.factory.createIdentifier(RuntimeNames.COMPUTE),
                arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_PROPERTY_ACCESS,
                false,
                false
            ),
            undefined,
            [factory.createIdArgument(hash), factory.createLambdaWrapper(node)]
        )
    }
}
