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
import { RuntimeNames, PositionalIdTracker } from "./utils"

export class InternalsTransformer extends arkts.AbstractVisitor {
    constructor(private positionalIdTracker: PositionalIdTracker) {
        super()
    }

    visitor(beforeChildren: arkts.AstNode): arkts.AstNode {
        const node = this.visitEachChild(beforeChildren)
        if (arkts.isCallExpression(node)) {
            if (arkts.isIdentifier(node.callee)) {
                if (node.callee.name == RuntimeNames.__CONTEXT) {
                    return arkts.factory.createIdentifier(
                        RuntimeNames.CONTEXT,
                        undefined
                    )
                }
                if (node.callee.name == RuntimeNames.__ID) {
                    return arkts.factory.createIdentifier(
                        RuntimeNames.ID,
                        undefined
                    )
                }
                if (node.callee.name == RuntimeNames.__KEY) {
                    return this.positionalIdTracker.id(RuntimeNames.__KEY)
                }
            }
        }
        return node
    }
}
