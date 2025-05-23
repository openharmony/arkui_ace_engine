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

import { DecoratorNames, getValueInDecorator, hasDecorator } from "./property-translators/utils"
import { CustomComponentNames, Importer, ImportingTransformer, InternalAnnotations } from "./utils"
import { annotation, classMethods, isAnnotation } from "./common/arkts-utils"

export interface PropertyTransformer extends ImportingTransformer {
    check(property: arkts.ClassProperty): boolean
    applyBuild(property: arkts.ClassProperty, result: arkts.Statement[]): void
    applyStruct(clazz: arkts.ClassDeclaration, property: arkts.ClassProperty, result: arkts.Statement[], pageLocalStorage?: arkts.Expression): void
    applyOptions(property: arkts.ClassProperty, result: arkts.Statement[]): void
    applyInitialization(property: arkts.ClassProperty, result: arkts.Statement[]): void
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

function createWrapperType(name: string, type: arkts.TypeNode): arkts.ETSTypeReference {
    return arkts.factory.createETSTypeReference(
        arkts.factory.createETSTypeReferencePart(
            arkts.factory.createIdentifier(name),
            arkts.factory.createTSTypeParameterInstantiation([type]),
            undefined
        )
    )
}

export function backingFieldName(name: string): string {
    return "__backing_" + name
}

function callBackingFieldMethod(method: string, property: arkts.ClassProperty, args: arkts.Expression[]): arkts.Statement {
    return arkts.factory.createExpressionStatement(
        arkts.factory.createCallExpression(
            fieldOf(fieldOf(arkts.factory.createThisExpression(), backingFieldName(property.id!.name)), method),
            args, undefined
        ))
}

function createWrappedProperty(
    name: string,
    clazz: arkts.ClassDeclaration,
    property: arkts.ClassProperty,
    wrapperTypeName: string,
    ctorParams: arkts.Expression[] = []
): arkts.ClassElement[] {
    const wrapperType = createWrapperType(wrapperTypeName, property.typeAnnotation!)
    const backingName = backingFieldName(name)
    let ctorArguments: arkts.Expression[] = [...ctorParams, arkts.factory.createStringLiteral(name)]
    if (property.value != undefined) {
        ctorArguments.push(property.value)
    }
    const backingField = arkts.factory.createClassProperty(
        arkts.factory.createIdentifier(backingName),
        arkts.factory.createETSNewClassInstanceExpression(wrapperType, ctorArguments),
        wrapperType,
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
                            arkts.factory.createIdentifier(backingName),
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
        property.typeAnnotation,
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
                        arkts.factory.createIdentifier(backingName),
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
                arkts.factory.createIdentifier("value"),
                false,
                undefined,
                property.typeAnnotation!
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
    setter.parent = getter

    return [backingField, getter]
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

export abstract class PropertyTransformerBase implements PropertyTransformer {
    abstract check(property: arkts.ClassProperty): boolean

    applyInitialization(property: arkts.ClassProperty, result: arkts.Statement[]): void { }
    applyBuild(property: arkts.ClassProperty, result: arkts.Statement[]): void { }
    applyStruct(clazz: arkts.ClassDeclaration, property: arkts.ClassProperty, result: arkts.ClassElement[]): void { }
    applyOptions(property: arkts.ClassProperty, result: arkts.ClassElement[]): void { }
    collectImports(result: Importer): void { }
}

function applyInitializer(property: arkts.ClassProperty, setter: string = "init"): arkts.Statement {
    let name = property.id?.name!
    return arkts.factory.createBlockStatement([
        arkts.factory.createExpressionStatement(
            arkts.factory.createCallExpression(
                fieldOf(
                    fieldOf(
                        arkts.factory.createThisExpression(), backingFieldName(name)
                    ), setter
                ),
                [
                    fieldOf(arkts.factory.createIdentifier(CustomComponentNames.COMPONENT_INITIALIZERS_NAME), name, true)
                ],
                undefined
            )
        )
    ])
}

export class StateTransformer extends PropertyTransformerBase {
    applyInitialization(property: arkts.ClassProperty, result: arkts.Statement[]): void {
        result.push(applyInitializer(property))
    }
    check(property: arkts.ClassProperty): boolean {
        return hasDecorator(property, DecoratorNames.STATE)
    }
    applyOptions(property: arkts.ClassProperty, result: arkts.ClassElement[]): void {
        result.push(createOptionalClassProperty(property.id!.name, property))
    }
    applyStruct(clazz: arkts.ClassDeclaration, property: arkts.ClassProperty, result: arkts.ClassElement[]): void {
        result.push(...createWrappedProperty(property.id!.name, clazz, property, "StateDecoratorProperty"))
    }
    collectImports(imports: Importer): void {
        imports.add("StateDecoratorProperty", "@ohos.arkui")
    }
}

export class PlainPropertyTransformer extends PropertyTransformerBase {
    check(property: arkts.ClassProperty): boolean {
        return property.annotations.length == 0
    }
    applyInitialization(property: arkts.ClassProperty, result: arkts.Statement[]): void {
        result.push(applyInitializer(property))
    }
    applyStruct(clazz: arkts.ClassDeclaration, property: arkts.ClassProperty, result: arkts.ClassElement[]): void {
        result.push(...createWrappedProperty(property.id!.name, clazz, property, "PlainStructProperty"))
    }
    applyOptions(property: arkts.ClassProperty, result: arkts.ClassElement[]): void {
        result.push(createOptionalClassProperty(property.id!.name, property))
    }
    collectImports(imports: Importer): void {
        imports.add("PlainStructProperty", "@ohos.arkui")
    }
}

export class LinkTransformer extends PropertyTransformerBase {
    applyInitialization(property: arkts.ClassProperty, result: arkts.Statement[]): void {
        const init = fieldOf(
            arkts.factory.createIdentifier(CustomComponentNames.COMPONENT_INITIALIZERS_NAME), property.id?.name!, true)
        result.push(arkts.factory.createIfStatement(
            (arkts.factory.createBinaryExpression(init, arkts.factory.createUndefinedLiteral(),
                Es2pandaTokenType.TOKEN_TYPE_PUNCTUATOR_NOT_EQUAL)),
            applyInitializer(property, "provide")
        ))
    }
    check(property: arkts.ClassProperty): boolean {
        return hasDecorator(property, DecoratorNames.LINK)
    }
    applyStruct(clazz: arkts.ClassDeclaration, property: arkts.ClassProperty, result: arkts.ClassElement[]): void {
        result.push(...createWrappedProperty(property.id!.name, clazz, property, "LinkDecoratorProperty"))
    }
    applyOptions(property: arkts.ClassProperty, result: arkts.ClassElement[]): void {
        result.push(arkts.factory.createClassProperty(
            arkts.factory.createIdentifier(property.id?.name!),
            undefined,
            createWrapperType("AbstractProperty", property.typeAnnotation!),
            arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_OPTIONAL,
            false
        ))
    }
    applyBuild(property: arkts.ClassProperty, result: arkts.Statement[]): void {
    }
    collectImports(imports: Importer): void {
        imports.add("LinkDecoratorProperty", "@ohos.arkui")
        imports.add("AbstractProperty", "@ohos.arkui")
    }
}

export class StorageLinkTransformer extends PropertyTransformerBase {
    check(property: arkts.ClassProperty): boolean {
        return hasDecorator(property, DecoratorNames.STORAGE_LINK)
    }

    applyStruct(clazz: arkts.ClassDeclaration, property: arkts.ClassProperty, result: arkts.ClassElement[]): void {
        result.push(...createWrappedProperty(property.id!.name, clazz, property, "StorageLinkDecoratorProperty", [
            arkts.factory.createStringLiteral(getValueInDecorator(property, DecoratorNames.STORAGE_LINK)!)
        ]))
    }

    collectImports(imports: Importer): void {
        imports.add("StorageLinkDecoratorProperty", "@ohos.arkui")
        imports.add("AbstractProperty", "@ohos.arkui")
    }
}


export class LocalStorageLinkTransformer extends StorageLinkTransformer {
    check(property: arkts.ClassProperty): boolean {
        return hasDecorator(property, DecoratorNames.LOCAL_STORAGE_LINK)
    }
    applyStruct(clazz: arkts.ClassDeclaration, property: arkts.ClassProperty, result: arkts.ClassElement[], pageLocalStorage?: arkts.Expression): void {
        if (!pageLocalStorage) {
            throw new Error(`@LocalStorageLink decorator requires storage or useSharedStorage to be set in @Entry decorator of the current file`)
        }
        result.push(...createWrappedProperty(property.id!.name, clazz, property, "LocalStorageLinkDecoratorProperty",
            [
                pageLocalStorage,
                arkts.factory.createStringLiteral(
                    annotationArgumentName(DecoratorNames.LOCAL_STORAGE_LINK, property)!
                )
            ]
        ))
    }
    collectImports(imports: Importer): void {
        imports.add("LocalStorageLinkDecoratorProperty", "@ohos.arkui")
        imports.add("AbstractProperty", "@ohos.arkui")
    }
}

export class PropTransformer extends PropertyTransformerBase {
    applyInitialization(property: arkts.ClassProperty, result: arkts.Statement[]): void {
        result.push(applyInitializer(property))
    }
    check(property: arkts.ClassProperty): boolean {
        return hasDecorator(property, DecoratorNames.PROP)
    }
    applyStruct(clazz: arkts.ClassDeclaration, property: arkts.ClassProperty, result: arkts.ClassElement[]): void {
        result.push(...createWrappedProperty(property.id!.name, clazz, property, "PropDecoratorProperty"))
    }
    applyOptions(property: arkts.ClassProperty, result: arkts.ClassElement[]): void {
        result.push(createOptionalClassProperty(property.id!.name, property))
    }
    applyBuild(property: arkts.ClassProperty, result: arkts.Statement[]): void {
        // Call backing.update(__context().scope<void>(__id(), 3), initializers?.property)
        result.push(callBackingFieldMethod("update", property, [
            // __context().scope<void>(__id(), 1)
            arkts.factory.createCallExpression(
                fieldOf(memoContext(), "scope"),
                [
                    memoId(), arkts.factory.createNumberLiteral(3)
                ], undefined, false),
            fieldOf(arkts.factory.createIdentifier(CustomComponentNames.COMPONENT_INITIALIZERS_NAME), property.id?.name!, true)
        ]))
    }
    collectImports(imports: Importer): void {
        imports.add("PropDecoratorProperty", "@ohos.arkui")
        imports.add("__id", "@koalaui/runtime")
    }
}

export class StoragePropTransformer extends PropertyTransformerBase {
    check(property: arkts.ClassProperty): boolean {
        return hasDecorator(property, DecoratorNames.STORAGE_PROP)
    }
    applyStruct(clazz: arkts.ClassDeclaration, property: arkts.ClassProperty, result: arkts.ClassElement[]): void {
        result.push(...createWrappedProperty(property.id!.name, clazz, property, "StoragePropDecoratorProperty",
            [
                arkts.factory.createStringLiteral(
                    annotationArgumentName(DecoratorNames.STORAGE_PROP, property)!
                )
            ]
        ))
    }
    collectImports(imports: Importer): void {
        imports.add("StoragePropDecoratorProperty", "@ohos.arkui")
        imports.add("AbstractProperty", "@ohos.arkui")
    }
}

export class LocalStoragePropTransformer extends StoragePropTransformer {
    check(property: arkts.ClassProperty): boolean {
        return hasDecorator(property, DecoratorNames.LOCAL_STORAGE_PROP)
    }
    applyStruct(clazz: arkts.ClassDeclaration, property: arkts.ClassProperty, result: arkts.ClassElement[], pageLocalStorage?: arkts.Expression): void {
        if (!pageLocalStorage) {
            throw new Error(`@LocalStorageProp decorator requires storage or useSharedStorage to be set in @Entry decorator of the current file`)
        }
        result.push(...createWrappedProperty(property.id!.name, clazz, property, "LocalStoragePropDecoratorProperty",
            [
                pageLocalStorage,
                arkts.factory.createStringLiteral(
                    annotationArgumentName(DecoratorNames.LOCAL_STORAGE_PROP, property)!
                )
            ]
        ))
    }
    collectImports(imports: Importer): void {
        imports.add("LocalStoragePropDecoratorProperty", "@ohos.arkui")
        imports.add("AbstractProperty", "@ohos.arkui")
    }
}

export class ObjectLinkTransformer extends PropertyTransformerBase {
    applyInitialization(property: arkts.ClassProperty, result: arkts.Statement[]): void {
        result.push(applyInitializer(property))
    }
    check(property: arkts.ClassProperty): boolean {
        return hasDecorator(property, DecoratorNames.OBJECT_LINK)
    }
    applyStruct(clazz: arkts.ClassDeclaration, property: arkts.ClassProperty, result: arkts.ClassElement[]): void {
        throw new Error(`Implement me`)
    }
    applyOptions(property: arkts.ClassProperty, result: arkts.ClassElement[]): void {
        throw new Error(`Implement me`)
    }
}

export function fieldOf(base: arkts.Expression, name: string, optional: boolean = false): arkts.MemberExpression {
    return arkts.factory.createMemberExpression(
        base,
        arkts.factory.createIdentifier(name),
        arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_PROPERTY_ACCESS,
        false,
        optional)
}

function annotationArgumentName(name: string, propertyOriginal: arkts.ClassProperty): string | undefined {
    const property = propertyOriginal.annotations.find(it => arkts.isIdentifier(it.expr) && it.expr.name == name)!.properties[0]
    if (property === undefined) {
        return undefined
    }
    if (!arkts.isClassProperty(property)) {
        return undefined
    }
    if (property.value === undefined) {
        return undefined
    }
    if (!arkts.isStringLiteral(property.value)) {
        return undefined
    }
    return property.value.str
}

function memoContext(): arkts.Expression {
    return arkts.factory.createCallExpression(arkts.factory.createIdentifier("__context"), [], undefined)
}

function memoId(): arkts.Expression {
    return arkts.factory.createCallExpression(arkts.factory.createIdentifier("__id"), [], undefined)
}

export class ProvideTransformer extends PropertyTransformerBase {
    check(property: arkts.ClassProperty): boolean {
        return hasDecorator(property, DecoratorNames.PROVIDE)
    }
    applyInitialization(property: arkts.ClassProperty, result: arkts.Statement[]): void {
        result.push(applyInitializer(property))
    }
    applyBuild(property: arkts.ClassProperty, result: arkts.Statement[]): void {
        result.push(callBackingFieldMethod("provide", property, [memoContext()]))
    }
    applyStruct(clazz: arkts.ClassDeclaration, property: arkts.ClassProperty, result: arkts.ClassElement[]): void {
        result.push(...createWrappedProperty(property.id!.name, clazz, property, "ProvideDecoratorProperty",
            [
                arkts.factory.createStringLiteral(
                    annotationArgumentName(DecoratorNames.PROVIDE, property) ?? property.id?.name!
                )
            ]
        ))
    }
    applyOptions(property: arkts.ClassProperty, result: arkts.ClassElement[]): void {
        result.push(createOptionalClassProperty(property.id!.name, property))
    }
    collectImports(imports: Importer): void {
        imports.add("ProvideDecoratorProperty", "@ohos.arkui")
        imports.add("__context", "@koalaui/runtime")
    }
}

export class ConsumeTransformer extends PropertyTransformerBase {
    check(property: arkts.ClassProperty): boolean {
        return hasDecorator(property, DecoratorNames.CONSUME)
    }
    applyBuild(property: arkts.ClassProperty, result: arkts.Statement[]): void {
        result.push(callBackingFieldMethod("consume", property, [memoContext()]))
    }
    applyStruct(clazz: arkts.ClassDeclaration, property: arkts.ClassProperty, result: arkts.ClassElement[]): void {
        result.push(...createWrappedProperty(property.id!.name, clazz, property, "ConsumeDecoratorProperty",
            [
                arkts.factory.createStringLiteral(
                    annotationArgumentName(DecoratorNames.CONSUME, property) ?? property.id?.name!
                )
            ]
        ))
    }
    applyOptions(property: arkts.ClassProperty, result: arkts.ClassElement[]): void {
    }
    collectImports(imports: Importer): void {
        imports.add("ConsumeDecoratorProperty", "@ohos.arkui")
        imports.add("__context", "@koalaui/runtime")
        imports.add("StateContext", "@koalaui/runtime")
    }
}

export class BuilderParamTransformer extends PropertyTransformerBase {
    check(property: arkts.ClassProperty): boolean {
        return hasDecorator(property, DecoratorNames.BUILDER_PARAM)
    }
    applyInitialization(property: arkts.ClassProperty, result: arkts.Statement[]): void {
        result.push(applyInitStatement(property))
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
    applyOptions(property: arkts.ClassProperty, result: arkts.ClassElement[]): void {
        let backing = createOptionalClassProperty(property.id!.name, property)
        backing.setAnnotations([annotation(InternalAnnotations.MEMO)])
        result.push(backing)
    }
}

function applyInitStatement(property: arkts.ClassProperty): arkts.Statement {
    const name = property.id?.name!
    const identifier = arkts.factory.createIdentifier(name, undefined)
    const initDeclaration = arkts.factory.createVariableDeclaration(
        arkts.Es2pandaVariableDeclarationKind.VARIABLE_DECLARATION_KIND_CONST,
        [
            arkts.factory.createVariableDeclarator(
                arkts.Es2pandaVariableDeclaratorFlag.VARIABLE_DECLARATOR_FLAG_CONST,
                identifier,
                fieldOf(arkts.factory.createIdentifier(CustomComponentNames.COMPONENT_INITIALIZERS_NAME), name, true)
            )
        ]
    )
    const initBlock = arkts.factory.createIfStatement(
        arkts.factory.createBinaryExpression(
            identifier,
            arkts.factory.createUndefinedLiteral(),
            Es2pandaTokenType.TOKEN_TYPE_PUNCTUATOR_NOT_EQUAL
        ),
        arkts.factory.createBlockStatement([
            arkts.factory.createExpressionStatement(
                arkts.factory.createAssignmentExpression(
                    fieldOf(arkts.factory.createThisExpression(), name),
                    identifier,
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
