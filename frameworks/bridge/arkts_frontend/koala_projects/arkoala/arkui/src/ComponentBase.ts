/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

import { ArkUINativeModule, NativePeerNode, PeerNode } from "@koalaui/arkoala"
import { PeerReceiver } from "./peers/PeerReceiver"
import { ArkCommonMethodAttributes } from "./generated/peers/ArkCommonPeer"
import { int32 } from "@koalaui/compat"
import { KoalaCallsiteKey } from "@koalaui/common"
import { __id, NodeAttach } from "@koalaui/runtime"
import { SortedArray } from "./shared/utils"
import { endImplicitAnimation, startImplicitAnimations } from "./ArkAnimation"

export abstract class ComponentBase implements PeerReceiver {
    protected peer?: PeerNode
    setPeer(peer: PeerNode) {
        this.peer = peer
    }
    private currentPriority = 0

    /** @memo */
    __applyStyle(
        /** @memo */
        style: (instance: this, ...args: any) => this,
        ...args: any
    ): this {
        style(this, ...args)
        return this
    }

    __applyAnimatableExtend(func: (instance: this, arg: any) => this, arg: any): this {
        func(this, arg)
        return this
    }

    aboutToAppear() { }
    aboutToDisappear() { }

    /** @memo */
    pageTransition() {

    }

    onPageShow?() { }
    onPageHide?() { }
    onBackPress?() { }
    private attributePriority(): int32 {
        return this.currentPriority++
    }
    private priorityNameMap = new Map<string, int32>()
    private priorityIdMap = new Map<KoalaCallsiteKey, int32>()

    private animations: SortedArray<AnimateParam> | undefined = undefined

    /** @memo */
    animation(value: AnimateParam): this {
        if (this.animations === undefined) {
            this.animations = new SortedArray<AnimateParam>()
        }
        this.animations.add(this.attributePriority(), value)
        return this
    }

    private currentAnimation?: AnimateParam

    /** @memo:intrinsic */
    protected applyAnimations() {
        if (this.animations === undefined && this.currentAnimation === undefined) return
        let priority = this.attributePriority()
        let animation = this.animations?.find(priority)
        if (animation && this.currentAnimation != animation) {
            if (this.currentAnimation) {
                console.log("stop implicit animation", this.currentAnimation)
                ArkUINativeModule._ApplyModifierFinish(this.getNativePeerNode().ptr)
                // TODO: think about it
                //nativeModule()._CloseImplicitAnimation();
            }
            this.currentAnimation = animation
            startImplicitAnimations(this.currentAnimation!)
        }
    }

    /** @memo:intrinsic */
    protected checkPriority(
        name: string
    ): boolean {
        let id = __id()
        let priority = this.priorityIdMap.get(id)
        if (priority == undefined) {
            priority = this.currentPriority++
            this.priorityIdMap.set(id, priority)
            this.priorityNameMap.set(name, priority)
            return true
        }
        let oldPriority = this.priorityNameMap.get(name)
        if (oldPriority != undefined && oldPriority > priority) {
            console.log(`Ignore setting ${name} as it has lower priority`)
            return false
        } else {
            if (oldPriority != priority)
                this.priorityNameMap.set(name, priority)
        }
        return true
    }
    // It's not recommended to call these methods outside of the memo context.
    protected getPeerNode(): PeerNode {
        return this.peer!
    }
    protected getNativePeerNode(): NativePeerNode {
        return this.getPeerNode().peer
    }

    protected applyAttributesFinish(): void {
        if (this.currentAnimation) {
            this.currentAnimation = undefined
            endImplicitAnimation()
        }
        if (this.peer?.peer?.ptr) {
            ArkUINativeModule._ApplyModifierFinish(this.peer.peer.ptr)
        }
    }
}

/** @memo */
export function Attach<T extends PeerNode, A extends ArkCommonMethodAttributes>(
    create: () => T,
    attributes?: A,
    /** @memo */
    content?: () => void,
    ) {
    NodeAttach(create, (node: T) => {
        if (attributes !== undefined) {
            node.applyAttributes(attributes)
        }
        content?.()
    })
}