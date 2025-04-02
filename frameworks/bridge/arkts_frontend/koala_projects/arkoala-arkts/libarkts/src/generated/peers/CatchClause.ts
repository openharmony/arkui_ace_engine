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
import { Expression } from "./Expression"
import { BlockStatement } from "./BlockStatement"
export class CatchClause extends TypedStatement {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 11)
        super(pointer)
        console.warn("Warning: stub node CatchClause")
    }
    static createCatchClause(param?: Expression, body?: BlockStatement): CatchClause {
        return new CatchClause(global.generatedEs2panda._CreateCatchClause(global.context, passNode(param), passNode(body)))
    }
    static updateCatchClause(original?: CatchClause, param?: Expression, body?: BlockStatement): CatchClause {
        return new CatchClause(global.generatedEs2panda._UpdateCatchClause(global.context, passNode(original), passNode(param), passNode(body)))
    }
    get param(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._CatchClauseParamConst(global.context, this.peer))
    }
    get body(): BlockStatement | undefined {
        return unpackNode(global.generatedEs2panda._CatchClauseBodyConst(global.context, this.peer))
    }
}
export function isCatchClause(node: AstNode): node is CatchClause {
    return node instanceof CatchClause
}
if (!nodeByType.has(11)) {
    nodeByType.set(11, CatchClause)
}