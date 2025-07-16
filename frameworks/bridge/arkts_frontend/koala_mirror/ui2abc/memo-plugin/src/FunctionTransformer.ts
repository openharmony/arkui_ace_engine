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
import {
    MemoFunctionKind,
    PositionalIdTracker,
    RuntimeNames,
    getDeclResolveGensym,
    hasMemoStableAnnotation,
    hasWrapAnnotation,
    isTrackableParam,
    moveToFront,
    shouldWrap,
} from "./utils"
import { ParameterTransformer, ParamInfo } from "./ParameterTransformer"
import { ReturnTransformer } from "./ReturnTranformer"
import { InternalsTransformer } from "./InternalsTransformer"
import { SignatureTransformer } from "./SignatureTransformer"
import {
    castParameters,
    getName,
    getParams,
    isMemo,
    isMemoizable,
    memoizableHasReceiver,
    parametersBlockHasReceiver,
} from "./api-utils"

function needThisRewrite(hasReceiver: boolean, isStatic: boolean, stableThis: boolean) {
    return hasReceiver && !isStatic && !stableThis
}

function mayAddLastReturn(node: arkts.BlockStatement): boolean {
    return node.statements.length == 0 || (
        !arkts.isReturnStatement(node.statements[node.statements.length - 1]) &&
        !arkts.isThrowStatement(node.statements[node.statements.length - 1])
    )
}

function dropUntrackableParameters(parameters: readonly arkts.ETSParameterExpression[], trackContentParam: boolean) {
    return parameters.filter((it, index) => isTrackableParam(it, index + 1 == parameters.length, trackContentParam))
}

function getMemoParameterIdentifiers(parameters: readonly arkts.ETSParameterExpression[], trackContentParam: boolean) {
    return [
        ...dropUntrackableParameters(parameters, trackContentParam).map(it => {
            return { ident: it.ident!, param: it }
        })
    ]
}

function fixGensymParams(params: ParamInfo[], body: arkts.BlockStatement) {
    var gensymParamsCount = 0;
    for (var i = 0; i < params.length; i++) {
        if (params[i].ident.name.startsWith(RuntimeNames.GENSYM)) {
            if (gensymParamsCount >= body.statements.length) {
                throw new Error(`Expected ${params[i].ident.name} replacement to original parameter`)
            }
            const declaration = body.statements[gensymParamsCount]
            if (!arkts.isVariableDeclaration(declaration)) {
                throw new Error(`Expected ${params[i].ident.name} replacement to original parameter`)
            }
            if (!arkts.isIdentifier(declaration.declarators[0].id)) {
                throw new Error(`Expected ${params[i].ident.name} replacement to original parameter`)
            }
            params[i].ident = declaration.declarators[0].id
            gensymParamsCount++
        }
    }
    return gensymParamsCount
}

function updateFunctionBody(
    node: arkts.BlockStatement,
    parameters: readonly arkts.ETSParameterExpression[],
    returnTypeAnnotation: arkts.TypeNode | undefined,
    hasReceiver: boolean,
    isStatic: boolean,
    stableThis: boolean,
    hash: arkts.Expression,
    addLogging: boolean,
    trackContentParam: boolean,
): [
    arkts.BlockStatement,
    ParamInfo[],
    arkts.VariableDeclaration | undefined,
    arkts.ReturnStatement | arkts.BlockStatement | undefined,
] {
    const shouldCreateMemoThisParam = needThisRewrite(hasReceiver, isStatic, stableThis) && !parametersBlockHasReceiver(parameters)
    const parameterIdentifiers = getMemoParameterIdentifiers(parameters, trackContentParam)
    const gensymParamsCount = fixGensymParams(parameterIdentifiers, node)
    const parameterNames = [...(shouldCreateMemoThisParam ? [RuntimeNames.THIS.valueOf()] : []), ...parameterIdentifiers.map(it => it.ident.name)]
    const scopeDeclaration = factory.createScopeDeclaration(
        arkts.isTSThisType(returnTypeAnnotation) ? undefined : returnTypeAnnotation,
        hash, parameterNames.length
    )
    const memoParametersDeclaration = parameterNames.length ? factory.createMemoParameterDeclaration(parameterNames) : undefined
    const syntheticReturnStatement = factory.createSyntheticReturnStatement(returnTypeAnnotation)
    const unchangedCheck = [factory.createIfStatementWithSyntheticReturnStatement(syntheticReturnStatement)]
    const thisParamSubscription = (arkts.isTSThisType(returnTypeAnnotation) && !stableThis)
        ? [arkts.factory.createExpressionStatement(factory.createMemoParameterAccess("=t"))]
        : []
    return [
        arkts.factory.updateBlockStatement(
            node,
            [
                ...node.statements.slice(0, gensymParamsCount),
                scopeDeclaration,
                ...(memoParametersDeclaration ? [memoParametersDeclaration] : []),
                ...(addLogging ? [factory.createMemoParameterModifiedLogging(parameterNames)] : []),
                ...(addLogging ? [factory.createUnchangedLogging()] : []),
                ...unchangedCheck,
                ...thisParamSubscription,
                ...node.statements.slice(gensymParamsCount),
                ...(mayAddLastReturn(node) ? [arkts.factory.createReturnStatement(undefined)] : []),
            ]
        ),
        parameterIdentifiers,
        memoParametersDeclaration,
        syntheticReturnStatement,
    ]
}

class FunctionTransformerOptions {
    receiverContext?: boolean
}

export class FunctionTransformer extends arkts.AbstractVisitor {
    constructor(
        public scriptFunctions: Map<arkts.KNativePointer, MemoFunctionKind>,
        public typeAliases: Map<arkts.KNativePointer, MemoFunctionKind>,
        private positionalIdTracker: PositionalIdTracker,
        private signatureTransformer: SignatureTransformer,
        private internalsTransformer: InternalsTransformer,
        private parameterTransformer: ParameterTransformer,
        private returnTransformer: ReturnTransformer,
        private addLogging: boolean,
        private trackContentParam: boolean,
    ) {
        super()
    }

    private stable: number = 0

    public modified: boolean = false

    enter(node: arkts.AstNode) {
        if (arkts.isClassDefinition(node)) {
            if (hasMemoStableAnnotation(node)) {
                this.stable++
            }
        }
        return this
    }

    exit(node: arkts.AstNode) {
        if (arkts.isClassDefinition(node)) {
            if (hasMemoStableAnnotation(node)) {
                this.stable--
            }
        }
        return this
    }

    fixObjectArg(arg: arkts.Expression, param: arkts.ETSParameterExpression) {
        if (param.typeAnnotation && (arkts.isObjectExpression(arg) || hasWrapAnnotation(param))) {
            return arkts.factory.createTSAsExpression(
                arg,
                param.typeAnnotation.clone(),
                false
            )
        }
        return arg
    }

    updateScriptFunction(
        scriptFunction: arkts.ScriptFunction,
        hasReceiver: boolean,
        name: string = "",
    ): arkts.ScriptFunction {
        if (!scriptFunction.body || !arkts.isBlockStatement(scriptFunction.body)) {
            return scriptFunction
        }
        const afterInternalsTransformer = this.internalsTransformer.visitor(scriptFunction.body) as arkts.BlockStatement
        const kind = this.scriptFunctions.get(scriptFunction.originalPeer) ?? MemoFunctionKind.NONE
        if (kind == MemoFunctionKind.INTRINSIC || kind == MemoFunctionKind.ENTRY) {
            return arkts.factory.updateScriptFunction(
                scriptFunction,
                afterInternalsTransformer,
                scriptFunction.typeParams,
                scriptFunction.params,
                scriptFunction.returnTypeAnnotation,
                false,
                scriptFunction.flags,
                scriptFunction.modifierFlags,
                scriptFunction.id,
                scriptFunction.annotations,
            )
        }

        const isStatic = (scriptFunction.modifierFlags & arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_STATIC) != 0
        const isStableThis = this.stable > 0
        const [body, parameterIdentifiers, memoParametersDeclaration, syntheticReturnStatement] = updateFunctionBody(
            afterInternalsTransformer,
            castParameters(scriptFunction.params),
            scriptFunction.returnTypeAnnotation,
            hasReceiver,
            isStatic,
            isStableThis,
            this.positionalIdTracker.id(name),
            this.addLogging,
            this.trackContentParam,
        )
        const afterParameterTransformer = this.parameterTransformer
            .withThis(needThisRewrite(hasReceiver, isStatic, isStableThis))
            .withParameters(parameterIdentifiers)
            .skip(memoParametersDeclaration)
            .visitor(body)
        const afterReturnTransformer = this.returnTransformer
            .skip(syntheticReturnStatement)
            .rewriteThis(isStableThis)
            .visitor(afterParameterTransformer)
        return arkts.factory.updateScriptFunction(
            scriptFunction,
            afterReturnTransformer,
            scriptFunction.typeParams,
            scriptFunction.params,
            scriptFunction.returnTypeAnnotation,
            false,
            scriptFunction.flags,
            scriptFunction.modifierFlags,
            scriptFunction.id,
            scriptFunction.annotations,
        )
    }

    transformScriptFunction(node: arkts.ScriptFunction, options?: FunctionTransformerOptions): arkts.ScriptFunction {
        const kind = this.scriptFunctions.get(node.originalPeer) ?? MemoFunctionKind.NONE // can it actually be undefined?
        if (kind === MemoFunctionKind.NONE) {
            return this.signatureTransformer.visitor(node)
        }
        this.modified = true
        return this.signatureTransformer.visitor(
            this.updateScriptFunction(
                node,
                node.hasReceiver || (options?.receiverContext == true),
                node.id?.name,
            )
        )
    }

    transformCallExpression(node: arkts.CallExpression, options?: FunctionTransformerOptions): arkts.CallExpression {
        const expr = node.callee
        const decl = getDeclResolveGensym(expr!)
        if (decl === undefined) {
            return node
        }
        if (!isMemoizable(decl) || !isMemo(decl)) {
            return node
        }

        const params = getParams(decl)
        const updatedArguments = node.arguments.map((it, index) => {
            if (!params[index]) return it
            // Improve: this is not quite correct.
            // This code is too dependent on the availability of parameter declaration and its type
            // Most of the decisions should be taken basing on the fact that this is a memo call
            if (shouldWrap(params[index], index + 1 == params.length, this.trackContentParam, it)) {
                return factory.createComputeExpression(this.positionalIdTracker.id(getName(decl)), this.fixObjectArg(it, params[index]))
            }
            return this.fixObjectArg(it, params[index])
        })
        this.modified = true

        let newArgs = [...factory.createHiddenArguments(this.positionalIdTracker.id(getName(decl))), ...updatedArguments]
        if (memoizableHasReceiver(decl)) {
            newArgs = moveToFront(newArgs, 2)
        }
        return arkts.factory.updateCallExpression(
            node,
            node.callee,
            newArgs,
            node.typeParams,
            node.isOptional,
            node.hasTrailingComma,
            node.trailingBlock,
        )
    }

    transformETSFunctionType(node: arkts.ETSFunctionType, options?: FunctionTransformerOptions): arkts.ETSFunctionType {
        return this.signatureTransformer.visitor(node)
    }

    visitor(beforeChildren: arkts.ETSModule, options?: FunctionTransformerOptions): arkts.ETSModule
    visitor(beforeChildren: arkts.AstNode, options?: FunctionTransformerOptions): arkts.AstNode {
        this.enter(beforeChildren)
        const node = this.visitEachChild(beforeChildren, {
            receiverContext:
                (options?.receiverContext || arkts.isMethodDefinition(beforeChildren)) && !arkts.isScriptFunction(beforeChildren)
        })
        this.exit(beforeChildren)
        if (arkts.isScriptFunction(node)) {
            return this.transformScriptFunction(node, options)
        }
        if (arkts.isCallExpression(node)) {
            return this.transformCallExpression(node, options)
        }
        if (arkts.isETSFunctionType(node)) {
            return this.transformETSFunctionType(node, options)
        }
        return node
    }
}
