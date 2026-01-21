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
import { CommonMethod, BlurStyle, ArkCommonMethodPeer, ArkCommonMethodComponent, AttributeModifier, Bindable } from 'arkui/component/common';
import { ColorMetrics, LengthMetrics } from 'arkui/Graphics';
import { Font } from 'arkui/component/units';
import { int32 } from '@koalaui/common';
import { KPointer } from "@koalaui/interop"
import { ComponentBase } from 'arkui/ComponentBase';
import { PeerNode } from 'arkui/PeerNode';
import { ArcAlphabetIndexerExtender } from 'arkui/component/idlize';
import { NodeAttach, remember } from "@koalaui/runtime"

export interface ArcAlphabetIndexerInitInfo {
    arrayValue: Array<string>;
    selected: int32 | Bindable<int32>;
}
export type OnSelectCallback = (index: int32) => void;

export class ArkArcAlphabetIndexerPeer extends ArkCommonMethodPeer {
    constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }

    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkArcAlphabetIndexerPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArcAlphabetIndexerExtender.arcAlphabetIndexerConstruct(peerId, flags)
        const _peer  = new ArkArcAlphabetIndexerPeer(_peerPtr, peerId, "ArcAlphabetIndexer", flags)
        component?.setPeer(_peer)
        return _peer
    }

    setArcAlphabetIndexerOptionsAttribute(info: ArcAlphabetIndexerInitInfo): void {
        ArcAlphabetIndexerExtender.setArcAlphabetIndexerInitInfo(this.peer.ptr, info.arrayValue, info.selected);
    }

    setColorAttribute(color: ColorMetrics | undefined): void {
        ArcAlphabetIndexerExtender.color(this.peer.ptr, color);
    }

    setSelectedColorAttribute(color: ColorMetrics | undefined): void {
        ArcAlphabetIndexerExtender.selectedColor(this.peer.ptr, color);
    }

    setPopupColorAttribute(color: ColorMetrics | undefined): void {
        ArcAlphabetIndexerExtender.popupColor(this.peer.ptr, color);
    }

    setSelectedBackgroundColorAttribute(color: ColorMetrics | undefined): void {
        ArcAlphabetIndexerExtender.selectedBackgroundColor(this.peer.ptr, color);
    }

    setPopupBackgroundAttribute(color: ColorMetrics | undefined): void {
        ArcAlphabetIndexerExtender.popupBackground(this.peer.ptr, color);
    }

    setUsePopupAttribute(enabled: boolean | undefined): void {
        ArcAlphabetIndexerExtender.usePopup(this.peer.ptr, enabled);
    }

    setSelectedFontAttribute(font: Font | undefined): void {
        ArcAlphabetIndexerExtender.selectedFont(this.peer.ptr, font);
    }

    setPopupFontAttribute(font: Font | undefined): void {
        ArcAlphabetIndexerExtender.popupFont(this.peer.ptr, font);
    }

    setFontAttribute(font: Font | undefined): void {
        ArcAlphabetIndexerExtender.font(this.peer.ptr, font);
    }

    setItemSizeAttribute(size: LengthMetrics | undefined): void {
        ArcAlphabetIndexerExtender.itemSize(this.peer.ptr, size);
    }

    setSelectedAttribute(index: int32 | Bindable<int32> | undefined): void {
        ArcAlphabetIndexerExtender.selected(this.peer.ptr, index);
    }

    setAutoCollapseAttribute(enable: boolean | undefined): void {
        ArcAlphabetIndexerExtender.autoCollapse(this.peer.ptr, enable);
    }

    setOnSelectAttribute(handler: OnSelectCallback | undefined): void {
        ArcAlphabetIndexerExtender.onSelect(this.peer.ptr, handler);
    }

    setPopupBackgroundBlurStyleAttribute(style: BlurStyle | undefined): void {
        ArcAlphabetIndexerExtender.popupBackgroundBlurStyle(this.peer.ptr, style);
    }
}

export interface ArcAlphabetIndexerAttribute extends CommonMethod {
    setArcAlphabetIndexerOptions(info: ArcAlphabetIndexerInitInfo): this {
        throw new Error("Unimplemented method setArcAlphabetIndexerOptions")
    }
    color(value: ColorMetrics | undefined): this {
        throw new Error("Unimplemented method color")
    }
    selectedColor(value: ColorMetrics | undefined): this {
        throw new Error("Unimplemented method selectedColor")
    }
    popupColor(value: ColorMetrics | undefined): this {
        throw new Error("Unimplemented method popupColor")
    }
    selectedBackgroundColor(value: ColorMetrics | undefined): this {
        throw new Error("Unimplemented method selectedBackgroundColor")
    }
    popupBackground(value: ColorMetrics | undefined): this {
        throw new Error("Unimplemented method popupBackground")
    }
    usePopup(value: boolean | undefined): this {
        throw new Error("Unimplemented method usePopup")
    }
    selectedFont(value: Font | undefined): this {
        throw new Error("Unimplemented method selectedFont")
    }
    popupFont(value: Font | undefined): this {
        throw new Error("Unimplemented method popupFont")
    }
    font(value: Font | undefined): this {
        throw new Error("Unimplemented method font")
    }
    itemSize(value: LengthMetrics | undefined): this {
        throw new Error("Unimplemented method itemSize")
    }
    selected(value: int32 | undefined | Bindable<int32>): this {
        throw new Error("Unimplemented method selected")
    }
    autoCollapse(value: boolean | undefined): this {
        throw new Error("Unimplemented method autoCollapse")
    }
    onSelect(value: OnSelectCallback | undefined): this {
        throw new Error("Unimplemented method onSelect")
    }
    popupBackgroundBlurStyle(value: BlurStyle | undefined): this {
        throw new Error("Unimplemented method popupBackgroundBlurStyle")
    }
    attributeModifier(value: AttributeModifier<ArcAlphabetIndexerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}

export class ArkArcAlphabetIndexerComponent extends ArkCommonMethodComponent implements ArcAlphabetIndexerAttribute {
    getPeer(): ArkArcAlphabetIndexerPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkArcAlphabetIndexerPeer)
    }
    public setArcAlphabetIndexerOptions(info: ArcAlphabetIndexerInitInfo): this {
        if (this.checkPriority("setArcAlphabetIndexerOptions")) {
            const info_casted = info as (ArcAlphabetIndexerInitInfo)
            this.getPeer()?.setArcAlphabetIndexerOptionsAttribute(info_casted)
            this.applyOptionsFinish('ArcAlphabetIndexerAttribute');
            return this
        }
        return this
    }
    public color(value: ColorMetrics | undefined): this {
        if (this.checkPriority("color")) {
            const value_casted = value as (ColorMetrics | undefined)
            this.getPeer()?.setColorAttribute(value_casted)
            return this
        }
        return this
    }
    public selectedColor(value: ColorMetrics | undefined): this {
        if (this.checkPriority("selectedColor")) {
            const value_casted = value as (ColorMetrics | undefined)
            this.getPeer()?.setSelectedColorAttribute(value_casted)
            return this
        }
        return this
    }
    public popupColor(value: ColorMetrics | undefined): this {
        if (this.checkPriority("popupColor")) {
            const value_casted = value as (ColorMetrics | undefined)
            this.getPeer()?.setPopupColorAttribute(value_casted)
            return this
        }
        return this
    }
    public selectedBackgroundColor(value: ColorMetrics | undefined): this {
        if (this.checkPriority("selectedBackgroundColor")) {
            const value_casted = value as (ColorMetrics | undefined)
            this.getPeer()?.setSelectedBackgroundColorAttribute(value_casted)
            return this
        }
        return this
    }
    public popupBackground(value: ColorMetrics | undefined): this {
        if (this.checkPriority("popupBackground")) {
            const value_casted = value as (ColorMetrics | undefined)
            this.getPeer()?.setPopupBackgroundAttribute(value_casted)
            return this
        }
        return this
    }
    public usePopup(value: boolean | undefined): this {
        if (this.checkPriority("usePopup")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setUsePopupAttribute(value_casted)
            return this
        }
        return this
    }
    public selectedFont(value: Font | undefined): this {
        if (this.checkPriority("selectedFont")) {
            const value_casted = value as (Font | undefined)
            this.getPeer()?.setSelectedFontAttribute(value_casted)
            return this
        }
        return this
    }
    public popupFont(value: Font | undefined): this {
        if (this.checkPriority("popupFont")) {
            const value_casted = value as (Font | undefined)
            this.getPeer()?.setPopupFontAttribute(value_casted)
            return this
        }
        return this
    }
    public font(value: Font | undefined): this {
        if (this.checkPriority("font")) {
            const value_casted = value as (Font | undefined)
            this.getPeer()?.setFontAttribute(value_casted)
            return this
        }
        return this
    }
    public itemSize(value: LengthMetrics | undefined): this {
        if (this.checkPriority("itemSize")) {
            const value_casted = value as (LengthMetrics | undefined)
            this.getPeer()?.setItemSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public selected(value: int32 | undefined | Bindable<int32>): this {
        if (this.checkPriority("selected")) {
            const value_casted = value as (int32 | undefined | Bindable<int32>)
            this.getPeer()?.setSelectedAttribute(value_casted)
            return this
        }
        return this
    }
    public autoCollapse(value: boolean | undefined): this {
        if (this.checkPriority("autoCollapse")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setAutoCollapseAttribute(value_casted)
            return this
        }
        return this
    }
    public onSelect(value: OnSelectCallback | undefined): this {
        if (this.checkPriority("onSelect")) {
            const value_casted = value as (OnSelectCallback | undefined)
            this.getPeer()?.setOnSelectAttribute(value_casted)
            return this
        }
        return this
    }
    public popupBackgroundBlurStyle(value: BlurStyle | undefined): this {
        if (this.checkPriority("popupBackgroundBlurStyle")) {
            const value_casted = value as (BlurStyle | undefined)
            this.getPeer()?.setPopupBackgroundBlurStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ArcAlphabetIndexerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        // hookArcAlphabetIndexerAttributeModifier(this, value);
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
    public applyOptionsFinish(traceName: string): void {
        super.applyOptionsFinish(traceName)
    }
}

@memo
export function ArcAlphabetIndexerImpl(
    @memo
    style: ((attributes: ArcAlphabetIndexerAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkArcAlphabetIndexerComponent>((): ArkArcAlphabetIndexerComponent => {
        return new ArkArcAlphabetIndexerComponent()
    })
    NodeAttach<ArkArcAlphabetIndexerPeer>((): ArkArcAlphabetIndexerPeer => ArkArcAlphabetIndexerPeer.create(receiver), (peer: ArkArcAlphabetIndexerPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}
