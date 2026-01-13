/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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


// WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!

import { CommonMethodModifier } from "./CommonMethodModifier"
import { ModifierState } from './CommonModifier'
import { AttributeModifier } from "#handwritten"
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { ArkScrollBarPeer, ScrollBarAttribute } from "./component/scrollBar"
import { int32 } from "@koalaui/common"
import { CommonMethod } from "./component/common"
import { ColorMetrics } from "arkui.Graphics"
export class ScrollBarModifier extends CommonMethodModifier implements ScrollBarAttribute,AttributeModifier<ScrollBarAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState	
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: ScrollBarAttribute): void { }
    applyPressedAttribute(instance: ScrollBarAttribute): void { }
    applyFocusedAttribute(instance: ScrollBarAttribute): void { }
    applyDisabledAttribute(instance: ScrollBarAttribute): void { }
    applySelectedAttribute(instance: ScrollBarAttribute): void { }
    _enableNestedScroll_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableNestedScroll_0_0value?: boolean | undefined
    _scrollBarColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _scrollBarColor_0_0value?: ColorMetrics | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkScrollBarPeer;
        if (this._enableNestedScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableNestedScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableNestedScrollAttribute((this._enableNestedScroll_0_0value as boolean | undefined));
                    this._enableNestedScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableNestedScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableNestedScroll_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableNestedScrollAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._scrollBarColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._scrollBarColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setScrollBarColorAttribute((this._scrollBarColor_0_0value as ColorMetrics | undefined));
                    this._scrollBarColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._scrollBarColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._scrollBarColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setScrollBarColorAttribute((undefined as ColorMetrics | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: ScrollBarModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        if (modifier._enableNestedScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableNestedScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableNestedScroll(modifier._enableNestedScroll_0_0value);
                    break;
                }
                default: {
                    this.enableNestedScroll((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._scrollBarColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._scrollBarColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.scrollBarColor(modifier._scrollBarColor_0_0value);
                    break;
                }
                default: {
                    this.scrollBarColor((undefined as ColorMetrics | undefined));
                }
            }
        }
    }
    enableNestedScroll(value: boolean | undefined): this {
        if (((this._enableNestedScroll_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableNestedScroll_0_0value) !== (value)))
        {
            this._enableNestedScroll_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableNestedScroll_0_0value = value
            this._state.fireChange()
        } else
        {
            this._enableNestedScroll_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    scrollBarColor(value: ColorMetrics | undefined): this {
        if (((this._scrollBarColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._scrollBarColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._scrollBarColor_0_0value = value
        } else
        {
            this._scrollBarColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ScrollBarAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
