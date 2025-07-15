/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { classProperties, mangle } from "./common/arkts-utils"
import { createETSTypeReference, getRuntimePackage, getComponentPackage, Importer } from "./utils"
import { DecoratorNames, hasDecorator, isDecoratorAnnotation } from "./property-translators/utils";
import { fieldOf } from "./property-transformers";

export class ClassTransformer extends arkts.AbstractVisitor {
    constructor(private importer: Importer, options?: arkts.VisitorOptions) {
        super(options)
    }

    visitor(node: arkts.AstNode): arkts.AstNode {
        if (arkts.isETSModule(node)) {
            const program = (node as arkts.ETSModule).program
            if (program
                && (!program.modulePrefix
                    || (!program.modulePrefix.startsWith(getComponentPackage())
                        && !program.modulePrefix.startsWith("@koalaui")))) {
                return this.visitEachChild(node)
            }
        }
        if (arkts.isClassDeclaration(node) && !arkts.isETSStructDeclaration(node)) {
            const props = classProperties(node, propertyVerifier)
            return classVerifier(node, props) ? this.updateClass(node, props) : node
        }
        return node
    }

    updateClass(clazz: arkts.ClassDeclaration, properties: arkts.ClassProperty[]): arkts.ClassDeclaration {
        let classDef = clazz.definition!
        const isObserved = isObservedClass(classDef)
        const classImplements: arkts.TSClassImplements[] = [
            ...clazz.definition?.implements ?? [],
        ]
        if (isObserved) {
            this.importer.add('observableProxy', getRuntimePackage())
            this.importer.add('ObservableClass', getRuntimePackage())
            classImplements.push(arkts.factory.createTSClassImplements(
                createETSTypeReference("ObservableClass"))
            )
        }
        if (properties.length > 0 || isObserved) {
            if (properties.find(trackPropVerifier)) {
                this.importer.add('TrackableProps', getRuntimePackage())
                classImplements.push(arkts.factory.createTSClassImplements(
                    createETSTypeReference("TrackableProps"))
                )
            }
            classDef = arkts.factory.updateClassDefinition(
                classDef,
                classDef.ident,
                classDef.typeParams,
                classDef.superTypeParams,
                classImplements,
                undefined,
                classDef.super,
                this.rewriteClassProperties(clazz, properties, classDef.body as arkts.ClassElement[] ?? [], isObserved),
                classDef.modifiers,
                classDef.modifierFlags
            )
        }
        return arkts.factory.updateClassDeclaration(clazz,
            classDef.setAnnotations(this.rewriteAnnotations(classDef.annotations)),
            clazz.modifierFlags
        )
    }

    rewriteClassProperties(clazz: arkts.ClassDeclaration,
                           properties: arkts.ClassProperty[],
                           body: readonly arkts.ClassElement[],
                           isObservedClass: boolean): arkts.ClassElement[] {
        const result: arkts.ClassElement[] = []
        if (isObservedClass) {
            createImplObservedFlagMethod(result)
        }
        const trackedProps = properties
            .filter(trackPropVerifier)
            .map(it => it.id?.name!)
        if (trackedProps.length > 0) {
            createImplTrackedPropsMethod(trackedProps, result);
        }
        body.forEach(node => {
            if (arkts.isClassProperty(node) && propertyVerifier(node)) {
                this.rewriteProperty(node, isObservedClass, result)
            } else if (arkts.isMethodDefinition(node) && node.isConstructor) {
                result.push(this.updateConstructor(node, properties, isObservedClass))
            } else {
                result.push(node)
            }
        })
        return result
    }

    rewriteProperty(property: arkts.ClassProperty, isObservedClass: boolean, result: arkts.ClassElement[]) {
        const backing = arkts.factory.createClassProperty(
            createBackingIdentifier(property),
            observeValueIfNeeded(property.value, isObservedClass),
            property.typeAnnotation,
            arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PRIVATE,
            false
        )
        backing.setAnnotations(this.rewriteAnnotations(property.annotations))
        result.push(backing)

        result.push(createGetterSetter(property, isObservedClass))
    }

    rewriteAnnotations(annotations: readonly arkts.AnnotationUsage[]): arkts.AnnotationUsage[] {
        return annotations.filter(it => !isDecoratorAnnotation(it, DecoratorNames.TRACK) && !isDecoratorAnnotation(it, DecoratorNames.OBSERVED))
    }

    updateConstructor(method: arkts.MethodDefinition, properties: arkts.ClassProperty[], isObservedClass: boolean) {
        const originalBody = method.function?.body as arkts.BlockStatement
        if (!method.function || !originalBody) {
            return method
        }

        const statements: arkts.Statement[] = []
        originalBody.statements.forEach(state => {
            if (arkts.isExpressionStatement(state)
                && arkts.isAssignmentExpression((state as arkts.ExpressionStatement).expression)) {
                statements.push(this.rewriteStatement(state, properties, isObservedClass))
            } else {
                statements.push(state)
            }
        })

        return arkts.factory.updateMethodDefinition(
            method,
            method.kind,
            method.id,
            arkts.factory.createFunctionExpression(
                method.id,
                arkts.factory.createScriptFunction(
                    arkts.factory.createBlockStatement(statements),
                    method.function.typeParams,
                    method.function.params ?? [],
                    method.function.returnTypeAnnotation,
                    method.function.hasReceiver,
                    method.function.flags,
                    method.function.modifierFlags,
                    method.function.id,
                    method.function.annotations
                )
            ),
            method.modifierFlags,
            method.isComputed
        )
    }

    rewriteStatement(state: arkts.ExpressionStatement, properties: arkts.ClassProperty[], isObservedClass: boolean): arkts.ExpressionStatement {
        const expr = state.expression as arkts.AssignmentExpression
        if (arkts.isMemberExpression(expr.left)
            && arkts.isThisExpression(expr.left.object)
            && arkts.isIdentifier(expr.left.property)) {
            const propertyName = expr.left.property.name
            const property = properties.find(it => it.id?.name == propertyName)
            if (property) {
                return arkts.factory.createExpressionStatement(
                    arkts.factory.createAssignmentExpression(
                        arkts.factory.createMemberExpression(
                            arkts.factory.createThisExpression(),
                            createBackingIdentifier(property),
                            arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_PROPERTY_ACCESS,
                            false,
                            false
                        ),
                        observeValueIfNeeded(expr.right, isObservedClass),
                        expr.operatorType
                    )
                )
            }
        }
        return state
    }
}

function propertyVerifier(property: arkts.ClassProperty): boolean {
    return arkts.hasModifierFlag(property, arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC)
        && !arkts.hasModifierFlag(property, arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_STATIC)
}

function trackPropVerifier(property: arkts.ClassProperty): boolean {
    return hasDecorator(property, DecoratorNames.TRACK) && propertyVerifier(property)
}

function classVerifier(clazz: arkts.ClassDeclaration, properties: readonly arkts.ClassProperty[]): boolean {
    if (clazz.definition == undefined) {
        return false
    }
    if (isObservedClass(clazz.definition)) {
        return true
    }
    return properties.some(hasTrackDecorator);
}

function createBackingIdentifier(property: arkts.ClassProperty): arkts.Identifier {
    return arkts.factory.createIdentifier("__backing_" + property.id!.name)
}

function createGetterSetter(property: arkts.ClassProperty, isObservedClass: boolean): arkts.MethodDefinition {
    const name = property.id!.name
    const getterFunction = arkts.factory.createScriptFunction(
        arkts.factory.createBlockStatement([
            arkts.factory.createReturnStatement(
                arkts.factory.createMemberExpression(
                    arkts.factory.createThisExpression(),
                    createBackingIdentifier(property),
                    arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_PROPERTY_ACCESS,
                    false,
                    false
                )
            )
        ]),
        undefined,
        [],
        property.typeAnnotation?.clone(),
        true,
        arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_METHOD | arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_GETTER,
        arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC,
        arkts.factory.createIdentifier(name),
        []
    )

    const setterFunction = arkts.factory.createScriptFunction(
        arkts.factory.createBlockStatement([
            arkts.factory.createExpressionStatement(
                arkts.factory.createAssignmentExpression(
                    arkts.factory.createMemberExpression(
                        arkts.factory.createThisExpression(),
                        createBackingIdentifier(property),
                        arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_PROPERTY_ACCESS,
                        false,
                        false
                    ),
                    observeValueIfNeeded(arkts.factory.createIdentifier("value", property.typeAnnotation?.clone()), isObservedClass),
                    arkts.Es2pandaTokenType.TOKEN_TYPE_PUNCTUATOR_SUBSTITUTION
                )
            )
        ]),
        undefined,
        [
            arkts.factory.createETSParameterExpression(
                arkts.factory.createIdentifier("value", property.typeAnnotation?.clone()),
                false,
                undefined,
            )
        ],
        undefined,
        true,
        arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_METHOD | arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_SETTER | arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_OVERLOAD,
        arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC,
        arkts.factory.createIdentifier(name),
        []
    )

    let setter = arkts.factory.createMethodDefinition(
        arkts.Es2pandaMethodDefinitionKind.METHOD_DEFINITION_KIND_SET,
        arkts.factory.createIdentifier(name),
        arkts.factory.createFunctionExpression(arkts.factory.createIdentifier(name), setterFunction),
        arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC,
        false
    )

    let getter = arkts.factory.createMethodDefinition(
        arkts.Es2pandaMethodDefinitionKind.METHOD_DEFINITION_KIND_GET,
        arkts.factory.createIdentifier(name),
        arkts.factory.createFunctionExpression(arkts.factory.createIdentifier(name), getterFunction),
        arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC,
        false,
        [setter]
    )

    return getter
}

function createImplTrackedPropsMethod(trackedProps: readonly string[], result: arkts.ClassElement[]) {
    createMethodDefinition("trackedProperties",
        arkts.factory.createBlockStatement(
            [
                arkts.factory.createIfStatement(
                    checkThisCurrentClass(),
                    arkts.factory.createReturnStatement(
                        arkts.factory.createETSNewClassInstanceExpression(
                            createETSTypeReference("Set", ["string"]),
                            trackedProps.length
                                ? [arkts.factory.createArrayExpression(
                                    trackedProps.map(it => arkts.factory.createStringLiteral(it)))]
                                : []
                        )
                    )
                ),
                arkts.factory.createReturnStatement(arkts.factory.createUndefinedLiteral())
            ]
        ),
        arkts.factory.createETSUnionType(
            [createETSTypeReference("ReadonlySet", ["string"]), createETSTypeReference("undefined")]
        ),
        result)
}

function createImplObservedFlagMethod(result: arkts.ClassElement[]) {
    createMethodDefinition("isObserved",
        arkts.factory.createBlockStatement([arkts.factory.createReturnStatement(checkThisCurrentClass())]),
        arkts.factory.createETSPrimitiveType(arkts.Es2pandaPrimitiveType.PRIMITIVE_TYPE_BOOLEAN),
        result)
}

function createMethodDefinition(methodName: string,
                         body: arkts.AstNode,
                         returnTypeNode: arkts.TypeNode,
                         result: arkts.ClassElement[]) {
    result.push(arkts.factory.createMethodDefinition(
        arkts.Es2pandaMethodDefinitionKind.METHOD_DEFINITION_KIND_METHOD,
        arkts.factory.createIdentifier(methodName),
        arkts.factory.createFunctionExpression(
            arkts.factory.createIdentifier(methodName),
            arkts.factory.createScriptFunction(
                body,
                undefined,
                [],
                returnTypeNode,
                false,
                arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_METHOD,
                arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC,
                arkts.factory.createIdentifier(methodName),
                []
            )
        ),
        arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC
        | arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_OVERRIDE,
        false
    ))
}

function observeValueIfNeeded(value: arkts.Expression | undefined, isObservedClass: boolean) {
    if (!value || !isObservedClass) {
        return value
    }
    return arkts.factory.createCallExpression(
        arkts.factory.createIdentifier("observableProxy"),
        [value],
        undefined
    )
}

function isObservedClass(definition: arkts.ClassDefinition): boolean {
    return definition.annotations.some(annot =>
        isDecoratorAnnotation(annot, DecoratorNames.OBSERVED)
    )
}

function hasTrackDecorator(prop: arkts.ClassProperty): boolean {
    return prop.annotations.some(annot =>
        isDecoratorAnnotation(annot, DecoratorNames.TRACK)
    )
}

function checkThisCurrentClass(): arkts.Expression {
    return arkts.factory.createBinaryExpression(
        arkts.factory.createCallExpression(
            fieldOf(arkts.factory.createIdentifier("Class"), "of"),
            [arkts.factory.createThisExpression()],
            undefined
        ),
        arkts.factory.createCallExpression(
            fieldOf(arkts.factory.createIdentifier("Class"), "current"),
            [],
            undefined
        ),
        arkts.Es2pandaTokenType.TOKEN_TYPE_PUNCTUATOR_EQUAL
    )
}