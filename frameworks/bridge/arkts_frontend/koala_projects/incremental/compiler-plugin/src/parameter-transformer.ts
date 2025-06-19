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

import * as ts from '@koalaui/ets-tsc';
import { ScopedVisitor } from './ScopedVisitor';
import {
    FunctionKind,
    Tracer,
    isTrackableParameter,
    parameterStateName as localStateName,
    PositionalIdTracker,
    runtimeIdentifier,
    RuntimeNames,
    isFunctionOrMethod,
    getDeclarationsByNode,
    isMemoKind,
    asString,
} from "./util"

export class ParameterTransformer extends ScopedVisitor<void> {
    constructor(
        public tracer: Tracer,
        public typechecker: ts.TypeChecker,
        public sourceFile: ts.SourceFile,
        public positionalIdTracker: PositionalIdTracker,
        public functionTable: Map<ts.SignatureDeclarationBase, FunctionKind>,
        ctx: ts.TransformationContext
    ) {
        super(functionTable, ctx)
    }

    transformParameterUse(node: ts.Identifier): ts.PropertyAccessExpression {
        const originalName = ts.idText(node)
        const newName = localStateName(originalName)

        return ts.factory.createPropertyAccessExpression(
            ts.factory.createIdentifier(newName),
            runtimeIdentifier(RuntimeNames.VALUE)
        )
    }

    isTrackedParameter(node: ts.Identifier): boolean {
        const declarations = getDeclarationsByNode(this.typechecker, node)
        const declaration = declarations[0]
        if (!declaration) return false
        if (!ts.isParameter(declaration)) return false
        if (!isTrackableParameter(this.sourceFile, declaration)) return false

        const func = declaration.parent
        if (!isFunctionOrMethod(func)) return false

        const originalFunc = ts.getOriginalNode(func) as ts.FunctionLikeDeclarationBase
        const kind = this.functionTable.get(originalFunc)

        return isMemoKind(kind)
    }

    visitor(node: ts.Node): ts.Node {
        if (ts.isParameter(node)) {
            return ts.factory.updateParameterDeclaration(
                node,
                node.modifiers,
                node.dotDotDotToken,
                node.name,
                node.questionToken,
                node.type,
                node.initializer ?
                    this.visitEachChild(node.initializer) as ts.Expression :
                    undefined
            )
        }
        if (isFunctionOrMethod(node)) {
            const kind = this.declarationKind(node)
            return this.withFunctionScope(kind, undefined, ()=>this.visitEachChild(node))
        }
        if (ts.isIdentifier(node) && this.isTrackedParameter(node)) {
            return this.transformParameterUse(node)
        }
        return this.visitEachChild(node)
    }
}
