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
import { MemoFunctionKind } from "./utils"

export class SignatureTransformer extends arkts.AbstractVisitor {
    public modified = false

    constructor(
        public scriptFunctions: Map<arkts.KNativePointer, MemoFunctionKind>,
        public ETSFunctionTypes: Map<arkts.KNativePointer, MemoFunctionKind>,
    ) {
        super()
    }

    visitor(node: arkts.ScriptFunction): arkts.ScriptFunction
    visitor(node: arkts.ETSFunctionType): arkts.ETSFunctionType
    visitor(node: arkts.AstNode): arkts.AstNode {
        if (arkts.isScriptFunction(node)) {
            const memo = this.scriptFunctions.get(node.originalPeer)
            const shouldTransform = memo == MemoFunctionKind.MEMO || memo == MemoFunctionKind.INTRINSIC
            if (shouldTransform) {
                this.modified = true
            }
            return arkts.factory.updateScriptFunction(
                node,
                node.body,
                node.typeParams,
                [...(shouldTransform ? factory.createHiddenParameters() : []), ...node.params],
                node.returnTypeAnnotation
                    ? node.returnTypeAnnotation
                    : shouldTransform
                        ? arkts.factory.createETSPrimitiveType(arkts.Es2pandaPrimitiveType.PRIMITIVE_TYPE_VOID)
                        : undefined,
                node.hasReceiver,
                node.flags,
                node.modifierFlags,
                node.id,
                node.annotations
            )
        }
        if (arkts.isETSFunctionType(node)) {
            const memo = this.ETSFunctionTypes.get(node.originalPeer)
            if (memo) {
                this.modified = true
            }
            return arkts.factory.updateETSFunctionType(
                node,
                undefined,
                [...(memo ? factory.createHiddenParameters() : []), ...node.params],
                node.returnType,
                false,
                arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_ARROW,
                node.annotations,
            )
        }

        return this.visitEachChild(node)
    }
}
