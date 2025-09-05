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

import { AnnotationUsage, ClassDefinition, ClassElement, Expression, isArrowFunctionExpression, isClassDefinition, isClassProperty, isETSFunctionType, isETSModule, isETSNewClassInstanceExpression, isScriptFunction, isTSEnumDeclaration, TSEnumDeclaration, TSEnumMember } from "src/generated";
import { AbstractVisitor } from "./AbstractVisitor";
import { AstNode } from "./peers/AstNode"
import { Es2pandaModifierFlags } from "src/generated/Es2pandaEnums";
import { factory } from "src/generated/factory";
import { arkts } from "src";
import { TypeAliasDeclaration } from "@koalaui/ets-tsc";

function filterAnnotations(annotations: AnnotationUsage[]): AnnotationUsage[] {
    return annotations.filter(it => it.baseName?.name != "OptionalParametersAnnotation")
}

export abstract class ContextAwareVisitor extends AbstractVisitor {
    private contextStack: ('global' | 'namespace')[] = ['global']
    protected get context() {
        return this.contextStack.at(-1)!
    }
    private enter(node:AstNode): () => void {
        if (isETSModule(node) && node.ident?.name !== 'ETSGLOBAL') {
            this.contextStack.push('namespace')
            return () => this.contextStack.pop()
        }
        if (isClassDefinition(node) && node.isNamespaceTransformed && node.ident?.name !== 'ETSGLOBAL') {
            this.contextStack.push('namespace')
            return () => this.contextStack.pop()
        }
        return () => {}
    }

    visitEachChild(node: AstNode, options?: object): AstNode {
        const leave = this.enter(node)
        const r = super.visitEachChild(node, options)
        leave()
        return r
    }
}

export class CheckedBackFilter extends ContextAwareVisitor {
    transformInitializer(node: Expression|undefined): Expression|undefined {
        if (node == undefined) return undefined
        if (!isETSNewClassInstanceExpression(node)) return node
        return node.arguments[1]
    }
    transformEnum(node: ClassDefinition): AstNode {
        return TSEnumDeclaration.create1TSEnumDeclaration(
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
            !!(node.modifierFlags & Es2pandaModifierFlags.MODIFIER_FLAGS_DECLARE) && this.context !== 'namespace'
        )
    }
    transformScopedClass(node:ClassDefinition): ClassDefinition {
        return ClassDefinition.createClassDefinition(
            node.ident,
            node.typeParams,
            node.superTypeParams,
            node.implements,
            node.ctor,
            node.super,
            node.body,
            node.modifiers,
            this.context === 'namespace'
                ? node.modifierFlags & (~Es2pandaModifierFlags.MODIFIER_FLAGS_DECLARE)
                : node.modifierFlags
        )
    }
    transformScopedEnum(node:TSEnumDeclaration): TSEnumDeclaration {
        return TSEnumDeclaration.create1TSEnumDeclaration(
            node.key,
            node.members,
            node.isConst,
            false,
            !!(node.modifierFlags & Es2pandaModifierFlags.MODIFIER_FLAGS_DECLARE) && this.context !== 'namespace'
        )
    }
    visitor(beforeChildren: AstNode): AstNode {
        const node = this.visitEachChild(beforeChildren)
        if (isTSEnumDeclaration(node)) {
            return this.transformScopedEnum(node)
        }
        if (isClassDefinition(node)) {
            if (node.isEnumTransformed) {
                return this.transformEnum(node)
            } else {
                const transformed = this.context === 'namespace'
                    ? this.transformScopedClass(node)
                    : node
                return transformed.setAnnotations(filterAnnotations([...node.annotations]))
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
