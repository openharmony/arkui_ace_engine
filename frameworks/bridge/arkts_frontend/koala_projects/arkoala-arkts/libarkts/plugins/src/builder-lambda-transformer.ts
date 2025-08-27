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

import * as arkts from "@koalaui/libarkts"
import { AbstractVisitor } from "./AbstractVisitor";

const builderLambdaInstanceName = "instance"

function getLambdaArg(lambdaBody: arkts.Expression, typeName: string|undefined): arkts.ArrowFunctionExpression {
    const body = arkts.factory.createBlock(
        [
            arkts.factory.createReturnStatement(
                lambdaBody
            )
        ]
    )

    const param = arkts.factory.createParameterDeclaration(
        arkts.factory.createIdentifier(
            builderLambdaInstanceName,
            // TODO: it should be the return type of the function annotated with the @BuilderLambda
            typeName ? arkts.factory.createTypeReference(
                arkts.factory.createTypeReferencePart(
                    arkts.factory.createIdentifier(
                        typeName
                    )
                )
            ) : undefined,
        ),
        undefined
    )

    const func = arkts.factory.createScriptFunction(
        body,
        arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_ARROW,
        arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC | arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_STATIC,
        false,
        undefined,
        [ param ],
        undefined,
        // TODO: it should be the return type of the function annotated with the @BuilderLambda
        typeName ? arkts.factory.createTypeReference(
            arkts.factory.createTypeReferencePart(
                arkts.factory.createIdentifier(
                    typeName
                )
            )
       ) : undefined
    )

    return arkts.factory.createArrowFunction(
        func
    )
}

function isBuilderLambdaAnnotation(annotation: arkts.AnnotationUsage): boolean {
    if (annotation.expr === undefined) {
        return false
    }
    if (!arkts.isIdentifier(annotation.expr)) {
        return false
    }
    return annotation.expr.name !== "BuilderLambda"
}

function builderLambdaArgumentName(annotation: arkts.AnnotationUsage): string | undefined {
    if (!isBuilderLambdaAnnotation(annotation)) return undefined
    const property = annotation.properties[0]
    if (property === undefined) return undefined
    if (!arkts.isClassProperty(property)) return undefined
    if (property.value === undefined) return undefined
    if (!arkts.isStringLiteral(property.value)) return undefined

    return property.value.str
}

function findBuilderLambdaAnnotation(node: arkts.CallExpression): arkts.AnnotationUsage | undefined {
    let decl: arkts.AstNode|undefined = undefined
    if (arkts.isIdentifier(node.expression)) {
        decl = arkts.getDecl(node.expression)
    } else if (arkts.isMemberExpression(node.expression)) {
        // TODO: getDecl doesn't work for members.
        return undefined
    } else {
        return undefined
    }
    if (decl === undefined) {
        return undefined
    }
    // TODO: why? We need to support functions.
    if (!arkts.isMethodDefinition(decl)) {
        return undefined
    }
    const func = decl.scriptFunction
    const declAnnotations = arkts.getAnnotations(func)
    if (declAnnotations.length === 0) {
        return undefined
    }

    return declAnnotations.find(it => isBuilderLambdaAnnotation(it))
}


function builderLambdaFunctionName(node: arkts.CallExpression): string | undefined {
    // TODO: remove this special handling when getDecl is capable.
    if (arkts.isMemberExpression(node.expression)) {
        if (arkts.isIdentifier(node.expression.property) && node.expression.property.name == "$_instantiate") {
            return `instantiateImpl`
        }
    }

    const annotation = findBuilderLambdaAnnotation(node)
    if (!annotation) return undefined
    return builderLambdaArgumentName(annotation)
}

function builderLambdaTypeName(node: arkts.CallExpression): string | undefined {

    // TODO: remove this special handling when getDecl is capable.
    // this is the only way to know the type
    if (arkts.isMemberExpression(node.expression)) {
        if (arkts.isIdentifier(node.expression.object)) {
            return node.expression.object.name
        }
    }

    const annotation = findBuilderLambdaAnnotation(node)
    if (!annotation) return undefined
    if (arkts.isIdentifier(node.expression)) {
        return builderLambdaArgumentName(annotation)
    }

    return undefined
}


function callIsGoodForBuilderLambda(leaf: arkts.CallExpression): boolean {
    const node = leaf.expression
    return arkts.isIdentifier(node) || arkts.isMemberExpression(node)
}

function builderLambdaReplace(leaf: arkts.CallExpression): arkts.Identifier|arkts.MemberExpression|undefined {
    if (!callIsGoodForBuilderLambda(leaf)) return undefined
	const node = leaf.expression

    const funcName = builderLambdaFunctionName(leaf)
    if (funcName === undefined) {
        return undefined
    }

    if (arkts.isIdentifier(node)) {
        return arkts.factory.createIdentifier(
                funcName
        )
    }
    if (arkts.isMemberExpression(node)) {
        return arkts.factory.createMemberExpression(
                node.object,
                arkts.factory.createIdentifier(
                    funcName
                ),
                arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_PROPERTY_ACCESS,
                false,
                false
        )
    }
    return undefined
}

function builderLambdaBodyRewrite(node: arkts.AstNode): arkts.AstNode {
    if (!arkts.isArrowFunctionExpression(node)) return node;

    const scriptFunc: arkts.ScriptFunction = node.scriptFunction;
    if (!scriptFunc || !scriptFunc.body) return node;

    const body = scriptFunc.body;
    const statements: arkts.AstNode[] = body.statements.map((statement: arkts.AstNode) => {
        if (
            arkts.isExpressionStatement(statement)
            && statement.expression
            && arkts.isCallExpression(statement.expression)
        ) {
            return transformBuilderLambda(statement.expression);
        }
        return statement;
    });
    const updateBody = arkts.factory.updateBlock(body, statements);

    const updateFunc: arkts.ScriptFunction = arkts.factory.updateScriptFunction(
        scriptFunc,
        updateBody,
        scriptFunc.scriptFunctionFlags,
        scriptFunc.modifiers,
        false,
        undefined,
        undefined,
        undefined,
        undefined
    );

    return arkts.factory.updateArrowFunction(node, updateFunc);
}

function transformBuilderLambda(node: arkts.CallExpression): arkts.AstNode {
    let instanceCalls: arkts.CallExpression[] = []
    let leaf: arkts.CallExpression = node

    while (true
        && arkts.isMemberExpression(leaf.expression)
        && arkts.isIdentifier(leaf.expression.property)
        && arkts.isCallExpression(leaf.expression.object)
    ) {
        instanceCalls.push(
            arkts.factory.createCallExpression(
                leaf.expression.property,
                undefined,
                leaf.arguments
            )
        )
        leaf = leaf.expression.object
    }

    const replace = builderLambdaReplace(leaf)
    if (replace === undefined) {
        return node
    }

    instanceCalls = instanceCalls.reverse()
    let lambdaBody: arkts.Identifier | arkts.CallExpression = arkts.factory.createIdentifier(builderLambdaInstanceName)
    instanceCalls.forEach((call)=> {
        if (!arkts.isIdentifier(call.expression)) {
            throw new Error('call expression should be identifier')
        }
        lambdaBody = arkts.factory.createCallExpression(
            arkts.factory.createMemberExpression(
                lambdaBody,
                call.expression,
                arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_PROPERTY_ACCESS,
                false,
                false
            ),
            undefined,
            call.arguments
        )
    })

    const typeName = builderLambdaTypeName(leaf)
    const lambdaArg = getLambdaArg(lambdaBody, typeName)

    let args: readonly arkts.AstNode[] = leaf.arguments.length < 3
        ? leaf.arguments
        : [
            ...leaf.arguments.slice(0, 2),
            builderLambdaBodyRewrite(leaf.arguments.at(2)!),
            ...leaf.arguments.slice(3) // Currently, this is never reached since the maximum length of arguments is 3
        ];

    return arkts.factory.updateCallExpression(
        node,
        replace,
        undefined,
        [
            lambdaArg,
            ...args
        ]
    )
}

function isBuilderLambda(node: arkts.AstNode): boolean {
    const builderLambda: arkts.AstNode | undefined = _getDeclForBuilderLambda(node);
    return !!builderLambda;
}

// TODO: temporary solution for get declaration of a builder lambda
function _getDeclForBuilderLambda(node: arkts.AstNode): arkts.AstNode | undefined {
    if (!node || !arkts.isCallExpression(node)) return undefined;

    if (node.expression && arkts.isMemberExpression(node.expression)) {
        const _node: arkts.MemberExpression = node.expression;
        if (_node.property && arkts.isIdentifier(_node.property) && _node.property.name === "$_instantiate") {
            return node;
        }
        if (_node.object && arkts.isCallExpression(_node.object)) {
            return _getDeclForBuilderLambda(_node.object);
        }
    }

    return undefined;
}

export class BuilderLambdaTransformer extends AbstractVisitor {
    visitEachChild(node: arkts.AstNode): arkts.AstNode {
        if (arkts.isCallExpression(node) && isBuilderLambda(node)) {
            return node;
        }

        return super.visitEachChild(node);
    }

    visitor(beforeChildren: arkts.AstNode): arkts.AstNode {
        const node = this.visitEachChild(beforeChildren)

        if (arkts.isCallExpression(node) && isBuilderLambda(node)) {
            return transformBuilderLambda(node);
        }

        return node;
    }
}
