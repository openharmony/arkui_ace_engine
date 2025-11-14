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
import { AttributeModifier, ContentModifier, hookProgressContentModifier } from "#handwritten"
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { ArkProgressPeer, LinearStyleOptions, RingStyleOptions, CapsuleStyleOptions, ProgressStyleOptions, ProgressConfiguration, ProgressAttribute } from "./component/progress"
import { int32 } from "@koalaui/common"
import { ModifierState } from "./CommonModifier"
import { CommonMethod } from "./component/common"
import { ResourceColor } from "./component/units"
import { Color } from "./component/enums"
import { Resource } from "global.resource"
import { LinearGradient } from "./component/dataPanel"
export class ProgressModifier extends CommonMethodModifier implements ProgressAttribute,AttributeModifier<ProgressAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: ProgressAttribute): void { }
    applyPressedAttribute(instance: ProgressAttribute): void { }
    applyFocusedAttribute(instance: ProgressAttribute): void { }
    applyDisabledAttribute(instance: ProgressAttribute): void { }
    applySelectedAttribute(instance: ProgressAttribute): void { }
    _value_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _value_0_0value?: number | undefined
    _color_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _color_0_0value?: ResourceColor | LinearGradient | undefined
    _style_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _style_0_0value?: LinearStyleOptions | RingStyleOptions | CapsuleStyleOptions | ProgressStyleOptions | undefined
    _privacySensitive_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _privacySensitive_0_0value?: boolean | undefined
    _contentModifier_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _contentModifier_0_0value?: ContentModifier<ProgressConfiguration> | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkProgressPeer;
        if (this._value_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._value_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setValueAttribute((this._value_0_0value as number | undefined));
                    this._value_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._value_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._value_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setValueAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._color_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._color_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setColorAttribute((this._color_0_0value as ResourceColor | LinearGradient | undefined));
                    this._color_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._color_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._color_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setColorAttribute((undefined as ResourceColor | LinearGradient | undefined));
                }
            }
        }
        if (this._style_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._style_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setStyleAttribute((this._style_0_0value as LinearStyleOptions | RingStyleOptions | CapsuleStyleOptions | ProgressStyleOptions | undefined));
                    this._style_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._style_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._style_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setStyleAttribute((undefined as LinearStyleOptions | RingStyleOptions | CapsuleStyleOptions | ProgressStyleOptions | undefined));
                }
            }
        }
        if (this._privacySensitive_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._privacySensitive_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPrivacySensitiveAttribute((this._privacySensitive_0_0value as boolean | undefined));
                    this._privacySensitive_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._privacySensitive_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._privacySensitive_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPrivacySensitiveAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._contentModifier_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._contentModifier_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    hookProgressContentModifier(peer, (this._contentModifier_0_0value as ContentModifier<ProgressConfiguration> | undefined));
                    this._contentModifier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._contentModifier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._contentModifier_0_flag = AttributeUpdaterFlag.INITIAL;
                    hookProgressContentModifier(peer, (undefined as ContentModifier<ProgressConfiguration> | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: ProgressModifier): void {
       super.mergeModifier(modifier)
        this._state = modifier._state;
        if (modifier._value_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._value_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.value(modifier._value_0_0value);
                    break;
                }
                default: {
                    this.value((undefined as number | undefined));
                }
            }
        }
        if (modifier._color_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._color_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.color(modifier._color_0_0value);
                    break;
                }
                default: {
                    this.color((undefined as ResourceColor | LinearGradient | undefined));
                }
            }
        }
        if (modifier._style_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._style_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.style(modifier._style_0_0value);
                    break;
                }
                default: {
                    this.style((undefined as LinearStyleOptions | RingStyleOptions | CapsuleStyleOptions | ProgressStyleOptions | undefined));
                }
            }
        }
        if (modifier._privacySensitive_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._privacySensitive_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.privacySensitive(modifier._privacySensitive_0_0value);
                    break;
                }
                default: {
                    this.privacySensitive((undefined as boolean | undefined));
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
                    this.contentModifier((undefined as ContentModifier<ProgressConfiguration> | undefined));
                }
            }
        }
    }
    value(value: number | undefined): this {
        if (((this._value_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._value_0_0value) !== (value)))
        {
            this._value_0_flag = AttributeUpdaterFlag.UPDATE
            this._value_0_0value = value
            this._state.fireChange()
        } else
        {
            this._value_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    color(value: ResourceColor | LinearGradient | undefined): this {
        if (((this._color_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._color_0_flag = AttributeUpdaterFlag.UPDATE
            this._color_0_0value = value
            this._state.fireChange()
        } else
        {
            this._color_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    style(value: LinearStyleOptions | RingStyleOptions | CapsuleStyleOptions | ProgressStyleOptions | undefined): this {
        if (((this._style_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._style_0_flag = AttributeUpdaterFlag.UPDATE
            this._style_0_0value = value
            this._state.fireChange()
        } else
        {
            this._style_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    privacySensitive(value: boolean | undefined): this {
        if (((this._privacySensitive_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._privacySensitive_0_0value) !== (value)))
        {
            this._privacySensitive_0_flag = AttributeUpdaterFlag.UPDATE
            this._privacySensitive_0_0value = value
            this._state.fireChange()
        } else
        {
            this._privacySensitive_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    contentModifier(value: ContentModifier<ProgressConfiguration> | undefined): this {
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
    public attributeModifier(value: AttributeModifier<ProgressAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
