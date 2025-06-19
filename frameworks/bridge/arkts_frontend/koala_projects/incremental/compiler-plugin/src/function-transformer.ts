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
import { AbstractVisitor } from "./AbstractVisitor"
import { Rewrite } from './transformation-context';
import {
    FunctionKind,
    Tracer,
    idPlusKey,
    PositionalIdTracker,
    wrapInCompute,
    RuntimeNames,
    runtimeIdentifier,
    isMemoKind,
    hiddenParameters,
    createComputeScope,
    isVoidOrNotSpecified,
    localStateStatement,
    isTrackableParameter,
    hasStaticModifier,
    isMethodOfStableClass,
    skipParenthesizedExpression,
    isThis,
    isThisStable,
} from "./util"


function callIsIntrinsicContext(node: ts.Identifier): boolean {
    return ts.idText(node) == RuntimeNames.__CONTEXT
}

function callIsIntrinsicId(node: ts.Identifier): boolean {
    return ts.idText(node) == RuntimeNames.__ID
}

function callIsIntrinsicKey(node: ts.Identifier): boolean {
    return ts.idText(node) == RuntimeNames.__KEY
}

function transformIntrinsicContextCall(node: ts.CallExpression): ts.Identifier {
    return runtimeIdentifier(RuntimeNames.CONTEXT)
}

function transformIntrinsicIdCall(node: ts.CallExpression): ts.Identifier {
    return runtimeIdentifier(RuntimeNames.ID)
}

function transformIntrinsicKeyCall(positionalIdTracker: PositionalIdTracker, node: ts.CallExpression): ts.Expression {
    return positionalIdTracker.id(RuntimeNames.__KEY)
}

// Given a lambda type (foo:XXX, bar:YYY) => ZZZ
// returns the type name XXX of the first argument.
// Or undefined if such name can't be found.
function firstArgTypeName(lambdaType: ts.TypeNode|undefined): string|undefined {
    if (lambdaType === undefined) return undefined
    if (!ts.isFunctionTypeNode(lambdaType)) return undefined
    const firstArg = lambdaType?.parameters[0]
    if (!firstArg) return undefined
    if (!firstArg.type) return undefined
    if (!ts.isTypeReferenceNode(firstArg.type)) return undefined
    if (!ts.isIdentifier(firstArg.type.typeName)) return undefined
    return ts.idText(firstArg.type.typeName)
}

export class FunctionTransformer extends AbstractVisitor {
    constructor(
        public tracer: Tracer,
        public typechecker: ts.TypeChecker,
        public sourceFile: ts.SourceFile,
        public rewrite: Rewrite,
        ctx: ts.TransformationContext
    ) {
        super(ctx)
    }

    trace(msg: any) {
        this.tracer.trace(msg)
    }


/*
// The context.compute rewrite with lambda

function foo0(p1, p2) {
    const ps1 = context.parState()
    const ps2 = context.parState()
    return context.compute(__contex, __id + "id", () => {
        if (a) return "1"
        return "2"
        // body
    })
}

// The lambda-less rewrite

function foo1(p1, p2): R {
    const scope = __context().scope<R>(__id() + "id", 2)
    const ps1 = scope.param(0, p1, "name p1")
    const ps2 = scope.param(1, p2, "name p2")
    if (scope.unchanged) return scope.cached

    // body
    if (a) return scope.recache("1")
    return scope.recache("2")
}
*/

    // Given a function parameter
    //
    // /** @memo */
    // function foo(width: number)
    //
    // produces a tracking state variable for it
    //
    // const __memo_state_width = context.param(width)
    //
    parameterStateStatement(parameter: ts.ParameterDeclaration, parameterIndex: number): ts.Statement|undefined {
        if (!ts.isIdentifier(parameter.name)) return undefined
        const parameterNameString = ts.idText(parameter.name)
        const parameterName = ts.factory.createIdentifier(parameterNameString)
        return localStateStatement(
            parameterNameString,
            parameterName,
            parameterIndex
        )
    }

    parameterStateStatements(
        originalParameters: ReadonlyArray<ts.ParameterDeclaration>,
        hasThis: boolean
    ): ts.Statement[] {
        const trackable = originalParameters.filter(parameter => isTrackableParameter(this.sourceFile, parameter))

        const statements =  trackable.map(
            (parameter, index) => this.parameterStateStatement(parameter, hasThis ? index + 1 : index )
        ).filter(it => it !== undefined) as ts.Statement[]

        if (hasThis) {
            statements.push(
                localStateStatement(
                    "this", ts.factory.createThis(), 0)
            )
        }
        return statements
    }

    createEarlyReturn(originalType: ts.TypeNode | undefined): ts.Statement {
        return ts.factory.createIfStatement(
            ts.factory.createPropertyAccessExpression(
                runtimeIdentifier(RuntimeNames.SCOPE),
                runtimeIdentifier(RuntimeNames.INTERNAL_VALUE_OK),
            ),
            isVoidOrNotSpecified(originalType)
                ? ts.factory.createBlock([
                    ts.factory.createExpressionStatement(
                        ts.factory.createPropertyAccessExpression(
                            runtimeIdentifier(RuntimeNames.SCOPE),
                            runtimeIdentifier(RuntimeNames.INTERNAL_VALUE),
                        )),
                    createSyntheticReturn(undefined)
                ])
                : isThis(originalType) && isThisStable(this.typechecker, this.sourceFile, originalType)
                    ? ts.factory.createBlock([
                        ts.factory.createExpressionStatement(ts.factory.createPropertyAccessExpression(
                            runtimeIdentifier(RuntimeNames.SCOPE),
                            runtimeIdentifier(RuntimeNames.INTERNAL_VALUE),
                        )),
                        createSyntheticReturn(ts.factory.createThis())
                    ])
                    : createSyntheticReturn(
                        ts.factory.createPropertyAccessExpression(
                            runtimeIdentifier(RuntimeNames.SCOPE),
                            runtimeIdentifier(RuntimeNames.INTERNAL_VALUE),
                        )
                    )
        )
    }

    transformComputeCallable(
        originalParameters: ts.NodeArray<ts.ParameterDeclaration>,
        originalBody: ts.ConciseBody | undefined,
        originalType: ts.TypeNode | undefined,
        hasThis: boolean = false
    ): {
        newParameters: ts.ParameterDeclaration[],
            newBody: ts.FunctionBody|undefined
    } {
        const additionalParameters = hiddenParameters(this.rewrite)
        const newParameters = additionalParameters.concat(originalParameters)

        if (!originalBody) return {newParameters, newBody: undefined}

        const parameterStates = this.parameterStateStatements(originalParameters, hasThis)
        const scope = createComputeScope(
            parameterStates.length, 
            idPlusKey(this.rewrite.positionalIdTracker), 
            isThis(originalType) && isThisStable(this.typechecker, this.sourceFile, originalType)
                ? ts.factory.createKeywordTypeNode(ts.SyntaxKind.VoidKeyword)
                : originalType)
        const earlyReturn = this.createEarlyReturn(originalType)

        let newStatements: ts.Statement[]
        if (ts.isBlock(originalBody)) {
            const lastStatement = originalBody.statements[originalBody.statements.length - 1]
            if (!lastStatement || !ts.isReturnStatement(lastStatement)) {
                newStatements = [
                    scope,
                    ...parameterStates,
                    earlyReturn,
                    ...originalBody.statements,
                    ts.factory.createReturnStatement()
                ]
            } else {
                newStatements = [
                    scope,
                    ...parameterStates,
                    earlyReturn,
                    ...originalBody.statements
                ]
            }
        } else { // It is an expression or undefined
            newStatements = [
                scope,
                ...parameterStates,
                earlyReturn,
                ts.factory.createReturnStatement(originalBody)
            ]
        }

        const newBody = ts.factory.createBlock(
            newStatements,
            true
        )

        return {newParameters, newBody}
    }

    getReturnType(node: ts.FunctionLikeDeclaration): ts.TypeNode | undefined {
        // We mandate explicit return type for all memo functions
        // And only allow it for void case.
        return node.type ?? ts.factory.createKeywordTypeNode(ts.SyntaxKind.VoidKeyword)
    }

    transformComputeMethod(originalMethod: ts.MethodDeclaration): ts.MethodDeclaration {
        const { newParameters, newBody } = this.transformComputeCallable(
            originalMethod.parameters,
            originalMethod.body,
            this.getReturnType(originalMethod),
            (!hasStaticModifier(originalMethod) && !isMethodOfStableClass(this.sourceFile, originalMethod))
        )
        const updatedMethod = ts.factory.updateMethodDeclaration(
            originalMethod,
            originalMethod.modifiers,
            originalMethod.asteriskToken,
            originalMethod.name,
            originalMethod.questionToken,
            originalMethod.typeParameters,
            newParameters,
            originalMethod.type,
            newBody
        )

        return updatedMethod
    }

    transformComputeArrow(originalArrow: ts.ArrowFunction): ts.ArrowFunction {
        const { newParameters, newBody } = this.transformComputeCallable(
            originalArrow.parameters,
            originalArrow.body,
            this.getReturnType(originalArrow)
        )
        const updatedArrow = ts.factory.updateArrowFunction(
            originalArrow,
            originalArrow.modifiers,
            originalArrow.typeParameters,
            newParameters,
            originalArrow.type,
            ts.factory.createToken(ts.SyntaxKind.EqualsGreaterThanToken),
            newBody!
        )

        return updatedArrow
    }

    transformComputeFunctionExpression(original: ts.FunctionExpression): ts.FunctionExpression {
        const { newParameters, newBody } = this.transformComputeCallable(
            original.parameters,
            original.body,
            this.getReturnType(original)
        )
        const updated = ts.factory.updateFunctionExpression(
            original,
            original.modifiers,
            original.asteriskToken,
            original.name,
            original.typeParameters,
            newParameters,
            original.type,
            newBody!
        )

        return updated
    }

    transformComputeFunctionType(original: ts.FunctionTypeNode): ts.FunctionTypeNode {
        const { newParameters, newBody } = this.transformComputeCallable(
            original.parameters,
            undefined,
            undefined
        )
        const updated = ts.factory.updateFunctionTypeNode(
            original,
            original.typeParameters,
            ts.factory.createNodeArray(newParameters),
            original.type
        )

        return updated
    }

    maybeTransformFunctionType(original: ts.TypeNode): ts.TypeNode {
        if (!ts.isFunctionTypeNode(original)) return original
        return this.transformComputeFunctionType(original)
    }

    transformGetter(original: ts.GetAccessorDeclaration): ts.GetAccessorDeclaration {
        return ts.factory.updateGetAccessorDeclaration(
            original,
            original.modifiers,
            original.name,
            original.parameters,
            original.type ? this.maybeTransformFunctionType(original.type) : undefined,
            original.body
        )
    }

    transformSetter(original: ts.SetAccessorDeclaration): ts.SetAccessorDeclaration {
        return ts.factory.updateSetAccessorDeclaration(
            original,
            original.modifiers,
            original.name,
            original.parameters,
            original.body
        )
    }

    transformComputeMethodSignature(original: ts.MethodSignature): ts.MethodSignature {
        const { newParameters, newBody } = this.transformComputeCallable(
            original.parameters,
            undefined,
            undefined
        )
        const updated = ts.factory.updateMethodSignature(
            original,
            original.modifiers,
            original.name,
            original.questionToken,
            original.typeParameters,
            ts.factory.createNodeArray(newParameters),
            original.type
        )

        return updated
    }


    transformComputeFunction(originalFunction: ts.FunctionDeclaration): ts.FunctionDeclaration {
        const { newParameters, newBody } = this.transformComputeCallable(
            originalFunction.parameters,
            originalFunction.body,
            this.getReturnType(originalFunction)
        )
        const updatedFunction = ts.factory.updateFunctionDeclaration(
            originalFunction,
            originalFunction.modifiers,
            originalFunction.asteriskToken,
            originalFunction.name,
            originalFunction.typeParameters,
            newParameters,
            originalFunction.type,
            newBody
        )

        return updatedFunction
    }

    transformIntrinsicMethod(originalMethod: ts.MethodDeclaration): ts.MethodDeclaration {
        const updatedMethod = ts.factory.updateMethodDeclaration(
            originalMethod,
            originalMethod.modifiers,
            originalMethod.asteriskToken,
            originalMethod.name,
            originalMethod.questionToken,
            originalMethod.typeParameters,
            hiddenParameters(this.rewrite).concat(originalMethod.parameters),
            originalMethod.type,
            originalMethod.body
        )

        return updatedMethod
    }

    transformIntrinsicFunction(originalFunction: ts.FunctionDeclaration): ts.FunctionDeclaration {
        const updatedFunction = ts.factory.updateFunctionDeclaration(
            originalFunction,
            originalFunction.modifiers,
            originalFunction.asteriskToken,
            originalFunction.name,
            originalFunction.typeParameters,
            hiddenParameters(this.rewrite).concat(originalFunction.parameters),
            originalFunction.type,
            originalFunction.body
        )

        return updatedFunction
    }

    transformCallWithName(node: ts.CallExpression, sourceFile: ts.SourceFile, name: string): ts.CallExpression {
        const args = node.arguments.slice()
        const idExpression = idPlusKey(this.rewrite.positionalIdTracker)

        args.unshift(
            idExpression
        )
        args.unshift(
            runtimeIdentifier(RuntimeNames.CONTEXT),
        )

        const update = ts.factory.updateCallExpression(
            node,
            node.expression,
            node.typeArguments,
            args
        )
        return update
    }

    transformCall(node: ts.CallExpression, sourceFile: ts.SourceFile): ts.CallExpression {
        const identifier = node.expression
        if (!identifier || !ts.isIdentifier(identifier)) {
            throw `Could not transform @memo call to ${identifier}`
        }
        const name = ts.idText(identifier)

        return this.transformCallWithName(node, sourceFile, name)
    }

    transformMethodCall(node: ts.CallExpression, sourceFile: ts.SourceFile): ts.CallExpression {
        if (!ts.isPropertyAccessExpression(node.expression)) {
            throw `Unexpected expression kind ${ts.SyntaxKind[node.expression.kind]}`
        }
        const member = node.expression.name
        if (!member || !ts.isIdentifier(member)) {
            throw `Could not transform @memo call to ${member}`
        }
        const name = ts.idText(member)
        return this.transformCallWithName(node, sourceFile, name)
    }

    wrapInCompute(node: ts.ObjectLiteralExpression | ts.ArrowFunction | ts.AsExpression): ts.Expression {
        if (ts.isAsExpression(node)) {
            if (!ts.isObjectLiteralExpression(node.expression)) return node
        }
        return wrapInCompute(node, idPlusKey(this.rewrite.positionalIdTracker))
    }

    transformTransformedType(node: ts.TypeReferenceNode): ts.TypeReferenceNode {
        return ts.factory.updateTypeReferenceNode(
            node,
            ts.factory.createIdentifier("number"), // Yes, just number.
            undefined
        )
    }

    visitCall(node: ts.CallExpression): ts.Expression {
        if (ts.isParenthesizedExpression(node.expression)) {
            node = ts.factory.updateCallExpression(
                node,
                skipParenthesizedExpression(node.expression),
                undefined,
                node.arguments
            )
        }
        let transformed: ts.Expression | undefined = undefined
        if (ts.isIdentifier(node.expression)) {
            const identifier = node.expression
            if (callIsIntrinsicContext(identifier)) {
                transformed = transformIntrinsicContextCall(node)
            } else if (callIsIntrinsicId(identifier)) {
                transformed = transformIntrinsicIdCall(node)
            } else if (callIsIntrinsicKey(identifier)) {
                transformed = transformIntrinsicKeyCall(this.rewrite.positionalIdTracker, node)
            } else {
                const kind = this.rewrite.callTable.get(ts.getOriginalNode(node, ts.isCallExpression))
                if (kind) {
                    transformed = this.transformCall(node, this.sourceFile)
                }
            }
        } else if (ts.isPropertyAccessExpression(node.expression)) {
            const kind = this.rewrite.callTable.get(ts.getOriginalNode(node, ts.isCallExpression))
            if (kind) {
                transformed = this.transformMethodCall(node, this.sourceFile)
            }
        }
        return transformed ?? node
    }

    visitor(beforeChildren: ts.Node): ts.Node {
        // Note that visitEachChild can create a new node if its children have changed.
        const node = this.visitEachChild(beforeChildren)
        let transformed: ts.Node|undefined = undefined

        if (ts.isCallExpression(node)) {
            transformed = this.visitCall(node)
        } else if (ts.isFunctionDeclaration(node)) {
            const originalNode = ts.getOriginalNode(node, ts.isFunctionDeclaration)
            switch (this.rewrite.functionTable.get(originalNode)) {
                case FunctionKind.MEMO:
                    transformed = this.transformComputeFunction(node)
                    break;
                case FunctionKind.MEMO_INTRINSIC:
                    transformed = this.transformIntrinsicFunction(node)
                    break;
            }
        } else if (ts.isMethodDeclaration(node)) {
            const originalNode = ts.getOriginalNode(node, ts.isMethodDeclaration)
            switch (this.rewrite.functionTable.get(originalNode)) {
                case FunctionKind.MEMO:
                    transformed = this.transformComputeMethod(node)
                    break;
                case FunctionKind.MEMO_INTRINSIC:
                    transformed = this.transformIntrinsicMethod(node)
                    break;
            }
        } else if (ts.isArrowFunction(node)) {
            const originalNode = ts.getOriginalNode(node, ts.isArrowFunction)
            switch (this.rewrite.functionTable.get(originalNode)) {
                case FunctionKind.MEMO:
                    transformed = this.transformComputeArrow(node)
                    break
                case FunctionKind.MEMO_INTRINSIC:
                    break
                default: {
                    const originalNode = ts.getOriginalNode(node, ts.isArrowFunction)
                    const originalParent = originalNode.parent
                    if (originalParent && ts.isCallExpression(originalParent)) {
                        if (isMemoKind(this.rewrite.callTable.get(originalParent)))
                            transformed = this.wrapInCompute(node)
                    }
                }
                /*
                    TODO: no memo:intrinsic lambdas for now.
                */
            }
        } else if (ts.isFunctionExpression(node)) {
            const originalNode = ts.getOriginalNode(node, ts.isFunctionExpression)
            switch (this.rewrite.functionTable.get(originalNode)) {
                case FunctionKind.MEMO:
                    transformed = this.transformComputeFunctionExpression(node)
                    break;
                /*
                    TODO: no memo:intrinsic lambdas for now.
                */
            }
        } else if (ts.isFunctionTypeNode(node)) {
            const originalNode = ts.getOriginalNode(node, ts.isFunctionTypeNode)
            switch (this.rewrite.functionTable.get(originalNode)) {
                case FunctionKind.MEMO:
                    transformed = this.transformComputeFunctionType(node)
                    break;
                /*
                    TODO: no memo:intrinsic lambdas for now.
                */
            }
        } else if (ts.isMethodSignature(node)) {
            const originalNode = ts.getOriginalNode(node, ts.isMethodSignature)
            switch (this.rewrite.functionTable.get(originalNode)) {
                case FunctionKind.MEMO:
                    transformed = this.transformComputeMethodSignature(node)
                    break;
                /*
                    TODO: no memo:intrinsic signatures for now.
                */
            }
        } else if (ts.isGetAccessor(node)) {
            const originalNode = ts.getOriginalNode(node, ts.isGetAccessorDeclaration)
            if (this.rewrite.functionTable.get(originalNode) == FunctionKind.MEMO) {
                transformed = this.transformGetter(node)
            }
        } else if (ts.isSetAccessor(node)) {
            const originalNode = ts.getOriginalNode(node, ts.isSetAccessorDeclaration)
            if (this.rewrite.functionTable.get(originalNode) == FunctionKind.MEMO) {
                transformed = this.transformSetter(node)
            }
        } else if (ts.isObjectLiteralExpression(node)) {
            const originalNode = ts.getOriginalNode(node, ts.isObjectLiteralExpression)
            const originalParent = originalNode.parent
            if (originalParent && ts.isCallExpression(originalParent)) {
                if (isMemoKind(this.rewrite.callTable.get(originalParent)))
                    transformed = this.wrapInCompute(node)
            }
        } else if (ts.isAsExpression(node)) {
            const originalNode = ts.getOriginalNode(node, ts.isAsExpression)
            const originalParent = originalNode.parent
            if (originalParent && ts.isCallExpression(originalParent)) {
                if (isMemoKind(this.rewrite.callTable.get(originalParent)))
                    transformed = this.wrapInCompute(node)
            }
        }
        else if (ts.isTypeReferenceNode(node)) {
            if (ts.isIdentifier(node.typeName) && ts.idText(node.typeName) == RuntimeNames.TRANSFORMED_TYPE) {
                transformed = this.transformTransformedType(node)
            }
        }
        return transformed ?? node
    }
}

function createSyntheticReturn(node: ts.Expression | undefined): ts.ReturnStatement {
    return ts.factory.createReturnStatement(
        ts.factory.createCallExpression(
            runtimeIdentifier(RuntimeNames.SYNTHETIC_RETURN_MARK),
            undefined,
            node ? [node] : undefined
        )
    )
}
