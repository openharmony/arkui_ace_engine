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

import {
    KNativePointer as KPtr,
    KInt,
    KBoolean,
    KNativePointer,
    registerNativeModuleLibraryName,
    loadNativeModuleLibrary,
    KDouble
} from "@koalaui/interop"
import { Es2pandaNativeModule as GeneratedEs2pandaNativeModule } from "./generated/Es2pandaNativeModule"
import * as path from "path"

// TODO: this type should be in interop
export type KPtrArray = BigUint64Array

export class Es2pandaNativeModule {
    _ClassDefinitionSuper(context: KPtr, node: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _CreateTSInterfaceDeclaration(_context: KPtr, _extends: KPtrArray, _extendsLen: KInt, _id: KPtr, _typeParams: KPtr, _body: KPtr, _isStatic: KBoolean, _isExternal: KBoolean): KPtr {
        throw new Error("Not implemented")
    }
    _CreateTSTypeParameterInstantiation(context: KPtr, params: KPtrArray, paramsLen: KInt): KPtr {
        throw new Error("Not implemented")
    }
    _ClassElementKey(context: KPtr, node: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _ClassElementValue(context: KPtr, node: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _AnnotationUsageIrExpr(context: KPtr, node: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _AnnotationUsageIrPropertiesConst(context: KPtr, node: KPtr, returnLen: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _AnnotationAllowedAnnotations(context: KPtr, node: KPtr, returnLen: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _AnnotationAllowedAnnotationsConst(context: KPtr, node: KPtr, returnLen: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _AstNodeRebind(context: KPtr, node: KPtr): void {
        throw new Error("Not implemented")
    }
    _AstNodeRecheck(context: KPtr, node: KPtr): void {
        throw new Error("Not implemented")
    }

    _ContextState(context: KPtr): KInt {
        throw new Error("Not implemented")
    }
    _ContextErrorMessage(context: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _AstNodeChildren(context: KPtr, node: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _ETSParserCreateExpression(context: KPtr, sourceCode: String, flags: KInt): KPtr {
        throw new Error("Not implemented")
    }
    _AstNodeDumpModifiers(context: KPtr, node: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _CreateAstDumper(context: KPtr, node: KPtr, source: String): KPtr {
        throw new Error("Not implemented")
    }
    _AstDumperModifierToString(context: KPtr, dumper: KPtr, flags: KInt): KPtr {
        throw new Error("Not implemented")
    }

    _CreateConfig(argc: number, argv: string[]): KPtr {
        throw new Error("Not implemented")
    }
    _DestroyConfig(config: KPtr): void {
        throw new Error("Not implemented")
    }
    _CreateContextFromString(config: KPtr, source: String, filename: String): KPtr {
        throw new Error("Not implemented")
    }
    _CreateContextFromFile(config: KPtr, filename: String): KPtr {
        throw new Error("Not implemented")
    }
    _DestroyContext(context: KPtr): void {
        throw new Error("Not implemented")
    }
    _ProceedToState(context: KPtr, state: number): void {
        throw new Error("Not implemented")
    }
    _ContextProgram(context: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _ProgramAst(context: KPtr, program: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _CheckerStartChecker(context: KPtr): KBoolean {
        throw new Error("Not implemented")
    }
    _VarBinderIdentifierAnalysis(context: KPtr): void {
        throw new Error("Not implemented")
    }
    _VarBinderInitTopScope(context: KPtr): void {
        throw new Error("Not implemented")
    }
    _VarBinderSetGenStdLib(context: KPtr, genStdLibT: KBoolean): void {
        throw new Error("Not implemented")
    }
    _SourceFileGetChildren(node: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _BlockGetStatements(node: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _FunctionDeclarationIsAnonymousConst(context: KPtr, node: KPtr): KBoolean {
        throw new Error("Not implemented")
    }
    _ExpressionStatementGetExpression(context: KPtr, node: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _CallExpressionArguments(context: KPtr, node: KPtr, returnLen: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _CallExpressionCallee(context: KPtr, node: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _IdentifierGetText(node: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _IdentifierIsPrivateIdentConst(context: KPtr, node: KPtr): KBoolean {
        throw new Error("Not implemented")
    }
    _PropertyAccessExpressionGetExpression(node: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _PropertyAccessExpressionGetName(node: KPtr): KPtr {
        throw new Error("Not implemented")
    }

    _FunctionDeclarationFunction(context: KPtr, node: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _ScriptFunctionSignature(context: KPtr, node: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _ScriptFunctionParams(context: KPtr, node: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _ScriptFunctionId(context: KPtr, node: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _ScriptFunctionBody(context: KPtr, node: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _ScriptFunctionAnnotations(context: KPtr, node: KPtr, returnLen: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _ScriptFunctionSetIdent(context: KPtr, ast: KPtr, id: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _ScriptFunctionSetSignature(context: KPtr, ast: KPtr, signature: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _ScriptFunctionSetBody(context: KPtr, ast: KPtr, body: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _ScriptFunctionSetScope(context: KPtr, ast: KPtr, scope: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _ScriptFunctionSetAnnotations(context: KPtr, ast: KPtr, annotations: KPtrArray, annotationsLen: KInt): KPtr {
        throw new Error("Not implemented")
    }
    _ScriptFunctionDeclareConst(context: KPtr, node: KPtr): KBoolean {
        throw new Error("Not implemented")
    }
    _ScriptFunctionFlagsConst(context: KPtr, node: KPtr): KInt {
        throw new Error("Not implemented")
    }
    _ScriptFunctionTypeParams(context: KPtr, node: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _ScriptFunctionReturnTypeAnnotation(context: KPtr, node: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _ScriptFunctionAddFlag(context: KPtr, node: KPtr, flags: KInt): void {
        throw new Error("Not implemented")
    }
    _ClassPropertyAnnotations(context: KPtr, node: KPtr, returnLen: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _ClassPropertySetAnnotations(context: KPtr, ast: KPtr, annotations: KPtrArray, annotationsLen: KInt): KPtr {
        throw new Error("Not implemented")
    }
    _UpdateBlockStatement(context: KPtr, original: KPtr, statementList: KPtrArray, statementListLen: KInt): KPtr {
        throw new Error("Not implemented")
    }
    _BlockStatementSetScope(context: KPtr, node: KPtr, scope: KPtrArray): void {
        throw new Error("Not implemented")
    }
    _CreateIdentifier1(context: KPtr, name: String): KPtr {
        throw new Error("Not implemented")
    }
    _CreateIdentifier2(context: KPtr, name: String, type_annotation: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _IdentifierSetName(context: KPtr, node: KPtr, name: String): void {
        throw new Error("Not implemented")
    }
    _IdentifierIdentifierFlags(context: KPtr, node: KPtr): KInt {
        throw new Error("Not implemented")
    }
    _CreateFunctionDeclaration(context: KPtr, func: KPtr, annotations: KPtrArray, annotationsLen: KInt, isAnon: KBoolean): KPtr {
        throw new Error("Not implemented")
    }
    _UpdateFunctionDeclaration(context: KPtr, node: KPtr, annotations: KPtrArray, annotationsLen: KInt, func: KPtr, isAnon: KBoolean): KPtr {
        throw new Error("Not implemented")
    }
    _CreateReturnStatement1(context: KPtr, argument: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _ReturnStatementArgument(context: KPtr, node: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _CreateIfStatement(context: KPtr, test: KPtr, consequent: KPtr, alternate: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _CreateBinaryExpression(context: KPtr, left: KPtr, right: KPtr, operatorType: KInt): KPtr {
        throw new Error("Not implemented")
    }
    _CreateAssignmentExpression(context: KPtr, left: KPtr, right: KPtr, assignmentOperator: KInt): KPtr {
        throw new Error("Not implemented")
    }
    _CreateMethodDefinition(context: KPtr, kind: KInt, key: KPtr, value: KPtr, modifiers: KInt, isComputed: KBoolean): KPtr {
        throw new Error("Not implemented")
    }
    _CreateClassProperty(context: KPtr, key: KPtr, value: KPtr, typeAnnotation: KPtr, modifiers: KInt, isComputed: KBoolean): KPtr {
        throw new Error("Not implemented")
    }
    _CreateETSImportDeclaration(context: KPtr, source: KPtr, specifiers: KPtrArray, specifiersLen: KInt, importKind: KInt): KNativePointer {
        throw new Error("Not implemented")
    }
    _ETSImportDeclarationSourceConst(context: KPtr, node: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _ETSImportDeclarationResolvedSource(context: KPtr, node: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _ETSImportDeclarationHasDeclConst(context: KPtr, node: KPtr): KBoolean {
        throw new Error("Not implemented")
    }
    _CreateImportSource(context: KPtr, source: KPtr, resolvedSource: KPtr, hasDecl: KBoolean): KNativePointer {
        throw new Error("Not implemented")
    }
    _CreateImportSpecifier(context: KPtr, imported: KPtr, local: KPtr): KNativePointer {
        throw new Error("Not implemented")
    }

    _CreateFunctionSignature(context: KPtr, typeParams: KPtr, params: KPtrArray, paramsLen: KInt, returnTypeAnnotation: KPtr, hasReceiver: KBoolean): KPtr {
        throw new Error("Not implemented")
    }
    _CreateScriptFunction(context: KPtr, databody: KPtr, datasignature: KPtr, datafuncFlags: KInt, dataflags: KInt): KPtr {
        throw new Error("Not implemented")
    }
    _UpdateScriptFunction(context: KPtr, original: KPtr, databody: KPtr, datasignature: KPtr, datafuncFlags: KInt, dataflags: KInt, datadeclare: KBoolean): KPtr {
        throw new Error("Not implemented")
    }
    _CreateBlockStatement(context: KPtr, statementList: KPtrArray, statementListLen: KInt): KPtr {
        throw new Error("Not implemented")
    }
    _AstNodeScopeConst(context: KPtr, ast: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _AstNodeParent(context: KPtr, ast: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _AstNodeSetParent(context: KPtr, ast: KPtr, parent: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _AstNodeClone(context: KPtr, ast: KPtr, parent: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _AstNodeModifiers(context: KPtr, ast: KPtr): KInt {
        throw new Error("Not implemented")
    }
    _AstNodeAddModifier(context: KPtr, ast: KPtr, flags: KInt): void {
        throw new Error("Not implemented")
    }
    _AstNodeClearModifier(context: KPtr, ast: KPtr, flags: KInt): void {
        throw new Error("Not implemented")
    }
    _AstNodeVariableConst(context: KPtr, ast: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _AstNodeTypeConst(context: KPtr, ast: KPtr): KInt {
        throw new Error("Not implemented")
    }
    _FunctionSignatureTypeParams(context: KPtr, ast: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _FunctionSignatureReturnType(context: KPtr, ast: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _FunctionSignatureParamsConst(context: KPtr, ast: KPtr, returnTypeLen: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _UpdateIdentifier1(context: KPtr, ast: KPtr, name: string): KPtr {
        throw new Error("Not implemented")
    }
    _UpdateIdentifier2(context: KPtr, ast: KPtr, name: string, typeAnnotation: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _UpdateMethodDefinition(context: KPtr, node: KPtr, kind: KInt, key: KPtr, value: KPtr, modifiers: KInt, isComputed: KBoolean): KPtr {
        throw new Error("Not implemented")
    }
    _MethodDefinitionFunction(context: KPtr, node: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _MethodDefinitionKindConst(context: KPtr, node: KPtr): KInt {
        throw new Error("Not implemented")
    }

    _CreateMemberExpression(context: KPtr, object: KPtr, property: KPtr, kind: KInt, computed: KBoolean, optional: KBoolean): KPtr {
        throw new Error("Not implemented")
    }
    _UpdateMemberExpression(context: KPtr, node: KPtr, object: KPtr, property: KPtr, kind: KInt, computed: KBoolean, optional: KBoolean): KPtr {
        throw new Error("Not implemented")
    }
    _MemberExpressionObject(context: KPtr, node: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _MemberExpressionProperty(context: KPtr, node: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _MemberExpressionKindConst(context: KPtr, node: KPtr): KInt {
        throw new Error("Not implemented")
    }
    _CreateCallExpression(context: KPtr, callee: KPtr, args: KPtrArray, argsLen: KInt, typeParams: KPtr, optional: KBoolean, trailingComma: KBoolean): KPtr {
        throw new Error("Not implemented")
    }
    _UpdateCallExpression(node: KPtr, context: KPtr, callee: KPtr, args: KPtrArray, argsLen: KInt, typeParams: KPtr, optional: KBoolean, trailingComma: KBoolean): KPtr {
        throw new Error("Not implemented")
    }
    _CreateArrowFunctionExpression(context: KPtr, node: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _FunctionExpressionFunction(context: KPtr, node: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _ArrowFunctionExpressionFunction(context: KPtr, node: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _ArrowFunctionExpressionCreateTypeAnnotation(context: KPtr, node: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _CreateFunctionExpression(context: KPtr, node: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _UpdateFunctionExpression(context: KPtr, original: KPtr, node: KPtr): KPtr {
        throw new Error("Not implemented")
    }

    _CreateExpressionStatement(context: KPtr, expr: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _UpdateExpressionStatement(context: KPtr, node: KPtr, expr: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _CreateETSParameterExpression(context: KPtr, identifier: KPtr, initializer: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _CreateETSPrimitiveType(context: KPtr, type: KInt): KPtr {
        throw new Error("Not implemented")
    }
    _ETSPrimitiveTypeGetPrimitiveTypeConst(context: KPtr, node: KNativePointer): KInt {
        throw new Error("Not implemented")
    }
    _CreateETSTypeReference(context: KPtr, part: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _CreateETSTypeReferencePart(context: KPtr, name: KPtr, typeParams: KPtr, prev: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _CreateETSTypeReferencePart1(context: KPtr, name: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _IsIdentifier(node: KPtr): KBoolean {
        throw new Error("Not implemented")
    }
    _IdentifierName(context: KPtr, node: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _ETSParameterExpressionIdent(context: KPtr, node: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _ETSParameterExpressionAnnotations(context: KPtr, node: KPtr, returnLen: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _ETSParameterExpressionSetAnnotations(context: KPtr, ast: KPtr, annotations: KPtrArray, annotationsLen: KInt): KPtr {
        throw new Error("Not implemented")
    }
    _CreateTSTypeParameterDeclaration(context: KPtr, params: KPtrArray, paramsLen: KInt, requiredParams: KInt): KPtr {
        throw new Error("Not implemented")
    }
    _TSTypeParameterDeclarationParamsConst(context: KPtr, node: KPtr, returnTypeLen: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _CreateTSTypeParameter(context: KPtr, name: KPtr, constraint: KPtr, defaultType: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _TSTypeParameterName(context: KPtr, node: KPtr): KPtr {
        throw new Error("Not implemented")
    }

    _CreateTSUnionType(context: KPtr, types: KPtrArray, typesLen: KInt): KPtr {
        throw new Error("Not implemented")
    }
    _TSUnionTypeTypesConst(context: KPtr, node: KPtr, returnTypeLen: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _CreateETSUnionTypeIr(context: KPtr, types: KPtrArray, typesLen: KInt): KPtr {
        throw new Error("Not implemented")
    }
    _ETSUnionTypeIrTypesConst(context: KPtr, node: KPtr, returnTypeLen: KPtr): KPtr {
        throw new Error("Not implemented")
    }

    _CreateVariableDeclaration(context: KPtr, kind: KInt, declarators: KPtrArray, declaratorsLen: KInt): KPtr {
        throw new Error("Not implemented")
    }
    _UpdateVariableDeclaration(context: KPtr, original: KPtr, kind: KInt, declarators: KPtrArray, declaratorsLen: KInt, declare: KBoolean): KPtr {
        throw new Error("Not implemented")
    }
    _CreateVariableDeclarator(context: KPtr, flag: KInt, ident: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _VariableDeclarationDeclaratorsConst(context: KPtr, node: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _VariableDeclarationKindConst(context: KPtr, node: KPtr): KInt {
        throw new Error("Not implemented")
    }
    _VariableDeclaratorId(context: KPtr, node: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _VariableDeclaratorSetInit(context: KPtr, node: KPtr, init: KPtr): void {
        throw new Error("Not implemented")
    }

    _CreateStringLiteral(context: KPtr, string: string): KPtr {
        throw new Error("Not implemented")
    }
    _CreateNumberLiteral(context: KPtr, value: KDouble): KPtr {
        throw new Error("Not implemented")
    }
    _NumberLiteralStrConst(context: KPtr, node: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _StringLiteralStrConst(context: KPtr, node: KPtr): KPtr {
        throw new Error("Not implemented")
    }

    _BlockStatementStatements(context: KPtr, node: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _BlockStatementSetStatements(context: KPtr, node: KPtr, statements: KPtrArray, statementsLen: KInt): void {
        throw new Error("Not implemented")
    }
    _ClassDeclarationDefinition(context: KPtr, node: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _ClassDefinitionBody(context: KPtr, node: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _ClassDefinitionIdent(context: KPtr, node: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _ClassDefinitionTypeParamsConst(context: KPtr, node: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _CreateETSStructDeclaration(context: KPtr, def: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _CreateClassDeclaration(context: KPtr, def: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _UpdateClassDeclaration(context: KPtr, original: KPtr, def: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _CreateClassDefinition1(context: KPtr, ident: KPtr, body: KPtrArray, bodyLen: KInt, modifiers: KInt, flags: KInt): KPtr {
        throw new Error("Not implemented")
    }
    _ClassDefinitionSetTypeParams(context: KPtr, ast: KPtr, typeParams: KPtr): void {
        throw new Error("Not implemented")
    }
    _ClassDefinitionSetSuper(context: KPtr, ast: KPtr, superClass: KPtr): void {
        throw new Error("Not implemented")
    }
    _UpdateClassDefinition1(context: KPtr, original: KPtr, ident: KPtr, body: KPtrArray, bodyLen: KInt, modifiers: KInt, flags: KInt): KPtr {
        throw new Error("Not implemented")
    }
    _CreateETSFunctionTypeIr(context: KPtr, signature: KPtr, funcFlags: KInt): KPtr {
        throw new Error("Not implemented")
    }
    _CreateSuperExpression(context: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _UpdateSuperExpression(context: KPtr, original: KPtr): KPtr {
        throw new Error("Not implemented")
    }

    _IsProgram(context: KPtr, node: KPtr): KBoolean {
        throw new Error("Not implemented")
    }
    _AstNodeDumpJSONConst(context: KPtr, node: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _AstNodeDumpEtsSrcConst(context: KPtr, node: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _AstNodeUpdateChildren(context: KPtr, node: KPtr): void {
        throw new Error("Not implemented")
    }
    _AstNodeUpdateAll(context: KPtr, node: KPtr): void {
        throw new Error("Not implemented")
    }
    _AstNodeSetOriginalNode(context: KPtr, ast: KPtr, originalNode: KPtr): void {
        throw new Error("Not implemented")
    }
    _AstNodeOriginalNodeConst(context: KPtr, ast: KPtr): KPtr {
        throw new Error("Not implemented")
    }

    _VarBinderSetProgram(context: KPtr): void {
        throw new Error("Not implemented")
    }
    _VarBinderSetContext(context: KPtr): void {
        throw new Error("Not implemented")
    }

    _VariableDeclaration(context: KPtr, variable: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _DeclNode(context: KPtr, decl: KPtr): KPtr {
        throw new Error("Not implemented")
    }

    _ScopeSetParent(context: KPtr, ast: KPtr, scope: KPtr): void {
        throw new Error("Not implemented")
    }

    _CallExpressionSignature(context: KPtr, classInstance: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _SignatureFunction(context: KPtr, classInstance: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _DeclarationFromIdentifier(context: KPtr, identifier: KPtr): KPtr {
        throw new Error("Not implemented")
    }
    _IsTSInterfaceDeclaration(ast: KNativePointer): KBoolean {
        throw new Error("Not implemented")
    }

    _IsAnnotationDeclaration(ast: KNativePointer): KBoolean {
        throw new Error("Not implemented")
    }

    _IsAnnotationUsage(ast: KNativePointer): KBoolean {
        throw new Error("Not implemented")
    }

    _IsClassProperty(ast: KNativePointer): KBoolean {
        throw new Error("Not implemented")
    }

    _CreateAnnotationUsageIr(context: KPtr, ast: KPtr): KPtr {
        throw new Error("Not implemented")
    }
}

export function initEs2panda(): Es2pandaNativeModule {
    registerNativeModuleLibraryName("NativeModule", path.resolve(__dirname, "../native/build/es2panda.node"))
    const instance = new Es2pandaNativeModule()
    loadNativeModuleLibrary("NativeModule", instance)
    return instance
}

export function initGeneratedEs2panda(): GeneratedEs2pandaNativeModule {
    registerNativeModuleLibraryName("NativeModule", path.resolve(__dirname, "../native/build/es2panda.node"))
    const instance = new GeneratedEs2pandaNativeModule()
    // registerNativeModule("InteropNativeModule", NativeModule)
    loadNativeModuleLibrary("NativeModule", instance)
    return instance
}