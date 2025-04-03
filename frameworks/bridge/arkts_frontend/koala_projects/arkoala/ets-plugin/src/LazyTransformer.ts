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

import * as ts from '@koalaui/ets-tsc'
import { AbstractVisitor } from './AbstractVisitor'
import { Importer } from './Importer'
import { id } from './ApiUtils'
import { CallTable, idTextOrError } from './utils'


function statementIsLazyForEach(statement: ts.Statement): boolean {
    if (!ts.isExpressionStatement(statement)) return false
    if (!ts.isCallExpression(statement.expression)) return false
    const callee = statement.expression.expression
    if (!ts.isIdentifier(callee)) return false
    if (ts.idText(callee) != "LazyForEach") return false
    return true
}

function statementIsForEach(statement: ts.Statement): boolean {
    if (!ts.isExpressionStatement(statement)) return false
    if (!ts.isCallExpression(statement.expression)) return false
    const callee = statement.expression.expression
    if (!ts.isIdentifier(callee)) return false
    if (ts.idText(callee) != "ForEach") return false
    return true
}

export class LazyTransformer extends AbstractVisitor {
    constructor(
        sourceFile: ts.SourceFile,
        ctx: ts.TransformationContext,
        private importer: Importer,
        private callTable: CallTable
    ) {
        super(sourceFile, ctx)
    }


    convertChildIfNeeded(node: ts.Statement): ts.Statement {
        if (!statementIsForEach(node)) return node

        return this.convertForEachToForEachByArray(node as ts.ExpressionStatement)
    }

    convertForEachToForEachByArray(node: ts.ExpressionStatement): ts.ExpressionStatement {
        const call = node.expression as ts.CallExpression
        const newEts = ts.factory.updateCallExpression(
            call,
            id(this.importer.withAdaptorImport("LazyForEachByArray")),
            call.typeArguments,
            call.arguments
        )
        return ts.factory.updateExpressionStatement(
            node,
            newEts
        )
    }

    convertToLazy(node: ts.EtsComponentExpression): ts.EtsComponentExpression {
        const newBody = node.body ?
            ts.factory.updateBlock(
                node.body,
                node.body.statements.map(it => this.convertChildIfNeeded(it))
            ) : undefined

        const name = id("Lazy" + idTextOrError(node.expression))
        this.callTable.lazyCalls.add(name)
        return ts.factory.updateEtsComponentExpression(
            node,
            name,
            node.arguments,
            newBody
        )
    }


    visitor(beforeChildren: ts.Node): ts.Node {
        if (this.importer.isArkoala()) return beforeChildren

        const node = this.visitEachChild(beforeChildren)
        if (ts.isEtsComponentExpression(node)) {
            const body = node.body
            if (!body) return node

            const lazy = body.statements.find(
                it => statementIsLazyForEach(it)
            )
            if (!lazy) return node

            this.importer.addAdaptorImport("LazyForEach")
            return this.convertToLazy(node)
        }
        return node
    }
}
