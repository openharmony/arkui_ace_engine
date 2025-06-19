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

import { MaybeOptionalExpression } from "./MaybeOptionalExpression"
import { Expression } from "./Expression"
import { Es2pandaMemberExpressionKind } from "./../Es2pandaEnums"
export class MemberExpression extends MaybeOptionalExpression {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 45)
        super(pointer)
        console.warn("Warning: stub node MemberExpression")
    }
    static createMemberExpression(object_arg: Expression | undefined, property: Expression | undefined, kind: Es2pandaMemberExpressionKind, computed: boolean, optional_arg: boolean): MemberExpression {
        return new MemberExpression(global.generatedEs2panda._CreateMemberExpression(global.context, passNode(object_arg), passNode(property), kind, computed, optional_arg))
    }
    static updateMemberExpression(original: MemberExpression | undefined, object_arg: Expression | undefined, property: Expression | undefined, kind: Es2pandaMemberExpressionKind, computed: boolean, optional_arg: boolean): MemberExpression {
        return new MemberExpression(global.generatedEs2panda._UpdateMemberExpression(global.context, passNode(original), passNode(object_arg), passNode(property), kind, computed, optional_arg))
    }
    get object(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._MemberExpressionObjectConst(global.context, this.peer))
    }
    /** @deprecated */
    setObject(object_arg: Expression): this {
        global.generatedEs2panda._MemberExpressionSetObject(global.context, this.peer, passNode(object_arg))
        return this
    }
    /** @deprecated */
    setProperty(prop: Expression): this {
        global.generatedEs2panda._MemberExpressionSetProperty(global.context, this.peer, passNode(prop))
        return this
    }
    get property(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._MemberExpressionPropertyConst(global.context, this.peer))
    }
    get isComputed(): boolean {
        return global.generatedEs2panda._MemberExpressionIsComputedConst(global.context, this.peer)
    }
    get kind(): Es2pandaMemberExpressionKind {
        return global.generatedEs2panda._MemberExpressionKindConst(global.context, this.peer)
    }
    /** @deprecated */
    addMemberKind(kind: Es2pandaMemberExpressionKind): this {
        global.generatedEs2panda._MemberExpressionAddMemberKind(global.context, this.peer, kind)
        return this
    }
    /** @deprecated */
    removeMemberKind(kind: Es2pandaMemberExpressionKind): this {
        global.generatedEs2panda._MemberExpressionRemoveMemberKind(global.context, this.peer, kind)
        return this
    }
    get isIgnoreBox(): boolean {
        return global.generatedEs2panda._MemberExpressionIsIgnoreBoxConst(global.context, this.peer)
    }
    /** @deprecated */
    setIgnoreBox(): this {
        global.generatedEs2panda._MemberExpressionSetIgnoreBox(global.context, this.peer)
        return this
    }
}
export function isMemberExpression(node: AstNode): node is MemberExpression {
    return node instanceof MemberExpression
}
if (!nodeByType.has(45)) {
    nodeByType.set(45, MemberExpression)
}