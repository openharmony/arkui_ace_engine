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

import * as ts from "@koalaui/ets-tsc"
import { AbstractVisitor } from './AbstractVisitor'

export class CallExpressionCollector extends AbstractVisitor {
    private readonly map = new Map<string, boolean>()

    constructor(sourceFile: ts.SourceFile, ctx: ts.TransformationContext, ...names: string[]) {
        super(sourceFile, ctx)
        for (const name of names) {
            this.map.set(name, false)
        }
    }

    isVisited(name: string): boolean {
        return this.map.get(name) === true
    }

    visitor(beforeChildren: ts.Node): ts.Node {
        const node = this.visitEachChild(beforeChildren)
        if (ts.isCallExpression(node)) {
            const expression = node.expression
            if (ts.isIdentifier(expression)) {
                const name = ts.idText(expression)
                const exist = this.map.get(name)
                if (!exist) this.map.set(name, true)
            }
        }
        return node
    }
}
