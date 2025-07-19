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
import { fieldOf } from "./property-transformers"
import { annotation, backingField } from "./common/arkts-utils"
import { StructDescriptor, StructsResolver, StructTable } from "./struct-recorder";
import { DecoratorNames } from "./property-translators/utils";

export class StructCallRewriter extends arkts.AbstractVisitor {
    currentStructRewritten: StructDescriptor | undefined = undefined
    currentStructCalled: StructDescriptor | undefined = undefined
    isInCall = false

    constructor(private structs: StructTable, private importer: Importer) {
        super()
    }

    private addImports(statement: arkts.ETSImportDeclaration) {
        statement.specifiers.forEach(it => {
            const name = (it as arkts.ImportSpecifier).imported
            if (name && this.structs?.findStruct(name.name)) {
                this.importer.add(getCustomComponentOptionsName(name.name), statement.source?.str!)
            }
        })
    }

    visitor(node: arkts.AstNode, options?: object): arkts.AstNode {
        if (arkts.isETSImportDeclaration(node)) {
            this.addImports(node)
            return node
        }
        if (arkts.isETSStructDeclaration(node)) {
            const struct = StructTable.toDescriptor(node)
            this.currentStructRewritten = struct
            const result = this.visitEachChild(node)
            this.currentStructRewritten = undefined
            return result
        }
        if (arkts.isCallExpression(node) && arkts.isIdentifier(node.callee)) {
            this.isInCall = true
            this.currentStructCalled = this.structs.findStruct(node.callee.name)
            const result = this.visitEachChild(node)
            this.currentStructCalled = undefined
            this.isInCall = false
            return result
        }

        if (this.currentStructRewritten != undefined && this.isInCall && arkts.isObjectExpression(node)) {
            return this.createObjectLiteralRewrite(node)
        }
        return this.visitEachChild(node)
    }

    private createObjectLiteralRewrite(expression: arkts.ObjectExpression): arkts.Expression {
        const rewritten = arkts.factory.createObjectExpression(
            arkts.Es2pandaAstNodeType.AST_NODE_TYPE_OBJECT_EXPRESSION,
            expression.properties.map(value => {
                if (arkts.isProperty(value) && arkts.isIdentifier(value.value)) {
                    return arkts.factory.createProperty(
                        arkts.Es2pandaPropertyKind.PROPERTY_KIND_INIT,
                        value.key,
                        this.createDollarRewrite(value.value), false, false
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
        return rewritten
    }

    // Improve: FIX, move to checked phase
    private updateArrowFunctionExpression(targetPropertyNameId: arkts.Identifier, original: arkts.ArrowFunctionExpression): arkts.ArrowFunctionExpression {
        let targetPropertyName = targetPropertyNameId.name
        // Add @memo annotation if using @BuildParam decorated property
        let decorators = this.currentStructCalled?.decoratorsFor(targetPropertyName)
        if (decorators?.find(it => it == DecoratorNames.BUILDER_PARAM)) {
            original.setAnnotations([annotation(InternalAnnotations.MEMO)])
        }
        return original
    }

    private createMemberRewrite(original: arkts.MemberExpression): arkts.Expression {
        if (!this.currentStructRewritten) return original
        if (arkts.isThisExpression(original.object) && arkts.isIdentifier(original.property)) {
            let thisPropertyName = original.property.name
            // Use backing field instead of property value, if using property.
            let decorators = this.currentStructRewritten.decoratorsFor(thisPropertyName)
            if (decorators && decorators.includes(DecoratorNames.LINK)) {
                return fieldOf(arkts.factory.createThisExpression(), backingField(thisPropertyName))
            }
        }
        return original
    }

    private createDollarRewrite(original: arkts.Identifier): arkts.Expression {
        if (!this.currentStructRewritten) return original
        if (original.name.startsWith('$')) {
            let thisPropertyName = original.name.substring(1)
            // Use backing field instead of property value, if using property.
            let decorators = this.currentStructRewritten?.decoratorsFor(thisPropertyName)
            if (decorators && decorators.length > 0) {
                return fieldOf(arkts.factory.createThisExpression(), backingField(thisPropertyName))
            }
        }
        return original
    }
}