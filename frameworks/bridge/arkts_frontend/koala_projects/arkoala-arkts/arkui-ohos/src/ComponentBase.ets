/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { memo, memo_intrinsic, memo_entry, memo_stable, memo_skip } from "@koalaui/runtime/annotations"
import { PeerNode } from './PeerNode'
import { ArkUINativeModule } from "#components"
import { AnimateParam, UIGestureEvent } from './framework'
import { UICommonBase } from './base'
import { AceTrace } from "./base/AceTrace"
import { unsafeCast } from "@koalaui/common"

export class ComponentBase implements UICommonBase {
    protected peer?: PeerNode
    protected isFirstBuild: boolean = true
    public isFirstRender: boolean = true
    protected gestureEvent: UIGestureEvent | undefined = undefined
    private attributeHook_: (peer?: PeerNode)=>void = ()=>{}
    setPeer(peer: PeerNode | undefined) {
        this.peer = peer
    }
    getPeer(): PeerNode | undefined {
        return this.peer;
    }
    setGestureEvent(gestureEvent: UIGestureEvent | undefined) {
        this.gestureEvent = gestureEvent
    }
    getGestureEvent(): UIGestureEvent | undefined {
        return this.gestureEvent
    }
    protected checkPriority(name: string): boolean {
        this.attributeHook_(this.peer);
        return true
    }
    public applyAttributesFinish(): void {
        if (AceTrace.GetAttributeSetTraceEnabled())
        {
            AceTrace.end()
        }
        this.isFirstBuild = false;
        ArkUINativeModule._ApplyModifierFinish(this.peer!.peer.ptr)
    }
    public applyOptionsFinish(traceName: string): void {
        if (AceTrace.GetAttributeSetTraceEnabled())
        {
            AceTrace.begin(traceName)
        }
    }
    public applyAttributes(attrs: Object): void {
        this.applyAttributesFinish()
    }
    public animationStart(param: AnimateParam): this {
        return this
    }

    public animationEnd(): this {
        return this;
    }
    
    public setAttributeHook(hook: (peer?: PeerNode) => void) {
        this.attributeHook_ = hook;
    }

    @memo
    public __applyStyle<T, A>(
        @memo
        func: (instance: T, arg: A) => T,  // should be ...args: A[], but that doesn't currently compile
        arg: A
    ): T {
        func(unsafeCast<T>(this), arg)
        return unsafeCast<T>(this)
    }

    @memo
    public __applyAnimatableExtend<T, A>(
        @memo
        func: (instance: T, arg: A) => T,
        arg: A
    ): T {
        func(unsafeCast<T>(this), arg)
        return unsafeCast<T>(this)
    }
}
