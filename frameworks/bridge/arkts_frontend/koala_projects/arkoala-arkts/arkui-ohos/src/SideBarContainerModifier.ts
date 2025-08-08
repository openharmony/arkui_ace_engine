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

import { AttributeModifier, CommonMethod, Bindable } from "arkui/component/common"
import { AttributeUpdaterFlag, CommonMethodModifier } from './CommonMethodModifier';
import { ButtonStyle, SideBarPosition, SideBarContainerAttribute, ArkSideBarContainerPeer, DividerStyle } from "arkui/component/sidebar"
import { Length, Dimension } from "arkui/component/units"
import { Resource } from "global.resource"
import { PeerNode } from './PeerNode'

export class SideBarContainerModifier extends CommonMethodModifier implements SideBarContainerAttribute,AttributeModifier<SideBarContainerAttribute> {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    applyNormalAttribute(instance: SideBarContainerAttribute): void { }
    applyPressedAttribute(instance: SideBarContainerAttribute): void { }
    applyFocusedAttribute(instance: SideBarContainerAttribute): void { }
    applyDisabledAttribute(instance: SideBarContainerAttribute): void { }
    applySelectedAttribute(instance: SideBarContainerAttribute): void { }
    _showSideBar_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _showSideBar_0_0value?: boolean | Bindable<boolean> | undefined
    _controlButton_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _controlButton_0_0value?: ButtonStyle | undefined
    _showControlButton_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _showControlButton_0_0value?: boolean | undefined
    _onChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onChange_0_0value?: ((value: boolean) => void) | undefined
    _sideBarWidth_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _sideBarWidth_0_0value?: number | Bindable<number> | undefined
    _minSideBarWidth_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _minSideBarWidth_0_0value?: number | undefined
    _maxSideBarWidth_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _maxSideBarWidth_0_0value?: number | undefined
    _sideBarWidth_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _sideBarWidth_1_0value?: Length | undefined
    _minSideBarWidth_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _minSideBarWidth_1_0value?: Length | undefined
    _maxSideBarWidth_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _maxSideBarWidth_1_0value?: Length | undefined
    _autoHide_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _autoHide_0_0value?: boolean | undefined
    _sideBarPosition_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _sideBarPosition_0_0value?: SideBarPosition | undefined
    _divider_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _divider_0_0value?: DividerStyle | null | undefined
    _minContentWidth_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _minContentWidth_0_0value?: Dimension | undefined
    applyModifierPatch(peerNode: PeerNode): void {
        super.applyModifierPatch(peerNode)
        const peer = peerNode as ArkSideBarContainerPeer
        if (this._showSideBar_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._showSideBar_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.showSideBarAttribute((this._showSideBar_0_0value as boolean | undefined));
                    this._showSideBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._showSideBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._showSideBar_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.showSideBarAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._controlButton_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._controlButton_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.controlButtonAttribute((this._controlButton_0_0value as ButtonStyle | undefined));
                    this._controlButton_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._controlButton_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._controlButton_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.controlButtonAttribute((undefined as ButtonStyle | undefined));
                }
            }
        }
        if (this._showControlButton_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._showControlButton_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.showControlButtonAttribute((this._showControlButton_0_0value as boolean | undefined));
                    this._showControlButton_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._showControlButton_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._showControlButton_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.showControlButtonAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onChangeAttribute((this._onChange_0_0value as ((value: boolean) => void) | undefined));
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onChangeAttribute((undefined as ((value: boolean) => void) | undefined));
                }
            }
        }
        if (this._sideBarWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._sideBarWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.sideBarWidth0Attribute((this._sideBarWidth_0_0value as number | undefined));
                    this._sideBarWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._sideBarWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._sideBarWidth_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.sideBarWidth0Attribute((undefined as number | undefined));
                }
            }
        }
        if (this._minSideBarWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._minSideBarWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.minSideBarWidth0Attribute((this._minSideBarWidth_0_0value as number | undefined));
                    this._minSideBarWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._minSideBarWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._minSideBarWidth_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.minSideBarWidth0Attribute((undefined as number | undefined));
                }
            }
        }
        if (this._maxSideBarWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._maxSideBarWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.maxSideBarWidth0Attribute((this._maxSideBarWidth_0_0value as number | undefined));
                    this._maxSideBarWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._maxSideBarWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._maxSideBarWidth_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.maxSideBarWidth0Attribute((undefined as number | undefined));
                }
            }
        }
        if (this._sideBarWidth_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._sideBarWidth_1_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.sideBarWidth1Attribute((this._sideBarWidth_1_0value as Length | undefined));
                    this._sideBarWidth_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._sideBarWidth_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._sideBarWidth_1_flag = AttributeUpdaterFlag.INITIAL;
                    peer.sideBarWidth1Attribute((undefined as Length | undefined));
                }
            }
        }
        if (this._minSideBarWidth_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._minSideBarWidth_1_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.minSideBarWidth1Attribute((this._minSideBarWidth_1_0value as Length | undefined));
                    this._minSideBarWidth_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._minSideBarWidth_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._minSideBarWidth_1_flag = AttributeUpdaterFlag.INITIAL;
                    peer.minSideBarWidth1Attribute((undefined as Length | undefined));
                }
            }
        }
        if (this._maxSideBarWidth_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._maxSideBarWidth_1_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.maxSideBarWidth1Attribute((this._maxSideBarWidth_1_0value as Length | undefined));
                    this._maxSideBarWidth_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._maxSideBarWidth_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._maxSideBarWidth_1_flag = AttributeUpdaterFlag.INITIAL;
                    peer.maxSideBarWidth1Attribute((undefined as Length | undefined));
                }
            }
        }
        if (this._autoHide_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._autoHide_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.autoHideAttribute((this._autoHide_0_0value as boolean | undefined));
                    this._autoHide_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._autoHide_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._autoHide_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.autoHideAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._sideBarPosition_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._sideBarPosition_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.sideBarPositionAttribute((this._sideBarPosition_0_0value as SideBarPosition | undefined));
                    this._sideBarPosition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._sideBarPosition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._sideBarPosition_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.sideBarPositionAttribute((undefined as SideBarPosition | undefined));
                }
            }
        }
        if (this._divider_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._divider_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.dividerAttribute((this._divider_0_0value as DividerStyle | null | undefined));
                    this._divider_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._divider_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._divider_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.dividerAttribute((undefined as DividerStyle | null | undefined));
                }
            }
        }
        if (this._minContentWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._minContentWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.minContentWidthAttribute((this._minContentWidth_0_0value as Dimension | undefined));
                    this._minContentWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._minContentWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._minContentWidth_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.minContentWidthAttribute((undefined as Dimension | undefined));
                }
            }
        }
    }
    mergeModifier(value: CommonMethodModifier): void {
        super.mergeModifier(value)
        if (!(value instanceof SideBarContainerModifier)) {
            return;
        }
        const modifier = value as SideBarContainerModifier;

        if (modifier._showSideBar_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._showSideBar_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.showSideBar(modifier._showSideBar_0_0value);
                    break;
                }
                default: {
                    this.showSideBar((undefined as boolean | Bindable<boolean> | undefined));
                }
            }
        }
        if (modifier._controlButton_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._controlButton_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.controlButton(modifier._controlButton_0_0value);
                    break;
                }
                default: {
                    this.controlButton((undefined as ButtonStyle | undefined));
                }
            }
        }
        if (modifier._showControlButton_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._showControlButton_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.showControlButton(modifier._showControlButton_0_0value);
                    break;
                }
                default: {
                    this.showControlButton((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onChange(modifier._onChange_0_0value);
                    break;
                }
                default: {
                    this.onChange((undefined as ((value: boolean) => void) | undefined));
                }
            }
        }
        if (modifier._sideBarWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._sideBarWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.sideBarWidth(modifier._sideBarWidth_0_0value);
                    break;
                }
                default: {
                    this.sideBarWidth((undefined as number | Bindable<number> | undefined));
                }
            }
        }
        if (modifier._minSideBarWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._minSideBarWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.minSideBarWidth(modifier._minSideBarWidth_0_0value);
                    break;
                }
                default: {
                    this.minSideBarWidth((undefined as number | undefined));
                }
            }
        }
        if (modifier._maxSideBarWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._maxSideBarWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.maxSideBarWidth(modifier._maxSideBarWidth_0_0value);
                    break;
                }
                default: {
                    this.maxSideBarWidth((undefined as number | undefined));
                }
            }
        }
        if (modifier._autoHide_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._autoHide_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.autoHide(modifier._autoHide_0_0value);
                    break;
                }
                default: {
                    this.autoHide((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._sideBarPosition_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._sideBarPosition_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.sideBarPosition(modifier._sideBarPosition_0_0value);
                    break;
                }
                default: {
                    this.sideBarPosition((undefined as SideBarPosition | undefined));
                }
            }
        }
        if (modifier._divider_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._divider_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.divider(modifier._divider_0_0value);
                    break;
                }
                default: {
                    this.divider((undefined as DividerStyle | null | undefined));
                }
            }
        }
        if (modifier._minContentWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._minContentWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
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
        if (((this._showSideBar_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._showSideBar_0_flag = AttributeUpdaterFlag.UPDATE
            this._showSideBar_0_0value = value
        } else
        {
            this._showSideBar_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    controlButton(value: ButtonStyle | undefined): this {
        if (((this._controlButton_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._controlButton_0_flag = AttributeUpdaterFlag.UPDATE
            this._controlButton_0_0value = value
        } else
        {
            this._controlButton_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    showControlButton(value: boolean | undefined): this {
        if (((this._showControlButton_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._showControlButton_0_0value) !== (value)))
        {
            this._showControlButton_0_flag = AttributeUpdaterFlag.UPDATE
            this._showControlButton_0_0value = value
        } else
        {
            this._showControlButton_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onChange(value: ((value: boolean) => void) | undefined): this {
        if (((this._onChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onChange_0_0value = value
        } else
        {
            this._onChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    sideBarWidth(value: number | Bindable<number> | undefined): this {
        if (((this._sideBarWidth_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._sideBarWidth_0_flag = AttributeUpdaterFlag.UPDATE
            this._sideBarWidth_0_0value = value
        } else
        {
            this._sideBarWidth_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    minSideBarWidth(value: number | undefined): this {
        if (((this._minSideBarWidth_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._minSideBarWidth_0_0value) !== (value)))
        {
            this._minSideBarWidth_0_flag = AttributeUpdaterFlag.UPDATE
            this._minSideBarWidth_0_0value = value
        } else
        {
            this._minSideBarWidth_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    maxSideBarWidth(value: number | undefined): this {
        if (((this._maxSideBarWidth_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._maxSideBarWidth_0_0value) !== (value)))
        {
            this._maxSideBarWidth_0_flag = AttributeUpdaterFlag.UPDATE
            this._maxSideBarWidth_0_0value = value
        } else
        {
            this._maxSideBarWidth_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    autoHide(value: boolean | undefined): this {
        if (((this._autoHide_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._autoHide_0_0value) !== (value)))
        {
            this._autoHide_0_flag = AttributeUpdaterFlag.UPDATE
            this._autoHide_0_0value = value
        } else
        {
            this._autoHide_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    sideBarPosition(value: SideBarPosition | undefined): this {
        if (((this._sideBarPosition_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._sideBarPosition_0_flag = AttributeUpdaterFlag.UPDATE
            this._sideBarPosition_0_0value = value
        } else
        {
            this._sideBarPosition_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    divider(value: DividerStyle | null | undefined): this {
        if (((this._divider_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._divider_0_flag = AttributeUpdaterFlag.UPDATE
            this._divider_0_0value = value
        } else
        {
            this._divider_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    minContentWidth(value: Dimension | undefined): this {
        if (((this._minContentWidth_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._minContentWidth_0_flag = AttributeUpdaterFlag.UPDATE
            this._minContentWidth_0_0value = value
        } else
        {
            this._minContentWidth_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<SideBarContainerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    _onChangeEvent_showSideBar(callback: ((select: boolean | undefined) => void)): void {
        throw new Error("Unimplmented")
    }
}
