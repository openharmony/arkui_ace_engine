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
import { Es2pandaModifierFlags } from "@koalaui/libarkts"

import { classProperties } from "./common/arkts-utils"
import {
    createETSTypeReference,
    DecoratorNames,
    getComponentPackage,
    getDecoratorName,
    getRuntimePackage,
    Importer,
    isDecoratorAnnotation,
    mangle
} from "./utils"
import { backingFieldNameOf, fieldOf } from "./property-transformers";

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
            const props = classProperties(node,
                it => arkts.hasModifierFlag(it, arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC))
            const classContext = extractClassContext(node, props)
            return classContext?.isClassObservable() ? this.updateClass(node, props, classContext) : node
        }
        return node
    }

    addObservableClassImplements(result: arkts.TSClassImplements[]) {
        const className = "ObservableClass"
        this.importer.add(className, getRuntimePackage())
        result.push(arkts.factory.createTSClassImplements(createETSTypeReference(className)))
    }

    updateClass(clazz: arkts.ClassDeclaration,
                properties: arkts.ClassProperty[],
                classContext: ClassContext): arkts.ClassDeclaration {
        let classDef = clazz.definition!
        const classImplements: arkts.TSClassImplements[] = [
            ...clazz.definition?.implements ?? [],
        ]
        if (properties.length > 0) {
            if (classContext.isClassObservable()) {
                this.importer.add("observableProxy", getRuntimePackage())
                this.addObservableClassImplements(classImplements)
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
        if (classContext.isClassObservable()) {
            this.injectClassMetadata(classDef, classContext, result)
        }
        body.forEach(node => {
            if (arkts.isClassProperty(node) && classContext.needRewriteProperty(node)) {
                this.rewriteProperty(node, classContext, classDef.ident?.name!, result)
            } else if (arkts.isMethodDefinition(node) && node.isConstructor) {
                result.push(this.updateConstructor(node, properties, classContext))
            } else {
                result.push(node)
            }
        })
        return result
    }

    injectClassMetadata(classDef: arkts.ClassDefinition, classContext: ClassContext, result: arkts.ClassElement[]) {
        const classMetadataName = "ClassMetadata"
        const classMetadataPropName = mangle("classMetadata")

        this.importer.add(classMetadataName, getRuntimePackage())
        const classMetadataType = createETSTypeReference(classMetadataName)
        let trackableProps: string[] | undefined
        if (classContext.trackedPropertyNames.length > 0) {
            trackableProps = classContext.trackedPropertyNames
        } else if (classContext.tracedPropertyNames.length > 0) {
            trackableProps = classContext.tracedPropertyNames
        }

        let typedProps: [string, string][] | undefined
        if (classContext.typedProperties.length > 0) {
            typedProps = []
            for (const prop of classContext.typedProperties.values()) {
                typedProps.push([prop[0], prop[1][0].args[0]])
            }
        }
        const metadataCtorArgs: arkts.Expression[] = [
            this.findClassMetadata(classMetadataType, classDef.super),
            arkts.factory.createBooleanLiteral(classContext.isObservedV1()),
            arkts.factory.createBooleanLiteral(classContext.isObservedV2()),
            trackableProps
                ? arkts.factory.createArrayExpression(trackableProps.map(it => arkts.factory.createStringLiteral(it)))
                : arkts.factory.createUndefinedLiteral(),
            typedProps
                ? arkts.factory.createArrayExpression(typedProps.map(it =>
                    arkts.factory.createArrayExpression([arkts.factory.createStringLiteral(it[0]),
                        arkts.factory.createStringLiteral(it[1])])))
                : arkts.factory.createUndefinedLiteral()
        ]
        result.push(
            arkts.factory.createClassProperty(
                arkts.factory.createIdentifier(classMetadataPropName),
                arkts.factory.createETSNewClassInstanceExpression(classMetadataType, metadataCtorArgs),
                arkts.factory.createETSUnionType([classMetadataType, arkts.factory.createETSUndefinedType()]),
                arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PRIVATE
                | arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_READONLY
                | arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_STATIC,
                false
            )
        )
        createClassMetadataMethod(classDef, classMetadataType, classMetadataPropName, result)
    }

    findClassMetadata(classMetadataType: arkts.ETSTypeReference, type: arkts.Expression | undefined): arkts.Expression {
        return arkts.isETSTypeReference(type)
            ? arkts.factory.createCallExpression(
                fieldOf(classMetadataType, "findClassMetadata"),
                [
                    arkts.factory.createCallExpression(
                        fieldOf(arkts.factory.createIdentifier("Type"), "from"),
                        [],
                        arkts.factory.createTSTypeParameterInstantiation([createETSTypeReference(type.baseName?.name!)]),
                        false,
                        false,
                    )
                ],
                undefined,
                false,
                false
            )
            : arkts.factory.createUndefinedLiteral()
    }

    rewriteProperty(property: arkts.ClassProperty,
                    classContext: ClassContext,
                    className: string,
                    result: arkts.ClassElement[]) {
        let modifiers = arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PRIVATE
        if (isStaticProperty(property)) {
            modifiers |= arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_STATIC
            this.importer.add("globalMutableState", getRuntimePackage())
        }
        const backing = arkts.factory.createClassProperty(
            arkts.factory.createIdentifier(backingFieldNameOf(property)),
            createBackingPropertyRValue(property, property.value, classContext),
            createBackingPropertyType(property, classContext),
            modifiers,
            false
        )
        backing.setAnnotations(this.rewriteAnnotations(property.annotations))
        result.push(backing)

        result.push(createGetterSetter(property, classContext, className))
    }

    rewriteAnnotations(annotations: readonly arkts.AnnotationUsage[]): arkts.AnnotationUsage[] {
        const decorators = [
            DecoratorNames.TRACK,
            DecoratorNames.TRACE,
            DecoratorNames.OBSERVED,
            DecoratorNames.OBSERVED_V2,
            DecoratorNames.TYPE,
        ]
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
            if (property && classContext.needRewriteProperty(property)) {
                return arkts.factory.createExpressionStatement(
                    arkts.factory.createAssignmentExpression(
                        arkts.factory.createMemberExpression(
                            arkts.factory.createThisExpression(),
                            arkts.factory.createIdentifier(backingFieldNameOf(property)),
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
    return ![arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PRIVATE,
        Es2pandaModifierFlags.MODIFIER_FLAGS_PROTECTED]
        .some(it => arkts.hasModifierFlag(property, it));
}

function getDecoratorArgs(decorator: arkts.AnnotationUsage): string[] {
    const args: string[] = []
    for (const prop of decorator.properties) {
        if (arkts.isClassProperty(prop) && arkts.isIdentifier(prop.value)) {
            args.push(prop.value.name)
        }
    }
    return args
}

function getDecoratedProperties(properties: readonly arkts.ClassProperty[]): ReadonlyMap<string, PropertyDecorator[]> {
    const propertyInfo = new Map<string, PropertyDecorator[]>()
    for (const prop of properties) {
        if (!propertyVerifier(prop)) {
            continue
        }
        const propName = prop.id!.name!
        const decorators = propertyInfo.get(propName) ?? []

        for (const anno of prop.annotations) {
            let decorator = getDecoratorName(anno)
            if (decorator === undefined) {
                continue
            }
            if (decorators.length === 0) {
                propertyInfo.set(propName, decorators)
            }
            decorators.push(new PropertyDecorator(decorator, getDecoratorArgs(anno)))
        }
    }
    return propertyInfo
}

function extractClassContext(clazz: arkts.ClassDeclaration,
                             properties: readonly arkts.ClassProperty[]): ClassContext | undefined {
    if (clazz.definition != undefined) {
        return new ClassContext(getObservedDecoratorType(clazz.definition), getDecoratedProperties(properties))
    }
    return undefined
}

function createBackingPropertyRValue(property: arkts.ClassProperty, value: arkts.Expression | undefined, classContext: ClassContext): arkts.Expression | undefined {
    const propValue = observePropIfNeeded(property.id?.name!, value, classContext)
    if (isStaticProperty(property) && classContext.tracedPropertyNames.includes(property.id?.name!)) {
        return arkts.factory.createCallExpression(
            arkts.factory.createIdentifier("globalMutableState"),
            [propValue!],
            arkts.factory.createTSTypeParameterInstantiation([property.typeAnnotation!]),
            false,
            false,
            undefined
        )
    }
    return propValue
}

function createBackingPropertyType(property: arkts.ClassProperty, classContext: ClassContext) {
    return isStaticProperty(property) && classContext.tracedPropertyNames.includes(property.id?.name!)
        ? undefined
        : property.typeAnnotation
}

function createPropertyAccess(className: string, property: arkts.ClassProperty, classContext: ClassContext) {
    const receiver = isStaticProperty(property)
        ? createETSTypeReference(className)
        : arkts.factory.createThisExpression()
    const expr = fieldOf(receiver, backingFieldNameOf(property))
    if (isStaticProperty(property) && classContext.tracedPropertyNames.includes(property.id?.name!)) {
        return fieldOf(expr, "value")
    }
    return expr
}

function createGetterSetter(property: arkts.ClassProperty,
                            classContext: ClassContext,
                            className: string): arkts.MethodDefinition {
    let modifiers = arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC
    if (isStaticProperty(property)) {
        modifiers |= arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_STATIC
    }
    const name = property.id!.name
    const getterStatements: arkts.Statement[] = []
    recreateDisposedState(property, classContext, className, getterStatements)
    getterStatements.push(arkts.factory.createReturnStatement(createPropertyAccess(className, property, classContext)))
    const getterFunction = arkts.factory.createScriptFunction(
        arkts.factory.createBlockStatement(getterStatements),
        undefined,
        [],
        property.typeAnnotation?.clone(),
        true,
        arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_METHOD | arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_GETTER,
        modifiers,
        arkts.factory.createIdentifier(name),
        []
    )

    const setterFunction = arkts.factory.createScriptFunction(
        arkts.factory.createBlockStatement([
            arkts.factory.createExpressionStatement(
                arkts.factory.createAssignmentExpression(
                    createPropertyAccess(className, property, classContext),
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
        modifiers,
        arkts.factory.createIdentifier(name),
        []
    )

    let setter = arkts.factory.createMethodDefinition(
        arkts.Es2pandaMethodDefinitionKind.METHOD_DEFINITION_KIND_SET,
        arkts.factory.createIdentifier(name),
        arkts.factory.createFunctionExpression(arkts.factory.createIdentifier(name), setterFunction),
        modifiers,
        false
    )

    let getter = arkts.factory.createMethodDefinition(
        arkts.Es2pandaMethodDefinitionKind.METHOD_DEFINITION_KIND_GET,
        arkts.factory.createIdentifier(name),
        arkts.factory.createFunctionExpression(arkts.factory.createIdentifier(name), getterFunction),
        modifiers,
        false,
        [setter]
    )

    return getter
}

function createClassMetadataMethod(classDef: arkts.ClassDefinition,
                                   classMetadataType: arkts.ETSTypeReference,
                                   classMetadataPropName: string,
                                   result: arkts.ClassElement[]) {
    const body: arkts.Statement[] = []
    body.push(
        arkts.factory.createReturnStatement(
            fieldOf(createETSTypeReference(classDef.ident?.name!), classMetadataPropName)
        )
    )
    createMethodDefinition("getClassMetadata",
        arkts.factory.createBlockStatement(body),
        arkts.factory.createETSUnionType([classMetadataType,
            arkts.factory.createETSUndefinedType()]),
        result
    )
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
    const isClassFullyObserved = classContext.isObservedV1() && classContext.trackedPropertyNames.length == 0
    const isTrackedProp = classContext.tracedPropertyNames.includes(propertyName)
    const isTracedProp = classContext.trackedPropertyNames.includes(propertyName)
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

function isStaticProperty(property: arkts.ClassProperty): boolean {
    return arkts.hasModifierFlag(property, arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_STATIC)
}

function recreateDisposedState(property: arkts.ClassProperty,
                               classContext: ClassContext,
                               className: string,
                               statements: arkts.Statement[]) {
    if (isStaticProperty(property)) {
        const state = fieldOf(createETSTypeReference(className), backingFieldNameOf(property))
        statements.push(arkts.factory.createIfStatement(fieldOf(state, "disposed"),
            arkts.factory.createBlockStatement(
                [
                    arkts.factory.createExpressionStatement(
                        arkts.factory.createAssignmentExpression(
                            state,
                            createBackingPropertyRValue(property, fieldOf(state, "value"), classContext),
                            arkts.Es2pandaTokenType.TOKEN_TYPE_PUNCTUATOR_SUBSTITUTION
                        )
                    )
                ]
            )
        ))
    }
}

class ClassContext {
    readonly decoratorType: ObservedDecoratorType | undefined
    readonly properties: ReadonlyMap<string, PropertyDecorator[]>

    constructor(observedDecoratorType: ObservedDecoratorType | undefined,
                properties: ReadonlyMap<string, PropertyDecorator[]>) {
        this.decoratorType = observedDecoratorType
        this.properties = properties

        this.verify()
    }

    get trackedPropertyNames() {
        return Array.from(this.properties.entries())
            .filter(it => it[1].some(it => it.name == DecoratorNames.TRACK))
            .map(it => it[0])
    }

    get tracedPropertyNames() {
        return Array.from(this.properties.entries())
            .filter(it => it[1].some(it => it.name == DecoratorNames.TRACE))
            .map(it => it[0])
    }

    get typedPropertyNames() {
        return this.typedProperties.map(it => it[0])
    }

    get typedProperties() {
        return Array.from(this.properties.entries())
            .filter(it => it[1].some(it => it.name == DecoratorNames.TYPE))
    }

    private verify() {
        if (this.decoratorType == DecoratorNames.OBSERVED_V2) {
            if (this.trackedPropertyNames.length) {
                throw new Error("@Track decorator is not applicable with @ObservedV2 decorator")
            }
        } else {
            if (this.tracedPropertyNames.length || this.typedPropertyNames.length) {
                throw new Error("@Trace decorator is only used with @ObservedV2 decorator")
            }
        }
    }

    isObservedV1(): boolean {
        return this.decoratorType == DecoratorNames.OBSERVED
    }

    isObservedV2(): boolean {
        return this.decoratorType == DecoratorNames.OBSERVED_V2
    }

    isClassObservable() {
        return this.decoratorType || this.trackedPropertyNames.length
    }

    needRewriteProperty(property: arkts.ClassProperty): boolean {
        if (this.isObservedV1() || this.trackedPropertyNames.length) {
            return !isStaticProperty(property)
        }
        return this.isObservedV2() && this.tracedPropertyNames.includes(property.id?.name!)
    }
}

class PropertyDecorator {
    readonly name: DecoratorNames
    readonly args: string[] = []

    constructor(name: DecoratorNames, args: string[] = []) {
        this.name = name
        this.args = args
    }
}