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

import * as arkts from "../../../../../src/arkts-api"
import * as fs from 'fs'

class AddOptionalChain extends arkts.AbstractVisitor {
    visitor(beforeChildren: arkts.AstNode): arkts.AstNode {
        const node = this.visitEachChild(beforeChildren)
        if (arkts.isVariableDeclarator(node) && arkts.isIdentifier(node.id) && node.id.name == "zzz") {
            return arkts.factory.updateVariableDeclarator(
                node,
                node.flag,
                node.id,
                arkts.factory.createChainExpression(
                    arkts.factory.createMemberExpression(

                        arkts.factory.createIdentifier("x"),
                        arkts.factory.createIdentifier("y"),
                        arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_PROPERTY_ACCESS,
                        false,
                        false
                    )
                )

            )
        }
        return node
    }
}

export function addOptionalChain(program: arkts.Program) {
    const inserted = (new AddOptionalChain()).visitor(program.astNode)
    const result = (new arkts.ChainExpressionFilter()).visitor(inserted)
    return result
}
