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

import { CommonMethodModifier } from './CommonMethodModifier'
import { AttributeModifier } from '#handwritten'
import { AttributeUpdaterFlag } from './AttributeUpdaterFlag'
import { PeerNode } from './PeerNode'
import { ArkSideBarContainerPeer, ButtonStyle, SideBarPosition, SideBarContainerAttribute } from './component/sidebar'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod, Bindable, DividerStyle } from './component/common'
import { Length, Resource as arkui_component_units_Resource, Dimension } from './component/units'
import { Resource as global_resource_Resource } from 'global.resource'
export class SideBarContainerModifier extends CommonMethodModifier implements SideBarContainerAttribute,AttributeModifier<SideBarContainerAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState;
    _addr: ArrayBuffer = new ArrayBuffer(4096);
    _flagArray: Uint8Array = new Uint8Array(this._addr);
    constructor() {
        super();
        this._flagArray.fill(0);
    }
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: SideBarContainerAttribute): void { }
    applyPressedAttribute(instance: SideBarContainerAttribute): void { }
    applyFocusedAttribute(instance: SideBarContainerAttribute): void { }
    applyDisabledAttribute(instance: SideBarContainerAttribute): void { }
    applySelectedAttribute(instance: SideBarContainerAttribute): void { }
    public _showSideBar_0_0value?: boolean | Bindable<boolean> | undefined
    public _controlButton_0_0value?: ButtonStyle | undefined
    public _showControlButton_0_0value?: boolean | undefined
    public _onChange_0_0value?: ((isSelected: boolean) => void) | undefined
    public _sideBarWidth_0_0value?: Length | Bindable<Length> | undefined
    public _minSideBarWidth_0_0value?: Length | undefined
    public _maxSideBarWidth_0_0value?: Length | undefined
    public _autoHide_0_0value?: boolean | undefined
    public _sideBarPosition_0_0value?: SideBarPosition | undefined
    public _divider_0_0value?: DividerStyle | null | undefined
    public _minContentWidth_0_0value?: Dimension | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkSideBarContainerPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkSideBarContainerPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setShowSideBarAttribute((this._showSideBar_0_0value as boolean | Bindable<boolean> | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setShowSideBarAttribute((undefined as boolean | Bindable<boolean> | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setControlButtonAttribute((this._controlButton_0_0value as ButtonStyle | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setControlButtonAttribute((undefined as ButtonStyle | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setShowControlButtonAttribute((this._showControlButton_0_0value as boolean | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setShowControlButtonAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1: {
                    peer.setOnChangeAttribute((this._onChange_0_0value as ((isSelected: boolean) => void) | undefined));
                    flagArray[3] = 2;
                    break;
                }
                case 3: {
                    flagArray[3] = 2;
                    break;
                }
                default: {
                    flagArray[3] = 0;
                    peer.setOnChangeAttribute((undefined as ((isSelected: boolean) => void) | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1: {
                    peer.setSideBarWidthAttribute((this._sideBarWidth_0_0value as Length | Bindable<Length> | undefined));
                    flagArray[4] = 2;
                    break;
                }
                case 3: {
                    flagArray[4] = 2;
                    break;
                }
                default: {
                    flagArray[4] = 0;
                    peer.setSideBarWidthAttribute((undefined as Length | Bindable<Length> | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1: {
                    peer.setMinSideBarWidthAttribute((this._minSideBarWidth_0_0value as Length | undefined));
                    flagArray[5] = 2;
                    break;
                }
                case 3: {
                    flagArray[5] = 2;
                    break;
                }
                default: {
                    flagArray[5] = 0;
                    peer.setMinSideBarWidthAttribute((undefined as Length | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1: {
                    peer.setMaxSideBarWidthAttribute((this._maxSideBarWidth_0_0value as Length | undefined));
                    flagArray[6] = 2;
                    break;
                }
                case 3: {
                    flagArray[6] = 2;
                    break;
                }
                default: {
                    flagArray[6] = 0;
                    peer.setMaxSideBarWidthAttribute((undefined as Length | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1: {
                    peer.setAutoHideAttribute((this._autoHide_0_0value as boolean | undefined));
                    flagArray[7] = 2;
                    break;
                }
                case 3: {
                    flagArray[7] = 2;
                    break;
                }
                default: {
                    flagArray[7] = 0;
                    peer.setAutoHideAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1: {
                    peer.setSideBarPositionAttribute((this._sideBarPosition_0_0value as SideBarPosition | undefined));
                    flagArray[8] = 2;
                    break;
                }
                case 3: {
                    flagArray[8] = 2;
                    break;
                }
                default: {
                    flagArray[8] = 0;
                    peer.setSideBarPositionAttribute((undefined as SideBarPosition | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1: {
                    peer.setDividerAttribute((this._divider_0_0value as DividerStyle | null | undefined));
                    flagArray[9] = 2;
                    break;
                }
                case 3: {
                    flagArray[9] = 2;
                    break;
                }
                default: {
                    flagArray[9] = 0;
                    peer.setDividerAttribute((undefined as DividerStyle | null | undefined));
                }
            }
        }
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1: {
                    peer.setMinContentWidthAttribute((this._minContentWidth_0_0value as Dimension | undefined));
                    flagArray[10] = 2;
                    break;
                }
                case 3: {
                    flagArray[10] = 2;
                    break;
                }
                default: {
                    flagArray[10] = 0;
                    peer.setMinContentWidthAttribute((undefined as Dimension | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: SideBarContainerModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
    }
    mergeModifier0(modifier: SideBarContainerModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.showSideBar(modifier._showSideBar_0_0value);
                    break;
                }
                default: {
                    this.showSideBar((undefined as boolean | Bindable<boolean> | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.controlButton(modifier._controlButton_0_0value);
                    break;
                }
                default: {
                    this.controlButton((undefined as ButtonStyle | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.showControlButton(modifier._showControlButton_0_0value);
                    break;
                }
                default: {
                    this.showControlButton((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1:
                case 3: {
                    this.onChange(modifier._onChange_0_0value);
                    break;
                }
                default: {
                    this.onChange((undefined as ((isSelected: boolean) => void) | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1:
                case 3: {
                    this.sideBarWidth(modifier._sideBarWidth_0_0value);
                    break;
                }
                default: {
                    this.sideBarWidth((undefined as Length | Bindable<Length> | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1:
                case 3: {
                    this.minSideBarWidth(modifier._minSideBarWidth_0_0value);
                    break;
                }
                default: {
                    this.minSideBarWidth((undefined as Length | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1:
                case 3: {
                    this.maxSideBarWidth(modifier._maxSideBarWidth_0_0value);
                    break;
                }
                default: {
                    this.maxSideBarWidth((undefined as Length | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1:
                case 3: {
                    this.autoHide(modifier._autoHide_0_0value);
                    break;
                }
                default: {
                    this.autoHide((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1:
                case 3: {
                    this.sideBarPosition(modifier._sideBarPosition_0_0value);
                    break;
                }
                default: {
                    this.sideBarPosition((undefined as SideBarPosition | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1:
                case 3: {
                    this.divider(modifier._divider_0_0value);
                    break;
                }
                default: {
                    this.divider((undefined as DividerStyle | null | undefined));
                }
            }
        }
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1:
                case 3: {
                    this.minContentWidth(modifier._minContentWidth_0_0value);
                    break;
                }
                default: {
                    this.minContentWidth((undefined as Dimension | undefined));
                }
            }
        }
    }
    showSideBar(value: boolean | Bindable<boolean> | undefined): this {
        if (((this._flagArray[0]) == (0)) || (true)) {
            this._flagArray[0] = 1
            this._showSideBar_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    controlButton(value: ButtonStyle | undefined): this {
        if (((this._flagArray[1]) == (0)) || (true)) {
            this._flagArray[1] = 1
            this._controlButton_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    showControlButton(value: boolean | undefined): this {
        if (((this._flagArray[2]) == (0)) || ((this._showControlButton_0_0value) !== (value))) {
            this._flagArray[2] = 1
            this._showControlButton_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[2] = 3
        }
        return this
    }
    onChange(value: ((isSelected: boolean) => void) | undefined): this {
        if (((this._flagArray[3]) == (0)) || (true)) {
            this._flagArray[3] = 1
            this._onChange_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[3] = 3
        }
        return this
    }
    sideBarWidth(value: Length | Bindable<Length> | undefined): this {
        if (((this._flagArray[4]) == (0)) || (true)) {
            this._flagArray[4] = 1
            this._sideBarWidth_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[4] = 3
        }
        return this
    }
    minSideBarWidth(value: Length | undefined): this {
        if (((this._flagArray[5]) == (0)) || (true)) {
            this._flagArray[5] = 1
            this._minSideBarWidth_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[5] = 3
        }
        return this
    }
    maxSideBarWidth(value: Length | undefined): this {
        if (((this._flagArray[6]) == (0)) || (true)) {
            this._flagArray[6] = 1
            this._maxSideBarWidth_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[6] = 3
        }
        return this
    }
    autoHide(value: boolean | undefined): this {
        if (((this._flagArray[7]) == (0)) || ((this._autoHide_0_0value) !== (value))) {
            this._flagArray[7] = 1
            this._autoHide_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[7] = 3
        }
        return this
    }
    sideBarPosition(value: SideBarPosition | undefined): this {
        if (((this._flagArray[8]) == (0)) || (true)) {
            this._flagArray[8] = 1
            this._sideBarPosition_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[8] = 3
        }
        return this
    }
    divider(value: DividerStyle | null | undefined): this {
        if (((this._flagArray[9]) == (0)) || (true)) {
            this._flagArray[9] = 1
            this._divider_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[9] = 3
        }
        return this
    }
    minContentWidth(value: Dimension | undefined): this {
        if (((this._flagArray[10]) == (0)) || (true)) {
            this._flagArray[10] = 1
            this._minContentWidth_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[10] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<SideBarContainerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}
