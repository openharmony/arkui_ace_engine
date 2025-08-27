import { SyntaxKind, } from "@koalaui/ets-tsc"

import {
    ArrowFunction,
    Block,
    CallExpression,
    ClassDeclaration,
    ExpressionStatement,
    FunctionDeclaration,
    FunctionExpression,
    FunctionTypeNode,
    GetAccessorDeclaration,
    Identifier,
    MethodDeclaration,
    MethodSignature,
    Node,
    ParameterDeclaration,
    PropertyAccessExpression,
    PropertyDeclaration,
    PropertySignature,
    SetAccessorDeclaration,
    SourceFile,
    VariableDeclaration,
    VariableDeclarationList,
    VariableStatement,
} from "../types"

export function isIdentifier(node: Node): node is Identifier {
    return node.kind === SyntaxKind.Identifier
}

export function isCallExpression(node: Node): node is CallExpression {
    return node.kind === SyntaxKind.CallExpression
}

export function isPropertyAccessExpression(node: Node): node is PropertyAccessExpression {
    return node.kind === SyntaxKind.PropertyAccessExpression
}

export function isFunctionDeclaration(node: Node): node is FunctionDeclaration {
    return node.kind === SyntaxKind.FunctionDeclaration
}

export function isMethodDeclaration(node: Node): node is MethodDeclaration {
    return node.kind === SyntaxKind.MethodDeclaration
}

export function isSourceFile(node: Node): node is SourceFile {
    return node.kind === SyntaxKind.SourceFile
}

export function isExpressionStatement(node: Node): node is ExpressionStatement {
    return node.kind === SyntaxKind.ExpressionStatement
}

export function isArrowFunction(node: Node): node is ArrowFunction {
    return node.kind === SyntaxKind.ArrowFunction
}

export function isClassDeclaration(node: Node): node is ClassDeclaration {
    return node.kind === SyntaxKind.ClassDeclaration
}

export function isBlock(node: Node): node is Block {
    return node.kind === SyntaxKind.Block
}

export function isFunctionExpression(node: Node): node is FunctionExpression {
    return node.kind === SyntaxKind.FunctionExpression
}

export function isParameter(node: Node): node is ParameterDeclaration {
    return node.kind === SyntaxKind.Parameter
}

export function isVariableDeclaration(node: Node): node is VariableDeclaration {
    return node.kind === SyntaxKind.VariableDeclaration
}

export function isVariableDeclarationList(node: Node): node is VariableDeclarationList {
    return node.kind === SyntaxKind.VariableDeclarationList
}

export function isPropertyDeclaration(node: Node): node is PropertyDeclaration {
    return node.kind === SyntaxKind.PropertyDeclaration
}

export function isPropertySignature(node: Node): node is PropertySignature {
    return node.kind === SyntaxKind.PropertySignature
}

export function isFunctionTypeNode(node: Node): node is FunctionTypeNode {
    return node.kind === SyntaxKind.FunctionType
}

export function isMethodSignature(node: Node): node is MethodSignature {
    return node.kind === SyntaxKind.MethodSignature
}

export function isGetAccessorDeclaration(node: Node): node is GetAccessorDeclaration {
    return node.kind === SyntaxKind.GetAccessor
}

export function isSetAccessorDeclaration(node: Node): node is SetAccessorDeclaration {
    return node.kind === SyntaxKind.SetAccessor
}

export function isVariableStatement(node: Node): node is VariableStatement {
    return node.kind === SyntaxKind.VariableStatement
}
