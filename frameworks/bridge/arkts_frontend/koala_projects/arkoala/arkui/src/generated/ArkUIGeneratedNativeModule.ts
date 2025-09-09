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

import { KInt, KLong, KBoolean, KFloat, KUInt, KStringPtr, KPointer, KNativePointer, KInt32ArrayPtr, KUint8ArrayPtr, KFloat32ArrayPtr, pointer, KInteropReturnBuffer, loadNativeModuleLibrary } from "@koalaui/interop"
import { int32,int64, float32 } from "@koalaui/common"
import { Length } from "./ArkUnitsInterfaces"

export class ArkUIGeneratedNativeModule {
    private static _isLoaded: boolean = false
    private static _LoadOnce(): boolean {
        if ((this._isLoaded) == (false))
        {
            this._isLoaded = true
            loadNativeModuleLibrary("ArkUIGeneratedNativeModule", ArkUIGeneratedNativeModule)
            return true
        }
        return false
    }
    static _Root_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Root_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _ComponentRoot_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ComponentRoot_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _AbilityComponent_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._AbilityComponent_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _AbilityComponentInterface_setAbilityComponentOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AbilityComponentInterface_setAbilityComponentOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _AbilityComponentAttribute_onConnect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AbilityComponentAttribute_onConnect(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _AbilityComponentAttribute_onDisconnect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AbilityComponentAttribute_onDisconnect(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _AlphabetIndexer_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._AlphabetIndexer_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _AlphabetIndexerInterface_setAlphabetIndexerOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AlphabetIndexerInterface_setAlphabetIndexerOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _AlphabetIndexerAttribute_onSelected(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AlphabetIndexerAttribute_onSelected(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _AlphabetIndexerAttribute_color(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AlphabetIndexerAttribute_color(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _AlphabetIndexerAttribute_selectedColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AlphabetIndexerAttribute_selectedColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _AlphabetIndexerAttribute_popupColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AlphabetIndexerAttribute_popupColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _AlphabetIndexerAttribute_selectedBackgroundColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AlphabetIndexerAttribute_selectedBackgroundColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _AlphabetIndexerAttribute_popupBackground(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AlphabetIndexerAttribute_popupBackground(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _AlphabetIndexerAttribute_popupSelectedColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AlphabetIndexerAttribute_popupSelectedColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _AlphabetIndexerAttribute_popupUnselectedColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AlphabetIndexerAttribute_popupUnselectedColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _AlphabetIndexerAttribute_popupItemBackgroundColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AlphabetIndexerAttribute_popupItemBackgroundColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _AlphabetIndexerAttribute_usingPopup(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AlphabetIndexerAttribute_usingPopup(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _AlphabetIndexerAttribute_selectedFont(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AlphabetIndexerAttribute_selectedFont(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _AlphabetIndexerAttribute_popupFont(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AlphabetIndexerAttribute_popupFont(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _AlphabetIndexerAttribute_popupItemFont(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AlphabetIndexerAttribute_popupItemFont(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _AlphabetIndexerAttribute_itemSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AlphabetIndexerAttribute_itemSize(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _AlphabetIndexerAttribute_font(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AlphabetIndexerAttribute_font(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _AlphabetIndexerAttribute_onSelect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AlphabetIndexerAttribute_onSelect(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _AlphabetIndexerAttribute_onRequestPopupData(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AlphabetIndexerAttribute_onRequestPopupData(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _AlphabetIndexerAttribute_onPopupSelect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AlphabetIndexerAttribute_onPopupSelect(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _AlphabetIndexerAttribute_selected(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AlphabetIndexerAttribute_selected(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _AlphabetIndexerAttribute_popupPosition(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AlphabetIndexerAttribute_popupPosition(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _AlphabetIndexerAttribute_autoCollapse(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AlphabetIndexerAttribute_autoCollapse(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _AlphabetIndexerAttribute_popupItemBorderRadius(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AlphabetIndexerAttribute_popupItemBorderRadius(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _AlphabetIndexerAttribute_itemBorderRadius(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AlphabetIndexerAttribute_itemBorderRadius(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _AlphabetIndexerAttribute_popupBackgroundBlurStyle(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AlphabetIndexerAttribute_popupBackgroundBlurStyle(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _AlphabetIndexerAttribute_popupTitleBackground(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AlphabetIndexerAttribute_popupTitleBackground(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _AlphabetIndexerAttribute_enableHapticFeedback(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AlphabetIndexerAttribute_enableHapticFeedback(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _AlphabetIndexerAttribute_alignStyle(ptr: KPointer, value: KInt, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AlphabetIndexerAttribute_alignStyle(ptr, value, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _AlphabetIndexerAttribute__onChangeEvent_selected(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AlphabetIndexerAttribute__onChangeEvent_selected(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Animator_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Animator_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _AnimatorInterface_setAnimatorOptions(ptr: KPointer, value: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AnimatorInterface_setAnimatorOptions(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _AnimatorAttribute_state(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AnimatorAttribute_state(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _AnimatorAttribute_duration(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AnimatorAttribute_duration(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _AnimatorAttribute_curve(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AnimatorAttribute_curve(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _AnimatorAttribute_delay(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AnimatorAttribute_delay(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _AnimatorAttribute_fillMode(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AnimatorAttribute_fillMode(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _AnimatorAttribute_iterations(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AnimatorAttribute_iterations(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _AnimatorAttribute_playMode(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AnimatorAttribute_playMode(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _AnimatorAttribute_motion(ptr: KPointer, value: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AnimatorAttribute_motion(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _AnimatorAttribute_onStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AnimatorAttribute_onStart(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _AnimatorAttribute_onPause(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AnimatorAttribute_onPause(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _AnimatorAttribute_onRepeat(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AnimatorAttribute_onRepeat(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _AnimatorAttribute_onCancel(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AnimatorAttribute_onCancel(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _AnimatorAttribute_onFinish(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AnimatorAttribute_onFinish(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _AnimatorAttribute_onFrame(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AnimatorAttribute_onFrame(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Badge_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Badge_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _BadgeInterface_setBadgeOptions0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._BadgeInterface_setBadgeOptions0(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _BadgeInterface_setBadgeOptions1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._BadgeInterface_setBadgeOptions1(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Blank_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Blank_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _BlankInterface_setBlankOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._BlankInterface_setBlankOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _BlankAttribute_color(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._BlankAttribute_color(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Button_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Button_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _ButtonInterface_setButtonOptions0(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ButtonInterface_setButtonOptions0(ptr)
        }
        throw new Error("Not implemented")
    }
    static _ButtonInterface_setButtonOptions1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ButtonInterface_setButtonOptions1(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ButtonInterface_setButtonOptions2(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ButtonInterface_setButtonOptions2(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ButtonAttribute_type(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ButtonAttribute_type(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ButtonAttribute_stateEffect(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ButtonAttribute_stateEffect(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ButtonAttribute_buttonStyle(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ButtonAttribute_buttonStyle(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ButtonAttribute_controlSize(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ButtonAttribute_controlSize(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ButtonAttribute_role(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ButtonAttribute_role(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ButtonAttribute_fontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ButtonAttribute_fontColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ButtonAttribute_fontSize(ptr: KPointer, value: Length): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ButtonAttribute_fontSize(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ButtonAttribute_fontWeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ButtonAttribute_fontWeight(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ButtonAttribute_fontStyle(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ButtonAttribute_fontStyle(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ButtonAttribute_fontFamily(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ButtonAttribute_fontFamily(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ButtonAttribute_contentModifier(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ButtonAttribute_contentModifier(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ButtonAttribute_labelStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ButtonAttribute_labelStyle(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Calendar_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Calendar_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _CalendarInterface_setCalendarOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CalendarInterface_setCalendarOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CalendarAttribute_showLunar(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CalendarAttribute_showLunar(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CalendarAttribute_showHoliday(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CalendarAttribute_showHoliday(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CalendarAttribute_needSlide(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CalendarAttribute_needSlide(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CalendarAttribute_startOfWeek(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CalendarAttribute_startOfWeek(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CalendarAttribute_offDays(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CalendarAttribute_offDays(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CalendarAttribute_direction(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CalendarAttribute_direction(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CalendarAttribute_currentDayStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CalendarAttribute_currentDayStyle(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CalendarAttribute_nonCurrentDayStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CalendarAttribute_nonCurrentDayStyle(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CalendarAttribute_todayStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CalendarAttribute_todayStyle(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CalendarAttribute_weekStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CalendarAttribute_weekStyle(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CalendarAttribute_workStateStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CalendarAttribute_workStateStyle(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CalendarAttribute_onSelectChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CalendarAttribute_onSelectChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CalendarAttribute_onRequestData(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CalendarAttribute_onRequestData(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CalendarPicker_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CalendarPicker_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _CalendarPickerInterface_setCalendarPickerOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CalendarPickerInterface_setCalendarPickerOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CalendarPickerAttribute_textStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CalendarPickerAttribute_textStyle(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CalendarPickerAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CalendarPickerAttribute_onChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CalendarPickerAttribute_edgeAlign(ptr: KPointer, alignType: KInt, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CalendarPickerAttribute_edgeAlign(ptr, alignType, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Canvas_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Canvas_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _CanvasInterface_setCanvasOptions0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasInterface_setCanvasOptions0(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CanvasInterface_setCanvasOptions1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasInterface_setCanvasOptions1(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CanvasAttribute_onReady(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasAttribute_onReady(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CanvasAttribute_enableAnalyzer(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasAttribute_enableAnalyzer(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _Checkbox_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Checkbox_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _CheckboxInterface_setCheckboxOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CheckboxInterface_setCheckboxOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CheckboxAttribute_select(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CheckboxAttribute_select(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CheckboxAttribute_selectedColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CheckboxAttribute_selectedColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CheckboxAttribute_shape(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CheckboxAttribute_shape(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CheckboxAttribute_unselectedColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CheckboxAttribute_unselectedColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CheckboxAttribute_mark(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CheckboxAttribute_mark(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CheckboxAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CheckboxAttribute_onChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CheckboxAttribute_contentModifier(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CheckboxAttribute_contentModifier(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CheckboxAttribute__onChangeEvent_select(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CheckboxAttribute__onChangeEvent_select(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CheckboxGroup_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CheckboxGroup_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _CheckboxGroupInterface_setCheckboxGroupOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CheckboxGroupInterface_setCheckboxGroupOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CheckboxGroupAttribute_selectAll(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CheckboxGroupAttribute_selectAll(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CheckboxGroupAttribute_selectedColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CheckboxGroupAttribute_selectedColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CheckboxGroupAttribute_unselectedColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CheckboxGroupAttribute_unselectedColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CheckboxGroupAttribute_mark(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CheckboxGroupAttribute_mark(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CheckboxGroupAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CheckboxGroupAttribute_onChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CheckboxGroupAttribute_checkboxShape(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CheckboxGroupAttribute_checkboxShape(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CheckboxGroupAttribute__onChangeEvent_selectAll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CheckboxGroupAttribute__onChangeEvent_selectAll(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Circle_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Circle_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _CircleInterface_setCircleOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CircleInterface_setCircleOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Column_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Column_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _ColumnInterface_setColumnOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ColumnInterface_setColumnOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ColumnAttribute_alignItems(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ColumnAttribute_alignItems(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ColumnAttribute_justifyContent(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ColumnAttribute_justifyContent(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ColumnAttribute_pointLight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ColumnAttribute_pointLight(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ColumnAttribute_reverse(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ColumnAttribute_reverse(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ColumnSplit_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ColumnSplit_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _ColumnSplitInterface_setColumnSplitOptions(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ColumnSplitInterface_setColumnSplitOptions(ptr)
        }
        throw new Error("Not implemented")
    }
    static _ColumnSplitAttribute_resizeable(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ColumnSplitAttribute_resizeable(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ColumnSplitAttribute_divider(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ColumnSplitAttribute_divider(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_width(ptr: KPointer, value: Length): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_width(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_height(ptr: KPointer, value: Length): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_height(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_drawModifier(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_drawModifier(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_responseRegion(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_responseRegion(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_mouseResponseRegion(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_mouseResponseRegion(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_size(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_size(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_constraintSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_constraintSize(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_touchable(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_touchable(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_hitTestBehavior(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_hitTestBehavior(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_onChildTouchTest(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_onChildTouchTest(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_layoutWeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_layoutWeight(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_chainWeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_chainWeight(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_padding(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_padding(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_safeAreaPadding(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_safeAreaPadding(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_margin(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_margin(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_backgroundColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_backgroundColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_pixelRound(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_pixelRound(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_backgroundImageSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_backgroundImageSize(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_backgroundImagePosition(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_backgroundImagePosition(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_backgroundEffect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_backgroundEffect(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_backgroundImageResizable(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_backgroundImageResizable(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_foregroundEffect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_foregroundEffect(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_visualEffect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_visualEffect(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_backgroundFilter(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_backgroundFilter(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_foregroundFilter(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_foregroundFilter(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_compositingFilter(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_compositingFilter(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_opacity(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_opacity(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_border(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_border(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_borderStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_borderStyle(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_borderWidth(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_borderWidth(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_borderColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_borderColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_borderRadius(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_borderRadius(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_borderImage(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_borderImage(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_outline(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_outline(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_outlineStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_outlineStyle(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_outlineWidth(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_outlineWidth(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_outlineColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_outlineColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_outlineRadius(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_outlineRadius(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_foregroundColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_foregroundColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_onClick0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_onClick0(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_onClick1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32, distanceThreshold: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_onClick1(ptr, thisArray, thisLength, distanceThreshold)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_onHover(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_onHover(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_onAccessibilityHover(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_onAccessibilityHover(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_hoverEffect(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_hoverEffect(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_onMouse(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_onMouse(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_onTouch(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_onTouch(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_onKeyEvent(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_onKeyEvent(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_onKeyPreIme(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_onKeyPreIme(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_focusable(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_focusable(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_onFocus(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_onFocus(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_onBlur(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_onBlur(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_tabIndex(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_tabIndex(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_defaultFocus(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_defaultFocus(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_groupDefaultFocus(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_groupDefaultFocus(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_focusOnTouch(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_focusOnTouch(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_focusBox(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_focusBox(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_animation(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_animation(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_transition0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_transition0(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_transition1(ptr: KPointer, effect: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_transition1(ptr, effect, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_motionBlur(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_motionBlur(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_brightness(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_brightness(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_contrast(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_contrast(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_grayscale(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_grayscale(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_colorBlend(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_colorBlend(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_saturate(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_saturate(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_sepia(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_sepia(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_invert(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_invert(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_hueRotate(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_hueRotate(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_useShadowBatching(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_useShadowBatching(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_useEffect0(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_useEffect0(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_useEffect1(ptr: KPointer, useEffect: KInt, effectType: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_useEffect1(ptr, useEffect, effectType)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_renderGroup(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_renderGroup(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_freeze(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_freeze(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_translate(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_translate(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_scale(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_scale(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_gridSpan(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_gridSpan(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_gridOffset(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_gridOffset(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_rotate(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_rotate(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_transform(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_transform(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_onAppear(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_onAppear(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_onDisAppear(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_onDisAppear(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_onAttach(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_onAttach(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_onDetach(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_onDetach(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_onAreaChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_onAreaChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_visibility(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_visibility(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_flexGrow(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_flexGrow(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_flexShrink(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_flexShrink(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_flexBasis(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_flexBasis(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_alignSelf(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_alignSelf(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_displayPriority(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_displayPriority(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_zIndex(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_zIndex(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_direction(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_direction(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_align(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_align(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_position(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_position(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_markAnchor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_markAnchor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_offset(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_offset(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_enabled(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_enabled(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_useSizeType(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_useSizeType(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_alignRules0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_alignRules0(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_alignRules1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_alignRules1(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_aspectRatio(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_aspectRatio(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_clickEffect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_clickEffect(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_onDragStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_onDragStart(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_onDragEnter(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_onDragEnter(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_onDragMove(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_onDragMove(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_onDragLeave(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_onDragLeave(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_onDrop(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_onDrop(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_onDragEnd(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_onDragEnd(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_allowDrop(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_allowDrop(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_draggable(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_draggable(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_dragPreview(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_dragPreview(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_onPreDrag(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_onPreDrag(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_linearGradient(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_linearGradient(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_sweepGradient(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_sweepGradient(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_radialGradient(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_radialGradient(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_motionPath(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_motionPath(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_shadow(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_shadow(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_clip0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_clip0(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_clip1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_clip1(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_clipShape(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_clipShape(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_mask0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_mask0(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_mask1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_mask1(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_maskShape(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_maskShape(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_key(ptr: KPointer, value: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_key(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_id(ptr: KPointer, value: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_id(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_geometryTransition0(ptr: KPointer, value: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_geometryTransition0(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_geometryTransition1(ptr: KPointer, id: KStringPtr, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_geometryTransition1(ptr, id, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_stateStyles(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_stateStyles(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_restoreId(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_restoreId(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_sphericalEffect(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_sphericalEffect(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_lightUpEffect(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_lightUpEffect(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_pixelStretchEffect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_pixelStretchEffect(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_accessibilityGroup0(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_accessibilityGroup0(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_accessibilityGroup1(ptr: KPointer, isGroup: KInt, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_accessibilityGroup1(ptr, isGroup, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_accessibilityText0(ptr: KPointer, value: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_accessibilityText0(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_accessibilityText1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_accessibilityText1(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_accessibilityTextHint(ptr: KPointer, value: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_accessibilityTextHint(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_accessibilityDescription0(ptr: KPointer, value: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_accessibilityDescription0(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_accessibilityDescription1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_accessibilityDescription1(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_accessibilityLevel(ptr: KPointer, value: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_accessibilityLevel(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_accessibilityVirtualNode(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_accessibilityVirtualNode(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_accessibilityChecked(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_accessibilityChecked(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_accessibilitySelected(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_accessibilitySelected(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_obscured(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_obscured(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_reuseId(ptr: KPointer, value: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_reuseId(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_renderFit(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_renderFit(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_gestureModifier(ptr: KPointer, value: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_gestureModifier(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_backgroundBrightness(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_backgroundBrightness(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_onGestureJudgeBegin(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_onGestureJudgeBegin(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_onGestureRecognizerJudgeBegin0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_onGestureRecognizerJudgeBegin0(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_onGestureRecognizerJudgeBegin1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32, exposeInnerGesture: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_onGestureRecognizerJudgeBegin1(ptr, thisArray, thisLength, exposeInnerGesture)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_shouldBuiltInRecognizerParallelWith(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_shouldBuiltInRecognizerParallelWith(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_monopolizeEvents(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_monopolizeEvents(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_onTouchIntercept(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_onTouchIntercept(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_onSizeChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_onSizeChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_customProperty(ptr: KPointer, name: KStringPtr, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_customProperty(ptr, name, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_expandSafeArea(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_expandSafeArea(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_background(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_background(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_backgroundImage(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_backgroundImage(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_backgroundBlurStyle(ptr: KPointer, value: KInt, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_backgroundBlurStyle(ptr, value, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_foregroundBlurStyle(ptr: KPointer, value: KInt, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_foregroundBlurStyle(ptr, value, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_focusScopeId0(ptr: KPointer, id: KStringPtr, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_focusScopeId0(ptr, id, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_focusScopeId1(ptr: KPointer, id: KStringPtr, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_focusScopeId1(ptr, id, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_focusScopePriority(ptr: KPointer, scopeId: KStringPtr, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_focusScopePriority(ptr, scopeId, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_gesture(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_gesture(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_priorityGesture(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_priorityGesture(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_parallelGesture(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_parallelGesture(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_blur(ptr: KPointer, value: number, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_blur(ptr, value, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_linearGradientBlur(ptr: KPointer, value: number, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_linearGradientBlur(ptr, value, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_systemBarEffect(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_systemBarEffect(ptr)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_backdropBlur(ptr: KPointer, value: number, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_backdropBlur(ptr, value, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_sharedTransition(ptr: KPointer, id: KStringPtr, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_sharedTransition(ptr, id, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_chainMode(ptr: KPointer, direction: KInt, style: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_chainMode(ptr, direction, style)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_dragPreviewOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_dragPreviewOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_overlay(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_overlay(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_blendMode(ptr: KPointer, value: KInt, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_blendMode(ptr, value, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_advancedBlendMode(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_advancedBlendMode(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_bindPopup(ptr: KPointer, show: KInt, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_bindPopup(ptr, show, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_bindMenu0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_bindMenu0(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_bindMenu1(ptr: KPointer, isShow: KInt, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_bindMenu1(ptr, isShow, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_bindContextMenu0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32, responseType: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_bindContextMenu0(ptr, thisArray, thisLength, responseType)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_bindContextMenu1(ptr: KPointer, isShown: KInt, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_bindContextMenu1(ptr, isShown, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_bindContentCover0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_bindContentCover0(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_bindContentCover1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_bindContentCover1(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_bindSheet(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_bindSheet(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_onVisibleAreaChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_onVisibleAreaChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonMethod_keyboardShortcut(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonMethod_keyboardShortcut(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonShapeMethod_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonShapeMethod_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _CommonShapeMethod_stroke(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonShapeMethod_stroke(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonShapeMethod_fill(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonShapeMethod_fill(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonShapeMethod_strokeDashOffset(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonShapeMethod_strokeDashOffset(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonShapeMethod_strokeLineCap(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonShapeMethod_strokeLineCap(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonShapeMethod_strokeLineJoin(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonShapeMethod_strokeLineJoin(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonShapeMethod_strokeMiterLimit(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonShapeMethod_strokeMiterLimit(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonShapeMethod_strokeOpacity(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonShapeMethod_strokeOpacity(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonShapeMethod_fillOpacity(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonShapeMethod_fillOpacity(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonShapeMethod_strokeWidth(ptr: KPointer, value: Length): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonShapeMethod_strokeWidth(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonShapeMethod_antiAlias(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonShapeMethod_antiAlias(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CommonShapeMethod_strokeDashArray(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonShapeMethod_strokeDashArray(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Common_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Common_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _CommonInterface_setCommonOptions(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonInterface_setCommonOptions(ptr)
        }
        throw new Error("Not implemented")
    }
    static _ScrollableCommonMethod_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScrollableCommonMethod_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _ScrollableCommonMethod_scrollBar(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScrollableCommonMethod_scrollBar(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ScrollableCommonMethod_scrollBarColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScrollableCommonMethod_scrollBarColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ScrollableCommonMethod_scrollBarWidth(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScrollableCommonMethod_scrollBarWidth(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ScrollableCommonMethod_nestedScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScrollableCommonMethod_nestedScroll(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ScrollableCommonMethod_enableScrollInteraction(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScrollableCommonMethod_enableScrollInteraction(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ScrollableCommonMethod_friction(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScrollableCommonMethod_friction(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ScrollableCommonMethod_onScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScrollableCommonMethod_onScroll(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ScrollableCommonMethod_onWillScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScrollableCommonMethod_onWillScroll(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ScrollableCommonMethod_onDidScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScrollableCommonMethod_onDidScroll(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ScrollableCommonMethod_onReachStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScrollableCommonMethod_onReachStart(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ScrollableCommonMethod_onReachEnd(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScrollableCommonMethod_onReachEnd(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ScrollableCommonMethod_onScrollStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScrollableCommonMethod_onScrollStart(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ScrollableCommonMethod_onScrollStop(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScrollableCommonMethod_onScrollStop(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ScrollableCommonMethod_flingSpeedLimit(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScrollableCommonMethod_flingSpeedLimit(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ScrollableCommonMethod_clipContent(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScrollableCommonMethod_clipContent(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ScrollableCommonMethod_edgeEffect(ptr: KPointer, edgeEffect: KInt, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScrollableCommonMethod_edgeEffect(ptr, edgeEffect, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ScrollableCommonMethod_fadingEdge(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScrollableCommonMethod_fadingEdge(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Component3D_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Component3D_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _Component3DInterface_setComponent3DOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._Component3DInterface_setComponent3DOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Component3DAttribute_environment(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._Component3DAttribute_environment(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Component3DAttribute_shader(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._Component3DAttribute_shader(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Component3DAttribute_shaderImageTexture(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._Component3DAttribute_shaderImageTexture(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Component3DAttribute_shaderInputBuffer(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._Component3DAttribute_shaderInputBuffer(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Component3DAttribute_renderWidth(ptr: KPointer, value: Length): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._Component3DAttribute_renderWidth(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _Component3DAttribute_renderHeight(ptr: KPointer, value: Length): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._Component3DAttribute_renderHeight(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _Component3DAttribute_customRender(ptr: KPointer, thisArray: Uint8Array, thisLength: int32, selfRenderUpdate: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._Component3DAttribute_customRender(ptr, thisArray, thisLength, selfRenderUpdate)
        }
        throw new Error("Not implemented")
    }
    static _ContainerSpan_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ContainerSpan_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _ContainerSpanInterface_setContainerSpanOptions(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ContainerSpanInterface_setContainerSpanOptions(ptr)
        }
        throw new Error("Not implemented")
    }
    static _ContainerSpanAttribute_textBackgroundStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ContainerSpanAttribute_textBackgroundStyle(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Counter_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Counter_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _CounterInterface_setCounterOptions(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CounterInterface_setCounterOptions(ptr)
        }
        throw new Error("Not implemented")
    }
    static _CounterAttribute_onInc(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CounterAttribute_onInc(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CounterAttribute_onDec(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CounterAttribute_onDec(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CounterAttribute_enableDec(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CounterAttribute_enableDec(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _CounterAttribute_enableInc(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CounterAttribute_enableInc(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _DataPanel_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._DataPanel_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _DataPanelInterface_setDataPanelOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._DataPanelInterface_setDataPanelOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _DataPanelAttribute_closeEffect(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._DataPanelAttribute_closeEffect(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _DataPanelAttribute_valueColors(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._DataPanelAttribute_valueColors(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _DataPanelAttribute_trackBackgroundColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._DataPanelAttribute_trackBackgroundColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _DataPanelAttribute_strokeWidth(ptr: KPointer, value: Length): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._DataPanelAttribute_strokeWidth(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _DataPanelAttribute_trackShadow(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._DataPanelAttribute_trackShadow(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _DataPanelAttribute_contentModifier(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._DataPanelAttribute_contentModifier(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _DatePicker_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._DatePicker_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _DatePickerInterface_setDatePickerOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._DatePickerInterface_setDatePickerOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _DatePickerAttribute_lunar(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._DatePickerAttribute_lunar(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _DatePickerAttribute_disappearTextStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._DatePickerAttribute_disappearTextStyle(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _DatePickerAttribute_textStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._DatePickerAttribute_textStyle(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _DatePickerAttribute_selectedTextStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._DatePickerAttribute_selectedTextStyle(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _DatePickerAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._DatePickerAttribute_onChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _DatePickerAttribute_onDateChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._DatePickerAttribute_onDateChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _DatePickerAttribute__onChangeEvent_selected(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._DatePickerAttribute__onChangeEvent_selected(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Divider_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Divider_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _DividerInterface_setDividerOptions(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._DividerInterface_setDividerOptions(ptr)
        }
        throw new Error("Not implemented")
    }
    static _DividerAttribute_vertical(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._DividerAttribute_vertical(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _DividerAttribute_color(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._DividerAttribute_color(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _DividerAttribute_strokeWidth(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._DividerAttribute_strokeWidth(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _DividerAttribute_lineCap(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._DividerAttribute_lineCap(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _EffectComponent_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._EffectComponent_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _EffectComponentInterface_setEffectComponentOptions(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._EffectComponentInterface_setEffectComponentOptions(ptr)
        }
        throw new Error("Not implemented")
    }
    static _Ellipse_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Ellipse_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _EllipseInterface_setEllipseOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._EllipseInterface_setEllipseOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _EmbeddedComponent_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._EmbeddedComponent_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _EmbeddedComponentInterface_setEmbeddedComponentOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32, type: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._EmbeddedComponentInterface_setEmbeddedComponentOptions(ptr, thisArray, thisLength, type)
        }
        throw new Error("Not implemented")
    }
    static _EmbeddedComponentAttribute_onTerminated(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._EmbeddedComponentAttribute_onTerminated(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _EmbeddedComponentAttribute_onError(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._EmbeddedComponentAttribute_onError(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Flex_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Flex_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _FlexInterface_setFlexOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._FlexInterface_setFlexOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _FlexAttribute_pointLight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._FlexAttribute_pointLight(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _FlowItem_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._FlowItem_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _FlowItemInterface_setFlowItemOptions(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._FlowItemInterface_setFlowItemOptions(ptr)
        }
        throw new Error("Not implemented")
    }
    static _FolderStack_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._FolderStack_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _FolderStackInterface_setFolderStackOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._FolderStackInterface_setFolderStackOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _FolderStackAttribute_alignContent(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._FolderStackAttribute_alignContent(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _FolderStackAttribute_onFolderStateChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._FolderStackAttribute_onFolderStateChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _FolderStackAttribute_onHoverStatusChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._FolderStackAttribute_onHoverStatusChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _FolderStackAttribute_enableAnimation(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._FolderStackAttribute_enableAnimation(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _FolderStackAttribute_autoHalfFold(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._FolderStackAttribute_autoHalfFold(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _FormComponent_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._FormComponent_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _FormComponentInterface_setFormComponentOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._FormComponentInterface_setFormComponentOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _FormComponentAttribute_size(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._FormComponentAttribute_size(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _FormComponentAttribute_moduleName(ptr: KPointer, value: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._FormComponentAttribute_moduleName(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _FormComponentAttribute_dimension(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._FormComponentAttribute_dimension(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _FormComponentAttribute_allowUpdate(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._FormComponentAttribute_allowUpdate(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _FormComponentAttribute_visibility(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._FormComponentAttribute_visibility(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _FormComponentAttribute_onAcquired(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._FormComponentAttribute_onAcquired(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _FormComponentAttribute_onError(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._FormComponentAttribute_onError(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _FormComponentAttribute_onRouter(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._FormComponentAttribute_onRouter(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _FormComponentAttribute_onUninstall(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._FormComponentAttribute_onUninstall(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _FormComponentAttribute_onLoad(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._FormComponentAttribute_onLoad(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _FormLink_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._FormLink_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _FormLinkInterface_setFormLinkOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._FormLinkInterface_setFormLinkOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Gauge_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Gauge_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _GaugeInterface_setGaugeOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GaugeInterface_setGaugeOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GaugeAttribute_value(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GaugeAttribute_value(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _GaugeAttribute_startAngle(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GaugeAttribute_startAngle(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _GaugeAttribute_endAngle(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GaugeAttribute_endAngle(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _GaugeAttribute_colors(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GaugeAttribute_colors(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GaugeAttribute_strokeWidth(ptr: KPointer, value: Length): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GaugeAttribute_strokeWidth(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _GaugeAttribute_description(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GaugeAttribute_description(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GaugeAttribute_trackShadow(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GaugeAttribute_trackShadow(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GaugeAttribute_indicator(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GaugeAttribute_indicator(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GaugeAttribute_privacySensitive(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GaugeAttribute_privacySensitive(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GaugeAttribute_contentModifier(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GaugeAttribute_contentModifier(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Grid_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Grid_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _GridInterface_setGridOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridInterface_setGridOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GridAttribute_columnsTemplate(ptr: KPointer, value: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridAttribute_columnsTemplate(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _GridAttribute_rowsTemplate(ptr: KPointer, value: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridAttribute_rowsTemplate(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _GridAttribute_columnsGap(ptr: KPointer, value: Length): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridAttribute_columnsGap(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _GridAttribute_rowsGap(ptr: KPointer, value: Length): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridAttribute_rowsGap(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _GridAttribute_scrollBarWidth(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridAttribute_scrollBarWidth(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GridAttribute_scrollBarColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridAttribute_scrollBarColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GridAttribute_scrollBar(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridAttribute_scrollBar(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _GridAttribute_onScrollBarUpdate(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridAttribute_onScrollBarUpdate(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GridAttribute_onScrollIndex(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridAttribute_onScrollIndex(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GridAttribute_cachedCount0(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridAttribute_cachedCount0(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _GridAttribute_cachedCount1(ptr: KPointer, count: number, show: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridAttribute_cachedCount1(ptr, count, show)
        }
        throw new Error("Not implemented")
    }
    static _GridAttribute_editMode(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridAttribute_editMode(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _GridAttribute_multiSelectable(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridAttribute_multiSelectable(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _GridAttribute_maxCount(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridAttribute_maxCount(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _GridAttribute_minCount(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridAttribute_minCount(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _GridAttribute_cellLength(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridAttribute_cellLength(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _GridAttribute_layoutDirection(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridAttribute_layoutDirection(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _GridAttribute_supportAnimation(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridAttribute_supportAnimation(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _GridAttribute_onItemDragStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridAttribute_onItemDragStart(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GridAttribute_onItemDragEnter(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridAttribute_onItemDragEnter(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GridAttribute_onItemDragMove(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridAttribute_onItemDragMove(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GridAttribute_onItemDragLeave(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridAttribute_onItemDragLeave(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GridAttribute_onItemDrop(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridAttribute_onItemDrop(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GridAttribute_nestedScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridAttribute_nestedScroll(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GridAttribute_enableScrollInteraction(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridAttribute_enableScrollInteraction(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _GridAttribute_friction(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridAttribute_friction(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GridAttribute_alignItems(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridAttribute_alignItems(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GridAttribute_onScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridAttribute_onScroll(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GridAttribute_onReachStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridAttribute_onReachStart(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GridAttribute_onReachEnd(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridAttribute_onReachEnd(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GridAttribute_onScrollStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridAttribute_onScrollStart(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GridAttribute_onScrollStop(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridAttribute_onScrollStop(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GridAttribute_onScrollFrameBegin(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridAttribute_onScrollFrameBegin(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GridAttribute_edgeEffect(ptr: KPointer, value: KInt, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridAttribute_edgeEffect(ptr, value, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GridItem_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridItem_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _GridItemInterface_setGridItemOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridItemInterface_setGridItemOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GridItemAttribute_rowStart(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridItemAttribute_rowStart(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _GridItemAttribute_rowEnd(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridItemAttribute_rowEnd(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _GridItemAttribute_columnStart(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridItemAttribute_columnStart(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _GridItemAttribute_columnEnd(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridItemAttribute_columnEnd(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _GridItemAttribute_forceRebuild(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridItemAttribute_forceRebuild(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _GridItemAttribute_selectable(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridItemAttribute_selectable(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _GridItemAttribute_selected(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridItemAttribute_selected(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _GridItemAttribute_onSelect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridItemAttribute_onSelect(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GridItemAttribute__onChangeEvent_selected(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridItemAttribute__onChangeEvent_selected(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GridCol_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridCol_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _GridColInterface_setGridColOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridColInterface_setGridColOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GridColAttribute_span(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridColAttribute_span(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GridColAttribute_gridColOffset(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridColAttribute_gridColOffset(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GridColAttribute_order(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridColAttribute_order(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GridContainer_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridContainer_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _GridContainerInterface_setGridContainerOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridContainerInterface_setGridContainerOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GridRow_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridRow_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _GridRowInterface_setGridRowOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridRowInterface_setGridRowOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GridRowAttribute_onBreakpointChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridRowAttribute_onBreakpointChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GridRowAttribute_alignItems(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GridRowAttribute_alignItems(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _Hyperlink_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Hyperlink_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _HyperlinkInterface_setHyperlinkOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._HyperlinkInterface_setHyperlinkOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _HyperlinkAttribute_color(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._HyperlinkAttribute_color(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Image_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Image_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _ImageInterface_setImageOptions0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageInterface_setImageOptions0(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ImageInterface_setImageOptions1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageInterface_setImageOptions1(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ImageInterface_setImageOptions2(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageInterface_setImageOptions2(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ImageAttribute_alt(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageAttribute_alt(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ImageAttribute_matchTextDirection(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageAttribute_matchTextDirection(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ImageAttribute_fitOriginalSize(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageAttribute_fitOriginalSize(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ImageAttribute_fillColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageAttribute_fillColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ImageAttribute_objectFit(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageAttribute_objectFit(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ImageAttribute_objectRepeat(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageAttribute_objectRepeat(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ImageAttribute_autoResize(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageAttribute_autoResize(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ImageAttribute_renderMode(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageAttribute_renderMode(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ImageAttribute_dynamicRangeMode(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageAttribute_dynamicRangeMode(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ImageAttribute_interpolation(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageAttribute_interpolation(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ImageAttribute_sourceSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageAttribute_sourceSize(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ImageAttribute_syncLoad(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageAttribute_syncLoad(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ImageAttribute_colorFilter(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageAttribute_colorFilter(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ImageAttribute_copyOption(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageAttribute_copyOption(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ImageAttribute_draggable(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageAttribute_draggable(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ImageAttribute_pointLight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageAttribute_pointLight(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ImageAttribute_edgeAntialiasing(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageAttribute_edgeAntialiasing(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ImageAttribute_onComplete(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageAttribute_onComplete(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ImageAttribute_onError(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageAttribute_onError(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ImageAttribute_onFinish(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageAttribute_onFinish(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ImageAttribute_enableAnalyzer(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageAttribute_enableAnalyzer(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ImageAttribute_analyzerConfig(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageAttribute_analyzerConfig(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ImageAttribute_resizable(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageAttribute_resizable(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ImageAttribute_privacySensitive(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageAttribute_privacySensitive(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ImageAttribute_enhancedImageQuality(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageAttribute_enhancedImageQuality(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ImageAnimator_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageAnimator_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _ImageAnimatorInterface_setImageAnimatorOptions(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageAnimatorInterface_setImageAnimatorOptions(ptr)
        }
        throw new Error("Not implemented")
    }
    static _ImageAnimatorAttribute_images(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageAnimatorAttribute_images(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ImageAnimatorAttribute_state(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageAnimatorAttribute_state(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ImageAnimatorAttribute_duration(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageAnimatorAttribute_duration(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ImageAnimatorAttribute_reverse(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageAnimatorAttribute_reverse(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ImageAnimatorAttribute_fixedSize(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageAnimatorAttribute_fixedSize(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ImageAnimatorAttribute_preDecode(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageAnimatorAttribute_preDecode(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ImageAnimatorAttribute_fillMode(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageAnimatorAttribute_fillMode(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ImageAnimatorAttribute_iterations(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageAnimatorAttribute_iterations(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ImageAnimatorAttribute_onStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageAnimatorAttribute_onStart(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ImageAnimatorAttribute_onPause(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageAnimatorAttribute_onPause(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ImageAnimatorAttribute_onRepeat(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageAnimatorAttribute_onRepeat(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ImageAnimatorAttribute_onCancel(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageAnimatorAttribute_onCancel(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ImageAnimatorAttribute_onFinish(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageAnimatorAttribute_onFinish(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ImageSpan_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageSpan_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _ImageSpanInterface_setImageSpanOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageSpanInterface_setImageSpanOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ImageSpanAttribute_verticalAlign(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageSpanAttribute_verticalAlign(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ImageSpanAttribute_colorFilter(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageSpanAttribute_colorFilter(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ImageSpanAttribute_objectFit(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageSpanAttribute_objectFit(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ImageSpanAttribute_onComplete(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageSpanAttribute_onComplete(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ImageSpanAttribute_onError(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageSpanAttribute_onError(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ImageSpanAttribute_alt(ptr: KPointer, value: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageSpanAttribute_alt(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _Line_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Line_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _LineInterface_setLineOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._LineInterface_setLineOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _LineAttribute_startPoint(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._LineAttribute_startPoint(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _LineAttribute_endPoint(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._LineAttribute_endPoint(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _List_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._List_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _ListInterface_setListOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListInterface_setListOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ListAttribute_alignListItem(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListAttribute_alignListItem(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ListAttribute_listDirection(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListAttribute_listDirection(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ListAttribute_scrollBar(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListAttribute_scrollBar(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ListAttribute_contentStartOffset(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListAttribute_contentStartOffset(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ListAttribute_contentEndOffset(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListAttribute_contentEndOffset(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ListAttribute_divider(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListAttribute_divider(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ListAttribute_editMode(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListAttribute_editMode(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ListAttribute_multiSelectable(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListAttribute_multiSelectable(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ListAttribute_cachedCount0(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListAttribute_cachedCount0(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ListAttribute_cachedCount1(ptr: KPointer, count: number, show: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListAttribute_cachedCount1(ptr, count, show)
        }
        throw new Error("Not implemented")
    }
    static _ListAttribute_chainAnimation(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListAttribute_chainAnimation(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ListAttribute_chainAnimationOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListAttribute_chainAnimationOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ListAttribute_sticky(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListAttribute_sticky(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ListAttribute_scrollSnapAlign(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListAttribute_scrollSnapAlign(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ListAttribute_nestedScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListAttribute_nestedScroll(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ListAttribute_enableScrollInteraction(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListAttribute_enableScrollInteraction(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ListAttribute_friction(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListAttribute_friction(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ListAttribute_childrenMainSize(ptr: KPointer, value: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListAttribute_childrenMainSize(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ListAttribute_maintainVisibleContentPosition(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListAttribute_maintainVisibleContentPosition(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ListAttribute_onScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListAttribute_onScroll(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ListAttribute_onScrollIndex(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListAttribute_onScrollIndex(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ListAttribute_onScrollVisibleContentChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListAttribute_onScrollVisibleContentChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ListAttribute_onReachStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListAttribute_onReachStart(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ListAttribute_onReachEnd(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListAttribute_onReachEnd(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ListAttribute_onScrollStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListAttribute_onScrollStart(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ListAttribute_onScrollStop(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListAttribute_onScrollStop(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ListAttribute_onItemDelete(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListAttribute_onItemDelete(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ListAttribute_onItemMove(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListAttribute_onItemMove(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ListAttribute_onItemDragStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListAttribute_onItemDragStart(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ListAttribute_onItemDragEnter(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListAttribute_onItemDragEnter(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ListAttribute_onItemDragMove(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListAttribute_onItemDragMove(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ListAttribute_onItemDragLeave(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListAttribute_onItemDragLeave(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ListAttribute_onItemDrop(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListAttribute_onItemDrop(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ListAttribute_onScrollFrameBegin(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListAttribute_onScrollFrameBegin(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ListAttribute_lanes(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListAttribute_lanes(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ListAttribute_edgeEffect(ptr: KPointer, value: KInt, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListAttribute_edgeEffect(ptr, value, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ListItem_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListItem_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _ListItemInterface_setListItemOptions0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListItemInterface_setListItemOptions0(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ListItemInterface_setListItemOptions1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListItemInterface_setListItemOptions1(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ListItemAttribute_sticky(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListItemAttribute_sticky(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ListItemAttribute_editable(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListItemAttribute_editable(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ListItemAttribute_selectable(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListItemAttribute_selectable(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ListItemAttribute_selected(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListItemAttribute_selected(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ListItemAttribute_swipeAction(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListItemAttribute_swipeAction(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ListItemAttribute_onSelect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListItemAttribute_onSelect(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ListItemAttribute__onChangeEvent_selected(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListItemAttribute__onChangeEvent_selected(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ListItemGroup_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListItemGroup_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _ListItemGroupInterface_setListItemGroupOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListItemGroupInterface_setListItemGroupOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ListItemGroupAttribute_divider(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListItemGroupAttribute_divider(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ListItemGroupAttribute_childrenMainSize(ptr: KPointer, value: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListItemGroupAttribute_childrenMainSize(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _LoadingProgress_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._LoadingProgress_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _LoadingProgressInterface_setLoadingProgressOptions(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._LoadingProgressInterface_setLoadingProgressOptions(ptr)
        }
        throw new Error("Not implemented")
    }
    static _LoadingProgressAttribute_color(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._LoadingProgressAttribute_color(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _LoadingProgressAttribute_enableLoading(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._LoadingProgressAttribute_enableLoading(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _LoadingProgressAttribute_contentModifier(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._LoadingProgressAttribute_contentModifier(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _LocationButton_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._LocationButton_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _LocationButtonInterface_setLocationButtonOptions0(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._LocationButtonInterface_setLocationButtonOptions0(ptr)
        }
        throw new Error("Not implemented")
    }
    static _LocationButtonInterface_setLocationButtonOptions1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._LocationButtonInterface_setLocationButtonOptions1(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _LocationButtonAttribute_onClick(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._LocationButtonAttribute_onClick(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Marquee_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Marquee_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _MarqueeInterface_setMarqueeOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MarqueeInterface_setMarqueeOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _MarqueeAttribute_fontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MarqueeAttribute_fontColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _MarqueeAttribute_fontSize(ptr: KPointer, value: Length): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MarqueeAttribute_fontSize(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _MarqueeAttribute_allowScale(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MarqueeAttribute_allowScale(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _MarqueeAttribute_fontWeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MarqueeAttribute_fontWeight(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _MarqueeAttribute_fontFamily(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MarqueeAttribute_fontFamily(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _MarqueeAttribute_marqueeUpdateStrategy(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MarqueeAttribute_marqueeUpdateStrategy(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _MarqueeAttribute_onStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MarqueeAttribute_onStart(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _MarqueeAttribute_onBounce(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MarqueeAttribute_onBounce(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _MarqueeAttribute_onFinish(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MarqueeAttribute_onFinish(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _MediaCachedImage_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._MediaCachedImage_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _MediaCachedImageInterface_setMediaCachedImageOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MediaCachedImageInterface_setMediaCachedImageOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Menu_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Menu_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _MenuInterface_setMenuOptions(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MenuInterface_setMenuOptions(ptr)
        }
        throw new Error("Not implemented")
    }
    static _MenuAttribute_fontSize(ptr: KPointer, value: Length): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MenuAttribute_fontSize(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _MenuAttribute_font(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MenuAttribute_font(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _MenuAttribute_fontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MenuAttribute_fontColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _MenuAttribute_radius(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MenuAttribute_radius(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _MenuAttribute_menuItemDivider(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MenuAttribute_menuItemDivider(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _MenuAttribute_menuItemGroupDivider(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MenuAttribute_menuItemGroupDivider(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _MenuAttribute_subMenuExpandingMode(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MenuAttribute_subMenuExpandingMode(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _MenuItem_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._MenuItem_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _MenuItemInterface_setMenuItemOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MenuItemInterface_setMenuItemOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _MenuItemAttribute_selected(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MenuItemAttribute_selected(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _MenuItemAttribute_selectIcon(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MenuItemAttribute_selectIcon(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _MenuItemAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MenuItemAttribute_onChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _MenuItemAttribute_contentFont(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MenuItemAttribute_contentFont(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _MenuItemAttribute_contentFontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MenuItemAttribute_contentFontColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _MenuItemAttribute_labelFont(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MenuItemAttribute_labelFont(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _MenuItemAttribute_labelFontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MenuItemAttribute_labelFontColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _MenuItemAttribute__onChangeEvent_selected(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MenuItemAttribute__onChangeEvent_selected(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _MenuItemGroup_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._MenuItemGroup_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _MenuItemGroupInterface_setMenuItemGroupOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MenuItemGroupInterface_setMenuItemGroupOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavDestination_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavDestination_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _NavDestinationInterface_setNavDestinationOptions(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavDestinationInterface_setNavDestinationOptions(ptr)
        }
        throw new Error("Not implemented")
    }
    static _NavDestinationAttribute_hideTitleBar0(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavDestinationAttribute_hideTitleBar0(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _NavDestinationAttribute_hideTitleBar1(ptr: KPointer, hide: KInt, animated: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavDestinationAttribute_hideTitleBar1(ptr, hide, animated)
        }
        throw new Error("Not implemented")
    }
    static _NavDestinationAttribute_onShown(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavDestinationAttribute_onShown(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavDestinationAttribute_onHidden(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavDestinationAttribute_onHidden(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavDestinationAttribute_onBackPressed(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavDestinationAttribute_onBackPressed(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavDestinationAttribute_mode(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavDestinationAttribute_mode(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _NavDestinationAttribute_backButtonIcon(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavDestinationAttribute_backButtonIcon(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavDestinationAttribute_menus(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavDestinationAttribute_menus(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavDestinationAttribute_onReady(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavDestinationAttribute_onReady(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavDestinationAttribute_onWillAppear(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavDestinationAttribute_onWillAppear(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavDestinationAttribute_onWillDisappear(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavDestinationAttribute_onWillDisappear(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavDestinationAttribute_onWillShow(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavDestinationAttribute_onWillShow(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavDestinationAttribute_onWillHide(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavDestinationAttribute_onWillHide(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavDestinationAttribute_systemBarStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavDestinationAttribute_systemBarStyle(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavDestinationAttribute_recoverable(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavDestinationAttribute_recoverable(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavDestinationAttribute_systemTransition(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavDestinationAttribute_systemTransition(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _NavDestinationAttribute_title(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavDestinationAttribute_title(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavDestinationAttribute_toolbarConfiguration(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavDestinationAttribute_toolbarConfiguration(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavDestinationAttribute_hideToolBar(ptr: KPointer, hide: KInt, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavDestinationAttribute_hideToolBar(ptr, hide, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavDestinationAttribute_ignoreLayoutSafeArea(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavDestinationAttribute_ignoreLayoutSafeArea(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavRouter_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavRouter_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _NavRouterInterface_setNavRouterOptions0(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavRouterInterface_setNavRouterOptions0(ptr)
        }
        throw new Error("Not implemented")
    }
    static _NavRouterInterface_setNavRouterOptions1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavRouterInterface_setNavRouterOptions1(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavRouterAttribute_onStateChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavRouterAttribute_onStateChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavRouterAttribute_mode(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavRouterAttribute_mode(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _Navigator_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Navigator_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _NavigatorInterface_setNavigatorOptions0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavigatorInterface_setNavigatorOptions0(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavigatorInterface_setNavigatorOptions1(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavigatorInterface_setNavigatorOptions1(ptr)
        }
        throw new Error("Not implemented")
    }
    static _NavigatorAttribute_active(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavigatorAttribute_active(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _NavigatorAttribute_type(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavigatorAttribute_type(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _NavigatorAttribute_target(ptr: KPointer, value: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavigatorAttribute_target(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _NavigatorAttribute_params(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavigatorAttribute_params(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NodeContainer_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._NodeContainer_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _NodeContainerInterface_setNodeContainerOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NodeContainerInterface_setNodeContainerOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Panel_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Panel_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _PanelInterface_setPanelOptions(ptr: KPointer, show: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PanelInterface_setPanelOptions(ptr, show)
        }
        throw new Error("Not implemented")
    }
    static _PanelAttribute_mode(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PanelAttribute_mode(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _PanelAttribute_type(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PanelAttribute_type(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _PanelAttribute_dragBar(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PanelAttribute_dragBar(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _PanelAttribute_customHeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PanelAttribute_customHeight(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _PanelAttribute_fullHeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PanelAttribute_fullHeight(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _PanelAttribute_halfHeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PanelAttribute_halfHeight(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _PanelAttribute_miniHeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PanelAttribute_miniHeight(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _PanelAttribute_show(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PanelAttribute_show(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _PanelAttribute_backgroundMask(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PanelAttribute_backgroundMask(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _PanelAttribute_showCloseIcon(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PanelAttribute_showCloseIcon(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _PanelAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PanelAttribute_onChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _PanelAttribute_onHeightChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PanelAttribute_onHeightChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _PanelAttribute__onChangeEvent_mode(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PanelAttribute__onChangeEvent_mode(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _PasteButton_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._PasteButton_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _PasteButtonInterface_setPasteButtonOptions0(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PasteButtonInterface_setPasteButtonOptions0(ptr)
        }
        throw new Error("Not implemented")
    }
    static _PasteButtonInterface_setPasteButtonOptions1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PasteButtonInterface_setPasteButtonOptions1(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _PasteButtonAttribute_onClick(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PasteButtonAttribute_onClick(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Path_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Path_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _PathInterface_setPathOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PathInterface_setPathOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _PathAttribute_commands(ptr: KPointer, value: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PathAttribute_commands(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _PatternLock_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._PatternLock_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _PatternLockInterface_setPatternLockOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PatternLockInterface_setPatternLockOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _PatternLockAttribute_sideLength(ptr: KPointer, value: Length): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PatternLockAttribute_sideLength(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _PatternLockAttribute_circleRadius(ptr: KPointer, value: Length): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PatternLockAttribute_circleRadius(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _PatternLockAttribute_backgroundColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PatternLockAttribute_backgroundColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _PatternLockAttribute_regularColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PatternLockAttribute_regularColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _PatternLockAttribute_selectedColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PatternLockAttribute_selectedColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _PatternLockAttribute_activeColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PatternLockAttribute_activeColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _PatternLockAttribute_pathColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PatternLockAttribute_pathColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _PatternLockAttribute_pathStrokeWidth(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PatternLockAttribute_pathStrokeWidth(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _PatternLockAttribute_onPatternComplete(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PatternLockAttribute_onPatternComplete(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _PatternLockAttribute_autoReset(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PatternLockAttribute_autoReset(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _PatternLockAttribute_onDotConnect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PatternLockAttribute_onDotConnect(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _PatternLockAttribute_activateCircleStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PatternLockAttribute_activateCircleStyle(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _PluginComponent_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._PluginComponent_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _PluginComponentInterface_setPluginComponentOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PluginComponentInterface_setPluginComponentOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _PluginComponentAttribute_onComplete(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PluginComponentAttribute_onComplete(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _PluginComponentAttribute_onError(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PluginComponentAttribute_onError(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Polygon_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Polygon_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _PolygonInterface_setPolygonOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PolygonInterface_setPolygonOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _PolygonAttribute_points(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PolygonAttribute_points(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Polyline_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Polyline_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _PolylineInterface_setPolylineOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PolylineInterface_setPolylineOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _PolylineAttribute_points(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PolylineAttribute_points(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Progress_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Progress_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _ProgressInterface_setProgressOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ProgressInterface_setProgressOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ProgressAttribute_value(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ProgressAttribute_value(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ProgressAttribute_color(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ProgressAttribute_color(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ProgressAttribute_style(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ProgressAttribute_style(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ProgressAttribute_privacySensitive(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ProgressAttribute_privacySensitive(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ProgressAttribute_contentModifier(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ProgressAttribute_contentModifier(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _QRCode_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._QRCode_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _QRCodeInterface_setQRCodeOptions(ptr: KPointer, value: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._QRCodeInterface_setQRCodeOptions(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _QRCodeAttribute_color(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._QRCodeAttribute_color(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _QRCodeAttribute_backgroundColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._QRCodeAttribute_backgroundColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _QRCodeAttribute_contentOpacity(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._QRCodeAttribute_contentOpacity(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Radio_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Radio_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _RadioInterface_setRadioOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RadioInterface_setRadioOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RadioAttribute_checked(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RadioAttribute_checked(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _RadioAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RadioAttribute_onChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RadioAttribute_radioStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RadioAttribute_radioStyle(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RadioAttribute_contentModifier(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RadioAttribute_contentModifier(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RadioAttribute__onChangeEvent_checked(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RadioAttribute__onChangeEvent_checked(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Rating_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Rating_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _RatingInterface_setRatingOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RatingInterface_setRatingOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RatingAttribute_stars(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RatingAttribute_stars(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _RatingAttribute_stepSize(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RatingAttribute_stepSize(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _RatingAttribute_starStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RatingAttribute_starStyle(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RatingAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RatingAttribute_onChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RatingAttribute_contentModifier(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RatingAttribute_contentModifier(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RatingAttribute__onChangeEvent_rating(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RatingAttribute__onChangeEvent_rating(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Rect_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Rect_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _RectInterface_setRectOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RectInterface_setRectOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RectAttribute_radiusWidth(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RectAttribute_radiusWidth(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RectAttribute_radiusHeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RectAttribute_radiusHeight(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RectAttribute_radius(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RectAttribute_radius(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Refresh_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Refresh_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _RefreshInterface_setRefreshOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RefreshInterface_setRefreshOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RefreshAttribute_onStateChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RefreshAttribute_onStateChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RefreshAttribute_onRefreshing(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RefreshAttribute_onRefreshing(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RefreshAttribute_refreshOffset(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RefreshAttribute_refreshOffset(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _RefreshAttribute_pullToRefresh(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RefreshAttribute_pullToRefresh(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _RefreshAttribute_onOffsetChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RefreshAttribute_onOffsetChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RefreshAttribute_pullDownRatio(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RefreshAttribute_pullDownRatio(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RefreshAttribute__onChangeEvent_refreshing(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RefreshAttribute__onChangeEvent_refreshing(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RelativeContainer_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._RelativeContainer_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _RelativeContainerInterface_setRelativeContainerOptions(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RelativeContainerInterface_setRelativeContainerOptions(ptr)
        }
        throw new Error("Not implemented")
    }
    static _RelativeContainerAttribute_guideLine(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RelativeContainerAttribute_guideLine(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RelativeContainerAttribute_barrier0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RelativeContainerAttribute_barrier0(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RelativeContainerAttribute_barrier1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RelativeContainerAttribute_barrier1(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RichEditor_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditor_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorInterface_setRichEditorOptions0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorInterface_setRichEditorOptions0(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorInterface_setRichEditorOptions1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorInterface_setRichEditorOptions1(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorAttribute_onReady(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorAttribute_onReady(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorAttribute_onSelect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorAttribute_onSelect(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorAttribute_onSelectionChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorAttribute_onSelectionChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorAttribute_aboutToIMEInput(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorAttribute_aboutToIMEInput(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorAttribute_onIMEInputComplete(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorAttribute_onIMEInputComplete(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorAttribute_onDidIMEInput(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorAttribute_onDidIMEInput(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorAttribute_aboutToDelete(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorAttribute_aboutToDelete(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorAttribute_onDeleteComplete(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorAttribute_onDeleteComplete(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorAttribute_copyOptions(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorAttribute_copyOptions(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorAttribute_onPaste(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorAttribute_onPaste(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorAttribute_enableDataDetector(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorAttribute_enableDataDetector(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorAttribute_enablePreviewText(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorAttribute_enablePreviewText(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorAttribute_dataDetectorConfig(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorAttribute_dataDetectorConfig(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorAttribute_caretColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorAttribute_caretColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorAttribute_selectedBackgroundColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorAttribute_selectedBackgroundColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorAttribute_onEditingChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorAttribute_onEditingChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorAttribute_enterKeyType(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorAttribute_enterKeyType(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorAttribute_onSubmit(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorAttribute_onSubmit(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorAttribute_onWillChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorAttribute_onWillChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorAttribute_onDidChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorAttribute_onDidChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorAttribute_onCut(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorAttribute_onCut(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorAttribute_onCopy(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorAttribute_onCopy(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorAttribute_editMenuOptions(ptr: KPointer, value: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorAttribute_editMenuOptions(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorAttribute_enableKeyboardOnFocus(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorAttribute_enableKeyboardOnFocus(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorAttribute_enableHapticFeedback(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorAttribute_enableHapticFeedback(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorAttribute_barState(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorAttribute_barState(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorAttribute_bindSelectionMenu(ptr: KPointer, spanType: KInt, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorAttribute_bindSelectionMenu(ptr, spanType, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorAttribute_customKeyboard(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorAttribute_customKeyboard(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorAttribute_placeholder(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorAttribute_placeholder(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RichText_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichText_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _RichTextInterface_setRichTextOptions(ptr: KPointer, content: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichTextInterface_setRichTextOptions(ptr, content)
        }
        throw new Error("Not implemented")
    }
    static _RichTextAttribute_onStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichTextAttribute_onStart(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RichTextAttribute_onComplete(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichTextAttribute_onComplete(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RootScene_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._RootScene_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _RootSceneInterface_setRootSceneOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RootSceneInterface_setRootSceneOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Row_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Row_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _RowInterface_setRowOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RowInterface_setRowOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RowAttribute_alignItems(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RowAttribute_alignItems(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _RowAttribute_justifyContent(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RowAttribute_justifyContent(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _RowAttribute_pointLight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RowAttribute_pointLight(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RowAttribute_reverse(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RowAttribute_reverse(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RowSplit_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._RowSplit_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _RowSplitInterface_setRowSplitOptions(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RowSplitInterface_setRowSplitOptions(ptr)
        }
        throw new Error("Not implemented")
    }
    static _RowSplitAttribute_resizeable(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RowSplitAttribute_resizeable(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SaveButton_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._SaveButton_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _SaveButtonInterface_setSaveButtonOptions0(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SaveButtonInterface_setSaveButtonOptions0(ptr)
        }
        throw new Error("Not implemented")
    }
    static _SaveButtonInterface_setSaveButtonOptions1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SaveButtonInterface_setSaveButtonOptions1(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SaveButtonAttribute_onClick(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SaveButtonAttribute_onClick(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Screen_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Screen_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _ScreenInterface_setScreenOptions(ptr: KPointer, screenId: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScreenInterface_setScreenOptions(ptr, screenId)
        }
        throw new Error("Not implemented")
    }
    static _Scroll_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Scroll_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _ScrollInterface_setScrollOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScrollInterface_setScrollOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ScrollAttribute_scrollable(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScrollAttribute_scrollable(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ScrollAttribute_onScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScrollAttribute_onScroll(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ScrollAttribute_onWillScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScrollAttribute_onWillScroll(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ScrollAttribute_onDidScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScrollAttribute_onDidScroll(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ScrollAttribute_onScrollEdge(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScrollAttribute_onScrollEdge(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ScrollAttribute_onScrollStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScrollAttribute_onScrollStart(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ScrollAttribute_onScrollEnd(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScrollAttribute_onScrollEnd(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ScrollAttribute_onScrollStop(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScrollAttribute_onScrollStop(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ScrollAttribute_scrollBar(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScrollAttribute_scrollBar(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ScrollAttribute_scrollBarColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScrollAttribute_scrollBarColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ScrollAttribute_scrollBarWidth(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScrollAttribute_scrollBarWidth(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ScrollAttribute_onScrollFrameBegin(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScrollAttribute_onScrollFrameBegin(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ScrollAttribute_nestedScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScrollAttribute_nestedScroll(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ScrollAttribute_enableScrollInteraction(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScrollAttribute_enableScrollInteraction(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ScrollAttribute_friction(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScrollAttribute_friction(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ScrollAttribute_scrollSnap(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScrollAttribute_scrollSnap(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ScrollAttribute_enablePaging(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScrollAttribute_enablePaging(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ScrollAttribute_initialOffset(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScrollAttribute_initialOffset(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ScrollAttribute_edgeEffect(ptr: KPointer, edgeEffect: KInt, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScrollAttribute_edgeEffect(ptr, edgeEffect, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ScrollBar_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScrollBar_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _ScrollBarInterface_setScrollBarOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScrollBarInterface_setScrollBarOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ScrollBarAttribute_enableNestedScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScrollBarAttribute_enableNestedScroll(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Search_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Search_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _SearchInterface_setSearchOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SearchInterface_setSearchOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SearchAttribute_fontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SearchAttribute_fontColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SearchAttribute_searchIcon(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SearchAttribute_searchIcon(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SearchAttribute_cancelButton(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SearchAttribute_cancelButton(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SearchAttribute_textIndent(ptr: KPointer, value: Length): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SearchAttribute_textIndent(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SearchAttribute_onEditChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SearchAttribute_onEditChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SearchAttribute_selectedBackgroundColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SearchAttribute_selectedBackgroundColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SearchAttribute_caretStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SearchAttribute_caretStyle(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SearchAttribute_placeholderColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SearchAttribute_placeholderColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SearchAttribute_placeholderFont(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SearchAttribute_placeholderFont(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SearchAttribute_textFont(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SearchAttribute_textFont(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SearchAttribute_enterKeyType(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SearchAttribute_enterKeyType(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SearchAttribute_onSubmit0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SearchAttribute_onSubmit0(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SearchAttribute_onSubmit1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SearchAttribute_onSubmit1(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SearchAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SearchAttribute_onChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SearchAttribute_onTextSelectionChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SearchAttribute_onTextSelectionChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SearchAttribute_onContentScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SearchAttribute_onContentScroll(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SearchAttribute_onCopy(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SearchAttribute_onCopy(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SearchAttribute_onCut(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SearchAttribute_onCut(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SearchAttribute_onPaste(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SearchAttribute_onPaste(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SearchAttribute_copyOption(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SearchAttribute_copyOption(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SearchAttribute_maxLength(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SearchAttribute_maxLength(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SearchAttribute_textAlign(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SearchAttribute_textAlign(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SearchAttribute_enableKeyboardOnFocus(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SearchAttribute_enableKeyboardOnFocus(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SearchAttribute_selectionMenuHidden(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SearchAttribute_selectionMenuHidden(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SearchAttribute_minFontSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SearchAttribute_minFontSize(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SearchAttribute_maxFontSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SearchAttribute_maxFontSize(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SearchAttribute_decoration(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SearchAttribute_decoration(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SearchAttribute_letterSpacing(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SearchAttribute_letterSpacing(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SearchAttribute_lineHeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SearchAttribute_lineHeight(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SearchAttribute_type(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SearchAttribute_type(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SearchAttribute_fontFeature(ptr: KPointer, value: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SearchAttribute_fontFeature(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SearchAttribute_onWillInsert(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SearchAttribute_onWillInsert(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SearchAttribute_onDidInsert(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SearchAttribute_onDidInsert(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SearchAttribute_onWillDelete(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SearchAttribute_onWillDelete(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SearchAttribute_onDidDelete(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SearchAttribute_onDidDelete(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SearchAttribute_editMenuOptions(ptr: KPointer, value: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SearchAttribute_editMenuOptions(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SearchAttribute_enablePreviewText(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SearchAttribute_enablePreviewText(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SearchAttribute_enableHapticFeedback(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SearchAttribute_enableHapticFeedback(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SearchAttribute_searchButton(ptr: KPointer, value: KStringPtr, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SearchAttribute_searchButton(ptr, value, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SearchAttribute_inputFilter(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SearchAttribute_inputFilter(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SearchAttribute_customKeyboard(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SearchAttribute_customKeyboard(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SearchAttribute__onChangeEvent_value(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SearchAttribute__onChangeEvent_value(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SecurityComponentMethod_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._SecurityComponentMethod_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _SecurityComponentMethod_iconSize(ptr: KPointer, value: Length): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SecurityComponentMethod_iconSize(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SecurityComponentMethod_layoutDirection(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SecurityComponentMethod_layoutDirection(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SecurityComponentMethod_position(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SecurityComponentMethod_position(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SecurityComponentMethod_markAnchor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SecurityComponentMethod_markAnchor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SecurityComponentMethod_offset(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SecurityComponentMethod_offset(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SecurityComponentMethod_fontSize(ptr: KPointer, value: Length): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SecurityComponentMethod_fontSize(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SecurityComponentMethod_fontStyle(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SecurityComponentMethod_fontStyle(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SecurityComponentMethod_fontWeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SecurityComponentMethod_fontWeight(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SecurityComponentMethod_fontFamily(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SecurityComponentMethod_fontFamily(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SecurityComponentMethod_fontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SecurityComponentMethod_fontColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SecurityComponentMethod_iconColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SecurityComponentMethod_iconColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SecurityComponentMethod_backgroundColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SecurityComponentMethod_backgroundColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SecurityComponentMethod_borderStyle(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SecurityComponentMethod_borderStyle(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SecurityComponentMethod_borderWidth(ptr: KPointer, value: Length): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SecurityComponentMethod_borderWidth(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SecurityComponentMethod_borderColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SecurityComponentMethod_borderColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SecurityComponentMethod_borderRadius(ptr: KPointer, value: Length): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SecurityComponentMethod_borderRadius(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SecurityComponentMethod_padding(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SecurityComponentMethod_padding(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SecurityComponentMethod_textIconSpace(ptr: KPointer, value: Length): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SecurityComponentMethod_textIconSpace(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SecurityComponentMethod_key(ptr: KPointer, value: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SecurityComponentMethod_key(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SecurityComponentMethod_width(ptr: KPointer, value: Length): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SecurityComponentMethod_width(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SecurityComponentMethod_height(ptr: KPointer, value: Length): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SecurityComponentMethod_height(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SecurityComponentMethod_size(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SecurityComponentMethod_size(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SecurityComponentMethod_constraintSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SecurityComponentMethod_constraintSize(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Select_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Select_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _SelectInterface_setSelectOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SelectInterface_setSelectOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SelectAttribute_selected(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SelectAttribute_selected(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SelectAttribute_value(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SelectAttribute_value(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SelectAttribute_font(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SelectAttribute_font(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SelectAttribute_fontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SelectAttribute_fontColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SelectAttribute_selectedOptionBgColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SelectAttribute_selectedOptionBgColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SelectAttribute_selectedOptionFont(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SelectAttribute_selectedOptionFont(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SelectAttribute_selectedOptionFontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SelectAttribute_selectedOptionFontColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SelectAttribute_optionBgColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SelectAttribute_optionBgColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SelectAttribute_optionFont(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SelectAttribute_optionFont(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SelectAttribute_optionFontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SelectAttribute_optionFontColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SelectAttribute_onSelect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SelectAttribute_onSelect(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SelectAttribute_space(ptr: KPointer, value: Length): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SelectAttribute_space(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SelectAttribute_arrowPosition(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SelectAttribute_arrowPosition(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SelectAttribute_optionWidth(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SelectAttribute_optionWidth(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SelectAttribute_optionHeight(ptr: KPointer, value: Length): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SelectAttribute_optionHeight(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SelectAttribute_menuBackgroundColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SelectAttribute_menuBackgroundColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SelectAttribute_menuBackgroundBlurStyle(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SelectAttribute_menuBackgroundBlurStyle(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SelectAttribute_controlSize(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SelectAttribute_controlSize(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SelectAttribute_menuItemContentModifier(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SelectAttribute_menuItemContentModifier(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SelectAttribute_divider(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SelectAttribute_divider(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SelectAttribute_menuAlign(ptr: KPointer, alignType: KInt, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SelectAttribute_menuAlign(ptr, alignType, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SelectAttribute__onChangeEvent_selected(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SelectAttribute__onChangeEvent_selected(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SelectAttribute__onChangeEvent_value(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SelectAttribute__onChangeEvent_value(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Shape_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Shape_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _ShapeInterface_setShapeOptions0(ptr: KPointer, value: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ShapeInterface_setShapeOptions0(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ShapeInterface_setShapeOptions1(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ShapeInterface_setShapeOptions1(ptr)
        }
        throw new Error("Not implemented")
    }
    static _ShapeAttribute_viewPort(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ShapeAttribute_viewPort(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ShapeAttribute_stroke(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ShapeAttribute_stroke(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ShapeAttribute_fill(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ShapeAttribute_fill(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ShapeAttribute_strokeDashOffset(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ShapeAttribute_strokeDashOffset(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ShapeAttribute_strokeDashArray(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ShapeAttribute_strokeDashArray(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ShapeAttribute_strokeLineCap(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ShapeAttribute_strokeLineCap(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ShapeAttribute_strokeLineJoin(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ShapeAttribute_strokeLineJoin(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ShapeAttribute_strokeMiterLimit(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ShapeAttribute_strokeMiterLimit(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ShapeAttribute_strokeOpacity(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ShapeAttribute_strokeOpacity(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ShapeAttribute_fillOpacity(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ShapeAttribute_fillOpacity(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ShapeAttribute_strokeWidth(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ShapeAttribute_strokeWidth(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ShapeAttribute_antiAlias(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ShapeAttribute_antiAlias(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ShapeAttribute_mesh(ptr: KPointer, thisArray: Uint8Array, thisLength: int32, column: number, row: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ShapeAttribute_mesh(ptr, thisArray, thisLength, column, row)
        }
        throw new Error("Not implemented")
    }
    static _Slider_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Slider_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _SliderInterface_setSliderOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SliderInterface_setSliderOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SliderAttribute_blockColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SliderAttribute_blockColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SliderAttribute_trackColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SliderAttribute_trackColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SliderAttribute_selectedColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SliderAttribute_selectedColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SliderAttribute_minLabel(ptr: KPointer, value: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SliderAttribute_minLabel(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SliderAttribute_maxLabel(ptr: KPointer, value: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SliderAttribute_maxLabel(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SliderAttribute_showSteps(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SliderAttribute_showSteps(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SliderAttribute_trackThickness(ptr: KPointer, value: Length): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SliderAttribute_trackThickness(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SliderAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SliderAttribute_onChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SliderAttribute_blockBorderColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SliderAttribute_blockBorderColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SliderAttribute_blockBorderWidth(ptr: KPointer, value: Length): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SliderAttribute_blockBorderWidth(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SliderAttribute_stepColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SliderAttribute_stepColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SliderAttribute_trackBorderRadius(ptr: KPointer, value: Length): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SliderAttribute_trackBorderRadius(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SliderAttribute_selectedBorderRadius(ptr: KPointer, value: Length): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SliderAttribute_selectedBorderRadius(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SliderAttribute_blockSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SliderAttribute_blockSize(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SliderAttribute_blockStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SliderAttribute_blockStyle(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SliderAttribute_stepSize(ptr: KPointer, value: Length): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SliderAttribute_stepSize(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SliderAttribute_sliderInteractionMode(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SliderAttribute_sliderInteractionMode(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SliderAttribute_minResponsiveDistance(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SliderAttribute_minResponsiveDistance(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SliderAttribute_contentModifier(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SliderAttribute_contentModifier(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SliderAttribute_slideRange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SliderAttribute_slideRange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SliderAttribute_showTips(ptr: KPointer, value: KInt, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SliderAttribute_showTips(ptr, value, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SliderAttribute__onChangeEvent_value(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SliderAttribute__onChangeEvent_value(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _BaseSpan_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._BaseSpan_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _BaseSpan_textBackgroundStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._BaseSpan_textBackgroundStyle(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _BaseSpan_baselineOffset(ptr: KPointer, value: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._BaseSpan_baselineOffset(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _Span_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Span_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _SpanInterface_setSpanOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SpanInterface_setSpanOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SpanAttribute_font(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SpanAttribute_font(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SpanAttribute_fontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SpanAttribute_fontColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SpanAttribute_fontSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SpanAttribute_fontSize(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SpanAttribute_fontStyle(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SpanAttribute_fontStyle(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SpanAttribute_fontWeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SpanAttribute_fontWeight(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SpanAttribute_fontFamily(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SpanAttribute_fontFamily(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SpanAttribute_decoration(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SpanAttribute_decoration(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SpanAttribute_letterSpacing(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SpanAttribute_letterSpacing(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SpanAttribute_textCase(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SpanAttribute_textCase(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SpanAttribute_lineHeight(ptr: KPointer, value: Length): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SpanAttribute_lineHeight(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SpanAttribute_textShadow(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SpanAttribute_textShadow(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Stack_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Stack_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _StackInterface_setStackOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._StackInterface_setStackOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _StackAttribute_alignContent(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._StackAttribute_alignContent(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _StackAttribute_pointLight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._StackAttribute_pointLight(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Stepper_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Stepper_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _StepperInterface_setStepperOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._StepperInterface_setStepperOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _StepperAttribute_onFinish(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._StepperAttribute_onFinish(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _StepperAttribute_onSkip(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._StepperAttribute_onSkip(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _StepperAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._StepperAttribute_onChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _StepperAttribute_onNext(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._StepperAttribute_onNext(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _StepperAttribute_onPrevious(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._StepperAttribute_onPrevious(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _StepperAttribute__onChangeEvent_index(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._StepperAttribute__onChangeEvent_index(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _StepperItem_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._StepperItem_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _StepperItemInterface_setStepperItemOptions(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._StepperItemInterface_setStepperItemOptions(ptr)
        }
        throw new Error("Not implemented")
    }
    static _StepperItemAttribute_prevLabel(ptr: KPointer, value: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._StepperItemAttribute_prevLabel(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _StepperItemAttribute_nextLabel(ptr: KPointer, value: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._StepperItemAttribute_nextLabel(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _StepperItemAttribute_status(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._StepperItemAttribute_status(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Swiper_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Swiper_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _SwiperInterface_setSwiperOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwiperInterface_setSwiperOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SwiperAttribute_index(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwiperAttribute_index(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SwiperAttribute_autoPlay(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwiperAttribute_autoPlay(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SwiperAttribute_interval(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwiperAttribute_interval(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SwiperAttribute_indicator0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwiperAttribute_indicator0(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SwiperAttribute_indicator1(ptr: KPointer, value: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwiperAttribute_indicator1(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SwiperAttribute_loop(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwiperAttribute_loop(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SwiperAttribute_duration(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwiperAttribute_duration(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SwiperAttribute_vertical(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwiperAttribute_vertical(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SwiperAttribute_itemSpace(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwiperAttribute_itemSpace(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SwiperAttribute_displayMode(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwiperAttribute_displayMode(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SwiperAttribute_cachedCount(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwiperAttribute_cachedCount(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SwiperAttribute_effectMode(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwiperAttribute_effectMode(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SwiperAttribute_disableSwipe(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwiperAttribute_disableSwipe(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SwiperAttribute_curve(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwiperAttribute_curve(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SwiperAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwiperAttribute_onChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SwiperAttribute_indicatorStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwiperAttribute_indicatorStyle(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SwiperAttribute_onAnimationStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwiperAttribute_onAnimationStart(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SwiperAttribute_onAnimationEnd(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwiperAttribute_onAnimationEnd(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SwiperAttribute_onGestureSwipe(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwiperAttribute_onGestureSwipe(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SwiperAttribute_nestedScroll(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwiperAttribute_nestedScroll(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SwiperAttribute_customContentTransition(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwiperAttribute_customContentTransition(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SwiperAttribute_onContentDidScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwiperAttribute_onContentDidScroll(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SwiperAttribute_indicatorInteractive(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwiperAttribute_indicatorInteractive(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SwiperAttribute_displayArrow(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwiperAttribute_displayArrow(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SwiperAttribute_displayCount(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwiperAttribute_displayCount(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SwiperAttribute_prevMargin(ptr: KPointer, value: Length, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwiperAttribute_prevMargin(ptr, value, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SwiperAttribute_nextMargin(ptr: KPointer, value: Length, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwiperAttribute_nextMargin(ptr, value, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SwiperAttribute__onChangeEvent_index(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwiperAttribute__onChangeEvent_index(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _IndicatorComponent_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._IndicatorComponent_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _IndicatorComponentInterface_setIndicatorComponentOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._IndicatorComponentInterface_setIndicatorComponentOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _IndicatorComponentAttribute_initialIndex(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._IndicatorComponentAttribute_initialIndex(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _IndicatorComponentAttribute_count(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._IndicatorComponentAttribute_count(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _IndicatorComponentAttribute_style(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._IndicatorComponentAttribute_style(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _IndicatorComponentAttribute_loop(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._IndicatorComponentAttribute_loop(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _IndicatorComponentAttribute_vertical(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._IndicatorComponentAttribute_vertical(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _IndicatorComponentAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._IndicatorComponentAttribute_onChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SymbolGlyph_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._SymbolGlyph_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _SymbolGlyphInterface_setSymbolGlyphOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SymbolGlyphInterface_setSymbolGlyphOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SymbolGlyphAttribute_fontSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SymbolGlyphAttribute_fontSize(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SymbolGlyphAttribute_fontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SymbolGlyphAttribute_fontColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SymbolGlyphAttribute_fontWeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SymbolGlyphAttribute_fontWeight(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SymbolGlyphAttribute_effectStrategy(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SymbolGlyphAttribute_effectStrategy(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SymbolGlyphAttribute_renderingStrategy(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SymbolGlyphAttribute_renderingStrategy(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SymbolGlyphAttribute_symbolEffect0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SymbolGlyphAttribute_symbolEffect0(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SymbolGlyphAttribute_symbolEffect1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SymbolGlyphAttribute_symbolEffect1(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SymbolSpan_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._SymbolSpan_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _SymbolSpanInterface_setSymbolSpanOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SymbolSpanInterface_setSymbolSpanOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SymbolSpanAttribute_fontSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SymbolSpanAttribute_fontSize(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SymbolSpanAttribute_fontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SymbolSpanAttribute_fontColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SymbolSpanAttribute_fontWeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SymbolSpanAttribute_fontWeight(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SymbolSpanAttribute_effectStrategy(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SymbolSpanAttribute_effectStrategy(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SymbolSpanAttribute_renderingStrategy(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SymbolSpanAttribute_renderingStrategy(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _Tabs_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Tabs_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _TabsInterface_setTabsOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TabsInterface_setTabsOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TabsAttribute_vertical(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TabsAttribute_vertical(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TabsAttribute_barPosition(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TabsAttribute_barPosition(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TabsAttribute_scrollable(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TabsAttribute_scrollable(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TabsAttribute_barMode0(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TabsAttribute_barMode0(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TabsAttribute_barMode1(ptr: KPointer, value: KInt, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TabsAttribute_barMode1(ptr, value, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TabsAttribute_barWidth(ptr: KPointer, value: Length): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TabsAttribute_barWidth(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TabsAttribute_barHeight(ptr: KPointer, value: Length): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TabsAttribute_barHeight(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TabsAttribute_animationDuration(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TabsAttribute_animationDuration(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TabsAttribute_animationMode(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TabsAttribute_animationMode(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TabsAttribute_edgeEffect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TabsAttribute_edgeEffect(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TabsAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TabsAttribute_onChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TabsAttribute_onTabBarClick(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TabsAttribute_onTabBarClick(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TabsAttribute_onAnimationStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TabsAttribute_onAnimationStart(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TabsAttribute_onAnimationEnd(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TabsAttribute_onAnimationEnd(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TabsAttribute_onGestureSwipe(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TabsAttribute_onGestureSwipe(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TabsAttribute_fadingEdge(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TabsAttribute_fadingEdge(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TabsAttribute_divider(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TabsAttribute_divider(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TabsAttribute_barOverlap(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TabsAttribute_barOverlap(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TabsAttribute_barBackgroundColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TabsAttribute_barBackgroundColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TabsAttribute_barGridAlign(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TabsAttribute_barGridAlign(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TabsAttribute_customContentTransition(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TabsAttribute_customContentTransition(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TabsAttribute_barBackgroundBlurStyle0(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TabsAttribute_barBackgroundBlurStyle0(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TabsAttribute_barBackgroundBlurStyle1(ptr: KPointer, style: KInt, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TabsAttribute_barBackgroundBlurStyle1(ptr, style, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TabsAttribute_barBackgroundEffect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TabsAttribute_barBackgroundEffect(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TabsAttribute_onContentWillChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TabsAttribute_onContentWillChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TabsAttribute_barModeScrollable(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TabsAttribute_barModeScrollable(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TabsAttribute__onChangeEvent_index(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TabsAttribute__onChangeEvent_index(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TabContent_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TabContent_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _TabContentInterface_setTabContentOptions(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TabContentInterface_setTabContentOptions(ptr)
        }
        throw new Error("Not implemented")
    }
    static _TabContentAttribute_tabBar0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TabContentAttribute_tabBar0(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TabContentAttribute_tabBar1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TabContentAttribute_tabBar1(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TabContentAttribute_onWillShow(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TabContentAttribute_onWillShow(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TabContentAttribute_onWillHide(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TabContentAttribute_onWillHide(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Text_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Text_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _TextInterface_setTextOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInterface_setTextOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAttribute_font0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAttribute_font0(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAttribute_font1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAttribute_font1(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAttribute_fontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAttribute_fontColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAttribute_fontSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAttribute_fontSize(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAttribute_minFontSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAttribute_minFontSize(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAttribute_maxFontSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAttribute_maxFontSize(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAttribute_minFontScale(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAttribute_minFontScale(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAttribute_maxFontScale(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAttribute_maxFontScale(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAttribute_fontStyle(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAttribute_fontStyle(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextAttribute_fontWeight0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAttribute_fontWeight0(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAttribute_fontWeight1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAttribute_fontWeight1(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAttribute_lineSpacing(ptr: KPointer, value: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAttribute_lineSpacing(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextAttribute_textAlign(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAttribute_textAlign(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextAttribute_lineHeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAttribute_lineHeight(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAttribute_textOverflow(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAttribute_textOverflow(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAttribute_fontFamily(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAttribute_fontFamily(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAttribute_maxLines(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAttribute_maxLines(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextAttribute_decoration(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAttribute_decoration(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAttribute_letterSpacing(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAttribute_letterSpacing(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAttribute_textCase(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAttribute_textCase(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextAttribute_baselineOffset(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAttribute_baselineOffset(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAttribute_copyOption(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAttribute_copyOption(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextAttribute_draggable(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAttribute_draggable(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextAttribute_textShadow(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAttribute_textShadow(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAttribute_heightAdaptivePolicy(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAttribute_heightAdaptivePolicy(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextAttribute_textIndent(ptr: KPointer, value: Length): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAttribute_textIndent(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextAttribute_wordBreak(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAttribute_wordBreak(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextAttribute_lineBreakStrategy(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAttribute_lineBreakStrategy(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextAttribute_onCopy(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAttribute_onCopy(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAttribute_caretColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAttribute_caretColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAttribute_selectedBackgroundColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAttribute_selectedBackgroundColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAttribute_ellipsisMode(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAttribute_ellipsisMode(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextAttribute_enableDataDetector(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAttribute_enableDataDetector(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextAttribute_dataDetectorConfig(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAttribute_dataDetectorConfig(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAttribute_onTextSelectionChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAttribute_onTextSelectionChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAttribute_fontFeature(ptr: KPointer, value: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAttribute_fontFeature(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextAttribute_privacySensitive(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAttribute_privacySensitive(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextAttribute_textSelectable(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAttribute_textSelectable(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextAttribute_editMenuOptions(ptr: KPointer, value: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAttribute_editMenuOptions(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextAttribute_halfLeading(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAttribute_halfLeading(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextAttribute_enableHapticFeedback(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAttribute_enableHapticFeedback(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextAttribute_selection(ptr: KPointer, selectionStart: number, selectionEnd: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAttribute_selection(ptr, selectionStart, selectionEnd)
        }
        throw new Error("Not implemented")
    }
    static _TextAttribute_bindSelectionMenu(ptr: KPointer, spanType: KInt, thisArray: Uint8Array, thisLength: int32, responseType: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAttribute_bindSelectionMenu(ptr, spanType, thisArray, thisLength, responseType)
        }
        throw new Error("Not implemented")
    }
    static _TextArea_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextArea_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaInterface_setTextAreaOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaInterface_setTextAreaOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_placeholderColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_placeholderColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_placeholderFont(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_placeholderFont(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_enterKeyType(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_enterKeyType(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_textAlign(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_textAlign(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_caretColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_caretColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_fontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_fontColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_fontSize(ptr: KPointer, value: Length): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_fontSize(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_fontStyle(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_fontStyle(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_fontWeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_fontWeight(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_fontFamily(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_fontFamily(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_textOverflow(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_textOverflow(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_textIndent(ptr: KPointer, value: Length): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_textIndent(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_caretStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_caretStyle(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_selectedBackgroundColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_selectedBackgroundColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_onSubmit0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_onSubmit0(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_onSubmit1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_onSubmit1(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_onChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_onTextSelectionChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_onTextSelectionChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_onContentScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_onContentScroll(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_onEditChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_onEditChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_onCopy(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_onCopy(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_onCut(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_onCut(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_onPaste(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_onPaste(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_copyOption(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_copyOption(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_enableKeyboardOnFocus(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_enableKeyboardOnFocus(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_maxLength(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_maxLength(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_style(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_style(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_barState(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_barState(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_selectionMenuHidden(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_selectionMenuHidden(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_minFontSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_minFontSize(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_maxFontSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_maxFontSize(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_heightAdaptivePolicy(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_heightAdaptivePolicy(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_maxLines(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_maxLines(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_wordBreak(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_wordBreak(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_lineBreakStrategy(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_lineBreakStrategy(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_decoration(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_decoration(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_letterSpacing(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_letterSpacing(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_lineSpacing(ptr: KPointer, value: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_lineSpacing(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_lineHeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_lineHeight(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_type(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_type(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_enableAutoFill(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_enableAutoFill(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_contentType(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_contentType(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_fontFeature(ptr: KPointer, value: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_fontFeature(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_onWillInsert(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_onWillInsert(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_onDidInsert(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_onDidInsert(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_onWillDelete(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_onWillDelete(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_onDidDelete(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_onDidDelete(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_editMenuOptions(ptr: KPointer, value: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_editMenuOptions(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_enablePreviewText(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_enablePreviewText(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_enableHapticFeedback(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_enableHapticFeedback(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_inputFilter(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_inputFilter(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_showCounter(ptr: KPointer, value: KInt, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_showCounter(ptr, value, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute_customKeyboard(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute_customKeyboard(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaAttribute__onChangeEvent_text(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaAttribute__onChangeEvent_text(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextClock_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextClock_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _TextClockInterface_setTextClockOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextClockInterface_setTextClockOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextClockAttribute_format(ptr: KPointer, value: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextClockAttribute_format(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextClockAttribute_onDateChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextClockAttribute_onDateChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextClockAttribute_fontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextClockAttribute_fontColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextClockAttribute_fontSize(ptr: KPointer, value: Length): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextClockAttribute_fontSize(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextClockAttribute_fontStyle(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextClockAttribute_fontStyle(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextClockAttribute_fontWeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextClockAttribute_fontWeight(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextClockAttribute_fontFamily(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextClockAttribute_fontFamily(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextClockAttribute_textShadow(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextClockAttribute_textShadow(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextClockAttribute_fontFeature(ptr: KPointer, value: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextClockAttribute_fontFeature(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextClockAttribute_contentModifier(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextClockAttribute_contentModifier(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextClockAttribute_dateTimeOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextClockAttribute_dateTimeOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextInput_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInput_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _TextInputInterface_setTextInputOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputInterface_setTextInputOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_type(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_type(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_contentType(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_contentType(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_placeholderColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_placeholderColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_textOverflow(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_textOverflow(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_textIndent(ptr: KPointer, value: Length): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_textIndent(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_placeholderFont(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_placeholderFont(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_enterKeyType(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_enterKeyType(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_caretColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_caretColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_onEditChanged(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_onEditChanged(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_onEditChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_onEditChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_onSubmit(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_onSubmit(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_onChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_onTextSelectionChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_onTextSelectionChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_onContentScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_onContentScroll(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_maxLength(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_maxLength(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_fontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_fontColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_fontSize(ptr: KPointer, value: Length): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_fontSize(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_fontStyle(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_fontStyle(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_fontWeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_fontWeight(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_fontFamily(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_fontFamily(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_onCopy(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_onCopy(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_onCut(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_onCut(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_onPaste(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_onPaste(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_copyOption(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_copyOption(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_showPasswordIcon(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_showPasswordIcon(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_textAlign(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_textAlign(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_style(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_style(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_caretStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_caretStyle(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_selectedBackgroundColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_selectedBackgroundColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_caretPosition(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_caretPosition(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_enableKeyboardOnFocus(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_enableKeyboardOnFocus(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_passwordIcon(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_passwordIcon(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_showError(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_showError(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_showUnit(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_showUnit(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_showUnderline(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_showUnderline(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_underlineColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_underlineColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_selectionMenuHidden(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_selectionMenuHidden(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_barState(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_barState(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_maxLines(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_maxLines(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_wordBreak(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_wordBreak(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_lineBreakStrategy(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_lineBreakStrategy(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_cancelButton0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_cancelButton0(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_cancelButton1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_cancelButton1(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_selectAll(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_selectAll(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_minFontSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_minFontSize(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_maxFontSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_maxFontSize(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_heightAdaptivePolicy(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_heightAdaptivePolicy(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_enableAutoFill(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_enableAutoFill(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_decoration(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_decoration(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_letterSpacing(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_letterSpacing(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_lineHeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_lineHeight(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_passwordRules(ptr: KPointer, value: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_passwordRules(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_fontFeature(ptr: KPointer, value: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_fontFeature(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_showPassword(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_showPassword(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_onSecurityStateChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_onSecurityStateChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_onWillInsert(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_onWillInsert(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_onDidInsert(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_onDidInsert(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_onWillDelete(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_onWillDelete(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_onDidDelete(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_onDidDelete(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_editMenuOptions(ptr: KPointer, value: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_editMenuOptions(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_enablePreviewText(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_enablePreviewText(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_enableHapticFeedback(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_enableHapticFeedback(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_inputFilter(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_inputFilter(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_customKeyboard(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_customKeyboard(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute_showCounter(ptr: KPointer, value: KInt, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute_showCounter(ptr, value, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextInputAttribute__onChangeEvent_text(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputAttribute__onChangeEvent_text(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextPicker_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextPicker_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _TextPickerInterface_setTextPickerOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextPickerInterface_setTextPickerOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextPickerAttribute_defaultPickerItemHeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextPickerAttribute_defaultPickerItemHeight(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextPickerAttribute_canLoop(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextPickerAttribute_canLoop(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextPickerAttribute_disappearTextStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextPickerAttribute_disappearTextStyle(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextPickerAttribute_textStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextPickerAttribute_textStyle(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextPickerAttribute_selectedTextStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextPickerAttribute_selectedTextStyle(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextPickerAttribute_onAccept(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextPickerAttribute_onAccept(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextPickerAttribute_onCancel(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextPickerAttribute_onCancel(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextPickerAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextPickerAttribute_onChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextPickerAttribute_selectedIndex(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextPickerAttribute_selectedIndex(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextPickerAttribute_divider(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextPickerAttribute_divider(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextPickerAttribute_gradientHeight(ptr: KPointer, value: Length): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextPickerAttribute_gradientHeight(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextPickerAttribute__onChangeEvent_selected(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextPickerAttribute__onChangeEvent_selected(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextPickerAttribute__onChangeEvent_value(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextPickerAttribute__onChangeEvent_value(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextTimer_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextTimer_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _TextTimerInterface_setTextTimerOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextTimerInterface_setTextTimerOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextTimerAttribute_format(ptr: KPointer, value: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextTimerAttribute_format(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextTimerAttribute_fontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextTimerAttribute_fontColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextTimerAttribute_fontSize(ptr: KPointer, value: Length): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextTimerAttribute_fontSize(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextTimerAttribute_fontStyle(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextTimerAttribute_fontStyle(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextTimerAttribute_fontWeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextTimerAttribute_fontWeight(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextTimerAttribute_fontFamily(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextTimerAttribute_fontFamily(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextTimerAttribute_onTimer(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextTimerAttribute_onTimer(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextTimerAttribute_textShadow(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextTimerAttribute_textShadow(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextTimerAttribute_contentModifier(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextTimerAttribute_contentModifier(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TimePicker_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TimePicker_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _TimePickerInterface_setTimePickerOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TimePickerInterface_setTimePickerOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TimePickerAttribute_useMilitaryTime(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TimePickerAttribute_useMilitaryTime(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TimePickerAttribute_loop(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TimePickerAttribute_loop(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TimePickerAttribute_disappearTextStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TimePickerAttribute_disappearTextStyle(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TimePickerAttribute_textStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TimePickerAttribute_textStyle(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TimePickerAttribute_selectedTextStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TimePickerAttribute_selectedTextStyle(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TimePickerAttribute_dateTimeOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TimePickerAttribute_dateTimeOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TimePickerAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TimePickerAttribute_onChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TimePickerAttribute_enableHapticFeedback(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TimePickerAttribute_enableHapticFeedback(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TimePickerAttribute__onChangeEvent_selected(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TimePickerAttribute__onChangeEvent_selected(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Toggle_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Toggle_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _ToggleInterface_setToggleOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ToggleInterface_setToggleOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ToggleAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ToggleAttribute_onChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ToggleAttribute_contentModifier(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ToggleAttribute_contentModifier(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ToggleAttribute_selectedColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ToggleAttribute_selectedColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ToggleAttribute_switchPointColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ToggleAttribute_switchPointColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ToggleAttribute_switchStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ToggleAttribute_switchStyle(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ToggleAttribute__onChangeEvent_isOn(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ToggleAttribute__onChangeEvent_isOn(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Video_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Video_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _VideoInterface_setVideoOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._VideoInterface_setVideoOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _VideoAttribute_muted(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._VideoAttribute_muted(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _VideoAttribute_autoPlay(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._VideoAttribute_autoPlay(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _VideoAttribute_controls(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._VideoAttribute_controls(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _VideoAttribute_loop(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._VideoAttribute_loop(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _VideoAttribute_objectFit(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._VideoAttribute_objectFit(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _VideoAttribute_onStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._VideoAttribute_onStart(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _VideoAttribute_onPause(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._VideoAttribute_onPause(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _VideoAttribute_onFinish(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._VideoAttribute_onFinish(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _VideoAttribute_onFullscreenChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._VideoAttribute_onFullscreenChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _VideoAttribute_onPrepared(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._VideoAttribute_onPrepared(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _VideoAttribute_onSeeking(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._VideoAttribute_onSeeking(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _VideoAttribute_onSeeked(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._VideoAttribute_onSeeked(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _VideoAttribute_onUpdate(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._VideoAttribute_onUpdate(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _VideoAttribute_onError(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._VideoAttribute_onError(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _VideoAttribute_onStop(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._VideoAttribute_onStop(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _VideoAttribute_enableAnalyzer(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._VideoAttribute_enableAnalyzer(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _VideoAttribute_analyzerConfig(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._VideoAttribute_analyzerConfig(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Web_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Web_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _WebInterface_setWebOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebInterface_setWebOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_javaScriptAccess(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_javaScriptAccess(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_fileAccess(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_fileAccess(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onlineImageAccess(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onlineImageAccess(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_domStorageAccess(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_domStorageAccess(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_imageAccess(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_imageAccess(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_mixedMode(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_mixedMode(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_zoomAccess(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_zoomAccess(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_geolocationAccess(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_geolocationAccess(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_javaScriptProxy(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_javaScriptProxy(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_password(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_password(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_cacheMode(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_cacheMode(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_darkMode(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_darkMode(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_forceDarkAccess(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_forceDarkAccess(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_mediaOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_mediaOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_tableData(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_tableData(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_wideViewModeAccess(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_wideViewModeAccess(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_overviewModeAccess(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_overviewModeAccess(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_overScrollMode(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_overScrollMode(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_textZoomAtio(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_textZoomAtio(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_textZoomRatio(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_textZoomRatio(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_databaseAccess(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_databaseAccess(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_initialScale(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_initialScale(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_userAgent(ptr: KPointer, value: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_userAgent(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_metaViewport(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_metaViewport(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onPageEnd(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onPageEnd(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onPageBegin(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onPageBegin(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onProgressChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onProgressChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onTitleReceive(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onTitleReceive(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onGeolocationHide(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onGeolocationHide(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onGeolocationShow(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onGeolocationShow(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onRequestSelected(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onRequestSelected(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onAlert(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onAlert(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onBeforeUnload(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onBeforeUnload(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onConfirm(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onConfirm(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onPrompt(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onPrompt(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onConsole(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onConsole(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onErrorReceive(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onErrorReceive(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onHttpErrorReceive(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onHttpErrorReceive(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onDownloadStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onDownloadStart(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onRefreshAccessedHistory(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onRefreshAccessedHistory(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onUrlLoadIntercept(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onUrlLoadIntercept(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onSslErrorReceive(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onSslErrorReceive(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onRenderExited0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onRenderExited0(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onRenderExited1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onRenderExited1(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onShowFileSelector(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onShowFileSelector(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onFileSelectorShow(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onFileSelectorShow(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onResourceLoad(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onResourceLoad(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onFullScreenExit(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onFullScreenExit(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onFullScreenEnter(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onFullScreenEnter(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onScaleChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onScaleChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onHttpAuthRequest(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onHttpAuthRequest(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onInterceptRequest(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onInterceptRequest(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onPermissionRequest(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onPermissionRequest(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onScreenCaptureRequest(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onScreenCaptureRequest(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onContextMenuShow(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onContextMenuShow(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onContextMenuHide(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onContextMenuHide(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_mediaPlayGestureAccess(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_mediaPlayGestureAccess(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onSearchResultReceive(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onSearchResultReceive(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onScroll(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onSslErrorEventReceive(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onSslErrorEventReceive(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onSslErrorEvent(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onSslErrorEvent(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onClientAuthenticationRequest(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onClientAuthenticationRequest(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onWindowNew(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onWindowNew(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onWindowExit(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onWindowExit(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_multiWindowAccess(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_multiWindowAccess(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onInterceptKeyEvent(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onInterceptKeyEvent(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_webStandardFont(ptr: KPointer, value: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_webStandardFont(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_webSerifFont(ptr: KPointer, value: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_webSerifFont(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_webSansSerifFont(ptr: KPointer, value: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_webSansSerifFont(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_webFixedFont(ptr: KPointer, value: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_webFixedFont(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_webFantasyFont(ptr: KPointer, value: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_webFantasyFont(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_webCursiveFont(ptr: KPointer, value: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_webCursiveFont(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_defaultFixedFontSize(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_defaultFixedFontSize(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_defaultFontSize(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_defaultFontSize(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_minFontSize(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_minFontSize(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_minLogicalFontSize(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_minLogicalFontSize(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_defaultTextEncodingFormat(ptr: KPointer, value: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_defaultTextEncodingFormat(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_forceDisplayScrollBar(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_forceDisplayScrollBar(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_blockNetwork(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_blockNetwork(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_horizontalScrollBarAccess(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_horizontalScrollBarAccess(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_verticalScrollBarAccess(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_verticalScrollBarAccess(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onTouchIconUrlReceived(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onTouchIconUrlReceived(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onFaviconReceived(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onFaviconReceived(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onPageVisible(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onPageVisible(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onDataResubmitted(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onDataResubmitted(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_pinchSmooth(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_pinchSmooth(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_allowWindowOpenMethod(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_allowWindowOpenMethod(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onAudioStateChanged(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onAudioStateChanged(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onFirstContentfulPaint(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onFirstContentfulPaint(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onFirstMeaningfulPaint(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onFirstMeaningfulPaint(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onLargestContentfulPaint(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onLargestContentfulPaint(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onLoadIntercept(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onLoadIntercept(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onControllerAttached(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onControllerAttached(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onOverScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onOverScroll(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onSafeBrowsingCheckResult(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onSafeBrowsingCheckResult(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onNavigationEntryCommitted(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onNavigationEntryCommitted(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onIntelligentTrackingPreventionResult(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onIntelligentTrackingPreventionResult(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_javaScriptOnDocumentStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_javaScriptOnDocumentStart(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_javaScriptOnDocumentEnd(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_javaScriptOnDocumentEnd(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_layoutMode(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_layoutMode(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_nestedScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_nestedScroll(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_enableNativeEmbedMode(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_enableNativeEmbedMode(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onNativeEmbedLifecycleChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onNativeEmbedLifecycleChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onNativeEmbedVisibilityChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onNativeEmbedVisibilityChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onNativeEmbedGestureEvent(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onNativeEmbedGestureEvent(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_copyOptions(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_copyOptions(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onOverrideUrlLoading(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onOverrideUrlLoading(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_textAutosizing(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_textAutosizing(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_enableNativeMediaPlayer(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_enableNativeMediaPlayer(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_enableSmoothDragResize(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_enableSmoothDragResize(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onRenderProcessNotResponding(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onRenderProcessNotResponding(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onRenderProcessResponding(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onRenderProcessResponding(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_selectionMenuOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_selectionMenuOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onViewportFitChanged(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onViewportFitChanged(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onInterceptKeyboardAttach(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onInterceptKeyboardAttach(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_onAdsBlocked(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_onAdsBlocked(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_keyboardAvoidMode(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_keyboardAvoidMode(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_editMenuOptions(ptr: KPointer, value: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_editMenuOptions(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_enableHapticFeedback(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_enableHapticFeedback(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_registerNativeEmbedRule(ptr: KPointer, tag: KStringPtr, type: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_registerNativeEmbedRule(ptr, tag, type)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_bindSelectionMenu(ptr: KPointer, elementType: KInt, thisArray: Uint8Array, thisLength: int32, responseType: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_bindSelectionMenu(ptr, elementType, thisArray, thisLength, responseType)
        }
        throw new Error("Not implemented")
    }
    static _WebAttribute_forceEnableZoom(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebAttribute_forceEnableZoom(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WindowScene_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._WindowScene_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _WindowSceneInterface_setWindowSceneOptions(ptr: KPointer, persistentId: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WindowSceneInterface_setWindowSceneOptions(ptr, persistentId)
        }
        throw new Error("Not implemented")
    }
    static _WindowSceneAttribute_attractionEffect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32, fraction: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WindowSceneAttribute_attractionEffect(ptr, thisArray, thisLength, fraction)
        }
        throw new Error("Not implemented")
    }
    static _XComponent_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._XComponent_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _XComponentInterface_setXComponentOptions0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._XComponentInterface_setXComponentOptions0(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _XComponentInterface_setXComponentOptions1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._XComponentInterface_setXComponentOptions1(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _XComponentInterface_setXComponentOptions2(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._XComponentInterface_setXComponentOptions2(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _XComponentAttribute_onLoad(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._XComponentAttribute_onLoad(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _XComponentAttribute_onDestroy(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._XComponentAttribute_onDestroy(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _XComponentAttribute_enableAnalyzer(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._XComponentAttribute_enableAnalyzer(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _XComponentAttribute_enableSecure(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._XComponentAttribute_enableSecure(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SideBarContainer_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._SideBarContainer_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _SideBarContainerInterface_setSideBarContainerOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SideBarContainerInterface_setSideBarContainerOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SideBarContainerAttribute_showSideBar(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SideBarContainerAttribute_showSideBar(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SideBarContainerAttribute_controlButton(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SideBarContainerAttribute_controlButton(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SideBarContainerAttribute_showControlButton(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SideBarContainerAttribute_showControlButton(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SideBarContainerAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SideBarContainerAttribute_onChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SideBarContainerAttribute_sideBarWidth0(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SideBarContainerAttribute_sideBarWidth0(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SideBarContainerAttribute_sideBarWidth1(ptr: KPointer, value: Length): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SideBarContainerAttribute_sideBarWidth1(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SideBarContainerAttribute_minSideBarWidth0(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SideBarContainerAttribute_minSideBarWidth0(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SideBarContainerAttribute_minSideBarWidth1(ptr: KPointer, value: Length): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SideBarContainerAttribute_minSideBarWidth1(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SideBarContainerAttribute_maxSideBarWidth0(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SideBarContainerAttribute_maxSideBarWidth0(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SideBarContainerAttribute_maxSideBarWidth1(ptr: KPointer, value: Length): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SideBarContainerAttribute_maxSideBarWidth1(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SideBarContainerAttribute_autoHide(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SideBarContainerAttribute_autoHide(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SideBarContainerAttribute_sideBarPosition(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SideBarContainerAttribute_sideBarPosition(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SideBarContainerAttribute_divider(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SideBarContainerAttribute_divider(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SideBarContainerAttribute_minContentWidth(ptr: KPointer, value: Length): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SideBarContainerAttribute_minContentWidth(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SideBarContainerAttribute__onChangeEvent_showSideBar(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SideBarContainerAttribute__onChangeEvent_showSideBar(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RemoteWindow_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._RemoteWindow_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _RemoteWindowInterface_setRemoteWindowOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RemoteWindowInterface_setRemoteWindowOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WaterFlow_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._WaterFlow_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _WaterFlowInterface_setWaterFlowOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WaterFlowInterface_setWaterFlowOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WaterFlowAttribute_columnsTemplate(ptr: KPointer, value: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WaterFlowAttribute_columnsTemplate(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WaterFlowAttribute_itemConstraintSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WaterFlowAttribute_itemConstraintSize(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WaterFlowAttribute_rowsTemplate(ptr: KPointer, value: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WaterFlowAttribute_rowsTemplate(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WaterFlowAttribute_columnsGap(ptr: KPointer, value: Length): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WaterFlowAttribute_columnsGap(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WaterFlowAttribute_rowsGap(ptr: KPointer, value: Length): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WaterFlowAttribute_rowsGap(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WaterFlowAttribute_layoutDirection(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WaterFlowAttribute_layoutDirection(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WaterFlowAttribute_nestedScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WaterFlowAttribute_nestedScroll(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WaterFlowAttribute_enableScrollInteraction(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WaterFlowAttribute_enableScrollInteraction(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WaterFlowAttribute_friction(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WaterFlowAttribute_friction(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WaterFlowAttribute_cachedCount0(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WaterFlowAttribute_cachedCount0(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _WaterFlowAttribute_cachedCount1(ptr: KPointer, count: number, show: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WaterFlowAttribute_cachedCount1(ptr, count, show)
        }
        throw new Error("Not implemented")
    }
    static _WaterFlowAttribute_onReachStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WaterFlowAttribute_onReachStart(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WaterFlowAttribute_onReachEnd(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WaterFlowAttribute_onReachEnd(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WaterFlowAttribute_onScrollFrameBegin(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WaterFlowAttribute_onScrollFrameBegin(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WaterFlowAttribute_onScrollIndex(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WaterFlowAttribute_onScrollIndex(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _UIExtensionComponent_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._UIExtensionComponent_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _UIExtensionComponentInterface_setUIExtensionComponentOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._UIExtensionComponentInterface_setUIExtensionComponentOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _UIExtensionComponentAttribute_onRemoteReady(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._UIExtensionComponentAttribute_onRemoteReady(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _UIExtensionComponentAttribute_onReceive(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._UIExtensionComponentAttribute_onReceive(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _UIExtensionComponentAttribute_onResult(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._UIExtensionComponentAttribute_onResult(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _UIExtensionComponentAttribute_onRelease(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._UIExtensionComponentAttribute_onRelease(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _UIExtensionComponentAttribute_onError(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._UIExtensionComponentAttribute_onError(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _UIExtensionComponentAttribute_onTerminated(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._UIExtensionComponentAttribute_onTerminated(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _LinearIndicator_construct(id: KInt, flags: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._LinearIndicator_construct(id, flags)
        }
        throw new Error("Not implemented")
    }
    static _LinearIndicatorInterface_setLinearIndicatorOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._LinearIndicatorInterface_setLinearIndicatorOptions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _LinearIndicatorAttribute_indicatorStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._LinearIndicatorAttribute_indicatorStyle(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _LinearIndicatorAttribute_indicatorLoop(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._LinearIndicatorAttribute_indicatorLoop(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _LinearIndicatorAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._LinearIndicatorAttribute_onChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _AnimationExtender_SetClipRect(node: KPointer, x: KFloat, y: KFloat, width: KFloat, height: KFloat): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AnimationExtender_SetClipRect(node, x, y, width, height)
        }
        throw new Error("Not implemented")
    }
    static _AnimationExtender_OpenImplicitAnimation(thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AnimationExtender_OpenImplicitAnimation(thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _AnimationExtender_CloseImplicitAnimation(): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AnimationExtender_CloseImplicitAnimation()
        }
        throw new Error("Not implemented")
    }
    static _AnimationExtender_StartDoubleAnimation(node: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AnimationExtender_StartDoubleAnimation(node, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _AnimationExtender_AnimationTranslate(node: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AnimationExtender_AnimationTranslate(node, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _UnifiedData_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._UnifiedData_ctor()
        }
        throw new Error("Not implemented")
    }
    static _UnifiedData_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._UnifiedData_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _UnifiedData_hasType(ptr: KPointer, UnifiedData_type: KStringPtr): boolean {
        if ((this._LoadOnce()) == (true))
        {
            return this._UnifiedData_hasType(ptr, UnifiedData_type)
        }
        throw new Error("Not implemented")
    }
    static _UnifiedData_getTypes(ptr: KPointer): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._UnifiedData_getTypes(ptr)
        }
        throw new Error("Not implemented")
    }
    static _LazyForEachOps_NeedMoreElements(node: KPointer, mark: KPointer, direction: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._LazyForEachOps_NeedMoreElements(node, mark, direction)
        }
        throw new Error("Not implemented")
    }
    static _LazyForEachOps_OnRangeUpdate(node: KPointer, totalCount: KInt, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._LazyForEachOps_OnRangeUpdate(node, totalCount, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _LazyForEachOps_SetCurrentIndex(node: KPointer, index: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._LazyForEachOps_SetCurrentIndex(node, index)
        }
        throw new Error("Not implemented")
    }
    static _LazyForEachOps_Prepare(node: KPointer, itemCount: KInt, offset: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._LazyForEachOps_Prepare(node, itemCount, offset)
        }
        throw new Error("Not implemented")
    }
    static _LazyForEachOps_NotifyChange(node: KPointer, startIndex: KInt, endIndex: KInt, count: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._LazyForEachOps_NotifyChange(node, startIndex, endIndex, count)
        }
        throw new Error("Not implemented")
    }
    static _SystemOps_StartFrame(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._SystemOps_StartFrame()
        }
        throw new Error("Not implemented")
    }
    static _SystemOps_EndFrame(root: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SystemOps_EndFrame(root)
        }
        throw new Error("Not implemented")
    }
    static _SystemOps_syncInstanceId(instanceId: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SystemOps_syncInstanceId(instanceId)
        }
        throw new Error("Not implemented")
    }
    static _SystemOps_restoreInstanceId(): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SystemOps_restoreInstanceId()
        }
        throw new Error("Not implemented")
    }
    static _DrawingCanvas_ctor(pixelmap: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._DrawingCanvas_ctor(pixelmap)
        }
        throw new Error("Not implemented")
    }
    static _DrawingCanvas_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._DrawingCanvas_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _DrawingCanvas_drawRect(ptr: KPointer, left: number, top: number, right: number, bottom: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._DrawingCanvas_drawRect(ptr, left, top, right, bottom)
        }
        throw new Error("Not implemented")
    }
    static _LengthMetrics_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._LengthMetrics_ctor()
        }
        throw new Error("Not implemented")
    }
    static _LengthMetrics_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._LengthMetrics_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _LengthMetrics_px(value: number): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._LengthMetrics_px(value)
        }
        throw new Error("Not implemented")
    }
    static _LengthMetrics_vp(value: number): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._LengthMetrics_vp(value)
        }
        throw new Error("Not implemented")
    }
    static _LengthMetrics_fp(value: number): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._LengthMetrics_fp(value)
        }
        throw new Error("Not implemented")
    }
    static _LengthMetrics_percent(value: number): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._LengthMetrics_percent(value)
        }
        throw new Error("Not implemented")
    }
    static _LengthMetrics_lpx(value: number): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._LengthMetrics_lpx(value)
        }
        throw new Error("Not implemented")
    }
    static _LengthMetrics_resource(thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._LengthMetrics_resource(thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _LengthMetrics_getUnit(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._LengthMetrics_getUnit(ptr)
        }
        throw new Error("Not implemented")
    }
    static _LengthMetrics_setUnit(ptr: KPointer, unit: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._LengthMetrics_setUnit(ptr, unit)
        }
        throw new Error("Not implemented")
    }
    static _LengthMetrics_getValue(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._LengthMetrics_getValue(ptr)
        }
        throw new Error("Not implemented")
    }
    static _LengthMetrics_setValue(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._LengthMetrics_setValue(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ColorMetrics_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ColorMetrics_ctor()
        }
        throw new Error("Not implemented")
    }
    static _ColorMetrics_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ColorMetrics_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _ColorMetrics_numeric(value: number): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ColorMetrics_numeric(value)
        }
        throw new Error("Not implemented")
    }
    static _ColorMetrics_rgba(red: number, green: number, blue: number, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ColorMetrics_rgba(red, green, blue, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ColorMetrics_resourceColor(thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ColorMetrics_resourceColor(thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ColorMetrics_blendColor(ptr: KPointer, overlayColor: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ColorMetrics_blendColor(ptr, overlayColor)
        }
        throw new Error("Not implemented")
    }
    static _ColorMetrics_getColor(ptr: KPointer): string {
        if ((this._LoadOnce()) == (true))
        {
            return this._ColorMetrics_getColor(ptr)
        }
        throw new Error("Not implemented")
    }
    static _ColorMetrics_getRed(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._ColorMetrics_getRed(ptr)
        }
        throw new Error("Not implemented")
    }
    static _ColorMetrics_getGreen(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._ColorMetrics_getGreen(ptr)
        }
        throw new Error("Not implemented")
    }
    static _ColorMetrics_getBlue(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._ColorMetrics_getBlue(ptr)
        }
        throw new Error("Not implemented")
    }
    static _ColorMetrics_getAlpha(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._ColorMetrics_getAlpha(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebviewController_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebviewController_ctor()
        }
        throw new Error("Not implemented")
    }
    static _WebviewController_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebviewController_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _WebviewController_initializeWebEngine(): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebviewController_initializeWebEngine()
        }
        throw new Error("Not implemented")
    }
    static _WebviewController_loadUrl(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebviewController_loadUrl(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GlobalScope_ohos_arkui_componentSnapshot_get(id: KStringPtr, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GlobalScope_ohos_arkui_componentSnapshot_get(id, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GlobalScope_ohos_arkui_performanceMonitor_begin(scene: KStringPtr, startInputType: KInt, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GlobalScope_ohos_arkui_performanceMonitor_begin(scene, startInputType, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GlobalScope_ohos_arkui_performanceMonitor_end(scene: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GlobalScope_ohos_arkui_performanceMonitor_end(scene)
        }
        throw new Error("Not implemented")
    }
    static _GlobalScope_ohos_arkui_performanceMonitor_recordInputEventTime(actionType: KInt, sourceType: KInt, time: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GlobalScope_ohos_arkui_performanceMonitor_recordInputEventTime(actionType, sourceType, time)
        }
        throw new Error("Not implemented")
    }
    static _CommonShape_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonShape_ctor()
        }
        throw new Error("Not implemented")
    }
    static _CommonShape_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonShape_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _CommonShape_offset(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonShape_offset(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonShape_fill(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonShape_fill(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CommonShape_position(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CommonShape_position(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _BaseShape_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._BaseShape_ctor()
        }
        throw new Error("Not implemented")
    }
    static _BaseShape_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._BaseShape_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _BaseShape_width(ptr: KPointer, width: Length): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._BaseShape_width(ptr, width)
        }
        throw new Error("Not implemented")
    }
    static _BaseShape_height(ptr: KPointer, height: Length): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._BaseShape_height(ptr, height)
        }
        throw new Error("Not implemented")
    }
    static _BaseShape_size(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._BaseShape_size(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RectShape_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._RectShape_ctor(thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RectShape_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._RectShape_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _RectShape_offset(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._RectShape_offset(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RectShape_fill(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._RectShape_fill(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RectShape_position(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._RectShape_position(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RectShape_width(ptr: KPointer, width: Length): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._RectShape_width(ptr, width)
        }
        throw new Error("Not implemented")
    }
    static _RectShape_height(ptr: KPointer, height: Length): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._RectShape_height(ptr, height)
        }
        throw new Error("Not implemented")
    }
    static _RectShape_size(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._RectShape_size(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RectShape_radiusWidth(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._RectShape_radiusWidth(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RectShape_radiusHeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._RectShape_radiusHeight(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RectShape_radius(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._RectShape_radius(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CircleShape_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CircleShape_ctor(thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CircleShape_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CircleShape_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _CircleShape_offset(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CircleShape_offset(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CircleShape_fill(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CircleShape_fill(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CircleShape_position(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CircleShape_position(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CircleShape_width(ptr: KPointer, width: Length): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CircleShape_width(ptr, width)
        }
        throw new Error("Not implemented")
    }
    static _CircleShape_height(ptr: KPointer, height: Length): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CircleShape_height(ptr, height)
        }
        throw new Error("Not implemented")
    }
    static _CircleShape_size(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CircleShape_size(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _EllipseShape_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._EllipseShape_ctor(thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _EllipseShape_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._EllipseShape_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _EllipseShape_offset(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._EllipseShape_offset(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _EllipseShape_fill(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._EllipseShape_fill(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _EllipseShape_position(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._EllipseShape_position(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _EllipseShape_width(ptr: KPointer, width: Length): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._EllipseShape_width(ptr, width)
        }
        throw new Error("Not implemented")
    }
    static _EllipseShape_height(ptr: KPointer, height: Length): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._EllipseShape_height(ptr, height)
        }
        throw new Error("Not implemented")
    }
    static _EllipseShape_size(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._EllipseShape_size(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _PathShape_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._PathShape_ctor(thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _PathShape_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._PathShape_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _PathShape_offset(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._PathShape_offset(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _PathShape_fill(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._PathShape_fill(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _PathShape_position(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._PathShape_position(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _PathShape_commands(ptr: KPointer, commands: KStringPtr): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._PathShape_commands(ptr, commands)
        }
        throw new Error("Not implemented")
    }
    static _GlobalScope_ohos_font_registerFont(thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GlobalScope_ohos_font_registerFont(thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GlobalScope_ohos_font_getSystemFontList(): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._GlobalScope_ohos_font_getSystemFontList()
        }
        throw new Error("Not implemented")
    }
    static _ScaleSymbolEffect_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScaleSymbolEffect_ctor(thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ScaleSymbolEffect_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScaleSymbolEffect_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _ScaleSymbolEffect_getScope(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScaleSymbolEffect_getScope(ptr)
        }
        throw new Error("Not implemented")
    }
    static _ScaleSymbolEffect_setScope(ptr: KPointer, scope: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScaleSymbolEffect_setScope(ptr, scope)
        }
        throw new Error("Not implemented")
    }
    static _ScaleSymbolEffect_getDirection(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScaleSymbolEffect_getDirection(ptr)
        }
        throw new Error("Not implemented")
    }
    static _ScaleSymbolEffect_setDirection(ptr: KPointer, direction: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScaleSymbolEffect_setDirection(ptr, direction)
        }
        throw new Error("Not implemented")
    }
    static _ReplaceSymbolEffect_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ReplaceSymbolEffect_ctor(thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ReplaceSymbolEffect_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ReplaceSymbolEffect_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _ReplaceSymbolEffect_getScope(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ReplaceSymbolEffect_getScope(ptr)
        }
        throw new Error("Not implemented")
    }
    static _ReplaceSymbolEffect_setScope(ptr: KPointer, scope: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ReplaceSymbolEffect_setScope(ptr, scope)
        }
        throw new Error("Not implemented")
    }
    static _FrameNode_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._FrameNode_ctor(thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _FrameNode_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._FrameNode_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _FrameNode_isModifiable(ptr: KPointer): boolean {
        if ((this._LoadOnce()) == (true))
        {
            return this._FrameNode_isModifiable(ptr)
        }
        throw new Error("Not implemented")
    }
    static _FrameNode_appendChild(ptr: KPointer, node: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._FrameNode_appendChild(ptr, node)
        }
        throw new Error("Not implemented")
    }
    static _FrameNode_insertChildAfter(ptr: KPointer, child: KPointer, sibling: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._FrameNode_insertChildAfter(ptr, child, sibling)
        }
        throw new Error("Not implemented")
    }
    static _FrameNode_removeChild(ptr: KPointer, node: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._FrameNode_removeChild(ptr, node)
        }
        throw new Error("Not implemented")
    }
    static _FrameNode_clearChildren(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._FrameNode_clearChildren(ptr)
        }
        throw new Error("Not implemented")
    }
    static _FrameNode_getChild(ptr: KPointer, index: number): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._FrameNode_getChild(ptr, index)
        }
        throw new Error("Not implemented")
    }
    static _FrameNode_getFirstChild(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._FrameNode_getFirstChild(ptr)
        }
        throw new Error("Not implemented")
    }
    static _FrameNode_getNextSibling(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._FrameNode_getNextSibling(ptr)
        }
        throw new Error("Not implemented")
    }
    static _FrameNode_getPreviousSibling(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._FrameNode_getPreviousSibling(ptr)
        }
        throw new Error("Not implemented")
    }
    static _FrameNode_getParent(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._FrameNode_getParent(ptr)
        }
        throw new Error("Not implemented")
    }
    static _FrameNode_getChildrenCount(ptr: KPointer): int32 {
        if ((this._LoadOnce()) == (true))
        {
            return this._FrameNode_getChildrenCount(ptr)
        }
        throw new Error("Not implemented")
    }
    static _FrameNode_dispose(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._FrameNode_dispose(ptr)
        }
        throw new Error("Not implemented")
    }
    static _FrameNode_getOpacity(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._FrameNode_getOpacity(ptr)
        }
        throw new Error("Not implemented")
    }
    static _FrameNode_getPositionToWindowWithTransform(ptr: KPointer): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._FrameNode_getPositionToWindowWithTransform(ptr)
        }
        throw new Error("Not implemented")
    }
    static _FrameNode_getFrameNodeByKey(name: KStringPtr): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._FrameNode_getFrameNodeByKey(name)
        }
        throw new Error("Not implemented")
    }
    static _FrameNode_reuse(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._FrameNode_reuse(ptr)
        }
        throw new Error("Not implemented")
    }
    static _FrameNode_recycle(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._FrameNode_recycle(ptr)
        }
        throw new Error("Not implemented")
    }
    static _PixelMap_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._PixelMap_ctor()
        }
        throw new Error("Not implemented")
    }
    static _PixelMap_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._PixelMap_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _PixelMap_readPixelsToBufferSync(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PixelMap_readPixelsToBufferSync(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _PixelMap_writeBufferToPixels(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PixelMap_writeBufferToPixels(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _PixelMap_getIsEditable(ptr: KPointer): boolean {
        if ((this._LoadOnce()) == (true))
        {
            return this._PixelMap_getIsEditable(ptr)
        }
        throw new Error("Not implemented")
    }
    static _PixelMap_getIsStrideAlignment(ptr: KPointer): boolean {
        if ((this._LoadOnce()) == (true))
        {
            return this._PixelMap_getIsStrideAlignment(ptr)
        }
        throw new Error("Not implemented")
    }
    static _NavExtender_setUpdateStackCallback(peer: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavExtender_setUpdateStackCallback(peer, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavExtender_syncStack(peer: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavExtender_syncStack(peer)
        }
        throw new Error("Not implemented")
    }
    static _NavExtender_checkNeedCreate(navigation: KPointer, index: int32): boolean {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavExtender_checkNeedCreate(navigation, index)
        }
        throw new Error("Not implemented")
    }
    static _NavExtender_navigationCreate(peer: KInt, flag: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavExtender_navigationCreate(peer, flag)
        }
        throw new Error("Not implemented")
    }
    static _NavExtender_setNavigationOptions(navigation: KPointer, stack: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavExtender_setNavigationOptions(navigation, stack)
        }
        throw new Error("Not implemented")
    }
    static _NavExtender_setNavDestinationNode(peer: KPointer, index: KInt, node: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavExtender_setNavDestinationNode(peer, index, node)
        }
        throw new Error("Not implemented")
    }
    static _EventEmulator_emitClickEvent(node: KPointer, event: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._EventEmulator_emitClickEvent(node, event)
        }
        throw new Error("Not implemented")
    }
    static _EventEmulator_emitTextInputEvent(node: KPointer, text: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._EventEmulator_emitTextInputEvent(node, text)
        }
        throw new Error("Not implemented")
    }
    static _ActionSheet_show(thisArray: Uint8Array, thisLength: int32): undefined {
        if ((this._LoadOnce()) == (true))
        {
            return this._ActionSheet_show(thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _AlertDialog_show(thisArray: Uint8Array, thisLength: int32): undefined {
        if ((this._LoadOnce()) == (true))
        {
            return this._AlertDialog_show(thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SpringProp_ctor(mass: number, stiffness: number, damping: number): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._SpringProp_ctor(mass, stiffness, damping)
        }
        throw new Error("Not implemented")
    }
    static _SpringProp_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._SpringProp_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _SpringMotion_ctor(start: number, end: number, velocity: number, prop: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._SpringMotion_ctor(start, end, velocity, prop)
        }
        throw new Error("Not implemented")
    }
    static _SpringMotion_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._SpringMotion_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _FrictionMotion_ctor(friction: number, position: number, velocity: number): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._FrictionMotion_ctor(friction, position, velocity)
        }
        throw new Error("Not implemented")
    }
    static _FrictionMotion_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._FrictionMotion_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _ScrollMotion_ctor(position: number, velocity: number, min: number, max: number, prop: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScrollMotion_ctor(position, velocity, min, max, prop)
        }
        throw new Error("Not implemented")
    }
    static _ScrollMotion_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScrollMotion_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _CalendarController_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CalendarController_ctor()
        }
        throw new Error("Not implemented")
    }
    static _CalendarController_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CalendarController_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _CalendarController_backToToday(ptr: KPointer): undefined {
        if ((this._LoadOnce()) == (true))
        {
            return this._CalendarController_backToToday(ptr)
        }
        throw new Error("Not implemented")
    }
    static _CalendarController_goTo(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): undefined {
        if ((this._LoadOnce()) == (true))
        {
            return this._CalendarController_goTo(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CalendarPickerDialog_show(thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CalendarPickerDialog_show(thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CanvasGradient_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasGradient_ctor()
        }
        throw new Error("Not implemented")
    }
    static _CanvasGradient_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasGradient_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _CanvasGradient_addColorStop(ptr: KPointer, offset: number, color: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasGradient_addColorStop(ptr, offset, color)
        }
        throw new Error("Not implemented")
    }
    static _CanvasPath_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasPath_ctor()
        }
        throw new Error("Not implemented")
    }
    static _CanvasPath_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasPath_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _CanvasPath_arc(ptr: KPointer, x: number, y: number, radius: number, startAngle: number, endAngle: number, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasPath_arc(ptr, x, y, radius, startAngle, endAngle, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CanvasPath_arcTo(ptr: KPointer, x1: number, y1: number, x2: number, y2: number, radius: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasPath_arcTo(ptr, x1, y1, x2, y2, radius)
        }
        throw new Error("Not implemented")
    }
    static _CanvasPath_bezierCurveTo(ptr: KPointer, cp1x: number, cp1y: number, cp2x: number, cp2y: number, x: number, y: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasPath_bezierCurveTo(ptr, cp1x, cp1y, cp2x, cp2y, x, y)
        }
        throw new Error("Not implemented")
    }
    static _CanvasPath_closePath(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasPath_closePath(ptr)
        }
        throw new Error("Not implemented")
    }
    static _CanvasPath_ellipse(ptr: KPointer, x: number, y: number, radiusX: number, radiusY: number, rotation: number, startAngle: number, endAngle: number, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasPath_ellipse(ptr, x, y, radiusX, radiusY, rotation, startAngle, endAngle, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CanvasPath_lineTo(ptr: KPointer, x: number, y: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasPath_lineTo(ptr, x, y)
        }
        throw new Error("Not implemented")
    }
    static _CanvasPath_moveTo(ptr: KPointer, x: number, y: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasPath_moveTo(ptr, x, y)
        }
        throw new Error("Not implemented")
    }
    static _CanvasPath_quadraticCurveTo(ptr: KPointer, cpx: number, cpy: number, x: number, y: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasPath_quadraticCurveTo(ptr, cpx, cpy, x, y)
        }
        throw new Error("Not implemented")
    }
    static _CanvasPath_rect(ptr: KPointer, x: number, y: number, w: number, h: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasPath_rect(ptr, x, y, w, h)
        }
        throw new Error("Not implemented")
    }
    static _Path2D_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Path2D_ctor()
        }
        throw new Error("Not implemented")
    }
    static _Path2D_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Path2D_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _Path2D_addPath(ptr: KPointer, path: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._Path2D_addPath(ptr, path, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CanvasPattern_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasPattern_ctor()
        }
        throw new Error("Not implemented")
    }
    static _CanvasPattern_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasPattern_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _CanvasPattern_setTransform(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasPattern_setTransform(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ImageBitmap_ctor(src: KStringPtr): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageBitmap_ctor(src)
        }
        throw new Error("Not implemented")
    }
    static _ImageBitmap_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageBitmap_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _ImageBitmap_close(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageBitmap_close(ptr)
        }
        throw new Error("Not implemented")
    }
    static _ImageBitmap_getHeight(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageBitmap_getHeight(ptr)
        }
        throw new Error("Not implemented")
    }
    static _ImageBitmap_getWidth(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageBitmap_getWidth(ptr)
        }
        throw new Error("Not implemented")
    }
    static _ImageData_ctor(width: number, height: number, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageData_ctor(width, height, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ImageData_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageData_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _ImageData_getHeight(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageData_getHeight(ptr)
        }
        throw new Error("Not implemented")
    }
    static _ImageData_getWidth(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageData_getWidth(ptr)
        }
        throw new Error("Not implemented")
    }
    static _RenderingContextSettings_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._RenderingContextSettings_ctor(thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RenderingContextSettings_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._RenderingContextSettings_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _RenderingContextSettings_getAntialias(ptr: KPointer): boolean {
        if ((this._LoadOnce()) == (true))
        {
            return this._RenderingContextSettings_getAntialias(ptr)
        }
        throw new Error("Not implemented")
    }
    static _RenderingContextSettings_setAntialias(ptr: KPointer, antialias: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RenderingContextSettings_setAntialias(ptr, antialias)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_ctor()
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_drawImage0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32, dx: number, dy: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_drawImage0(ptr, thisArray, thisLength, dx, dy)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_drawImage1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32, dx: number, dy: number, dw: number, dh: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_drawImage1(ptr, thisArray, thisLength, dx, dy, dw, dh)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_drawImage2(ptr: KPointer, thisArray: Uint8Array, thisLength: int32, sx: number, sy: number, sw: number, sh: number, dx: number, dy: number, dw: number, dh: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_drawImage2(ptr, thisArray, thisLength, sx, sy, sw, sh, dx, dy, dw, dh)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_beginPath(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_beginPath(ptr)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_clip0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_clip0(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_clip1(ptr: KPointer, path: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_clip1(ptr, path, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_fill0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_fill0(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_fill1(ptr: KPointer, path: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_fill1(ptr, path, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_stroke0(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_stroke0(ptr)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_stroke1(ptr: KPointer, path: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_stroke1(ptr, path)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_createLinearGradient(ptr: KPointer, x0: number, y0: number, x1: number, y1: number): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_createLinearGradient(ptr, x0, y0, x1, y1)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_createPattern(ptr: KPointer, image: KPointer, thisArray: Uint8Array, thisLength: int32): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_createPattern(ptr, image, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_createRadialGradient(ptr: KPointer, x0: number, y0: number, r0: number, x1: number, y1: number, r1: number): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_createRadialGradient(ptr, x0, y0, r0, x1, y1, r1)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_createConicGradient(ptr: KPointer, startAngle: number, x: number, y: number): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_createConicGradient(ptr, startAngle, x, y)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_createImageData0(ptr: KPointer, sw: number, sh: number): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_createImageData0(ptr, sw, sh)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_createImageData1(ptr: KPointer, imagedata: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_createImageData1(ptr, imagedata)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_getImageData(ptr: KPointer, sx: number, sy: number, sw: number, sh: number): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_getImageData(ptr, sx, sy, sw, sh)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_getPixelMap(ptr: KPointer, sx: number, sy: number, sw: number, sh: number): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_getPixelMap(ptr, sx, sy, sw, sh)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_putImageData0(ptr: KPointer, imagedata: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_putImageData0(ptr, imagedata, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_putImageData1(ptr: KPointer, imagedata: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_putImageData1(ptr, imagedata, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_getLineDash(ptr: KPointer): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_getLineDash(ptr)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_setLineDash(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_setLineDash(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_clearRect(ptr: KPointer, x: number, y: number, w: number, h: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_clearRect(ptr, x, y, w, h)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_fillRect(ptr: KPointer, x: number, y: number, w: number, h: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_fillRect(ptr, x, y, w, h)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_strokeRect(ptr: KPointer, x: number, y: number, w: number, h: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_strokeRect(ptr, x, y, w, h)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_restore(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_restore(ptr)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_save(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_save(ptr)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_fillText(ptr: KPointer, text: KStringPtr, x: number, y: number, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_fillText(ptr, text, x, y, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_measureText(ptr: KPointer, text: KStringPtr): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_measureText(ptr, text)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_strokeText(ptr: KPointer, text: KStringPtr, x: number, y: number, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_strokeText(ptr, text, x, y, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_getTransform(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_getTransform(ptr)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_resetTransform(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_resetTransform(ptr)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_rotate(ptr: KPointer, angle: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_rotate(ptr, angle)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_scale(ptr: KPointer, x: number, y: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_scale(ptr, x, y)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_setTransform0(ptr: KPointer, a: number, b: number, c: number, d: number, e: number, f: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_setTransform0(ptr, a, b, c, d, e, f)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_setTransform1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_setTransform1(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_transform(ptr: KPointer, a: number, b: number, c: number, d: number, e: number, f: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_transform(ptr, a, b, c, d, e, f)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_translate(ptr: KPointer, x: number, y: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_translate(ptr, x, y)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_setPixelMap(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_setPixelMap(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_transferFromImageBitmap(ptr: KPointer, bitmap: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_transferFromImageBitmap(ptr, bitmap)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_saveLayer(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_saveLayer(ptr)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_restoreLayer(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_restoreLayer(ptr)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_reset(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_reset(ptr)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_getGlobalAlpha(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_getGlobalAlpha(ptr)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_setGlobalAlpha(ptr: KPointer, globalAlpha: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_setGlobalAlpha(ptr, globalAlpha)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_getGlobalCompositeOperation(ptr: KPointer): string {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_getGlobalCompositeOperation(ptr)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_setGlobalCompositeOperation(ptr: KPointer, globalCompositeOperation: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_setGlobalCompositeOperation(ptr, globalCompositeOperation)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_setFillStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_setFillStyle(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_setStrokeStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_setStrokeStyle(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_getFilter(ptr: KPointer): string {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_getFilter(ptr)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_setFilter(ptr: KPointer, filter: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_setFilter(ptr, filter)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_getImageSmoothingEnabled(ptr: KPointer): boolean {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_getImageSmoothingEnabled(ptr)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_setImageSmoothingEnabled(ptr: KPointer, imageSmoothingEnabled: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_setImageSmoothingEnabled(ptr, imageSmoothingEnabled)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_getImageSmoothingQuality(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_getImageSmoothingQuality(ptr)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_setImageSmoothingQuality(ptr: KPointer, imageSmoothingQuality: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_setImageSmoothingQuality(ptr, imageSmoothingQuality)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_getLineCap(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_getLineCap(ptr)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_setLineCap(ptr: KPointer, lineCap: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_setLineCap(ptr, lineCap)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_getLineDashOffset(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_getLineDashOffset(ptr)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_setLineDashOffset(ptr: KPointer, lineDashOffset: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_setLineDashOffset(ptr, lineDashOffset)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_getLineJoin(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_getLineJoin(ptr)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_setLineJoin(ptr: KPointer, lineJoin: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_setLineJoin(ptr, lineJoin)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_getLineWidth(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_getLineWidth(ptr)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_setLineWidth(ptr: KPointer, lineWidth: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_setLineWidth(ptr, lineWidth)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_getMiterLimit(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_getMiterLimit(ptr)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_setMiterLimit(ptr: KPointer, miterLimit: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_setMiterLimit(ptr, miterLimit)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_getShadowBlur(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_getShadowBlur(ptr)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_setShadowBlur(ptr: KPointer, shadowBlur: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_setShadowBlur(ptr, shadowBlur)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_getShadowColor(ptr: KPointer): string {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_getShadowColor(ptr)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_setShadowColor(ptr: KPointer, shadowColor: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_setShadowColor(ptr, shadowColor)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_getShadowOffsetX(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_getShadowOffsetX(ptr)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_setShadowOffsetX(ptr: KPointer, shadowOffsetX: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_setShadowOffsetX(ptr, shadowOffsetX)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_getShadowOffsetY(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_getShadowOffsetY(ptr)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_setShadowOffsetY(ptr: KPointer, shadowOffsetY: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_setShadowOffsetY(ptr, shadowOffsetY)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_getDirection(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_getDirection(ptr)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_setDirection(ptr: KPointer, direction: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_setDirection(ptr, direction)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_getFont(ptr: KPointer): string {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_getFont(ptr)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_setFont(ptr: KPointer, font: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_setFont(ptr, font)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_getTextAlign(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_getTextAlign(ptr)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_setTextAlign(ptr: KPointer, textAlign: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_setTextAlign(ptr, textAlign)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_getTextBaseline(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_getTextBaseline(ptr)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderer_setTextBaseline(ptr: KPointer, textBaseline: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderer_setTextBaseline(ptr, textBaseline)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderingContext2D_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderingContext2D_ctor(thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderingContext2D_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderingContext2D_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderingContext2D_toDataURL(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): string {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderingContext2D_toDataURL(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderingContext2D_startImageAnalyzer(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderingContext2D_startImageAnalyzer(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderingContext2D_stopImageAnalyzer(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderingContext2D_stopImageAnalyzer(ptr)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderingContext2D_onOnAttach(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderingContext2D_onOnAttach(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderingContext2D_offOnAttach(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderingContext2D_offOnAttach(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderingContext2D_onOnDetach(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderingContext2D_onOnDetach(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderingContext2D_offOnDetach(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderingContext2D_offOnDetach(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderingContext2D_getHeight(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderingContext2D_getHeight(ptr)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderingContext2D_getWidth(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderingContext2D_getWidth(ptr)
        }
        throw new Error("Not implemented")
    }
    static _CanvasRenderingContext2D_getCanvas(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CanvasRenderingContext2D_getCanvas(ptr)
        }
        throw new Error("Not implemented")
    }
    static _OffscreenCanvasRenderingContext2D_ctor(width: number, height: number, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._OffscreenCanvasRenderingContext2D_ctor(width, height, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _OffscreenCanvasRenderingContext2D_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._OffscreenCanvasRenderingContext2D_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _OffscreenCanvasRenderingContext2D_toDataURL(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): string {
        if ((this._LoadOnce()) == (true))
        {
            return this._OffscreenCanvasRenderingContext2D_toDataURL(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _OffscreenCanvasRenderingContext2D_transferToImageBitmap(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._OffscreenCanvasRenderingContext2D_transferToImageBitmap(ptr)
        }
        throw new Error("Not implemented")
    }
    static _OffscreenCanvas_ctor(width: number, height: number): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._OffscreenCanvas_ctor(width, height)
        }
        throw new Error("Not implemented")
    }
    static _OffscreenCanvas_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._OffscreenCanvas_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _OffscreenCanvas_transferToImageBitmap(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._OffscreenCanvas_transferToImageBitmap(ptr)
        }
        throw new Error("Not implemented")
    }
    static _OffscreenCanvas_getContext2d(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._OffscreenCanvas_getContext2d(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _OffscreenCanvas_getHeight(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._OffscreenCanvas_getHeight(ptr)
        }
        throw new Error("Not implemented")
    }
    static _OffscreenCanvas_setHeight(ptr: KPointer, height: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._OffscreenCanvas_setHeight(ptr, height)
        }
        throw new Error("Not implemented")
    }
    static _OffscreenCanvas_getWidth(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._OffscreenCanvas_getWidth(ptr)
        }
        throw new Error("Not implemented")
    }
    static _OffscreenCanvas_setWidth(ptr: KPointer, width: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._OffscreenCanvas_setWidth(ptr, width)
        }
        throw new Error("Not implemented")
    }
    static _DrawingRenderingContext_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._DrawingRenderingContext_ctor(thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _DrawingRenderingContext_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._DrawingRenderingContext_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _DrawingRenderingContext_invalidate(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._DrawingRenderingContext_invalidate(ptr)
        }
        throw new Error("Not implemented")
    }
    static _DrawingRenderingContext_getCanvas(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._DrawingRenderingContext_getCanvas(ptr)
        }
        throw new Error("Not implemented")
    }
    static _ICurve_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ICurve_ctor()
        }
        throw new Error("Not implemented")
    }
    static _ICurve_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ICurve_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _ICurve_interpolate(ptr: KPointer, fraction: number): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._ICurve_interpolate(ptr, fraction)
        }
        throw new Error("Not implemented")
    }
    static _DrawModifier_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._DrawModifier_ctor()
        }
        throw new Error("Not implemented")
    }
    static _DrawModifier_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._DrawModifier_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _DrawModifier_drawBehind(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._DrawModifier_drawBehind(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _DrawModifier_drawContent(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._DrawModifier_drawContent(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _DrawModifier_drawFront(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._DrawModifier_drawFront(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _DrawModifier_invalidate(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._DrawModifier_invalidate(ptr)
        }
        throw new Error("Not implemented")
    }
    static _TransitionEffect_ctor(type: KStringPtr, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TransitionEffect_ctor(type, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TransitionEffect_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TransitionEffect_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _TransitionEffect_translate(thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TransitionEffect_translate(thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TransitionEffect_rotate(thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TransitionEffect_rotate(thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TransitionEffect_scale(thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TransitionEffect_scale(thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TransitionEffect_opacity(alpha: number): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TransitionEffect_opacity(alpha)
        }
        throw new Error("Not implemented")
    }
    static _TransitionEffect_move(edge: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TransitionEffect_move(edge)
        }
        throw new Error("Not implemented")
    }
    static _TransitionEffect_asymmetric(appear: KPointer, disappear: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TransitionEffect_asymmetric(appear, disappear)
        }
        throw new Error("Not implemented")
    }
    static _TransitionEffect_animation(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TransitionEffect_animation(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TransitionEffect_combine(ptr: KPointer, transitionEffect: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TransitionEffect_combine(ptr, transitionEffect)
        }
        throw new Error("Not implemented")
    }
    static _TransitionEffect_getIDENTITY(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TransitionEffect_getIDENTITY()
        }
        throw new Error("Not implemented")
    }
    static _TransitionEffect_getOPACITY(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TransitionEffect_getOPACITY()
        }
        throw new Error("Not implemented")
    }
    static _TransitionEffect_getSLIDE(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TransitionEffect_getSLIDE()
        }
        throw new Error("Not implemented")
    }
    static _TransitionEffect_getSLIDE_SWITCH(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TransitionEffect_getSLIDE_SWITCH()
        }
        throw new Error("Not implemented")
    }
    static _BaseEvent_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._BaseEvent_ctor()
        }
        throw new Error("Not implemented")
    }
    static _BaseEvent_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._BaseEvent_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _BaseEvent_getModifierKeyState(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): boolean {
        if ((this._LoadOnce()) == (true))
        {
            return this._BaseEvent_getModifierKeyState(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _BaseEvent_setTarget(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._BaseEvent_setTarget(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _BaseEvent_getTimestamp(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._BaseEvent_getTimestamp(ptr)
        }
        throw new Error("Not implemented")
    }
    static _BaseEvent_setTimestamp(ptr: KPointer, timestamp: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._BaseEvent_setTimestamp(ptr, timestamp)
        }
        throw new Error("Not implemented")
    }
    static _BaseEvent_getSource(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._BaseEvent_getSource(ptr)
        }
        throw new Error("Not implemented")
    }
    static _BaseEvent_setSource(ptr: KPointer, source: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._BaseEvent_setSource(ptr, source)
        }
        throw new Error("Not implemented")
    }
    static _BaseEvent_getAxisHorizontal(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._BaseEvent_getAxisHorizontal(ptr)
        }
        throw new Error("Not implemented")
    }
    static _BaseEvent_setAxisHorizontal(ptr: KPointer, axisHorizontal: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._BaseEvent_setAxisHorizontal(ptr, axisHorizontal)
        }
        throw new Error("Not implemented")
    }
    static _BaseEvent_getAxisVertical(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._BaseEvent_getAxisVertical(ptr)
        }
        throw new Error("Not implemented")
    }
    static _BaseEvent_setAxisVertical(ptr: KPointer, axisVertical: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._BaseEvent_setAxisVertical(ptr, axisVertical)
        }
        throw new Error("Not implemented")
    }
    static _BaseEvent_getAxisPinch(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._BaseEvent_getAxisPinch(ptr)
        }
        throw new Error("Not implemented")
    }
    static _BaseEvent_setAxisPinch(ptr: KPointer, axisPinch: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._BaseEvent_setAxisPinch(ptr, axisPinch)
        }
        throw new Error("Not implemented")
    }
    static _BaseEvent_getPressure(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._BaseEvent_getPressure(ptr)
        }
        throw new Error("Not implemented")
    }
    static _BaseEvent_setPressure(ptr: KPointer, pressure: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._BaseEvent_setPressure(ptr, pressure)
        }
        throw new Error("Not implemented")
    }
    static _BaseEvent_getTiltX(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._BaseEvent_getTiltX(ptr)
        }
        throw new Error("Not implemented")
    }
    static _BaseEvent_setTiltX(ptr: KPointer, tiltX: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._BaseEvent_setTiltX(ptr, tiltX)
        }
        throw new Error("Not implemented")
    }
    static _BaseEvent_getTiltY(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._BaseEvent_getTiltY(ptr)
        }
        throw new Error("Not implemented")
    }
    static _BaseEvent_setTiltY(ptr: KPointer, tiltY: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._BaseEvent_setTiltY(ptr, tiltY)
        }
        throw new Error("Not implemented")
    }
    static _BaseEvent_getSourceTool(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._BaseEvent_getSourceTool(ptr)
        }
        throw new Error("Not implemented")
    }
    static _BaseEvent_setSourceTool(ptr: KPointer, sourceTool: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._BaseEvent_setSourceTool(ptr, sourceTool)
        }
        throw new Error("Not implemented")
    }
    static _BaseEvent_getDeviceId(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._BaseEvent_getDeviceId(ptr)
        }
        throw new Error("Not implemented")
    }
    static _BaseEvent_setDeviceId(ptr: KPointer, deviceId: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._BaseEvent_setDeviceId(ptr, deviceId)
        }
        throw new Error("Not implemented")
    }
    static _ClickEvent_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ClickEvent_ctor()
        }
        throw new Error("Not implemented")
    }
    static _ClickEvent_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ClickEvent_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _ClickEvent_getDisplayX(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._ClickEvent_getDisplayX(ptr)
        }
        throw new Error("Not implemented")
    }
    static _ClickEvent_setDisplayX(ptr: KPointer, displayX: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ClickEvent_setDisplayX(ptr, displayX)
        }
        throw new Error("Not implemented")
    }
    static _ClickEvent_getDisplayY(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._ClickEvent_getDisplayY(ptr)
        }
        throw new Error("Not implemented")
    }
    static _ClickEvent_setDisplayY(ptr: KPointer, displayY: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ClickEvent_setDisplayY(ptr, displayY)
        }
        throw new Error("Not implemented")
    }
    static _ClickEvent_getWindowX(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._ClickEvent_getWindowX(ptr)
        }
        throw new Error("Not implemented")
    }
    static _ClickEvent_setWindowX(ptr: KPointer, windowX: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ClickEvent_setWindowX(ptr, windowX)
        }
        throw new Error("Not implemented")
    }
    static _ClickEvent_getWindowY(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._ClickEvent_getWindowY(ptr)
        }
        throw new Error("Not implemented")
    }
    static _ClickEvent_setWindowY(ptr: KPointer, windowY: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ClickEvent_setWindowY(ptr, windowY)
        }
        throw new Error("Not implemented")
    }
    static _ClickEvent_getScreenX(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._ClickEvent_getScreenX(ptr)
        }
        throw new Error("Not implemented")
    }
    static _ClickEvent_setScreenX(ptr: KPointer, screenX: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ClickEvent_setScreenX(ptr, screenX)
        }
        throw new Error("Not implemented")
    }
    static _ClickEvent_getScreenY(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._ClickEvent_getScreenY(ptr)
        }
        throw new Error("Not implemented")
    }
    static _ClickEvent_setScreenY(ptr: KPointer, screenY: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ClickEvent_setScreenY(ptr, screenY)
        }
        throw new Error("Not implemented")
    }
    static _ClickEvent_getX(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._ClickEvent_getX(ptr)
        }
        throw new Error("Not implemented")
    }
    static _ClickEvent_setX(ptr: KPointer, x: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ClickEvent_setX(ptr, x)
        }
        throw new Error("Not implemented")
    }
    static _ClickEvent_getY(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._ClickEvent_getY(ptr)
        }
        throw new Error("Not implemented")
    }
    static _ClickEvent_setY(ptr: KPointer, y: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ClickEvent_setY(ptr, y)
        }
        throw new Error("Not implemented")
    }
    static _ClickEvent_getPreventDefault(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ClickEvent_getPreventDefault(ptr)
        }
        throw new Error("Not implemented")
    }
    static _ClickEvent_setPreventDefault(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ClickEvent_setPreventDefault(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _HoverEvent_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._HoverEvent_ctor()
        }
        throw new Error("Not implemented")
    }
    static _HoverEvent_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._HoverEvent_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _HoverEvent_getStopPropagation(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._HoverEvent_getStopPropagation(ptr)
        }
        throw new Error("Not implemented")
    }
    static _HoverEvent_setStopPropagation(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._HoverEvent_setStopPropagation(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _MouseEvent_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._MouseEvent_ctor()
        }
        throw new Error("Not implemented")
    }
    static _MouseEvent_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._MouseEvent_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _MouseEvent_getButton(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._MouseEvent_getButton(ptr)
        }
        throw new Error("Not implemented")
    }
    static _MouseEvent_setButton(ptr: KPointer, button: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MouseEvent_setButton(ptr, button)
        }
        throw new Error("Not implemented")
    }
    static _MouseEvent_getAction(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._MouseEvent_getAction(ptr)
        }
        throw new Error("Not implemented")
    }
    static _MouseEvent_setAction(ptr: KPointer, action: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MouseEvent_setAction(ptr, action)
        }
        throw new Error("Not implemented")
    }
    static _MouseEvent_getDisplayX(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._MouseEvent_getDisplayX(ptr)
        }
        throw new Error("Not implemented")
    }
    static _MouseEvent_setDisplayX(ptr: KPointer, displayX: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MouseEvent_setDisplayX(ptr, displayX)
        }
        throw new Error("Not implemented")
    }
    static _MouseEvent_getDisplayY(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._MouseEvent_getDisplayY(ptr)
        }
        throw new Error("Not implemented")
    }
    static _MouseEvent_setDisplayY(ptr: KPointer, displayY: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MouseEvent_setDisplayY(ptr, displayY)
        }
        throw new Error("Not implemented")
    }
    static _MouseEvent_getWindowX(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._MouseEvent_getWindowX(ptr)
        }
        throw new Error("Not implemented")
    }
    static _MouseEvent_setWindowX(ptr: KPointer, windowX: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MouseEvent_setWindowX(ptr, windowX)
        }
        throw new Error("Not implemented")
    }
    static _MouseEvent_getWindowY(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._MouseEvent_getWindowY(ptr)
        }
        throw new Error("Not implemented")
    }
    static _MouseEvent_setWindowY(ptr: KPointer, windowY: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MouseEvent_setWindowY(ptr, windowY)
        }
        throw new Error("Not implemented")
    }
    static _MouseEvent_getScreenX(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._MouseEvent_getScreenX(ptr)
        }
        throw new Error("Not implemented")
    }
    static _MouseEvent_setScreenX(ptr: KPointer, screenX: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MouseEvent_setScreenX(ptr, screenX)
        }
        throw new Error("Not implemented")
    }
    static _MouseEvent_getScreenY(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._MouseEvent_getScreenY(ptr)
        }
        throw new Error("Not implemented")
    }
    static _MouseEvent_setScreenY(ptr: KPointer, screenY: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MouseEvent_setScreenY(ptr, screenY)
        }
        throw new Error("Not implemented")
    }
    static _MouseEvent_getX(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._MouseEvent_getX(ptr)
        }
        throw new Error("Not implemented")
    }
    static _MouseEvent_setX(ptr: KPointer, x: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MouseEvent_setX(ptr, x)
        }
        throw new Error("Not implemented")
    }
    static _MouseEvent_getY(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._MouseEvent_getY(ptr)
        }
        throw new Error("Not implemented")
    }
    static _MouseEvent_setY(ptr: KPointer, y: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MouseEvent_setY(ptr, y)
        }
        throw new Error("Not implemented")
    }
    static _MouseEvent_getStopPropagation(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._MouseEvent_getStopPropagation(ptr)
        }
        throw new Error("Not implemented")
    }
    static _MouseEvent_setStopPropagation(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MouseEvent_setStopPropagation(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _AccessibilityHoverEvent_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._AccessibilityHoverEvent_ctor()
        }
        throw new Error("Not implemented")
    }
    static _AccessibilityHoverEvent_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._AccessibilityHoverEvent_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _AccessibilityHoverEvent_getType(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._AccessibilityHoverEvent_getType(ptr)
        }
        throw new Error("Not implemented")
    }
    static _AccessibilityHoverEvent_setType(ptr: KPointer, type: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AccessibilityHoverEvent_setType(ptr, type)
        }
        throw new Error("Not implemented")
    }
    static _AccessibilityHoverEvent_getX(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._AccessibilityHoverEvent_getX(ptr)
        }
        throw new Error("Not implemented")
    }
    static _AccessibilityHoverEvent_setX(ptr: KPointer, x: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AccessibilityHoverEvent_setX(ptr, x)
        }
        throw new Error("Not implemented")
    }
    static _AccessibilityHoverEvent_getY(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._AccessibilityHoverEvent_getY(ptr)
        }
        throw new Error("Not implemented")
    }
    static _AccessibilityHoverEvent_setY(ptr: KPointer, y: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AccessibilityHoverEvent_setY(ptr, y)
        }
        throw new Error("Not implemented")
    }
    static _AccessibilityHoverEvent_getDisplayX(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._AccessibilityHoverEvent_getDisplayX(ptr)
        }
        throw new Error("Not implemented")
    }
    static _AccessibilityHoverEvent_setDisplayX(ptr: KPointer, displayX: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AccessibilityHoverEvent_setDisplayX(ptr, displayX)
        }
        throw new Error("Not implemented")
    }
    static _AccessibilityHoverEvent_getDisplayY(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._AccessibilityHoverEvent_getDisplayY(ptr)
        }
        throw new Error("Not implemented")
    }
    static _AccessibilityHoverEvent_setDisplayY(ptr: KPointer, displayY: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AccessibilityHoverEvent_setDisplayY(ptr, displayY)
        }
        throw new Error("Not implemented")
    }
    static _AccessibilityHoverEvent_getWindowX(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._AccessibilityHoverEvent_getWindowX(ptr)
        }
        throw new Error("Not implemented")
    }
    static _AccessibilityHoverEvent_setWindowX(ptr: KPointer, windowX: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AccessibilityHoverEvent_setWindowX(ptr, windowX)
        }
        throw new Error("Not implemented")
    }
    static _AccessibilityHoverEvent_getWindowY(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._AccessibilityHoverEvent_getWindowY(ptr)
        }
        throw new Error("Not implemented")
    }
    static _AccessibilityHoverEvent_setWindowY(ptr: KPointer, windowY: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AccessibilityHoverEvent_setWindowY(ptr, windowY)
        }
        throw new Error("Not implemented")
    }
    static _TouchEvent_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TouchEvent_ctor()
        }
        throw new Error("Not implemented")
    }
    static _TouchEvent_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TouchEvent_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _TouchEvent_getHistoricalPoints(ptr: KPointer): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TouchEvent_getHistoricalPoints(ptr)
        }
        throw new Error("Not implemented")
    }
    static _TouchEvent_getType(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TouchEvent_getType(ptr)
        }
        throw new Error("Not implemented")
    }
    static _TouchEvent_setType(ptr: KPointer, type: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TouchEvent_setType(ptr, type)
        }
        throw new Error("Not implemented")
    }
    static _TouchEvent_getTouches(ptr: KPointer): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TouchEvent_getTouches(ptr)
        }
        throw new Error("Not implemented")
    }
    static _TouchEvent_setTouches(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TouchEvent_setTouches(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TouchEvent_getChangedTouches(ptr: KPointer): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TouchEvent_getChangedTouches(ptr)
        }
        throw new Error("Not implemented")
    }
    static _TouchEvent_setChangedTouches(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TouchEvent_setChangedTouches(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TouchEvent_getStopPropagation(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TouchEvent_getStopPropagation(ptr)
        }
        throw new Error("Not implemented")
    }
    static _TouchEvent_setStopPropagation(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TouchEvent_setStopPropagation(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TouchEvent_getPreventDefault(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TouchEvent_getPreventDefault(ptr)
        }
        throw new Error("Not implemented")
    }
    static _TouchEvent_setPreventDefault(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TouchEvent_setPreventDefault(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _PixelMapMock_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._PixelMapMock_ctor()
        }
        throw new Error("Not implemented")
    }
    static _PixelMapMock_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._PixelMapMock_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _PixelMapMock_release(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PixelMapMock_release(ptr)
        }
        throw new Error("Not implemented")
    }
    static _DragEvent_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._DragEvent_ctor()
        }
        throw new Error("Not implemented")
    }
    static _DragEvent_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._DragEvent_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _DragEvent_getDisplayX(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._DragEvent_getDisplayX(ptr)
        }
        throw new Error("Not implemented")
    }
    static _DragEvent_getDisplayY(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._DragEvent_getDisplayY(ptr)
        }
        throw new Error("Not implemented")
    }
    static _DragEvent_getWindowX(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._DragEvent_getWindowX(ptr)
        }
        throw new Error("Not implemented")
    }
    static _DragEvent_getWindowY(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._DragEvent_getWindowY(ptr)
        }
        throw new Error("Not implemented")
    }
    static _DragEvent_getX(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._DragEvent_getX(ptr)
        }
        throw new Error("Not implemented")
    }
    static _DragEvent_getY(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._DragEvent_getY(ptr)
        }
        throw new Error("Not implemented")
    }
    static _DragEvent_setData(ptr: KPointer, unifiedData: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._DragEvent_setData(ptr, unifiedData)
        }
        throw new Error("Not implemented")
    }
    static _DragEvent_getData(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._DragEvent_getData(ptr)
        }
        throw new Error("Not implemented")
    }
    static _DragEvent_getSummary(ptr: KPointer): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._DragEvent_getSummary(ptr)
        }
        throw new Error("Not implemented")
    }
    static _DragEvent_setResult(ptr: KPointer, dragResult: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._DragEvent_setResult(ptr, dragResult)
        }
        throw new Error("Not implemented")
    }
    static _DragEvent_getResult(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._DragEvent_getResult(ptr)
        }
        throw new Error("Not implemented")
    }
    static _DragEvent_getPreviewRect(ptr: KPointer): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._DragEvent_getPreviewRect(ptr)
        }
        throw new Error("Not implemented")
    }
    static _DragEvent_getVelocityX(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._DragEvent_getVelocityX(ptr)
        }
        throw new Error("Not implemented")
    }
    static _DragEvent_getVelocityY(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._DragEvent_getVelocityY(ptr)
        }
        throw new Error("Not implemented")
    }
    static _DragEvent_getVelocity(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._DragEvent_getVelocity(ptr)
        }
        throw new Error("Not implemented")
    }
    static _DragEvent_getModifierKeyState(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): boolean {
        if ((this._LoadOnce()) == (true))
        {
            return this._DragEvent_getModifierKeyState(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _DragEvent_getDragBehavior(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._DragEvent_getDragBehavior(ptr)
        }
        throw new Error("Not implemented")
    }
    static _DragEvent_setDragBehavior(ptr: KPointer, dragBehavior: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._DragEvent_setDragBehavior(ptr, dragBehavior)
        }
        throw new Error("Not implemented")
    }
    static _DragEvent_getUseCustomDropAnimation(ptr: KPointer): boolean {
        if ((this._LoadOnce()) == (true))
        {
            return this._DragEvent_getUseCustomDropAnimation(ptr)
        }
        throw new Error("Not implemented")
    }
    static _DragEvent_setUseCustomDropAnimation(ptr: KPointer, useCustomDropAnimation: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._DragEvent_setUseCustomDropAnimation(ptr, useCustomDropAnimation)
        }
        throw new Error("Not implemented")
    }
    static _KeyEvent_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._KeyEvent_ctor()
        }
        throw new Error("Not implemented")
    }
    static _KeyEvent_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._KeyEvent_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _KeyEvent_getModifierKeyState(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): boolean {
        if ((this._LoadOnce()) == (true))
        {
            return this._KeyEvent_getModifierKeyState(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _KeyEvent_getType(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._KeyEvent_getType(ptr)
        }
        throw new Error("Not implemented")
    }
    static _KeyEvent_setType(ptr: KPointer, type: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._KeyEvent_setType(ptr, type)
        }
        throw new Error("Not implemented")
    }
    static _KeyEvent_getKeyCode(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._KeyEvent_getKeyCode(ptr)
        }
        throw new Error("Not implemented")
    }
    static _KeyEvent_setKeyCode(ptr: KPointer, keyCode: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._KeyEvent_setKeyCode(ptr, keyCode)
        }
        throw new Error("Not implemented")
    }
    static _KeyEvent_getKeyText(ptr: KPointer): string {
        if ((this._LoadOnce()) == (true))
        {
            return this._KeyEvent_getKeyText(ptr)
        }
        throw new Error("Not implemented")
    }
    static _KeyEvent_setKeyText(ptr: KPointer, keyText: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._KeyEvent_setKeyText(ptr, keyText)
        }
        throw new Error("Not implemented")
    }
    static _KeyEvent_getKeySource(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._KeyEvent_getKeySource(ptr)
        }
        throw new Error("Not implemented")
    }
    static _KeyEvent_setKeySource(ptr: KPointer, keySource: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._KeyEvent_setKeySource(ptr, keySource)
        }
        throw new Error("Not implemented")
    }
    static _KeyEvent_getDeviceId(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._KeyEvent_getDeviceId(ptr)
        }
        throw new Error("Not implemented")
    }
    static _KeyEvent_setDeviceId(ptr: KPointer, deviceId: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._KeyEvent_setDeviceId(ptr, deviceId)
        }
        throw new Error("Not implemented")
    }
    static _KeyEvent_getMetaKey(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._KeyEvent_getMetaKey(ptr)
        }
        throw new Error("Not implemented")
    }
    static _KeyEvent_setMetaKey(ptr: KPointer, metaKey: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._KeyEvent_setMetaKey(ptr, metaKey)
        }
        throw new Error("Not implemented")
    }
    static _KeyEvent_getTimestamp(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._KeyEvent_getTimestamp(ptr)
        }
        throw new Error("Not implemented")
    }
    static _KeyEvent_setTimestamp(ptr: KPointer, timestamp: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._KeyEvent_setTimestamp(ptr, timestamp)
        }
        throw new Error("Not implemented")
    }
    static _KeyEvent_getStopPropagation(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._KeyEvent_getStopPropagation(ptr)
        }
        throw new Error("Not implemented")
    }
    static _KeyEvent_setStopPropagation(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._KeyEvent_setStopPropagation(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _KeyEvent_setIntentionCode(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._KeyEvent_setIntentionCode(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _KeyEvent_getUnicode(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._KeyEvent_getUnicode(ptr)
        }
        throw new Error("Not implemented")
    }
    static _KeyEvent_setUnicode(ptr: KPointer, unicode: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._KeyEvent_setUnicode(ptr, unicode)
        }
        throw new Error("Not implemented")
    }
    static _ProgressMask_ctor(value: number, total: number, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ProgressMask_ctor(value, total, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ProgressMask_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ProgressMask_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _ProgressMask_updateProgress(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ProgressMask_updateProgress(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _ProgressMask_updateColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ProgressMask_updateColor(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ProgressMask_enableBreathingAnimation(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ProgressMask_enableBreathingAnimation(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _Measurable_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Measurable_ctor()
        }
        throw new Error("Not implemented")
    }
    static _Measurable_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Measurable_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _Measurable_measure(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Measurable_measure(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Measurable_getMargin(ptr: KPointer): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Measurable_getMargin(ptr)
        }
        throw new Error("Not implemented")
    }
    static _Measurable_getPadding(ptr: KPointer): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Measurable_getPadding(ptr)
        }
        throw new Error("Not implemented")
    }
    static _Measurable_getBorderWidth(ptr: KPointer): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Measurable_getBorderWidth(ptr)
        }
        throw new Error("Not implemented")
    }
    static _View_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._View_ctor()
        }
        throw new Error("Not implemented")
    }
    static _View_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._View_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _View_create(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): any {
        if ((this._LoadOnce()) == (true))
        {
            return this._View_create(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextContentControllerBase_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextContentControllerBase_ctor()
        }
        throw new Error("Not implemented")
    }
    static _TextContentControllerBase_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextContentControllerBase_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _TextContentControllerBase_getCaretOffset(ptr: KPointer): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextContentControllerBase_getCaretOffset(ptr)
        }
        throw new Error("Not implemented")
    }
    static _TextContentControllerBase_getTextContentRect(ptr: KPointer): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextContentControllerBase_getTextContentRect(ptr)
        }
        throw new Error("Not implemented")
    }
    static _TextContentControllerBase_getTextContentLineCount(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextContentControllerBase_getTextContentLineCount(ptr)
        }
        throw new Error("Not implemented")
    }
    static _ChildrenMainSize_ctor(childDefaultSize: number): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ChildrenMainSize_ctor(childDefaultSize)
        }
        throw new Error("Not implemented")
    }
    static _ChildrenMainSize_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ChildrenMainSize_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _ChildrenMainSize_splice(ptr: KPointer, start: number, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ChildrenMainSize_splice(ptr, start, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ChildrenMainSize_update(ptr: KPointer, index: number, childSize: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ChildrenMainSize_update(ptr, index, childSize)
        }
        throw new Error("Not implemented")
    }
    static _ChildrenMainSize_getChildDefaultSize(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._ChildrenMainSize_getChildDefaultSize(ptr)
        }
        throw new Error("Not implemented")
    }
    static _ChildrenMainSize_setChildDefaultSize(ptr: KPointer, childDefaultSize: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ChildrenMainSize_setChildDefaultSize(ptr, childDefaultSize)
        }
        throw new Error("Not implemented")
    }
    static _UICommonEvent_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._UICommonEvent_ctor()
        }
        throw new Error("Not implemented")
    }
    static _UICommonEvent_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._UICommonEvent_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _UICommonEvent_setOnClick(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._UICommonEvent_setOnClick(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _UICommonEvent_setOnTouch(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._UICommonEvent_setOnTouch(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _UICommonEvent_setOnAppear(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._UICommonEvent_setOnAppear(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _UICommonEvent_setOnDisappear(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._UICommonEvent_setOnDisappear(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _UICommonEvent_setOnKeyEvent(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._UICommonEvent_setOnKeyEvent(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _UICommonEvent_setOnFocus(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._UICommonEvent_setOnFocus(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _UICommonEvent_setOnBlur(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._UICommonEvent_setOnBlur(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _UICommonEvent_setOnHover(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._UICommonEvent_setOnHover(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _UICommonEvent_setOnMouse(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._UICommonEvent_setOnMouse(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _UICommonEvent_setOnSizeChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._UICommonEvent_setOnSizeChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _UICommonEvent_setOnVisibleAreaApproximateChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._UICommonEvent_setOnVisibleAreaApproximateChange(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GestureModifier_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._GestureModifier_ctor()
        }
        throw new Error("Not implemented")
    }
    static _GestureModifier_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._GestureModifier_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _GestureModifier_applyGesture(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GestureModifier_applyGesture(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ContextMenu_close(): undefined {
        if ((this._LoadOnce()) == (true))
        {
            return this._ContextMenu_close()
        }
        throw new Error("Not implemented")
    }
    static _CustomDialogController_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CustomDialogController_ctor(thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CustomDialogController_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CustomDialogController_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _CustomDialogController_open(ptr: KPointer): undefined {
        if ((this._LoadOnce()) == (true))
        {
            return this._CustomDialogController_open(ptr)
        }
        throw new Error("Not implemented")
    }
    static _CustomDialogController_close(ptr: KPointer): undefined {
        if ((this._LoadOnce()) == (true))
        {
            return this._CustomDialogController_close(ptr)
        }
        throw new Error("Not implemented")
    }
    static _LinearGradient_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._LinearGradient_ctor(thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _LinearGradient_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._LinearGradient_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _DatePickerDialog_show(thisArray: Uint8Array, thisLength: int32): undefined {
        if ((this._LoadOnce()) == (true))
        {
            return this._DatePickerDialog_show(thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _BaseGestureEvent_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._BaseGestureEvent_ctor()
        }
        throw new Error("Not implemented")
    }
    static _BaseGestureEvent_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._BaseGestureEvent_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _BaseGestureEvent_getFingerList(ptr: KPointer): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._BaseGestureEvent_getFingerList(ptr)
        }
        throw new Error("Not implemented")
    }
    static _BaseGestureEvent_setFingerList(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._BaseGestureEvent_setFingerList(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TapGestureEvent_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TapGestureEvent_ctor()
        }
        throw new Error("Not implemented")
    }
    static _TapGestureEvent_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TapGestureEvent_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _LongPressGestureEvent_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._LongPressGestureEvent_ctor()
        }
        throw new Error("Not implemented")
    }
    static _LongPressGestureEvent_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._LongPressGestureEvent_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _LongPressGestureEvent_getRepeat(ptr: KPointer): boolean {
        if ((this._LoadOnce()) == (true))
        {
            return this._LongPressGestureEvent_getRepeat(ptr)
        }
        throw new Error("Not implemented")
    }
    static _LongPressGestureEvent_setRepeat(ptr: KPointer, repeat: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._LongPressGestureEvent_setRepeat(ptr, repeat)
        }
        throw new Error("Not implemented")
    }
    static _PanGestureEvent_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._PanGestureEvent_ctor()
        }
        throw new Error("Not implemented")
    }
    static _PanGestureEvent_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._PanGestureEvent_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _PanGestureEvent_getOffsetX(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._PanGestureEvent_getOffsetX(ptr)
        }
        throw new Error("Not implemented")
    }
    static _PanGestureEvent_setOffsetX(ptr: KPointer, offsetX: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PanGestureEvent_setOffsetX(ptr, offsetX)
        }
        throw new Error("Not implemented")
    }
    static _PanGestureEvent_getOffsetY(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._PanGestureEvent_getOffsetY(ptr)
        }
        throw new Error("Not implemented")
    }
    static _PanGestureEvent_setOffsetY(ptr: KPointer, offsetY: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PanGestureEvent_setOffsetY(ptr, offsetY)
        }
        throw new Error("Not implemented")
    }
    static _PanGestureEvent_getVelocityX(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._PanGestureEvent_getVelocityX(ptr)
        }
        throw new Error("Not implemented")
    }
    static _PanGestureEvent_setVelocityX(ptr: KPointer, velocityX: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PanGestureEvent_setVelocityX(ptr, velocityX)
        }
        throw new Error("Not implemented")
    }
    static _PanGestureEvent_getVelocityY(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._PanGestureEvent_getVelocityY(ptr)
        }
        throw new Error("Not implemented")
    }
    static _PanGestureEvent_setVelocityY(ptr: KPointer, velocityY: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PanGestureEvent_setVelocityY(ptr, velocityY)
        }
        throw new Error("Not implemented")
    }
    static _PanGestureEvent_getVelocity(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._PanGestureEvent_getVelocity(ptr)
        }
        throw new Error("Not implemented")
    }
    static _PanGestureEvent_setVelocity(ptr: KPointer, velocity: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PanGestureEvent_setVelocity(ptr, velocity)
        }
        throw new Error("Not implemented")
    }
    static _PinchGestureEvent_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._PinchGestureEvent_ctor()
        }
        throw new Error("Not implemented")
    }
    static _PinchGestureEvent_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._PinchGestureEvent_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _PinchGestureEvent_getScale(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._PinchGestureEvent_getScale(ptr)
        }
        throw new Error("Not implemented")
    }
    static _PinchGestureEvent_setScale(ptr: KPointer, scale: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PinchGestureEvent_setScale(ptr, scale)
        }
        throw new Error("Not implemented")
    }
    static _PinchGestureEvent_getPinchCenterX(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._PinchGestureEvent_getPinchCenterX(ptr)
        }
        throw new Error("Not implemented")
    }
    static _PinchGestureEvent_setPinchCenterX(ptr: KPointer, pinchCenterX: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PinchGestureEvent_setPinchCenterX(ptr, pinchCenterX)
        }
        throw new Error("Not implemented")
    }
    static _PinchGestureEvent_getPinchCenterY(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._PinchGestureEvent_getPinchCenterY(ptr)
        }
        throw new Error("Not implemented")
    }
    static _PinchGestureEvent_setPinchCenterY(ptr: KPointer, pinchCenterY: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PinchGestureEvent_setPinchCenterY(ptr, pinchCenterY)
        }
        throw new Error("Not implemented")
    }
    static _RotationGestureEvent_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._RotationGestureEvent_ctor()
        }
        throw new Error("Not implemented")
    }
    static _RotationGestureEvent_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._RotationGestureEvent_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _RotationGestureEvent_getAngle(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._RotationGestureEvent_getAngle(ptr)
        }
        throw new Error("Not implemented")
    }
    static _RotationGestureEvent_setAngle(ptr: KPointer, angle: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RotationGestureEvent_setAngle(ptr, angle)
        }
        throw new Error("Not implemented")
    }
    static _SwipeGestureEvent_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwipeGestureEvent_ctor()
        }
        throw new Error("Not implemented")
    }
    static _SwipeGestureEvent_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwipeGestureEvent_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _SwipeGestureEvent_getAngle(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwipeGestureEvent_getAngle(ptr)
        }
        throw new Error("Not implemented")
    }
    static _SwipeGestureEvent_setAngle(ptr: KPointer, angle: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwipeGestureEvent_setAngle(ptr, angle)
        }
        throw new Error("Not implemented")
    }
    static _SwipeGestureEvent_getSpeed(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwipeGestureEvent_getSpeed(ptr)
        }
        throw new Error("Not implemented")
    }
    static _SwipeGestureEvent_setSpeed(ptr: KPointer, speed: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwipeGestureEvent_setSpeed(ptr, speed)
        }
        throw new Error("Not implemented")
    }
    static _GestureEvent_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._GestureEvent_ctor()
        }
        throw new Error("Not implemented")
    }
    static _GestureEvent_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._GestureEvent_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _GestureEvent_getRepeat(ptr: KPointer): boolean {
        if ((this._LoadOnce()) == (true))
        {
            return this._GestureEvent_getRepeat(ptr)
        }
        throw new Error("Not implemented")
    }
    static _GestureEvent_setRepeat(ptr: KPointer, repeat: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GestureEvent_setRepeat(ptr, repeat)
        }
        throw new Error("Not implemented")
    }
    static _GestureEvent_getFingerList(ptr: KPointer): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._GestureEvent_getFingerList(ptr)
        }
        throw new Error("Not implemented")
    }
    static _GestureEvent_setFingerList(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GestureEvent_setFingerList(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GestureEvent_getOffsetX(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._GestureEvent_getOffsetX(ptr)
        }
        throw new Error("Not implemented")
    }
    static _GestureEvent_setOffsetX(ptr: KPointer, offsetX: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GestureEvent_setOffsetX(ptr, offsetX)
        }
        throw new Error("Not implemented")
    }
    static _GestureEvent_getOffsetY(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._GestureEvent_getOffsetY(ptr)
        }
        throw new Error("Not implemented")
    }
    static _GestureEvent_setOffsetY(ptr: KPointer, offsetY: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GestureEvent_setOffsetY(ptr, offsetY)
        }
        throw new Error("Not implemented")
    }
    static _GestureEvent_getAngle(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._GestureEvent_getAngle(ptr)
        }
        throw new Error("Not implemented")
    }
    static _GestureEvent_setAngle(ptr: KPointer, angle: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GestureEvent_setAngle(ptr, angle)
        }
        throw new Error("Not implemented")
    }
    static _GestureEvent_getSpeed(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._GestureEvent_getSpeed(ptr)
        }
        throw new Error("Not implemented")
    }
    static _GestureEvent_setSpeed(ptr: KPointer, speed: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GestureEvent_setSpeed(ptr, speed)
        }
        throw new Error("Not implemented")
    }
    static _GestureEvent_getScale(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._GestureEvent_getScale(ptr)
        }
        throw new Error("Not implemented")
    }
    static _GestureEvent_setScale(ptr: KPointer, scale: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GestureEvent_setScale(ptr, scale)
        }
        throw new Error("Not implemented")
    }
    static _GestureEvent_getPinchCenterX(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._GestureEvent_getPinchCenterX(ptr)
        }
        throw new Error("Not implemented")
    }
    static _GestureEvent_setPinchCenterX(ptr: KPointer, pinchCenterX: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GestureEvent_setPinchCenterX(ptr, pinchCenterX)
        }
        throw new Error("Not implemented")
    }
    static _GestureEvent_getPinchCenterY(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._GestureEvent_getPinchCenterY(ptr)
        }
        throw new Error("Not implemented")
    }
    static _GestureEvent_setPinchCenterY(ptr: KPointer, pinchCenterY: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GestureEvent_setPinchCenterY(ptr, pinchCenterY)
        }
        throw new Error("Not implemented")
    }
    static _GestureEvent_getVelocityX(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._GestureEvent_getVelocityX(ptr)
        }
        throw new Error("Not implemented")
    }
    static _GestureEvent_setVelocityX(ptr: KPointer, velocityX: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GestureEvent_setVelocityX(ptr, velocityX)
        }
        throw new Error("Not implemented")
    }
    static _GestureEvent_getVelocityY(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._GestureEvent_getVelocityY(ptr)
        }
        throw new Error("Not implemented")
    }
    static _GestureEvent_setVelocityY(ptr: KPointer, velocityY: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GestureEvent_setVelocityY(ptr, velocityY)
        }
        throw new Error("Not implemented")
    }
    static _GestureEvent_getVelocity(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._GestureEvent_getVelocity(ptr)
        }
        throw new Error("Not implemented")
    }
    static _GestureEvent_setVelocity(ptr: KPointer, velocity: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GestureEvent_setVelocity(ptr, velocity)
        }
        throw new Error("Not implemented")
    }
    static _TapGestureInterface_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TapGestureInterface_ctor()
        }
        throw new Error("Not implemented")
    }
    static _TapGestureInterface_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TapGestureInterface_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _TapGestureInterface_onAction(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TapGestureInterface_onAction(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _LongPressGestureInterface_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._LongPressGestureInterface_ctor()
        }
        throw new Error("Not implemented")
    }
    static _LongPressGestureInterface_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._LongPressGestureInterface_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _LongPressGestureInterface_onAction(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._LongPressGestureInterface_onAction(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _LongPressGestureInterface_onActionEnd(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._LongPressGestureInterface_onActionEnd(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _LongPressGestureInterface_onActionCancel(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._LongPressGestureInterface_onActionCancel(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _PanGestureOptions_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._PanGestureOptions_ctor(thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _PanGestureOptions_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._PanGestureOptions_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _PanGestureOptions_setDirection(ptr: KPointer, value: KInt): undefined {
        if ((this._LoadOnce()) == (true))
        {
            return this._PanGestureOptions_setDirection(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _PanGestureOptions_setDistance(ptr: KPointer, value: number): undefined {
        if ((this._LoadOnce()) == (true))
        {
            return this._PanGestureOptions_setDistance(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _PanGestureOptions_setFingers(ptr: KPointer, value: number): undefined {
        if ((this._LoadOnce()) == (true))
        {
            return this._PanGestureOptions_setFingers(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _PanGestureOptions_getDirection(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._PanGestureOptions_getDirection(ptr)
        }
        throw new Error("Not implemented")
    }
    static _PanGestureInterface_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._PanGestureInterface_ctor()
        }
        throw new Error("Not implemented")
    }
    static _PanGestureInterface_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._PanGestureInterface_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _PanGestureInterface_onActionStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._PanGestureInterface_onActionStart(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _PanGestureInterface_onActionUpdate(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._PanGestureInterface_onActionUpdate(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _PanGestureInterface_onActionEnd(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._PanGestureInterface_onActionEnd(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _PanGestureInterface_onActionCancel(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._PanGestureInterface_onActionCancel(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SwipeGestureInterface_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwipeGestureInterface_ctor()
        }
        throw new Error("Not implemented")
    }
    static _SwipeGestureInterface_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwipeGestureInterface_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _SwipeGestureInterface_onAction(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwipeGestureInterface_onAction(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _PinchGestureInterface_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._PinchGestureInterface_ctor()
        }
        throw new Error("Not implemented")
    }
    static _PinchGestureInterface_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._PinchGestureInterface_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _PinchGestureInterface_onActionStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._PinchGestureInterface_onActionStart(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _PinchGestureInterface_onActionUpdate(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._PinchGestureInterface_onActionUpdate(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _PinchGestureInterface_onActionEnd(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._PinchGestureInterface_onActionEnd(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _PinchGestureInterface_onActionCancel(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._PinchGestureInterface_onActionCancel(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RotationGestureInterface_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._RotationGestureInterface_ctor()
        }
        throw new Error("Not implemented")
    }
    static _RotationGestureInterface_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._RotationGestureInterface_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _RotationGestureInterface_onActionStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._RotationGestureInterface_onActionStart(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RotationGestureInterface_onActionUpdate(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._RotationGestureInterface_onActionUpdate(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RotationGestureInterface_onActionEnd(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._RotationGestureInterface_onActionEnd(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RotationGestureInterface_onActionCancel(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._RotationGestureInterface_onActionCancel(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GestureGroupInterface_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._GestureGroupInterface_ctor()
        }
        throw new Error("Not implemented")
    }
    static _GestureGroupInterface_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._GestureGroupInterface_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _GestureGroupInterface_onCancel(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._GestureGroupInterface_onCancel(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ScrollableTargetInfo_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScrollableTargetInfo_ctor()
        }
        throw new Error("Not implemented")
    }
    static _ScrollableTargetInfo_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScrollableTargetInfo_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _ScrollableTargetInfo_isBegin(ptr: KPointer): boolean {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScrollableTargetInfo_isBegin(ptr)
        }
        throw new Error("Not implemented")
    }
    static _ScrollableTargetInfo_isEnd(ptr: KPointer): boolean {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScrollableTargetInfo_isEnd(ptr)
        }
        throw new Error("Not implemented")
    }
    static _EventTargetInfo_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._EventTargetInfo_ctor()
        }
        throw new Error("Not implemented")
    }
    static _EventTargetInfo_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._EventTargetInfo_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _EventTargetInfo_getId(ptr: KPointer): string {
        if ((this._LoadOnce()) == (true))
        {
            return this._EventTargetInfo_getId(ptr)
        }
        throw new Error("Not implemented")
    }
    static _GestureRecognizer_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._GestureRecognizer_ctor()
        }
        throw new Error("Not implemented")
    }
    static _GestureRecognizer_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._GestureRecognizer_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _GestureRecognizer_getTag(ptr: KPointer): string {
        if ((this._LoadOnce()) == (true))
        {
            return this._GestureRecognizer_getTag(ptr)
        }
        throw new Error("Not implemented")
    }
    static _GestureRecognizer_getType(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._GestureRecognizer_getType(ptr)
        }
        throw new Error("Not implemented")
    }
    static _GestureRecognizer_isBuiltIn(ptr: KPointer): boolean {
        if ((this._LoadOnce()) == (true))
        {
            return this._GestureRecognizer_isBuiltIn(ptr)
        }
        throw new Error("Not implemented")
    }
    static _GestureRecognizer_setEnabled(ptr: KPointer, isEnabled: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GestureRecognizer_setEnabled(ptr, isEnabled)
        }
        throw new Error("Not implemented")
    }
    static _GestureRecognizer_isEnabled(ptr: KPointer): boolean {
        if ((this._LoadOnce()) == (true))
        {
            return this._GestureRecognizer_isEnabled(ptr)
        }
        throw new Error("Not implemented")
    }
    static _GestureRecognizer_getState(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._GestureRecognizer_getState(ptr)
        }
        throw new Error("Not implemented")
    }
    static _GestureRecognizer_getEventTargetInfo(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._GestureRecognizer_getEventTargetInfo(ptr)
        }
        throw new Error("Not implemented")
    }
    static _GestureRecognizer_isValid(ptr: KPointer): boolean {
        if ((this._LoadOnce()) == (true))
        {
            return this._GestureRecognizer_isValid(ptr)
        }
        throw new Error("Not implemented")
    }
    static _PanRecognizer_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._PanRecognizer_ctor()
        }
        throw new Error("Not implemented")
    }
    static _PanRecognizer_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._PanRecognizer_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _PanRecognizer_getPanGestureOptions(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._PanRecognizer_getPanGestureOptions(ptr)
        }
        throw new Error("Not implemented")
    }
    static _ImageAnalyzerController_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageAnalyzerController_ctor()
        }
        throw new Error("Not implemented")
    }
    static _ImageAnalyzerController_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageAnalyzerController_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _ImageAnalyzerController_getImageAnalyzerSupportTypes(ptr: KPointer): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageAnalyzerController_getImageAnalyzerSupportTypes(ptr)
        }
        throw new Error("Not implemented")
    }
    static _ListScroller_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListScroller_ctor()
        }
        throw new Error("Not implemented")
    }
    static _ListScroller_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListScroller_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _ListScroller_getItemRectInGroup(ptr: KPointer, index: number, indexInGroup: number): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListScroller_getItemRectInGroup(ptr, index, indexInGroup)
        }
        throw new Error("Not implemented")
    }
    static _ListScroller_scrollToItemInGroup(ptr: KPointer, index: number, indexInGroup: number, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListScroller_scrollToItemInGroup(ptr, index, indexInGroup, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ListScroller_closeAllSwipeActions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListScroller_closeAllSwipeActions(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ListScroller_getVisibleListContentInfo(ptr: KPointer, x: number, y: number): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ListScroller_getVisibleListContentInfo(ptr, x, y)
        }
        throw new Error("Not implemented")
    }
    static _Matrix2D_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Matrix2D_ctor()
        }
        throw new Error("Not implemented")
    }
    static _Matrix2D_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Matrix2D_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _Matrix2D_identity(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Matrix2D_identity(ptr)
        }
        throw new Error("Not implemented")
    }
    static _Matrix2D_invert(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Matrix2D_invert(ptr)
        }
        throw new Error("Not implemented")
    }
    static _Matrix2D_multiply(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Matrix2D_multiply(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Matrix2D_rotate0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Matrix2D_rotate0(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Matrix2D_rotate1(ptr: KPointer, degree: number, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Matrix2D_rotate1(ptr, degree, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Matrix2D_translate(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Matrix2D_translate(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Matrix2D_scale(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Matrix2D_scale(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Matrix2D_getScaleX(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._Matrix2D_getScaleX(ptr)
        }
        throw new Error("Not implemented")
    }
    static _Matrix2D_setScaleX(ptr: KPointer, scaleX: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._Matrix2D_setScaleX(ptr, scaleX)
        }
        throw new Error("Not implemented")
    }
    static _Matrix2D_getRotateY(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._Matrix2D_getRotateY(ptr)
        }
        throw new Error("Not implemented")
    }
    static _Matrix2D_setRotateY(ptr: KPointer, rotateY: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._Matrix2D_setRotateY(ptr, rotateY)
        }
        throw new Error("Not implemented")
    }
    static _Matrix2D_getRotateX(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._Matrix2D_getRotateX(ptr)
        }
        throw new Error("Not implemented")
    }
    static _Matrix2D_setRotateX(ptr: KPointer, rotateX: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._Matrix2D_setRotateX(ptr, rotateX)
        }
        throw new Error("Not implemented")
    }
    static _Matrix2D_getScaleY(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._Matrix2D_getScaleY(ptr)
        }
        throw new Error("Not implemented")
    }
    static _Matrix2D_setScaleY(ptr: KPointer, scaleY: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._Matrix2D_setScaleY(ptr, scaleY)
        }
        throw new Error("Not implemented")
    }
    static _Matrix2D_getTranslateX(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._Matrix2D_getTranslateX(ptr)
        }
        throw new Error("Not implemented")
    }
    static _Matrix2D_setTranslateX(ptr: KPointer, translateX: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._Matrix2D_setTranslateX(ptr, translateX)
        }
        throw new Error("Not implemented")
    }
    static _Matrix2D_getTranslateY(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._Matrix2D_getTranslateY(ptr)
        }
        throw new Error("Not implemented")
    }
    static _Matrix2D_setTranslateY(ptr: KPointer, translateY: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._Matrix2D_setTranslateY(ptr, translateY)
        }
        throw new Error("Not implemented")
    }
    static _NavDestinationContext_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavDestinationContext_ctor()
        }
        throw new Error("Not implemented")
    }
    static _NavDestinationContext_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavDestinationContext_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _NavDestinationContext_getConfigInRouteMap(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavDestinationContext_getConfigInRouteMap(ptr)
        }
        throw new Error("Not implemented")
    }
    static _NavDestinationContext_getPathInfo(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavDestinationContext_getPathInfo(ptr)
        }
        throw new Error("Not implemented")
    }
    static _NavDestinationContext_setPathInfo(ptr: KPointer, pathInfo: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavDestinationContext_setPathInfo(ptr, pathInfo)
        }
        throw new Error("Not implemented")
    }
    static _NavDestinationContext_getPathStack(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavDestinationContext_getPathStack(ptr)
        }
        throw new Error("Not implemented")
    }
    static _NavDestinationContext_setPathStack(ptr: KPointer, pathStack: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavDestinationContext_setPathStack(ptr, pathStack)
        }
        throw new Error("Not implemented")
    }
    static _NavDestinationContext_getNavDestinationId(ptr: KPointer): string {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavDestinationContext_getNavDestinationId(ptr)
        }
        throw new Error("Not implemented")
    }
    static _NavDestinationContext_setNavDestinationId(ptr: KPointer, navDestinationId: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavDestinationContext_setNavDestinationId(ptr, navDestinationId)
        }
        throw new Error("Not implemented")
    }
    static _NavPathInfo_ctor(name: KStringPtr, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavPathInfo_ctor(name, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavPathInfo_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavPathInfo_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _NavPathInfo_getName(ptr: KPointer): string {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavPathInfo_getName(ptr)
        }
        throw new Error("Not implemented")
    }
    static _NavPathInfo_setName(ptr: KPointer, name: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavPathInfo_setName(ptr, name)
        }
        throw new Error("Not implemented")
    }
    static _NavPathInfo_setParam(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavPathInfo_setParam(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavPathInfo_getOnPop(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavPathInfo_getOnPop(ptr)
        }
        throw new Error("Not implemented")
    }
    static _NavPathInfo_setOnPop(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavPathInfo_setOnPop(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavPathInfo_getIsEntry(ptr: KPointer): boolean {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavPathInfo_getIsEntry(ptr)
        }
        throw new Error("Not implemented")
    }
    static _NavPathInfo_setIsEntry(ptr: KPointer, isEntry: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavPathInfo_setIsEntry(ptr, isEntry)
        }
        throw new Error("Not implemented")
    }
    static _NavPathStack_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavPathStack_ctor()
        }
        throw new Error("Not implemented")
    }
    static _NavPathStack_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavPathStack_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _NavPathStack_pushPath0(ptr: KPointer, info: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavPathStack_pushPath0(ptr, info, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavPathStack_pushPath1(ptr: KPointer, info: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavPathStack_pushPath1(ptr, info, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavPathStack_pushDestination0(ptr: KPointer, info: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavPathStack_pushDestination0(ptr, info, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavPathStack_pushDestination1(ptr: KPointer, info: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavPathStack_pushDestination1(ptr, info, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavPathStack_pushPathByName0(ptr: KPointer, name: KStringPtr, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavPathStack_pushPathByName0(ptr, name, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavPathStack_pushPathByName1(ptr: KPointer, name: KStringPtr, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavPathStack_pushPathByName1(ptr, name, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavPathStack_pushDestinationByName0(ptr: KPointer, name: KStringPtr, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavPathStack_pushDestinationByName0(ptr, name, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavPathStack_pushDestinationByName1(ptr: KPointer, name: KStringPtr, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavPathStack_pushDestinationByName1(ptr, name, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavPathStack_replacePath0(ptr: KPointer, info: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavPathStack_replacePath0(ptr, info, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavPathStack_replacePath1(ptr: KPointer, info: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavPathStack_replacePath1(ptr, info, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavPathStack_replaceDestination(ptr: KPointer, info: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavPathStack_replaceDestination(ptr, info, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavPathStack_replacePathByName(ptr: KPointer, name: KStringPtr, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavPathStack_replacePathByName(ptr, name, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavPathStack_removeByIndexes(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavPathStack_removeByIndexes(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavPathStack_removeByName(ptr: KPointer, name: KStringPtr): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavPathStack_removeByName(ptr, name)
        }
        throw new Error("Not implemented")
    }
    static _NavPathStack_removeByNavDestinationId(ptr: KPointer, navDestinationId: KStringPtr): boolean {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavPathStack_removeByNavDestinationId(ptr, navDestinationId)
        }
        throw new Error("Not implemented")
    }
    static _NavPathStack_pop0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavPathStack_pop0(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavPathStack_pop1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavPathStack_pop1(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavPathStack_popToName0(ptr: KPointer, name: KStringPtr, thisArray: Uint8Array, thisLength: int32): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavPathStack_popToName0(ptr, name, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavPathStack_popToName1(ptr: KPointer, name: KStringPtr, thisArray: Uint8Array, thisLength: int32): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavPathStack_popToName1(ptr, name, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavPathStack_popToIndex0(ptr: KPointer, index: number, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavPathStack_popToIndex0(ptr, index, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavPathStack_popToIndex1(ptr: KPointer, index: number, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavPathStack_popToIndex1(ptr, index, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavPathStack_moveToTop(ptr: KPointer, name: KStringPtr, thisArray: Uint8Array, thisLength: int32): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavPathStack_moveToTop(ptr, name, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavPathStack_moveIndexToTop(ptr: KPointer, index: number, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavPathStack_moveIndexToTop(ptr, index, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavPathStack_clear(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavPathStack_clear(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavPathStack_getAllPathName(ptr: KPointer): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavPathStack_getAllPathName(ptr)
        }
        throw new Error("Not implemented")
    }
    static _NavPathStack_getParamByIndex(ptr: KPointer, index: number): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavPathStack_getParamByIndex(ptr, index)
        }
        throw new Error("Not implemented")
    }
    static _NavPathStack_getParamByName(ptr: KPointer, name: KStringPtr): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavPathStack_getParamByName(ptr, name)
        }
        throw new Error("Not implemented")
    }
    static _NavPathStack_getIndexByName(ptr: KPointer, name: KStringPtr): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavPathStack_getIndexByName(ptr, name)
        }
        throw new Error("Not implemented")
    }
    static _NavPathStack_getParent(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavPathStack_getParent(ptr)
        }
        throw new Error("Not implemented")
    }
    static _NavPathStack_size(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavPathStack_size(ptr)
        }
        throw new Error("Not implemented")
    }
    static _NavPathStack_disableAnimation(ptr: KPointer, value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavPathStack_disableAnimation(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _NavPathStack_setInterception(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavPathStack_setInterception(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavigationTransitionProxy_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavigationTransitionProxy_ctor()
        }
        throw new Error("Not implemented")
    }
    static _NavigationTransitionProxy_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavigationTransitionProxy_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _NavigationTransitionProxy_finishTransition(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavigationTransitionProxy_finishTransition(ptr)
        }
        throw new Error("Not implemented")
    }
    static _NavigationTransitionProxy_cancelTransition(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavigationTransitionProxy_cancelTransition(ptr)
        }
        throw new Error("Not implemented")
    }
    static _NavigationTransitionProxy_updateTransition(ptr: KPointer, progress: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavigationTransitionProxy_updateTransition(ptr, progress)
        }
        throw new Error("Not implemented")
    }
    static _NavigationTransitionProxy_setFrom(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavigationTransitionProxy_setFrom(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavigationTransitionProxy_setTo(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavigationTransitionProxy_setTo(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _NavigationTransitionProxy_getIsInteractive(ptr: KPointer): boolean {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavigationTransitionProxy_getIsInteractive(ptr)
        }
        throw new Error("Not implemented")
    }
    static _NavigationTransitionProxy_setIsInteractive(ptr: KPointer, isInteractive: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._NavigationTransitionProxy_setIsInteractive(ptr, isInteractive)
        }
        throw new Error("Not implemented")
    }
    static _PatternLockController_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._PatternLockController_ctor()
        }
        throw new Error("Not implemented")
    }
    static _PatternLockController_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._PatternLockController_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _PatternLockController_reset(ptr: KPointer): undefined {
        if ((this._LoadOnce()) == (true))
        {
            return this._PatternLockController_reset(ptr)
        }
        throw new Error("Not implemented")
    }
    static _PatternLockController_setChallengeResult(ptr: KPointer, result: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PatternLockController_setChallengeResult(ptr, result)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorBaseController_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorBaseController_ctor()
        }
        throw new Error("Not implemented")
    }
    static _RichEditorBaseController_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorBaseController_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _RichEditorBaseController_getCaretOffset(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorBaseController_getCaretOffset(ptr)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorBaseController_setCaretOffset(ptr: KPointer, offset: number): boolean {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorBaseController_setCaretOffset(ptr, offset)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorBaseController_closeSelectionMenu(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorBaseController_closeSelectionMenu(ptr)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorBaseController_getTypingStyle(ptr: KPointer): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorBaseController_getTypingStyle(ptr)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorBaseController_setTypingStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorBaseController_setTypingStyle(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorBaseController_setSelection(ptr: KPointer, selectionStart: number, selectionEnd: number, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorBaseController_setSelection(ptr, selectionStart, selectionEnd, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorBaseController_isEditing(ptr: KPointer): boolean {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorBaseController_isEditing(ptr)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorBaseController_stopEditing(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorBaseController_stopEditing(ptr)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorBaseController_getLayoutManager(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorBaseController_getLayoutManager(ptr)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorBaseController_getPreviewText(ptr: KPointer): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorBaseController_getPreviewText(ptr)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorController_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorController_ctor()
        }
        throw new Error("Not implemented")
    }
    static _RichEditorController_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorController_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _RichEditorController_addTextSpan(ptr: KPointer, value: KStringPtr, thisArray: Uint8Array, thisLength: int32): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorController_addTextSpan(ptr, value, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorController_addImageSpan(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorController_addImageSpan(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorController_addBuilderSpan(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorController_addBuilderSpan(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorController_addSymbolSpan(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorController_addSymbolSpan(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorController_updateSpanStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorController_updateSpanStyle(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorController_updateParagraphStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorController_updateParagraphStyle(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorController_deleteSpans(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorController_deleteSpans(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorController_getSpans(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorController_getSpans(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorController_getParagraphs(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorController_getParagraphs(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorController_getSelection(ptr: KPointer): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorController_getSelection(ptr)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorController_fromStyledString(ptr: KPointer, value: KPointer): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorController_fromStyledString(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorController_toStyledString(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorController_toStyledString(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorStyledStringController_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorStyledStringController_ctor()
        }
        throw new Error("Not implemented")
    }
    static _RichEditorStyledStringController_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorStyledStringController_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _RichEditorStyledStringController_setStyledString(ptr: KPointer, styledString: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorStyledStringController_setStyledString(ptr, styledString)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorStyledStringController_getStyledString(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorStyledStringController_getStyledString(ptr)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorStyledStringController_getSelection(ptr: KPointer): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorStyledStringController_getSelection(ptr)
        }
        throw new Error("Not implemented")
    }
    static _RichEditorStyledStringController_onContentChanged(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RichEditorStyledStringController_onContentChanged(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Scroller_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Scroller_ctor()
        }
        throw new Error("Not implemented")
    }
    static _Scroller_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Scroller_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _Scroller_scrollTo(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): undefined {
        if ((this._LoadOnce()) == (true))
        {
            return this._Scroller_scrollTo(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Scroller_scrollEdge(ptr: KPointer, value: KInt, thisArray: Uint8Array, thisLength: int32): undefined {
        if ((this._LoadOnce()) == (true))
        {
            return this._Scroller_scrollEdge(ptr, value, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Scroller_fling(ptr: KPointer, velocity: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._Scroller_fling(ptr, velocity)
        }
        throw new Error("Not implemented")
    }
    static _Scroller_scrollPage0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): undefined {
        if ((this._LoadOnce()) == (true))
        {
            return this._Scroller_scrollPage0(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Scroller_scrollPage1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): undefined {
        if ((this._LoadOnce()) == (true))
        {
            return this._Scroller_scrollPage1(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Scroller_currentOffset(ptr: KPointer): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Scroller_currentOffset(ptr)
        }
        throw new Error("Not implemented")
    }
    static _Scroller_scrollToIndex(ptr: KPointer, value: number, thisArray: Uint8Array, thisLength: int32): undefined {
        if ((this._LoadOnce()) == (true))
        {
            return this._Scroller_scrollToIndex(ptr, value, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _Scroller_scrollBy(ptr: KPointer, dx: Length, dy: Length): undefined {
        if ((this._LoadOnce()) == (true))
        {
            return this._Scroller_scrollBy(ptr, dx, dy)
        }
        throw new Error("Not implemented")
    }
    static _Scroller_isAtEnd(ptr: KPointer): boolean {
        if ((this._LoadOnce()) == (true))
        {
            return this._Scroller_isAtEnd(ptr)
        }
        throw new Error("Not implemented")
    }
    static _Scroller_getItemRect(ptr: KPointer, index: number): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._Scroller_getItemRect(ptr, index)
        }
        throw new Error("Not implemented")
    }
    static _Scroller_getItemIndex(ptr: KPointer, x: number, y: number): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._Scroller_getItemIndex(ptr, x, y)
        }
        throw new Error("Not implemented")
    }
    static _SearchController_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._SearchController_ctor()
        }
        throw new Error("Not implemented")
    }
    static _SearchController_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._SearchController_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _SearchController_caretPosition(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SearchController_caretPosition(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _SearchController_stopEditing(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SearchController_stopEditing(ptr)
        }
        throw new Error("Not implemented")
    }
    static _SearchController_setTextSelection(ptr: KPointer, selectionStart: number, selectionEnd: number, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SearchController_setTextSelection(ptr, selectionStart, selectionEnd, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SwiperController_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwiperController_ctor()
        }
        throw new Error("Not implemented")
    }
    static _SwiperController_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwiperController_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _SwiperController_showNext(ptr: KPointer): undefined {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwiperController_showNext(ptr)
        }
        throw new Error("Not implemented")
    }
    static _SwiperController_showPrevious(ptr: KPointer): undefined {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwiperController_showPrevious(ptr)
        }
        throw new Error("Not implemented")
    }
    static _SwiperController_changeIndex(ptr: KPointer, index: number, thisArray: Uint8Array, thisLength: int32): undefined {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwiperController_changeIndex(ptr, index, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SwiperController_finishAnimation(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): undefined {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwiperController_finishAnimation(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SwiperContentTransitionProxy_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwiperContentTransitionProxy_ctor()
        }
        throw new Error("Not implemented")
    }
    static _SwiperContentTransitionProxy_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwiperContentTransitionProxy_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _SwiperContentTransitionProxy_finishTransition(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwiperContentTransitionProxy_finishTransition(ptr)
        }
        throw new Error("Not implemented")
    }
    static _SwiperContentTransitionProxy_getSelectedIndex(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwiperContentTransitionProxy_getSelectedIndex(ptr)
        }
        throw new Error("Not implemented")
    }
    static _SwiperContentTransitionProxy_setSelectedIndex(ptr: KPointer, selectedIndex: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwiperContentTransitionProxy_setSelectedIndex(ptr, selectedIndex)
        }
        throw new Error("Not implemented")
    }
    static _SwiperContentTransitionProxy_getIndex(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwiperContentTransitionProxy_getIndex(ptr)
        }
        throw new Error("Not implemented")
    }
    static _SwiperContentTransitionProxy_setIndex(ptr: KPointer, index: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwiperContentTransitionProxy_setIndex(ptr, index)
        }
        throw new Error("Not implemented")
    }
    static _SwiperContentTransitionProxy_getPosition(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwiperContentTransitionProxy_getPosition(ptr)
        }
        throw new Error("Not implemented")
    }
    static _SwiperContentTransitionProxy_setPosition(ptr: KPointer, position: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwiperContentTransitionProxy_setPosition(ptr, position)
        }
        throw new Error("Not implemented")
    }
    static _SwiperContentTransitionProxy_getMainAxisLength(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwiperContentTransitionProxy_getMainAxisLength(ptr)
        }
        throw new Error("Not implemented")
    }
    static _SwiperContentTransitionProxy_setMainAxisLength(ptr: KPointer, mainAxisLength: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SwiperContentTransitionProxy_setMainAxisLength(ptr, mainAxisLength)
        }
        throw new Error("Not implemented")
    }
    static _IndicatorComponentController_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._IndicatorComponentController_ctor()
        }
        throw new Error("Not implemented")
    }
    static _IndicatorComponentController_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._IndicatorComponentController_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _IndicatorComponentController_showNext(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._IndicatorComponentController_showNext(ptr)
        }
        throw new Error("Not implemented")
    }
    static _IndicatorComponentController_showPrevious(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._IndicatorComponentController_showPrevious(ptr)
        }
        throw new Error("Not implemented")
    }
    static _IndicatorComponentController_changeIndex(ptr: KPointer, index: number, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._IndicatorComponentController_changeIndex(ptr, index, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _HierarchicalSymbolEffect_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._HierarchicalSymbolEffect_ctor(thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _HierarchicalSymbolEffect_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._HierarchicalSymbolEffect_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _HierarchicalSymbolEffect_getFillStyle(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._HierarchicalSymbolEffect_getFillStyle(ptr)
        }
        throw new Error("Not implemented")
    }
    static _HierarchicalSymbolEffect_setFillStyle(ptr: KPointer, fillStyle: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._HierarchicalSymbolEffect_setFillStyle(ptr, fillStyle)
        }
        throw new Error("Not implemented")
    }
    static _AppearSymbolEffect_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._AppearSymbolEffect_ctor(thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _AppearSymbolEffect_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._AppearSymbolEffect_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _AppearSymbolEffect_getScope(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._AppearSymbolEffect_getScope(ptr)
        }
        throw new Error("Not implemented")
    }
    static _AppearSymbolEffect_setScope(ptr: KPointer, scope: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._AppearSymbolEffect_setScope(ptr, scope)
        }
        throw new Error("Not implemented")
    }
    static _DisappearSymbolEffect_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._DisappearSymbolEffect_ctor(thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _DisappearSymbolEffect_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._DisappearSymbolEffect_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _DisappearSymbolEffect_getScope(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._DisappearSymbolEffect_getScope(ptr)
        }
        throw new Error("Not implemented")
    }
    static _DisappearSymbolEffect_setScope(ptr: KPointer, scope: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._DisappearSymbolEffect_setScope(ptr, scope)
        }
        throw new Error("Not implemented")
    }
    static _BounceSymbolEffect_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._BounceSymbolEffect_ctor(thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _BounceSymbolEffect_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._BounceSymbolEffect_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _BounceSymbolEffect_getScope(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._BounceSymbolEffect_getScope(ptr)
        }
        throw new Error("Not implemented")
    }
    static _BounceSymbolEffect_setScope(ptr: KPointer, scope: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._BounceSymbolEffect_setScope(ptr, scope)
        }
        throw new Error("Not implemented")
    }
    static _BounceSymbolEffect_getDirection(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._BounceSymbolEffect_getDirection(ptr)
        }
        throw new Error("Not implemented")
    }
    static _BounceSymbolEffect_setDirection(ptr: KPointer, direction: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._BounceSymbolEffect_setDirection(ptr, direction)
        }
        throw new Error("Not implemented")
    }
    static _TabsController_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TabsController_ctor()
        }
        throw new Error("Not implemented")
    }
    static _TabsController_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TabsController_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _TabsController_changeIndex(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TabsController_changeIndex(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TabsController_preloadItems(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TabsController_preloadItems(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TabsController_setTabBarTranslate(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TabsController_setTabBarTranslate(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TabsController_setTabBarOpacity(ptr: KPointer, opacity: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TabsController_setTabBarOpacity(ptr, opacity)
        }
        throw new Error("Not implemented")
    }
    static _TabContentTransitionProxy_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TabContentTransitionProxy_ctor()
        }
        throw new Error("Not implemented")
    }
    static _TabContentTransitionProxy_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TabContentTransitionProxy_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _TabContentTransitionProxy_finishTransition(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TabContentTransitionProxy_finishTransition(ptr)
        }
        throw new Error("Not implemented")
    }
    static _TabContentTransitionProxy_getFrom(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._TabContentTransitionProxy_getFrom(ptr)
        }
        throw new Error("Not implemented")
    }
    static _TabContentTransitionProxy_setFrom(ptr: KPointer, from: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TabContentTransitionProxy_setFrom(ptr, from)
        }
        throw new Error("Not implemented")
    }
    static _TabContentTransitionProxy_getTo(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._TabContentTransitionProxy_getTo(ptr)
        }
        throw new Error("Not implemented")
    }
    static _TabContentTransitionProxy_setTo(ptr: KPointer, to: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TabContentTransitionProxy_setTo(ptr, to)
        }
        throw new Error("Not implemented")
    }
    static _TextController_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextController_ctor()
        }
        throw new Error("Not implemented")
    }
    static _TextController_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextController_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _TextController_closeSelectionMenu(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextController_closeSelectionMenu(ptr)
        }
        throw new Error("Not implemented")
    }
    static _TextController_setStyledString(ptr: KPointer, value: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextController_setStyledString(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextController_getLayoutManager(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextController_getLayoutManager(ptr)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaController_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaController_ctor()
        }
        throw new Error("Not implemented")
    }
    static _TextAreaController_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaController_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _TextAreaController_caretPosition(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaController_caretPosition(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaController_setTextSelection(ptr: KPointer, selectionStart: number, selectionEnd: number, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaController_setTextSelection(ptr, selectionStart, selectionEnd, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextAreaController_stopEditing(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextAreaController_stopEditing(ptr)
        }
        throw new Error("Not implemented")
    }
    static _TextClockController_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextClockController_ctor()
        }
        throw new Error("Not implemented")
    }
    static _TextClockController_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextClockController_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _TextClockController_start(ptr: KPointer): undefined {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextClockController_start(ptr)
        }
        throw new Error("Not implemented")
    }
    static _TextClockController_stop(ptr: KPointer): undefined {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextClockController_stop(ptr)
        }
        throw new Error("Not implemented")
    }
    static _TextBaseController_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextBaseController_ctor()
        }
        throw new Error("Not implemented")
    }
    static _TextBaseController_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextBaseController_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _TextBaseController_setSelection(ptr: KPointer, selectionStart: number, selectionEnd: number, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextBaseController_setSelection(ptr, selectionStart, selectionEnd, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextBaseController_closeSelectionMenu(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextBaseController_closeSelectionMenu(ptr)
        }
        throw new Error("Not implemented")
    }
    static _TextBaseController_getLayoutManager(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextBaseController_getLayoutManager(ptr)
        }
        throw new Error("Not implemented")
    }
    static _TextEditControllerEx_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextEditControllerEx_ctor()
        }
        throw new Error("Not implemented")
    }
    static _TextEditControllerEx_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextEditControllerEx_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _TextEditControllerEx_isEditing(ptr: KPointer): boolean {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextEditControllerEx_isEditing(ptr)
        }
        throw new Error("Not implemented")
    }
    static _TextEditControllerEx_stopEditing(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextEditControllerEx_stopEditing(ptr)
        }
        throw new Error("Not implemented")
    }
    static _TextEditControllerEx_setCaretOffset(ptr: KPointer, offset: number): boolean {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextEditControllerEx_setCaretOffset(ptr, offset)
        }
        throw new Error("Not implemented")
    }
    static _TextEditControllerEx_getCaretOffset(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextEditControllerEx_getCaretOffset(ptr)
        }
        throw new Error("Not implemented")
    }
    static _TextEditControllerEx_getPreviewText(ptr: KPointer): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextEditControllerEx_getPreviewText(ptr)
        }
        throw new Error("Not implemented")
    }
    static _StyledStringController_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._StyledStringController_ctor()
        }
        throw new Error("Not implemented")
    }
    static _StyledStringController_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._StyledStringController_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _StyledStringController_setStyledString(ptr: KPointer, styledString: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._StyledStringController_setStyledString(ptr, styledString)
        }
        throw new Error("Not implemented")
    }
    static _StyledStringController_getStyledString(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._StyledStringController_getStyledString(ptr)
        }
        throw new Error("Not implemented")
    }
    static _LayoutManager_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._LayoutManager_ctor()
        }
        throw new Error("Not implemented")
    }
    static _LayoutManager_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._LayoutManager_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _LayoutManager_getLineCount(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._LayoutManager_getLineCount(ptr)
        }
        throw new Error("Not implemented")
    }
    static _LayoutManager_getGlyphPositionAtCoordinate(ptr: KPointer, x: number, y: number): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._LayoutManager_getGlyphPositionAtCoordinate(ptr, x, y)
        }
        throw new Error("Not implemented")
    }
    static _LayoutManager_getLineMetrics(ptr: KPointer, lineNumber: number): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._LayoutManager_getLineMetrics(ptr, lineNumber)
        }
        throw new Error("Not implemented")
    }
    static _LayoutManager_getRectsForRange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32, widthStyle: KInt, heightStyle: KInt): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._LayoutManager_getRectsForRange(ptr, thisArray, thisLength, widthStyle, heightStyle)
        }
        throw new Error("Not implemented")
    }
    static _TextMenuItemId_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextMenuItemId_ctor()
        }
        throw new Error("Not implemented")
    }
    static _TextMenuItemId_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextMenuItemId_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _TextMenuItemId_of(thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextMenuItemId_of(thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextMenuItemId_equals(ptr: KPointer, id: KPointer): boolean {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextMenuItemId_equals(ptr, id)
        }
        throw new Error("Not implemented")
    }
    static _TextMenuItemId_getCUT(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextMenuItemId_getCUT()
        }
        throw new Error("Not implemented")
    }
    static _TextMenuItemId_getCOPY(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextMenuItemId_getCOPY()
        }
        throw new Error("Not implemented")
    }
    static _TextMenuItemId_getPASTE(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextMenuItemId_getPASTE()
        }
        throw new Error("Not implemented")
    }
    static _TextMenuItemId_getSELECT_ALL(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextMenuItemId_getSELECT_ALL()
        }
        throw new Error("Not implemented")
    }
    static _TextMenuItemId_getCOLLABORATION_SERVICE(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextMenuItemId_getCOLLABORATION_SERVICE()
        }
        throw new Error("Not implemented")
    }
    static _TextMenuItemId_getCAMERA_INPUT(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextMenuItemId_getCAMERA_INPUT()
        }
        throw new Error("Not implemented")
    }
    static _TextMenuItemId_getAI_WRITER(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextMenuItemId_getAI_WRITER()
        }
        throw new Error("Not implemented")
    }
    static _EditMenuOptions_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._EditMenuOptions_ctor()
        }
        throw new Error("Not implemented")
    }
    static _EditMenuOptions_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._EditMenuOptions_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _EditMenuOptions_onCreateMenu(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._EditMenuOptions_onCreateMenu(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _EditMenuOptions_onMenuItemClick(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): boolean {
        if ((this._LoadOnce()) == (true))
        {
            return this._EditMenuOptions_onMenuItemClick(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _SubmitEvent_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._SubmitEvent_ctor()
        }
        throw new Error("Not implemented")
    }
    static _SubmitEvent_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._SubmitEvent_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _SubmitEvent_keepEditableState(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SubmitEvent_keepEditableState(ptr)
        }
        throw new Error("Not implemented")
    }
    static _SubmitEvent_getText(ptr: KPointer): string {
        if ((this._LoadOnce()) == (true))
        {
            return this._SubmitEvent_getText(ptr)
        }
        throw new Error("Not implemented")
    }
    static _SubmitEvent_setText(ptr: KPointer, text: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SubmitEvent_setText(ptr, text)
        }
        throw new Error("Not implemented")
    }
    static _TextInputController_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputController_ctor()
        }
        throw new Error("Not implemented")
    }
    static _TextInputController_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputController_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _TextInputController_caretPosition(ptr: KPointer, value: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputController_caretPosition(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _TextInputController_setTextSelection(ptr: KPointer, selectionStart: number, selectionEnd: number, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputController_setTextSelection(ptr, selectionStart, selectionEnd, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextInputController_stopEditing(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextInputController_stopEditing(ptr)
        }
        throw new Error("Not implemented")
    }
    static _TextPickerDialog_show(thisArray: Uint8Array, thisLength: int32): undefined {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextPickerDialog_show(thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextTimerController_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextTimerController_ctor()
        }
        throw new Error("Not implemented")
    }
    static _TextTimerController_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextTimerController_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _TextTimerController_start(ptr: KPointer): undefined {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextTimerController_start(ptr)
        }
        throw new Error("Not implemented")
    }
    static _TextTimerController_pause(ptr: KPointer): undefined {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextTimerController_pause(ptr)
        }
        throw new Error("Not implemented")
    }
    static _TextTimerController_reset(ptr: KPointer): undefined {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextTimerController_reset(ptr)
        }
        throw new Error("Not implemented")
    }
    static _TimePickerDialog_show(thisArray: Uint8Array, thisLength: int32): undefined {
        if ((this._LoadOnce()) == (true))
        {
            return this._TimePickerDialog_show(thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ColorFilter_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ColorFilter_ctor(thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ColorFilter_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ColorFilter_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _VideoController_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._VideoController_ctor()
        }
        throw new Error("Not implemented")
    }
    static _VideoController_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._VideoController_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _VideoController_start(ptr: KPointer): undefined {
        if ((this._LoadOnce()) == (true))
        {
            return this._VideoController_start(ptr)
        }
        throw new Error("Not implemented")
    }
    static _VideoController_pause(ptr: KPointer): undefined {
        if ((this._LoadOnce()) == (true))
        {
            return this._VideoController_pause(ptr)
        }
        throw new Error("Not implemented")
    }
    static _VideoController_stop(ptr: KPointer): undefined {
        if ((this._LoadOnce()) == (true))
        {
            return this._VideoController_stop(ptr)
        }
        throw new Error("Not implemented")
    }
    static _VideoController_setCurrentTime0(ptr: KPointer, value: number): undefined {
        if ((this._LoadOnce()) == (true))
        {
            return this._VideoController_setCurrentTime0(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _VideoController_requestFullscreen(ptr: KPointer, value: KInt): undefined {
        if ((this._LoadOnce()) == (true))
        {
            return this._VideoController_requestFullscreen(ptr, value)
        }
        throw new Error("Not implemented")
    }
    static _VideoController_exitFullscreen(ptr: KPointer): undefined {
        if ((this._LoadOnce()) == (true))
        {
            return this._VideoController_exitFullscreen(ptr)
        }
        throw new Error("Not implemented")
    }
    static _VideoController_setCurrentTime1(ptr: KPointer, value: number, seekMode: KInt): undefined {
        if ((this._LoadOnce()) == (true))
        {
            return this._VideoController_setCurrentTime1(ptr, value, seekMode)
        }
        throw new Error("Not implemented")
    }
    static _VideoController_reset(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._VideoController_reset(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebKeyboardController_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebKeyboardController_ctor()
        }
        throw new Error("Not implemented")
    }
    static _WebKeyboardController_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebKeyboardController_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _WebKeyboardController_insertText(ptr: KPointer, text: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebKeyboardController_insertText(ptr, text)
        }
        throw new Error("Not implemented")
    }
    static _WebKeyboardController_deleteForward(ptr: KPointer, length: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebKeyboardController_deleteForward(ptr, length)
        }
        throw new Error("Not implemented")
    }
    static _WebKeyboardController_deleteBackward(ptr: KPointer, length: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebKeyboardController_deleteBackward(ptr, length)
        }
        throw new Error("Not implemented")
    }
    static _WebKeyboardController_sendFunctionKey(ptr: KPointer, key: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebKeyboardController_sendFunctionKey(ptr, key)
        }
        throw new Error("Not implemented")
    }
    static _WebKeyboardController_close(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebKeyboardController_close(ptr)
        }
        throw new Error("Not implemented")
    }
    static _FullScreenExitHandler_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._FullScreenExitHandler_ctor()
        }
        throw new Error("Not implemented")
    }
    static _FullScreenExitHandler_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._FullScreenExitHandler_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _FullScreenExitHandler_exitFullScreen(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._FullScreenExitHandler_exitFullScreen(ptr)
        }
        throw new Error("Not implemented")
    }
    static _FileSelectorParam_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._FileSelectorParam_ctor()
        }
        throw new Error("Not implemented")
    }
    static _FileSelectorParam_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._FileSelectorParam_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _FileSelectorParam_getTitle(ptr: KPointer): string {
        if ((this._LoadOnce()) == (true))
        {
            return this._FileSelectorParam_getTitle(ptr)
        }
        throw new Error("Not implemented")
    }
    static _FileSelectorParam_getMode(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._FileSelectorParam_getMode(ptr)
        }
        throw new Error("Not implemented")
    }
    static _FileSelectorParam_getAcceptType(ptr: KPointer): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._FileSelectorParam_getAcceptType(ptr)
        }
        throw new Error("Not implemented")
    }
    static _FileSelectorParam_isCapture(ptr: KPointer): boolean {
        if ((this._LoadOnce()) == (true))
        {
            return this._FileSelectorParam_isCapture(ptr)
        }
        throw new Error("Not implemented")
    }
    static _JsResult_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._JsResult_ctor()
        }
        throw new Error("Not implemented")
    }
    static _JsResult_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._JsResult_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _JsResult_handleCancel(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._JsResult_handleCancel(ptr)
        }
        throw new Error("Not implemented")
    }
    static _JsResult_handleConfirm(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._JsResult_handleConfirm(ptr)
        }
        throw new Error("Not implemented")
    }
    static _JsResult_handlePromptConfirm(ptr: KPointer, result: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._JsResult_handlePromptConfirm(ptr, result)
        }
        throw new Error("Not implemented")
    }
    static _FileSelectorResult_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._FileSelectorResult_ctor()
        }
        throw new Error("Not implemented")
    }
    static _FileSelectorResult_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._FileSelectorResult_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _FileSelectorResult_handleFileList(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._FileSelectorResult_handleFileList(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _HttpAuthHandler_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._HttpAuthHandler_ctor()
        }
        throw new Error("Not implemented")
    }
    static _HttpAuthHandler_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._HttpAuthHandler_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _HttpAuthHandler_confirm(ptr: KPointer, userName: KStringPtr, password: KStringPtr): boolean {
        if ((this._LoadOnce()) == (true))
        {
            return this._HttpAuthHandler_confirm(ptr, userName, password)
        }
        throw new Error("Not implemented")
    }
    static _HttpAuthHandler_cancel(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._HttpAuthHandler_cancel(ptr)
        }
        throw new Error("Not implemented")
    }
    static _HttpAuthHandler_isHttpAuthInfoSaved(ptr: KPointer): boolean {
        if ((this._LoadOnce()) == (true))
        {
            return this._HttpAuthHandler_isHttpAuthInfoSaved(ptr)
        }
        throw new Error("Not implemented")
    }
    static _SslErrorHandler_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._SslErrorHandler_ctor()
        }
        throw new Error("Not implemented")
    }
    static _SslErrorHandler_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._SslErrorHandler_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _SslErrorHandler_handleConfirm(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SslErrorHandler_handleConfirm(ptr)
        }
        throw new Error("Not implemented")
    }
    static _SslErrorHandler_handleCancel(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SslErrorHandler_handleCancel(ptr)
        }
        throw new Error("Not implemented")
    }
    static _ClientAuthenticationHandler_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ClientAuthenticationHandler_ctor()
        }
        throw new Error("Not implemented")
    }
    static _ClientAuthenticationHandler_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ClientAuthenticationHandler_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _ClientAuthenticationHandler_confirm0(ptr: KPointer, priKeyFile: KStringPtr, certChainFile: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ClientAuthenticationHandler_confirm0(ptr, priKeyFile, certChainFile)
        }
        throw new Error("Not implemented")
    }
    static _ClientAuthenticationHandler_confirm1(ptr: KPointer, authUri: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ClientAuthenticationHandler_confirm1(ptr, authUri)
        }
        throw new Error("Not implemented")
    }
    static _ClientAuthenticationHandler_cancel(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ClientAuthenticationHandler_cancel(ptr)
        }
        throw new Error("Not implemented")
    }
    static _ClientAuthenticationHandler_ignore(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ClientAuthenticationHandler_ignore(ptr)
        }
        throw new Error("Not implemented")
    }
    static _PermissionRequest_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._PermissionRequest_ctor()
        }
        throw new Error("Not implemented")
    }
    static _PermissionRequest_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._PermissionRequest_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _PermissionRequest_deny(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PermissionRequest_deny(ptr)
        }
        throw new Error("Not implemented")
    }
    static _PermissionRequest_getOrigin(ptr: KPointer): string {
        if ((this._LoadOnce()) == (true))
        {
            return this._PermissionRequest_getOrigin(ptr)
        }
        throw new Error("Not implemented")
    }
    static _PermissionRequest_getAccessibleResource(ptr: KPointer): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._PermissionRequest_getAccessibleResource(ptr)
        }
        throw new Error("Not implemented")
    }
    static _PermissionRequest_grant(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._PermissionRequest_grant(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ScreenCaptureHandler_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScreenCaptureHandler_ctor()
        }
        throw new Error("Not implemented")
    }
    static _ScreenCaptureHandler_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScreenCaptureHandler_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _ScreenCaptureHandler_getOrigin(ptr: KPointer): string {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScreenCaptureHandler_getOrigin(ptr)
        }
        throw new Error("Not implemented")
    }
    static _ScreenCaptureHandler_grant(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScreenCaptureHandler_grant(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ScreenCaptureHandler_deny(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ScreenCaptureHandler_deny(ptr)
        }
        throw new Error("Not implemented")
    }
    static _DataResubmissionHandler_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._DataResubmissionHandler_ctor()
        }
        throw new Error("Not implemented")
    }
    static _DataResubmissionHandler_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._DataResubmissionHandler_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _DataResubmissionHandler_resend(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._DataResubmissionHandler_resend(ptr)
        }
        throw new Error("Not implemented")
    }
    static _DataResubmissionHandler_cancel(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._DataResubmissionHandler_cancel(ptr)
        }
        throw new Error("Not implemented")
    }
    static _ControllerHandler_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ControllerHandler_ctor()
        }
        throw new Error("Not implemented")
    }
    static _ControllerHandler_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ControllerHandler_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _ControllerHandler_setWebController(ptr: KPointer, controller: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ControllerHandler_setWebController(ptr, controller)
        }
        throw new Error("Not implemented")
    }
    static _WebContextMenuParam_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebContextMenuParam_ctor()
        }
        throw new Error("Not implemented")
    }
    static _WebContextMenuParam_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebContextMenuParam_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _WebContextMenuParam_x(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebContextMenuParam_x(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebContextMenuParam_y(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebContextMenuParam_y(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebContextMenuParam_getLinkUrl(ptr: KPointer): string {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebContextMenuParam_getLinkUrl(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebContextMenuParam_getUnfilteredLinkUrl(ptr: KPointer): string {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebContextMenuParam_getUnfilteredLinkUrl(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebContextMenuParam_getSourceUrl(ptr: KPointer): string {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebContextMenuParam_getSourceUrl(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebContextMenuParam_existsImageContents(ptr: KPointer): boolean {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebContextMenuParam_existsImageContents(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebContextMenuParam_getMediaType(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebContextMenuParam_getMediaType(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebContextMenuParam_getSelectionText(ptr: KPointer): string {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebContextMenuParam_getSelectionText(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebContextMenuParam_getSourceType(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebContextMenuParam_getSourceType(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebContextMenuParam_getInputFieldType(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebContextMenuParam_getInputFieldType(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebContextMenuParam_isEditable(ptr: KPointer): boolean {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebContextMenuParam_isEditable(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebContextMenuParam_getEditStateFlags(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebContextMenuParam_getEditStateFlags(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebContextMenuParam_getPreviewWidth(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebContextMenuParam_getPreviewWidth(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebContextMenuParam_getPreviewHeight(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebContextMenuParam_getPreviewHeight(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebContextMenuResult_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebContextMenuResult_ctor()
        }
        throw new Error("Not implemented")
    }
    static _WebContextMenuResult_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebContextMenuResult_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _WebContextMenuResult_closeContextMenu(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebContextMenuResult_closeContextMenu(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebContextMenuResult_copyImage(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebContextMenuResult_copyImage(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebContextMenuResult_copy(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebContextMenuResult_copy(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebContextMenuResult_paste(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebContextMenuResult_paste(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebContextMenuResult_cut(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebContextMenuResult_cut(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebContextMenuResult_selectAll(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebContextMenuResult_selectAll(ptr)
        }
        throw new Error("Not implemented")
    }
    static _ConsoleMessage_ctor(message: KStringPtr, sourceId: KStringPtr, lineNumber: number, messageLevel: KInt): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ConsoleMessage_ctor(message, sourceId, lineNumber, messageLevel)
        }
        throw new Error("Not implemented")
    }
    static _ConsoleMessage_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ConsoleMessage_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _ConsoleMessage_getMessage(ptr: KPointer): string {
        if ((this._LoadOnce()) == (true))
        {
            return this._ConsoleMessage_getMessage(ptr)
        }
        throw new Error("Not implemented")
    }
    static _ConsoleMessage_getSourceId(ptr: KPointer): string {
        if ((this._LoadOnce()) == (true))
        {
            return this._ConsoleMessage_getSourceId(ptr)
        }
        throw new Error("Not implemented")
    }
    static _ConsoleMessage_getLineNumber(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._ConsoleMessage_getLineNumber(ptr)
        }
        throw new Error("Not implemented")
    }
    static _ConsoleMessage_getMessageLevel(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ConsoleMessage_getMessageLevel(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebResourceRequest_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebResourceRequest_ctor()
        }
        throw new Error("Not implemented")
    }
    static _WebResourceRequest_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebResourceRequest_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _WebResourceRequest_getRequestHeader(ptr: KPointer): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebResourceRequest_getRequestHeader(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebResourceRequest_getRequestUrl(ptr: KPointer): string {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebResourceRequest_getRequestUrl(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebResourceRequest_isRequestGesture(ptr: KPointer): boolean {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebResourceRequest_isRequestGesture(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebResourceRequest_isMainFrame(ptr: KPointer): boolean {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebResourceRequest_isMainFrame(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebResourceRequest_isRedirect(ptr: KPointer): boolean {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebResourceRequest_isRedirect(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebResourceRequest_getRequestMethod(ptr: KPointer): string {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebResourceRequest_getRequestMethod(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebResourceResponse_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebResourceResponse_ctor()
        }
        throw new Error("Not implemented")
    }
    static _WebResourceResponse_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebResourceResponse_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _WebResourceResponse_getResponseData(ptr: KPointer): string {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebResourceResponse_getResponseData(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebResourceResponse_getResponseDataEx(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebResourceResponse_getResponseDataEx(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebResourceResponse_getResponseEncoding(ptr: KPointer): string {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebResourceResponse_getResponseEncoding(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebResourceResponse_getResponseMimeType(ptr: KPointer): string {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebResourceResponse_getResponseMimeType(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebResourceResponse_getReasonMessage(ptr: KPointer): string {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebResourceResponse_getReasonMessage(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebResourceResponse_getResponseHeader(ptr: KPointer): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebResourceResponse_getResponseHeader(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebResourceResponse_getResponseCode(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebResourceResponse_getResponseCode(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebResourceResponse_setResponseData(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebResourceResponse_setResponseData(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebResourceResponse_setResponseEncoding(ptr: KPointer, encoding: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebResourceResponse_setResponseEncoding(ptr, encoding)
        }
        throw new Error("Not implemented")
    }
    static _WebResourceResponse_setResponseMimeType(ptr: KPointer, mimeType: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebResourceResponse_setResponseMimeType(ptr, mimeType)
        }
        throw new Error("Not implemented")
    }
    static _WebResourceResponse_setReasonMessage(ptr: KPointer, reason: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebResourceResponse_setReasonMessage(ptr, reason)
        }
        throw new Error("Not implemented")
    }
    static _WebResourceResponse_setResponseHeader(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebResourceResponse_setResponseHeader(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebResourceResponse_setResponseCode(ptr: KPointer, code: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebResourceResponse_setResponseCode(ptr, code)
        }
        throw new Error("Not implemented")
    }
    static _WebResourceResponse_setResponseIsReady(ptr: KPointer, IsReady: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebResourceResponse_setResponseIsReady(ptr, IsReady)
        }
        throw new Error("Not implemented")
    }
    static _WebResourceResponse_getResponseIsReady(ptr: KPointer): boolean {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebResourceResponse_getResponseIsReady(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebResourceError_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebResourceError_ctor()
        }
        throw new Error("Not implemented")
    }
    static _WebResourceError_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebResourceError_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _WebResourceError_getErrorInfo(ptr: KPointer): string {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebResourceError_getErrorInfo(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebResourceError_getErrorCode(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebResourceError_getErrorCode(ptr)
        }
        throw new Error("Not implemented")
    }
    static _JsGeolocation_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._JsGeolocation_ctor()
        }
        throw new Error("Not implemented")
    }
    static _JsGeolocation_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._JsGeolocation_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _JsGeolocation_invoke(ptr: KPointer, origin: KStringPtr, allow: KInt, retain: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._JsGeolocation_invoke(ptr, origin, allow, retain)
        }
        throw new Error("Not implemented")
    }
    static _WebCookie_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebCookie_ctor()
        }
        throw new Error("Not implemented")
    }
    static _WebCookie_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebCookie_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _WebCookie_setCookie(ptr: KPointer): undefined {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebCookie_setCookie(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebCookie_saveCookie(ptr: KPointer): undefined {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebCookie_saveCookie(ptr)
        }
        throw new Error("Not implemented")
    }
    static _EventResult_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._EventResult_ctor()
        }
        throw new Error("Not implemented")
    }
    static _EventResult_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._EventResult_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _EventResult_setGestureEventResult(ptr: KPointer, result: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._EventResult_setGestureEventResult(ptr, result)
        }
        throw new Error("Not implemented")
    }
    static _WebController_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebController_ctor()
        }
        throw new Error("Not implemented")
    }
    static _WebController_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebController_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _WebController_onInactive(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebController_onInactive(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebController_onActive(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebController_onActive(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebController_zoom(ptr: KPointer, factor: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebController_zoom(ptr, factor)
        }
        throw new Error("Not implemented")
    }
    static _WebController_clearHistory(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebController_clearHistory(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebController_runJavaScript(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): undefined {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebController_runJavaScript(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebController_loadData(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): undefined {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebController_loadData(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebController_loadUrl(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): undefined {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebController_loadUrl(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebController_refresh(ptr: KPointer): undefined {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebController_refresh(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebController_stop(ptr: KPointer): undefined {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebController_stop(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebController_registerJavaScriptProxy(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): undefined {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebController_registerJavaScriptProxy(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WebController_deleteJavaScriptRegister(ptr: KPointer, name: KStringPtr): undefined {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebController_deleteJavaScriptRegister(ptr, name)
        }
        throw new Error("Not implemented")
    }
    static _WebController_getHitTest(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebController_getHitTest(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebController_requestFocus(ptr: KPointer): undefined {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebController_requestFocus(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebController_accessBackward(ptr: KPointer): boolean {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebController_accessBackward(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebController_accessForward(ptr: KPointer): boolean {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebController_accessForward(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebController_accessStep(ptr: KPointer, step: number): boolean {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebController_accessStep(ptr, step)
        }
        throw new Error("Not implemented")
    }
    static _WebController_backward(ptr: KPointer): undefined {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebController_backward(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebController_forward(ptr: KPointer): undefined {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebController_forward(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WebController_getCookieManager(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._WebController_getCookieManager(ptr)
        }
        throw new Error("Not implemented")
    }
    static _XComponentController_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._XComponentController_ctor()
        }
        throw new Error("Not implemented")
    }
    static _XComponentController_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._XComponentController_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _XComponentController_getXComponentSurfaceId(ptr: KPointer): string {
        if ((this._LoadOnce()) == (true))
        {
            return this._XComponentController_getXComponentSurfaceId(ptr)
        }
        throw new Error("Not implemented")
    }
    static _XComponentController_getXComponentContext(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._XComponentController_getXComponentContext(ptr)
        }
        throw new Error("Not implemented")
    }
    static _XComponentController_setXComponentSurfaceSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._XComponentController_setXComponentSurfaceSize(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _XComponentController_setXComponentSurfaceRect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._XComponentController_setXComponentSurfaceRect(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _XComponentController_getXComponentSurfaceRect(ptr: KPointer): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._XComponentController_getXComponentSurfaceRect(ptr)
        }
        throw new Error("Not implemented")
    }
    static _XComponentController_setXComponentSurfaceRotation(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._XComponentController_setXComponentSurfaceRotation(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _XComponentController_getXComponentSurfaceRotation(ptr: KPointer): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._XComponentController_getXComponentSurfaceRotation(ptr)
        }
        throw new Error("Not implemented")
    }
    static _XComponentController_onSurfaceCreated(ptr: KPointer, surfaceId: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._XComponentController_onSurfaceCreated(ptr, surfaceId)
        }
        throw new Error("Not implemented")
    }
    static _XComponentController_onSurfaceChanged(ptr: KPointer, surfaceId: KStringPtr, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._XComponentController_onSurfaceChanged(ptr, surfaceId, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _XComponentController_onSurfaceDestroyed(ptr: KPointer, surfaceId: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._XComponentController_onSurfaceDestroyed(ptr, surfaceId)
        }
        throw new Error("Not implemented")
    }
    static _XComponentController_startImageAnalyzer(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._XComponentController_startImageAnalyzer(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _XComponentController_stopImageAnalyzer(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._XComponentController_stopImageAnalyzer(ptr)
        }
        throw new Error("Not implemented")
    }
    static _XComponentController_setOnSurfaceCreatedCallback(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._XComponentController_setOnSurfaceCreatedCallback(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _XComponentController_setOnSurfaceChangedCallback(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._XComponentController_setOnSurfaceChangedCallback(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _XComponentController_setOnSurfaceDestroyedCallback(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._XComponentController_setOnSurfaceDestroyedCallback(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WaterFlowSections_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._WaterFlowSections_ctor()
        }
        throw new Error("Not implemented")
    }
    static _WaterFlowSections_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._WaterFlowSections_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _WaterFlowSections_splice(ptr: KPointer, start: number, thisArray: Uint8Array, thisLength: int32): boolean {
        if ((this._LoadOnce()) == (true))
        {
            return this._WaterFlowSections_splice(ptr, start, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WaterFlowSections_push(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): boolean {
        if ((this._LoadOnce()) == (true))
        {
            return this._WaterFlowSections_push(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WaterFlowSections_update(ptr: KPointer, sectionIndex: number, thisArray: Uint8Array, thisLength: int32): boolean {
        if ((this._LoadOnce()) == (true))
        {
            return this._WaterFlowSections_update(ptr, sectionIndex, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _WaterFlowSections_values(ptr: KPointer): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._WaterFlowSections_values(ptr)
        }
        throw new Error("Not implemented")
    }
    static _WaterFlowSections_length(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._WaterFlowSections_length(ptr)
        }
        throw new Error("Not implemented")
    }
    static _UIExtensionProxy_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._UIExtensionProxy_ctor()
        }
        throw new Error("Not implemented")
    }
    static _UIExtensionProxy_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._UIExtensionProxy_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _UIExtensionProxy_send(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._UIExtensionProxy_send(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _UIExtensionProxy_sendSync(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._UIExtensionProxy_sendSync(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _UIExtensionProxy_onAsyncReceiverRegister(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._UIExtensionProxy_onAsyncReceiverRegister(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _UIExtensionProxy_onSyncReceiverRegister(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._UIExtensionProxy_onSyncReceiverRegister(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _UIExtensionProxy_offAsyncReceiverRegister(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._UIExtensionProxy_offAsyncReceiverRegister(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _UIExtensionProxy_offSyncReceiverRegister(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._UIExtensionProxy_offSyncReceiverRegister(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _StyledString_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._StyledString_ctor(thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _StyledString_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._StyledString_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _StyledString_getString(ptr: KPointer): string {
        if ((this._LoadOnce()) == (true))
        {
            return this._StyledString_getString(ptr)
        }
        throw new Error("Not implemented")
    }
    static _StyledString_getStyles(ptr: KPointer, start: number, length: number, thisArray: Uint8Array, thisLength: int32): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._StyledString_getStyles(ptr, start, length, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _StyledString_equals(ptr: KPointer, other: KPointer): boolean {
        if ((this._LoadOnce()) == (true))
        {
            return this._StyledString_equals(ptr, other)
        }
        throw new Error("Not implemented")
    }
    static _StyledString_subStyledString(ptr: KPointer, start: number, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._StyledString_subStyledString(ptr, start, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _StyledString_fromHtml(html: KStringPtr, thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._StyledString_fromHtml(html, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _StyledString_toHtml(styledString: KPointer): string {
        if ((this._LoadOnce()) == (true))
        {
            return this._StyledString_toHtml(styledString)
        }
        throw new Error("Not implemented")
    }
    static _StyledString_marshalling(styledString: KPointer): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._StyledString_marshalling(styledString)
        }
        throw new Error("Not implemented")
    }
    static _StyledString_unmarshalling(thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._StyledString_unmarshalling(thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _StyledString_getLength(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._StyledString_getLength(ptr)
        }
        throw new Error("Not implemented")
    }
    static _TextStyle_styled_string_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextStyle_styled_string_ctor(thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextStyle_styled_string_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextStyle_styled_string_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _TextStyle_styled_string_getFontFamily(ptr: KPointer): string {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextStyle_styled_string_getFontFamily(ptr)
        }
        throw new Error("Not implemented")
    }
    static _TextStyle_styled_string_getFontSize(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextStyle_styled_string_getFontSize(ptr)
        }
        throw new Error("Not implemented")
    }
    static _TextStyle_styled_string_getFontWeight(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextStyle_styled_string_getFontWeight(ptr)
        }
        throw new Error("Not implemented")
    }
    static _TextStyle_styled_string_getFontStyle(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextStyle_styled_string_getFontStyle(ptr)
        }
        throw new Error("Not implemented")
    }
    static _DecorationStyle_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._DecorationStyle_ctor(thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _DecorationStyle_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._DecorationStyle_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _DecorationStyle_getType(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._DecorationStyle_getType(ptr)
        }
        throw new Error("Not implemented")
    }
    static _DecorationStyle_getStyle(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._DecorationStyle_getStyle(ptr)
        }
        throw new Error("Not implemented")
    }
    static _BaselineOffsetStyle_ctor(value: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._BaselineOffsetStyle_ctor(value)
        }
        throw new Error("Not implemented")
    }
    static _BaselineOffsetStyle_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._BaselineOffsetStyle_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _BaselineOffsetStyle_getBaselineOffset(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._BaselineOffsetStyle_getBaselineOffset(ptr)
        }
        throw new Error("Not implemented")
    }
    static _LetterSpacingStyle_ctor(value: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._LetterSpacingStyle_ctor(value)
        }
        throw new Error("Not implemented")
    }
    static _LetterSpacingStyle_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._LetterSpacingStyle_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _LetterSpacingStyle_getLetterSpacing(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._LetterSpacingStyle_getLetterSpacing(ptr)
        }
        throw new Error("Not implemented")
    }
    static _TextShadowStyle_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextShadowStyle_ctor(thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _TextShadowStyle_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextShadowStyle_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _TextShadowStyle_getTextShadow(ptr: KPointer): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TextShadowStyle_getTextShadow(ptr)
        }
        throw new Error("Not implemented")
    }
    static _BackgroundColorStyle_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._BackgroundColorStyle_ctor(thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _BackgroundColorStyle_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._BackgroundColorStyle_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _GestureStyle_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._GestureStyle_ctor(thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GestureStyle_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._GestureStyle_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _ParagraphStyle_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ParagraphStyle_ctor(thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ParagraphStyle_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ParagraphStyle_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _ParagraphStyle_getTextAlign(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ParagraphStyle_getTextAlign(ptr)
        }
        throw new Error("Not implemented")
    }
    static _ParagraphStyle_getTextIndent(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._ParagraphStyle_getTextIndent(ptr)
        }
        throw new Error("Not implemented")
    }
    static _ParagraphStyle_getMaxLines(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._ParagraphStyle_getMaxLines(ptr)
        }
        throw new Error("Not implemented")
    }
    static _ParagraphStyle_getOverflow(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ParagraphStyle_getOverflow(ptr)
        }
        throw new Error("Not implemented")
    }
    static _ParagraphStyle_getWordBreak(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ParagraphStyle_getWordBreak(ptr)
        }
        throw new Error("Not implemented")
    }
    static _LineHeightStyle_ctor(lineHeight: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._LineHeightStyle_ctor(lineHeight)
        }
        throw new Error("Not implemented")
    }
    static _LineHeightStyle_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._LineHeightStyle_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _LineHeightStyle_getLineHeight(ptr: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._LineHeightStyle_getLineHeight(ptr)
        }
        throw new Error("Not implemented")
    }
    static _UrlStyle_ctor(url: KStringPtr): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._UrlStyle_ctor(url)
        }
        throw new Error("Not implemented")
    }
    static _UrlStyle_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._UrlStyle_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _UrlStyle_getUrl(ptr: KPointer): string {
        if ((this._LoadOnce()) == (true))
        {
            return this._UrlStyle_getUrl(ptr)
        }
        throw new Error("Not implemented")
    }
    static _MutableStyledString_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._MutableStyledString_ctor()
        }
        throw new Error("Not implemented")
    }
    static _MutableStyledString_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._MutableStyledString_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _MutableStyledString_replaceString(ptr: KPointer, start: number, length: number, other: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MutableStyledString_replaceString(ptr, start, length, other)
        }
        throw new Error("Not implemented")
    }
    static _MutableStyledString_insertString(ptr: KPointer, start: number, other: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MutableStyledString_insertString(ptr, start, other)
        }
        throw new Error("Not implemented")
    }
    static _MutableStyledString_removeString(ptr: KPointer, start: number, length: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MutableStyledString_removeString(ptr, start, length)
        }
        throw new Error("Not implemented")
    }
    static _MutableStyledString_replaceStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MutableStyledString_replaceStyle(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _MutableStyledString_setStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MutableStyledString_setStyle(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _MutableStyledString_removeStyle(ptr: KPointer, start: number, length: number, styledKey: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MutableStyledString_removeStyle(ptr, start, length, styledKey)
        }
        throw new Error("Not implemented")
    }
    static _MutableStyledString_removeStyles(ptr: KPointer, start: number, length: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MutableStyledString_removeStyles(ptr, start, length)
        }
        throw new Error("Not implemented")
    }
    static _MutableStyledString_clearStyles(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MutableStyledString_clearStyles(ptr)
        }
        throw new Error("Not implemented")
    }
    static _MutableStyledString_replaceStyledString(ptr: KPointer, start: number, length: number, other: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MutableStyledString_replaceStyledString(ptr, start, length, other)
        }
        throw new Error("Not implemented")
    }
    static _MutableStyledString_insertStyledString(ptr: KPointer, start: number, other: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MutableStyledString_insertStyledString(ptr, start, other)
        }
        throw new Error("Not implemented")
    }
    static _MutableStyledString_appendStyledString(ptr: KPointer, other: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MutableStyledString_appendStyledString(ptr, other)
        }
        throw new Error("Not implemented")
    }
    static _ImageAttachment_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageAttachment_ctor(thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _ImageAttachment_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageAttachment_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _ImageAttachment_getValue(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageAttachment_getValue(ptr)
        }
        throw new Error("Not implemented")
    }
    static _ImageAttachment_getVerticalAlign(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageAttachment_getVerticalAlign(ptr)
        }
        throw new Error("Not implemented")
    }
    static _ImageAttachment_getObjectFit(ptr: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._ImageAttachment_getObjectFit(ptr)
        }
        throw new Error("Not implemented")
    }
    static _CustomSpan_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CustomSpan_ctor()
        }
        throw new Error("Not implemented")
    }
    static _CustomSpan_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CustomSpan_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _CustomSpan_onMeasure(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CustomSpan_onMeasure(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CustomSpan_onDraw(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CustomSpan_onDraw(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _CustomSpan_invalidate(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._CustomSpan_invalidate(ptr)
        }
        throw new Error("Not implemented")
    }
    static _LinearIndicatorController_ctor(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._LinearIndicatorController_ctor()
        }
        throw new Error("Not implemented")
    }
    static _LinearIndicatorController_getFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._LinearIndicatorController_getFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _LinearIndicatorController_setProgress(ptr: KPointer, index: number, progress: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._LinearIndicatorController_setProgress(ptr, index, progress)
        }
        throw new Error("Not implemented")
    }
    static _LinearIndicatorController_start(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._LinearIndicatorController_start(ptr, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _LinearIndicatorController_pause(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._LinearIndicatorController_pause(ptr)
        }
        throw new Error("Not implemented")
    }
    static _LinearIndicatorController_stop(ptr: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._LinearIndicatorController_stop(ptr)
        }
        throw new Error("Not implemented")
    }
    static _GlobalScope_getContext(thisArray: Uint8Array, thisLength: int32): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._GlobalScope_getContext(thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GlobalScope_postCardAction(thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GlobalScope_postCardAction(thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GlobalScope_dollar_r(value: KStringPtr, thisArray: Uint8Array, thisLength: int32): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._GlobalScope_dollar_r(value, thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GlobalScope_dollar_rawfile(value: KStringPtr): KInteropReturnBuffer {
        if ((this._LoadOnce()) == (true))
        {
            return this._GlobalScope_dollar_rawfile(value)
        }
        throw new Error("Not implemented")
    }
    static _GlobalScope_animateTo(thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GlobalScope_animateTo(thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GlobalScope_animateToImmediately(thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GlobalScope_animateToImmediately(thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GlobalScope_vp2px(value: number): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._GlobalScope_vp2px(value)
        }
        throw new Error("Not implemented")
    }
    static _GlobalScope_px2vp(value: number): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._GlobalScope_px2vp(value)
        }
        throw new Error("Not implemented")
    }
    static _GlobalScope_fp2px(value: number): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._GlobalScope_fp2px(value)
        }
        throw new Error("Not implemented")
    }
    static _GlobalScope_px2fp(value: number): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._GlobalScope_px2fp(value)
        }
        throw new Error("Not implemented")
    }
    static _GlobalScope_lpx2px(value: number): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._GlobalScope_lpx2px(value)
        }
        throw new Error("Not implemented")
    }
    static _GlobalScope_px2lpx(value: number): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._GlobalScope_px2lpx(value)
        }
        throw new Error("Not implemented")
    }
    static _GlobalScope_getInspectorNodes(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._GlobalScope_getInspectorNodes()
        }
        throw new Error("Not implemented")
    }
    static _GlobalScope_getInspectorNodeById(id: number): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._GlobalScope_getInspectorNodeById(id)
        }
        throw new Error("Not implemented")
    }
    static _GlobalScope_setAppBgColor(value: KStringPtr): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GlobalScope_setAppBgColor(value)
        }
        throw new Error("Not implemented")
    }
    static _GlobalScope_Profiler_registerVsyncCallback(thisArray: Uint8Array, thisLength: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GlobalScope_Profiler_registerVsyncCallback(thisArray, thisLength)
        }
        throw new Error("Not implemented")
    }
    static _GlobalScope_Profiler_unregisterVsyncCallback(): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GlobalScope_Profiler_unregisterVsyncCallback()
        }
        throw new Error("Not implemented")
    }
    static _GlobalScope_cursorControl_setCursor(value: KInt): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GlobalScope_cursorControl_setCursor(value)
        }
        throw new Error("Not implemented")
    }
    static _GlobalScope_cursorControl_restoreDefault(): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._GlobalScope_cursorControl_restoreDefault()
        }
        throw new Error("Not implemented")
    }
    static _GlobalScope_focusControl_requestFocus(value: KStringPtr): boolean {
        if ((this._LoadOnce()) == (true))
        {
            return this._GlobalScope_focusControl_requestFocus(value)
        }
        throw new Error("Not implemented")
    }
    static _UIStateGet(value: KPointer): int64 {
        if ((this._LoadOnce()) == (true)) {
            return this._UIStateGet(value)
        }
        throw new Error("Not implemented")
    }
}