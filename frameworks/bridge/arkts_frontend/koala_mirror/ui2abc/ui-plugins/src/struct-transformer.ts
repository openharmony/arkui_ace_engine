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
    annotation,
    collect,
    filterDefined
} from "./common/arkts-utils";
import {
    classifyProperty,
    PropertyTranslator
} from "./property-translators";
import {
    CustomComponentNames,
    getCustomComponentOptionsName,
    getTypeNameFromTypeParameter,
    getTypeParamsFromClassDecl,
} from "./utils";
import {
    factory
} from "./ui-factory";
import { DecoratorNames, hasDecorator } from "./property-translators/utils";

function isCustomComponentClass(node: arkts.ClassDeclaration): boolean {
    if (!node.definition?.ident?.name) return false;
    const name: string = node.definition.ident.name;
    const structCollection: Set<string> = arkts.GlobalInfo.getInfoInstance().getStructCollection();
    return structCollection.has(name)
}

function isKnownMethodDefinition(method: arkts.MethodDefinition, name: string): boolean {
    if (!method || !arkts.isMethodDefinition(method)) return false;

    // For now, we only considered matched method name.
    const isNameMatched: boolean = method.id?.name === name;
    return isNameMatched;
}

function transformBuildMethod(
    method: arkts.MethodDefinition,
    typeName: string,
    optionsName: string,
    isDecl?: boolean
): arkts.MethodDefinition {
    const updateKey: arkts.Identifier = arkts.factory.createIdentifier(
        CustomComponentNames.COMPONENT_BUILD, undefined
    );

    const scriptFunction: arkts.ScriptFunction = method.function!
    const updateScriptFunction = arkts.factory.createScriptFunction(
        scriptFunction.body,
        scriptFunction.typeParams,
        [
            factory.createStyleParameter(typeName),
            factory.createContentParameter(),
            factory.createInitializersOptionsParameter(optionsName)
        ],
        arkts.factory.createETSPrimitiveType(arkts.Es2pandaPrimitiveType.PRIMITIVE_TYPE_VOID),
        false,
        scriptFunction.flags,
        scriptFunction.modifierFlags,
        updateKey,
        [annotation("memo")]
    );

    const modifiers: arkts.Es2pandaModifierFlags = isDecl
        ? arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_ABSTRACT
        : arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC;
    return arkts.factory.createMethodDefinition(
        arkts.Es2pandaMethodDefinitionKind.METHOD_DEFINITION_KIND_METHOD,
        updateKey,
        arkts.factory.createFunctionExpression(updateKey, updateScriptFunction),
        modifiers,
        false
    );
}

function createInitializeStruct(
    structInfo: arkts.StructInfo,
    optionsTypeName: string,
    isDecl?: boolean
) {
    const updateKey: arkts.Identifier = arkts.factory.createIdentifier(
        CustomComponentNames.COMPONENT_INITIALIZE_STRUCT, undefined
    );

    let body: arkts.BlockStatement | undefined;
    let modifiers: arkts.Es2pandaModifierFlags = arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_ABSTRACT;
    if (!isDecl) {
        body = arkts.factory.createBlockStatement(structInfo.initializeBody);
        modifiers = arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC;
    }
    const scriptFunction: arkts.ScriptFunction = arkts.factory.createScriptFunction(
        body,
        undefined,
        [
            factory.createInitializersOptionsParameter(optionsTypeName),
            factory.createContentParameter()
        ],
        arkts.factory.createETSPrimitiveType(arkts.Es2pandaPrimitiveType.PRIMITIVE_TYPE_VOID),
        false,
        arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_METHOD,
        modifiers,
        updateKey,
        undefined
    );

    return arkts.factory.createMethodDefinition(
        arkts.Es2pandaMethodDefinitionKind.METHOD_DEFINITION_KIND_METHOD,
        updateKey,
        arkts.factory.createFunctionExpression(updateKey, scriptFunction),
        modifiers,
        false
    );
}

function createUpdateStruct(
    structInfo: arkts.StructInfo,
    optionsTypeName: string,
    isDecl?: boolean
) {
    const updateKey: arkts.Identifier = arkts.factory.createIdentifier(
        CustomComponentNames.COMPONENT_UPDATE_STRUCT, undefined
    )

    let body: arkts.BlockStatement | undefined;
    let modifiers: arkts.Es2pandaModifierFlags = arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_ABSTRACT;
    if (!isDecl) {
        body = arkts.factory.createBlockStatement(structInfo.updateBody);
        modifiers = arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC;
    }

    const scriptFunction: arkts.ScriptFunction = arkts.factory.createScriptFunction(
        body,
        undefined,
        [
            factory.createInitializersOptionsParameter(optionsTypeName)
        ],
        arkts.factory.createETSPrimitiveType(arkts.Es2pandaPrimitiveType.PRIMITIVE_TYPE_VOID),
        false,
        arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_METHOD,
        modifiers,
        updateKey,
        undefined
    );

    return arkts.factory.createMethodDefinition(
        arkts.Es2pandaMethodDefinitionKind.METHOD_DEFINITION_KIND_METHOD,
        updateKey,
        arkts.factory.createFunctionExpression(updateKey, scriptFunction),
        modifiers,
        false
    );
}

function tranformPropertyMembers(
    className: string,
    propertyTranslators: PropertyTranslator[],
    optionsTypeName: string,
    isDecl?: boolean,
    scope?: ScopeInfo
): arkts.AstNode[] {
    const propertyMembers = propertyTranslators.map(translator =>
        translator.translateMember()
    );
    const currentStructInfo: arkts.StructInfo = arkts.GlobalInfo
        .getInfoInstance()
        .getStructInfo(className);
    const collections = [];
    if (!scope?.hasInitializeStruct) {
        collections.push(createInitializeStruct(currentStructInfo, optionsTypeName, isDecl))
    }
    if (!scope?.hasUpdateStruct) {
        collections.push(createUpdateStruct(currentStructInfo, optionsTypeName, isDecl))
    }
    return collect(...collections, ...propertyMembers);
}

function tranformClassMembers(
    node: arkts.ClassDeclaration,
    isDecl?: boolean,
    scope?: ScopeInfo
): arkts.ClassDeclaration {
    if (!node.definition) {
        return node;
    }

    let classTypeName: string | undefined;
    let classOptionsName: string | undefined;
    if (isDecl) {
        const [classType, classOptions] = getTypeParamsFromClassDecl(node);
        classTypeName = getTypeNameFromTypeParameter(classType);
        classOptionsName = getTypeNameFromTypeParameter(classOptions);
    }

    const definition: arkts.ClassDefinition = node.definition;
    const className: string | undefined = node.definition.ident?.name;
    if (!className) {
        throw new Error("Non Empty className expected for Component")
    }

    const propertyTranslators: PropertyTranslator[] = filterDefined(
        definition.body.map(it => classifyProperty(it, className))
    );

    const translatedMembers: arkts.AstNode[] = tranformPropertyMembers(
        className,
        propertyTranslators,
        classOptionsName ?? getCustomComponentOptionsName(className),
        isDecl,
        scope
    );

    const updateMembers: arkts.AstNode[] = definition.body
        .filter((member)=>!arkts.isClassProperty(member))
        .map((member: arkts.AstNode) => {
            if (arkts.isMethodDefinition(member) && hasDecorator(member, DecoratorNames.BUILDER)) {
                member.function!.setAnnotations([annotation("memo")]);
                return member;
            }
            if (
                arkts.isMethodDefinition(member)
                && isKnownMethodDefinition(member, CustomComponentNames.COMPONENT_CONSTRUCTOR_ORI)
                && !isDecl
            ) {
                return arkts.factory.createMethodDefinition(
                    arkts.Es2pandaMethodDefinitionKind.METHOD_DEFINITION_KIND_CONSTRUCTOR,
                    member.id,
                    arkts.factory.createFunctionExpression(member.id, member.function),
                    arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_CONSTRUCTOR,
                    false
                );
            }
            if (
                arkts.isMethodDefinition(member)
                && isKnownMethodDefinition(member, CustomComponentNames.COMPONENT_BUILD_ORI)
            ) {
                const buildMethod = transformBuildMethod(
                    member,
                    classTypeName ?? className,
                    classOptionsName ?? getCustomComponentOptionsName(className),
                    isDecl
                );
                return buildMethod;
            }

            return member;
        }
    );

    const updateClassDef: arkts.ClassDefinition = arkts.factory.updateClassDefinition(
        definition,
        definition.ident,
        definition.typeParams,
        definition.superTypeParams,
        definition.implements,
        undefined,
        definition.super,
        [...translatedMembers, ...updateMembers],
        definition.modifiers,
        arkts.classDefinitionFlags(definition)
    );

    return arkts.factory.updateClassDeclaration(node, updateClassDef);
}

type ScopeInfo = {
    name: string,
    hasInitializeStruct?: boolean,
    hasUpdateStruct?: boolean,
}

export class StructTransformer extends arkts.AbstractVisitor {
    private scopeInfos: ScopeInfo[] = [];

    enter(node: arkts.AstNode) {
        if (arkts.isClassDeclaration(node) && isCustomComponentClass(node)) {
            this.scopeInfos.push({ name: node.definition!.ident!.name });
        }
        if (arkts.isMethodDefinition(node) && this.scopeInfos.length > 0) {
            const name = node.id!.name
            const scopeInfo = this.scopeInfos.pop()!;
            scopeInfo.hasInitializeStruct ||= (name === CustomComponentNames.COMPONENT_INITIALIZE_STRUCT);
            scopeInfo.hasUpdateStruct ||= (name === CustomComponentNames.COMPONENT_UPDATE_STRUCT);
            this.scopeInfos.push(scopeInfo);
        }
    }

    exit(node: arkts.AstNode) {
        if (arkts.isClassDeclaration(node) && isCustomComponentClass(node)) {
            this.scopeInfos.pop();
        }
    }

    visitor(beforeChildren: arkts.AstNode): arkts.AstNode {
        this.enter(beforeChildren);
        const node = this.visitEachChild(beforeChildren);
        if (arkts.isClassDeclaration(node) && isCustomComponentClass(node)) {
            let scope: ScopeInfo | undefined;
            if (this.scopeInfos.length > 0) {
                scope = this.scopeInfos[this.scopeInfos.length - 1];
            }
            const newClass: arkts.ClassDeclaration = tranformClassMembers(
                node,
                arkts.hasModifierFlag(node, arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_DECLARE),
                scope
            );
            this.exit(beforeChildren);
            return newClass;
        }
        return node
    }
}
