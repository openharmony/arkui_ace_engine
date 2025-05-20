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
import { Statement } from "./Statement"
export class SwitchCaseStatement extends Statement {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 85)
        super(pointer)
    }
    static createSwitchCaseStatement(test: Expression | undefined, consequent: readonly Statement[]): SwitchCaseStatement {
        return new SwitchCaseStatement(global.generatedEs2panda._CreateSwitchCaseStatement(global.context, passNode(test), passNodeArray(consequent), consequent.length))
    }
    static updateSwitchCaseStatement(original: SwitchCaseStatement | undefined, test: Expression | undefined, consequent: readonly Statement[]): SwitchCaseStatement {
        return new SwitchCaseStatement(global.generatedEs2panda._UpdateSwitchCaseStatement(global.context, passNode(original), passNode(test), passNodeArray(consequent), consequent.length))
    }
    get test(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._SwitchCaseStatementTest(global.context, this.peer))
    }
    /** @deprecated */
    setTest(test?: Expression): this {
        global.generatedEs2panda._SwitchCaseStatementSetTest(global.context, this.peer, passNode(test))
        return this
    }
    get consequent(): readonly Statement[] {
        return unpackNodeArray(global.generatedEs2panda._SwitchCaseStatementConsequentConst(global.context, this.peer))
    }
}
export function isSwitchCaseStatement(node: object | undefined): node is SwitchCaseStatement {
    return node instanceof SwitchCaseStatement
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_SWITCH_CASE_STATEMENT)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_SWITCH_CASE_STATEMENT, (peer: KNativePointer) => new SwitchCaseStatement(peer))
}