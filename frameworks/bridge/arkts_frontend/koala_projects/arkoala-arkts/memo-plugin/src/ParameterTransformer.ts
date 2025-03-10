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
    private rewriteIdentifiers?: Map<KPointer, () => arkts.MemberExpression | arkts.Identifier>
    private rewriteCalls?: Map<KPointer, (passArgs: arkts.AstNode[]) => arkts.CallExpression>
    private skipNode?: arkts.VariableDeclaration

    constructor(private positionalIdTracker: PositionalIdTracker) {
        super()
    }

    withParameters(parameters: arkts.ETSParameterExpression[]): ParameterTransformer {
        this.rewriteCalls = new Map(parameters.filter(it => it.type && (arkts.isETSFunctionType(it.type) || arkts.isETSUnionType(it.type))).map((it) => {
            return [it.peer, (passArgs: arkts.AstNode[]) => {
                if (hasMemoAnnotation(it) || hasMemoIntrinsicAnnotation(it)) {
                    if (it.type && arkts.isETSFunctionType(it.type) && !it.optional) {
                        return factory.createMemoParameterAccessMemoWithScope(it.identifier.name, this.positionalIdTracker?.id(), passArgs)
                    } else {
                        return factory.createMemoParameterAccessMemoWithoutScope(it.identifier.name, this.positionalIdTracker?.id(), passArgs)
                    }
                }
                return factory.createMemoParameterAccessCall(it.identifier.name, this.positionalIdTracker?.id(), passArgs)
            }]
        }))
        this.rewriteIdentifiers = new Map(parameters.map((it) => {
            return [it.peer, () => {
                if ((it.type && arkts.isETSFunctionType(it.type)) || it.optional) {
                    return arkts.factory.createIdentifier(it.identifier.name)
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
        if (arkts.isCallExpression(beforeChildren)) {
            if (arkts.isIdentifier(beforeChildren.expression)) {
                const decl = arkts.getDecl(beforeChildren.expression)
                if (decl && arkts.isEtsParameterExpression(decl) && this.rewriteCalls?.has(decl.peer)) {
                    return this.rewriteCalls.get(decl.peer)!(
                        beforeChildren.arguments.map((it) => this.visitor(it))
                    )
                }
            }
        }
        const node = this.visitEachChild(beforeChildren)
        if (arkts.isIdentifier(node)) {
            const decl = arkts.getDecl(node)
            if ((decl && arkts.isEtsParameterExpression(decl)) && this.rewriteIdentifiers?.has(decl.peer)) {
                const res = this.rewriteIdentifiers.get(decl.peer)!()
                if (arkts.isMemberExpression(res)) {
                    return res
                }
            }
        }
        return node
    }
}
