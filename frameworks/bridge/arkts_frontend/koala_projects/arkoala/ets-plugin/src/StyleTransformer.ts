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

import * as ts from '@koalaui/ets-tsc'
import { AbstractVisitor } from './AbstractVisitor'
import { ExtensionStylesTransformer } from './ExtensionStylesTransformer'
import { Importer } from './Importer'
import {
    bindThis,
    createThisFieldAccess,
    getDeclarationsByNode,
    id,
    isUndefined,
    undefinedValue
} from './ApiUtils'
import { CallTable, extendsLikeFunctionName, isBuilderLambdaCall, isBuiltinComponentName, isStructCall, RewriteNames, styledInstance } from './utils'

enum ExtensionStyleRewrite {
    Regular,
    StylesFunction,
    ExtendFunction,
    AnimatableExtendFunction,
    StylesMethod,
    ExtendMethod,
    AnimatableExtendMethod
}

export class StyleTransformer extends AbstractVisitor {
    constructor(
        sourceFile: ts.SourceFile,
        ctx: ts.TransformationContext,
        private typechecker: ts.TypeChecker,
        public importer: Importer,
        private styleFunctionTransformer: ExtensionStylesTransformer,
        private callTable: CallTable
    ) {
        super(sourceFile, ctx)
    }

    private isStylesFunction(name: string): boolean {
        return this.styleFunctionTransformer.stylesFunctions.includes(name)
    }

    private isExtendFunction(name: string): boolean {
        return this.styleFunctionTransformer.extendFunctions.includes(name)
    }

    private isAnimatableExtendFunction(name: string): boolean {
        return this.styleFunctionTransformer.animatableExtendFunctions.includes(name)
    }

    private isStylesMethod(name: ts.MethodDeclaration): boolean {
        return this.styleFunctionTransformer.stylesMethods.includes(name)
    }

    private isExtendMethod(name: ts.MethodDeclaration): boolean {
        return this.styleFunctionTransformer.extendMethods.includes(name)
    }

    private isAnimatableExtendMethod(name: ts.MethodDeclaration): boolean {
        return this.styleFunctionTransformer.animatableExtendMethods.includes(name)
    }

    // Do we need classes here, like we have for property initializers?
    private classifyExtensionStyleRewrite(name: ts.Identifier, nameExtension: ts.Identifier): ExtensionStyleRewrite {
        const nameString = ts.idText(name)
        const nameOfExtendsFunction = extendsLikeFunctionName(nameString, ts.idText(nameExtension))
        if (this.isStylesFunction(nameString)) return ExtensionStyleRewrite.StylesFunction
        if (this.isExtendFunction(nameOfExtendsFunction)) return ExtensionStyleRewrite.ExtendFunction
        if (this.isAnimatableExtendFunction(nameOfExtendsFunction)) return ExtensionStyleRewrite.AnimatableExtendFunction

        const declaration = getDeclarationsByNode(this.typechecker, name)[0]
        if (!declaration) return ExtensionStyleRewrite.Regular
        if (!ts.isMethodDeclaration(declaration)) return ExtensionStyleRewrite.Regular
        const originalDeclaration = ts.getOriginalNode(declaration) as ts.MethodDeclaration

        if (this.isStylesMethod(originalDeclaration)) return ExtensionStyleRewrite.StylesMethod
        if (this.isExtendMethod(originalDeclaration)) return ExtensionStyleRewrite.ExtendMethod
        if (this.isAnimatableExtendMethod(originalDeclaration)) return ExtensionStyleRewrite.AnimatableExtendMethod

        return ExtensionStyleRewrite.Regular
    }

    transformEtsComponent(
        node: ts.CallExpression,
        dot: ts.PropertyAccessExpression,
        originalNode: ts.EtsComponentExpression | ts.CallExpression,
        receiverName: ts.Identifier,
        args: ts.NodeArray<ts.Expression>,
        isEts: boolean
    ): ts.EtsComponentExpression | ts.CallExpression {
        const firstEtsArg: ts.Expression = args[0]
        const firstEtsArgOrUndefined = isUndefined(firstEtsArg) ? undefined : firstEtsArg
        const restEtsArgs = args.slice(1)

        const rewrite = this.classifyExtensionStyleRewrite(dot.name as ts.Identifier, receiverName)

        const propertyName = dot.name

        const maybeSyntheticName = this.maybeSyntheticFunctionName(rewrite, propertyName, receiverName)
        const styleApplicatorOrOriginalPropertyName = this.maybeStyleApplicator(rewrite, propertyName)

        const newDot = ts.factory.updatePropertyAccessExpression(
            dot,
            firstEtsArgOrUndefined ?? id(styledInstance),
            styleApplicatorOrOriginalPropertyName
        )

        const detachedStyle = ts.factory.updateCallExpression(
            node,
            newDot,
            undefined,
            this.maybePrependStyleFunctionArgument(rewrite, maybeSyntheticName, node.arguments)
        )

        if (isEts) {
            const ets = originalNode as ts.EtsComponentExpression
            return ts.factory.updateEtsComponentExpression(
                ets,
                receiverName,
                [detachedStyle, ...restEtsArgs],
                ets.body
            )
        }

        const call = originalNode as ts.CallExpression
        return ts.factory.updateCallExpression(
            call,
            receiverName,
            undefined,
            [detachedStyle, ...restEtsArgs],
        )
    }

    private maybeStyleApplicator(rewrite: ExtensionStyleRewrite, propertyName: ts.MemberName): ts.MemberName {
        switch (rewrite) {
            case ExtensionStyleRewrite.StylesFunction:
            case ExtensionStyleRewrite.ExtendFunction:
            case ExtensionStyleRewrite.StylesMethod:
                return id(RewriteNames.ApplyStyle)
            case ExtensionStyleRewrite.AnimatableExtendFunction:
                return id(RewriteNames.ApplyAnimatableExtend)
            case ExtensionStyleRewrite.ExtendMethod:
            case ExtensionStyleRewrite.AnimatableExtendMethod:
                console.log("TODO: need an implementatyion of @Extend applied to methods")
                return propertyName
            default:
                return propertyName
        }
    }

    private maybeSyntheticFunctionName(rewrite: ExtensionStyleRewrite, propertyName: ts.MemberName, componentName: ts.Identifier): ts.Identifier {
        switch (rewrite) {
            case ExtensionStyleRewrite.ExtendFunction:
            case ExtensionStyleRewrite.AnimatableExtendFunction:
            case ExtensionStyleRewrite.ExtendMethod:
            case ExtensionStyleRewrite.AnimatableExtendMethod:
                const propertyNameString = ts.idText(propertyName)
                const componentNameString = ts.idText(componentName)
                return id(extendsLikeFunctionName(propertyNameString, componentNameString))
            default:
                return propertyName as ts.Identifier
        }
    }

    private maybePrependStyleFunctionArgument(rewrite: ExtensionStyleRewrite, maybeSyntheticName: ts.MemberName, nodeArguments: ts.NodeArray<ts.Expression>): readonly ts.Expression[] {
        switch (rewrite) {
            case ExtensionStyleRewrite.StylesFunction:
            case ExtensionStyleRewrite.ExtendFunction:
            case ExtensionStyleRewrite.AnimatableExtendFunction:
                return [maybeSyntheticName, ...nodeArguments]
            case ExtensionStyleRewrite.StylesMethod:
            case ExtensionStyleRewrite.ExtendMethod:
            case ExtensionStyleRewrite.AnimatableExtendMethod:
                return [bindThis(createThisFieldAccess(maybeSyntheticName)), ...nodeArguments]
            default:
                return nodeArguments
        }
    }

    // Assumption: Ets nodes were preprocessed to have "undefined"
    // as their first argument.
    //
    // We need to rewrite
    //   ets(undefined, some, args).foo().bar().qux()
    //   ets(instance.foo().bar().qux(), some, args)
    // No style ets is left as is:
    //   ets(some, args)
    // The trick here is that ets() is the deepest in the PropertyAccessExpression tree.
    visitor(beforeChildren: ts.Node): ts.Node {
        const node = this.visitEachChild(beforeChildren)

        // Recognize ets().foo()
        if (ts.isCallExpression(node) &&
            ts.isPropertyAccessExpression(node.expression) &&
            ts.isEtsComponentExpression(node.expression.expression)) {
            const dot = node.expression
            const ets = node.expression.expression
            return this.transformEtsComponent(node, dot, ets, ets.expression as ts.Identifier, ets.arguments, true)
        }
        // Recognize ets().foo()
        if (ts.isCallExpression(node) &&
            ts.isPropertyAccessExpression(node.expression) &&
            ts.isCallExpression(node.expression.expression) &&
                (isBuilderLambdaCall(this.callTable, node.expression.expression) ||
                isStructCall(this.callTable, node.expression.expression))
        ) {
            const dot = node.expression
            const call = node.expression.expression
            return this.transformEtsComponent(node, dot, call, call.expression as ts.Identifier, call.arguments, false)
        }

        return node
    }
}

// Preprocess Ets nodes by providing an undefined as the first arg
// so that we don't have to think if it is already provided later
export class EtsFirstArgTransformer extends AbstractVisitor {
    constructor(
        sourceFile: ts.SourceFile,
        ctx: ts.TransformationContext,
        public importer: Importer,
        private callTable: CallTable
    ) {
        super(sourceFile, ctx)
    }

    visitor(beforeChildren: ts.Node): ts.Node {
        const node = this.visitEachChild(beforeChildren)
        if (ts.isEtsComponentExpression(node)) {
            const casted = this.castIfComponentInitialization(node)
            return ts.factory.updateEtsComponentExpression(
                casted,
                casted.expression,
                [undefinedValue(), ...casted.arguments],
                casted.body
            )
        }
        if (ts.isCallExpression(node) &&
                (isBuilderLambdaCall(this.callTable, node) ||
                isStructCall(this.callTable, node))
        ) {
            return ts.factory.updateCallExpression(
                node,
                node.expression,
                node.typeArguments,
                [undefinedValue(), ...node.arguments]
            )
        }
        return node
    }

    private castIfComponentInitialization(node: ts.EtsComponentExpression)  {
        if (!this.importer.isArkts()) return node
        if (!ts.isIdentifier(node.expression)) return node
        if (!isBuiltinComponentName(this.ctx, ts.idText(node.expression))) return node
        if (node.arguments.length !== 1) return node
        const singleArgument = node.arguments[0]
        if (!ts.isObjectLiteralExpression(singleArgument)) return node

        let componentName = node.expression.getText()

        /*
            Workaround for PageTransitionEnter/PageTransitionExit
         */
        if (ts.idText(node.expression).includes(`PageTransition`)) {
            componentName = `PageTransition`
        }

        return ts.factory.updateEtsComponentExpression(
            node,
            node.expression,
            [ts.factory.createAsExpression(
                singleArgument,
                ts.factory.createTypeReferenceNode(
                    this.importer.withAdaptorImport(`${componentName}Options`)
                )
            )],
            node.body
        )
    }
}
