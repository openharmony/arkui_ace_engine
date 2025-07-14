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
 
import * as arkts from "../../../../src/arkts-api"

class ConstructorWithOverload extends arkts.AbstractVisitor {
    visitor(beforeChildren: arkts.BlockStatement): arkts.BlockStatement
    visitor(beforeChildren: arkts.AstNode): arkts.AstNode {
        const node = this.visitEachChild(beforeChildren)
        if (arkts.isScriptFunction(node) && node.id?.name == "constructor") {
            return arkts.factory.updateScriptFunction(
                node,
                arkts.factory.createBlockStatement(
                    [

                        arkts.factory.createIfStatement(
                            arkts.factory.createBooleanLiteral(true),
                            arkts.factory.createReturnStatement(),
                            undefined
                        ),
                        ...(arkts.isBlockStatement(node.body) ? node.body.statements : []),
                    ]
                ),
                node.typeParams,
                node.params,
                node.returnTypeAnnotation,
                node.hasReceiver,
                node.flags,
                node.modifierFlags,
                node.id,
                node.annotations
            )
        }
        return node
    }
}

export function constructorWithOverload(program: arkts.Program) {
    program.setAst(new ConstructorWithOverload().visitor(program.ast))
}
