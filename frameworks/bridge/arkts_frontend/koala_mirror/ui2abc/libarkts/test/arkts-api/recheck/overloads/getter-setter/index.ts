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
 
import * as arkts from "../../../../../src/arkts-api"

class InsertParameterToType extends arkts.AbstractVisitor {
    visitor(beforeChildren: arkts.ETSModule): arkts.ETSModule
    visitor(beforeChildren: arkts.AstNode): arkts.AstNode {
        const node = this.visitEachChild(beforeChildren)
        if (arkts.isETSFunctionType(node)) {
            return arkts.factory.createETSFunctionType(
                node.typeParams,
                [
                    arkts.factory.createETSParameterExpression(
                        arkts.factory.createIdentifier("createdParam"),
                        false,
                        undefined,
                        arkts.factory.createETSPrimitiveType(arkts.Es2pandaPrimitiveType.PRIMITIVE_TYPE_BOOLEAN),
                        undefined
                    ),
                    ...node.params
                ],
                node.returnType,
                node.isExtensionFunction,
                node.flags,
                node.annotations,
            )
        }
        return node
    }
}

export function insertParameterToType(program: arkts.Program) {
    return (new InsertParameterToType()).visitor(program.astNode)
}
