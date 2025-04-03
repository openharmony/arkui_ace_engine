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

const ANNOTATION = "_MEMO_"

function isAnnotatedCallExpression(node: ts.Node): boolean {
    return ts.isCallExpression(node) && ts.isIdentifier(node.expression) && node.expression.text.startsWith(ANNOTATION)
}

function isAnnotatedMethodDeclaration(node: ts.Node): boolean {
    return ts.isMethodDeclaration(node) && node.name.text.startsWith(ANNOTATION)
}

function transformCallExpression(node: ts.CallExpression): ts.Node {
    const decl = ts.getDecl(node.expression)
    if (decl === undefined) {
        throw new Error('memo function not found')
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
            ts.factory.createIdentifier("__memo_context"),
            ts.factory.createIdentifier("__memo_id"),
            ...node.arguments
        ]
    )
}

function transformMethodDeclaration(node: ts.MethodDeclaration): ts.Node {
    const memoContextParam =
        ts.factory.createParameterDeclaration(
            undefined,
            undefined,
            ts.factory.createIdentifier("__memo_context"),
            undefined,
            ts.factory.createTypeReferenceNode(
                ts.factory.createIdentifier("__memo_context_type")
            ),
            undefined
        )
    const memoIdParam =
        ts.factory.createParameterDeclaration(
            undefined,
            undefined,
            ts.factory.createIdentifier("__memo_id"),
            undefined,
            ts.factory.createTypeReferenceNode(
                ts.factory.createIdentifier("__memo_id_type")
            ),
            undefined
        )
    const bodyStatements = [
        ts.factory.createIfStatement(
            ts.factory.createPropertyAccessExpression(
                ts.factory.createIdentifier("__memo_scope"),
                ts.factory.createIdentifier("unchanged")
            ),
            ts.factory.createReturnStatement(
                ts.factory.createPropertyAccessExpression(
                    ts.factory.createIdentifier("__memo_scope"),
                    ts.factory.createIdentifier("cached")
                )
            ),
            undefined
        ),
        ts.factory.createExpressionStatement(
            ts.factory.createCallExpression(
                ts.factory.createIdentifier("content"),
                undefined,
                [
                ts.factory.createIdentifier("__memo_context"),
                ts.factory.createBinaryExpression(
                    ts.factory.createIdentifier("__memo_id"),
                    ts.factory.createToken(ts.SyntaxKind.PlusToken),
                    ts.factory.createStringLiteral("key_id_main.ts")
                )
                ]
        )),
        ...(node.body?.statements ?? []),
        ts.factory.createReturnStatement(
            ts.factory.createCallExpression(
                ts.factory.createPropertyAccessExpression(
                    ts.factory.createIdentifier("__memo_scope"),
                    ts.factory.createIdentifier("recache")
                ),
                undefined,
                undefined
            )
        ),
    ]
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
            memoContextParam,
            memoIdParam,
            ...node.parameters
        ],
        undefined,
        node.body ?
        ts.factory.updateBlock(
            node.body,
            bodyStatements
        ) : undefined
    )
}

export class MemoTransformer extends AbstractVisitor {
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
