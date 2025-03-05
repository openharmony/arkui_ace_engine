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
import { factory } from "./MemoFactory"
import { AbstractVisitor } from "./AbstractVisitor"
import {
    PositionalIdTracker,
    hasMemoAnnotation,
    hasMemoIntrinsicAnnotation,
} from "./utils"
import { ParameterTransformer } from "./ParameterTransformer"
import { ReturnTransformer } from "./ReturnTranformer"

function updateFunctionBody(
    node: arkts.BlockStatement,
    parameters: arkts.ETSParameterExpression[],
    returnTypeAnnotation: arkts.AstNode | undefined,
    hash: arkts.NumberLiteral | arkts.StringLiteral
): [
    arkts.BlockStatement,
    arkts.VariableDeclaration | undefined,
    arkts.ReturnStatement | undefined,
] {
    const scopeDeclaration = factory.createScopeDeclaration(returnTypeAnnotation, hash, parameters.length)
    const memoParameters = parameters.map((name, id) => { return factory.createMemoParameterDeclarator(id, name.identifier.name) })
    const memoParametersDeclaration = memoParameters.length
        ? [
            arkts.factory.createVariableDeclaration(
                0,
                arkts.Es2pandaVariableDeclarationKind.VARIABLE_DECLARATION_KIND_CONST,
                memoParameters,
            )
        ]
        : []
    const syntheticReturnStatement = factory.createSyntheticReturnStatement()
    const unchangedCheck = factory.createIfStatementWithSyntheticReturnStatement(syntheticReturnStatement)
    if (node.statements.length && node.statements[node.statements.length - 1] instanceof arkts.ReturnStatement) {
        return [
            arkts.factory.updateBlock(
                node,
                [
                    scopeDeclaration,
                    ...memoParametersDeclaration,
                    unchangedCheck,
                    ...node.statements,
                ]
            ),
            memoParametersDeclaration.length ? memoParametersDeclaration[0] : undefined,
            syntheticReturnStatement,
        ]
    } else {
        return [
            arkts.factory.updateBlock(
                node,
                [
                    scopeDeclaration,
                    ...memoParametersDeclaration,
                    unchangedCheck,
                    ...node.statements,
                    arkts.factory.createReturnStatement(),
                ]
            ),
            memoParametersDeclaration.length ? memoParametersDeclaration[0] : undefined,
            syntheticReturnStatement,
        ]
    }
}

export class FunctionTransformer extends AbstractVisitor {
    constructor(
        private positionalIdTracker: PositionalIdTracker,
        private parameterTransformer: ParameterTransformer,
        private returnTransformer: ReturnTransformer
    ) {
        super()
    }

    updateScriptFunction(
        scriptFunction: arkts.ScriptFunction,
        name: string = "",
    ): arkts.ScriptFunction {
        if (!scriptFunction.body) {
            return scriptFunction
        }
        const [body, memoParametersDeclaration, syntheticReturnStatement] = updateFunctionBody(
            scriptFunction.body,
            scriptFunction.parameters,
            scriptFunction.returnTypeAnnotation,
            this.positionalIdTracker.id(name),
        )
        const afterParameterTransformer = this.parameterTransformer
            .withParameters(scriptFunction.parameters)
            .skip(memoParametersDeclaration)
            .visitor(body)
        const afterReturnTransformer = this.returnTransformer
            .skip(syntheticReturnStatement)
            .visitor(afterParameterTransformer)
        const updatedParameters = scriptFunction.parameters.map((param) => {
            if (hasMemoAnnotation(param)) {
                if (!(param.type instanceof arkts.ETSFunctionType)) {
                    throw "ArrowFunctionExpression expected for @memo parameter of @memo function"
                }
                param.type = arkts.factory.createFunctionType(
                    arkts.factory.createFunctionSignature(
                        undefined,
                        [...factory.createHiddenParameters(), ...param.type.params],
                        param.type.returnType,
                    ),
                    arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_ARROW,
                )
            }
            return param
        })
        return arkts.factory.updateScriptFunction(
            scriptFunction,
            afterReturnTransformer,
            scriptFunction.scriptFunctionFlags,
            scriptFunction.modifiers,
            false,
            scriptFunction.ident,
            [...factory.createHiddenParameters(), ...updatedParameters],
            scriptFunction.typeParamsDecl,
            scriptFunction.returnTypeAnnotation
        )
    }

    visitor(beforeChildren: arkts.AstNode): arkts.AstNode {
        // TODO: Remove (currently annotations are lost on visitor)
        const methodDefinitionHasMemoAnnotation =
            beforeChildren instanceof arkts.MethodDefinition && hasMemoAnnotation(beforeChildren.scriptFunction)
        const methodDefinitionHasMemoIntrinsicAnnotation =
            beforeChildren instanceof arkts.MethodDefinition && hasMemoIntrinsicAnnotation(beforeChildren.scriptFunction)

        const node = this.visitEachChild(beforeChildren)
        if (node instanceof arkts.MethodDefinition && node.scriptFunction.body) {
            if (methodDefinitionHasMemoAnnotation || methodDefinitionHasMemoIntrinsicAnnotation) {
                return arkts.factory.updateMethodDefinition(
                    node,
                    arkts.Es2pandaMethodDefinitionKind.METHOD_DEFINITION_KIND_METHOD,
                    node.name,
                    arkts.factory.createFunctionExpression(
                        this.updateScriptFunction(node.scriptFunction, node.name.name),
                    ),
                    node.modifiers,
                    false
                )
            }
        }
        if (node instanceof arkts.CallExpression) {
            const expr = node.expression
            const decl = arkts.getDecl(expr)
            if (decl instanceof arkts.MethodDefinition && (hasMemoAnnotation(decl.scriptFunction) || hasMemoIntrinsicAnnotation(decl.scriptFunction))) {
                const updatedArguments = node.arguments.map((it, index) => {
                    if (decl.scriptFunction.parameters[index].type instanceof arkts.ETSFunctionType) {
                        if (!hasMemoAnnotation(decl.scriptFunction.parameters[index]) && !hasMemoIntrinsicAnnotation(decl.scriptFunction.parameters[index])) {
                            return factory.createComputeExpression(this.positionalIdTracker.id(decl.name.name), it)
                        }
                        if (!(it instanceof arkts.ArrowFunctionExpression)) {
                            throw "ArrowFunctionExpression expected for @memo argument of @memo function"
                        }
                        return this.updateScriptFunction(it.scriptFunction)
                    }
                    return it
                })
                return arkts.factory.updateCallExpression(
                    node,
                    node.expression,
                    undefined,
                    [...factory.createHiddenArguments(this.positionalIdTracker.id(decl.name.name)), ...updatedArguments]
                )
            }
        }
        return node
    }
}
