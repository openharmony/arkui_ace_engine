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
import { getDeclResolveGensym, MemoFunctionKind } from "./utils"
import { getName, isMemo, isMemoizable, Memoizable } from "./api-utils"

type ScopeInfo = {
    name?: string,
    isMemo: boolean
}

export class DiagnosticVisitor extends arkts.AbstractVisitor {
    constructor(
        public scriptFunctions: Map<arkts.KNativePointer, MemoFunctionKind>,
    ) {
        super()
    }

    private scopes: ScopeInfo[] = []

    enter(node: arkts.AstNode) {
        if (arkts.isScriptFunction(node)) {
            const name = node.id?.name
            const isMemo = this.scriptFunctions.get(node.originalPeer) != MemoFunctionKind.NONE
            this.scopes.push({ name , isMemo })
        }
        return this
    }

    exit(node: arkts.AstNode) {
        if (arkts.isScriptFunction(node)) {
            this.scopes.pop()
        }
        return this
    }

    checkMemoCall(decl: Memoizable) {
        if (this.scopes[this.scopes.length - 1].isMemo === false) {
            if (this.scopes[this.scopes.length - 1].name) {
                console.error(`Attempt to call @memo-method ${getName(decl)} from non-@memo-method ${this.scopes[this.scopes.length - 1].name}`)
                throw "Invalid @memo usage"
            } else {
                console.error(`Attempt to call @memo-method ${getName(decl)} from anonymous non-@memo-method`)
                throw "Invalid @memo usage"
            }
        }
        return this
    }

    visitor(beforeChildren: arkts.AstNode): arkts.AstNode {
        this.enter(beforeChildren)
        const node = this.visitEachChild(beforeChildren)
        this.exit(beforeChildren)

        if (arkts.isCallExpression(node)) {
            const expr = node.callee
            const decl = getDeclResolveGensym(expr!)
            if (isMemoizable(decl) && isMemo(decl)) {
                this.checkMemoCall(decl)
            }
        }
        return node
    }
}
