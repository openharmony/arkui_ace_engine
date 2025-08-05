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

import { classProperties } from "./common/arkts-utils"
import { createETSTypeReference, getRuntimePackage, getComponentPackage, Importer, mangle } from "./utils"
import { DecoratorNames, hasDecorator, isDecoratorAnnotation } from "./utils";
import { fieldOf } from "./property-transformers";

type ObservedDecoratorType = DecoratorNames.OBSERVED | DecoratorNames.OBSERVED_V2

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
            const classContext = extractClassContext(node, props)
            return classContext?.decoratorType || classContext?.trackedProperties.length
                ? this.updateClass(node, props, classContext) : node
        }
        return node
    }

    addImplObservedDecorator(decoratorType: ObservedDecoratorType, result: arkts.TSClassImplements[]) {
        this.importer.add('observableProxy', getRuntimePackage())
        let className: string
        if (decoratorType == DecoratorNames.OBSERVED) {
            className = "ObservableClass"
        } else if (decoratorType == DecoratorNames.OBSERVED_V2) {
            className = "ObservableClassV2"
        }
        this.importer.add(className!, getRuntimePackage())
        result.push(arkts.factory.createTSClassImplements(createETSTypeReference(className!)))
    }

    addImplTrackDecorator(result: arkts.TSClassImplements[]) {
        this.importer.add('TrackableProps', getRuntimePackage())
        result.push(arkts.factory.createTSClassImplements(
            createETSTypeReference("TrackableProps"))
        )
    }

    updateClass(clazz: arkts.ClassDeclaration,
                properties: arkts.ClassProperty[],
                classContext: ClassContext): arkts.ClassDeclaration {
        let classDef = clazz.definition!
        const classImplements: arkts.TSClassImplements[] = [
            ...clazz.definition?.implements ?? [],
        ]
        if (properties.length > 0) {
            if (classContext.decoratorType) {
                this.addImplObservedDecorator(classContext.decoratorType, classImplements)
            }
            if (classContext.trackedProperties.length) {
                this.addImplTrackDecorator(classImplements)
            }
            classDef = arkts.factory.updateClassDefinition(
                classDef,
                classDef.ident,
                classDef.typeParams,
                classDef.superTypeParams,
                classImplements,
                undefined,
                classDef.super,
                this.rewriteClassProperties(classDef, properties, classDef.body as arkts.ClassElement[] ?? [], classContext),
                classDef.modifiers,
                classDef.modifierFlags
            )
        }
        return arkts.factory.updateClassDeclaration(clazz,
            classDef.setAnnotations(this.rewriteAnnotations(classDef.annotations)),
            clazz.modifierFlags
        )
    }

    rewriteClassProperties(classDef: arkts.ClassDefinition,
                           properties: arkts.ClassProperty[],
                           body: readonly arkts.ClassElement[],
                           classContext: ClassContext): arkts.ClassElement[] {
        const result: arkts.ClassElement[] = []
        if (classContext.decoratorType == DecoratorNames.OBSERVED) {
            createImplObservedFlagMethod(result)
        } else if (classContext.decoratorType == DecoratorNames.OBSERVED_V2) {
            const tracedProps = properties
                .filter(tracePropVerifier)
                .map(it => it.id?.name!)
            createImplTrackablePropsMethod(classDef, "ObservableClassV2", "tracedProperties", tracedProps, result)
        }
        const trackedProps = properties
            .filter(trackPropVerifier)
            .map(it => it.id?.name!)
        if (trackedProps.length > 0) {
            createImplTrackablePropsMethod(classDef, "TrackableProps", "trackedProperties", trackedProps, result)
        }
        body.forEach(node => {
            if (arkts.isClassProperty(node) && propertyVerifier(node)) {
                this.rewriteProperty(node, classContext, result)
            } else if (arkts.isMethodDefinition(node) && node.isConstructor) {
                result.push(this.updateConstructor(node, properties, classContext))
            } else {
                result.push(node)
            }
        })
        return result
    }

    rewriteProperty(property: arkts.ClassProperty,
                    classContext: ClassContext,
                    result: arkts.ClassElement[]) {
        const backing = arkts.factory.createClassProperty(
            createBackingIdentifier(property),
            observePropIfNeeded(property.id?.name!, property.value, classContext),
            property.typeAnnotation,
            arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PRIVATE,
            false
        )
        backing.setAnnotations(this.rewriteAnnotations(property.annotations))
        result.push(backing)

        result.push(createGetterSetter(property, classContext))
    }

    rewriteAnnotations(annotations: readonly arkts.AnnotationUsage[]): arkts.AnnotationUsage[] {
        const decorators = [DecoratorNames.TRACK, DecoratorNames.TRACE, DecoratorNames.OBSERVED, DecoratorNames.OBSERVED_V2]
        return annotations.filter(it =>
            !decorators.some(decorator => isDecoratorAnnotation(it, decorator))
        )
    }

    updateConstructor(method: arkts.MethodDefinition,
                      properties: arkts.ClassProperty[],
                      classContext: ClassContext) {
        const originalBody = method.function?.body as arkts.BlockStatement
        if (!method.function || !originalBody) {
            return method
        }

        const statements: arkts.Statement[] = []
        originalBody.statements.forEach(state => {
            if (arkts.isExpressionStatement(state)
                && arkts.isAssignmentExpression((state as arkts.ExpressionStatement).expression)) {
                statements.push(this.rewriteStatement(state, properties, classContext))
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

    rewriteStatement(state: arkts.ExpressionStatement,
                     properties: arkts.ClassProperty[],
                     classContext: ClassContext): arkts.ExpressionStatement {
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
                        observePropIfNeeded(propertyName, expr.right, classContext),
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

function tracePropVerifier(property: arkts.ClassProperty): boolean {
    return hasDecorator(property, DecoratorNames.TRACE) && propertyVerifier(property)
}

function extractClassContext(clazz: arkts.ClassDeclaration,
                             properties: readonly arkts.ClassProperty[]): ClassContext | undefined {
    if (clazz.definition != undefined) {
        return new ClassContext(getObservedDecoratorType(clazz.definition),
            properties
                .filter(trackPropVerifier)
                .map(it => it.id?.name!),
            properties
                .filter(tracePropVerifier)
                .map(it => it.id?.name!))
    }
    return undefined
}

function createBackingIdentifier(property: arkts.ClassProperty): arkts.Identifier {
    return arkts.factory.createIdentifier("__backing_" + property.id!.name)
}

function createGetterSetter(property: arkts.ClassProperty,
                            classContext: ClassContext): arkts.MethodDefinition {
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
                    observePropIfNeeded(property.id?.name!,
                        arkts.factory.createIdentifier("value", property.typeAnnotation?.clone()),
                        classContext),
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

function addTrackablePropsFromParent(trackedPropsIdent: string,
                                     interfaceName: string,
                                     methodName: string,
                                     result: arkts.Statement[]) {
    const trackableProps = arkts.factory.createIfStatement(
        arkts.factory.createBinaryExpression(
            arkts.factory.createThisExpression(),
            createETSTypeReference(interfaceName),
            arkts.Es2pandaTokenType.TOKEN_TYPE_KEYW_INSTANCEOF
        ),
        arkts.factory.createBlockStatement(
            [
                arkts.factory.createExpressionStatement(
                    arkts.factory.createAssignmentExpression(
                        arkts.factory.createIdentifier(trackedPropsIdent),
                        arkts.factory.createCallExpression(
                            fieldOf(arkts.factory.createIdentifier(trackedPropsIdent), "concat"),
                            [
                                arkts.factory.createCallExpression(
                                    fieldOf(arkts.factory.createIdentifier("Array"), "from"),
                                    [
                                        arkts.factory.createCallExpression(
                                            fieldOf(arkts.factory.createSuperExpression(), methodName),
                                            [],
                                            undefined,
                                            false,
                                            false,
                                            undefined,
                                        )
                                    ],
                                    undefined,
                                    false,
                                    false,
                                    undefined,
                                )
                            ],
                            undefined,
                            false,
                            false,
                            undefined,
                        ),
                        arkts.Es2pandaTokenType.TOKEN_TYPE_PUNCTUATOR_SUBSTITUTION
                    )
                )
            ]
        )
    )
    result.push(trackableProps)
}

function createImplTrackablePropsMethod(classDef: arkts.ClassDefinition,
                                        interfaceName: string,
                                        methodName: string,
                                        trackableProps: readonly string[],
                                        result: arkts.ClassElement[]) {
    const trackedPropsIdent = mangle("trackedProps")
    const body: arkts.Statement[] = []
    body.push(
        arkts.factory.createVariableDeclaration(
            arkts.Es2pandaVariableDeclarationKind.VARIABLE_DECLARATION_KIND_LET,
            [
                arkts.factory.createVariableDeclarator(
                    arkts.Es2pandaVariableDeclaratorFlag.VARIABLE_DECLARATOR_FLAG_LET,
                    arkts.factory.createIdentifier(trackedPropsIdent),
                    arkts.factory.createArrayExpression(
                        trackableProps.map(it => arkts.factory.createStringLiteral(it))
                    )
                )
            ]
        )
    )
    if (classDef.super) {
        addTrackablePropsFromParent(trackedPropsIdent, interfaceName, methodName, body)
    }
    body.push(arkts.factory.createReturnStatement(
        arkts.factory.createETSNewClassInstanceExpression(
            createETSTypeReference("Set", ["string"]),
            [arkts.factory.createIdentifier(trackedPropsIdent)]
        )
    ))
    createMethodDefinition(methodName,
        arkts.factory.createBlockStatement(body),
        createETSTypeReference("ReadonlySet", ["string"]),
        result
    )
}

function createImplObservedFlagMethod(result: arkts.ClassElement[]) {
    result.push(
        arkts.factory.createClassProperty(
            arkts.factory.createIdentifier(mangle("isCalleeCurrentClass")),
            createCheckThisCurrentClass(),
            arkts.factory.createETSPrimitiveType(arkts.Es2pandaPrimitiveType.PRIMITIVE_TYPE_BOOLEAN),
            arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PRIVATE | arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_READONLY,
            false
        )
    )
    createMethodDefinition("isObserved",
        arkts.factory.createBlockStatement([arkts.factory.createReturnStatement(
            fieldOf(arkts.factory.createThisExpression(), mangle("isCalleeCurrentClass"))
        )]),
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

function observePropIfNeeded(propertyName: string,
                             propertyValue: arkts.Expression | undefined,
                             classContext: ClassContext) {
    const isClassFullyObserved = classContext.decoratorType == DecoratorNames.OBSERVED && classContext.trackedProperties.length == 0
    const isTrackedProp = classContext.tracedProperties.includes(propertyName)
    const isTracedProp = classContext.trackedProperties.includes(propertyName)
    if (propertyValue && (isClassFullyObserved || isTrackedProp || isTracedProp)) {
        return arkts.factory.createCallExpression(
            arkts.factory.createIdentifier("observableProxy"),
            [propertyValue],
            undefined,
            false,
            false,
            undefined,
        )
    }
    return propertyValue
}

function getObservedDecoratorType(definition: arkts.ClassDefinition): ObservedDecoratorType | undefined {
    if (definition.annotations.some(annot =>
        isDecoratorAnnotation(annot, DecoratorNames.OBSERVED))) {
        return DecoratorNames.OBSERVED
    } else if (definition.annotations.some(annot =>
        isDecoratorAnnotation(annot, DecoratorNames.OBSERVED_V2))) {
        return DecoratorNames.OBSERVED_V2
    }
    return undefined
}

function createCheckThisCurrentClass(): arkts.Expression {
    return arkts.factory.createBinaryExpression(
        arkts.factory.createCallExpression(
            fieldOf(arkts.factory.createIdentifier("Class"), "of"),
            [arkts.factory.createThisExpression()],
            undefined,
            false,
            false,
            undefined,
        ),
        arkts.factory.createCallExpression(
            fieldOf(arkts.factory.createIdentifier("Class"), "current"),
            [],
            undefined,
            false,
            false,
            undefined,
        ),
        arkts.Es2pandaTokenType.TOKEN_TYPE_PUNCTUATOR_EQUAL
    )
}

class ClassContext {
    readonly decoratorType: ObservedDecoratorType | undefined
    readonly trackedProperties: readonly string[] = []
    readonly tracedProperties: readonly string[] = []

    constructor(observedDecoratorType: ObservedDecoratorType | undefined,
                trackedProperties: readonly string[],
                tracedProperties: readonly string[]) {
        this.decoratorType = observedDecoratorType
        this.trackedProperties = trackedProperties
        this.tracedProperties = tracedProperties

        this.verify()
    }

    private verify() {
        if (this.decoratorType == DecoratorNames.OBSERVED_V2) {
            if (this.trackedProperties.length) {
                throw new Error("@Track decorator is not applicable with @ObservedV2 decorator")
            }
        } else {
            if (this.tracedProperties.length) {
                throw new Error("@Trace decorator is only used with @ObservedV2 decorator")
            }
        }
    }
}