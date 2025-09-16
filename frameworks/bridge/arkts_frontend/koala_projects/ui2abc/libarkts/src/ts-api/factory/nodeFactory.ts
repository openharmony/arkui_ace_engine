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

import { throwError } from "../../utils"
import * as ts from "@koalaui/ets-tsc"
import * as arkts from "../../arkts-api"

import {
    passNode,
    passNodeArray,
    passToken,
    passModifiersToScriptFunction,
    passModifiers,
    passIdentifier,
    passTypeParams,
    passVariableDeclarationKind,
} from "../utilities/private"
import {
    SyntaxKind,
    NodeFlags,
} from "../static/enums"
import {
    Es2pandaContextState,
    Es2pandaPrimitiveType,
    Es2pandaMethodDefinitionKind,
    Es2pandaModifierFlags,
    Es2pandaScriptFunctionFlags,
    Es2pandaMemberExpressionKind,
    Es2pandaClassDefinitionModifiers,
    Es2pandaVariableDeclarationKind,
    Es2pandaVariableDeclaratorFlag,
} from "../../arkts-api"
import {
    // ts types:
    Modifier,
    BinaryOperatorToken,

    Node,
    Token,
    Identifier,
    StringLiteral,
    FunctionDeclaration,
    Block,
    KeywordTypeNode,
    PropertyAccessExpression,
    ParameterDeclaration,
    ReturnStatement,
    IfStatement,
    ExpressionStatement,
    CallExpression,
    ArrowFunction,
    TypeReferenceNode,
    BinaryExpression,
    FunctionTypeNode,
    TypeNode,
    Expression,
    Statement,
    SourceFile,
    ClassElement,
    MethodDeclaration,
    ConstructorDeclaration,
    TypeParameterDeclaration,
    NumericLiteral,
    ClassDeclaration,
    VariableDeclaration,
    VariableDeclarationList,
    VariableStatement,
    UnionTypeNode,
    SuperExpression,
    ParenthesizedExpression,
    ImportDeclaration,
    ImportClause,
    ImportSpecifier,
} from "../types"

// TODO: add flags and base
export function createNodeFactory() {
    return {
        createSourceFile,
        updateSourceFile,
        createIdentifier,
        createStringLiteral,
        createNumericLiteral,
        createFunctionDeclaration,
        updateFunctionDeclaration,
        createParameterDeclaration,
        updateParameterDeclaration,
        createETSTypeReferenceNode,
        updateTypeReferenceNode,
        createKeywordTypeNode,
        createBlock,
        updateBlock,
        createExpressionStatement,
        updateExpressionStatement,
        createReturnStatement,
        updateReturnStatement,
        createPropertyAccessExpression,
        updatePropertyAccessExpression,
        createCallExpression,
        updateCallExpression,
        createIfStatement,
        updateIfStatement,
        createToken,
        createBinaryExpression,
        updateBinaryExpression,
        createArrowFunction,
        updateArrowFunction,
        createFunctionTypeNode,
        updateFunctionTypeNode,
        createMethodDeclaration,
        updateMethodDeclaration,
        createConstructorDeclaration,
        updateConstructorDeclaration,
        createTypeParameterDeclaration,
        updateTypeParameterDeclaration,
        createClassDeclaration,
        updateClassDeclaration,
        createVariableDeclarationList,
        updateVariableDeclarationList,
        createVariableStatement,
        updateVariableStatement,
        createVariableDeclaration,
        updateVariableDeclaration,
        createETSUnionTypeNode,
        updateETSUnionTypeNode,
        createSuper,
        updateSuper,
        createParenthesizedExpression,
        updateParenthesizedExpression,
        // createImportDeclaration,
        createImportSpecifier,
    }

    // @api
    // function createSourceFile(
    //     statements: readonly Statement[],
    //     endOfFileToken: EndOfFileToken,
    //     flags: NodeFlags,
    // ): SourceFile;
    function createSourceFile(source: string, state: Es2pandaContextState = Es2pandaContextState.ES2PANDA_STATE_PARSED): SourceFile {
        const node = arkts.EtsScript.createFromSource(source, state)
        return new SourceFile(node)
    }

    // TODO: fix (now doesn't create a new node)
    // @api
    // updateSourceFile(
    //     node: SourceFile,
    //     statements: readonly Statement[],
    //     isDeclarationFile?: boolean,
    //     referencedFiles?: readonly FileReference[],
    //     typeReferences?: readonly FileReference[],
    //     hasNoDefaultLib?: boolean,
    //     libReferences?: readonly FileReference[]
    // ): SourceFile;
    function updateSourceFile(
        node: SourceFile,
        statements: readonly Statement[]
    ): SourceFile {
        return new SourceFile(
            arkts.EtsScript.updateByStatements(
                node.node,
                passNodeArray(statements)
            )
        )
    }

    // @api
    // createIdentifier(
    //     text: string
    // ): Identifier;
    function createIdentifier(
        text: string,
        typeAnnotation?: TypeNode | undefined
    ): Identifier {
        return new Identifier(
            arkts.factory.createIdentifier(
                text,
                passNode(typeAnnotation)
            )
        )
    }

    // @api
    // createStringLiteral(
    //     text: string,
    //     isSingleQuote?: boolean
    // ): StringLiteral;
    function createStringLiteral(
        str: string
    ): StringLiteral {
        return new StringLiteral(
            arkts.factory.createStringLiteral(
                str
            )
        )
    }

    // @api
    // createNumericLiteral(
    //     value: string | number,
    //     numericLiteralFlags: TokenFlags = TokenFlags.None
    // ): NumericLiteral {
    function createNumericLiteral(
        value: number
    ): NumericLiteral {
        return new NumericLiteral(
            arkts.factory.createNumberLiteral(
                value
            )
        )
    }

    // @api
    // createVariableDeclarationList(
    //     declarations: readonly VariableDeclaration[],
    //     flags = NodeFlags.None
    // ): VariableDeclarationList
    function createVariableDeclarationList(
        declarations: readonly VariableDeclaration[],
        flags: NodeFlags = NodeFlags.None
    ): VariableDeclarationList {
        return new VariableDeclarationList(
            arkts.factory.createVariableDeclaration(
                passModifiers([]),
                passVariableDeclarationKind(flags),
                passNodeArray(declarations)
            )
        )
    }

    // @api
    // updateVariableDeclarationList(
    //     node: VariableDeclarationList,
    //     declarations: readonly VariableDeclaration[]
    // ): VariableDeclarationList
    function updateVariableDeclarationList(
        node: VariableDeclarationList,
        declarations: readonly VariableDeclaration[]
    ): VariableDeclarationList {
        return new VariableDeclarationList(
            arkts.factory.updateVariableDeclaration(
                node.node,
                passModifiers([]),
                passVariableDeclarationKind(node.flags),
                passNodeArray(declarations)
            )
        )
    }

    // @api
    // createVariableStatement(
    //     modifiers: readonly ModifierLike[] | undefined,
    //     declarationList: VariableDeclarationList | readonly VariableDeclaration[]
    // ): VariableStatement
    function createVariableStatement(
        modifiers: readonly Modifier[] | undefined,
        declarationList: VariableDeclarationList | readonly VariableDeclaration[]
    ): VariableStatement {
        const node: arkts.VariableDeclaration = (declarationList instanceof VariableDeclarationList) ? declarationList.node : createVariableDeclarationList(declarationList, undefined).node
        return new VariableStatement(
            arkts.factory.createVariableDeclaration(
                passModifiers(modifiers),
                node.declarationKind,
                node.declarators
            )
        )
    }

    // @api
    // updateVariableStatement(
    //     node: VariableStatement,
    //     modifiers: readonly ModifierLike[] | undefined,
    //     declarationList: VariableDeclarationList
    // ): VariableStatement
    function updateVariableStatement(
        node: VariableStatement,
        modifiers: readonly Modifier[] | undefined,
        declarationList: VariableDeclarationList
    ): VariableStatement {
        return new VariableStatement(
            arkts.factory.updateVariableDeclaration(
                node.node,
                passModifiers(modifiers),
                declarationList.node.declarationKind,
                declarationList.node.declarators
            )
        )
    }

    // @api
    // createVariableDeclaration(
    //     name: string | BindingName,
    //     exclamationToken: ExclamationToken | undefined,
    //     type: TypeNode | undefined,
    //     initializer: Expression | undefined
    // ): VariableDeclaration
    function createVariableDeclaration(
        name: string | Identifier,
        exclamationToken: undefined,
        type: TypeNode | undefined,
        initializer: Expression | undefined
    ): VariableDeclaration {
        return new VariableDeclaration(
            arkts.factory.createVariableDeclarator(
                // TODO: maybe incorrect
                Es2pandaVariableDeclaratorFlag.VARIABLE_DECLARATOR_FLAG_UNKNOWN,
                passIdentifier(name, type),
                passNode(initializer)
            )
        )
    }

    // @api
    // function updateVariableDeclaration(
    //     node: VariableDeclaration,
    //     name: BindingName,
    //     exclamationToken: ExclamationToken | undefined,
    //     type: TypeNode | undefined,
    //     initializer: Expression | undefined
    // ): VariableDeclaration
    function updateVariableDeclaration(
        node: VariableDeclaration,
        name: Identifier,
        exclamationToken: undefined,
        type: TypeNode | undefined,
        initializer: Expression | undefined
    ): VariableDeclaration {
        return new VariableDeclaration(
            arkts.factory.updateVariableDeclarator(
                node.node,
                // TODO: maybe incorrect
                Es2pandaVariableDeclaratorFlag.VARIABLE_DECLARATOR_FLAG_UNKNOWN,
                passIdentifier(name, type),
                passNode(initializer)
            )
        )
    }

    // @api
    // createFunctionDeclaration(
    //     modifiers: readonly ModifierLike[] | undefined,
    //     asteriskToken: AsteriskToken | undefined,
    //     name: string | Identifier | undefined,
    //     typeParameters: readonly TypeParameterDeclaration[] | undefined,
    //     parameters: readonly ParameterDeclaration[],
    //     type: TypeNode | undefined,
    //     body: Block | undefined
    // ): FunctionDeclaration;
    function createFunctionDeclaration(
        modifiers: readonly Modifier[] | undefined,
        asteriskToken: undefined,
        name: string | Identifier | undefined,
        typeParameters: readonly TypeParameterDeclaration[] | undefined,
        parameters: readonly ParameterDeclaration[],
        type: TypeNode | undefined,
        body: Block | undefined
    ): FunctionDeclaration {
        return new FunctionDeclaration(
            arkts.factory.createFunctionDeclaration(
                arkts.factory.createScriptFunction(
                    body?.node,
                    arkts.FunctionSignature.create(
                        passTypeParams(typeParameters),
                        passNodeArray(parameters),
                        type?.node
                    ),
                    0,
                    passModifiers(modifiers) | Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC | Es2pandaModifierFlags.MODIFIER_FLAGS_STATIC,
                    body === undefined,
                    passIdentifier(name)
                ),
                false
            )
        )
    }

    // @api
    // updateFunctionDeclaration(
    //     node: FunctionDeclaration,
    //     modifiers: readonly ModifierLike[] | undefined,
    //     asteriskToken: AsteriskToken | undefined,
    //     name: Identifier | undefined,
    //     typeParameters: readonly TypeParameterDeclaration[] | undefined,
    //     parameters: readonly ParameterDeclaration[],
    //     type: TypeNode | undefined,
    //     body: Block | undefined
    // ): FunctionDeclaration;
    function updateFunctionDeclaration(
        node: FunctionDeclaration,
        modifiers: readonly Modifier[] | undefined,
        asteriskToken: undefined,
        name: Identifier | undefined,
        typeParameters: readonly TypeParameterDeclaration[] | undefined,
        parameters: readonly ParameterDeclaration[],
        type: TypeNode | undefined,
        body: Block | undefined
    ): FunctionDeclaration {
        return new FunctionDeclaration(
            arkts.factory.updateFunctionDeclaration(
                node.node,
                arkts.factory.updateScriptFunction(
                    node.node.scriptFunction,
                    body?.node,
                    arkts.FunctionSignature.create(
                        passTypeParams(typeParameters),
                        passNodeArray(parameters),
                        type?.node
                    ),
                    0,
                    passModifiers(modifiers) | Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC | Es2pandaModifierFlags.MODIFIER_FLAGS_STATIC,
                    body === undefined,
                    passIdentifier(name)
                ),
                false
            )
        )
    }

    // @api
    // createParameterDeclaration(
    //     modifiers: readonly ModifierLike[] | undefined,
    //     dotDotDotToken: DotDotDotToken | undefined,
    //     name: string | BindingName,
    //     questionToken?: QuestionToken,
    //     type?: TypeNode,
    //     initializer?: Expression
    // ): ParameterDeclaration;
    function createParameterDeclaration(
        modifiers: readonly Modifier[] | undefined,
        dotDotDotToken: undefined,
        name: string | Identifier,
        questionToken?: undefined,
        type?: TypeNode,
        initializer?: Expression
    ): ParameterDeclaration {
        return new ParameterDeclaration(
            arkts.factory.createParameterDeclaration(
                arkts.factory.createIdentifier(
                    (name instanceof Identifier) ? name.node.name : name,
                    type?.node
                ),
                initializer?.node
            )
        )
    }

    // @api
    // function updateParameterDeclaration(
    //     node: ParameterDeclaration,
    //     modifiers: readonly ModifierLike[] | undefined,
    //     dotDotDotToken: DotDotDotToken | undefined,
    //     name: string | BindingName,
    //     questionToken: QuestionToken | undefined,
    //     type: TypeNode | undefined,
    //     initializer: Expression | undefined,
    // ): ParameterDeclaration
    function updateParameterDeclaration(
        node: ParameterDeclaration,
        modifiers: readonly Modifier[] | undefined,
        dotDotDotToken: undefined,
        name: string | Identifier,
        questionToken?: undefined,
        type?: TypeNode,
        initializer?: Expression
    ): ParameterDeclaration {
        return new ParameterDeclaration(
            arkts.factory.updateParameterDeclaration(
                node.node,
                arkts.factory.createIdentifier(
                    (name instanceof Identifier) ? name.node.name : name,
                    type?.node
                ),
                initializer?.node
            )
        )
    }

    // @api
    // createTypeParameterDeclaration(
    //     modifiers: readonly Modifier[] | undefined,
    //     name: string | Identifier,
    //     constraint?: TypeNode,
    //     defaultType?: TypeNode
    // ): TypeParameterDeclaration;
    function createTypeParameterDeclaration(
        modifiers: readonly Modifier[] | undefined,
        name: string | Identifier,
        constraint?: TypeNode,
        defaultType?: TypeNode
    ): TypeParameterDeclaration {
        return new TypeParameterDeclaration(
            arkts.factory.createTypeParameter(
                passIdentifier(name),
                constraint?.node,
                defaultType?.node,
                passModifiers(modifiers)
            )
        )
    }

    // @api
    // function updateTypeParameterDeclaration(
    //     node: TypeParameterDeclaration,
    //     modifiers: readonly Modifier[] | undefined,
    //     name: Identifier,
    //     constraint: TypeNode | undefined,
    //     defaultType: TypeNode | undefined
    // ): TypeParameterDeclaration
    function updateTypeParameterDeclaration(
        node: TypeParameterDeclaration,
        modifiers: readonly Modifier[] | undefined,
        name: string | Identifier,
        constraint?: TypeNode,
        defaultType?: TypeNode
    ): TypeParameterDeclaration {
        return new TypeParameterDeclaration(
            arkts.factory.updateTypeParameter(
                node.node,
                passIdentifier(name),
                constraint?.node,
                defaultType?.node,
                passModifiers(modifiers)
            )
        )
    }

    // @api
    // createETSUnionTypeNode(
    //     types: readonly TypeNode[]
    // ): UnionTypeNode
    function createETSUnionTypeNode(
        types: readonly TypeNode[]
    ): UnionTypeNode {
        return new UnionTypeNode(
            arkts.factory.createETSUnionType(
                passNodeArray(types)
            )
        )
    }

    // @api
    // function updateETSUnionTypeNode(
    //     node: UnionTypeNode,
    //     types: NodeArray<TypeNode>
    // ): UnionTypeNode
    function updateETSUnionTypeNode(
        node: UnionTypeNode,
        types: readonly TypeNode[]
    ): UnionTypeNode {
        return new UnionTypeNode(
            arkts.factory.updateETSUnionType(
                node.node,
                passNodeArray(types)
            )
        )

    }

    // @api
    // createETSTypeReferenceNode(
    //     typeName: string | EntityName,
    //     typeArguments?: readonly TypeNode[]
    // ): TypeReferenceNode;
    function createETSTypeReferenceNode(
        typeName: Identifier,
        typeArguments?: undefined
    ): TypeReferenceNode {
        return new TypeReferenceNode(
            arkts.factory.createETSTypeReferenceFromId(
                typeName.node
            )
        )
    }

    // @api
    // function updateTypeReferenceNode(
    //     node: TypeReferenceNode,
    //     typeName: EntityName,
    //     typeArguments: NodeArray<TypeNode> | undefined
    // ): TypeReferenceNode
    function updateTypeReferenceNode(
        node: TypeReferenceNode,
        typeName: Identifier,
        typeArguments?: undefined
    ): TypeReferenceNode {
        return new TypeReferenceNode(
            arkts.factory.updateTypeReferenceFromId(
                node.node,
                typeName.node
            )
        )
    }

    // @api
    // createKeywordTypeNode<TKind extends KeywordTypeSyntaxKind>(
    //     kind: TKind
    // ): KeywordTypeNode<TKind>;
    function createKeywordTypeNode(
        TKind: ts.KeywordTypeSyntaxKind
    ): KeywordTypeNode {
        function createKeywordTypeNodeFromString(
            keyword: string
        ): KeywordTypeNode {
            return new KeywordTypeNode(
                arkts.factory.createETSTypeReferenceFromId(
                    arkts.factory.createIdentifier(
                        keyword
                    )
                )
            )
        }

        function createKeywordTypeNodeFromKind(
            kind: number
        ): KeywordTypeNode {
            return new KeywordTypeNode(
                arkts.factory.createPrimitiveType(
                    kind
                )
            )
        }

        const keywords = new Map<ts.KeywordTypeSyntaxKind, KeywordTypeNode>([
            [ts.SyntaxKind.NumberKeyword, createKeywordTypeNodeFromString("number")],
            [ts.SyntaxKind.StringKeyword, createKeywordTypeNodeFromString("string")],
            [ts.SyntaxKind.AnyKeyword, createKeywordTypeNodeFromString("any")],
            [ts.SyntaxKind.VoidKeyword, createKeywordTypeNodeFromKind(8)],
        ])
        return keywords.get(TKind) ?? throwError('unsupported keyword')
    }

    // @api
    // createBlock(
    //     statements: readonly Statement[],
    //     multiLine?: boolean
    // ): Block;
    function createBlock(
        statements: readonly Statement[],
        multiline?: boolean
    ): Block {
        return new Block(
            arkts.factory.createBlock(
                passNodeArray(statements)
            )
        )
    }

    // @api
    // updateBlock(
    //     node: Block,
    //     statements: readonly Statement[]
    // ): Block;
    function updateBlock(
        node: Block,
        statements: readonly Statement[]
    ): Block {
        return new Block(
            arkts.factory.updateBlock(
                node.node,
                passNodeArray(statements)
            )
        )
    }

    // @api
    // createExpressionStatement(
    //     expression: Expression
    // ): ExpressionStatement;
    function createExpressionStatement(
        expression: Expression
    ): ExpressionStatement {
        return new ExpressionStatement(
            arkts.factory.createExpressionStatement(
                expression.node
            )
        )
    }

    // @api
    // updateExpressionStatement(
    //     node: ExpressionStatement,
    //     expression: Expression
    // ): ExpressionStatement;
    function updateExpressionStatement(
        node: ExpressionStatement,
        expression: Expression
    ): ExpressionStatement {
        return new ExpressionStatement(
            arkts.factory.updateExpressionStatement(
                node.node,
                expression.node
            )
        )
    }

    // @api
    // createReturnStatement(
    //     expression?: Expression
    // ): ReturnStatement;
    function createReturnStatement(
        expression: Expression
    ): ReturnStatement {
        return new ReturnStatement(
            arkts.factory.createReturnStatement(
                expression.node
            )
        )
    }

    // @api
    // function updateReturnStatement(
    //     node: ReturnStatement,
    //     expression: Expression | undefined
    // ): ReturnStatement
    function updateReturnStatement(
        node: ReturnStatement,
        expression: Expression
    ): ReturnStatement {
        return new ReturnStatement(
            arkts.factory.updateReturnStatement(
                node.node,
                expression.node
            )
        )
    }

    // @api
    // createPropertyAccessExpression(
    //     expression: Expression,
    //     name: string | MemberName
    // ): PropertyAccessExpression;
    function createPropertyAccessExpression(
        expression: Expression,
        name: string | Identifier
    ): PropertyAccessExpression {
        return new PropertyAccessExpression(
            arkts.factory.createMemberExpression(
                expression.node,
                passIdentifier(name),
                Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_PROPERTY_ACCESS,
                false,
                false
            )
        )
    }

    // @api
    // updatePropertyAccessExpression(
    //     node: PropertyAccessExpression,
    //     expression: Expression,
    //     name: MemberName
    // ): PropertyAccessExpression;
    function updatePropertyAccessExpression(
        node: PropertyAccessExpression,
        expression: Expression,
        name: Identifier
    ): PropertyAccessExpression {
        return new PropertyAccessExpression(
            arkts.factory.updateMemberExpression(
                node.node,
                expression.node,
                passIdentifier(name),
                Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_PROPERTY_ACCESS,
                false,
                false
            )
        )
    }

    // @api
    // createCallExpression(
    //     expression: Expression,
    //     typeArguments: readonly TypeNode[] | undefined,
    //     argumentsArray: readonly Expression[] | undefined
    // ): CallExpression;
    function createCallExpression(
        expression: Expression,
        typeArguments: readonly TypeNode[] | undefined,
        argumentsArray: readonly Expression[] | undefined
    ): CallExpression {
        return new CallExpression(
            arkts.factory.createCallExpression(
                expression.node,
                (typeArguments !== undefined) ?
                arkts.factory.createTypeParameterDeclaration(passNodeArray(typeArguments)) : undefined,
                passNodeArray(argumentsArray)
            )
        )
    }

    // @api
    // updateCallExpression(
    //     node: CallExpression,
    //     expression: Expression,
    //     typeArguments: readonly TypeNode[] | undefined,
    //     argumentsArray: readonly Expression[]
    // ): CallExpression;
    function updateCallExpression(
        node: CallExpression,
        expression: Expression,
        typeArguments: readonly TypeNode[] | undefined,
        argumentsArray: readonly Expression[] | undefined
    ): CallExpression {
        return new CallExpression(
            arkts.factory.updateCallExpression(
                node.node,
                expression.node,
                (typeArguments !== undefined) ?
                arkts.factory.createTypeParameterDeclaration(passNodeArray(typeArguments)) : undefined,
                passNodeArray(argumentsArray)
            )
        )
    }

    // @api
    // createIfStatement(
    //     expression: Expression,
    //     thenStatement: Statement,
    //     elseStatement?: Statement
    // ): IfStatement;
    function createIfStatement(
        expression: Expression,
        thenStatement: Statement,
        elseStatement?: undefined
    ): IfStatement {
        return new IfStatement(
            arkts.factory.createIfStatement(
                passNode(expression),
                passNode(thenStatement),
                passNode(elseStatement),
            )
        )
    }

    // @api
    // updateIfStatement(
    //     expression: Expression,
    //     thenStatement: Statement,
    //     elseStatement: Statement | undefined
    // ): IfStatement;
    function updateIfStatement(
        node: IfStatement,
        expression: Expression,
        thenStatement: Statement,
        elseStatement?: undefined
    ): IfStatement {
        return new IfStatement(
            arkts.factory.updateIfStatement(
                node.node,
                passNode(expression),
                passNode(thenStatement),
                passNode(elseStatement),
            )
        )
    }

    // TODO: rewrite maybe
    // @api
    // createToken(
    //     token: SyntaxKind._
    // ): _;
    function createToken<TKind extends ts.TokenSyntaxKind>(
        token: TKind
    ) {
        return new Token(token)
    }

    // @api
    // createBinaryExpression(
    //     left: Expression,
    //     operator: BinaryOperator | BinaryOperatorToken,
    //     right: Expression
    // ): BinaryExpression;
    function createBinaryExpression(
        left: Expression,
        operator: BinaryOperatorToken,
        right: Expression
    ): BinaryExpression {
        return new BinaryExpression(
            arkts.factory.createBinaryExpression(
                passNode(left),
                passToken(operator),
                passNode(right),
            )
        )
    }

    // @api
    // function updateBinaryExpression(
    //     node: BinaryExpression,
    //     left: Expression,
    //     operator: BinaryOperatorToken,
    //     right: Expression
    // ): BinaryExpression
    function updateBinaryExpression(
        node: BinaryExpression,
        left: Expression,
        operator: BinaryOperatorToken,
        right: Expression
    ): BinaryExpression {
        return new BinaryExpression(
            arkts.factory.updateBinaryExpression(
                node.node,
                passNode(left),
                passToken(operator),
                passNode(right),
            )
        )
    }

    // @api
    // createArrowFunction(
    //     modifiers: readonly Modifier[] | undefined,
    //     typeParameters: readonly TypeParameterDeclaration[] | undefined,
    //     parameters: readonly ParameterDeclaration[],
    //     type: TypeNode | undefined,
    //     equalsGreaterThanToken: EqualsGreaterThanToken | undefined,
    //     body: ConciseBody
    // ): ArrowFunction;
    function createArrowFunction(
        modifiers: readonly Modifier[] | undefined,
        typeParameters: readonly TypeParameterDeclaration[] | undefined,
        parameters: readonly ParameterDeclaration[],
        type: TypeNode | undefined,
        equalsGreaterThanToken: Token<ts.SyntaxKind.EqualsGreaterThanToken> | undefined,
        body: Block
    ) {
        return new ArrowFunction(
            arkts.factory.createArrowFunction(
                arkts.factory.createScriptFunction(
                    passNode(body),
                    arkts.FunctionSignature.create(
                        passTypeParams(typeParameters),
                        passNodeArray(parameters),
                        passNode(type)
                    ),
                    passModifiersToScriptFunction(modifiers) | Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_ARROW,
                    passModifiers(modifiers) | Es2pandaModifierFlags.MODIFIER_FLAGS_NONE,
                    false,
                    undefined
                )
            )
        )
    }

    // @api
    // function updateArrowFunction(
    //     node: ArrowFunction,
    //     modifiers: readonly Modifier[] | undefined,
    //     typeParameters: readonly TypeParameterDeclaration[] | undefined,
    //     parameters: readonly ParameterDeclaration[],
    //     type: TypeNode | undefined,
    //     equalsGreaterThanToken: EqualsGreaterThanToken,
    //     body: ConciseBody,
    // ): ArrowFunction
    function updateArrowFunction(
        node: ArrowFunction,
        modifiers: readonly Modifier[] | undefined,
        typeParameters: readonly TypeParameterDeclaration[] | undefined,
        parameters: readonly ParameterDeclaration[],
        type: undefined,
        equalsGreaterThanToken: Token<ts.SyntaxKind.EqualsGreaterThanToken> | undefined,
        body: Block,
    ): ArrowFunction {
        return new ArrowFunction(
            arkts.factory.updateArrowFunction(
                node.node,
                arkts.factory.updateScriptFunction(
                    node.node.scriptFunction,
                    passNode(body),
                    arkts.FunctionSignature.create(
                        passTypeParams(typeParameters),
                        passNodeArray(parameters),
                        passNode(type)
                    ),
                    passModifiersToScriptFunction(modifiers) | Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_ARROW,
                    passModifiers(modifiers) | Es2pandaModifierFlags.MODIFIER_FLAGS_NONE,
                    false,
                    undefined
                )
            )
        )
    }

    // @api
    // function createClassDeclaration(
    //     modifiers: readonly ModifierLike[] | undefined,
    //     name: string | Identifier | undefined,
    //     typeParameters: readonly TypeParameterDeclaration[] | undefined,
    //     heritageClauses: readonly HeritageClause[] | undefined,
    //     members: readonly ClassElement[],
    // ): ClassDeclaration
    function createClassDeclaration(
        modifiers: readonly Modifier[] | undefined,
        name: string | Identifier | undefined,
        typeParameters: readonly TypeParameterDeclaration[] | undefined,
        heritageClauses: readonly TypeParameterDeclaration[] | undefined,
        members: readonly ClassElement[]
    ): ClassDeclaration {
        return new ClassDeclaration(
            arkts.factory.createClassDeclaration(
                arkts.factory.createClassDefinition(
                    passIdentifier(name),
                    passNodeArray(members),
                    // passModifiers(modifiers) | es2panda_ModifierFlags.MODIFIER_FLAGS_PUBLIC | es2panda_ModifierFlags.MODIFIER_FLAGS_STATIC,
                    Es2pandaModifierFlags.MODIFIER_FLAGS_NONE,
                    // TODO: pass through modifiers
                    Es2pandaClassDefinitionModifiers.CLASS_DEFINITION_MODIFIERS_NONE,
                    passTypeParams(typeParameters),
                    undefined
                )
            )
        )
    }

    // @api
    // updateClassDeclaration(
    //     node: ClassDeclaration,
    //     modifiers: readonly ModifierLike[] | undefined,
    //     name: Identifier | undefined,
    //     typeParameters: readonly TypeParameterDeclaration[] | undefined,
    //     heritageClauses: readonly HeritageClause[] | undefined,
    //     members: readonly ClassElement[]
    // ): ClassDeclaration;
    function updateClassDeclaration(
        node: ClassDeclaration,
        modifiers: readonly Modifier[] | undefined,
        name: Identifier | undefined,
        typeParameters: readonly TypeParameterDeclaration[] | undefined,
        heritageClauses: undefined,
        members: readonly ClassElement[]
    ): ClassDeclaration {
        return new ClassDeclaration(
            arkts.factory.updateClassDeclaration(
                node.node,
                arkts.factory.updateClassDefinition(
                    node.node.definition,
                    passIdentifier(name),
                    passNodeArray(members),
                    // passModifiers(modifiers) | es2panda_ModifierFlags.MODIFIER_FLAGS_PUBLIC | es2panda_ModifierFlags.MODIFIER_FLAGS_STATIC,
                    Es2pandaModifierFlags.MODIFIER_FLAGS_NONE,
                    // TODO: pass through modifiers
                    Es2pandaClassDefinitionModifiers.CLASS_DEFINITION_MODIFIERS_NONE,
                    passTypeParams(typeParameters)
                )
            )
        )
    }

    // @api
    // tsc: createFunctionTypeNode(
    //     typeParameters: readonly TypeParameterDeclaration[] | undefined,
    //     parameters: readonly ParameterDeclaration[],
    //     type: TypeNode
    // ): FunctionTypeNode;
    function createFunctionTypeNode(
        typeParameters: readonly TypeParameterDeclaration[] | undefined,
        parameters: readonly ParameterDeclaration[],
        type: TypeNode
    ): FunctionTypeNode {
        return new FunctionTypeNode(
            arkts.factory.createFunctionType(
                arkts.FunctionSignature.create(
                    passTypeParams(typeParameters),
                    passNodeArray(parameters),
                    passNode(type)
                ),
                Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_NONE
            )
        )
    }

    // @api
    // function updateFunctionTypeNode(
    //     node: FunctionTypeNode,
    //     typeParameters: NodeArray<TypeParameterDeclaration> | undefined,
    //     parameters: NodeArray<ParameterDeclaration>,
    //     type: TypeNode,
    // ): FunctionTypeNode
    function updateFunctionTypeNode(
        node: FunctionTypeNode,
        typeParameters: readonly TypeParameterDeclaration[] | undefined,
        parameters: readonly ParameterDeclaration[],
        type: TypeNode
    ): FunctionTypeNode {
        return new FunctionTypeNode(
            arkts.factory.updateFunctionType(
                node.node,
                arkts.FunctionSignature.create(
                    passTypeParams(typeParameters),
                    passNodeArray(parameters),
                    passNode(type)
                ),
                Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_NONE
            )
        )
    }

    // TODO: fix modifiers
    // @api
    // createMethodDeclaration(
    //     modifiers: readonly ModifierLike[] | undefined,
    //     asteriskToken: AsteriskToken | undefined,
    //     name: string | PropertyName,
    //     questionToken: QuestionToken | undefined,
    //     typeParameters: readonly TypeParameterDeclaration[] | undefined,
    //     parameters: readonly ParameterDeclaration[],
    //     type: TypeNode | undefined,
    //     body: Block | undefined
    // ): MethodDeclaration;
    function createMethodDeclaration(
        modifiers: readonly Modifier[] | undefined,
        asteriskToken: undefined,
        name: string | Identifier,
        questionToken: undefined,
        typeParameters: readonly TypeParameterDeclaration[] | undefined,
        parameters: readonly ParameterDeclaration[],
        type: TypeNode | undefined,
        body: Block | undefined
    ): MethodDeclaration {
        const _name = passIdentifier(name)
        return new MethodDeclaration(
            arkts.factory.createMethodDefinition(
                Es2pandaMethodDefinitionKind.METHOD_DEFINITION_KIND_METHOD,
                _name,
                arkts.factory.createFunctionExpression(
                    arkts.factory.createScriptFunction(
                        passNode(body),
                        arkts.FunctionSignature.create(
                            passTypeParams(typeParameters),
                            passNodeArray(parameters),
                            passNode(type)
                        ),
                        0,
                        passModifiers(modifiers) | Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC || Es2pandaModifierFlags.MODIFIER_FLAGS_STATIC,
                        false,
                        _name
                    )
                ),
                passModifiers(modifiers),
                false
            )
        )
    }

    // @api
    // tsc: updateMethodDeclaration(
    //     node: MethodDeclaration,
    //     modifiers: readonly ModifierLike[] | undefined,
    //     asteriskToken: AsteriskToken | undefined,
    //     name: PropertyName,
    //     questionToken: QuestionToken | undefined,
    //     typeParameters: readonly TypeParameterDeclaration[] | undefined,
    //     parameters: readonly ParameterDeclaration[],
    //     type: TypeNode | undefined,
    //     body: Block | undefined
    // ): MethodDeclaration;
    function updateMethodDeclaration(
        node: MethodDeclaration,
        modifiers: readonly Modifier[] | undefined,
        asteriskToken: undefined,
        name: Identifier,
        questionToken: undefined,
        typeParameters: readonly TypeParameterDeclaration[] | undefined,
        parameters: readonly ParameterDeclaration[],
        type: undefined,
        body: Block | undefined
    ): MethodDeclaration {
        const _name = passIdentifier(name)
        return new MethodDeclaration(
            arkts.factory.updateMethodDefinition(
                node.node,
                Es2pandaMethodDefinitionKind.METHOD_DEFINITION_KIND_METHOD,
                _name,
                arkts.factory.createFunctionExpression(
                    // TODO: maybe fix
                    arkts.factory.updateScriptFunction(
                        node.node.scriptFunction,
                        passNode(body),
                        arkts.FunctionSignature.create(
                            passTypeParams(typeParameters),
                            passNodeArray(parameters),
                            passNode(type)
                        ),
                        0,
                        passModifiers(modifiers) | Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC || Es2pandaModifierFlags.MODIFIER_FLAGS_STATIC,
                        false,
                        _name
                    )
                ),
                passModifiers(modifiers),
                false
            )
        )
    }

    // @api
    // createConstructorDeclaration(
    //     modifiers: readonly ModifierLike[] | undefined,
    //     parameters: readonly ParameterDeclaration[],
    //     body: Block | undefined
    // ): ConstructorDeclaration;
    function createConstructorDeclaration(
        modifiers: readonly Modifier[] | undefined,
        parameters: readonly ParameterDeclaration[],
        body: Block | undefined
    ): ConstructorDeclaration {
        const _name = arkts.factory.createIdentifier(
            "constructor"
        )
        return new ConstructorDeclaration(
            arkts.factory.createMethodDefinition(
                Es2pandaMethodDefinitionKind.METHOD_DEFINITION_KIND_CONSTRUCTOR,
                _name,
                arkts.factory.createFunctionExpression(
                    arkts.factory.createScriptFunction(
                        passNode(body),
                        arkts.FunctionSignature.create(
                            undefined,
                            passNodeArray(parameters),
                            // TODO: change to void maybe
                            undefined
                        ),
                        passModifiersToScriptFunction(modifiers) | Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_CONSTRUCTOR,
                        passModifiers(modifiers) | Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC | Es2pandaModifierFlags.MODIFIER_FLAGS_CONSTRUCTOR,
                        false,
                        _name
                    )
                ),
                passModifiers(modifiers) | Es2pandaModifierFlags.MODIFIER_FLAGS_CONSTRUCTOR,
                false
            )
        )
    }

    // @api
    // function updateConstructorDeclaration(
    //     node: ConstructorDeclaration,
    //     modifiers: readonly ModifierLike[] | undefined,
    //     parameters: readonly ParameterDeclaration[],
    //     body: Block | undefined,
    // ): ConstructorDeclaration
    function updateConstructorDeclaration(
        node: ConstructorDeclaration,
        modifiers: readonly Modifier[] | undefined,
        parameters: readonly ParameterDeclaration[],
        body: Block | undefined
    ): ConstructorDeclaration {
        const _name = arkts.factory.updateIdentifier(
            node.node.name,
            "constructor"
        )
        return new ConstructorDeclaration(
            arkts.factory.updateMethodDefinition(
                node.node,
                Es2pandaMethodDefinitionKind.METHOD_DEFINITION_KIND_CONSTRUCTOR,
                _name,
                arkts.factory.createFunctionExpression(
                    // TODO: maybe fix
                    arkts.factory.updateScriptFunction(
                        node.node.scriptFunction,
                        passNode(body),
                        arkts.FunctionSignature.create(
                            undefined,
                            passNodeArray(parameters),
                            // TODO: change to void maybe
                            undefined
                        ),
                        passModifiersToScriptFunction(modifiers) | Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_CONSTRUCTOR,
                        passModifiers(modifiers) | Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC | Es2pandaModifierFlags.MODIFIER_FLAGS_CONSTRUCTOR,
                        false,
                        _name
                    )
                ),
                passModifiers(modifiers) | Es2pandaModifierFlags.MODIFIER_FLAGS_CONSTRUCTOR,
                false
            )
        )

    }

    // @api
    // tsc: createSuper(
    // ): SuperExpression;
    function createSuper(
    ): SuperExpression {
        return new SuperExpression(
            arkts.factory.createSuperExpression()
        )
    }

    // @api
    // tsc: updateSuper(
    //     node: SuperExpression
    // ): SuperExpression;
    function updateSuper(
        node: SuperExpression
    ): SuperExpression {
        return new SuperExpression(
            arkts.factory.updateSuperExpression(
                node.node,
            )
        )
    }

    // @api
    // tsc: createParenthesizedExpression(
    //     expression: Expression
    // ): ParenthesizedExpression;
    function createParenthesizedExpression(
        expression: Expression
    ): ParenthesizedExpression {
        return expression
        // TODO:
        // return new ParenthesizedExpression(
        //     expression
        // )
    }

    // @api
    // tsc: updateParenthesizedExpression(
    //     node: ParenthesizedExpression,
    //     expression: Expression
    // ): ParenthesizedExpression;
    function updateParenthesizedExpression(
        node: ParenthesizedExpression,
        expression: Expression
    ): ParenthesizedExpression {
        return expression
        // TODO:
        // return new ParenthesizedExpression(
        //     expression
        // )
    }

    // // @api
    // // createImportDeclaration(
    // //     decorators: readonly Decorator[] | undefined,
    // //     modifiers: readonly Modifier[] | undefined,
    // //     importClause: ImportClause | undefined,
    // //     moduleSpecifier: Expression,
    // //     assertClause?: AssertClause
    // // ): ImportDeclaration;
    // function createImportDeclaration(
    //     decorators: undefined,
    //     modifiers: readonly Modifier[] | undefined,
    //     importClause: ImportClause | undefined,
    //     moduleSpecifier: StringLiteral,
    //     assertClause?: undefined
    // ): ImportDeclaration {
    //     return new ImportDeclaration(
    //         arkts.EtsImportDeclaration.create(
    //             undefined,
    //             arkts.ImportSource.create(moduleSpecifier.node),

    //         )
    //     )
    // }

    // @api
    // createImportSpecifier(
    //     isTypeOnly: boolean,
    //     propertyName: Identifier | undefined,
    //     name: Identifier
    // ): ImportSpecifier;
    function createImportSpecifier(
        isTypeOnly: boolean,
        propertyName: Identifier | undefined,
        name: Identifier
    ): ImportSpecifier {
        return new ImportSpecifier(
            name.node
        )
    }
}

export const factory = createNodeFactory();
