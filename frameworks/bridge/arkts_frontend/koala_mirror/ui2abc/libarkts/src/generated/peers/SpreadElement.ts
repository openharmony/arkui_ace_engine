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

import { AnnotatedExpression } from "./AnnotatedExpression"
import { Decorator } from "./Decorator"
import { Es2pandaAstNodeType } from "./../Es2pandaEnums"
import { Expression } from "./Expression"
import { TypeNode } from "./TypeNode"
import { ValidationInfo } from "./ValidationInfo"
export class SpreadElement extends AnnotatedExpression {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 163)
        super(pointer)
    }
    static createSpreadElement(nodeType: Es2pandaAstNodeType, argument?: Expression): SpreadElement {
        return new SpreadElement(global.generatedEs2panda._CreateSpreadElement(global.context, nodeType, passNode(argument)))
    }
    static updateSpreadElement(original: SpreadElement | undefined, nodeType: Es2pandaAstNodeType, argument?: Expression): SpreadElement {
        return new SpreadElement(global.generatedEs2panda._UpdateSpreadElement(global.context, passNode(original), nodeType, passNode(argument)))
    }
    get argument(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._SpreadElementArgument(global.context, this.peer))
    }
    get isOptional(): boolean {
        return global.generatedEs2panda._SpreadElementIsOptionalConst(global.context, this.peer)
    }
    get decorators(): readonly Decorator[] {
        return unpackNodeArray(global.generatedEs2panda._SpreadElementDecoratorsConst(global.context, this.peer))
    }
    /** @deprecated */
    setOptional(optional_arg: boolean): this {
        global.generatedEs2panda._SpreadElementSetOptional(global.context, this.peer, optional_arg)
        return this
    }
    get validateExpression(): ValidationInfo | undefined {
        return new ValidationInfo(global.generatedEs2panda._SpreadElementValidateExpression(global.context, this.peer))
    }
    get typeAnnotation(): TypeNode | undefined {
        return unpackNode(global.generatedEs2panda._SpreadElementTypeAnnotationConst(global.context, this.peer))
    }
    /** @deprecated */
    setTsTypeAnnotation(typeAnnotation?: TypeNode): this {
        global.generatedEs2panda._SpreadElementSetTsTypeAnnotation(global.context, this.peer, passNode(typeAnnotation))
        return this
    }
}
export function isSpreadElement(node: object | undefined): node is SpreadElement {
    return node instanceof SpreadElement
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_SPREAD_ELEMENT)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_SPREAD_ELEMENT, (peer: KNativePointer) => new SpreadElement(peer))
}