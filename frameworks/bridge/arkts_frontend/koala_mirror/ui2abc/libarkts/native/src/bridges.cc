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

#include "common.h"

#include <set>
#include <string>
#include <mutex>

std::set<std::string> globalStructInfo;
std::mutex g_structMutex;

void impl_InsertGlobalStructInfo(KNativePointer contextPtr, KStringPtr& instancePtr)
{
    std::lock_guard<std::mutex> lock(g_structMutex);
    globalStructInfo.insert(getStringCopy(instancePtr));
    return;
}
KOALA_INTEROP_V2(InsertGlobalStructInfo, KNativePointer, KStringPtr);

KBoolean impl_HasGlobalStructInfo(KNativePointer contextPtr, KStringPtr& instancePtr)
{
    std::lock_guard<std::mutex> lock(g_structMutex);
    return globalStructInfo.count(getStringCopy(instancePtr));
}
KOALA_INTEROP_2(HasGlobalStructInfo, KBoolean, KNativePointer, KStringPtr);

KNativePointer impl_AstNodeRecheck(KNativePointer contextPtr, KNativePointer nodePtr)
{
    auto context = reinterpret_cast<es2panda_Context*>(contextPtr);
    auto node = reinterpret_cast<es2panda_AstNode*>(nodePtr);
    GetImpl()->AstNodeRecheck(context, node);
    return nullptr;
}
KOALA_INTEROP_2(AstNodeRecheck, KNativePointer, KNativePointer, KNativePointer)

KNativePointer impl_AstNodeRebind(KNativePointer contextPtr, KNativePointer nodePtr)
{
    auto context = reinterpret_cast<es2panda_Context*>(contextPtr);
    auto node = reinterpret_cast<es2panda_AstNode*>(nodePtr);
    GetImpl()->AstNodeRebind(context, node);
    return nullptr;
}
KOALA_INTEROP_2(AstNodeRebind, KNativePointer, KNativePointer, KNativePointer)

KNativePointer impl_AnnotationAllowedAnnotations(KNativePointer contextPtr, KNativePointer nodePtr, KNativePointer returnLen)
{
    auto context = reinterpret_cast<es2panda_Context*>(contextPtr);
    auto node = reinterpret_cast<es2panda_AstNode*>(nodePtr);
    std::size_t params_len = 0;
    auto annotations = GetImpl()->AnnotationAllowedAnnotations(context, node, &params_len);
    return StageArena::cloneVector(annotations, params_len);
}
KOALA_INTEROP_3(AnnotationAllowedAnnotations, KNativePointer, KNativePointer, KNativePointer, KNativePointer)

KNativePointer impl_AnnotationAllowedAnnotationsConst(KNativePointer contextPtr, KNativePointer nodePtr, KNativePointer returnLen)
{
    auto context = reinterpret_cast<es2panda_Context*>(contextPtr);
    auto node = reinterpret_cast<es2panda_AstNode*>(nodePtr);
    std::size_t params_len = 0;
    auto annotations = GetImpl()->AnnotationAllowedAnnotationsConst(context, node, &params_len);
    return StageArena::cloneVector(annotations, params_len);
}
KOALA_INTEROP_3(AnnotationAllowedAnnotationsConst, KNativePointer, KNativePointer, KNativePointer, KNativePointer)

KNativePointer impl_AstNodeVariableConst(KNativePointer contextPtr, KNativePointer nodePtr)
{
    auto context = reinterpret_cast<es2panda_Context*>(contextPtr);
    auto node = reinterpret_cast<es2panda_AstNode*>(nodePtr);

    return GetImpl()->AstNodeVariableConst(context, node);
}
KOALA_INTEROP_2(AstNodeVariableConst, KNativePointer, KNativePointer, KNativePointer)

KNativePointer impl_VariableDeclaration(KNativePointer contextPtr, KNativePointer variablePtr)
{
    auto context = reinterpret_cast<es2panda_Context*>(contextPtr);
    auto variable = reinterpret_cast<es2panda_Variable*>(variablePtr);

    return GetImpl()->VariableDeclaration(context, variable);
}
KOALA_INTEROP_2(VariableDeclaration, KNativePointer, KNativePointer, KNativePointer)

KNativePointer impl_DeclNode(KNativePointer contextPtr, KNativePointer declPtr)
{
    auto context = reinterpret_cast<es2panda_Context*>(contextPtr);
    auto decl = reinterpret_cast<es2panda_Declaration*>(declPtr);

    return GetImpl()->DeclNode(context, decl);
}
KOALA_INTEROP_2(DeclNode, KNativePointer, KNativePointer, KNativePointer)

KNativePointer impl_AstNodeScopeConst(KNativePointer contextPtr, KNativePointer nodePtr)
{
    auto context = reinterpret_cast<es2panda_Context*>(contextPtr);
    auto node = reinterpret_cast<es2panda_AstNode*>(nodePtr);
    return GetImpl()->AstNodeScopeConst(context, node);
}
KOALA_INTEROP_2(AstNodeScopeConst, KNativePointer, KNativePointer, KNativePointer)

KNativePointer impl_ScopeSetParent(KNativePointer contextPtr, KNativePointer nodePtr, KNativePointer parentPtr)
{
    auto context = reinterpret_cast<es2panda_Context*>(contextPtr);
    auto node = reinterpret_cast<es2panda_Scope*>(nodePtr);
    auto parent = reinterpret_cast<es2panda_Scope*>(parentPtr);
    GetImpl()->ScopeSetParent(context, node, parent);
    return node;
}
KOALA_INTEROP_3(ScopeSetParent, KNativePointer, KNativePointer, KNativePointer, KNativePointer)

KNativePointer impl_ETSParserCreateExpression(KNativePointer contextPtr, KStringPtr& sourceCodePtr, KInt flagsT)
{
    auto context = reinterpret_cast<es2panda_Context*>(contextPtr);
    auto flags = static_cast<Es2pandaExpressionParseFlags>(flagsT);

    return GetImpl()->ETSParserCreateExpression(context, getStringCopy(sourceCodePtr), flags);
}
KOALA_INTEROP_3(ETSParserCreateExpression, KNativePointer, KNativePointer, KStringPtr, KInt)

KBoolean impl_IsProgram(KNativePointer contextPtr, KNativePointer nodePtr)
{
    auto context = reinterpret_cast<es2panda_Context*>(contextPtr);
    auto node = reinterpret_cast<es2panda_AstNode*>(nodePtr);
    return GetImpl()->AstNodeIsProgramConst(context, node);
}
KOALA_INTEROP_2(IsProgram, KBoolean, KNativePointer, KNativePointer)

KBoolean impl_IsBlockStatement(KNativePointer nodePtr)
{
    auto node = reinterpret_cast<es2panda_AstNode*>(nodePtr);
    return GetImpl()->IsBlockStatement(node);
}
KOALA_INTEROP_1(IsBlockStatement, KBoolean, KNativePointer)

KNativePointer impl_ProceedToState(KNativePointer contextPtr, KInt state)
{
    auto context = reinterpret_cast<es2panda_Context*>(contextPtr);
    return GetImpl()->ProceedToState(context, intToState(state));
}
KOALA_INTEROP_2(ProceedToState, KNativePointer, KNativePointer, KInt)

KNativePointer impl_ContextProgram(KNativePointer contextPtr)
{
    auto context = reinterpret_cast<es2panda_Context*>(contextPtr);
    return GetImpl()->ContextProgram(context);
}
KOALA_INTEROP_1(ContextProgram, KNativePointer, KNativePointer)

KNativePointer impl_ProgramAst(KNativePointer contextPtr, KNativePointer programPtr)
{
    auto context = reinterpret_cast<es2panda_Context*>(contextPtr);
    auto program = reinterpret_cast<es2panda_Program*>(programPtr);
    return GetImpl()->ProgramAst(context, program);
}
KOALA_INTEROP_2(ProgramAst, KNativePointer, KNativePointer, KNativePointer)

KBoolean impl_IsIdentifier(KNativePointer nodePtr)
{
    auto node = reinterpret_cast<es2panda_AstNode*>(nodePtr);
    return GetImpl()->IsIdentifier(node);
}
KOALA_INTEROP_1(IsIdentifier, KBoolean, KNativePointer)

KNativePointer impl_CreateContextFromString(KNativePointer configPtr, KStringPtr& sourcePtr, KStringPtr& filenamePtr)
{
    auto config = reinterpret_cast<es2panda_Config*>(configPtr);
    return GetImpl()->CreateContextFromString(config, sourcePtr.data(), filenamePtr.data());
}
KOALA_INTEROP_3(CreateContextFromString, KNativePointer, KNativePointer, KStringPtr, KStringPtr)

KNativePointer impl_CreateContextFromFile(KNativePointer configPtr, KStringPtr& filenamePtr)
{
    auto config = reinterpret_cast<es2panda_Config*>(configPtr);
    return GetImpl()->CreateContextFromFile(config, getStringCopy(filenamePtr));
}
KOALA_INTEROP_2(CreateContextFromFile, KNativePointer, KNativePointer, KStringPtr)

KInt impl_ContextState(KNativePointer contextPtr)
{
    auto context = reinterpret_cast<es2panda_Context*>(contextPtr);

    return static_cast<KInt>(GetImpl()->ContextState(context));
}
KOALA_INTEROP_1(ContextState, KInt, KNativePointer)

KNativePointer impl_ContextErrorMessage(KNativePointer contextPtr)
{
    auto context = reinterpret_cast<es2panda_Context*>(contextPtr);

    return StageArena::strdup(GetImpl()->ContextErrorMessage(context));
}
KOALA_INTEROP_1(ContextErrorMessage, KNativePointer, KNativePointer)

KNativePointer impl_CallExpressionSignature(KNativePointer context, KNativePointer classInstance)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _classInstance = reinterpret_cast<es2panda_AstNode*>(classInstance);
    const auto result = GetImpl()->CallExpressionSignature(_context, _classInstance);
    return result;
}
KOALA_INTEROP_2(CallExpressionSignature, KNativePointer, KNativePointer, KNativePointer)

KNativePointer impl_SignatureFunction(KNativePointer context, KNativePointer classInstance)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _classInstance = reinterpret_cast<es2panda_Signature*>(classInstance);
    const auto result = GetImpl()->SignatureFunction(_context, _classInstance);
    return result;
}
KOALA_INTEROP_2(SignatureFunction, KNativePointer, KNativePointer, KNativePointer)

KNativePointer impl_DeclarationFromIdentifier(KNativePointer context, KNativePointer identifier)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _identifier = reinterpret_cast<es2panda_AstNode*>(identifier);
    const auto result = GetImpl()->DeclarationFromIdentifier(_context, _identifier);
    return result;
}
KOALA_INTEROP_2(DeclarationFromIdentifier, KNativePointer, KNativePointer, KNativePointer)

static KNativePointer impl_ProgramExternalSources(KNativePointer contextPtr, KNativePointer instancePtr)
{
    auto context = reinterpret_cast<es2panda_Context*>(contextPtr);
    auto&& instance = reinterpret_cast<es2panda_Program *>(instancePtr);
    std::size_t source_len = 0;
    auto external_sources = GetImpl()->ProgramExternalSources(context, instance, &source_len);
    return StageArena::cloneVector(external_sources, source_len);
}
KOALA_INTEROP_2(ProgramExternalSources, KNativePointer, KNativePointer, KNativePointer);

static KNativePointer impl_ProgramDirectExternalSources(KNativePointer contextPtr, KNativePointer instancePtr)
{
    auto context = reinterpret_cast<es2panda_Context*>(contextPtr);
    auto&& instance = reinterpret_cast<es2panda_Program *>(instancePtr);
    std::size_t sourceLen = 0;
    auto externalSources = GetImpl()->ProgramDirectExternalSources(context, instance, &sourceLen);
    return new std::vector<void*>(externalSources, externalSources + sourceLen);
}
KOALA_INTEROP_2(ProgramDirectExternalSources, KNativePointer, KNativePointer, KNativePointer);

static KNativePointer impl_ProgramModuleNameConst(KNativePointer contextPtr, KNativePointer instancePtr)
{
    auto context = reinterpret_cast<es2panda_Context*>(contextPtr);
    auto program = reinterpret_cast<es2panda_Program*>(instancePtr);
    auto result = GetImpl()->ProgramModuleNameConst(context, program);
    return new std::string(result);
}
KOALA_INTEROP_2(ProgramModuleNameConst, KNativePointer, KNativePointer, KNativePointer);

static KNativePointer impl_ExternalSourceName(KNativePointer instance)
{
    auto&& _instance_ = reinterpret_cast<es2panda_ExternalSource *>(instance);
    auto&& result = GetImpl()->ExternalSourceName(_instance_);
    return StageArena::strdup(result);
}
KOALA_INTEROP_1(ExternalSourceName, KNativePointer, KNativePointer);

static KNativePointer impl_ExternalSourcePrograms(KNativePointer instance)
{
    auto&& _instance_ = reinterpret_cast<es2panda_ExternalSource *>(instance);
    std::size_t program_len = 0;
    auto programs = GetImpl()->ExternalSourcePrograms(_instance_, &program_len);
    return StageArena::cloneVector(programs, program_len);
}
KOALA_INTEROP_1(ExternalSourcePrograms, KNativePointer, KNativePointer);

KBoolean impl_IsClassProperty(KNativePointer nodePtr)
{
    auto node = reinterpret_cast<es2panda_AstNode*>(nodePtr);
    return GetImpl()->IsClassProperty(node);
}
KOALA_INTEROP_1(IsClassProperty, KBoolean, KNativePointer)

KBoolean impl_IsETSUnionType(KNativePointer nodePtr)
{
    auto node = reinterpret_cast<es2panda_AstNode*>(nodePtr);
    return GetImpl()->IsETSUnionType(node);
}
KOALA_INTEROP_1(IsETSUnionType, KBoolean, KNativePointer)

KBoolean impl_IsETSFunctionType(KNativePointer nodePtr)
{
    auto node = reinterpret_cast<es2panda_AstNode*>(nodePtr);
    return GetImpl()->IsETSFunctionType(node);
}
KOALA_INTEROP_1(IsETSFunctionType, KBoolean, KNativePointer)

KNativePointer impl_ETSParserBuildImportDeclaration(KNativePointer context, KNativePointer source,
                                               KNativePointerArray specifiers, KUInt specifiersSequenceLength,
                                               KInt importKind, KNativePointer programPtr, KInt flags)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _source = reinterpret_cast<es2panda_AstNode*>(source);
    const auto _specifiers = reinterpret_cast<es2panda_AstNode**>(specifiers);
    const auto _specifiersSequenceLength = static_cast<KUInt>(specifiersSequenceLength);
    const auto _importKind = static_cast<Es2pandaImportKinds>(importKind);
    const auto _program = reinterpret_cast<es2panda_Program*>(programPtr);
    const auto _flags = static_cast<Es2pandaImportFlags>(flags);
    auto result = GetImpl()->ETSParserBuildImportDeclaration(_context, _importKind, _specifiers,
                                                             _specifiersSequenceLength, _source, _program, _flags);
    return result;
}
KOALA_INTEROP_7(ETSParserBuildImportDeclaration, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray,
                KUInt, KInt, KNativePointer, KInt)

KInt impl_GenerateTsDeclarationsFromContext(KNativePointer contextPtr, KStringPtr &outputDeclEts, KStringPtr &outputEts,
                                            KBoolean exportAll)
{
    auto context = reinterpret_cast<es2panda_Context *>(contextPtr);
    return GetImpl()->GenerateTsDeclarationsFromContext(context, outputDeclEts.data(), outputEts.data(), exportAll);
}
KOALA_INTEROP_4(GenerateTsDeclarationsFromContext, KInt, KNativePointer, KStringPtr, KStringPtr, KBoolean)

KInt impl_GenerateStaticDeclarationsFromContext(KNativePointer contextPtr, KStringPtr &outputPath)
{
    auto context = reinterpret_cast<es2panda_Context *>(contextPtr);
    return GetImpl()->GenerateStaticDeclarationsFromContext(context, outputPath.data());
}
KOALA_INTEROP_2(GenerateStaticDeclarationsFromContext, KInt, KNativePointer, KStringPtr)
void impl_InsertETSImportDeclarationAndParse(KNativePointer context, KNativePointer program, KNativePointer importDeclaration)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _program = reinterpret_cast<es2panda_Program*>(program);
    const auto _import = reinterpret_cast<es2panda_AstNode*>(importDeclaration);
    GetImpl()->InsertETSImportDeclarationAndParse(_context, _program, _import);
}
KOALA_INTEROP_V3(InsertETSImportDeclarationAndParse, KNativePointer, KNativePointer, KNativePointer)

KNativePointer impl_ETSParserGetImportPathManager(KNativePointer contextPtr)
{
    auto context = reinterpret_cast<es2panda_Context*>(contextPtr);
    return GetImpl()->ETSParserGetImportPathManager(context);
}
KOALA_INTEROP_1(ETSParserGetImportPathManager, KNativePointer, KNativePointer);

KNativePointer impl_CreateSourcePosition(KNativePointer context, KInt index, KInt line)
{
    auto&& _context_ = reinterpret_cast<es2panda_Context *>(context);
    return GetImpl()->CreateSourcePosition(_context_, index, line);
}
KOALA_INTEROP_3(CreateSourcePosition, KNativePointer, KNativePointer, KInt, KInt);

KInt impl_SourcePositionIndex(KNativePointer context, KNativePointer instance)
{
    auto&& _context_ = reinterpret_cast<es2panda_Context *>(context);
    auto&& _instance_ = reinterpret_cast<es2panda_SourcePosition *>(instance);
    return GetImpl()->SourcePositionIndex(_context_, _instance_);
}
KOALA_INTEROP_2(SourcePositionIndex, KInt, KNativePointer, KNativePointer);

KInt impl_SourcePositionLine(KNativePointer context, KNativePointer instance)
{
    auto&& _context_ = reinterpret_cast<es2panda_Context *>(context);
    auto&& _instance_ = reinterpret_cast<es2panda_SourcePosition *>(instance);
    return GetImpl()->SourcePositionLine(_context_, _instance_);
}
KOALA_INTEROP_2(SourcePositionLine, KInt, KNativePointer, KNativePointer);

KNativePointer impl_CreateSourceRange(KNativePointer context, KNativePointer start, KNativePointer end)
{
    auto&& _context_ = reinterpret_cast<es2panda_Context *>(context);
    auto&& _start_ = reinterpret_cast<es2panda_SourcePosition *>(start);
    auto&& _end_ = reinterpret_cast<es2panda_SourcePosition *>(end);
    return GetImpl()->CreateSourceRange(_context_, _start_, _end_);
}
KOALA_INTEROP_3(CreateSourceRange, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ProgramFileNameConst(KNativePointer contextPtr, KNativePointer programPtr)
{
    auto context = reinterpret_cast<es2panda_Context*>(contextPtr);
    auto program = reinterpret_cast<es2panda_Program*>(programPtr);
    auto result = GetImpl()->ProgramFileNameConst(context, program);
    return new std::string(result);
}
KOALA_INTEROP_2(ProgramFileNameConst, KNativePointer, KNativePointer, KNativePointer)

KNativePointer impl_ProgramFileNameWithExtensionConst(KNativePointer contextPtr, KNativePointer programPtr)
{
    auto context = reinterpret_cast<es2panda_Context*>(contextPtr);
    auto program = reinterpret_cast<es2panda_Program*>(programPtr);
    auto result = GetImpl()->ProgramFileNameWithExtensionConst(context, program);
    return new std::string(result);
}
KOALA_INTEROP_2(ProgramFileNameWithExtensionConst, KNativePointer, KNativePointer, KNativePointer)

KBoolean impl_ProgramIsASTLoweredConst(KNativePointer contextPtr, KNativePointer instancePtr)
{
    auto context = reinterpret_cast<es2panda_Context *>(contextPtr);
    auto &&instance = reinterpret_cast<es2panda_Program *>(instancePtr);
    return GetImpl()->ProgramIsASTLoweredConst(context, instance);
}
KOALA_INTEROP_2(ProgramIsASTLoweredConst, KBoolean, KNativePointer, KNativePointer);

KNativePointer impl_ETSParserGetGlobalProgramAbsName(KNativePointer contextPtr)
{
    auto context = reinterpret_cast<es2panda_Context*>(contextPtr);
    auto result = GetImpl()->ETSParserGetGlobalProgramAbsName(context);
    return new std::string(result);
}
KOALA_INTEROP_1(ETSParserGetGlobalProgramAbsName, KNativePointer, KNativePointer)

KNativePointer impl_ClassVariableDeclaration(KNativePointer context, KNativePointer classInstance)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _classInstance = reinterpret_cast<es2panda_AstNode*>(classInstance);
    auto _typedTsType = GetImpl()->TypedTsType(_context, _classInstance);
    if (_typedTsType == nullptr) {
        return nullptr;
    }
    const auto _instanceType = reinterpret_cast<es2panda_Type*>(_typedTsType);
    auto _typeVar = GetImpl()->TypeVariable(_context, _instanceType);
    if (_typeVar == nullptr) {
        return nullptr;
    }
    const auto result = reinterpret_cast<es2panda_Declaration*>(GetImpl()->VariableDeclaration(_context, _typeVar));
    const auto declNode = GetImpl()->DeclNode(_context, result);
    return declNode;
}
KOALA_INTEROP_2(ClassVariableDeclaration, KNativePointer, KNativePointer, KNativePointer)

KBoolean impl_IsMethodDefinition(KNativePointer nodePtr)
{
    auto node = reinterpret_cast<es2panda_AstNode*>(nodePtr);
    return GetImpl()->IsMethodDefinition(node);
}
KOALA_INTEROP_1(IsMethodDefinition, KBoolean, KNativePointer)
KNativePointer impl_TSInterfaceBodyBodyPtr(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->TSInterfaceBodyBodyPtr(_context, _receiver, &length);
    return new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(TSInterfaceBodyBodyPtr, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_AnnotationDeclarationPropertiesPtrConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->AnnotationDeclarationPropertiesPtrConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(AnnotationDeclarationPropertiesPtrConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_SourceRangeStart(KNativePointer context, KNativePointer range)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _range = reinterpret_cast<es2panda_SourceRange*>(range);
    auto result = GetImpl()->SourceRangeStart(_context, _range);
    return result;
}
KOALA_INTEROP_2(SourceRangeStart, KNativePointer, KNativePointer, KNativePointer)

KNativePointer impl_SourceRangeEnd(KNativePointer context, KNativePointer range)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _range = reinterpret_cast<es2panda_SourceRange*>(range);
    auto result = GetImpl()->SourceRangeEnd(_context, _range);
    return result;
}
KOALA_INTEROP_2(SourceRangeEnd, KNativePointer, KNativePointer, KNativePointer)

KBoolean impl_IsArrayExpression(KNativePointer nodePtr)
{
    auto node = reinterpret_cast<es2panda_AstNode*>(nodePtr);
    return GetImpl()->IsArrayExpression(node);
}
KOALA_INTEROP_1(IsArrayExpression, KBoolean, KNativePointer)

KNativePointer impl_CreateDiagnosticKind(KNativePointer context, KStringPtr& message, KInt type)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _message = getStringCopy(message);
    const auto _type = static_cast<es2panda_PluginDiagnosticType>(type);
    return const_cast<es2panda_DiagnosticKind *>(GetImpl()->CreateDiagnosticKind(_context, _message, _type));
}
KOALA_INTEROP_3(CreateDiagnosticKind, KNativePointer, KNativePointer, KStringPtr, KInt);

inline KUInt unpackUInt(const KByte* bytes)
{
    const KUInt BYTE_0 = 0;
    const KUInt BYTE_1 = 1;
    const KUInt BYTE_2 = 2;
    const KUInt BYTE_3 = 3;

    const KUInt BYTE_1_SHIFT = 8;
    const KUInt BYTE_2_SHIFT = 16;
    const KUInt BYTE_3_SHIFT = 24;
    return (bytes[BYTE_0] | (bytes[BYTE_1] << BYTE_1_SHIFT)
        | (bytes[BYTE_2] << BYTE_2_SHIFT) | (bytes[BYTE_3] << BYTE_3_SHIFT)
    );
}

KNativePointer impl_CreateDiagnosticInfo(KNativePointer context, KNativePointer kind, KStringArray argsPtr, KInt argc)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _kind = reinterpret_cast<es2panda_DiagnosticKind*>(kind);
    const std::size_t headerLen = 4;
    const char** _args = new const char*[argc];
    std::size_t position = headerLen;
    std::size_t strLen;
    for (std::size_t i = 0; i < static_cast<std::size_t>(argc); ++i) {
        strLen = unpackUInt(argsPtr + position);
        position += headerLen;
        _args[i] = strdup(std::string(reinterpret_cast<const char*>(argsPtr + position), strLen).c_str());
        position += strLen;
    }
    return GetImpl()->CreateDiagnosticInfo(_context, _kind, _args, argc);
}
KOALA_INTEROP_4(CreateDiagnosticInfo, KNativePointer, KNativePointer, KNativePointer, KStringArray, KInt);

KNativePointer impl_CreateSuggestionInfo(KNativePointer context, KNativePointer kind, KStringArray argsPtr,
                                         KInt argc, KStringPtr& substitutionCode)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _kind = reinterpret_cast<es2panda_DiagnosticKind *>(kind);
    const std::size_t headerLen = 4;
    const char** _args = new const char*[argc];
    std::size_t position = headerLen;
    std::size_t strLen;
    for (std::size_t i = 0; i < static_cast<std::size_t>(argc); ++i) {
        strLen = unpackUInt(argsPtr + position);
        position += headerLen;
        _args[i] = strdup(std::string(reinterpret_cast<const char*>(argsPtr + position), strLen).c_str());
        position += strLen;
    }
    const auto _substitutionCode = getStringCopy(substitutionCode);
    return GetImpl()->CreateSuggestionInfo(_context, _kind, _args, argc, _substitutionCode);
}
KOALA_INTEROP_5(CreateSuggestionInfo, KNativePointer, KNativePointer, KNativePointer,
                KStringArray, KInt, KStringPtr);

void impl_LogDiagnostic(KNativePointer context, KNativePointer kind, KStringArray argvPtr,
                        KInt argc, KNativePointer pos)
{
    auto&& _context_ = reinterpret_cast<es2panda_Context *>(context);
    auto&& _kind_ = reinterpret_cast<es2panda_DiagnosticKind *>(kind);
    auto&& _pos_ = reinterpret_cast<es2panda_SourcePosition *>(pos);
    const std::size_t headerLen = 4;
    const char** argv = new const char*[argc];
    std::size_t position = headerLen;
    std::size_t strLen;
    for (std::size_t i = 0; i < static_cast<std::size_t>(argc); ++i) {
        strLen = unpackUInt(argvPtr + position);
        position += headerLen;
        argv[i] = strdup(std::string(reinterpret_cast<const char*>(argvPtr + position), strLen).c_str());
        position += strLen;
    }
    GetImpl()->LogDiagnostic(_context_, _kind_, argv, argc, _pos_);
}
KOALA_INTEROP_V5(LogDiagnostic, KNativePointer, KNativePointer, KStringArray, KInt, KNativePointer);

void impl_LogDiagnosticWithSuggestion(KNativePointer context, KNativePointer diagnosticInfo,
                                      KNativePointer suggestionInfo, KNativePointer range)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _diagnosticInfo = reinterpret_cast<es2panda_DiagnosticInfo*>(diagnosticInfo);
    const auto _suggestionInfo = reinterpret_cast<es2panda_SuggestionInfo*>(suggestionInfo);
    const auto _range = reinterpret_cast<es2panda_SourceRange*>(range);
    GetImpl()->LogDiagnosticWithSuggestion(_context, _diagnosticInfo, _suggestionInfo, _range);
}
KOALA_INTEROP_V4(LogDiagnosticWithSuggestion, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_AnnotationUsageIrPropertiesPtrConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->AnnotationUsageIrPropertiesPtrConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(AnnotationUsageIrPropertiesPtrConst, KNativePointer, KNativePointer, KNativePointer);