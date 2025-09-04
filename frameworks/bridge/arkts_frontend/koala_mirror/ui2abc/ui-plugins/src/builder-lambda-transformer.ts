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
import { BuilderLambdaNames, InternalAnnotations, getCustomComponentOptionsName, styledInstance, uiAttributeName } from "./utils"
import { StructDescriptor, StructsResolver } from "./struct-recorder"
import { DecoratorNames } from "./property-translators/utils"
import { fieldOf } from "./property-transformers"
import { addAnnotation, annotation, backingField, removeAnnotationByName } from "./common/arkts-utils"


function isBuilderLambdaAnnotation(annotation: arkts.AnnotationUsage): boolean {
    if (annotation.expr === undefined) {
        return false
    }
    if (!arkts.isIdentifier(annotation.expr)) {
        return false
    }
    return annotation.expr.name == BuilderLambdaNames.BUILDER_LAMBDA_NAME
}

function isComponentBuilderAnnotation(annotation: arkts.AnnotationUsage): boolean {
    if (annotation.expr === undefined) {
        return false
    }
    if (!arkts.isIdentifier(annotation.expr)) {
        return false
    }
    return annotation.expr.name == BuilderLambdaNames.ANNOTATION_NAME
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

function findComponentBuilderAnnotation(func: arkts.ScriptFunction): arkts.AnnotationUsage | undefined {
    const declAnnotations = arkts.getAnnotations(func)
    if (declAnnotations.length === 0) {
        return undefined
    }
    return declAnnotations.find(it => isComponentBuilderAnnotation(it))
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
    const func = getScriptFunction(node)
    if (func == undefined) return undefined

    if (findComponentBuilderAnnotation(func)) {
        return func.id?.name!
    }

    const annotation = findBuilderLambdaAnnotation(func)
    if (!annotation) return undefined

    return builderLambdaArgumentName(annotation)
}
/*
 Improve: remove this once compiler is capable of inferring type on it's own
  whole function is a couple of hacks
 */
function inferType(node: arkts.CallExpression): arkts.Identifier | undefined {
    if (arkts.isIdentifier(node.callee)) {
        const component = node.callee.name.replace("Impl", "")
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
    // Improve: What are the restrictions on builderLambda name?
    return arkts.factory.createMemberExpression(
        arkts.factory.createIdentifier(name.split('.')[0]),
        arkts.factory.createIdentifier(name.split('.')[1]),
        arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_PROPERTY_ACCESS,
        false,
        false
    )
}

function isOptionsType(type: arkts.TypeNode): type is arkts.ETSTypeReference {
    return arkts.isETSTypeReference(type) && arkts.isIdentifier(type.part?.name) && (type.part?.name?.name?.startsWith("__Options") ?? false)
}

function isStringType(type: arkts.TypeNode): type is arkts.ETSTypeReference {
    return arkts.isETSTypeReference(type) && arkts.isIdentifier(type.part?.name) && (type.part?.name?.name == "string")
}

function maybeFieldRewrite(struct: StructDescriptor, property: arkts.Property): arkts.Expression {
    const value = property.value as arkts.MemberExpression
    if (!arkts.isIdentifier(property.key)) return property.value!
    if (arkts.isThisExpression(value.object) && arkts.isIdentifier(value.property)) {
        let targetName = property.key.name
        let localName = value.property.name
        // Hack to work around the fact that $-conversion already made transition to backing field,
        // let's rework.
        if (struct.hasDecorator(targetName, DecoratorNames.LINK) && !localName.startsWith("__backing")) {
            return fieldOf(arkts.factory.createThisExpression(), backingField(localName))
        }
    }
    return value
}

function rewriteOptionsParameter(expression: arkts.Expression, type: arkts.TypeNode, struct: StructDescriptor): arkts.Expression {
    if (!arkts.isObjectExpression(expression) || !struct) return expression
    return arkts.factory.createTSAsExpression(
        arkts.factory.updateObjectExpression(
            expression,
            expression.properties.map(value => {
                if (arkts.isProperty(value) && arkts.isMemberExpression(value.value)) {
                    return arkts.factory.updateProperty(
                        value,
                        arkts.Es2pandaPropertyKind.PROPERTY_KIND_INIT,
                        value.key,
                        maybeFieldRewrite(struct, value), false, false
                    )
                } else {
                    return value
                }
            })),
        type.clone(), false
    )
}

function transformBuilderLambdaCall(resolver: StructsResolver | undefined, node: arkts.CallExpression): arkts.CallExpression {
    const implFunction = builderLambdaFunctionName(node)
    if (implFunction === undefined) {
        return node
    }
    const callee = getScriptFunction(node)
    let optionsIndex = -1
    let optionsType: arkts.ETSTypeReference | undefined = undefined
    let struct: StructDescriptor | undefined = undefined
    let reuseIndex = -1
    let reuseKey: string | undefined = undefined
    if (callee) {
        callee.params.forEach((it, index) => {
            if (arkts.isETSParameterExpression(it)) {
                let type = it.typeAnnotation
                if (arkts.isETSUnionType(type) && isOptionsType(type.types[0])) {
                    optionsIndex = index
                    optionsType = type.types[0] as arkts.ETSTypeReference
                    struct = resolver?.findStructByOptions(optionsType.baseName!)
                }
                if (arkts.isETSUnionType(type) && isStringType(type.types[0])
                    && struct && struct.hasAnnotation(DecoratorNames.REUSABLE)) {
                    reuseIndex = index
                    reuseKey = struct.name
                }
            }
        })
    }
    const reuseAgrs: arkts.Expression[] = []
    if (reuseIndex > -1 && node.arguments.length <= reuseIndex + 1) {
        reuseAgrs.push(arkts.factory.createStringLiteral(reuseKey!))
        if (node.arguments.length <= reuseIndex + 1) {
            reuseAgrs.push(arkts.factory.createUndefinedLiteral())
        }
    }
    return arkts.factory.updateCallExpression(
        node,
        builderLambdaCallee(implFunction),
        [
            createBuilderLambdaInstanceLambda(node),
            ...node.arguments.slice(1).map((it, index) => {
                // Workaround for type inference bug!
                if (index == optionsIndex) {
                    return rewriteOptionsParameter(it, optionsType!, struct!)
                } else {
                    return it
                }
            }),
            ...reuseAgrs
        ],
        node.typeParams,
        node.isOptional,
        node.hasTrailingComma,
        node.trailingBlock
    )
}

// Improve: for now it all works, but it is unclear
// if it will keep working under Recheck.
// in theory we don't add new files to import here,
// only the new names from the same file,
// to it should be okay.
function transformETSImportDeclaration(resolver: StructsResolver | undefined, node: arkts.ETSImportDeclaration): arkts.ETSImportDeclaration {
    const additionalNames: string[] = []
    node.specifiers.forEach(it => {
        if (arkts.isImportSpecifier(it)) {
            const name = it.imported
            const struct = resolver?.findStruct(it.imported!)
            if (struct) {
                additionalNames.push(getCustomComponentOptionsName(name?.name!))
            }
            const scriptFunction = name ? getIdentifierScriptFunction(name) : undefined
            if (scriptFunction) {
                const target = builderLambdaTargetFunctionName(scriptFunction)
                if (target) {
                    // Improve: The type name here should not be explicitly manipulated
                    // but the type checker of the compiler is still incapable
                    // to infer the proper lambda argument types
                    additionalNames.push(uiAttributeName(name?.name!))
                    additionalNames.push(target)
                } else if (findComponentBuilderAnnotation(scriptFunction)) {
                    additionalNames.push(uiAttributeName(name?.name!))
                }
            }
        }
    })
    if (additionalNames.length == 0) return node

    return arkts.factory.updateETSImportDeclaration(
        node,
        node.source,
        [...node.specifiers,
        ...additionalNames.map(it => arkts.factory.createImportSpecifier(
            arkts.factory.createIdentifier(it),
            arkts.factory.createIdentifier(it)
        ))
        ],
        node.isTypeKind ? arkts.Es2pandaImportKinds.IMPORT_KINDS_TYPES : arkts.Es2pandaImportKinds.IMPORT_KINDS_ALL
    )
}

function isComponentBuilder(node: arkts.AstNode): boolean {
    if (!arkts.isMethodDefinition(node)) return false
    const func = node.function!
    return findComponentBuilderAnnotation(func) != undefined
}

function createStyleParameter(
    typeNode: arkts.TypeNode | undefined,
): arkts.ETSParameterExpression {
    const styleLambdaParam = arkts.factory.createETSParameterExpression(
        arkts.factory.createIdentifier(BuilderLambdaNames.STYLE_ARROW_PARAM_NAME, typeNode),
        false,
        undefined
    )
    const funcType = arkts.factory.createETSFunctionType(
        undefined,
        [styleLambdaParam],
        arkts.factory.createETSPrimitiveType(arkts.Es2pandaPrimitiveType.PRIMITIVE_TYPE_VOID),
        false,
        arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_ARROW,
        // Improve: get dealt with @memo on type of param in memo-plugin to put MEMO here
    )

    let parameter: arkts.ETSParameterExpression;
    const optionalFuncType = arkts.factory.createETSUnionType([funcType, arkts.factory.createETSUndefinedType()]);
    parameter = arkts.factory.createETSParameterExpression(
        arkts.factory.createIdentifier(BuilderLambdaNames.STYLE_PARAM_NAME, optionalFuncType),
        false,
        undefined,
        [annotation(InternalAnnotations.MEMO)]
    )
    return parameter
}

function transformComponentBuilder(
    node: arkts.MethodDefinition,
): arkts.MethodDefinition {
    const styleArg = createStyleParameter(node.function?.returnTypeAnnotation?.clone())
    const func: arkts.ScriptFunction = node.function!
    const newAnnotations = addAnnotation(
        removeAnnotationByName(func.annotations, BuilderLambdaNames.ANNOTATION_NAME),
        InternalAnnotations.MEMO
    )
    const newParams: arkts.Expression[] = [styleArg, ...func.params]
    const updateFunc = arkts.factory.updateScriptFunction(
        func,
        func.body,
        func.typeParams,
        newParams,
        arkts.factory.createETSPrimitiveType(arkts.Es2pandaPrimitiveType.PRIMITIVE_TYPE_VOID),
        false,
        func.flags,
        func.modifierFlags,
        node.id,
        newAnnotations
    )

    const result = arkts.factory.updateMethodDefinition(
        node,
        node.kind,
        node.id,
        arkts.factory.createFunctionExpression(arkts.factory.createIdentifier(node.id?.name!), updateFunc),
        node.modifierFlags,
        false,
        node.overloads
    )

    return result
}


export class BuilderLambdaTransformer extends arkts.AbstractVisitor {
    constructor(private resolver: StructsResolver | undefined) {
        super()
    }
    visitor(beforeChildren: arkts.AstNode): arkts.AstNode {
        const node = this.visitEachChild(beforeChildren)

        if (arkts.isCallExpression(node)) {
            return transformBuilderLambdaCall(this.resolver, node)
        }
        if (arkts.isMethodDefinition(node) && isComponentBuilder(node)) {
            return transformComponentBuilder(node)
        }
        if (arkts.isETSImportDeclaration(node)) {
            return transformETSImportDeclaration(this.resolver, node)
        }

        return node
    }
}
