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
import { isMethodDefinition } from "../generated"
import { AbstractVisitor } from "./AbstractVisitor"
import { AstNode } from "./peers/AstNode"

export class SetBaseOverloads extends AbstractVisitor {
    visitor(node: AstNode): AstNode {
        if (isMethodDefinition(node)) {
            const baseOverloadMethod = node
            return factory.updateMethodDefinition(
                node,
                node.kind,
                node.key,
                node.value,
                node.modifierFlags,
                node.isComputed,
                node.overloads.map((it) => {
                    it.setBaseOverloadMethod(baseOverloadMethod)
                    return it
                })
            )
        }
        return this.visitEachChild(node)
    }
}

export function setBaseOverloads(node: AstNode) {
    new SetBaseOverloads().visitor(node)
}
