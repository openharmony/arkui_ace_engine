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

import * as ts from '@koalaui/ets-tsc'
import * as path from 'path'
import { getDeclarationsByNode, getDecorator, hasDecorator, id, isCallDecorator, isDecorator, prependComment, Void } from './ApiUtils'
import { Importer } from "./Importer";

export const ComponentDecorator = "Component"
export const EntryDecorator = "Entry"
export const ReusableDecorator = "Reusable"
export const LocalStoragePropertyName = "_entry_local_storage_"

export const StateDecorator = "State"
export const PropDecorator = "Prop"
export const LinkDecorator = "Link"
export const ObjectLinkDecorator = "ObjectLink"
export const ProvideDecorator = "Provide"
export const ConsumeDecorator = "Consume"
export const StorageLinkDecorator = "StorageLink"
export const StoragePropDecorator = "StorageProp"
export const LocalStorageLinkDecorator = "LocalStorageLink"
export const LocalStoragePropDecorator = "LocalStorageProp"
export const BuilderParamDecorator = "BuilderParam"
export const BuilderDecorator = "Builder"
export const BuilderLambdaDecorator = "BuilderLambda"
export const WatchDecorator = "Watch"
export const CustomDialogDecorator = "CustomDialog"

export const StylesDecorator = "Styles"
export const ExtendDecorator = "Extend"
export const AnimatableExtendDecorator = "AnimatableExtend"
export const ArkCommonMethodInterface = "ArkCommonMethodInterface"
export const ArkCommonMethodComponent = "ArkCommonMethodComponent"
export const T_TypeParameter = "T"
export const styledInstance = mangle("instance")
export const CommonInstance = "CommonInstance"
export const Instance = "Instance"
export const DollarDollar = "$$"

export enum SyncedPropertyConstructor {
    propState = "propState",
    objectLink = "objectLinkState"
}

export enum StateImplementation {
    SyncedProperty = "SyncedProperty",
    MutableState = "MutableState",
}

export enum RewriteNames {
    Initializers = "initializers",
    InitializeStruct = "__initializeStruct",
    UpdateStruct = "__updateStruct",
    ToRecord = "__toRecord",
    ApplyStyle = "__applyStyle",
    ApplyAnimatableExtend = "__applyAnimatableExtend"
}

export class NameTable {
    structs: string[] = []
    dollars: string[] = []
}

export class IssueTable {
    newEtsWithProperty: number[] = []
    newEts: number[] = []
    builderLambda: number[] = []
}

export class CallTable {
    builderLambdas = new Map<ts.CallExpression, string>()
    globalBuilderCalls = new Set<ts.CallExpression>()
    legacyCalls = new Set<ts.CallExpression>()
    structCalls = new Set<ts.CallExpression>()
    lazyCalls = new Set<ts.Identifier>()
}

export function prependMemoComment<T extends ts.Node>(node: T): T {
    return prependComment(node, "* @memo ")
}

export function prependMemoStable<T extends ts.Node>(node: T): T {
    return prependComment(node, "* @memo:stable ")
}

export function prependMemoCommentIfArkoala<T extends ts.Node>(node: T, importer: Importer): T {
    return importer.isArkoala()
        ? prependMemoComment(node)
        : node
}

export function prependDoubleLineMemoComment<T extends ts.Node>(node: T): T {
    return prependComment(prependComment(node, ""), "* @memo ")
}

export function relativeToSource(sourcePath: string, sourceDir: string): string {
    return path.relative(sourceDir, sourcePath)
}

export function emitStartupFile(entryFile: string, sourceDir: string, destinationDir: string) {
    const absoluteSourceDir = path.resolve(sourceDir)
    const absoluteEntryFile = path.resolve(entryFile)
    const relativeEntryFile = path.relative(absoluteSourceDir, absoluteEntryFile)
    if (!relativeEntryFile.endsWith(".ets")) return

    const importPath = relativeEntryFile.substring(0, relativeEntryFile.length - 4)
    console.log("IMPORT FROM: " + importPath)

    const mainFile = path.join(destinationDir, "main.ts")
    console.log("STARTUP: " + mainFile)

}

export function typeParameterExtendsType(name: string, superName: string, superArguments: string[]) {
    return ts.factory.createTypeParameterDeclaration(
        undefined,
        id(name),
        ts.factory.createTypeReferenceNode(
            id(superName),
            superArguments.map(
                it => ts.factory.createTypeReferenceNode(
                    id(it)
                )
            )
        ),
        undefined
    )
}

export function mangleIfBuild(name: ts.PropertyName): ts.PropertyName {
    if (!ts.isIdentifier(name)) return name
    const stringName = ts.idText(name)
    if (stringName === "build") {
        return id(mangle("build"))
    } else {
        return name
    }
}

export function isNamedDeclaration(node: ts.Node): node is ts.NamedDeclaration {
    return ("name" in node)
}

/** @returns true if the given node represents an identifier */
export function isTextIdentifier(node: ts.Node): node is ts.Identifier | ts.PrivateIdentifier {
    return ts.isIdentifier(node) || ts.isPrivateIdentifier(node)
}

/** @returns text identifier from the specified node */
export function idTextOrError(node: ts.Node): string {
    if (isTextIdentifier(node)) return ts.idText(node)
    throw new Error("Expected an identifier, got: " + ts.SyntaxKind[node.kind])
}

export function asString(node: ts.Node | undefined): string {
    if (node === undefined) return "undefined node"
    if (isTextIdentifier(node)) return ts.idText(node)
    if (ts.isEtsComponentExpression(node)) return `EtsComponentExpression(${ts.idText(node.expression as ts.Identifier)}`
    if (isNamedDeclaration(node)) {
        if (node.name === undefined) {
            return `${ts.SyntaxKind[node.kind]}(undefined name)`
        } else {
            return `${ts.SyntaxKind[node.kind]}(${asString(node.name)})`
        }
    } else {
        return `${ts.SyntaxKind[node.kind]}`
    }
}

export function adaptorName(original: string): string {
    return `Ark${original}`
}

export function adaptorComponentName(original: string): string {
    return `Ark${original}Component`
}

export function etsAttributeName(original: string): string {
    const attribute = `${original}Attribute`
    return attribute.startsWith("Lazy") ? attribute.substring(4) : attribute
}

export function backingField(originalName: string): string {
    return mangle(`backing_${originalName}`)
}

export function backingFieldName(originalName: ts.Identifier | ts.PrivateIdentifier): ts.Identifier {
    return id(backingField(ts.idText(originalName)))
}

export function adaptorEtsName(name: ts.Identifier): ts.Identifier {
    return id(adaptorName(ts.idText(name)))
}

export function adaptorEtsAttributeName(name: ts.Identifier): ts.Identifier {
    return id(etsAttributeName(ts.idText(name)))
}

export function adaptorClassName(name: ts.Identifier): ts.Identifier
export function adaptorClassName(name: undefined): undefined
export function adaptorClassName(name: ts.Identifier | undefined): ts.Identifier | undefined
export function adaptorClassName(name: ts.Identifier | undefined): ts.Identifier | undefined {
    if (!name) return undefined
    return id(adaptorComponentName(ts.idText(name)))
}

export function customDialogImplName(name: ts.Identifier | undefined): ts.Identifier | undefined {
    if (!name) return undefined
    return id(ts.idText(name) + "Impl")
}

export function deduceBuilderLambdaName(functionDeclaration: ts.FunctionDeclaration): string {
    const decorator = getDecorator(functionDeclaration, BuilderLambdaDecorator)
    if (!decorator) throw new Error("Expected a decorator")

    if (ts.isCallExpression(decorator.expression)) {
        const name = decorator.expression.arguments[0]!
        if (ts.isIdentifier(name)) {
            return ts.idText(name)
        }
        if (ts.isStringLiteral(name)) {
            return name.text
        }
    }
    throw new Error("Unexpected decorator kind: " + asString(decorator.expression))
}

export function findBuilderLambdaRedirect(typechecker: ts.TypeChecker, node: ts.Node): string | undefined {
    if (!ts.isCallExpression(node)) return undefined
    const func = node.expression
    if (!ts.isIdentifier(func)) return undefined

    const declarations = getDeclarationsByNode(typechecker, func)

    if (declarations.length == 0) return undefined
    const firstDeclaration = declarations[0]
    if (!firstDeclaration) return undefined
    if (!isBuilderLambda(firstDeclaration)) return undefined

    return deduceBuilderLambdaName(firstDeclaration as ts.FunctionDeclaration)
}

export function isBuilderLambdaCall(callTable: CallTable, node: ts.CallExpression): boolean {
    const originalNode = ts.getOriginalNode(node) as ts.CallExpression
    return callTable.builderLambdas.has(originalNode)
}

export function isStructCall(callTable: CallTable, node: ts.CallExpression): boolean {
    const originalNode = ts.getOriginalNode(node) as ts.CallExpression
    return callTable.structCalls.has(originalNode)
}

export function deduceProvideConsumeName(property: ts.PropertyDeclaration, name: string): string {
    const decorator = getDecorator(property, name)
    if (!decorator) throw new Error("Expected a decorator")

    // @Provide foo
    if (ts.isIdentifier(decorator.expression)) {
        return idTextOrError(property.name)
    }
    // @Provide("bar") foo && @Provide({ allowOverride: 'bar'}) bar
    if (ts.isCallExpression(decorator.expression)) {
        const arg = decorator.expression.arguments[0]!
        if (ts.isIdentifier(arg)) {
            return ts.idText(arg)
        }
        if (ts.isStringLiteral(arg)) {
            return arg.text
        }
        // @Provide({ allowOverride: 'bar'}) bar
        if (ts.isObjectLiteralExpression(arg)) {
            const propertiesName = (arg as ts.ObjectLiteralExpression).properties
                .filter(
                    (property) =>
                        ts.isPropertyAssignment(property) &&
                        property.name.getText() === "allowOverride"
                )
            if (propertiesName.length > 0) {
                const arg = propertiesName[0] as ts.PropertyAssignment
                if (ts.isStringLiteral(arg.initializer)) {
                    return arg.initializer.text
                }
            }
        }
    }

    throw new Error("Unexpected decorator kind: " + asString(decorator.expression))
}

export function deduceProvideName(property: ts.PropertyDeclaration) {
    return deduceProvideConsumeName(property, ProvideDecorator)
}

export function deduceConsumeName(property: ts.PropertyDeclaration) {
    return deduceProvideConsumeName(property, ConsumeDecorator)
}

export function getAnnotationArgument(decorator: ts.Decorator): ts.Identifier | undefined {
    if (!ts.isCallExpression(decorator.expression)) return undefined
    const args = decorator.expression.arguments
    if (args.length > 1) return undefined
    const argument = args[0]
    if (!ts.isIdentifier(argument)) return undefined
    return argument
}

export function isExtend(decorator: ts.Decorator): boolean {
    return isCallDecorator(decorator, ExtendDecorator)
}

export function isState(property: ts.PropertyDeclaration): boolean {
    return hasDecorator(property, StateDecorator)
}

export function isLink(property: ts.PropertyDeclaration): boolean {
    return hasDecorator(property, LinkDecorator)
}

export function isProp(property: ts.PropertyDeclaration): boolean {
    return hasDecorator(property, PropDecorator)
}

export function isObjectLink(property: ts.PropertyDeclaration): boolean {
    return hasDecorator(property, ObjectLinkDecorator)
}

export function isConsume(property: ts.PropertyDeclaration): boolean {
    return hasDecorator(property, ConsumeDecorator)
}

export function isStorageProp(property: ts.PropertyDeclaration): boolean {
    return hasDecorator(property, StoragePropDecorator)
}

export function isStorageLink(property: ts.PropertyDeclaration): boolean {
    return hasDecorator(property, StorageLinkDecorator)
}

export function isLocalStorageProp(property: ts.PropertyDeclaration): boolean {
    return hasDecorator(property, LocalStoragePropDecorator)
}

export function isLocalStorageLink(property: ts.PropertyDeclaration): boolean {
    return hasDecorator(property, LocalStorageLinkDecorator)
}

export function isBuilder(property: ts.MethodDeclaration): boolean {
    return hasDecorator(property, BuilderDecorator)
}

export function isBuilderParam(property: ts.PropertyDeclaration): boolean {
    return hasDecorator(property, BuilderParamDecorator)
}

export function isProvide(property: ts.PropertyDeclaration): boolean {
    return hasDecorator(property, ProvideDecorator)
}

export function dropBuilder(modifierLikes: readonly ts.ModifierLike[] | undefined): ts.ModifierLike[] | undefined {
    return dropDecorators(modifierLikes, BuilderDecorator)
}

export function dropStylesLike(modifierLikes: readonly ts.ModifierLike[] | undefined): ts.ModifierLike[] | undefined {
    return dropDecorators(modifierLikes, StylesDecorator, ExtendDecorator, AnimatableExtendDecorator)
}

export function dropDecorators(modifierLikes: readonly ts.ModifierLike[] | undefined, ...decorators: (string | undefined)[]): ts.ModifierLike[] | undefined {
    const defined = decorators.filter((it): it is string => it !== undefined)
    return modifierLikes?.filter(it => defined.every(decorator => !isDecorator(it, decorator)))
}

export function filterDecorators(node: ts.Node): readonly ts.Decorator[] | undefined {
    return ts.getAllDecorators(node)
}

export function filterModifiers(node: ts.Node): readonly ts.Modifier[] | undefined {
    if (!ts.canHaveModifiers(node)) {
        return undefined
    }
    return ts.getModifiers(node)
}

export function contextLocalStateOf(name: string, initializer: ts.Expression, type?: ts.TypeNode): ts.Expression {
    return ts.factory.createCallExpression(
        id("contextLocalStateOf"),
        type ? [type] : undefined,
        [
            ts.factory.createStringLiteral(name),
            ts.factory.createArrowFunction(
                undefined,
                undefined,
                [],
                undefined,
                ts.factory.createToken(ts.SyntaxKind.EqualsGreaterThanToken),
                initializer
            )
        ]
    )
}

export function isGlobalBuilder(node: ts.Node): boolean {
    return ts.isFunctionDeclaration(node) && hasDecorator(node, BuilderDecorator)
}

export function isBuilderLambda(node: ts.Node): boolean {
    return ts.isFunctionDeclaration(node) && hasDecorator(node, BuilderLambdaDecorator)
}

export function provideConsumeVariableName(decorator: string, prefix: string, property: ts.PropertyDeclaration): ts.Identifier {
    if (!ts.isIdentifier(property.name) && !ts.isPrivateIdentifier(property.name)) {
        throw new Error("Expected an identifier")
    }

    return id(prefix + deduceProvideConsumeName(property, decorator))
}

export function consumeVariableName(consume: ts.PropertyDeclaration): ts.Identifier {
    return provideConsumeVariableName(ConsumeDecorator, "__consume_", consume)
}

export function provideVariableName(provide: ts.PropertyDeclaration): ts.Identifier {
    return provideConsumeVariableName(ProvideDecorator, "__provide_", provide)
}

export function createProvideInitializerField(provide: ts.PropertyDeclaration): ts.PropertyAssignment {
    return ts.factory.createPropertyAssignment(
        backingFieldName(provide.name as ts.Identifier),
        provideVariableName(provide)
    )
}

export function createConsumeInitializerField(consume: ts.PropertyDeclaration): ts.PropertyAssignment {
    return ts.factory.createPropertyAssignment(
        backingFieldName(consume.name as ts.Identifier),
        consumeVariableName(consume)
    )
}

export function filterDecoratedProperties(members: ts.NodeArray<ts.ClassElement>, decoratorName: string): ts.PropertyDeclaration[] {
    return members.filter(property => ts.isPropertyDeclaration(property) && hasDecorator(property, decoratorName)) as ts.PropertyDeclaration[]
}

export function filterLinks(members: ts.NodeArray<ts.ClassElement>): ts.PropertyDeclaration[] {
    return members.filter(it =>
        ts.isPropertyDeclaration(it) && isLink(it)
    ) as ts.PropertyDeclaration[]
}

export function filterProps(members: ts.NodeArray<ts.ClassElement>): ts.PropertyDeclaration[] {
    return members.filter(it =>
        ts.isPropertyDeclaration(it) && isProp(it)
    ) as ts.PropertyDeclaration[]
}

export function filterObjectLinks(members: ts.NodeArray<ts.ClassElement>): ts.PropertyDeclaration[] {
    return members.filter(it =>
        ts.isPropertyDeclaration(it) && isObjectLink(it)
    ) as ts.PropertyDeclaration[]
}

export function filterConsumes(members: ts.NodeArray<ts.ClassElement>): ts.PropertyDeclaration[] {
    return members.filter(it =>
        ts.isPropertyDeclaration(it) && isConsume(it)
    ) as ts.PropertyDeclaration[]
}

export function filterProvides(members: ts.NodeArray<ts.ClassElement>): ts.PropertyDeclaration[] {
    return members.filter(it =>
        ts.isPropertyDeclaration(it) && isProvide(it)
    ) as ts.PropertyDeclaration[]
}

/** @returns a nullable accessor: `expression?.name` */
export function createNullableAccessor(expression: ts.Expression, name: string): ts.Expression {
    return ts.factory.createPropertyAccessChain(expression, ts.factory.createToken(ts.SyntaxKind.QuestionDotToken), name)
}

/** @returns a not-null accessor: `expression!.name!` */
export function createNotNullAccessor(expression: ts.Expression, name: string): ts.Expression {
    return ts.factory.createNonNullExpression(ts.factory.createPropertyAccessExpression(ts.factory.createNonNullExpression(expression), name))
}

/** @returns a multiline block with the given statements */
export function createBlock(...statements: ts.Statement[]): ts.Block {
    return ts.factory.createBlock(statements, true)
}

/** @returns a nullish coalescing expression with safe right part: `left ?? (right)` */
export function createNullishCoalescing(left: ts.Expression, right: ts.Expression): ts.Expression {
    return ts.factory.createBinaryExpression(left, ts.factory.createToken(ts.SyntaxKind.QuestionQuestionToken), ts.factory.createParenthesizedExpression(right))
}

export function createValueAccessor(expression: ts.Expression): ts.Expression {
    return ts.factory.createPropertyAccessExpression(expression, "value")
}

export function filterDefined<T>(value: (T | undefined)[]): T[] {
    return value.filter((it: T | undefined): it is T => it != undefined)
}

export function collect<T>(...value: (ReadonlyArray<T> | T | undefined)[]): T[] {
    const empty: (T | undefined)[] = []
    return filterDefined(empty.concat(...value))
}

export function initializers() {
    return id(RewriteNames.Initializers)
}

export function isDefined<T>(value: T | undefined | null): value is T {
    return value !== undefined && value !== null
}

export function extendsLikeFunctionName(propertyName: string, componentName: string): string {
    return propertyName + "__" + componentName
}

export function hasLocalDeclaration(typechecker: ts.TypeChecker, node: ts.Identifier): boolean {
    const declarations = getDeclarationsByNode(typechecker, node)
    return (declarations.length == 1 && declarations[0].getSourceFile() == node.getSourceFile())
}

export function isBuiltinComponentName(ctx: ts.TransformationContext, name: string) {
    return ctx.getCompilerOptions().ets?.components.includes(name)
}

export function voidLambdaType() {
    return ts.factory.createFunctionTypeNode(
        undefined,
        [],
        Void()
    )
}

export function assertUnreachable(...args: never): never {
    throw new Error(`never`)
}

export function throwError(message: string): never {
    throw new Error(message)
}

// Produce a name outside of user space
export function mangle(value: string): string {
    return `__${value}`
}

export function buildBuilderArgument(): string {
    return mangle("builder")
}

export function commonMethodComponentId(importer: Importer): ts.Identifier {
    return id(importer.withAdaptorImport(ArkCommonMethodComponent))
}

export function commonMethodComponentType(importer: Importer): ts.TypeReferenceNode {
    return ts.factory.createTypeReferenceNode(importer.withAdaptorImport(ArkCommonMethodComponent))
}

export function getSingleExpression(block?: ts.Block): ts.Expression | undefined {
    const statement = getSingleStatement(block)
    return statement && ts.isExpressionStatement(statement) ? statement.expression:undefined
}

export function getSingleStatement(block?: ts.Block): ts.Statement | undefined {
    return block && block.statements.length === 1 ? block.statements[0] : undefined
}
