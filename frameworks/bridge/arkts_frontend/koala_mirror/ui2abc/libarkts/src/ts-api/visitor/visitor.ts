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

import * as ts from "../."
import { factory } from "../factory/nodeFactory"
import { SyntaxKind } from "../static/enums"

type Visitor = (node: ts.Node) => ts.Node

// Improve: rethink (remove as)
function nodeVisitor<T extends ts.Node | undefined>(node: T, visitor: Visitor): T {
    if (node === undefined) {
        return node
    }
    return visitor(node) as T
}

// Improve: rethink (remove as)
function nodesVisitor<T extends ts.Node, TIn extends ts.NodeArray<T> | undefined>(nodes: TIn, visitor: Visitor): T[] | TIn {
    if (nodes === undefined) {
        return nodes
    }
    return nodes.map(node => visitor(node) as T)
}

type VisitEachChildFunction<T extends ts.Node> = (node: T, visitor: Visitor) => T

// Improve: add more nodes
type HasChildren =
    | ts.SourceFile
    | ts.FunctionDeclaration
    | ts.ExpressionStatement
    | ts.CallExpression
    | ts.PropertyAccessExpression
    | ts.ClassDeclaration
    | ts.MethodDeclaration
    | ts.Block
    | ts.VariableStatement
    | ts.VariableDeclarationList

type VisitEachChildTable = { [TNode in HasChildren as TNode["kind"]]: VisitEachChildFunction<TNode> }

// Improve: add more nodes
const visitEachChildTable: VisitEachChildTable = {
    [SyntaxKind.SourceFile]: function (node: ts.SourceFile, visitor: Visitor) {
        return factory.updateSourceFile(
            node,
            nodesVisitor(node.statements, visitor)
        )
    },
    [SyntaxKind.FunctionDeclaration]: function (node: ts.FunctionDeclaration, visitor: Visitor) {
        return factory.updateFunctionDeclaration(
            node,
            node.modifiers,
            undefined,
            nodeVisitor(node.name, visitor),
            nodesVisitor(node.typeParameters, visitor),
            nodesVisitor(node.parameters, visitor),
            nodeVisitor(node.type, visitor),
            nodeVisitor(node.body, visitor),
        )
    },
    [SyntaxKind.ExpressionStatement]: function (node: ts.ExpressionStatement, visitor: Visitor) {
        return factory.updateExpressionStatement(
            node,
            nodeVisitor(node.expression, visitor)
        )
    },
    [SyntaxKind.CallExpression]: function (node: ts.CallExpression, visitor: Visitor) {
        return factory.updateCallExpression(
            node,
            nodeVisitor(node.expression, visitor),
            undefined,
            nodesVisitor(node.arguments, visitor)
        )
    },
    [SyntaxKind.PropertyAccessExpression]: function (node: ts.PropertyAccessExpression, visitor: Visitor) {
        return factory.updatePropertyAccessExpression(
            node,
            nodeVisitor(node.expression, visitor),
            nodeVisitor(node.name, visitor)
        )
    },
    [SyntaxKind.ClassDeclaration]: function (node: ts.ClassDeclaration, visitor: Visitor) {
        return factory.updateClassDeclaration(
            node,
            undefined,
            nodeVisitor(node.name, visitor),
            undefined,
            undefined,
            nodesVisitor(node.members, visitor)
        )
    },
    [SyntaxKind.MethodDeclaration]: function (node: ts.MethodDeclaration, visitor: Visitor) {
        return factory.updateMethodDeclaration(
            node,
            undefined,
            undefined,
            nodeVisitor(node.name, visitor),
            undefined,
            undefined,
            nodesVisitor(node.parameters, visitor),
            undefined,
            nodeVisitor(node.body, visitor),
        )
    },
    [SyntaxKind.Block]: function (node: ts.Block, visitor: Visitor) {
        return factory.updateBlock(
            node,
            nodesVisitor(node.statements, visitor),
        )
    },
    [SyntaxKind.VariableStatement]: function (node: ts.VariableStatement, visitor: Visitor) {
        return factory.updateVariableStatement(
            node,
            undefined,
            nodeVisitor(node.declarationList, visitor),
        )
    },
    [SyntaxKind.VariableDeclarationList]: function (node: ts.VariableDeclarationList, visitor: Visitor) {
        return factory.updateVariableDeclarationList(
            node,
            nodesVisitor(node.declarations, visitor),
        )
    },
}

function nodeHasChildren(node: ts.Node): node is HasChildren {
    return node.kind in visitEachChildTable
}

export function visitEachChild<T extends ts.Node>(
    node: T,
    visitor: Visitor
): T {
    const visitFunc = (visitEachChildTable as Record<SyntaxKind, VisitEachChildFunction<any> | undefined>)[node.kind];
    if (nodeHasChildren(node) && visitFunc === undefined) {
        throwError('Unsupported node kind: ' + node.kind)
    }
    return (visitFunc === undefined) ? node : visitFunc(node, visitor);
}
