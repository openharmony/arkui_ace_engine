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
import { getDeclResolveGensym, getMemoFunctionKind, MemoFunctionKind } from "./utils"
import { getParams, isMemoAnnotatable, isMemoizable } from "./api-utils"

class AnalysisVisitorOptions {
    applyMemo?: MemoFunctionKind
}

function isSetter(node: arkts.ScriptFunction) {
    return node.flags & arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_SETTER
}

function isGetter(node: arkts.ScriptFunction) {
    return node.flags & arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_GETTER
}

export class AnalysisVisitor extends arkts.AbstractVisitor {
    // TODO: migrate to wrappers instead of pointers
    constructor(
        public scriptFunctions: Map<arkts.KNativePointer, MemoFunctionKind>,
        public ETSFunctionTypes: Map<arkts.KNativePointer, MemoFunctionKind>,
    ) {
        super()
    }

    visitor(node: arkts.BlockStatement, options?: AnalysisVisitorOptions): arkts.BlockStatement
    visitor(node: arkts.CallExpression, options?: AnalysisVisitorOptions): arkts.CallExpression
    visitor(node: arkts.Expression, options?: AnalysisVisitorOptions): arkts.Expression
    visitor(node: arkts.AstNode, options?: AnalysisVisitorOptions): arkts.AstNode {
        if (arkts.isScriptFunction(node)) {
            if (isSetter(node) || isGetter(node)) {
                return this.visitEachChild(node, { applyMemo: options?.applyMemo ? options?.applyMemo : getMemoFunctionKind(node) })
            }
            const kind = options?.applyMemo ? options?.applyMemo : getMemoFunctionKind(node)
            this.scriptFunctions.set(node.originalPeer, kind)
            return this.visitEachChild(node, { applyMemo: false })
        }
        if (arkts.isETSFunctionType(node)) {
            const kind = options?.applyMemo ? options?.applyMemo : getMemoFunctionKind(node)
            this.ETSFunctionTypes.set(node.originalPeer, kind)
            return this.visitEachChild(node, { applyMemo: false })
        }

        if (isMemoAnnotatable(node)) {
            return this.visitEachChild(node, { applyMemo: options?.applyMemo ? options?.applyMemo : getMemoFunctionKind(node) })
        }

        if (arkts.isCallExpression(node)) {
            const expr = node.callee
            const decl = getDeclResolveGensym(expr!)
            if (!isMemoizable(decl)) {
                return node
            }
            const params = getParams(decl)
            return arkts.factory.updateCallExpression(
                node,
                this.visitor(node.callee!, options),
                node.arguments.map((arg, index) => this.visitor(arg, { applyMemo: params[index] ? getMemoFunctionKind(params[index]) : undefined })),
                node.typeParams ? this.visitor(node.typeParams, options) as arkts.TSTypeParameterInstantiation : undefined,
                node.isOptional,
                node.hasTrailingComma,
                node.trailingBlock ? this.visitor(node.trailingBlock, options) : undefined,
            )
        }

        return this.visitEachChild(node, options)
    }
}
