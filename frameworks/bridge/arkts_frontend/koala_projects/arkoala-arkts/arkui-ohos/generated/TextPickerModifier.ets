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
import { AttributeModifier, hookTextPickerDivider } from "#handwritten"
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { ArkTextPickerPeer, TextPickerTextStyle, OnTextPickerChangeCallback, TextPickerScrollStopCallback, TextPickerEnterSelectedAreaCallback, DividerOptions, TextPickerAttribute } from "./component/textPicker"
import { int32 } from "@koalaui/common"
import { ModifierState } from "./CommonModifier"
import { CommonMethod, PickerTextStyle } from "./component/common"
import { Dimension } from "./component/units"
import { Resource } from "global.resource"
import { CrownSensitivity } from "./component/enums"
export class TextPickerModifier extends CommonMethodModifier implements TextPickerAttribute,AttributeModifier<TextPickerAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: TextPickerAttribute): void { }
    applyPressedAttribute(instance: TextPickerAttribute): void { }
    applyFocusedAttribute(instance: TextPickerAttribute): void { }
    applyDisabledAttribute(instance: TextPickerAttribute): void { }
    applySelectedAttribute(instance: TextPickerAttribute): void { }
    _defaultPickerItemHeight_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _defaultPickerItemHeight_0_0value?: double | string | undefined
    _canLoop_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _canLoop_0_0value?: boolean | undefined
    _disappearTextStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _disappearTextStyle_0_0value?: PickerTextStyle | undefined
    _textStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _textStyle_0_0value?: PickerTextStyle | undefined
    _selectedTextStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selectedTextStyle_0_0value?: PickerTextStyle | undefined
    _disableTextStyleAnimation_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _disableTextStyleAnimation_0_0value?: boolean | undefined
    _defaultTextStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _defaultTextStyle_0_0value?: TextPickerTextStyle | undefined
    _onChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onChange_0_0value?: OnTextPickerChangeCallback | undefined
    _onScrollStop_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onScrollStop_0_0value?: TextPickerScrollStopCallback | undefined
    _onEnterSelectedArea_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onEnterSelectedArea_0_0value?: TextPickerEnterSelectedAreaCallback | undefined
    _selectedIndex_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selectedIndex_0_0value?: int32 | Array<int32> | undefined
    _divider_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _divider_0_0value?: DividerOptions | null | undefined
    _gradientHeight_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _gradientHeight_0_0value?: Dimension | undefined
    _enableHapticFeedback_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableHapticFeedback_0_0value?: boolean | undefined
    _digitalCrownSensitivity_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _digitalCrownSensitivity_0_0value?: CrownSensitivity | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkTextPickerPeer;
        if (this._defaultPickerItemHeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._defaultPickerItemHeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDefaultPickerItemHeightAttribute((this._defaultPickerItemHeight_0_0value as double | string | undefined));
                    this._defaultPickerItemHeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._defaultPickerItemHeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._defaultPickerItemHeight_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDefaultPickerItemHeightAttribute((undefined as double | string | undefined));
                }
            }
        }
        if (this._canLoop_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._canLoop_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCanLoopAttribute((this._canLoop_0_0value as boolean | undefined));
                    this._canLoop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._canLoop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._canLoop_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCanLoopAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._disappearTextStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._disappearTextStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDisappearTextStyleAttribute((this._disappearTextStyle_0_0value as PickerTextStyle | undefined));
                    this._disappearTextStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._disappearTextStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._disappearTextStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDisappearTextStyleAttribute((undefined as PickerTextStyle | undefined));
                }
            }
        }
        if (this._textStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._textStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTextStyleAttribute((this._textStyle_0_0value as PickerTextStyle | undefined));
                    this._textStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._textStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._textStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTextStyleAttribute((undefined as PickerTextStyle | undefined));
                }
            }
        }
        if (this._selectedTextStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._selectedTextStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSelectedTextStyleAttribute((this._selectedTextStyle_0_0value as PickerTextStyle | undefined));
                    this._selectedTextStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selectedTextStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selectedTextStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSelectedTextStyleAttribute((undefined as PickerTextStyle | undefined));
                }
            }
        }
        if (this._disableTextStyleAnimation_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._disableTextStyleAnimation_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDisableTextStyleAnimationAttribute((this._disableTextStyleAnimation_0_0value as boolean | undefined));
                    this._disableTextStyleAnimation_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._disableTextStyleAnimation_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._disableTextStyleAnimation_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDisableTextStyleAnimationAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._defaultTextStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._defaultTextStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDefaultTextStyleAttribute((this._defaultTextStyle_0_0value as TextPickerTextStyle | undefined));
                    this._defaultTextStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._defaultTextStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._defaultTextStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDefaultTextStyleAttribute((undefined as TextPickerTextStyle | undefined));
                }
            }
        }
        if (this._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnChangeAttribute((this._onChange_0_0value as OnTextPickerChangeCallback | undefined));
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnChangeAttribute((undefined as OnTextPickerChangeCallback | undefined));
                }
            }
        }
        if (this._onScrollStop_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onScrollStop_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnScrollStopAttribute((this._onScrollStop_0_0value as TextPickerScrollStopCallback | undefined));
                    this._onScrollStop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onScrollStop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onScrollStop_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnScrollStopAttribute((undefined as TextPickerScrollStopCallback | undefined));
                }
            }
        }
        if (this._onEnterSelectedArea_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onEnterSelectedArea_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnEnterSelectedAreaAttribute((this._onEnterSelectedArea_0_0value as TextPickerEnterSelectedAreaCallback | undefined));
                    this._onEnterSelectedArea_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onEnterSelectedArea_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onEnterSelectedArea_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnEnterSelectedAreaAttribute((undefined as TextPickerEnterSelectedAreaCallback | undefined));
                }
            }
        }
        if (this._selectedIndex_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._selectedIndex_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSelectedIndexAttribute((this._selectedIndex_0_0value as int32 | Array<int32> | undefined));
                    this._selectedIndex_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selectedIndex_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selectedIndex_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSelectedIndexAttribute((undefined as int32 | Array<int32> | undefined));
                }
            }
        }
        if (this._divider_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._divider_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    hookTextPickerDivider(peer, (this._divider_0_0value as DividerOptions | null | undefined));
                    this._divider_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._divider_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._divider_0_flag = AttributeUpdaterFlag.INITIAL;
                    hookTextPickerDivider(peer, (undefined as DividerOptions | null | undefined));
                }
            }
        }
        if (this._gradientHeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._gradientHeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setGradientHeightAttribute((this._gradientHeight_0_0value as Dimension | undefined));
                    this._gradientHeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._gradientHeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._gradientHeight_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setGradientHeightAttribute((undefined as Dimension | undefined));
                }
            }
        }
        if (this._enableHapticFeedback_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableHapticFeedback_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableHapticFeedbackAttribute((this._enableHapticFeedback_0_0value as boolean | undefined));
                    this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableHapticFeedbackAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._digitalCrownSensitivity_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._digitalCrownSensitivity_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDigitalCrownSensitivityAttribute((this._digitalCrownSensitivity_0_0value as CrownSensitivity | undefined));
                    this._digitalCrownSensitivity_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._digitalCrownSensitivity_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._digitalCrownSensitivity_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDigitalCrownSensitivityAttribute((undefined as CrownSensitivity | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: TextPickerModifier): void {
       super.mergeModifier(modifier)
        this._state = modifier._state;
        if (modifier._defaultPickerItemHeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._defaultPickerItemHeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.defaultPickerItemHeight(modifier._defaultPickerItemHeight_0_0value);
                    break;
                }
                default: {
                    this.defaultPickerItemHeight((undefined as double | string | undefined));
                }
            }
        }
        if (modifier._canLoop_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._canLoop_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.canLoop(modifier._canLoop_0_0value);
                    break;
                }
                default: {
                    this.canLoop((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._disappearTextStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._disappearTextStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.disappearTextStyle(modifier._disappearTextStyle_0_0value);
                    break;
                }
                default: {
                    this.disappearTextStyle((undefined as PickerTextStyle | undefined));
                }
            }
        }
        if (modifier._textStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._textStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.textStyle(modifier._textStyle_0_0value);
                    break;
                }
                default: {
                    this.textStyle((undefined as PickerTextStyle | undefined));
                }
            }
        }
        if (modifier._selectedTextStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._selectedTextStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.selectedTextStyle(modifier._selectedTextStyle_0_0value);
                    break;
                }
                default: {
                    this.selectedTextStyle((undefined as PickerTextStyle | undefined));
                }
            }
        }
        if (modifier._disableTextStyleAnimation_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._disableTextStyleAnimation_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.disableTextStyleAnimation(modifier._disableTextStyleAnimation_0_0value);
                    break;
                }
                default: {
                    this.disableTextStyleAnimation((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._defaultTextStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._defaultTextStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.defaultTextStyle(modifier._defaultTextStyle_0_0value);
                    break;
                }
                default: {
                    this.defaultTextStyle((undefined as TextPickerTextStyle | undefined));
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
                    this.onChange((undefined as OnTextPickerChangeCallback | undefined));
                }
            }
        }
        if (modifier._onScrollStop_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onScrollStop_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onScrollStop(modifier._onScrollStop_0_0value);
                    break;
                }
                default: {
                    this.onScrollStop((undefined as TextPickerScrollStopCallback | undefined));
                }
            }
        }
        if (modifier._onEnterSelectedArea_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onEnterSelectedArea_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onEnterSelectedArea(modifier._onEnterSelectedArea_0_0value);
                    break;
                }
                default: {
                    this.onEnterSelectedArea((undefined as TextPickerEnterSelectedAreaCallback | undefined));
                }
            }
        }
        if (modifier._selectedIndex_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._selectedIndex_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.selectedIndex(modifier._selectedIndex_0_0value);
                    break;
                }
                default: {
                    this.selectedIndex((undefined as int32 | Array<int32> | undefined));
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
                    this.divider((undefined as DividerOptions | null | undefined));
                }
            }
        }
        if (modifier._gradientHeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._gradientHeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.gradientHeight(modifier._gradientHeight_0_0value);
                    break;
                }
                default: {
                    this.gradientHeight((undefined as Dimension | undefined));
                }
            }
        }
        if (modifier._enableHapticFeedback_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableHapticFeedback_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableHapticFeedback(modifier._enableHapticFeedback_0_0value);
                    break;
                }
                default: {
                    this.enableHapticFeedback((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._digitalCrownSensitivity_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._digitalCrownSensitivity_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.digitalCrownSensitivity(modifier._digitalCrownSensitivity_0_0value);
                    break;
                }
                default: {
                    this.digitalCrownSensitivity((undefined as CrownSensitivity | undefined));
                }
            }
        }
    }
    defaultPickerItemHeight(value: double | string | undefined): this {
        if (((this._defaultPickerItemHeight_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._defaultPickerItemHeight_0_0value) !== (value)))
        {
            this._defaultPickerItemHeight_0_flag = AttributeUpdaterFlag.UPDATE
            this._defaultPickerItemHeight_0_0value = value
            this._state.fireChange()
        } else
        {
            this._defaultPickerItemHeight_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    canLoop(value: boolean | undefined): this {
        if (((this._canLoop_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._canLoop_0_0value) !== (value)))
        {
            this._canLoop_0_flag = AttributeUpdaterFlag.UPDATE
            this._canLoop_0_0value = value
            this._state.fireChange()
        } else
        {
            this._canLoop_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    disappearTextStyle(value: PickerTextStyle | undefined): this {
        if (((this._disappearTextStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._disappearTextStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._disappearTextStyle_0_0value = value
            this._state.fireChange()
        } else
        {
            this._disappearTextStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    textStyle(value: PickerTextStyle | undefined): this {
        if (((this._textStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._textStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._textStyle_0_0value = value
            this._state.fireChange()
        } else
        {
            this._textStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    selectedTextStyle(value: PickerTextStyle | undefined): this {
        if (((this._selectedTextStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._selectedTextStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._selectedTextStyle_0_0value = value
            this._state.fireChange()
        } else
        {
            this._selectedTextStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    disableTextStyleAnimation(value: boolean | undefined): this {
        if (((this._disableTextStyleAnimation_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._disableTextStyleAnimation_0_0value) !== (value)))
        {
            this._disableTextStyleAnimation_0_flag = AttributeUpdaterFlag.UPDATE
            this._disableTextStyleAnimation_0_0value = value
            this._state.fireChange()
        } else
        {
            this._disableTextStyleAnimation_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    defaultTextStyle(value: TextPickerTextStyle | undefined): this {
        if (((this._defaultTextStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._defaultTextStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._defaultTextStyle_0_0value = value
            this._state.fireChange()
        } else
        {
            this._defaultTextStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onChange(value: OnTextPickerChangeCallback | undefined): this {
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
    onScrollStop(value: TextPickerScrollStopCallback | undefined): this {
        if (((this._onScrollStop_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onScrollStop_0_flag = AttributeUpdaterFlag.UPDATE
            this._onScrollStop_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onScrollStop_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onEnterSelectedArea(value: TextPickerEnterSelectedAreaCallback | undefined): this {
        if (((this._onEnterSelectedArea_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onEnterSelectedArea_0_flag = AttributeUpdaterFlag.UPDATE
            this._onEnterSelectedArea_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onEnterSelectedArea_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    selectedIndex(value: int32 | Array<int32> | undefined): this {
        if (((this._selectedIndex_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._selectedIndex_0_0value) !== (value)))
        {
            this._selectedIndex_0_flag = AttributeUpdaterFlag.UPDATE
            this._selectedIndex_0_0value = value
            this._state.fireChange()
        } else
        {
            this._selectedIndex_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    divider(value: DividerOptions | null | undefined): this {
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
    gradientHeight(value: Dimension | undefined): this {
        if (((this._gradientHeight_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._gradientHeight_0_flag = AttributeUpdaterFlag.UPDATE
            this._gradientHeight_0_0value = value
            this._state.fireChange()
        } else
        {
            this._gradientHeight_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableHapticFeedback(value: boolean | undefined): this {
        if (((this._enableHapticFeedback_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableHapticFeedback_0_0value) !== (value)))
        {
            this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableHapticFeedback_0_0value = value
            this._state.fireChange()
        } else
        {
            this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        if (((this._digitalCrownSensitivity_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._digitalCrownSensitivity_0_flag = AttributeUpdaterFlag.UPDATE
            this._digitalCrownSensitivity_0_0value = value
            this._state.fireChange()
        } else
        {
            this._digitalCrownSensitivity_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<TextPickerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
