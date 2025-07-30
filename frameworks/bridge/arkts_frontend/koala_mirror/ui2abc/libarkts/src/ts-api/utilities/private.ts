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

import * as ts from "../"
import * as arkts from "../../arkts-api"

import { KInt } from "@koalaui/interop"
import {
    SyntaxKind,
    TokenSyntaxKind,
    NodeFlags,
} from "../static/enums"
import {
    Es2pandaAstNodeType,
    Es2pandaModifierFlags,
    Es2pandaScriptFunctionFlags,
    Es2pandaTokenType,
    Es2pandaVariableDeclarationKind,
} from "../../arkts-api"

export function todo(): any {
    throwError("Not yet implemented")
}

type kindTypes =
    | { new (node: arkts.AstNode): ts.Node }
    | { new (node: arkts.Identifier): ts.Identifier }
    | { new (node: arkts.EtsScript): ts.SourceFile }
    | { new (node: arkts.StringLiteral): ts.StringLiteral }
    | { new (node: arkts.NumberLiteral): ts.NumericLiteral }
    | { new (node: arkts.ExpressionStatement): ts.ExpressionStatement }
    | { new (node: arkts.FunctionDeclaration): ts.FunctionDeclaration }
    | { new (node: arkts.ReturnStatement): ts.ReturnStatement }
    | { new (node: arkts.ETSParameterExpression): ts.ParameterDeclaration }
    | { new (node: arkts.CallExpression): ts.CallExpression }
    | { new (node: arkts.BlockStatement): ts.Block }
    | { new (node: arkts.TSTypeParameter): ts.TypeParameterDeclaration}
    | { new (node: arkts.MemberExpression): ts.PropertyAccessExpression}
    | { new (node: arkts.IfStatement): ts.IfStatement}
    | { new (node: arkts.ETSTypeReference): ts.TypeReferenceNode }
    | { new (node: arkts.ETSPrimitiveType | arkts.ETSTypeReference): ts.KeywordTypeNode }
    | { new (node: arkts.BinaryExpression): ts.BinaryExpression }
    | { new (node: arkts.ETSUnionType): ts.UnionTypeNode }
    | { new (node: arkts.ArrowFunctionExpression): ts.ArrowFunction }
    | { new (node: arkts.ClassDeclaration): ts.ClassDeclaration }
    | { new (node: arkts.MethodDefinition): ts.MethodDeclaration }
    | { new (node: arkts.VariableDeclarator): ts.VariableDeclaration }
    | { new (node: arkts.VariableDeclaration): ts.VariableStatement }

export function classByEtsNode(node: arkts.AstNode) {
    const types =
        new Map<Es2pandaAstNodeType, kindTypes>([
            [Es2pandaAstNodeType.AST_NODE_TYPE_ETS_MODULE, ts.SourceFile],
            [Es2pandaAstNodeType.AST_NODE_TYPE_IDENTIFIER, ts.Identifier],
            [Es2pandaAstNodeType.AST_NODE_TYPE_STRING_LITERAL, ts.StringLiteral],
            [Es2pandaAstNodeType.AST_NODE_TYPE_NUMBER_LITERAL, ts.NumericLiteral],
            [Es2pandaAstNodeType.AST_NODE_TYPE_EXPRESSION_STATEMENT, ts.ExpressionStatement],
            [Es2pandaAstNodeType.AST_NODE_TYPE_FUNCTION_DECLARATION, ts.FunctionDeclaration],
            [Es2pandaAstNodeType.AST_NODE_TYPE_RETURN_STATEMENT, ts.ReturnStatement],
            [Es2pandaAstNodeType.AST_NODE_TYPE_ETS_PARAMETER_EXPRESSION, ts.ParameterDeclaration],
            [Es2pandaAstNodeType.AST_NODE_TYPE_CALL_EXPRESSION, ts.CallExpression],
            [Es2pandaAstNodeType.AST_NODE_TYPE_BLOCK_STATEMENT, ts.Block],
            [Es2pandaAstNodeType.AST_NODE_TYPE_ETS_TYPE_REFERENCE, ts.TypeReferenceNode],
            [Es2pandaAstNodeType.AST_NODE_TYPE_TS_TYPE_PARAMETER, ts.TypeParameterDeclaration],
            [Es2pandaAstNodeType.AST_NODE_TYPE_MEMBER_EXPRESSION, ts.PropertyAccessExpression],
            [Es2pandaAstNodeType.AST_NODE_TYPE_IF_STATEMENT, ts.IfStatement],
            [Es2pandaAstNodeType.AST_NODE_TYPE_ETS_PRIMITIVE_TYPE, ts.KeywordTypeNode],
            [Es2pandaAstNodeType.AST_NODE_TYPE_BINARY_EXPRESSION, ts.BinaryExpression],
            [Es2pandaAstNodeType.AST_NODE_TYPE_ETS_UNION_TYPE, ts.UnionTypeNode],
            [Es2pandaAstNodeType.AST_NODE_TYPE_ARROW_FUNCTION_EXPRESSION, ts.ArrowFunction],
            [Es2pandaAstNodeType.AST_NODE_TYPE_CLASS_DECLARATION, ts.ClassDeclaration],
            [Es2pandaAstNodeType.AST_NODE_TYPE_METHOD_DEFINITION, ts.MethodDeclaration],
            [Es2pandaAstNodeType.AST_NODE_TYPE_VARIABLE_DECLARATION, ts.VariableStatement],
            [Es2pandaAstNodeType.AST_NODE_TYPE_VARIABLE_DECLARATOR, ts.VariableDeclaration],
            [Es2pandaAstNodeType.AST_NODE_TYPE_SUPER_EXPRESSION, ts.SuperExpression],

            [Es2pandaAstNodeType.AST_NODE_TYPE_CLASS_STATIC_BLOCK, ts.UnsupportedNode],
            [Es2pandaAstNodeType.AST_NODE_TYPE_CLASS_PROPERTY, ts.UnsupportedNode],
            [Es2pandaAstNodeType.AST_NODE_TYPE_ETS_IMPORT_DECLARATION, ts.UnsupportedNode],
        ])

    return types.get(node.type) ?? throwError(`UNSUPPORTED NODE (ts): ${Es2pandaAstNodeType[node.type]}`)
}

// TODO: add checks for casts in functions below

export function unpackNode<U extends arkts.AstNode, T extends ts.Node<U> >(node: U): T
export function unpackNode<U extends arkts.AstNode | undefined, T extends ts.Node<U> >(node: U): T | undefined
export function unpackNode<U extends arkts.AstNode | undefined, T extends ts.Node<U> >(node: U): T | undefined {
    if (node === undefined) {
        return undefined
    }
    return (new (classByEtsNode(node))(node as any)) as T
}

export function passNode<T extends arkts.AstNode>(node: ts.Node<T>): T
export function passNode<T extends arkts.AstNode>(node: ts.Node<T> | undefined): T | undefined
export function passNode<T extends arkts.AstNode>(node: ts.Node<T> | undefined): T | undefined {
    if (node === undefined) {
        return undefined
    }
    return (node.node as T) ?? throwError('trying to pass non-compatible node')
}

export function unpackNodeArray<U extends arkts.AstNode | undefined, T extends ts.Node<arkts.AstNode> >(nodes: readonly U[]): ts.NodeArray<T>
export function unpackNodeArray<U extends arkts.AstNode | undefined, T extends ts.Node<arkts.AstNode> >(nodes: readonly U[] | undefined): ts.NodeArray<T> | undefined
export function unpackNodeArray<U extends arkts.AstNode | undefined, T extends ts.Node<arkts.AstNode> >(nodes: readonly U[] | undefined): ts.NodeArray<T> | undefined {
    return nodes?.map((node: U) => unpackNode(node)) as ReadonlyArray<ts.Node<arkts.AstNode> > as ts.NodeArray<T>
}

export function passNodeArray<T extends arkts.AstNode>(nodes: readonly ts.Node<T>[]): T[]
export function passNodeArray<T extends arkts.AstNode>(nodes: readonly ts.Node<T>[] | undefined): T[] | undefined
export function passNodeArray<T extends arkts.AstNode>(nodes: readonly ts.Node<T>[] | undefined): T[] | undefined {
    return nodes?.map((node: ts.Node<T>) => passNode<T>(node))
}

export function passIdentifier(node: ts.Identifier | string, typeAnnotation?: ts.TypeNode): arkts.Identifier
export function passIdentifier(node: ts.Identifier | string | undefined, typeAnnotation?: ts.TypeNode): arkts.Identifier | undefined
export function passIdentifier(node: ts.Identifier | string | undefined, typeAnnotation?: ts.TypeNode): arkts.Identifier | undefined {
    if (node === undefined) {
        return undefined
    }
    if (node instanceof ts.Identifier) {
        if (typeAnnotation === undefined) {
            return node.node
        }
        return arkts.Identifier.create(
            node.node.name,
            passNode(typeAnnotation)
        )
    }
    return arkts.Identifier.create(
        node,
        passNode(typeAnnotation)
    )
}

// TODO: support optional params
export function passTypeParams(params: readonly ts.TypeParameterDeclaration[] | undefined): arkts.TSTypeParameterDeclaration | undefined {
    if (params === undefined) {
        return undefined
    }
    return arkts.factory.createTypeParameterDeclaration(
        passNodeArray(params)
    )
}

export function unpackModifiers(modifiers: KInt | undefined): ts.NodeArray<ts.Modifier> {
    const translation = new Map<Es2pandaModifierFlags, ts.ModifierSyntaxKind>([
        // [Es2pandaModifierFlags.MODIFIER_FLAGS_NONE, SyntaxKind.UnknownKeyword],
        // [Es2pandaModifierFlags.MODIFIER_FLAGS_CONSTRUCTOR, SyntaxKind.ConstructorKeyword],

        [Es2pandaModifierFlags.MODIFIER_FLAGS_ABSTRACT, SyntaxKind.AbstractKeyword],
        // TODO: unsupported
        // [Es2pandaModifierFlags. , SyntaxKind.AccessorKeyword],
        [Es2pandaModifierFlags.MODIFIER_FLAGS_ASYNC, SyntaxKind.AsyncKeyword],
        [Es2pandaModifierFlags.MODIFIER_FLAGS_CONST, SyntaxKind.ConstKeyword],
        [Es2pandaModifierFlags.MODIFIER_FLAGS_DECLARE, SyntaxKind.DeclareKeyword],
        // TODO: choose one
        // [Es2pandaModifierFlags.MODIFIER_FLAGS_DEFAULT_EXPORT, SyntaxKind.DefaultClause],
        // [Es2pandaModifierFlags.MODIFIER_FLAGS_DEFAULT_EXPORT, SyntaxKind.DefaultKeyword],
        [Es2pandaModifierFlags.MODIFIER_FLAGS_EXPORT, SyntaxKind.ExportKeyword],
        [Es2pandaModifierFlags.MODIFIER_FLAGS_IN, SyntaxKind.InKeyword],
        [Es2pandaModifierFlags.MODIFIER_FLAGS_PRIVATE, SyntaxKind.PrivateKeyword],
        [Es2pandaModifierFlags.MODIFIER_FLAGS_PROTECTED, SyntaxKind.ProtectedKeyword],
        [Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC, SyntaxKind.PublicKeyword],
        [Es2pandaModifierFlags.MODIFIER_FLAGS_OUT, SyntaxKind.OutKeyword],
        [Es2pandaModifierFlags.MODIFIER_FLAGS_OVERRIDE, SyntaxKind.OverrideKeyword],
        [Es2pandaModifierFlags.MODIFIER_FLAGS_READONLY, SyntaxKind.ReadonlyKeyword],
        [Es2pandaModifierFlags.MODIFIER_FLAGS_STATIC, SyntaxKind.StaticKeyword],
    ])

    const bits = function*(flags: KInt) {
        let bit: KInt = 1
        while (flags >= bit) {
        if ((flags & bit) > 0) {
            yield bit
        }
        bit <<= 1
        }
    }
    if (modifiers === undefined) {
        return [] as ReadonlyArray<ts.Modifier> as ts.NodeArray<ts.Modifier>
    }
    let mods: ts.Modifier[] = []
    for (const bit of bits(modifiers)) {
        mods.push(new ts.Modifier(translation.get(bit) ?? throwError(`Unsupported modifier: ${bit}`)))
    }
    return mods as ReadonlyArray<ts.Modifier> as ts.NodeArray<ts.Modifier>
}

export function passModifiers(modifiers: ReadonlyArray<ts.Modifier | undefined | Es2pandaModifierFlags> | undefined): KInt {
    const translation = new Map<ts.ModifierSyntaxKind, Es2pandaModifierFlags>([
        // [SyntaxKind.UnknownKeyword, Es2pandaModifierFlags.MODIFIER_FLAGS_NONE],
        // [SyntaxKind.ConstructorKeyword, Es2pandaModifierFlags.MODIFIER_FLAGS_CONSTRUCTOR],

        [SyntaxKind.AbstractKeyword, Es2pandaModifierFlags.MODIFIER_FLAGS_ABSTRACT],
        // TODO: unsupported
        // [SyntaxKind.AccessorKeyword, Es2pandaModifierFlags.],
        [SyntaxKind.AsyncKeyword, Es2pandaModifierFlags.MODIFIER_FLAGS_ASYNC],
        [SyntaxKind.ConstKeyword, Es2pandaModifierFlags.MODIFIER_FLAGS_CONST],
        [SyntaxKind.DeclareKeyword, Es2pandaModifierFlags.MODIFIER_FLAGS_DECLARE],
        [SyntaxKind.DefaultKeyword, Es2pandaModifierFlags.MODIFIER_FLAGS_DEFAULT_EXPORT],
        [SyntaxKind.ExportKeyword, Es2pandaModifierFlags.MODIFIER_FLAGS_EXPORT],
        [SyntaxKind.InKeyword, Es2pandaModifierFlags.MODIFIER_FLAGS_IN],
        [SyntaxKind.PrivateKeyword, Es2pandaModifierFlags.MODIFIER_FLAGS_PRIVATE],
        [SyntaxKind.ProtectedKeyword, Es2pandaModifierFlags.MODIFIER_FLAGS_PROTECTED],
        [SyntaxKind.PublicKeyword, Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC],
        [SyntaxKind.OutKeyword, Es2pandaModifierFlags.MODIFIER_FLAGS_OUT],
        [SyntaxKind.OverrideKeyword, Es2pandaModifierFlags.MODIFIER_FLAGS_OVERRIDE],
        [SyntaxKind.ReadonlyKeyword, Es2pandaModifierFlags.MODIFIER_FLAGS_READONLY],
        [SyntaxKind.StaticKeyword, Es2pandaModifierFlags.MODIFIER_FLAGS_STATIC],
    ])

    if (modifiers === undefined) {
        return Es2pandaModifierFlags.MODIFIER_FLAGS_NONE
    }
    return modifiers
        .map((mod: ts.Modifier | undefined | Es2pandaModifierFlags) => {
            if (mod === undefined) {
                return Es2pandaModifierFlags.MODIFIER_FLAGS_NONE
            }
            if (typeof mod === 'object') {
                return translation.get(mod.kind) ?? throwError(`Unsupported modifier: ${mod.kind}`)
            }
            return mod
        })
        .reduce(
            (prev, curr) => (prev | curr),
            Es2pandaModifierFlags.MODIFIER_FLAGS_NONE
        )
}

export function passToken<TKind extends TokenSyntaxKind>(token: ts.Token<TKind>): KInt {
    const translation = new Map<TokenSyntaxKind, Es2pandaTokenType>([
        [SyntaxKind.PlusToken, Es2pandaTokenType.TOKEN_TYPE_PUNCTUATOR_PLUS],
        [SyntaxKind.MinusToken, Es2pandaTokenType.TOKEN_TYPE_PUNCTUATOR_MINUS],
        [SyntaxKind.AsteriskToken, Es2pandaTokenType.TOKEN_TYPE_PUNCTUATOR_MULTIPLY],
    ])

    return translation.get(token.kind) ?? throwError('unsupported token')
}

export function passModifiersToScriptFunction(modifiers: readonly ts.Modifier[] | undefined): KInt {
    const translation = new Map<ts.ModifierSyntaxKind, Es2pandaScriptFunctionFlags>([
        [SyntaxKind.StaticKeyword, Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_STATIC_BLOCK],
        [SyntaxKind.AsyncKeyword, Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_ASYNC],
        [SyntaxKind.PublicKeyword, Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_NONE],
    ])

    return modifiers?.reduce(
        (prev, curr) => prev | (translation.get(curr.kind) ?? throwError(`Unsupported ScriptFunction flag: ${curr.kind}`)),
        Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_NONE
    ) ?? Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_NONE
}

export function passVariableDeclarationKind(flags: NodeFlags): Es2pandaVariableDeclarationKind {
    const translation = new Map<NodeFlags, Es2pandaVariableDeclarationKind>([
        [NodeFlags.Const, Es2pandaVariableDeclarationKind.VARIABLE_DECLARATION_KIND_CONST],
        [NodeFlags.Let, Es2pandaVariableDeclarationKind.VARIABLE_DECLARATION_KIND_LET],
        [NodeFlags.None, Es2pandaVariableDeclarationKind.VARIABLE_DECLARATION_KIND_VAR],
    ])

    return translation.get(flags) ?? throwError('unsupported VariableDeclarationKind')
}

export function unpackVariableDeclarationKind(kind: Es2pandaVariableDeclarationKind): NodeFlags {
    const translation = new Map<Es2pandaVariableDeclarationKind, NodeFlags>([
        [Es2pandaVariableDeclarationKind.VARIABLE_DECLARATION_KIND_CONST, NodeFlags.Const],
        [Es2pandaVariableDeclarationKind.VARIABLE_DECLARATION_KIND_LET, NodeFlags.Let],
        [Es2pandaVariableDeclarationKind.VARIABLE_DECLARATION_KIND_VAR, NodeFlags.None],
    ])

    return translation.get(kind) ?? throwError('unsupported VariableDeclarationKind')
}
