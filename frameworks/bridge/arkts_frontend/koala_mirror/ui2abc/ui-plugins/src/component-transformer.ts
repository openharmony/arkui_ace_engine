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
import {
    CustomComponentNames,
    getCustomComponentOptionsName,
    Importer,
    InternalAnnotations
} from "./utils";
import { BuilderParamTransformer, ConsumeTransformer, LinkTransformer, LocalStorageLinkTransformer, LocalStoragePropTransformer, ObjectLinkTransformer, PropertyTransformer, PropTransformer, ProvideTransformer, StateTransformer, StorageLinkTransformer, StoragePropTransformer, PlainPropertyTransformer, fieldOf, isOptionBackedByProperty, isOptionBackedByPropertyName } from "./property-transformers";
import { annotation, backingField, isAnnotation } from "./common/arkts-utils";
import { DecoratorNames, DecoratorParameters, hasDecorator } from "./property-translators/utils";
import {
    factory
} from "./ui-factory"
import { StructDescriptor, StructTable } from "./struct-recorder";

export interface ApplicationInfo {
    bundleName: string,
    moduleName: string
}

export interface ComponentTransformerOptions {
    arkui?: string
    applicationInfo?: ApplicationInfo
}

function computeOptionsName(clazz: arkts.ClassDeclaration): string {
    return clazz.definition?.typeParams?.params?.[1]?.name?.name ??
        getCustomComponentOptionsName(clazz.definition?.ident?.name!)
}

export class ComponentTransformer extends arkts.AbstractVisitor {
    private arkuiImport?: string

    constructor(private imports: Importer, options?: ComponentTransformerOptions) {
        super()
        this.arkuiImport = options?.arkui
    }

    private transformStatements(statements: readonly arkts.Statement[]): arkts.Statement[] {
        let result: arkts.Statement[] = []
        this.parseEntryParameter(statements)
        this.imports.add(
            CustomComponentNames.COMPONENT_CLASS_NAME,
            this.arkuiImport ?? CustomComponentNames.COMPONENT_DEFAULT_IMPORT)
        this.imports.add(InternalAnnotations.MEMO, "@koalaui/runtime/annotations")
        this.propertyTransformers.forEach(it => it.collectImports(this.imports))
        statements.forEach(statement => {
            if (arkts.isETSStructDeclaration(statement)) {
                this.rewriteStruct(statement, result)
            } else {
                result.push(statement)
            }
        })
        return result
    }

    private rewriteModule(node: arkts.ETSModule): arkts.ETSModule {
        return arkts.updateETSModuleByStatements(node, this.transformStatements(node.statements))
    }

    private optionsName(clazz: arkts.ClassDefinition): arkts.Identifier {
        return arkts.factory.createIdentifier(getCustomComponentOptionsName(clazz.ident!.name))
    }

    private rewriteStructToOptions(node: arkts.ETSStructDeclaration): arkts.TSInterfaceDeclaration {
        return arkts.factory.createInterfaceDeclaration(
            [],
            this.optionsName(node.definition!),
            undefined,
            arkts.factory.createTSInterfaceBody(this.rewriteOptionsBody(node)),
            false,
            false,
            arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_EXPORT,
        )
    }

    private rewriteOptionsBody(node: arkts.ETSStructDeclaration): arkts.Statement[] {
        let result: arkts.Statement[] = []
        forEachProperty(node, property => {
            this.getPropertyTransformer(property).applyOptions(property, result)
        })
        return result
    }

    private rewriteStructToClass(node: arkts.ETSStructDeclaration): arkts.ClassDeclaration {
        return arkts.factory.createClassDeclaration(
            arkts.factory.createClassDefinition(
                arkts.factory.createIdentifier(node.definition!.ident!.name),
                undefined,
                undefined,
                node.definition?.implements ?? [],
                undefined,
                arkts.factory.createETSTypeReference(
                    arkts.factory.createETSTypeReferencePart(
                        arkts.factory.createIdentifier(CustomComponentNames.COMPONENT_CLASS_NAME, undefined),
                        arkts.factory.createTSTypeParameterInstantiation(
                            [
                                arkts.factory.createETSTypeReference(
                                    arkts.factory.createETSTypeReferencePart(
                                        arkts.factory.createIdentifier(node.definition!.ident!.name),
                                        undefined, undefined
                                    )
                                ),
                                arkts.factory.createETSTypeReference(
                                    arkts.factory.createETSTypeReferencePart(
                                        this.optionsName(node.definition!),
                                        undefined, undefined
                                    )
                                ),
                            ]
                        ), undefined
                    )
                ),
                this.rewriteStructMembers(node, (node.definition?.body as arkts.ClassElement[]) ?? []),
                arkts.Es2pandaClassDefinitionModifiers.CLASS_DEFINITION_MODIFIERS_CLASS_DECL,
                arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_FINAL
            ),
            arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_EXPORT,
        )
    }

    private rewriteStructMembers(clazz: arkts.ClassDeclaration, body: readonly arkts.ClassElement[]): arkts.ClassElement[] {
        let result: arkts.ClassElement[] = []
        body.forEach(node => {
            if (arkts.isClassProperty(node)) {
                this.getPropertyTransformer(node).applyStruct(clazz, node, result)
            } else if (arkts.isMethodDefinition(node)) {
                let method = node as arkts.MethodDefinition
                if (method.function?.id?.name == CustomComponentNames.COMPONENT_BUILD_ORI) {
                    result.push(this.rewriteBuild(clazz, node))
                } else if (hasDecorator(node, DecoratorNames.BUILDER)) {
                    result.push(this.rewriteBuilder(method))
                } else {
                    result.push(method)
                }
            } else {
                throw new Error(`How to rewrite ${node}?`)
            }
        })
        this.addInitializeStruct(clazz, result)
        this.addDisposeStruct(clazz, result)
        return result
    }

    private addInitializeStruct(clazz: arkts.ClassDeclaration, classBody: arkts.AstNode[]) {
        const statements: arkts.Statement[] = []
        forEachProperty(clazz, property => {
            this.getPropertyTransformer(property).applyInitializeStruct(this.pageLocalStorage, property, statements)
        })
        if (statements.length > 0) {
            classBody.push(createVoidMethod(CustomComponentNames.COMPONENT_INITIALIZE_STRUCT, [
                factory.createInitializersOptionsParameter(computeOptionsName(clazz)),
                factory.createContentParameter(),
            ], statements))
        }
    }

    private addDisposeStruct(clazz: arkts.ClassDeclaration, classBody: arkts.AstNode[]) {
        const statements: arkts.Statement[] = []
        forEachProperty(clazz, property => {
            this.getPropertyTransformer(property).applyDisposeStruct(property, statements)
        })
        if (statements.length > 0) {
            classBody.push(createVoidMethod(CustomComponentNames.COMPONENT_DISPOSE_STRUCT, [], statements))
        }
    }

    private rewriteBuildBody(clazz: arkts.ClassDeclaration, oldBody: arkts.BlockStatement): arkts.BlockStatement {
        let result: arkts.Statement[] = []
        forEachProperty(clazz, property => {
            this.getPropertyTransformer(property).applyBuild(property, result)
        })
        oldBody.statements.forEach((it) => {
            result.push(it)
        })
        return arkts.factory.createBlockStatement(result)
    }

    private rewriteBuild(clazz: arkts.ClassDeclaration, method: arkts.MethodDefinition): arkts.MethodDefinition {
        let isDeclaration = arkts.hasModifierFlag(method, arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_DECLARE)
        const newName: arkts.Identifier = arkts.factory.createIdentifier(CustomComponentNames.COMPONENT_BUILD)
        const className = clazz.definition?.ident?.name!
        const classTypeName = clazz.definition?.typeParams?.params?.[0]?.name?.name ?? className
        const classOptionsName = computeOptionsName(clazz)
        const scriptFunction = method.function as arkts.ScriptFunction
        const newFunction = arkts.factory.createScriptFunction(
            this.rewriteBuildBody(clazz, scriptFunction.body! as arkts.BlockStatement),
            scriptFunction.typeParams,
            [
                factory.createStyleParameter(classTypeName),
                factory.createContentParameter(),
                factory.createInitializersOptionsParameter(classOptionsName)
            ],
            arkts.factory.createETSPrimitiveType(arkts.Es2pandaPrimitiveType.PRIMITIVE_TYPE_VOID),
            false,
            scriptFunction.flags,
            scriptFunction.modifierFlags,
            newName,
            [annotation(InternalAnnotations.MEMO)]
        )
        const modifiers: arkts.Es2pandaModifierFlags = isDeclaration
            ? arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_ABSTRACT
            : arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC;
        return arkts.factory.createMethodDefinition(
            arkts.Es2pandaMethodDefinitionKind.METHOD_DEFINITION_KIND_METHOD,
            newName,
            arkts.factory.createFunctionExpression(newName, newFunction),
            modifiers,
            false
        )
    }

    private rewriteBuilder(method: arkts.MethodDefinition): arkts.MethodDefinition {
        method.function!.setAnnotations([annotation(InternalAnnotations.MEMO)])
        return method
    }

    private pageLocalStorage: arkts.Expression | undefined

    private parseLocalStorage(annotation: arkts.AnnotationUsage | undefined): arkts.Expression | undefined {
        if (!annotation || annotation.properties.length === 0) {
            return undefined
        }
        const properties: arkts.ClassProperty[] = annotation.properties.filter(property => {
            return arkts.isClassProperty(property)
        }).map(property => property as arkts.ClassProperty)

        // shared
        const useSharedStorage = !!properties.find(property => {
            return property.id?.name === DecoratorParameters.USE_SHARED_STORAGE && arkts.isBooleanLiteral(property.value) && property.value.value
        })
        if (useSharedStorage) {
            return arkts.factory.createCallExpression(
                fieldOf(arkts.factory.createIdentifier("LocalStorage"), "getShared"), [], undefined
            )
        }

        // concrete
        const storage = properties.find(property => property.id?.name === "storage")
        if (storage && storage.value) {
            return storage.value
        }

        // fallback to one string literal parameter
        if (arkts.isStringLiteral(properties[0].value)) {
            return arkts.factory.createIdentifier(properties[0].value.str)
        }

        return undefined
    }

    private parseEntryParameter(statements: readonly arkts.Statement[]) {
        for (const statement of statements) {
            if (!arkts.isETSStructDeclaration(statement)) {
                continue
            }
            const entryAnnotation = statement.definition?.annotations.filter(it => isAnnotation(it, DecoratorNames.ENTRY))[0]
            this.pageLocalStorage = this.parseLocalStorage(entryAnnotation)
            if (this.pageLocalStorage) {
                break
            }
        }
    }

    propertyTransformers: PropertyTransformer[] = [
        new StateTransformer(),
        new PlainPropertyTransformer(),
        new LinkTransformer(),
        new PropTransformer(),
        new StorageLinkTransformer(),
        new StoragePropTransformer(),
        new LocalStorageLinkTransformer(),
        new LocalStoragePropTransformer(),
        new ObjectLinkTransformer(),
        new ProvideTransformer(),
        new ConsumeTransformer(),
        new BuilderParamTransformer(),
    ]

    getPropertyTransformer(property: arkts.ClassProperty): PropertyTransformer {
        const transformer = this.propertyTransformers.find(it => it.check(property))
        if (transformer) return transformer
        throw new Error(`Cannot find transformer for property ${property.id?.name}`)
    }

    private rewriteStruct(node: arkts.ETSStructDeclaration, result: arkts.Statement[]) {
        result.push(this.rewriteStructToClass(node))
        result.push(this.rewriteStructToOptions(node))
    }

    visitor(node: arkts.AstNode): arkts.AstNode {
        if (arkts.isETSModule(node)) {
            return this.rewriteModule(node)
        }
        throw new Error(`Must not be there`)
    }
}

function forEachProperty(clazz: arkts.ClassDeclaration, callback: (property: arkts.ClassProperty) => void) {
    clazz.definition?.body.forEach(node => {
        if (arkts.isClassProperty(node)) callback(node)
    })
}

function createVoidMethod(methodName: string, parameters: readonly arkts.Expression[], statements: readonly arkts.Statement[]): arkts.MethodDefinition {
    return arkts.factory.createMethodDefinition(
        arkts.Es2pandaMethodDefinitionKind.METHOD_DEFINITION_KIND_METHOD,
        arkts.factory.createIdentifier(methodName),
        arkts.factory.createFunctionExpression(
            arkts.factory.createIdentifier(methodName),
            arkts.factory.createScriptFunction(
                arkts.factory.createBlockStatement(statements),
                undefined,
                parameters,
                arkts.factory.createETSPrimitiveType(arkts.Es2pandaPrimitiveType.PRIMITIVE_TYPE_VOID),
                false,
                arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_METHOD,
                arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PROTECTED,
                arkts.factory.createIdentifier(methodName),
                []
            )
        ),
        arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PROTECTED,
        false
    )
}
