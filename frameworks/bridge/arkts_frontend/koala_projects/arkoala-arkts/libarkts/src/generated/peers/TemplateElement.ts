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

import { Expression } from "./Expression"
export class TemplateElement extends Expression {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 141)
        super(pointer)
        console.warn("Warning: stub node TemplateElement")
    }
    static createTemplateElement(): TemplateElement {
        return new TemplateElement(global.generatedEs2panda._CreateTemplateElement(global.context))
    }
    static updateTemplateElement(original?: TemplateElement): TemplateElement {
        return new TemplateElement(global.generatedEs2panda._UpdateTemplateElement(global.context, passNode(original)))
    }
    static create1TemplateElement(raw: string, cooked: string): TemplateElement {
        return new TemplateElement(global.generatedEs2panda._CreateTemplateElement1(global.context, raw, cooked))
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
export function isTemplateElement(node: AstNode): node is TemplateElement {
    return node instanceof TemplateElement
}
if (!nodeByType.has(141)) {
    nodeByType.set(141, TemplateElement)
}