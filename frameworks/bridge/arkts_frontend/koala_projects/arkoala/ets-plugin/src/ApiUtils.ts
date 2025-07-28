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
import { asString, collect, filterDecorators, throwError } from "./utils"

export function parameter(
    name: string | ts.Identifier,
    type: ts.TypeNode | undefined,
    initializer?: ts.Expression
) {
    return ts.factory.createParameterDeclaration(
        undefined,
        undefined,
        name,
        undefined,
        type,
        initializer
    )
}

export function optionalParameter(
    name: string | ts.Identifier,
    type: ts.TypeNode | undefined,
    initializer?: ts.Expression
) {
    return ts.factory.createParameterDeclaration(
        undefined,
        undefined,
        name,
        ts.factory.createToken(ts.SyntaxKind.QuestionToken),
        type,
        initializer
    )
}

export function assignment(left: ts.Expression, right: ts.Expression): ts.ExpressionStatement {
    return ts.factory.createExpressionStatement(
        ts.factory.createBinaryExpression(
            left,
            ts.factory.createToken(ts.SyntaxKind.EqualsToken),
            right
        )
    )
}

export function tripleNotEqualsUndefined(left: ts.Expression): ts.Expression {
    return ts.factory.createBinaryExpression(
        left,
        ts.factory.createToken(ts.SyntaxKind.ExclamationEqualsEqualsToken),
        undefinedValue()
    )
}

export function id(name: string): ts.Identifier {
    return ts.factory.createIdentifier(name)
}

export function Any(): ts.TypeNode {
    return ts.factory.createKeywordTypeNode(ts.SyntaxKind.AnyKeyword)
}

export function Undefined() {
    return ts.factory.createKeywordTypeNode(ts.SyntaxKind.UndefinedKeyword)
}

export function ObjectType(): ts.TypeNode {
    return ts.factory.createKeywordTypeNode(ts.SyntaxKind.ObjectKeyword)
}

export function StringType(): ts.TypeNode {
    return ts.factory.createKeywordTypeNode(ts.SyntaxKind.StringKeyword)
}

export function Void() {
    return ts.factory.createToken(ts.SyntaxKind.VoidKeyword)
}

export function Export() {
    return ts.factory.createToken(ts.SyntaxKind.ExportKeyword)
}

export function Private() {
    return ts.factory.createToken(ts.SyntaxKind.PrivateKeyword)
}

export function Exclamation() {
    return ts.factory.createToken(ts.SyntaxKind.ExclamationToken)
}

export function undefinedValue(): ts.Expression {
    return ts.factory.createIdentifier("undefined")
}

export function anyIfNoType(type: ts.TypeNode | undefined): ts.TypeNode {
    if (!type) return Any()
    return type
}


export function provideAnyTypeIfNone(parameter: ts.ParameterDeclaration): ts.ParameterDeclaration {
    return ts.factory.updateParameterDeclaration(
        parameter,
        parameter.modifiers,
        parameter.dotDotDotToken,
        parameter.name,
        parameter.questionToken,
        anyIfNoType(parameter.type),
        parameter.initializer
    )
}

export function orUndefined(type: ts.TypeNode): ts.TypeNode {
    return ts.factory.createUnionTypeNode([
        type,
        Undefined()
    ])
}

export function isKnownIdentifier(name: ts.Node | undefined, value: string): boolean {
    return (name != undefined) &&
        (ts.isIdentifier(name) || ts.isPrivateIdentifier(name)) &&
        ts.idText(name) == value
}

export function isUndefined(node: ts.Expression): boolean {
    return node.kind == ts.SyntaxKind.UndefinedKeyword ||
        ts.isIdentifier(node) && ts.idText(node) == "undefined"
}

export function prependComment<T extends ts.Node>(node: T, comment: string): T {
    return ts.addSyntheticLeadingComment(node, ts.SyntaxKind.MultiLineCommentTrivia, comment, true);
}

export function isDecorator(modifierLike: ts.ModifierLike, name: string): boolean {
    if (!ts.isDecorator(modifierLike)) {
        return false
    }
    return isKnownIdentifier(modifierLike.expression, name) || isCallDecorator(modifierLike, name)
}

export function isCallDecorator(decorator: ts.Decorator, name: string): boolean {
    return ts.isCallExpression(decorator.expression) && isKnownIdentifier(decorator.expression.expression, name)
}

export function hasDecorator(node: ts.Node, name: string): boolean {
    return getDecorator(node, name) != undefined
}

export function getDecorator(node: ts.Node, name: string): ts.Decorator | undefined {
    return filterDecorators(node)?.find(it => isDecorator(it, name))
}

export function findDecoratorArguments(
    decorators: ReadonlyArray<ts.Decorator> | undefined,
    name: string,
    nth: number
): ReadonlyArray<ts.Expression> | undefined {
    return decorators
        ?.filter(it => isCallDecorator(it, name))
        ?.map(it => (it.expression as ts.CallExpression).arguments[nth])
}

export function findDecoratorLiterals(
    decorators: ReadonlyArray<ts.Decorator> | undefined,
    name: string,
    nth: number,
): ReadonlyArray<string> | undefined {
    return findDecoratorArguments(decorators, name, nth)?.map(it => (it as ts.StringLiteral).text)
}

export function findDecoratorArgument(
    decorators: ReadonlyArray<ts.Decorator> | undefined,
    name: string,
    nth: number,
): ts.Expression {
    const args = findDecoratorArguments(decorators, name, nth)
    if (args?.length === 1) return args[0]
    throw new Error(name + " must have only one argument, but got " + args?.length)
}

export function createThisFieldAccess(name: string | ts.Identifier | ts.PrivateIdentifier): ts.Expression {
    return ts.factory.createPropertyAccessExpression(
        ts.factory.createThis(),
        name
    )
}

export function bindThis(expression: ts.Expression): ts.Expression {
    return ts.factory.createCallExpression(
        ts.factory.createPropertyAccessExpression(
            expression,
            "bind"
        ),
        undefined,
        [ts.factory.createThis()]
    )

}

export function getLineNumber(sourceFile: ts.SourceFile, position: number): number {
    return ts.getLineAndCharacterOfPosition(sourceFile, position).line + 1 // First line is 1.
}

export function getDeclarationsByNode(typechecker: ts.TypeChecker, node: ts.Node): ts.Declaration[] {
    const symbol = typechecker.getSymbolAtLocation(node)
    const declarations = symbol?.getDeclarations() ?? []
    return declarations
}

export function dropModifier(modifierLikes: ts.ModifierLike[] | undefined, kind: ts.SyntaxKind): ts.ModifierLike[] | undefined {
    return modifierLikes?.filter(it => it.kind != kind)
}

export function dropModifiers(modifierLikes: ts.ModifierLike[] | undefined, ...kinds: ts.SyntaxKind[]): ts.ModifierLike[] | undefined {
    return modifierLikes?.filter(it => kinds.every(kind => it.kind != kind))
}

export function dropReadonly(modifierLikes: ts.ModifierLike[] | undefined): ts.ModifierLike[] | undefined {
    return dropModifier(modifierLikes, ts.SyntaxKind.ReadonlyKeyword)
}

export function dropPublic(modifierLikes: ts.ModifierLike[] | undefined): ts.ModifierLike[] | undefined {
    return dropModifier(modifierLikes, ts.SyntaxKind.PublicKeyword)
}

export function dropPrivate(modifierLikes: ts.ModifierLike[] | undefined): ts.ModifierLike[] | undefined {
    return dropModifier(modifierLikes, ts.SyntaxKind.PrivateKeyword)
}

export function makePrivate(modifierLikes: ts.ModifierLike[] | undefined): ts.ModifierLike[] | undefined {
    return collect(Private(), dropModifiers(modifierLikes, ts.SyntaxKind.PublicKeyword, ts.SyntaxKind.PrivateKeyword, ts.SyntaxKind.ProtectedKeyword))
}

export function isStatic(node: ts.Node): boolean {
    if (!ts.canHaveModifiers(node)) return false
    const modifierLikes = ts.getModifiers(node)
    return !!(modifierLikes?.find(it =>
        it.kind == ts.SyntaxKind.StaticKeyword)
    )
}

export function sourceStructName(node: ts.StructDeclaration) {
    return node.name ?? throwError(`Nameless struct`)
}

export function asIdentifier(node: ts.Node): ts.Identifier {
    if (ts.isIdentifier(node)) return node
    throwError(`Expected ts.Identifier, got ${asString(node)}`)
}

export function findObjectPropertyValue(arg: ts.ObjectLiteralExpression, name: string): ts.Expression|undefined {
    const property =  arg.properties
        .filter(it => ts.isPropertyAssignment(it))
        .find(it => it.name?.getText() == name) as ts.PropertyAssignment|undefined
    return property?.initializer
}