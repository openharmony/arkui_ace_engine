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
import { Identifier } from "./Identifier"
export class TSQualifiedName extends Expression {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 128)
        super(pointer)
        console.warn("Warning: stub node TSQualifiedName")
    }
    static createTSQualifiedName(left?: Expression, right?: Identifier): TSQualifiedName {
        return new TSQualifiedName(global.generatedEs2panda._CreateTSQualifiedName(global.context, passNode(left), passNode(right)))
    }
    static updateTSQualifiedName(original?: TSQualifiedName, left?: Expression, right?: Identifier): TSQualifiedName {
        return new TSQualifiedName(global.generatedEs2panda._UpdateTSQualifiedName(global.context, passNode(original), passNode(left), passNode(right)))
    }
    get left(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._TSQualifiedNameLeftConst(global.context, this.peer))
    }
    get right(): Identifier | undefined {
        return unpackNode(global.generatedEs2panda._TSQualifiedNameRightConst(global.context, this.peer))
    }
}
export function isTSQualifiedName(node: AstNode): node is TSQualifiedName {
    return node instanceof TSQualifiedName
}
if (!nodeByType.has(128)) {
    nodeByType.set(128, TSQualifiedName)
}