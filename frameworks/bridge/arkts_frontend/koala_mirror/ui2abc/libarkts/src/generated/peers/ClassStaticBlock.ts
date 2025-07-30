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

import { ClassElement } from "./ClassElement"
import { Es2pandaAstNodeType } from "./../Es2pandaEnums"
import { Expression } from "./Expression"
import { ScriptFunction } from "./ScriptFunction"
export class ClassStaticBlock extends ClassElement {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 18)
        super(pointer)
    }
    static createClassStaticBlock(value?: Expression): ClassStaticBlock {
        return new ClassStaticBlock(global.generatedEs2panda._CreateClassStaticBlock(global.context, passNode(value)))
    }
    static updateClassStaticBlock(original?: ClassStaticBlock, value?: Expression): ClassStaticBlock {
        return new ClassStaticBlock(global.generatedEs2panda._UpdateClassStaticBlock(global.context, passNode(original), passNode(value)))
    }
    get function(): ScriptFunction | undefined {
        return unpackNode(global.generatedEs2panda._ClassStaticBlockFunction(global.context, this.peer))
    }
    get name(): string {
        return unpackString(global.generatedEs2panda._ClassStaticBlockNameConst(global.context, this.peer))
    }
}
export function isClassStaticBlock(node: object | undefined): node is ClassStaticBlock {
    return node instanceof ClassStaticBlock
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_CLASS_STATIC_BLOCK)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_CLASS_STATIC_BLOCK, (peer: KNativePointer) => new ClassStaticBlock(peer))
}