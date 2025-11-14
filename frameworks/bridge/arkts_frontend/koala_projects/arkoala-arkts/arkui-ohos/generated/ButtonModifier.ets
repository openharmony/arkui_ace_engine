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
import { AttributeModifier, ContentModifier } from "#handwritten"
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { ArkButtonPeer, ButtonType, ButtonStyleMode, ControlSize, ButtonRole, ButtonConfiguration, ButtonLabelStyle, ButtonAttribute } from "./component/button"
import { int32 } from "@koalaui/common"
import { ModifierState } from "./CommonModifier"
import { CommonMethod } from "./component/common"
import { ResourceColor, Length } from "./component/units"
import { Color, FontWeight, FontStyle } from "./component/enums"
import { Resource } from "global.resource"
export class ButtonModifier extends CommonMethodModifier implements ButtonAttribute,AttributeModifier<ButtonAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: ButtonAttribute): void { }
    applyPressedAttribute(instance: ButtonAttribute): void { }
    applyFocusedAttribute(instance: ButtonAttribute): void { }
    applyDisabledAttribute(instance: ButtonAttribute): void { }
    applySelectedAttribute(instance: ButtonAttribute): void { }
    _type_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _type_0_0value?: ButtonType | undefined
    _stateEffect_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _stateEffect_0_0value?: boolean | undefined
    _buttonStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _buttonStyle_0_0value?: ButtonStyleMode | undefined
    _controlSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _controlSize_0_0value?: ControlSize | undefined
    _role_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _role_0_0value?: ButtonRole | undefined
    _fontColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontColor_0_0value?: ResourceColor | undefined
    _fontSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontSize_0_0value?: Length | undefined
    _fontWeight_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontWeight_0_0value?: int32 | FontWeight | string | undefined
    _fontStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontStyle_0_0value?: FontStyle | undefined
    _fontFamily_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontFamily_0_0value?: string | Resource | undefined
    _labelStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _labelStyle_0_0value?: ButtonLabelStyle | undefined
    _minFontScale_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _minFontScale_0_0value?: double | Resource | undefined
    _maxFontScale_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _maxFontScale_0_0value?: double | Resource | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkButtonPeer;
        if (this._type_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._type_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTypeAttribute((this._type_0_0value as ButtonType | undefined));
                    this._type_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._type_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._type_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTypeAttribute((undefined as ButtonType | undefined));
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
        if (this._buttonStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._buttonStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setButtonStyleAttribute((this._buttonStyle_0_0value as ButtonStyleMode | undefined));
                    this._buttonStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._buttonStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._buttonStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setButtonStyleAttribute((undefined as ButtonStyleMode | undefined));
                }
            }
        }
        if (this._controlSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._controlSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setControlSizeAttribute((this._controlSize_0_0value as ControlSize | undefined));
                    this._controlSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._controlSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._controlSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setControlSizeAttribute((undefined as ControlSize | undefined));
                }
            }
        }
        if (this._role_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._role_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setRoleAttribute((this._role_0_0value as ButtonRole | undefined));
                    this._role_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._role_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._role_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setRoleAttribute((undefined as ButtonRole | undefined));
                }
            }
        }
        if (this._fontColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFontColorAttribute((this._fontColor_0_0value as ResourceColor | undefined));
                    this._fontColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFontColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._fontSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFontSizeAttribute((this._fontSize_0_0value as Length | undefined));
                    this._fontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFontSizeAttribute((undefined as Length | undefined));
                }
            }
        }
        if (this._fontWeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontWeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFontWeightAttribute((this._fontWeight_0_0value as int32 | FontWeight | string | undefined));
                    this._fontWeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontWeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontWeight_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFontWeightAttribute((undefined as int32 | FontWeight | string | undefined));
                }
            }
        }
        if (this._fontStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFontStyleAttribute((this._fontStyle_0_0value as FontStyle | undefined));
                    this._fontStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFontStyleAttribute((undefined as FontStyle | undefined));
                }
            }
        }
        if (this._fontFamily_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontFamily_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFontFamilyAttribute((this._fontFamily_0_0value as string | Resource | undefined));
                    this._fontFamily_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontFamily_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontFamily_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFontFamilyAttribute((undefined as string | Resource | undefined));
                }
            }
        }
        if (this._labelStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._labelStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setLabelStyleAttribute((this._labelStyle_0_0value as ButtonLabelStyle | undefined));
                    this._labelStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._labelStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._labelStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setLabelStyleAttribute((undefined as ButtonLabelStyle | undefined));
                }
            }
        }
        if (this._minFontScale_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._minFontScale_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMinFontScaleAttribute((this._minFontScale_0_0value as double | Resource | undefined));
                    this._minFontScale_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._minFontScale_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._minFontScale_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMinFontScaleAttribute((undefined as double | Resource | undefined));
                }
            }
        }
        if (this._maxFontScale_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._maxFontScale_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMaxFontScaleAttribute((this._maxFontScale_0_0value as double | Resource | undefined));
                    this._maxFontScale_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._maxFontScale_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._maxFontScale_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMaxFontScaleAttribute((undefined as double | Resource | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: ButtonModifier): void {
       super.mergeModifier(modifier)
        this._state = modifier._state;
        if (modifier._type_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._type_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.type(modifier._type_0_0value);
                    break;
                }
                default: {
                    this.type((undefined as ButtonType | undefined));
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
        if (modifier._buttonStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._buttonStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.buttonStyle(modifier._buttonStyle_0_0value);
                    break;
                }
                default: {
                    this.buttonStyle((undefined as ButtonStyleMode | undefined));
                }
            }
        }
        if (modifier._controlSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._controlSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.controlSize(modifier._controlSize_0_0value);
                    break;
                }
                default: {
                    this.controlSize((undefined as ControlSize | undefined));
                }
            }
        }
        if (modifier._role_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._role_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.role(modifier._role_0_0value);
                    break;
                }
                default: {
                    this.role((undefined as ButtonRole | undefined));
                }
            }
        }
        if (modifier._fontColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fontColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fontColor(modifier._fontColor_0_0value);
                    break;
                }
                default: {
                    this.fontColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._fontSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fontSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fontSize(modifier._fontSize_0_0value);
                    break;
                }
                default: {
                    this.fontSize((undefined as Length | undefined));
                }
            }
        }
        if (modifier._fontWeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fontWeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fontWeight(modifier._fontWeight_0_0value);
                    break;
                }
                default: {
                    this.fontWeight((undefined as int32 | FontWeight | string | undefined));
                }
            }
        }
        if (modifier._fontStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fontStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fontStyle(modifier._fontStyle_0_0value);
                    break;
                }
                default: {
                    this.fontStyle((undefined as FontStyle | undefined));
                }
            }
        }
        if (modifier._fontFamily_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fontFamily_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fontFamily(modifier._fontFamily_0_0value);
                    break;
                }
                default: {
                    this.fontFamily((undefined as string | Resource | undefined));
                }
            }
        }
        if (modifier._labelStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._labelStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.labelStyle(modifier._labelStyle_0_0value);
                    break;
                }
                default: {
                    this.labelStyle((undefined as ButtonLabelStyle | undefined));
                }
            }
        }
        if (modifier._minFontScale_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._minFontScale_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.minFontScale(modifier._minFontScale_0_0value);
                    break;
                }
                default: {
                    this.minFontScale((undefined as double | Resource | undefined));
                }
            }
        }
        if (modifier._maxFontScale_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._maxFontScale_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.maxFontScale(modifier._maxFontScale_0_0value);
                    break;
                }
                default: {
                    this.maxFontScale((undefined as double | Resource | undefined));
                }
            }
        }
    }
    type(value: ButtonType | undefined): this {
        if (((this._type_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._type_0_flag = AttributeUpdaterFlag.UPDATE
            this._type_0_0value = value
            this._state.fireChange()
        } else
        {
            this._type_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    stateEffect(value: boolean | undefined): this {
        if (((this._stateEffect_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._stateEffect_0_0value) !== (value)))
        {
            this._stateEffect_0_flag = AttributeUpdaterFlag.UPDATE
            this._stateEffect_0_0value = value
            this._state.fireChange()
        } else
        {
            this._stateEffect_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    buttonStyle(value: ButtonStyleMode | undefined): this {
        if (((this._buttonStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._buttonStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._buttonStyle_0_0value = value
            this._state.fireChange()
        } else
        {
            this._buttonStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    controlSize(value: ControlSize | undefined): this {
        if (((this._controlSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._controlSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._controlSize_0_0value = value
            this._state.fireChange()
        } else
        {
            this._controlSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    role(value: ButtonRole | undefined): this {
        if (((this._role_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._role_0_flag = AttributeUpdaterFlag.UPDATE
            this._role_0_0value = value
            this._state.fireChange()
        } else
        {
            this._role_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fontColor(value: ResourceColor | undefined): this {
        if (((this._fontColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._fontColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._fontColor_0_0value = value
            this._state.fireChange()
        } else
        {
            this._fontColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fontSize(value: Length | undefined): this {
        if (((this._fontSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._fontSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._fontSize_0_0value = value
            this._state.fireChange()
        } else
        {
            this._fontSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fontWeight(value: int32 | FontWeight | string | undefined): this {
        if (((this._fontWeight_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._fontWeight_0_flag = AttributeUpdaterFlag.UPDATE
            this._fontWeight_0_0value = value
            this._state.fireChange()
        } else
        {
            this._fontWeight_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fontStyle(value: FontStyle | undefined): this {
        if (((this._fontStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._fontStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._fontStyle_0_0value = value
            this._state.fireChange()
        } else
        {
            this._fontStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fontFamily(value: string | Resource | undefined): this {
        if (((this._fontFamily_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._fontFamily_0_flag = AttributeUpdaterFlag.UPDATE
            this._fontFamily_0_0value = value
            this._state.fireChange()
        } else
        {
            this._fontFamily_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    labelStyle(value: ButtonLabelStyle | undefined): this {
        if (((this._labelStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._labelStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._labelStyle_0_0value = value
            this._state.fireChange()
        } else
        {
            this._labelStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    minFontScale(value: double | Resource | undefined): this {
        if (((this._minFontScale_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._minFontScale_0_flag = AttributeUpdaterFlag.UPDATE
            this._minFontScale_0_0value = value
            this._state.fireChange()
        } else
        {
            this._minFontScale_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    maxFontScale(value: double | Resource | undefined): this {
        if (((this._maxFontScale_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._maxFontScale_0_flag = AttributeUpdaterFlag.UPDATE
            this._maxFontScale_0_0value = value
            this._state.fireChange()
        } else
        {
            this._maxFontScale_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ButtonAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
