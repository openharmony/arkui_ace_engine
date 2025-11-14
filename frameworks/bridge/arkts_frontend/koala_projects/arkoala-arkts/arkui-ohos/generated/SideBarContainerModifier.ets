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
import { AttributeModifier } from "#handwritten"
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { ArkSideBarContainerPeer, ButtonStyle, SideBarPosition, SideBarContainerAttribute } from "./component/sidebar"
import { int32 } from "@koalaui/common"
import { ModifierState } from "./CommonModifier"
import { CommonMethod, Bindable, DividerStyle } from "./component/common"
import { Length, Dimension } from "./component/units"
import { Resource } from "global.resource"
export class SideBarContainerModifier extends CommonMethodModifier implements SideBarContainerAttribute,AttributeModifier<SideBarContainerAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
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
    _sideBarWidth_0_0value?: Length | Bindable<Length> | undefined
    _minSideBarWidth_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _minSideBarWidth_0_0value?: Length | undefined
    _maxSideBarWidth_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _maxSideBarWidth_0_0value?: Length | undefined
    _autoHide_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _autoHide_0_0value?: boolean | undefined
    _sideBarPosition_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _sideBarPosition_0_0value?: SideBarPosition | undefined
    _divider_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _divider_0_0value?: DividerStyle | null | undefined
    _minContentWidth_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _minContentWidth_0_0value?: Dimension | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkSideBarContainerPeer;
        if (this._showSideBar_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._showSideBar_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setShowSideBarAttribute((this._showSideBar_0_0value as boolean | Bindable<boolean> | undefined));
                    this._showSideBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._showSideBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._showSideBar_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setShowSideBarAttribute((undefined as boolean | Bindable<boolean> | undefined));
                }
            }
        }
        if (this._controlButton_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._controlButton_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setControlButtonAttribute((this._controlButton_0_0value as ButtonStyle | undefined));
                    this._controlButton_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._controlButton_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._controlButton_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setControlButtonAttribute((undefined as ButtonStyle | undefined));
                }
            }
        }
        if (this._showControlButton_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._showControlButton_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setShowControlButtonAttribute((this._showControlButton_0_0value as boolean | undefined));
                    this._showControlButton_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._showControlButton_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._showControlButton_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setShowControlButtonAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnChangeAttribute((this._onChange_0_0value as ((value: boolean) => void) | undefined));
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnChangeAttribute((undefined as ((value: boolean) => void) | undefined));
                }
            }
        }
        if (this._sideBarWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._sideBarWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSideBarWidthAttribute((this._sideBarWidth_0_0value as Length | Bindable<Length> | undefined));
                    this._sideBarWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._sideBarWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._sideBarWidth_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSideBarWidthAttribute((undefined as Length | Bindable<Length> | undefined));
                }
            }
        }
        if (this._minSideBarWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._minSideBarWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMinSideBarWidthAttribute((this._minSideBarWidth_0_0value as Length | undefined));
                    this._minSideBarWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._minSideBarWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._minSideBarWidth_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMinSideBarWidthAttribute((undefined as Length | undefined));
                }
            }
        }
        if (this._maxSideBarWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._maxSideBarWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMaxSideBarWidthAttribute((this._maxSideBarWidth_0_0value as Length | undefined));
                    this._maxSideBarWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._maxSideBarWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._maxSideBarWidth_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMaxSideBarWidthAttribute((undefined as Length | undefined));
                }
            }
        }
        if (this._autoHide_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._autoHide_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAutoHideAttribute((this._autoHide_0_0value as boolean | undefined));
                    this._autoHide_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._autoHide_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._autoHide_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAutoHideAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._sideBarPosition_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._sideBarPosition_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSideBarPositionAttribute((this._sideBarPosition_0_0value as SideBarPosition | undefined));
                    this._sideBarPosition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._sideBarPosition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._sideBarPosition_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSideBarPositionAttribute((undefined as SideBarPosition | undefined));
                }
            }
        }
        if (this._divider_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._divider_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDividerAttribute((this._divider_0_0value as DividerStyle | null | undefined));
                    this._divider_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._divider_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._divider_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDividerAttribute((undefined as DividerStyle | null | undefined));
                }
            }
        }
        if (this._minContentWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._minContentWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMinContentWidthAttribute((this._minContentWidth_0_0value as Dimension | undefined));
                    this._minContentWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._minContentWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._minContentWidth_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMinContentWidthAttribute((undefined as Dimension | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: SideBarContainerModifier): void {
       super.mergeModifier(modifier)
        this._state = modifier._state;
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
                    this.sideBarWidth((undefined as Length | Bindable<Length> | undefined));
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
                    this.minSideBarWidth((undefined as Length | undefined));
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
                    this.maxSideBarWidth((undefined as Length | undefined));
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
            this._state.fireChange()
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
            this._state.fireChange()
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
            this._state.fireChange()
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
            this._state.fireChange()
        } else
        {
            this._onChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    sideBarWidth(value: Length | Bindable<Length> | undefined): this {
        if (((this._sideBarWidth_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._sideBarWidth_0_flag = AttributeUpdaterFlag.UPDATE
            this._sideBarWidth_0_0value = value
            this._state.fireChange()
        } else
        {
            this._sideBarWidth_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    minSideBarWidth(value: Length | undefined): this {
        if (((this._minSideBarWidth_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._minSideBarWidth_0_flag = AttributeUpdaterFlag.UPDATE
            this._minSideBarWidth_0_0value = value
            this._state.fireChange()
        } else
        {
            this._minSideBarWidth_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    maxSideBarWidth(value: Length | undefined): this {
        if (((this._maxSideBarWidth_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._maxSideBarWidth_0_flag = AttributeUpdaterFlag.UPDATE
            this._maxSideBarWidth_0_0value = value
            this._state.fireChange()
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
            this._state.fireChange()
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
            this._state.fireChange()
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
            this._state.fireChange()
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
            this._state.fireChange()
        } else
        {
            this._minContentWidth_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<SideBarContainerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
