/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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
import { ArkUIPickerComponentPeer, OnUIPickerComponentCallback, PickerIndicatorStyle, UIPickerComponentAttribute } from "./component/uiPickerComponent"
import { int32 } from "@koalaui/common"
import { ModifierState } from "./CommonModifier"
import { CommonMethod } from "./component/common"
export class UIPickerComponentModifier extends CommonMethodModifier implements UIPickerComponentAttribute,AttributeModifier<UIPickerComponentAttribute> {
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
    applyNormalAttribute(instance: UIPickerComponentAttribute): void { }
    applyPressedAttribute(instance: UIPickerComponentAttribute): void { }
    applyFocusedAttribute(instance: UIPickerComponentAttribute): void { }
    applyDisabledAttribute(instance: UIPickerComponentAttribute): void { }
    applySelectedAttribute(instance: UIPickerComponentAttribute): void { }
    _onChange_0_0value?: OnUIPickerComponentCallback | undefined
    _onScrollStop_0_0value?: OnUIPickerComponentCallback | undefined
    _canLoop_0_0value?: boolean | undefined
    _enableHapticFeedback_0_0value?: boolean | undefined
    _selectionIndicator_0_0value?: PickerIndicatorStyle | undefined
    applyModifierPatch(node: PeerNode): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkUIPickerComponentPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkUIPickerComponentPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0)
        {
            switch (flagArray[0]) {
                case 1: {
                    peer.setOnChangeAttribute((this._onChange_0_0value as OnUIPickerComponentCallback | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setOnChangeAttribute((undefined as OnUIPickerComponentCallback | undefined));
                }
            }
        }
        if (flagArray[1] != 0)
        {
            switch (flagArray[1]) {
                case 1: {
                    peer.setOnScrollStopAttribute((this._onScrollStop_0_0value as OnUIPickerComponentCallback | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setOnScrollStopAttribute((undefined as OnUIPickerComponentCallback | undefined));
                }
            }
        }
        if (flagArray[2] != 0)
        {
            switch (flagArray[2]) {
                case 1: {
                    peer.setCanLoopAttribute((this._canLoop_0_0value as boolean | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setCanLoopAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[3] != 0)
        {
            switch (flagArray[3]) {
                case 1: {
                    peer.setEnableHapticFeedbackAttribute((this._enableHapticFeedback_0_0value as boolean | undefined));
                    flagArray[3] = 2;
                    break;
                }
                case 3: {
                    flagArray[3] = 2;
                    break;
                }
                default: {
                    flagArray[3] = 0;
                    peer.setEnableHapticFeedbackAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[4] != 0)
        {
            switch (flagArray[4]) {
                case 1: {
                    peer.setSelectionIndicatorAttribute((this._selectionIndicator_0_0value as PickerIndicatorStyle | undefined));
                    flagArray[4] = 2;
                    break;
                }
                case 3: {
                    flagArray[4] = 2;
                    break;
                }
                default: {
                    flagArray[4] = 0;
                    peer.setSelectionIndicatorAttribute((undefined as PickerIndicatorStyle | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: UIPickerComponentModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
    }
    mergeModifier0(modifier: UIPickerComponentModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0)
        {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.onChange(modifier._onChange_0_0value);
                    break;
                }
                default: {
                    this.onChange((undefined as OnUIPickerComponentCallback | undefined));
                }
            }
        }
        if (flagArray[1] != 0)
        {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.onScrollStop(modifier._onScrollStop_0_0value);
                    break;
                }
                default: {
                    this.onScrollStop((undefined as OnUIPickerComponentCallback | undefined));
                }
            }
        }
        if (flagArray[2] != 0)
        {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.canLoop(modifier._canLoop_0_0value);
                    break;
                }
                default: {
                    this.canLoop((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[3] != 0)
        {
            switch (flagArray[3]) {
                case 1:
                case 3: {
                    this.enableHapticFeedback(modifier._enableHapticFeedback_0_0value);
                    break;
                }
                default: {
                    this.enableHapticFeedback((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[4] != 0)
        {
            switch (flagArray[4]) {
                case 1:
                case 3: {
                    this.selectionIndicator(modifier._selectionIndicator_0_0value);
                    break;
                }
                default: {
                    this.selectionIndicator((undefined as PickerIndicatorStyle | undefined));
                }
            }
        }
    }
    onChange(value: OnUIPickerComponentCallback | undefined): this {
        if (((this._flagArray[0]) == (0)) || (true))
        {
            this._flagArray[0] = 1
            this._onChange_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[0] = 3
        }
        return this
    }
    onScrollStop(value: OnUIPickerComponentCallback | undefined): this {
        if (((this._flagArray[1]) == (0)) || (true))
        {
            this._flagArray[1] = 1
            this._onScrollStop_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[1] = 3
        }
        return this
    }
    canLoop(value: boolean | undefined): this {
        if (((this._flagArray[2]) == (0)) || ((this._canLoop_0_0value) !== (value)))
        {
            this._flagArray[2] = 1
            this._canLoop_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[2] = 3
        }
        return this
    }
    enableHapticFeedback(value: boolean | undefined): this {
        if (((this._flagArray[3]) == (0)) || ((this._enableHapticFeedback_0_0value) !== (value)))
        {
            this._flagArray[3] = 1
            this._enableHapticFeedback_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[3] = 3
        }
        return this
    }
    selectionIndicator(value: PickerIndicatorStyle | undefined): this {
        if (((this._flagArray[4]) == (0)) || (true))
        {
            this._flagArray[4] = 1
            this._selectionIndicator_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[4] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<UIPickerComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}