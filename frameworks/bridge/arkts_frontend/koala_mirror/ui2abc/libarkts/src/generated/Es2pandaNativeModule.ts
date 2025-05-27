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
    KNativePointer,
    KStringPtr,
    KUInt,
    KInt,
    KBoolean,
    KDouble,
    KFloat,
    KLong
} from "@koalaui/interop"

// TODO: this type should be in interop
export type KNativePointerArray = BigUint64Array

export class Es2pandaNativeModule {
    _CreateNumberLiteral(context: KNativePointer, value: KInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateNumberLiteral1(context: KNativePointer, value: KLong): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateNumberLiteral2(context: KNativePointer, value: KDouble): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateNumberLiteral3(context: KNativePointer, value: KFloat): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateNumberLiteral(context: KNativePointer, original: KNativePointer, value: KInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateNumberLiteral1(context: KNativePointer, original: KNativePointer, value: KLong): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateNumberLiteral2(context: KNativePointer, original: KNativePointer, value: KDouble): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateNumberLiteral3(context: KNativePointer, original: KNativePointer, value: KFloat): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _NumberLiteralStrConst(context: KNativePointer, receiver: KNativePointer): KStringPtr {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateLabelledStatement(context: KNativePointer, ident: KNativePointer, body: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateLabelledStatement(context: KNativePointer, original: KNativePointer, ident: KNativePointer, body: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _LabelledStatementBody(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _LabelledStatementBodyConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _LabelledStatementIdentConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _LabelledStatementIdent(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _LabelledStatementGetReferencedStatementConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateThrowStatement(context: KNativePointer, argument: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateThrowStatement(context: KNativePointer, original: KNativePointer, argument: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ThrowStatementArgumentConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateClassProperty(context: KNativePointer, key: KNativePointer, value: KNativePointer, typeAnnotation: KNativePointer, modifiers: KInt, isComputed: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateClassProperty(context: KNativePointer, original: KNativePointer, key: KNativePointer, value: KNativePointer, typeAnnotation: KNativePointer, modifiers: KInt, isComputed: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassPropertyIsDefaultAccessModifierConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassPropertySetDefaultAccessModifier(context: KNativePointer, receiver: KNativePointer, isDefault: KBoolean): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassPropertyTypeAnnotationConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassPropertySetTypeAnnotation(context: KNativePointer, receiver: KNativePointer, typeAnnotation: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassPropertyNeedInitInStaticBlockConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassPropertySetInitInStaticBlock(context: KNativePointer, receiver: KNativePointer, needInitInStaticBlock: KBoolean): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassPropertyAnnotations(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassPropertyAnnotationsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassPropertySetAnnotations(context: KNativePointer, receiver: KNativePointer, annotations: BigUint64Array, annotationsSequenceLength: KUInt): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSVoidKeyword(context: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSVoidKeyword(context: KNativePointer, original: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateETSFunctionType(context: KNativePointer, signature: KNativePointer, funcFlags: KInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateETSFunctionType(context: KNativePointer, original: KNativePointer, signature: KNativePointer, funcFlags: KInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSFunctionTypeTypeParamsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSFunctionTypeTypeParams(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSFunctionTypeParamsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSFunctionTypeReturnTypeConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSFunctionTypeReturnType(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSFunctionTypeFunctionalInterface(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSFunctionTypeFunctionalInterfaceConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSFunctionTypeSetFunctionalInterface(context: KNativePointer, receiver: KNativePointer, functionalInterface: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSFunctionTypeFlags(context: KNativePointer, receiver: KNativePointer): KInt {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSFunctionTypeIsThrowingConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSFunctionTypeIsRethrowingConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSFunctionTypeIsExtensionFunctionConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSTypeOperator(context: KNativePointer, type: KNativePointer, operatorType: KInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSTypeOperator(context: KNativePointer, original: KNativePointer, type: KNativePointer, operatorType: KInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSTypeOperatorTypeConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSTypeOperatorIsReadonlyConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSTypeOperatorIsKeyofConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSTypeOperatorIsUniqueConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateIfStatement(context: KNativePointer, test: KNativePointer, consequent: KNativePointer, alternate: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateIfStatement(context: KNativePointer, original: KNativePointer, test: KNativePointer, consequent: KNativePointer, alternate: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _IfStatementTestConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _IfStatementTest(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _IfStatementConsequentConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _IfStatementConsequent(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _IfStatementAlternate(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _IfStatementAlternateConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _IfStatementSetAlternate(context: KNativePointer, receiver: KNativePointer, alternate: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSConstructorType(context: KNativePointer, signature: KNativePointer, abstract: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSConstructorType(context: KNativePointer, original: KNativePointer, signature: KNativePointer, abstract: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSConstructorTypeTypeParamsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSConstructorTypeTypeParams(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSConstructorTypeParamsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSConstructorTypeReturnTypeConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSConstructorTypeReturnType(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSConstructorTypeAbstractConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateDecorator(context: KNativePointer, expr: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateDecorator(context: KNativePointer, original: KNativePointer, expr: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _DecoratorExprConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSEnumDeclaration(context: KNativePointer, key: KNativePointer, members: BigUint64Array, membersSequenceLength: KUInt, isConst: KBoolean, isStatic: KBoolean, isDeclare: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSEnumDeclaration(context: KNativePointer, original: KNativePointer, key: KNativePointer, members: BigUint64Array, membersSequenceLength: KUInt, isConst: KBoolean, isStatic: KBoolean, isDeclare: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSEnumDeclarationKeyConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSEnumDeclarationKey(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSEnumDeclarationMembersConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSEnumDeclarationInternalNameConst(context: KNativePointer, receiver: KNativePointer): KStringPtr {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSEnumDeclarationSetInternalName(context: KNativePointer, receiver: KNativePointer, internalName: KStringPtr): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSEnumDeclarationBoxedClassConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSEnumDeclarationSetBoxedClass(context: KNativePointer, receiver: KNativePointer, wrapperClass: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSEnumDeclarationIsConstConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSEnumDeclarationDecoratorsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSNeverKeyword(context: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSNeverKeyword(context: KNativePointer, original: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateImportDefaultSpecifier(context: KNativePointer, local: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateImportDefaultSpecifier(context: KNativePointer, original: KNativePointer, local: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ImportDefaultSpecifierLocalConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ImportDefaultSpecifierLocal(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateObjectExpression(context: KNativePointer, nodeType: KInt, properties: BigUint64Array, propertiesSequenceLength: KUInt, trailingComma: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateObjectExpression(context: KNativePointer, original: KNativePointer, nodeType: KInt, properties: BigUint64Array, propertiesSequenceLength: KUInt, trailingComma: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ObjectExpressionPropertiesConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ObjectExpressionIsDeclarationConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ObjectExpressionIsOptionalConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ObjectExpressionDecoratorsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ObjectExpressionValidateExpression(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ObjectExpressionConvertibleToObjectPattern(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ObjectExpressionSetDeclaration(context: KNativePointer, receiver: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ObjectExpressionSetOptional(context: KNativePointer, receiver: KNativePointer, optional_arg: KBoolean): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ObjectExpressionTypeAnnotationConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ObjectExpressionSetTsTypeAnnotation(context: KNativePointer, receiver: KNativePointer, typeAnnotation: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateImportSpecifier(context: KNativePointer, imported: KNativePointer, local: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateImportSpecifier(context: KNativePointer, original: KNativePointer, imported: KNativePointer, local: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ImportSpecifierImported(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ImportSpecifierImportedConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ImportSpecifierLocal(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ImportSpecifierLocalConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ImportSpecifierIsRemovableConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ImportSpecifierSetRemovable(context: KNativePointer, receiver: KNativePointer, isRemovable: KBoolean): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateConditionalExpression(context: KNativePointer, test: KNativePointer, consequent: KNativePointer, alternate: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateConditionalExpression(context: KNativePointer, original: KNativePointer, test: KNativePointer, consequent: KNativePointer, alternate: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ConditionalExpressionTestConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ConditionalExpressionTest(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ConditionalExpressionSetTest(context: KNativePointer, receiver: KNativePointer, expr: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ConditionalExpressionConsequentConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ConditionalExpressionConsequent(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ConditionalExpressionSetConsequent(context: KNativePointer, receiver: KNativePointer, expr: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ConditionalExpressionAlternateConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ConditionalExpressionAlternate(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ConditionalExpressionSetAlternate(context: KNativePointer, receiver: KNativePointer, expr: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateCallExpression(context: KNativePointer, callee: KNativePointer, _arguments: BigUint64Array, _argumentsSequenceLength: KUInt, typeParams: KNativePointer, optional_arg: KBoolean, trailingComma: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateCallExpression1(context: KNativePointer, other: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateCallExpression1(context: KNativePointer, original: KNativePointer, other: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CallExpressionCalleeConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CallExpressionCallee(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CallExpressionSetCallee(context: KNativePointer, receiver: KNativePointer, callee: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CallExpressionTypeParamsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CallExpressionTypeParams(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CallExpressionArgumentsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CallExpressionArguments(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CallExpressionHasTrailingCommaConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CallExpressionSetTypeParams(context: KNativePointer, receiver: KNativePointer, typeParams: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CallExpressionSetTrailingBlock(context: KNativePointer, receiver: KNativePointer, block: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CallExpressionIsExtensionAccessorCall(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CallExpressionTrailingBlockConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CallExpressionSetIsTrailingBlockInNewLine(context: KNativePointer, receiver: KNativePointer, isNewLine: KBoolean): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CallExpressionIsTrailingBlockInNewLineConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CallExpressionSetIsTrailingCall(context: KNativePointer, receiver: KNativePointer, isTrailingCall: KBoolean): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CallExpressionIsTrailingCallConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CallExpressionIsETSConstructorCallConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateBigIntLiteral(context: KNativePointer, src: KStringPtr): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateBigIntLiteral(context: KNativePointer, original: KNativePointer, src: KStringPtr): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _BigIntLiteralStrConst(context: KNativePointer, receiver: KNativePointer): KStringPtr {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassElementId(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassElementIdConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassElementKey(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassElementKeyConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassElementValue(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassElementSetValue(context: KNativePointer, receiver: KNativePointer, value: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassElementValueConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassElementOriginEnumMemberConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassElementSetOrigEnumMember(context: KNativePointer, receiver: KNativePointer, enumMember: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassElementIsPrivateElementConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassElementDecoratorsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassElementIsComputedConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassElementAddDecorator(context: KNativePointer, receiver: KNativePointer, decorator: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassElementToPrivateFieldKindConst(context: KNativePointer, receiver: KNativePointer, isStatic: KBoolean): KInt {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSImportType(context: KNativePointer, param: KNativePointer, typeParams: KNativePointer, qualifier: KNativePointer, isTypeof: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSImportType(context: KNativePointer, original: KNativePointer, param: KNativePointer, typeParams: KNativePointer, qualifier: KNativePointer, isTypeof: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSImportTypeParamConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSImportTypeTypeParamsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSImportTypeQualifierConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSImportTypeIsTypeofConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTaggedTemplateExpression(context: KNativePointer, tag: KNativePointer, quasi: KNativePointer, typeParams: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTaggedTemplateExpression(context: KNativePointer, original: KNativePointer, tag: KNativePointer, quasi: KNativePointer, typeParams: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TaggedTemplateExpressionTagConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TaggedTemplateExpressionQuasiConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TaggedTemplateExpressionTypeParamsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateFunctionDeclaration(context: KNativePointer, func: KNativePointer, annotations: BigUint64Array, annotationsSequenceLength: KUInt, isAnonymous: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateFunctionDeclaration(context: KNativePointer, original: KNativePointer, func: KNativePointer, annotations: BigUint64Array, annotationsSequenceLength: KUInt, isAnonymous: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateFunctionDeclaration1(context: KNativePointer, func: KNativePointer, isAnonymous: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateFunctionDeclaration1(context: KNativePointer, original: KNativePointer, func: KNativePointer, isAnonymous: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _FunctionDeclarationFunction(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _FunctionDeclarationIsAnonymousConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _FunctionDeclarationFunctionConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _FunctionDeclarationAnnotations(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _FunctionDeclarationAnnotationsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _FunctionDeclarationSetAnnotations(context: KNativePointer, receiver: KNativePointer, annotations: BigUint64Array, annotationsSequenceLength: KUInt): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateETSTypeReference(context: KNativePointer, part: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateETSTypeReference(context: KNativePointer, original: KNativePointer, part: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSTypeReferencePart(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSTypeReferencePartConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSTypeReferenceBaseNameConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSTypeReference(context: KNativePointer, typeName: KNativePointer, typeParams: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSTypeReference(context: KNativePointer, original: KNativePointer, typeName: KNativePointer, typeParams: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSTypeReferenceTypeParamsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSTypeReferenceTypeNameConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSTypeReferenceBaseNameConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateNamedType(context: KNativePointer, name: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateNamedType(context: KNativePointer, original: KNativePointer, name: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _NamedTypeNameConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _NamedTypeTypeParamsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _NamedTypeIsNullableConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _NamedTypeSetNullable(context: KNativePointer, receiver: KNativePointer, nullable: KBoolean): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _NamedTypeSetNext(context: KNativePointer, receiver: KNativePointer, next: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _NamedTypeSetTypeParams(context: KNativePointer, receiver: KNativePointer, typeParams: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSFunctionType(context: KNativePointer, signature: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSFunctionType(context: KNativePointer, original: KNativePointer, signature: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSFunctionTypeTypeParamsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSFunctionTypeTypeParams(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSFunctionTypeParamsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSFunctionTypeReturnTypeConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSFunctionTypeReturnType(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSFunctionTypeSetNullable(context: KNativePointer, receiver: KNativePointer, nullable: KBoolean): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTemplateElement(context: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTemplateElement(context: KNativePointer, original: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTemplateElement1(context: KNativePointer, raw: KStringPtr, cooked: KStringPtr): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTemplateElement1(context: KNativePointer, original: KNativePointer, raw: KStringPtr, cooked: KStringPtr): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TemplateElementRawConst(context: KNativePointer, receiver: KNativePointer): KStringPtr {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TemplateElementCookedConst(context: KNativePointer, receiver: KNativePointer): KStringPtr {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSInterfaceDeclaration(context: KNativePointer, _extends: BigUint64Array, _extendsSequenceLength: KUInt, id: KNativePointer, typeParams: KNativePointer, body: KNativePointer, isStatic: KBoolean, isExternal: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSInterfaceDeclaration(context: KNativePointer, original: KNativePointer, _extends: BigUint64Array, _extendsSequenceLength: KUInt, id: KNativePointer, typeParams: KNativePointer, body: KNativePointer, isStatic: KBoolean, isExternal: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSInterfaceDeclarationBody(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSInterfaceDeclarationBodyConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSInterfaceDeclarationId(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSInterfaceDeclarationIdConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSInterfaceDeclarationInternalNameConst(context: KNativePointer, receiver: KNativePointer): KStringPtr {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSInterfaceDeclarationSetInternalName(context: KNativePointer, receiver: KNativePointer, internalName: KStringPtr): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSInterfaceDeclarationIsStaticConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSInterfaceDeclarationIsFromExternalConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSInterfaceDeclarationTypeParamsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSInterfaceDeclarationTypeParams(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSInterfaceDeclarationExtends(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSInterfaceDeclarationExtendsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSInterfaceDeclarationDecoratorsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSInterfaceDeclarationGetAnonClass(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSInterfaceDeclarationGetAnonClassConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSInterfaceDeclarationSetAnonClass(context: KNativePointer, receiver: KNativePointer, anonClass: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSInterfaceDeclarationAnnotations(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSInterfaceDeclarationAnnotationsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSInterfaceDeclarationSetAnnotations(context: KNativePointer, receiver: KNativePointer, annotations: BigUint64Array, annotationsSequenceLength: KUInt): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateVariableDeclaration(context: KNativePointer, kind: KInt, declarators: BigUint64Array, declaratorsSequenceLength: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateVariableDeclaration(context: KNativePointer, original: KNativePointer, kind: KInt, declarators: BigUint64Array, declaratorsSequenceLength: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _VariableDeclarationDeclaratorsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _VariableDeclarationKindConst(context: KNativePointer, receiver: KNativePointer): KInt {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _VariableDeclarationDecoratorsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _VariableDeclarationGetDeclaratorByNameConst(context: KNativePointer, receiver: KNativePointer, name: KStringPtr): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _VariableDeclarationAnnotations(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _VariableDeclarationAnnotationsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _VariableDeclarationSetAnnotations(context: KNativePointer, receiver: KNativePointer, annotations: BigUint64Array, annotationsSequenceLength: KUInt): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateUndefinedLiteral(context: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateUndefinedLiteral(context: KNativePointer, original: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateMemberExpression(context: KNativePointer, object_arg: KNativePointer, property: KNativePointer, kind: KInt, computed: KBoolean, optional_arg: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateMemberExpression(context: KNativePointer, original: KNativePointer, object_arg: KNativePointer, property: KNativePointer, kind: KInt, computed: KBoolean, optional_arg: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _MemberExpressionObject(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _MemberExpressionObjectConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _MemberExpressionSetObject(context: KNativePointer, receiver: KNativePointer, object_arg: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _MemberExpressionSetProperty(context: KNativePointer, receiver: KNativePointer, prop: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _MemberExpressionProperty(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _MemberExpressionPropertyConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _MemberExpressionIsComputedConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _MemberExpressionKindConst(context: KNativePointer, receiver: KNativePointer): KInt {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _MemberExpressionAddMemberKind(context: KNativePointer, receiver: KNativePointer, kind: KInt): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _MemberExpressionHasMemberKindConst(context: KNativePointer, receiver: KNativePointer, kind: KInt): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _MemberExpressionRemoveMemberKind(context: KNativePointer, receiver: KNativePointer, kind: KInt): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _MemberExpressionExtensionAccessorTypeConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _MemberExpressionIsIgnoreBoxConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _MemberExpressionSetIgnoreBox(context: KNativePointer, receiver: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _MemberExpressionIsPrivateReferenceConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _MemberExpressionCompileToRegConst(context: KNativePointer, receiver: KNativePointer, pg: KNativePointer, objReg: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _MemberExpressionCompileToRegsConst(context: KNativePointer, receiver: KNativePointer, pg: KNativePointer, object_arg: KNativePointer, property: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSClassImplements(context: KNativePointer, expression: KNativePointer, typeParameters: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSClassImplements(context: KNativePointer, original: KNativePointer, expression: KNativePointer, typeParameters: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSClassImplements1(context: KNativePointer, expression: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSClassImplements1(context: KNativePointer, original: KNativePointer, expression: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSClassImplementsExpr(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSClassImplementsExprConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSClassImplementsTypeParametersConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSObjectKeyword(context: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSObjectKeyword(context: KNativePointer, original: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateETSUnionType(context: KNativePointer, types: BigUint64Array, typesSequenceLength: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateETSUnionType(context: KNativePointer, original: KNativePointer, types: BigUint64Array, typesSequenceLength: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSUnionTypeTypesConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateETSKeyofType(context: KNativePointer, type: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateETSKeyofType(context: KNativePointer, original: KNativePointer, type: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSKeyofTypeGetTypeRefConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSPropertySignature(context: KNativePointer, key: KNativePointer, typeAnnotation: KNativePointer, computed: KBoolean, optional_arg: KBoolean, readonly_arg: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSPropertySignature(context: KNativePointer, original: KNativePointer, key: KNativePointer, typeAnnotation: KNativePointer, computed: KBoolean, optional_arg: KBoolean, readonly_arg: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSPropertySignatureKeyConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSPropertySignatureKey(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSPropertySignatureComputedConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSPropertySignatureOptionalConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSPropertySignatureReadonlyConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSPropertySignatureTypeAnnotationConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSPropertySignatureSetTsTypeAnnotation(context: KNativePointer, receiver: KNativePointer, typeAnnotation: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSConditionalType(context: KNativePointer, checkType: KNativePointer, extendsType: KNativePointer, trueType: KNativePointer, falseType: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSConditionalType(context: KNativePointer, original: KNativePointer, checkType: KNativePointer, extendsType: KNativePointer, trueType: KNativePointer, falseType: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSConditionalTypeCheckTypeConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSConditionalTypeExtendsTypeConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSConditionalTypeTrueTypeConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSConditionalTypeFalseTypeConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSLiteralType(context: KNativePointer, literal: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSLiteralType(context: KNativePointer, original: KNativePointer, literal: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSLiteralTypeLiteralConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSTypeAliasDeclaration(context: KNativePointer, id: KNativePointer, typeParams: KNativePointer, typeAnnotation: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSTypeAliasDeclaration(context: KNativePointer, original: KNativePointer, id: KNativePointer, typeParams: KNativePointer, typeAnnotation: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSTypeAliasDeclaration1(context: KNativePointer, id: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSTypeAliasDeclaration1(context: KNativePointer, original: KNativePointer, id: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSTypeAliasDeclarationId(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSTypeAliasDeclarationIdConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSTypeAliasDeclarationTypeParamsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSTypeAliasDeclarationDecoratorsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSTypeAliasDeclarationSetTypeParameters(context: KNativePointer, receiver: KNativePointer, typeParams: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSTypeAliasDeclarationAnnotations(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSTypeAliasDeclarationAnnotationsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSTypeAliasDeclarationSetAnnotations(context: KNativePointer, receiver: KNativePointer, annotations: BigUint64Array, annotationsSequenceLength: KUInt): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSTypeAliasDeclarationTypeAnnotationConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSTypeAliasDeclarationSetTsTypeAnnotation(context: KNativePointer, receiver: KNativePointer, typeAnnotation: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateDebuggerStatement(context: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateDebuggerStatement(context: KNativePointer, original: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateReturnStatement(context: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateReturnStatement(context: KNativePointer, original: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateReturnStatement1(context: KNativePointer, argument: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateReturnStatement1(context: KNativePointer, original: KNativePointer, argument: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ReturnStatementArgument(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ReturnStatementArgumentConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ReturnStatementSetArgument(context: KNativePointer, receiver: KNativePointer, arg: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ReturnStatementIsAsyncImplReturnConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateExportDefaultDeclaration(context: KNativePointer, decl: KNativePointer, exportEquals: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateExportDefaultDeclaration(context: KNativePointer, original: KNativePointer, decl: KNativePointer, exportEquals: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ExportDefaultDeclarationDecl(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ExportDefaultDeclarationDeclConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ExportDefaultDeclarationIsExportEqualsConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateScriptFunction(context: KNativePointer, databody: KNativePointer, datasignature: KNativePointer, datafuncFlags: KInt, dataflags: KInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateScriptFunction(context: KNativePointer, original: KNativePointer, databody: KNativePointer, datasignature: KNativePointer, datafuncFlags: KInt, dataflags: KInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionIdConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionId(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionParamsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionParams(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionReturnStatementsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionReturnStatements(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionTypeParamsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionTypeParams(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionBodyConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionBody(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionAddReturnStatement(context: KNativePointer, receiver: KNativePointer, returnStatement: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionSetBody(context: KNativePointer, receiver: KNativePointer, body: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionReturnTypeAnnotationConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionReturnTypeAnnotation(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionSetReturnTypeAnnotation(context: KNativePointer, receiver: KNativePointer, node: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionIsEntryPointConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionIsGeneratorConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionIsAsyncFuncConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionIsAsyncImplFuncConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionIsArrowConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionIsOverloadConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionIsExternalOverloadConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionIsConstructorConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionIsGetterConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionIsSetterConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionIsExtensionAccessorConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionIsMethodConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionIsProxyConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionIsStaticBlockConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionIsEnumConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionIsHiddenConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionIsExternalConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionIsImplicitSuperCallNeededConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionHasBodyConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionHasRestParameterConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionHasReturnStatementConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionHasThrowStatementConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionIsThrowingConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionIsRethrowingConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionIsDynamicConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionIsExtensionMethodConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionFlagsConst(context: KNativePointer, receiver: KNativePointer): KInt {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionHasReceiverConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionSetIdent(context: KNativePointer, receiver: KNativePointer, id: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionAddFlag(context: KNativePointer, receiver: KNativePointer, flags: KInt): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionClearFlag(context: KNativePointer, receiver: KNativePointer, flags: KInt): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionAddModifier(context: KNativePointer, receiver: KNativePointer, flags: KInt): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionFormalParamsLengthConst(context: KNativePointer, receiver: KNativePointer): KUInt {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionSetIsolatedDeclgenReturnType(context: KNativePointer, receiver: KNativePointer, type: KStringPtr): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionGetIsolatedDeclgenReturnTypeConst(context: KNativePointer, receiver: KNativePointer): KStringPtr {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionAnnotations(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionAnnotationsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ScriptFunctionSetAnnotations(context: KNativePointer, receiver: KNativePointer, annotations: BigUint64Array, annotationsSequenceLength: KUInt): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateClassDefinition(context: KNativePointer, ident: KNativePointer, typeParams: KNativePointer, superTypeParams: KNativePointer, _implements: BigUint64Array, _implementsSequenceLength: KUInt, ctor: KNativePointer, superClass: KNativePointer, body: BigUint64Array, bodySequenceLength: KUInt, modifiers: KInt, flags: KInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateClassDefinition(context: KNativePointer, original: KNativePointer, ident: KNativePointer, typeParams: KNativePointer, superTypeParams: KNativePointer, _implements: BigUint64Array, _implementsSequenceLength: KUInt, ctor: KNativePointer, superClass: KNativePointer, body: BigUint64Array, bodySequenceLength: KUInt, modifiers: KInt, flags: KInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateClassDefinition1(context: KNativePointer, ident: KNativePointer, body: BigUint64Array, bodySequenceLength: KUInt, modifiers: KInt, flags: KInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateClassDefinition1(context: KNativePointer, original: KNativePointer, ident: KNativePointer, body: BigUint64Array, bodySequenceLength: KUInt, modifiers: KInt, flags: KInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateClassDefinition2(context: KNativePointer, ident: KNativePointer, modifiers: KInt, flags: KInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateClassDefinition2(context: KNativePointer, original: KNativePointer, ident: KNativePointer, modifiers: KInt, flags: KInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionIdentConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionIdent(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionSetIdent(context: KNativePointer, receiver: KNativePointer, ident: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionInternalNameConst(context: KNativePointer, receiver: KNativePointer): KStringPtr {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionSetInternalName(context: KNativePointer, receiver: KNativePointer, internalName: KStringPtr): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionSuper(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionSuperConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionSetSuper(context: KNativePointer, receiver: KNativePointer, superClass: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionIsGlobalConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionIsLocalConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionIsExternConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionIsFromExternalConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionIsInnerConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionIsGlobalInitializedConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionIsClassDefinitionCheckedConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionIsAnonymousConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionIsIntEnumTransformedConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionIsStringEnumTransformedConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionIsEnumTransformedConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionIsNamespaceTransformedConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionIsFromStructConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionIsModuleConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionSetGlobalInitialized(context: KNativePointer, receiver: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionSetInnerModifier(context: KNativePointer, receiver: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionSetClassDefinitionChecked(context: KNativePointer, receiver: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionSetAnonymousModifier(context: KNativePointer, receiver: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionSetNamespaceTransformed(context: KNativePointer, receiver: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionSetFromStructModifier(context: KNativePointer, receiver: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionModifiersConst(context: KNativePointer, receiver: KNativePointer): KInt {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionSetModifiers(context: KNativePointer, receiver: KNativePointer, modifiers: KInt): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionAddProperties(context: KNativePointer, receiver: KNativePointer, body: BigUint64Array, bodySequenceLength: KUInt): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionBody(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionBodyConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionCtor(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionSetCtor(context: KNativePointer, receiver: KNativePointer, ctor: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionImplements(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionImplementsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionTypeParamsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionTypeParams(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionSetTypeParams(context: KNativePointer, receiver: KNativePointer, typeParams: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionSuperTypeParamsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionSuperTypeParams(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionLocalTypeCounter(context: KNativePointer, receiver: KNativePointer): KInt {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionLocalIndexConst(context: KNativePointer, receiver: KNativePointer): KInt {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionLocalPrefixConst(context: KNativePointer, receiver: KNativePointer): KStringPtr {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionSetOrigEnumDecl(context: KNativePointer, receiver: KNativePointer, enumDecl: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionOrigEnumDeclConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionGetAnonClass(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionSetAnonClass(context: KNativePointer, receiver: KNativePointer, anonClass: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionCtorConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionHasPrivateMethodConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionHasNativeMethodConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionHasComputedInstanceFieldConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionHasMatchingPrivateKeyConst(context: KNativePointer, receiver: KNativePointer, name: KStringPtr): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionAddToExportedClasses(context: KNativePointer, receiver: KNativePointer, cls: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionAnnotations(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionAnnotationsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDefinitionSetAnnotations(context: KNativePointer, receiver: KNativePointer, annotations: BigUint64Array, annotationsSequenceLength: KUInt): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateArrayExpression(context: KNativePointer, elements: BigUint64Array, elementsSequenceLength: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateArrayExpression(context: KNativePointer, original: KNativePointer, elements: BigUint64Array, elementsSequenceLength: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateArrayExpression1(context: KNativePointer, nodeType: KInt, elements: BigUint64Array, elementsSequenceLength: KUInt, trailingComma: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateArrayExpression1(context: KNativePointer, original: KNativePointer, nodeType: KInt, elements: BigUint64Array, elementsSequenceLength: KUInt, trailingComma: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ArrayExpressionGetElementNodeAtIdxConst(context: KNativePointer, receiver: KNativePointer, idx: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ArrayExpressionElementsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ArrayExpressionElements(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ArrayExpressionSetElements(context: KNativePointer, receiver: KNativePointer, elements: BigUint64Array, elementsSequenceLength: KUInt): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ArrayExpressionIsDeclarationConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ArrayExpressionIsOptionalConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ArrayExpressionSetDeclaration(context: KNativePointer, receiver: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ArrayExpressionSetOptional(context: KNativePointer, receiver: KNativePointer, optional_arg: KBoolean): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ArrayExpressionDecoratorsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ArrayExpressionClearPreferredType(context: KNativePointer, receiver: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ArrayExpressionConvertibleToArrayPattern(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ArrayExpressionValidateExpression(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ArrayExpressionTrySetPreferredTypeForNestedArrayExprConst(context: KNativePointer, receiver: KNativePointer, nestedArrayExpr: KNativePointer, idx: KUInt): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ArrayExpressionTypeAnnotationConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ArrayExpressionSetTsTypeAnnotation(context: KNativePointer, receiver: KNativePointer, typeAnnotation: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSInterfaceBody(context: KNativePointer, body: BigUint64Array, bodySequenceLength: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSInterfaceBody(context: KNativePointer, original: KNativePointer, body: BigUint64Array, bodySequenceLength: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSInterfaceBodyBody(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSInterfaceBodyBodyConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSTypeQuery(context: KNativePointer, exprName: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSTypeQuery(context: KNativePointer, original: KNativePointer, exprName: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSTypeQueryExprNameConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSBigintKeyword(context: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSBigintKeyword(context: KNativePointer, original: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateProperty(context: KNativePointer, key: KNativePointer, value: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateProperty(context: KNativePointer, original: KNativePointer, key: KNativePointer, value: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateProperty1(context: KNativePointer, kind: KInt, key: KNativePointer, value: KNativePointer, isMethod: KBoolean, isComputed: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateProperty1(context: KNativePointer, original: KNativePointer, kind: KInt, key: KNativePointer, value: KNativePointer, isMethod: KBoolean, isComputed: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _PropertyKey(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _PropertyKeyConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _PropertyValueConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _PropertyValue(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _PropertyKindConst(context: KNativePointer, receiver: KNativePointer): KInt {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _PropertyIsMethodConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _PropertyIsShorthandConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _PropertyIsComputedConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _PropertyIsAccessorConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _PropertyIsAccessorKind(context: KNativePointer, receiver: KNativePointer, kind: KInt): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _PropertyConvertibleToPatternProperty(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _PropertyValidateExpression(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateVariableDeclarator(context: KNativePointer, flag: KInt, ident: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateVariableDeclarator(context: KNativePointer, original: KNativePointer, flag: KInt, ident: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateVariableDeclarator1(context: KNativePointer, flag: KInt, ident: KNativePointer, init: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateVariableDeclarator1(context: KNativePointer, original: KNativePointer, flag: KInt, ident: KNativePointer, init: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _VariableDeclaratorInit(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _VariableDeclaratorInitConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _VariableDeclaratorSetInit(context: KNativePointer, receiver: KNativePointer, init: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _VariableDeclaratorId(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _VariableDeclaratorIdConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _VariableDeclaratorFlag(context: KNativePointer, receiver: KNativePointer): KInt {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateStringLiteral(context: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateStringLiteral(context: KNativePointer, original: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateStringLiteral1(context: KNativePointer, str: KStringPtr): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateStringLiteral1(context: KNativePointer, original: KNativePointer, str: KStringPtr): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _StringLiteralStrConst(context: KNativePointer, receiver: KNativePointer): KStringPtr {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSTypeAssertion(context: KNativePointer, typeAnnotation: KNativePointer, expression: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSTypeAssertion(context: KNativePointer, original: KNativePointer, typeAnnotation: KNativePointer, expression: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSTypeAssertionGetExpressionConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSTypeAssertionTypeAnnotationConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSTypeAssertionSetTsTypeAnnotation(context: KNativePointer, receiver: KNativePointer, typeAnnotation: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSExternalModuleReference(context: KNativePointer, expr: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSExternalModuleReference(context: KNativePointer, original: KNativePointer, expr: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSExternalModuleReferenceExprConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSUndefinedKeyword(context: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSUndefinedKeyword(context: KNativePointer, original: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateETSTuple(context: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateETSTuple(context: KNativePointer, original: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateETSTuple1(context: KNativePointer, size: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateETSTuple1(context: KNativePointer, original: KNativePointer, size: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateETSTuple2(context: KNativePointer, typeList: BigUint64Array, typeListSequenceLength: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateETSTuple2(context: KNativePointer, original: KNativePointer, typeList: BigUint64Array, typeListSequenceLength: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSTupleGetTupleSizeConst(context: KNativePointer, receiver: KNativePointer): KUInt {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSTupleGetTupleTypeAnnotationsList(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSTupleGetTupleTypeAnnotationsListConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSTupleSetTypeAnnotationsList(context: KNativePointer, receiver: KNativePointer, typeNodeList: BigUint64Array, typeNodeListSequenceLength: KUInt): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateETSStringLiteralType(context: KNativePointer, value: KStringPtr): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateETSStringLiteralType(context: KNativePointer, original: KNativePointer, value: KStringPtr): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTryStatement(context: KNativePointer, block: KNativePointer, catchClauses: BigUint64Array, catchClausesSequenceLength: KUInt, finalizer: KNativePointer, finalizerInsertionsLabelPair: BigUint64Array, finalizerInsertionsLabelPairSequenceLength: KUInt, finalizerInsertionsStatement: BigUint64Array, finalizerInsertionsStatementSequenceLength: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTryStatement(context: KNativePointer, original: KNativePointer, block: KNativePointer, catchClauses: BigUint64Array, catchClausesSequenceLength: KUInt, finalizer: KNativePointer, finalizerInsertionsLabelPair: BigUint64Array, finalizerInsertionsLabelPairSequenceLength: KUInt, finalizerInsertionsStatement: BigUint64Array, finalizerInsertionsStatementSequenceLength: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTryStatement1(context: KNativePointer, other: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTryStatement1(context: KNativePointer, original: KNativePointer, other: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TryStatementFinallyBlockConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TryStatementBlockConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TryStatementHasFinalizerConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TryStatementHasDefaultCatchClauseConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TryStatementCatchClausesConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TryStatementFinallyCanCompleteNormallyConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TryStatementSetFinallyCanCompleteNormally(context: KNativePointer, receiver: KNativePointer, finallyCanCompleteNormally: KBoolean): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeIsProgramConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeIsStatementConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeIsExpressionConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeIsTypedConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeAsTyped(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeAsTypedConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeIsBrokenStatementConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeAsExpression(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeAsExpressionConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeAsStatement(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeAsStatementConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeSetRange(context: KNativePointer, receiver: KNativePointer, loc: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeSetStart(context: KNativePointer, receiver: KNativePointer, start: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeSetEnd(context: KNativePointer, receiver: KNativePointer, end: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeStartConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeEndConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeRangeConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeTypeConst(context: KNativePointer, receiver: KNativePointer): KInt {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeParent(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeParentConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeSetParent(context: KNativePointer, receiver: KNativePointer, parent: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeDecoratorsPtrConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeAddDecorators(context: KNativePointer, receiver: KNativePointer, decorators: BigUint64Array, decoratorsSequenceLength: KUInt): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeCanHaveDecoratorConst(context: KNativePointer, receiver: KNativePointer, inTs: KBoolean): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeIsReadonlyConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeIsReadonlyTypeConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeIsOptionalDeclarationConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeIsDefiniteConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeIsConstructorConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeIsOverrideConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeSetOverride(context: KNativePointer, receiver: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeIsAsyncConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeIsSynchronizedConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeIsNativeConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeIsConstConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeIsStaticConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeIsFinalConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeIsAbstractConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeIsPublicConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeIsProtectedConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeIsPrivateConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeIsInternalConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeIsExportedConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeIsDefaultExportedConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeIsExportedTypeConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeIsDeclareConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeIsInConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeIsOutConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeIsSetterConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeAddModifier(context: KNativePointer, receiver: KNativePointer, flags: KInt): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeClearModifier(context: KNativePointer, receiver: KNativePointer, flags: KInt): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeModifiers(context: KNativePointer, receiver: KNativePointer): KInt {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeModifiersConst(context: KNativePointer, receiver: KNativePointer): KInt {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeHasExportAliasConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeAsClassElement(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeAsClassElementConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeIsScopeBearerConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeClearScope(context: KNativePointer, receiver: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeGetTopStatement(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeGetTopStatementConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeClone(context: KNativePointer, receiver: KNativePointer, parent: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeDumpJSONConst(context: KNativePointer, receiver: KNativePointer): KStringPtr {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeDumpEtsSrcConst(context: KNativePointer, receiver: KNativePointer): KStringPtr {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeDumpDeclConst(context: KNativePointer, receiver: KNativePointer): KStringPtr {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeIsolatedDumpDeclConst(context: KNativePointer, receiver: KNativePointer): KStringPtr {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeDumpConst(context: KNativePointer, receiver: KNativePointer, dumper: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeDumpConst1(context: KNativePointer, receiver: KNativePointer, dumper: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeCompileConst(context: KNativePointer, receiver: KNativePointer, pg: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeCompileConst1(context: KNativePointer, receiver: KNativePointer, etsg: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeSetTransformedNode(context: KNativePointer, receiver: KNativePointer, transformationName: KStringPtr, transformedNode: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeAccept(context: KNativePointer, receiver: KNativePointer, v: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeSetOriginalNode(context: KNativePointer, receiver: KNativePointer, originalNode: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeOriginalNodeConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeCleanUp(context: KNativePointer, receiver: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstNodeShallowClone(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateUnaryExpression(context: KNativePointer, argument: KNativePointer, unaryOperator: KInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateUnaryExpression(context: KNativePointer, original: KNativePointer, argument: KNativePointer, unaryOperator: KInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UnaryExpressionOperatorTypeConst(context: KNativePointer, receiver: KNativePointer): KInt {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UnaryExpressionArgument(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UnaryExpressionArgumentConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateForInStatement(context: KNativePointer, left: KNativePointer, right: KNativePointer, body: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateForInStatement(context: KNativePointer, original: KNativePointer, left: KNativePointer, right: KNativePointer, body: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ForInStatementLeft(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ForInStatementLeftConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ForInStatementRight(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ForInStatementRightConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ForInStatementBody(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ForInStatementBodyConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateThisExpression(context: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateThisExpression(context: KNativePointer, original: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSMethodSignature(context: KNativePointer, key: KNativePointer, signature: KNativePointer, computed: KBoolean, optional_arg: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSMethodSignature(context: KNativePointer, original: KNativePointer, key: KNativePointer, signature: KNativePointer, computed: KBoolean, optional_arg: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSMethodSignatureKeyConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSMethodSignatureKey(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSMethodSignatureTypeParamsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSMethodSignatureTypeParams(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSMethodSignatureParamsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSMethodSignatureReturnTypeAnnotationConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSMethodSignatureReturnTypeAnnotation(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSMethodSignatureComputedConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSMethodSignatureOptionalConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateBinaryExpression(context: KNativePointer, left: KNativePointer, right: KNativePointer, operatorType: KInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateBinaryExpression(context: KNativePointer, original: KNativePointer, left: KNativePointer, right: KNativePointer, operatorType: KInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _BinaryExpressionLeftConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _BinaryExpressionLeft(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _BinaryExpressionRightConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _BinaryExpressionRight(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _BinaryExpressionResultConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _BinaryExpressionResult(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _BinaryExpressionOperatorTypeConst(context: KNativePointer, receiver: KNativePointer): KInt {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _BinaryExpressionIsLogicalConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _BinaryExpressionIsLogicalExtendedConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _BinaryExpressionIsBitwiseConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _BinaryExpressionIsArithmeticConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _BinaryExpressionSetLeft(context: KNativePointer, receiver: KNativePointer, expr: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _BinaryExpressionSetRight(context: KNativePointer, receiver: KNativePointer, expr: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _BinaryExpressionSetResult(context: KNativePointer, receiver: KNativePointer, expr: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _BinaryExpressionSetOperator(context: KNativePointer, receiver: KNativePointer, operatorType: KInt): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _BinaryExpressionCompileOperandsConst(context: KNativePointer, receiver: KNativePointer, etsg: KNativePointer, lhs: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateSuperExpression(context: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateSuperExpression(context: KNativePointer, original: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateAssertStatement(context: KNativePointer, test: KNativePointer, second: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateAssertStatement(context: KNativePointer, original: KNativePointer, test: KNativePointer, second: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AssertStatementTestConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AssertStatementTest(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AssertStatementSecondConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSStringKeyword(context: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSStringKeyword(context: KNativePointer, original: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateAssignmentExpression(context: KNativePointer, left: KNativePointer, right: KNativePointer, assignmentOperator: KInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateAssignmentExpression(context: KNativePointer, original: KNativePointer, left: KNativePointer, right: KNativePointer, assignmentOperator: KInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateAssignmentExpression1(context: KNativePointer, type: KInt, left: KNativePointer, right: KNativePointer, assignmentOperator: KInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateAssignmentExpression1(context: KNativePointer, original: KNativePointer, type: KInt, left: KNativePointer, right: KNativePointer, assignmentOperator: KInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AssignmentExpressionLeftConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AssignmentExpressionLeft(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AssignmentExpressionRight(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AssignmentExpressionRightConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AssignmentExpressionSetRight(context: KNativePointer, receiver: KNativePointer, expr: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AssignmentExpressionSetLeft(context: KNativePointer, receiver: KNativePointer, expr: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AssignmentExpressionResultConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AssignmentExpressionResult(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AssignmentExpressionOperatorTypeConst(context: KNativePointer, receiver: KNativePointer): KInt {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AssignmentExpressionSetOperatorType(context: KNativePointer, receiver: KNativePointer, tokenType: KInt): KInt {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AssignmentExpressionSetResult(context: KNativePointer, receiver: KNativePointer, expr: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AssignmentExpressionIsLogicalExtendedConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AssignmentExpressionSetIgnoreConstAssign(context: KNativePointer, receiver: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AssignmentExpressionIsIgnoreConstAssignConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AssignmentExpressionConvertibleToAssignmentPatternLeft(context: KNativePointer, receiver: KNativePointer, mustBePattern: KBoolean): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AssignmentExpressionConvertibleToAssignmentPatternRight(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AssignmentExpressionConvertibleToAssignmentPattern(context: KNativePointer, receiver: KNativePointer, mustBePattern: KBoolean): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AssignmentExpressionCompilePatternConst(context: KNativePointer, receiver: KNativePointer, pg: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateExpressionStatement(context: KNativePointer, expr: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateExpressionStatement(context: KNativePointer, original: KNativePointer, expr: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ExpressionStatementGetExpressionConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ExpressionStatementGetExpression(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ExpressionStatementSetExpression(context: KNativePointer, receiver: KNativePointer, expr: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSModuleIdent(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSModuleIdentConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSModuleIsETSScriptConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSModuleIsNamespaceConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSModuleIsNamespaceChainLastNodeConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSModuleSetNamespaceChainLastNode(context: KNativePointer, receiver: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSModuleAnnotations(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSModuleAnnotationsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSModuleSetAnnotations(context: KNativePointer, receiver: KNativePointer, annotations: BigUint64Array, annotationsSequenceLength: KUInt): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateMetaProperty(context: KNativePointer, kind: KInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateMetaProperty(context: KNativePointer, original: KNativePointer, kind: KInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _MetaPropertyKindConst(context: KNativePointer, receiver: KNativePointer): KInt {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSArrayType(context: KNativePointer, elementType: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSArrayType(context: KNativePointer, original: KNativePointer, elementType: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSArrayTypeElementTypeConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSSignatureDeclaration(context: KNativePointer, kind: KInt, signature: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSSignatureDeclaration(context: KNativePointer, original: KNativePointer, kind: KInt, signature: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSSignatureDeclarationTypeParamsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSSignatureDeclarationTypeParams(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSSignatureDeclarationParamsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSSignatureDeclarationReturnTypeAnnotationConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSSignatureDeclarationReturnTypeAnnotation(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSSignatureDeclarationKindConst(context: KNativePointer, receiver: KNativePointer): KInt {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateExportAllDeclaration(context: KNativePointer, source: KNativePointer, exported: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateExportAllDeclaration(context: KNativePointer, original: KNativePointer, source: KNativePointer, exported: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ExportAllDeclarationSourceConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ExportAllDeclarationExportedConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateExportSpecifier(context: KNativePointer, local: KNativePointer, exported: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateExportSpecifier(context: KNativePointer, original: KNativePointer, local: KNativePointer, exported: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ExportSpecifierLocalConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ExportSpecifierExportedConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ExportSpecifierSetDefault(context: KNativePointer, receiver: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ExportSpecifierIsDefaultConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ExportSpecifierSetConstantExpression(context: KNativePointer, receiver: KNativePointer, constantExpression: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ExportSpecifierGetConstantExpressionConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSTupleType(context: KNativePointer, elementTypes: BigUint64Array, elementTypesSequenceLength: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSTupleType(context: KNativePointer, original: KNativePointer, elementTypes: BigUint64Array, elementTypesSequenceLength: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSTupleTypeElementTypeConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateFunctionExpression(context: KNativePointer, func: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateFunctionExpression(context: KNativePointer, original: KNativePointer, func: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateFunctionExpression1(context: KNativePointer, namedExpr: KNativePointer, func: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateFunctionExpression1(context: KNativePointer, original: KNativePointer, namedExpr: KNativePointer, func: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _FunctionExpressionFunctionConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _FunctionExpressionFunction(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _FunctionExpressionIsAnonymousConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _FunctionExpressionId(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSIndexSignature(context: KNativePointer, param: KNativePointer, typeAnnotation: KNativePointer, readonly_arg: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSIndexSignature(context: KNativePointer, original: KNativePointer, param: KNativePointer, typeAnnotation: KNativePointer, readonly_arg: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSIndexSignatureParamConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSIndexSignatureTypeAnnotationConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSIndexSignatureReadonlyConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSIndexSignatureKindConst(context: KNativePointer, receiver: KNativePointer): KInt {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSModuleDeclaration(context: KNativePointer, name: KNativePointer, body: KNativePointer, declare: KBoolean, _global: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSModuleDeclaration(context: KNativePointer, original: KNativePointer, name: KNativePointer, body: KNativePointer, declare: KBoolean, _global: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSModuleDeclarationNameConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSModuleDeclarationBodyConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSModuleDeclarationGlobalConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSModuleDeclarationIsExternalOrAmbientConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateImportDeclaration(context: KNativePointer, source: KNativePointer, specifiers: BigUint64Array, specifiersSequenceLength: KUInt, importKinds: KInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateImportDeclaration(context: KNativePointer, original: KNativePointer, source: KNativePointer, specifiers: BigUint64Array, specifiersSequenceLength: KUInt, importKinds: KInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ImportDeclarationSourceConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ImportDeclarationSource(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ImportDeclarationSpecifiersConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ImportDeclarationSpecifiers(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ImportDeclarationIsTypeKindConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSParenthesizedType(context: KNativePointer, type: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSParenthesizedType(context: KNativePointer, original: KNativePointer, type: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSParenthesizedTypeTypeConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateCharLiteral(context: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateCharLiteral(context: KNativePointer, original: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateETSPackageDeclaration(context: KNativePointer, name: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateETSPackageDeclaration(context: KNativePointer, original: KNativePointer, name: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateETSImportDeclaration(context: KNativePointer, importPath: KNativePointer, specifiers: BigUint64Array, specifiersSequenceLength: KUInt, importKinds: KInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateETSImportDeclaration(context: KNativePointer, original: KNativePointer, importPath: KNativePointer, specifiers: BigUint64Array, specifiersSequenceLength: KUInt, importKinds: KInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSImportDeclarationSetImportMetadata(context: KNativePointer, receiver: KNativePointer, importFlags: KInt, lang: KInt, resolvedSource: KStringPtr, declPath: KStringPtr, ohmUrl: KStringPtr): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSImportDeclarationDeclPathConst(context: KNativePointer, receiver: KNativePointer): KStringPtr {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSImportDeclarationOhmUrlConst(context: KNativePointer, receiver: KNativePointer): KStringPtr {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSImportDeclarationIsValidConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSImportDeclarationIsPureDynamicConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSImportDeclarationAssemblerName(context: KNativePointer, receiver: KNativePointer): KStringPtr {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSImportDeclarationAssemblerNameConst(context: KNativePointer, receiver: KNativePointer): KStringPtr {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSImportDeclarationResolvedSourceConst(context: KNativePointer, receiver: KNativePointer): KStringPtr {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateETSStructDeclaration(context: KNativePointer, def: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateETSStructDeclaration(context: KNativePointer, original: KNativePointer, def: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSModuleBlock(context: KNativePointer, statements: BigUint64Array, statementsSequenceLength: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSModuleBlock(context: KNativePointer, original: KNativePointer, statements: BigUint64Array, statementsSequenceLength: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSModuleBlockStatementsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateETSNewArrayInstanceExpression(context: KNativePointer, typeReference: KNativePointer, dimension: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateETSNewArrayInstanceExpression(context: KNativePointer, original: KNativePointer, typeReference: KNativePointer, dimension: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSNewArrayInstanceExpressionTypeReference(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSNewArrayInstanceExpressionTypeReferenceConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSNewArrayInstanceExpressionDimension(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSNewArrayInstanceExpressionDimensionConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSNewArrayInstanceExpressionSetDimension(context: KNativePointer, receiver: KNativePointer, dimension: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSNewArrayInstanceExpressionClearPreferredType(context: KNativePointer, receiver: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateAnnotationDeclaration(context: KNativePointer, expr: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateAnnotationDeclaration(context: KNativePointer, original: KNativePointer, expr: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateAnnotationDeclaration1(context: KNativePointer, expr: KNativePointer, properties: BigUint64Array, propertiesSequenceLength: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateAnnotationDeclaration1(context: KNativePointer, original: KNativePointer, expr: KNativePointer, properties: BigUint64Array, propertiesSequenceLength: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AnnotationDeclarationInternalNameConst(context: KNativePointer, receiver: KNativePointer): KStringPtr {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AnnotationDeclarationSetInternalName(context: KNativePointer, receiver: KNativePointer, internalName: KStringPtr): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AnnotationDeclarationExprConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AnnotationDeclarationExpr(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AnnotationDeclarationProperties(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AnnotationDeclarationPropertiesConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AnnotationDeclarationAddProperties(context: KNativePointer, receiver: KNativePointer, properties: BigUint64Array, propertiesSequenceLength: KUInt): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AnnotationDeclarationIsSourceRetentionConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AnnotationDeclarationIsBytecodeRetentionConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AnnotationDeclarationIsRuntimeRetentionConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AnnotationDeclarationSetSourceRetention(context: KNativePointer, receiver: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AnnotationDeclarationSetBytecodeRetention(context: KNativePointer, receiver: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AnnotationDeclarationSetRuntimeRetention(context: KNativePointer, receiver: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AnnotationDeclarationGetBaseNameConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AnnotationDeclarationAnnotations(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AnnotationDeclarationAnnotationsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AnnotationDeclarationSetAnnotations(context: KNativePointer, receiver: KNativePointer, annotations: BigUint64Array, annotationsSequenceLength: KUInt): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateAnnotationUsage(context: KNativePointer, expr: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateAnnotationUsage(context: KNativePointer, original: KNativePointer, expr: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateAnnotationUsage1(context: KNativePointer, expr: KNativePointer, properties: BigUint64Array, propertiesSequenceLength: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateAnnotationUsage1(context: KNativePointer, original: KNativePointer, expr: KNativePointer, properties: BigUint64Array, propertiesSequenceLength: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AnnotationUsageExpr(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AnnotationUsageProperties(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AnnotationUsagePropertiesConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AnnotationUsageAddProperty(context: KNativePointer, receiver: KNativePointer, property: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AnnotationUsageSetProperties(context: KNativePointer, receiver: KNativePointer, properties: BigUint64Array, propertiesSequenceLength: KUInt): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AnnotationUsageGetBaseNameConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateEmptyStatement(context: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateEmptyStatement(context: KNativePointer, original: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateEmptyStatement1(context: KNativePointer, isBrokenStatement: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateEmptyStatement1(context: KNativePointer, original: KNativePointer, isBrokenStatement: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _EmptyStatementIsBrokenStatement(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateWhileStatement(context: KNativePointer, test: KNativePointer, body: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateWhileStatement(context: KNativePointer, original: KNativePointer, test: KNativePointer, body: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _WhileStatementTestConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _WhileStatementTest(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _WhileStatementBodyConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _WhileStatementBody(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateFunctionSignature(context: KNativePointer, typeParams: KNativePointer, params: BigUint64Array, paramsSequenceLength: KUInt, returnTypeAnnotation: KNativePointer, hasReceiver: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _FunctionSignatureParamsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _FunctionSignatureParams(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _FunctionSignatureTypeParams(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _FunctionSignatureTypeParamsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _FunctionSignatureReturnType(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _FunctionSignatureSetReturnType(context: KNativePointer, receiver: KNativePointer, type: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _FunctionSignatureReturnTypeConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _FunctionSignatureClone(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _FunctionSignatureHasReceiverConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateChainExpression(context: KNativePointer, expression: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateChainExpression(context: KNativePointer, original: KNativePointer, expression: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ChainExpressionGetExpressionConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ChainExpressionGetExpression(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ChainExpressionCompileToRegConst(context: KNativePointer, receiver: KNativePointer, pg: KNativePointer, objReg: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSIntersectionType(context: KNativePointer, types: BigUint64Array, typesSequenceLength: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSIntersectionType(context: KNativePointer, original: KNativePointer, types: BigUint64Array, typesSequenceLength: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSIntersectionTypeTypesConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateUpdateExpression(context: KNativePointer, argument: KNativePointer, updateOperator: KInt, isPrefix: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateUpdateExpression(context: KNativePointer, original: KNativePointer, argument: KNativePointer, updateOperator: KInt, isPrefix: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateExpressionOperatorTypeConst(context: KNativePointer, receiver: KNativePointer): KInt {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateExpressionArgument(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateExpressionArgumentConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateExpressionIsPrefixConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateBlockExpression(context: KNativePointer, statements: BigUint64Array, statementsSequenceLength: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateBlockExpression(context: KNativePointer, original: KNativePointer, statements: BigUint64Array, statementsSequenceLength: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _BlockExpressionStatementsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _BlockExpressionStatements(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _BlockExpressionAddStatements(context: KNativePointer, receiver: KNativePointer, statements: BigUint64Array, statementsSequenceLength: KUInt): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _BlockExpressionAddStatement(context: KNativePointer, receiver: KNativePointer, statement: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSTypeLiteral(context: KNativePointer, members: BigUint64Array, membersSequenceLength: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSTypeLiteral(context: KNativePointer, original: KNativePointer, members: BigUint64Array, membersSequenceLength: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSTypeLiteralMembersConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSTypeParameter(context: KNativePointer, name: KNativePointer, constraint: KNativePointer, defaultType: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSTypeParameter(context: KNativePointer, original: KNativePointer, name: KNativePointer, constraint: KNativePointer, defaultType: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSTypeParameter1(context: KNativePointer, name: KNativePointer, constraint: KNativePointer, defaultType: KNativePointer, flags: KInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSTypeParameter1(context: KNativePointer, original: KNativePointer, name: KNativePointer, constraint: KNativePointer, defaultType: KNativePointer, flags: KInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSTypeParameterNameConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSTypeParameterName(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSTypeParameterConstraint(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSTypeParameterConstraintConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSTypeParameterSetConstraint(context: KNativePointer, receiver: KNativePointer, constraint: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSTypeParameterDefaultTypeConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSTypeParameterSetDefaultType(context: KNativePointer, receiver: KNativePointer, defaultType: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSTypeParameterAnnotations(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSTypeParameterAnnotationsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSTypeParameterSetAnnotations(context: KNativePointer, receiver: KNativePointer, annotations: BigUint64Array, annotationsSequenceLength: KUInt): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSBooleanKeyword(context: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSBooleanKeyword(context: KNativePointer, original: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateSpreadElement(context: KNativePointer, nodeType: KInt, argument: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateSpreadElement(context: KNativePointer, original: KNativePointer, nodeType: KInt, argument: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _SpreadElementArgumentConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _SpreadElementArgument(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _SpreadElementIsOptionalConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _SpreadElementDecoratorsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _SpreadElementSetOptional(context: KNativePointer, receiver: KNativePointer, optional_arg: KBoolean): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _SpreadElementValidateExpression(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _SpreadElementConvertibleToRest(context: KNativePointer, receiver: KNativePointer, isDeclaration: KBoolean, allowPattern: KBoolean): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _SpreadElementTypeAnnotationConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _SpreadElementSetTsTypeAnnotation(context: KNativePointer, receiver: KNativePointer, typeAnnotation: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSTypePredicate(context: KNativePointer, parameterName: KNativePointer, typeAnnotation: KNativePointer, asserts: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSTypePredicate(context: KNativePointer, original: KNativePointer, parameterName: KNativePointer, typeAnnotation: KNativePointer, asserts: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSTypePredicateParameterNameConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSTypePredicateTypeAnnotationConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSTypePredicateAssertsConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateImportNamespaceSpecifier(context: KNativePointer, local: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateImportNamespaceSpecifier(context: KNativePointer, original: KNativePointer, local: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ImportNamespaceSpecifierLocal(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ImportNamespaceSpecifierLocalConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateExportNamedDeclaration(context: KNativePointer, source: KNativePointer, specifiers: BigUint64Array, specifiersSequenceLength: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateExportNamedDeclaration(context: KNativePointer, original: KNativePointer, source: KNativePointer, specifiers: BigUint64Array, specifiersSequenceLength: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateExportNamedDeclaration1(context: KNativePointer, decl: KNativePointer, specifiers: BigUint64Array, specifiersSequenceLength: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateExportNamedDeclaration1(context: KNativePointer, original: KNativePointer, decl: KNativePointer, specifiers: BigUint64Array, specifiersSequenceLength: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateExportNamedDeclaration2(context: KNativePointer, decl: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateExportNamedDeclaration2(context: KNativePointer, original: KNativePointer, decl: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ExportNamedDeclarationDeclConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ExportNamedDeclarationSourceConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ExportNamedDeclarationSpecifiersConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ExportNamedDeclarationReplaceSpecifiers(context: KNativePointer, receiver: KNativePointer, specifiers: BigUint64Array, specifiersSequenceLength: KUInt): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateETSParameterExpression(context: KNativePointer, identOrSpread: KNativePointer, isOptional: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateETSParameterExpression(context: KNativePointer, original: KNativePointer, identOrSpread: KNativePointer, isOptional: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateETSParameterExpression1(context: KNativePointer, identOrSpread: KNativePointer, initializer: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateETSParameterExpression1(context: KNativePointer, original: KNativePointer, identOrSpread: KNativePointer, initializer: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSParameterExpressionNameConst(context: KNativePointer, receiver: KNativePointer): KStringPtr {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSParameterExpressionIdentConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSParameterExpressionIdent(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSParameterExpressionSetIdent(context: KNativePointer, receiver: KNativePointer, ident: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSParameterExpressionRestParameterConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSParameterExpressionRestParameter(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSParameterExpressionInitializerConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSParameterExpressionInitializer(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSParameterExpressionSetLexerSaved(context: KNativePointer, receiver: KNativePointer, s: KStringPtr): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSParameterExpressionLexerSavedConst(context: KNativePointer, receiver: KNativePointer): KStringPtr {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSParameterExpressionTypeAnnotationConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSParameterExpressionTypeAnnotation(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSParameterExpressionSetTypeAnnotation(context: KNativePointer, receiver: KNativePointer, typeNode: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSParameterExpressionIsOptionalConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSParameterExpressionSetOptional(context: KNativePointer, receiver: KNativePointer, value: KBoolean): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSParameterExpressionSetInitializer(context: KNativePointer, receiver: KNativePointer, initExpr: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSParameterExpressionIsRestParameterConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSParameterExpressionGetRequiredParamsConst(context: KNativePointer, receiver: KNativePointer): KUInt {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSParameterExpressionSetRequiredParams(context: KNativePointer, receiver: KNativePointer, value: KUInt): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSParameterExpressionAnnotations(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSParameterExpressionAnnotationsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSParameterExpressionSetAnnotations(context: KNativePointer, receiver: KNativePointer, annotations: BigUint64Array, annotationsSequenceLength: KUInt): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSTypeParameterInstantiation(context: KNativePointer, params: BigUint64Array, paramsSequenceLength: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSTypeParameterInstantiation(context: KNativePointer, original: KNativePointer, params: BigUint64Array, paramsSequenceLength: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSTypeParameterInstantiationParamsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateNullLiteral(context: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateNullLiteral(context: KNativePointer, original: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSInferType(context: KNativePointer, typeParam: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSInferType(context: KNativePointer, original: KNativePointer, typeParam: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSInferTypeTypeParamConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateSwitchCaseStatement(context: KNativePointer, test: KNativePointer, consequent: BigUint64Array, consequentSequenceLength: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateSwitchCaseStatement(context: KNativePointer, original: KNativePointer, test: KNativePointer, consequent: BigUint64Array, consequentSequenceLength: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _SwitchCaseStatementTest(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _SwitchCaseStatementTestConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _SwitchCaseStatementSetTest(context: KNativePointer, receiver: KNativePointer, test: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _SwitchCaseStatementConsequentConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateYieldExpression(context: KNativePointer, argument: KNativePointer, isDelegate: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateYieldExpression(context: KNativePointer, original: KNativePointer, argument: KNativePointer, isDelegate: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _YieldExpressionHasDelegateConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _YieldExpressionArgumentConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSImportEqualsDeclaration(context: KNativePointer, id: KNativePointer, moduleReference: KNativePointer, isExport: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSImportEqualsDeclaration(context: KNativePointer, original: KNativePointer, id: KNativePointer, moduleReference: KNativePointer, isExport: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSImportEqualsDeclarationIdConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSImportEqualsDeclarationModuleReferenceConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSImportEqualsDeclarationIsExportConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateBooleanLiteral(context: KNativePointer, value: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateBooleanLiteral(context: KNativePointer, original: KNativePointer, value: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _BooleanLiteralValueConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSNumberKeyword(context: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSNumberKeyword(context: KNativePointer, original: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateClassStaticBlock(context: KNativePointer, value: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateClassStaticBlock(context: KNativePointer, original: KNativePointer, value: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassStaticBlockFunction(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassStaticBlockFunctionConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassStaticBlockNameConst(context: KNativePointer, receiver: KNativePointer): KStringPtr {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSNonNullExpression(context: KNativePointer, expr: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSNonNullExpression(context: KNativePointer, original: KNativePointer, expr: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSNonNullExpressionExprConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSNonNullExpressionExpr(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSNonNullExpressionSetExpr(context: KNativePointer, receiver: KNativePointer, expr: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreatePrefixAssertionExpression(context: KNativePointer, expr: KNativePointer, type: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdatePrefixAssertionExpression(context: KNativePointer, original: KNativePointer, expr: KNativePointer, type: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _PrefixAssertionExpressionExprConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _PrefixAssertionExpressionTypeConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateClassExpression(context: KNativePointer, def: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateClassExpression(context: KNativePointer, original: KNativePointer, def: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassExpressionDefinitionConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateForOfStatement(context: KNativePointer, left: KNativePointer, right: KNativePointer, body: KNativePointer, isAwait: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateForOfStatement(context: KNativePointer, original: KNativePointer, left: KNativePointer, right: KNativePointer, body: KNativePointer, isAwait: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ForOfStatementLeft(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ForOfStatementLeftConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ForOfStatementRight(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ForOfStatementRightConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ForOfStatementBody(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ForOfStatementBodyConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ForOfStatementIsAwaitConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTemplateLiteral(context: KNativePointer, quasis: BigUint64Array, quasisSequenceLength: KUInt, expressions: BigUint64Array, expressionsSequenceLength: KUInt, multilineString: KStringPtr): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTemplateLiteral(context: KNativePointer, original: KNativePointer, quasis: BigUint64Array, quasisSequenceLength: KUInt, expressions: BigUint64Array, expressionsSequenceLength: KUInt, multilineString: KStringPtr): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TemplateLiteralQuasisConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TemplateLiteralExpressionsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TemplateLiteralGetMultilineStringConst(context: KNativePointer, receiver: KNativePointer): KStringPtr {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSUnionType(context: KNativePointer, types: BigUint64Array, typesSequenceLength: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSUnionType(context: KNativePointer, original: KNativePointer, types: BigUint64Array, typesSequenceLength: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSUnionTypeTypesConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSUnknownKeyword(context: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSUnknownKeyword(context: KNativePointer, original: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateIdentifier(context: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateIdentifier(context: KNativePointer, original: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateIdentifier1(context: KNativePointer, name: KStringPtr): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateIdentifier1(context: KNativePointer, original: KNativePointer, name: KStringPtr): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateIdentifier2(context: KNativePointer, name: KStringPtr, typeAnnotation: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateIdentifier2(context: KNativePointer, original: KNativePointer, name: KStringPtr, typeAnnotation: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _IdentifierNameConst(context: KNativePointer, receiver: KNativePointer): KStringPtr {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _IdentifierName(context: KNativePointer, receiver: KNativePointer): KStringPtr {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _IdentifierSetName(context: KNativePointer, receiver: KNativePointer, newName: KStringPtr): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _IdentifierDecoratorsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _IdentifierIsErrorPlaceHolderConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _IdentifierIsOptionalConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _IdentifierSetOptional(context: KNativePointer, receiver: KNativePointer, optional_arg: KBoolean): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _IdentifierIsReferenceConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _IdentifierIsTdzConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _IdentifierSetTdz(context: KNativePointer, receiver: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _IdentifierSetAccessor(context: KNativePointer, receiver: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _IdentifierIsAccessorConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _IdentifierSetMutator(context: KNativePointer, receiver: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _IdentifierIsMutatorConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _IdentifierIsReceiverConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _IdentifierIsPrivateIdentConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _IdentifierSetPrivate(context: KNativePointer, receiver: KNativePointer, isPrivate: KBoolean): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _IdentifierIsIgnoreBoxConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _IdentifierSetIgnoreBox(context: KNativePointer, receiver: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _IdentifierIsAnnotationDeclConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _IdentifierSetAnnotationDecl(context: KNativePointer, receiver: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _IdentifierIsAnnotationUsageConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _IdentifierSetAnnotationUsage(context: KNativePointer, receiver: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _IdentifierCloneReference(context: KNativePointer, receiver: KNativePointer, parent: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _IdentifierValidateExpression(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _IdentifierTypeAnnotationConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _IdentifierSetTsTypeAnnotation(context: KNativePointer, receiver: KNativePointer, typeAnnotation: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateOpaqueTypeNode1(context: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateOpaqueTypeNode1(context: KNativePointer, original: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateBlockStatement(context: KNativePointer, statementList: BigUint64Array, statementListSequenceLength: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateBlockStatement(context: KNativePointer, original: KNativePointer, statementList: BigUint64Array, statementListSequenceLength: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _BlockStatementStatementsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _BlockStatementStatements(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _BlockStatementSetStatements(context: KNativePointer, receiver: KNativePointer, statementList: BigUint64Array, statementListSequenceLength: KUInt): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _BlockStatementAddStatement(context: KNativePointer, receiver: KNativePointer, stmt: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _BlockStatementAddStatements(context: KNativePointer, receiver: KNativePointer, stmts: BigUint64Array, stmtsSequenceLength: KUInt): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _BlockStatementAddTrailingBlock(context: KNativePointer, receiver: KNativePointer, stmt: KNativePointer, trailingBlock: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateDirectEvalExpression(context: KNativePointer, callee: KNativePointer, _arguments: BigUint64Array, _argumentsSequenceLength: KUInt, typeParams: KNativePointer, optional_arg: KBoolean, parserStatus: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateDirectEvalExpression(context: KNativePointer, original: KNativePointer, callee: KNativePointer, _arguments: BigUint64Array, _argumentsSequenceLength: KUInt, typeParams: KNativePointer, optional_arg: KBoolean, parserStatus: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSTypeParameterDeclaration(context: KNativePointer, params: BigUint64Array, paramsSequenceLength: KUInt, requiredParams: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSTypeParameterDeclaration(context: KNativePointer, original: KNativePointer, params: BigUint64Array, paramsSequenceLength: KUInt, requiredParams: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSTypeParameterDeclarationParamsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSTypeParameterDeclarationAddParam(context: KNativePointer, receiver: KNativePointer, param: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSTypeParameterDeclarationRequiredParamsConst(context: KNativePointer, receiver: KNativePointer): KUInt {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateMethodDefinition(context: KNativePointer, kind: KInt, key: KNativePointer, value: KNativePointer, modifiers: KInt, isComputed: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateMethodDefinition(context: KNativePointer, original: KNativePointer, kind: KInt, key: KNativePointer, value: KNativePointer, modifiers: KInt, isComputed: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _MethodDefinitionKindConst(context: KNativePointer, receiver: KNativePointer): KInt {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _MethodDefinitionIsConstructorConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _MethodDefinitionIsMethodConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _MethodDefinitionIsExtensionMethodConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _MethodDefinitionIsGetterConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _MethodDefinitionIsSetterConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _MethodDefinitionIsDefaultAccessModifierConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _MethodDefinitionSetDefaultAccessModifier(context: KNativePointer, receiver: KNativePointer, isDefault: KBoolean): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _MethodDefinitionOverloadsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _MethodDefinitionBaseOverloadMethodConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _MethodDefinitionBaseOverloadMethod(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _MethodDefinitionAsyncPairMethodConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _MethodDefinitionAsyncPairMethod(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _MethodDefinitionSetOverloads(context: KNativePointer, receiver: KNativePointer, overloads: BigUint64Array, overloadsSequenceLength: KUInt): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _MethodDefinitionClearOverloads(context: KNativePointer, receiver: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _MethodDefinitionAddOverload(context: KNativePointer, receiver: KNativePointer, overload: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _MethodDefinitionSetBaseOverloadMethod(context: KNativePointer, receiver: KNativePointer, baseOverloadMethod: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _MethodDefinitionSetAsyncPairMethod(context: KNativePointer, receiver: KNativePointer, method: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _MethodDefinitionHasOverload(context: KNativePointer, receiver: KNativePointer, overload: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _MethodDefinitionFunction(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _MethodDefinitionFunctionConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _MethodDefinitionInitializeOverloadInfo(context: KNativePointer, receiver: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSNullKeyword(context: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSNullKeyword(context: KNativePointer, original: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSInterfaceHeritage(context: KNativePointer, expr: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSInterfaceHeritage(context: KNativePointer, original: KNativePointer, expr: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSInterfaceHeritageExpr(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSInterfaceHeritageExprConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ExpressionIsGroupedConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ExpressionSetGrouped(context: KNativePointer, receiver: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ExpressionAsLiteralConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ExpressionAsLiteral(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ExpressionIsLiteralConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ExpressionIsTypeNodeConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ExpressionIsAnnotatedExpressionConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ExpressionAsTypeNode(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ExpressionAsTypeNodeConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ExpressionAsAnnotatedExpression(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ExpressionAsAnnotatedExpressionConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ExpressionIsBrokenExpressionConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ExpressionToStringConst(context: KNativePointer, receiver: KNativePointer): KStringPtr {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AnnotatedExpressionTypeAnnotationConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AnnotatedExpressionSetTsTypeAnnotation(context: KNativePointer, receiver: KNativePointer, typeAnnotation: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _MaybeOptionalExpressionIsOptionalConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _MaybeOptionalExpressionClearOptional(context: KNativePointer, receiver: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateSrcDumper(context: KNativePointer, node: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateSrcDumper1(context: KNativePointer, node: KNativePointer, isDeclgen: KBoolean, isIsolatedDeclgen: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _SrcDumperAdd(context: KNativePointer, receiver: KNativePointer, str: KStringPtr): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _SrcDumperAdd1(context: KNativePointer, receiver: KNativePointer, i: KInt): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _SrcDumperAdd2(context: KNativePointer, receiver: KNativePointer, l: KLong): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _SrcDumperAdd3(context: KNativePointer, receiver: KNativePointer, f: KFloat): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _SrcDumperAdd4(context: KNativePointer, receiver: KNativePointer, d: KDouble): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _SrcDumperStrConst(context: KNativePointer, receiver: KNativePointer): KStringPtr {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _SrcDumperIncrIndent(context: KNativePointer, receiver: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _SrcDumperDecrIndent(context: KNativePointer, receiver: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _SrcDumperEndl(context: KNativePointer, receiver: KNativePointer, num: KUInt): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _SrcDumperIsDeclgenConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _SrcDumperIsIsolatedDeclgenConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _SrcDumperDumpNode(context: KNativePointer, receiver: KNativePointer, key: KStringPtr): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _SrcDumperRemoveNode(context: KNativePointer, receiver: KNativePointer, key: KStringPtr): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _SrcDumperIsIndirectDepPhaseConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _SrcDumperRun(context: KNativePointer, receiver: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateETSClassLiteral(context: KNativePointer, expr: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateETSClassLiteral(context: KNativePointer, original: KNativePointer, expr: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSClassLiteralExprConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateBreakStatement(context: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateBreakStatement(context: KNativePointer, original: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateBreakStatement1(context: KNativePointer, ident: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateBreakStatement1(context: KNativePointer, original: KNativePointer, ident: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _BreakStatementIdentConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _BreakStatementIdent(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _BreakStatementTargetConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _BreakStatementHasTargetConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _BreakStatementSetTarget(context: KNativePointer, receiver: KNativePointer, target: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateRegExpLiteral(context: KNativePointer, pattern: KStringPtr, flags: KInt, flagsStr: KStringPtr): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateRegExpLiteral(context: KNativePointer, original: KNativePointer, pattern: KStringPtr, flags: KInt, flagsStr: KStringPtr): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _RegExpLiteralPatternConst(context: KNativePointer, receiver: KNativePointer): KStringPtr {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _RegExpLiteralFlagsConst(context: KNativePointer, receiver: KNativePointer): KInt {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSMappedType(context: KNativePointer, typeParameter: KNativePointer, typeAnnotation: KNativePointer, readonly_arg: KInt, optional_arg: KInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSMappedType(context: KNativePointer, original: KNativePointer, typeParameter: KNativePointer, typeAnnotation: KNativePointer, readonly_arg: KInt, optional_arg: KInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSMappedTypeTypeParameter(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSMappedTypeTypeAnnotation(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSMappedTypeReadonly(context: KNativePointer, receiver: KNativePointer): KInt {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSMappedTypeOptional(context: KNativePointer, receiver: KNativePointer): KInt {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSAnyKeyword(context: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSAnyKeyword(context: KNativePointer, original: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateClassDeclaration(context: KNativePointer, def: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateClassDeclaration(context: KNativePointer, original: KNativePointer, def: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDeclarationDefinition(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDeclarationDefinitionConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ClassDeclarationDecoratorsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSIndexedAccessType(context: KNativePointer, objectType: KNativePointer, indexType: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSIndexedAccessType(context: KNativePointer, original: KNativePointer, objectType: KNativePointer, indexType: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSIndexedAccessTypeObjectTypeConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSIndexedAccessTypeIndexTypeConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSQualifiedName(context: KNativePointer, left: KNativePointer, right: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSQualifiedName(context: KNativePointer, original: KNativePointer, left: KNativePointer, right: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSQualifiedNameLeftConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSQualifiedNameLeft(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSQualifiedNameRightConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSQualifiedNameRight(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSQualifiedNameNameConst(context: KNativePointer, receiver: KNativePointer): KStringPtr {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSQualifiedNameResolveLeftMostQualifiedName(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSQualifiedNameResolveLeftMostQualifiedNameConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateAwaitExpression(context: KNativePointer, argument: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateAwaitExpression(context: KNativePointer, original: KNativePointer, argument: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AwaitExpressionArgumentConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateValidationInfo(context: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateValidationInfo1(context: KNativePointer, m: KStringPtr, p: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ValidationInfoFailConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateContinueStatement(context: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateContinueStatement(context: KNativePointer, original: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateContinueStatement1(context: KNativePointer, ident: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateContinueStatement1(context: KNativePointer, original: KNativePointer, ident: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ContinueStatementIdentConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ContinueStatementIdent(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ContinueStatementTargetConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ContinueStatementHasTargetConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ContinueStatementSetTarget(context: KNativePointer, receiver: KNativePointer, target: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateETSNewMultiDimArrayInstanceExpression(context: KNativePointer, typeReference: KNativePointer, dimensions: BigUint64Array, dimensionsSequenceLength: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateETSNewMultiDimArrayInstanceExpression(context: KNativePointer, original: KNativePointer, typeReference: KNativePointer, dimensions: BigUint64Array, dimensionsSequenceLength: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateETSNewMultiDimArrayInstanceExpression1(context: KNativePointer, other: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateETSNewMultiDimArrayInstanceExpression1(context: KNativePointer, original: KNativePointer, other: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSNewMultiDimArrayInstanceExpressionTypeReference(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSNewMultiDimArrayInstanceExpressionTypeReferenceConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSNewMultiDimArrayInstanceExpressionDimensions(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSNewMultiDimArrayInstanceExpressionDimensionsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSNewMultiDimArrayInstanceExpressionClearPreferredType(context: KNativePointer, receiver: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSNamedTupleMember(context: KNativePointer, label: KNativePointer, elementType: KNativePointer, optional_arg: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSNamedTupleMember(context: KNativePointer, original: KNativePointer, label: KNativePointer, elementType: KNativePointer, optional_arg: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSNamedTupleMemberLabelConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSNamedTupleMemberElementType(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSNamedTupleMemberElementTypeConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSNamedTupleMemberIsOptionalConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateImportExpression(context: KNativePointer, source: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateImportExpression(context: KNativePointer, original: KNativePointer, source: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ImportExpressionSource(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ImportExpressionSourceConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateAstDumper(context: KNativePointer, node: KNativePointer, sourceCode: KStringPtr): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstDumperModifierToString(context: KNativePointer, receiver: KNativePointer, flags: KInt): KStringPtr {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstDumperTypeOperatorToString(context: KNativePointer, receiver: KNativePointer, operatorType: KInt): KStringPtr {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _AstDumperStrConst(context: KNativePointer, receiver: KNativePointer): KStringPtr {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateETSNullType(context: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateETSNullType(context: KNativePointer, original: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateETSUndefinedType(context: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateETSUndefinedType(context: KNativePointer, original: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTypeofExpression(context: KNativePointer, argument: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTypeofExpression(context: KNativePointer, original: KNativePointer, argument: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TypeofExpressionArgumentConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSEnumMember(context: KNativePointer, key: KNativePointer, init: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSEnumMember(context: KNativePointer, original: KNativePointer, key: KNativePointer, init: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSEnumMember1(context: KNativePointer, key: KNativePointer, init: KNativePointer, isGenerated: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSEnumMember1(context: KNativePointer, original: KNativePointer, key: KNativePointer, init: KNativePointer, isGenerated: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSEnumMemberKeyConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSEnumMemberKey(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSEnumMemberInitConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSEnumMemberInit(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSEnumMemberIsGeneratedConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSEnumMemberNameConst(context: KNativePointer, receiver: KNativePointer): KStringPtr {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateSwitchStatement(context: KNativePointer, discriminant: KNativePointer, cases: BigUint64Array, casesSequenceLength: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateSwitchStatement(context: KNativePointer, original: KNativePointer, discriminant: KNativePointer, cases: BigUint64Array, casesSequenceLength: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _SwitchStatementDiscriminantConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _SwitchStatementDiscriminant(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _SwitchStatementSetDiscriminant(context: KNativePointer, receiver: KNativePointer, discriminant: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _SwitchStatementCasesConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _SwitchStatementCases(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateDoWhileStatement(context: KNativePointer, body: KNativePointer, test: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateDoWhileStatement(context: KNativePointer, original: KNativePointer, body: KNativePointer, test: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _DoWhileStatementBodyConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _DoWhileStatementBody(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _DoWhileStatementTestConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _DoWhileStatementTest(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateCatchClause(context: KNativePointer, param: KNativePointer, body: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateCatchClause(context: KNativePointer, original: KNativePointer, param: KNativePointer, body: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateCatchClause1(context: KNativePointer, other: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateCatchClause1(context: KNativePointer, original: KNativePointer, other: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CatchClauseParam(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CatchClauseParamConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CatchClauseBody(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CatchClauseBodyConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CatchClauseIsDefaultCatchClauseConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateSequenceExpression(context: KNativePointer, sequence_arg: BigUint64Array, sequence_argSequenceLength: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateSequenceExpression(context: KNativePointer, original: KNativePointer, sequence_arg: BigUint64Array, sequence_argSequenceLength: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _SequenceExpressionSequenceConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _SequenceExpressionSequence(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateArrowFunctionExpression(context: KNativePointer, func: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateArrowFunctionExpression(context: KNativePointer, original: KNativePointer, func: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateArrowFunctionExpression1(context: KNativePointer, other: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateArrowFunctionExpression1(context: KNativePointer, original: KNativePointer, other: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ArrowFunctionExpressionFunctionConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ArrowFunctionExpressionFunction(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ArrowFunctionExpressionCreateTypeAnnotation(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ArrowFunctionExpressionAnnotations(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ArrowFunctionExpressionAnnotationsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ArrowFunctionExpressionSetAnnotations(context: KNativePointer, receiver: KNativePointer, annotations: BigUint64Array, annotationsSequenceLength: KUInt): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateOmittedExpression(context: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateOmittedExpression(context: KNativePointer, original: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateETSNewClassInstanceExpression(context: KNativePointer, typeReference: KNativePointer, _arguments: BigUint64Array, _argumentsSequenceLength: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateETSNewClassInstanceExpression(context: KNativePointer, original: KNativePointer, typeReference: KNativePointer, _arguments: BigUint64Array, _argumentsSequenceLength: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateETSNewClassInstanceExpression1(context: KNativePointer, other: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateETSNewClassInstanceExpression1(context: KNativePointer, original: KNativePointer, other: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSNewClassInstanceExpressionGetTypeRefConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSNewClassInstanceExpressionGetArguments(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSNewClassInstanceExpressionGetArgumentsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSNewClassInstanceExpressionSetArguments(context: KNativePointer, receiver: KNativePointer, _arguments: BigUint64Array, _argumentsSequenceLength: KUInt): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSNewClassInstanceExpressionAddToArgumentsFront(context: KNativePointer, receiver: KNativePointer, expr: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSAsExpression(context: KNativePointer, expression: KNativePointer, typeAnnotation: KNativePointer, isConst: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSAsExpression(context: KNativePointer, original: KNativePointer, expression: KNativePointer, typeAnnotation: KNativePointer, isConst: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSAsExpressionExprConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSAsExpressionExpr(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSAsExpressionSetExpr(context: KNativePointer, receiver: KNativePointer, expr: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSAsExpressionIsConstConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSAsExpressionSetUncheckedCast(context: KNativePointer, receiver: KNativePointer, isUncheckedCast: KBoolean): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSAsExpressionTypeAnnotationConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSAsExpressionSetTsTypeAnnotation(context: KNativePointer, receiver: KNativePointer, typeAnnotation: KNativePointer): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateForUpdateStatement(context: KNativePointer, init: KNativePointer, test: KNativePointer, update: KNativePointer, body: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ForUpdateStatementInit(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ForUpdateStatementInitConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ForUpdateStatementTest(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ForUpdateStatementTestConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ForUpdateStatementUpdateConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ForUpdateStatementBody(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ForUpdateStatementBodyConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateETSTypeReferencePart(context: KNativePointer, name: KNativePointer, typeParams: KNativePointer, prev: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateETSTypeReferencePart(context: KNativePointer, original: KNativePointer, name: KNativePointer, typeParams: KNativePointer, prev: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateETSTypeReferencePart1(context: KNativePointer, name: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateETSTypeReferencePart1(context: KNativePointer, original: KNativePointer, name: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSTypeReferencePartPrevious(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSTypeReferencePartPreviousConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSTypeReferencePartName(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSTypeReferencePartTypeParams(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSTypeReferencePartNameConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSTypeReferencePartGetIdent(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSReExportDeclarationGetETSImportDeclarationsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSReExportDeclarationGetETSImportDeclarations(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSReExportDeclarationGetProgramPathConst(context: KNativePointer, receiver: KNativePointer): KStringPtr {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateETSPrimitiveType(context: KNativePointer, type: KInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateETSPrimitiveType(context: KNativePointer, original: KNativePointer, type: KInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSPrimitiveTypeGetPrimitiveTypeConst(context: KNativePointer, receiver: KNativePointer): KInt {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TypeNodeAnnotations(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TypeNodeAnnotationsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TypeNodeSetAnnotations(context: KNativePointer, receiver: KNativePointer, annotations: BigUint64Array, annotationsSequenceLength: KUInt): void {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateNewExpression(context: KNativePointer, callee: KNativePointer, _arguments: BigUint64Array, _argumentsSequenceLength: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateNewExpression(context: KNativePointer, original: KNativePointer, callee: KNativePointer, _arguments: BigUint64Array, _argumentsSequenceLength: KUInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _NewExpressionCalleeConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _NewExpressionArgumentsConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSParameterProperty(context: KNativePointer, accessibility: KInt, parameter: KNativePointer, readonly_arg: KBoolean, isStatic: KBoolean, isExport: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSParameterProperty(context: KNativePointer, original: KNativePointer, accessibility: KInt, parameter: KNativePointer, readonly_arg: KBoolean, isStatic: KBoolean, isExport: KBoolean): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSParameterPropertyAccessibilityConst(context: KNativePointer, receiver: KNativePointer): KInt {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSParameterPropertyReadonlyConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSParameterPropertyIsStaticConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSParameterPropertyIsExportConst(context: KNativePointer, receiver: KNativePointer): KBoolean {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _TSParameterPropertyParameterConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateETSWildcardType(context: KNativePointer, typeReference: KNativePointer, flags: KInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateETSWildcardType(context: KNativePointer, original: KNativePointer, typeReference: KNativePointer, flags: KInt): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSWildcardTypeTypeReference(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _ETSWildcardTypeTypeReferenceConst(context: KNativePointer, receiver: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateTSThisType(context: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _UpdateTSThisType(context: KNativePointer, original: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateInterfaceDecl(context: KNativePointer, name: KStringPtr): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateInterfaceDecl1(context: KNativePointer, name: KStringPtr, declNode: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
    _CreateFunctionDecl(context: KNativePointer, name: KStringPtr, node: KNativePointer): KNativePointer {
        throw new Error("This methods was not overloaded by native module initialization")
    }
}