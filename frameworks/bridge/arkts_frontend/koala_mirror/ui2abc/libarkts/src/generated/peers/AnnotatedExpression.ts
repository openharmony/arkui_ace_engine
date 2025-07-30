/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
    global,
    passNode,
    passNodeArray,
    unpackNonNullableNode,
    unpackNode,
    unpackNodeArray,
    assertValidPeer,
    AstNode,
    KNativePointer,
    nodeByType,
    ArktsObject,
    unpackString
} from "../../reexport-for-generated"

import { Expression } from "./Expression"
import { TypeNode } from "./TypeNode"
export class AnnotatedExpression extends Expression {
    constructor(pointer: KNativePointer) {
        super(pointer)
    }
    get typeAnnotation(): TypeNode | undefined {
        return unpackNode(global.generatedEs2panda._AnnotatedExpressionTypeAnnotationConst(global.context, this.peer))
    }
    /** @deprecated */
    setTsTypeAnnotation(typeAnnotation?: TypeNode): this {
        global.generatedEs2panda._AnnotatedExpressionSetTsTypeAnnotation(global.context, this.peer, passNode(typeAnnotation))
        return this
    }
}
export function isAnnotatedExpression(node: object | undefined): node is AnnotatedExpression {
    return node instanceof AnnotatedExpression
}