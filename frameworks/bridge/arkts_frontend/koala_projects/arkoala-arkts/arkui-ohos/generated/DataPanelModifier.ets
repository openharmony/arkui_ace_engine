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
import { AttributeModifier, ContentModifier, hookDataPanelContentModifier } from "#handwritten"
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { ArkDataPanelPeer, LinearGradient, DataPanelShadowOptions, DataPanelConfiguration, DataPanelAttribute } from "./component/dataPanel"
import { int32 } from "@koalaui/common"
import { ModifierState } from "./CommonModifier"
import { CommonMethod } from "./component/common"
import { ResourceColor, Length } from "./component/units"
import { Color } from "./component/enums"
import { Resource } from "global.resource"
export class DataPanelModifier extends CommonMethodModifier implements DataPanelAttribute,AttributeModifier<DataPanelAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: DataPanelAttribute): void { }
    applyPressedAttribute(instance: DataPanelAttribute): void { }
    applyFocusedAttribute(instance: DataPanelAttribute): void { }
    applyDisabledAttribute(instance: DataPanelAttribute): void { }
    applySelectedAttribute(instance: DataPanelAttribute): void { }
    _closeEffect_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _closeEffect_0_0value?: boolean | undefined
    _valueColors_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _valueColors_0_0value?: Array<ResourceColor | LinearGradient> | undefined
    _trackBackgroundColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _trackBackgroundColor_0_0value?: ResourceColor | undefined
    _strokeWidth_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _strokeWidth_0_0value?: Length | undefined
    _trackShadow_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _trackShadow_0_0value?: DataPanelShadowOptions | null | undefined
    _contentModifier_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _contentModifier_0_0value?: ContentModifier<DataPanelConfiguration> | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkDataPanelPeer;
        if (this._closeEffect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._closeEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCloseEffectAttribute((this._closeEffect_0_0value as boolean | undefined));
                    this._closeEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._closeEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._closeEffect_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCloseEffectAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._valueColors_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._valueColors_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setValueColorsAttribute((this._valueColors_0_0value as Array<ResourceColor | LinearGradient> | undefined));
                    this._valueColors_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._valueColors_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._valueColors_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setValueColorsAttribute((undefined as Array<ResourceColor | LinearGradient> | undefined));
                }
            }
        }
        if (this._trackBackgroundColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._trackBackgroundColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTrackBackgroundColorAttribute((this._trackBackgroundColor_0_0value as ResourceColor | undefined));
                    this._trackBackgroundColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._trackBackgroundColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._trackBackgroundColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTrackBackgroundColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._strokeWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._strokeWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setStrokeWidthAttribute((this._strokeWidth_0_0value as Length | undefined));
                    this._strokeWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._strokeWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._strokeWidth_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setStrokeWidthAttribute((undefined as Length | undefined));
                }
            }
        }
        if (this._trackShadow_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._trackShadow_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTrackShadowAttribute((this._trackShadow_0_0value as DataPanelShadowOptions | null | undefined));
                    this._trackShadow_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._trackShadow_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._trackShadow_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTrackShadowAttribute((undefined as DataPanelShadowOptions | null | undefined));
                }
            }
        }
        if (this._contentModifier_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._contentModifier_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    hookDataPanelContentModifier(peer, (this._contentModifier_0_0value as ContentModifier<DataPanelConfiguration> | undefined));
                    this._contentModifier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._contentModifier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._contentModifier_0_flag = AttributeUpdaterFlag.INITIAL;
                    hookDataPanelContentModifier(peer, (undefined as ContentModifier<DataPanelConfiguration> | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: DataPanelModifier): void {
       super.mergeModifier(modifier)
        this._state = modifier._state;
        if (modifier._closeEffect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._closeEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.closeEffect(modifier._closeEffect_0_0value);
                    break;
                }
                default: {
                    this.closeEffect((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._valueColors_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._valueColors_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.valueColors(modifier._valueColors_0_0value);
                    break;
                }
                default: {
                    this.valueColors((undefined as Array<ResourceColor | LinearGradient> | undefined));
                }
            }
        }
        if (modifier._trackBackgroundColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._trackBackgroundColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.trackBackgroundColor(modifier._trackBackgroundColor_0_0value);
                    break;
                }
                default: {
                    this.trackBackgroundColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._strokeWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._strokeWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.strokeWidth(modifier._strokeWidth_0_0value);
                    break;
                }
                default: {
                    this.strokeWidth((undefined as Length | undefined));
                }
            }
        }
        if (modifier._trackShadow_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._trackShadow_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.trackShadow(modifier._trackShadow_0_0value);
                    break;
                }
                default: {
                    this.trackShadow((undefined as DataPanelShadowOptions | null | undefined));
                }
            }
        }
        if (modifier._contentModifier_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._contentModifier_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.contentModifier(modifier._contentModifier_0_0value);
                    break;
                }
                default: {
                    this.contentModifier((undefined as ContentModifier<DataPanelConfiguration> | undefined));
                }
            }
        }
    }
    closeEffect(value: boolean | undefined): this {
        if (((this._closeEffect_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._closeEffect_0_0value) !== (value)))
        {
            this._closeEffect_0_flag = AttributeUpdaterFlag.UPDATE
            this._closeEffect_0_0value = value
            this._state.fireChange()
        } else
        {
            this._closeEffect_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    valueColors(value: Array<ResourceColor | LinearGradient> | undefined): this {
        if (((this._valueColors_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._valueColors_0_flag = AttributeUpdaterFlag.UPDATE
            this._valueColors_0_0value = value
            this._state.fireChange()
        } else
        {
            this._valueColors_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    trackBackgroundColor(value: ResourceColor | undefined): this {
        if (((this._trackBackgroundColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._trackBackgroundColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._trackBackgroundColor_0_0value = value
            this._state.fireChange()
        } else
        {
            this._trackBackgroundColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    strokeWidth(value: Length | undefined): this {
        if (((this._strokeWidth_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._strokeWidth_0_flag = AttributeUpdaterFlag.UPDATE
            this._strokeWidth_0_0value = value
            this._state.fireChange()
        } else
        {
            this._strokeWidth_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    trackShadow(value: DataPanelShadowOptions | null | undefined): this {
        if (((this._trackShadow_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._trackShadow_0_flag = AttributeUpdaterFlag.UPDATE
            this._trackShadow_0_0value = value
            this._state.fireChange()
        } else
        {
            this._trackShadow_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    contentModifier(value: ContentModifier<DataPanelConfiguration> | undefined): this {
        if (((this._contentModifier_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._contentModifier_0_flag = AttributeUpdaterFlag.UPDATE
            this._contentModifier_0_0value = value
            this._state.fireChange()
        } else
        {
            this._contentModifier_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<DataPanelAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
