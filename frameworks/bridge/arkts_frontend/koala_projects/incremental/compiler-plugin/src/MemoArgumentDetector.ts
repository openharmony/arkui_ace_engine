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
import { Rewrite } from './transformation-context';
import { AbstractVisitor } from './AbstractVisitor'
import { FunctionKind, isAnyMemoKind } from './util';

export class MemoArgumentDetector extends AbstractVisitor {
    constructor(
        public typechecker: ts.TypeChecker,
        public rewrite: Rewrite,
        public memoArgument: ts.Node,
        ctx: ts.TransformationContext,
    ) {
        super(ctx)
    }    
    hasMemoArgument : boolean = false
    

    visitor(node: ts.Node): ts.Node {

        if(ts.isCallExpression(node)){
            const callKind = this.rewrite.callTable.get(node) ?? FunctionKind.REGULAR
            if(isAnyMemoKind(callKind)) {
                this.hasMemoArgument = true
                this.memoArgument = node
            }
        }
        return this.visitEachChild(node)
    }

    usingMemoFunction(node: ts.Expression): boolean {
        this.hasMemoArgument = false
        this.visitor(node)
        return this.hasMemoArgument
    }    
}