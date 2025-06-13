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

import { int32 } from "@koalaui/common"
import { LegacyNodeType, PeerNode, PeerNodeType } from "./PeerNode"
import { IncrementalNode, NodeAttach, contextNode } from "@koalaui/runtime"
import { ArkUINativeModule } from "./generated/ArkUINativeModule"
import { nullptr, pointer } from "@koalaui/interop"

export declare class LegacyComponent {
    __chained: number
    name: string
    create: (() => void) | undefined
    createWithLabel: ((arg: string) => void) | undefined
    pop(): void
}

declare class ViewPU {
    static create(view: ViewPU): void
    initialRender(): void;
    rerender(): void;
    updateStateVars(params: Object): void
    updateStateVarsOfChildByElmtId(elementId: number, arg: Object): void
}

export class LegacyWrapper extends IncrementalNode {
    private elementId: int32
    private view: ViewPU
    constructor(elementId: int32, parent: pointer, view: ViewPU) {
        super(LegacyNodeType)
        this.elementId = elementId
        this.view = view
        ViewPU.create(view)
        view.initialRender()
        let ptr = ArkUINativeModule._GetNodeByViewStack()
        if (parent != nullptr && ptr != nullptr)
            ArkUINativeModule._AddChild(parent, ptr)
    }
    update() {
        this.view.rerender()
    }
}

/** @memo:intrinsic */
export function LegacyNode(factory: (elementId: int32) => ViewPU) {
    let parent = contextNode<PeerNode>(PeerNodeType).getPeerPtr()
    let elementId = PeerNode.nextId()
    NodeAttach(() => new LegacyWrapper(elementId, parent, factory(elementId)), node => node.update())
}