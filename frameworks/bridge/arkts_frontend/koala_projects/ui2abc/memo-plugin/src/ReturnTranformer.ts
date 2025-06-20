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
import { isSyntheticReturnStatement } from "./utils"

/**
 * This transformer corrects function's body according to memo transformation
 */
export class ReturnTransformer extends arkts.AbstractVisitor {
    private skipNode?: arkts.ReturnStatement | arkts.BlockStatement
    private stableThis: boolean = false

    skip(syntheticReturnStatement?: arkts.ReturnStatement | arkts.BlockStatement): ReturnTransformer {
        this.skipNode = syntheticReturnStatement
        return this
    }

    rewriteThis(stableThis: boolean): ReturnTransformer {
        this.stableThis = stableThis
        return this
    }

    visitor(beforeChildren: arkts.AstNode): arkts.AstNode {
        // TODO: temporary checking skip nodes by comparison with expected skip nodes
        // Should be fixed when update procedure implemented properly
        if (/* beforeChildren === this.skipNode */ isSyntheticReturnStatement(beforeChildren)) {
            return beforeChildren
        }
        if (arkts.isScriptFunction(beforeChildren)) {
            return beforeChildren
        }
        const node = this.visitEachChild(beforeChildren)
        if (arkts.isReturnStatement(node)) {
            if (node.argument == undefined || arkts.isThisExpression(node.argument)) {
                return arkts.factory.createBlockStatement([
                    arkts.factory.createExpressionStatement(
                        factory.createRecacheCall()
                    ),
                    node
                ])
            }
            return arkts.factory.updateReturnStatement(node, factory.createRecacheCall(node.argument))
        }
        return node
    }
}
