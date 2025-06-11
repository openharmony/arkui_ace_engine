/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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


import { Expression } from "../../generated"
import {
    assertValidPeer,
    AstNode,
    Es2pandaAstNodeType,
    Es2pandaMemberExpressionKind,
    KNativePointer,
    passNode,
    unpackNonNullableNode,
    global
} from "../../reexport-for-generated"

export class MemberExpression extends Expression {
    constructor(peer: KNativePointer) {
        assertValidPeer(peer, Es2pandaAstNodeType.AST_NODE_TYPE_MEMBER_EXPRESSION)
        super(peer)
    }

    static create(
        object: AstNode,
        property: AstNode,
        kind: Es2pandaMemberExpressionKind,
        computed: boolean,
        optional: boolean
    ): MemberExpression {
        return new MemberExpression(
            global.generatedEs2panda._CreateMemberExpression(
                global.context,
                passNode(object),
                passNode(property),
                kind,
                computed,
                optional
            )
        )
    }

    protected override dumpMessage(): string {
        return ` <kind: ${this.kind}>`
    }

    get object(): AstNode {
        return unpackNonNullableNode(global.generatedEs2panda._MemberExpressionObject(global.context, this.peer))
    }

    get property(): AstNode {
        return unpackNonNullableNode(global.generatedEs2panda._MemberExpressionProperty(global.context, this.peer))
    }

    get kind(): Es2pandaMemberExpressionKind {
        return global.generatedEs2panda._MemberExpressionKindConst(global.context, this.peer)
    }

    get computed(): boolean {
        return global.generatedEs2panda._MemberExpressionIsComputedConst(global.context, this.peer)
    }

    get optional(): boolean {
        return false // todo: no corresponding method in es2panda
    }
}