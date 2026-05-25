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
import { ItemFillPolicy } from 'arkui/component/units'
import { int32 } from '@koalaui/common'
import { KPointer } from '@koalaui/interop'
import { ComponentBase } from 'arkui/ComponentBase'
import { PeerNode } from 'arkui/PeerNode'
import { LazyWaterFlowLayoutExtender } from '#generated'
import { hookLazyWaterFlowLayoutAttributeAttributeModifier, hookLazyVWaterFlowLayoutAttributeModifier } from '#handwritten'
import { ModifierStateManager } from 'arkui/CommonModifier'
import { LazyVWaterFlowLayoutModifier } from 'arkui/LazyVWaterFlowLayoutModifier'
import { NodeAttach, remember } from '@koalaui/runtime'

export interface LazyWaterFlowLayoutAttribute extends CommonMethod {
    rowsGap(value: LengthMetrics | undefined): this {
        return this
    }
    columnsGap(value: LengthMetrics | undefined): this {
        return this
    }
    onVisibleIndexesChange(callback: OnVisibleIndexesChangeCallback | undefined): this {
        return this
    }
    attributeModifier(modifier: AttributeModifier<LazyWaterFlowLayoutAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        return this
    }
}

export interface LazyVWaterFlowLayoutAttribute extends LazyWaterFlowLayoutAttribute {
    setLazyVWaterFlowLayoutOptions(): this {
        return this
    }
    columnsTemplate(value: string | ItemFillPolicy | undefined): this {
        return this
    }
    attributeModifier(
        modifier: AttributeModifier<LazyVWaterFlowLayoutAttribute> | AttributeModifier<LazyWaterFlowLayoutAttribute> |
            AttributeModifier<CommonMethod> | undefined): this {
        return this
    }
}

export class ArkLazyWaterFlowLayoutAttributePeer extends ArkCommonMethodPeer {
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    setRowsGapAttribute(value: LengthMetrics | undefined): void {
        LazyWaterFlowLayoutExtender.rowsGap(this.peer.ptr, value)
    }
    setColumnsGapAttribute(value: LengthMetrics | undefined): void {
        LazyWaterFlowLayoutExtender.columnsGap(this.peer.ptr, value)
    }
    setOnVisibleIndexesChangeAttribute(callback: OnVisibleIndexesChangeCallback | undefined): void {
        LazyWaterFlowLayoutExtender.onVisibleIndexesChange(this.peer.ptr, callback)
    }
}

export class ArkLazyVWaterFlowLayoutPeer extends ArkLazyWaterFlowLayoutAttributePeer {
    lazyVWaterFlowLayoutAttributeSet?: LazyVWaterFlowLayoutModifier

    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkLazyVWaterFlowLayoutPeer {
        const peerId = PeerNode.nextId()
        const _peerPtr = LazyWaterFlowLayoutExtender.lazyVWaterFlowLayoutConstructor(peerId)
        const _peer = new ArkLazyVWaterFlowLayoutPeer(_peerPtr, peerId, 'LazyVWaterFlowLayout', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setLazyVWaterFlowLayoutOptionsAttribute(): void {
        LazyWaterFlowLayoutExtender.setLazyVWaterFlowLayoutOptions(this.peer.ptr)
    }
    setColumnsTemplateAttribute(value: string | ItemFillPolicy | undefined): void {
        LazyWaterFlowLayoutExtender.columnsTemplate(this.peer.ptr, value)
    }
}

export class ArkLazyWaterFlowLayoutAttributeComponent extends ArkCommonMethodComponent implements LazyWaterFlowLayoutAttribute {
    getPeer(): ArkLazyWaterFlowLayoutAttributePeer {
        if (!this.peer) {
            throw new Error('Attribute function should be called in memo context')
        }
        return (this.peer as ArkLazyWaterFlowLayoutAttributePeer)
    }
    public rowsGap(value: LengthMetrics | undefined): this {
        if (this.checkPriority('rowsGap')) {
            const value_casted = value as (LengthMetrics | undefined)
            this.getPeer()?.setRowsGapAttribute(value_casted)
            return this
        }
        return this
    }
    public columnsGap(value: LengthMetrics | undefined): this {
        if (this.checkPriority('columnsGap')) {
            const value_casted = value as (LengthMetrics | undefined)
            this.getPeer()?.setColumnsGapAttribute(value_casted)
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
    public attributeModifier(modifier: AttributeModifier<LazyWaterFlowLayoutAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookLazyWaterFlowLayoutAttributeAttributeModifier(this, modifier)
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

export class ArkLazyVWaterFlowLayoutComponent extends ArkLazyWaterFlowLayoutAttributeComponent implements LazyVWaterFlowLayoutAttribute {
    getPeer(): ArkLazyVWaterFlowLayoutPeer {
        if (!this.peer) {
            throw new Error('Attribute function should be called in memo context')
        }
        return (this.peer as ArkLazyVWaterFlowLayoutPeer)
    }
    public setLazyVWaterFlowLayoutOptions(): this {
        if (this.checkPriority('setLazyVWaterFlowLayoutOptions')) {
            this.getPeer()?.setLazyVWaterFlowLayoutOptionsAttribute()
            this.applyOptionsFinish('LazyVWaterFlowLayoutAttribute')
            return this
        }
        return this
    }
    public columnsTemplate(value: string | ItemFillPolicy | undefined): this {
        if (this.checkPriority('columnsTemplate')) {
            const value_casted = value as (string | ItemFillPolicy | undefined)
            this.getPeer()?.setColumnsTemplateAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(
        modifier: AttributeModifier<LazyVWaterFlowLayoutAttribute> | AttributeModifier<LazyWaterFlowLayoutAttribute> |
            AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookLazyVWaterFlowLayoutAttributeModifier(this, modifier)
        })
        return this
    }
}

@memo
export function LazyVWaterFlowLayoutImpl(
    @memo
    style: ((attributes: LazyVWaterFlowLayoutAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkLazyVWaterFlowLayoutComponent>((): ArkLazyVWaterFlowLayoutComponent => {
        return new ArkLazyVWaterFlowLayoutComponent()
    })
    NodeAttach<ArkLazyVWaterFlowLayoutPeer>((): ArkLazyVWaterFlowLayoutPeer => ArkLazyVWaterFlowLayoutPeer.create(receiver), (peer: ArkLazyVWaterFlowLayoutPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}

export type LazyVWaterFlowLayoutInterface = (content_?: () => void) => LazyVWaterFlowLayoutAttribute
