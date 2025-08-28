/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { AttributeModifier, ContentModifier } from 'arkui/component/common'
import { ButtonType, ButtonStyleMode, ControlSize, ButtonRole, ButtonConfiguration, ButtonLabelStyle, ButtonAttribute, ArkButtonPeer, ArkButtonComponent } from 'arkui/component/button'
import { AttributeUpdaterFlag, CommonMethodModifier } from './CommonMethodModifier';
import { Length, ResourceColor } from './component/units';
import { FontWeight, FontStyle } from './component/enums'
import { Resource } from 'global.resource'
import { hookButtonContentModifier } from './handwritten';
import { PeerNode } from './PeerNode';

export class ButtonModifier extends CommonMethodModifier implements ButtonAttribute, AttributeModifier<ButtonAttribute> {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
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
    _fontWeight_0_0value?: number | FontWeight | string | undefined
    _fontStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontStyle_0_0value?: FontStyle | undefined
    _fontFamily_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontFamily_0_0value?: string | Resource | undefined
    _contentModifier_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _contentModifier_0_0value?: ContentModifier<ButtonConfiguration> | undefined
    _labelStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _labelStyle_0_0value?: ButtonLabelStyle | undefined
    _minFontScale_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _minFontScale_0_0value?: number | Resource | undefined
    _maxFontScale_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _maxFontScale_0_0value?: number | Resource | undefined
    applyModifierPatch(value: PeerNode): void {
        super.applyModifierPatch(value)
        const peer = value as ArkButtonPeer
        if (this._type_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._type_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.typeAttribute((this._type_0_0value as ButtonType | undefined));
                    this._type_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._type_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._type_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.typeAttribute((undefined as ButtonType | undefined));
                }
            }
        }
        if (this._stateEffect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._stateEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.stateEffectAttribute((this._stateEffect_0_0value as boolean | undefined));
                    this._stateEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._stateEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._stateEffect_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.stateEffectAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._buttonStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._buttonStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.buttonStyleAttribute((this._buttonStyle_0_0value as ButtonStyleMode | undefined));
                    this._buttonStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._buttonStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._buttonStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.buttonStyleAttribute((undefined as ButtonStyleMode | undefined));
                }
            }
        }
        if (this._controlSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._controlSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.controlSizeAttribute((this._controlSize_0_0value as ControlSize | undefined));
                    this._controlSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._controlSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._controlSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.controlSizeAttribute((undefined as ControlSize | undefined));
                }
            }
        }
        if (this._role_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._role_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.roleAttribute((this._role_0_0value as ButtonRole | undefined));
                    this._role_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._role_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._role_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.roleAttribute((undefined as ButtonRole | undefined));
                }
            }
        }
        if (this._fontColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.fontColorAttribute((this._fontColor_0_0value as ResourceColor | undefined));
                    this._fontColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.fontColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._fontSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.fontSizeAttribute((this._fontSize_0_0value as Length | undefined));
                    this._fontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.fontSizeAttribute((undefined as Length | undefined));
                }
            }
        }
        if (this._fontWeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontWeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.fontWeightAttribute((this._fontWeight_0_0value as number | FontWeight | string | undefined));
                    this._fontWeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontWeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontWeight_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.fontWeightAttribute((undefined as number | FontWeight | string | undefined));
                }
            }
        }
        if (this._fontStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.fontStyleAttribute((this._fontStyle_0_0value as FontStyle | undefined));
                    this._fontStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.fontStyleAttribute((undefined as FontStyle | undefined));
                }
            }
        }
        if (this._fontFamily_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontFamily_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.fontFamilyAttribute((this._fontFamily_0_0value as string | Resource | undefined));
                    this._fontFamily_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontFamily_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontFamily_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.fontFamilyAttribute((undefined as string | Resource | undefined));
                }
            }
        }
        if (this._contentModifier_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._contentModifier_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    const arkButtonComponent: ArkButtonComponent = new ArkButtonComponent();
                    arkButtonComponent.setPeer(peer);
                    hookButtonContentModifier(arkButtonComponent, (this._contentModifier_0_0value as ContentModifier<ButtonConfiguration> | undefined));
                    this._contentModifier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._contentModifier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._contentModifier_0_flag = AttributeUpdaterFlag.INITIAL;
                    const arkButtonComponent: ArkButtonComponent = new ArkButtonComponent();
                    arkButtonComponent.setPeer(peer);
                    hookButtonContentModifier(arkButtonComponent, undefined);
                }
            }
        }
        if (this._labelStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._labelStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.labelStyleAttribute((this._labelStyle_0_0value as ButtonLabelStyle | undefined));
                    this._labelStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._labelStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._labelStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.labelStyleAttribute((undefined as ButtonLabelStyle | undefined));
                }
            }
        }
        if (this._minFontScale_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._minFontScale_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.minFontScaleAttribute((this._minFontScale_0_0value as number | Resource | undefined));
                    this._minFontScale_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._minFontScale_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._minFontScale_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.minFontScaleAttribute((undefined as number | Resource | undefined));
                }
            }
        }
        if (this._maxFontScale_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._maxFontScale_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.maxFontScaleAttribute((this._maxFontScale_0_0value as number | Resource | undefined));
                    this._maxFontScale_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._maxFontScale_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._maxFontScale_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.maxFontScaleAttribute((undefined as number | Resource | undefined));
                }
            }
        }
    }
    mergeModifier(value: CommonMethodModifier): void {
        super.mergeModifier(value)
        if (!(value instanceof ButtonModifier)) {
            return
        }
        const modifier = value as ButtonModifier;
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
                    this.fontWeight((undefined as number | FontWeight | string | undefined));
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
        if (modifier._contentModifier_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._contentModifier_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.contentModifier(modifier._contentModifier_0_0value);
                    break;
                }
                default: {
                    this.contentModifier((undefined as ContentModifier<ButtonConfiguration> | undefined));
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
                    this.minFontScale((undefined as number | Resource | undefined));
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
                    this.maxFontScale((undefined as number | Resource | undefined));
                }
            }
        }
    }
    type(value: ButtonType | undefined): this {
        if (((this._type_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._type_0_flag = AttributeUpdaterFlag.UPDATE
            this._type_0_0value = value
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
        } else
        {
            this._fontSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fontWeight(value: number | FontWeight | string | undefined): this {
        if (((this._fontWeight_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._fontWeight_0_flag = AttributeUpdaterFlag.UPDATE
            this._fontWeight_0_0value = value
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
        } else
        {
            this._fontFamily_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    contentModifier(value: ContentModifier<ButtonConfiguration> | undefined): this {
        if (((this._contentModifier_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._contentModifier_0_flag = AttributeUpdaterFlag.UPDATE
            this._contentModifier_0_0value = value
        } else
        {
            this._contentModifier_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    labelStyle(value: ButtonLabelStyle | undefined): this {
        if (((this._labelStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._labelStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._labelStyle_0_0value = value
        } else
        {
            this._labelStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    minFontScale(value: number | Resource | undefined): this {
        if (((this._minFontScale_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._minFontScale_0_flag = AttributeUpdaterFlag.UPDATE
            this._minFontScale_0_0value = value
        } else
        {
            this._minFontScale_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    maxFontScale(value: number | Resource | undefined): this {
        if (((this._maxFontScale_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._maxFontScale_0_flag = AttributeUpdaterFlag.UPDATE
            this._maxFontScale_0_0value = value
        } else
        {
            this._maxFontScale_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
}