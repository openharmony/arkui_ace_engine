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

#include <common.h>

KNativePointer impl_CreateLabelledStatement(KNativePointer context, KNativePointer ident, KNativePointer body)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _ident = reinterpret_cast<es2panda_AstNode*>(ident);
    const auto _body = reinterpret_cast<es2panda_AstNode*>(body);
    auto result = GetImpl()->CreateLabelledStatement(_context, _ident, _body);
    return result;
}
KOALA_INTEROP_3(CreateLabelledStatement, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateLabelledStatement(KNativePointer context, KNativePointer original, KNativePointer ident, KNativePointer body)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _ident = reinterpret_cast<es2panda_AstNode*>(ident);
    const auto _body = reinterpret_cast<es2panda_AstNode*>(body);
    auto result = GetImpl()->UpdateLabelledStatement(_context, _original, _ident, _body);
    return result;
}
KOALA_INTEROP_4(UpdateLabelledStatement, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_LabelledStatementBodyConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->LabelledStatementBodyConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(LabelledStatementBodyConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_LabelledStatementIdentConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->LabelledStatementIdentConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(LabelledStatementIdentConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_LabelledStatementIdent(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->LabelledStatementIdent(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(LabelledStatementIdent, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_LabelledStatementGetReferencedStatementConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->LabelledStatementGetReferencedStatementConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(LabelledStatementGetReferencedStatementConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateThrowStatement(KNativePointer context, KNativePointer argument)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _argument = reinterpret_cast<es2panda_AstNode*>(argument);
    auto result = GetImpl()->CreateThrowStatement(_context, _argument);
    return result;
}
KOALA_INTEROP_2(CreateThrowStatement, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateThrowStatement(KNativePointer context, KNativePointer original, KNativePointer argument)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _argument = reinterpret_cast<es2panda_AstNode*>(argument);
    auto result = GetImpl()->UpdateThrowStatement(_context, _original, _argument);
    return result;
}
KOALA_INTEROP_3(UpdateThrowStatement, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ThrowStatementArgumentConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ThrowStatementArgumentConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ThrowStatementArgumentConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateClassProperty(KNativePointer context, KNativePointer key, KNativePointer value, KNativePointer typeAnnotation, KInt modifiers, KBoolean isComputed)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _key = reinterpret_cast<es2panda_AstNode*>(key);
    const auto _value = reinterpret_cast<es2panda_AstNode*>(value);
    const auto _typeAnnotation = reinterpret_cast<es2panda_AstNode*>(typeAnnotation);
    const auto _modifiers = static_cast<Es2pandaModifierFlags>(modifiers);
    const auto _isComputed = static_cast<KBoolean>(isComputed);
    auto result = GetImpl()->CreateClassProperty(_context, _key, _value, _typeAnnotation, _modifiers, _isComputed);
    return result;
}
KOALA_INTEROP_6(CreateClassProperty, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KInt, KBoolean);

KNativePointer impl_UpdateClassProperty(KNativePointer context, KNativePointer original, KNativePointer key, KNativePointer value, KNativePointer typeAnnotation, KInt modifiers, KBoolean isComputed)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _key = reinterpret_cast<es2panda_AstNode*>(key);
    const auto _value = reinterpret_cast<es2panda_AstNode*>(value);
    const auto _typeAnnotation = reinterpret_cast<es2panda_AstNode*>(typeAnnotation);
    const auto _modifiers = static_cast<Es2pandaModifierFlags>(modifiers);
    const auto _isComputed = static_cast<KBoolean>(isComputed);
    auto result = GetImpl()->UpdateClassProperty(_context, _original, _key, _value, _typeAnnotation, _modifiers, _isComputed);
    return result;
}
KOALA_INTEROP_7(UpdateClassProperty, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KInt, KBoolean);

KNativePointer impl_ClassPropertyTypeAnnotationConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ClassPropertyTypeAnnotationConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ClassPropertyTypeAnnotationConst, KNativePointer, KNativePointer, KNativePointer);

void impl_ClassPropertySetTypeAnnotation(KNativePointer context, KNativePointer receiver, KNativePointer typeAnnotation)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _typeAnnotation = reinterpret_cast<es2panda_AstNode*>(typeAnnotation);
    GetImpl()->ClassPropertySetTypeAnnotation(_context, _receiver, _typeAnnotation);
    return ;
}
KOALA_INTEROP_V3(ClassPropertySetTypeAnnotation, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ClassPropertyAnnotations(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->ClassPropertyAnnotations(_context, _receiver, &length);
    return new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(ClassPropertyAnnotations, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ClassPropertyAnnotationsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->ClassPropertyAnnotationsConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(ClassPropertyAnnotationsConst, KNativePointer, KNativePointer, KNativePointer);

void impl_ClassPropertySetAnnotations(KNativePointer context, KNativePointer receiver, KNativePointerArray annotations, KUInt annotationsSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _annotations = reinterpret_cast<es2panda_AstNode**>(annotations);
    const auto _annotationsSequenceLength = static_cast<KUInt>(annotationsSequenceLength);
    GetImpl()->ClassPropertySetAnnotations(_context, _receiver, _annotations, _annotationsSequenceLength);
    return ;
}
KOALA_INTEROP_V4(ClassPropertySetAnnotations, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_CreateTSVoidKeyword(KNativePointer context)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    auto result = GetImpl()->CreateTSVoidKeyword(_context);
    return result;
}
KOALA_INTEROP_1(CreateTSVoidKeyword, KNativePointer, KNativePointer);

KNativePointer impl_UpdateTSVoidKeyword(KNativePointer context, KNativePointer original)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    auto result = GetImpl()->UpdateTSVoidKeyword(_context, _original);
    return result;
}
KOALA_INTEROP_2(UpdateTSVoidKeyword, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateETSFunctionTypeIr(KNativePointer context, KNativePointer signature, KInt funcFlags)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _signature = reinterpret_cast<es2panda_FunctionSignature*>(signature);
    const auto _funcFlags = static_cast<Es2pandaScriptFunctionFlags>(funcFlags);
    auto result = GetImpl()->CreateETSFunctionTypeIr(_context, _signature, _funcFlags);
    return result;
}
KOALA_INTEROP_3(CreateETSFunctionTypeIr, KNativePointer, KNativePointer, KNativePointer, KInt);

KNativePointer impl_UpdateETSFunctionTypeIr(KNativePointer context, KNativePointer original, KNativePointer signature, KInt funcFlags)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _signature = reinterpret_cast<es2panda_FunctionSignature*>(signature);
    const auto _funcFlags = static_cast<Es2pandaScriptFunctionFlags>(funcFlags);
    auto result = GetImpl()->UpdateETSFunctionTypeIr(_context, _original, _signature, _funcFlags);
    return result;
}
KOALA_INTEROP_4(UpdateETSFunctionTypeIr, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KInt);

KNativePointer impl_ETSFunctionTypeIrTypeParamsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSFunctionTypeIrTypeParamsConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ETSFunctionTypeIrTypeParamsConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ETSFunctionTypeIrTypeParams(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSFunctionTypeIrTypeParams(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ETSFunctionTypeIrTypeParams, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ETSFunctionTypeIrParamsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->ETSFunctionTypeIrParamsConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(ETSFunctionTypeIrParamsConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ETSFunctionTypeIrReturnTypeConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSFunctionTypeIrReturnTypeConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ETSFunctionTypeIrReturnTypeConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ETSFunctionTypeIrReturnType(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSFunctionTypeIrReturnType(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ETSFunctionTypeIrReturnType, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ETSFunctionTypeIrFunctionalInterface(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSFunctionTypeIrFunctionalInterface(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ETSFunctionTypeIrFunctionalInterface, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ETSFunctionTypeIrFunctionalInterfaceConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSFunctionTypeIrFunctionalInterfaceConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ETSFunctionTypeIrFunctionalInterfaceConst, KNativePointer, KNativePointer, KNativePointer);

void impl_ETSFunctionTypeIrSetFunctionalInterface(KNativePointer context, KNativePointer receiver, KNativePointer functionalInterface)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _functionalInterface = reinterpret_cast<es2panda_AstNode*>(functionalInterface);
    GetImpl()->ETSFunctionTypeIrSetFunctionalInterface(_context, _receiver, _functionalInterface);
    return ;
}
KOALA_INTEROP_V3(ETSFunctionTypeIrSetFunctionalInterface, KNativePointer, KNativePointer, KNativePointer);

KInt impl_ETSFunctionTypeIrFlags(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSFunctionTypeIrFlags(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ETSFunctionTypeIrFlags, KInt, KNativePointer, KNativePointer);

KBoolean impl_ETSFunctionTypeIrIsThrowingConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSFunctionTypeIrIsThrowingConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ETSFunctionTypeIrIsThrowingConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_ETSFunctionTypeIrIsRethrowingConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSFunctionTypeIrIsRethrowingConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ETSFunctionTypeIrIsRethrowingConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_ETSFunctionTypeIrIsExtensionFunctionConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSFunctionTypeIrIsExtensionFunctionConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ETSFunctionTypeIrIsExtensionFunctionConst, KBoolean, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSTypeOperator(KNativePointer context, KNativePointer type, KInt operatorType)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _type = reinterpret_cast<es2panda_AstNode*>(type);
    const auto _operatorType = static_cast<Es2pandaTSOperatorType>(operatorType);
    auto result = GetImpl()->CreateTSTypeOperator(_context, _type, _operatorType);
    return result;
}
KOALA_INTEROP_3(CreateTSTypeOperator, KNativePointer, KNativePointer, KNativePointer, KInt);

KNativePointer impl_UpdateTSTypeOperator(KNativePointer context, KNativePointer original, KNativePointer type, KInt operatorType)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _type = reinterpret_cast<es2panda_AstNode*>(type);
    const auto _operatorType = static_cast<Es2pandaTSOperatorType>(operatorType);
    auto result = GetImpl()->UpdateTSTypeOperator(_context, _original, _type, _operatorType);
    return result;
}
KOALA_INTEROP_4(UpdateTSTypeOperator, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KInt);

KNativePointer impl_TSTypeOperatorTypeConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSTypeOperatorTypeConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSTypeOperatorTypeConst, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_TSTypeOperatorIsReadonlyConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSTypeOperatorIsReadonlyConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSTypeOperatorIsReadonlyConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_TSTypeOperatorIsKeyofConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSTypeOperatorIsKeyofConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSTypeOperatorIsKeyofConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_TSTypeOperatorIsUniqueConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSTypeOperatorIsUniqueConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSTypeOperatorIsUniqueConst, KBoolean, KNativePointer, KNativePointer);

KNativePointer impl_CreateIfStatement(KNativePointer context, KNativePointer test, KNativePointer consequent, KNativePointer alternate)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _test = reinterpret_cast<es2panda_AstNode*>(test);
    const auto _consequent = reinterpret_cast<es2panda_AstNode*>(consequent);
    const auto _alternate = reinterpret_cast<es2panda_AstNode*>(alternate);
    auto result = GetImpl()->CreateIfStatement(_context, _test, _consequent, _alternate);
    return result;
}
KOALA_INTEROP_4(CreateIfStatement, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateIfStatement(KNativePointer context, KNativePointer original, KNativePointer test, KNativePointer consequent, KNativePointer alternate)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _test = reinterpret_cast<es2panda_AstNode*>(test);
    const auto _consequent = reinterpret_cast<es2panda_AstNode*>(consequent);
    const auto _alternate = reinterpret_cast<es2panda_AstNode*>(alternate);
    auto result = GetImpl()->UpdateIfStatement(_context, _original, _test, _consequent, _alternate);
    return result;
}
KOALA_INTEROP_5(UpdateIfStatement, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_IfStatementTestConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->IfStatementTestConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(IfStatementTestConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_IfStatementTest(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->IfStatementTest(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(IfStatementTest, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_IfStatementConsequentConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->IfStatementConsequentConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(IfStatementConsequentConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_IfStatementConsequent(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->IfStatementConsequent(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(IfStatementConsequent, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_IfStatementAlternate(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->IfStatementAlternate(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(IfStatementAlternate, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_IfStatementAlternateConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->IfStatementAlternateConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(IfStatementAlternateConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSConstructorType(KNativePointer context, KNativePointer signature, KBoolean abstract)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _signature = reinterpret_cast<es2panda_FunctionSignature*>(signature);
    const auto _abstract = static_cast<KBoolean>(abstract);
    auto result = GetImpl()->CreateTSConstructorType(_context, _signature, _abstract);
    return result;
}
KOALA_INTEROP_3(CreateTSConstructorType, KNativePointer, KNativePointer, KNativePointer, KBoolean);

KNativePointer impl_UpdateTSConstructorType(KNativePointer context, KNativePointer original, KNativePointer signature, KBoolean abstract)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _signature = reinterpret_cast<es2panda_FunctionSignature*>(signature);
    const auto _abstract = static_cast<KBoolean>(abstract);
    auto result = GetImpl()->UpdateTSConstructorType(_context, _original, _signature, _abstract);
    return result;
}
KOALA_INTEROP_4(UpdateTSConstructorType, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KBoolean);

KNativePointer impl_TSConstructorTypeTypeParamsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSConstructorTypeTypeParamsConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSConstructorTypeTypeParamsConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSConstructorTypeTypeParams(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSConstructorTypeTypeParams(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSConstructorTypeTypeParams, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSConstructorTypeParamsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->TSConstructorTypeParamsConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(TSConstructorTypeParamsConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSConstructorTypeReturnTypeConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSConstructorTypeReturnTypeConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSConstructorTypeReturnTypeConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSConstructorTypeReturnType(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSConstructorTypeReturnType(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSConstructorTypeReturnType, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_TSConstructorTypeAbstractConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSConstructorTypeAbstractConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSConstructorTypeAbstractConst, KBoolean, KNativePointer, KNativePointer);

KNativePointer impl_CreateDecorator(KNativePointer context, KNativePointer expr)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _expr = reinterpret_cast<es2panda_AstNode*>(expr);
    auto result = GetImpl()->CreateDecorator(_context, _expr);
    return result;
}
KOALA_INTEROP_2(CreateDecorator, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateDecorator(KNativePointer context, KNativePointer original, KNativePointer expr)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _expr = reinterpret_cast<es2panda_AstNode*>(expr);
    auto result = GetImpl()->UpdateDecorator(_context, _original, _expr);
    return result;
}
KOALA_INTEROP_3(UpdateDecorator, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_DecoratorExprConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->DecoratorExprConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(DecoratorExprConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSEnumDeclaration(KNativePointer context, KNativePointer key, KNativePointerArray members, KUInt membersSequenceLength, KBoolean isConst, KBoolean isStatic, KBoolean isDeclare)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _key = reinterpret_cast<es2panda_AstNode*>(key);
    const auto _members = reinterpret_cast<es2panda_AstNode**>(members);
    const auto _membersSequenceLength = static_cast<KUInt>(membersSequenceLength);
    const auto _isConst = static_cast<KBoolean>(isConst);
    const auto _isStatic = static_cast<KBoolean>(isStatic);
    const auto _isDeclare = static_cast<KBoolean>(isDeclare);
    auto result = GetImpl()->CreateTSEnumDeclaration(_context, _key, _members, _membersSequenceLength, _isConst, _isStatic, _isDeclare);
    return result;
}
KOALA_INTEROP_7(CreateTSEnumDeclaration, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt, KBoolean, KBoolean, KBoolean);

KNativePointer impl_UpdateTSEnumDeclaration(KNativePointer context, KNativePointer original, KNativePointer key, KNativePointerArray members, KUInt membersSequenceLength, KBoolean isConst, KBoolean isStatic, KBoolean isDeclare)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _key = reinterpret_cast<es2panda_AstNode*>(key);
    const auto _members = reinterpret_cast<es2panda_AstNode**>(members);
    const auto _membersSequenceLength = static_cast<KUInt>(membersSequenceLength);
    const auto _isConst = static_cast<KBoolean>(isConst);
    const auto _isStatic = static_cast<KBoolean>(isStatic);
    const auto _isDeclare = static_cast<KBoolean>(isDeclare);
    auto result = GetImpl()->UpdateTSEnumDeclaration(_context, _original, _key, _members, _membersSequenceLength, _isConst, _isStatic, _isDeclare);
    return result;
}
KOALA_INTEROP_8(UpdateTSEnumDeclaration, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt, KBoolean, KBoolean, KBoolean);

KNativePointer impl_TSEnumDeclarationKeyConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSEnumDeclarationKeyConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSEnumDeclarationKeyConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSEnumDeclarationKey(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSEnumDeclarationKey(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSEnumDeclarationKey, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSEnumDeclarationMembersConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->TSEnumDeclarationMembersConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(TSEnumDeclarationMembersConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSEnumDeclarationInternalNameConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSEnumDeclarationInternalNameConst(_context, _receiver);
    return new std::string(result);
}
KOALA_INTEROP_2(TSEnumDeclarationInternalNameConst, KNativePointer, KNativePointer, KNativePointer);

void impl_TSEnumDeclarationSetInternalName(KNativePointer context, KNativePointer receiver, KStringPtr& internalName)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _internalName = getStringCopy(internalName);
    GetImpl()->TSEnumDeclarationSetInternalName(_context, _receiver, _internalName);
    return ;
}
KOALA_INTEROP_V3(TSEnumDeclarationSetInternalName, KNativePointer, KNativePointer, KStringPtr);

KNativePointer impl_TSEnumDeclarationBoxedClassConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSEnumDeclarationBoxedClassConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSEnumDeclarationBoxedClassConst, KNativePointer, KNativePointer, KNativePointer);

void impl_TSEnumDeclarationSetBoxedClass(KNativePointer context, KNativePointer receiver, KNativePointer wrapperClass)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _wrapperClass = reinterpret_cast<es2panda_AstNode*>(wrapperClass);
    GetImpl()->TSEnumDeclarationSetBoxedClass(_context, _receiver, _wrapperClass);
    return ;
}
KOALA_INTEROP_V3(TSEnumDeclarationSetBoxedClass, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_TSEnumDeclarationIsConstConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSEnumDeclarationIsConstConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSEnumDeclarationIsConstConst, KBoolean, KNativePointer, KNativePointer);

KNativePointer impl_TSEnumDeclarationDecoratorsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->TSEnumDeclarationDecoratorsConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(TSEnumDeclarationDecoratorsConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSNeverKeyword(KNativePointer context)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    auto result = GetImpl()->CreateTSNeverKeyword(_context);
    return result;
}
KOALA_INTEROP_1(CreateTSNeverKeyword, KNativePointer, KNativePointer);

KNativePointer impl_UpdateTSNeverKeyword(KNativePointer context, KNativePointer original)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    auto result = GetImpl()->UpdateTSNeverKeyword(_context, _original);
    return result;
}
KOALA_INTEROP_2(UpdateTSNeverKeyword, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateImportDefaultSpecifier(KNativePointer context, KNativePointer local)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _local = reinterpret_cast<es2panda_AstNode*>(local);
    auto result = GetImpl()->CreateImportDefaultSpecifier(_context, _local);
    return result;
}
KOALA_INTEROP_2(CreateImportDefaultSpecifier, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateImportDefaultSpecifier(KNativePointer context, KNativePointer original, KNativePointer local)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _local = reinterpret_cast<es2panda_AstNode*>(local);
    auto result = GetImpl()->UpdateImportDefaultSpecifier(_context, _original, _local);
    return result;
}
KOALA_INTEROP_3(UpdateImportDefaultSpecifier, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ImportDefaultSpecifierLocalConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ImportDefaultSpecifierLocalConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ImportDefaultSpecifierLocalConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ImportDefaultSpecifierLocal(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ImportDefaultSpecifierLocal(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ImportDefaultSpecifierLocal, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateObjectExpression(KNativePointer context, KInt nodeType, KNativePointerArray properties, KUInt propertiesSequenceLength, KBoolean trailingComma)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _nodeType = static_cast<Es2pandaAstNodeType>(nodeType);
    const auto _properties = reinterpret_cast<es2panda_AstNode**>(properties);
    const auto _propertiesSequenceLength = static_cast<KUInt>(propertiesSequenceLength);
    const auto _trailingComma = static_cast<KBoolean>(trailingComma);
    auto result = GetImpl()->CreateObjectExpression(_context, _nodeType, _properties, _propertiesSequenceLength, _trailingComma);
    return result;
}
KOALA_INTEROP_5(CreateObjectExpression, KNativePointer, KNativePointer, KInt, KNativePointerArray, KUInt, KBoolean);

KNativePointer impl_UpdateObjectExpression(KNativePointer context, KNativePointer original, KInt nodeType, KNativePointerArray properties, KUInt propertiesSequenceLength, KBoolean trailingComma)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _nodeType = static_cast<Es2pandaAstNodeType>(nodeType);
    const auto _properties = reinterpret_cast<es2panda_AstNode**>(properties);
    const auto _propertiesSequenceLength = static_cast<KUInt>(propertiesSequenceLength);
    const auto _trailingComma = static_cast<KBoolean>(trailingComma);
    auto result = GetImpl()->UpdateObjectExpression(_context, _original, _nodeType, _properties, _propertiesSequenceLength, _trailingComma);
    return result;
}
KOALA_INTEROP_6(UpdateObjectExpression, KNativePointer, KNativePointer, KNativePointer, KInt, KNativePointerArray, KUInt, KBoolean);

KNativePointer impl_ObjectExpressionPropertiesConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->ObjectExpressionPropertiesConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(ObjectExpressionPropertiesConst, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_ObjectExpressionIsDeclarationConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ObjectExpressionIsDeclarationConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ObjectExpressionIsDeclarationConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_ObjectExpressionIsOptionalConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ObjectExpressionIsOptionalConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ObjectExpressionIsOptionalConst, KBoolean, KNativePointer, KNativePointer);

KNativePointer impl_ObjectExpressionDecoratorsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->ObjectExpressionDecoratorsConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(ObjectExpressionDecoratorsConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ObjectExpressionValidateExpression(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ObjectExpressionValidateExpression(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ObjectExpressionValidateExpression, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_ObjectExpressionConvertibleToObjectPattern(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ObjectExpressionConvertibleToObjectPattern(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ObjectExpressionConvertibleToObjectPattern, KBoolean, KNativePointer, KNativePointer);

void impl_ObjectExpressionSetDeclaration(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    GetImpl()->ObjectExpressionSetDeclaration(_context, _receiver);
    return ;
}
KOALA_INTEROP_V2(ObjectExpressionSetDeclaration, KNativePointer, KNativePointer);

void impl_ObjectExpressionSetOptional(KNativePointer context, KNativePointer receiver, KBoolean optional_arg)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _optional_arg = static_cast<KBoolean>(optional_arg);
    GetImpl()->ObjectExpressionSetOptional(_context, _receiver, _optional_arg);
    return ;
}
KOALA_INTEROP_V3(ObjectExpressionSetOptional, KNativePointer, KNativePointer, KBoolean);

KNativePointer impl_ObjectExpressionTypeAnnotationConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ObjectExpressionTypeAnnotationConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ObjectExpressionTypeAnnotationConst, KNativePointer, KNativePointer, KNativePointer);

void impl_ObjectExpressionSetTsTypeAnnotation(KNativePointer context, KNativePointer receiver, KNativePointer typeAnnotation)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _typeAnnotation = reinterpret_cast<es2panda_AstNode*>(typeAnnotation);
    GetImpl()->ObjectExpressionSetTsTypeAnnotation(_context, _receiver, _typeAnnotation);
    return ;
}
KOALA_INTEROP_V3(ObjectExpressionSetTsTypeAnnotation, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateImportSpecifier(KNativePointer context, KNativePointer imported, KNativePointer local)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _imported = reinterpret_cast<es2panda_AstNode*>(imported);
    const auto _local = reinterpret_cast<es2panda_AstNode*>(local);
    auto result = GetImpl()->CreateImportSpecifier(_context, _imported, _local);
    return result;
}
KOALA_INTEROP_3(CreateImportSpecifier, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateImportSpecifier(KNativePointer context, KNativePointer original, KNativePointer imported, KNativePointer local)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _imported = reinterpret_cast<es2panda_AstNode*>(imported);
    const auto _local = reinterpret_cast<es2panda_AstNode*>(local);
    auto result = GetImpl()->UpdateImportSpecifier(_context, _original, _imported, _local);
    return result;
}
KOALA_INTEROP_4(UpdateImportSpecifier, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ImportSpecifierImported(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ImportSpecifierImported(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ImportSpecifierImported, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ImportSpecifierImportedConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ImportSpecifierImportedConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ImportSpecifierImportedConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ImportSpecifierLocal(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ImportSpecifierLocal(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ImportSpecifierLocal, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ImportSpecifierLocalConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ImportSpecifierLocalConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ImportSpecifierLocalConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateConditionalExpression(KNativePointer context, KNativePointer test, KNativePointer consequent, KNativePointer alternate)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _test = reinterpret_cast<es2panda_AstNode*>(test);
    const auto _consequent = reinterpret_cast<es2panda_AstNode*>(consequent);
    const auto _alternate = reinterpret_cast<es2panda_AstNode*>(alternate);
    auto result = GetImpl()->CreateConditionalExpression(_context, _test, _consequent, _alternate);
    return result;
}
KOALA_INTEROP_4(CreateConditionalExpression, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateConditionalExpression(KNativePointer context, KNativePointer original, KNativePointer test, KNativePointer consequent, KNativePointer alternate)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _test = reinterpret_cast<es2panda_AstNode*>(test);
    const auto _consequent = reinterpret_cast<es2panda_AstNode*>(consequent);
    const auto _alternate = reinterpret_cast<es2panda_AstNode*>(alternate);
    auto result = GetImpl()->UpdateConditionalExpression(_context, _original, _test, _consequent, _alternate);
    return result;
}
KOALA_INTEROP_5(UpdateConditionalExpression, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ConditionalExpressionTestConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ConditionalExpressionTestConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ConditionalExpressionTestConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ConditionalExpressionTest(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ConditionalExpressionTest(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ConditionalExpressionTest, KNativePointer, KNativePointer, KNativePointer);

void impl_ConditionalExpressionSetTest(KNativePointer context, KNativePointer receiver, KNativePointer expr)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _expr = reinterpret_cast<es2panda_AstNode*>(expr);
    GetImpl()->ConditionalExpressionSetTest(_context, _receiver, _expr);
    return ;
}
KOALA_INTEROP_V3(ConditionalExpressionSetTest, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ConditionalExpressionConsequentConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ConditionalExpressionConsequentConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ConditionalExpressionConsequentConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ConditionalExpressionConsequent(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ConditionalExpressionConsequent(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ConditionalExpressionConsequent, KNativePointer, KNativePointer, KNativePointer);

void impl_ConditionalExpressionSetConsequent(KNativePointer context, KNativePointer receiver, KNativePointer expr)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _expr = reinterpret_cast<es2panda_AstNode*>(expr);
    GetImpl()->ConditionalExpressionSetConsequent(_context, _receiver, _expr);
    return ;
}
KOALA_INTEROP_V3(ConditionalExpressionSetConsequent, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ConditionalExpressionAlternateConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ConditionalExpressionAlternateConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ConditionalExpressionAlternateConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ConditionalExpressionAlternate(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ConditionalExpressionAlternate(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ConditionalExpressionAlternate, KNativePointer, KNativePointer, KNativePointer);

void impl_ConditionalExpressionSetAlternate(KNativePointer context, KNativePointer receiver, KNativePointer expr)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _expr = reinterpret_cast<es2panda_AstNode*>(expr);
    GetImpl()->ConditionalExpressionSetAlternate(_context, _receiver, _expr);
    return ;
}
KOALA_INTEROP_V3(ConditionalExpressionSetAlternate, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateCallExpression(KNativePointer context, KNativePointer callee, KNativePointerArray _arguments, KUInt _argumentsSequenceLength, KNativePointer typeParams, KBoolean optional_arg, KBoolean trailingComma)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _callee = reinterpret_cast<es2panda_AstNode*>(callee);
    const auto __arguments = reinterpret_cast<es2panda_AstNode**>(_arguments);
    const auto __argumentsSequenceLength = static_cast<KUInt>(_argumentsSequenceLength);
    const auto _typeParams = reinterpret_cast<es2panda_AstNode*>(typeParams);
    const auto _optional_arg = static_cast<KBoolean>(optional_arg);
    const auto _trailingComma = static_cast<KBoolean>(trailingComma);
    auto result = GetImpl()->CreateCallExpression(_context, _callee, __arguments, __argumentsSequenceLength, _typeParams, _optional_arg, _trailingComma);
    return result;
}
KOALA_INTEROP_7(CreateCallExpression, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt, KNativePointer, KBoolean, KBoolean);

KNativePointer impl_CreateCallExpression1(KNativePointer context, KNativePointer other)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _other = reinterpret_cast<es2panda_AstNode*>(other);
    auto result = GetImpl()->CreateCallExpression1(_context, _other);
    return result;
}
KOALA_INTEROP_2(CreateCallExpression1, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateCallExpression1(KNativePointer context, KNativePointer original, KNativePointer other)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _other = reinterpret_cast<es2panda_AstNode*>(other);
    auto result = GetImpl()->UpdateCallExpression1(_context, _original, _other);
    return result;
}
KOALA_INTEROP_3(UpdateCallExpression1, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CallExpressionCalleeConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->CallExpressionCalleeConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(CallExpressionCalleeConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CallExpressionCallee(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->CallExpressionCallee(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(CallExpressionCallee, KNativePointer, KNativePointer, KNativePointer);

void impl_CallExpressionSetCallee(KNativePointer context, KNativePointer receiver, KNativePointer callee)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _callee = reinterpret_cast<es2panda_AstNode*>(callee);
    GetImpl()->CallExpressionSetCallee(_context, _receiver, _callee);
    return ;
}
KOALA_INTEROP_V3(CallExpressionSetCallee, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CallExpressionTypeParamsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->CallExpressionTypeParamsConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(CallExpressionTypeParamsConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CallExpressionTypeParams(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->CallExpressionTypeParams(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(CallExpressionTypeParams, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CallExpressionArgumentsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->CallExpressionArgumentsConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(CallExpressionArgumentsConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CallExpressionArguments(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->CallExpressionArguments(_context, _receiver, &length);
    return new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(CallExpressionArguments, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_CallExpressionHasTrailingCommaConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->CallExpressionHasTrailingCommaConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(CallExpressionHasTrailingCommaConst, KBoolean, KNativePointer, KNativePointer);

void impl_CallExpressionSetTypeParams(KNativePointer context, KNativePointer receiver, KNativePointer typeParams)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _typeParams = reinterpret_cast<es2panda_AstNode*>(typeParams);
    GetImpl()->CallExpressionSetTypeParams(_context, _receiver, _typeParams);
    return ;
}
KOALA_INTEROP_V3(CallExpressionSetTypeParams, KNativePointer, KNativePointer, KNativePointer);

void impl_CallExpressionSetTrailingBlock(KNativePointer context, KNativePointer receiver, KNativePointer block)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _block = reinterpret_cast<es2panda_AstNode*>(block);
    GetImpl()->CallExpressionSetTrailingBlock(_context, _receiver, _block);
    return ;
}
KOALA_INTEROP_V3(CallExpressionSetTrailingBlock, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_CallExpressionIsExtensionAccessorCall(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->CallExpressionIsExtensionAccessorCall(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(CallExpressionIsExtensionAccessorCall, KBoolean, KNativePointer, KNativePointer);

KNativePointer impl_CallExpressionTrailingBlockConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->CallExpressionTrailingBlockConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(CallExpressionTrailingBlockConst, KNativePointer, KNativePointer, KNativePointer);

void impl_CallExpressionSetIsTrailingBlockInNewLine(KNativePointer context, KNativePointer receiver, KBoolean isNewLine)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _isNewLine = static_cast<KBoolean>(isNewLine);
    GetImpl()->CallExpressionSetIsTrailingBlockInNewLine(_context, _receiver, _isNewLine);
    return ;
}
KOALA_INTEROP_V3(CallExpressionSetIsTrailingBlockInNewLine, KNativePointer, KNativePointer, KBoolean);

KBoolean impl_CallExpressionIsTrailingBlockInNewLineConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->CallExpressionIsTrailingBlockInNewLineConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(CallExpressionIsTrailingBlockInNewLineConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_CallExpressionIsETSConstructorCallConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->CallExpressionIsETSConstructorCallConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(CallExpressionIsETSConstructorCallConst, KBoolean, KNativePointer, KNativePointer);

KNativePointer impl_CreateBigIntLiteral(KNativePointer context, KStringPtr& src)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _src = getStringCopy(src);
    auto result = GetImpl()->CreateBigIntLiteral(_context, _src);
    return result;
}
KOALA_INTEROP_2(CreateBigIntLiteral, KNativePointer, KNativePointer, KStringPtr);

KNativePointer impl_UpdateBigIntLiteral(KNativePointer context, KNativePointer original, KStringPtr& src)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _src = getStringCopy(src);
    auto result = GetImpl()->UpdateBigIntLiteral(_context, _original, _src);
    return result;
}
KOALA_INTEROP_3(UpdateBigIntLiteral, KNativePointer, KNativePointer, KNativePointer, KStringPtr);

KNativePointer impl_BigIntLiteralStrConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->BigIntLiteralStrConst(_context, _receiver);
    return new std::string(result);
}
KOALA_INTEROP_2(BigIntLiteralStrConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ClassElementId(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ClassElementId(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ClassElementId, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ClassElementIdConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ClassElementIdConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ClassElementIdConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ClassElementKey(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ClassElementKey(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ClassElementKey, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ClassElementKeyConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ClassElementKeyConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ClassElementKeyConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ClassElementValue(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ClassElementValue(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ClassElementValue, KNativePointer, KNativePointer, KNativePointer);

void impl_ClassElementSetValue(KNativePointer context, KNativePointer receiver, KNativePointer value)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _value = reinterpret_cast<es2panda_AstNode*>(value);
    GetImpl()->ClassElementSetValue(_context, _receiver, _value);
    return ;
}
KOALA_INTEROP_V3(ClassElementSetValue, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ClassElementValueConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ClassElementValueConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ClassElementValueConst, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_ClassElementIsPrivateElementConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ClassElementIsPrivateElementConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ClassElementIsPrivateElementConst, KBoolean, KNativePointer, KNativePointer);

KNativePointer impl_ClassElementDecoratorsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->ClassElementDecoratorsConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(ClassElementDecoratorsConst, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_ClassElementIsComputedConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ClassElementIsComputedConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ClassElementIsComputedConst, KBoolean, KNativePointer, KNativePointer);

void impl_ClassElementAddDecorator(KNativePointer context, KNativePointer receiver, KNativePointer decorator)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _decorator = reinterpret_cast<es2panda_AstNode*>(decorator);
    GetImpl()->ClassElementAddDecorator(_context, _receiver, _decorator);
    return ;
}
KOALA_INTEROP_V3(ClassElementAddDecorator, KNativePointer, KNativePointer, KNativePointer);

KInt impl_ClassElementToPrivateFieldKindConst(KNativePointer context, KNativePointer receiver, KBoolean isStatic)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _isStatic = static_cast<KBoolean>(isStatic);
    auto result = GetImpl()->ClassElementToPrivateFieldKindConst(_context, _receiver, _isStatic);
    return result;
}
KOALA_INTEROP_3(ClassElementToPrivateFieldKindConst, KInt, KNativePointer, KNativePointer, KBoolean);

KNativePointer impl_CreateTSImportType(KNativePointer context, KNativePointer param, KNativePointer typeParams, KNativePointer qualifier, KBoolean isTypeof)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _param = reinterpret_cast<es2panda_AstNode*>(param);
    const auto _typeParams = reinterpret_cast<es2panda_AstNode*>(typeParams);
    const auto _qualifier = reinterpret_cast<es2panda_AstNode*>(qualifier);
    const auto _isTypeof = static_cast<KBoolean>(isTypeof);
    auto result = GetImpl()->CreateTSImportType(_context, _param, _typeParams, _qualifier, _isTypeof);
    return result;
}
KOALA_INTEROP_5(CreateTSImportType, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KBoolean);

KNativePointer impl_UpdateTSImportType(KNativePointer context, KNativePointer original, KNativePointer param, KNativePointer typeParams, KNativePointer qualifier, KBoolean isTypeof)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _param = reinterpret_cast<es2panda_AstNode*>(param);
    const auto _typeParams = reinterpret_cast<es2panda_AstNode*>(typeParams);
    const auto _qualifier = reinterpret_cast<es2panda_AstNode*>(qualifier);
    const auto _isTypeof = static_cast<KBoolean>(isTypeof);
    auto result = GetImpl()->UpdateTSImportType(_context, _original, _param, _typeParams, _qualifier, _isTypeof);
    return result;
}
KOALA_INTEROP_6(UpdateTSImportType, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KBoolean);

KNativePointer impl_TSImportTypeParamConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSImportTypeParamConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSImportTypeParamConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSImportTypeTypeParamsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSImportTypeTypeParamsConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSImportTypeTypeParamsConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSImportTypeQualifierConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSImportTypeQualifierConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSImportTypeQualifierConst, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_TSImportTypeIsTypeofConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSImportTypeIsTypeofConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSImportTypeIsTypeofConst, KBoolean, KNativePointer, KNativePointer);

KNativePointer impl_CreateTaggedTemplateExpression(KNativePointer context, KNativePointer tag, KNativePointer quasi, KNativePointer typeParams)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _tag = reinterpret_cast<es2panda_AstNode*>(tag);
    const auto _quasi = reinterpret_cast<es2panda_AstNode*>(quasi);
    const auto _typeParams = reinterpret_cast<es2panda_AstNode*>(typeParams);
    auto result = GetImpl()->CreateTaggedTemplateExpression(_context, _tag, _quasi, _typeParams);
    return result;
}
KOALA_INTEROP_4(CreateTaggedTemplateExpression, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateTaggedTemplateExpression(KNativePointer context, KNativePointer original, KNativePointer tag, KNativePointer quasi, KNativePointer typeParams)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _tag = reinterpret_cast<es2panda_AstNode*>(tag);
    const auto _quasi = reinterpret_cast<es2panda_AstNode*>(quasi);
    const auto _typeParams = reinterpret_cast<es2panda_AstNode*>(typeParams);
    auto result = GetImpl()->UpdateTaggedTemplateExpression(_context, _original, _tag, _quasi, _typeParams);
    return result;
}
KOALA_INTEROP_5(UpdateTaggedTemplateExpression, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TaggedTemplateExpressionTagConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TaggedTemplateExpressionTagConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TaggedTemplateExpressionTagConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TaggedTemplateExpressionQuasiConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TaggedTemplateExpressionQuasiConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TaggedTemplateExpressionQuasiConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TaggedTemplateExpressionTypeParamsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TaggedTemplateExpressionTypeParamsConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TaggedTemplateExpressionTypeParamsConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateFunctionDeclaration(KNativePointer context, KNativePointer func, KNativePointerArray annotations, KUInt annotationsSequenceLength, KBoolean isAnonymous)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _func = reinterpret_cast<es2panda_AstNode*>(func);
    const auto _annotations = reinterpret_cast<es2panda_AstNode**>(annotations);
    const auto _annotationsSequenceLength = static_cast<KUInt>(annotationsSequenceLength);
    const auto _isAnonymous = static_cast<KBoolean>(isAnonymous);
    auto result = GetImpl()->CreateFunctionDeclaration(_context, _func, _annotations, _annotationsSequenceLength, _isAnonymous);
    return result;
}
KOALA_INTEROP_5(CreateFunctionDeclaration, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt, KBoolean);

KNativePointer impl_UpdateFunctionDeclaration(KNativePointer context, KNativePointer original, KNativePointer func, KNativePointerArray annotations, KUInt annotationsSequenceLength, KBoolean isAnonymous)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _func = reinterpret_cast<es2panda_AstNode*>(func);
    const auto _annotations = reinterpret_cast<es2panda_AstNode**>(annotations);
    const auto _annotationsSequenceLength = static_cast<KUInt>(annotationsSequenceLength);
    const auto _isAnonymous = static_cast<KBoolean>(isAnonymous);
    auto result = GetImpl()->UpdateFunctionDeclaration(_context, _original, _func, _annotations, _annotationsSequenceLength, _isAnonymous);
    return result;
}
KOALA_INTEROP_6(UpdateFunctionDeclaration, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt, KBoolean);

KNativePointer impl_CreateFunctionDeclaration1(KNativePointer context, KNativePointer func, KBoolean isAnonymous)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _func = reinterpret_cast<es2panda_AstNode*>(func);
    const auto _isAnonymous = static_cast<KBoolean>(isAnonymous);
    auto result = GetImpl()->CreateFunctionDeclaration1(_context, _func, _isAnonymous);
    return result;
}
KOALA_INTEROP_3(CreateFunctionDeclaration1, KNativePointer, KNativePointer, KNativePointer, KBoolean);

KNativePointer impl_UpdateFunctionDeclaration1(KNativePointer context, KNativePointer original, KNativePointer func, KBoolean isAnonymous)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _func = reinterpret_cast<es2panda_AstNode*>(func);
    const auto _isAnonymous = static_cast<KBoolean>(isAnonymous);
    auto result = GetImpl()->UpdateFunctionDeclaration1(_context, _original, _func, _isAnonymous);
    return result;
}
KOALA_INTEROP_4(UpdateFunctionDeclaration1, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KBoolean);

KNativePointer impl_FunctionDeclarationFunction(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->FunctionDeclarationFunction(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(FunctionDeclarationFunction, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_FunctionDeclarationIsAnonymousConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->FunctionDeclarationIsAnonymousConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(FunctionDeclarationIsAnonymousConst, KBoolean, KNativePointer, KNativePointer);

KNativePointer impl_FunctionDeclarationFunctionConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->FunctionDeclarationFunctionConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(FunctionDeclarationFunctionConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_FunctionDeclarationAnnotations(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->FunctionDeclarationAnnotations(_context, _receiver, &length);
    return new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(FunctionDeclarationAnnotations, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_FunctionDeclarationAnnotationsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->FunctionDeclarationAnnotationsConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(FunctionDeclarationAnnotationsConst, KNativePointer, KNativePointer, KNativePointer);

void impl_FunctionDeclarationSetAnnotations(KNativePointer context, KNativePointer receiver, KNativePointerArray annotations, KUInt annotationsSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _annotations = reinterpret_cast<es2panda_AstNode**>(annotations);
    const auto _annotationsSequenceLength = static_cast<KUInt>(annotationsSequenceLength);
    GetImpl()->FunctionDeclarationSetAnnotations(_context, _receiver, _annotations, _annotationsSequenceLength);
    return ;
}
KOALA_INTEROP_V4(FunctionDeclarationSetAnnotations, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_CreateETSTypeReference(KNativePointer context, KNativePointer part)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _part = reinterpret_cast<es2panda_AstNode*>(part);
    auto result = GetImpl()->CreateETSTypeReference(_context, _part);
    return result;
}
KOALA_INTEROP_2(CreateETSTypeReference, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateETSTypeReference(KNativePointer context, KNativePointer original, KNativePointer part)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _part = reinterpret_cast<es2panda_AstNode*>(part);
    auto result = GetImpl()->UpdateETSTypeReference(_context, _original, _part);
    return result;
}
KOALA_INTEROP_3(UpdateETSTypeReference, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ETSTypeReferencePart(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSTypeReferencePart(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ETSTypeReferencePart, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ETSTypeReferencePartConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSTypeReferencePartConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ETSTypeReferencePartConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ETSTypeReferenceBaseNameConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSTypeReferenceBaseNameConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ETSTypeReferenceBaseNameConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSTypeReference(KNativePointer context, KNativePointer typeName, KNativePointer typeParams)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _typeName = reinterpret_cast<es2panda_AstNode*>(typeName);
    const auto _typeParams = reinterpret_cast<es2panda_AstNode*>(typeParams);
    auto result = GetImpl()->CreateTSTypeReference(_context, _typeName, _typeParams);
    return result;
}
KOALA_INTEROP_3(CreateTSTypeReference, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateTSTypeReference(KNativePointer context, KNativePointer original, KNativePointer typeName, KNativePointer typeParams)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _typeName = reinterpret_cast<es2panda_AstNode*>(typeName);
    const auto _typeParams = reinterpret_cast<es2panda_AstNode*>(typeParams);
    auto result = GetImpl()->UpdateTSTypeReference(_context, _original, _typeName, _typeParams);
    return result;
}
KOALA_INTEROP_4(UpdateTSTypeReference, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSTypeReferenceTypeParamsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSTypeReferenceTypeParamsConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSTypeReferenceTypeParamsConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSTypeReferenceTypeNameConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSTypeReferenceTypeNameConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSTypeReferenceTypeNameConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSTypeReferenceBaseNameConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSTypeReferenceBaseNameConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSTypeReferenceBaseNameConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateImportSource(KNativePointer context, KNativePointer source, KNativePointer resolvedSource, KBoolean hasDecl)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _source = reinterpret_cast<es2panda_AstNode*>(source);
    const auto _resolvedSource = reinterpret_cast<es2panda_AstNode*>(resolvedSource);
    const auto _hasDecl = static_cast<KBoolean>(hasDecl);
    auto result = GetImpl()->CreateImportSource(_context, _source, _resolvedSource, _hasDecl);
    return result;
}
KOALA_INTEROP_4(CreateImportSource, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KBoolean);

KNativePointer impl_ImportSourceSourceConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_ImportSource*>(receiver);
    auto result = GetImpl()->ImportSourceSourceConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ImportSourceSourceConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ImportSourceSource(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_ImportSource*>(receiver);
    auto result = GetImpl()->ImportSourceSource(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ImportSourceSource, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ImportSourceResolvedSourceConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_ImportSource*>(receiver);
    auto result = GetImpl()->ImportSourceResolvedSourceConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ImportSourceResolvedSourceConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ImportSourceResolvedSource(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_ImportSource*>(receiver);
    auto result = GetImpl()->ImportSourceResolvedSource(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ImportSourceResolvedSource, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_ImportSourceHasDeclConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_ImportSource*>(receiver);
    auto result = GetImpl()->ImportSourceHasDeclConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ImportSourceHasDeclConst, KBoolean, KNativePointer, KNativePointer);

KNativePointer impl_CreateNamedType(KNativePointer context, KNativePointer name)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _name = reinterpret_cast<es2panda_AstNode*>(name);
    auto result = GetImpl()->CreateNamedType(_context, _name);
    return result;
}
KOALA_INTEROP_2(CreateNamedType, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateNamedType(KNativePointer context, KNativePointer original, KNativePointer name)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _name = reinterpret_cast<es2panda_AstNode*>(name);
    auto result = GetImpl()->UpdateNamedType(_context, _original, _name);
    return result;
}
KOALA_INTEROP_3(UpdateNamedType, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_NamedTypeNameConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->NamedTypeNameConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(NamedTypeNameConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_NamedTypeTypeParamsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->NamedTypeTypeParamsConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(NamedTypeTypeParamsConst, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_NamedTypeIsNullableConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->NamedTypeIsNullableConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(NamedTypeIsNullableConst, KBoolean, KNativePointer, KNativePointer);

void impl_NamedTypeSetNullable(KNativePointer context, KNativePointer receiver, KBoolean nullable)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _nullable = static_cast<KBoolean>(nullable);
    GetImpl()->NamedTypeSetNullable(_context, _receiver, _nullable);
    return ;
}
KOALA_INTEROP_V3(NamedTypeSetNullable, KNativePointer, KNativePointer, KBoolean);

void impl_NamedTypeSetNext(KNativePointer context, KNativePointer receiver, KNativePointer next)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _next = reinterpret_cast<es2panda_AstNode*>(next);
    GetImpl()->NamedTypeSetNext(_context, _receiver, _next);
    return ;
}
KOALA_INTEROP_V3(NamedTypeSetNext, KNativePointer, KNativePointer, KNativePointer);

void impl_NamedTypeSetTypeParams(KNativePointer context, KNativePointer receiver, KNativePointer typeParams)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _typeParams = reinterpret_cast<es2panda_AstNode*>(typeParams);
    GetImpl()->NamedTypeSetTypeParams(_context, _receiver, _typeParams);
    return ;
}
KOALA_INTEROP_V3(NamedTypeSetTypeParams, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_NumberLiteralStrConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->NumberLiteralStrConst(_context, _receiver);
    return new std::string(result);
}
KOALA_INTEROP_2(NumberLiteralStrConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSFunctionType(KNativePointer context, KNativePointer signature)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _signature = reinterpret_cast<es2panda_FunctionSignature*>(signature);
    auto result = GetImpl()->CreateTSFunctionType(_context, _signature);
    return result;
}
KOALA_INTEROP_2(CreateTSFunctionType, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateTSFunctionType(KNativePointer context, KNativePointer original, KNativePointer signature)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _signature = reinterpret_cast<es2panda_FunctionSignature*>(signature);
    auto result = GetImpl()->UpdateTSFunctionType(_context, _original, _signature);
    return result;
}
KOALA_INTEROP_3(UpdateTSFunctionType, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSFunctionTypeTypeParamsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSFunctionTypeTypeParamsConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSFunctionTypeTypeParamsConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSFunctionTypeTypeParams(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSFunctionTypeTypeParams(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSFunctionTypeTypeParams, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSFunctionTypeParamsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->TSFunctionTypeParamsConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(TSFunctionTypeParamsConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSFunctionTypeReturnTypeConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSFunctionTypeReturnTypeConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSFunctionTypeReturnTypeConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSFunctionTypeReturnType(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSFunctionTypeReturnType(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSFunctionTypeReturnType, KNativePointer, KNativePointer, KNativePointer);

void impl_TSFunctionTypeSetNullable(KNativePointer context, KNativePointer receiver, KBoolean nullable)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _nullable = static_cast<KBoolean>(nullable);
    GetImpl()->TSFunctionTypeSetNullable(_context, _receiver, _nullable);
    return ;
}
KOALA_INTEROP_V3(TSFunctionTypeSetNullable, KNativePointer, KNativePointer, KBoolean);

KNativePointer impl_CreateTemplateElement(KNativePointer context)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    auto result = GetImpl()->CreateTemplateElement(_context);
    return result;
}
KOALA_INTEROP_1(CreateTemplateElement, KNativePointer, KNativePointer);

KNativePointer impl_UpdateTemplateElement(KNativePointer context, KNativePointer original)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    auto result = GetImpl()->UpdateTemplateElement(_context, _original);
    return result;
}
KOALA_INTEROP_2(UpdateTemplateElement, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateTemplateElement1(KNativePointer context, KStringPtr& raw, KStringPtr& cooked)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _raw = getStringCopy(raw);
    const auto _cooked = getStringCopy(cooked);
    auto result = GetImpl()->CreateTemplateElement1(_context, _raw, _cooked);
    return result;
}
KOALA_INTEROP_3(CreateTemplateElement1, KNativePointer, KNativePointer, KStringPtr, KStringPtr);

KNativePointer impl_UpdateTemplateElement1(KNativePointer context, KNativePointer original, KStringPtr& raw, KStringPtr& cooked)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _raw = getStringCopy(raw);
    const auto _cooked = getStringCopy(cooked);
    auto result = GetImpl()->UpdateTemplateElement1(_context, _original, _raw, _cooked);
    return result;
}
KOALA_INTEROP_4(UpdateTemplateElement1, KNativePointer, KNativePointer, KNativePointer, KStringPtr, KStringPtr);

KNativePointer impl_TemplateElementRawConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TemplateElementRawConst(_context, _receiver);
    return new std::string(result);
}
KOALA_INTEROP_2(TemplateElementRawConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TemplateElementCookedConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TemplateElementCookedConst(_context, _receiver);
    return new std::string(result);
}
KOALA_INTEROP_2(TemplateElementCookedConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSInterfaceDeclaration(KNativePointer context, KNativePointerArray _extends, KUInt _extendsSequenceLength, KNativePointer id, KNativePointer typeParams, KNativePointer body, KBoolean isStatic, KBoolean isExternal)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto __extends = reinterpret_cast<es2panda_AstNode**>(_extends);
    const auto __extendsSequenceLength = static_cast<KUInt>(_extendsSequenceLength);
    const auto _id = reinterpret_cast<es2panda_AstNode*>(id);
    const auto _typeParams = reinterpret_cast<es2panda_AstNode*>(typeParams);
    const auto _body = reinterpret_cast<es2panda_AstNode*>(body);
    const auto _isStatic = static_cast<KBoolean>(isStatic);
    const auto _isExternal = static_cast<KBoolean>(isExternal);
    auto result = GetImpl()->CreateTSInterfaceDeclaration(_context, __extends, __extendsSequenceLength, _id, _typeParams, _body, _isStatic, _isExternal);
    return result;
}
KOALA_INTEROP_8(CreateTSInterfaceDeclaration, KNativePointer, KNativePointer, KNativePointerArray, KUInt, KNativePointer, KNativePointer, KNativePointer, KBoolean, KBoolean);

KNativePointer impl_UpdateTSInterfaceDeclaration(KNativePointer context, KNativePointer original, KNativePointerArray _extends, KUInt _extendsSequenceLength, KNativePointer id, KNativePointer typeParams, KNativePointer body, KBoolean isStatic, KBoolean isExternal)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto __extends = reinterpret_cast<es2panda_AstNode**>(_extends);
    const auto __extendsSequenceLength = static_cast<KUInt>(_extendsSequenceLength);
    const auto _id = reinterpret_cast<es2panda_AstNode*>(id);
    const auto _typeParams = reinterpret_cast<es2panda_AstNode*>(typeParams);
    const auto _body = reinterpret_cast<es2panda_AstNode*>(body);
    const auto _isStatic = static_cast<KBoolean>(isStatic);
    const auto _isExternal = static_cast<KBoolean>(isExternal);
    auto result = GetImpl()->UpdateTSInterfaceDeclaration(_context, _original, __extends, __extendsSequenceLength, _id, _typeParams, _body, _isStatic, _isExternal);
    return result;
}
KOALA_INTEROP_9(UpdateTSInterfaceDeclaration, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt, KNativePointer, KNativePointer, KNativePointer, KBoolean, KBoolean);

KNativePointer impl_TSInterfaceDeclarationBody(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSInterfaceDeclarationBody(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSInterfaceDeclarationBody, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSInterfaceDeclarationBodyConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSInterfaceDeclarationBodyConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSInterfaceDeclarationBodyConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSInterfaceDeclarationId(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSInterfaceDeclarationId(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSInterfaceDeclarationId, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSInterfaceDeclarationIdConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSInterfaceDeclarationIdConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSInterfaceDeclarationIdConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSInterfaceDeclarationInternalNameConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSInterfaceDeclarationInternalNameConst(_context, _receiver);
    return new std::string(result);
}
KOALA_INTEROP_2(TSInterfaceDeclarationInternalNameConst, KNativePointer, KNativePointer, KNativePointer);

void impl_TSInterfaceDeclarationSetInternalName(KNativePointer context, KNativePointer receiver, KStringPtr& internalName)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _internalName = getStringCopy(internalName);
    GetImpl()->TSInterfaceDeclarationSetInternalName(_context, _receiver, _internalName);
    return ;
}
KOALA_INTEROP_V3(TSInterfaceDeclarationSetInternalName, KNativePointer, KNativePointer, KStringPtr);

KBoolean impl_TSInterfaceDeclarationIsStaticConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSInterfaceDeclarationIsStaticConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSInterfaceDeclarationIsStaticConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_TSInterfaceDeclarationIsFromExternalConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSInterfaceDeclarationIsFromExternalConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSInterfaceDeclarationIsFromExternalConst, KBoolean, KNativePointer, KNativePointer);

KNativePointer impl_TSInterfaceDeclarationTypeParamsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSInterfaceDeclarationTypeParamsConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSInterfaceDeclarationTypeParamsConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSInterfaceDeclarationTypeParams(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSInterfaceDeclarationTypeParams(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSInterfaceDeclarationTypeParams, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSInterfaceDeclarationExtends(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->TSInterfaceDeclarationExtends(_context, _receiver, &length);
    return new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(TSInterfaceDeclarationExtends, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSInterfaceDeclarationExtendsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->TSInterfaceDeclarationExtendsConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(TSInterfaceDeclarationExtendsConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSInterfaceDeclarationDecoratorsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->TSInterfaceDeclarationDecoratorsConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(TSInterfaceDeclarationDecoratorsConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSInterfaceDeclarationGetAnonClass(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSInterfaceDeclarationGetAnonClass(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSInterfaceDeclarationGetAnonClass, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSInterfaceDeclarationGetAnonClassConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSInterfaceDeclarationGetAnonClassConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSInterfaceDeclarationGetAnonClassConst, KNativePointer, KNativePointer, KNativePointer);

void impl_TSInterfaceDeclarationSetAnonClass(KNativePointer context, KNativePointer receiver, KNativePointer anonClass)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _anonClass = reinterpret_cast<es2panda_AstNode*>(anonClass);
    GetImpl()->TSInterfaceDeclarationSetAnonClass(_context, _receiver, _anonClass);
    return ;
}
KOALA_INTEROP_V3(TSInterfaceDeclarationSetAnonClass, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSInterfaceDeclarationAnnotations(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->TSInterfaceDeclarationAnnotations(_context, _receiver, &length);
    return new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(TSInterfaceDeclarationAnnotations, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSInterfaceDeclarationAnnotationsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->TSInterfaceDeclarationAnnotationsConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(TSInterfaceDeclarationAnnotationsConst, KNativePointer, KNativePointer, KNativePointer);

void impl_TSInterfaceDeclarationSetAnnotations(KNativePointer context, KNativePointer receiver, KNativePointerArray annotations, KUInt annotationsSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _annotations = reinterpret_cast<es2panda_AstNode**>(annotations);
    const auto _annotationsSequenceLength = static_cast<KUInt>(annotationsSequenceLength);
    GetImpl()->TSInterfaceDeclarationSetAnnotations(_context, _receiver, _annotations, _annotationsSequenceLength);
    return ;
}
KOALA_INTEROP_V4(TSInterfaceDeclarationSetAnnotations, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_CreateVariableDeclaration(KNativePointer context, KInt kind, KNativePointerArray declarators, KUInt declaratorsSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _kind = static_cast<Es2pandaVariableDeclarationKind>(kind);
    const auto _declarators = reinterpret_cast<es2panda_AstNode**>(declarators);
    const auto _declaratorsSequenceLength = static_cast<KUInt>(declaratorsSequenceLength);
    auto result = GetImpl()->CreateVariableDeclaration(_context, _kind, _declarators, _declaratorsSequenceLength);
    return result;
}
KOALA_INTEROP_4(CreateVariableDeclaration, KNativePointer, KNativePointer, KInt, KNativePointerArray, KUInt);

KNativePointer impl_UpdateVariableDeclaration(KNativePointer context, KNativePointer original, KInt kind, KNativePointerArray declarators, KUInt declaratorsSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _kind = static_cast<Es2pandaVariableDeclarationKind>(kind);
    const auto _declarators = reinterpret_cast<es2panda_AstNode**>(declarators);
    const auto _declaratorsSequenceLength = static_cast<KUInt>(declaratorsSequenceLength);
    auto result = GetImpl()->UpdateVariableDeclaration(_context, _original, _kind, _declarators, _declaratorsSequenceLength);
    return result;
}
KOALA_INTEROP_5(UpdateVariableDeclaration, KNativePointer, KNativePointer, KNativePointer, KInt, KNativePointerArray, KUInt);

KNativePointer impl_VariableDeclarationDeclaratorsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->VariableDeclarationDeclaratorsConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(VariableDeclarationDeclaratorsConst, KNativePointer, KNativePointer, KNativePointer);

KInt impl_VariableDeclarationKindConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->VariableDeclarationKindConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(VariableDeclarationKindConst, KInt, KNativePointer, KNativePointer);

KNativePointer impl_VariableDeclarationDecoratorsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->VariableDeclarationDecoratorsConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(VariableDeclarationDecoratorsConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_VariableDeclarationGetDeclaratorByNameConst(KNativePointer context, KNativePointer receiver, KStringPtr& name)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _name = getStringCopy(name);
    auto result = GetImpl()->VariableDeclarationGetDeclaratorByNameConst(_context, _receiver, _name);
    return (void*)result;
}
KOALA_INTEROP_3(VariableDeclarationGetDeclaratorByNameConst, KNativePointer, KNativePointer, KNativePointer, KStringPtr);

KNativePointer impl_VariableDeclarationAnnotations(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->VariableDeclarationAnnotations(_context, _receiver, &length);
    return new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(VariableDeclarationAnnotations, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_VariableDeclarationAnnotationsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->VariableDeclarationAnnotationsConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(VariableDeclarationAnnotationsConst, KNativePointer, KNativePointer, KNativePointer);

void impl_VariableDeclarationSetAnnotations(KNativePointer context, KNativePointer receiver, KNativePointerArray annotations, KUInt annotationsSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _annotations = reinterpret_cast<es2panda_AstNode**>(annotations);
    const auto _annotationsSequenceLength = static_cast<KUInt>(annotationsSequenceLength);
    GetImpl()->VariableDeclarationSetAnnotations(_context, _receiver, _annotations, _annotationsSequenceLength);
    return ;
}
KOALA_INTEROP_V4(VariableDeclarationSetAnnotations, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_CreateUndefinedLiteral(KNativePointer context)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    auto result = GetImpl()->CreateUndefinedLiteral(_context);
    return result;
}
KOALA_INTEROP_1(CreateUndefinedLiteral, KNativePointer, KNativePointer);

KNativePointer impl_UpdateUndefinedLiteral(KNativePointer context, KNativePointer original)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    auto result = GetImpl()->UpdateUndefinedLiteral(_context, _original);
    return result;
}
KOALA_INTEROP_2(UpdateUndefinedLiteral, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateMemberExpression(KNativePointer context, KNativePointer object_arg, KNativePointer property, KInt kind, KBoolean computed, KBoolean optional_arg)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _object_arg = reinterpret_cast<es2panda_AstNode*>(object_arg);
    const auto _property = reinterpret_cast<es2panda_AstNode*>(property);
    const auto _kind = static_cast<Es2pandaMemberExpressionKind>(kind);
    const auto _computed = static_cast<KBoolean>(computed);
    const auto _optional_arg = static_cast<KBoolean>(optional_arg);
    auto result = GetImpl()->CreateMemberExpression(_context, _object_arg, _property, _kind, _computed, _optional_arg);
    return result;
}
KOALA_INTEROP_6(CreateMemberExpression, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KInt, KBoolean, KBoolean);

KNativePointer impl_UpdateMemberExpression(KNativePointer context, KNativePointer original, KNativePointer object_arg, KNativePointer property, KInt kind, KBoolean computed, KBoolean optional_arg)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _object_arg = reinterpret_cast<es2panda_AstNode*>(object_arg);
    const auto _property = reinterpret_cast<es2panda_AstNode*>(property);
    const auto _kind = static_cast<Es2pandaMemberExpressionKind>(kind);
    const auto _computed = static_cast<KBoolean>(computed);
    const auto _optional_arg = static_cast<KBoolean>(optional_arg);
    auto result = GetImpl()->UpdateMemberExpression(_context, _original, _object_arg, _property, _kind, _computed, _optional_arg);
    return result;
}
KOALA_INTEROP_7(UpdateMemberExpression, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KInt, KBoolean, KBoolean);

KNativePointer impl_MemberExpressionObject(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->MemberExpressionObject(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(MemberExpressionObject, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_MemberExpressionObjectConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->MemberExpressionObjectConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(MemberExpressionObjectConst, KNativePointer, KNativePointer, KNativePointer);

void impl_MemberExpressionSetObject(KNativePointer context, KNativePointer receiver, KNativePointer object_arg)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _object_arg = reinterpret_cast<es2panda_AstNode*>(object_arg);
    GetImpl()->MemberExpressionSetObject(_context, _receiver, _object_arg);
    return ;
}
KOALA_INTEROP_V3(MemberExpressionSetObject, KNativePointer, KNativePointer, KNativePointer);

void impl_MemberExpressionSetProperty(KNativePointer context, KNativePointer receiver, KNativePointer prop)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _prop = reinterpret_cast<es2panda_AstNode*>(prop);
    GetImpl()->MemberExpressionSetProperty(_context, _receiver, _prop);
    return ;
}
KOALA_INTEROP_V3(MemberExpressionSetProperty, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_MemberExpressionProperty(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->MemberExpressionProperty(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(MemberExpressionProperty, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_MemberExpressionPropertyConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->MemberExpressionPropertyConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(MemberExpressionPropertyConst, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_MemberExpressionIsComputedConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->MemberExpressionIsComputedConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(MemberExpressionIsComputedConst, KBoolean, KNativePointer, KNativePointer);

KInt impl_MemberExpressionKindConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->MemberExpressionKindConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(MemberExpressionKindConst, KInt, KNativePointer, KNativePointer);

void impl_MemberExpressionAddMemberKind(KNativePointer context, KNativePointer receiver, KInt kind)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _kind = static_cast<Es2pandaMemberExpressionKind>(kind);
    GetImpl()->MemberExpressionAddMemberKind(_context, _receiver, _kind);
    return ;
}
KOALA_INTEROP_V3(MemberExpressionAddMemberKind, KNativePointer, KNativePointer, KInt);

KBoolean impl_MemberExpressionHasMemberKindConst(KNativePointer context, KNativePointer receiver, KInt kind)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _kind = static_cast<Es2pandaMemberExpressionKind>(kind);
    auto result = GetImpl()->MemberExpressionHasMemberKindConst(_context, _receiver, _kind);
    return result;
}
KOALA_INTEROP_3(MemberExpressionHasMemberKindConst, KBoolean, KNativePointer, KNativePointer, KInt);

void impl_MemberExpressionRemoveMemberKind(KNativePointer context, KNativePointer receiver, KInt kind)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _kind = static_cast<Es2pandaMemberExpressionKind>(kind);
    GetImpl()->MemberExpressionRemoveMemberKind(_context, _receiver, _kind);
    return ;
}
KOALA_INTEROP_V3(MemberExpressionRemoveMemberKind, KNativePointer, KNativePointer, KInt);

KBoolean impl_MemberExpressionIsIgnoreBoxConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->MemberExpressionIsIgnoreBoxConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(MemberExpressionIsIgnoreBoxConst, KBoolean, KNativePointer, KNativePointer);

void impl_MemberExpressionSetIgnoreBox(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    GetImpl()->MemberExpressionSetIgnoreBox(_context, _receiver);
    return ;
}
KOALA_INTEROP_V2(MemberExpressionSetIgnoreBox, KNativePointer, KNativePointer);

KBoolean impl_MemberExpressionIsPrivateReferenceConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->MemberExpressionIsPrivateReferenceConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(MemberExpressionIsPrivateReferenceConst, KBoolean, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSClassImplements(KNativePointer context, KNativePointer expression, KNativePointer typeParameters)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _expression = reinterpret_cast<es2panda_AstNode*>(expression);
    const auto _typeParameters = reinterpret_cast<es2panda_AstNode*>(typeParameters);
    auto result = GetImpl()->CreateTSClassImplements(_context, _expression, _typeParameters);
    return result;
}
KOALA_INTEROP_3(CreateTSClassImplements, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateTSClassImplements(KNativePointer context, KNativePointer original, KNativePointer expression, KNativePointer typeParameters)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _expression = reinterpret_cast<es2panda_AstNode*>(expression);
    const auto _typeParameters = reinterpret_cast<es2panda_AstNode*>(typeParameters);
    auto result = GetImpl()->UpdateTSClassImplements(_context, _original, _expression, _typeParameters);
    return result;
}
KOALA_INTEROP_4(UpdateTSClassImplements, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSClassImplements1(KNativePointer context, KNativePointer expression)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _expression = reinterpret_cast<es2panda_AstNode*>(expression);
    auto result = GetImpl()->CreateTSClassImplements1(_context, _expression);
    return result;
}
KOALA_INTEROP_2(CreateTSClassImplements1, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateTSClassImplements1(KNativePointer context, KNativePointer original, KNativePointer expression)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _expression = reinterpret_cast<es2panda_AstNode*>(expression);
    auto result = GetImpl()->UpdateTSClassImplements1(_context, _original, _expression);
    return result;
}
KOALA_INTEROP_3(UpdateTSClassImplements1, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSClassImplementsExpr(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSClassImplementsExpr(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSClassImplementsExpr, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSClassImplementsExprConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSClassImplementsExprConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSClassImplementsExprConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSClassImplementsTypeParametersConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSClassImplementsTypeParametersConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSClassImplementsTypeParametersConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSObjectKeyword(KNativePointer context)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    auto result = GetImpl()->CreateTSObjectKeyword(_context);
    return result;
}
KOALA_INTEROP_1(CreateTSObjectKeyword, KNativePointer, KNativePointer);

KNativePointer impl_UpdateTSObjectKeyword(KNativePointer context, KNativePointer original)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    auto result = GetImpl()->UpdateTSObjectKeyword(_context, _original);
    return result;
}
KOALA_INTEROP_2(UpdateTSObjectKeyword, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateETSUnionTypeIr(KNativePointer context, KNativePointerArray types, KUInt typesSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _types = reinterpret_cast<es2panda_AstNode**>(types);
    const auto _typesSequenceLength = static_cast<KUInt>(typesSequenceLength);
    auto result = GetImpl()->CreateETSUnionTypeIr(_context, _types, _typesSequenceLength);
    return result;
}
KOALA_INTEROP_3(CreateETSUnionTypeIr, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_UpdateETSUnionTypeIr(KNativePointer context, KNativePointer original, KNativePointerArray types, KUInt typesSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _types = reinterpret_cast<es2panda_AstNode**>(types);
    const auto _typesSequenceLength = static_cast<KUInt>(typesSequenceLength);
    auto result = GetImpl()->UpdateETSUnionTypeIr(_context, _original, _types, _typesSequenceLength);
    return result;
}
KOALA_INTEROP_4(UpdateETSUnionTypeIr, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_ETSUnionTypeIrTypesConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->ETSUnionTypeIrTypesConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(ETSUnionTypeIrTypesConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSPropertySignature(KNativePointer context, KNativePointer key, KNativePointer typeAnnotation, KBoolean computed, KBoolean optional_arg, KBoolean readonly_arg)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _key = reinterpret_cast<es2panda_AstNode*>(key);
    const auto _typeAnnotation = reinterpret_cast<es2panda_AstNode*>(typeAnnotation);
    const auto _computed = static_cast<KBoolean>(computed);
    const auto _optional_arg = static_cast<KBoolean>(optional_arg);
    const auto _readonly_arg = static_cast<KBoolean>(readonly_arg);
    auto result = GetImpl()->CreateTSPropertySignature(_context, _key, _typeAnnotation, _computed, _optional_arg, _readonly_arg);
    return result;
}
KOALA_INTEROP_6(CreateTSPropertySignature, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KBoolean, KBoolean, KBoolean);

KNativePointer impl_UpdateTSPropertySignature(KNativePointer context, KNativePointer original, KNativePointer key, KNativePointer typeAnnotation, KBoolean computed, KBoolean optional_arg, KBoolean readonly_arg)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _key = reinterpret_cast<es2panda_AstNode*>(key);
    const auto _typeAnnotation = reinterpret_cast<es2panda_AstNode*>(typeAnnotation);
    const auto _computed = static_cast<KBoolean>(computed);
    const auto _optional_arg = static_cast<KBoolean>(optional_arg);
    const auto _readonly_arg = static_cast<KBoolean>(readonly_arg);
    auto result = GetImpl()->UpdateTSPropertySignature(_context, _original, _key, _typeAnnotation, _computed, _optional_arg, _readonly_arg);
    return result;
}
KOALA_INTEROP_7(UpdateTSPropertySignature, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KBoolean, KBoolean, KBoolean);

KNativePointer impl_TSPropertySignatureKeyConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSPropertySignatureKeyConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSPropertySignatureKeyConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSPropertySignatureKey(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSPropertySignatureKey(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSPropertySignatureKey, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_TSPropertySignatureComputedConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSPropertySignatureComputedConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSPropertySignatureComputedConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_TSPropertySignatureOptionalConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSPropertySignatureOptionalConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSPropertySignatureOptionalConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_TSPropertySignatureReadonlyConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSPropertySignatureReadonlyConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSPropertySignatureReadonlyConst, KBoolean, KNativePointer, KNativePointer);

KNativePointer impl_TSPropertySignatureTypeAnnotationConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSPropertySignatureTypeAnnotationConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSPropertySignatureTypeAnnotationConst, KNativePointer, KNativePointer, KNativePointer);

void impl_TSPropertySignatureSetTsTypeAnnotation(KNativePointer context, KNativePointer receiver, KNativePointer typeAnnotation)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _typeAnnotation = reinterpret_cast<es2panda_AstNode*>(typeAnnotation);
    GetImpl()->TSPropertySignatureSetTsTypeAnnotation(_context, _receiver, _typeAnnotation);
    return ;
}
KOALA_INTEROP_V3(TSPropertySignatureSetTsTypeAnnotation, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSConditionalType(KNativePointer context, KNativePointer checkType, KNativePointer extendsType, KNativePointer trueType, KNativePointer falseType)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _checkType = reinterpret_cast<es2panda_AstNode*>(checkType);
    const auto _extendsType = reinterpret_cast<es2panda_AstNode*>(extendsType);
    const auto _trueType = reinterpret_cast<es2panda_AstNode*>(trueType);
    const auto _falseType = reinterpret_cast<es2panda_AstNode*>(falseType);
    auto result = GetImpl()->CreateTSConditionalType(_context, _checkType, _extendsType, _trueType, _falseType);
    return result;
}
KOALA_INTEROP_5(CreateTSConditionalType, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateTSConditionalType(KNativePointer context, KNativePointer original, KNativePointer checkType, KNativePointer extendsType, KNativePointer trueType, KNativePointer falseType)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _checkType = reinterpret_cast<es2panda_AstNode*>(checkType);
    const auto _extendsType = reinterpret_cast<es2panda_AstNode*>(extendsType);
    const auto _trueType = reinterpret_cast<es2panda_AstNode*>(trueType);
    const auto _falseType = reinterpret_cast<es2panda_AstNode*>(falseType);
    auto result = GetImpl()->UpdateTSConditionalType(_context, _original, _checkType, _extendsType, _trueType, _falseType);
    return result;
}
KOALA_INTEROP_6(UpdateTSConditionalType, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSConditionalTypeCheckTypeConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSConditionalTypeCheckTypeConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSConditionalTypeCheckTypeConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSConditionalTypeExtendsTypeConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSConditionalTypeExtendsTypeConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSConditionalTypeExtendsTypeConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSConditionalTypeTrueTypeConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSConditionalTypeTrueTypeConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSConditionalTypeTrueTypeConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSConditionalTypeFalseTypeConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSConditionalTypeFalseTypeConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSConditionalTypeFalseTypeConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSLiteralType(KNativePointer context, KNativePointer literal)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _literal = reinterpret_cast<es2panda_AstNode*>(literal);
    auto result = GetImpl()->CreateTSLiteralType(_context, _literal);
    return result;
}
KOALA_INTEROP_2(CreateTSLiteralType, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateTSLiteralType(KNativePointer context, KNativePointer original, KNativePointer literal)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _literal = reinterpret_cast<es2panda_AstNode*>(literal);
    auto result = GetImpl()->UpdateTSLiteralType(_context, _original, _literal);
    return result;
}
KOALA_INTEROP_3(UpdateTSLiteralType, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSLiteralTypeLiteralConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSLiteralTypeLiteralConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSLiteralTypeLiteralConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSTypeAliasDeclaration(KNativePointer context, KNativePointer id, KNativePointer typeParams, KNativePointer typeAnnotation)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _id = reinterpret_cast<es2panda_AstNode*>(id);
    const auto _typeParams = reinterpret_cast<es2panda_AstNode*>(typeParams);
    const auto _typeAnnotation = reinterpret_cast<es2panda_AstNode*>(typeAnnotation);
    auto result = GetImpl()->CreateTSTypeAliasDeclaration(_context, _id, _typeParams, _typeAnnotation);
    return result;
}
KOALA_INTEROP_4(CreateTSTypeAliasDeclaration, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateTSTypeAliasDeclaration(KNativePointer context, KNativePointer original, KNativePointer id, KNativePointer typeParams, KNativePointer typeAnnotation)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _id = reinterpret_cast<es2panda_AstNode*>(id);
    const auto _typeParams = reinterpret_cast<es2panda_AstNode*>(typeParams);
    const auto _typeAnnotation = reinterpret_cast<es2panda_AstNode*>(typeAnnotation);
    auto result = GetImpl()->UpdateTSTypeAliasDeclaration(_context, _original, _id, _typeParams, _typeAnnotation);
    return result;
}
KOALA_INTEROP_5(UpdateTSTypeAliasDeclaration, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSTypeAliasDeclaration1(KNativePointer context, KNativePointer id)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _id = reinterpret_cast<es2panda_AstNode*>(id);
    auto result = GetImpl()->CreateTSTypeAliasDeclaration1(_context, _id);
    return result;
}
KOALA_INTEROP_2(CreateTSTypeAliasDeclaration1, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateTSTypeAliasDeclaration1(KNativePointer context, KNativePointer original, KNativePointer id)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _id = reinterpret_cast<es2panda_AstNode*>(id);
    auto result = GetImpl()->UpdateTSTypeAliasDeclaration1(_context, _original, _id);
    return result;
}
KOALA_INTEROP_3(UpdateTSTypeAliasDeclaration1, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSTypeAliasDeclarationId(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSTypeAliasDeclarationId(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSTypeAliasDeclarationId, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSTypeAliasDeclarationIdConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSTypeAliasDeclarationIdConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSTypeAliasDeclarationIdConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSTypeAliasDeclarationTypeParamsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSTypeAliasDeclarationTypeParamsConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSTypeAliasDeclarationTypeParamsConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSTypeAliasDeclarationDecoratorsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->TSTypeAliasDeclarationDecoratorsConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(TSTypeAliasDeclarationDecoratorsConst, KNativePointer, KNativePointer, KNativePointer);

void impl_TSTypeAliasDeclarationSetTypeParameters(KNativePointer context, KNativePointer receiver, KNativePointer typeParams)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _typeParams = reinterpret_cast<es2panda_AstNode*>(typeParams);
    GetImpl()->TSTypeAliasDeclarationSetTypeParameters(_context, _receiver, _typeParams);
    return ;
}
KOALA_INTEROP_V3(TSTypeAliasDeclarationSetTypeParameters, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSTypeAliasDeclarationAnnotations(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->TSTypeAliasDeclarationAnnotations(_context, _receiver, &length);
    return new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(TSTypeAliasDeclarationAnnotations, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSTypeAliasDeclarationAnnotationsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->TSTypeAliasDeclarationAnnotationsConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(TSTypeAliasDeclarationAnnotationsConst, KNativePointer, KNativePointer, KNativePointer);

void impl_TSTypeAliasDeclarationSetAnnotations(KNativePointer context, KNativePointer receiver, KNativePointerArray annotations, KUInt annotationsSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _annotations = reinterpret_cast<es2panda_AstNode**>(annotations);
    const auto _annotationsSequenceLength = static_cast<KUInt>(annotationsSequenceLength);
    GetImpl()->TSTypeAliasDeclarationSetAnnotations(_context, _receiver, _annotations, _annotationsSequenceLength);
    return ;
}
KOALA_INTEROP_V4(TSTypeAliasDeclarationSetAnnotations, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_TSTypeAliasDeclarationTypeAnnotationConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSTypeAliasDeclarationTypeAnnotationConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSTypeAliasDeclarationTypeAnnotationConst, KNativePointer, KNativePointer, KNativePointer);

void impl_TSTypeAliasDeclarationSetTsTypeAnnotation(KNativePointer context, KNativePointer receiver, KNativePointer typeAnnotation)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _typeAnnotation = reinterpret_cast<es2panda_AstNode*>(typeAnnotation);
    GetImpl()->TSTypeAliasDeclarationSetTsTypeAnnotation(_context, _receiver, _typeAnnotation);
    return ;
}
KOALA_INTEROP_V3(TSTypeAliasDeclarationSetTsTypeAnnotation, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateDebuggerStatement(KNativePointer context)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    auto result = GetImpl()->CreateDebuggerStatement(_context);
    return result;
}
KOALA_INTEROP_1(CreateDebuggerStatement, KNativePointer, KNativePointer);

KNativePointer impl_UpdateDebuggerStatement(KNativePointer context, KNativePointer original)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    auto result = GetImpl()->UpdateDebuggerStatement(_context, _original);
    return result;
}
KOALA_INTEROP_2(UpdateDebuggerStatement, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateReturnStatement(KNativePointer context)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    auto result = GetImpl()->CreateReturnStatement(_context);
    return result;
}
KOALA_INTEROP_1(CreateReturnStatement, KNativePointer, KNativePointer);

KNativePointer impl_UpdateReturnStatement(KNativePointer context, KNativePointer original)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    auto result = GetImpl()->UpdateReturnStatement(_context, _original);
    return result;
}
KOALA_INTEROP_2(UpdateReturnStatement, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateReturnStatement1(KNativePointer context, KNativePointer argument)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _argument = reinterpret_cast<es2panda_AstNode*>(argument);
    auto result = GetImpl()->CreateReturnStatement1(_context, _argument);
    return result;
}
KOALA_INTEROP_2(CreateReturnStatement1, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateReturnStatement1(KNativePointer context, KNativePointer original, KNativePointer argument)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _argument = reinterpret_cast<es2panda_AstNode*>(argument);
    auto result = GetImpl()->UpdateReturnStatement1(_context, _original, _argument);
    return result;
}
KOALA_INTEROP_3(UpdateReturnStatement1, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ReturnStatementArgument(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ReturnStatementArgument(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ReturnStatementArgument, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ReturnStatementArgumentConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ReturnStatementArgumentConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ReturnStatementArgumentConst, KNativePointer, KNativePointer, KNativePointer);

void impl_ReturnStatementSetArgument(KNativePointer context, KNativePointer receiver, KNativePointer arg)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _arg = reinterpret_cast<es2panda_AstNode*>(arg);
    GetImpl()->ReturnStatementSetArgument(_context, _receiver, _arg);
    return ;
}
KOALA_INTEROP_V3(ReturnStatementSetArgument, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateExportDefaultDeclaration(KNativePointer context, KNativePointer decl, KBoolean exportEquals)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _decl = reinterpret_cast<es2panda_AstNode*>(decl);
    const auto _exportEquals = static_cast<KBoolean>(exportEquals);
    auto result = GetImpl()->CreateExportDefaultDeclaration(_context, _decl, _exportEquals);
    return result;
}
KOALA_INTEROP_3(CreateExportDefaultDeclaration, KNativePointer, KNativePointer, KNativePointer, KBoolean);

KNativePointer impl_UpdateExportDefaultDeclaration(KNativePointer context, KNativePointer original, KNativePointer decl, KBoolean exportEquals)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _decl = reinterpret_cast<es2panda_AstNode*>(decl);
    const auto _exportEquals = static_cast<KBoolean>(exportEquals);
    auto result = GetImpl()->UpdateExportDefaultDeclaration(_context, _original, _decl, _exportEquals);
    return result;
}
KOALA_INTEROP_4(UpdateExportDefaultDeclaration, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KBoolean);

KNativePointer impl_ExportDefaultDeclarationDecl(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ExportDefaultDeclarationDecl(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ExportDefaultDeclarationDecl, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ExportDefaultDeclarationDeclConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ExportDefaultDeclarationDeclConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ExportDefaultDeclarationDeclConst, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_ExportDefaultDeclarationIsExportEqualsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ExportDefaultDeclarationIsExportEqualsConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ExportDefaultDeclarationIsExportEqualsConst, KBoolean, KNativePointer, KNativePointer);

KNativePointer impl_CreateScriptFunction(KNativePointer context, KNativePointer databody, KNativePointer datasignature, KInt datafuncFlags, KInt dataflags)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _databody = reinterpret_cast<es2panda_AstNode*>(databody);
    const auto _datasignature = reinterpret_cast<es2panda_FunctionSignature*>(datasignature);
    const auto _datafuncFlags = static_cast<KInt>(datafuncFlags);
    const auto _dataflags = static_cast<KInt>(dataflags);
    auto result = GetImpl()->CreateScriptFunction(_context, _databody, _datasignature, _datafuncFlags, _dataflags);
    return result;
}
KOALA_INTEROP_5(CreateScriptFunction, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KInt, KInt);

KNativePointer impl_UpdateScriptFunction(KNativePointer context, KNativePointer original, KNativePointer databody, KNativePointer datasignature, KInt datafuncFlags, KInt dataflags)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _databody = reinterpret_cast<es2panda_AstNode*>(databody);
    const auto _datasignature = reinterpret_cast<es2panda_FunctionSignature*>(datasignature);
    const auto _datafuncFlags = static_cast<KInt>(datafuncFlags);
    const auto _dataflags = static_cast<KInt>(dataflags);
    auto result = GetImpl()->UpdateScriptFunction(_context, _original, _databody, _datasignature, _datafuncFlags, _dataflags);
    return result;
}
KOALA_INTEROP_6(UpdateScriptFunction, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KInt, KInt);

KNativePointer impl_ScriptFunctionIdConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ScriptFunctionIdConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ScriptFunctionIdConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ScriptFunctionId(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ScriptFunctionId(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ScriptFunctionId, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ScriptFunctionParamsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->ScriptFunctionParamsConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(ScriptFunctionParamsConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ScriptFunctionParams(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->ScriptFunctionParams(_context, _receiver, &length);
    return new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(ScriptFunctionParams, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ScriptFunctionReturnStatementsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->ScriptFunctionReturnStatementsConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(ScriptFunctionReturnStatementsConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ScriptFunctionReturnStatements(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->ScriptFunctionReturnStatements(_context, _receiver, &length);
    return new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(ScriptFunctionReturnStatements, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ScriptFunctionTypeParamsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ScriptFunctionTypeParamsConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ScriptFunctionTypeParamsConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ScriptFunctionTypeParams(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ScriptFunctionTypeParams(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ScriptFunctionTypeParams, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ScriptFunctionBodyConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ScriptFunctionBodyConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ScriptFunctionBodyConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ScriptFunctionBody(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ScriptFunctionBody(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ScriptFunctionBody, KNativePointer, KNativePointer, KNativePointer);

void impl_ScriptFunctionAddReturnStatement(KNativePointer context, KNativePointer receiver, KNativePointer returnStatement)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _returnStatement = reinterpret_cast<es2panda_AstNode*>(returnStatement);
    GetImpl()->ScriptFunctionAddReturnStatement(_context, _receiver, _returnStatement);
    return ;
}
KOALA_INTEROP_V3(ScriptFunctionAddReturnStatement, KNativePointer, KNativePointer, KNativePointer);

void impl_ScriptFunctionSetBody(KNativePointer context, KNativePointer receiver, KNativePointer body)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _body = reinterpret_cast<es2panda_AstNode*>(body);
    GetImpl()->ScriptFunctionSetBody(_context, _receiver, _body);
    return ;
}
KOALA_INTEROP_V3(ScriptFunctionSetBody, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ScriptFunctionReturnTypeAnnotationConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ScriptFunctionReturnTypeAnnotationConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ScriptFunctionReturnTypeAnnotationConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ScriptFunctionReturnTypeAnnotation(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ScriptFunctionReturnTypeAnnotation(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ScriptFunctionReturnTypeAnnotation, KNativePointer, KNativePointer, KNativePointer);

void impl_ScriptFunctionSetReturnTypeAnnotation(KNativePointer context, KNativePointer receiver, KNativePointer node)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _node = reinterpret_cast<es2panda_AstNode*>(node);
    GetImpl()->ScriptFunctionSetReturnTypeAnnotation(_context, _receiver, _node);
    return ;
}
KOALA_INTEROP_V3(ScriptFunctionSetReturnTypeAnnotation, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_ScriptFunctionIsEntryPointConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ScriptFunctionIsEntryPointConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ScriptFunctionIsEntryPointConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_ScriptFunctionIsGeneratorConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ScriptFunctionIsGeneratorConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ScriptFunctionIsGeneratorConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_ScriptFunctionIsAsyncFuncConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ScriptFunctionIsAsyncFuncConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ScriptFunctionIsAsyncFuncConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_ScriptFunctionIsAsyncImplFuncConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ScriptFunctionIsAsyncImplFuncConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ScriptFunctionIsAsyncImplFuncConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_ScriptFunctionIsArrowConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ScriptFunctionIsArrowConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ScriptFunctionIsArrowConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_ScriptFunctionIsOverloadConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ScriptFunctionIsOverloadConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ScriptFunctionIsOverloadConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_ScriptFunctionIsExternalOverloadConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ScriptFunctionIsExternalOverloadConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ScriptFunctionIsExternalOverloadConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_ScriptFunctionIsConstructorConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ScriptFunctionIsConstructorConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ScriptFunctionIsConstructorConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_ScriptFunctionIsGetterConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ScriptFunctionIsGetterConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ScriptFunctionIsGetterConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_ScriptFunctionIsSetterConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ScriptFunctionIsSetterConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ScriptFunctionIsSetterConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_ScriptFunctionIsExtensionAccessorConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ScriptFunctionIsExtensionAccessorConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ScriptFunctionIsExtensionAccessorConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_ScriptFunctionIsMethodConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ScriptFunctionIsMethodConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ScriptFunctionIsMethodConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_ScriptFunctionIsProxyConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ScriptFunctionIsProxyConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ScriptFunctionIsProxyConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_ScriptFunctionIsStaticBlockConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ScriptFunctionIsStaticBlockConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ScriptFunctionIsStaticBlockConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_ScriptFunctionIsEnumConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ScriptFunctionIsEnumConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ScriptFunctionIsEnumConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_ScriptFunctionIsHiddenConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ScriptFunctionIsHiddenConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ScriptFunctionIsHiddenConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_ScriptFunctionIsExternalConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ScriptFunctionIsExternalConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ScriptFunctionIsExternalConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_ScriptFunctionIsImplicitSuperCallNeededConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ScriptFunctionIsImplicitSuperCallNeededConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ScriptFunctionIsImplicitSuperCallNeededConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_ScriptFunctionHasBodyConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ScriptFunctionHasBodyConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ScriptFunctionHasBodyConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_ScriptFunctionHasRestParameterConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ScriptFunctionHasRestParameterConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ScriptFunctionHasRestParameterConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_ScriptFunctionHasReturnStatementConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ScriptFunctionHasReturnStatementConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ScriptFunctionHasReturnStatementConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_ScriptFunctionHasThrowStatementConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ScriptFunctionHasThrowStatementConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ScriptFunctionHasThrowStatementConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_ScriptFunctionIsThrowingConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ScriptFunctionIsThrowingConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ScriptFunctionIsThrowingConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_ScriptFunctionIsRethrowingConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ScriptFunctionIsRethrowingConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ScriptFunctionIsRethrowingConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_ScriptFunctionIsDynamicConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ScriptFunctionIsDynamicConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ScriptFunctionIsDynamicConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_ScriptFunctionIsExtensionMethodConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ScriptFunctionIsExtensionMethodConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ScriptFunctionIsExtensionMethodConst, KBoolean, KNativePointer, KNativePointer);

KInt impl_ScriptFunctionFlagsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ScriptFunctionFlagsConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ScriptFunctionFlagsConst, KInt, KNativePointer, KNativePointer);

KBoolean impl_ScriptFunctionHasReceiverConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ScriptFunctionHasReceiverConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ScriptFunctionHasReceiverConst, KBoolean, KNativePointer, KNativePointer);

void impl_ScriptFunctionSetIdent(KNativePointer context, KNativePointer receiver, KNativePointer id)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _id = reinterpret_cast<es2panda_AstNode*>(id);
    GetImpl()->ScriptFunctionSetIdent(_context, _receiver, _id);
    return ;
}
KOALA_INTEROP_V3(ScriptFunctionSetIdent, KNativePointer, KNativePointer, KNativePointer);

void impl_ScriptFunctionAddFlag(KNativePointer context, KNativePointer receiver, KInt flags)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _flags = static_cast<Es2pandaScriptFunctionFlags>(flags);
    GetImpl()->ScriptFunctionAddFlag(_context, _receiver, _flags);
    return ;
}
KOALA_INTEROP_V3(ScriptFunctionAddFlag, KNativePointer, KNativePointer, KInt);

void impl_ScriptFunctionAddModifier(KNativePointer context, KNativePointer receiver, KInt flags)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _flags = static_cast<Es2pandaModifierFlags>(flags);
    GetImpl()->ScriptFunctionAddModifier(_context, _receiver, _flags);
    return ;
}
KOALA_INTEROP_V3(ScriptFunctionAddModifier, KNativePointer, KNativePointer, KInt);

KUInt impl_ScriptFunctionFormalParamsLengthConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ScriptFunctionFormalParamsLengthConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ScriptFunctionFormalParamsLengthConst, KUInt, KNativePointer, KNativePointer);

KNativePointer impl_ScriptFunctionAnnotations(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->ScriptFunctionAnnotations(_context, _receiver, &length);
    return new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(ScriptFunctionAnnotations, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ScriptFunctionAnnotationsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->ScriptFunctionAnnotationsConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(ScriptFunctionAnnotationsConst, KNativePointer, KNativePointer, KNativePointer);

void impl_ScriptFunctionSetAnnotations(KNativePointer context, KNativePointer receiver, KNativePointerArray annotations, KUInt annotationsSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _annotations = reinterpret_cast<es2panda_AstNode**>(annotations);
    const auto _annotationsSequenceLength = static_cast<KUInt>(annotationsSequenceLength);
    GetImpl()->ScriptFunctionSetAnnotations(_context, _receiver, _annotations, _annotationsSequenceLength);
    return ;
}
KOALA_INTEROP_V4(ScriptFunctionSetAnnotations, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_CreateClassDefinition(KNativePointer context, KNativePointer ident, KNativePointer typeParams, KNativePointer superTypeParams, KNativePointerArray _implements, KUInt _implementsSequenceLength, KNativePointer ctor, KNativePointer superClass, KNativePointerArray body, KUInt bodySequenceLength, KInt modifiers, KInt flags)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _ident = reinterpret_cast<es2panda_AstNode*>(ident);
    const auto _typeParams = reinterpret_cast<es2panda_AstNode*>(typeParams);
    const auto _superTypeParams = reinterpret_cast<es2panda_AstNode*>(superTypeParams);
    const auto __implements = reinterpret_cast<es2panda_AstNode**>(_implements);
    const auto __implementsSequenceLength = static_cast<KUInt>(_implementsSequenceLength);
    const auto _ctor = reinterpret_cast<es2panda_AstNode*>(ctor);
    const auto _superClass = reinterpret_cast<es2panda_AstNode*>(superClass);
    const auto _body = reinterpret_cast<es2panda_AstNode**>(body);
    const auto _bodySequenceLength = static_cast<KUInt>(bodySequenceLength);
    const auto _modifiers = static_cast<Es2pandaClassDefinitionModifiers>(modifiers);
    const auto _flags = static_cast<Es2pandaModifierFlags>(flags);
    auto result = GetImpl()->CreateClassDefinition(_context, _ident, _typeParams, _superTypeParams, __implements, __implementsSequenceLength, _ctor, _superClass, _body, _bodySequenceLength, _modifiers, _flags);
    return result;
}
KOALA_INTEROP_12(CreateClassDefinition, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt, KNativePointer, KNativePointer, KNativePointerArray, KUInt, KInt, KInt);

KNativePointer impl_UpdateClassDefinition(KNativePointer context, KNativePointer original, KNativePointer ident, KNativePointer typeParams, KNativePointer superTypeParams, KNativePointerArray _implements, KUInt _implementsSequenceLength, KNativePointer ctor, KNativePointer superClass, KNativePointerArray body, KUInt bodySequenceLength, KInt modifiers, KInt flags)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _ident = reinterpret_cast<es2panda_AstNode*>(ident);
    const auto _typeParams = reinterpret_cast<es2panda_AstNode*>(typeParams);
    const auto _superTypeParams = reinterpret_cast<es2panda_AstNode*>(superTypeParams);
    const auto __implements = reinterpret_cast<es2panda_AstNode**>(_implements);
    const auto __implementsSequenceLength = static_cast<KUInt>(_implementsSequenceLength);
    const auto _ctor = reinterpret_cast<es2panda_AstNode*>(ctor);
    const auto _superClass = reinterpret_cast<es2panda_AstNode*>(superClass);
    const auto _body = reinterpret_cast<es2panda_AstNode**>(body);
    const auto _bodySequenceLength = static_cast<KUInt>(bodySequenceLength);
    const auto _modifiers = static_cast<Es2pandaClassDefinitionModifiers>(modifiers);
    const auto _flags = static_cast<Es2pandaModifierFlags>(flags);
    auto result = GetImpl()->UpdateClassDefinition(_context, _original, _ident, _typeParams, _superTypeParams, __implements, __implementsSequenceLength, _ctor, _superClass, _body, _bodySequenceLength, _modifiers, _flags);
    return result;
}
KOALA_INTEROP_13(UpdateClassDefinition, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt, KNativePointer, KNativePointer, KNativePointerArray, KUInt, KInt, KInt);

KNativePointer impl_CreateClassDefinition1(KNativePointer context, KNativePointer ident, KNativePointerArray body, KUInt bodySequenceLength, KInt modifiers, KInt flags)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _ident = reinterpret_cast<es2panda_AstNode*>(ident);
    const auto _body = reinterpret_cast<es2panda_AstNode**>(body);
    const auto _bodySequenceLength = static_cast<KUInt>(bodySequenceLength);
    const auto _modifiers = static_cast<Es2pandaClassDefinitionModifiers>(modifiers);
    const auto _flags = static_cast<Es2pandaModifierFlags>(flags);
    auto result = GetImpl()->CreateClassDefinition1(_context, _ident, _body, _bodySequenceLength, _modifiers, _flags);
    return result;
}
KOALA_INTEROP_6(CreateClassDefinition1, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt, KInt, KInt);

KNativePointer impl_UpdateClassDefinition1(KNativePointer context, KNativePointer original, KNativePointer ident, KNativePointerArray body, KUInt bodySequenceLength, KInt modifiers, KInt flags)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _ident = reinterpret_cast<es2panda_AstNode*>(ident);
    const auto _body = reinterpret_cast<es2panda_AstNode**>(body);
    const auto _bodySequenceLength = static_cast<KUInt>(bodySequenceLength);
    const auto _modifiers = static_cast<Es2pandaClassDefinitionModifiers>(modifiers);
    const auto _flags = static_cast<Es2pandaModifierFlags>(flags);
    auto result = GetImpl()->UpdateClassDefinition1(_context, _original, _ident, _body, _bodySequenceLength, _modifiers, _flags);
    return result;
}
KOALA_INTEROP_7(UpdateClassDefinition1, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt, KInt, KInt);

KNativePointer impl_CreateClassDefinition2(KNativePointer context, KNativePointer ident, KInt modifiers, KInt flags)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _ident = reinterpret_cast<es2panda_AstNode*>(ident);
    const auto _modifiers = static_cast<Es2pandaClassDefinitionModifiers>(modifiers);
    const auto _flags = static_cast<Es2pandaModifierFlags>(flags);
    auto result = GetImpl()->CreateClassDefinition2(_context, _ident, _modifiers, _flags);
    return result;
}
KOALA_INTEROP_4(CreateClassDefinition2, KNativePointer, KNativePointer, KNativePointer, KInt, KInt);

KNativePointer impl_UpdateClassDefinition2(KNativePointer context, KNativePointer original, KNativePointer ident, KInt modifiers, KInt flags)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _ident = reinterpret_cast<es2panda_AstNode*>(ident);
    const auto _modifiers = static_cast<Es2pandaClassDefinitionModifiers>(modifiers);
    const auto _flags = static_cast<Es2pandaModifierFlags>(flags);
    auto result = GetImpl()->UpdateClassDefinition2(_context, _original, _ident, _modifiers, _flags);
    return result;
}
KOALA_INTEROP_5(UpdateClassDefinition2, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KInt, KInt);

KNativePointer impl_ClassDefinitionIdentConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ClassDefinitionIdentConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ClassDefinitionIdentConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ClassDefinitionIdent(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ClassDefinitionIdent(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ClassDefinitionIdent, KNativePointer, KNativePointer, KNativePointer);

void impl_ClassDefinitionSetIdent(KNativePointer context, KNativePointer receiver, KNativePointer ident)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _ident = reinterpret_cast<es2panda_AstNode*>(ident);
    GetImpl()->ClassDefinitionSetIdent(_context, _receiver, _ident);
    return ;
}
KOALA_INTEROP_V3(ClassDefinitionSetIdent, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ClassDefinitionInternalNameConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ClassDefinitionInternalNameConst(_context, _receiver);
    return new std::string(result);
}
KOALA_INTEROP_2(ClassDefinitionInternalNameConst, KNativePointer, KNativePointer, KNativePointer);

void impl_ClassDefinitionSetInternalName(KNativePointer context, KNativePointer receiver, KStringPtr& internalName)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _internalName = getStringCopy(internalName);
    GetImpl()->ClassDefinitionSetInternalName(_context, _receiver, _internalName);
    return ;
}
KOALA_INTEROP_V3(ClassDefinitionSetInternalName, KNativePointer, KNativePointer, KStringPtr);

KNativePointer impl_ClassDefinitionSuper(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ClassDefinitionSuper(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ClassDefinitionSuper, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ClassDefinitionSuperConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ClassDefinitionSuperConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ClassDefinitionSuperConst, KNativePointer, KNativePointer, KNativePointer);

void impl_ClassDefinitionSetSuper(KNativePointer context, KNativePointer receiver, KNativePointer superClass)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _superClass = reinterpret_cast<es2panda_AstNode*>(superClass);
    GetImpl()->ClassDefinitionSetSuper(_context, _receiver, _superClass);
    return ;
}
KOALA_INTEROP_V3(ClassDefinitionSetSuper, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_ClassDefinitionIsGlobalConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ClassDefinitionIsGlobalConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ClassDefinitionIsGlobalConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_ClassDefinitionIsLocalConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ClassDefinitionIsLocalConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ClassDefinitionIsLocalConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_ClassDefinitionIsExternConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ClassDefinitionIsExternConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ClassDefinitionIsExternConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_ClassDefinitionIsFromExternalConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ClassDefinitionIsFromExternalConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ClassDefinitionIsFromExternalConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_ClassDefinitionIsInnerConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ClassDefinitionIsInnerConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ClassDefinitionIsInnerConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_ClassDefinitionIsGlobalInitializedConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ClassDefinitionIsGlobalInitializedConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ClassDefinitionIsGlobalInitializedConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_ClassDefinitionIsClassDefinitionCheckedConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ClassDefinitionIsClassDefinitionCheckedConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ClassDefinitionIsClassDefinitionCheckedConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_ClassDefinitionIsAnonymousConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ClassDefinitionIsAnonymousConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ClassDefinitionIsAnonymousConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_ClassDefinitionIsNamespaceTransformedConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ClassDefinitionIsNamespaceTransformedConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ClassDefinitionIsNamespaceTransformedConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_ClassDefinitionIsModuleConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ClassDefinitionIsModuleConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ClassDefinitionIsModuleConst, KBoolean, KNativePointer, KNativePointer);

void impl_ClassDefinitionSetGlobalInitialized(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    GetImpl()->ClassDefinitionSetGlobalInitialized(_context, _receiver);
    return ;
}
KOALA_INTEROP_V2(ClassDefinitionSetGlobalInitialized, KNativePointer, KNativePointer);

void impl_ClassDefinitionSetInnerModifier(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    GetImpl()->ClassDefinitionSetInnerModifier(_context, _receiver);
    return ;
}
KOALA_INTEROP_V2(ClassDefinitionSetInnerModifier, KNativePointer, KNativePointer);

void impl_ClassDefinitionSetClassDefinitionChecked(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    GetImpl()->ClassDefinitionSetClassDefinitionChecked(_context, _receiver);
    return ;
}
KOALA_INTEROP_V2(ClassDefinitionSetClassDefinitionChecked, KNativePointer, KNativePointer);

void impl_ClassDefinitionSetAnonymousModifier(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    GetImpl()->ClassDefinitionSetAnonymousModifier(_context, _receiver);
    return ;
}
KOALA_INTEROP_V2(ClassDefinitionSetAnonymousModifier, KNativePointer, KNativePointer);

void impl_ClassDefinitionSetNamespaceTransformed(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    GetImpl()->ClassDefinitionSetNamespaceTransformed(_context, _receiver);
    return ;
}
KOALA_INTEROP_V2(ClassDefinitionSetNamespaceTransformed, KNativePointer, KNativePointer);

KInt impl_ClassDefinitionModifiersConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ClassDefinitionModifiersConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ClassDefinitionModifiersConst, KInt, KNativePointer, KNativePointer);

void impl_ClassDefinitionSetModifiers(KNativePointer context, KNativePointer receiver, KInt modifiers)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _modifiers = static_cast<Es2pandaClassDefinitionModifiers>(modifiers);
    GetImpl()->ClassDefinitionSetModifiers(_context, _receiver, _modifiers);
    return ;
}
KOALA_INTEROP_V3(ClassDefinitionSetModifiers, KNativePointer, KNativePointer, KInt);

void impl_ClassDefinitionAddProperties(KNativePointer context, KNativePointer receiver, KNativePointerArray body, KUInt bodySequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _body = reinterpret_cast<es2panda_AstNode**>(body);
    const auto _bodySequenceLength = static_cast<KUInt>(bodySequenceLength);
    GetImpl()->ClassDefinitionAddProperties(_context, _receiver, _body, _bodySequenceLength);
    return ;
}
KOALA_INTEROP_V4(ClassDefinitionAddProperties, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_ClassDefinitionBody(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->ClassDefinitionBody(_context, _receiver, &length);
    return new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(ClassDefinitionBody, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ClassDefinitionBodyConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->ClassDefinitionBodyConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(ClassDefinitionBodyConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ClassDefinitionCtor(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ClassDefinitionCtor(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ClassDefinitionCtor, KNativePointer, KNativePointer, KNativePointer);

void impl_ClassDefinitionSetCtor(KNativePointer context, KNativePointer receiver, KNativePointer ctor)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _ctor = reinterpret_cast<es2panda_AstNode*>(ctor);
    GetImpl()->ClassDefinitionSetCtor(_context, _receiver, _ctor);
    return ;
}
KOALA_INTEROP_V3(ClassDefinitionSetCtor, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ClassDefinitionImplements(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->ClassDefinitionImplements(_context, _receiver, &length);
    return new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(ClassDefinitionImplements, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ClassDefinitionImplementsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->ClassDefinitionImplementsConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(ClassDefinitionImplementsConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ClassDefinitionTypeParamsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ClassDefinitionTypeParamsConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ClassDefinitionTypeParamsConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ClassDefinitionTypeParams(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ClassDefinitionTypeParams(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ClassDefinitionTypeParams, KNativePointer, KNativePointer, KNativePointer);

void impl_ClassDefinitionSetTypeParams(KNativePointer context, KNativePointer receiver, KNativePointer typeParams)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _typeParams = reinterpret_cast<es2panda_AstNode*>(typeParams);
    GetImpl()->ClassDefinitionSetTypeParams(_context, _receiver, _typeParams);
    return ;
}
KOALA_INTEROP_V3(ClassDefinitionSetTypeParams, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ClassDefinitionSuperTypeParamsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ClassDefinitionSuperTypeParamsConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ClassDefinitionSuperTypeParamsConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ClassDefinitionSuperTypeParams(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ClassDefinitionSuperTypeParams(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ClassDefinitionSuperTypeParams, KNativePointer, KNativePointer, KNativePointer);

KInt impl_ClassDefinitionLocalTypeCounter(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ClassDefinitionLocalTypeCounter(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ClassDefinitionLocalTypeCounter, KInt, KNativePointer, KNativePointer);

KInt impl_ClassDefinitionLocalIndexConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ClassDefinitionLocalIndexConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ClassDefinitionLocalIndexConst, KInt, KNativePointer, KNativePointer);

KNativePointer impl_ClassDefinitionLocalPrefixConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ClassDefinitionLocalPrefixConst(_context, _receiver);
    return new std::string(result);
}
KOALA_INTEROP_2(ClassDefinitionLocalPrefixConst, KNativePointer, KNativePointer, KNativePointer);

void impl_ClassDefinitionSetOrigEnumDecl(KNativePointer context, KNativePointer receiver, KNativePointer enumDecl)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _enumDecl = reinterpret_cast<es2panda_AstNode*>(enumDecl);
    GetImpl()->ClassDefinitionSetOrigEnumDecl(_context, _receiver, _enumDecl);
    return ;
}
KOALA_INTEROP_V3(ClassDefinitionSetOrigEnumDecl, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ClassDefinitionOrigEnumDeclConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ClassDefinitionOrigEnumDeclConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ClassDefinitionOrigEnumDeclConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ClassDefinitionGetAnonClass(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ClassDefinitionGetAnonClass(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ClassDefinitionGetAnonClass, KNativePointer, KNativePointer, KNativePointer);

void impl_ClassDefinitionSetAnonClass(KNativePointer context, KNativePointer receiver, KNativePointer anonClass)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _anonClass = reinterpret_cast<es2panda_AstNode*>(anonClass);
    GetImpl()->ClassDefinitionSetAnonClass(_context, _receiver, _anonClass);
    return ;
}
KOALA_INTEROP_V3(ClassDefinitionSetAnonClass, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ClassDefinitionCtorConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ClassDefinitionCtorConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ClassDefinitionCtorConst, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_ClassDefinitionHasPrivateMethodConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ClassDefinitionHasPrivateMethodConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ClassDefinitionHasPrivateMethodConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_ClassDefinitionHasComputedInstanceFieldConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ClassDefinitionHasComputedInstanceFieldConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ClassDefinitionHasComputedInstanceFieldConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_ClassDefinitionHasMatchingPrivateKeyConst(KNativePointer context, KNativePointer receiver, KStringPtr& name)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _name = getStringCopy(name);
    auto result = GetImpl()->ClassDefinitionHasMatchingPrivateKeyConst(_context, _receiver, _name);
    return result;
}
KOALA_INTEROP_3(ClassDefinitionHasMatchingPrivateKeyConst, KBoolean, KNativePointer, KNativePointer, KStringPtr);

KNativePointer impl_ClassDefinitionAnnotations(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->ClassDefinitionAnnotations(_context, _receiver, &length);
    return new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(ClassDefinitionAnnotations, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ClassDefinitionAnnotationsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->ClassDefinitionAnnotationsConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(ClassDefinitionAnnotationsConst, KNativePointer, KNativePointer, KNativePointer);

void impl_ClassDefinitionSetAnnotations(KNativePointer context, KNativePointer receiver, KNativePointerArray annotations, KUInt annotationsSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _annotations = reinterpret_cast<es2panda_AstNode**>(annotations);
    const auto _annotationsSequenceLength = static_cast<KUInt>(annotationsSequenceLength);
    GetImpl()->ClassDefinitionSetAnnotations(_context, _receiver, _annotations, _annotationsSequenceLength);
    return ;
}
KOALA_INTEROP_V4(ClassDefinitionSetAnnotations, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_CreateArrayExpression(KNativePointer context, KNativePointerArray elements, KUInt elementsSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _elements = reinterpret_cast<es2panda_AstNode**>(elements);
    const auto _elementsSequenceLength = static_cast<KUInt>(elementsSequenceLength);
    auto result = GetImpl()->CreateArrayExpression(_context, _elements, _elementsSequenceLength);
    return result;
}
KOALA_INTEROP_3(CreateArrayExpression, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_UpdateArrayExpression(KNativePointer context, KNativePointer original, KNativePointerArray elements, KUInt elementsSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _elements = reinterpret_cast<es2panda_AstNode**>(elements);
    const auto _elementsSequenceLength = static_cast<KUInt>(elementsSequenceLength);
    auto result = GetImpl()->UpdateArrayExpression(_context, _original, _elements, _elementsSequenceLength);
    return result;
}
KOALA_INTEROP_4(UpdateArrayExpression, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_CreateArrayExpression1(KNativePointer context, KInt nodeType, KNativePointerArray elements, KUInt elementsSequenceLength, KBoolean trailingComma)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _nodeType = static_cast<Es2pandaAstNodeType>(nodeType);
    const auto _elements = reinterpret_cast<es2panda_AstNode**>(elements);
    const auto _elementsSequenceLength = static_cast<KUInt>(elementsSequenceLength);
    const auto _trailingComma = static_cast<KBoolean>(trailingComma);
    auto result = GetImpl()->CreateArrayExpression1(_context, _nodeType, _elements, _elementsSequenceLength, _trailingComma);
    return result;
}
KOALA_INTEROP_5(CreateArrayExpression1, KNativePointer, KNativePointer, KInt, KNativePointerArray, KUInt, KBoolean);

KNativePointer impl_UpdateArrayExpression1(KNativePointer context, KNativePointer original, KInt nodeType, KNativePointerArray elements, KUInt elementsSequenceLength, KBoolean trailingComma)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _nodeType = static_cast<Es2pandaAstNodeType>(nodeType);
    const auto _elements = reinterpret_cast<es2panda_AstNode**>(elements);
    const auto _elementsSequenceLength = static_cast<KUInt>(elementsSequenceLength);
    const auto _trailingComma = static_cast<KBoolean>(trailingComma);
    auto result = GetImpl()->UpdateArrayExpression1(_context, _original, _nodeType, _elements, _elementsSequenceLength, _trailingComma);
    return result;
}
KOALA_INTEROP_6(UpdateArrayExpression1, KNativePointer, KNativePointer, KNativePointer, KInt, KNativePointerArray, KUInt, KBoolean);

KNativePointer impl_ArrayExpressionGetElementNodeAtIdxConst(KNativePointer context, KNativePointer receiver, KUInt idx)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _idx = static_cast<KUInt>(idx);
    auto result = GetImpl()->ArrayExpressionGetElementNodeAtIdxConst(_context, _receiver, _idx);
    return (void*)result;
}
KOALA_INTEROP_3(ArrayExpressionGetElementNodeAtIdxConst, KNativePointer, KNativePointer, KNativePointer, KUInt);

KNativePointer impl_ArrayExpressionElementsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->ArrayExpressionElementsConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(ArrayExpressionElementsConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ArrayExpressionElements(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->ArrayExpressionElements(_context, _receiver, &length);
    return new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(ArrayExpressionElements, KNativePointer, KNativePointer, KNativePointer);

void impl_ArrayExpressionSetElements(KNativePointer context, KNativePointer receiver, KNativePointerArray elements, KUInt elementsSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _elements = reinterpret_cast<es2panda_AstNode**>(elements);
    const auto _elementsSequenceLength = static_cast<KUInt>(elementsSequenceLength);
    GetImpl()->ArrayExpressionSetElements(_context, _receiver, _elements, _elementsSequenceLength);
    return ;
}
KOALA_INTEROP_V4(ArrayExpressionSetElements, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KBoolean impl_ArrayExpressionIsDeclarationConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ArrayExpressionIsDeclarationConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ArrayExpressionIsDeclarationConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_ArrayExpressionIsOptionalConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ArrayExpressionIsOptionalConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ArrayExpressionIsOptionalConst, KBoolean, KNativePointer, KNativePointer);

void impl_ArrayExpressionSetDeclaration(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    GetImpl()->ArrayExpressionSetDeclaration(_context, _receiver);
    return ;
}
KOALA_INTEROP_V2(ArrayExpressionSetDeclaration, KNativePointer, KNativePointer);

void impl_ArrayExpressionSetOptional(KNativePointer context, KNativePointer receiver, KBoolean optional_arg)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _optional_arg = static_cast<KBoolean>(optional_arg);
    GetImpl()->ArrayExpressionSetOptional(_context, _receiver, _optional_arg);
    return ;
}
KOALA_INTEROP_V3(ArrayExpressionSetOptional, KNativePointer, KNativePointer, KBoolean);

KNativePointer impl_ArrayExpressionDecoratorsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->ArrayExpressionDecoratorsConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(ArrayExpressionDecoratorsConst, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_ArrayExpressionConvertibleToArrayPattern(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ArrayExpressionConvertibleToArrayPattern(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ArrayExpressionConvertibleToArrayPattern, KBoolean, KNativePointer, KNativePointer);

KNativePointer impl_ArrayExpressionValidateExpression(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ArrayExpressionValidateExpression(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ArrayExpressionValidateExpression, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_ArrayExpressionTrySetPreferredTypeForNestedArrayExprConst(KNativePointer context, KNativePointer receiver, KNativePointer nestedArrayExpr, KUInt idx)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _nestedArrayExpr = reinterpret_cast<es2panda_AstNode*>(nestedArrayExpr);
    const auto _idx = static_cast<KUInt>(idx);
    auto result = GetImpl()->ArrayExpressionTrySetPreferredTypeForNestedArrayExprConst(_context, _receiver, _nestedArrayExpr, _idx);
    return result;
}
KOALA_INTEROP_4(ArrayExpressionTrySetPreferredTypeForNestedArrayExprConst, KBoolean, KNativePointer, KNativePointer, KNativePointer, KUInt);

KNativePointer impl_ArrayExpressionTypeAnnotationConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ArrayExpressionTypeAnnotationConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ArrayExpressionTypeAnnotationConst, KNativePointer, KNativePointer, KNativePointer);

void impl_ArrayExpressionSetTsTypeAnnotation(KNativePointer context, KNativePointer receiver, KNativePointer typeAnnotation)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _typeAnnotation = reinterpret_cast<es2panda_AstNode*>(typeAnnotation);
    GetImpl()->ArrayExpressionSetTsTypeAnnotation(_context, _receiver, _typeAnnotation);
    return ;
}
KOALA_INTEROP_V3(ArrayExpressionSetTsTypeAnnotation, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSInterfaceBody(KNativePointer context, KNativePointerArray body, KUInt bodySequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _body = reinterpret_cast<es2panda_AstNode**>(body);
    const auto _bodySequenceLength = static_cast<KUInt>(bodySequenceLength);
    auto result = GetImpl()->CreateTSInterfaceBody(_context, _body, _bodySequenceLength);
    return result;
}
KOALA_INTEROP_3(CreateTSInterfaceBody, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_UpdateTSInterfaceBody(KNativePointer context, KNativePointer original, KNativePointerArray body, KUInt bodySequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _body = reinterpret_cast<es2panda_AstNode**>(body);
    const auto _bodySequenceLength = static_cast<KUInt>(bodySequenceLength);
    auto result = GetImpl()->UpdateTSInterfaceBody(_context, _original, _body, _bodySequenceLength);
    return result;
}
KOALA_INTEROP_4(UpdateTSInterfaceBody, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_TSInterfaceBodyBodyPtr(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->TSInterfaceBodyBodyPtr(_context, _receiver, &length);
    return new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(TSInterfaceBodyBodyPtr, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSInterfaceBodyBody(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->TSInterfaceBodyBody(_context, _receiver, &length);
    return new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(TSInterfaceBodyBody, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSInterfaceBodyBodyConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->TSInterfaceBodyBodyConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(TSInterfaceBodyBodyConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSTypeQuery(KNativePointer context, KNativePointer exprName)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _exprName = reinterpret_cast<es2panda_AstNode*>(exprName);
    auto result = GetImpl()->CreateTSTypeQuery(_context, _exprName);
    return result;
}
KOALA_INTEROP_2(CreateTSTypeQuery, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateTSTypeQuery(KNativePointer context, KNativePointer original, KNativePointer exprName)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _exprName = reinterpret_cast<es2panda_AstNode*>(exprName);
    auto result = GetImpl()->UpdateTSTypeQuery(_context, _original, _exprName);
    return result;
}
KOALA_INTEROP_3(UpdateTSTypeQuery, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSTypeQueryExprNameConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSTypeQueryExprNameConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSTypeQueryExprNameConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSBigintKeyword(KNativePointer context)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    auto result = GetImpl()->CreateTSBigintKeyword(_context);
    return result;
}
KOALA_INTEROP_1(CreateTSBigintKeyword, KNativePointer, KNativePointer);

KNativePointer impl_UpdateTSBigintKeyword(KNativePointer context, KNativePointer original)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    auto result = GetImpl()->UpdateTSBigintKeyword(_context, _original);
    return result;
}
KOALA_INTEROP_2(UpdateTSBigintKeyword, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateProperty(KNativePointer context, KNativePointer key, KNativePointer value)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _key = reinterpret_cast<es2panda_AstNode*>(key);
    const auto _value = reinterpret_cast<es2panda_AstNode*>(value);
    auto result = GetImpl()->CreateProperty(_context, _key, _value);
    return result;
}
KOALA_INTEROP_3(CreateProperty, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateProperty(KNativePointer context, KNativePointer original, KNativePointer key, KNativePointer value)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _key = reinterpret_cast<es2panda_AstNode*>(key);
    const auto _value = reinterpret_cast<es2panda_AstNode*>(value);
    auto result = GetImpl()->UpdateProperty(_context, _original, _key, _value);
    return result;
}
KOALA_INTEROP_4(UpdateProperty, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateProperty1(KNativePointer context, KInt kind, KNativePointer key, KNativePointer value, KBoolean isMethod, KBoolean isComputed)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _kind = static_cast<Es2pandaPropertyKind>(kind);
    const auto _key = reinterpret_cast<es2panda_AstNode*>(key);
    const auto _value = reinterpret_cast<es2panda_AstNode*>(value);
    const auto _isMethod = static_cast<KBoolean>(isMethod);
    const auto _isComputed = static_cast<KBoolean>(isComputed);
    auto result = GetImpl()->CreateProperty1(_context, _kind, _key, _value, _isMethod, _isComputed);
    return result;
}
KOALA_INTEROP_6(CreateProperty1, KNativePointer, KNativePointer, KInt, KNativePointer, KNativePointer, KBoolean, KBoolean);

KNativePointer impl_UpdateProperty1(KNativePointer context, KNativePointer original, KInt kind, KNativePointer key, KNativePointer value, KBoolean isMethod, KBoolean isComputed)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _kind = static_cast<Es2pandaPropertyKind>(kind);
    const auto _key = reinterpret_cast<es2panda_AstNode*>(key);
    const auto _value = reinterpret_cast<es2panda_AstNode*>(value);
    const auto _isMethod = static_cast<KBoolean>(isMethod);
    const auto _isComputed = static_cast<KBoolean>(isComputed);
    auto result = GetImpl()->UpdateProperty1(_context, _original, _kind, _key, _value, _isMethod, _isComputed);
    return result;
}
KOALA_INTEROP_7(UpdateProperty1, KNativePointer, KNativePointer, KNativePointer, KInt, KNativePointer, KNativePointer, KBoolean, KBoolean);

KNativePointer impl_PropertyKey(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->PropertyKey(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(PropertyKey, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_PropertyKeyConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->PropertyKeyConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(PropertyKeyConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_PropertyValueConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->PropertyValueConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(PropertyValueConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_PropertyValue(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->PropertyValue(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(PropertyValue, KNativePointer, KNativePointer, KNativePointer);

KInt impl_PropertyKindConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->PropertyKindConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(PropertyKindConst, KInt, KNativePointer, KNativePointer);

KBoolean impl_PropertyIsMethodConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->PropertyIsMethodConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(PropertyIsMethodConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_PropertyIsShorthandConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->PropertyIsShorthandConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(PropertyIsShorthandConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_PropertyIsComputedConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->PropertyIsComputedConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(PropertyIsComputedConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_PropertyIsAccessorConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->PropertyIsAccessorConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(PropertyIsAccessorConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_PropertyIsAccessorKind(KNativePointer context, KNativePointer receiver, KInt kind)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _kind = static_cast<Es2pandaPropertyKind>(kind);
    auto result = GetImpl()->PropertyIsAccessorKind(_context, _receiver, _kind);
    return result;
}
KOALA_INTEROP_3(PropertyIsAccessorKind, KBoolean, KNativePointer, KNativePointer, KInt);

KBoolean impl_PropertyConvertibleToPatternProperty(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->PropertyConvertibleToPatternProperty(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(PropertyConvertibleToPatternProperty, KBoolean, KNativePointer, KNativePointer);

KNativePointer impl_PropertyValidateExpression(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->PropertyValidateExpression(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(PropertyValidateExpression, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateVariableDeclarator(KNativePointer context, KInt flag, KNativePointer ident)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _flag = static_cast<Es2pandaVariableDeclaratorFlag>(flag);
    const auto _ident = reinterpret_cast<es2panda_AstNode*>(ident);
    auto result = GetImpl()->CreateVariableDeclarator(_context, _flag, _ident);
    return result;
}
KOALA_INTEROP_3(CreateVariableDeclarator, KNativePointer, KNativePointer, KInt, KNativePointer);

KNativePointer impl_UpdateVariableDeclarator(KNativePointer context, KNativePointer original, KInt flag, KNativePointer ident)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _flag = static_cast<Es2pandaVariableDeclaratorFlag>(flag);
    const auto _ident = reinterpret_cast<es2panda_AstNode*>(ident);
    auto result = GetImpl()->UpdateVariableDeclarator(_context, _original, _flag, _ident);
    return result;
}
KOALA_INTEROP_4(UpdateVariableDeclarator, KNativePointer, KNativePointer, KNativePointer, KInt, KNativePointer);

KNativePointer impl_CreateVariableDeclarator1(KNativePointer context, KInt flag, KNativePointer ident, KNativePointer init)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _flag = static_cast<Es2pandaVariableDeclaratorFlag>(flag);
    const auto _ident = reinterpret_cast<es2panda_AstNode*>(ident);
    const auto _init = reinterpret_cast<es2panda_AstNode*>(init);
    auto result = GetImpl()->CreateVariableDeclarator1(_context, _flag, _ident, _init);
    return result;
}
KOALA_INTEROP_4(CreateVariableDeclarator1, KNativePointer, KNativePointer, KInt, KNativePointer, KNativePointer);

KNativePointer impl_UpdateVariableDeclarator1(KNativePointer context, KNativePointer original, KInt flag, KNativePointer ident, KNativePointer init)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _flag = static_cast<Es2pandaVariableDeclaratorFlag>(flag);
    const auto _ident = reinterpret_cast<es2panda_AstNode*>(ident);
    const auto _init = reinterpret_cast<es2panda_AstNode*>(init);
    auto result = GetImpl()->UpdateVariableDeclarator1(_context, _original, _flag, _ident, _init);
    return result;
}
KOALA_INTEROP_5(UpdateVariableDeclarator1, KNativePointer, KNativePointer, KNativePointer, KInt, KNativePointer, KNativePointer);

KNativePointer impl_VariableDeclaratorInit(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->VariableDeclaratorInit(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(VariableDeclaratorInit, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_VariableDeclaratorInitConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->VariableDeclaratorInitConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(VariableDeclaratorInitConst, KNativePointer, KNativePointer, KNativePointer);

void impl_VariableDeclaratorSetInit(KNativePointer context, KNativePointer receiver, KNativePointer init)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _init = reinterpret_cast<es2panda_AstNode*>(init);
    GetImpl()->VariableDeclaratorSetInit(_context, _receiver, _init);
    return ;
}
KOALA_INTEROP_V3(VariableDeclaratorSetInit, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_VariableDeclaratorId(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->VariableDeclaratorId(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(VariableDeclaratorId, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_VariableDeclaratorIdConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->VariableDeclaratorIdConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(VariableDeclaratorIdConst, KNativePointer, KNativePointer, KNativePointer);

KInt impl_VariableDeclaratorFlag(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->VariableDeclaratorFlag(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(VariableDeclaratorFlag, KInt, KNativePointer, KNativePointer);

KNativePointer impl_CreateStringLiteral(KNativePointer context)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    auto result = GetImpl()->CreateStringLiteral(_context);
    return result;
}
KOALA_INTEROP_1(CreateStringLiteral, KNativePointer, KNativePointer);

KNativePointer impl_UpdateStringLiteral(KNativePointer context, KNativePointer original)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    auto result = GetImpl()->UpdateStringLiteral(_context, _original);
    return result;
}
KOALA_INTEROP_2(UpdateStringLiteral, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateStringLiteral1(KNativePointer context, KStringPtr& str)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _str = getStringCopy(str);
    auto result = GetImpl()->CreateStringLiteral1(_context, _str);
    return result;
}
KOALA_INTEROP_2(CreateStringLiteral1, KNativePointer, KNativePointer, KStringPtr);

KNativePointer impl_UpdateStringLiteral1(KNativePointer context, KNativePointer original, KStringPtr& str)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _str = getStringCopy(str);
    auto result = GetImpl()->UpdateStringLiteral1(_context, _original, _str);
    return result;
}
KOALA_INTEROP_3(UpdateStringLiteral1, KNativePointer, KNativePointer, KNativePointer, KStringPtr);

KNativePointer impl_StringLiteralStrConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->StringLiteralStrConst(_context, _receiver);
    return new std::string(result);
}
KOALA_INTEROP_2(StringLiteralStrConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSTypeAssertion(KNativePointer context, KNativePointer typeAnnotation, KNativePointer expression)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _typeAnnotation = reinterpret_cast<es2panda_AstNode*>(typeAnnotation);
    const auto _expression = reinterpret_cast<es2panda_AstNode*>(expression);
    auto result = GetImpl()->CreateTSTypeAssertion(_context, _typeAnnotation, _expression);
    return result;
}
KOALA_INTEROP_3(CreateTSTypeAssertion, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateTSTypeAssertion(KNativePointer context, KNativePointer original, KNativePointer typeAnnotation, KNativePointer expression)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _typeAnnotation = reinterpret_cast<es2panda_AstNode*>(typeAnnotation);
    const auto _expression = reinterpret_cast<es2panda_AstNode*>(expression);
    auto result = GetImpl()->UpdateTSTypeAssertion(_context, _original, _typeAnnotation, _expression);
    return result;
}
KOALA_INTEROP_4(UpdateTSTypeAssertion, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSTypeAssertionGetExpressionConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSTypeAssertionGetExpressionConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSTypeAssertionGetExpressionConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSTypeAssertionTypeAnnotationConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSTypeAssertionTypeAnnotationConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSTypeAssertionTypeAnnotationConst, KNativePointer, KNativePointer, KNativePointer);

void impl_TSTypeAssertionSetTsTypeAnnotation(KNativePointer context, KNativePointer receiver, KNativePointer typeAnnotation)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _typeAnnotation = reinterpret_cast<es2panda_AstNode*>(typeAnnotation);
    GetImpl()->TSTypeAssertionSetTsTypeAnnotation(_context, _receiver, _typeAnnotation);
    return ;
}
KOALA_INTEROP_V3(TSTypeAssertionSetTsTypeAnnotation, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSExternalModuleReference(KNativePointer context, KNativePointer expr)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _expr = reinterpret_cast<es2panda_AstNode*>(expr);
    auto result = GetImpl()->CreateTSExternalModuleReference(_context, _expr);
    return result;
}
KOALA_INTEROP_2(CreateTSExternalModuleReference, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateTSExternalModuleReference(KNativePointer context, KNativePointer original, KNativePointer expr)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _expr = reinterpret_cast<es2panda_AstNode*>(expr);
    auto result = GetImpl()->UpdateTSExternalModuleReference(_context, _original, _expr);
    return result;
}
KOALA_INTEROP_3(UpdateTSExternalModuleReference, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSExternalModuleReferenceExprConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSExternalModuleReferenceExprConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSExternalModuleReferenceExprConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSUndefinedKeyword(KNativePointer context)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    auto result = GetImpl()->CreateTSUndefinedKeyword(_context);
    return result;
}
KOALA_INTEROP_1(CreateTSUndefinedKeyword, KNativePointer, KNativePointer);

KNativePointer impl_UpdateTSUndefinedKeyword(KNativePointer context, KNativePointer original)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    auto result = GetImpl()->UpdateTSUndefinedKeyword(_context, _original);
    return result;
}
KOALA_INTEROP_2(UpdateTSUndefinedKeyword, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateETSTuple(KNativePointer context)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    auto result = GetImpl()->CreateETSTuple(_context);
    return result;
}
KOALA_INTEROP_1(CreateETSTuple, KNativePointer, KNativePointer);

KNativePointer impl_UpdateETSTuple(KNativePointer context, KNativePointer original)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    auto result = GetImpl()->UpdateETSTuple(_context, _original);
    return result;
}
KOALA_INTEROP_2(UpdateETSTuple, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateETSTuple1(KNativePointer context, KUInt size)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _size = static_cast<KUInt>(size);
    auto result = GetImpl()->CreateETSTuple1(_context, _size);
    return result;
}
KOALA_INTEROP_2(CreateETSTuple1, KNativePointer, KNativePointer, KUInt);

KNativePointer impl_UpdateETSTuple1(KNativePointer context, KNativePointer original, KUInt size)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _size = static_cast<KUInt>(size);
    auto result = GetImpl()->UpdateETSTuple1(_context, _original, _size);
    return result;
}
KOALA_INTEROP_3(UpdateETSTuple1, KNativePointer, KNativePointer, KNativePointer, KUInt);

KNativePointer impl_CreateETSTuple2(KNativePointer context, KNativePointerArray typeList, KUInt typeListSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _typeList = reinterpret_cast<es2panda_AstNode**>(typeList);
    const auto _typeListSequenceLength = static_cast<KUInt>(typeListSequenceLength);
    auto result = GetImpl()->CreateETSTuple2(_context, _typeList, _typeListSequenceLength);
    return result;
}
KOALA_INTEROP_3(CreateETSTuple2, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_UpdateETSTuple2(KNativePointer context, KNativePointer original, KNativePointerArray typeList, KUInt typeListSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _typeList = reinterpret_cast<es2panda_AstNode**>(typeList);
    const auto _typeListSequenceLength = static_cast<KUInt>(typeListSequenceLength);
    auto result = GetImpl()->UpdateETSTuple2(_context, _original, _typeList, _typeListSequenceLength);
    return result;
}
KOALA_INTEROP_4(UpdateETSTuple2, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KUInt impl_ETSTupleGetTupleSizeConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSTupleGetTupleSizeConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ETSTupleGetTupleSizeConst, KUInt, KNativePointer, KNativePointer);

KNativePointer impl_ETSTupleGetTupleTypeAnnotationsListConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->ETSTupleGetTupleTypeAnnotationsListConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(ETSTupleGetTupleTypeAnnotationsListConst, KNativePointer, KNativePointer, KNativePointer);

void impl_ETSTupleSetTypeAnnotationsList(KNativePointer context, KNativePointer receiver, KNativePointerArray typeNodeList, KUInt typeNodeListSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _typeNodeList = reinterpret_cast<es2panda_AstNode**>(typeNodeList);
    const auto _typeNodeListSequenceLength = static_cast<KUInt>(typeNodeListSequenceLength);
    GetImpl()->ETSTupleSetTypeAnnotationsList(_context, _receiver, _typeNodeList, _typeNodeListSequenceLength);
    return ;
}
KOALA_INTEROP_V4(ETSTupleSetTypeAnnotationsList, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_TryStatementFinallyBlockConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TryStatementFinallyBlockConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TryStatementFinallyBlockConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TryStatementBlockConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TryStatementBlockConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TryStatementBlockConst, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_TryStatementHasFinalizerConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TryStatementHasFinalizerConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TryStatementHasFinalizerConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_TryStatementHasDefaultCatchClauseConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TryStatementHasDefaultCatchClauseConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TryStatementHasDefaultCatchClauseConst, KBoolean, KNativePointer, KNativePointer);

KNativePointer impl_TryStatementCatchClausesConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->TryStatementCatchClausesConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(TryStatementCatchClausesConst, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_TryStatementFinallyCanCompleteNormallyConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TryStatementFinallyCanCompleteNormallyConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TryStatementFinallyCanCompleteNormallyConst, KBoolean, KNativePointer, KNativePointer);

void impl_TryStatementSetFinallyCanCompleteNormally(KNativePointer context, KNativePointer receiver, KBoolean finallyCanCompleteNormally)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _finallyCanCompleteNormally = static_cast<KBoolean>(finallyCanCompleteNormally);
    GetImpl()->TryStatementSetFinallyCanCompleteNormally(_context, _receiver, _finallyCanCompleteNormally);
    return ;
}
KOALA_INTEROP_V3(TryStatementSetFinallyCanCompleteNormally, KNativePointer, KNativePointer, KBoolean);

KBoolean impl_AstNodeIsProgramConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeIsProgramConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AstNodeIsProgramConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_AstNodeIsStatementConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeIsStatementConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AstNodeIsStatementConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_AstNodeIsExpressionConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeIsExpressionConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AstNodeIsExpressionConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_AstNodeIsTypedConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeIsTypedConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AstNodeIsTypedConst, KBoolean, KNativePointer, KNativePointer);

KNativePointer impl_AstNodeAsTyped(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeAsTyped(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AstNodeAsTyped, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_AstNodeAsTypedConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeAsTypedConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(AstNodeAsTypedConst, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_AstNodeIsBrokenStatementConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeIsBrokenStatementConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AstNodeIsBrokenStatementConst, KBoolean, KNativePointer, KNativePointer);

KNativePointer impl_AstNodeAsExpression(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeAsExpression(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AstNodeAsExpression, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_AstNodeAsExpressionConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeAsExpressionConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(AstNodeAsExpressionConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_AstNodeAsStatement(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeAsStatement(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AstNodeAsStatement, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_AstNodeAsStatementConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeAsStatementConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(AstNodeAsStatementConst, KNativePointer, KNativePointer, KNativePointer);

KInt impl_AstNodeTypeConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeTypeConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AstNodeTypeConst, KInt, KNativePointer, KNativePointer);

KNativePointer impl_AstNodeParent(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeParent(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AstNodeParent, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_AstNodeParentConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeParentConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(AstNodeParentConst, KNativePointer, KNativePointer, KNativePointer);

void impl_AstNodeSetParent(KNativePointer context, KNativePointer receiver, KNativePointer parent)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _parent = reinterpret_cast<es2panda_AstNode*>(parent);
    GetImpl()->AstNodeSetParent(_context, _receiver, _parent);
    return ;
}
KOALA_INTEROP_V3(AstNodeSetParent, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_AstNodeDecoratorsPtrConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->AstNodeDecoratorsPtrConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(AstNodeDecoratorsPtrConst, KNativePointer, KNativePointer, KNativePointer);

void impl_AstNodeAddDecorators(KNativePointer context, KNativePointer receiver, KNativePointerArray decorators, KUInt decoratorsSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _decorators = reinterpret_cast<es2panda_AstNode**>(decorators);
    const auto _decoratorsSequenceLength = static_cast<KUInt>(decoratorsSequenceLength);
    GetImpl()->AstNodeAddDecorators(_context, _receiver, _decorators, _decoratorsSequenceLength);
    return ;
}
KOALA_INTEROP_V4(AstNodeAddDecorators, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KBoolean impl_AstNodeCanHaveDecoratorConst(KNativePointer context, KNativePointer receiver, KBoolean inTs)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _inTs = static_cast<KBoolean>(inTs);
    auto result = GetImpl()->AstNodeCanHaveDecoratorConst(_context, _receiver, _inTs);
    return result;
}
KOALA_INTEROP_3(AstNodeCanHaveDecoratorConst, KBoolean, KNativePointer, KNativePointer, KBoolean);

KBoolean impl_AstNodeIsReadonlyConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeIsReadonlyConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AstNodeIsReadonlyConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_AstNodeIsReadonlyTypeConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeIsReadonlyTypeConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AstNodeIsReadonlyTypeConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_AstNodeIsOptionalDeclarationConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeIsOptionalDeclarationConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AstNodeIsOptionalDeclarationConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_AstNodeIsDefiniteConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeIsDefiniteConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AstNodeIsDefiniteConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_AstNodeIsConstructorConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeIsConstructorConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AstNodeIsConstructorConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_AstNodeIsOverrideConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeIsOverrideConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AstNodeIsOverrideConst, KBoolean, KNativePointer, KNativePointer);

void impl_AstNodeSetOverride(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    GetImpl()->AstNodeSetOverride(_context, _receiver);
    return ;
}
KOALA_INTEROP_V2(AstNodeSetOverride, KNativePointer, KNativePointer);

KBoolean impl_AstNodeIsAsyncConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeIsAsyncConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AstNodeIsAsyncConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_AstNodeIsSynchronizedConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeIsSynchronizedConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AstNodeIsSynchronizedConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_AstNodeIsNativeConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeIsNativeConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AstNodeIsNativeConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_AstNodeIsConstConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeIsConstConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AstNodeIsConstConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_AstNodeIsStaticConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeIsStaticConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AstNodeIsStaticConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_AstNodeIsFinalConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeIsFinalConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AstNodeIsFinalConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_AstNodeIsAbstractConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeIsAbstractConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AstNodeIsAbstractConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_AstNodeIsPublicConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeIsPublicConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AstNodeIsPublicConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_AstNodeIsProtectedConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeIsProtectedConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AstNodeIsProtectedConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_AstNodeIsPrivateConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeIsPrivateConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AstNodeIsPrivateConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_AstNodeIsInternalConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeIsInternalConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AstNodeIsInternalConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_AstNodeIsExportedConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeIsExportedConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AstNodeIsExportedConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_AstNodeIsDefaultExportedConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeIsDefaultExportedConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AstNodeIsDefaultExportedConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_AstNodeIsExportedTypeConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeIsExportedTypeConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AstNodeIsExportedTypeConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_AstNodeIsDeclareConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeIsDeclareConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AstNodeIsDeclareConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_AstNodeIsInConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeIsInConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AstNodeIsInConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_AstNodeIsOutConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeIsOutConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AstNodeIsOutConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_AstNodeIsSetterConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeIsSetterConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AstNodeIsSetterConst, KBoolean, KNativePointer, KNativePointer);

void impl_AstNodeAddModifier(KNativePointer context, KNativePointer receiver, KInt flags)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _flags = static_cast<Es2pandaModifierFlags>(flags);
    GetImpl()->AstNodeAddModifier(_context, _receiver, _flags);
    return ;
}
KOALA_INTEROP_V3(AstNodeAddModifier, KNativePointer, KNativePointer, KInt);

void impl_AstNodeClearModifier(KNativePointer context, KNativePointer receiver, KInt flags)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _flags = static_cast<Es2pandaModifierFlags>(flags);
    GetImpl()->AstNodeClearModifier(_context, _receiver, _flags);
    return ;
}
KOALA_INTEROP_V3(AstNodeClearModifier, KNativePointer, KNativePointer, KInt);

KInt impl_AstNodeModifiers(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeModifiers(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AstNodeModifiers, KInt, KNativePointer, KNativePointer);

KInt impl_AstNodeModifiersConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeModifiersConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AstNodeModifiersConst, KInt, KNativePointer, KNativePointer);

KBoolean impl_AstNodeHasExportAliasConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeHasExportAliasConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AstNodeHasExportAliasConst, KBoolean, KNativePointer, KNativePointer);

KNativePointer impl_AstNodeAsClassElement(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeAsClassElement(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AstNodeAsClassElement, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_AstNodeAsClassElementConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeAsClassElementConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(AstNodeAsClassElementConst, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_AstNodeIsScopeBearerConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeIsScopeBearerConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AstNodeIsScopeBearerConst, KBoolean, KNativePointer, KNativePointer);

void impl_AstNodeClearScope(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    GetImpl()->AstNodeClearScope(_context, _receiver);
    return ;
}
KOALA_INTEROP_V2(AstNodeClearScope, KNativePointer, KNativePointer);

KNativePointer impl_AstNodeGetTopStatement(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeGetTopStatement(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AstNodeGetTopStatement, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_AstNodeGetTopStatementConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeGetTopStatementConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(AstNodeGetTopStatementConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_AstNodeClone(KNativePointer context, KNativePointer receiver, KNativePointer parent)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _parent = reinterpret_cast<es2panda_AstNode*>(parent);
    auto result = GetImpl()->AstNodeClone(_context, _receiver, _parent);
    return result;
}
KOALA_INTEROP_3(AstNodeClone, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_AstNodeDumpJSONConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeDumpJSONConst(_context, _receiver);
    return new std::string(result);
}
KOALA_INTEROP_2(AstNodeDumpJSONConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_AstNodeDumpEtsSrcConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeDumpEtsSrcConst(_context, _receiver);
    return new std::string(result);
}
KOALA_INTEROP_2(AstNodeDumpEtsSrcConst, KNativePointer, KNativePointer, KNativePointer);

void impl_AstNodeDumpConst(KNativePointer context, KNativePointer receiver, KNativePointer dumper)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _dumper = reinterpret_cast<es2panda_AstDumper*>(dumper);
    GetImpl()->AstNodeDumpConst(_context, _receiver, _dumper);
    return ;
}
KOALA_INTEROP_V3(AstNodeDumpConst, KNativePointer, KNativePointer, KNativePointer);

void impl_AstNodeDumpConst1(KNativePointer context, KNativePointer receiver, KNativePointer dumper)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _dumper = reinterpret_cast<es2panda_SrcDumper*>(dumper);
    GetImpl()->AstNodeDumpConst1(_context, _receiver, _dumper);
    return ;
}
KOALA_INTEROP_V3(AstNodeDumpConst1, KNativePointer, KNativePointer, KNativePointer);

void impl_AstNodeSetTransformedNode(KNativePointer context, KNativePointer receiver, KStringPtr& transformationName, KNativePointer transformedNode)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _transformationName = getStringCopy(transformationName);
    const auto _transformedNode = reinterpret_cast<es2panda_AstNode*>(transformedNode);
    GetImpl()->AstNodeSetTransformedNode(_context, _receiver, _transformationName, _transformedNode);
    return ;
}
KOALA_INTEROP_V4(AstNodeSetTransformedNode, KNativePointer, KNativePointer, KStringPtr, KNativePointer);

void impl_AstNodeSetOriginalNode(KNativePointer context, KNativePointer receiver, KNativePointer originalNode)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _originalNode = reinterpret_cast<es2panda_AstNode*>(originalNode);
    GetImpl()->AstNodeSetOriginalNode(_context, _receiver, _originalNode);
    return ;
}
KOALA_INTEROP_V3(AstNodeSetOriginalNode, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_AstNodeOriginalNodeConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AstNodeOriginalNodeConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(AstNodeOriginalNodeConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateUnaryExpression(KNativePointer context, KNativePointer argument, KInt unaryOperator)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _argument = reinterpret_cast<es2panda_AstNode*>(argument);
    const auto _unaryOperator = static_cast<Es2pandaTokenType>(unaryOperator);
    auto result = GetImpl()->CreateUnaryExpression(_context, _argument, _unaryOperator);
    return result;
}
KOALA_INTEROP_3(CreateUnaryExpression, KNativePointer, KNativePointer, KNativePointer, KInt);

KNativePointer impl_UpdateUnaryExpression(KNativePointer context, KNativePointer original, KNativePointer argument, KInt unaryOperator)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _argument = reinterpret_cast<es2panda_AstNode*>(argument);
    const auto _unaryOperator = static_cast<Es2pandaTokenType>(unaryOperator);
    auto result = GetImpl()->UpdateUnaryExpression(_context, _original, _argument, _unaryOperator);
    return result;
}
KOALA_INTEROP_4(UpdateUnaryExpression, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KInt);

KInt impl_UnaryExpressionOperatorTypeConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->UnaryExpressionOperatorTypeConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(UnaryExpressionOperatorTypeConst, KInt, KNativePointer, KNativePointer);

KNativePointer impl_UnaryExpressionArgument(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->UnaryExpressionArgument(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(UnaryExpressionArgument, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UnaryExpressionArgumentConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->UnaryExpressionArgumentConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(UnaryExpressionArgumentConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateForInStatement(KNativePointer context, KNativePointer left, KNativePointer right, KNativePointer body)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _left = reinterpret_cast<es2panda_AstNode*>(left);
    const auto _right = reinterpret_cast<es2panda_AstNode*>(right);
    const auto _body = reinterpret_cast<es2panda_AstNode*>(body);
    auto result = GetImpl()->CreateForInStatement(_context, _left, _right, _body);
    return result;
}
KOALA_INTEROP_4(CreateForInStatement, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateForInStatement(KNativePointer context, KNativePointer original, KNativePointer left, KNativePointer right, KNativePointer body)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _left = reinterpret_cast<es2panda_AstNode*>(left);
    const auto _right = reinterpret_cast<es2panda_AstNode*>(right);
    const auto _body = reinterpret_cast<es2panda_AstNode*>(body);
    auto result = GetImpl()->UpdateForInStatement(_context, _original, _left, _right, _body);
    return result;
}
KOALA_INTEROP_5(UpdateForInStatement, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ForInStatementLeft(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ForInStatementLeft(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ForInStatementLeft, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ForInStatementLeftConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ForInStatementLeftConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ForInStatementLeftConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ForInStatementRight(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ForInStatementRight(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ForInStatementRight, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ForInStatementRightConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ForInStatementRightConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ForInStatementRightConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ForInStatementBody(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ForInStatementBody(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ForInStatementBody, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ForInStatementBodyConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ForInStatementBodyConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ForInStatementBodyConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateThisExpression(KNativePointer context)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    auto result = GetImpl()->CreateThisExpression(_context);
    return result;
}
KOALA_INTEROP_1(CreateThisExpression, KNativePointer, KNativePointer);

KNativePointer impl_UpdateThisExpression(KNativePointer context, KNativePointer original)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    auto result = GetImpl()->UpdateThisExpression(_context, _original);
    return result;
}
KOALA_INTEROP_2(UpdateThisExpression, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSMethodSignature(KNativePointer context, KNativePointer key, KNativePointer signature, KBoolean computed, KBoolean optional_arg)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _key = reinterpret_cast<es2panda_AstNode*>(key);
    const auto _signature = reinterpret_cast<es2panda_FunctionSignature*>(signature);
    const auto _computed = static_cast<KBoolean>(computed);
    const auto _optional_arg = static_cast<KBoolean>(optional_arg);
    auto result = GetImpl()->CreateTSMethodSignature(_context, _key, _signature, _computed, _optional_arg);
    return result;
}
KOALA_INTEROP_5(CreateTSMethodSignature, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KBoolean, KBoolean);

KNativePointer impl_UpdateTSMethodSignature(KNativePointer context, KNativePointer original, KNativePointer key, KNativePointer signature, KBoolean computed, KBoolean optional_arg)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _key = reinterpret_cast<es2panda_AstNode*>(key);
    const auto _signature = reinterpret_cast<es2panda_FunctionSignature*>(signature);
    const auto _computed = static_cast<KBoolean>(computed);
    const auto _optional_arg = static_cast<KBoolean>(optional_arg);
    auto result = GetImpl()->UpdateTSMethodSignature(_context, _original, _key, _signature, _computed, _optional_arg);
    return result;
}
KOALA_INTEROP_6(UpdateTSMethodSignature, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KBoolean, KBoolean);

KNativePointer impl_TSMethodSignatureKeyConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSMethodSignatureKeyConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSMethodSignatureKeyConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSMethodSignatureKey(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSMethodSignatureKey(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSMethodSignatureKey, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSMethodSignatureTypeParamsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSMethodSignatureTypeParamsConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSMethodSignatureTypeParamsConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSMethodSignatureTypeParams(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSMethodSignatureTypeParams(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSMethodSignatureTypeParams, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSMethodSignatureParamsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->TSMethodSignatureParamsConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(TSMethodSignatureParamsConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSMethodSignatureReturnTypeAnnotationConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSMethodSignatureReturnTypeAnnotationConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSMethodSignatureReturnTypeAnnotationConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSMethodSignatureReturnTypeAnnotation(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSMethodSignatureReturnTypeAnnotation(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSMethodSignatureReturnTypeAnnotation, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_TSMethodSignatureComputedConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSMethodSignatureComputedConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSMethodSignatureComputedConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_TSMethodSignatureOptionalConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSMethodSignatureOptionalConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSMethodSignatureOptionalConst, KBoolean, KNativePointer, KNativePointer);

KNativePointer impl_CreateBinaryExpression(KNativePointer context, KNativePointer left, KNativePointer right, KInt operatorType)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _left = reinterpret_cast<es2panda_AstNode*>(left);
    const auto _right = reinterpret_cast<es2panda_AstNode*>(right);
    const auto _operatorType = static_cast<Es2pandaTokenType>(operatorType);
    auto result = GetImpl()->CreateBinaryExpression(_context, _left, _right, _operatorType);
    return result;
}
KOALA_INTEROP_4(CreateBinaryExpression, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KInt);

KNativePointer impl_UpdateBinaryExpression(KNativePointer context, KNativePointer original, KNativePointer left, KNativePointer right, KInt operatorType)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _left = reinterpret_cast<es2panda_AstNode*>(left);
    const auto _right = reinterpret_cast<es2panda_AstNode*>(right);
    const auto _operatorType = static_cast<Es2pandaTokenType>(operatorType);
    auto result = GetImpl()->UpdateBinaryExpression(_context, _original, _left, _right, _operatorType);
    return result;
}
KOALA_INTEROP_5(UpdateBinaryExpression, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KInt);

KNativePointer impl_BinaryExpressionLeftConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->BinaryExpressionLeftConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(BinaryExpressionLeftConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_BinaryExpressionLeft(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->BinaryExpressionLeft(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(BinaryExpressionLeft, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_BinaryExpressionRightConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->BinaryExpressionRightConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(BinaryExpressionRightConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_BinaryExpressionRight(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->BinaryExpressionRight(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(BinaryExpressionRight, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_BinaryExpressionResultConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->BinaryExpressionResultConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(BinaryExpressionResultConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_BinaryExpressionResult(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->BinaryExpressionResult(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(BinaryExpressionResult, KNativePointer, KNativePointer, KNativePointer);

KInt impl_BinaryExpressionOperatorTypeConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->BinaryExpressionOperatorTypeConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(BinaryExpressionOperatorTypeConst, KInt, KNativePointer, KNativePointer);

KBoolean impl_BinaryExpressionIsLogicalConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->BinaryExpressionIsLogicalConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(BinaryExpressionIsLogicalConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_BinaryExpressionIsLogicalExtendedConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->BinaryExpressionIsLogicalExtendedConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(BinaryExpressionIsLogicalExtendedConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_BinaryExpressionIsBitwiseConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->BinaryExpressionIsBitwiseConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(BinaryExpressionIsBitwiseConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_BinaryExpressionIsArithmeticConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->BinaryExpressionIsArithmeticConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(BinaryExpressionIsArithmeticConst, KBoolean, KNativePointer, KNativePointer);

void impl_BinaryExpressionSetLeft(KNativePointer context, KNativePointer receiver, KNativePointer expr)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _expr = reinterpret_cast<es2panda_AstNode*>(expr);
    GetImpl()->BinaryExpressionSetLeft(_context, _receiver, _expr);
    return ;
}
KOALA_INTEROP_V3(BinaryExpressionSetLeft, KNativePointer, KNativePointer, KNativePointer);

void impl_BinaryExpressionSetRight(KNativePointer context, KNativePointer receiver, KNativePointer expr)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _expr = reinterpret_cast<es2panda_AstNode*>(expr);
    GetImpl()->BinaryExpressionSetRight(_context, _receiver, _expr);
    return ;
}
KOALA_INTEROP_V3(BinaryExpressionSetRight, KNativePointer, KNativePointer, KNativePointer);

void impl_BinaryExpressionSetResult(KNativePointer context, KNativePointer receiver, KNativePointer expr)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _expr = reinterpret_cast<es2panda_AstNode*>(expr);
    GetImpl()->BinaryExpressionSetResult(_context, _receiver, _expr);
    return ;
}
KOALA_INTEROP_V3(BinaryExpressionSetResult, KNativePointer, KNativePointer, KNativePointer);

void impl_BinaryExpressionSetOperator(KNativePointer context, KNativePointer receiver, KInt operatorType)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _operatorType = static_cast<Es2pandaTokenType>(operatorType);
    GetImpl()->BinaryExpressionSetOperator(_context, _receiver, _operatorType);
    return ;
}
KOALA_INTEROP_V3(BinaryExpressionSetOperator, KNativePointer, KNativePointer, KInt);

KNativePointer impl_CreateSuperExpression(KNativePointer context)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    auto result = GetImpl()->CreateSuperExpression(_context);
    return result;
}
KOALA_INTEROP_1(CreateSuperExpression, KNativePointer, KNativePointer);

KNativePointer impl_UpdateSuperExpression(KNativePointer context, KNativePointer original)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    auto result = GetImpl()->UpdateSuperExpression(_context, _original);
    return result;
}
KOALA_INTEROP_2(UpdateSuperExpression, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateAssertStatement(KNativePointer context, KNativePointer test, KNativePointer second)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _test = reinterpret_cast<es2panda_AstNode*>(test);
    const auto _second = reinterpret_cast<es2panda_AstNode*>(second);
    auto result = GetImpl()->CreateAssertStatement(_context, _test, _second);
    return result;
}
KOALA_INTEROP_3(CreateAssertStatement, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateAssertStatement(KNativePointer context, KNativePointer original, KNativePointer test, KNativePointer second)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _test = reinterpret_cast<es2panda_AstNode*>(test);
    const auto _second = reinterpret_cast<es2panda_AstNode*>(second);
    auto result = GetImpl()->UpdateAssertStatement(_context, _original, _test, _second);
    return result;
}
KOALA_INTEROP_4(UpdateAssertStatement, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_AssertStatementTestConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AssertStatementTestConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(AssertStatementTestConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_AssertStatementTest(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AssertStatementTest(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AssertStatementTest, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_AssertStatementSecondConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AssertStatementSecondConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(AssertStatementSecondConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSStringKeyword(KNativePointer context)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    auto result = GetImpl()->CreateTSStringKeyword(_context);
    return result;
}
KOALA_INTEROP_1(CreateTSStringKeyword, KNativePointer, KNativePointer);

KNativePointer impl_UpdateTSStringKeyword(KNativePointer context, KNativePointer original)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    auto result = GetImpl()->UpdateTSStringKeyword(_context, _original);
    return result;
}
KOALA_INTEROP_2(UpdateTSStringKeyword, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateAssignmentExpression(KNativePointer context, KNativePointer left, KNativePointer right, KInt assignmentOperator)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _left = reinterpret_cast<es2panda_AstNode*>(left);
    const auto _right = reinterpret_cast<es2panda_AstNode*>(right);
    const auto _assignmentOperator = static_cast<Es2pandaTokenType>(assignmentOperator);
    auto result = GetImpl()->CreateAssignmentExpression(_context, _left, _right, _assignmentOperator);
    return result;
}
KOALA_INTEROP_4(CreateAssignmentExpression, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KInt);

KNativePointer impl_UpdateAssignmentExpression(KNativePointer context, KNativePointer original, KNativePointer left, KNativePointer right, KInt assignmentOperator)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _left = reinterpret_cast<es2panda_AstNode*>(left);
    const auto _right = reinterpret_cast<es2panda_AstNode*>(right);
    const auto _assignmentOperator = static_cast<Es2pandaTokenType>(assignmentOperator);
    auto result = GetImpl()->UpdateAssignmentExpression(_context, _original, _left, _right, _assignmentOperator);
    return result;
}
KOALA_INTEROP_5(UpdateAssignmentExpression, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KInt);

KNativePointer impl_CreateAssignmentExpression1(KNativePointer context, KInt type, KNativePointer left, KNativePointer right, KInt assignmentOperator)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _type = static_cast<Es2pandaAstNodeType>(type);
    const auto _left = reinterpret_cast<es2panda_AstNode*>(left);
    const auto _right = reinterpret_cast<es2panda_AstNode*>(right);
    const auto _assignmentOperator = static_cast<Es2pandaTokenType>(assignmentOperator);
    auto result = GetImpl()->CreateAssignmentExpression1(_context, _type, _left, _right, _assignmentOperator);
    return result;
}
KOALA_INTEROP_5(CreateAssignmentExpression1, KNativePointer, KNativePointer, KInt, KNativePointer, KNativePointer, KInt);

KNativePointer impl_UpdateAssignmentExpression1(KNativePointer context, KNativePointer original, KInt type, KNativePointer left, KNativePointer right, KInt assignmentOperator)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _type = static_cast<Es2pandaAstNodeType>(type);
    const auto _left = reinterpret_cast<es2panda_AstNode*>(left);
    const auto _right = reinterpret_cast<es2panda_AstNode*>(right);
    const auto _assignmentOperator = static_cast<Es2pandaTokenType>(assignmentOperator);
    auto result = GetImpl()->UpdateAssignmentExpression1(_context, _original, _type, _left, _right, _assignmentOperator);
    return result;
}
KOALA_INTEROP_6(UpdateAssignmentExpression1, KNativePointer, KNativePointer, KNativePointer, KInt, KNativePointer, KNativePointer, KInt);

KNativePointer impl_AssignmentExpressionLeftConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AssignmentExpressionLeftConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(AssignmentExpressionLeftConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_AssignmentExpressionLeft(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AssignmentExpressionLeft(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AssignmentExpressionLeft, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_AssignmentExpressionRight(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AssignmentExpressionRight(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AssignmentExpressionRight, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_AssignmentExpressionRightConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AssignmentExpressionRightConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(AssignmentExpressionRightConst, KNativePointer, KNativePointer, KNativePointer);

void impl_AssignmentExpressionSetRight(KNativePointer context, KNativePointer receiver, KNativePointer expr)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _expr = reinterpret_cast<es2panda_AstNode*>(expr);
    GetImpl()->AssignmentExpressionSetRight(_context, _receiver, _expr);
    return ;
}
KOALA_INTEROP_V3(AssignmentExpressionSetRight, KNativePointer, KNativePointer, KNativePointer);

void impl_AssignmentExpressionSetLeft(KNativePointer context, KNativePointer receiver, KNativePointer expr)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _expr = reinterpret_cast<es2panda_AstNode*>(expr);
    GetImpl()->AssignmentExpressionSetLeft(_context, _receiver, _expr);
    return ;
}
KOALA_INTEROP_V3(AssignmentExpressionSetLeft, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_AssignmentExpressionResultConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AssignmentExpressionResultConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(AssignmentExpressionResultConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_AssignmentExpressionResult(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AssignmentExpressionResult(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AssignmentExpressionResult, KNativePointer, KNativePointer, KNativePointer);

KInt impl_AssignmentExpressionOperatorTypeConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AssignmentExpressionOperatorTypeConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AssignmentExpressionOperatorTypeConst, KInt, KNativePointer, KNativePointer);

KInt impl_AssignmentExpressionSetOperatorType(KNativePointer context, KNativePointer receiver, KInt tokenType)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _tokenType = static_cast<Es2pandaTokenType>(tokenType);
    auto result = GetImpl()->AssignmentExpressionSetOperatorType(_context, _receiver, _tokenType);
    return result;
}
KOALA_INTEROP_3(AssignmentExpressionSetOperatorType, KInt, KNativePointer, KNativePointer, KInt);

void impl_AssignmentExpressionSetResult(KNativePointer context, KNativePointer receiver, KNativePointer expr)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _expr = reinterpret_cast<es2panda_AstNode*>(expr);
    GetImpl()->AssignmentExpressionSetResult(_context, _receiver, _expr);
    return ;
}
KOALA_INTEROP_V3(AssignmentExpressionSetResult, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_AssignmentExpressionIsLogicalExtendedConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AssignmentExpressionIsLogicalExtendedConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AssignmentExpressionIsLogicalExtendedConst, KBoolean, KNativePointer, KNativePointer);

void impl_AssignmentExpressionSetIgnoreConstAssign(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    GetImpl()->AssignmentExpressionSetIgnoreConstAssign(_context, _receiver);
    return ;
}
KOALA_INTEROP_V2(AssignmentExpressionSetIgnoreConstAssign, KNativePointer, KNativePointer);

KBoolean impl_AssignmentExpressionIsIgnoreConstAssignConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AssignmentExpressionIsIgnoreConstAssignConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AssignmentExpressionIsIgnoreConstAssignConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_AssignmentExpressionConvertibleToAssignmentPatternLeft(KNativePointer context, KNativePointer receiver, KBoolean mustBePattern)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _mustBePattern = static_cast<KBoolean>(mustBePattern);
    auto result = GetImpl()->AssignmentExpressionConvertibleToAssignmentPatternLeft(_context, _receiver, _mustBePattern);
    return result;
}
KOALA_INTEROP_3(AssignmentExpressionConvertibleToAssignmentPatternLeft, KBoolean, KNativePointer, KNativePointer, KBoolean);

KBoolean impl_AssignmentExpressionConvertibleToAssignmentPatternRight(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AssignmentExpressionConvertibleToAssignmentPatternRight(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AssignmentExpressionConvertibleToAssignmentPatternRight, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_AssignmentExpressionConvertibleToAssignmentPattern(KNativePointer context, KNativePointer receiver, KBoolean mustBePattern)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _mustBePattern = static_cast<KBoolean>(mustBePattern);
    auto result = GetImpl()->AssignmentExpressionConvertibleToAssignmentPattern(_context, _receiver, _mustBePattern);
    return result;
}
KOALA_INTEROP_3(AssignmentExpressionConvertibleToAssignmentPattern, KBoolean, KNativePointer, KNativePointer, KBoolean);

KNativePointer impl_CreateExpressionStatement(KNativePointer context, KNativePointer expr)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _expr = reinterpret_cast<es2panda_AstNode*>(expr);
    auto result = GetImpl()->CreateExpressionStatement(_context, _expr);
    return result;
}
KOALA_INTEROP_2(CreateExpressionStatement, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateExpressionStatement(KNativePointer context, KNativePointer original, KNativePointer expr)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _expr = reinterpret_cast<es2panda_AstNode*>(expr);
    auto result = GetImpl()->UpdateExpressionStatement(_context, _original, _expr);
    return result;
}
KOALA_INTEROP_3(UpdateExpressionStatement, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ExpressionStatementGetExpressionConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ExpressionStatementGetExpressionConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ExpressionStatementGetExpressionConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ExpressionStatementGetExpression(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ExpressionStatementGetExpression(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ExpressionStatementGetExpression, KNativePointer, KNativePointer, KNativePointer);

void impl_ExpressionStatementSetExpression(KNativePointer context, KNativePointer receiver, KNativePointer expr)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _expr = reinterpret_cast<es2panda_AstNode*>(expr);
    GetImpl()->ExpressionStatementSetExpression(_context, _receiver, _expr);
    return ;
}
KOALA_INTEROP_V3(ExpressionStatementSetExpression, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ETSModuleIdent(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSModuleIdent(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ETSModuleIdent, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ETSModuleIdentConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSModuleIdentConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ETSModuleIdentConst, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_ETSModuleIsETSScriptConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSModuleIsETSScriptConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ETSModuleIsETSScriptConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_ETSModuleIsNamespaceConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSModuleIsNamespaceConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ETSModuleIsNamespaceConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_ETSModuleIsNamespaceChainLastNodeConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSModuleIsNamespaceChainLastNodeConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ETSModuleIsNamespaceChainLastNodeConst, KBoolean, KNativePointer, KNativePointer);

void impl_ETSModuleSetNamespaceChainLastNode(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    GetImpl()->ETSModuleSetNamespaceChainLastNode(_context, _receiver);
    return ;
}
KOALA_INTEROP_V2(ETSModuleSetNamespaceChainLastNode, KNativePointer, KNativePointer);

KNativePointer impl_ETSModuleAnnotations(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->ETSModuleAnnotations(_context, _receiver, &length);
    return new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(ETSModuleAnnotations, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ETSModuleAnnotationsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->ETSModuleAnnotationsConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(ETSModuleAnnotationsConst, KNativePointer, KNativePointer, KNativePointer);

void impl_ETSModuleSetAnnotations(KNativePointer context, KNativePointer receiver, KNativePointerArray annotations, KUInt annotationsSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _annotations = reinterpret_cast<es2panda_AstNode**>(annotations);
    const auto _annotationsSequenceLength = static_cast<KUInt>(annotationsSequenceLength);
    GetImpl()->ETSModuleSetAnnotations(_context, _receiver, _annotations, _annotationsSequenceLength);
    return ;
}
KOALA_INTEROP_V4(ETSModuleSetAnnotations, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_CreateMetaProperty(KNativePointer context, KInt kind)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _kind = static_cast<Es2pandaMetaPropertyKind>(kind);
    auto result = GetImpl()->CreateMetaProperty(_context, _kind);
    return result;
}
KOALA_INTEROP_2(CreateMetaProperty, KNativePointer, KNativePointer, KInt);

KNativePointer impl_UpdateMetaProperty(KNativePointer context, KNativePointer original, KInt kind)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _kind = static_cast<Es2pandaMetaPropertyKind>(kind);
    auto result = GetImpl()->UpdateMetaProperty(_context, _original, _kind);
    return result;
}
KOALA_INTEROP_3(UpdateMetaProperty, KNativePointer, KNativePointer, KNativePointer, KInt);

KInt impl_MetaPropertyKindConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->MetaPropertyKindConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(MetaPropertyKindConst, KInt, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSArrayType(KNativePointer context, KNativePointer elementType)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _elementType = reinterpret_cast<es2panda_AstNode*>(elementType);
    auto result = GetImpl()->CreateTSArrayType(_context, _elementType);
    return result;
}
KOALA_INTEROP_2(CreateTSArrayType, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateTSArrayType(KNativePointer context, KNativePointer original, KNativePointer elementType)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _elementType = reinterpret_cast<es2panda_AstNode*>(elementType);
    auto result = GetImpl()->UpdateTSArrayType(_context, _original, _elementType);
    return result;
}
KOALA_INTEROP_3(UpdateTSArrayType, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSArrayTypeElementTypeConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSArrayTypeElementTypeConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSArrayTypeElementTypeConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSSignatureDeclaration(KNativePointer context, KInt kind, KNativePointer signature)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _kind = static_cast<Es2pandaTSSignatureDeclarationKind>(kind);
    const auto _signature = reinterpret_cast<es2panda_FunctionSignature*>(signature);
    auto result = GetImpl()->CreateTSSignatureDeclaration(_context, _kind, _signature);
    return result;
}
KOALA_INTEROP_3(CreateTSSignatureDeclaration, KNativePointer, KNativePointer, KInt, KNativePointer);

KNativePointer impl_UpdateTSSignatureDeclaration(KNativePointer context, KNativePointer original, KInt kind, KNativePointer signature)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _kind = static_cast<Es2pandaTSSignatureDeclarationKind>(kind);
    const auto _signature = reinterpret_cast<es2panda_FunctionSignature*>(signature);
    auto result = GetImpl()->UpdateTSSignatureDeclaration(_context, _original, _kind, _signature);
    return result;
}
KOALA_INTEROP_4(UpdateTSSignatureDeclaration, KNativePointer, KNativePointer, KNativePointer, KInt, KNativePointer);

KNativePointer impl_TSSignatureDeclarationTypeParamsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSSignatureDeclarationTypeParamsConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSSignatureDeclarationTypeParamsConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSSignatureDeclarationTypeParams(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSSignatureDeclarationTypeParams(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSSignatureDeclarationTypeParams, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSSignatureDeclarationParamsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->TSSignatureDeclarationParamsConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(TSSignatureDeclarationParamsConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSSignatureDeclarationReturnTypeAnnotationConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSSignatureDeclarationReturnTypeAnnotationConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSSignatureDeclarationReturnTypeAnnotationConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSSignatureDeclarationReturnTypeAnnotation(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSSignatureDeclarationReturnTypeAnnotation(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSSignatureDeclarationReturnTypeAnnotation, KNativePointer, KNativePointer, KNativePointer);

KInt impl_TSSignatureDeclarationKindConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSSignatureDeclarationKindConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSSignatureDeclarationKindConst, KInt, KNativePointer, KNativePointer);

KNativePointer impl_CreateExportAllDeclaration(KNativePointer context, KNativePointer source, KNativePointer exported)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _source = reinterpret_cast<es2panda_AstNode*>(source);
    const auto _exported = reinterpret_cast<es2panda_AstNode*>(exported);
    auto result = GetImpl()->CreateExportAllDeclaration(_context, _source, _exported);
    return result;
}
KOALA_INTEROP_3(CreateExportAllDeclaration, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateExportAllDeclaration(KNativePointer context, KNativePointer original, KNativePointer source, KNativePointer exported)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _source = reinterpret_cast<es2panda_AstNode*>(source);
    const auto _exported = reinterpret_cast<es2panda_AstNode*>(exported);
    auto result = GetImpl()->UpdateExportAllDeclaration(_context, _original, _source, _exported);
    return result;
}
KOALA_INTEROP_4(UpdateExportAllDeclaration, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ExportAllDeclarationSourceConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ExportAllDeclarationSourceConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ExportAllDeclarationSourceConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ExportAllDeclarationExportedConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ExportAllDeclarationExportedConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ExportAllDeclarationExportedConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateExportSpecifier(KNativePointer context, KNativePointer local, KNativePointer exported)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _local = reinterpret_cast<es2panda_AstNode*>(local);
    const auto _exported = reinterpret_cast<es2panda_AstNode*>(exported);
    auto result = GetImpl()->CreateExportSpecifier(_context, _local, _exported);
    return result;
}
KOALA_INTEROP_3(CreateExportSpecifier, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateExportSpecifier(KNativePointer context, KNativePointer original, KNativePointer local, KNativePointer exported)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _local = reinterpret_cast<es2panda_AstNode*>(local);
    const auto _exported = reinterpret_cast<es2panda_AstNode*>(exported);
    auto result = GetImpl()->UpdateExportSpecifier(_context, _original, _local, _exported);
    return result;
}
KOALA_INTEROP_4(UpdateExportSpecifier, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ExportSpecifierLocalConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ExportSpecifierLocalConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ExportSpecifierLocalConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ExportSpecifierExportedConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ExportSpecifierExportedConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ExportSpecifierExportedConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSTupleType(KNativePointer context, KNativePointerArray elementTypes, KUInt elementTypesSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _elementTypes = reinterpret_cast<es2panda_AstNode**>(elementTypes);
    const auto _elementTypesSequenceLength = static_cast<KUInt>(elementTypesSequenceLength);
    auto result = GetImpl()->CreateTSTupleType(_context, _elementTypes, _elementTypesSequenceLength);
    return result;
}
KOALA_INTEROP_3(CreateTSTupleType, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_UpdateTSTupleType(KNativePointer context, KNativePointer original, KNativePointerArray elementTypes, KUInt elementTypesSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _elementTypes = reinterpret_cast<es2panda_AstNode**>(elementTypes);
    const auto _elementTypesSequenceLength = static_cast<KUInt>(elementTypesSequenceLength);
    auto result = GetImpl()->UpdateTSTupleType(_context, _original, _elementTypes, _elementTypesSequenceLength);
    return result;
}
KOALA_INTEROP_4(UpdateTSTupleType, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_TSTupleTypeElementTypeConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->TSTupleTypeElementTypeConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(TSTupleTypeElementTypeConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateFunctionExpression(KNativePointer context, KNativePointer func)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _func = reinterpret_cast<es2panda_AstNode*>(func);
    auto result = GetImpl()->CreateFunctionExpression(_context, _func);
    return result;
}
KOALA_INTEROP_2(CreateFunctionExpression, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateFunctionExpression(KNativePointer context, KNativePointer original, KNativePointer func)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _func = reinterpret_cast<es2panda_AstNode*>(func);
    auto result = GetImpl()->UpdateFunctionExpression(_context, _original, _func);
    return result;
}
KOALA_INTEROP_3(UpdateFunctionExpression, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateFunctionExpression1(KNativePointer context, KNativePointer namedExpr, KNativePointer func)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _namedExpr = reinterpret_cast<es2panda_AstNode*>(namedExpr);
    const auto _func = reinterpret_cast<es2panda_AstNode*>(func);
    auto result = GetImpl()->CreateFunctionExpression1(_context, _namedExpr, _func);
    return result;
}
KOALA_INTEROP_3(CreateFunctionExpression1, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateFunctionExpression1(KNativePointer context, KNativePointer original, KNativePointer namedExpr, KNativePointer func)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _namedExpr = reinterpret_cast<es2panda_AstNode*>(namedExpr);
    const auto _func = reinterpret_cast<es2panda_AstNode*>(func);
    auto result = GetImpl()->UpdateFunctionExpression1(_context, _original, _namedExpr, _func);
    return result;
}
KOALA_INTEROP_4(UpdateFunctionExpression1, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_FunctionExpressionFunctionConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->FunctionExpressionFunctionConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(FunctionExpressionFunctionConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_FunctionExpressionFunction(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->FunctionExpressionFunction(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(FunctionExpressionFunction, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_FunctionExpressionIsAnonymousConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->FunctionExpressionIsAnonymousConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(FunctionExpressionIsAnonymousConst, KBoolean, KNativePointer, KNativePointer);

KNativePointer impl_FunctionExpressionId(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->FunctionExpressionId(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(FunctionExpressionId, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSIndexSignature(KNativePointer context, KNativePointer param, KNativePointer typeAnnotation, KBoolean readonly_arg)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _param = reinterpret_cast<es2panda_AstNode*>(param);
    const auto _typeAnnotation = reinterpret_cast<es2panda_AstNode*>(typeAnnotation);
    const auto _readonly_arg = static_cast<KBoolean>(readonly_arg);
    auto result = GetImpl()->CreateTSIndexSignature(_context, _param, _typeAnnotation, _readonly_arg);
    return result;
}
KOALA_INTEROP_4(CreateTSIndexSignature, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KBoolean);

KNativePointer impl_UpdateTSIndexSignature(KNativePointer context, KNativePointer original, KNativePointer param, KNativePointer typeAnnotation, KBoolean readonly_arg)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _param = reinterpret_cast<es2panda_AstNode*>(param);
    const auto _typeAnnotation = reinterpret_cast<es2panda_AstNode*>(typeAnnotation);
    const auto _readonly_arg = static_cast<KBoolean>(readonly_arg);
    auto result = GetImpl()->UpdateTSIndexSignature(_context, _original, _param, _typeAnnotation, _readonly_arg);
    return result;
}
KOALA_INTEROP_5(UpdateTSIndexSignature, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KBoolean);

KNativePointer impl_TSIndexSignatureParamConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSIndexSignatureParamConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSIndexSignatureParamConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSIndexSignatureTypeAnnotationConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSIndexSignatureTypeAnnotationConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSIndexSignatureTypeAnnotationConst, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_TSIndexSignatureReadonlyConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSIndexSignatureReadonlyConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSIndexSignatureReadonlyConst, KBoolean, KNativePointer, KNativePointer);

KInt impl_TSIndexSignatureKindConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSIndexSignatureKindConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSIndexSignatureKindConst, KInt, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSModuleDeclaration(KNativePointer context, KNativePointer name, KNativePointer body, KBoolean declare, KBoolean _global)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _name = reinterpret_cast<es2panda_AstNode*>(name);
    const auto _body = reinterpret_cast<es2panda_AstNode*>(body);
    const auto _declare = static_cast<KBoolean>(declare);
    const auto __global = static_cast<KBoolean>(_global);
    auto result = GetImpl()->CreateTSModuleDeclaration(_context, _name, _body, _declare, __global);
    return result;
}
KOALA_INTEROP_5(CreateTSModuleDeclaration, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KBoolean, KBoolean);

KNativePointer impl_UpdateTSModuleDeclaration(KNativePointer context, KNativePointer original, KNativePointer name, KNativePointer body, KBoolean declare, KBoolean _global)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _name = reinterpret_cast<es2panda_AstNode*>(name);
    const auto _body = reinterpret_cast<es2panda_AstNode*>(body);
    const auto _declare = static_cast<KBoolean>(declare);
    const auto __global = static_cast<KBoolean>(_global);
    auto result = GetImpl()->UpdateTSModuleDeclaration(_context, _original, _name, _body, _declare, __global);
    return result;
}
KOALA_INTEROP_6(UpdateTSModuleDeclaration, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KBoolean, KBoolean);

KNativePointer impl_TSModuleDeclarationNameConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSModuleDeclarationNameConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSModuleDeclarationNameConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSModuleDeclarationBodyConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSModuleDeclarationBodyConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSModuleDeclarationBodyConst, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_TSModuleDeclarationGlobalConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSModuleDeclarationGlobalConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSModuleDeclarationGlobalConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_TSModuleDeclarationIsExternalOrAmbientConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSModuleDeclarationIsExternalOrAmbientConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSModuleDeclarationIsExternalOrAmbientConst, KBoolean, KNativePointer, KNativePointer);

KNativePointer impl_CreateImportDeclaration(KNativePointer context, KNativePointer source, KNativePointerArray specifiers, KUInt specifiersSequenceLength, KInt importKind)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _source = reinterpret_cast<es2panda_AstNode*>(source);
    const auto _specifiers = reinterpret_cast<es2panda_AstNode**>(specifiers);
    const auto _specifiersSequenceLength = static_cast<KUInt>(specifiersSequenceLength);
    const auto _importKind = static_cast<Es2pandaImportKinds>(importKind);
    auto result = GetImpl()->CreateImportDeclaration(_context, _source, _specifiers, _specifiersSequenceLength, _importKind);
    return result;
}
KOALA_INTEROP_5(CreateImportDeclaration, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt, KInt);

KNativePointer impl_UpdateImportDeclaration(KNativePointer context, KNativePointer original, KNativePointer source, KNativePointerArray specifiers, KUInt specifiersSequenceLength, KInt importKind)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _source = reinterpret_cast<es2panda_AstNode*>(source);
    const auto _specifiers = reinterpret_cast<es2panda_AstNode**>(specifiers);
    const auto _specifiersSequenceLength = static_cast<KUInt>(specifiersSequenceLength);
    const auto _importKind = static_cast<Es2pandaImportKinds>(importKind);
    auto result = GetImpl()->UpdateImportDeclaration(_context, _original, _source, _specifiers, _specifiersSequenceLength, _importKind);
    return result;
}
KOALA_INTEROP_6(UpdateImportDeclaration, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt, KInt);

KNativePointer impl_ImportDeclarationSourceConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ImportDeclarationSourceConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ImportDeclarationSourceConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ImportDeclarationSource(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ImportDeclarationSource(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ImportDeclarationSource, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ImportDeclarationSpecifiersConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->ImportDeclarationSpecifiersConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(ImportDeclarationSpecifiersConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ImportDeclarationSpecifiers(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->ImportDeclarationSpecifiers(_context, _receiver, &length);
    return new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(ImportDeclarationSpecifiers, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_ImportDeclarationIsTypeKindConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ImportDeclarationIsTypeKindConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ImportDeclarationIsTypeKindConst, KBoolean, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSParenthesizedType(KNativePointer context, KNativePointer type)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _type = reinterpret_cast<es2panda_AstNode*>(type);
    auto result = GetImpl()->CreateTSParenthesizedType(_context, _type);
    return result;
}
KOALA_INTEROP_2(CreateTSParenthesizedType, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateTSParenthesizedType(KNativePointer context, KNativePointer original, KNativePointer type)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _type = reinterpret_cast<es2panda_AstNode*>(type);
    auto result = GetImpl()->UpdateTSParenthesizedType(_context, _original, _type);
    return result;
}
KOALA_INTEROP_3(UpdateTSParenthesizedType, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSParenthesizedTypeTypeConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSParenthesizedTypeTypeConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSParenthesizedTypeTypeConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateCharLiteral(KNativePointer context)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    auto result = GetImpl()->CreateCharLiteral(_context);
    return result;
}
KOALA_INTEROP_1(CreateCharLiteral, KNativePointer, KNativePointer);

KNativePointer impl_UpdateCharLiteral(KNativePointer context, KNativePointer original)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    auto result = GetImpl()->UpdateCharLiteral(_context, _original);
    return result;
}
KOALA_INTEROP_2(UpdateCharLiteral, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateETSPackageDeclaration(KNativePointer context, KNativePointer name)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _name = reinterpret_cast<es2panda_AstNode*>(name);
    auto result = GetImpl()->CreateETSPackageDeclaration(_context, _name);
    return result;
}
KOALA_INTEROP_2(CreateETSPackageDeclaration, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateETSPackageDeclaration(KNativePointer context, KNativePointer original, KNativePointer name)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _name = reinterpret_cast<es2panda_AstNode*>(name);
    auto result = GetImpl()->UpdateETSPackageDeclaration(_context, _original, _name);
    return result;
}
KOALA_INTEROP_3(UpdateETSPackageDeclaration, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateETSImportDeclaration(KNativePointer context, KNativePointer source, KNativePointerArray specifiers, KUInt specifiersSequenceLength, KInt importKind)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _source = reinterpret_cast<es2panda_ImportSource*>(source);
    const auto _specifiers = reinterpret_cast<es2panda_AstNode**>(specifiers);
    const auto _specifiersSequenceLength = static_cast<KUInt>(specifiersSequenceLength);
    const auto _importKind = static_cast<Es2pandaImportKinds>(importKind);
    auto result = GetImpl()->CreateETSImportDeclaration(_context, _source, _specifiers, _specifiersSequenceLength, _importKind);
    return result;
}
KOALA_INTEROP_5(CreateETSImportDeclaration, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt, KInt);

KNativePointer impl_UpdateETSImportDeclaration(KNativePointer context, KNativePointer original, KNativePointer source, KNativePointerArray specifiers, KUInt specifiersSequenceLength, KInt importKind)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _source = reinterpret_cast<es2panda_ImportSource*>(source);
    const auto _specifiers = reinterpret_cast<es2panda_AstNode**>(specifiers);
    const auto _specifiersSequenceLength = static_cast<KUInt>(specifiersSequenceLength);
    const auto _importKind = static_cast<Es2pandaImportKinds>(importKind);
    auto result = GetImpl()->UpdateETSImportDeclaration(_context, _original, _source, _specifiers, _specifiersSequenceLength, _importKind);
    return result;
}
KOALA_INTEROP_6(UpdateETSImportDeclaration, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt, KInt);

KBoolean impl_ETSImportDeclarationHasDeclConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSImportDeclarationHasDeclConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ETSImportDeclarationHasDeclConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_ETSImportDeclarationIsPureDynamicConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSImportDeclarationIsPureDynamicConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ETSImportDeclarationIsPureDynamicConst, KBoolean, KNativePointer, KNativePointer);

KNativePointer impl_ETSImportDeclarationAssemblerName(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSImportDeclarationAssemblerName(_context, _receiver);
    return new std::string(result);
}
KOALA_INTEROP_2(ETSImportDeclarationAssemblerName, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ETSImportDeclarationAssemblerNameConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSImportDeclarationAssemblerNameConst(_context, _receiver);
    return new std::string(result);
}
KOALA_INTEROP_2(ETSImportDeclarationAssemblerNameConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ETSImportDeclarationSourceConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSImportDeclarationSourceConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ETSImportDeclarationSourceConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ETSImportDeclarationResolvedSource(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSImportDeclarationResolvedSource(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ETSImportDeclarationResolvedSource, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ETSImportDeclarationResolvedSourceConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSImportDeclarationResolvedSourceConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ETSImportDeclarationResolvedSourceConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateETSStructDeclaration(KNativePointer context, KNativePointer def)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _def = reinterpret_cast<es2panda_AstNode*>(def);
    auto result = GetImpl()->CreateETSStructDeclaration(_context, _def);
    return result;
}
KOALA_INTEROP_2(CreateETSStructDeclaration, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateETSStructDeclaration(KNativePointer context, KNativePointer original, KNativePointer def)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _def = reinterpret_cast<es2panda_AstNode*>(def);
    auto result = GetImpl()->UpdateETSStructDeclaration(_context, _original, _def);
    return result;
}
KOALA_INTEROP_3(UpdateETSStructDeclaration, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSModuleBlock(KNativePointer context, KNativePointerArray statements, KUInt statementsSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _statements = reinterpret_cast<es2panda_AstNode**>(statements);
    const auto _statementsSequenceLength = static_cast<KUInt>(statementsSequenceLength);
    auto result = GetImpl()->CreateTSModuleBlock(_context, _statements, _statementsSequenceLength);
    return result;
}
KOALA_INTEROP_3(CreateTSModuleBlock, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_UpdateTSModuleBlock(KNativePointer context, KNativePointer original, KNativePointerArray statements, KUInt statementsSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _statements = reinterpret_cast<es2panda_AstNode**>(statements);
    const auto _statementsSequenceLength = static_cast<KUInt>(statementsSequenceLength);
    auto result = GetImpl()->UpdateTSModuleBlock(_context, _original, _statements, _statementsSequenceLength);
    return result;
}
KOALA_INTEROP_4(UpdateTSModuleBlock, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_TSModuleBlockStatementsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->TSModuleBlockStatementsConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(TSModuleBlockStatementsConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateETSNewArrayInstanceExpression(KNativePointer context, KNativePointer typeReference, KNativePointer dimension)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _typeReference = reinterpret_cast<es2panda_AstNode*>(typeReference);
    const auto _dimension = reinterpret_cast<es2panda_AstNode*>(dimension);
    auto result = GetImpl()->CreateETSNewArrayInstanceExpression(_context, _typeReference, _dimension);
    return result;
}
KOALA_INTEROP_3(CreateETSNewArrayInstanceExpression, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateETSNewArrayInstanceExpression(KNativePointer context, KNativePointer original, KNativePointer typeReference, KNativePointer dimension)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _typeReference = reinterpret_cast<es2panda_AstNode*>(typeReference);
    const auto _dimension = reinterpret_cast<es2panda_AstNode*>(dimension);
    auto result = GetImpl()->UpdateETSNewArrayInstanceExpression(_context, _original, _typeReference, _dimension);
    return result;
}
KOALA_INTEROP_4(UpdateETSNewArrayInstanceExpression, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ETSNewArrayInstanceExpressionTypeReference(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSNewArrayInstanceExpressionTypeReference(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ETSNewArrayInstanceExpressionTypeReference, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ETSNewArrayInstanceExpressionTypeReferenceConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSNewArrayInstanceExpressionTypeReferenceConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ETSNewArrayInstanceExpressionTypeReferenceConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ETSNewArrayInstanceExpressionDimension(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSNewArrayInstanceExpressionDimension(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ETSNewArrayInstanceExpressionDimension, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ETSNewArrayInstanceExpressionDimensionConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSNewArrayInstanceExpressionDimensionConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ETSNewArrayInstanceExpressionDimensionConst, KNativePointer, KNativePointer, KNativePointer);

void impl_ETSNewArrayInstanceExpressionSetDimension(KNativePointer context, KNativePointer receiver, KNativePointer dimension)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _dimension = reinterpret_cast<es2panda_AstNode*>(dimension);
    GetImpl()->ETSNewArrayInstanceExpressionSetDimension(_context, _receiver, _dimension);
    return ;
}
KOALA_INTEROP_V3(ETSNewArrayInstanceExpressionSetDimension, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateAnnotationDeclaration(KNativePointer context, KNativePointer expr)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _expr = reinterpret_cast<es2panda_AstNode*>(expr);
    auto result = GetImpl()->CreateAnnotationDeclaration(_context, _expr);
    return result;
}
KOALA_INTEROP_2(CreateAnnotationDeclaration, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateAnnotationDeclaration(KNativePointer context, KNativePointer original, KNativePointer expr)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _expr = reinterpret_cast<es2panda_AstNode*>(expr);
    auto result = GetImpl()->UpdateAnnotationDeclaration(_context, _original, _expr);
    return result;
}
KOALA_INTEROP_3(UpdateAnnotationDeclaration, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateAnnotationDeclaration1(KNativePointer context, KNativePointer expr, KNativePointerArray properties, KUInt propertiesSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _expr = reinterpret_cast<es2panda_AstNode*>(expr);
    const auto _properties = reinterpret_cast<es2panda_AstNode**>(properties);
    const auto _propertiesSequenceLength = static_cast<KUInt>(propertiesSequenceLength);
    auto result = GetImpl()->CreateAnnotationDeclaration1(_context, _expr, _properties, _propertiesSequenceLength);
    return result;
}
KOALA_INTEROP_4(CreateAnnotationDeclaration1, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_UpdateAnnotationDeclaration1(KNativePointer context, KNativePointer original, KNativePointer expr, KNativePointerArray properties, KUInt propertiesSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _expr = reinterpret_cast<es2panda_AstNode*>(expr);
    const auto _properties = reinterpret_cast<es2panda_AstNode**>(properties);
    const auto _propertiesSequenceLength = static_cast<KUInt>(propertiesSequenceLength);
    auto result = GetImpl()->UpdateAnnotationDeclaration1(_context, _original, _expr, _properties, _propertiesSequenceLength);
    return result;
}
KOALA_INTEROP_5(UpdateAnnotationDeclaration1, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_AnnotationDeclarationInternalNameConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AnnotationDeclarationInternalNameConst(_context, _receiver);
    return new std::string(result);
}
KOALA_INTEROP_2(AnnotationDeclarationInternalNameConst, KNativePointer, KNativePointer, KNativePointer);

void impl_AnnotationDeclarationSetInternalName(KNativePointer context, KNativePointer receiver, KStringPtr& internalName)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _internalName = getStringCopy(internalName);
    GetImpl()->AnnotationDeclarationSetInternalName(_context, _receiver, _internalName);
    return ;
}
KOALA_INTEROP_V3(AnnotationDeclarationSetInternalName, KNativePointer, KNativePointer, KStringPtr);

KNativePointer impl_AnnotationDeclarationExprConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AnnotationDeclarationExprConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(AnnotationDeclarationExprConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_AnnotationDeclarationExpr(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AnnotationDeclarationExpr(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AnnotationDeclarationExpr, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_AnnotationDeclarationProperties(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->AnnotationDeclarationProperties(_context, _receiver, &length);
    return new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(AnnotationDeclarationProperties, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_AnnotationDeclarationPropertiesConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->AnnotationDeclarationPropertiesConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(AnnotationDeclarationPropertiesConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_AnnotationDeclarationPropertiesPtrConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->AnnotationDeclarationPropertiesPtrConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(AnnotationDeclarationPropertiesPtrConst, KNativePointer, KNativePointer, KNativePointer);

void impl_AnnotationDeclarationAddProperties(KNativePointer context, KNativePointer receiver, KNativePointerArray properties, KUInt propertiesSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _properties = reinterpret_cast<es2panda_AstNode**>(properties);
    const auto _propertiesSequenceLength = static_cast<KUInt>(propertiesSequenceLength);
    GetImpl()->AnnotationDeclarationAddProperties(_context, _receiver, _properties, _propertiesSequenceLength);
    return ;
}
KOALA_INTEROP_V4(AnnotationDeclarationAddProperties, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KBoolean impl_AnnotationDeclarationIsSourceRetentionConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AnnotationDeclarationIsSourceRetentionConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AnnotationDeclarationIsSourceRetentionConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_AnnotationDeclarationIsBytecodeRetentionConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AnnotationDeclarationIsBytecodeRetentionConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AnnotationDeclarationIsBytecodeRetentionConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_AnnotationDeclarationIsRuntimeRetentionConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AnnotationDeclarationIsRuntimeRetentionConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AnnotationDeclarationIsRuntimeRetentionConst, KBoolean, KNativePointer, KNativePointer);

void impl_AnnotationDeclarationSetSourceRetention(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    GetImpl()->AnnotationDeclarationSetSourceRetention(_context, _receiver);
    return ;
}
KOALA_INTEROP_V2(AnnotationDeclarationSetSourceRetention, KNativePointer, KNativePointer);

void impl_AnnotationDeclarationSetBytecodeRetention(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    GetImpl()->AnnotationDeclarationSetBytecodeRetention(_context, _receiver);
    return ;
}
KOALA_INTEROP_V2(AnnotationDeclarationSetBytecodeRetention, KNativePointer, KNativePointer);

void impl_AnnotationDeclarationSetRuntimeRetention(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    GetImpl()->AnnotationDeclarationSetRuntimeRetention(_context, _receiver);
    return ;
}
KOALA_INTEROP_V2(AnnotationDeclarationSetRuntimeRetention, KNativePointer, KNativePointer);

KNativePointer impl_AnnotationDeclarationGetBaseNameConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AnnotationDeclarationGetBaseNameConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(AnnotationDeclarationGetBaseNameConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_AnnotationDeclarationAnnotations(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->AnnotationDeclarationAnnotations(_context, _receiver, &length);
    return new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(AnnotationDeclarationAnnotations, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_AnnotationDeclarationAnnotationsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->AnnotationDeclarationAnnotationsConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(AnnotationDeclarationAnnotationsConst, KNativePointer, KNativePointer, KNativePointer);

void impl_AnnotationDeclarationSetAnnotations(KNativePointer context, KNativePointer receiver, KNativePointerArray annotations, KUInt annotationsSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _annotations = reinterpret_cast<es2panda_AstNode**>(annotations);
    const auto _annotationsSequenceLength = static_cast<KUInt>(annotationsSequenceLength);
    GetImpl()->AnnotationDeclarationSetAnnotations(_context, _receiver, _annotations, _annotationsSequenceLength);
    return ;
}
KOALA_INTEROP_V4(AnnotationDeclarationSetAnnotations, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_CreateAnnotationUsageIr(KNativePointer context, KNativePointer expr)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _expr = reinterpret_cast<es2panda_AstNode*>(expr);
    auto result = GetImpl()->CreateAnnotationUsageIr(_context, _expr);
    return result;
}
KOALA_INTEROP_2(CreateAnnotationUsageIr, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateAnnotationUsageIr(KNativePointer context, KNativePointer original, KNativePointer expr)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _expr = reinterpret_cast<es2panda_AstNode*>(expr);
    auto result = GetImpl()->UpdateAnnotationUsageIr(_context, _original, _expr);
    return result;
}
KOALA_INTEROP_3(UpdateAnnotationUsageIr, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateAnnotationUsageIr1(KNativePointer context, KNativePointer expr, KNativePointerArray properties, KUInt propertiesSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _expr = reinterpret_cast<es2panda_AstNode*>(expr);
    const auto _properties = reinterpret_cast<es2panda_AstNode**>(properties);
    const auto _propertiesSequenceLength = static_cast<KUInt>(propertiesSequenceLength);
    auto result = GetImpl()->CreateAnnotationUsageIr1(_context, _expr, _properties, _propertiesSequenceLength);
    return result;
}
KOALA_INTEROP_4(CreateAnnotationUsageIr1, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_UpdateAnnotationUsageIr1(KNativePointer context, KNativePointer original, KNativePointer expr, KNativePointerArray properties, KUInt propertiesSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _expr = reinterpret_cast<es2panda_AstNode*>(expr);
    const auto _properties = reinterpret_cast<es2panda_AstNode**>(properties);
    const auto _propertiesSequenceLength = static_cast<KUInt>(propertiesSequenceLength);
    auto result = GetImpl()->UpdateAnnotationUsageIr1(_context, _original, _expr, _properties, _propertiesSequenceLength);
    return result;
}
KOALA_INTEROP_5(UpdateAnnotationUsageIr1, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_AnnotationUsageIrExpr(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AnnotationUsageIrExpr(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(AnnotationUsageIrExpr, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_AnnotationUsageIrProperties(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->AnnotationUsageIrProperties(_context, _receiver, &length);
    return new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(AnnotationUsageIrProperties, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_AnnotationUsageIrPropertiesConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->AnnotationUsageIrPropertiesConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(AnnotationUsageIrPropertiesConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_AnnotationUsageIrPropertiesPtrConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->AnnotationUsageIrPropertiesPtrConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(AnnotationUsageIrPropertiesPtrConst, KNativePointer, KNativePointer, KNativePointer);

void impl_AnnotationUsageIrAddProperty(KNativePointer context, KNativePointer receiver, KNativePointer property)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _property = reinterpret_cast<es2panda_AstNode*>(property);
    GetImpl()->AnnotationUsageIrAddProperty(_context, _receiver, _property);
    return ;
}
KOALA_INTEROP_V3(AnnotationUsageIrAddProperty, KNativePointer, KNativePointer, KNativePointer);

void impl_AnnotationUsageIrSetProperties(KNativePointer context, KNativePointer receiver, KNativePointerArray properties, KUInt propertiesSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _properties = reinterpret_cast<es2panda_AstNode**>(properties);
    const auto _propertiesSequenceLength = static_cast<KUInt>(propertiesSequenceLength);
    GetImpl()->AnnotationUsageIrSetProperties(_context, _receiver, _properties, _propertiesSequenceLength);
    return ;
}
KOALA_INTEROP_V4(AnnotationUsageIrSetProperties, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_AnnotationUsageIrGetBaseNameConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AnnotationUsageIrGetBaseNameConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(AnnotationUsageIrGetBaseNameConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateEmptyStatement(KNativePointer context)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    auto result = GetImpl()->CreateEmptyStatement(_context);
    return result;
}
KOALA_INTEROP_1(CreateEmptyStatement, KNativePointer, KNativePointer);

KNativePointer impl_UpdateEmptyStatement(KNativePointer context, KNativePointer original)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    auto result = GetImpl()->UpdateEmptyStatement(_context, _original);
    return result;
}
KOALA_INTEROP_2(UpdateEmptyStatement, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateETSLaunchExpression(KNativePointer context, KNativePointer expr)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _expr = reinterpret_cast<es2panda_AstNode*>(expr);
    auto result = GetImpl()->CreateETSLaunchExpression(_context, _expr);
    return result;
}
KOALA_INTEROP_2(CreateETSLaunchExpression, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateETSLaunchExpression(KNativePointer context, KNativePointer original, KNativePointer expr)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _expr = reinterpret_cast<es2panda_AstNode*>(expr);
    auto result = GetImpl()->UpdateETSLaunchExpression(_context, _original, _expr);
    return result;
}
KOALA_INTEROP_3(UpdateETSLaunchExpression, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_ETSLaunchExpressionIsStaticCallConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSLaunchExpressionIsStaticCallConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ETSLaunchExpressionIsStaticCallConst, KBoolean, KNativePointer, KNativePointer);

KNativePointer impl_ETSLaunchExpressionCallConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSLaunchExpressionCallConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ETSLaunchExpressionCallConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateWhileStatement(KNativePointer context, KNativePointer test, KNativePointer body)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _test = reinterpret_cast<es2panda_AstNode*>(test);
    const auto _body = reinterpret_cast<es2panda_AstNode*>(body);
    auto result = GetImpl()->CreateWhileStatement(_context, _test, _body);
    return result;
}
KOALA_INTEROP_3(CreateWhileStatement, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateWhileStatement(KNativePointer context, KNativePointer original, KNativePointer test, KNativePointer body)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _test = reinterpret_cast<es2panda_AstNode*>(test);
    const auto _body = reinterpret_cast<es2panda_AstNode*>(body);
    auto result = GetImpl()->UpdateWhileStatement(_context, _original, _test, _body);
    return result;
}
KOALA_INTEROP_4(UpdateWhileStatement, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_WhileStatementTestConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->WhileStatementTestConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(WhileStatementTestConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_WhileStatementTest(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->WhileStatementTest(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(WhileStatementTest, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_WhileStatementBodyConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->WhileStatementBodyConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(WhileStatementBodyConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_WhileStatementBody(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->WhileStatementBody(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(WhileStatementBody, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateFunctionSignature(KNativePointer context, KNativePointer typeParams, KNativePointerArray params, KUInt paramsSequenceLength, KNativePointer returnTypeAnnotation, KBoolean hasReceiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _typeParams = reinterpret_cast<es2panda_AstNode*>(typeParams);
    const auto _params = reinterpret_cast<es2panda_AstNode**>(params);
    const auto _paramsSequenceLength = static_cast<KUInt>(paramsSequenceLength);
    const auto _returnTypeAnnotation = reinterpret_cast<es2panda_AstNode*>(returnTypeAnnotation);
    const auto _hasReceiver = static_cast<KBoolean>(hasReceiver);
    auto result = GetImpl()->CreateFunctionSignature(_context, _typeParams, _params, _paramsSequenceLength, _returnTypeAnnotation, _hasReceiver);
    return result;
}
KOALA_INTEROP_6(CreateFunctionSignature, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt, KNativePointer, KBoolean);

KNativePointer impl_FunctionSignatureParamsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_FunctionSignature*>(receiver);
    std::size_t length;
    auto result = GetImpl()->FunctionSignatureParamsConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(FunctionSignatureParamsConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_FunctionSignatureParams(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_FunctionSignature*>(receiver);
    std::size_t length;
    auto result = GetImpl()->FunctionSignatureParams(_context, _receiver, &length);
    return new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(FunctionSignatureParams, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_FunctionSignatureTypeParams(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_FunctionSignature*>(receiver);
    auto result = GetImpl()->FunctionSignatureTypeParams(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(FunctionSignatureTypeParams, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_FunctionSignatureTypeParamsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_FunctionSignature*>(receiver);
    auto result = GetImpl()->FunctionSignatureTypeParamsConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(FunctionSignatureTypeParamsConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_FunctionSignatureReturnType(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_FunctionSignature*>(receiver);
    auto result = GetImpl()->FunctionSignatureReturnType(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(FunctionSignatureReturnType, KNativePointer, KNativePointer, KNativePointer);

void impl_FunctionSignatureSetReturnType(KNativePointer context, KNativePointer receiver, KNativePointer type)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_FunctionSignature*>(receiver);
    const auto _type = reinterpret_cast<es2panda_AstNode*>(type);
    GetImpl()->FunctionSignatureSetReturnType(_context, _receiver, _type);
    return ;
}
KOALA_INTEROP_V3(FunctionSignatureSetReturnType, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_FunctionSignatureReturnTypeConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_FunctionSignature*>(receiver);
    auto result = GetImpl()->FunctionSignatureReturnTypeConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(FunctionSignatureReturnTypeConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_FunctionSignatureClone(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_FunctionSignature*>(receiver);
    auto result = GetImpl()->FunctionSignatureClone(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(FunctionSignatureClone, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_FunctionSignatureHasReceiverConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_FunctionSignature*>(receiver);
    auto result = GetImpl()->FunctionSignatureHasReceiverConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(FunctionSignatureHasReceiverConst, KBoolean, KNativePointer, KNativePointer);

KNativePointer impl_CreateChainExpression(KNativePointer context, KNativePointer expression)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _expression = reinterpret_cast<es2panda_AstNode*>(expression);
    auto result = GetImpl()->CreateChainExpression(_context, _expression);
    return result;
}
KOALA_INTEROP_2(CreateChainExpression, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateChainExpression(KNativePointer context, KNativePointer original, KNativePointer expression)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _expression = reinterpret_cast<es2panda_AstNode*>(expression);
    auto result = GetImpl()->UpdateChainExpression(_context, _original, _expression);
    return result;
}
KOALA_INTEROP_3(UpdateChainExpression, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ChainExpressionGetExpressionConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ChainExpressionGetExpressionConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ChainExpressionGetExpressionConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ChainExpressionGetExpression(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ChainExpressionGetExpression(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ChainExpressionGetExpression, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSIntersectionType(KNativePointer context, KNativePointerArray types, KUInt typesSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _types = reinterpret_cast<es2panda_AstNode**>(types);
    const auto _typesSequenceLength = static_cast<KUInt>(typesSequenceLength);
    auto result = GetImpl()->CreateTSIntersectionType(_context, _types, _typesSequenceLength);
    return result;
}
KOALA_INTEROP_3(CreateTSIntersectionType, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_UpdateTSIntersectionType(KNativePointer context, KNativePointer original, KNativePointerArray types, KUInt typesSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _types = reinterpret_cast<es2panda_AstNode**>(types);
    const auto _typesSequenceLength = static_cast<KUInt>(typesSequenceLength);
    auto result = GetImpl()->UpdateTSIntersectionType(_context, _original, _types, _typesSequenceLength);
    return result;
}
KOALA_INTEROP_4(UpdateTSIntersectionType, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_TSIntersectionTypeTypesConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->TSIntersectionTypeTypesConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(TSIntersectionTypeTypesConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateUpdateExpression(KNativePointer context, KNativePointer argument, KInt updateOperator, KBoolean isPrefix)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _argument = reinterpret_cast<es2panda_AstNode*>(argument);
    const auto _updateOperator = static_cast<Es2pandaTokenType>(updateOperator);
    const auto _isPrefix = static_cast<KBoolean>(isPrefix);
    auto result = GetImpl()->CreateUpdateExpression(_context, _argument, _updateOperator, _isPrefix);
    return result;
}
KOALA_INTEROP_4(CreateUpdateExpression, KNativePointer, KNativePointer, KNativePointer, KInt, KBoolean);

KNativePointer impl_UpdateUpdateExpression(KNativePointer context, KNativePointer original, KNativePointer argument, KInt updateOperator, KBoolean isPrefix)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _argument = reinterpret_cast<es2panda_AstNode*>(argument);
    const auto _updateOperator = static_cast<Es2pandaTokenType>(updateOperator);
    const auto _isPrefix = static_cast<KBoolean>(isPrefix);
    auto result = GetImpl()->UpdateUpdateExpression(_context, _original, _argument, _updateOperator, _isPrefix);
    return result;
}
KOALA_INTEROP_5(UpdateUpdateExpression, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KInt, KBoolean);

KInt impl_UpdateExpressionOperatorTypeConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->UpdateExpressionOperatorTypeConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(UpdateExpressionOperatorTypeConst, KInt, KNativePointer, KNativePointer);

KNativePointer impl_UpdateExpressionArgument(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->UpdateExpressionArgument(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(UpdateExpressionArgument, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateExpressionArgumentConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->UpdateExpressionArgumentConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(UpdateExpressionArgumentConst, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_UpdateExpressionIsPrefixConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->UpdateExpressionIsPrefixConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(UpdateExpressionIsPrefixConst, KBoolean, KNativePointer, KNativePointer);

KNativePointer impl_CreateBlockExpression(KNativePointer context, KNativePointerArray statements, KUInt statementsSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _statements = reinterpret_cast<es2panda_AstNode**>(statements);
    const auto _statementsSequenceLength = static_cast<KUInt>(statementsSequenceLength);
    auto result = GetImpl()->CreateBlockExpression(_context, _statements, _statementsSequenceLength);
    return result;
}
KOALA_INTEROP_3(CreateBlockExpression, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_UpdateBlockExpression(KNativePointer context, KNativePointer original, KNativePointerArray statements, KUInt statementsSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _statements = reinterpret_cast<es2panda_AstNode**>(statements);
    const auto _statementsSequenceLength = static_cast<KUInt>(statementsSequenceLength);
    auto result = GetImpl()->UpdateBlockExpression(_context, _original, _statements, _statementsSequenceLength);
    return result;
}
KOALA_INTEROP_4(UpdateBlockExpression, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_BlockExpressionStatementsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->BlockExpressionStatementsConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(BlockExpressionStatementsConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_BlockExpressionStatements(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->BlockExpressionStatements(_context, _receiver, &length);
    return new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(BlockExpressionStatements, KNativePointer, KNativePointer, KNativePointer);

void impl_BlockExpressionAddStatements(KNativePointer context, KNativePointer receiver, KNativePointerArray statements, KUInt statementsSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _statements = reinterpret_cast<es2panda_AstNode**>(statements);
    const auto _statementsSequenceLength = static_cast<KUInt>(statementsSequenceLength);
    GetImpl()->BlockExpressionAddStatements(_context, _receiver, _statements, _statementsSequenceLength);
    return ;
}
KOALA_INTEROP_V4(BlockExpressionAddStatements, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

void impl_BlockExpressionAddStatement(KNativePointer context, KNativePointer receiver, KNativePointer statement)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _statement = reinterpret_cast<es2panda_AstNode*>(statement);
    GetImpl()->BlockExpressionAddStatement(_context, _receiver, _statement);
    return ;
}
KOALA_INTEROP_V3(BlockExpressionAddStatement, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSTypeLiteral(KNativePointer context, KNativePointerArray members, KUInt membersSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _members = reinterpret_cast<es2panda_AstNode**>(members);
    const auto _membersSequenceLength = static_cast<KUInt>(membersSequenceLength);
    auto result = GetImpl()->CreateTSTypeLiteral(_context, _members, _membersSequenceLength);
    return result;
}
KOALA_INTEROP_3(CreateTSTypeLiteral, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_UpdateTSTypeLiteral(KNativePointer context, KNativePointer original, KNativePointerArray members, KUInt membersSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _members = reinterpret_cast<es2panda_AstNode**>(members);
    const auto _membersSequenceLength = static_cast<KUInt>(membersSequenceLength);
    auto result = GetImpl()->UpdateTSTypeLiteral(_context, _original, _members, _membersSequenceLength);
    return result;
}
KOALA_INTEROP_4(UpdateTSTypeLiteral, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_TSTypeLiteralMembersConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->TSTypeLiteralMembersConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(TSTypeLiteralMembersConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSTypeParameter(KNativePointer context, KNativePointer name, KNativePointer constraint, KNativePointer defaultType)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _name = reinterpret_cast<es2panda_AstNode*>(name);
    const auto _constraint = reinterpret_cast<es2panda_AstNode*>(constraint);
    const auto _defaultType = reinterpret_cast<es2panda_AstNode*>(defaultType);
    auto result = GetImpl()->CreateTSTypeParameter(_context, _name, _constraint, _defaultType);
    return result;
}
KOALA_INTEROP_4(CreateTSTypeParameter, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateTSTypeParameter(KNativePointer context, KNativePointer original, KNativePointer name, KNativePointer constraint, KNativePointer defaultType)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _name = reinterpret_cast<es2panda_AstNode*>(name);
    const auto _constraint = reinterpret_cast<es2panda_AstNode*>(constraint);
    const auto _defaultType = reinterpret_cast<es2panda_AstNode*>(defaultType);
    auto result = GetImpl()->UpdateTSTypeParameter(_context, _original, _name, _constraint, _defaultType);
    return result;
}
KOALA_INTEROP_5(UpdateTSTypeParameter, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSTypeParameter1(KNativePointer context, KNativePointer name, KNativePointer constraint, KNativePointer defaultType, KInt flags)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _name = reinterpret_cast<es2panda_AstNode*>(name);
    const auto _constraint = reinterpret_cast<es2panda_AstNode*>(constraint);
    const auto _defaultType = reinterpret_cast<es2panda_AstNode*>(defaultType);
    const auto _flags = static_cast<Es2pandaModifierFlags>(flags);
    auto result = GetImpl()->CreateTSTypeParameter1(_context, _name, _constraint, _defaultType, _flags);
    return result;
}
KOALA_INTEROP_5(CreateTSTypeParameter1, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KInt);

KNativePointer impl_UpdateTSTypeParameter1(KNativePointer context, KNativePointer original, KNativePointer name, KNativePointer constraint, KNativePointer defaultType, KInt flags)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _name = reinterpret_cast<es2panda_AstNode*>(name);
    const auto _constraint = reinterpret_cast<es2panda_AstNode*>(constraint);
    const auto _defaultType = reinterpret_cast<es2panda_AstNode*>(defaultType);
    const auto _flags = static_cast<Es2pandaModifierFlags>(flags);
    auto result = GetImpl()->UpdateTSTypeParameter1(_context, _original, _name, _constraint, _defaultType, _flags);
    return result;
}
KOALA_INTEROP_6(UpdateTSTypeParameter1, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KInt);

KNativePointer impl_TSTypeParameterNameConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSTypeParameterNameConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSTypeParameterNameConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSTypeParameterName(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSTypeParameterName(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSTypeParameterName, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSTypeParameterConstraint(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSTypeParameterConstraint(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSTypeParameterConstraint, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSTypeParameterConstraintConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSTypeParameterConstraintConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSTypeParameterConstraintConst, KNativePointer, KNativePointer, KNativePointer);

void impl_TSTypeParameterSetConstraint(KNativePointer context, KNativePointer receiver, KNativePointer constraint)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _constraint = reinterpret_cast<es2panda_AstNode*>(constraint);
    GetImpl()->TSTypeParameterSetConstraint(_context, _receiver, _constraint);
    return ;
}
KOALA_INTEROP_V3(TSTypeParameterSetConstraint, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSTypeParameterDefaultTypeConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSTypeParameterDefaultTypeConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSTypeParameterDefaultTypeConst, KNativePointer, KNativePointer, KNativePointer);

void impl_TSTypeParameterSetDefaultType(KNativePointer context, KNativePointer receiver, KNativePointer defaultType)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _defaultType = reinterpret_cast<es2panda_AstNode*>(defaultType);
    GetImpl()->TSTypeParameterSetDefaultType(_context, _receiver, _defaultType);
    return ;
}
KOALA_INTEROP_V3(TSTypeParameterSetDefaultType, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSTypeParameterAnnotations(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->TSTypeParameterAnnotations(_context, _receiver, &length);
    return new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(TSTypeParameterAnnotations, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSTypeParameterAnnotationsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->TSTypeParameterAnnotationsConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(TSTypeParameterAnnotationsConst, KNativePointer, KNativePointer, KNativePointer);

void impl_TSTypeParameterSetAnnotations(KNativePointer context, KNativePointer receiver, KNativePointerArray annotations, KUInt annotationsSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _annotations = reinterpret_cast<es2panda_AstNode**>(annotations);
    const auto _annotationsSequenceLength = static_cast<KUInt>(annotationsSequenceLength);
    GetImpl()->TSTypeParameterSetAnnotations(_context, _receiver, _annotations, _annotationsSequenceLength);
    return ;
}
KOALA_INTEROP_V4(TSTypeParameterSetAnnotations, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_CreateTSBooleanKeyword(KNativePointer context)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    auto result = GetImpl()->CreateTSBooleanKeyword(_context);
    return result;
}
KOALA_INTEROP_1(CreateTSBooleanKeyword, KNativePointer, KNativePointer);

KNativePointer impl_UpdateTSBooleanKeyword(KNativePointer context, KNativePointer original)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    auto result = GetImpl()->UpdateTSBooleanKeyword(_context, _original);
    return result;
}
KOALA_INTEROP_2(UpdateTSBooleanKeyword, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateSpreadElement(KNativePointer context, KInt nodeType, KNativePointer argument)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _nodeType = static_cast<Es2pandaAstNodeType>(nodeType);
    const auto _argument = reinterpret_cast<es2panda_AstNode*>(argument);
    auto result = GetImpl()->CreateSpreadElement(_context, _nodeType, _argument);
    return result;
}
KOALA_INTEROP_3(CreateSpreadElement, KNativePointer, KNativePointer, KInt, KNativePointer);

KNativePointer impl_UpdateSpreadElement(KNativePointer context, KNativePointer original, KInt nodeType, KNativePointer argument)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _nodeType = static_cast<Es2pandaAstNodeType>(nodeType);
    const auto _argument = reinterpret_cast<es2panda_AstNode*>(argument);
    auto result = GetImpl()->UpdateSpreadElement(_context, _original, _nodeType, _argument);
    return result;
}
KOALA_INTEROP_4(UpdateSpreadElement, KNativePointer, KNativePointer, KNativePointer, KInt, KNativePointer);

KNativePointer impl_SpreadElementArgumentConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->SpreadElementArgumentConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(SpreadElementArgumentConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_SpreadElementArgument(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->SpreadElementArgument(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(SpreadElementArgument, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_SpreadElementIsOptionalConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->SpreadElementIsOptionalConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(SpreadElementIsOptionalConst, KBoolean, KNativePointer, KNativePointer);

KNativePointer impl_SpreadElementDecoratorsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->SpreadElementDecoratorsConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(SpreadElementDecoratorsConst, KNativePointer, KNativePointer, KNativePointer);

void impl_SpreadElementSetOptional(KNativePointer context, KNativePointer receiver, KBoolean optional_arg)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _optional_arg = static_cast<KBoolean>(optional_arg);
    GetImpl()->SpreadElementSetOptional(_context, _receiver, _optional_arg);
    return ;
}
KOALA_INTEROP_V3(SpreadElementSetOptional, KNativePointer, KNativePointer, KBoolean);

KNativePointer impl_SpreadElementValidateExpression(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->SpreadElementValidateExpression(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(SpreadElementValidateExpression, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_SpreadElementConvertibleToRest(KNativePointer context, KNativePointer receiver, KBoolean isDeclaration, KBoolean allowPattern)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _isDeclaration = static_cast<KBoolean>(isDeclaration);
    const auto _allowPattern = static_cast<KBoolean>(allowPattern);
    auto result = GetImpl()->SpreadElementConvertibleToRest(_context, _receiver, _isDeclaration, _allowPattern);
    return result;
}
KOALA_INTEROP_4(SpreadElementConvertibleToRest, KBoolean, KNativePointer, KNativePointer, KBoolean, KBoolean);

KNativePointer impl_SpreadElementTypeAnnotationConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->SpreadElementTypeAnnotationConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(SpreadElementTypeAnnotationConst, KNativePointer, KNativePointer, KNativePointer);

void impl_SpreadElementSetTsTypeAnnotation(KNativePointer context, KNativePointer receiver, KNativePointer typeAnnotation)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _typeAnnotation = reinterpret_cast<es2panda_AstNode*>(typeAnnotation);
    GetImpl()->SpreadElementSetTsTypeAnnotation(_context, _receiver, _typeAnnotation);
    return ;
}
KOALA_INTEROP_V3(SpreadElementSetTsTypeAnnotation, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSTypePredicate(KNativePointer context, KNativePointer parameterName, KNativePointer typeAnnotation, KBoolean asserts)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _parameterName = reinterpret_cast<es2panda_AstNode*>(parameterName);
    const auto _typeAnnotation = reinterpret_cast<es2panda_AstNode*>(typeAnnotation);
    const auto _asserts = static_cast<KBoolean>(asserts);
    auto result = GetImpl()->CreateTSTypePredicate(_context, _parameterName, _typeAnnotation, _asserts);
    return result;
}
KOALA_INTEROP_4(CreateTSTypePredicate, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KBoolean);

KNativePointer impl_UpdateTSTypePredicate(KNativePointer context, KNativePointer original, KNativePointer parameterName, KNativePointer typeAnnotation, KBoolean asserts)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _parameterName = reinterpret_cast<es2panda_AstNode*>(parameterName);
    const auto _typeAnnotation = reinterpret_cast<es2panda_AstNode*>(typeAnnotation);
    const auto _asserts = static_cast<KBoolean>(asserts);
    auto result = GetImpl()->UpdateTSTypePredicate(_context, _original, _parameterName, _typeAnnotation, _asserts);
    return result;
}
KOALA_INTEROP_5(UpdateTSTypePredicate, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KBoolean);

KNativePointer impl_TSTypePredicateParameterNameConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSTypePredicateParameterNameConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSTypePredicateParameterNameConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSTypePredicateTypeAnnotationConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSTypePredicateTypeAnnotationConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSTypePredicateTypeAnnotationConst, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_TSTypePredicateAssertsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSTypePredicateAssertsConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSTypePredicateAssertsConst, KBoolean, KNativePointer, KNativePointer);

KNativePointer impl_CreateImportNamespaceSpecifier(KNativePointer context, KNativePointer local)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _local = reinterpret_cast<es2panda_AstNode*>(local);
    auto result = GetImpl()->CreateImportNamespaceSpecifier(_context, _local);
    return result;
}
KOALA_INTEROP_2(CreateImportNamespaceSpecifier, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateImportNamespaceSpecifier(KNativePointer context, KNativePointer original, KNativePointer local)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _local = reinterpret_cast<es2panda_AstNode*>(local);
    auto result = GetImpl()->UpdateImportNamespaceSpecifier(_context, _original, _local);
    return result;
}
KOALA_INTEROP_3(UpdateImportNamespaceSpecifier, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ImportNamespaceSpecifierLocal(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ImportNamespaceSpecifierLocal(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ImportNamespaceSpecifierLocal, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ImportNamespaceSpecifierLocalConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ImportNamespaceSpecifierLocalConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ImportNamespaceSpecifierLocalConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateExportNamedDeclaration(KNativePointer context, KNativePointer source, KNativePointerArray specifiers, KUInt specifiersSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _source = reinterpret_cast<es2panda_AstNode*>(source);
    const auto _specifiers = reinterpret_cast<es2panda_AstNode**>(specifiers);
    const auto _specifiersSequenceLength = static_cast<KUInt>(specifiersSequenceLength);
    auto result = GetImpl()->CreateExportNamedDeclaration(_context, _source, _specifiers, _specifiersSequenceLength);
    return result;
}
KOALA_INTEROP_4(CreateExportNamedDeclaration, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_UpdateExportNamedDeclaration(KNativePointer context, KNativePointer original, KNativePointer source, KNativePointerArray specifiers, KUInt specifiersSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _source = reinterpret_cast<es2panda_AstNode*>(source);
    const auto _specifiers = reinterpret_cast<es2panda_AstNode**>(specifiers);
    const auto _specifiersSequenceLength = static_cast<KUInt>(specifiersSequenceLength);
    auto result = GetImpl()->UpdateExportNamedDeclaration(_context, _original, _source, _specifiers, _specifiersSequenceLength);
    return result;
}
KOALA_INTEROP_5(UpdateExportNamedDeclaration, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_CreateExportNamedDeclaration1(KNativePointer context, KNativePointer decl, KNativePointerArray specifiers, KUInt specifiersSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _decl = reinterpret_cast<es2panda_AstNode*>(decl);
    const auto _specifiers = reinterpret_cast<es2panda_AstNode**>(specifiers);
    const auto _specifiersSequenceLength = static_cast<KUInt>(specifiersSequenceLength);
    auto result = GetImpl()->CreateExportNamedDeclaration1(_context, _decl, _specifiers, _specifiersSequenceLength);
    return result;
}
KOALA_INTEROP_4(CreateExportNamedDeclaration1, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_UpdateExportNamedDeclaration1(KNativePointer context, KNativePointer original, KNativePointer decl, KNativePointerArray specifiers, KUInt specifiersSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _decl = reinterpret_cast<es2panda_AstNode*>(decl);
    const auto _specifiers = reinterpret_cast<es2panda_AstNode**>(specifiers);
    const auto _specifiersSequenceLength = static_cast<KUInt>(specifiersSequenceLength);
    auto result = GetImpl()->UpdateExportNamedDeclaration1(_context, _original, _decl, _specifiers, _specifiersSequenceLength);
    return result;
}
KOALA_INTEROP_5(UpdateExportNamedDeclaration1, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_CreateExportNamedDeclaration2(KNativePointer context, KNativePointer decl)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _decl = reinterpret_cast<es2panda_AstNode*>(decl);
    auto result = GetImpl()->CreateExportNamedDeclaration2(_context, _decl);
    return result;
}
KOALA_INTEROP_2(CreateExportNamedDeclaration2, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateExportNamedDeclaration2(KNativePointer context, KNativePointer original, KNativePointer decl)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _decl = reinterpret_cast<es2panda_AstNode*>(decl);
    auto result = GetImpl()->UpdateExportNamedDeclaration2(_context, _original, _decl);
    return result;
}
KOALA_INTEROP_3(UpdateExportNamedDeclaration2, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ExportNamedDeclarationDeclConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ExportNamedDeclarationDeclConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ExportNamedDeclarationDeclConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ExportNamedDeclarationSourceConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ExportNamedDeclarationSourceConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ExportNamedDeclarationSourceConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ExportNamedDeclarationSpecifiersConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->ExportNamedDeclarationSpecifiersConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(ExportNamedDeclarationSpecifiersConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateETSParameterExpression(KNativePointer context, KNativePointer identOrSpread, KBoolean isOptional)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _identOrSpread = reinterpret_cast<es2panda_AstNode*>(identOrSpread);
    const auto _isOptional = static_cast<KBoolean>(isOptional);
    auto result = GetImpl()->CreateETSParameterExpression(_context, _identOrSpread, _isOptional);
    return result;
}
KOALA_INTEROP_3(CreateETSParameterExpression, KNativePointer, KNativePointer, KNativePointer, KBoolean);

KNativePointer impl_UpdateETSParameterExpression(KNativePointer context, KNativePointer original, KNativePointer identOrSpread, KBoolean isOptional)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _identOrSpread = reinterpret_cast<es2panda_AstNode*>(identOrSpread);
    const auto _isOptional = static_cast<KBoolean>(isOptional);
    auto result = GetImpl()->UpdateETSParameterExpression(_context, _original, _identOrSpread, _isOptional);
    return result;
}
KOALA_INTEROP_4(UpdateETSParameterExpression, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KBoolean);

KNativePointer impl_CreateETSParameterExpression1(KNativePointer context, KNativePointer identOrSpread, KNativePointer initializer)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _identOrSpread = reinterpret_cast<es2panda_AstNode*>(identOrSpread);
    const auto _initializer = reinterpret_cast<es2panda_AstNode*>(initializer);
    auto result = GetImpl()->CreateETSParameterExpression1(_context, _identOrSpread, _initializer);
    return result;
}
KOALA_INTEROP_3(CreateETSParameterExpression1, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateETSParameterExpression1(KNativePointer context, KNativePointer original, KNativePointer identOrSpread, KNativePointer initializer)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _identOrSpread = reinterpret_cast<es2panda_AstNode*>(identOrSpread);
    const auto _initializer = reinterpret_cast<es2panda_AstNode*>(initializer);
    auto result = GetImpl()->UpdateETSParameterExpression1(_context, _original, _identOrSpread, _initializer);
    return result;
}
KOALA_INTEROP_4(UpdateETSParameterExpression1, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ETSParameterExpressionNameConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSParameterExpressionNameConst(_context, _receiver);
    return new std::string(result);
}
KOALA_INTEROP_2(ETSParameterExpressionNameConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ETSParameterExpressionIdentConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSParameterExpressionIdentConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ETSParameterExpressionIdentConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ETSParameterExpressionIdent(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSParameterExpressionIdent(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ETSParameterExpressionIdent, KNativePointer, KNativePointer, KNativePointer);

void impl_ETSParameterExpressionSetIdent(KNativePointer context, KNativePointer receiver, KNativePointer ident)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _ident = reinterpret_cast<es2panda_AstNode*>(ident);
    GetImpl()->ETSParameterExpressionSetIdent(_context, _receiver, _ident);
    return ;
}
KOALA_INTEROP_V3(ETSParameterExpressionSetIdent, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ETSParameterExpressionRestParameterConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSParameterExpressionRestParameterConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ETSParameterExpressionRestParameterConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ETSParameterExpressionRestParameter(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSParameterExpressionRestParameter(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ETSParameterExpressionRestParameter, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ETSParameterExpressionInitializerConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSParameterExpressionInitializerConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ETSParameterExpressionInitializerConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ETSParameterExpressionInitializer(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSParameterExpressionInitializer(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ETSParameterExpressionInitializer, KNativePointer, KNativePointer, KNativePointer);

void impl_ETSParameterExpressionSetLexerSaved(KNativePointer context, KNativePointer receiver, KStringPtr& s)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _s = getStringCopy(s);
    GetImpl()->ETSParameterExpressionSetLexerSaved(_context, _receiver, _s);
    return ;
}
KOALA_INTEROP_V3(ETSParameterExpressionSetLexerSaved, KNativePointer, KNativePointer, KStringPtr);

KNativePointer impl_ETSParameterExpressionLexerSavedConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSParameterExpressionLexerSavedConst(_context, _receiver);
    return new std::string(result);
}
KOALA_INTEROP_2(ETSParameterExpressionLexerSavedConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ETSParameterExpressionTypeAnnotationConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSParameterExpressionTypeAnnotationConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ETSParameterExpressionTypeAnnotationConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ETSParameterExpressionTypeAnnotation(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSParameterExpressionTypeAnnotation(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ETSParameterExpressionTypeAnnotation, KNativePointer, KNativePointer, KNativePointer);

void impl_ETSParameterExpressionSetTypeAnnotation(KNativePointer context, KNativePointer receiver, KNativePointer typeNode)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _typeNode = reinterpret_cast<es2panda_AstNode*>(typeNode);
    GetImpl()->ETSParameterExpressionSetTypeAnnotation(_context, _receiver, _typeNode);
    return ;
}
KOALA_INTEROP_V3(ETSParameterExpressionSetTypeAnnotation, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_ETSParameterExpressionIsOptionalConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSParameterExpressionIsOptionalConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ETSParameterExpressionIsOptionalConst, KBoolean, KNativePointer, KNativePointer);

void impl_ETSParameterExpressionSetOptional(KNativePointer context, KNativePointer receiver, KBoolean value)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _value = static_cast<KBoolean>(value);
    GetImpl()->ETSParameterExpressionSetOptional(_context, _receiver, _value);
    return ;
}
KOALA_INTEROP_V3(ETSParameterExpressionSetOptional, KNativePointer, KNativePointer, KBoolean);

void impl_ETSParameterExpressionSetInitializer(KNativePointer context, KNativePointer receiver, KNativePointer initExpr)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _initExpr = reinterpret_cast<es2panda_AstNode*>(initExpr);
    GetImpl()->ETSParameterExpressionSetInitializer(_context, _receiver, _initExpr);
    return ;
}
KOALA_INTEROP_V3(ETSParameterExpressionSetInitializer, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_ETSParameterExpressionIsRestParameterConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSParameterExpressionIsRestParameterConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ETSParameterExpressionIsRestParameterConst, KBoolean, KNativePointer, KNativePointer);

KUInt impl_ETSParameterExpressionGetRequiredParamsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSParameterExpressionGetRequiredParamsConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ETSParameterExpressionGetRequiredParamsConst, KUInt, KNativePointer, KNativePointer);

void impl_ETSParameterExpressionSetRequiredParams(KNativePointer context, KNativePointer receiver, KUInt value)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _value = static_cast<KUInt>(value);
    GetImpl()->ETSParameterExpressionSetRequiredParams(_context, _receiver, _value);
    return ;
}
KOALA_INTEROP_V3(ETSParameterExpressionSetRequiredParams, KNativePointer, KNativePointer, KUInt);

KNativePointer impl_ETSParameterExpressionAnnotations(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->ETSParameterExpressionAnnotations(_context, _receiver, &length);
    return new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(ETSParameterExpressionAnnotations, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ETSParameterExpressionAnnotationsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->ETSParameterExpressionAnnotationsConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(ETSParameterExpressionAnnotationsConst, KNativePointer, KNativePointer, KNativePointer);

void impl_ETSParameterExpressionSetAnnotations(KNativePointer context, KNativePointer receiver, KNativePointerArray annotations, KUInt annotationsSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _annotations = reinterpret_cast<es2panda_AstNode**>(annotations);
    const auto _annotationsSequenceLength = static_cast<KUInt>(annotationsSequenceLength);
    GetImpl()->ETSParameterExpressionSetAnnotations(_context, _receiver, _annotations, _annotationsSequenceLength);
    return ;
}
KOALA_INTEROP_V4(ETSParameterExpressionSetAnnotations, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_CreateTSTypeParameterInstantiation(KNativePointer context, KNativePointerArray params, KUInt paramsSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _params = reinterpret_cast<es2panda_AstNode**>(params);
    const auto _paramsSequenceLength = static_cast<KUInt>(paramsSequenceLength);
    auto result = GetImpl()->CreateTSTypeParameterInstantiation(_context, _params, _paramsSequenceLength);
    return result;
}
KOALA_INTEROP_3(CreateTSTypeParameterInstantiation, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_UpdateTSTypeParameterInstantiation(KNativePointer context, KNativePointer original, KNativePointerArray params, KUInt paramsSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _params = reinterpret_cast<es2panda_AstNode**>(params);
    const auto _paramsSequenceLength = static_cast<KUInt>(paramsSequenceLength);
    auto result = GetImpl()->UpdateTSTypeParameterInstantiation(_context, _original, _params, _paramsSequenceLength);
    return result;
}
KOALA_INTEROP_4(UpdateTSTypeParameterInstantiation, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_TSTypeParameterInstantiationParamsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->TSTypeParameterInstantiationParamsConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(TSTypeParameterInstantiationParamsConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateNullLiteral(KNativePointer context)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    auto result = GetImpl()->CreateNullLiteral(_context);
    return result;
}
KOALA_INTEROP_1(CreateNullLiteral, KNativePointer, KNativePointer);

KNativePointer impl_UpdateNullLiteral(KNativePointer context, KNativePointer original)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    auto result = GetImpl()->UpdateNullLiteral(_context, _original);
    return result;
}
KOALA_INTEROP_2(UpdateNullLiteral, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSInferType(KNativePointer context, KNativePointer typeParam)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _typeParam = reinterpret_cast<es2panda_AstNode*>(typeParam);
    auto result = GetImpl()->CreateTSInferType(_context, _typeParam);
    return result;
}
KOALA_INTEROP_2(CreateTSInferType, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateTSInferType(KNativePointer context, KNativePointer original, KNativePointer typeParam)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _typeParam = reinterpret_cast<es2panda_AstNode*>(typeParam);
    auto result = GetImpl()->UpdateTSInferType(_context, _original, _typeParam);
    return result;
}
KOALA_INTEROP_3(UpdateTSInferType, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSInferTypeTypeParamConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSInferTypeTypeParamConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSInferTypeTypeParamConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateSwitchCaseStatement(KNativePointer context, KNativePointer test, KNativePointerArray consequent, KUInt consequentSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _test = reinterpret_cast<es2panda_AstNode*>(test);
    const auto _consequent = reinterpret_cast<es2panda_AstNode**>(consequent);
    const auto _consequentSequenceLength = static_cast<KUInt>(consequentSequenceLength);
    auto result = GetImpl()->CreateSwitchCaseStatement(_context, _test, _consequent, _consequentSequenceLength);
    return result;
}
KOALA_INTEROP_4(CreateSwitchCaseStatement, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_UpdateSwitchCaseStatement(KNativePointer context, KNativePointer original, KNativePointer test, KNativePointerArray consequent, KUInt consequentSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _test = reinterpret_cast<es2panda_AstNode*>(test);
    const auto _consequent = reinterpret_cast<es2panda_AstNode**>(consequent);
    const auto _consequentSequenceLength = static_cast<KUInt>(consequentSequenceLength);
    auto result = GetImpl()->UpdateSwitchCaseStatement(_context, _original, _test, _consequent, _consequentSequenceLength);
    return result;
}
KOALA_INTEROP_5(UpdateSwitchCaseStatement, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_SwitchCaseStatementTest(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->SwitchCaseStatementTest(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(SwitchCaseStatementTest, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_SwitchCaseStatementTestConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->SwitchCaseStatementTestConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(SwitchCaseStatementTestConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_SwitchCaseStatementConsequentConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->SwitchCaseStatementConsequentConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(SwitchCaseStatementConsequentConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateYieldExpression(KNativePointer context, KNativePointer argument, KBoolean isDelegate)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _argument = reinterpret_cast<es2panda_AstNode*>(argument);
    const auto _isDelegate = static_cast<KBoolean>(isDelegate);
    auto result = GetImpl()->CreateYieldExpression(_context, _argument, _isDelegate);
    return result;
}
KOALA_INTEROP_3(CreateYieldExpression, KNativePointer, KNativePointer, KNativePointer, KBoolean);

KNativePointer impl_UpdateYieldExpression(KNativePointer context, KNativePointer original, KNativePointer argument, KBoolean isDelegate)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _argument = reinterpret_cast<es2panda_AstNode*>(argument);
    const auto _isDelegate = static_cast<KBoolean>(isDelegate);
    auto result = GetImpl()->UpdateYieldExpression(_context, _original, _argument, _isDelegate);
    return result;
}
KOALA_INTEROP_4(UpdateYieldExpression, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KBoolean);

KBoolean impl_YieldExpressionHasDelegateConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->YieldExpressionHasDelegateConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(YieldExpressionHasDelegateConst, KBoolean, KNativePointer, KNativePointer);

KNativePointer impl_YieldExpressionArgumentConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->YieldExpressionArgumentConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(YieldExpressionArgumentConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSImportEqualsDeclaration(KNativePointer context, KNativePointer id, KNativePointer moduleReference, KBoolean isExport)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _id = reinterpret_cast<es2panda_AstNode*>(id);
    const auto _moduleReference = reinterpret_cast<es2panda_AstNode*>(moduleReference);
    const auto _isExport = static_cast<KBoolean>(isExport);
    auto result = GetImpl()->CreateTSImportEqualsDeclaration(_context, _id, _moduleReference, _isExport);
    return result;
}
KOALA_INTEROP_4(CreateTSImportEqualsDeclaration, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KBoolean);

KNativePointer impl_UpdateTSImportEqualsDeclaration(KNativePointer context, KNativePointer original, KNativePointer id, KNativePointer moduleReference, KBoolean isExport)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _id = reinterpret_cast<es2panda_AstNode*>(id);
    const auto _moduleReference = reinterpret_cast<es2panda_AstNode*>(moduleReference);
    const auto _isExport = static_cast<KBoolean>(isExport);
    auto result = GetImpl()->UpdateTSImportEqualsDeclaration(_context, _original, _id, _moduleReference, _isExport);
    return result;
}
KOALA_INTEROP_5(UpdateTSImportEqualsDeclaration, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KBoolean);

KNativePointer impl_TSImportEqualsDeclarationIdConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSImportEqualsDeclarationIdConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSImportEqualsDeclarationIdConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSImportEqualsDeclarationModuleReferenceConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSImportEqualsDeclarationModuleReferenceConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSImportEqualsDeclarationModuleReferenceConst, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_TSImportEqualsDeclarationIsExportConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSImportEqualsDeclarationIsExportConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSImportEqualsDeclarationIsExportConst, KBoolean, KNativePointer, KNativePointer);

KNativePointer impl_CreateBooleanLiteral(KNativePointer context, KBoolean value)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _value = static_cast<KBoolean>(value);
    auto result = GetImpl()->CreateBooleanLiteral(_context, _value);
    return result;
}
KOALA_INTEROP_2(CreateBooleanLiteral, KNativePointer, KNativePointer, KBoolean);

KNativePointer impl_UpdateBooleanLiteral(KNativePointer context, KNativePointer original, KBoolean value)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _value = static_cast<KBoolean>(value);
    auto result = GetImpl()->UpdateBooleanLiteral(_context, _original, _value);
    return result;
}
KOALA_INTEROP_3(UpdateBooleanLiteral, KNativePointer, KNativePointer, KNativePointer, KBoolean);

KBoolean impl_BooleanLiteralValueConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->BooleanLiteralValueConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(BooleanLiteralValueConst, KBoolean, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSNumberKeyword(KNativePointer context)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    auto result = GetImpl()->CreateTSNumberKeyword(_context);
    return result;
}
KOALA_INTEROP_1(CreateTSNumberKeyword, KNativePointer, KNativePointer);

KNativePointer impl_UpdateTSNumberKeyword(KNativePointer context, KNativePointer original)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    auto result = GetImpl()->UpdateTSNumberKeyword(_context, _original);
    return result;
}
KOALA_INTEROP_2(UpdateTSNumberKeyword, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateClassStaticBlock(KNativePointer context, KNativePointer value)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _value = reinterpret_cast<es2panda_AstNode*>(value);
    auto result = GetImpl()->CreateClassStaticBlock(_context, _value);
    return result;
}
KOALA_INTEROP_2(CreateClassStaticBlock, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateClassStaticBlock(KNativePointer context, KNativePointer original, KNativePointer value)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _value = reinterpret_cast<es2panda_AstNode*>(value);
    auto result = GetImpl()->UpdateClassStaticBlock(_context, _original, _value);
    return result;
}
KOALA_INTEROP_3(UpdateClassStaticBlock, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ClassStaticBlockFunction(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ClassStaticBlockFunction(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ClassStaticBlockFunction, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ClassStaticBlockFunctionConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ClassStaticBlockFunctionConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ClassStaticBlockFunctionConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ClassStaticBlockNameConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ClassStaticBlockNameConst(_context, _receiver);
    return new std::string(result);
}
KOALA_INTEROP_2(ClassStaticBlockNameConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSNonNullExpression(KNativePointer context, KNativePointer expr)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _expr = reinterpret_cast<es2panda_AstNode*>(expr);
    auto result = GetImpl()->CreateTSNonNullExpression(_context, _expr);
    return result;
}
KOALA_INTEROP_2(CreateTSNonNullExpression, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateTSNonNullExpression(KNativePointer context, KNativePointer original, KNativePointer expr)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _expr = reinterpret_cast<es2panda_AstNode*>(expr);
    auto result = GetImpl()->UpdateTSNonNullExpression(_context, _original, _expr);
    return result;
}
KOALA_INTEROP_3(UpdateTSNonNullExpression, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSNonNullExpressionExprConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSNonNullExpressionExprConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSNonNullExpressionExprConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSNonNullExpressionExpr(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSNonNullExpressionExpr(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSNonNullExpressionExpr, KNativePointer, KNativePointer, KNativePointer);

void impl_TSNonNullExpressionSetExpr(KNativePointer context, KNativePointer receiver, KNativePointer expr)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _expr = reinterpret_cast<es2panda_AstNode*>(expr);
    GetImpl()->TSNonNullExpressionSetExpr(_context, _receiver, _expr);
    return ;
}
KOALA_INTEROP_V3(TSNonNullExpressionSetExpr, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreatePrefixAssertionExpression(KNativePointer context, KNativePointer expr, KNativePointer type)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _expr = reinterpret_cast<es2panda_AstNode*>(expr);
    const auto _type = reinterpret_cast<es2panda_AstNode*>(type);
    auto result = GetImpl()->CreatePrefixAssertionExpression(_context, _expr, _type);
    return result;
}
KOALA_INTEROP_3(CreatePrefixAssertionExpression, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdatePrefixAssertionExpression(KNativePointer context, KNativePointer original, KNativePointer expr, KNativePointer type)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _expr = reinterpret_cast<es2panda_AstNode*>(expr);
    const auto _type = reinterpret_cast<es2panda_AstNode*>(type);
    auto result = GetImpl()->UpdatePrefixAssertionExpression(_context, _original, _expr, _type);
    return result;
}
KOALA_INTEROP_4(UpdatePrefixAssertionExpression, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_PrefixAssertionExpressionExprConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->PrefixAssertionExpressionExprConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(PrefixAssertionExpressionExprConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_PrefixAssertionExpressionTypeConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->PrefixAssertionExpressionTypeConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(PrefixAssertionExpressionTypeConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateClassExpression(KNativePointer context, KNativePointer def)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _def = reinterpret_cast<es2panda_AstNode*>(def);
    auto result = GetImpl()->CreateClassExpression(_context, _def);
    return result;
}
KOALA_INTEROP_2(CreateClassExpression, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateClassExpression(KNativePointer context, KNativePointer original, KNativePointer def)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _def = reinterpret_cast<es2panda_AstNode*>(def);
    auto result = GetImpl()->UpdateClassExpression(_context, _original, _def);
    return result;
}
KOALA_INTEROP_3(UpdateClassExpression, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ClassExpressionDefinitionConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ClassExpressionDefinitionConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ClassExpressionDefinitionConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateForOfStatement(KNativePointer context, KNativePointer left, KNativePointer right, KNativePointer body, KBoolean isAwait)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _left = reinterpret_cast<es2panda_AstNode*>(left);
    const auto _right = reinterpret_cast<es2panda_AstNode*>(right);
    const auto _body = reinterpret_cast<es2panda_AstNode*>(body);
    const auto _isAwait = static_cast<KBoolean>(isAwait);
    auto result = GetImpl()->CreateForOfStatement(_context, _left, _right, _body, _isAwait);
    return result;
}
KOALA_INTEROP_5(CreateForOfStatement, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KBoolean);

KNativePointer impl_UpdateForOfStatement(KNativePointer context, KNativePointer original, KNativePointer left, KNativePointer right, KNativePointer body, KBoolean isAwait)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _left = reinterpret_cast<es2panda_AstNode*>(left);
    const auto _right = reinterpret_cast<es2panda_AstNode*>(right);
    const auto _body = reinterpret_cast<es2panda_AstNode*>(body);
    const auto _isAwait = static_cast<KBoolean>(isAwait);
    auto result = GetImpl()->UpdateForOfStatement(_context, _original, _left, _right, _body, _isAwait);
    return result;
}
KOALA_INTEROP_6(UpdateForOfStatement, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KBoolean);

KNativePointer impl_ForOfStatementLeft(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ForOfStatementLeft(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ForOfStatementLeft, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ForOfStatementLeftConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ForOfStatementLeftConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ForOfStatementLeftConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ForOfStatementRight(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ForOfStatementRight(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ForOfStatementRight, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ForOfStatementRightConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ForOfStatementRightConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ForOfStatementRightConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ForOfStatementBody(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ForOfStatementBody(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ForOfStatementBody, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ForOfStatementBodyConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ForOfStatementBodyConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ForOfStatementBodyConst, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_ForOfStatementIsAwaitConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ForOfStatementIsAwaitConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ForOfStatementIsAwaitConst, KBoolean, KNativePointer, KNativePointer);

KNativePointer impl_CreateTemplateLiteral(KNativePointer context, KNativePointerArray quasis, KUInt quasisSequenceLength, KNativePointerArray expressions, KUInt expressionsSequenceLength, KStringPtr& multilineString)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _quasis = reinterpret_cast<es2panda_AstNode**>(quasis);
    const auto _quasisSequenceLength = static_cast<KUInt>(quasisSequenceLength);
    const auto _expressions = reinterpret_cast<es2panda_AstNode**>(expressions);
    const auto _expressionsSequenceLength = static_cast<KUInt>(expressionsSequenceLength);
    const auto _multilineString = getStringCopy(multilineString);
    auto result = GetImpl()->CreateTemplateLiteral(_context, _quasis, _quasisSequenceLength, _expressions, _expressionsSequenceLength, _multilineString);
    return result;
}
KOALA_INTEROP_6(CreateTemplateLiteral, KNativePointer, KNativePointer, KNativePointerArray, KUInt, KNativePointerArray, KUInt, KStringPtr);

KNativePointer impl_UpdateTemplateLiteral(KNativePointer context, KNativePointer original, KNativePointerArray quasis, KUInt quasisSequenceLength, KNativePointerArray expressions, KUInt expressionsSequenceLength, KStringPtr& multilineString)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _quasis = reinterpret_cast<es2panda_AstNode**>(quasis);
    const auto _quasisSequenceLength = static_cast<KUInt>(quasisSequenceLength);
    const auto _expressions = reinterpret_cast<es2panda_AstNode**>(expressions);
    const auto _expressionsSequenceLength = static_cast<KUInt>(expressionsSequenceLength);
    const auto _multilineString = getStringCopy(multilineString);
    auto result = GetImpl()->UpdateTemplateLiteral(_context, _original, _quasis, _quasisSequenceLength, _expressions, _expressionsSequenceLength, _multilineString);
    return result;
}
KOALA_INTEROP_7(UpdateTemplateLiteral, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt, KNativePointerArray, KUInt, KStringPtr);

KNativePointer impl_TemplateLiteralQuasisConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->TemplateLiteralQuasisConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(TemplateLiteralQuasisConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TemplateLiteralExpressionsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->TemplateLiteralExpressionsConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(TemplateLiteralExpressionsConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TemplateLiteralGetMultilineStringConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TemplateLiteralGetMultilineStringConst(_context, _receiver);
    return new std::string(result);
}
KOALA_INTEROP_2(TemplateLiteralGetMultilineStringConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSUnionType(KNativePointer context, KNativePointerArray types, KUInt typesSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _types = reinterpret_cast<es2panda_AstNode**>(types);
    const auto _typesSequenceLength = static_cast<KUInt>(typesSequenceLength);
    auto result = GetImpl()->CreateTSUnionType(_context, _types, _typesSequenceLength);
    return result;
}
KOALA_INTEROP_3(CreateTSUnionType, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_UpdateTSUnionType(KNativePointer context, KNativePointer original, KNativePointerArray types, KUInt typesSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _types = reinterpret_cast<es2panda_AstNode**>(types);
    const auto _typesSequenceLength = static_cast<KUInt>(typesSequenceLength);
    auto result = GetImpl()->UpdateTSUnionType(_context, _original, _types, _typesSequenceLength);
    return result;
}
KOALA_INTEROP_4(UpdateTSUnionType, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_TSUnionTypeTypesConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->TSUnionTypeTypesConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(TSUnionTypeTypesConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSUnknownKeyword(KNativePointer context)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    auto result = GetImpl()->CreateTSUnknownKeyword(_context);
    return result;
}
KOALA_INTEROP_1(CreateTSUnknownKeyword, KNativePointer, KNativePointer);

KNativePointer impl_UpdateTSUnknownKeyword(KNativePointer context, KNativePointer original)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    auto result = GetImpl()->UpdateTSUnknownKeyword(_context, _original);
    return result;
}
KOALA_INTEROP_2(UpdateTSUnknownKeyword, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateIdentifier(KNativePointer context)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    auto result = GetImpl()->CreateIdentifier(_context);
    return result;
}
KOALA_INTEROP_1(CreateIdentifier, KNativePointer, KNativePointer);

KNativePointer impl_UpdateIdentifier(KNativePointer context, KNativePointer original)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    auto result = GetImpl()->UpdateIdentifier(_context, _original);
    return result;
}
KOALA_INTEROP_2(UpdateIdentifier, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateIdentifier1(KNativePointer context, KStringPtr& name)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _name = getStringCopy(name);
    auto result = GetImpl()->CreateIdentifier1(_context, _name);
    return result;
}
KOALA_INTEROP_2(CreateIdentifier1, KNativePointer, KNativePointer, KStringPtr);

KNativePointer impl_UpdateIdentifier1(KNativePointer context, KNativePointer original, KStringPtr& name)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _name = getStringCopy(name);
    auto result = GetImpl()->UpdateIdentifier1(_context, _original, _name);
    return result;
}
KOALA_INTEROP_3(UpdateIdentifier1, KNativePointer, KNativePointer, KNativePointer, KStringPtr);

KNativePointer impl_CreateIdentifier2(KNativePointer context, KStringPtr& name, KNativePointer typeAnnotation)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _name = getStringCopy(name);
    const auto _typeAnnotation = reinterpret_cast<es2panda_AstNode*>(typeAnnotation);
    auto result = GetImpl()->CreateIdentifier2(_context, _name, _typeAnnotation);
    return result;
}
KOALA_INTEROP_3(CreateIdentifier2, KNativePointer, KNativePointer, KStringPtr, KNativePointer);

KNativePointer impl_UpdateIdentifier2(KNativePointer context, KNativePointer original, KStringPtr& name, KNativePointer typeAnnotation)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _name = getStringCopy(name);
    const auto _typeAnnotation = reinterpret_cast<es2panda_AstNode*>(typeAnnotation);
    auto result = GetImpl()->UpdateIdentifier2(_context, _original, _name, _typeAnnotation);
    return result;
}
KOALA_INTEROP_4(UpdateIdentifier2, KNativePointer, KNativePointer, KNativePointer, KStringPtr, KNativePointer);

KNativePointer impl_IdentifierNameConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->IdentifierNameConst(_context, _receiver);
    return new std::string(result);
}
KOALA_INTEROP_2(IdentifierNameConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_IdentifierName(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->IdentifierName(_context, _receiver);
    return new std::string(result);
}
KOALA_INTEROP_2(IdentifierName, KNativePointer, KNativePointer, KNativePointer);

void impl_IdentifierSetName(KNativePointer context, KNativePointer receiver, KStringPtr& newName)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _newName = getStringCopy(newName);
    GetImpl()->IdentifierSetName(_context, _receiver, _newName);
    return ;
}
KOALA_INTEROP_V3(IdentifierSetName, KNativePointer, KNativePointer, KStringPtr);

KNativePointer impl_IdentifierDecoratorsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->IdentifierDecoratorsConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(IdentifierDecoratorsConst, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_IdentifierIsErrorPlaceHolderConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->IdentifierIsErrorPlaceHolderConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(IdentifierIsErrorPlaceHolderConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_IdentifierIsOptionalConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->IdentifierIsOptionalConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(IdentifierIsOptionalConst, KBoolean, KNativePointer, KNativePointer);

void impl_IdentifierSetOptional(KNativePointer context, KNativePointer receiver, KBoolean optional_arg)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _optional_arg = static_cast<KBoolean>(optional_arg);
    GetImpl()->IdentifierSetOptional(_context, _receiver, _optional_arg);
    return ;
}
KOALA_INTEROP_V3(IdentifierSetOptional, KNativePointer, KNativePointer, KBoolean);

KBoolean impl_IdentifierIsReferenceConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->IdentifierIsReferenceConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(IdentifierIsReferenceConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_IdentifierIsTdzConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->IdentifierIsTdzConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(IdentifierIsTdzConst, KBoolean, KNativePointer, KNativePointer);

void impl_IdentifierSetTdz(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    GetImpl()->IdentifierSetTdz(_context, _receiver);
    return ;
}
KOALA_INTEROP_V2(IdentifierSetTdz, KNativePointer, KNativePointer);

void impl_IdentifierSetAccessor(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    GetImpl()->IdentifierSetAccessor(_context, _receiver);
    return ;
}
KOALA_INTEROP_V2(IdentifierSetAccessor, KNativePointer, KNativePointer);

KBoolean impl_IdentifierIsAccessorConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->IdentifierIsAccessorConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(IdentifierIsAccessorConst, KBoolean, KNativePointer, KNativePointer);

void impl_IdentifierSetMutator(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    GetImpl()->IdentifierSetMutator(_context, _receiver);
    return ;
}
KOALA_INTEROP_V2(IdentifierSetMutator, KNativePointer, KNativePointer);

KBoolean impl_IdentifierIsMutatorConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->IdentifierIsMutatorConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(IdentifierIsMutatorConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_IdentifierIsReceiverConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->IdentifierIsReceiverConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(IdentifierIsReceiverConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_IdentifierIsPrivateIdentConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->IdentifierIsPrivateIdentConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(IdentifierIsPrivateIdentConst, KBoolean, KNativePointer, KNativePointer);

void impl_IdentifierSetPrivate(KNativePointer context, KNativePointer receiver, KBoolean isPrivate)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _isPrivate = static_cast<KBoolean>(isPrivate);
    GetImpl()->IdentifierSetPrivate(_context, _receiver, _isPrivate);
    return ;
}
KOALA_INTEROP_V3(IdentifierSetPrivate, KNativePointer, KNativePointer, KBoolean);

KBoolean impl_IdentifierIsIgnoreBoxConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->IdentifierIsIgnoreBoxConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(IdentifierIsIgnoreBoxConst, KBoolean, KNativePointer, KNativePointer);

void impl_IdentifierSetIgnoreBox(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    GetImpl()->IdentifierSetIgnoreBox(_context, _receiver);
    return ;
}
KOALA_INTEROP_V2(IdentifierSetIgnoreBox, KNativePointer, KNativePointer);

KBoolean impl_IdentifierIsAnnotationDeclConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->IdentifierIsAnnotationDeclConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(IdentifierIsAnnotationDeclConst, KBoolean, KNativePointer, KNativePointer);

void impl_IdentifierSetAnnotationDecl(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    GetImpl()->IdentifierSetAnnotationDecl(_context, _receiver);
    return ;
}
KOALA_INTEROP_V2(IdentifierSetAnnotationDecl, KNativePointer, KNativePointer);

KBoolean impl_IdentifierIsAnnotationUsageConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->IdentifierIsAnnotationUsageConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(IdentifierIsAnnotationUsageConst, KBoolean, KNativePointer, KNativePointer);

void impl_IdentifierSetAnnotationUsage(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    GetImpl()->IdentifierSetAnnotationUsage(_context, _receiver);
    return ;
}
KOALA_INTEROP_V2(IdentifierSetAnnotationUsage, KNativePointer, KNativePointer);

KNativePointer impl_IdentifierCloneReference(KNativePointer context, KNativePointer receiver, KNativePointer parent)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _parent = reinterpret_cast<es2panda_AstNode*>(parent);
    auto result = GetImpl()->IdentifierCloneReference(_context, _receiver, _parent);
    return result;
}
KOALA_INTEROP_3(IdentifierCloneReference, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_IdentifierValidateExpression(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->IdentifierValidateExpression(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(IdentifierValidateExpression, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_IdentifierTypeAnnotationConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->IdentifierTypeAnnotationConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(IdentifierTypeAnnotationConst, KNativePointer, KNativePointer, KNativePointer);

void impl_IdentifierSetTsTypeAnnotation(KNativePointer context, KNativePointer receiver, KNativePointer typeAnnotation)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _typeAnnotation = reinterpret_cast<es2panda_AstNode*>(typeAnnotation);
    GetImpl()->IdentifierSetTsTypeAnnotation(_context, _receiver, _typeAnnotation);
    return ;
}
KOALA_INTEROP_V3(IdentifierSetTsTypeAnnotation, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateOpaqueTypeNode1(KNativePointer context)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    auto result = GetImpl()->CreateOpaqueTypeNode1(_context);
    return result;
}
KOALA_INTEROP_1(CreateOpaqueTypeNode1, KNativePointer, KNativePointer);

KNativePointer impl_UpdateOpaqueTypeNode1(KNativePointer context, KNativePointer original)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    auto result = GetImpl()->UpdateOpaqueTypeNode1(_context, _original);
    return result;
}
KOALA_INTEROP_2(UpdateOpaqueTypeNode1, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateBlockStatement(KNativePointer context, KNativePointerArray statementList, KUInt statementListSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _statementList = reinterpret_cast<es2panda_AstNode**>(statementList);
    const auto _statementListSequenceLength = static_cast<KUInt>(statementListSequenceLength);
    auto result = GetImpl()->CreateBlockStatement(_context, _statementList, _statementListSequenceLength);
    return result;
}
KOALA_INTEROP_3(CreateBlockStatement, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_UpdateBlockStatement(KNativePointer context, KNativePointer original, KNativePointerArray statementList, KUInt statementListSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _statementList = reinterpret_cast<es2panda_AstNode**>(statementList);
    const auto _statementListSequenceLength = static_cast<KUInt>(statementListSequenceLength);
    auto result = GetImpl()->UpdateBlockStatement(_context, _original, _statementList, _statementListSequenceLength);
    return result;
}
KOALA_INTEROP_4(UpdateBlockStatement, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_BlockStatementStatementsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->BlockStatementStatementsConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(BlockStatementStatementsConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_BlockStatementStatements(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->BlockStatementStatements(_context, _receiver, &length);
    return new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(BlockStatementStatements, KNativePointer, KNativePointer, KNativePointer);

void impl_BlockStatementSetStatements(KNativePointer context, KNativePointer receiver, KNativePointerArray statementList, KUInt statementListSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _statementList = reinterpret_cast<es2panda_AstNode**>(statementList);
    const auto _statementListSequenceLength = static_cast<KUInt>(statementListSequenceLength);
    GetImpl()->BlockStatementSetStatements(_context, _receiver, _statementList, _statementListSequenceLength);
    return ;
}
KOALA_INTEROP_V4(BlockStatementSetStatements, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

void impl_BlockStatementAddTrailingBlock(KNativePointer context, KNativePointer receiver, KNativePointer stmt, KNativePointer trailingBlock)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _stmt = reinterpret_cast<es2panda_AstNode*>(stmt);
    const auto _trailingBlock = reinterpret_cast<es2panda_AstNode*>(trailingBlock);
    GetImpl()->BlockStatementAddTrailingBlock(_context, _receiver, _stmt, _trailingBlock);
    return ;
}
KOALA_INTEROP_V4(BlockStatementAddTrailingBlock, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateDirectEvalExpression(KNativePointer context, KNativePointer callee, KNativePointerArray _arguments, KUInt _argumentsSequenceLength, KNativePointer typeParams, KBoolean optional_arg, KUInt parserStatus)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _callee = reinterpret_cast<es2panda_AstNode*>(callee);
    const auto __arguments = reinterpret_cast<es2panda_AstNode**>(_arguments);
    const auto __argumentsSequenceLength = static_cast<KUInt>(_argumentsSequenceLength);
    const auto _typeParams = reinterpret_cast<es2panda_AstNode*>(typeParams);
    const auto _optional_arg = static_cast<KBoolean>(optional_arg);
    const auto _parserStatus = static_cast<KUInt>(parserStatus);
    auto result = GetImpl()->CreateDirectEvalExpression(_context, _callee, __arguments, __argumentsSequenceLength, _typeParams, _optional_arg, _parserStatus);
    return result;
}
KOALA_INTEROP_7(CreateDirectEvalExpression, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt, KNativePointer, KBoolean, KUInt);

KNativePointer impl_UpdateDirectEvalExpression(KNativePointer context, KNativePointer original, KNativePointer callee, KNativePointerArray _arguments, KUInt _argumentsSequenceLength, KNativePointer typeParams, KBoolean optional_arg, KUInt parserStatus)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _callee = reinterpret_cast<es2panda_AstNode*>(callee);
    const auto __arguments = reinterpret_cast<es2panda_AstNode**>(_arguments);
    const auto __argumentsSequenceLength = static_cast<KUInt>(_argumentsSequenceLength);
    const auto _typeParams = reinterpret_cast<es2panda_AstNode*>(typeParams);
    const auto _optional_arg = static_cast<KBoolean>(optional_arg);
    const auto _parserStatus = static_cast<KUInt>(parserStatus);
    auto result = GetImpl()->UpdateDirectEvalExpression(_context, _original, _callee, __arguments, __argumentsSequenceLength, _typeParams, _optional_arg, _parserStatus);
    return result;
}
KOALA_INTEROP_8(UpdateDirectEvalExpression, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt, KNativePointer, KBoolean, KUInt);

KNativePointer impl_CreateTSTypeParameterDeclaration(KNativePointer context, KNativePointerArray params, KUInt paramsSequenceLength, KUInt requiredParams)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _params = reinterpret_cast<es2panda_AstNode**>(params);
    const auto _paramsSequenceLength = static_cast<KUInt>(paramsSequenceLength);
    const auto _requiredParams = static_cast<KUInt>(requiredParams);
    auto result = GetImpl()->CreateTSTypeParameterDeclaration(_context, _params, _paramsSequenceLength, _requiredParams);
    return result;
}
KOALA_INTEROP_4(CreateTSTypeParameterDeclaration, KNativePointer, KNativePointer, KNativePointerArray, KUInt, KUInt);

KNativePointer impl_UpdateTSTypeParameterDeclaration(KNativePointer context, KNativePointer original, KNativePointerArray params, KUInt paramsSequenceLength, KUInt requiredParams)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _params = reinterpret_cast<es2panda_AstNode**>(params);
    const auto _paramsSequenceLength = static_cast<KUInt>(paramsSequenceLength);
    const auto _requiredParams = static_cast<KUInt>(requiredParams);
    auto result = GetImpl()->UpdateTSTypeParameterDeclaration(_context, _original, _params, _paramsSequenceLength, _requiredParams);
    return result;
}
KOALA_INTEROP_5(UpdateTSTypeParameterDeclaration, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt, KUInt);

KNativePointer impl_TSTypeParameterDeclarationParamsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->TSTypeParameterDeclarationParamsConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(TSTypeParameterDeclarationParamsConst, KNativePointer, KNativePointer, KNativePointer);

void impl_TSTypeParameterDeclarationAddParam(KNativePointer context, KNativePointer receiver, KNativePointer param)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _param = reinterpret_cast<es2panda_AstNode*>(param);
    GetImpl()->TSTypeParameterDeclarationAddParam(_context, _receiver, _param);
    return ;
}
KOALA_INTEROP_V3(TSTypeParameterDeclarationAddParam, KNativePointer, KNativePointer, KNativePointer);

KUInt impl_TSTypeParameterDeclarationRequiredParamsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSTypeParameterDeclarationRequiredParamsConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSTypeParameterDeclarationRequiredParamsConst, KUInt, KNativePointer, KNativePointer);

KNativePointer impl_CreateMethodDefinition(KNativePointer context, KInt kind, KNativePointer key, KNativePointer value, KInt modifiers, KBoolean isComputed)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _kind = static_cast<Es2pandaMethodDefinitionKind>(kind);
    const auto _key = reinterpret_cast<es2panda_AstNode*>(key);
    const auto _value = reinterpret_cast<es2panda_AstNode*>(value);
    const auto _modifiers = static_cast<Es2pandaModifierFlags>(modifiers);
    const auto _isComputed = static_cast<KBoolean>(isComputed);
    auto result = GetImpl()->CreateMethodDefinition(_context, _kind, _key, _value, _modifiers, _isComputed);
    return result;
}
KOALA_INTEROP_6(CreateMethodDefinition, KNativePointer, KNativePointer, KInt, KNativePointer, KNativePointer, KInt, KBoolean);

KNativePointer impl_UpdateMethodDefinition(KNativePointer context, KNativePointer original, KInt kind, KNativePointer key, KNativePointer value, KInt modifiers, KBoolean isComputed)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _kind = static_cast<Es2pandaMethodDefinitionKind>(kind);
    const auto _key = reinterpret_cast<es2panda_AstNode*>(key);
    const auto _value = reinterpret_cast<es2panda_AstNode*>(value);
    const auto _modifiers = static_cast<Es2pandaModifierFlags>(modifiers);
    const auto _isComputed = static_cast<KBoolean>(isComputed);
    auto result = GetImpl()->UpdateMethodDefinition(_context, _original, _kind, _key, _value, _modifiers, _isComputed);
    return result;
}
KOALA_INTEROP_7(UpdateMethodDefinition, KNativePointer, KNativePointer, KNativePointer, KInt, KNativePointer, KNativePointer, KInt, KBoolean);

KInt impl_MethodDefinitionKindConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->MethodDefinitionKindConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(MethodDefinitionKindConst, KInt, KNativePointer, KNativePointer);

KBoolean impl_MethodDefinitionIsConstructorConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->MethodDefinitionIsConstructorConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(MethodDefinitionIsConstructorConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_MethodDefinitionIsExtensionMethodConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->MethodDefinitionIsExtensionMethodConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(MethodDefinitionIsExtensionMethodConst, KBoolean, KNativePointer, KNativePointer);

KNativePointer impl_MethodDefinitionOverloadsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->MethodDefinitionOverloadsConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(MethodDefinitionOverloadsConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_MethodDefinitionBaseOverloadMethodConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->MethodDefinitionBaseOverloadMethodConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(MethodDefinitionBaseOverloadMethodConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_MethodDefinitionBaseOverloadMethod(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->MethodDefinitionBaseOverloadMethod(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(MethodDefinitionBaseOverloadMethod, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_MethodDefinitionAsyncPairMethodConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->MethodDefinitionAsyncPairMethodConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(MethodDefinitionAsyncPairMethodConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_MethodDefinitionAsyncPairMethod(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->MethodDefinitionAsyncPairMethod(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(MethodDefinitionAsyncPairMethod, KNativePointer, KNativePointer, KNativePointer);

void impl_MethodDefinitionSetOverloads(KNativePointer context, KNativePointer receiver, KNativePointerArray overloads, KUInt overloadsSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _overloads = reinterpret_cast<es2panda_AstNode**>(overloads);
    const auto _overloadsSequenceLength = static_cast<KUInt>(overloadsSequenceLength);
    GetImpl()->MethodDefinitionSetOverloads(_context, _receiver, _overloads, _overloadsSequenceLength);
    return ;
}
KOALA_INTEROP_V4(MethodDefinitionSetOverloads, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

void impl_MethodDefinitionClearOverloads(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    GetImpl()->MethodDefinitionClearOverloads(_context, _receiver);
    return ;
}
KOALA_INTEROP_V2(MethodDefinitionClearOverloads, KNativePointer, KNativePointer);

void impl_MethodDefinitionAddOverload(KNativePointer context, KNativePointer receiver, KNativePointer overload)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _overload = reinterpret_cast<es2panda_AstNode*>(overload);
    GetImpl()->MethodDefinitionAddOverload(_context, _receiver, _overload);
    return ;
}
KOALA_INTEROP_V3(MethodDefinitionAddOverload, KNativePointer, KNativePointer, KNativePointer);

void impl_MethodDefinitionSetBaseOverloadMethod(KNativePointer context, KNativePointer receiver, KNativePointer baseOverloadMethod)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _baseOverloadMethod = reinterpret_cast<es2panda_AstNode*>(baseOverloadMethod);
    GetImpl()->MethodDefinitionSetBaseOverloadMethod(_context, _receiver, _baseOverloadMethod);
    return ;
}
KOALA_INTEROP_V3(MethodDefinitionSetBaseOverloadMethod, KNativePointer, KNativePointer, KNativePointer);

void impl_MethodDefinitionSetAsyncPairMethod(KNativePointer context, KNativePointer receiver, KNativePointer method)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _method = reinterpret_cast<es2panda_AstNode*>(method);
    GetImpl()->MethodDefinitionSetAsyncPairMethod(_context, _receiver, _method);
    return ;
}
KOALA_INTEROP_V3(MethodDefinitionSetAsyncPairMethod, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_MethodDefinitionHasOverload(KNativePointer context, KNativePointer receiver, KNativePointer overload)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _overload = reinterpret_cast<es2panda_AstNode*>(overload);
    auto result = GetImpl()->MethodDefinitionHasOverload(_context, _receiver, _overload);
    return result;
}
KOALA_INTEROP_3(MethodDefinitionHasOverload, KBoolean, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_MethodDefinitionFunction(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->MethodDefinitionFunction(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(MethodDefinitionFunction, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_MethodDefinitionFunctionConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->MethodDefinitionFunctionConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(MethodDefinitionFunctionConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSNullKeyword(KNativePointer context)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    auto result = GetImpl()->CreateTSNullKeyword(_context);
    return result;
}
KOALA_INTEROP_1(CreateTSNullKeyword, KNativePointer, KNativePointer);

KNativePointer impl_UpdateTSNullKeyword(KNativePointer context, KNativePointer original)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    auto result = GetImpl()->UpdateTSNullKeyword(_context, _original);
    return result;
}
KOALA_INTEROP_2(UpdateTSNullKeyword, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSInterfaceHeritage(KNativePointer context, KNativePointer expr)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _expr = reinterpret_cast<es2panda_AstNode*>(expr);
    auto result = GetImpl()->CreateTSInterfaceHeritage(_context, _expr);
    return result;
}
KOALA_INTEROP_2(CreateTSInterfaceHeritage, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateTSInterfaceHeritage(KNativePointer context, KNativePointer original, KNativePointer expr)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _expr = reinterpret_cast<es2panda_AstNode*>(expr);
    auto result = GetImpl()->UpdateTSInterfaceHeritage(_context, _original, _expr);
    return result;
}
KOALA_INTEROP_3(UpdateTSInterfaceHeritage, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSInterfaceHeritageExpr(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSInterfaceHeritageExpr(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSInterfaceHeritageExpr, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSInterfaceHeritageExprConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSInterfaceHeritageExprConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSInterfaceHeritageExprConst, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_ExpressionIsGroupedConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ExpressionIsGroupedConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ExpressionIsGroupedConst, KBoolean, KNativePointer, KNativePointer);

void impl_ExpressionSetGrouped(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    GetImpl()->ExpressionSetGrouped(_context, _receiver);
    return ;
}
KOALA_INTEROP_V2(ExpressionSetGrouped, KNativePointer, KNativePointer);

KNativePointer impl_ExpressionAsLiteralConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ExpressionAsLiteralConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ExpressionAsLiteralConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ExpressionAsLiteral(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ExpressionAsLiteral(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ExpressionAsLiteral, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_ExpressionIsLiteralConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ExpressionIsLiteralConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ExpressionIsLiteralConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_ExpressionIsTypeNodeConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ExpressionIsTypeNodeConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ExpressionIsTypeNodeConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_ExpressionIsAnnotatedExpressionConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ExpressionIsAnnotatedExpressionConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ExpressionIsAnnotatedExpressionConst, KBoolean, KNativePointer, KNativePointer);

KNativePointer impl_ExpressionAsTypeNode(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ExpressionAsTypeNode(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ExpressionAsTypeNode, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ExpressionAsTypeNodeConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ExpressionAsTypeNodeConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ExpressionAsTypeNodeConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ExpressionAsAnnotatedExpression(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ExpressionAsAnnotatedExpression(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ExpressionAsAnnotatedExpression, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ExpressionAsAnnotatedExpressionConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ExpressionAsAnnotatedExpressionConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ExpressionAsAnnotatedExpressionConst, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_ExpressionIsBrokenExpressionConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ExpressionIsBrokenExpressionConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ExpressionIsBrokenExpressionConst, KBoolean, KNativePointer, KNativePointer);

KNativePointer impl_ExpressionToStringConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ExpressionToStringConst(_context, _receiver);
    return new std::string(result);
}
KOALA_INTEROP_2(ExpressionToStringConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_AnnotatedExpressionTypeAnnotationConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AnnotatedExpressionTypeAnnotationConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(AnnotatedExpressionTypeAnnotationConst, KNativePointer, KNativePointer, KNativePointer);

void impl_AnnotatedExpressionSetTsTypeAnnotation(KNativePointer context, KNativePointer receiver, KNativePointer typeAnnotation)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _typeAnnotation = reinterpret_cast<es2panda_AstNode*>(typeAnnotation);
    GetImpl()->AnnotatedExpressionSetTsTypeAnnotation(_context, _receiver, _typeAnnotation);
    return ;
}
KOALA_INTEROP_V3(AnnotatedExpressionSetTsTypeAnnotation, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_MaybeOptionalExpressionIsOptionalConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->MaybeOptionalExpressionIsOptionalConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(MaybeOptionalExpressionIsOptionalConst, KBoolean, KNativePointer, KNativePointer);

void impl_MaybeOptionalExpressionClearOptional(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    GetImpl()->MaybeOptionalExpressionClearOptional(_context, _receiver);
    return ;
}
KOALA_INTEROP_V2(MaybeOptionalExpressionClearOptional, KNativePointer, KNativePointer);

KNativePointer impl_CreateSrcDumper(KNativePointer context, KNativePointer node)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _node = reinterpret_cast<es2panda_AstNode*>(node);
    auto result = GetImpl()->CreateSrcDumper(_context, _node);
    return result;
}
KOALA_INTEROP_2(CreateSrcDumper, KNativePointer, KNativePointer, KNativePointer);

void impl_SrcDumperAdd(KNativePointer context, KNativePointer receiver, KStringPtr& str)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_SrcDumper*>(receiver);
    const auto _str = getStringCopy(str);
    GetImpl()->SrcDumperAdd(_context, _receiver, _str);
    return ;
}
KOALA_INTEROP_V3(SrcDumperAdd, KNativePointer, KNativePointer, KStringPtr);

void impl_SrcDumperAdd1(KNativePointer context, KNativePointer receiver, KInt i)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_SrcDumper*>(receiver);
    const auto _i = static_cast<KInt>(i);
    GetImpl()->SrcDumperAdd1(_context, _receiver, _i);
    return ;
}
KOALA_INTEROP_V3(SrcDumperAdd1, KNativePointer, KNativePointer, KInt);

void impl_SrcDumperAdd2(KNativePointer context, KNativePointer receiver, KLong l)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_SrcDumper*>(receiver);
    const auto _l = static_cast<KLong>(l);
    GetImpl()->SrcDumperAdd2(_context, _receiver, _l);
    return ;
}
KOALA_INTEROP_V3(SrcDumperAdd2, KNativePointer, KNativePointer, KLong);

void impl_SrcDumperAdd3(KNativePointer context, KNativePointer receiver, KFloat f)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_SrcDumper*>(receiver);
    const auto _f = static_cast<KFloat>(f);
    GetImpl()->SrcDumperAdd3(_context, _receiver, _f);
    return ;
}
KOALA_INTEROP_V3(SrcDumperAdd3, KNativePointer, KNativePointer, KFloat);

void impl_SrcDumperAdd4(KNativePointer context, KNativePointer receiver, KDouble d)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_SrcDumper*>(receiver);
    const auto _d = static_cast<KDouble>(d);
    GetImpl()->SrcDumperAdd4(_context, _receiver, _d);
    return ;
}
KOALA_INTEROP_V3(SrcDumperAdd4, KNativePointer, KNativePointer, KDouble);

KNativePointer impl_SrcDumperStrConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_SrcDumper*>(receiver);
    auto result = GetImpl()->SrcDumperStrConst(_context, _receiver);
    return new std::string(result);
}
KOALA_INTEROP_2(SrcDumperStrConst, KNativePointer, KNativePointer, KNativePointer);

void impl_SrcDumperIncrIndent(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_SrcDumper*>(receiver);
    GetImpl()->SrcDumperIncrIndent(_context, _receiver);
    return ;
}
KOALA_INTEROP_V2(SrcDumperIncrIndent, KNativePointer, KNativePointer);

void impl_SrcDumperDecrIndent(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_SrcDumper*>(receiver);
    GetImpl()->SrcDumperDecrIndent(_context, _receiver);
    return ;
}
KOALA_INTEROP_V2(SrcDumperDecrIndent, KNativePointer, KNativePointer);

void impl_SrcDumperEndl(KNativePointer context, KNativePointer receiver, KUInt num)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_SrcDumper*>(receiver);
    const auto _num = static_cast<KUInt>(num);
    GetImpl()->SrcDumperEndl(_context, _receiver, _num);
    return ;
}
KOALA_INTEROP_V3(SrcDumperEndl, KNativePointer, KNativePointer, KUInt);

KNativePointer impl_CreateETSClassLiteral(KNativePointer context, KNativePointer expr)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _expr = reinterpret_cast<es2panda_AstNode*>(expr);
    auto result = GetImpl()->CreateETSClassLiteral(_context, _expr);
    return result;
}
KOALA_INTEROP_2(CreateETSClassLiteral, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateETSClassLiteral(KNativePointer context, KNativePointer original, KNativePointer expr)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _expr = reinterpret_cast<es2panda_AstNode*>(expr);
    auto result = GetImpl()->UpdateETSClassLiteral(_context, _original, _expr);
    return result;
}
KOALA_INTEROP_3(UpdateETSClassLiteral, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ETSClassLiteralExprConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSClassLiteralExprConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ETSClassLiteralExprConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateBreakStatement(KNativePointer context)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    auto result = GetImpl()->CreateBreakStatement(_context);
    return result;
}
KOALA_INTEROP_1(CreateBreakStatement, KNativePointer, KNativePointer);

KNativePointer impl_UpdateBreakStatement(KNativePointer context, KNativePointer original)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    auto result = GetImpl()->UpdateBreakStatement(_context, _original);
    return result;
}
KOALA_INTEROP_2(UpdateBreakStatement, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateBreakStatement1(KNativePointer context, KNativePointer ident)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _ident = reinterpret_cast<es2panda_AstNode*>(ident);
    auto result = GetImpl()->CreateBreakStatement1(_context, _ident);
    return result;
}
KOALA_INTEROP_2(CreateBreakStatement1, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateBreakStatement1(KNativePointer context, KNativePointer original, KNativePointer ident)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _ident = reinterpret_cast<es2panda_AstNode*>(ident);
    auto result = GetImpl()->UpdateBreakStatement1(_context, _original, _ident);
    return result;
}
KOALA_INTEROP_3(UpdateBreakStatement1, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_BreakStatementIdentConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->BreakStatementIdentConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(BreakStatementIdentConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_BreakStatementIdent(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->BreakStatementIdent(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(BreakStatementIdent, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_BreakStatementTargetConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->BreakStatementTargetConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(BreakStatementTargetConst, KNativePointer, KNativePointer, KNativePointer);

void impl_BreakStatementSetTarget(KNativePointer context, KNativePointer receiver, KNativePointer target)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _target = reinterpret_cast<es2panda_AstNode*>(target);
    GetImpl()->BreakStatementSetTarget(_context, _receiver, _target);
    return ;
}
KOALA_INTEROP_V3(BreakStatementSetTarget, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateRegExpLiteral(KNativePointer context, KStringPtr& pattern, KInt flags, KStringPtr& flagsStr)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _pattern = getStringCopy(pattern);
    const auto _flags = static_cast<Es2pandaRegExpFlags>(flags);
    const auto _flagsStr = getStringCopy(flagsStr);
    auto result = GetImpl()->CreateRegExpLiteral(_context, _pattern, _flags, _flagsStr);
    return result;
}
KOALA_INTEROP_4(CreateRegExpLiteral, KNativePointer, KNativePointer, KStringPtr, KInt, KStringPtr);

KNativePointer impl_UpdateRegExpLiteral(KNativePointer context, KNativePointer original, KStringPtr& pattern, KInt flags, KStringPtr& flagsStr)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _pattern = getStringCopy(pattern);
    const auto _flags = static_cast<Es2pandaRegExpFlags>(flags);
    const auto _flagsStr = getStringCopy(flagsStr);
    auto result = GetImpl()->UpdateRegExpLiteral(_context, _original, _pattern, _flags, _flagsStr);
    return result;
}
KOALA_INTEROP_5(UpdateRegExpLiteral, KNativePointer, KNativePointer, KNativePointer, KStringPtr, KInt, KStringPtr);

KNativePointer impl_RegExpLiteralPatternConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->RegExpLiteralPatternConst(_context, _receiver);
    return new std::string(result);
}
KOALA_INTEROP_2(RegExpLiteralPatternConst, KNativePointer, KNativePointer, KNativePointer);

KInt impl_RegExpLiteralFlagsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->RegExpLiteralFlagsConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(RegExpLiteralFlagsConst, KInt, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSMappedType(KNativePointer context, KNativePointer typeParameter, KNativePointer typeAnnotation, KInt readonly_arg, KInt optional_arg)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _typeParameter = reinterpret_cast<es2panda_AstNode*>(typeParameter);
    const auto _typeAnnotation = reinterpret_cast<es2panda_AstNode*>(typeAnnotation);
    const auto _readonly_arg = static_cast<Es2pandaMappedOption>(readonly_arg);
    const auto _optional_arg = static_cast<Es2pandaMappedOption>(optional_arg);
    auto result = GetImpl()->CreateTSMappedType(_context, _typeParameter, _typeAnnotation, _readonly_arg, _optional_arg);
    return result;
}
KOALA_INTEROP_5(CreateTSMappedType, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KInt, KInt);

KNativePointer impl_UpdateTSMappedType(KNativePointer context, KNativePointer original, KNativePointer typeParameter, KNativePointer typeAnnotation, KInt readonly_arg, KInt optional_arg)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _typeParameter = reinterpret_cast<es2panda_AstNode*>(typeParameter);
    const auto _typeAnnotation = reinterpret_cast<es2panda_AstNode*>(typeAnnotation);
    const auto _readonly_arg = static_cast<Es2pandaMappedOption>(readonly_arg);
    const auto _optional_arg = static_cast<Es2pandaMappedOption>(optional_arg);
    auto result = GetImpl()->UpdateTSMappedType(_context, _original, _typeParameter, _typeAnnotation, _readonly_arg, _optional_arg);
    return result;
}
KOALA_INTEROP_6(UpdateTSMappedType, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KInt, KInt);

KNativePointer impl_TSMappedTypeTypeParameter(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSMappedTypeTypeParameter(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSMappedTypeTypeParameter, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSMappedTypeTypeAnnotation(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSMappedTypeTypeAnnotation(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSMappedTypeTypeAnnotation, KNativePointer, KNativePointer, KNativePointer);

KInt impl_TSMappedTypeReadonly(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSMappedTypeReadonly(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSMappedTypeReadonly, KInt, KNativePointer, KNativePointer);

KInt impl_TSMappedTypeOptional(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSMappedTypeOptional(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSMappedTypeOptional, KInt, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSAnyKeyword(KNativePointer context)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    auto result = GetImpl()->CreateTSAnyKeyword(_context);
    return result;
}
KOALA_INTEROP_1(CreateTSAnyKeyword, KNativePointer, KNativePointer);

KNativePointer impl_UpdateTSAnyKeyword(KNativePointer context, KNativePointer original)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    auto result = GetImpl()->UpdateTSAnyKeyword(_context, _original);
    return result;
}
KOALA_INTEROP_2(UpdateTSAnyKeyword, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateClassDeclaration(KNativePointer context, KNativePointer def)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _def = reinterpret_cast<es2panda_AstNode*>(def);
    auto result = GetImpl()->CreateClassDeclaration(_context, _def);
    return result;
}
KOALA_INTEROP_2(CreateClassDeclaration, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateClassDeclaration(KNativePointer context, KNativePointer original, KNativePointer def)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _def = reinterpret_cast<es2panda_AstNode*>(def);
    auto result = GetImpl()->UpdateClassDeclaration(_context, _original, _def);
    return result;
}
KOALA_INTEROP_3(UpdateClassDeclaration, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ClassDeclarationDefinition(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ClassDeclarationDefinition(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ClassDeclarationDefinition, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ClassDeclarationDefinitionConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ClassDeclarationDefinitionConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ClassDeclarationDefinitionConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ClassDeclarationDecoratorsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->ClassDeclarationDecoratorsConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(ClassDeclarationDecoratorsConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSIndexedAccessType(KNativePointer context, KNativePointer objectType, KNativePointer indexType)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _objectType = reinterpret_cast<es2panda_AstNode*>(objectType);
    const auto _indexType = reinterpret_cast<es2panda_AstNode*>(indexType);
    auto result = GetImpl()->CreateTSIndexedAccessType(_context, _objectType, _indexType);
    return result;
}
KOALA_INTEROP_3(CreateTSIndexedAccessType, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateTSIndexedAccessType(KNativePointer context, KNativePointer original, KNativePointer objectType, KNativePointer indexType)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _objectType = reinterpret_cast<es2panda_AstNode*>(objectType);
    const auto _indexType = reinterpret_cast<es2panda_AstNode*>(indexType);
    auto result = GetImpl()->UpdateTSIndexedAccessType(_context, _original, _objectType, _indexType);
    return result;
}
KOALA_INTEROP_4(UpdateTSIndexedAccessType, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSIndexedAccessTypeObjectTypeConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSIndexedAccessTypeObjectTypeConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSIndexedAccessTypeObjectTypeConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSIndexedAccessTypeIndexTypeConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSIndexedAccessTypeIndexTypeConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSIndexedAccessTypeIndexTypeConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSQualifiedName(KNativePointer context, KNativePointer left, KNativePointer right)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _left = reinterpret_cast<es2panda_AstNode*>(left);
    const auto _right = reinterpret_cast<es2panda_AstNode*>(right);
    auto result = GetImpl()->CreateTSQualifiedName(_context, _left, _right);
    return result;
}
KOALA_INTEROP_3(CreateTSQualifiedName, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateTSQualifiedName(KNativePointer context, KNativePointer original, KNativePointer left, KNativePointer right)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _left = reinterpret_cast<es2panda_AstNode*>(left);
    const auto _right = reinterpret_cast<es2panda_AstNode*>(right);
    auto result = GetImpl()->UpdateTSQualifiedName(_context, _original, _left, _right);
    return result;
}
KOALA_INTEROP_4(UpdateTSQualifiedName, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSQualifiedNameLeftConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSQualifiedNameLeftConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSQualifiedNameLeftConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSQualifiedNameLeft(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSQualifiedNameLeft(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSQualifiedNameLeft, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSQualifiedNameRightConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSQualifiedNameRightConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSQualifiedNameRightConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSQualifiedNameRight(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSQualifiedNameRight(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSQualifiedNameRight, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSQualifiedNameNameConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSQualifiedNameNameConst(_context, _receiver);
    return new std::string(result);
}
KOALA_INTEROP_2(TSQualifiedNameNameConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSQualifiedNameResolveLeftMostQualifiedName(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSQualifiedNameResolveLeftMostQualifiedName(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSQualifiedNameResolveLeftMostQualifiedName, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSQualifiedNameResolveLeftMostQualifiedNameConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSQualifiedNameResolveLeftMostQualifiedNameConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSQualifiedNameResolveLeftMostQualifiedNameConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateAwaitExpression(KNativePointer context, KNativePointer argument)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _argument = reinterpret_cast<es2panda_AstNode*>(argument);
    auto result = GetImpl()->CreateAwaitExpression(_context, _argument);
    return result;
}
KOALA_INTEROP_2(CreateAwaitExpression, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateAwaitExpression(KNativePointer context, KNativePointer original, KNativePointer argument)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _argument = reinterpret_cast<es2panda_AstNode*>(argument);
    auto result = GetImpl()->UpdateAwaitExpression(_context, _original, _argument);
    return result;
}
KOALA_INTEROP_3(UpdateAwaitExpression, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_AwaitExpressionArgumentConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->AwaitExpressionArgumentConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(AwaitExpressionArgumentConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateValidationInfo(KNativePointer context)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    auto result = GetImpl()->CreateValidationInfo(_context);
    return result;
}
KOALA_INTEROP_1(CreateValidationInfo, KNativePointer, KNativePointer);

KBoolean impl_ValidationInfoFailConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_ValidationInfo*>(receiver);
    auto result = GetImpl()->ValidationInfoFailConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ValidationInfoFailConst, KBoolean, KNativePointer, KNativePointer);

KNativePointer impl_CreateContinueStatement(KNativePointer context)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    auto result = GetImpl()->CreateContinueStatement(_context);
    return result;
}
KOALA_INTEROP_1(CreateContinueStatement, KNativePointer, KNativePointer);

KNativePointer impl_UpdateContinueStatement(KNativePointer context, KNativePointer original)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    auto result = GetImpl()->UpdateContinueStatement(_context, _original);
    return result;
}
KOALA_INTEROP_2(UpdateContinueStatement, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateContinueStatement1(KNativePointer context, KNativePointer ident)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _ident = reinterpret_cast<es2panda_AstNode*>(ident);
    auto result = GetImpl()->CreateContinueStatement1(_context, _ident);
    return result;
}
KOALA_INTEROP_2(CreateContinueStatement1, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateContinueStatement1(KNativePointer context, KNativePointer original, KNativePointer ident)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _ident = reinterpret_cast<es2panda_AstNode*>(ident);
    auto result = GetImpl()->UpdateContinueStatement1(_context, _original, _ident);
    return result;
}
KOALA_INTEROP_3(UpdateContinueStatement1, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ContinueStatementIdentConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ContinueStatementIdentConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ContinueStatementIdentConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ContinueStatementIdent(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ContinueStatementIdent(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ContinueStatementIdent, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ContinueStatementTargetConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ContinueStatementTargetConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ContinueStatementTargetConst, KNativePointer, KNativePointer, KNativePointer);

void impl_ContinueStatementSetTarget(KNativePointer context, KNativePointer receiver, KNativePointer target)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _target = reinterpret_cast<es2panda_AstNode*>(target);
    GetImpl()->ContinueStatementSetTarget(_context, _receiver, _target);
    return ;
}
KOALA_INTEROP_V3(ContinueStatementSetTarget, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateETSNewMultiDimArrayInstanceExpression(KNativePointer context, KNativePointer typeReference, KNativePointerArray dimensions, KUInt dimensionsSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _typeReference = reinterpret_cast<es2panda_AstNode*>(typeReference);
    const auto _dimensions = reinterpret_cast<es2panda_AstNode**>(dimensions);
    const auto _dimensionsSequenceLength = static_cast<KUInt>(dimensionsSequenceLength);
    auto result = GetImpl()->CreateETSNewMultiDimArrayInstanceExpression(_context, _typeReference, _dimensions, _dimensionsSequenceLength);
    return result;
}
KOALA_INTEROP_4(CreateETSNewMultiDimArrayInstanceExpression, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_UpdateETSNewMultiDimArrayInstanceExpression(KNativePointer context, KNativePointer original, KNativePointer typeReference, KNativePointerArray dimensions, KUInt dimensionsSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _typeReference = reinterpret_cast<es2panda_AstNode*>(typeReference);
    const auto _dimensions = reinterpret_cast<es2panda_AstNode**>(dimensions);
    const auto _dimensionsSequenceLength = static_cast<KUInt>(dimensionsSequenceLength);
    auto result = GetImpl()->UpdateETSNewMultiDimArrayInstanceExpression(_context, _original, _typeReference, _dimensions, _dimensionsSequenceLength);
    return result;
}
KOALA_INTEROP_5(UpdateETSNewMultiDimArrayInstanceExpression, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_CreateETSNewMultiDimArrayInstanceExpression1(KNativePointer context, KNativePointer other)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _other = reinterpret_cast<es2panda_AstNode*>(other);
    auto result = GetImpl()->CreateETSNewMultiDimArrayInstanceExpression1(_context, _other);
    return result;
}
KOALA_INTEROP_2(CreateETSNewMultiDimArrayInstanceExpression1, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateETSNewMultiDimArrayInstanceExpression1(KNativePointer context, KNativePointer original, KNativePointer other)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _other = reinterpret_cast<es2panda_AstNode*>(other);
    auto result = GetImpl()->UpdateETSNewMultiDimArrayInstanceExpression1(_context, _original, _other);
    return result;
}
KOALA_INTEROP_3(UpdateETSNewMultiDimArrayInstanceExpression1, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ETSNewMultiDimArrayInstanceExpressionTypeReference(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSNewMultiDimArrayInstanceExpressionTypeReference(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ETSNewMultiDimArrayInstanceExpressionTypeReference, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ETSNewMultiDimArrayInstanceExpressionTypeReferenceConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSNewMultiDimArrayInstanceExpressionTypeReferenceConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ETSNewMultiDimArrayInstanceExpressionTypeReferenceConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ETSNewMultiDimArrayInstanceExpressionDimensions(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->ETSNewMultiDimArrayInstanceExpressionDimensions(_context, _receiver, &length);
    return new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(ETSNewMultiDimArrayInstanceExpressionDimensions, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ETSNewMultiDimArrayInstanceExpressionDimensionsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->ETSNewMultiDimArrayInstanceExpressionDimensionsConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(ETSNewMultiDimArrayInstanceExpressionDimensionsConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSNamedTupleMember(KNativePointer context, KNativePointer label, KNativePointer elementType, KBoolean optional_arg)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _label = reinterpret_cast<es2panda_AstNode*>(label);
    const auto _elementType = reinterpret_cast<es2panda_AstNode*>(elementType);
    const auto _optional_arg = static_cast<KBoolean>(optional_arg);
    auto result = GetImpl()->CreateTSNamedTupleMember(_context, _label, _elementType, _optional_arg);
    return result;
}
KOALA_INTEROP_4(CreateTSNamedTupleMember, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KBoolean);

KNativePointer impl_UpdateTSNamedTupleMember(KNativePointer context, KNativePointer original, KNativePointer label, KNativePointer elementType, KBoolean optional_arg)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _label = reinterpret_cast<es2panda_AstNode*>(label);
    const auto _elementType = reinterpret_cast<es2panda_AstNode*>(elementType);
    const auto _optional_arg = static_cast<KBoolean>(optional_arg);
    auto result = GetImpl()->UpdateTSNamedTupleMember(_context, _original, _label, _elementType, _optional_arg);
    return result;
}
KOALA_INTEROP_5(UpdateTSNamedTupleMember, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KBoolean);

KNativePointer impl_TSNamedTupleMemberLabelConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSNamedTupleMemberLabelConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSNamedTupleMemberLabelConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSNamedTupleMemberElementType(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSNamedTupleMemberElementType(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSNamedTupleMemberElementType, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSNamedTupleMemberElementTypeConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSNamedTupleMemberElementTypeConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSNamedTupleMemberElementTypeConst, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_TSNamedTupleMemberIsOptionalConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSNamedTupleMemberIsOptionalConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSNamedTupleMemberIsOptionalConst, KBoolean, KNativePointer, KNativePointer);

KNativePointer impl_CreateImportExpression(KNativePointer context, KNativePointer source)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _source = reinterpret_cast<es2panda_AstNode*>(source);
    auto result = GetImpl()->CreateImportExpression(_context, _source);
    return result;
}
KOALA_INTEROP_2(CreateImportExpression, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateImportExpression(KNativePointer context, KNativePointer original, KNativePointer source)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _source = reinterpret_cast<es2panda_AstNode*>(source);
    auto result = GetImpl()->UpdateImportExpression(_context, _original, _source);
    return result;
}
KOALA_INTEROP_3(UpdateImportExpression, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ImportExpressionSource(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ImportExpressionSource(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ImportExpressionSource, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ImportExpressionSourceConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ImportExpressionSourceConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ImportExpressionSourceConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateAstDumper(KNativePointer context, KNativePointer node, KStringPtr& sourceCode)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _node = reinterpret_cast<es2panda_AstNode*>(node);
    const auto _sourceCode = getStringCopy(sourceCode);
    auto result = GetImpl()->CreateAstDumper(_context, _node, _sourceCode);
    return result;
}
KOALA_INTEROP_3(CreateAstDumper, KNativePointer, KNativePointer, KNativePointer, KStringPtr);

KNativePointer impl_AstDumperModifierToString(KNativePointer context, KNativePointer receiver, KInt flags)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstDumper*>(receiver);
    const auto _flags = static_cast<Es2pandaModifierFlags>(flags);
    auto result = GetImpl()->AstDumperModifierToString(_context, _receiver, _flags);
    return new std::string(result);
}
KOALA_INTEROP_3(AstDumperModifierToString, KNativePointer, KNativePointer, KNativePointer, KInt);

KNativePointer impl_AstDumperTypeOperatorToString(KNativePointer context, KNativePointer receiver, KInt operatorType)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstDumper*>(receiver);
    const auto _operatorType = static_cast<Es2pandaTSOperatorType>(operatorType);
    auto result = GetImpl()->AstDumperTypeOperatorToString(_context, _receiver, _operatorType);
    return new std::string(result);
}
KOALA_INTEROP_3(AstDumperTypeOperatorToString, KNativePointer, KNativePointer, KNativePointer, KInt);

KNativePointer impl_AstDumperStrConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstDumper*>(receiver);
    auto result = GetImpl()->AstDumperStrConst(_context, _receiver);
    return new std::string(result);
}
KOALA_INTEROP_2(AstDumperStrConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateETSNullTypeIr(KNativePointer context)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    auto result = GetImpl()->CreateETSNullTypeIr(_context);
    return result;
}
KOALA_INTEROP_1(CreateETSNullTypeIr, KNativePointer, KNativePointer);

KNativePointer impl_UpdateETSNullTypeIr(KNativePointer context, KNativePointer original)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    auto result = GetImpl()->UpdateETSNullTypeIr(_context, _original);
    return result;
}
KOALA_INTEROP_2(UpdateETSNullTypeIr, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateETSUndefinedTypeIr(KNativePointer context)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    auto result = GetImpl()->CreateETSUndefinedTypeIr(_context);
    return result;
}
KOALA_INTEROP_1(CreateETSUndefinedTypeIr, KNativePointer, KNativePointer);

KNativePointer impl_UpdateETSUndefinedTypeIr(KNativePointer context, KNativePointer original)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    auto result = GetImpl()->UpdateETSUndefinedTypeIr(_context, _original);
    return result;
}
KOALA_INTEROP_2(UpdateETSUndefinedTypeIr, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateTypeofExpression(KNativePointer context, KNativePointer argument)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _argument = reinterpret_cast<es2panda_AstNode*>(argument);
    auto result = GetImpl()->CreateTypeofExpression(_context, _argument);
    return result;
}
KOALA_INTEROP_2(CreateTypeofExpression, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateTypeofExpression(KNativePointer context, KNativePointer original, KNativePointer argument)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _argument = reinterpret_cast<es2panda_AstNode*>(argument);
    auto result = GetImpl()->UpdateTypeofExpression(_context, _original, _argument);
    return result;
}
KOALA_INTEROP_3(UpdateTypeofExpression, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TypeofExpressionArgumentConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TypeofExpressionArgumentConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TypeofExpressionArgumentConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSEnumMember(KNativePointer context, KNativePointer key, KNativePointer init)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _key = reinterpret_cast<es2panda_AstNode*>(key);
    const auto _init = reinterpret_cast<es2panda_AstNode*>(init);
    auto result = GetImpl()->CreateTSEnumMember(_context, _key, _init);
    return result;
}
KOALA_INTEROP_3(CreateTSEnumMember, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateTSEnumMember(KNativePointer context, KNativePointer original, KNativePointer key, KNativePointer init)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _key = reinterpret_cast<es2panda_AstNode*>(key);
    const auto _init = reinterpret_cast<es2panda_AstNode*>(init);
    auto result = GetImpl()->UpdateTSEnumMember(_context, _original, _key, _init);
    return result;
}
KOALA_INTEROP_4(UpdateTSEnumMember, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSEnumMember1(KNativePointer context, KNativePointer key, KNativePointer init, KBoolean isGenerated)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _key = reinterpret_cast<es2panda_AstNode*>(key);
    const auto _init = reinterpret_cast<es2panda_AstNode*>(init);
    const auto _isGenerated = static_cast<KBoolean>(isGenerated);
    auto result = GetImpl()->CreateTSEnumMember1(_context, _key, _init, _isGenerated);
    return result;
}
KOALA_INTEROP_4(CreateTSEnumMember1, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KBoolean);

KNativePointer impl_UpdateTSEnumMember1(KNativePointer context, KNativePointer original, KNativePointer key, KNativePointer init, KBoolean isGenerated)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _key = reinterpret_cast<es2panda_AstNode*>(key);
    const auto _init = reinterpret_cast<es2panda_AstNode*>(init);
    const auto _isGenerated = static_cast<KBoolean>(isGenerated);
    auto result = GetImpl()->UpdateTSEnumMember1(_context, _original, _key, _init, _isGenerated);
    return result;
}
KOALA_INTEROP_5(UpdateTSEnumMember1, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KBoolean);

KNativePointer impl_TSEnumMemberKeyConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSEnumMemberKeyConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSEnumMemberKeyConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSEnumMemberKey(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSEnumMemberKey(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSEnumMemberKey, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSEnumMemberInitConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSEnumMemberInitConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSEnumMemberInitConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSEnumMemberInit(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSEnumMemberInit(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSEnumMemberInit, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_TSEnumMemberIsGeneratedConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSEnumMemberIsGeneratedConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSEnumMemberIsGeneratedConst, KBoolean, KNativePointer, KNativePointer);

KNativePointer impl_TSEnumMemberNameConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSEnumMemberNameConst(_context, _receiver);
    return new std::string(result);
}
KOALA_INTEROP_2(TSEnumMemberNameConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateSwitchStatement(KNativePointer context, KNativePointer discriminant, KNativePointerArray cases, KUInt casesSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _discriminant = reinterpret_cast<es2panda_AstNode*>(discriminant);
    const auto _cases = reinterpret_cast<es2panda_AstNode**>(cases);
    const auto _casesSequenceLength = static_cast<KUInt>(casesSequenceLength);
    auto result = GetImpl()->CreateSwitchStatement(_context, _discriminant, _cases, _casesSequenceLength);
    return result;
}
KOALA_INTEROP_4(CreateSwitchStatement, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_UpdateSwitchStatement(KNativePointer context, KNativePointer original, KNativePointer discriminant, KNativePointerArray cases, KUInt casesSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _discriminant = reinterpret_cast<es2panda_AstNode*>(discriminant);
    const auto _cases = reinterpret_cast<es2panda_AstNode**>(cases);
    const auto _casesSequenceLength = static_cast<KUInt>(casesSequenceLength);
    auto result = GetImpl()->UpdateSwitchStatement(_context, _original, _discriminant, _cases, _casesSequenceLength);
    return result;
}
KOALA_INTEROP_5(UpdateSwitchStatement, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_SwitchStatementDiscriminantConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->SwitchStatementDiscriminantConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(SwitchStatementDiscriminantConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_SwitchStatementDiscriminant(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->SwitchStatementDiscriminant(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(SwitchStatementDiscriminant, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_SwitchStatementCasesConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->SwitchStatementCasesConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(SwitchStatementCasesConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_SwitchStatementCases(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->SwitchStatementCases(_context, _receiver, &length);
    return new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(SwitchStatementCases, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateDoWhileStatement(KNativePointer context, KNativePointer body, KNativePointer test)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _body = reinterpret_cast<es2panda_AstNode*>(body);
    const auto _test = reinterpret_cast<es2panda_AstNode*>(test);
    auto result = GetImpl()->CreateDoWhileStatement(_context, _body, _test);
    return result;
}
KOALA_INTEROP_3(CreateDoWhileStatement, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateDoWhileStatement(KNativePointer context, KNativePointer original, KNativePointer body, KNativePointer test)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _body = reinterpret_cast<es2panda_AstNode*>(body);
    const auto _test = reinterpret_cast<es2panda_AstNode*>(test);
    auto result = GetImpl()->UpdateDoWhileStatement(_context, _original, _body, _test);
    return result;
}
KOALA_INTEROP_4(UpdateDoWhileStatement, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_DoWhileStatementBodyConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->DoWhileStatementBodyConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(DoWhileStatementBodyConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_DoWhileStatementBody(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->DoWhileStatementBody(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(DoWhileStatementBody, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_DoWhileStatementTestConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->DoWhileStatementTestConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(DoWhileStatementTestConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_DoWhileStatementTest(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->DoWhileStatementTest(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(DoWhileStatementTest, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateCatchClause(KNativePointer context, KNativePointer param, KNativePointer body)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _param = reinterpret_cast<es2panda_AstNode*>(param);
    const auto _body = reinterpret_cast<es2panda_AstNode*>(body);
    auto result = GetImpl()->CreateCatchClause(_context, _param, _body);
    return result;
}
KOALA_INTEROP_3(CreateCatchClause, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateCatchClause(KNativePointer context, KNativePointer original, KNativePointer param, KNativePointer body)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _param = reinterpret_cast<es2panda_AstNode*>(param);
    const auto _body = reinterpret_cast<es2panda_AstNode*>(body);
    auto result = GetImpl()->UpdateCatchClause(_context, _original, _param, _body);
    return result;
}
KOALA_INTEROP_4(UpdateCatchClause, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CatchClauseParam(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->CatchClauseParam(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(CatchClauseParam, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CatchClauseParamConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->CatchClauseParamConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(CatchClauseParamConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CatchClauseBody(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->CatchClauseBody(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(CatchClauseBody, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CatchClauseBodyConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->CatchClauseBodyConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(CatchClauseBodyConst, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_CatchClauseIsDefaultCatchClauseConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->CatchClauseIsDefaultCatchClauseConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(CatchClauseIsDefaultCatchClauseConst, KBoolean, KNativePointer, KNativePointer);

KNativePointer impl_CreateSequenceExpression(KNativePointer context, KNativePointerArray sequence_arg, KUInt sequence_argSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _sequence_arg = reinterpret_cast<es2panda_AstNode**>(sequence_arg);
    const auto _sequence_argSequenceLength = static_cast<KUInt>(sequence_argSequenceLength);
    auto result = GetImpl()->CreateSequenceExpression(_context, _sequence_arg, _sequence_argSequenceLength);
    return result;
}
KOALA_INTEROP_3(CreateSequenceExpression, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_UpdateSequenceExpression(KNativePointer context, KNativePointer original, KNativePointerArray sequence_arg, KUInt sequence_argSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _sequence_arg = reinterpret_cast<es2panda_AstNode**>(sequence_arg);
    const auto _sequence_argSequenceLength = static_cast<KUInt>(sequence_argSequenceLength);
    auto result = GetImpl()->UpdateSequenceExpression(_context, _original, _sequence_arg, _sequence_argSequenceLength);
    return result;
}
KOALA_INTEROP_4(UpdateSequenceExpression, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_SequenceExpressionSequenceConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->SequenceExpressionSequenceConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(SequenceExpressionSequenceConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_SequenceExpressionSequence(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->SequenceExpressionSequence(_context, _receiver, &length);
    return new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(SequenceExpressionSequence, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateArrowFunctionExpression(KNativePointer context, KNativePointer func)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _func = reinterpret_cast<es2panda_AstNode*>(func);
    auto result = GetImpl()->CreateArrowFunctionExpression(_context, _func);
    return result;
}
KOALA_INTEROP_2(CreateArrowFunctionExpression, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateArrowFunctionExpression(KNativePointer context, KNativePointer original, KNativePointer func)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _func = reinterpret_cast<es2panda_AstNode*>(func);
    auto result = GetImpl()->UpdateArrowFunctionExpression(_context, _original, _func);
    return result;
}
KOALA_INTEROP_3(UpdateArrowFunctionExpression, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateArrowFunctionExpression1(KNativePointer context, KNativePointer other)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _other = reinterpret_cast<es2panda_AstNode*>(other);
    auto result = GetImpl()->CreateArrowFunctionExpression1(_context, _other);
    return result;
}
KOALA_INTEROP_2(CreateArrowFunctionExpression1, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateArrowFunctionExpression1(KNativePointer context, KNativePointer original, KNativePointer other)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _other = reinterpret_cast<es2panda_AstNode*>(other);
    auto result = GetImpl()->UpdateArrowFunctionExpression1(_context, _original, _other);
    return result;
}
KOALA_INTEROP_3(UpdateArrowFunctionExpression1, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ArrowFunctionExpressionFunctionConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ArrowFunctionExpressionFunctionConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ArrowFunctionExpressionFunctionConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ArrowFunctionExpressionFunction(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ArrowFunctionExpressionFunction(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ArrowFunctionExpressionFunction, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ArrowFunctionExpressionCreateTypeAnnotation(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ArrowFunctionExpressionCreateTypeAnnotation(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ArrowFunctionExpressionCreateTypeAnnotation, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ArrowFunctionExpressionAnnotations(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->ArrowFunctionExpressionAnnotations(_context, _receiver, &length);
    return new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(ArrowFunctionExpressionAnnotations, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ArrowFunctionExpressionAnnotationsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->ArrowFunctionExpressionAnnotationsConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(ArrowFunctionExpressionAnnotationsConst, KNativePointer, KNativePointer, KNativePointer);

void impl_ArrowFunctionExpressionSetAnnotations(KNativePointer context, KNativePointer receiver, KNativePointerArray annotations, KUInt annotationsSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _annotations = reinterpret_cast<es2panda_AstNode**>(annotations);
    const auto _annotationsSequenceLength = static_cast<KUInt>(annotationsSequenceLength);
    GetImpl()->ArrowFunctionExpressionSetAnnotations(_context, _receiver, _annotations, _annotationsSequenceLength);
    return ;
}
KOALA_INTEROP_V4(ArrowFunctionExpressionSetAnnotations, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_CreateOmittedExpression(KNativePointer context)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    auto result = GetImpl()->CreateOmittedExpression(_context);
    return result;
}
KOALA_INTEROP_1(CreateOmittedExpression, KNativePointer, KNativePointer);

KNativePointer impl_UpdateOmittedExpression(KNativePointer context, KNativePointer original)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    auto result = GetImpl()->UpdateOmittedExpression(_context, _original);
    return result;
}
KOALA_INTEROP_2(UpdateOmittedExpression, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateETSNewClassInstanceExpression(KNativePointer context, KNativePointer typeReference, KNativePointerArray _arguments, KUInt _argumentsSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _typeReference = reinterpret_cast<es2panda_AstNode*>(typeReference);
    const auto __arguments = reinterpret_cast<es2panda_AstNode**>(_arguments);
    const auto __argumentsSequenceLength = static_cast<KUInt>(_argumentsSequenceLength);
    auto result = GetImpl()->CreateETSNewClassInstanceExpression(_context, _typeReference, __arguments, __argumentsSequenceLength);
    return result;
}
KOALA_INTEROP_4(CreateETSNewClassInstanceExpression, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_UpdateETSNewClassInstanceExpression(KNativePointer context, KNativePointer original, KNativePointer typeReference, KNativePointerArray _arguments, KUInt _argumentsSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _typeReference = reinterpret_cast<es2panda_AstNode*>(typeReference);
    const auto __arguments = reinterpret_cast<es2panda_AstNode**>(_arguments);
    const auto __argumentsSequenceLength = static_cast<KUInt>(_argumentsSequenceLength);
    auto result = GetImpl()->UpdateETSNewClassInstanceExpression(_context, _original, _typeReference, __arguments, __argumentsSequenceLength);
    return result;
}
KOALA_INTEROP_5(UpdateETSNewClassInstanceExpression, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_CreateETSNewClassInstanceExpression1(KNativePointer context, KNativePointer other)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _other = reinterpret_cast<es2panda_AstNode*>(other);
    auto result = GetImpl()->CreateETSNewClassInstanceExpression1(_context, _other);
    return result;
}
KOALA_INTEROP_2(CreateETSNewClassInstanceExpression1, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateETSNewClassInstanceExpression1(KNativePointer context, KNativePointer original, KNativePointer other)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _other = reinterpret_cast<es2panda_AstNode*>(other);
    auto result = GetImpl()->UpdateETSNewClassInstanceExpression1(_context, _original, _other);
    return result;
}
KOALA_INTEROP_3(UpdateETSNewClassInstanceExpression1, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ETSNewClassInstanceExpressionGetTypeRefConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSNewClassInstanceExpressionGetTypeRefConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ETSNewClassInstanceExpressionGetTypeRefConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ETSNewClassInstanceExpressionGetArguments(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->ETSNewClassInstanceExpressionGetArguments(_context, _receiver, &length);
    return new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(ETSNewClassInstanceExpressionGetArguments, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ETSNewClassInstanceExpressionGetArgumentsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->ETSNewClassInstanceExpressionGetArgumentsConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(ETSNewClassInstanceExpressionGetArgumentsConst, KNativePointer, KNativePointer, KNativePointer);

void impl_ETSNewClassInstanceExpressionSetArguments(KNativePointer context, KNativePointer receiver, KNativePointerArray _arguments, KUInt _argumentsSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto __arguments = reinterpret_cast<es2panda_AstNode**>(_arguments);
    const auto __argumentsSequenceLength = static_cast<KUInt>(_argumentsSequenceLength);
    GetImpl()->ETSNewClassInstanceExpressionSetArguments(_context, _receiver, __arguments, __argumentsSequenceLength);
    return ;
}
KOALA_INTEROP_V4(ETSNewClassInstanceExpressionSetArguments, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

void impl_ETSNewClassInstanceExpressionAddToArgumentsFront(KNativePointer context, KNativePointer receiver, KNativePointer expr)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _expr = reinterpret_cast<es2panda_AstNode*>(expr);
    GetImpl()->ETSNewClassInstanceExpressionAddToArgumentsFront(_context, _receiver, _expr);
    return ;
}
KOALA_INTEROP_V3(ETSNewClassInstanceExpressionAddToArgumentsFront, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSAsExpression(KNativePointer context, KNativePointer expression, KNativePointer typeAnnotation, KBoolean isConst)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _expression = reinterpret_cast<es2panda_AstNode*>(expression);
    const auto _typeAnnotation = reinterpret_cast<es2panda_AstNode*>(typeAnnotation);
    const auto _isConst = static_cast<KBoolean>(isConst);
    auto result = GetImpl()->CreateTSAsExpression(_context, _expression, _typeAnnotation, _isConst);
    return result;
}
KOALA_INTEROP_4(CreateTSAsExpression, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KBoolean);

KNativePointer impl_UpdateTSAsExpression(KNativePointer context, KNativePointer original, KNativePointer expression, KNativePointer typeAnnotation, KBoolean isConst)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _expression = reinterpret_cast<es2panda_AstNode*>(expression);
    const auto _typeAnnotation = reinterpret_cast<es2panda_AstNode*>(typeAnnotation);
    const auto _isConst = static_cast<KBoolean>(isConst);
    auto result = GetImpl()->UpdateTSAsExpression(_context, _original, _expression, _typeAnnotation, _isConst);
    return result;
}
KOALA_INTEROP_5(UpdateTSAsExpression, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KBoolean);

KNativePointer impl_TSAsExpressionExprConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSAsExpressionExprConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSAsExpressionExprConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TSAsExpressionExpr(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSAsExpressionExpr(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSAsExpressionExpr, KNativePointer, KNativePointer, KNativePointer);

void impl_TSAsExpressionSetExpr(KNativePointer context, KNativePointer receiver, KNativePointer expr)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _expr = reinterpret_cast<es2panda_AstNode*>(expr);
    GetImpl()->TSAsExpressionSetExpr(_context, _receiver, _expr);
    return ;
}
KOALA_INTEROP_V3(TSAsExpressionSetExpr, KNativePointer, KNativePointer, KNativePointer);

KBoolean impl_TSAsExpressionIsConstConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSAsExpressionIsConstConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSAsExpressionIsConstConst, KBoolean, KNativePointer, KNativePointer);

void impl_TSAsExpressionSetUncheckedCast(KNativePointer context, KNativePointer receiver, KBoolean isUncheckedCast)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _isUncheckedCast = static_cast<KBoolean>(isUncheckedCast);
    GetImpl()->TSAsExpressionSetUncheckedCast(_context, _receiver, _isUncheckedCast);
    return ;
}
KOALA_INTEROP_V3(TSAsExpressionSetUncheckedCast, KNativePointer, KNativePointer, KBoolean);

KNativePointer impl_TSAsExpressionTypeAnnotationConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSAsExpressionTypeAnnotationConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSAsExpressionTypeAnnotationConst, KNativePointer, KNativePointer, KNativePointer);

void impl_TSAsExpressionSetTsTypeAnnotation(KNativePointer context, KNativePointer receiver, KNativePointer typeAnnotation)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _typeAnnotation = reinterpret_cast<es2panda_AstNode*>(typeAnnotation);
    GetImpl()->TSAsExpressionSetTsTypeAnnotation(_context, _receiver, _typeAnnotation);
    return ;
}
KOALA_INTEROP_V3(TSAsExpressionSetTsTypeAnnotation, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateForUpdateStatement(KNativePointer context, KNativePointer init, KNativePointer test, KNativePointer update, KNativePointer body)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _init = reinterpret_cast<es2panda_AstNode*>(init);
    const auto _test = reinterpret_cast<es2panda_AstNode*>(test);
    const auto _update = reinterpret_cast<es2panda_AstNode*>(update);
    const auto _body = reinterpret_cast<es2panda_AstNode*>(body);
    auto result = GetImpl()->CreateForUpdateStatement(_context, _init, _test, _update, _body);
    return result;
}
KOALA_INTEROP_5(CreateForUpdateStatement, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ForUpdateStatementInit(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ForUpdateStatementInit(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ForUpdateStatementInit, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ForUpdateStatementInitConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ForUpdateStatementInitConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ForUpdateStatementInitConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ForUpdateStatementTest(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ForUpdateStatementTest(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ForUpdateStatementTest, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ForUpdateStatementTestConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ForUpdateStatementTestConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ForUpdateStatementTestConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ForUpdateStatementUpdateConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ForUpdateStatementUpdateConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ForUpdateStatementUpdateConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ForUpdateStatementBody(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ForUpdateStatementBody(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ForUpdateStatementBody, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ForUpdateStatementBodyConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ForUpdateStatementBodyConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ForUpdateStatementBodyConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateETSTypeReferencePart(KNativePointer context, KNativePointer name, KNativePointer typeParams, KNativePointer prev)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _name = reinterpret_cast<es2panda_AstNode*>(name);
    const auto _typeParams = reinterpret_cast<es2panda_AstNode*>(typeParams);
    const auto _prev = reinterpret_cast<es2panda_AstNode*>(prev);
    auto result = GetImpl()->CreateETSTypeReferencePart(_context, _name, _typeParams, _prev);
    return result;
}
KOALA_INTEROP_4(CreateETSTypeReferencePart, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateETSTypeReferencePart(KNativePointer context, KNativePointer original, KNativePointer name, KNativePointer typeParams, KNativePointer prev)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _name = reinterpret_cast<es2panda_AstNode*>(name);
    const auto _typeParams = reinterpret_cast<es2panda_AstNode*>(typeParams);
    const auto _prev = reinterpret_cast<es2panda_AstNode*>(prev);
    auto result = GetImpl()->UpdateETSTypeReferencePart(_context, _original, _name, _typeParams, _prev);
    return result;
}
KOALA_INTEROP_5(UpdateETSTypeReferencePart, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateETSTypeReferencePart1(KNativePointer context, KNativePointer name)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _name = reinterpret_cast<es2panda_AstNode*>(name);
    auto result = GetImpl()->CreateETSTypeReferencePart1(_context, _name);
    return result;
}
KOALA_INTEROP_2(CreateETSTypeReferencePart1, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_UpdateETSTypeReferencePart1(KNativePointer context, KNativePointer original, KNativePointer name)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _name = reinterpret_cast<es2panda_AstNode*>(name);
    auto result = GetImpl()->UpdateETSTypeReferencePart1(_context, _original, _name);
    return result;
}
KOALA_INTEROP_3(UpdateETSTypeReferencePart1, KNativePointer, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ETSTypeReferencePartPrevious(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSTypeReferencePartPrevious(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ETSTypeReferencePartPrevious, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ETSTypeReferencePartPreviousConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSTypeReferencePartPreviousConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ETSTypeReferencePartPreviousConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ETSTypeReferencePartName(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSTypeReferencePartName(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ETSTypeReferencePartName, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ETSTypeReferencePartTypeParams(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSTypeReferencePartTypeParams(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ETSTypeReferencePartTypeParams, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ETSTypeReferencePartNameConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSTypeReferencePartNameConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ETSTypeReferencePartNameConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ETSReExportDeclarationGetETSImportDeclarationsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSReExportDeclarationGetETSImportDeclarationsConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ETSReExportDeclarationGetETSImportDeclarationsConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ETSReExportDeclarationGetETSImportDeclarations(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSReExportDeclarationGetETSImportDeclarations(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ETSReExportDeclarationGetETSImportDeclarations, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ETSReExportDeclarationGetProgramPathConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSReExportDeclarationGetProgramPathConst(_context, _receiver);
    return new std::string(result);
}
KOALA_INTEROP_2(ETSReExportDeclarationGetProgramPathConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateETSPrimitiveType(KNativePointer context, KInt type)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _type = static_cast<Es2pandaPrimitiveType>(type);
    auto result = GetImpl()->CreateETSPrimitiveType(_context, _type);
    return result;
}
KOALA_INTEROP_2(CreateETSPrimitiveType, KNativePointer, KNativePointer, KInt);

KNativePointer impl_UpdateETSPrimitiveType(KNativePointer context, KNativePointer original, KInt type)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _type = static_cast<Es2pandaPrimitiveType>(type);
    auto result = GetImpl()->UpdateETSPrimitiveType(_context, _original, _type);
    return result;
}
KOALA_INTEROP_3(UpdateETSPrimitiveType, KNativePointer, KNativePointer, KNativePointer, KInt);

KInt impl_ETSPrimitiveTypeGetPrimitiveTypeConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSPrimitiveTypeGetPrimitiveTypeConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ETSPrimitiveTypeGetPrimitiveTypeConst, KInt, KNativePointer, KNativePointer);

KNativePointer impl_TypeNodeAnnotations(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->TypeNodeAnnotations(_context, _receiver, &length);
    return new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(TypeNodeAnnotations, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_TypeNodeAnnotationsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->TypeNodeAnnotationsConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(TypeNodeAnnotationsConst, KNativePointer, KNativePointer, KNativePointer);

void impl_TypeNodeSetAnnotations(KNativePointer context, KNativePointer receiver, KNativePointerArray annotations, KUInt annotationsSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    const auto _annotations = reinterpret_cast<es2panda_AstNode**>(annotations);
    const auto _annotationsSequenceLength = static_cast<KUInt>(annotationsSequenceLength);
    GetImpl()->TypeNodeSetAnnotations(_context, _receiver, _annotations, _annotationsSequenceLength);
    return ;
}
KOALA_INTEROP_V4(TypeNodeSetAnnotations, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_CreateNewExpression(KNativePointer context, KNativePointer callee, KNativePointerArray _arguments, KUInt _argumentsSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _callee = reinterpret_cast<es2panda_AstNode*>(callee);
    const auto __arguments = reinterpret_cast<es2panda_AstNode**>(_arguments);
    const auto __argumentsSequenceLength = static_cast<KUInt>(_argumentsSequenceLength);
    auto result = GetImpl()->CreateNewExpression(_context, _callee, __arguments, __argumentsSequenceLength);
    return result;
}
KOALA_INTEROP_4(CreateNewExpression, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_UpdateNewExpression(KNativePointer context, KNativePointer original, KNativePointer callee, KNativePointerArray _arguments, KUInt _argumentsSequenceLength)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _callee = reinterpret_cast<es2panda_AstNode*>(callee);
    const auto __arguments = reinterpret_cast<es2panda_AstNode**>(_arguments);
    const auto __argumentsSequenceLength = static_cast<KUInt>(_argumentsSequenceLength);
    auto result = GetImpl()->UpdateNewExpression(_context, _original, _callee, __arguments, __argumentsSequenceLength);
    return result;
}
KOALA_INTEROP_5(UpdateNewExpression, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KUInt);

KNativePointer impl_NewExpressionCalleeConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->NewExpressionCalleeConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(NewExpressionCalleeConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_NewExpressionArgumentsConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    std::size_t length;
    auto result = GetImpl()->NewExpressionArgumentsConst(_context, _receiver, &length);
    return (void*)new std::vector<void*>(result, result + length);
}
KOALA_INTEROP_2(NewExpressionArgumentsConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSParameterProperty(KNativePointer context, KInt accessibility, KNativePointer parameter, KBoolean readonly_arg, KBoolean isStatic, KBoolean isExport)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _accessibility = static_cast<Es2pandaAccessibilityOption>(accessibility);
    const auto _parameter = reinterpret_cast<es2panda_AstNode*>(parameter);
    const auto _readonly_arg = static_cast<KBoolean>(readonly_arg);
    const auto _isStatic = static_cast<KBoolean>(isStatic);
    const auto _isExport = static_cast<KBoolean>(isExport);
    auto result = GetImpl()->CreateTSParameterProperty(_context, _accessibility, _parameter, _readonly_arg, _isStatic, _isExport);
    return result;
}
KOALA_INTEROP_6(CreateTSParameterProperty, KNativePointer, KNativePointer, KInt, KNativePointer, KBoolean, KBoolean, KBoolean);

KNativePointer impl_UpdateTSParameterProperty(KNativePointer context, KNativePointer original, KInt accessibility, KNativePointer parameter, KBoolean readonly_arg, KBoolean isStatic, KBoolean isExport)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _accessibility = static_cast<Es2pandaAccessibilityOption>(accessibility);
    const auto _parameter = reinterpret_cast<es2panda_AstNode*>(parameter);
    const auto _readonly_arg = static_cast<KBoolean>(readonly_arg);
    const auto _isStatic = static_cast<KBoolean>(isStatic);
    const auto _isExport = static_cast<KBoolean>(isExport);
    auto result = GetImpl()->UpdateTSParameterProperty(_context, _original, _accessibility, _parameter, _readonly_arg, _isStatic, _isExport);
    return result;
}
KOALA_INTEROP_7(UpdateTSParameterProperty, KNativePointer, KNativePointer, KNativePointer, KInt, KNativePointer, KBoolean, KBoolean, KBoolean);

KInt impl_TSParameterPropertyAccessibilityConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSParameterPropertyAccessibilityConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSParameterPropertyAccessibilityConst, KInt, KNativePointer, KNativePointer);

KBoolean impl_TSParameterPropertyReadonlyConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSParameterPropertyReadonlyConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSParameterPropertyReadonlyConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_TSParameterPropertyIsStaticConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSParameterPropertyIsStaticConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSParameterPropertyIsStaticConst, KBoolean, KNativePointer, KNativePointer);

KBoolean impl_TSParameterPropertyIsExportConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSParameterPropertyIsExportConst(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(TSParameterPropertyIsExportConst, KBoolean, KNativePointer, KNativePointer);

KNativePointer impl_TSParameterPropertyParameterConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->TSParameterPropertyParameterConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(TSParameterPropertyParameterConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateETSWildcardType(KNativePointer context, KNativePointer typeReference, KInt flags)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _typeReference = reinterpret_cast<es2panda_AstNode*>(typeReference);
    const auto _flags = static_cast<Es2pandaModifierFlags>(flags);
    auto result = GetImpl()->CreateETSWildcardType(_context, _typeReference, _flags);
    return result;
}
KOALA_INTEROP_3(CreateETSWildcardType, KNativePointer, KNativePointer, KNativePointer, KInt);

KNativePointer impl_UpdateETSWildcardType(KNativePointer context, KNativePointer original, KNativePointer typeReference, KInt flags)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    const auto _typeReference = reinterpret_cast<es2panda_AstNode*>(typeReference);
    const auto _flags = static_cast<Es2pandaModifierFlags>(flags);
    auto result = GetImpl()->UpdateETSWildcardType(_context, _original, _typeReference, _flags);
    return result;
}
KOALA_INTEROP_4(UpdateETSWildcardType, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KInt);

KNativePointer impl_ETSWildcardTypeTypeReference(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSWildcardTypeTypeReference(_context, _receiver);
    return result;
}
KOALA_INTEROP_2(ETSWildcardTypeTypeReference, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_ETSWildcardTypeTypeReferenceConst(KNativePointer context, KNativePointer receiver)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _receiver = reinterpret_cast<es2panda_AstNode*>(receiver);
    auto result = GetImpl()->ETSWildcardTypeTypeReferenceConst(_context, _receiver);
    return (void*)result;
}
KOALA_INTEROP_2(ETSWildcardTypeTypeReferenceConst, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateTSThisType(KNativePointer context)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    auto result = GetImpl()->CreateTSThisType(_context);
    return result;
}
KOALA_INTEROP_1(CreateTSThisType, KNativePointer, KNativePointer);

KNativePointer impl_UpdateTSThisType(KNativePointer context, KNativePointer original)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _original = reinterpret_cast<es2panda_AstNode*>(original);
    auto result = GetImpl()->UpdateTSThisType(_context, _original);
    return result;
}
KOALA_INTEROP_2(UpdateTSThisType, KNativePointer, KNativePointer, KNativePointer);

KNativePointer impl_CreateInterfaceDecl(KNativePointer context, KStringPtr& name)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _name = getStringCopy(name);
    auto result = GetImpl()->CreateInterfaceDecl(_context, _name);
    return result;
}
KOALA_INTEROP_2(CreateInterfaceDecl, KNativePointer, KNativePointer, KStringPtr);

KNativePointer impl_CreateInterfaceDecl1(KNativePointer context, KStringPtr& name, KNativePointer declNode)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _name = getStringCopy(name);
    const auto _declNode = reinterpret_cast<es2panda_AstNode*>(declNode);
    auto result = GetImpl()->CreateInterfaceDecl1(_context, _name, _declNode);
    return result;
}
KOALA_INTEROP_3(CreateInterfaceDecl1, KNativePointer, KNativePointer, KStringPtr, KNativePointer);

KNativePointer impl_CreateFunctionDecl(KNativePointer context, KStringPtr& name, KNativePointer node)
{
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _name = getStringCopy(name);
    const auto _node = reinterpret_cast<es2panda_AstNode*>(node);
    auto result = GetImpl()->CreateFunctionDecl(_context, _name, _node);
    return result;
}
KOALA_INTEROP_3(CreateFunctionDecl, KNativePointer, KNativePointer, KStringPtr, KNativePointer);

