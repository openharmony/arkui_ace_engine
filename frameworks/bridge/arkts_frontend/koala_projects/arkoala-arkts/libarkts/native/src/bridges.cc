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

#include "common.h"

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
    return new std::vector<void*>(annotations, annotations + params_len);
}
KOALA_INTEROP_3(AnnotationAllowedAnnotations, KNativePointer, KNativePointer, KNativePointer, KNativePointer)

KNativePointer impl_AnnotationAllowedAnnotationsConst(KNativePointer contextPtr, KNativePointer nodePtr, KNativePointer returnLen)
{
    auto context = reinterpret_cast<es2panda_Context*>(contextPtr);
    auto node = reinterpret_cast<es2panda_AstNode*>(nodePtr);
    std::size_t params_len = 0;
    auto annotations = GetImpl()->AnnotationAllowedAnnotationsConst(context, node, &params_len);
    return new std::vector<void*>(annotations, annotations + params_len);
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

KNativePointer impl_CreateNumberLiteral(KNativePointer contextPtr, KDouble value)
{
    auto context = reinterpret_cast<es2panda_Context*>(contextPtr);

    return GetImpl()->CreateNumberLiteral(context, value);
}
KOALA_INTEROP_2(CreateNumberLiteral, KNativePointer, KNativePointer, KDouble)

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
    auto context = reinterpret_cast<es2panda_Context*>(programPtr);
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

    return new string(GetImpl()->ContextErrorMessage(context));
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
    return new std::vector<void*>(external_sources, external_sources + source_len);
}
KOALA_INTEROP_2(ProgramExternalSources, KNativePointer, KNativePointer, KNativePointer);

static KNativePointer impl_ExternalSourceName(KNativePointer instance)
{
    auto&& _instance_ = reinterpret_cast<es2panda_ExternalSource *>(instance);
    auto&& _result_ = GetImpl()->ExternalSourceName(_instance_);
    return new std::string(_result_);
}
KOALA_INTEROP_1(ExternalSourceName, KNativePointer, KNativePointer);

static KNativePointer impl_ExternalSourcePrograms(KNativePointer instance)
{
    auto&& _instance_ = reinterpret_cast<es2panda_ExternalSource *>(instance);
    std::size_t program_len = 0;
    auto programs = GetImpl()->ExternalSourcePrograms(_instance_, &program_len);
    return new std::vector<void*>(programs, programs + program_len);
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
