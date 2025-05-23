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

import { ClassDefinition, ClassElement, ClassProperty, Es2pandaModifierFlags, Expression, TSEnumDeclaration, TSEnumMember, asString, factory, isCallExpression, isClassDeclaration, isClassDefinition, isClassProperty, isETSNewClassInstanceExpression } from "./index";
import { AbstractVisitor } from "./AbstractVisitor";
import { AstNode } from "./peers/AstNode"


export class CheckedBackFilter extends AbstractVisitor {
    transformInitializer(node: Expression|undefined): Expression|undefined {
        if (node == undefined) return undefined
        if (!isETSNewClassInstanceExpression(node)) return node
        // new ZZZ(ordinal, value) !-> value
        return node.arguments[1]
    }
    transformEnum(node: ClassDefinition): AstNode {
        return TSEnumDeclaration.createTSEnumDeclaration(
            node.ident,
            node.body.map(it => {
                const member: ClassElement = it as ClassElement
                if (!isClassProperty(member)) return undefined
                if (isClassProperty(member) && member.id?.name.startsWith("#")) return undefined
                return factory.createTSEnumMember(
                    member.key,
                    this.transformInitializer(member.value),
                    false
                )
            }).filter(it => it != undefined) as TSEnumMember[],
            false,
            false,
            !!(node.modifierFlags & Es2pandaModifierFlags.MODIFIER_FLAGS_DECLARE)
        )
    }
    visitor(beforeChildren: AstNode): AstNode {
        const node = this.visitEachChild(beforeChildren)
        if (isClassDefinition(node) && node.isEnumTransformed) {
            return this.transformEnum(node)
        }
        return node
    }
}