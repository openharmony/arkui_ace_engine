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

import {
    ArrowFunctionExpression,
    AssignmentExpression,
    CallExpression,
    ETSParameterExpression,
    EtsScript,
    ExpressionStatement,
    FunctionDeclaration,
    FunctionExpression,
    IfStatement,
    MethodDefinition,
    NumberLiteral,
    StructDeclaration,
    VariableDeclaration,
    VariableDeclarator,
    ETSStringLiteralType,
} from '../types';
import { MemberExpression } from '../to-be-generated/MemberExpression';
import {
    AnnotationUsage,
    BinaryExpression,
    BlockStatement,
    ClassDeclaration,
    ClassDefinition,
    ClassProperty,
    ConditionalExpression,
    ETSImportDeclaration,
    ETSFunctionType,
    ETSPrimitiveType,
    ETSTypeReference,
    ETSTypeReferencePart,
    ETSUndefinedType,
    ETSUnionType,
    FunctionSignature,
    Identifier,
    ImportSpecifier,
    NullLiteral,
    ReturnStatement,
    ScriptFunction,
    StringLiteral,
    SuperExpression,
    ThisExpression,
    TSInterfaceBody,
    TSInterfaceDeclaration,
    TSNonNullExpression,
    TSTypeParameter,
    TSTypeParameterDeclaration,
    TSTypeParameterInstantiation,
    TypeNode,
    UndefinedLiteral,
    TSAsExpression,
    TSTypeAliasDeclaration,
    ChainExpression,
    BlockExpression,
    ETSNewClassInstanceExpression,
    BooleanLiteral,
    ObjectExpression,
    Property,
    TemplateLiteral,
    ArrayExpression,
    AnnotationDeclaration,
    TryStatement,
    TSClassImplements,
} from '../../../generated';
import { updateIdentifier } from '../node-utilities/Identifier';
import { updateCallExpression } from '../node-utilities/CallExpression';
import { updateExpressionStatement } from '../node-utilities/ExpressionStatement';
import { updateMemberExpression } from '../node-utilities/MemberExpression';
import { updateFunctionDeclaration } from '../node-utilities/FunctionDeclaration';
import { updateBlockStatement } from '../node-utilities/BlockStatement';
import { updateArrowFunctionExpression } from '../node-utilities/ArrowFunctionExpression';
import { updateScriptFunction } from '../node-utilities/ScriptFunction';
import { updateStringLiteral } from '../node-utilities/StringLiteral';
import { updateNumberLiteral } from '../node-utilities/NumberLiteral';
import { updateETSParameterExpression } from '../node-utilities/ETSParameterExpression';
import { updateTSTypeParameter } from '../node-utilities/TSTypeParameter';
import { updateTSTypeParameterDeclaration } from '../node-utilities/TSTypeParameterDeclaration';
import { updateETSPrimitiveType } from '../node-utilities/ETSPrimitiveType';
import { updateETSTypeReference } from '../node-utilities/ETSTypeReference';
import { updateETSTypeReferencePart } from '../node-utilities/ETSTypeReferencePart';
import { updateETSImportDeclaration } from '../node-utilities/ETSImportDeclaration';
import { updateImportSpecifier } from '../node-utilities/ImportSpecifier';
import { updateVariableDeclaration } from '../node-utilities/VariableDeclaration';
import { updateVariableDeclarator } from '../node-utilities/VariableDeclarator';
import { updateETSUnionType } from '../node-utilities/ETSUnionType';
import { updateReturnStatement } from '../node-utilities/ReturnStatement';
import { updateIfStatement } from '../node-utilities/IfStatement';
import { updateBinaryExpression } from '../node-utilities/BinaryExpression';
import { updateClassDeclaration } from '../node-utilities/ClassDeclaration';
import { updateStructDeclaration } from '../node-utilities/StructDeclaration';
import { updateClassDefinition } from '../node-utilities/ClassDefinition';
import { updateClassProperty } from '../node-utilities/ClassProperty';
import { updateETSFunctionType } from '../node-utilities/ETSFunctionType';
import { updateFunctionExpression } from '../node-utilities/FunctionExpression';
import { updateMethodDefinition } from '../node-utilities/MethodDefinition';
import { updateSuperExpression } from '../node-utilities/SuperExpression';
import { updateTSTypeParameterInstantiation } from '../node-utilities/TSTypeParameterInstantiation';
import { updateTSInterfaceDeclaration } from '../node-utilities/TSInterfaceDeclaration';
import { updateTSInterfaceBody } from '../node-utilities/TSInterfaceBody';
import { updateUndefinedLiteral } from '../node-utilities/UndefinedLiteral';
import { updateAnnotationUsage, update1AnnotationUsage } from '../node-utilities/AnnotationUsage';
import { updateAssignmentExpression } from '../node-utilities/AssignmentExpression';
import { updateETSUndefinedType } from '../node-utilities/ETSUndefinedType';
import { updateConditionalExpression } from '../node-utilities/ConditionalExpression';
import { updateTSAsExpression } from '../node-utilities/TSAsExpression';
import { updateThisExpression } from '../node-utilities/ThisExpression';
import { updateTSTypeAliasDeclaration } from '../node-utilities/TSTypeAliasDeclaration';
import { updateTSNonNullExpression } from '../node-utilities/TSNonNullExpression';
import { updateChainExpression } from '../node-utilities/ChainExpression';
import { updateBlockExpression } from '../node-utilities/BlockExpression';
import { updateNullLiteral } from '../node-utilities/NullLiteral';
import { updateETSNewClassInstanceExpression } from '../node-utilities/ETSNewClassInstanceExpression';
import { updateObjectExpression } from '../node-utilities/ObjectExpression';
import { updateProperty } from '../node-utilities/Property';
import { updateTemplateLiteral } from '../node-utilities/TemplateLiteral';
import { updateArrayExpression } from '../node-utilities/ArrayExpression';
import { updateAnnotationDeclaration } from '../node-utilities/AnnotationDeclaration';
import { updateTryStatement } from '../node-utilities/TryStatement';
import { Es2pandaModifierFlags } from 'src/arkts-api';
import { updateTSClassImplements } from '../node-utilities/TSClassImplements';

export const factory = {
    get createIdentifier(): (...args: Parameters<typeof Identifier.create2Identifier>) => Identifier {
        return Identifier.create2Identifier;
    },
    get updateIdentifier(): (...args: Parameters<typeof updateIdentifier>) => Identifier {
        return updateIdentifier;
    },
    get createCallExpression(): (...args: Parameters<typeof CallExpression.create>) => CallExpression {
        return CallExpression.create;
    },
    get updateCallExpression(): (...args: Parameters<typeof updateCallExpression>) => CallExpression {
        return updateCallExpression;
    },
    get createExpressionStatement(): (...args: Parameters<typeof ExpressionStatement.create>) => ExpressionStatement {
        return ExpressionStatement.create;
    },
    get updateExpressionStatement(): (...args: Parameters<typeof updateExpressionStatement>) => ExpressionStatement {
        return updateExpressionStatement;
    },
    get createMemberExpression(): (...args: Parameters<typeof MemberExpression.create>) => MemberExpression {
        return MemberExpression.create;
    },
    get updateMemberExpression(): (...args: Parameters<typeof updateMemberExpression>) => MemberExpression {
        return updateMemberExpression;
    },
    get createEtsScript(): (...args: Parameters<typeof EtsScript.createFromSource>) => EtsScript {
        return EtsScript.createFromSource;
    },
    get updateEtsScript(): (...args: Parameters<typeof EtsScript.updateByStatements>) => EtsScript {
        return EtsScript.updateByStatements;
    },
    get createFunctionDeclaration(): (...args: Parameters<typeof FunctionDeclaration.create>) => FunctionDeclaration {
        return FunctionDeclaration.create;
    },
    get updateFunctionDeclaration(): (...args: Parameters<typeof updateFunctionDeclaration>) => FunctionDeclaration {
        return updateFunctionDeclaration;
    },
    get createBlock(): (...args: Parameters<typeof BlockStatement.createBlockStatement>) => BlockStatement {
        return BlockStatement.createBlockStatement;
    },
    get updateBlock(): (...args: Parameters<typeof updateBlockStatement>) => BlockStatement {
        return updateBlockStatement;
    },
    get createArrowFunction(): (...args: Parameters<typeof ArrowFunctionExpression.create>) => ArrowFunctionExpression {
        return ArrowFunctionExpression.create;
    },
    get updateArrowFunction(): (...args: Parameters<typeof updateArrowFunctionExpression>) => ArrowFunctionExpression {
        return updateArrowFunctionExpression;
    },
    get createScriptFunction(): (...args: Parameters<typeof ScriptFunction.createScriptFunction>) => ScriptFunction {
        return ScriptFunction.createScriptFunction;
    },
    get updateScriptFunction(): (...args: Parameters<typeof updateScriptFunction>) => ScriptFunction {
        return updateScriptFunction;
    },
    get createStringLiteral(): (...args: Parameters<typeof StringLiteral.create1StringLiteral>) => StringLiteral {
        return StringLiteral.create1StringLiteral;
    },
    get updateStringLiteral(): (...args: Parameters<typeof updateStringLiteral>) => StringLiteral {
        return updateStringLiteral;
    },
    get create1StringLiteral(): (...args: Parameters<typeof StringLiteral.create1StringLiteral>) => StringLiteral {
        return StringLiteral.create1StringLiteral;
    },
    get update1StringLiteral(): (...args: Parameters<typeof updateStringLiteral>) => StringLiteral {
        return updateStringLiteral;
    },
    get createNumericLiteral(): (...args: Parameters<typeof NumberLiteral.create>) => NumberLiteral {
        return NumberLiteral.create;
    },
    get updateNumericLiteral(): (...args: Parameters<typeof updateNumberLiteral>) => NumberLiteral {
        return updateNumberLiteral;
    },
    get createParameterDeclaration(): (
        ...args: Parameters<typeof ETSParameterExpression.create>
    ) => ETSParameterExpression {
        return ETSParameterExpression.create;
    },
    get updateParameterDeclaration(): (
        ...args: Parameters<typeof updateETSParameterExpression>
    ) => ETSParameterExpression {
        return updateETSParameterExpression;
    },
    get createTypeParameter(): (...args: Parameters<typeof TSTypeParameter.create1TSTypeParameter>) => TSTypeParameter {
        return TSTypeParameter.create1TSTypeParameter;
    },
    get updateTypeParameter(): (...args: Parameters<typeof updateTSTypeParameter>) => TSTypeParameter {
        return updateTSTypeParameter;
    },
    get createTypeParameterDeclaration(): (
        ...args: Parameters<typeof TSTypeParameterDeclaration.createTSTypeParameterDeclaration>
    ) => TSTypeParameterDeclaration {
        return TSTypeParameterDeclaration.createTSTypeParameterDeclaration;
    },
    get updateTypeParameterDeclaration(): (
        ...args: Parameters<typeof updateTSTypeParameterDeclaration>
    ) => TSTypeParameterDeclaration {
        return updateTSTypeParameterDeclaration;
    },
    get createPrimitiveType(): (
        ...args: Parameters<typeof ETSPrimitiveType.createETSPrimitiveType>
    ) => ETSPrimitiveType {
        return ETSPrimitiveType.createETSPrimitiveType;
    },
    get updatePrimitiveType(): (...args: Parameters<typeof updateETSPrimitiveType>) => ETSPrimitiveType {
        return updateETSPrimitiveType;
    },
    get createTypeReference(): (
        ...args: Parameters<typeof ETSTypeReference.createETSTypeReference>
    ) => ETSTypeReference {
        return ETSTypeReference.createETSTypeReference;
    },
    get updateTypeReference(): (...args: Parameters<typeof updateETSTypeReference>) => ETSTypeReference {
        return updateETSTypeReference;
    },
    get createTypeReferencePart(): (
        ...args: Parameters<typeof ETSTypeReferencePart.createETSTypeReferencePart>
    ) => ETSTypeReferencePart {
        return ETSTypeReferencePart.createETSTypeReferencePart;
    },
    get updateTypeReferencePart(): (...args: Parameters<typeof updateETSTypeReferencePart>) => ETSTypeReferencePart {
        return updateETSTypeReferencePart;
    },
    get createImportDeclaration(): (
        ...args: Parameters<typeof ETSImportDeclaration.createETSImportDeclaration>
    ) => ETSImportDeclaration {
        return ETSImportDeclaration.createETSImportDeclaration;
    },
    get updateImportDeclaration(): (...args: Parameters<typeof updateETSImportDeclaration>) => ETSImportDeclaration {
        return updateETSImportDeclaration;
    },
    get createImportSpecifier(): (
        ...args: Parameters<typeof ImportSpecifier.createImportSpecifier>
    ) => ImportSpecifier {
        return ImportSpecifier.createImportSpecifier;
    },
    get updateImportSpecifier(): (...args: Parameters<typeof updateImportSpecifier>) => ImportSpecifier {
        return updateImportSpecifier;
    },
    get createVariableDeclaration(): (...args: Parameters<typeof VariableDeclaration.create>) => VariableDeclaration {
        return VariableDeclaration.create;
    },
    get updateVariableDeclaration(): (...args: Parameters<typeof updateVariableDeclaration>) => VariableDeclaration {
        return updateVariableDeclaration;
    },
    get createVariableDeclarator(): (...args: Parameters<typeof VariableDeclarator.create>) => VariableDeclarator {
        return VariableDeclarator.create;
    },
    get updateVariableDeclarator(): (...args: Parameters<typeof updateVariableDeclarator>) => VariableDeclarator {
        return updateVariableDeclarator;
    },
    get createUnionType(): (...args: Parameters<typeof ETSUnionType.createETSUnionType>) => ETSUnionType {
        return ETSUnionType.createETSUnionType;
    },
    get updateUnionType(): (...args: Parameters<typeof updateETSUnionType>) => ETSUnionType {
        return updateETSUnionType;
    },
    get createReturnStatement(): (
        ...args: Parameters<typeof ReturnStatement.create1ReturnStatement>
    ) => ReturnStatement {
        return ReturnStatement.create1ReturnStatement;
    },
    get updateReturnStatement(): (...args: Parameters<typeof updateReturnStatement>) => ReturnStatement {
        return updateReturnStatement;
    },
    get createIfStatement(): (...args: Parameters<typeof IfStatement.create>) => IfStatement {
        return IfStatement.create;
    },
    get updateIfStatement(): (...args: Parameters<typeof updateIfStatement>) => IfStatement {
        return updateIfStatement;
    },
    get createBinaryExpression(): (
        ...args: Parameters<typeof BinaryExpression.createBinaryExpression>
    ) => BinaryExpression {
        return BinaryExpression.createBinaryExpression;
    },
    get updateBinaryExpression(): (...args: Parameters<typeof updateBinaryExpression>) => BinaryExpression {
        return updateBinaryExpression;
    },
    get createClassDeclaration(): (
        ...args: Parameters<typeof ClassDeclaration.createClassDeclaration>
    ) => ClassDeclaration {
        return ClassDeclaration.createClassDeclaration;
    },
    get updateClassDeclaration(): (...args: Parameters<typeof updateClassDeclaration>) => ClassDeclaration {
        return updateClassDeclaration;
    },
    get createStructDeclaration(): (...args: Parameters<typeof StructDeclaration.create>) => StructDeclaration {
        return StructDeclaration.create;
    },
    get updateStructDeclaration(): (...args: Parameters<typeof updateStructDeclaration>) => StructDeclaration {
        return updateStructDeclaration;
    },
    get createClassDefinition(): (
        ...args: Parameters<typeof ClassDefinition.createClassDefinition>
    ) => ClassDefinition {
        return ClassDefinition.createClassDefinition;
    },
    get updateClassDefinition(): (...args: Parameters<typeof updateClassDefinition>) => ClassDefinition {
        return updateClassDefinition;
    },
    get createClassProperty(): (...args: Parameters<typeof ClassProperty.createClassProperty>) => ClassProperty {
        return ClassProperty.createClassProperty;
    },
    get updateClassProperty(): (...args: Parameters<typeof updateClassProperty>) => ClassProperty {
        return updateClassProperty;
    },
    get createFunctionType(): (...args: Parameters<typeof ETSFunctionType.createETSFunctionType>) => ETSFunctionType {
        return ETSFunctionType.createETSFunctionType;
    },
    get updateFunctionType(): (...args: Parameters<typeof updateETSFunctionType>) => ETSFunctionType {
        return updateETSFunctionType;
    },
    get createFunctionExpression(): (...args: Parameters<typeof FunctionExpression.create>) => FunctionExpression {
        return FunctionExpression.create;
    },
    get updateFunctionExpression(): (...args: Parameters<typeof updateFunctionExpression>) => FunctionExpression {
        return updateFunctionExpression;
    },
    get createMethodDefinition(): (...args: Parameters<typeof MethodDefinition.create>) => MethodDefinition {
        return MethodDefinition.create;
    },
    get updateMethodDefinition(): (...args: Parameters<typeof updateMethodDefinition>) => MethodDefinition {
        return updateMethodDefinition;
    },
    get createSuperExpression(): (
        ...args: Parameters<typeof SuperExpression.createSuperExpression>
    ) => SuperExpression {
        return SuperExpression.createSuperExpression;
    },
    get updateSuperExpression(): (...args: Parameters<typeof updateSuperExpression>) => SuperExpression {
        return updateSuperExpression;
    },
    get createTSTypeParameterInstantiation(): (
        ...args: Parameters<typeof TSTypeParameterInstantiation.createTSTypeParameterInstantiation>
    ) => TSTypeParameterInstantiation {
        return TSTypeParameterInstantiation.createTSTypeParameterInstantiation;
    },
    get updateTSTypeParameterInstantiation(): (
        ...args: Parameters<typeof updateTSTypeParameterInstantiation>
    ) => TSTypeParameterInstantiation {
        return updateTSTypeParameterInstantiation;
    },
    get createInterfaceDeclaration(): (
        ...args: Parameters<typeof TSInterfaceDeclaration.createTSInterfaceDeclaration>
    ) => TSInterfaceDeclaration {
        return TSInterfaceDeclaration.createTSInterfaceDeclaration;
    },
    get updateInterfaceDeclaration(): (
        ...args: Parameters<typeof updateTSInterfaceDeclaration>
    ) => TSInterfaceDeclaration {
        return updateTSInterfaceDeclaration;
    },
    get createInterfaceBody(): (...args: Parameters<typeof TSInterfaceBody.createTSInterfaceBody>) => TSInterfaceBody {
        return TSInterfaceBody.createTSInterfaceBody;
    },
    get updateInterfaceBody(): (...args: Parameters<typeof updateTSInterfaceBody>) => TSInterfaceBody {
        return updateTSInterfaceBody;
    },
    get createUndefinedLiteral(): (
        ...args: Parameters<typeof UndefinedLiteral.createUndefinedLiteral>
    ) => UndefinedLiteral {
        return UndefinedLiteral.createUndefinedLiteral;
    },
    get updateUndefinedLiteral(): (...args: Parameters<typeof updateUndefinedLiteral>) => UndefinedLiteral {
        return updateUndefinedLiteral;
    },
    get createAnnotationDeclaration(): (
        ...args: Parameters<typeof AnnotationDeclaration.create1AnnotationDeclaration>
    ) => AnnotationDeclaration {
        return AnnotationDeclaration.create1AnnotationDeclaration;
    },
    get updateAnnotationDeclaration(): (
        ...args: Parameters<typeof updateAnnotationDeclaration>
    ) => AnnotationDeclaration {
        return updateAnnotationDeclaration;
    },
    get createAnnotationUsage(): (
        ...args: Parameters<typeof AnnotationUsage.create1AnnotationUsage>
    ) => AnnotationUsage {
        return AnnotationUsage.create1AnnotationUsage;
    },
    get updateAnnotationUsage(): (...args: Parameters<typeof updateAnnotationUsage>) => AnnotationUsage {
        return updateAnnotationUsage;
    },
    get create1AnnotationUsage(): (
        ...args: Parameters<typeof AnnotationUsage.create1AnnotationUsage>
    ) => AnnotationUsage {
        return AnnotationUsage.create1AnnotationUsage;
    },
    get update1AnnotationUsage(): (...args: Parameters<typeof update1AnnotationUsage>) => AnnotationUsage {
        return update1AnnotationUsage;
    },
    get createAssignmentExpression(): (
        ...args: Parameters<typeof AssignmentExpression.create>
    ) => AssignmentExpression {
        return AssignmentExpression.create;
    },
    get updateAssignmentExpression(): (...args: Parameters<typeof updateAssignmentExpression>) => AssignmentExpression {
        return updateAssignmentExpression;
    },
    get createETSUndefinedType(): (
        ...args: Parameters<typeof ETSUndefinedType.createETSUndefinedType>
    ) => ETSUndefinedType {
        return ETSUndefinedType.createETSUndefinedType;
    },
    get updateETSUndefinedType(): (...args: Parameters<typeof updateETSUndefinedType>) => ETSUndefinedType {
        return updateETSUndefinedType;
    },
    get createFunctionSignature(): (
        ...args: Parameters<typeof FunctionSignature.createFunctionSignature>
    ) => FunctionSignature {
        return FunctionSignature.createFunctionSignature;
    },
    get createConditionalExpression(): (
        ...args: Parameters<typeof ConditionalExpression.createConditionalExpression>
    ) => ConditionalExpression {
        return ConditionalExpression.createConditionalExpression;
    },
    get updateConditionalExpression(): (
        ...args: Parameters<typeof updateConditionalExpression>
    ) => ConditionalExpression {
        return updateConditionalExpression;
    },
    get createTSAsExpression(): (...args: Parameters<typeof TSAsExpression.createTSAsExpression>) => TSAsExpression {
        return TSAsExpression.createTSAsExpression;
    },
    get updateTSAsExpression(): (...args: Parameters<typeof updateTSAsExpression>) => TSAsExpression {
        return updateTSAsExpression;
    },
    get createThisExpression(): (...args: Parameters<typeof ThisExpression.createThisExpression>) => ThisExpression {
        return ThisExpression.createThisExpression;
    },
    get updateThisExpression(): (...args: Parameters<typeof updateThisExpression>) => ThisExpression {
        return updateThisExpression;
    },
    get createTSTypeAliasDeclaration(): (
        ...args: Parameters<typeof TSTypeAliasDeclaration.createTSTypeAliasDeclaration>
    ) => TSTypeAliasDeclaration {
        return TSTypeAliasDeclaration.createTSTypeAliasDeclaration;
    },
    get updateTSTypeAliasDeclaration(): (
        ...args: Parameters<typeof updateTSTypeAliasDeclaration>
    ) => TSTypeAliasDeclaration {
        return updateTSTypeAliasDeclaration;
    },
    get createTSNonNullExpression(): (
        ...args: Parameters<typeof TSNonNullExpression.createTSNonNullExpression>
    ) => TSNonNullExpression {
        return TSNonNullExpression.createTSNonNullExpression;
    },
    get updateTSNonNullExpression(): (...args: Parameters<typeof updateTSNonNullExpression>) => TSNonNullExpression {
        return updateTSNonNullExpression;
    },
    get createChainExpression(): (
        ...args: Parameters<typeof ChainExpression.createChainExpression>
    ) => ChainExpression {
        return ChainExpression.createChainExpression;
    },
    get updateChainExpression(): (...args: Parameters<typeof updateChainExpression>) => ChainExpression {
        return updateChainExpression;
    },
    get createBlockExpression(): (
        ...args: Parameters<typeof BlockExpression.createBlockExpression>
    ) => BlockExpression {
        return BlockExpression.createBlockExpression;
    },
    get updateBlockExpression(): (...args: Parameters<typeof updateBlockExpression>) => BlockExpression {
        return updateBlockExpression;
    },
    get createNullLiteral(): (...args: Parameters<typeof NullLiteral.createNullLiteral>) => NullLiteral {
        return NullLiteral.createNullLiteral;
    },
    get updateNullLiteral(): (...args: Parameters<typeof updateNullLiteral>) => NullLiteral {
        return updateNullLiteral;
    },
    get createETSNewClassInstanceExpression(): (
        ...args: Parameters<typeof ETSNewClassInstanceExpression.createETSNewClassInstanceExpression>
    ) => ETSNewClassInstanceExpression {
        return ETSNewClassInstanceExpression.createETSNewClassInstanceExpression;
    },
    get updateETSNewClassInstanceExpression(): (
        ...args: Parameters<typeof updateETSNewClassInstanceExpression>
    ) => ETSNewClassInstanceExpression {
        return updateETSNewClassInstanceExpression;
    },
    get createETSStringLiteralType(): (
        ...args: Parameters<typeof ETSStringLiteralType.create>
    ) => ETSStringLiteralType {
        return ETSStringLiteralType.create;
    },
    get createBooleanLiteral(): (...args: Parameters<typeof BooleanLiteral.createBooleanLiteral>) => BooleanLiteral {
        return BooleanLiteral.createBooleanLiteral;
    },
    get createObjectExpression(): (
        ...args: Parameters<typeof ObjectExpression.createObjectExpression>
    ) => ObjectExpression {
        return ObjectExpression.createObjectExpression;
    },
    get updateObjectExpression(): (...args: Parameters<typeof updateObjectExpression>) => ObjectExpression {
        return updateObjectExpression;
    },
    get createProperty(): (...args: Parameters<typeof Property.create1Property>) => Property {
        return Property.create1Property;
    },
    get updateProperty(): (...args: Parameters<typeof updateProperty>) => Property {
        return updateProperty;
    },
    get createTemplateLiteral(): (
        ...args: Parameters<typeof TemplateLiteral.createTemplateLiteral>
    ) => TemplateLiteral {
        return TemplateLiteral.createTemplateLiteral;
    },
    get updateTemplateLiteral(): (...args: Parameters<typeof updateTemplateLiteral>) => TemplateLiteral {
        return updateTemplateLiteral;
    },
    get createArrayExpression(): (
        ...args: Parameters<typeof ArrayExpression.create1ArrayExpression>
    ) => ArrayExpression {
        return ArrayExpression.create1ArrayExpression;
    },
    get updateArrayExpression(): (...args: Parameters<typeof updateArrayExpression>) => ArrayExpression {
        return updateArrayExpression;
    },
    get createTryStatement(): (...args: Parameters<typeof TryStatement.createTryStatement>) => TryStatement {
        return TryStatement.createTryStatement;
    },
    get updateTryStatement(): (...args: Parameters<typeof updateTryStatement>) => TryStatement {
        return updateTryStatement;
    },
    get createTSClassImplements(): (...args: Parameters<typeof TSClassImplements.createTSClassImplements>) => TSClassImplements {
        return TSClassImplements.createTSClassImplements;
    },
    get UpdateTSClassImplements(): (...args: Parameters<typeof updateTSClassImplements>) => TSClassImplements {
        return updateTSClassImplements;
    },
    /** @deprecated */
    createTypeParameter1_(name: Identifier, constraint?: TypeNode, defaultType?: TypeNode, flags = Es2pandaModifierFlags.MODIFIER_FLAGS_NONE) {
        return TSTypeParameter.create1TSTypeParameter(Identifier.create2Identifier(name.name), constraint, defaultType, flags);
    },
};
