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

import * as ts from '@koalaui/ets-tsc'
import { AbstractVisitor } from './AbstractVisitor'
import { getDecorator } from './ApiUtils'
import { Importer } from './Importer'
import { dropDecorators } from './utils'

export const ObservedDecorator = "Observed"

export class ObservedResolver extends AbstractVisitor {
    constructor(
        sourceFile: ts.SourceFile,
        ctx: ts.TransformationContext,
        private importer: Importer,
    ) {
        super(sourceFile, ctx)
    }

    visitor(beforeChildren: ts.Node): ts.Node {
        const node = this.visitEachChild(beforeChildren)
        if (ts.isClassDeclaration(node)) {
            const decorator = getDecorator(node, ObservedDecorator)
            if (decorator) {
                if (this.importer.isArkts()) {
                    console.log("Warning: @Observed class decorator is not supported yet in arkts 2.0 app")
                    return ts.factory.updateClassDeclaration(
                        node,
                        dropDecorators(node.modifiers, ObservedDecorator),
                        node.name,
                        node.typeParameters,
                        node.heritageClauses,
                        node.members)
                }
                // add corresponding import for TypeScript-based implementations
                this.importer.withCommonImport(ObservedDecorator)
            }
        }
        return node
    }
}
