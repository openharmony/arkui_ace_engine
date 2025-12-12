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
import { ArkPickerPeer, OnPickerCallback, PickerIndicatorStyle, PickerAttribute } from "./component/picker"
import { int32 } from "@koalaui/common"
import { CommonMethod } from "./component/common"
export class PickerModifier extends CommonMethodModifier implements PickerAttribute,AttributeModifier<PickerAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: PickerAttribute): void { }
    applyPressedAttribute(instance: PickerAttribute): void { }
    applyFocusedAttribute(instance: PickerAttribute): void { }
    applyDisabledAttribute(instance: PickerAttribute): void { }
    applySelectedAttribute(instance: PickerAttribute): void { }
    _onChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onChange_0_0value?: OnPickerCallback | undefined
    _onScrollStop_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onScrollStop_0_0value?: OnPickerCallback | undefined
    _canLoop_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _canLoop_0_0value?: boolean | undefined
    _enableHapticFeedback_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableHapticFeedback_0_0value?: boolean | undefined
    _selectionIndicator_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selectionIndicator_0_0value?: PickerIndicatorStyle | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkPickerPeer;
        if (this._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnChangeAttribute((this._onChange_0_0value as OnPickerCallback | undefined));
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnChangeAttribute((undefined as OnPickerCallback | undefined));
                }
            }
        }
        if (this._onScrollStop_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onScrollStop_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnScrollStopAttribute((this._onScrollStop_0_0value as OnPickerCallback | undefined));
                    this._onScrollStop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onScrollStop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onScrollStop_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnScrollStopAttribute((undefined as OnPickerCallback | undefined));
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
        if (this._selectionIndicator_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._selectionIndicator_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSelectionIndicatorAttribute((this._selectionIndicator_0_0value as PickerIndicatorStyle | undefined));
                    this._selectionIndicator_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selectionIndicator_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selectionIndicator_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSelectionIndicatorAttribute((undefined as PickerIndicatorStyle | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: PickerModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        if (modifier._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onChange(modifier._onChange_0_0value);
                    break;
                }
                default: {
                    this.onChange((undefined as OnPickerCallback | undefined));
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
                    this.onScrollStop((undefined as OnPickerCallback | undefined));
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
        if (modifier._selectionIndicator_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._selectionIndicator_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.selectionIndicator(modifier._selectionIndicator_0_0value);
                    break;
                }
                default: {
                    this.selectionIndicator((undefined as PickerIndicatorStyle | undefined));
                }
            }
        }
    }
    onChange(value: OnPickerCallback | undefined): this {
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
    onScrollStop(value: OnPickerCallback | undefined): this {
        if (((this._onScrollStop_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onScrollStop_0_flag = AttributeUpdaterFlag.UPDATE
            this._onScrollStop_0_0value = value
        } else
        {
            this._onScrollStop_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    canLoop(value: boolean | undefined): this {
        if (((this._canLoop_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._canLoop_0_0value) !== (value)))
        {
            this._canLoop_0_flag = AttributeUpdaterFlag.UPDATE
            this._canLoop_0_0value = value
        } else
        {
            this._canLoop_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableHapticFeedback(value: boolean | undefined): this {
        if (((this._enableHapticFeedback_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableHapticFeedback_0_0value) !== (value)))
        {
            this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableHapticFeedback_0_0value = value
        } else
        {
            this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    selectionIndicator(value: PickerIndicatorStyle | undefined): this {
        if (((this._selectionIndicator_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._selectionIndicator_0_flag = AttributeUpdaterFlag.UPDATE
            this._selectionIndicator_0_0value = value
        } else
        {
            this._selectionIndicator_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<PickerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
