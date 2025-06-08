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

import * as arkts from "@koalaui/libarkts"
import { builderLambdaFunctionName } from "./builder-lambda-transformer"

function lambdaReturnFilter(node: arkts.AstNode): arkts.AstNode {
    if (!arkts.isScriptFunction(node)) return node
    if (node.returnTypeAnnotation != undefined)return node
    const body = node.body
    if (!body) return node
    if (!arkts.isBlockStatement(body)) return node
    if (body.statements.length != 1) return node
    const statement = body.statements[0]
    if (!arkts.isReturnStatement(statement)) return node
    if (!statement.argument) return node
    const expr = statement.argument
    if (!arkts.isETSNewClassInstanceExpression(expr)) return node
    const typeReference = expr.typeRef
    if (!arkts.isETSTypeReference(typeReference)) return node
    if (!arkts.isETSTypeReferencePart(typeReference.part)) return node
    const part = typeReference.part
    if (part.typeParams) return node
    const typeName = typeReference.baseName?.name
    if (!typeName) return node

    return arkts.factory.updateScriptFunction(
        node,
        node.body,
        node.typeParams,
        node.params,
        arkts.factory.createETSTypeReference(
            arkts.factory.createETSTypeReferencePart(
                arkts.factory.createIdentifier(typeName),
                undefined,
                undefined
            )
        ),
        node.hasReceiver,
        node.flags,
        node.modifierFlags,
        node.id,
        node.annotations
    )
}

// es2panda creates the following instantiate factory:
//   StructBase.$_instantiate(() => new Foo())
// note that the type is not given.
// That later causes issues with memo rewrites so we rewrite it to
//   StructBase.$_instantiate((): Foo => new Foo())
export class InstantiateFactoryHelper extends arkts.AbstractVisitor {
    visitor(beforeChildren: arkts.AstNode): arkts.AstNode {
        const node = this.visitEachChild(beforeChildren)
        return lambdaReturnFilter(node)
    }
}
