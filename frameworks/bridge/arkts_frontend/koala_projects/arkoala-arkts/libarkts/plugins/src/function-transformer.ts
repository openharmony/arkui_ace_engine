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

import * as ts from "@koalaui/libarkts"
import { AbstractVisitor } from "./AbstractVisitor";

const ANNOTATION = "_REWRITE_"

function isAnnotatedCallExpression(node: ts.Node): boolean {
    return ts.isCallExpression(node) && ts.isIdentifier(node.expression) && node.expression.text.startsWith(ANNOTATION)
}

function isAnnotatedMethodDeclaration(node: ts.Node): boolean {
    return ts.isMethodDeclaration(node) && node.name.text.startsWith(ANNOTATION)
}

function transformCallExpression(node: ts.CallExpression): ts.Node {
    const decl = ts.getDecl(node.expression)
    if (decl === undefined) {
        throw new Error('memo function for call not found')
    }
    if (!ts.isIdentifier(node.expression)) {
        throw new Error('expression should be Identifier')
    }

    return ts.factory.updateCallExpression(
        node,
        ts.factory.createIdentifier(
            node.expression.text.slice(ANNOTATION.length)
        ),
        undefined,
        [
            ts.factory.createStringLiteral("SAMPLE"),
            ...node.arguments
        ]
    )
}

function transformMethodDeclaration(node: ts.MethodDeclaration): ts.Node {
    const stringParam =
        ts.factory.createParameterDeclaration(
            undefined,
            undefined,
            ts.factory.createIdentifier("x"),
            undefined,
            ts.factory.createKeywordTypeNode(ts.SyntaxKind.StringKeyword),
            undefined
        )
    return ts.factory.updateMethodDeclaration(
        node,
        undefined,
        undefined,
        ts.factory.createIdentifier(
            node.name.text.slice(ANNOTATION.length)
        ),
        undefined,
        undefined,
        [
            stringParam,
            ...node.parameters
        ],
        undefined,
        node.body,
    )
}

export class FunctionTransformer extends AbstractVisitor {
    constructor(
        ctx?: ts.TransformationContext
    ) {
        super(ctx)
    }

    visitor(beforeChildren: ts.Node): ts.Node {
        const node: ts.Node = this.visitEachChild(beforeChildren)

        if (isAnnotatedMethodDeclaration(node) && ts.isMethodDeclaration(node)) {
            return transformMethodDeclaration(node)
        } else if (isAnnotatedCallExpression(node) && ts.isCallExpression(node) && ts.isIdentifier(node.expression)) {
            return transformCallExpression(node)
        }

        return node
    }
}
