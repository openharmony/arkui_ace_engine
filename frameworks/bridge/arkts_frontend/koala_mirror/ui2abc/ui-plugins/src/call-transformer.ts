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
import { ApplicationInfo, ComponentTransformerOptions, ProjectConfig } from "./component-transformer"
import { getResourcePackage, Importer } from "./utils"
import { Dollars, getResourceParams, initResourceInfo, loadBuildJson, LoaderJson, ModuleType, RESOURCE_TYPE, ResourceInfo, ResourceParameter } from "./resources-utils"

export class CallTransformer extends arkts.AbstractVisitor {

    private applicationInfo?: ApplicationInfo
    private projectConfig?: ProjectConfig
    private classNode?: arkts.ClassDeclaration
    private whiteList = ["$r", "$rawfile"]

    private resourceInfo: ResourceInfo
    private aceBuildJson: LoaderJson

    constructor(private imports: Importer, options?: ComponentTransformerOptions, projectConfig?: ProjectConfig) {
        super()
        this.program = arkts.global.compilerContext!.program
        this.applicationInfo = options?.applicationInfo
        this.projectConfig = projectConfig

        this.aceBuildJson = loadBuildJson(this.projectConfig);
        this.resourceInfo = initResourceInfo(this.projectConfig, this.aceBuildJson);
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

    transformDollarCallExpression(node: arkts.CallExpression): arkts.CallExpression {

        if (!arkts.isIdentifier(node.callee) || !this.projectConfig) {
            return this.updateResourceCallDefault(node) // TODO: rework
        }

        const resourceKind: Dollars = node.callee.name as Dollars;
        const transformedKey: string = resourceKind === Dollars.DOLLAR_RESOURCE
                ? Dollars.TRANSFORM_DOLLAR_RESOURCE
                : Dollars.TRANSFORM_DOLLAR_RAWFILE;

        // add import { _r, _rawfile } from "arkui.component.resources";
        this.imports.add(transformedKey, getResourcePackage())

        if (arkts.isStringLiteral(node.arguments[0])) {
            return this.updateStringLiteralResource(
                node,
                this.projectConfig,
                resourceKind,
                transformedKey,
                node.arguments[0]
            )          
        } else if (node.arguments && node.arguments.length) {
            const resourceParams: ResourceParameter = getResourceParams(-1, resourceKind === Dollars.DOLLAR_RAWFILE ? RESOURCE_TYPE.rawfile : -1, Array.from(node.arguments))
            this.updateResourceCall(
                node,
                resourceParams,
                this.projectConfig,
                transformedKey
            )
        }
        return node;
    }

    updateStringLiteralResource(
        node: arkts.CallExpression,
        projectConfig: ProjectConfig,
        resourceKind: Dollars,
        transformedKey: string,
        arg: arkts.StringLiteral
    ): arkts.CallExpression {
        const resourceData: string[] = arg.str.trim().split('.');
        const fromOtherModule: boolean = !!resourceData.length && /^\[.*\]$/g.test(resourceData[0]);
        if (resourceKind === Dollars.DOLLAR_RAWFILE) {
            let resourceId: number = projectConfig.moduleType === ModuleType.HAR ? -1 : 0;
            if (resourceData && resourceData[0] && fromOtherModule) {
                resourceId = -1;
            }

            const resourceParams: ResourceParameter = getResourceParams(resourceId, RESOURCE_TYPE.rawfile, [node.arguments[0]])
            return this.updateResourceCall(
                node,
                resourceParams,
                projectConfig,
                transformedKey
            )
        } else {
            const resourceId: number =
                projectConfig.moduleType === ModuleType.HAR ||
                fromOtherModule ||
                !this.resourceInfo.resourcesList[resourceData[0]]
                    ? -1
                    : this.resourceInfo.resourcesList[resourceData[0]].get(resourceData[1])![resourceData[2]];

            const resourceParams: ResourceParameter = getResourceParams(
                resourceId,
                RESOURCE_TYPE[resourceData[1].trim()],
                projectConfig.moduleType === ModuleType.HAR || fromOtherModule
                    ? Array.from(node.arguments)
                    : Array.from(node.arguments.slice(1))
            )

            return this.updateResourceCall(
                node,
                resourceParams,
                projectConfig,
                transformedKey
            )
            
        }
    }

    updateResourceCall(
        node: arkts.CallExpression,
        resourceParams: ResourceParameter,
        projectConfig: ProjectConfig,
        transformedKey: string
    ): arkts.CallExpression {

        const args = [
            arkts.factory.createNumberLiteral(resourceParams.id),
            arkts.factory.createNumberLiteral(resourceParams.type),
            arkts.factory.createStringLiteral(projectConfig.bundleName ?? ""),
            arkts.factory.createStringLiteral(projectConfig.moduleName ?? "entry"),
            ...resourceParams.params,
        ];
        return arkts.factory.updateCallExpression(
            node,
            arkts.factory.createIdentifier(transformedKey),
            args,
            node.typeParams
        );  
    }

    // Use from rri. Maybe remove.
    updateResourceCallDefault(node: arkts.CallExpression) {
        const name = (node.callee as arkts.Identifier).name.replace('$', '_')
        // add import { _r, _rawfile } from "@ohos.arkui";
        this.imports.add(name, getResourcePackage())
        const args = node.arguments.slice()
        return arkts.factory.updateCallExpression(
            node,
            arkts.factory.createIdentifier(name),
            [
                arkts.factory.createStringLiteral(this.applicationInfo?.bundleName ?? ""),
                arkts.factory.createStringLiteral(this.applicationInfo?.moduleName ?? "entry"),
                ...args,
            ],
            node.typeParams
        )
    }

    private componentsList = new Map<string, any>([
        [ "Column", { args: 1 } ],
        [ "Row",  { args: 1 } ],
        [ "Stack",  { args: 1 } ],
        [ "List",  { args: 1 } ],
        [ "ListItem",  { args: 1 } ],
        [ "ListItemGroup", { args: 1 } ],
        [ "DatePicker",  { args: 1 } ],
        [ "Slider",  { args: 1 } ],
        [ "Tabs",  { args: 1 } ],
        [ "Text", { args: 2 } ],
        [ "TextInput",  { args: 1 } ],
        [ "Toggle",  { args: 1 } ],
        [ "Progress",  { args: 1 } ],
        [ "Swiper",  { args: 1 } ],
        [ "Grid",  { args: 2 } ],
        [ "GridCol",  { args: 1 } ],
        [ "GridRow",  { args: 1 } ],
        [ "GridItem",  { args: 1 } ],
        [ "Scroll",  { args: 1 } ],
        [ "Button", { args: 2 } ],
        [ "Image", { args: 2 } ],
        [ "Flex", { args: 1 } ],
        [ "MenuItem", { args: 1 } ],
        [ "MenuItemGroup", { args: 1 } ],
        [ "WaterFlow", { args: 1 } ],


    ])

    transformComponentCallExpression(node: arkts.CallExpression, nameIdent: arkts.Identifier): arkts.CallExpression {
        const name = nameIdent.name
        const component = this.componentsList.get(name)
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
