import {
    ArrowFunctionExpression,
    CallExpression,
    EtsImportDeclaration,
    ETSParameterExpression,
    EtsScript,
    ExpressionStatement,
    FunctionDeclaration,
    FunctionExpression,
    IfStatement,
    MethodDefinition,
    ScriptFunction,
    StructDeclaration,
    VariableDeclaration,
    VariableDeclarator,
} from "../types"
import { MemberExpression } from "../to-be-generated/MemberExpression"
import { AstNode } from "../peers/AstNode"

export function isCallExpression(node: AstNode): node is CallExpression {
    return node instanceof CallExpression
}

export function isMemberExpression(node: AstNode): node is MemberExpression {
    return node instanceof MemberExpression
}

export function isFunctionDeclaration(node: AstNode): node is FunctionDeclaration {
    return node instanceof FunctionDeclaration
}

export function isMethodDefinition(node: AstNode): node is MethodDefinition {
    return node instanceof MethodDefinition
}

export function isEtsScript(node: AstNode): node is EtsScript {
    return node instanceof EtsScript
}

export function isExpressionStatement(node: AstNode): node is ExpressionStatement {
    return node instanceof ExpressionStatement
}

export function isArrowFunctionExpression(node: AstNode): node is ArrowFunctionExpression {
    return node instanceof ArrowFunctionExpression
}

export function isStructDeclaration(node: AstNode): node is StructDeclaration {
    return node instanceof StructDeclaration
}

export function isFunctionExpression(node: AstNode): node is FunctionExpression {
    return node instanceof FunctionExpression
}

export function isEtsParameterExpression(node: AstNode): node is ETSParameterExpression {
    return node instanceof ETSParameterExpression
}

export function isVariableDeclaration(node: AstNode): node is VariableDeclaration {
    return node instanceof VariableDeclaration
}

export function isScriptFunction(node: AstNode): node is ScriptFunction {
    return node instanceof ScriptFunction
}

export function isEtsImportDeclaration(node: AstNode): node is EtsImportDeclaration {
    return node instanceof EtsImportDeclaration
}

export function isIfStatement(node: AstNode): node is IfStatement {
    return node instanceof IfStatement
}

export function isVariableDeclarator(node: AstNode): node is VariableDeclarator {
    return node instanceof VariableDeclarator
}
