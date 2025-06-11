/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
import { AbstractVisitor } from './AbstractVisitor';

export class AsExpressionTransformer extends AbstractVisitor {
    constructor(
        typeChecker: ts.TypeChecker,
        ctx: ts.TransformationContext,
    ) {
        super(ctx)
        this.typeMap = new Map<string, string>([
            [ 'byte',       'Byte'  ],
            [ 'short',      'Short' ],
            [ 'int',        'Int'   ],
            [ 'int32',      'Int'   ],
            [ 'int64',      'Long'  ],
            [ 'float',      'Float' ],
            [ 'float32',    'Float' ],
            [ 'float64',    'Double'],
            [ 'double',     'Double']
        ])
        this.typeChecker = typeChecker
    }

    typeChecker : ts.TypeChecker
    typeMap : Map<string, string>

    transformAsExpression(node: ts.AsExpression): ts.Node {
        if (!ts.isTypeReferenceNode(node.type)) {
            return node;
        }

        let typeRef = node.type as ts.TypeReferenceNode
        if (!ts.isIdentifier(typeRef.typeName)) {
            return node;
        }

        let typeName = ts.idText(typeRef.typeName as ts.Identifier)
        let expr = node.expression
        let type = this.typeChecker.getTypeAtLocation(expr)

        if (!this.typeMap.has(typeName)) {
            return node;
        }

        if (type.isUnion() || ts.Utils.isAnyType(type)) {
            return node;
        }

        let obj = ts.factory.createParenthesizedExpression(expr)
        let prop = ts.factory.createIdentifier("to" + this.typeMap.get(typeName))
        let callee = ts.factory.createPropertyAccessExpression(obj, prop)
        return ts.factory.createCallExpression(callee, undefined, undefined)
    }

    visitor(node: ts.Node): ts.Node {
        let transformed = node
        if (ts.isAsExpression(node)) {
            transformed = this.visitEachChild(this.transformAsExpression(node))
        }
        return this.visitEachChild(transformed)
    }
}
