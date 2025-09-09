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
import { Es2pandaTokenType } from "@koalaui/libarkts"

import { DecoratorNames, DecoratorParameters, hasDecorator } from "./property-translators/utils"
import { CustomComponentNames, getComponentPackage, getDecoratorPackage, getRuntimePackage, Importer, ImportingTransformer, InternalAnnotations } from "./utils"
import { annotation, classMethods, isAnnotation } from "./common/arkts-utils"

export interface PropertyTransformer extends ImportingTransformer {
    check(property: arkts.ClassProperty): boolean
    applyBuild(property: arkts.ClassProperty, result: arkts.Statement[]): void
    applyStruct(clazz: arkts.ClassDeclaration, property: arkts.ClassProperty, result: arkts.ClassElement[]): void
    applyOptions(property: arkts.ClassProperty, result: arkts.Statement[]): void
    applyInitializeStruct(localStorage: arkts.Expression | undefined, property: arkts.ClassProperty, result: arkts.Statement[]): void
    applyDisposeStruct(property: arkts.ClassProperty, result: arkts.Statement[]): void
    applyReuseRecord(property: arkts.ClassProperty, result: arkts.Expression[]): void
}

function createOptionalClassProperty(
    name: string,
    property: arkts.ClassProperty
): arkts.ClassProperty {
    let result = arkts.factory.createClassProperty(
        arkts.factory.createIdentifier(name, undefined),
        undefined,
        property.typeAnnotation,
        arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_OPTIONAL | arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC,
        false
    )
    return result
}

export function createWrapperType(name: string, type: arkts.TypeNode, useUnion: boolean = false): arkts.TypeNode {
    const box = arkts.factory.createETSTypeReference(
        arkts.factory.createETSTypeReferencePart(
            arkts.factory.createIdentifier(name),
            arkts.factory.createTSTypeParameterInstantiation([type.clone()]),
            undefined
        )
    )
    return useUnion ? arkts.factory.createETSUnionType([type.clone(), box]) : box
}

function backingFieldNameOf(property: arkts.ClassProperty): string {
    return "__backing_" + property.id!.name
}

function thisPropertyMethodCall(property: arkts.ClassProperty, method: string, args: readonly arkts.Expression[] = []): arkts.Statement {
    return arkts.factory.createExpressionStatement(thisPropertyMethodCallExpr(property, method, args))
}

function thisPropertyMethodCallExpr(property: arkts.ClassProperty, method: string, args: readonly arkts.Expression[] = []): arkts.CallExpression {
    return arkts.factory.createCallExpression(fieldOf(fieldOf(arkts.factory.createThisExpression(), backingFieldNameOf(property)), method), args, undefined)
}

function createWrappedProperty(
    clazz: arkts.ClassDeclaration,
    property: arkts.ClassProperty,
    wrapperTypeName: string,
    ctorParams: arkts.Expression[] = []
): arkts.ClassElement[] {
    const wrapperTypeForValue = createWrapperType(wrapperTypeName, property.typeAnnotation!)
    const wrapperTypeForType = createWrapperType(wrapperTypeName, property.typeAnnotation!)
    const name = property.id!.name
    let ctorArguments: arkts.Expression[] = [...ctorParams, arkts.factory.createStringLiteral(name)]
    if (property.value != undefined) {
        ctorArguments.push(property.value)
    }
    const backingField = arkts.factory.createClassProperty(
        arkts.factory.createIdentifier(backingFieldNameOf(property)),
        arkts.factory.createETSNewClassInstanceExpression(wrapperTypeForValue, ctorArguments),
        wrapperTypeForType,
        arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PRIVATE,
        false
    )

    const getterFunction = arkts.factory.createScriptFunction(
        arkts.factory.createBlockStatement([
            arkts.factory.createReturnStatement(
                arkts.factory.createCallExpression(
                    arkts.factory.createMemberExpression(
                        arkts.factory.createMemberExpression(
                            arkts.factory.createThisExpression(),
                            arkts.factory.createIdentifier(backingFieldNameOf(property)),
                            arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_PROPERTY_ACCESS,
                            false,
                            false
                        ),
                        arkts.factory.createIdentifier("get"),
                        arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_PROPERTY_ACCESS,
                        false,
                        false
                    ), [], undefined
                )
            )
        ]),
        undefined,
        [
        ],
        property.typeAnnotation?.clone(),
        true,
        arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_METHOD | arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_GETTER,
        arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC,
        arkts.factory.createIdentifier(name),
        []
    )

    const setterStatements: arkts.Statement[] = [
        arkts.factory.createExpressionStatement(
            arkts.factory.createCallExpression(
                arkts.factory.createMemberExpression(
                    arkts.factory.createMemberExpression(
                        arkts.factory.createThisExpression(),
                        arkts.factory.createIdentifier(backingFieldNameOf(property)),
                        arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_PROPERTY_ACCESS,
                        false,
                        false
                    ),
                    arkts.factory.createIdentifier("set"),
                    arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_PROPERTY_ACCESS,
                    false,
                    false
                ),
                [
                    arkts.factory.createIdentifier("value"),
                ],
                undefined
            )
        )
    ]
    const watchMethods = property.annotations.filter(isWatchDecorator).map(getWatchParameter)
    for (let i = 0; i < watchMethods.length; i++) {
        setterStatements.push(createWatchCall(clazz, watchMethods[i], name))
    }

    const setterFunction = arkts.factory.createScriptFunction(
        arkts.factory.createBlockStatement(setterStatements),
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

    return [backingField, getter]
}

function addTrackablePropertyTo(
    result: arkts.ClassElement[],
    clazz: arkts.ClassDeclaration,
    property: arkts.ClassProperty,
    propertyTypeName: string
) {
    const valueType = property.typeAnnotation
    if (!valueType) throw new Error(`@${propertyTypeName}: type is not specified for ${property.id?.name}`)

    const propertyName = property.id!.name
    const propertyTypeForValue = createWrapperType(propertyTypeName, valueType)
    const propertyTypeForType = createWrapperType(propertyTypeName, valueType)
    const propertyArgs: arkts.Expression[] = [arkts.factory.createStringLiteral(propertyName)]
    const watches = property.annotations.filter(isWatchDecorator).map(getWatchParameter)
    if (watches.length > 0) {
        propertyArgs.push(
            arkts.factory.createArrowFunctionExpression(
                arkts.factory.createScriptFunction(
                    arkts.factory.createBlockStatement(
                        watches.map(watch => createWatchCall(clazz, watch, propertyName))
                    ),
                    undefined,
                    [],
                    undefined,
                    false,
                    arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_ARROW,
                    arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_NONE,
                    undefined,
                    undefined
                )
            )
        )
    }
    const backingField = arkts.factory.createClassProperty(
        arkts.factory.createIdentifier(backingFieldNameOf(property)),
        arkts.factory.createETSNewClassInstanceExpression(propertyTypeForValue, propertyArgs),
        propertyTypeForType,
        arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PRIVATE,
        false
    )
    const getterFunction = arkts.factory.createScriptFunction(
        arkts.factory.createBlockStatement([
            arkts.factory.createReturnStatement(thisPropertyMethodCallExpr(property, "get"))
        ]),
        undefined,
        [],
        valueType.clone(),
        true,
        arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_METHOD | arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_GETTER,
        arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC,
        arkts.factory.createIdentifier(propertyName),
        []
    )
    const setterFunction = arkts.factory.createScriptFunction(
        arkts.factory.createBlockStatement([
            thisPropertyMethodCall(property, "set", [arkts.factory.createIdentifier("value")])
        ]),
        undefined,
        [
            arkts.factory.createETSParameterExpression(
                arkts.factory.createIdentifier("value", valueType.clone()),
                false,
                undefined,
            )
        ],
        undefined,
        true,
        arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_METHOD | arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_SETTER | arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_OVERLOAD,
        arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC,
        arkts.factory.createIdentifier(propertyName),
        []
    )
    const setter = arkts.factory.createMethodDefinition(
        arkts.Es2pandaMethodDefinitionKind.METHOD_DEFINITION_KIND_SET,
        arkts.factory.createIdentifier(propertyName),
        arkts.factory.createFunctionExpression(arkts.factory.createIdentifier(propertyName), setterFunction),
        arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC,
        false
    )
    const getter = arkts.factory.createMethodDefinition(
        arkts.Es2pandaMethodDefinitionKind.METHOD_DEFINITION_KIND_GET,
        arkts.factory.createIdentifier(propertyName),
        arkts.factory.createFunctionExpression(arkts.factory.createIdentifier(propertyName), getterFunction),
        arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC,
        false,
        [setter]
    )
    result.push(backingField)
    result.push(getter)
}

function isWatchDecorator(usage: arkts.AnnotationUsage): boolean {
    return isAnnotation(usage, DecoratorNames.WATCH)
}

function getWatchParameter(usage: arkts.AnnotationUsage): string {
    const properties = usage.properties
    if (properties.length != 1) throw new Error("@Watch: only one parameter is expected")
    const property = usage.properties[0]
    if (!arkts.isClassProperty(property)) throw new Error("@Watch: expected class property")
    const parameter = property.value
    if (!arkts.isStringLiteral(parameter)) throw new Error("@Watch: expected string literal")
    return parameter.str
}

function isWatchMethod(method: arkts.MethodDefinition, methodName: string): boolean {
    const f = method.function
    return (f != undefined)
        && (f.params.length == 1)
        && (f.id?.name == methodName)
}

function createWatchCall(clazz: arkts.ClassDeclaration, methodName: string, propertyName: string): arkts.Statement {
    const parameters = new Array<arkts.Expression>()
    const methods = classMethods(clazz, method => isWatchMethod(method, methodName))
    if (methods.length > 0) parameters.push(arkts.factory.createStringLiteral(propertyName))
    return arkts.factory.createExpressionStatement(
        arkts.factory.createCallExpression(
            fieldOf(arkts.factory.createThisExpression(), methodName),
            parameters,
            undefined)
    )
}

function addPropertyRecordTo(result: arkts.Expression[], property: arkts.ClassProperty) {
    result.push(arkts.factory.createProperty(
        arkts.Es2pandaPropertyKind.PROPERTY_KIND_INIT,
        arkts.factory.createStringLiteral(property.id!.name),
        arkts.factory.createBinaryExpression(
            fieldOf(arkts.factory.createTSNonNullExpression(
                arkts.factory.createIdentifier(CustomComponentNames.COMPONENT_INITIALIZERS_NAME)
            ), property.id!.name),
            property.value ?? arkts.factory.createETSNewClassInstanceExpression(
                arkts.factory.createETSTypeReference(
                    arkts.factory.createETSTypeReferencePart(
                        arkts.factory.createIdentifier("Object", undefined), undefined, undefined
                    )
                ),
                []),
            arkts.Es2pandaTokenType.TOKEN_TYPE_PUNCTUATOR_NULLISH_COALESCING
        ),
        false, false
    ))
}

export abstract class PropertyTransformerBase implements PropertyTransformer {
    constructor(public decoratorName: DecoratorNames, public className: string) {
    }
    check(property: arkts.ClassProperty): boolean {
        return hasDecorator(property, this.decoratorName)
    }
    collectImports(importer: Importer): void {
        importer.add(this.className, getDecoratorPackage())
    }
    applyOptions(property: arkts.ClassProperty, result: arkts.ClassElement[]): void {
    }
    applyStruct(clazz: arkts.ClassDeclaration, property: arkts.ClassProperty, result: arkts.ClassElement[]): void {
        addTrackablePropertyTo(result, clazz, property, this.className)
    }
    abstract applyInitializeStruct(localStorage: arkts.Expression | undefined, property: arkts.ClassProperty, result: arkts.Statement[]): void
    applyDisposeStruct(property: arkts.ClassProperty, result: arkts.Statement[]): void {
        result.push(thisPropertyMethodCall(property, "aboutToBeDeleted"))
    }
    applyReuseRecord(property: arkts.ClassProperty, result: arkts.Expression[]): void {
    }
    applyBuild(property: arkts.ClassProperty, result: arkts.Statement[]): void {
    }
}

export class StateTransformer extends PropertyTransformerBase {
    constructor() {
        super(DecoratorNames.STATE, "StateDecoratorProperty")
    }
    applyOptions(property: arkts.ClassProperty, result: arkts.ClassElement[]): void {
        result.push(createOptionalClassProperty(property.id!.name, property))
    }
    applyInitializeStruct(localStorage: arkts.Expression | undefined, property: arkts.ClassProperty, result: arkts.Statement[]): void {
        result.push(thisPropertyMethodCall(property, "init", [initializerOf(property), property.value!]))
    }
    applyReuseRecord(property: arkts.ClassProperty, result: arkts.Expression[]): void {
        addPropertyRecordTo(result, property)
    }
}

export class PlainPropertyTransformer implements PropertyTransformer {
    check(property: arkts.ClassProperty): boolean {
        return property.annotations.length == 0
    }
    collectImports(imports: Importer): void {
        imports.add("PlainStructProperty", getDecoratorPackage())
    }
    applyOptions(property: arkts.ClassProperty, result: arkts.ClassElement[]): void {
        result.push(createOptionalClassProperty(property.id!.name, property))
    }
    applyStruct(clazz: arkts.ClassDeclaration, property: arkts.ClassProperty, result: arkts.ClassElement[]): void {
        result.push(...createWrappedProperty(clazz, property, "PlainStructProperty"))
    }
    applyInitializeStruct(localStorage: arkts.Expression | undefined, property: arkts.ClassProperty, result: arkts.Statement[]): void {
        result.push(thisPropertyMethodCall(property, "init", [initializerOf(property)]))
    }
    applyDisposeStruct(property: arkts.ClassProperty, result: arkts.Statement[]): void {
    }
    applyReuseRecord(property: arkts.ClassProperty, result: arkts.Expression[]): void {
        addPropertyRecordTo(result, property)
    }
    applyBuild(property: arkts.ClassProperty, result: arkts.Statement[]): void {
    }
}

export class LinkTransformer extends PropertyTransformerBase {
    constructor() {
        super(DecoratorNames.LINK, "LinkDecoratorProperty")
    }
    applyOptions(property: arkts.ClassProperty, result: arkts.ClassElement[]): void {
       result.push(arkts.factory.createClassProperty(
                    arkts.factory.createIdentifier(property.id?.name!),
                    undefined,
                    createWrapperType("SubscribedAbstractProperty", property.typeAnnotation!, true),
                    arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_OPTIONAL,
                    false
        ))
        //result.push(createOptionalClassProperty(property.id!.name, property))
    }
    applyInitializeStruct(localStorage: arkts.Expression | undefined, property: arkts.ClassProperty, result: arkts.Statement[]): void {
        result.push(thisPropertyMethodCall(property, "linkTo", [initializerOf(property)]))
    }
    applyReuseRecord(property: arkts.ClassProperty, result: arkts.Expression[]): void {
        addPropertyRecordTo(result, property)
    }
    collectImports(imports: Importer): void {
        imports.add("SubscribedAbstractProperty", getDecoratorPackage())
        imports.add("LinkDecoratorProperty", getDecoratorPackage())
    }
}

function withStorageKey(expressions: arkts.Expression[], property: arkts.ClassProperty, decorator: DecoratorNames): arkts.Expression[] {
    const props = property.annotations.find(usage => isAnnotation(usage, decorator))!.properties
    if (props.length > 1) throw new Error(`@${decorator}: only one parameter is expected`)
    if (props.length > 0) {
        const prop = props[0]
        if (!arkts.isClassProperty(prop)) throw new Error(`@${decorator}: expected class property`)
        const param = prop.value
        if (param) expressions.push(param)
    }
    return expressions
}

export class StorageLinkTransformer extends PropertyTransformerBase {
    constructor() {
        super(DecoratorNames.STORAGE_LINK, "StorageLinkDecoratorProperty")
    }
    applyInitializeStruct(localStorage: arkts.Expression | undefined, property: arkts.ClassProperty, result: arkts.Statement[]): void {
        result.push(thisPropertyMethodCall(property, "init", withStorageKey([property.value!], property, this.decoratorName)))
    }
}


export class LocalStorageLinkTransformer extends PropertyTransformerBase {
    constructor() {
        super(DecoratorNames.LOCAL_STORAGE_LINK, "LocalStorageLinkDecoratorProperty")
    }
    applyInitializeStruct(localStorage: arkts.Expression | undefined, property: arkts.ClassProperty, result: arkts.Statement[]): void {
        if (!localStorage) throw new Error("@LocalStorageLink decorator requires specified local storage")
        result.push(thisPropertyMethodCall(property, "init", withStorageKey([property.value!, localStorage], property, this.decoratorName)))
    }
}

export class PropTransformer extends PropertyTransformerBase {
    constructor() {
        super(DecoratorNames.PROP, "PropDecoratorProperty")
    }
    applyOptions(property: arkts.ClassProperty, result: arkts.ClassElement[]): void {
        result.push(createOptionalClassProperty(property.id!.name, property))
    }
    applyInitializeStruct(localStorage: arkts.Expression | undefined, property: arkts.ClassProperty, result: arkts.Statement[]): void {
        result.push(thisPropertyMethodCall(property, "init", [initializerOf(property), property.value ?? arkts.factory.createUndefinedLiteral()]))
    }
    applyReuseRecord(property: arkts.ClassProperty, result: arkts.Expression[]): void {
        addPropertyRecordTo(result, property)
    }
    applyBuild(property: arkts.ClassProperty, result: arkts.Statement[]): void {
        result.push(thisPropertyMethodCall(property, "update", [initializerOf(property)]))
    }
}

export class StoragePropTransformer extends PropertyTransformerBase {
    constructor() {
        super(DecoratorNames.STORAGE_PROP, "StoragePropDecoratorProperty")
    }
    applyInitializeStruct(localStorage: arkts.Expression | undefined, property: arkts.ClassProperty, result: arkts.Statement[]): void {
        result.push(thisPropertyMethodCall(property, "init", withStorageKey([property.value!], property, this.decoratorName)))
    }
}

export class LocalStoragePropTransformer extends PropertyTransformerBase {
    constructor() {
        super(DecoratorNames.LOCAL_STORAGE_PROP, "LocalStoragePropDecoratorProperty")
    }
    applyInitializeStruct(localStorage: arkts.Expression | undefined, property: arkts.ClassProperty, result: arkts.Statement[]): void {
        if (!localStorage) throw new Error("@LocalStorageProp decorator requires specified local storage")
        result.push(thisPropertyMethodCall(property, "init", withStorageKey([property.value!, localStorage], property, this.decoratorName)))
    }
}

export class ObjectLinkTransformer extends PropertyTransformerBase {
    constructor() {
        super(DecoratorNames.OBJECT_LINK, "ObjectLinkDecoratorProperty")
    }
    applyOptions(property: arkts.ClassProperty, result: arkts.ClassElement[]): void {
        result.push(createOptionalClassProperty(property.id!.name, property))
    }
    applyInitializeStruct(localStorage: arkts.Expression | undefined, property: arkts.ClassProperty, result: arkts.Statement[]): void {
        result.push(thisPropertyMethodCall(property, "init", [initializerOf(property), property.value ?? arkts.factory.createUndefinedLiteral()]))
    }
    applyReuseRecord(property: arkts.ClassProperty, result: arkts.Expression[]): void {
        addPropertyRecordTo(result, property)
    }
    applyBuild(property: arkts.ClassProperty, result: arkts.Statement[]): void {
        result.push(thisPropertyMethodCall(property, "update", [initializerOf(property)]))
    }
}

export function fieldOf(base: arkts.Expression, name: string, optional: boolean = false): arkts.Expression {
    const result = arkts.factory.createMemberExpression(
        base,
        arkts.factory.createIdentifier(name),
        arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_PROPERTY_ACCESS,
        false,
        optional
    )
    if (optional) return arkts.factory.createChainExpression(result)
    return result
}

function initializerOf(property: arkts.ClassProperty): arkts.Expression {
    return fieldOf(arkts.factory.createIdentifier(CustomComponentNames.COMPONENT_INITIALIZERS_NAME), property.id!.name, true)
}

function parseAllowOverride(propertyOriginal: arkts.ClassProperty): boolean {
    const allowOverrideProperty = propertyOriginal.annotations.find(it => {
            return arkts.isIdentifier(it.expr) && it.expr.name === DecoratorNames.PROVIDE
        })?.properties.find(it => {
            return arkts.isClassProperty(it) && it.id?.name === DecoratorParameters.ALLOW_OVERRIDE
        })
    return allowOverrideProperty !== undefined
}

function callStatementsOnce(statements: arkts.Statement[]): arkts.Statement {
    const lambdaBody = arkts.factory.createBlockStatement(statements)
    const lambda = arkts.factory.createScriptFunction(
        lambdaBody,
        undefined,
        [],
        undefined,
        false,
        arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_ARROW,
        arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_NONE,
        undefined,
        undefined
    )
    return arkts.factory.createExpressionStatement(
        arkts.factory.createCallExpression(
            arkts.factory.createIdentifier("once"),
            [ arkts.factory.createArrowFunctionExpression(lambda) ],
            undefined,
        )
    )
}

export class ProvideTransformer extends PropertyTransformerBase {
    constructor() {
        super(DecoratorNames.PROVIDE, "ProvideDecoratorProperty")
    }
    applyOptions(property: arkts.ClassProperty, result: arkts.ClassElement[]): void {
        result.push(createOptionalClassProperty(property.id!.name, property))
    }
    applyInitializeStruct(localStorage: arkts.Expression | undefined, property: arkts.ClassProperty, result: arkts.Statement[]): void {
        result.push(thisPropertyMethodCall(property, "init", [initializerOf(property), property.value!]))
    }
    applyReuseRecord(property: arkts.ClassProperty, result: arkts.Expression[]): void {
        addPropertyRecordTo(result, property)
    }
    applyBuild(property: arkts.ClassProperty, result: arkts.Statement[]): void {
        const allowOverride = parseAllowOverride(property)
        const params = withStorageKey([], property, this.decoratorName)
        if (!allowOverride) {
            result.push(callStatementsOnce([
                thisPropertyMethodCall(property, "checkOverrides", params)
            ]))
        }
        result.push(thisPropertyMethodCall(property, "provide", params))
    }
    collectImports(imports: Importer): void {
        super.collectImports(imports)
        imports.add("once", getRuntimePackage())
    }

}

export class ConsumeTransformer extends PropertyTransformerBase {
    constructor() {
        super(DecoratorNames.CONSUME, "ConsumeDecoratorProperty")
    }
    applyInitializeStruct(localStorage: arkts.Expression | undefined, property: arkts.ClassProperty, result: arkts.Statement[]): void {
        if (property.value) throw new Error("@Consume decorator does not expect property initializer")
        result.push(thisPropertyMethodCall(property, "init", withStorageKey([], property, this.decoratorName)))
    }
}

export class BuilderParamTransformer implements PropertyTransformer {
    check(property: arkts.ClassProperty): boolean {
        return hasDecorator(property, DecoratorNames.BUILDER_PARAM)
    }
    collectImports(result: Importer): void {
    }
    applyOptions(property: arkts.ClassProperty, result: arkts.ClassElement[]): void {
        let backing = createOptionalClassProperty(property.id!.name, property)
        backing.setAnnotations([annotation(InternalAnnotations.MEMO)])
        result.push(backing)
    }
    applyStruct(clazz: arkts.ClassDeclaration, property: arkts.ClassProperty, result: arkts.ClassElement[]): void {
        let backing = arkts.factory.createClassProperty(
            property.id,
            property.value,
            undefined,
            arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC,
            false
        )
        backing.setAnnotations([annotation(InternalAnnotations.MEMO)])
        result.push(backing)
    }
    applyInitializeStruct(localStorage: arkts.Expression | undefined, property: arkts.ClassProperty, result: arkts.Statement[]): void {
        result.push(applyInitStatement(property))
    }
    applyDisposeStruct(property: arkts.ClassProperty, result: arkts.Statement[]): void {
    }
    applyReuseRecord(property: arkts.ClassProperty, result: arkts.Expression[]): void {
        // cause ClassCastError on panda while using default value
        // LambdaObject$lambda$invoke$805 cannot be cast to std.core.Function0
        // addPropertyRecordTo(result, property)
    }
    applyBuild(property: arkts.ClassProperty, result: arkts.Statement[]): void {
    }
}

function applyInitStatement(property: arkts.ClassProperty): arkts.Statement {
    const name = property.id?.name!
    const initDeclaration = arkts.factory.createVariableDeclaration(
        arkts.Es2pandaVariableDeclarationKind.VARIABLE_DECLARATION_KIND_CONST,
        [
            arkts.factory.createVariableDeclarator(
                arkts.Es2pandaVariableDeclaratorFlag.VARIABLE_DECLARATOR_FLAG_CONST,
                arkts.factory.createIdentifier(name),
                initializerOf(property)
            )
        ]
    )
    const initBlock = arkts.factory.createIfStatement(
        arkts.factory.createBinaryExpression(
            arkts.factory.createIdentifier(name),
            arkts.factory.createUndefinedLiteral(),
            Es2pandaTokenType.TOKEN_TYPE_PUNCTUATOR_NOT_EQUAL
        ),
        arkts.factory.createBlockStatement([
            arkts.factory.createExpressionStatement(
                arkts.factory.createAssignmentExpression(
                    fieldOf(arkts.factory.createThisExpression(), name),
                    arkts.factory.createTSNonNullExpression(arkts.factory.createIdentifier(name)),
                    arkts.Es2pandaTokenType.TOKEN_TYPE_PUNCTUATOR_SUBSTITUTION
                )
            )
        ])
    )
    return arkts.factory.createBlockStatement([initDeclaration, initBlock])
}

export function isOptionBackedByProperty(property: arkts.ClassProperty): boolean {
    return hasDecorator(property, DecoratorNames.LINK)
}

export function isOptionBackedByPropertyName(decorator: string): boolean {
    return decorator == DecoratorNames.LINK
}
