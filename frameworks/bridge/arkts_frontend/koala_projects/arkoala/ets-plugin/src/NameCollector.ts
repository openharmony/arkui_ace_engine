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
import { getLineNumber, isCallDecorator } from './ApiUtils'
import { NameTable, asString, isBuilderLambda, IssueTable, BuilderLambdaDecorator, filterDecorators } from './utils'


export class NameCollector extends AbstractVisitor {
    private printer = ts.createPrinter({ removeComments: false })
    constructor(
        sourceFile: ts.SourceFile,
        ctx: ts.TransformationContext,
        public nameTable: NameTable,
        private issueTable: IssueTable
    ) {
        super(sourceFile, ctx)
    }

    visitor(beforeChildren: ts.Node): ts.Node {
        const node = this.visitEachChild(beforeChildren)
        if (ts.isStructDeclaration(node)) {
            if (node.name) {
                this.nameTable.structs.push(ts.idText(node.name))
            }
            return node
        }
        if (isBuilderLambda(node)) {
            const decorators = filterDecorators(node)!
            const index = decorators.findIndex(decorator => isCallDecorator(decorator, BuilderLambdaDecorator))
            // Record builder lambda position to
            this.issueTable.builderLambda.push(getLineNumber(this.sourceFile, decorators[index].end))
        }
        return node
    }
}
