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

import { TypedStatement } from "./TypedStatement"
import { Es2pandaVariableDeclaratorFlag } from "./../Es2pandaEnums"
import { Expression } from "./Expression"
export class VariableDeclarator extends TypedStatement {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 150)
        super(pointer)
        console.warn("Warning: stub node VariableDeclarator")
    }
    static createVariableDeclarator(flag: Es2pandaVariableDeclaratorFlag, ident?: Expression): VariableDeclarator {
        return new VariableDeclarator(global.generatedEs2panda._CreateVariableDeclarator(global.context, flag, passNode(ident)))
    }
    static updateVariableDeclarator(original: VariableDeclarator | undefined, flag: Es2pandaVariableDeclaratorFlag, ident?: Expression): VariableDeclarator {
        return new VariableDeclarator(global.generatedEs2panda._UpdateVariableDeclarator(global.context, passNode(original), flag, passNode(ident)))
    }
    static create1VariableDeclarator(flag: Es2pandaVariableDeclaratorFlag, ident?: Expression, init?: Expression): VariableDeclarator {
        return new VariableDeclarator(global.generatedEs2panda._CreateVariableDeclarator1(global.context, flag, passNode(ident), passNode(init)))
    }
    static update1VariableDeclarator(original: VariableDeclarator | undefined, flag: Es2pandaVariableDeclaratorFlag, ident?: Expression, init?: Expression): VariableDeclarator {
        return new VariableDeclarator(global.generatedEs2panda._UpdateVariableDeclarator1(global.context, passNode(original), flag, passNode(ident), passNode(init)))
    }
    get init(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._VariableDeclaratorInitConst(global.context, this.peer))
    }
    /** @deprecated */
    setInit(init: Expression): this {
        global.generatedEs2panda._VariableDeclaratorSetInit(global.context, this.peer, passNode(init))
        return this
    }
    get id(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._VariableDeclaratorIdConst(global.context, this.peer))
    }
    get flag(): Es2pandaVariableDeclaratorFlag {
        return global.generatedEs2panda._VariableDeclaratorFlag(global.context, this.peer)
    }
}
export function isVariableDeclarator(node: AstNode): node is VariableDeclarator {
    return node instanceof VariableDeclarator
}
if (!nodeByType.has(150)) {
    nodeByType.set(150, VariableDeclarator)
}