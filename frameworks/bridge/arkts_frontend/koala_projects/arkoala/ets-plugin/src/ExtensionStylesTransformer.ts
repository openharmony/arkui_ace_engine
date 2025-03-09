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

import * as ts from '@koalaui/ets-tsc'
import { AbstractVisitor } from './AbstractVisitor'
import { Importer } from './Importer'
import {
    ExtendDecorator,
    StylesDecorator,
    typeParameterExtendsType,
    adaptorComponentName,
    AnimatableExtendDecorator,
    getAnnotationArgument,
    getSingleExpression,
    dropStylesLike,
    ArkCommonMethodInterface,
    T_TypeParameter,
    Instance,
    CommonInstance,
    extendsLikeFunctionName,
    prependMemoCommentIfArkoala
} from './utils'
import { Any, getDecorator, hasDecorator, id, parameter } from './ApiUtils'

function rewriteStyles(node: ts.FunctionDeclaration, importer: Importer): ts.FunctionDeclaration {
    const singleExpression = getSingleExpression(node.body)
    if (!singleExpression) return node // unexpected

    const firstParameter = parameter(
        CommonInstance,
        ts.factory.createTypeReferenceNode(
            T_TypeParameter
        )
    )

    const declaration = ts.factory.createFunctionDeclaration(
        // @Styles dropped as "Illegal decorator" because of create instead of update
        // We could not make updateFunctionDecl() remove the illegal decorators
        node.modifiers,
        node.asteriskToken,
        node.name,
        [typeParameterExtendsType(
            T_TypeParameter,
            importer.withAdaptorImport(ArkCommonMethodInterface),
            [T_TypeParameter]
        )],
        [firstParameter, ...node.parameters],
        ts.factory.createTypeReferenceNode(T_TypeParameter),
        ts.factory.createBlock([
            ts.factory.createReturnStatement(singleExpression)
        ], true)
    )

    return prependMemoCommentIfArkoala(declaration, importer)
}

function rewriteStylesMethod(node: ts.MethodDeclaration, importer: Importer): ts.MethodDeclaration {
    const singleExpression = getSingleExpression(node.body)
    if (!singleExpression) return node // unexpected

    const firstParameter = parameter(
        CommonInstance,
        ts.factory.createTypeReferenceNode(
            T_TypeParameter
        )
    )

    const declaration = ts.factory.createMethodDeclaration(
        dropStylesLike(node.modifiers),
        node.asteriskToken,
        node.name,
        node.questionToken,
        [typeParameterExtendsType(
            T_TypeParameter,
            importer.withAdaptorImport(ArkCommonMethodInterface),
            [T_TypeParameter]
        )],
        [firstParameter, ...node.parameters],
        ts.factory.createTypeReferenceNode(T_TypeParameter),
        ts.factory.createBlock([
            ts.factory.createReturnStatement(singleExpression)
        ], true)
    )

    return prependMemoCommentIfArkoala(declaration, importer)
}

function rewriteExtend(node: ts.FunctionDeclaration, extendType: string, importer: Importer): ts.FunctionDeclaration {
    const firstParameter = parameter(
        extendType + Instance,
        ts.factory.createTypeReferenceNode(T_TypeParameter)
    )

    const singleExpressionStatement = node.body?.statements?.[0]
    if (!singleExpressionStatement) return node
    if (!ts.isExpressionStatement(singleExpressionStatement)) return node

    const declaration = ts.factory.createFunctionDeclaration(
        // @Extend dropped as "Illegal decorator" because of create instead of update
        // We could not make updateFunctionDecl() remove the illegal decorators
        node.modifiers,
        node.asteriskToken,
        id(extendsLikeFunctionName(ts.idText(node.name!), extendType)),
        [typeParameterExtendsType(
            T_TypeParameter,
            adaptorComponentName(extendType),
            []
        )],
        [firstParameter, ...node.parameters],
        ts.factory.createTypeReferenceNode(T_TypeParameter),
        ts.factory.createBlock([
            ts.factory.createReturnStatement(singleExpressionStatement.expression)
        ], true)
    )
    return prependMemoCommentIfArkoala(declaration, importer)
}

function rewriteExtendMethod(node: ts.MethodDeclaration, extendType: string, importer: Importer): ts.MethodDeclaration {
    const firstParameter = parameter(
        extendType + Instance,
        ts.factory.createTypeReferenceNode(T_TypeParameter)
    )

    const singleExpressionStatement = node.body?.statements?.[0]
    if (!singleExpressionStatement) return node
    if (!ts.isExpressionStatement(singleExpressionStatement)) return node

    const declaration = ts.factory.updateMethodDeclaration(
        node,
        dropStylesLike(node.modifiers)?.concat(ts.factory.createToken(ts.SyntaxKind.StaticKeyword)),
        node.asteriskToken,
        id(extendsLikeFunctionName(ts.idText(node.name! as ts.Identifier), extendType)),
        node.questionToken,
        [typeParameterExtendsType(T_TypeParameter, adaptorComponentName(extendType), [])],
        [firstParameter, ...node.parameters],
        ts.factory.createTypeReferenceNode(T_TypeParameter),
        ts.factory.createBlock([
            ts.factory.createReturnStatement(singleExpressionStatement.expression)
        ], true)
    )
    return prependMemoCommentIfArkoala(declaration, importer)
}

export class ExtensionStylesTransformer extends AbstractVisitor {
    public stylesFunctions: string[] = []
    public extendFunctions: string[] = []
    public animatableExtendFunctions: string[] = []
    public stylesMethods: ts.Node[] = []
    public extendMethods: ts.Node[] = []
    public animatableExtendMethods: ts.Node[] = []

    constructor(
        sourceFile: ts.SourceFile,
        ctx: ts.TransformationContext,
        public typechecker: ts.TypeChecker,
        public importer: Importer
    ) {
        super(sourceFile, ctx)
    }

    visitor(beforeChildren: ts.Node): ts.Node {
        const node = this.visitEachChild(beforeChildren)

        if (ts.isFunctionDeclaration(node)) {
            if (hasDecorator(node, StylesDecorator)) {
                this.stylesFunctions.push(ts.idText(node.name!))
                return rewriteStyles(node, this.importer)
            }
            if (hasDecorator(node, ExtendDecorator)) {
                const decorator = getDecorator(node, ExtendDecorator)!
                const extensibleType = ts.idText(getAnnotationArgument(decorator)!)
                this.extendFunctions.push(extendsLikeFunctionName(ts.idText(node.name!), extensibleType))
                return rewriteExtend(node, extensibleType, this.importer)
            }
            if (hasDecorator(node, AnimatableExtendDecorator)) {
                const decorator = getDecorator(node, AnimatableExtendDecorator)!
                const extensibleType = ts.idText(getAnnotationArgument(decorator)!)
                this.animatableExtendFunctions.push(extendsLikeFunctionName(ts.idText(node.name!), extensibleType))
                return rewriteExtend(node, extensibleType, this.importer)
            }
        }
        if (ts.isMethodDeclaration(node)) {
            if (hasDecorator(node, StylesDecorator)) {
                this.stylesMethods.push(ts.getOriginalNode(node))
                return rewriteStylesMethod(node, this.importer)
            }
            if (hasDecorator(node, ExtendDecorator)) {
                const decorator = getDecorator(node, ExtendDecorator)!
                const extensibleType = ts.idText(getAnnotationArgument(decorator)!)
                this.extendMethods.push(ts.getOriginalNode(node))
                return rewriteExtendMethod(node, extensibleType, this.importer)
            }
            if (hasDecorator(node, AnimatableExtendDecorator)) {
                const decorator = getDecorator(node, AnimatableExtendDecorator)!
                const extensibleType = ts.idText(getAnnotationArgument(decorator)!)
                this.animatableExtendMethods.push(ts.getOriginalNode(node))
                return rewriteExtendMethod(node, extensibleType, this.importer)
            }
        }
        if (ts.isIdentifier(node)) {
            if (ts.idText(node) == CommonInstance) {
                return id(CommonInstance)
            }
            if (ts.idText(node).endsWith(Instance)) {
                const instanceName = ts.idText(node).slice(0, -8)
                return id(instanceName + Instance)
            }
        }

        return node
    }
}
