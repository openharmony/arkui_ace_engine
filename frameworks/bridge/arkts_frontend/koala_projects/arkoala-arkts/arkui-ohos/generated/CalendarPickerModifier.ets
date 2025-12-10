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

import { CommonMethodModifier } from './CommonMethodModifier'
import { AttributeModifier } from '#handwritten'
import { AttributeUpdaterFlag } from './AttributeUpdaterFlag'
import { PeerNode } from './PeerNode'
import { ArkCalendarPickerPeer, CalendarPickerAttribute, CalendarAlign } from './component/calendarPicker'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod, PickerTextStyle, Callback as arkui_component_common_Callback } from './component/common'
import { Offset } from './component/units'
export class CalendarPickerModifier extends CommonMethodModifier implements CalendarPickerAttribute,AttributeModifier<CalendarPickerAttribute> {
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
    applyNormalAttribute(instance: CalendarPickerAttribute): void { }
    applyPressedAttribute(instance: CalendarPickerAttribute): void { }
    applyFocusedAttribute(instance: CalendarPickerAttribute): void { }
    applyDisabledAttribute(instance: CalendarPickerAttribute): void { }
    applySelectedAttribute(instance: CalendarPickerAttribute): void { }
    public _textStyle_0_0value?: PickerTextStyle | undefined
    public _onChange_0_0value?: arkui_component_common_Callback<Date, void> | undefined
    public _markToday_0_0value?: boolean | undefined
    public _edgeAlign_0_0value?: CalendarAlign | undefined
    public _edgeAlign_0_1value?: Offset | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkCalendarPickerPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkCalendarPickerPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setTextStyleAttribute((this._textStyle_0_0value as PickerTextStyle | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setTextStyleAttribute((undefined as PickerTextStyle | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setOnChangeAttribute((this._onChange_0_0value as arkui_component_common_Callback<Date, void> | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setOnChangeAttribute((undefined as arkui_component_common_Callback<Date, void> | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setMarkTodayAttribute((this._markToday_0_0value as boolean | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setMarkTodayAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1: {
                    peer.setEdgeAlignAttribute((this._edgeAlign_0_0value as CalendarAlign | undefined), (this._edgeAlign_0_1value as Offset | undefined));
                    flagArray[3] = 2;
                    break;
                }
                case 3: {
                    flagArray[3] = 2;
                    break;
                }
                default: {
                    flagArray[3] = 0;
                    peer.setEdgeAlignAttribute((undefined as CalendarAlign | undefined), (undefined as Offset | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: CalendarPickerModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
    }
    mergeModifier0(modifier: CalendarPickerModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.textStyle(modifier._textStyle_0_0value);
                    break;
                }
                default: {
                    this.textStyle((undefined as PickerTextStyle | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.onChange(modifier._onChange_0_0value);
                    break;
                }
                default: {
                    this.onChange((undefined as arkui_component_common_Callback<Date, void> | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.markToday(modifier._markToday_0_0value);
                    break;
                }
                default: {
                    this.markToday((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1:
                case 3: {
                    this.edgeAlign(modifier._edgeAlign_0_0value, modifier._edgeAlign_0_1value);
                    break;
                }
                default: {
                    this.edgeAlign((undefined as CalendarAlign | undefined), (undefined as Offset | undefined));
                }
            }
        }
    }
    textStyle(value: PickerTextStyle | undefined): this {
        if (((this._flagArray[0]) == (0)) || (true)) {
            this._flagArray[0] = 1
            this._textStyle_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    onChange(value: arkui_component_common_Callback<Date, void> | undefined): this {
        if (((this._flagArray[1]) == (0)) || (true)) {
            this._flagArray[1] = 1
            this._onChange_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    markToday(value: boolean | undefined): this {
        if (((this._flagArray[2]) == (0)) || ((this._markToday_0_0value) !== (value))) {
            this._flagArray[2] = 1
            this._markToday_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[2] = 3
        }
        return this
    }
    edgeAlign(alignType: CalendarAlign | undefined, offset?: Offset): this {
        if (((this._flagArray[3]) == (0)) || (true) || (true)) {
            this._flagArray[3] = 1
            this._edgeAlign_0_0value = alignType
            this._edgeAlign_0_1value = offset
            this._state.fireChange()
        } else {
            this._flagArray[3] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<CalendarPickerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}
