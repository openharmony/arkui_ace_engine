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
import { AbstractVisitor } from "./AbstractVisitor";
import { FunctionKind, FunctionTable, isAnyMemoKind, isFunctionOrMethod, Tracer } from "./util";

export class DumpVisitor extends AbstractVisitor {
    constructor(
        public tracer: Tracer,
        public sourceFile: ts.SourceFile,
        public functionTable: FunctionTable,
        ctx: ts.TransformationContext
    ) {
        super(ctx)
    }

    declarationKind(node: ts.FunctionLikeDeclarationBase): FunctionKind {
        const originalNode = ts.getOriginalNode(node) as ts.FunctionLikeDeclarationBase
        return this.functionTable.get(originalNode) ?? FunctionKind.REGULAR
    }

    isAnyMemo(node: ts.FunctionLikeDeclarationBase): boolean {
        return isAnyMemoKind(this.declarationKind(node))
    }

    visitor(beforeChildren: ts.Node): ts.Node {
        const node = this.visitEachChild(beforeChildren)
        let transformed: ts.Node|undefined = undefined

        if (isFunctionOrMethod(node)) {
            if (isAnyMemoKind(this.declarationKind(node))) {
                this.tracer.keepTransformedFunction(node, this.sourceFile)
            }
            return node
        }
        return transformed ?? node
    }
}