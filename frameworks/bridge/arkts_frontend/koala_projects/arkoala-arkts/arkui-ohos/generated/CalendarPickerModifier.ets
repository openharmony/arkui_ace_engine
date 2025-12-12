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
import { ArkCalendarPickerPeer, CalendarPickerAttribute, CalendarAlign } from "./component/calendarPicker"
import { int32 } from "@koalaui/common"
import { CommonMethod, PickerTextStyle } from "./component/common"
import { Offset } from "./component/units"
export class CalendarPickerModifier extends CommonMethodModifier implements CalendarPickerAttribute,AttributeModifier<CalendarPickerAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState	
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: CalendarPickerAttribute): void { }
    applyPressedAttribute(instance: CalendarPickerAttribute): void { }
    applyFocusedAttribute(instance: CalendarPickerAttribute): void { }
    applyDisabledAttribute(instance: CalendarPickerAttribute): void { }
    applySelectedAttribute(instance: CalendarPickerAttribute): void { }
    _textStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _textStyle_0_0value?: PickerTextStyle | undefined
    _onChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onChange_0_0value?: ((value0: Date) => void) | undefined
    _markToday_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _markToday_0_0value?: boolean | undefined
    _edgeAlign_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _edgeAlign_0_0value?: CalendarAlign | undefined
    _edgeAlign_0_1value?: Offset | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkCalendarPickerPeer;
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
        if (this._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnChangeAttribute((this._onChange_0_0value as ((value0: Date) => void) | undefined));
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnChangeAttribute((undefined as ((value0: Date) => void) | undefined));
                }
            }
        }
        if (this._markToday_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._markToday_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMarkTodayAttribute((this._markToday_0_0value as boolean | undefined));
                    this._markToday_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._markToday_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._markToday_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMarkTodayAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._edgeAlign_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._edgeAlign_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEdgeAlignAttribute((this._edgeAlign_0_0value as CalendarAlign | undefined), (this._edgeAlign_0_1value as Offset | undefined | undefined));
                    this._edgeAlign_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._edgeAlign_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._edgeAlign_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEdgeAlignAttribute((undefined as CalendarAlign | undefined), (undefined as Offset | undefined | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: CalendarPickerModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
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
        if (modifier._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onChange(modifier._onChange_0_0value);
                    break;
                }
                default: {
                    this.onChange((undefined as ((value0: Date) => void) | undefined));
                }
            }
        }
        if (modifier._markToday_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._markToday_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.markToday(modifier._markToday_0_0value);
                    break;
                }
                default: {
                    this.markToday((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._edgeAlign_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._edgeAlign_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.edgeAlign(modifier._edgeAlign_0_0value, modifier._edgeAlign_0_1value);
                    break;
                }
                default: {
                    this.edgeAlign((undefined as CalendarAlign | undefined), (undefined as Offset | undefined | undefined));
                }
            }
        }
    }
    textStyle(value: PickerTextStyle | undefined): this {
        if (((this._textStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._textStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._textStyle_0_0value = value
        } else
        {
            this._textStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onChange(value: ((value0: Date) => void) | undefined): this {
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
    markToday(value: boolean | undefined): this {
        if (((this._markToday_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._markToday_0_0value) !== (value)))
        {
            this._markToday_0_flag = AttributeUpdaterFlag.UPDATE
            this._markToday_0_0value = value
        } else
        {
            this._markToday_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    edgeAlign(alignType: CalendarAlign | undefined, offset?: Offset): this {
        if (((this._edgeAlign_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._edgeAlign_0_flag = AttributeUpdaterFlag.UPDATE
            this._edgeAlign_0_0value = alignType
            this._edgeAlign_0_1value = offset
        } else
        {
            this._edgeAlign_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<CalendarPickerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
