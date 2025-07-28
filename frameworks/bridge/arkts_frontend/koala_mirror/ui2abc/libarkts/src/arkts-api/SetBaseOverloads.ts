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
import { ETSModule, isMethodDefinition, MethodDefinition } from "../generated"
import { AbstractVisitor } from "./AbstractVisitor"
import { AstNode } from "./peers/AstNode"

export class SetBaseOverloads extends AbstractVisitor {
    visitor(node: MethodDefinition, baseOverloadMethod?: MethodDefinition): MethodDefinition
    visitor(node: AstNode, baseOverloadMethod?: MethodDefinition): AstNode
    visitor(node: AstNode, baseOverloadMethod?: MethodDefinition): AstNode {
        if (isMethodDefinition(node)) {
            const result = factory.updateMethodDefinition(
                node,
                node.kind,
                node.key,
                node.value,
                node.modifierFlags,
                node.isComputed,
                node.overloads.map((it) => this.visitor(it, node)),
            )
            if (baseOverloadMethod) {
                result.setBaseOverloadMethod(baseOverloadMethod)
            }
            return result
        }
        return this.visitEachChild(node)
    }

    static instance?: SetBaseOverloads
}

export function setBaseOverloads(node: ETSModule) {
    if (!SetBaseOverloads.instance) {
        SetBaseOverloads.instance = new SetBaseOverloads()
    }
    SetBaseOverloads.instance.visitor(node)
}
