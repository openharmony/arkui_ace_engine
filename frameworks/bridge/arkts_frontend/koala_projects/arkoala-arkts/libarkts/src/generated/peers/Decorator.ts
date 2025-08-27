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

import { Statement } from "./Statement"
import { Expression } from "./Expression"
export class Decorator extends Statement {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 22)
        super(pointer)
        console.warn("Warning: stub node Decorator")
    }
    static createDecorator(expr?: Expression): Decorator {
        return new Decorator(global.generatedEs2panda._CreateDecorator(global.context, passNode(expr)))
    }
    static updateDecorator(original?: Decorator, expr?: Expression): Decorator {
        return new Decorator(global.generatedEs2panda._UpdateDecorator(global.context, passNode(original), passNode(expr)))
    }
    get expr(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._DecoratorExprConst(global.context, this.peer))
    }
}
export function isDecorator(node: AstNode): node is Decorator {
    return node instanceof Decorator
}
if (!nodeByType.has(22)) {
    nodeByType.set(22, Decorator)
}