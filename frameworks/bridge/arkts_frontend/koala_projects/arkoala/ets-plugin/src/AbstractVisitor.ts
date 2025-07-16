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
import { asString } from './utils'

export abstract class AbstractVisitor {
    constructor(public sourceFile: ts.SourceFile, public ctx: ts.TransformationContext) { }

    abstract visitor(node: ts.Node): ts.Node

    visitEtsChildren(node: ts.EtsComponentExpression): ts.Node {
        const transformedExpression = this.visitor(node.expression)
        const transformedArguments = node.arguments.map(it => this.visitor(it))
        const transformedBody = node.body ? this.visitor(node.body) : undefined

        const newEts =  ts.factory.updateEtsComponentExpression(
            node,
            transformedExpression as ts.Identifier,
            transformedArguments as ts.Expression[],
            transformedBody as ts.Block
        )

        return newEts
    }

    visitEachChild<T extends ts.Node>(node: T): ts.Node {
        if (ts.isEtsComponentExpression(node)) {
            return this.visitEtsChildren(node)
        }
        return ts.visitEachChild(node, it=> this.visitor(it), this.ctx)
    }
}

export class DebugVisitor extends AbstractVisitor {
    constructor(public sourceFile: ts.SourceFile, public ctx: ts.TransformationContext) {
        super(sourceFile, ctx)
    }

    indentation = 0

    withIndentation(exec: () => ts.Node): ts.Node {
        this.indentation++
        const result = exec()
        this.indentation--
        return result
    }

    visitor(node: ts.Node): ts.Node {
        console.log("@" + " ".repeat(this.indentation) + asString(node))
        return this.visitEachChild(node)
    }

    visitEachChild(node: ts.Node): ts.Node {
        return this.withIndentation(() =>
            super.visitEachChild(
                node
            )
        )
    }
}
