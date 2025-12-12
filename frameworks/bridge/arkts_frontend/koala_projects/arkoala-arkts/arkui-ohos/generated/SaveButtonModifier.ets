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

import { SecurityComponentMethodModifier } from "./SecurityComponentMethodModifier"
import { AttributeModifier, extractors, hookSaveButtonOnClick } from '#handwritten'
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { ArkSaveButtonPeer, SaveButtonCallback, SaveButtonOnClickResult, SaveButtonAttribute } from "./component/saveButton"
import { int32 } from "@koalaui/common"
import { SecurityComponentMethod } from "./component/securityComponent"
import { ClickEvent } from "./component/common"
import { BusinessError } from "@ohos.base"
import { Resource } from "global.resource"
import { Dimension, SizeOptions, BorderRadiuses } from "./component/units"
import { ModifierState } from './CommonModifier'
export class SaveButtonModifier extends SecurityComponentMethodModifier implements SaveButtonAttribute,AttributeModifier<SaveButtonAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState	
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: SaveButtonAttribute): void { }
    applyPressedAttribute(instance: SaveButtonAttribute): void { }
    applyFocusedAttribute(instance: SaveButtonAttribute): void { }
    applyDisabledAttribute(instance: SaveButtonAttribute): void { }
    applySelectedAttribute(instance: SaveButtonAttribute): void { }
    _onClick_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onClick_0_0value?: SaveButtonCallback | undefined
    _setIcon_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _setIcon_0_0value?: Resource | undefined
    _setText_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _setText_0_0value?: string | Resource | undefined
    _iconSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _iconSize_0_0value?: Dimension | SizeOptions | undefined
    _iconBorderRadius_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _iconBorderRadius_0_0value?: Dimension | BorderRadiuses | undefined
    _stateEffect_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _stateEffect_0_0value?: boolean | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkSaveButtonPeer;
        if (this._onClick_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onClick_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    hookSaveButtonOnClick(peer, (this._onClick_0_0value as SaveButtonCallback | undefined));
                    this._onClick_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onClick_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onClick_0_flag = AttributeUpdaterFlag.INITIAL;
                    hookSaveButtonOnClick(peer, (undefined as SaveButtonCallback | undefined));
                }
            }
        }
        if (this._setIcon_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._setIcon_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSetIconAttribute((this._setIcon_0_0value as Resource | undefined));
                    this._setIcon_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._setIcon_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._setIcon_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSetIconAttribute((undefined as Resource | undefined));
                }
            }
        }
        if (this._setText_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._setText_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSetTextAttribute((this._setText_0_0value as string | Resource | undefined));
                    this._setText_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._setText_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._setText_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSetTextAttribute((undefined as string | Resource | undefined));
                }
            }
        }
        if (this._iconSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._iconSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setIconSizeAttribute((this._iconSize_0_0value as Dimension | SizeOptions | undefined));
                    this._iconSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._iconSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._iconSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setIconSizeAttribute((undefined as Dimension | SizeOptions | undefined));
                }
            }
        }
        if (this._iconBorderRadius_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._iconBorderRadius_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setIconBorderRadiusAttribute((this._iconBorderRadius_0_0value as Dimension | BorderRadiuses | undefined));
                    this._iconBorderRadius_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._iconBorderRadius_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._iconBorderRadius_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setIconBorderRadiusAttribute((undefined as Dimension | BorderRadiuses | undefined));
                }
            }
        }
        if (this._stateEffect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._stateEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setStateEffectAttribute((this._stateEffect_0_0value as boolean | undefined));
                    this._stateEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._stateEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._stateEffect_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setStateEffectAttribute((undefined as boolean | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: SaveButtonModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        if (modifier._onClick_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onClick_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onClick(modifier._onClick_0_0value);
                    break;
                }
                default: {
                    this.onClick((undefined as SaveButtonCallback | undefined));
                }
            }
        }
        if (modifier._setIcon_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._setIcon_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.setIcon(modifier._setIcon_0_0value);
                    break;
                }
                default: {
                    this.setIcon((undefined as Resource | undefined));
                }
            }
        }
        if (modifier._setText_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._setText_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.setText(modifier._setText_0_0value);
                    break;
                }
                default: {
                    this.setText((undefined as string | Resource | undefined));
                }
            }
        }
        if (modifier._iconSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._iconSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.iconSize(modifier._iconSize_0_0value);
                    break;
                }
                default: {
                    this.iconSize((undefined as Dimension | SizeOptions | undefined));
                }
            }
        }
        if (modifier._iconBorderRadius_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._iconBorderRadius_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.iconBorderRadius(modifier._iconBorderRadius_0_0value);
                    break;
                }
                default: {
                    this.iconBorderRadius((undefined as Dimension | BorderRadiuses | undefined));
                }
            }
        }
        if (modifier._stateEffect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._stateEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.stateEffect(modifier._stateEffect_0_0value);
                    break;
                }
                default: {
                    this.stateEffect((undefined as boolean | undefined));
                }
            }
        }
    }
    onClick(value: SaveButtonCallback | undefined): this {
        if (((this._onClick_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onClick_0_flag = AttributeUpdaterFlag.UPDATE
            this._onClick_0_0value = value
        } else
        {
            this._onClick_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    setIcon(value: Resource | undefined): this {
        if (((this._setIcon_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._setIcon_0_flag = AttributeUpdaterFlag.UPDATE
            this._setIcon_0_0value = value
        } else
        {
            this._setIcon_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    setText(value: string | Resource | undefined): this {
        if (((this._setText_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._setText_0_flag = AttributeUpdaterFlag.UPDATE
            this._setText_0_0value = value
        } else
        {
            this._setText_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    iconSize(value: Dimension | SizeOptions | undefined): this {
        if (((this._iconSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._iconSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._iconSize_0_0value = value
        } else
        {
            this._iconSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    iconBorderRadius(value: Dimension | BorderRadiuses | undefined): this {
        if (((this._iconBorderRadius_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._iconBorderRadius_0_flag = AttributeUpdaterFlag.UPDATE
            this._iconBorderRadius_0_0value = value
        } else
        {
            this._iconBorderRadius_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    stateEffect(value: boolean | undefined): this {
        if (((this._stateEffect_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._stateEffect_0_0value) !== (value)))
        {
            this._stateEffect_0_flag = AttributeUpdaterFlag.UPDATE
            this._stateEffect_0_0value = value
        } else
        {
            this._stateEffect_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<SaveButtonAttribute> | AttributeModifier<SecurityComponentMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
