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

import * as arkts from "@koalaui/libarkts"
import { MemoFunctionKind } from "../utils"

type ScopeInfo = {
    name?: string,
    isMemo: boolean
}

export abstract class ScopedVisitor extends arkts.AbstractVisitor {
    private scopes: ScopeInfo[] = []

    protected constructor(
        protected scriptFunctions: Map<arkts.KNativePointer, MemoFunctionKind>
    ) {
        super()
    }

    protected enterScope(node: arkts.AstNode): void {
        if (arkts.isScriptFunction(node)) {
            const name = node.id?.name
            const isMemo = this.scriptFunctions.get(node.originalPeer) !== MemoFunctionKind.NONE
            this.scopes.push({ name , isMemo })
        }
    }

    protected exitScope(node: arkts.AstNode): void {
        if (arkts.isScriptFunction(node)) {
            this.scopes.pop()
        }
    }

    protected isCurrentScopeMemo(): boolean {
        return this.scopes[this.scopes.length - 1]?.isMemo ?? false
    }

    protected currentScopeName(): string | undefined {
        return this.scopes[this.scopes.length - 1]?.name
    }
}
