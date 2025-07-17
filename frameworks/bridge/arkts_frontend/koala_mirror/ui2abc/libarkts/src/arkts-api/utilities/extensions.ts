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

import type {
    ETSModule,
    MethodDefinition
} from "../../generated"
import { Es2pandaModuleFlag } from "../../generated/Es2pandaEnums"
import { global } from "../../reexport-for-generated"

export function extension_ETSModuleGetNamespaceFlag(this: ETSModule): Es2pandaModuleFlag {
    return (this.isETSScript ? Es2pandaModuleFlag.MODULE_FLAG_ETSSCRIPT : 0)
        + (this.isNamespace ? Es2pandaModuleFlag.MODULE_FLAG_NAMESPACE : 0)
        + (this.isNamespaceChainLastNode ? Es2pandaModuleFlag.MODULE_FLAG_NAMESPACE_CHAIN_LAST_NODE : 0)
}

export function extension_MethodDefinitionSetChildrenParentPtr(this: MethodDefinition) {
    global.es2panda._AstNodeSetChildrenParentPtr(global.context, this.peer)
    const overloads = this.overloads
    for (const overload of overloads) {
        overload.setBaseOverloadMethod(this)
        overload.parent = this // overloads are not listed as children in native
    }
}

export function extension_MethodDefinitionOnUpdate(this: MethodDefinition, original: MethodDefinition): void {
    this.setChildrenParentPtr()
    // Improve: Update modifiers only for specific AST nodes in the generated factory code
    this.modifierFlags = original.modifierFlags
    global.generatedEs2panda._AstNodeSetOriginalNode(global.context, this.peer, original.originalPeer)
    global.generatedEs2panda._AstNodeSetParent(global.context, this.peer, global.generatedEs2panda._AstNodeParent(global.context, original.peer))
    const originalBase = original.baseOverloadMethod
    if (originalBase) {
        this.setBaseOverloadMethod(originalBase)
    }
}
