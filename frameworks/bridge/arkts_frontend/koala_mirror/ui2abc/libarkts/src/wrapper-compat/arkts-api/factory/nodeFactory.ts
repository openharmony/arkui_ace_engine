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
import { updateCallExpression } from '../node-utilities/CallExpression';
import { updateExpressionStatement } from '../node-utilities/ExpressionStatement';
import { updateMemberExpression } from '../node-utilities/MemberExpression';
import { updateFunctionDeclaration } from '../node-utilities/FunctionDeclaration';
import { updateBlockStatement } from '../node-utilities/BlockStatement';
import { updateArrowFunctionExpression } from '../node-utilities/ArrowFunctionExpression';
import { updateScriptFunction } from '../node-utilities/ScriptFunction';
import { updateNumberLiteral } from '../node-utilities/NumberLiteral';
import { updateETSParameterExpression } from '../node-utilities/ETSParameterExpression';
import { updateTSTypeParameter } from '../node-utilities/TSTypeParameter';
import { updateETSImportDeclaration } from '../node-utilities/ETSImportDeclaration';
import { updateVariableDeclaration } from '../node-utilities/VariableDeclaration';
import { updateVariableDeclarator } from '../node-utilities/VariableDeclarator';
import { updateIfStatement } from '../node-utilities/IfStatement';
import { updateClassDeclaration } from '../node-utilities/ClassDeclaration';
import { updateStructDeclaration } from '../node-utilities/StructDeclaration';
import { updateClassDefinition } from '../node-utilities/ClassDefinition';
import { updateClassProperty } from '../node-utilities/ClassProperty';
import { updateETSFunctionType } from '../node-utilities/ETSFunctionType';
import { updateFunctionExpression } from '../node-utilities/FunctionExpression';
import { updateMethodDefinition } from '../node-utilities/MethodDefinition';
import { updateTSInterfaceDeclaration } from '../node-utilities/TSInterfaceDeclaration';
import { updateAssignmentExpression } from '../node-utilities/AssignmentExpression';
import { updateTSTypeAliasDeclaration } from '../node-utilities/TSTypeAliasDeclaration';
import { updateObjectExpression } from '../node-utilities/ObjectExpression';
import { updateProperty } from '../node-utilities/Property';
import { updateArrayExpression } from '../node-utilities/ArrayExpression';
import { updateTryStatement } from '../node-utilities/TryStatement';
import { Es2pandaModifierFlags } from 'src/arkts-api';

export const factory = {
    get createIdentifier(): (...args: Parameters<typeof Identifier.create2Identifier>) => Identifier {
        return Identifier.create2Identifier;
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
    get create1StringLiteral(): (...args: Parameters<typeof StringLiteral.create1StringLiteral>) => StringLiteral {
        return StringLiteral.create1StringLiteral;
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
    get createPrimitiveType(): (
        ...args: Parameters<typeof ETSPrimitiveType.createETSPrimitiveType>
    ) => ETSPrimitiveType {
        return ETSPrimitiveType.createETSPrimitiveType;
    },
    get createTypeReference(): (
        ...args: Parameters<typeof ETSTypeReference.createETSTypeReference>
    ) => ETSTypeReference {
        return ETSTypeReference.createETSTypeReference;
    },
    get createTypeReferencePart(): (
        ...args: Parameters<typeof ETSTypeReferencePart.createETSTypeReferencePart>
    ) => ETSTypeReferencePart {
        return ETSTypeReferencePart.createETSTypeReferencePart;
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
    get createReturnStatement(): (
        ...args: Parameters<typeof ReturnStatement.create1ReturnStatement>
    ) => ReturnStatement {
        return ReturnStatement.create1ReturnStatement;
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
    get createTSTypeParameterInstantiation(): (
        ...args: Parameters<typeof TSTypeParameterInstantiation.createTSTypeParameterInstantiation>
    ) => TSTypeParameterInstantiation {
        return TSTypeParameterInstantiation.createTSTypeParameterInstantiation;
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
    get createUndefinedLiteral(): (
        ...args: Parameters<typeof UndefinedLiteral.createUndefinedLiteral>
    ) => UndefinedLiteral {
        return UndefinedLiteral.createUndefinedLiteral;
    },
    get createAnnotationDeclaration(): (
        ...args: Parameters<typeof AnnotationDeclaration.create1AnnotationDeclaration>
    ) => AnnotationDeclaration {
        return AnnotationDeclaration.create1AnnotationDeclaration;
    },
    get createAnnotationUsage(): (
        ...args: Parameters<typeof AnnotationUsage.create1AnnotationUsage>
    ) => AnnotationUsage {
        return AnnotationUsage.create1AnnotationUsage;
    },
    get create1AnnotationUsage(): (
        ...args: Parameters<typeof AnnotationUsage.create1AnnotationUsage>
    ) => AnnotationUsage {
        return AnnotationUsage.create1AnnotationUsage;
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
    get createTSAsExpression(): (...args: Parameters<typeof TSAsExpression.createTSAsExpression>) => TSAsExpression {
        return TSAsExpression.createTSAsExpression;
    },
    get createThisExpression(): (...args: Parameters<typeof ThisExpression.createThisExpression>) => ThisExpression {
        return ThisExpression.createThisExpression;
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
    get createChainExpression(): (
        ...args: Parameters<typeof ChainExpression.createChainExpression>
    ) => ChainExpression {
        return ChainExpression.createChainExpression;
    },
    get createBlockExpression(): (
        ...args: Parameters<typeof BlockExpression.createBlockExpression>
    ) => BlockExpression {
        return BlockExpression.createBlockExpression;
    },
    get createNullLiteral(): (...args: Parameters<typeof NullLiteral.createNullLiteral>) => NullLiteral {
        return NullLiteral.createNullLiteral;
    },
    get createETSNewClassInstanceExpression(): (
        ...args: Parameters<typeof ETSNewClassInstanceExpression.createETSNewClassInstanceExpression>
    ) => ETSNewClassInstanceExpression {
        return ETSNewClassInstanceExpression.createETSNewClassInstanceExpression;
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
    /** @deprecated */
    createTypeParameter1_(name: Identifier, constraint?: TypeNode, defaultType?: TypeNode, flags = Es2pandaModifierFlags.MODIFIER_FLAGS_NONE) {
        return TSTypeParameter.create1TSTypeParameter(Identifier.create2Identifier(name.name), constraint, defaultType, flags);
    },
};
