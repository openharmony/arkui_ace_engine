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
import { AbstractVisitor } from "./AbstractVisitor"
import { FunctionKind, isAnyMemoKind, isMemoKind } from "./util"

class FunctionScope<T> {
    constructor(
        public kind: FunctionKind,
        public data: T,
    ){}
}

class FunctionScopes<T> {
    constructor() {}

    private stack: FunctionScope<T>[] = []

    push(kind: FunctionKind, data: T) {
        this.stack.push(new FunctionScope(kind, data))
    }
    pop() {
        this.stack.pop()
    }
    peek(): FunctionScope<T>|undefined {
        if (this.stack.length == 0) return undefined
        return this.stack[this.stack.length-1]
    }
}

export abstract class ScopedVisitor<T> extends AbstractVisitor {
    readonly functionScopes: FunctionScopes<T>
    constructor(
        public functionTable: Map<ts.SignatureDeclarationBase, FunctionKind>,
        ctx: ts.TransformationContext
    ) {
        super(ctx)
        this.functionScopes = new FunctionScopes()
    }

    declarationKind(node: ts.FunctionLikeDeclarationBase): FunctionKind {
        const originalNode = ts.getOriginalNode(node) as ts.FunctionLikeDeclarationBase
        return this.functionTable.get(originalNode) ?? FunctionKind.REGULAR
    }

    currentKind(): FunctionKind {
        return this.functionScopes.peek()?.kind ?? FunctionKind.REGULAR
    }

    isAnyMemo(node: ts.FunctionLikeDeclarationBase): boolean {
        return isAnyMemoKind(this.declarationKind(node))
    }

    isMemoOrComponent(node: ts.FunctionLikeDeclarationBase): boolean {
        return isMemoKind(this.declarationKind(node))
    }

    withFunctionScope<R>(kind: FunctionKind, data: T, body: ()=>R): R {
        let result: R
        this.functionScopes.push(kind, data)
        result = body()
        this.functionScopes.pop()
        return result
    }
}
