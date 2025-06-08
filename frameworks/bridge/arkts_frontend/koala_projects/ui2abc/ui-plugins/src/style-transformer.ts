/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
import { builderLambdaFunctionName } from "./builder-lambda-transformer"
import { styledInstance } from "./utils"

export class StyleTransformer extends arkts.AbstractVisitor {
    visitor(beforeChildren: arkts.AstNode): arkts.AstNode {
        const node = this.visitEachChild(beforeChildren)
        const isCallChain = arkts.isCallExpression(node)
            && arkts.isMemberExpression(node.callee)
            && arkts.isCallExpression(node.callee.object)
        if (!isCallChain) {
            return node
        }
        const implFunction = builderLambdaFunctionName(node.callee.object)
        if (implFunction === undefined) {
            return node
        }
        return transformStyle(node, node.callee, node.callee.object, node.callee.object.arguments)
    }
}

function transformStyle(
    outerCall: arkts.CallExpression,
    dot: arkts.MemberExpression,
    innerCall: arkts.CallExpression,
    args: readonly arkts.Expression[]
): arkts.AstNode {
    const firstArg = args[0]
    const firstArgOrUndefined = arkts.isUndefinedLiteral(firstArg) ? undefined : firstArg
    const restArgs = args.slice(1)

    const newDot = arkts.factory.updateMemberExpression(
        dot,
        firstArgOrUndefined ?? arkts.factory.createIdentifier(styledInstance, undefined),
        dot.property,
        dot.kind,
        dot.isComputed,
        dot.isOptional
    )

    const detachedStyle = arkts.factory.updateCallExpression(
        outerCall,
        newDot,
        outerCall.arguments,
        outerCall.typeParams
    )

    return arkts.factory.updateCallExpression(
        innerCall,
        innerCall.callee,
        [detachedStyle, ...restArgs],
        innerCall.typeParams
    )
}
