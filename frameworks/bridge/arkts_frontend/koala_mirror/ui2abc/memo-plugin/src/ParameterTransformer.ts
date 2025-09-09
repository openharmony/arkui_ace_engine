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
import { KPointer } from "@koalaui/interop"
import { PositionalIdTracker, RuntimeNames } from "./utils"

export type ParamInfo = {
    ident: arkts.Identifier,
    param: arkts.ETSParameterExpression
}

export class ParameterTransformer extends arkts.AbstractVisitor {
    private rewriteIdentifiers?: Map<KPointer, () => arkts.MemberExpression | arkts.Identifier>
    private rewriteCalls?: Map<KPointer, (passArgs: arkts.Expression[]) => arkts.CallExpression>
    private rewriteThis?: boolean
    private skipNode?: arkts.VariableDeclaration

    constructor(private positionalIdTracker: PositionalIdTracker) {
        super()
    }

    withThis(flag: boolean): ParameterTransformer {
        this.rewriteThis = flag
        return this
    }

    withParameters(parameters: ParamInfo[]): ParameterTransformer {
        this.rewriteCalls = new Map(parameters.filter(it =>
            it.param.typeAnnotation && (arkts.isETSFunctionType(it.param.typeAnnotation) || arkts.isETSUnionType(it.param.typeAnnotation))).map(it => {
                return [it.param.ident!.name.startsWith(RuntimeNames.GENSYM) ? it.ident.originalPeer : it.param.originalPeer, (passArgs: arkts.Expression[]) => {
                    return factory.createMemoParameterAccessCall(it.ident.name, passArgs)
                }]
            })
        )
        this.rewriteIdentifiers = new Map(parameters.map(it => {
                return [it.param.ident!.name.startsWith(RuntimeNames.GENSYM) ? it.ident.originalPeer : it.param.originalPeer, () => {
                    return factory.createMemoParameterAccess(it.ident.name)
                }]
            })
        )
        return this
    }

    skip(memoParametersDeclaration?: arkts.VariableDeclaration): ParameterTransformer {
        this.skipNode = memoParametersDeclaration
        return this
    }

    visitor(beforeChildren: arkts.AstNode): arkts.AstNode {
        if (beforeChildren === this.skipNode) {
            return beforeChildren
        }
        if (arkts.isVariableDeclaration(beforeChildren) && this.rewriteIdentifiers?.has(beforeChildren.declarators[0].id!.originalPeer)) {
            return beforeChildren
        }
        if (arkts.isCallExpression(beforeChildren)) {
            if (arkts.isIdentifier(beforeChildren.callee)) {
                const decl = arkts.getPeerDecl(beforeChildren.callee.originalPeer) // Improve: here should be getDeclResolveGensym, but it would result in code not passing filterSource
                if (decl && this.rewriteCalls?.has(decl.originalPeer)) {
                    return this.rewriteCalls.get(decl.originalPeer)!(
                        beforeChildren.arguments.map((it) => this.visitor(it) as arkts.Expression) // Improve: remove as
                    )
                }
            }
        }
        const node = this.visitEachChild(beforeChildren)
        if (arkts.isIdentifier(node)) {
            const decl = arkts.getPeerDecl(node.originalPeer) // Improve: here should be getDeclResolveGensym, but it would result in code not passing filterSource
            if (decl && this.rewriteIdentifiers?.has(decl.originalPeer)) {
                return this.rewriteIdentifiers.get(decl.originalPeer)!()
            }
        }
        if (arkts.isThisExpression(node) && this.rewriteThis) {
            if (arkts.isReturnStatement(node.parent)) {
                return node
            }
            return factory.createMemoParameterAccess(RuntimeNames.THIS)
        }
        return node
    }
}
