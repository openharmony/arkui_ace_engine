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
import { getCustomComponentOptionsName, Importer, InternalAnnotations } from "./utils"
import { fieldOf, isOptionBackedByPropertyName } from "./property-transformers"
import { annotation, backingField } from "./common/arkts-utils"
import { StructDescriptor, StructTable } from "./struct-recorder";
import { DecoratorNames } from "./property-translators/utils";

// For some time we execute this plugin on parrsed stage.
export class StructCallRewriter extends arkts.AbstractVisitor {
    currentStructRewritten: StructDescriptor | undefined = undefined
    currentStructCalled: StructDescriptor | undefined = undefined

    constructor(private importer: Importer, private structTable: StructTable) {
        super()
    }

    private addImports(statement: arkts.ETSImportDeclaration) {
        statement.specifiers.forEach(it => {
            const name = (it as arkts.ImportSpecifier).imported
            if (name && this.structTable.findStruct(name)) {
                this.importer.add(getCustomComponentOptionsName(name.name), statement.source?.str!)
            }
        })
    }

    visitor(node: arkts.AstNode, options?: object): arkts.AstNode {
        if (arkts.isETSImportDeclaration(node)) {
            this.addImports(node)
            return node
        }
        if (arkts.isClassDeclaration(node)) {
            const struct = this.structTable.findStruct(node.definition?.ident!)
            this.currentStructRewritten = struct
            const result = this.visitEachChild(node)
            this.currentStructRewritten = undefined
            return result
        }
        if (arkts.isCallExpression(node) && arkts.isIdentifier(node.callee)) {
            const struct = this.structTable.findStruct(node.callee as arkts.Identifier)
            let result: arkts.AstNode
            if (struct) {
                this.currentStructCalled = struct
                result = this.visitEachChild(node)
                this.currentStructCalled = undefined
            } else {
                result = this.visitEachChild(node)
            }
            return result
        }
        if (this.currentStructCalled != undefined && arkts.isObjectExpression(node)) {
            // Iterate over all statements to properly use fields getters
            return arkts.factory.createTSAsExpression(
                this.createObjectLiteralRewrite(node),
                arkts.factory.createTSTypeReference(arkts.factory.createIdentifier(
                    getCustomComponentOptionsName(this.currentStructCalled.name))),
                false
            )
        }
        return this.visitEachChild(node)
    }

    private createObjectLiteralRewrite(expression: arkts.ObjectExpression): arkts.ObjectExpression {
        return arkts.factory.createObjectExpression(
            arkts.Es2pandaAstNodeType.AST_NODE_TYPE_OBJECT_EXPRESSION,
            expression.properties.map(value => {
                if (arkts.isProperty(value) && arkts.isMemberExpression(value.value)) {
                    return arkts.factory.createProperty(
                        arkts.Es2pandaPropertyKind.PROPERTY_KIND_INIT,
                        value.key,
                        this.createMemberRewrite(value.key as arkts.Identifier, value.value), false, false
                    )
                } else if (arkts.isProperty(value) && arkts.isIdentifier(value.value)) {
                    return arkts.factory.createProperty(
                        arkts.Es2pandaPropertyKind.PROPERTY_KIND_INIT,
                        value.key,
                        this.createDollarRewrite(value.key as arkts.Identifier, value.value), false, false
                    )
                } else if (arkts.isProperty(value) && arkts.isArrowFunctionExpression(value.value)) {
                    return arkts.factory.createProperty(
                        arkts.Es2pandaPropertyKind.PROPERTY_KIND_INIT,
                        value.key,
                        this.updateArrowFunctionExpression(value.key as arkts.Identifier, value.value), false, false
                    )
                } else {
                    return value
                }
            }), false
        )
    }

    private createMemberRewrite(targetPropertyNameId: arkts.Identifier, original: arkts.MemberExpression): arkts.Expression {
        if (!this.currentStructRewritten) return original
        if (arkts.isThisExpression(original.object) && arkts.isIdentifier(original.property)) {
            let thisPropertyName = original.property.name
            let targetPropertyName = targetPropertyNameId.name
            // Use backing field instead of property value, if using property.
            let decorators = this.currentStructCalled?.decoratorsFor(targetPropertyName)
            if (decorators?.find(it => isOptionBackedByPropertyName(it))) {
                return fieldOf(arkts.factory.createThisExpression(), backingField(thisPropertyName))
            }
        }
        return original
    }

    private createDollarRewrite(targetPropertyNameId: arkts.Identifier, original: arkts.Identifier): arkts.Expression {
        if (!this.currentStructRewritten) return original
        if (original.name.startsWith('$')) {
            let targetPropertyName = targetPropertyNameId.name
            let thisPropertyName = original.name.substring(1)
            // Use backing field instead of property value, if using property.
            let decorators = this.currentStructCalled?.decoratorsFor(targetPropertyName)
            if (decorators?.find(it => isOptionBackedByPropertyName(it))) {
                return fieldOf(arkts.factory.createThisExpression(), backingField(thisPropertyName))
            }
        }
        return original
    }

    private updateArrowFunctionExpression(targetPropertyNameId: arkts.Identifier, original: arkts.ArrowFunctionExpression): arkts.ArrowFunctionExpression {
        if (!this.currentStructRewritten) return original
        let targetPropertyName = targetPropertyNameId.name
        // Add @memo annotation if using @BuildParam decorated property
        let decorators = this.currentStructCalled?.decoratorsFor(targetPropertyName)
        if (decorators?.find(it => it == DecoratorNames.BUILDER_PARAM)) {
            original.setAnnotations([annotation(InternalAnnotations.MEMO)])
        }
        return original
    }
}
