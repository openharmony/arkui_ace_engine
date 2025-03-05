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

import * as arkts from "@koalaui/libarkts"
import { factory } from "./MemoFactory"
import { AbstractVisitor } from "./AbstractVisitor"
import { KPointer } from "@koalaui/interop"
import { hasMemoAnnotation, hasMemoIntrinsicAnnotation, isMemoParametersDeclaration, PositionalIdTracker } from "./utils"

export class ParameterTransformer extends AbstractVisitor {
    private rewrites?: Map<KPointer, (passArgs?: arkts.AstNode[]) => arkts.CallExpression | arkts.MemberExpression>
    private skipNode?: arkts.VariableDeclaration

    constructor(private positionalIdTracker: PositionalIdTracker) {
        super()
    }

    withParameters(parameters: arkts.ETSParameterExpression[]): ParameterTransformer {
        this.rewrites = new Map(parameters.map((it) => {
            return [it.peer, (passArgs?: arkts.AstNode[]) => {
                if (it.type instanceof arkts.ETSFunctionType) {
                    if (hasMemoAnnotation(it) || hasMemoIntrinsicAnnotation(it)) {
                        return factory.createMemoParameterAccessMemo(it.identifier.name, this.positionalIdTracker?.id(), passArgs)
                    }
                    return factory.createMemoParameterAccessCall(it.identifier.name, this.positionalIdTracker?.id(), passArgs)
                }
                return factory.createMemoParameterAccess(it.identifier.name)
            }]
        }))
        return this
    }

    skip(memoParametersDeclaration?: arkts.VariableDeclaration): ParameterTransformer {
        this.skipNode = memoParametersDeclaration
        return this
    }

    visitor(beforeChildren: arkts.AstNode): arkts.AstNode {
        // TODO: temporary checking skip nodes by comparison with expected skip nodes
        // Should be fixed when update procedure implemented properly
        if (/* beforeChildren === this.skipNode */ isMemoParametersDeclaration(beforeChildren)) {
            return beforeChildren
        }
        if (beforeChildren instanceof arkts.CallExpression) {
            if (beforeChildren.expression instanceof arkts.Identifier) {
                const decl = arkts.getDecl(beforeChildren.expression)
                if (decl instanceof arkts.ETSParameterExpression && this.rewrites?.has(decl.peer)) {
                    return this.rewrites.get(decl.peer)!(
                        beforeChildren.arguments.map((it) => this.visitor(it))
                    )
                }
            }
        }
        const node = this.visitEachChild(beforeChildren)
        if (node instanceof arkts.Identifier) {
            const decl = arkts.getDecl(node)
            if (decl instanceof arkts.ETSParameterExpression && this.rewrites?.has(decl.peer)) {
                const res = this.rewrites.get(decl.peer)!()
                if (res instanceof arkts.MemberExpression) {
                    return res
                }
            }
        }
        return node
    }
}
