/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

import * as ts from '@koalaui/ets-tsc'
import { AbstractVisitor } from './AbstractVisitor'
import { Importer } from './Importer'
import { isDefined } from "./utils";

/**
 TODO:
   This is really a workaround to the entry point problem.
   I really hope we will be able to throw away this transformer.
   We should not rewrite anything outside the UI code realm. :-(
 */

/**
 * Rewrites
 *   import { Ability } from "@kit.AbilityKit"
 * to
 *   import { ArkoalaAbility as Ability } from "@koalaui/arkoala-arkui";
 */
export class AbilityTransformer extends AbstractVisitor {
    constructor(
        sourceFile: ts.SourceFile,
        ctx: ts.TransformationContext,
        private importer: Importer
    ) {
        super(sourceFile, ctx)
    }

    private readonly defaultExportModules = ["@ohos.app.ability.UIAbility", "@ohos.app.ability.Ability"]
    private readonly namedExportModules = ["@kit.AbilityKit"]

    private isNamedRewriteModule(node: ts.ImportDeclaration): boolean {
        if (!ts.isStringLiteral(node.moduleSpecifier)) return false
        return this.namedExportModules.includes(node.moduleSpecifier.text)
    }

    private isDefaultRewriteModule(node: ts.ImportDeclaration): boolean {
        if (!ts.isStringLiteral(node.moduleSpecifier)) return false
        return this.defaultExportModules.includes(node.moduleSpecifier.text)
    }

    private isAbilityIdentifier(node: ts.Identifier | undefined): boolean {
        if (node === undefined) return false
        return ts.idText(node) === "UIAbility" || ts.idText(node) === "default"
    }

    private createArkoalaAbilityImport(alias: ts.Identifier): ts.ImportDeclaration {
        return ts.factory.createImportDeclaration(
            [],
            ts.factory.createImportClause(
                false,
                undefined,
                ts.factory.createNamedImports([
                    ts.factory.createImportSpecifier(
                        false,
                        ts.factory.createIdentifier("ArkoalaAbility"),
                        alias
                    )
                ])
            ),
            ts.factory.createStringLiteral("@koalaui/arkoala-arkui"),
            undefined
        )
    }

    visitor(node: ts.Node): ts.Node {
        if (!this.importer.isArkoala()) return node

        if (ts.isSourceFile(node) && !this.containsArkoalaAbility(node)) {
            return this.rewriteSourceFile(node)
        }

        return this.visitEachChild(node)
    }

    private rewriteSourceFile(node: ts.SourceFile): ts.SourceFile {
        return ts.factory.updateSourceFile(
            node,
            node.statements
                .map(it =>
                    ts.isImportDeclaration(it)
                        ? this.rewriteImport(it)
                        : it
                )
                .flat()
        )
    }

    private rewriteImport(node: ts.ImportDeclaration): ts.ImportDeclaration[] {
        if (this.isDefaultRewriteModule(node)) {
            const alias = node?.importClause?.name
            if (alias === undefined) {
                /*
                  import { default as ... } from ...
                 */
                return this.splitImport(node)
            }

            const namedBindings = node?.importClause?.namedBindings
            const importSpecifiers =
                namedBindings !== undefined && ts.isNamedImports(namedBindings)
                    ? namedBindings.elements
                    : []

            return [
                ts.factory.updateImportDeclaration(
                    node,
                    node.modifiers,
                    ts.factory.createImportClause(
                        false,
                        undefined,
                        ts.factory.createNamedImports(
                            importSpecifiers
                        )
                    ),
                    node.moduleSpecifier,
                    node.assertClause
                ),
                this.createArkoalaAbilityImport(alias)
            ]
        }
        if (this.isNamedRewriteModule(node)) {
            return this.splitImport(node)
        }
        return [node]
    }

    private splitImport(node: ts.ImportDeclaration): ts.ImportDeclaration[] {
        const namedBindings = node?.importClause?.namedBindings
        if (namedBindings === undefined || !ts.isNamedImports(namedBindings)) return [node]

        const ability = namedBindings.elements
            .find(it => this.isAbilityIdentifier(this.getOriginalEntity(it)))
        if (ability === undefined) return [node]

        return [
            ts.factory.updateImportDeclaration(
                node,
                node.modifiers,
                ts.factory.createImportClause(
                    false,
                    undefined,
                    ts.factory.createNamedImports(
                        namedBindings.elements.filter(it => it !== ability)
                    )
                ),
                node.moduleSpecifier,
                node.assertClause
            ),
            this.createArkoalaAbilityImport(ability.name)
        ]
    }

    private containsArkoalaAbility(node: ts.SourceFile): boolean {
        return node.statements
            .filter(ts.isClassDeclaration)
            .map(it => it.name)
            .filter(isDefined)
            .some(it => ts.idText(it) === "ArkoalaAbility")
    }

    private getOriginalEntity(node: ts.ImportSpecifier): ts.Identifier {
        if (node.propertyName === undefined) return node.name
        return node.propertyName
    }
}

