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

import { nullptr } from "@koalaui/interop";
import * as arkts from "@koalaui/libarkts"
import { AbstractVisitor } from "./AbstractVisitor";

export interface ComponentTransformerOptions{
    arkui: string
}

export class ComponentTransformer extends AbstractVisitor {
    constructor(private options?: ComponentTransformerOptions) {
        super()
    }

    private context: { componentNames: string[] } = { componentNames: [] }

    isComponentStruct(node: arkts.StructDeclaration): boolean {
        // For now just rewrite any struct
        return true
    }

    createImportDeclaration() {
        return arkts.factory.createImportDeclaration(
            // TODO: es2panda has already resolved the "paths" section
            arkts.factory.create1StringLiteral(this.options?.arkui ?? '@ohos.arkui'),
            [
                arkts.factory.createImportSpecifier(
                    arkts.factory.createIdentifier('StructBase'),
                    nullptr // TODO: wtf
                )
            ],
            arkts.Es2pandaImportKinds.IMPORT_KINDS_TYPE,
            false
        )
    }

    processEtsScript(node: arkts.EtsScript): arkts.EtsScript {
        const interfaceDeclarations = this.context.componentNames.map(
            name => arkts.factory.createInterfaceDeclaration(
                [],
                arkts.factory.createIdentifier(`__Options_${name}`),
                nullptr, // TODO: wtf
                arkts.factory.createBlock([]),
                false,
                false
            )
        )
        return arkts.factory.updateEtsScript(
            node,
            [
                this.createImportDeclaration(),
                ...node.statements,
                ...interfaceDeclarations
            ]
        )
    }

    processComponent(node: arkts.ClassDeclaration | arkts.StructDeclaration): arkts.ClassDeclaration | arkts.StructDeclaration {
        const className = node.definition?.ident?.name
        if (!className) {
            throw "Non Empty className expected for Component"
        }
        arkts.GlobalInfo.getInfoInstance().add(className);
        this.context.componentNames.push(className)

        if (!node.definition) {
            return node
        }
        const newDefinition = arkts.factory.updateClassDefinition(
            node.definition,
            node.definition?.ident,
            undefined,
            undefined, // superTypeParams doen't work
            // arkts.factory.createTSTypeParameterInstantiation(
            //     [
            //         arkts.factory.createTypeReference(
            //             arkts.factory.createTypeReferencePart(
            //                 arkts.factory.createIdentifier("H")
            //             )
            //         ),
            //         arkts.factory.createTypeReferenceFromId(
            //             arkts.factory.createIdentifier(`__Options_${className}`)
            //         ),
            //     ]
            // ),
            node.definition?.implements,
            undefined,
            arkts.factory.createTypeReference(
                arkts.factory.createTypeReferencePart(
                    arkts.factory.createIdentifier('StructBase'),
                    arkts.factory.createTSTypeParameterInstantiation(
                        [
                            arkts.factory.createTypeReference(
                                arkts.factory.createTypeReferencePart(
                                    arkts.factory.createIdentifier(className)
                                )
                            ),
                            arkts.factory.createTypeReference(
                                arkts.factory.createTypeReferencePart(
                                    arkts.factory.createIdentifier(`__Options_${className}`)
                                )
                            ),
                        ]
                    )
                )
            ),
            node.definition?.body,
            node.definition?.modifiers,
            arkts.classDefinitionFlags(node.definition) | arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_FINAL
        )

        if (arkts.isStructDeclaration(node)) {
            return arkts.factory.createClassDeclaration(
                newDefinition
             )
        } else {
            return arkts.factory.updateClassDeclaration(
                node,
                newDefinition
            )
        }
    }

    visitor(node: arkts.AstNode): arkts.AstNode {
        const newNode = this.visitEachChild(node)
        if (arkts.isEtsScript(newNode)) {
            return this.processEtsScript(newNode)
        }
        if (arkts.isStructDeclaration(newNode) && this.isComponentStruct(newNode)) {
            return this.processComponent(newNode)
        }
        return newNode
    }
}
