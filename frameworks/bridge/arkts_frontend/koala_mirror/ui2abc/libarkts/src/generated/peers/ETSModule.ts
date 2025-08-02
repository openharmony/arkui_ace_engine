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

import { AnnotationUsage } from "./AnnotationUsage"
import { BlockStatement } from "./BlockStatement"
import { Es2pandaAstNodeType } from "./../Es2pandaEnums"
import { Identifier } from "./Identifier"
export class ETSModule extends BlockStatement {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 82)
        super(pointer)
    }
    get ident(): Identifier | undefined {
        return unpackNode(global.generatedEs2panda._ETSModuleIdent(global.context, this.peer))
    }
    get isETSScript(): boolean {
        return global.generatedEs2panda._ETSModuleIsETSScriptConst(global.context, this.peer)
    }
    get isNamespace(): boolean {
        return global.generatedEs2panda._ETSModuleIsNamespaceConst(global.context, this.peer)
    }
    get isNamespaceChainLastNode(): boolean {
        return global.generatedEs2panda._ETSModuleIsNamespaceChainLastNodeConst(global.context, this.peer)
    }
    /** @deprecated */
    setNamespaceChainLastNode(): this {
        global.generatedEs2panda._ETSModuleSetNamespaceChainLastNode(global.context, this.peer)
        return this
    }
    get annotations(): readonly AnnotationUsage[] {
        return unpackNodeArray(global.generatedEs2panda._ETSModuleAnnotations(global.context, this.peer))
    }
    /** @deprecated */
    setAnnotations(annotations: readonly AnnotationUsage[]): this {
        global.generatedEs2panda._ETSModuleSetAnnotations(global.context, this.peer, passNodeArray(annotations), annotations.length)
        return this
    }
}
export function isETSModule(node: object | undefined): node is ETSModule {
    return node instanceof ETSModule
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_ETS_MODULE)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_ETS_MODULE, (peer: KNativePointer) => new ETSModule(peer))
}