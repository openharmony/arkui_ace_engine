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
import { styledInstance, uiAttributeName } from "./utils"

function isBuilderLambdaAnnotation(annotation: arkts.AnnotationUsage): boolean {
    if (annotation.expr === undefined) {
        return false
    }
    if (!arkts.isIdentifier(annotation.expr)) {
        return false
    }
    return annotation.expr.name == "BuilderLambda"
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

function getIdentifierScriptFunction(node: arkts.Identifier): arkts.ScriptFunction | undefined {
    const decl = arkts.getDecl(node)
    if (!arkts.isFunctionDeclaration(decl) &&
        !arkts.isMethodDefinition(decl)) return undefined

    return decl.function
}

function getScriptFunction(node: arkts.CallExpression): arkts.ScriptFunction | undefined {
    if (arkts.isIdentifier(node.callee)) {
        return getIdentifierScriptFunction(node.callee)
    }
    if (arkts.isMemberExpression(node.callee)) {
        const decl = arkts.getDecl(node.callee.property!)
        if (!arkts.isMethodDefinition(decl)) return undefined
        return decl.function
    }
    return undefined
}

function findBuilderLambdaAnnotation(func: arkts.ScriptFunction): arkts.AnnotationUsage | undefined {
    const declAnnotations = arkts.getAnnotations(func)
    if (declAnnotations.length === 0) {
        return undefined
    }
    return declAnnotations.find(it => isBuilderLambdaAnnotation(it))
}

function findCallBuilderLambdaAnnotation(node: arkts.CallExpression): arkts.AnnotationUsage | undefined {
    const func = getScriptFunction(node)
    if (func == undefined) return undefined

    return findBuilderLambdaAnnotation(func)
}

export function builderLambdaTargetFunctionName(func: arkts.ScriptFunction): string | undefined {
    const annotation = findBuilderLambdaAnnotation(func)
    if (!annotation) return undefined

    return builderLambdaArgumentName(annotation)
}

export function builderLambdaFunctionName(node: arkts.CallExpression): string | undefined {
    const annotation = findCallBuilderLambdaAnnotation(node)
    if (!annotation) return undefined

    return builderLambdaArgumentName(annotation)
}
/*
 TODO: remove this once compiler is capable of inferring type on it's own
  whole function is a couple of hacks
 */
function inferType(node: arkts.CallExpression): arkts.Identifier | undefined {
    if (arkts.isIdentifier(node.callee)) {
        const component = node.callee.name
        return arkts.factory.createIdentifier(uiAttributeName(component))
    }
    const decl = arkts.getDecl(node.callee!)
    if (arkts.isMethodDefinition(decl)) {
        if (arkts.isClassDefinition(decl.parent)) {
            return decl.parent.ident
        }
    }
    return undefined
}

function createBuilderLambdaInstanceLambda(node: arkts.CallExpression): arkts.Expression {
    return createInstanceLambda(node.arguments[0], inferType(node))
}

function createInstanceLambda(
    instanceArgument: arkts.Expression,
    parameterTypeName?: arkts.Identifier
): arkts.Expression {
    if (arkts.isUndefinedLiteral(instanceArgument)) {
        return instanceArgument
    }
    const lambdaParameter = arkts.factory.createETSParameterExpression(
        arkts.factory.createIdentifier(
            styledInstance,
            parameterTypeName !== undefined ?
                arkts.factory.createETSTypeReference(
                    arkts.factory.createETSTypeReferencePart(
                        parameterTypeName, undefined, undefined
                    )
                )
                : undefined
        ),
        false
    )
    const instanceLambdaBody = arkts.factory.createBlockStatement([
        arkts.factory.createExpressionStatement(instanceArgument)
    ])
    return arkts.factory.createArrowFunctionExpression(
        arkts.factory.createScriptFunction(
            instanceLambdaBody,
            undefined,
            [lambdaParameter],
            arkts.factory.createETSPrimitiveType(arkts.Es2pandaPrimitiveType.PRIMITIVE_TYPE_VOID),
            false,
            arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_ARROW,
            arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_NONE,
            undefined,
            undefined
        )
    )
}

function builderLambdaCallee(name: string) {
    if (!name.includes('.')) {
        return arkts.factory.createIdentifier(name)
    }
    // TODO: What are the restrictions on builderLambda name?
    return arkts.factory.createMemberExpression(
        arkts.factory.createIdentifier(name.split('.')[0]),
        arkts.factory.createIdentifier(name.split('.')[1]),
        arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_PROPERTY_ACCESS,
        false,
        false
    )
}

function transformBuilderLambdaCall(node: arkts.CallExpression): arkts.CallExpression {
    const implFunction = builderLambdaFunctionName(node)
    if (implFunction === undefined) {
        return node
    }
    return arkts.factory.updateCallExpression(
        node,
        builderLambdaCallee(implFunction),
        [
            createBuilderLambdaInstanceLambda(node),
            ...node.arguments.slice(1)
        ],
        node.typeParams,
        node.isOptional,
        node.hasTrailingComma,
        node.trailingBlock
    )
}

// TODO: for now it all works, but it is unclear
// if it will keep working under Recheck.
// in theory we don't add new files to import here,
// only the new names from the same file,
// to it should be okay.
function transformETSImportDeclaration(node: arkts.ETSImportDeclaration): arkts.ETSImportDeclaration {
    const additionalNames: string[] = []
    node.specifiers.forEach(it => {
        const name = (it as arkts.ImportSpecifier).imported
        const scriptFunction = name ? getIdentifierScriptFunction(name) : undefined
        if (scriptFunction) {
            const target = builderLambdaTargetFunctionName(scriptFunction)
            if (target) {
                // TODO: The type name here should not be explicitly manipulated
                // but the type checker of the compiler is still incapable
                // to infer the proper lambda argument types
                additionalNames.push(uiAttributeName(name?.name!))
                additionalNames.push(target)
            }
        }
    })
    if (additionalNames.length == 0) return node

    return arkts.factory.updateETSImportDeclaration(
        node,
        node.source,
        [   ...node.specifiers,
            ...additionalNames.map(it => arkts.factory.createImportSpecifier(
                arkts.factory.createIdentifier(it),
                arkts.factory.createIdentifier(it)
            ))
        ],
        node.isTypeKind ? arkts.Es2pandaImportKinds.IMPORT_KINDS_TYPES : arkts.Es2pandaImportKinds.IMPORT_KINDS_ALL
    )
}


export class BuilderLambdaTransformer extends arkts.AbstractVisitor {
    visitor(beforeChildren: arkts.AstNode): arkts.AstNode {
        const node = this.visitEachChild(beforeChildren)

        if (arkts.isCallExpression(node)) {
            return transformBuilderLambdaCall(node)
        }
        if (arkts.isETSImportDeclaration(node)) {
            return transformETSImportDeclaration(node)
        }

        return node
    }
}
