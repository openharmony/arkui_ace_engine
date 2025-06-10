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

import * as ts from "@koalaui/ets-tsc"
import {
    Any,
    Private,
    asIdentifier,
    assignment,
    createThisFieldAccess,
    dropReadonly,
    findDecoratorArgument,
    id,
    isStatic,
    makePrivate,
    parameter,
} from "./ApiUtils"
import { Importer } from "./Importer"
import {
    backingField,
    backingFieldName,
    BuilderParamDecorator,
    collect,
    ConsumeDecorator,
    consumeVariableName,
    createBlock,
    createNotNullAccessor,
    createNullableAccessor,
    createNullishCoalescing,
    createValueAccessor,
    dropDecorators,
    filterDecorators,
    idTextOrError,
    initializers,
    isBuilderParam,
    isConsume,
    isLink,
    isLocalStorageLink,
    isLocalStorageProp,
    isObjectLink,
    isProp,
    isProvide,
    isState,
    isStorageLink,
    isStorageProp,
    LinkDecorator,
    LocalStorageLinkDecorator,
    LocalStoragePropDecorator,
    LocalStoragePropertyName,
    ObjectLinkDecorator,
    prependDoubleLineMemoComment,
    prependMemoComment,
    PropDecorator,
    ProvideDecorator,
    provideVariableName,
    StateDecorator,
    StateImplementation,
    StorageLinkDecorator,
    StoragePropDecorator,
    SyncedPropertyConstructor,
    WatchDecorator,
} from "./utils"
import { MessageCode, reportError } from "./diagnostics"
import { OptionDescriptor } from "./StructOptions"

export class PropertyTranslatorContext {
    constructor(
        public importer: Importer,
        public sourceFile: ts.SourceFile,
        public extras?: ts.TransformerExtras,
    ) {}
} {}


export abstract class PropertyTranslator {
    private cachedType: ts.TypeNode | undefined // do not analyze this.property.initializer every time
    constructor(
        protected property: ts.PropertyDeclaration,
        protected context: PropertyTranslatorContext
    ) { }

    get propertyName(): string {
        return idTextOrError(this.property.name)
    }
    get propertyType(): ts.TypeNode {
        let type = this.property.type ?? this.cachedType
        if (!type) this.cachedType = type = this.typeInference(this.property.initializer)
        return type
    }
    private typeInference(initializer?: ts.Expression): ts.TypeNode {
        // TODO: try to analyze this.property.initializer
        return Any()
    }

    abstract translateMember(): ts.ClassElement[]

    translateToInitialization(): ts.Statement | undefined {
        return undefined
    }
    translateToUpdate(): ts.Statement | undefined {
        return undefined
    }

    /**
     * translate struct property to an entry in Record<string, Object>
     * Only used in ArkTS implementation.
     */
    translateToRecordEntry(object: ts.Expression): ts.PropertyAssignment {
        const name = this.propertyName
        return ts.factory.createPropertyAssignment(
            ts.factory.createStringLiteral(name),
            createNullishCoalescing(
                createNullableAccessor(ts.factory.createPropertyAccessExpression(object, backingField(name)), "value"),
                ts.factory.createNewExpression(ts.factory.createIdentifier("Object"), undefined, [])
            )
        )
    }

    createStateOf(type: ts.TypeNode | undefined, ...initializer: ts.Expression[]): ts.Expression {
        return createStateOf(this.context.importer, type, ...initializer)
    }

    translateStateMember(
        property: ts.PropertyDeclaration,
        decoratorName: string,
        initializer: ts.Expression | undefined,
        type: ts.TypeNode | undefined,
        addExclamation: boolean
    ): ts.ClassElement[] {

        const originalName = idTextOrError(property.name)
        const newName = backingField(originalName)

        const field = ts.factory.updatePropertyDeclaration(
            property,
            makePrivate(dropDecorators(property.modifiers, decoratorName, WatchDecorator)),
            newName,
            ts.factory.createToken(ts.SyntaxKind.QuestionToken),
            type,
            initializer
        )

        const getter = this.createStateGetter(originalName, newName)
        const setter = this.createStateSetter(originalName, newName)

        return [field, getter, setter]
    }

    translatePlainMember(
        property: ts.PropertyDeclaration,
        initializer: ts.Expression | undefined,
        type: ts.TypeNode,
        decorator?: string,
        memo?: boolean
    ): ts.ClassElement[] {
        const originalName = idTextOrError(property.name)
        const newName = backingField(originalName)
        const isOptional = initializer === undefined

        const field = ts.factory.updatePropertyDeclaration(
            property,
            makePrivate(dropReadonly(dropDecorators(property.modifiers, decorator))),
            newName,
            isOptional ? ts.factory.createToken(ts.SyntaxKind.QuestionToken) : undefined,
            type,
            initializer
        )

        const getter = this.createPlainGetter(originalName, newName, type, memo, isOptional)
        const setter = this.createPlainSetter(originalName, newName, type, memo)

        const backingFieldWithMemo = memo ? prependMemoComment(field) : field

        // TODO: don't produce any setters for readonly properties
        return [backingFieldWithMemo, getter, setter]
    }

    mutableState(type: ts.TypeNode,): ts.TypeNode {
        return ts.factory.createTypeReferenceNode(
            id(this.context.importer.withRuntimeImport("MutableState")),
            [type]
        )
    }

    translateStateWithoutInitializer(
        property: ts.PropertyDeclaration,
        decoratorName: string,
        syncedProperty: boolean = false,
    ): ts.ClassElement[] {
        return this.translateStateMember(
            property,
            decoratorName,
            undefined,
            ts.factory.createTypeReferenceNode(
                syncedProperty
                    ? this.context.importer.withAdaptorImport("SyncedProperty")
                    : this.context.importer.withRuntimeImport("MutableState"),
                [
                    this.propertyType
                ]
            ),
            true
        )
    }

    translateStateWithInitializer(
        property: ts.PropertyDeclaration,
        decorator: string,
        initializer: ts.Expression,
    ): ts.ClassElement[] {
        return this.translateStateMember(property, decorator, initializer, undefined, false)
    }

    protected createAppStorageState(decoratorName: string): ts.Expression {
        return ts.factory.createCallExpression(
            id(this.context.importer.withAdaptorImport("AppStorageLinkState")),
            [this.propertyType],
            [
                findDecoratorArgument(filterDecorators(this.property), decoratorName, 0),
                this.property.initializer!
            ]
        )
    }

    protected createLocalStorageState(decoratorName: string): ts.Expression {
        return ts.factory.createCallExpression(
            id(this.context.importer.withAdaptorImport("StorageLinkState")),
            [this.propertyType],
            [
                createThisFieldAccess(LocalStoragePropertyName),
                findDecoratorArgument(filterDecorators(this.property), decoratorName, 0),
                this.property.initializer!
            ]
        )
    }

    private createStateGetter(originalName: string, newName: string): ts.GetAccessorDeclaration {
        return ts.factory.createGetAccessorDeclaration(
            [Private()],
            id(originalName),
            [],
            this.propertyType,
            createBlock(
                    ts.factory.createReturnStatement(
                        createValueAccessor(
                            // TODO: issue a message if there is no @Provide.
                            ts.factory.createNonNullExpression(
                                createThisFieldAccess(newName)
                            )
                        )
                    )
            )
        )

    }

    private createStateSetter(originalName: string, newName: string, postStatements?: ts.Statement[]) {
        const preStatement =
            (postStatements?.length ?? 0) > 0 ?
                ts.factory.createVariableStatement(
                    [Private()],
                    ts.factory.createVariableDeclarationList(
                        [
                            ts.factory.createVariableDeclaration(
                                id("oldValue"),
                                undefined,
                                undefined,
                                createValueAccessor(
                                    ts.factory.createNonNullExpression(
                                        createThisFieldAccess(newName)
                                    )
                                )
                            )
                        ],
                        ts.NodeFlags.Const
                    )
                )
                : undefined

        return ts.factory.createSetAccessorDeclaration(
            [Private()],
            id(originalName),
            [
                parameter(
                    "value",
                    this.propertyType
                )
            ],
            ts.factory.createBlock(
                collect(
                    preStatement,
                    assignment(
                        createValueAccessor(
                            // TODO: issue a message if there is no @Provide.
                            ts.factory.createNonNullExpression(
                                createThisFieldAccess(newName)
                            )
                        ),
                        createObservableProxy(this.context.importer, undefined, id("value"))
                    ),
                    postStatements
                ),
                true
            )
        )
    }

    createPlainGetter(
        originalName: string,
        newName: string,
        type: ts.TypeNode,
        memo: boolean = false,
        isOptional: boolean = false
    ): ts.GetAccessorDeclaration {
        let returnValue: ts.Expression = createThisFieldAccess(newName)
        if (isOptional) {
            returnValue = memo
                ? ts.factory.createNonNullExpression(returnValue)
                : ts.factory.createAsExpression(returnValue, type)
        }
        const getter = ts.factory.createGetAccessorDeclaration(
            [Private()],
            id(originalName),
            [],
            this.propertyType,
            createBlock(
                ts.factory.createReturnStatement(
                    returnValue
                )
            )
        )
        return memo ? prependMemoComment(getter) : getter
    }

    createPlainSetter(originalName: string, newName: string, type: ts.TypeNode | undefined, memo?: boolean) {
        const param = parameter(
            id("value"),
            type
        )

        return ts.factory.createSetAccessorDeclaration(
            [Private()],
            id(originalName),
            [
                memo ? prependDoubleLineMemoComment(param) : param
            ],
            createBlock(assignToField(newName, id("value")))
        )
    }

    translateInitializerOfSyncedProperty(constructorName: SyncedPropertyConstructor, withValue?: ts.Expression): ts.Expression {
        return ts.factory.createCallExpression(
            id(this.context.importer.withAdaptorImport(constructorName)),
            this.property.type ? [this.property.type] : undefined,
            withValue ? [withValue] : []
        )
    }

    translateToUpdateSyncedProperty(withValue: ts.Expression): ts.Statement {
        return ts.factory.createExpressionStatement(
            ts.factory.createCallChain(
                ts.factory.createPropertyAccessChain(
                    createThisFieldAccess(backingField(this.propertyName)),
                    ts.factory.createToken(ts.SyntaxKind.QuestionDotToken),
                    "update"
                ),
                undefined,
                undefined,
                [withValue]
            )
        )
    }

    abstract toInitialization(initializers: ts.Identifier): ts.PropertyAssignment[]

    protected initializeBacking(initializers: ts.Identifier) {
        return [this.initializeFromInitializers(
            backingField(this.propertyName),
            backingField(this.propertyName),
            initializers
        )]
    }

    protected initializePlain(initializers: ts.Identifier) {
        return [this.initializeFromInitializers(
            this.propertyName,
            this.propertyName,
            initializers
        )]
    }

    protected initializeBoth(initializers: ts.Identifier) {
        return [
            ...this.initializePlain(initializers),
            ...this.initializeBacking(initializers),
        ]
    }

    private initializeFromInitializers(to: string, from: string, initializers: ts.Identifier) {
        return ts.factory.createPropertyAssignment(
            id(to),
            ts.factory.createPropertyAccessChain(
                initializers,
                ts.factory.createToken(ts.SyntaxKind.QuestionDotToken),
                id(from)
            )
        )
    }

    public abstract implField(): OptionDescriptor[]

    protected stateImplField(impl: StateImplementation): OptionDescriptor[] {
        const originalName = asIdentifier(this.property.name)
        const originalType = getPropertyType(this.property, this.context)
        const backingName = backingFieldName(asIdentifier(this.property.name))
        const backingType = ts.factory.createTypeReferenceNode(
            (impl === StateImplementation.SyncedProperty) ?
                impl :
                this.context.importer.withRuntimeImport(impl),

            [originalType]
        )
        return [
            new OptionDescriptor(backingName, backingType),
            new OptionDescriptor(originalName, originalType)
        ]
    }

    protected plainImplField(needsMemo: boolean): OptionDescriptor[] {
        const name = asIdentifier(this.property.name)
        const type = getPropertyType(this.property, this.context)

        return [new OptionDescriptor(name, type, needsMemo)]
    }
}

export function createObservableProxy(importer: Importer, type: ts.TypeNode | undefined, ...initializer: ts.Expression[]): ts.Expression {
    return ts.factory.createCallExpression(
        id(importer.withCommonImport("observableProxy")),
        type ? [type] : undefined,
        initializer
    )
}

export function createStateOf(importer: Importer, type: ts.TypeNode | undefined, ...initializer: ts.Expression[]): ts.Expression {
    return ts.factory.createCallExpression(
        id(importer.withAdaptorImport("stateOf")),
        type ? [type] : undefined,
        initializer
    )
}

export function getPropertyType(property: ts.PropertyDeclaration, context: PropertyTranslatorContext): ts.TypeNode {
    const type = property.type
    if (type) return type
    reportError(
        MessageCode.EXPECTED_STRUCT_FIELD__TO_BE_EXPLICITLY_TYPED,
        `Expected field to be explicitly typed in ArkTS 1.2 app: ${property.getText(context.sourceFile)}`,
        property,
        context.sourceFile,
        context.extras
    )
    return ts.factory.createTypeReferenceNode("<Error type>")
}

class State extends PropertyTranslator {
    override implField(): OptionDescriptor[] {
        return this.stateImplField(StateImplementation.MutableState)
    }
    override toInitialization(initializers: ts.Identifier) {
        return this.initializeBacking(initializers)
    }

    translateMember(): ts.ClassElement[] {
        return this.translateStateWithoutInitializer(this.property, StateDecorator)
    }

    translateToInitialization(): ts.Statement {
        const name = this.propertyName
        return assignToBackingField(
            name,
            this.createStateOf(
                this.propertyType,
                createNullishCoalescing(
                    createNullableAccessor(initializers(), name),
                    this.property.initializer!
                ),
                ts.factory.createThis()
            )
        )
    }

    override translateToReuse(): ts.Statement | undefined {
        const name = this.propertyName
        return ts.factory.createIfStatement(
            createNullableAccessor(initializers(), name),
            assignToField(name, createNotNullAccessor(initializers(), name))
        )
    }
}

class Prop extends PropertyTranslator {
    override implField(): OptionDescriptor[] {
        return this.stateImplField(StateImplementation.SyncedProperty)
    }

    override toInitialization(initializers: ts.Identifier) {
        return this.initializeBoth(initializers)
    }

    translateMember(): ts.ClassElement[] {
        return this.translateStateWithoutInitializer(this.property, PropDecorator, true)
    }
    override translateToInitialization(): ts.Statement {
        return assignToBackingField(
            this.propertyName,
            this.translateInitializerOfSyncedProperty(SyncedPropertyConstructor.propState, this.property.initializer))
    }
    translateToUpdate(): ts.Statement {
        return this.translateToUpdateSyncedProperty(createNullableAccessor(initializers(), this.propertyName))
    }
    translateToBuildParameter(): ts.ParameterDeclaration {
        return translatePropOrObjectLinkToBuildParameter(this.property, this.context.importer)
    }
}

class Link extends PropertyTranslator {
    override implField(): OptionDescriptor[] {
        return this.stateImplField(StateImplementation.MutableState)
    }

    override toInitialization(initializers: ts.Identifier) {
        return this.initializeBacking(initializers)
    }

    translateMember(): ts.ClassElement[] {
        return this.translateStateWithoutInitializer(this.property, LinkDecorator)
    }
    translateToInitialization(): ts.Statement {
        return translateToInitializationFromInitializers(backingField(this.propertyName))
    }
}

class ObjectLink extends PropertyTranslator {
    override implField(): OptionDescriptor[] {
        return this.stateImplField(StateImplementation.SyncedProperty)
    }

    override toInitialization(initializers: ts.Identifier) {
        return this.initializeBoth(initializers)
    }

    translateMember(): ts.ClassElement[] {
        return this.translateStateWithoutInitializer(this.property, ObjectLinkDecorator, true)
    }
    override translateToInitialization(): ts.Statement {
        return assignToBackingField(
            this.propertyName,
            this.translateInitializerOfSyncedProperty(SyncedPropertyConstructor.objectLink, this.property.initializer))
    }
    translateToUpdate(): ts.Statement {
        return this.translateToUpdateSyncedProperty(createNullableAccessor(initializers(), this.propertyName))
    }
    translateToBuildParameter(): ts.ParameterDeclaration {
        return translatePropOrObjectLinkToBuildParameter(this.property, this.context.importer)
    }
}

class Provide extends PropertyTranslator {
    override implField(): OptionDescriptor[] {
        return this.stateImplField(StateImplementation.MutableState)
    }

    override toInitialization(initializers: ts.Identifier) {
        return [ts.factory.createPropertyAssignment(
            backingField(this.propertyName),
            provideVariableName(this.property)
        )]
    }

    translateMember(): ts.ClassElement[] {
        return this.translateStateWithoutInitializer(this.property, ProvideDecorator)
    }
    translateToInitialization() {
        return translateToInitializationFromInitializers(backingField(this.propertyName))
    }
}

class Consume extends PropertyTranslator {
    override implField(): OptionDescriptor[] {
        return this.stateImplField(StateImplementation.MutableState)
    }

    override toInitialization(initializers: ts.Identifier) {
        return [ts.factory.createPropertyAssignment(
            backingField(this.propertyName),
            consumeVariableName(this.property)
        )]
    }

    translateMember(): ts.ClassElement[] {
        return this.translateStateWithoutInitializer(this.property, ConsumeDecorator)
    }
    translateToInitialization() {
        return translateToInitializationFromInitializers(backingField(this.propertyName))
    }
}

class StorageLink extends PropertyTranslator {
    public implField(): OptionDescriptor[] {
        const name = backingFieldName(asIdentifier(this.property.name))
        const type = ts.factory.createTypeReferenceNode(
            this.context.importer.withRuntimeImport("MutableState"),
            [getPropertyType(this.property, this.context)]
        )

        const name1 = asIdentifier(this.property.name)
        const type1 = getPropertyType(this.property, this.context)
        return [
            new OptionDescriptor(name, type),
            new OptionDescriptor(name1, type1)
        ]
    }

    override toInitialization(initializers: ts.Identifier) {
        return this.initializeBacking(initializers)
    }

    translateMember(): ts.ClassElement[] {
        return this.translateStateWithoutInitializer(this.property, StorageLinkDecorator)
    }

    translateToInitialization(): ts.Statement {
        return assignToBackingField(this.propertyName, this.createAppStorageState(StorageLinkDecorator))
    }

}
class LocalStorageLink extends PropertyTranslator {
    override implField(): OptionDescriptor[] {
        return this.stateImplField(StateImplementation.MutableState)
    }

    override toInitialization(initializers: ts.Identifier) {
        return this.initializeBacking(initializers)
    }

    translateMember(): ts.ClassElement[] {
        return this.translateStateWithoutInitializer(this.property, LocalStorageLinkDecorator)
    }

    translateToInitialization(): ts.Statement {
        return assignToBackingField(this.propertyName, this.createLocalStorageState(LocalStorageLinkDecorator))
    }

}
class StorageProp extends PropertyTranslator {
    override implField(): OptionDescriptor[] {
        return this.stateImplField(StateImplementation.SyncedProperty)
    }

    override toInitialization(initializers: ts.Identifier) {
        return this.initializeBacking(initializers)
    }

    translateMember(): ts.ClassElement[] {
        return this.translateStateWithoutInitializer(this.property, StoragePropDecorator, true)
    }
    override translateToInitialization(): ts.Statement {
        return assignToBackingField(
            this.propertyName,
            this.translateInitializerOfSyncedProperty(SyncedPropertyConstructor.propState, this.createAppStorageValue()))
    }
    translateToUpdate(): ts.Statement {
        return this.translateToUpdateSyncedProperty(this.createAppStorageValue())
    }
    createAppStorageValue(): ts.Expression {
        return createValueAccessor(this.createAppStorageState(StoragePropDecorator))
    }

}
class LocalStorageProp extends PropertyTranslator {
    override implField(): OptionDescriptor[] {
        return this.stateImplField(StateImplementation.SyncedProperty)
    }

    override toInitialization(initializers: ts.Identifier) {
        return this.initializeBacking(initializers)
    }

    translateMember(): ts.ClassElement[] {
        return this.translateStateWithoutInitializer(this.property, LocalStoragePropDecorator, true)
    }
    override translateToInitialization(): ts.Statement {
        return assignToBackingField(
            this.propertyName,
            this.translateInitializerOfSyncedProperty(SyncedPropertyConstructor.propState, this.createLocalStorageValue()))
    }
    translateToUpdate(): ts.Statement {
        return this.translateToUpdateSyncedProperty(this.createLocalStorageValue())
    }
    createLocalStorageValue(): ts.Expression {
        return createValueAccessor(this.createLocalStorageState(LocalStoragePropDecorator))
    }
}

export class BuilderParam extends PropertyTranslator {
    override implField(): OptionDescriptor[] {
        return this.plainImplField(true)
    }

    override toInitialization(initializers: ts.Identifier) {
        return this.initializePlain(initializers)
    }

    constructor(protected property: ts.PropertyDeclaration, protected context: PropertyTranslatorContext) {
        super(property, context)
    }
    translateMember(): ts.ClassElement[] {
        return this.translatePlainMember(
            this.property,
            undefined,
            this.propertyType,
            BuilderParamDecorator,
            /* memo = */ true
        )
    }
    translateToInitialization(): ts.Statement | undefined {
        let initializer = this.property.initializer
        if (initializer) {
            initializer = prependDoubleLineMemoComment(
                ts.factory.createArrowFunction(
                    undefined,
                    undefined,
                    [],
                    undefined,
                    ts.factory.createToken(ts.SyntaxKind.EqualsGreaterThanToken),
                    createBlock(
                        ts.factory.createExpressionStatement(
                            ts.factory.createCallExpression(
                                initializer,
                                undefined,
                                []
                            )))
                )
            )
        }
        return initializePlainProperty(this.propertyName, initializer)
    }
}

class PlainProperty extends PropertyTranslator {
    override implField(): OptionDescriptor[] {
        return this.plainImplField(false)
    }

    override toInitialization(initializers: ts.Identifier) {
        return this.initializePlain(initializers)
    }

    constructor(protected property: ts.PropertyDeclaration, protected context: PropertyTranslatorContext) {
        super(property, context)
    }
    translateMember(): ts.ClassElement[] {
        return this.translatePlainMember(
            this.property,
            undefined,
            this.propertyType
        )
    }
    translateToInitialization(): ts.Statement | undefined {
        return initializePlainProperty(this.propertyName, this.property.initializer)
    }
}

function initializePlainProperty(name: string, initializer?: ts.Expression): ts.Statement {
    return initializer
        ? assignToBackingField(name, createNullishCoalescing(createNullableAccessor(initializers(), name), initializer))
        : ts.factory.createIfStatement(
            createNullableAccessor(initializers(), name),
            createBlock(assignToBackingField(name, createNullableAccessor(initializers(), name)))
        )
}

function assignToBackingField(name: string, expression: ts.Expression): ts.Statement {
    return assignToField(backingField(name), expression)
}

function assignToField(name: string, expression: ts.Expression): ts.Statement {
    return assignment(createThisFieldAccess(name), expression)
}

function translateToInitializationFromInitializers(name: string): ts.Statement {
    return assignToField(name, createNotNullAccessor(initializers(), name))
}

function translatePropOrObjectLinkToBuildParameter(property: ts.PropertyDeclaration, importer: Importer): ts.ParameterDeclaration {
    return parameter(
        backingField(idTextOrError(property.name)),
        property.type
    )
}

export function classifyProperty(member: ts.ClassElement, context: PropertyTranslatorContext): PropertyTranslator | undefined {
    if (!ts.isPropertyDeclaration(member)) return undefined
    if (isStatic(member)) return undefined

    if (isState(member)) return new State(member, context)
    if (isStorageProp(member)) return new StorageProp(member, context)
    if (isStorageLink(member)) return new StorageLink(member, context)
    if (isLocalStorageLink(member)) return new LocalStorageLink(member, context)
    if (isLocalStorageProp(member)) return new LocalStorageProp(member, context)
    if (isLink(member)) return new Link(member, context)
    if (isProp(member)) return new Prop(member, context)
    if (isObjectLink(member)) return new ObjectLink(member, context)
    if (isProvide(member)) return new Provide(member, context)
    if (isConsume(member)) return new Consume(member, context)
    if (isBuilderParam(member)) return new BuilderParam(member, context)

    return new PlainProperty(member, context)
}
