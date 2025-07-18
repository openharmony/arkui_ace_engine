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

import * as arkts from "@koalaui/libarkts"
import { ApplicationInfo, ComponentTransformerOptions } from "./component-transformer"
import { getComponentPackage, Importer } from "./utils"

export class CallTransformer extends arkts.AbstractVisitor {

    private applicationInfo?: ApplicationInfo
    private classNode?: arkts.ClassDeclaration
    private whiteList = ["$r", "$rawfile"]

    constructor(private imports: Importer, options?: ComponentTransformerOptions) {
        super()
        this.program = arkts.global.compilerContext.program
        this.applicationInfo = options?.applicationInfo
    }

    isDollarVariableAccess(identifier: arkts.Identifier): boolean {
        if (!this.classNode || !this.classNode.definition) return false
        const name = identifier.name
        // identifier name starts with $ and not with $r or $rawfile
        if (!name.startsWith("$")) return false
        if (this.whiteList.includes(name)) return false
        // the property is a member of the class
        const propName = name.substring(1)
        return this.classNode.definition.body
            .some(it => arkts.isClassProperty(it) && it.id?.name == propName)
    }

    transformDollarVariableAccess(node: arkts.Identifier): arkts.Expression {
        return arkts.factory.createMemberExpression(
            arkts.factory.createThisExpression(),
            arkts.factory.createIdentifier(node.name.substring(1)),
            arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_PROPERTY_ACCESS,
            false,
            false
        )
    }

    transformDollarCallExpression(callExpr: arkts.CallExpression): arkts.CallExpression {
        const name = (callExpr.callee as arkts.Identifier).name.replace('$', '_')
        // add import { _r, _rawfile } from "@ohos.arkui";
        this.imports.add(name, "@ohos.arkui")
        const args = callExpr.arguments.slice()
        return arkts.factory.updateCallExpression(
            callExpr,
            arkts.factory.createIdentifier(name),
            [
                arkts.factory.createStringLiteral(this.applicationInfo?.bundleName ?? ""),
                arkts.factory.createStringLiteral(this.applicationInfo?.moduleName ?? "entry"),
                ...args,
            ],
            callExpr.typeParams
        )
    }

    private componentsList = new Map<string, any>([
        [ "Column", { args: 1 } ],
        [ "Row",  { args: 1 } ],
        [ "List",  { args: 1 } ],
        [ "ListItem",  { args: 1 } ],
        [ "DatePicker",  { args: 1 } ],
        [ "Slider",  { args: 1 } ],
        [ "Tabs",  { args: 1 } ],
        [ "TextInput",  { args: 1 } ],
        [ "Toggle",  { args: 1 } ],
        [ "Progress",  { args: 1 } ],
        [ "Swiper",  { args: 1, options: "SwiperController" } ],
        [ "Grid",  { args: 2,  options: "GridLayoutOptions" } ],
        [ "GridItem",  { args: 1 } ],
        [ "Scroll",  { args: 1, options: "Scroller" } ],


    ])
    seenComponents = new Set<string>()

    transformComponentCallExpression(node: arkts.CallExpression, nameIdent: arkts.Identifier): arkts.CallExpression {
        const name = nameIdent.name
        const component = this.componentsList.get(name)
        if (!this.seenComponents.has(name)) {
            this.seenComponents.add(name)
            this.imports.add(component.options ?? `${name}Options`, getComponentPackage())
        }
        node = this.visitEachChild(node) as arkts.CallExpression
        return arkts.factory.createCallExpression(node.callee,
            this.insertUndefinedTillTrailing(node.arguments, component.args),
            node.typeParams,
            node.isOptional,
            node.hasTrailingComma,
            node.trailingBlock
        )
    }

    insertUndefinedTillTrailing(params: readonly arkts.Expression[], requestedParams: number): arkts.Expression[] {
        const result: arkts.Expression[] = []
        params.forEach(it => result.push(it))
        while (result.length < requestedParams) {
            result.push(arkts.factory.createUndefinedLiteral())
        }
        return result
    }

    visitor(node: arkts.AstNode): arkts.AstNode {
        if (arkts.isClassDeclaration(node)) {
            this.classNode = node
            const transformed = this.visitEachChild(node)
            this.classNode = undefined
            return transformed
        }
        if (arkts.isIdentifier(node)) {
            if (this.isDollarVariableAccess(node)) {
                return this.transformDollarVariableAccess(node)
            }
        } else if (arkts.isCallExpression(node) && arkts.isIdentifier(node.callee)) {
            // Ugly hack, until Panda 26224 is fixed.
            if (this.componentsList.get(node.callee.name)) {
                return this.transformComponentCallExpression(node, node.callee)
            }
            if (this.whiteList.includes(node.callee.name)) {
                return this.transformDollarCallExpression(node)
            }
        }
        return this.visitEachChild(node)
    }
}
