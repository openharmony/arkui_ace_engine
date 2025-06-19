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
import { Es2pandaPropertyKind } from "./../Es2pandaEnums"
import { ValidationInfo } from "./ValidationInfo"
export class Property extends Expression {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 55)
        super(pointer)
        console.warn("Warning: stub node Property")
    }
    static createProperty(key?: Expression, value?: Expression): Property {
        return new Property(global.generatedEs2panda._CreateProperty(global.context, passNode(key), passNode(value)))
    }
    static updateProperty(original?: Property, key?: Expression, value?: Expression): Property {
        return new Property(global.generatedEs2panda._UpdateProperty(global.context, passNode(original), passNode(key), passNode(value)))
    }
    static create1Property(kind: Es2pandaPropertyKind, key: Expression | undefined, value: Expression | undefined, isMethod: boolean, isComputed: boolean): Property {
        return new Property(global.generatedEs2panda._CreateProperty1(global.context, kind, passNode(key), passNode(value), isMethod, isComputed))
    }
    static update1Property(original: Property | undefined, kind: Es2pandaPropertyKind, key: Expression | undefined, value: Expression | undefined, isMethod: boolean, isComputed: boolean): Property {
        return new Property(global.generatedEs2panda._UpdateProperty1(global.context, passNode(original), kind, passNode(key), passNode(value), isMethod, isComputed))
    }
    get key(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._PropertyKeyConst(global.context, this.peer))
    }
    get value(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._PropertyValueConst(global.context, this.peer))
    }
    get kind(): Es2pandaPropertyKind {
        return global.generatedEs2panda._PropertyKindConst(global.context, this.peer)
    }
    get isMethod(): boolean {
        return global.generatedEs2panda._PropertyIsMethodConst(global.context, this.peer)
    }
    get isShorthand(): boolean {
        return global.generatedEs2panda._PropertyIsShorthandConst(global.context, this.peer)
    }
    get isComputed(): boolean {
        return global.generatedEs2panda._PropertyIsComputedConst(global.context, this.peer)
    }
    get isAccessor(): boolean {
        return global.generatedEs2panda._PropertyIsAccessorConst(global.context, this.peer)
    }
}
export function isProperty(node: AstNode): node is Property {
    return node instanceof Property
}
if (!nodeByType.has(55)) {
    nodeByType.set(55, Property)
}