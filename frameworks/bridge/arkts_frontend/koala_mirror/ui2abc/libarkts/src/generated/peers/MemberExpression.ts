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

import { CodeGen } from "./CodeGen"
import { ETSFunctionType } from "./ETSFunctionType"
import { Es2pandaAstNodeType } from "./../Es2pandaEnums"
import { Es2pandaMemberExpressionKind } from "./../Es2pandaEnums"
import { Expression } from "./Expression"
import { MaybeOptionalExpression } from "./MaybeOptionalExpression"
import { VReg } from "./VReg"
export class MemberExpression extends MaybeOptionalExpression {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 45)
        super(pointer)
    }
    static createMemberExpression(object_arg: Expression | undefined, property: Expression | undefined, kind: Es2pandaMemberExpressionKind, computed: boolean, optional_arg: boolean): MemberExpression {
        return new MemberExpression(global.generatedEs2panda._CreateMemberExpression(global.context, passNode(object_arg), passNode(property), kind, computed, optional_arg))
    }
    static updateMemberExpression(original: MemberExpression | undefined, object_arg: Expression | undefined, property: Expression | undefined, kind: Es2pandaMemberExpressionKind, computed: boolean, optional_arg: boolean): MemberExpression {
        return new MemberExpression(global.generatedEs2panda._UpdateMemberExpression(global.context, passNode(original), passNode(object_arg), passNode(property), kind, computed, optional_arg))
    }
    get object(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._MemberExpressionObject(global.context, this.peer))
    }
    /** @deprecated */
    setObject(object_arg?: Expression): this {
        global.generatedEs2panda._MemberExpressionSetObject(global.context, this.peer, passNode(object_arg))
        return this
    }
    /** @deprecated */
    setProperty(prop?: Expression): this {
        global.generatedEs2panda._MemberExpressionSetProperty(global.context, this.peer, passNode(prop))
        return this
    }
    get property(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._MemberExpressionProperty(global.context, this.peer))
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
    get extensionAccessorType(): ETSFunctionType | undefined {
        return unpackNode(global.generatedEs2panda._MemberExpressionExtensionAccessorTypeConst(global.context, this.peer))
    }
    get isIgnoreBox(): boolean {
        return global.generatedEs2panda._MemberExpressionIsIgnoreBoxConst(global.context, this.peer)
    }
    /** @deprecated */
    setIgnoreBox(): this {
        global.generatedEs2panda._MemberExpressionSetIgnoreBox(global.context, this.peer)
        return this
    }
    get isPrivateReference(): boolean {
        return global.generatedEs2panda._MemberExpressionIsPrivateReferenceConst(global.context, this.peer)
    }
    /** @deprecated */
    compileToReg(pg?: CodeGen, objReg?: VReg): this {
        global.generatedEs2panda._MemberExpressionCompileToRegConst(global.context, this.peer, passNode(pg), passNode(objReg))
        return this
    }
    /** @deprecated */
    compileToRegs(pg?: CodeGen, object_arg?: VReg, property?: VReg): this {
        global.generatedEs2panda._MemberExpressionCompileToRegsConst(global.context, this.peer, passNode(pg), passNode(object_arg), passNode(property))
        return this
    }
}
export function isMemberExpression(node: object | undefined): node is MemberExpression {
    return node instanceof MemberExpression
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_MEMBER_EXPRESSION)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_MEMBER_EXPRESSION, (peer: KNativePointer) => new MemberExpression(peer))
}