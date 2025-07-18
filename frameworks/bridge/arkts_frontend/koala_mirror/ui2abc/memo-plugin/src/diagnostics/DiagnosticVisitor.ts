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
import { getDeclResolveGensym, isMemoCall, MemoFunctionKind, RuntimeNames } from "../utils"
import { getName, isMemo, isMemoizable } from "../api-utils"
import { ScopedVisitor } from "./ScopedVisitor"
import { Reporter } from "./Reporter"
import { toArray } from "./ToArrayVisitor"

export class DiagnosticVisitor extends ScopedVisitor {
    constructor(functionTable: Map<arkts.KNativePointer, MemoFunctionKind>) {
        super(functionTable)
    }

    visitor(beforeChildren: arkts.AstNode): arkts.AstNode {
        this.enterScope(beforeChildren)
        const node = this.visitEachChild(beforeChildren)

        // Improve: check state mutation, panda issue 26718
        this.checkDefaultValueMemoCall(node)
        this.checkOutOfMemoContextMemoCall(node)
        this.checkMemoDeclarationIsExplicitlyTyped(node)
        this.checkParameterMutation(node)

        this.exitScope(beforeChildren)
        return node
    }

    private checkOutOfMemoContextMemoCall(node: arkts.AstNode): void {
        if (!arkts.isCallExpression(node)) return
        const callee = node.callee ?? arkts.throwError(`call expression has no callee`)
        const decl = getDeclResolveGensym(callee)
        if (!isMemoizable(decl)) return
        if (!isMemo(decl)) return
        if (this.isCurrentScopeMemo()) return
        const callName = getName(decl)
        const scopeName = this.currentScopeName()
        Reporter.reportOutOfContextMemoCall(callName, scopeName)
    }

    private checkDefaultValueMemoCall(node: arkts.AstNode): void {
        if (!arkts.isVariableDeclarator(node)) return
        if (!arkts.isIdentifier(node.id)) return
        if (!arkts.isConditionalExpression(node.init)) return
        if (node.init.test === undefined) return
        if (node.init.alternate === undefined) return
        const isGensym = (it: arkts.AstNode) =>
            arkts.isIdentifier(it) && it.name.includes(RuntimeNames.GENSYM)
        if (toArray(node.init.test).some(isGensym) && toArray(node.init.alternate).some(isMemoCall)) {
            Reporter.reportDefaultValueMemoCall(node.id.name)
        }
    }

    private checkMemoDeclarationIsExplicitlyTyped(node: arkts.AstNode): void {
        if (!arkts.isScriptFunction(node)) return
        const kind = this.scriptFunctions.get(node.originalPeer)
        if (kind === undefined) return
        if (kind === MemoFunctionKind.NONE) return
        if (node.returnTypeAnnotation !== undefined) return
        Reporter.reportMemoFunctionIsNotExplicitlyTyped(node?.id?.name)
    }

    private checkParameterMutation(node: arkts.AstNode): void {
        if (!arkts.isAssignmentExpression(node)) return
        if (!arkts.isIdentifier(node.left)) return
        const decl = arkts.getDecl(node.left)
        if (!arkts.isETSParameterExpression(decl)) return
        if (!this.isCurrentScopeMemo()) return

        Reporter.reportParameterReassignment(node.left.name, this.currentScopeName())
    }
}
