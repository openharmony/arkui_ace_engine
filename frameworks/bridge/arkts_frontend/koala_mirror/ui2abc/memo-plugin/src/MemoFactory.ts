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
import { DebugNames, RuntimeNames, isVoidReturn } from "./utils"

export class factory {
    // Importing
    static createContextTypeImportSpecifier(): arkts.ImportSpecifier {
        return arkts.factory.createImportSpecifier(
            arkts.factory.createIdentifier(RuntimeNames.CONTEXT_TYPE, undefined),
            arkts.factory.createIdentifier(RuntimeNames.CONTEXT_TYPE, undefined),
        )
    }
    static createIdTypeImportSpecifier(): arkts.ImportSpecifier {
        return arkts.factory.createImportSpecifier(
            arkts.factory.createIdentifier(RuntimeNames.ID_TYPE, undefined),
            arkts.factory.createIdentifier(RuntimeNames.ID_TYPE, undefined),
        )
    }
    static createHashImportSpecifier(): arkts.ImportSpecifier {
        return arkts.factory.createImportSpecifier(
            arkts.factory.createIdentifier(RuntimeNames.HASH, undefined),
            arkts.factory.createIdentifier(RuntimeNames.HASH, undefined),
        )
    }

    static createContextTypesImportDeclaration(debug: boolean, path?: string): arkts.ETSImportDeclaration {
        const mandatory = [factory.createContextTypeImportSpecifier(), factory.createIdTypeImportSpecifier()]
        return arkts.factory.createETSImportDeclaration(
            arkts.factory.createStringLiteral(path ?? RuntimeNames.CONTEXT_TYPE_DEFAULT_IMPORT),
            debug ? [...mandatory, factory.createHashImportSpecifier()] : mandatory,
            arkts.Es2pandaImportKinds.IMPORT_KINDS_ALL
        )
    }

    // Parameters
    static createContextParameter(): arkts.ETSParameterExpression {
        return arkts.factory.createETSParameterExpression(
            arkts.factory.createIdentifier(
                RuntimeNames.CONTEXT,
                arkts.factory.createETSTypeReference(
                    arkts.factory.createETSTypeReferencePart(
                        arkts.factory.createIdentifier(RuntimeNames.CONTEXT_TYPE, undefined),
                        undefined,
                        undefined
                    )
                )
            ),
            false
        )
    }
    static createIdParameter(): arkts.ETSParameterExpression {
        return arkts.factory.createETSParameterExpression(
            arkts.factory.createIdentifier(RuntimeNames.ID,
                arkts.factory.createETSTypeReference(
                    arkts.factory.createETSTypeReferencePart(
                        arkts.factory.createIdentifier(RuntimeNames.ID_TYPE, undefined),
                        undefined,
                        undefined
                    )
                )
            ),
            false
        )
    }
    static createHiddenParameters(): arkts.ETSParameterExpression[] {
        return [factory.createContextParameter(), factory.createIdParameter()]
    }

    // Arguments
    static createContextArgument(): arkts.Expression {
        return arkts.factory.createIdentifier(RuntimeNames.CONTEXT, undefined)
    }
    static createIdArgument(hash: arkts.Expression): arkts.Expression {
        return arkts.factory.createBinaryExpression(
            arkts.factory.createIdentifier(RuntimeNames.ID, undefined),
            hash,
            arkts.Es2pandaTokenType.TOKEN_TYPE_PUNCTUATOR_PLUS,
        )
    }
    static createHiddenArguments(hash: arkts.Expression): arkts.Expression[] {
        return [factory.createContextArgument(), factory.createIdArgument(hash)]
    }

    // Memo parameters
    static createMemoParameterIdentifier(name: string): arkts.Identifier {
        if (name === "=t") {
            return arkts.factory.createIdentifier(`${RuntimeNames.PARAMETER}_this`, undefined)
        }
        return arkts.factory.createIdentifier(`${RuntimeNames.PARAMETER}_${name}`, undefined)
    }
    static createMemoParameterDeclarator(id: number, name: string): arkts.VariableDeclarator {
        const original = (name == "this" || name == "=t") ?
            arkts.factory.createThisExpression() :
            arkts.factory.createIdentifier(name, undefined)
        return arkts.factory.createVariableDeclarator(
            arkts.Es2pandaVariableDeclaratorFlag.VARIABLE_DECLARATOR_FLAG_CONST,
            factory.createMemoParameterIdentifier(name),
            arkts.factory.createCallExpression(
                arkts.factory.createMemberExpression(
                    arkts.factory.createIdentifier(RuntimeNames.SCOPE, undefined),
                    arkts.factory.createIdentifier(RuntimeNames.INTERNAL_PARAMETER_STATE, undefined),
                    arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_PROPERTY_ACCESS,
                    false,
                    false
                ),
                [
                    arkts.factory.createNumberLiteral(id),
                    original,
                ],
                undefined,
            )
        )
    }
    static createMemoParameterDeclaration(parameters: string[]): arkts.VariableDeclaration {
        return arkts.factory.createVariableDeclaration(
            arkts.Es2pandaVariableDeclarationKind.VARIABLE_DECLARATION_KIND_CONST,
            parameters.map((name, id) => { return factory.createMemoParameterDeclarator(id, name) }),
        )
    }
    static createMemoParameterModifiedLogging(parameters: string[]): arkts.CallExpression {
        return arkts.factory.createCallExpression(
            arkts.factory.createMemberExpression(
                arkts.factory.createIdentifier(DebugNames.CONSOLE, undefined),
                arkts.factory.createIdentifier(DebugNames.LOG, undefined),
                arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_NONE,
                false,
                false,
            ),
            [
                arkts.factory.createStringLiteral(DebugNames.BANNER_PARAMETER),
                ...parameters.flatMap((name) => { return [
                    arkts.factory.createStringLiteral(`( ${name} modified:`),
                    arkts.factory.createMemberExpression(
                        factory.createMemoParameterIdentifier(name),
                        arkts.factory.createIdentifier("modified", undefined),
                        arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_GETTER,
                        false,
                        false
                    ),
                    arkts.factory.createStringLiteral(`)`),
                ] })
            ],
            undefined,
        )
    }
    static createMemoParameterAccess(name: string): arkts.MemberExpression {
        return arkts.factory.createMemberExpression(
            factory.createMemoParameterIdentifier(name),
            arkts.factory.createIdentifier(RuntimeNames.VALUE, undefined),
            arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_GETTER,
            false,
            false,
        )
    }
    static createMemoParameterAccessCall(name: string, passArgs?: arkts.Expression[]): arkts.CallExpression {
        const updatedArgs = passArgs ? passArgs : []
        return arkts.factory.createCallExpression(
            arkts.factory.createMemberExpression(
                factory.createMemoParameterIdentifier(name),
                arkts.factory.createIdentifier(RuntimeNames.VALUE, undefined),
                arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_GETTER,
                false,
                false,
            ),
            [...updatedArgs],
            undefined,
        )
    }

    // Recache
    static createScopeDeclaration(returnTypeAnnotation: arkts.TypeNode | undefined, hash: arkts.Expression, cnt: number): arkts.VariableDeclaration {
        return arkts.factory.createVariableDeclaration(
            arkts.Es2pandaVariableDeclarationKind.VARIABLE_DECLARATION_KIND_CONST,
            [
                arkts.factory.createVariableDeclarator(
                    arkts.Es2pandaVariableDeclaratorFlag.VARIABLE_DECLARATOR_FLAG_CONST,
                    arkts.factory.createIdentifier(RuntimeNames.SCOPE, undefined),
                    arkts.factory.createCallExpression(
                        arkts.factory.createMemberExpression(
                            arkts.factory.createIdentifier(RuntimeNames.CONTEXT, undefined),
                            arkts.factory.createIdentifier(RuntimeNames.INTERNAL_SCOPE, undefined),
                            arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_PROPERTY_ACCESS,
                            false,
                            false
                        ),
                        [
                            factory.createIdArgument(hash),
                            arkts.factory.createNumberLiteral(cnt)
                        ],
                        arkts.factory.createTSTypeParameterInstantiation(
                            returnTypeAnnotation
                                ? [returnTypeAnnotation]
                                : [arkts.factory.createETSPrimitiveType(arkts.Es2pandaPrimitiveType.PRIMITIVE_TYPE_VOID)],
                        ),
                    )
                )
            ]
        )
    }
    static createRecacheCall(arg?: arkts.Expression): arkts.CallExpression {
        return arkts.factory.createCallExpression(
            arkts.factory.createMemberExpression(
                arkts.factory.createIdentifier(RuntimeNames.SCOPE, undefined),
                arkts.factory.createIdentifier(RuntimeNames.INTERNAL_VALUE_NEW, undefined),
                arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_PROPERTY_ACCESS,
                false,
                false
            ),
            arg ? [arg] : [],
            undefined,
        )
    }
    static createReturnThis(): arkts.BlockStatement {
        return arkts.factory.createBlockStatement([
            arkts.factory.createExpressionStatement(
                factory.createRecacheCall()
            ),
            arkts.factory.createReturnStatement(
                arkts.factory.createThisExpression()
            )
        ])
    }
    static createCached(): arkts.Expression {
        return arkts.factory.createMemberExpression(
            arkts.factory.createIdentifier(RuntimeNames.SCOPE, undefined),
            arkts.factory.createIdentifier(RuntimeNames.INTERNAL_VALUE, undefined),
            arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_PROPERTY_ACCESS,
            false,
            false,
        )
    }
    static createSyntheticReturnStatement(returnTypeAnnotation: arkts.TypeNode | undefined): arkts.ReturnStatement | arkts.BlockStatement {
        if (isVoidReturn(returnTypeAnnotation)) {
            return arkts.factory.createBlockStatement([
                arkts.factory.createExpressionStatement(
                    this.createCached()
                ),
                arkts.factory.createReturnStatement(undefined)
            ])
        }
        if (arkts.isTSThisType(returnTypeAnnotation)) {
            return arkts.factory.createBlockStatement([
                arkts.factory.createExpressionStatement(
                    this.createCached()
                ),
                arkts.factory.createReturnStatement(arkts.factory.createThisExpression())
            ])
        }
        return arkts.factory.createReturnStatement(
            this.createCached(),
        )
    }
    static createIfStatementWithSyntheticReturnStatement(syntheticReturnStatement: arkts.ReturnStatement | arkts.BlockStatement): arkts.IfStatement {
        return arkts.factory.createIfStatement(
            arkts.factory.createMemberExpression(
                arkts.factory.createIdentifier(RuntimeNames.SCOPE, undefined),
                arkts.factory.createIdentifier(RuntimeNames.INTERNAL_VALUE_OK, undefined),
                arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_GETTER,
                false,
                false,
            ),
            syntheticReturnStatement,
            undefined,
        )
    }
    static createUnchangedLogging() {
        return arkts.factory.createCallExpression(
            arkts.factory.createMemberExpression(
                arkts.factory.createIdentifier(DebugNames.CONSOLE, undefined),
                arkts.factory.createIdentifier(DebugNames.LOG, undefined),
                arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_NONE,
                false,
                false,
            ),
            [
                arkts.factory.createStringLiteral(DebugNames.BANNER_UNCHANGED),
                arkts.factory.createMemberExpression(
                    arkts.factory.createIdentifier(RuntimeNames.SCOPE, undefined),
                    arkts.factory.createIdentifier(RuntimeNames.INTERNAL_VALUE_OK, undefined),
                    arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_GETTER,
                    false,
                    false
                )
            ],
            undefined,
        )
    }

    // All these deduce functions is a huge woraround for
    // recheck incapable to infer proper return types on lambdas.
    static deduceWrapperType(node: arkts.Expression): arkts.TypeNode|undefined {
        if (arkts.isArrowFunctionExpression(node)) return factory.deduceArrowWrapperType(node)
        if (arkts.isObjectExpression(node)) return factory.deduceObjectWrapperType(node)
        if (arkts.isTSAsExpression(node)) return factory.deduceAsWrapperType(node)
        return undefined
    }
    static deduceAsWrapperType(node: arkts.TSAsExpression): arkts.TypeNode|undefined {
        return node.typeAnnotation
    }
    static deduceObjectWrapperType(node: arkts.Expression): arkts.TypeNode|undefined {
        return undefined
    }
    static deduceArrowWrapperType(arrow: arkts.ArrowFunctionExpression): arkts.TypeNode|undefined {
        const origType: arkts.TypeNode | undefined = arrow.function?.returnTypeAnnotation
        if (origType == undefined) return undefined
        const params = arrow.function?.params?.map(it => {
            const param = it as arkts.ETSParameterExpression
            return arkts.factory.createETSParameterExpression(
                arkts.factory.createIdentifier(param.ident!.name),
                param.isOptional,
                undefined,
                param.typeAnnotation,
                undefined
            )
        }) ?? []
        return arkts.factory.createETSFunctionType(
            undefined,
            params,
            origType,
            false,
            arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_NONE,
            undefined
        )
    }

    // Compute
    static createLambdaWrapper(node: arkts.Expression): arkts.ArrowFunctionExpression {
        return arkts.factory.createArrowFunctionExpression(
            arkts.factory.createScriptFunction(
                arkts.factory.createBlockStatement([
                    arkts.factory.createReturnStatement(node)
                ]),
                undefined,
                [],
                factory.deduceWrapperType(node),
                false,
                arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_ARROW,
                arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_NONE,
                undefined,
                undefined,
            )
        )
    }
    static createComputeExpression(hash: arkts.Expression, node: arkts.Expression): arkts.CallExpression {
        return arkts.factory.createCallExpression(
            arkts.factory.createMemberExpression(
                arkts.factory.createIdentifier(RuntimeNames.CONTEXT, undefined),
                arkts.factory.createIdentifier(RuntimeNames.COMPUTE, undefined),
                arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_PROPERTY_ACCESS,
                false,
                false
            ),
            [factory.createIdArgument(hash), factory.createLambdaWrapper(node)],
            undefined,
        )
    }
}
