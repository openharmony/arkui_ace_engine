/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import { LengthMetrics } from 'arkui/Graphics'
import { ArkCommonMethodPeer, ArkCommonMethodComponent, CommonMethod, OnVisibleIndexesChangeCallback, AttributeModifier } from 'arkui/component/common'
import { HorizontalAlign } from 'arkui/component/enums'
import { int32 } from '@koalaui/common'
import { KPointer } from '@koalaui/interop'
import { ComponentBase } from 'arkui/ComponentBase'
import { PeerNode } from 'arkui/PeerNode'
import { LazyColumnLayoutExtender } from '#generated'
import { hookLazyColumnLayoutAttributeModifier } from '#handwritten'
import { ModifierStateManager } from 'arkui/CommonModifier'
import { LazyColumnLayoutModifier } from 'arkui/LazyColumnLayoutModifier'
import { NodeAttach, remember } from '@koalaui/runtime'

export interface LazyColumnLayoutAttribute extends CommonMethod {
    setLazyColumnLayoutOptions(): this {
        return this;
    }
    space(value: LengthMetrics | undefined): this {
        return this;
    }
    alignItems(value: HorizontalAlign | undefined): this {
        return this;
    }
    onVisibleIndexesChange(callback: OnVisibleIndexesChangeCallback | undefined): this {
        return this;
    }
    attributeModifier(modifier: AttributeModifier<LazyColumnLayoutAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        return this;
    }
}

export class ArkLazyColumnLayoutPeer extends ArkCommonMethodPeer {
    lazyColumnLayoutAttributeSet?: LazyColumnLayoutModifier

    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkLazyColumnLayoutPeer {
        const peerId = PeerNode.nextId()
        const _peerPtr = LazyColumnLayoutExtender.lazyColumnLayoutConstructor(peerId)
        const _peer = new ArkLazyColumnLayoutPeer(_peerPtr, peerId, 'LazyColumnLayout', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setLazyColumnLayoutOptionsAttribute(): void {
        LazyColumnLayoutExtender.setLazyColumnLayoutOptions(this.peer.ptr)
    }
    setSpaceAttribute(value: LengthMetrics | undefined): void {
        LazyColumnLayoutExtender.space(this.peer.ptr, value)
    }
    setAlignItemsAttribute(value: HorizontalAlign | undefined): void {
        LazyColumnLayoutExtender.alignItems(this.peer.ptr, value)
    }
    setOnVisibleIndexesChangeAttribute(callback: OnVisibleIndexesChangeCallback | undefined): void {
        LazyColumnLayoutExtender.onVisibleIndexesChange(this.peer.ptr, callback)
    }
}

export class ArkLazyColumnLayoutComponent extends ArkCommonMethodComponent implements LazyColumnLayoutAttribute {
    getPeer(): ArkLazyColumnLayoutPeer {
        if (!this.peer) {
            throw new Error('Attribute function should be called in memo context')
        }
        return (this.peer as ArkLazyColumnLayoutPeer)
    }
    public setLazyColumnLayoutOptions(): this {
        if (this.checkPriority('setLazyColumnLayoutOptions')) {
            this.getPeer()?.setLazyColumnLayoutOptionsAttribute()
            this.applyOptionsFinish('LazyColumnLayoutAttribute')
            return this
        }
        return this
    }
    public space(value: LengthMetrics | undefined): this {
        if (this.checkPriority('space')) {
            const value_casted = value as (LengthMetrics | undefined)
            this.getPeer()?.setSpaceAttribute(value_casted)
            return this
        }
        return this
    }
    public alignItems(value: HorizontalAlign | undefined): this {
        if (this.checkPriority('alignItems')) {
            const value_casted = value as (HorizontalAlign | undefined)
            this.getPeer()?.setAlignItemsAttribute(value_casted)
            return this
        }
        return this
    }
    public onVisibleIndexesChange(callback: OnVisibleIndexesChangeCallback | undefined): this {
        if (this.checkPriority('onVisibleIndexesChange')) {
            const callback_casted = callback as (OnVisibleIndexesChangeCallback | undefined)
            this.getPeer()?.setOnVisibleIndexesChangeAttribute(callback_casted)
            return this
        }
        return this
    }
    public attributeModifier(modifier: AttributeModifier<LazyColumnLayoutAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
 	        hookLazyColumnLayoutAttributeModifier(this, modifier)
 	    })
 	    return this
    }
    public applyAttributesFinish(): void {
        super.applyAttributesFinish()
    }
    public applyOptionsFinish(traceName: string): void {
        super.applyOptionsFinish(traceName)
    }
}

@memo
export function LazyColumnLayoutImpl(
    @memo
    style: ((attributes: LazyColumnLayoutAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkLazyColumnLayoutComponent>((): ArkLazyColumnLayoutComponent => {
        return new ArkLazyColumnLayoutComponent()
    })
    NodeAttach<ArkLazyColumnLayoutPeer>((): ArkLazyColumnLayoutPeer => ArkLazyColumnLayoutPeer.create(receiver), (peer: ArkLazyColumnLayoutPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}

export type LazyColumnLayoutInterface = (content_?: () => void) => LazyColumnLayoutAttribute
