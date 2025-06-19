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

import * as ts from '@koalaui/ets-tsc';
import { ScopedVisitor } from './ScopedVisitor';
import {
    FunctionKind,
    Tracer,
    parameterStateName as localStateName,
    PositionalIdTracker,
    runtimeIdentifier,
    RuntimeNames,
    isMemoKind,
    getSymbolByNode,
    getDeclarationsByNode,
    isStableClass,
    isThisStable,
} from "./util"

export class ThisTransformer extends ScopedVisitor<boolean> {
    constructor(
        public tracer: Tracer,
        public typechecker: ts.TypeChecker,
        public sourceFile: ts.SourceFile,
        public positionalIdTracker: PositionalIdTracker,
        public functionTable: Map<ts.SignatureDeclarationBase, FunctionKind>,
        ctx: ts.TransformationContext
    ) {
        super(functionTable, ctx)
    }

    transformThisUse(node: ts.ThisExpression): ts.PropertyAccessExpression {
        const newName = localStateName("this")
        return ts.factory.createPropertyAccessExpression(
            ts.factory.createIdentifier(newName),
            runtimeIdentifier(RuntimeNames.VALUE)
        )
    }

    override withFunctionScope<T>(kind: FunctionKind, isInMemoMethod: boolean, body: ()=>T): T {
        let result: T
        this.functionScopes.push(kind, isInMemoMethod)
        result = body()
        this.functionScopes.pop()
        return result
    }

    isThisExpression(node: ts.Node): node is ts.ThisExpression {
        return node.kind == ts.SyntaxKind.ThisKeyword
    }

    isInMemoMethod(): boolean {
        return this.functionScopes.peek()?.data ?? false
    }

    visitor(node: ts.Node): ts.Node {
        if (ts.isArrowFunction(node)) {
            return this.withFunctionScope(this.currentKind(), this.isInMemoMethod(), () => {
                return this.visitEachChild(node)
            })
        }  else if (ts.isFunctionDeclaration(node)) {
            return this.withFunctionScope(this.currentKind(), false, () => {
                return this.visitEachChild(node)
            })
        }  else if (ts.isMethodDeclaration(node)) {
            const kind = this.declarationKind(node)
            const isInMemoMethod = this.isInMemoMethod() || isMemoKind(kind)
            const transformedWithChildren = this.withFunctionScope(kind, isInMemoMethod, ()=>{
                return this.visitEachChild(node)
            })
            return transformedWithChildren

        } else if (this.isThisExpression(node)) {
            if (!isThisStable(this.typechecker, this.sourceFile, node) && this.isInMemoMethod()) {
                const transformed = node.parent ?
                    this.transformThisUse(node) :
                    node
                return this.visitEachChild(transformed)
            }
        }
        return this.visitEachChild(node)
    }
}
