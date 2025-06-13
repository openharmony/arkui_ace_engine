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
    Es2pandaAstNodeType,
    KNativePointer,
    nodeByType,
    ArktsObject,
    unpackString
} from "../../reexport-for-generated"

import { AnnotatedExpression } from "./AnnotatedExpression"
import { Expression } from "./Expression"
import { Decorator } from "./Decorator"
import { ValidationInfo } from "./ValidationInfo"
import { TypeNode } from "./TypeNode"
export class ObjectExpression extends AnnotatedExpression {
     constructor(pointer: KNativePointer) {
        super(pointer)
        console.warn("Warning: stub node ObjectExpression")
    }
    get properties(): readonly Expression[] {
        return unpackNodeArray(global.generatedEs2panda._ObjectExpressionPropertiesConst(global.context, this.peer))
    }
    get isDeclaration(): boolean {
        return global.generatedEs2panda._ObjectExpressionIsDeclarationConst(global.context, this.peer)
    }
    get isOptional(): boolean {
        return global.generatedEs2panda._ObjectExpressionIsOptionalConst(global.context, this.peer)
    }
    get decorators(): readonly Decorator[] {
        return unpackNodeArray(global.generatedEs2panda._ObjectExpressionDecoratorsConst(global.context, this.peer))
    }
    /** @deprecated */
    setDeclaration(): this {
        global.generatedEs2panda._ObjectExpressionSetDeclaration(global.context, this.peer)
        return this
    }
    /** @deprecated */
    setOptional(optional_arg: boolean): this {
        global.generatedEs2panda._ObjectExpressionSetOptional(global.context, this.peer, optional_arg)
        return this
    }
    get typeAnnotation(): TypeNode | undefined {
        return unpackNode(global.generatedEs2panda._ObjectExpressionTypeAnnotationConst(global.context, this.peer))
    }
    /** @deprecated */
    setTsTypeAnnotation(typeAnnotation: TypeNode): this {
        global.generatedEs2panda._ObjectExpressionSetTsTypeAnnotation(global.context, this.peer, passNode(typeAnnotation))
        return this
    }
}
export function isObjectExpression(node: AstNode): node is ObjectExpression {
    return node instanceof ObjectExpression
}