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

import { factory } from "./factory/nodeFactory"
import { BlockStatement, isReturnStatement, isScriptFunction, Program, ScriptFunction } from "../generated"
import { AbstractVisitor } from "./AbstractVisitor"
import { AstNode } from "./peers/AstNode"
import { Es2pandaPrimitiveType, Es2pandaScriptFunctionFlags } from "src/generated/Es2pandaEnums"

interface IsScriptFunctionRoot {
    isScriptFunctionRoot: boolean
}

// Improve: this is to workaround compiler not beeing able to infer return type on recheck
class CheckReturns extends AbstractVisitor {
    visitor(node: AstNode, options?: IsScriptFunctionRoot): AstNode {
        if (isReturnStatement(node) && node.argument !== undefined) {
            this.seenNonVoidReturn = true
        }
        if (isScriptFunction(node) && !options?.isScriptFunctionRoot) {
            return node
        }
        return this.visitEachChild(node)
    }

    seenNonVoidReturn: boolean = false
    static instance?: CheckReturns
}

// This function checks that it is possible to infer return type of script function as void
function checkReturns(node: AstNode): boolean {
    if (!CheckReturns.instance) {
        CheckReturns.instance = new CheckReturns()
    }
    CheckReturns.instance.seenNonVoidReturn = false
    CheckReturns.instance.visitor(node, { isScriptFunctionRoot: true })
    return CheckReturns.instance.seenNonVoidReturn == false
}

class InferVoidReturnType extends AbstractVisitor {
    visitor(node: BlockStatement): BlockStatement
    visitor(node: AstNode): AstNode {
        const result = this.visitEachChild(node)
        if (isScriptFunction(result) &&
            result.returnTypeAnnotation === undefined &&
            !result.isConstructor && // constructors should not have return type
            (result.flags & Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_SETTER) == 0 // setters should not return void
        ) {
            const isVoid = checkReturns(result)
            if (isVoid) {
                return factory.updateScriptFunction(
                    result,
                    result.body,
                    result.typeParams,
                    result.params,
                    factory.createETSPrimitiveType(
                        Es2pandaPrimitiveType.PRIMITIVE_TYPE_VOID,
                    ),
                    result.hasReceiver,
                    result.flags,
                    result.modifierFlags,
                    result.id,
                    result.annotations,
                )
            }
        }
        return result
    }
}

export function inferVoidReturnType(program: Program) {
    program.setAst(new InferVoidReturnType().visitor(program.ast))
}
