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
import { CommonMethod, BlurStyle, ArkCommonMethodPeer, ArkCommonMethodComponent, AttributeModifier, Bindable } from 'arkui/component/common';
import { ColorMetrics, LengthMetrics } from 'arkui/Graphics';
import { Font } from 'arkui/component/units';
import { int32 } from '@koalaui/common';
import { KPointer } from '@koalaui/interop';
import { ComponentBase } from 'arkui/ComponentBase';
import { PeerNode } from 'arkui/PeerNode';
import { ArcAlphabetIndexerExtender } from 'arkui/component/arcAlphabetIndexerExtender';
import { NodeAttach, remember } from "@koalaui/runtime"
import { TypeChecker } from "#components"

export interface ArcAlphabetIndexerInitInfo {
    arrayValue: string[];
    selected: number | Bindable<number>;
}
export type OnSelectCallback = (index: number) => void;

/** @memo:stable */
export class ArkArcAlphabetIndexerPeer extends ArkCommonMethodPeer {
    constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }

    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkArcAlphabetIndexerPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArcAlphabetIndexerExtender.ArcAlphabetIndexerConstruct(peerId, flags)
        const _peer  = new ArkArcAlphabetIndexerPeer(_peerPtr, peerId, "ArcAlphabetIndexer", flags)
        component?.setPeer(_peer)
        return _peer
    }

    setConstructInfoAttribute(info: ArcAlphabetIndexerInitInfo): void {
        if (TypeChecker.isBindableNumber(info.selected)) {
            let selectedBindable = info.selected as Bindable<number>;
            ArcAlphabetIndexerExtender.SetConstructInfo(this.peer.ptr, info.arrayValue, selectedBindable.value, (v: number) => {
                selectedBindable.onChange(v);
            });
        } else {
            let selected_cast = info.selected as number;
            ArcAlphabetIndexerExtender.SetConstructInfo(this.peer.ptr, info.arrayValue, selected_cast, undefined);
        }
    }

    setColorAttribute(color: ColorMetrics | undefined): void {
        ArcAlphabetIndexerExtender.SetColor(this.peer.ptr, color);
    }

    setSelectedColorAttribute(color: ColorMetrics | undefined): void {
        ArcAlphabetIndexerExtender.SetSelectedColor(this.peer.ptr, color);
    }

    setPopupColorAttribute(color: ColorMetrics | undefined): void {
        ArcAlphabetIndexerExtender.SetPopupColor(this.peer.ptr, color);
    }

    setSelectedBackgroundColorAttribute(color: ColorMetrics | undefined): void {
        ArcAlphabetIndexerExtender.SetSelectedBackgroundColor(this.peer.ptr, color);
    }

    setPopupBackgroundAttribute(color: ColorMetrics | undefined): void {
        ArcAlphabetIndexerExtender.SetPopupBackground(this.peer.ptr, color);
    }

    setUsePopupAttribute(enabled: boolean | undefined): void {
        ArcAlphabetIndexerExtender.SetUsePopup(this.peer.ptr, enabled);
    }

    setSelectedFontAttribute(font: Font | undefined): void {
        ArcAlphabetIndexerExtender.SetSelectedFont(this.peer.ptr, font);
    }

    setPopupFontAttribute(font: Font | undefined): void {
        ArcAlphabetIndexerExtender.SetPopupFont(this.peer.ptr, font);
    }

    setFontAttribute(font: Font | undefined): void {
        ArcAlphabetIndexerExtender.SetFont(this.peer.ptr, font);
    }

    setItemSizeAttribute(size: LengthMetrics | undefined): void {
        ArcAlphabetIndexerExtender.SetItemSize(this.peer.ptr, size);
    }

    setSelectedAttribute(index: number | Bindable<number> | undefined): void {
        if (TypeChecker.isBindableNumber(index)) {
            let indexBindable = index as Bindable<number>;
            ArcAlphabetIndexerExtender.SetSelected(this.peer.ptr, indexBindable.value, (v: number) => {
                indexBindable.onChange(v);
            });
        } else {
            let index_casted = index as (number | undefined);
            ArcAlphabetIndexerExtender.SetSelected(this.peer.ptr, index_casted, undefined);
        }
    }

    setAutoCollapseAttribute(enable: boolean | undefined): void {
        ArcAlphabetIndexerExtender.SetAutoCollapse(this.peer.ptr, enable);
    }

    setOnSelectAttribute(handler: OnSelectCallback | undefined): void {
        ArcAlphabetIndexerExtender.SetOnSelect(this.peer.ptr, handler);
    }

    setPopupBackgroundBlurStyleAttribute(style: BlurStyle | undefined): void {
        ArcAlphabetIndexerExtender.SetPopupBackgroundBlurStyle(this.peer.ptr, style);
    }
}

export interface ArcAlphabetIndexerAttribute extends CommonMethod {
    setConstructInfo(info: ArcAlphabetIndexerInitInfo): this {
        return this
    }
    color(color: ColorMetrics | undefined): this;
    selectedColor(color: ColorMetrics | undefined): this;
    popupColor(color: ColorMetrics | undefined): this;
    selectedBackgroundColor(color: ColorMetrics | undefined): this;
    popupBackground(color: ColorMetrics | undefined): this;
    usePopup(enabled: boolean | undefined): this;
    selectedFont(font: Font | undefined): this;
    popupFont(font: Font | undefined): this;
    font(font: Font | undefined): this;
    itemSize(size: LengthMetrics | undefined): this;
    selected(index: number | Bindable<number> | undefined): this;
    autoCollapse(enable: boolean | undefined): this;
    onSelect(handler: OnSelectCallback | undefined): this;
    popupBackgroundBlurStyle(style: BlurStyle | undefined): this;
}

export class ArkArcAlphabetIndexerComponent extends ArkCommonMethodComponent implements ArcAlphabetIndexerAttribute {
    getPeer(): ArkArcAlphabetIndexerPeer {
        return (this.peer as ArkArcAlphabetIndexerPeer)
    }

    public setConstructInfo(info: ArcAlphabetIndexerInitInfo): this {
        if (this.checkPriority("setConstructInfo")) {
            this.getPeer()?.setConstructInfoAttribute(info)
        }
        return this
    }

    public color(color: ColorMetrics | undefined): this {
        if (this.checkPriority("color")) {
            this.getPeer()?.setColorAttribute(color)
        }
        return this
    }

    public selectedColor(color: ColorMetrics | undefined): this {
        if (this.checkPriority("selectedColor")) {
            this.getPeer()?.setSelectedColorAttribute(color)
        }
        return this
    }

    public popupColor(color: ColorMetrics | undefined): this {
        if (this.checkPriority("popupColor")) {
            this.getPeer()?.setPopupColorAttribute(color)
        }
        return this
    }

    public selectedBackgroundColor(color: ColorMetrics | undefined): this {
        if (this.checkPriority("selectedBackgroundColor")) {
            this.getPeer()?.setSelectedBackgroundColorAttribute(color)
        }
        return this
    }

    public popupBackground(color: ColorMetrics | undefined): this {
        if (this.checkPriority("popupBackground")) {
            this.getPeer()?.setPopupBackgroundAttribute(color)
        }
        return this
    }

    public usePopup(enabled: boolean | undefined): this {
        if (this.checkPriority("usePopup")) {
            this.getPeer()?.setUsePopupAttribute(enabled)
        }
        return this
    }

    public selectedFont(font: Font | undefined): this {
        if (this.checkPriority("selectedFont")) {
            this.getPeer()?.setSelectedFontAttribute(font)
        }
        return this
    }

    public popupFont(font: Font | undefined): this {
        if (this.checkPriority("popupFont")) {
            this.getPeer()?.setPopupFontAttribute(font)
        }
        return this
    }

    public font(font: Font | undefined): this {
        if (this.checkPriority("font")) {
            this.getPeer()?.setFontAttribute(font)
        }
        return this
    }

    public itemSize(size: LengthMetrics | undefined): this {
        if (this.checkPriority("itemSize")) {
            this.getPeer()?.setItemSizeAttribute(size)
        }
        return this
    }

    public selected(index: number | Bindable<number> | undefined): this {
        if (this.checkPriority("selected")) {
            this.getPeer()?.setSelectedAttribute(index)
        }
        return this
    }

    public autoCollapse(enable: boolean | undefined): this {
        if (this.checkPriority("autoCollapse")) {
            this.getPeer()?.setAutoCollapseAttribute(enable)
        }
        return this
    }

    public onSelect(handler: OnSelectCallback | undefined): this {
        if (this.checkPriority("onSelect")) {
            this.getPeer()?.setOnSelectAttribute(handler)
        }
        return this
    }

    public popupBackgroundBlurStyle(style: BlurStyle | undefined): this {
        if (this.checkPriority("popupBackgroundBlurStyle")) {
            this.getPeer()?.setPopupBackgroundBlurStyleAttribute(style)
        }
        return this
    }

    public attributeModifier(modifier: AttributeModifier<ArcAlphabetIndexerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented");
        return this
    }

    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

/** @memo */
export function ArcAlphabetIndexerImpl(
    /** @memo */
    style: ((attributes: ArcAlphabetIndexerAttribute) => void) | undefined,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkArcAlphabetIndexerComponent()
    })
    NodeAttach<ArkArcAlphabetIndexerPeer>((): ArkArcAlphabetIndexerPeer => ArkArcAlphabetIndexerPeer.create(receiver), (_: ArkArcAlphabetIndexerPeer) => {
        style?.(receiver)
        content_?.()
    })
}
