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
import { nullptr } from "@koalaui/interop"
import {
    CustomComponentNames,
    getCustomComponentOptionsName,
    createOptionalClassProperty
} from "./utils";
import {
    isAnnotation
} from "./common/arkts-utils";
import { hasDecorator, DecoratorNames } from "./property-translators/utils"
import { annotation } from "./common/arkts-utils";
import { backingField, expectName } from "./common/arkts-utils";
import { getStageManagmentType } from "./property-translators/utils";

export interface ComponentTransformerOptions {
    arkui?: string
}

type ScopeInfo = {
    name: string,
    isComponent?: boolean,
}

interface ComponentContext {
    componentNames: string[],
    structMembers: Map<string, arkts.AstNode[]>,
}

export class ComponentTransformer extends arkts.AbstractVisitor {
    private scopeInfos: ScopeInfo[] = [];
    private componentNames: string[] = [];
    private arkui?: string;
    private context: ComponentContext = { componentNames: [], structMembers: new Map() };

    constructor(options?: ComponentTransformerOptions) {
        const _options: ComponentTransformerOptions = options ?? {};
        super();
        this.arkui = _options.arkui;
    }

    enter(node: arkts.AstNode) {
        if (arkts.isETSStructDeclaration(node) && !!node.definition?.ident) {
            const scopeInfo: ScopeInfo = { name: node.definition.ident.name };
            node.definition.annotations.forEach((anno) => {
                scopeInfo.isComponent ||= isAnnotation(anno, DecoratorNames.COMPONENT)
            });
            this.scopeInfos.push(scopeInfo)
        }
    }

    exit(node: arkts.AstNode) {
        if (arkts.isETSStructDeclaration(node) || arkts.isClassDeclaration(node)) {
            if (!node.definition || !node.definition.ident || this.scopeInfos.length === 0) return;
            if (this.scopeInfos[this.scopeInfos.length - 1]?.name === node.definition.ident.name) {
                this.scopeInfos.pop();
            }
        }
    }

    isComponentStruct(): boolean {
        if (this.scopeInfos.length === 0) return false;
        const scopeInfo: ScopeInfo = this.scopeInfos[this.scopeInfos.length - 1];
        return !!scopeInfo.isComponent;
    }

    createImportDeclaration(): void {
        const source: arkts.StringLiteral = arkts.factory.createStringLiteral(
            this.arkui ?? CustomComponentNames.COMPONENT_DEFAULT_IMPORT
        );
        const imported: arkts.Identifier = arkts.factory.createIdentifier(
            CustomComponentNames.COMPONENT_CLASS_NAME, undefined
        );
        const importDecl: arkts.ETSImportDeclaration = arkts.factory.createETSImportDeclaration(
            source,
            [
                arkts.factory.createImportSpecifier(
                    imported,
                    imported
                )
            ],
            arkts.Es2pandaImportKinds.IMPORT_KINDS_TYPES,
            arkts.global.compilerContext.program,
            arkts.Es2pandaImportFlags.IMPORT_FLAGS_DEFAULT_IMPORT
        )
        // Insert this import at the top of the script's statements.
        arkts.importDeclarationInsert(importDecl)
        return
    }

    processEtsScript(node: arkts.ETSModule): arkts.ETSModule {
        if (this.componentNames.length === 0) {
            return node
        }

        this.createImportDeclaration()
        let updateStatements: arkts.AstNode[] = [];
        updateStatements.push(
            ...this.componentNames.map(
                name => arkts.factory.createInterfaceDeclaration(
                    [],
                    arkts.factory.createIdentifier(
                        getCustomComponentOptionsName(name), undefined
                    ),
                    undefined,
                    arkts.factory.createTSInterfaceBody(
                        this.context.structMembers.has(name)
                        ? this.context.structMembers.get(name)!
                        : []
                    ),
                    false,
                    false
                )
            )
        );
        if (updateStatements.length > 0) {
            return arkts.updateETSModuleByStatements(
                node,
                [
                    ...node.statements,
                    ...updateStatements,
                ]
            )
        }
        return node;
    }

    processComponent(node: arkts.ClassDeclaration | arkts.ETSStructDeclaration): arkts.ClassDeclaration | arkts.ETSStructDeclaration {
        const scopeInfo = this.scopeInfos[this.scopeInfos.length - 1];
        const className = node.definition?.ident?.name;
        if (!className || scopeInfo?.name !== className) {
            return node;
        }

        arkts.GlobalInfo.getInfoInstance().add(className);
        this.componentNames.push(className);

        const definition: arkts.ClassDefinition = node.definition
        const newDefinition = arkts.factory.updateClassDefinition(
            definition,
            definition.ident,
            undefined,
            undefined, // superTypeParams doen't work
            definition.implements,
            undefined,
            arkts.factory.createETSTypeReference(
                arkts.factory.createETSTypeReferencePart(
                    arkts.factory.createIdentifier(CustomComponentNames.COMPONENT_CLASS_NAME, undefined),
                    arkts.factory.createTSTypeParameterInstantiation(
                        [
                            arkts.factory.createETSTypeReference(
                                arkts.factory.createETSTypeReferencePart(
                                    arkts.factory.createIdentifier(className, undefined),
                                    undefined, undefined
                                )
                            ),
                            arkts.factory.createETSTypeReference(
                                arkts.factory.createETSTypeReferencePart(
                                    arkts.factory.createIdentifier(
                                        `${CustomComponentNames.COMPONENT_INTERFACE_PREFIX}${className}`, undefined
                                    ), undefined, undefined
                                )
                            ),
                        ]
                    ), undefined
                )
            ),
            definition.body,
            definition.modifiers,
            arkts.classDefinitionFlags(definition) | arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_FINAL | arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_EXPORT
        )

        if (arkts.isETSStructDeclaration(node)) {
            this.collectComponentMembers(node, className);
            const _node = arkts.factory.createClassDeclaration(newDefinition);
            _node.updateModifiers(node.modifierFlags);
            return _node;
        } else {
            return arkts.factory.updateClassDeclaration(
                node,
                newDefinition
            )
        }
    }

    collectComponentMembers(node: arkts.ETSStructDeclaration, className: string): void {
        if (!this.context.structMembers.has(className)) {
            this.context.structMembers.set(className, []);
        }
        node.definition?.body.map(it => {
            if (arkts.isClassProperty(it)) {
                this.context.structMembers.get(className)!.push(...this.createInterfaceInnerMember(it));
            }
        });
    }

    createInterfaceInnerMember(member: arkts.ClassProperty): arkts.ClassProperty[] {
        const originalName: string = expectName(member.key);
        const newName: string = backingField(originalName);
        const originMember: arkts.ClassProperty = createOptionalClassProperty(originalName, member,
            '', arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC);
        // Complete BS.
        if (member.annotations.length > 0 && !hasDecorator(member, DecoratorNames.BUILDER_PARAM)) {
            const newMember: arkts.ClassProperty = createOptionalClassProperty(newName, member,
                getStageManagmentType(member), arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC);
            return [originMember, newMember]
        }
        return [originMember];
    }

    visitor(node: arkts.AstNode): arkts.AstNode {
        this.enter(node);
        const newNode = this.visitEachChild(node)
        if (arkts.isETSModule(newNode)) {
            const updateNode = this.processEtsScript(newNode)
            this.exit(newNode)
            return updateNode
        }
        if (arkts.isETSStructDeclaration(newNode) && this.isComponentStruct()) {
            const updateNode = this.processComponent(newNode)
            this.exit(newNode)
            return updateNode
        }
        return newNode
    }
}
