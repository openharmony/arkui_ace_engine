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

import { AnnotationUsage, ClassDefinition, ClassElement, ClassProperty, Expression, TSEnumDeclaration, TSEnumMember, isArrowFunctionExpression, isCallExpression, isClassDeclaration, isClassDefinition, isClassProperty, isETSFunctionType, isETSNewClassInstanceExpression, isETSParameterExpression, isIdentifier, isScriptFunction, isTSTypeAliasDeclaration, isVariableDeclaration } from "src/generated";
import { AbstractVisitor } from "./AbstractVisitor";
import { AstNode } from "./peers/AstNode"
import { Es2pandaModifierFlags } from "src/generated/Es2pandaEnums";
import { factory } from "src/generated/factory";

function filterAnnotations(annotations: AnnotationUsage[]): AnnotationUsage[] {
    return annotations.filter(it => it.baseName?.name != "OptionalParametersAnnotation")
}

export class CheckedBackFilter extends AbstractVisitor {
    transformInitializer(node: Expression|undefined): Expression|undefined {
        if (node == undefined) return undefined
        if (!isETSNewClassInstanceExpression(node)) return node
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
        if (isClassDefinition(node)) {
            if (node.isEnumTransformed) {
                return this.transformEnum(node)
            } else {
                return node.setAnnotations(filterAnnotations([...node.annotations]))
            }
        }
        if (isClassProperty(node)) {
            return node.setAnnotations(filterAnnotations([...node.annotations]))
        }
        if (isArrowFunctionExpression(node)) {
            return node.setAnnotations(filterAnnotations([...node.annotations]))
        }
        if (isETSFunctionType(node)) {
            return node.setAnnotations(filterAnnotations([...node.annotations]))
        }
        if (isScriptFunction(node)) {
            return node.setAnnotations(filterAnnotations([...node.annotations]))
        }
       
        return node
    }
}
