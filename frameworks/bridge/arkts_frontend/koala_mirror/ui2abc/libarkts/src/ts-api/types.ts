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

import * as ts from "@koalaui/ets-tsc"
import * as arkts from "../arkts-api"

import { throwError } from "../utils"
import {
    passModifiers,
    emptyImplementation,
    unpackModifiers,
    unpackNode,
    unpackNodeArray,
    unpackVariableDeclarationKind,
} from "./utilities/private"
import { SyntaxKind } from "./static/enums"

// Improve: write implementation
export interface TransformationContext {}

// Improve: write implementation
export interface Program {}

// Improve: remove U type param
export type NodeArray<T extends Node<U>, U extends arkts.AstNode | undefined = arkts.AstNode | undefined> = ts.NodeArray<T>

export abstract class Node<T extends arkts.AstNode | undefined = arkts.AstNode | undefined> implements ts.Node {
    constructor(node: T) {
        this.node = node
    }

    readonly node: T

    // Improve: remove any
    get parent(): any {
        if (this.node === undefined) {
            throwError('trying to get parent of undefined _node')
        }
        return unpackNode(this.node.parent)
    }

    set parent(node: Node) {
        if (this.node === undefined) {
            throwError('trying to set parent of undefined')
        }
        if (node.node === undefined) {
            throwError('trying to set parent to undefined')
        }
        this.node.parent = node.node
    }

    set modifiers(flags: readonly Modifier[] | undefined) {
        if (this.node === undefined) {
            throwError('trying to set modifiers of undefined')
        }
        this.node.modifiers = passModifiers(flags)
    }

    get modifiers(): NodeArray<Modifier> {
        return unpackModifiers(this.node?.modifiers)
    }

    abstract kind: SyntaxKind

    // Improve:
    forEachChild<T>(cbNode: (node: ts.Node) => T | undefined, cbNodeArray?: ((nodes: ts.NodeArray<ts.Node>) => T | undefined) | undefined): T | undefined { throw new Error("Method not implemented.") }
    getSourceFile(): ts.SourceFile { throw new Error("Method not implemented.") }
    getChildCount(sourceFile?: ts.SourceFile | undefined): number { throw new Error("Method not implemented.") }
    getChildAt(index: number, sourceFile?: ts.SourceFile | undefined): ts.Node { throw new Error("Method not implemented.") }
    getChildren(sourceFile?: ts.SourceFile | undefined): ts.Node[] { throw new Error("Method not implemented.") }

    getStart(sourceFile?: ts.SourceFile | undefined, includeJsDocComment?: boolean | undefined): number { throw new Error("Method not implemented.") }
    getFullStart(): number { throw new Error("Method not implemented.") }
    getEnd(): number { throw new Error("Method not implemented.") }
    getWidth(sourceFile?: ts.SourceFileLike | undefined): number { throw new Error("Method not implemented.") }
    getFullWidth(): number { throw new Error("Method not implemented.") }
    getLeadingTriviaWidth(sourceFile?: ts.SourceFile | undefined): number { throw new Error("Method not implemented.") }
    getFullText(sourceFile?: ts.SourceFile | undefined): string { throw new Error("Method not implemented.") }
    getText(sourceFile?: ts.SourceFile | undefined): string { throw new Error("Method not implemented.") }
    getFirstToken(sourceFile?: ts.SourceFile | undefined): ts.Node | undefined { throw new Error("Method not implemented.") }
    getLastToken(sourceFile?: ts.SourceFile | undefined): ts.Node | undefined { throw new Error("Method not implemented.") }

    get symbol(): ts.Symbol { return emptyImplementation() }
    get flags(): ts.NodeFlags { return emptyImplementation() }
    get pos(): number { return emptyImplementation() }
    get end(): number { return emptyImplementation() }
}

// Improve: add all tokens
export type BinaryOperator =
    | ts.SyntaxKind.PlusToken
    | ts.SyntaxKind.MinusToken

    | ts.SyntaxKind.AsteriskToken

export type BinaryOperatorToken = Token<BinaryOperator>;

// Improve: rethink maybe (temporary solution)
export class Token<TKind extends ts.TokenSyntaxKind> extends Node<undefined> {
    constructor(kind: TKind) {
        super(undefined)
        this.kind = kind
    }

    readonly kind: TKind;
}

export type ModifierSyntaxKind =
    // | SyntaxKind.ConstructorKeyword
    | SyntaxKind.AbstractKeyword
    | SyntaxKind.AccessorKeyword
    | SyntaxKind.AsyncKeyword
    | SyntaxKind.ConstKeyword
    | SyntaxKind.DeclareKeyword
    | SyntaxKind.DefaultKeyword
    | SyntaxKind.ExportKeyword
    | SyntaxKind.InKeyword
    | SyntaxKind.PrivateKeyword
    | SyntaxKind.ProtectedKeyword
    | SyntaxKind.PublicKeyword
    | SyntaxKind.ReadonlyKeyword
    | SyntaxKind.OutKeyword
    | SyntaxKind.OverrideKeyword
    | SyntaxKind.StaticKeyword;

export class Modifier extends Node<undefined> {
    constructor(kind: ModifierSyntaxKind) {
        super(undefined)
        this.kind = kind
    }

    public toString(): string {
        return `${this.kind}`
    }

    kind: ModifierSyntaxKind
}

export abstract class Expression extends Node<arkts.AstNode> implements ts.Expression {
    // Improve: support minimal interface
    _expressionBrand: any
}

export class FunctionDeclaration extends Node<arkts.FunctionDeclaration> implements ts.FunctionDeclaration, FunctionLikeDeclarationBase {
    constructor(node: arkts.FunctionDeclaration) {
        super(node)
        this.name = unpackNode(node.name)
        this.body = unpackNode(node.body)
        this.typeParameters = unpackNodeArray(node.typeParamsDecl?.parameters)
        this.type = unpackNode(node.returnType)
        this.parameters = unpackNodeArray(node.parameters)
    }

    readonly name?: Identifier | undefined
    readonly body?: Block | undefined
    readonly typeParameters?: NodeArray<TypeParameterDeclaration> | undefined
    readonly type?: TypeNode | undefined
    readonly parameters: NodeArray<ParameterDeclaration>
    readonly kind: ts.SyntaxKind.FunctionDeclaration = ts.SyntaxKind.FunctionDeclaration

    // brands
    _functionLikeDeclarationBrand: any
    _declarationBrand: any
    _statementBrand: any
}

export class FunctionExpression extends Node<arkts.FunctionExpression> implements ts.FunctionExpression, FunctionLikeDeclarationBase {
    constructor(node: arkts.FunctionExpression) {
        super(node)
        this.name = unpackNode(node.scriptFunction.ident)
        if (node.scriptFunction.body === undefined) {
            throwError('body expected to be not undefined')
        }
        this.body = unpackNode(node.scriptFunction.body)
        this.parameters = unpackNodeArray(node.scriptFunction.parameters)
    }

    readonly name?: Identifier
    readonly body: Block
    readonly parameters: NodeArray<ParameterDeclaration>
    readonly kind: ts.SyntaxKind.FunctionExpression = ts.SyntaxKind.FunctionExpression

    // brands
    _primaryExpressionBrand: any
    _memberExpressionBrand: any
    _leftHandSideExpressionBrand: any
    _updateExpressionBrand: any
    _unaryExpressionBrand: any
    _expressionBrand: any
    _functionLikeDeclarationBrand: any
    _declarationBrand: any
}

export class Identifier extends Node<arkts.Identifier> implements ts.Identifier, Expression {
    constructor(node: arkts.Identifier) {
        super(node)
        this.text = node.name
    }

    readonly text: string
    readonly kind: ts.SyntaxKind.Identifier = ts.SyntaxKind.Identifier

    // Improve:
    get escapedText(): ts.__String { return emptyImplementation() }

    // brands
    _primaryExpressionBrand: any
    _memberExpressionBrand: any
    _leftHandSideExpressionBrand: any
    _updateExpressionBrand: any
    _unaryExpressionBrand: any
    _expressionBrand: any
    _declarationBrand: any
}

export class PrivateIdentifier extends Node<arkts.Identifier> implements ts.PrivateIdentifier, Expression {
    constructor(node: arkts.Identifier) {
        super(node)
        this.text = node.name
        if (!node.isPrivate) {
            throwError('identifier expected to be private')
        }
    }

    readonly text: string
    readonly kind: ts.SyntaxKind.PrivateIdentifier = ts.SyntaxKind.PrivateIdentifier

    // Improve:
    get escapedText(): ts.__String { return emptyImplementation() }

    // brands
    _primaryExpressionBrand: any
    _memberExpressionBrand: any
    _leftHandSideExpressionBrand: any
    _updateExpressionBrand: any
    _unaryExpressionBrand: any
    _expressionBrand: any
    _declarationBrand: any
}

export abstract class Statement extends Node<arkts.AstNode> implements ts.Statement {
    // brands
    _statementBrand: any
}

export class Block extends Node<arkts.BlockStatement> implements ts.Block {
    constructor(node: arkts.BlockStatement) {
        super(node)
        this.statements = unpackNodeArray(node.statements)
    }

    readonly statements: NodeArray<Statement>
    readonly kind: ts.SyntaxKind.Block = ts.SyntaxKind.Block

    // brands
    _statementBrand: any
}

export class SourceFile extends Node<arkts.EtsScript> implements ts.SourceFile {
    constructor(node: arkts.EtsScript) {
        super(node)

        this.statements = unpackNodeArray(this.node.statements)
    }

    readonly statements: NodeArray<Statement>
    readonly kind: ts.SyntaxKind.SourceFile = ts.SyntaxKind.SourceFile

    // Improve:
    getLineAndCharacterOfPosition(pos: number): ts.LineAndCharacter { throw new Error("Method not implemented.") }
    getLineEndOfPosition(pos: number): number { throw new Error("Method not implemented.") }
    getLineStarts(): readonly number[] { throw new Error("Method not implemented.") }
    getPositionOfLineAndCharacter(line: number, character: number): number { throw new Error("Method not implemented.") }
    update(newText: string, textChangeRange: ts.TextChangeRange): ts.SourceFile { throw new Error("Method not implemented.") }
    get endOfFileToken(): ts.Token<ts.SyntaxKind.EndOfFileToken> { return emptyImplementation() }
    get fileName(): string { return emptyImplementation() }
    get text() { return emptyImplementation() }
    get amdDependencies(): readonly ts.AmdDependency[] { return emptyImplementation() }
    get referencedFiles(): readonly ts.FileReference[] { return emptyImplementation() }
    get typeReferenceDirectives(): readonly ts.FileReference[] { return emptyImplementation() }
    get libReferenceDirectives(): readonly ts.FileReference[] { return emptyImplementation() }
    get languageVariant(): ts.LanguageVariant { return emptyImplementation() }
    get isDeclarationFile(): boolean { return emptyImplementation() }
    get hasNoDefaultLib(): boolean { return emptyImplementation() }
    get languageVersion(): ts.ScriptTarget { return emptyImplementation() }

    // brands
    _declarationBrand: any
}

export abstract class LeftHandSideExpression extends Node<arkts.AstNode> implements ts.LeftHandSideExpression, Expression {
    // brands
    _leftHandSideExpressionBrand: any
    _updateExpressionBrand: any
    _unaryExpressionBrand: any
    _expressionBrand: any
}

export class ExpressionStatement extends Node<arkts.ExpressionStatement> implements ts.ExpressionStatement, Statement {
    constructor(node: arkts.ExpressionStatement) {
        super(node)
        this.expression = unpackNode(this.node.expression)
    }

    readonly expression: Expression
    readonly kind: ts.SyntaxKind.ExpressionStatement = ts.SyntaxKind.ExpressionStatement

    // brands
    _statementBrand: any
}

export class CallExpression extends Node<arkts.CallExpression> implements ts.CallExpression, LeftHandSideExpression {
    constructor(node: arkts.CallExpression) {
        super(node)
        this.expression = unpackNode(node.expression)
        this.arguments = unpackNodeArray(node.arguments)
    }

    readonly expression: LeftHandSideExpression
    readonly arguments: NodeArray<Expression>
    readonly kind: ts.SyntaxKind.CallExpression = ts.SyntaxKind.CallExpression

    // brands
    _leftHandSideExpressionBrand: any
    _updateExpressionBrand: any
    _unaryExpressionBrand: any
    _expressionBrand: any
    _declarationBrand: any
}

export class PropertyAccessExpression extends Node<arkts.MemberExpression> implements ts.PropertyAccessExpression, Expression {
    constructor(node: arkts.MemberExpression) {
        super(node)
        this.expression = unpackNode(node.object)
        this.name = unpackNode(node.property)
    }

    readonly expression: LeftHandSideExpression
    readonly name: Identifier
    readonly kind: ts.SyntaxKind.PropertyAccessExpression = ts.SyntaxKind.PropertyAccessExpression

    // brands
    _memberExpressionBrand: any
    _leftHandSideExpressionBrand: any
    _updateExpressionBrand: any
    _unaryExpressionBrand: any
    _expressionBrand: any
    _declarationBrand: any
}

export class StringLiteral extends Node<arkts.StringLiteral> implements ts.StringLiteral {
    constructor(node: arkts.StringLiteral) {
        super(node)

        this.text = node.str
    }

    readonly text: string
    readonly kind: ts.SyntaxKind.StringLiteral = ts.SyntaxKind.StringLiteral

    // brands
    _literalExpressionBrand: any
    _primaryExpressionBrand: any
    _memberExpressionBrand: any
    _leftHandSideExpressionBrand: any
    _updateExpressionBrand: any
    _unaryExpressionBrand: any
    _expressionBrand: any
    _declarationBrand: any
}

export class ClassDeclaration extends Node<arkts.ClassDeclaration> implements ts.ClassDeclaration {
    constructor(node: arkts.ClassDeclaration) {
        super(node)
        this.name = unpackNode(node.definition.name)
        this.members = unpackNodeArray(node.definition.members)
        this.typeParameters = unpackNodeArray(node.definition.typeParamsDecl?.parameters)
    }

    readonly name: Identifier
    readonly members: NodeArray<ClassElement>
    readonly typeParameters?: NodeArray<TypeParameterDeclaration>
    readonly kind: ts.SyntaxKind.ClassDeclaration = ts.SyntaxKind.ClassDeclaration

    // brands
    _declarationBrand: any
    _statementBrand: any
}

export abstract class ClassElement extends Node<arkts.AstNode> implements ts.ClassElement {
    // brands
    _declarationBrand: any
    _classElementBrand: any
}

export type MemberName = Identifier | PrivateIdentifier;

// Improve: support
// export type PropertyName = Identifier | StringLiteral | NumericLiteral | ts.ComputedPropertyName | PrivateIdentifier;
export type PropertyName = Identifier | StringLiteral | NumericLiteral | PrivateIdentifier;

// Improve: support
export type DeclarationName =
    | PropertyName
    // | JsxAttributeName
    // | StringLiteralLike
    // | ElementAccessExpression
    // | BindingPattern
    // | EntityNameExpression;

export interface Declaration extends Node<arkts.AstNode> {}

export abstract class NamedDeclaration extends Node<arkts.AstNode> implements ts.NamedDeclaration, Declaration {
    readonly name?: DeclarationName;

    // brands
    _declarationBrand: any
}

export type SignatureDeclaration = ts.CallSignatureDeclaration | ts.ConstructSignatureDeclaration | MethodSignature | ts.IndexSignatureDeclaration | FunctionTypeNode | ts.ConstructorTypeNode | ts.JSDocFunctionType | FunctionDeclaration | MethodDeclaration | ConstructorDeclaration | ts.AccessorDeclaration | FunctionExpression | ArrowFunction;

export interface SignatureDeclarationBase extends NamedDeclaration {}

export type VariableLikeDeclaration = ts.VariableDeclaration | ParameterDeclaration | ts.BindingElement | PropertyDeclaration | ts.PropertyAssignment | PropertySignature | ts.JsxAttribute | ts.ShorthandPropertyAssignment | ts.EnumMember | ts.JSDocPropertyTag | ts.JSDocParameterTag;

export interface FunctionLikeDeclarationBase extends SignatureDeclarationBase {
    // brands
    _functionLikeDeclarationBrand: any;
}

// Improve: support
// export type FunctionLikeDeclaration = FunctionDeclaration | MethodDeclaration | ts.GetAccessorDeclaration | ts.SetAccessorDeclaration | ConstructorDeclaration | FunctionExpression | ArrowFunction;
export type FunctionLikeDeclaration = FunctionDeclaration | MethodDeclaration | ConstructorDeclaration | FunctionExpression | ArrowFunction;

export class MethodSignature extends Node<arkts.AstNode> implements ts.MethodSignature, SignatureDeclarationBase {
    constructor(node: arkts.AstNode) {
        super(node)
    }

    // readonly name: PropertyName
    // readonly parameters: NodeArray<ParameterDeclaration>
    readonly kind: ts.SyntaxKind.MethodSignature = ts.SyntaxKind.MethodSignature

    // Improve:
    name: any
    parameters: any

    // brands
    _declarationBrand: any
    _typeElementBrand: any
}

// export class MethodDeclaration extends Node implements ts.MethodDeclaration, FunctionLikeDeclarationBase, ClassElement {
export class MethodDeclaration extends Node<arkts.MethodDefinition> implements ts.MethodDeclaration, ClassElement {
    constructor(node: arkts.MethodDefinition) {
        super(node)
        this.name = unpackNode(node.name)
        this.parameters = unpackNodeArray(node.scriptFunction.parameters)
        this.body = unpackNode(node.scriptFunction.body)
    }

    // tsc: readonly name?: PropertyName
    readonly name: Identifier
    readonly parameters: NodeArray<ParameterDeclaration>
    // tsc: readonly body?: FunctionBody | undefined
    readonly body?: Block | undefined
    readonly kind: ts.SyntaxKind.MethodDeclaration = ts.SyntaxKind.MethodDeclaration

    // brands
    _functionLikeDeclarationBrand: any
    _classElementBrand: any
    _objectLiteralBrand: any
    _declarationBrand: any
}

// export class ConstructorDeclaration extends Node<arkts.MethodDefinition> implements ts.ConstructorDeclaration, FunctionLikeDeclarationBase, ClassElement {
export class ConstructorDeclaration extends Node<arkts.MethodDefinition> implements ts.ConstructorDeclaration, ClassElement {
    constructor(node: arkts.MethodDefinition) {
        super(node)
        this.name = unpackNode(node.name)
        this.parameters = unpackNodeArray(node.scriptFunction.parameters)
        this.body = unpackNode(node.scriptFunction.body)
    }

    // ts: readonly name?: PropertyName
    readonly name: Identifier
    readonly parameters: NodeArray<ParameterDeclaration>
    // ts: readonly body?: FunctionBody | undefined
    readonly body?: Block
    readonly kind: ts.SyntaxKind.Constructor = ts.SyntaxKind.Constructor

    // brands
    _functionLikeDeclarationBrand: any
    _classElementBrand: any
    _objectLiteralBrand: any
    _declarationBrand: any
}

// Improve: specify arkts.AstNode type
export class PropertySignature extends Node<arkts.AstNode> implements ts.TypeElement {
    constructor(node: arkts.AstNode) {
        super(node)
    }

    readonly name?: PropertyName
    readonly kind: ts.SyntaxKind.PropertySignature = ts.SyntaxKind.PropertySignature

    // brands
    _typeElementBrand: any
    _declarationBrand: any
}

// Improve: specify arkts.AstNode type
export class PropertyDeclaration extends Node<arkts.AstNode> implements ts.PropertyDeclaration, ClassElement {
    constructor(node: arkts.AstNode) {
        super(node)
    }

    readonly kind: ts.SyntaxKind.PropertyDeclaration = ts.SyntaxKind.PropertyDeclaration

    // Improve:
    name: any

    // brands
    _classElementBrand: any
    _declarationBrand: any
}

// Improve: specify arkts.AstNode type
export class GetAccessorDeclaration extends Node<arkts.AstNode> implements ts.GetAccessorDeclaration, FunctionLikeDeclarationBase, ClassElement {
    constructor(node: arkts.AstNode) {
        super(node)
    }

    // readonly name: PropertyName
    // readonly parameters: NodeArray<ParameterDeclaration>
    readonly kind: ts.SyntaxKind.GetAccessor = ts.SyntaxKind.GetAccessor

    // Improve:
    name: any
    parameters: any

    // brands
    _functionLikeDeclarationBrand: any
    _declarationBrand: any
    _classElementBrand: any
    _typeElementBrand: any
    _objectLiteralBrand: any
}

// Improve: specify arkts.AstNode type
export class SetAccessorDeclaration extends Node<arkts.AstNode> implements ts.SetAccessorDeclaration, FunctionLikeDeclarationBase, ClassElement {
    constructor(node: arkts.AstNode) {
        super(node)
    }

    // readonly name: PropertyName
    // readonly parameters: NodeArray<ParameterDeclaration>
    readonly kind: ts.SyntaxKind.SetAccessor = ts.SyntaxKind.SetAccessor

    // Improve:
    name: any
    parameters: any

    // brands
    _functionLikeDeclarationBrand: any
    _declarationBrand: any
    _classElementBrand: any
    _typeElementBrand: any
    _objectLiteralBrand: any
}

export class ParameterDeclaration extends Node<arkts.ETSParameterExpression> implements ts.ParameterDeclaration, NamedDeclaration {
    constructor(node: arkts.ETSParameterExpression) {
        super(node)
    }

    readonly kind: ts.SyntaxKind.Parameter = ts.SyntaxKind.Parameter

    // Improve:
    name: any

    // brands
    _declarationBrand: any
}

export type BindingName = Identifier | ts.BindingPattern;

export class VariableStatement extends Node<arkts.VariableDeclaration> implements ts.VariableStatement {
    constructor(node: arkts.VariableDeclaration) {
        super(node)
        this.declarationList = new VariableDeclarationList(node)
    }

    readonly declarationList: VariableDeclarationList
    readonly kind: ts.SyntaxKind.VariableStatement = ts.SyntaxKind.VariableStatement

    // brands
    _statementBrand: any
}

export class VariableDeclarationList extends Node<arkts.VariableDeclaration> implements ts.VariableDeclarationList {
    constructor(node: arkts.VariableDeclaration) {
        super(node)
        this.declarations = unpackNodeArray(node.declarators)
    }

    readonly declarations: NodeArray<VariableDeclaration>
    get flags(): ts.NodeFlags { return unpackVariableDeclarationKind(this.node.declarationKind) }
    readonly kind: ts.SyntaxKind.VariableDeclarationList = ts.SyntaxKind.VariableDeclarationList
}

export class VariableDeclaration extends Node<arkts.VariableDeclarator> implements ts.VariableDeclaration, NamedDeclaration {
    constructor(node: arkts.VariableDeclarator) {
        super(node)
        this.name = unpackNode(node.name)
    }

    readonly name: Identifier
    readonly kind: ts.SyntaxKind.VariableDeclaration = ts.SyntaxKind.VariableDeclaration

    // brands
    _declarationBrand: any
}

export class TypeParameterDeclaration extends Node<arkts.TSTypeParameter> implements ts.TypeParameterDeclaration {
    constructor(node: arkts.TSTypeParameter) {
        super(node)
        this.name = unpackNode(node.name)
    }

    readonly name: Identifier
    readonly kind: ts.SyntaxKind.TypeParameter = ts.SyntaxKind.TypeParameter

    // brands
    _declarationBrand: any
}

export abstract class TypeNode extends Node<arkts.AstNode> implements ts.TypeNode {
    // brands
    _typeNodeBrand: any
}

export class KeywordTypeNode extends Node<arkts.ETSPrimitiveType | arkts.ETSTypeReference> implements ts.KeywordTypeNode, TypeNode {
    constructor(node: arkts.ETSPrimitiveType | arkts.ETSTypeReference) {
        super(node)
    }

    readonly kind: ts.KeywordTypeSyntaxKind = ts.SyntaxKind.UnknownKeyword

    // brands
    _typeNodeBrand: any
}

export class TypeReferenceNode extends Node<arkts.AstNode> implements ts.TypeReferenceNode, TypeNode {
    constructor(node: arkts.AstNode) {
        super(node)
    }

    readonly kind: ts.SyntaxKind.TypeReference = ts.SyntaxKind.TypeReference

    // Improve:
    typeName: any

    // brands
    _typeNodeBrand: any
}

export class FunctionTypeNode extends Node<arkts.AstNode> implements ts.FunctionTypeNode, TypeNode, SignatureDeclarationBase {
    constructor(node: arkts.AstNode) {
        super(node)
    }

    readonly name?: DeclarationName
    readonly kind: ts.SyntaxKind.FunctionType = ts.SyntaxKind.FunctionType

    // Improve: support minimal interface
    parameters: any
    type: any

    // brands
    _typeNodeBrand: any
    _declarationBrand: any
}

export class UnionTypeNode extends Node<arkts.ETSUnionType> implements ts.UnionTypeNode, TypeNode {
    constructor(node: arkts.ETSUnionType) {
        super(node)
        this.types = unpackNodeArray(node.types)
    }

    readonly types: NodeArray<TypeNode>
    readonly kind: ts.SyntaxKind.UnionType = ts.SyntaxKind.UnionType

    // brands
    _typeNodeBrand: any
}

export class ReturnStatement extends Node<arkts.ReturnStatement> implements ts.ReturnStatement, Statement {
    constructor(node: arkts.ReturnStatement) {
        super(node)
        this.expression = unpackNode(node.argument)
    }

    readonly expression: Expression | undefined
    readonly kind: ts.SyntaxKind.ReturnStatement = ts.SyntaxKind.ReturnStatement

    // brands
    _statementBrand: any
}

export class IfStatement extends Node<arkts.IfStatement> implements ts.IfStatement {
    constructor(node: arkts.IfStatement) {
        super(node)
    }

    readonly kind: ts.SyntaxKind.IfStatement = ts.SyntaxKind.IfStatement

    // Improve:
    thenStatement: any
    expression: any

    // brands
    _statementBrand: any
}

export class BinaryExpression extends Node<arkts.BinaryExpression> implements ts.BinaryExpression {
    constructor(node: arkts.BinaryExpression) {
        super(node)
    }

    readonly kind: ts.SyntaxKind.BinaryExpression = ts.SyntaxKind.BinaryExpression

    // Improve:
    left: any
    right: any
    operatorToken: any

    // brands
    _expressionBrand: any
    _declarationBrand: any
}

export class AssignmentExpression extends Node<arkts.AssignmentExpression> implements ts.AssignmentExpression<any> {
    constructor(node: arkts.AssignmentExpression) {
        super(node)
    }

    readonly kind: ts.SyntaxKind.BinaryExpression = ts.SyntaxKind.BinaryExpression

    // Improve:
    right: any
    left: any
    operatorToken: any

    // brands
    _expressionBrand: any
    _declarationBrand: any
}

export class ArrowFunction extends Node<arkts.ArrowFunctionExpression> implements ts.ArrowFunction {
    constructor(node: arkts.ArrowFunctionExpression) {
        super(node)
        if (node.scriptFunction.body === undefined) {
            throwError('node.scriptFunction.body not expected to be undefined')
        }
        this.body = unpackNode(node.scriptFunction.body)
        this.parameters = unpackNodeArray(node.scriptFunction.parameters)
    }

    get name(): never { return throwError(`name doesn't exist for ArrowFunction`) }
    readonly body: Block
    readonly parameters: NodeArray<ParameterDeclaration>
    readonly kind: ts.SyntaxKind.ArrowFunction = ts.SyntaxKind.ArrowFunction

    // Improve:
    equalsGreaterThanToken: any

    // brands
    _expressionBrand: any
    _functionLikeDeclarationBrand: any
    _declarationBrand: any
}

export class NumericLiteral extends Node<arkts.NumberLiteral> implements ts.NumericLiteral, Declaration {
    constructor(node: arkts.NumberLiteral) {
        super(node)

        this.text = `${node.value}`
    }

    readonly text: string
    readonly kind: ts.SyntaxKind.NumericLiteral = ts.SyntaxKind.NumericLiteral

    // brands
    _literalExpressionBrand: any
    _declarationBrand: any
    _primaryExpressionBrand: any
    _memberExpressionBrand: any
    _leftHandSideExpressionBrand: any
    _updateExpressionBrand: any
    _unaryExpressionBrand: any
    _expressionBrand: any
}

export class SuperExpression extends Node<arkts.SuperExpression> implements ts.SuperExpression {
    constructor(node: arkts.SuperExpression) {
        super(node)
    }

    readonly kind: ts.SyntaxKind.SuperKeyword = ts.SyntaxKind.SuperKeyword

    // brands
    _primaryExpressionBrand: any
    _memberExpressionBrand: any
    _leftHandSideExpressionBrand: any
    _updateExpressionBrand: any
    _unaryExpressionBrand: any
    _expressionBrand: any
}

export class HeritageClause extends Node<arkts.SuperExpression> implements ts.HeritageClause {
    constructor(node: arkts.SuperExpression) {
        super(node)
    }

    readonly kind: ts.SyntaxKind.HeritageClause = ts.SyntaxKind.HeritageClause
    // token: ts.SyntaxKind.ExtendsKeyword | ts.SyntaxKind.ImplementsKeyword
    // types: ts.NodeArray<ts.ExpressionWithTypeArguments>

    // Improve:
    token: any
    types: any
}


// Improve: there is no ParenthesizedExpression in ArkTS,
// so for temporary solution we're just gonna ignore this type of nodes
// and replace it with Expression underneath
export type ParenthesizedExpression = Expression
// export class ParenthesizedExpression extends Node<undefined> implements ts.ParenthesizedExpression {
//     constructor(expression: Expression) {
//         super(undefined)
//         this.expression = expression
//     }

//     readonly expression: Expression
//     readonly kind: ts.SyntaxKind.ParenthesizedExpression = ts.SyntaxKind.ParenthesizedExpression

//     // brands
//     _primaryExpressionBrand: any
//     _memberExpressionBrand: any
//     _leftHandSideExpressionBrand: any
//     _updateExpressionBrand: any
//     _unaryExpressionBrand: any
//     _expressionBrand: any
// }

// Improve:
export class ImportDeclaration extends Node<arkts.UnsupportedNode> implements ts.ImportDeclaration {
    constructor(node: arkts.UnsupportedNode) {
        super(node)
    }

    readonly kind: ts.SyntaxKind.ImportDeclaration = ts.SyntaxKind.ImportDeclaration

    // Improve:
    moduleSpecifier: any

    // brands
    _statementBrand: any
}

// Improve:
export class ImportClause extends Node<arkts.UnsupportedNode> implements ts.ImportClause {
    constructor(node: arkts.UnsupportedNode) {
        super(node)
    }

    readonly kind: ts.SyntaxKind.ImportClause = ts.SyntaxKind.ImportClause

    // Improve:
    isTypeOnly: any

    // brands
    _declarationBrand: any
}

// Improve:
export class NamedImports extends Node<arkts.UnsupportedNode> implements ts.NamedImports {
    constructor(node: arkts.UnsupportedNode) {
        super(node)
    }

    readonly kind: ts.SyntaxKind.NamedImports = ts.SyntaxKind.NamedImports

    // Improve:
    elements: any
}

export class ImportSpecifier extends Node<arkts.Identifier> implements ts.ImportSpecifier {
    constructor(node: arkts.Identifier) {
        super(node)
        this.name = unpackNode(this.node)
    }

    readonly name: Identifier
    readonly kind: ts.SyntaxKind.ImportSpecifier = ts.SyntaxKind.ImportSpecifier

    // Improve:
    isTypeOnly: any

    // brands
    _declarationBrand: any
}

export class UnsupportedNode extends Node<arkts.AstNode> implements ts.Node {
    constructor(node: arkts.AstNode) {
        super(node)
    }

    readonly kind: ts.SyntaxKind = SyntaxKind.Unknown
}
