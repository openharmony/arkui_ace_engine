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

import { Es2pandaAstNodeType } from "./../Es2pandaEnums"
import { Expression } from "./Expression"
export class TemplateElement extends Expression {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 142)
        super(pointer)
    }
    static create1TemplateElement(raw: string, cooked: string): TemplateElement {
        return new TemplateElement(global.generatedEs2panda._CreateTemplateElement1(global.context, raw, cooked))
    }
    static updateTemplateElement(original?: TemplateElement): TemplateElement {
        return new TemplateElement(global.generatedEs2panda._UpdateTemplateElement(global.context, passNode(original)))
    }
    static update1TemplateElement(original: TemplateElement | undefined, raw: string, cooked: string): TemplateElement {
        return new TemplateElement(global.generatedEs2panda._UpdateTemplateElement1(global.context, passNode(original), raw, cooked))
    }
    get raw(): string {
        return unpackString(global.generatedEs2panda._TemplateElementRawConst(global.context, this.peer))
    }
    get cooked(): string {
        return unpackString(global.generatedEs2panda._TemplateElementCookedConst(global.context, this.peer))
    }
}
export function isTemplateElement(node: object | undefined): node is TemplateElement {
    return node instanceof TemplateElement
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_TEMPLATE_ELEMENT)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_TEMPLATE_ELEMENT, (peer: KNativePointer) => new TemplateElement(peer))
}