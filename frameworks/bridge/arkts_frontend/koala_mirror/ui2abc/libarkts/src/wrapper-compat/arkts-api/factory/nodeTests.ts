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

import { global } from "../static/global"
import {
    ArrowFunctionExpression,
    CallExpression,
    ETSParameterExpression,
    EtsScript,
    ExpressionStatement,
    FunctionDeclaration,
    FunctionExpression,
    IfStatement,
    MethodDefinition,
    // ScriptFunction,
    StructDeclaration,
    VariableDeclaration,
    VariableDeclarator,
    AssignmentExpression,
    NumberLiteral
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
    return global.es2panda._IsMethodDefinition(node.peer);
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

// export function isScriptFunction(node: AstNode): node is ScriptFunction {
//     return node instanceof ScriptFunction
// }

export function isIfStatement(node: AstNode): node is IfStatement {
    return node instanceof IfStatement
}

export function isVariableDeclarator(node: AstNode): node is VariableDeclarator {
    return node instanceof VariableDeclarator
}

export function isAssignmentExpression(node: AstNode): node is AssignmentExpression {
    return node instanceof AssignmentExpression;
}

export function isNumberLiteral(node: AstNode): node is NumberLiteral {
    return node instanceof NumberLiteral;
}