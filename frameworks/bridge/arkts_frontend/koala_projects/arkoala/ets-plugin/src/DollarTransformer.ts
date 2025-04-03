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

import * as ts from "@koalaui/ets-tsc"
import { AbstractVisitor } from "./AbstractVisitor";
import { NameTable } from "./utils";
import { Importer } from "./Importer";

export interface ApplicationInfo {
    bundleName: string,
    moduleName: string
}

export class DollarTransformer extends AbstractVisitor {
    constructor(
        sourceFile: ts.SourceFile,
        ctx: ts.TransformationContext,
        private nameTable: NameTable,
        private importer: Importer,
        private applicationInfo?: ApplicationInfo
    ) {
        super(sourceFile, ctx)
    }

    currentStruct: ts.StructDeclaration | undefined = undefined

    whiteList = ["$$", "$r", "$rawfile"]

    isDollarVariableAccess(node: ts.Identifier): boolean {
        const name = ts.idText(node)
        if (!name.startsWith("$")) return false
        const fieldName = name.substring(1)
        // TODO: is it correct?
        //  The white list has a preference over the fields.
        if (this.whiteList.includes(name)) return false
        if (!this.currentStruct) return false
        if (this.currentStruct.members.find(it => (
            it.name &&
            ts.isIdentifier(it.name) &&
            ts.idText(it.name) == fieldName
        )) == undefined) return false
        // Already has a receiver.
        if (ts.isPropertyAccessExpression(node.parent)) return false

        return true
    }

    transformDollarVariableAccess(node: ts.Identifier): ts.Expression {
        this.nameTable.dollars.push(ts.idText(node))
        return ts.factory.createPropertyAccessExpression(
            ts.factory.createThis(),
            node
        )
    }

    transformDollarCallExpression(node: ts.CallExpression): ts.CallExpression {
        const name = ts.idText(node.expression as ts.Identifier).replace('$', '_')

        const args = node.arguments.slice()

        args.unshift(
            ts.factory.createStringLiteral(this.applicationInfo?.bundleName ?? ""),
            ts.factory.createStringLiteral(this.applicationInfo?.moduleName ?? "entry")
        )

        return ts.factory.updateCallExpression(
            node,
            ts.factory.createIdentifier(this.importer.withAdaptorImport(name)),
            node.typeArguments,
            args
        )

    }

    visitor(node: ts.Node): ts.Node {
        if (ts.isCallExpression(node) && ts.isIdentifier(node.expression)) {
            if (this.whiteList.includes(ts.idText(node.expression))) {
                return this.transformDollarCallExpression(node)
            }
        }
        if (ts.isStruct(node)) {
            this.currentStruct = node
            const transformed = this.visitEachChild(node)
            this.currentStruct = undefined
            return transformed
        } else if (ts.isIdentifier(node)) {
            if (this.currentStruct && this.isDollarVariableAccess(node)) {
                return this.transformDollarVariableAccess(node)
            }
        }
        return this.visitEachChild(node)
    }
}