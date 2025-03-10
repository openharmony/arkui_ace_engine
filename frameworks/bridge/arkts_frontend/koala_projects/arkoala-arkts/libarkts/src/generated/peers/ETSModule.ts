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

import { BlockStatement } from "./BlockStatement"
import { Identifier } from "./Identifier"
import { AnnotationUsage } from "./AnnotationUsage"
export class ETSModule extends BlockStatement {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 81)
        super(pointer)
        console.warn("Warning: stub node ETSModule")
    }
    get ident(): Identifier | undefined {
        return unpackNode(global.generatedEs2panda._ETSModuleIdentConst(global.context, this.peer))
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
        return unpackNodeArray(global.generatedEs2panda._ETSModuleAnnotationsConst(global.context, this.peer))
    }
    /** @deprecated */
    setAnnotations(annotations: readonly AnnotationUsage[]): this {
        global.generatedEs2panda._ETSModuleSetAnnotations(global.context, this.peer, passNodeArray(annotations), annotations.length)
        return this
    }
}
export function isETSModule(node: AstNode): node is ETSModule {
    return node instanceof ETSModule
}
if (!nodeByType.has(81)) {
    nodeByType.set(81, ETSModule)
}