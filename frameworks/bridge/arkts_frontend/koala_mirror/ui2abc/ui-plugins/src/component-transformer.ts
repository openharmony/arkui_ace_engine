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
import { DecoratorNames, hasDecorator } from "./property-translators/utils";
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


class StructCallRewriter extends arkts.AbstractVisitor {
    constructor(private structTable: StructTable) {
        super()
    }

    currentStructRewritten: arkts.ETSStructDeclaration | undefined = undefined
    currentStructCalled: StructDescriptor | undefined = undefined

    visitor(node: arkts.AstNode, options?: object): arkts.AstNode {
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
            let casted = arkts.factory.createTSAsExpression(
                this.createObjectLiteralRewrite(node),
                arkts.factory.createTSTypeReference(arkts.factory.createIdentifier(
                    getCustomComponentOptionsName(this.currentStructCalled.name))),
                false
            )
            return casted
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

    private createMemberRewrite(targetPropertyNameId: arkts.Identifier, original: arkts.MemberExpression): arkts.MemberExpression {
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

    private createDollarRewrite(targetPropertyNameId: arkts.Identifier, original: arkts.Identifier): arkts.MemberExpression | arkts.Identifier {
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

export class ComponentTransformer extends arkts.AbstractVisitor {
    private arkuiImport?: string
    private callRewriter: StructCallRewriter

    constructor(private imports: Importer, private structTable: StructTable, options?: ComponentTransformerOptions) {
        super()
        this.arkuiImport = options?.arkui
        this.callRewriter = new StructCallRewriter(structTable)
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
            } else if (arkts.isETSImportDeclaration(statement)) {
                this.rewriteImport(statement)
                result.push(statement)
            } else {
                result.push(statement)
            }
        })
        return result
    }

    private rewriteImport(statement: arkts.ETSImportDeclaration) {
        statement.specifiers.forEach(it => {
            const name = (it as arkts.ImportSpecifier).imported
            if (name && this.structTable.findStruct(name)) {
                this.imports.add(getCustomComponentOptionsName(name.name), statement.source?.str!)
            }
        })
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
        node.definition?.body.forEach(node => {
            if (arkts.isClassProperty(node)) {
                let transformer = this.propertyTransformers.find(it => it.check(node))
                if (transformer == undefined) throw new Error(`Cannot find transformer for property ${node.id?.name}`)
                transformer.applyOptions(node, result)
            }
        })
        return result
    }

    private rewriteStructToClass(node: arkts.ETSStructDeclaration): arkts.ClassDefinition {
        return arkts.factory.createClassDefinition(
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
            arkts.classDefinitionFlags(node.definition!) | arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_FINAL | arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_EXPORT)
    }

    private rewriteStructMembers(clazz: arkts.ClassDeclaration, body: readonly arkts.ClassElement[]): arkts.ClassElement[] {
        let result: arkts.ClassElement[] = []
        body.forEach(node => {
            if (arkts.isClassProperty(node)) {
                let transformer = this.propertyTransformers.find(it => it.check(node))
                if (transformer == undefined) throw new Error(`Cannot find transformer for property ${node.id?.name}`)
                transformer.applyStruct(clazz, node, result, this.pageLocalStorage)
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
        result.push(this.createInitializer(clazz))
        return result
    }

    private createInitializerBody(clazz: arkts.ClassDeclaration): arkts.Statement {
        let result: arkts.Statement[] = []
        clazz.definition?.body.forEach(node => {
            if (arkts.isClassProperty(node)) {
                let transformer = this.propertyTransformers.find(it => it.check(node))
                if (transformer == undefined) throw new Error(`Cannot find transformer for property ${node.id?.name}`)
                transformer.applyInitialization(node, result)
            }
        })
        return arkts.factory.createBlockStatement(result)
    }

    private createInitializer(clazz: arkts.ClassDeclaration): arkts.MethodDefinition {
        let methodName = arkts.factory.createIdentifier(CustomComponentNames.COMPONENT_INITIALIZE_STRUCT)
        const newFunction = arkts.factory.createScriptFunction(
            this.createInitializerBody(clazz),
            undefined,
            [
                factory.createInitializersOptionsParameter(computeOptionsName(clazz)),
                factory.createContentParameter(),
            ],
            arkts.factory.createETSPrimitiveType(arkts.Es2pandaPrimitiveType.PRIMITIVE_TYPE_VOID),
            false,
            arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_METHOD,
            arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PROTECTED,
            methodName,
            []
        )
        return arkts.factory.createMethodDefinition(
            arkts.Es2pandaMethodDefinitionKind.METHOD_DEFINITION_KIND_METHOD,
            methodName,
            arkts.factory.createFunctionExpression(methodName, newFunction),
            arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PROTECTED,
            false
        )
    }

    private rewriteBuildBody(clazz: arkts.ClassDeclaration, oldBody: arkts.BlockStatement): arkts.BlockStatement {
        let result: arkts.Statement[] = []
        clazz.definition!.body.forEach(node => {
            if (arkts.isClassProperty(node)) {
                let transformer = this.propertyTransformers.find(it => it.check(node))
                if (transformer == undefined)
                    throw new Error(`Cannot find transformer for property ${node.id?.name}`)
                transformer.applyBuild(node, result)
            }
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
            return property.id?.name === "useSharedStorage" && arkts.isBooleanLiteral(property.value) && property.value.value
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

    private rewriteStruct(node: arkts.ETSStructDeclaration, result: arkts.Statement[]) {
        this.callRewriter.currentStructRewritten = node
        result.push(this.callRewriter.visitor(arkts.factory.createClassDeclaration(this.rewriteStructToClass(node))))
        result.push(this.rewriteStructToOptions(node))
        this.callRewriter.currentStructRewritten = undefined
    }

    visitor(node: arkts.AstNode): arkts.AstNode {
        if (arkts.isETSModule(node)) {
            return this.rewriteModule(node)
        }
        throw new Error(`Must not be there`)
    }
}