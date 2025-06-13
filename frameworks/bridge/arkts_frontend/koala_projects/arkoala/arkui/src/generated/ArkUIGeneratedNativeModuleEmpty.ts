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

import { KInt, KLong, KBoolean, KFloat, KUInt, KStringPtr, KPointer, KNativePointer, KInt32ArrayPtr, KUint8ArrayPtr, KFloat32ArrayPtr, pointer, KInteropReturnBuffer } from "@koalaui/interop"
import { int32, int64, float32 } from "@koalaui/common"
import { Length } from "./ArkUnitsInterfaces"

export class ArkUIGeneratedNativeModuleEmpty {
    _Root_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Root_construct")
        return -1
    }
    _ComponentRoot_construct(id: KInt, flags: KInt): KPointer {
        console.log("_ComponentRoot_construct")
        return -1
    }
    _AbilityComponent_construct(id: KInt, flags: KInt): KPointer {
        console.log("_AbilityComponent_construct")
        return -1
    }
    _AbilityComponentInterface_setAbilityComponentOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_AbilityComponentInterface_setAbilityComponentOptions")
    }
    _AbilityComponentAttribute_onConnect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_AbilityComponentAttribute_onConnect")
    }
    _AbilityComponentAttribute_onDisconnect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_AbilityComponentAttribute_onDisconnect")
    }
    _AlphabetIndexer_construct(id: KInt, flags: KInt): KPointer {
        console.log("_AlphabetIndexer_construct")
        return -1
    }
    _AlphabetIndexerInterface_setAlphabetIndexerOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_AlphabetIndexerInterface_setAlphabetIndexerOptions")
    }
    _AlphabetIndexerAttribute_onSelected(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_AlphabetIndexerAttribute_onSelected")
    }
    _AlphabetIndexerAttribute_color(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_AlphabetIndexerAttribute_color")
    }
    _AlphabetIndexerAttribute_selectedColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_AlphabetIndexerAttribute_selectedColor")
    }
    _AlphabetIndexerAttribute_popupColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_AlphabetIndexerAttribute_popupColor")
    }
    _AlphabetIndexerAttribute_selectedBackgroundColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_AlphabetIndexerAttribute_selectedBackgroundColor")
    }
    _AlphabetIndexerAttribute_popupBackground(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_AlphabetIndexerAttribute_popupBackground")
    }
    _AlphabetIndexerAttribute_popupSelectedColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_AlphabetIndexerAttribute_popupSelectedColor")
    }
    _AlphabetIndexerAttribute_popupUnselectedColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_AlphabetIndexerAttribute_popupUnselectedColor")
    }
    _AlphabetIndexerAttribute_popupItemBackgroundColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_AlphabetIndexerAttribute_popupItemBackgroundColor")
    }
    _AlphabetIndexerAttribute_usingPopup(ptr: KPointer, value: KInt): void {
        console.log("_AlphabetIndexerAttribute_usingPopup")
    }
    _AlphabetIndexerAttribute_selectedFont(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_AlphabetIndexerAttribute_selectedFont")
    }
    _AlphabetIndexerAttribute_popupFont(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_AlphabetIndexerAttribute_popupFont")
    }
    _AlphabetIndexerAttribute_popupItemFont(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_AlphabetIndexerAttribute_popupItemFont")
    }
    _AlphabetIndexerAttribute_itemSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_AlphabetIndexerAttribute_itemSize")
    }
    _AlphabetIndexerAttribute_font(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_AlphabetIndexerAttribute_font")
    }
    _AlphabetIndexerAttribute_onSelect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_AlphabetIndexerAttribute_onSelect")
    }
    _AlphabetIndexerAttribute_onRequestPopupData(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_AlphabetIndexerAttribute_onRequestPopupData")
    }
    _AlphabetIndexerAttribute_onPopupSelect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_AlphabetIndexerAttribute_onPopupSelect")
    }
    _AlphabetIndexerAttribute_selected(ptr: KPointer, value: number): void {
        console.log("_AlphabetIndexerAttribute_selected")
    }
    _AlphabetIndexerAttribute_popupPosition(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_AlphabetIndexerAttribute_popupPosition")
    }
    _AlphabetIndexerAttribute_autoCollapse(ptr: KPointer, value: KInt): void {
        console.log("_AlphabetIndexerAttribute_autoCollapse")
    }
    _AlphabetIndexerAttribute_popupItemBorderRadius(ptr: KPointer, value: number): void {
        console.log("_AlphabetIndexerAttribute_popupItemBorderRadius")
    }
    _AlphabetIndexerAttribute_itemBorderRadius(ptr: KPointer, value: number): void {
        console.log("_AlphabetIndexerAttribute_itemBorderRadius")
    }
    _AlphabetIndexerAttribute_popupBackgroundBlurStyle(ptr: KPointer, value: KInt): void {
        console.log("_AlphabetIndexerAttribute_popupBackgroundBlurStyle")
    }
    _AlphabetIndexerAttribute_popupTitleBackground(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_AlphabetIndexerAttribute_popupTitleBackground")
    }
    _AlphabetIndexerAttribute_enableHapticFeedback(ptr: KPointer, value: KInt): void {
        console.log("_AlphabetIndexerAttribute_enableHapticFeedback")
    }
    _AlphabetIndexerAttribute_alignStyle(ptr: KPointer, value: KInt, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_AlphabetIndexerAttribute_alignStyle")
    }
    _AlphabetIndexerAttribute__onChangeEvent_selected(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_AlphabetIndexerAttribute__onChangeEvent_selected")
    }
    _Animator_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Animator_construct")
        return -1
    }
    _AnimatorInterface_setAnimatorOptions(ptr: KPointer, value: KStringPtr): void {
        console.log("_AnimatorInterface_setAnimatorOptions")
    }
    _AnimatorAttribute_state(ptr: KPointer, value: KInt): void {
        console.log("_AnimatorAttribute_state")
    }
    _AnimatorAttribute_duration(ptr: KPointer, value: number): void {
        console.log("_AnimatorAttribute_duration")
    }
    _AnimatorAttribute_curve(ptr: KPointer, value: KInt): void {
        console.log("_AnimatorAttribute_curve")
    }
    _AnimatorAttribute_delay(ptr: KPointer, value: number): void {
        console.log("_AnimatorAttribute_delay")
    }
    _AnimatorAttribute_fillMode(ptr: KPointer, value: KInt): void {
        console.log("_AnimatorAttribute_fillMode")
    }
    _AnimatorAttribute_iterations(ptr: KPointer, value: number): void {
        console.log("_AnimatorAttribute_iterations")
    }
    _AnimatorAttribute_playMode(ptr: KPointer, value: KInt): void {
        console.log("_AnimatorAttribute_playMode")
    }
    _AnimatorAttribute_motion(ptr: KPointer, value: KPointer): void {
        console.log("_AnimatorAttribute_motion")
    }
    _AnimatorAttribute_onStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_AnimatorAttribute_onStart")
    }
    _AnimatorAttribute_onPause(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_AnimatorAttribute_onPause")
    }
    _AnimatorAttribute_onRepeat(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_AnimatorAttribute_onRepeat")
    }
    _AnimatorAttribute_onCancel(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_AnimatorAttribute_onCancel")
    }
    _AnimatorAttribute_onFinish(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_AnimatorAttribute_onFinish")
    }
    _AnimatorAttribute_onFrame(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_AnimatorAttribute_onFrame")
    }
    _Badge_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Badge_construct")
        return -1
    }
    _BadgeInterface_setBadgeOptions0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_BadgeInterface_setBadgeOptions0")
    }
    _BadgeInterface_setBadgeOptions1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_BadgeInterface_setBadgeOptions1")
    }
    _Blank_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Blank_construct")
        return -1
    }
    _BlankInterface_setBlankOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_BlankInterface_setBlankOptions")
    }
    _BlankAttribute_color(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_BlankAttribute_color")
    }
    _Button_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Button_construct")
        return -1
    }
    _ButtonInterface_setButtonOptions0(ptr: KPointer): void {
        console.log("_ButtonInterface_setButtonOptions0")
    }
    _ButtonInterface_setButtonOptions1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ButtonInterface_setButtonOptions1")
    }
    _ButtonInterface_setButtonOptions2(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ButtonInterface_setButtonOptions2")
    }
    _ButtonAttribute_type(ptr: KPointer, value: KInt): void {
        console.log("_ButtonAttribute_type")
    }
    _ButtonAttribute_stateEffect(ptr: KPointer, value: KInt): void {
        console.log("_ButtonAttribute_stateEffect")
    }
    _ButtonAttribute_buttonStyle(ptr: KPointer, value: KInt): void {
        console.log("_ButtonAttribute_buttonStyle")
    }
    _ButtonAttribute_controlSize(ptr: KPointer, value: KInt): void {
        console.log("_ButtonAttribute_controlSize")
    }
    _ButtonAttribute_role(ptr: KPointer, value: KInt): void {
        console.log("_ButtonAttribute_role")
    }
    _ButtonAttribute_fontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ButtonAttribute_fontColor")
    }
    _ButtonAttribute_fontSize(ptr: KPointer, value: Length): void {
        console.log("_ButtonAttribute_fontSize")
    }
    _ButtonAttribute_fontWeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ButtonAttribute_fontWeight")
    }
    _ButtonAttribute_fontStyle(ptr: KPointer, value: KInt): void {
        console.log("_ButtonAttribute_fontStyle")
    }
    _ButtonAttribute_fontFamily(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ButtonAttribute_fontFamily")
    }
    _ButtonAttribute_contentModifier(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ButtonAttribute_contentModifier")
    }
    _ButtonAttribute_labelStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ButtonAttribute_labelStyle")
    }
    _Calendar_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Calendar_construct")
        return -1
    }
    _CalendarInterface_setCalendarOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CalendarInterface_setCalendarOptions")
    }
    _CalendarAttribute_showLunar(ptr: KPointer, value: KInt): void {
        console.log("_CalendarAttribute_showLunar")
    }
    _CalendarAttribute_showHoliday(ptr: KPointer, value: KInt): void {
        console.log("_CalendarAttribute_showHoliday")
    }
    _CalendarAttribute_needSlide(ptr: KPointer, value: KInt): void {
        console.log("_CalendarAttribute_needSlide")
    }
    _CalendarAttribute_startOfWeek(ptr: KPointer, value: number): void {
        console.log("_CalendarAttribute_startOfWeek")
    }
    _CalendarAttribute_offDays(ptr: KPointer, value: number): void {
        console.log("_CalendarAttribute_offDays")
    }
    _CalendarAttribute_direction(ptr: KPointer, value: KInt): void {
        console.log("_CalendarAttribute_direction")
    }
    _CalendarAttribute_currentDayStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CalendarAttribute_currentDayStyle")
    }
    _CalendarAttribute_nonCurrentDayStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CalendarAttribute_nonCurrentDayStyle")
    }
    _CalendarAttribute_todayStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CalendarAttribute_todayStyle")
    }
    _CalendarAttribute_weekStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CalendarAttribute_weekStyle")
    }
    _CalendarAttribute_workStateStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CalendarAttribute_workStateStyle")
    }
    _CalendarAttribute_onSelectChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CalendarAttribute_onSelectChange")
    }
    _CalendarAttribute_onRequestData(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CalendarAttribute_onRequestData")
    }
    _CalendarPicker_construct(id: KInt, flags: KInt): KPointer {
        console.log("_CalendarPicker_construct")
        return -1
    }
    _CalendarPickerInterface_setCalendarPickerOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CalendarPickerInterface_setCalendarPickerOptions")
    }
    _CalendarPickerAttribute_textStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CalendarPickerAttribute_textStyle")
    }
    _CalendarPickerAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CalendarPickerAttribute_onChange")
    }
    _CalendarPickerAttribute_edgeAlign(ptr: KPointer, alignType: KInt, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CalendarPickerAttribute_edgeAlign")
    }
    _Canvas_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Canvas_construct")
        return -1
    }
    _CanvasInterface_setCanvasOptions0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CanvasInterface_setCanvasOptions0")
    }
    _CanvasInterface_setCanvasOptions1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CanvasInterface_setCanvasOptions1")
    }
    _CanvasAttribute_onReady(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CanvasAttribute_onReady")
    }
    _CanvasAttribute_enableAnalyzer(ptr: KPointer, value: KInt): void {
        console.log("_CanvasAttribute_enableAnalyzer")
    }
    _Checkbox_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Checkbox_construct")
        return -1
    }
    _CheckboxInterface_setCheckboxOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CheckboxInterface_setCheckboxOptions")
    }
    _CheckboxAttribute_select(ptr: KPointer, value: KInt): void {
        console.log("_CheckboxAttribute_select")
    }
    _CheckboxAttribute_selectedColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CheckboxAttribute_selectedColor")
    }
    _CheckboxAttribute_shape(ptr: KPointer, value: KInt): void {
        console.log("_CheckboxAttribute_shape")
    }
    _CheckboxAttribute_unselectedColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CheckboxAttribute_unselectedColor")
    }
    _CheckboxAttribute_mark(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CheckboxAttribute_mark")
    }
    _CheckboxAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CheckboxAttribute_onChange")
    }
    _CheckboxAttribute_contentModifier(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CheckboxAttribute_contentModifier")
    }
    _CheckboxAttribute__onChangeEvent_select(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CheckboxAttribute__onChangeEvent_select")
    }
    _CheckboxGroup_construct(id: KInt, flags: KInt): KPointer {
        console.log("_CheckboxGroup_construct")
        return -1
    }
    _CheckboxGroupInterface_setCheckboxGroupOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CheckboxGroupInterface_setCheckboxGroupOptions")
    }
    _CheckboxGroupAttribute_selectAll(ptr: KPointer, value: KInt): void {
        console.log("_CheckboxGroupAttribute_selectAll")
    }
    _CheckboxGroupAttribute_selectedColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CheckboxGroupAttribute_selectedColor")
    }
    _CheckboxGroupAttribute_unselectedColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CheckboxGroupAttribute_unselectedColor")
    }
    _CheckboxGroupAttribute_mark(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CheckboxGroupAttribute_mark")
    }
    _CheckboxGroupAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CheckboxGroupAttribute_onChange")
    }
    _CheckboxGroupAttribute_checkboxShape(ptr: KPointer, value: KInt): void {
        console.log("_CheckboxGroupAttribute_checkboxShape")
    }
    _CheckboxGroupAttribute__onChangeEvent_selectAll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CheckboxGroupAttribute__onChangeEvent_selectAll")
    }
    _Circle_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Circle_construct")
        return -1
    }
    _CircleInterface_setCircleOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CircleInterface_setCircleOptions")
    }
    _Column_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Column_construct")
        return -1
    }
    _ColumnInterface_setColumnOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ColumnInterface_setColumnOptions")
    }
    _ColumnAttribute_alignItems(ptr: KPointer, value: KInt): void {
        console.log("_ColumnAttribute_alignItems")
    }
    _ColumnAttribute_justifyContent(ptr: KPointer, value: KInt): void {
        console.log("_ColumnAttribute_justifyContent")
    }
    _ColumnAttribute_pointLight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ColumnAttribute_pointLight")
    }
    _ColumnAttribute_reverse(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ColumnAttribute_reverse")
    }
    _ColumnSplit_construct(id: KInt, flags: KInt): KPointer {
        console.log("_ColumnSplit_construct")
        return -1
    }
    _ColumnSplitInterface_setColumnSplitOptions(ptr: KPointer): void {
        console.log("_ColumnSplitInterface_setColumnSplitOptions")
    }
    _ColumnSplitAttribute_resizeable(ptr: KPointer, value: KInt): void {
        console.log("_ColumnSplitAttribute_resizeable")
    }
    _ColumnSplitAttribute_divider(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ColumnSplitAttribute_divider")
    }
    _CommonMethod_construct(id: KInt, flags: KInt): KPointer {
        console.log("_CommonMethod_construct")
        return -1
    }
    _CommonMethod_width(ptr: KPointer, value: Length): void {
        console.log("_CommonMethod_width")
    }
    _CommonMethod_height(ptr: KPointer, value: Length): void {
        console.log("_CommonMethod_height")
    }
    _CommonMethod_drawModifier(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_drawModifier")
    }
    _CommonMethod_responseRegion(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_responseRegion")
    }
    _CommonMethod_mouseResponseRegion(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_mouseResponseRegion")
    }
    _CommonMethod_size(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_size")
    }
    _CommonMethod_constraintSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_constraintSize")
    }
    _CommonMethod_touchable(ptr: KPointer, value: KInt): void {
        console.log("_CommonMethod_touchable")
    }
    _CommonMethod_hitTestBehavior(ptr: KPointer, value: KInt): void {
        console.log("_CommonMethod_hitTestBehavior")
    }
    _CommonMethod_onChildTouchTest(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_onChildTouchTest")
    }
    _CommonMethod_layoutWeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_layoutWeight")
    }
    _CommonMethod_chainWeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_chainWeight")
    }
    _CommonMethod_padding(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_padding")
    }
    _CommonMethod_safeAreaPadding(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_safeAreaPadding")
    }
    _CommonMethod_margin(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_margin")
    }
    _CommonMethod_backgroundColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_backgroundColor")
    }
    _CommonMethod_pixelRound(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_pixelRound")
    }
    _CommonMethod_backgroundImageSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_backgroundImageSize")
    }
    _CommonMethod_backgroundImagePosition(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_backgroundImagePosition")
    }
    _CommonMethod_backgroundEffect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_backgroundEffect")
    }
    _CommonMethod_backgroundImageResizable(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_backgroundImageResizable")
    }
    _CommonMethod_foregroundEffect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_foregroundEffect")
    }
    _CommonMethod_visualEffect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_visualEffect")
    }
    _CommonMethod_backgroundFilter(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_backgroundFilter")
    }
    _CommonMethod_foregroundFilter(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_foregroundFilter")
    }
    _CommonMethod_compositingFilter(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_compositingFilter")
    }
    _CommonMethod_opacity(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_opacity")
    }
    _CommonMethod_border(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_border")
    }
    _CommonMethod_borderStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_borderStyle")
    }
    _CommonMethod_borderWidth(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_borderWidth")
    }
    _CommonMethod_borderColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_borderColor")
    }
    _CommonMethod_borderRadius(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_borderRadius")
    }
    _CommonMethod_borderImage(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_borderImage")
    }
    _CommonMethod_outline(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_outline")
    }
    _CommonMethod_outlineStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_outlineStyle")
    }
    _CommonMethod_outlineWidth(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_outlineWidth")
    }
    _CommonMethod_outlineColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_outlineColor")
    }
    _CommonMethod_outlineRadius(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_outlineRadius")
    }
    _CommonMethod_foregroundColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_foregroundColor")
    }
    _CommonMethod_onClick0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_onClick0")
    }
    _CommonMethod_onClick1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32, distanceThreshold: number): void {
        console.log("_CommonMethod_onClick1")
    }
    _CommonMethod_onHover(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_onHover")
    }
    _CommonMethod_onAccessibilityHover(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_onAccessibilityHover")
    }
    _CommonMethod_hoverEffect(ptr: KPointer, value: KInt): void {
        console.log("_CommonMethod_hoverEffect")
    }
    _CommonMethod_onMouse(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_onMouse")
    }
    _CommonMethod_onTouch(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_onTouch")
    }
    _CommonMethod_onKeyEvent(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_onKeyEvent")
    }
    _CommonMethod_onKeyPreIme(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_onKeyPreIme")
    }
    _CommonMethod_focusable(ptr: KPointer, value: KInt): void {
        console.log("_CommonMethod_focusable")
    }
    _CommonMethod_onFocus(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_onFocus")
    }
    _CommonMethod_onBlur(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_onBlur")
    }
    _CommonMethod_tabIndex(ptr: KPointer, value: number): void {
        console.log("_CommonMethod_tabIndex")
    }
    _CommonMethod_defaultFocus(ptr: KPointer, value: KInt): void {
        console.log("_CommonMethod_defaultFocus")
    }
    _CommonMethod_groupDefaultFocus(ptr: KPointer, value: KInt): void {
        console.log("_CommonMethod_groupDefaultFocus")
    }
    _CommonMethod_focusOnTouch(ptr: KPointer, value: KInt): void {
        console.log("_CommonMethod_focusOnTouch")
    }
    _CommonMethod_focusBox(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_focusBox")
    }
    _CommonMethod_animation(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_animation")
    }
    _CommonMethod_transition0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_transition0")
    }
    _CommonMethod_transition1(ptr: KPointer, effect: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_transition1")
    }
    _CommonMethod_motionBlur(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_motionBlur")
    }
    _CommonMethod_brightness(ptr: KPointer, value: number): void {
        console.log("_CommonMethod_brightness")
    }
    _CommonMethod_contrast(ptr: KPointer, value: number): void {
        console.log("_CommonMethod_contrast")
    }
    _CommonMethod_grayscale(ptr: KPointer, value: number): void {
        console.log("_CommonMethod_grayscale")
    }
    _CommonMethod_colorBlend(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_colorBlend")
    }
    _CommonMethod_saturate(ptr: KPointer, value: number): void {
        console.log("_CommonMethod_saturate")
    }
    _CommonMethod_sepia(ptr: KPointer, value: number): void {
        console.log("_CommonMethod_sepia")
    }
    _CommonMethod_invert(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_invert")
    }
    _CommonMethod_hueRotate(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_hueRotate")
    }
    _CommonMethod_useShadowBatching(ptr: KPointer, value: KInt): void {
        console.log("_CommonMethod_useShadowBatching")
    }
    _CommonMethod_useEffect0(ptr: KPointer, value: KInt): void {
        console.log("_CommonMethod_useEffect0")
    }
    _CommonMethod_useEffect1(ptr: KPointer, useEffect: KInt, effectType: KInt): void {
        console.log("_CommonMethod_useEffect1")
    }
    _CommonMethod_renderGroup(ptr: KPointer, value: KInt): void {
        console.log("_CommonMethod_renderGroup")
    }
    _CommonMethod_freeze(ptr: KPointer, value: KInt): void {
        console.log("_CommonMethod_freeze")
    }
    _CommonMethod_translate(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_translate")
    }
    _CommonMethod_scale(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_scale")
    }
    _CommonMethod_gridSpan(ptr: KPointer, value: number): void {
        console.log("_CommonMethod_gridSpan")
    }
    _CommonMethod_gridOffset(ptr: KPointer, value: number): void {
        console.log("_CommonMethod_gridOffset")
    }
    _CommonMethod_rotate(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_rotate")
    }
    _CommonMethod_transform(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_transform")
    }
    _CommonMethod_onAppear(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_onAppear")
    }
    _CommonMethod_onDisAppear(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_onDisAppear")
    }
    _CommonMethod_onAttach(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_onAttach")
    }
    _CommonMethod_onDetach(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_onDetach")
    }
    _CommonMethod_onAreaChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_onAreaChange")
    }
    _CommonMethod_visibility(ptr: KPointer, value: KInt): void {
        console.log("_CommonMethod_visibility")
    }
    _CommonMethod_flexGrow(ptr: KPointer, value: number): void {
        console.log("_CommonMethod_flexGrow")
    }
    _CommonMethod_flexShrink(ptr: KPointer, value: number): void {
        console.log("_CommonMethod_flexShrink")
    }
    _CommonMethod_flexBasis(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_flexBasis")
    }
    _CommonMethod_alignSelf(ptr: KPointer, value: KInt): void {
        console.log("_CommonMethod_alignSelf")
    }
    _CommonMethod_displayPriority(ptr: KPointer, value: number): void {
        console.log("_CommonMethod_displayPriority")
    }
    _CommonMethod_zIndex(ptr: KPointer, value: number): void {
        console.log("_CommonMethod_zIndex")
    }
    _CommonMethod_direction(ptr: KPointer, value: KInt): void {
        console.log("_CommonMethod_direction")
    }
    _CommonMethod_align(ptr: KPointer, value: KInt): void {
        console.log("_CommonMethod_align")
    }
    _CommonMethod_position(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_position")
    }
    _CommonMethod_markAnchor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_markAnchor")
    }
    _CommonMethod_offset(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_offset")
    }
    _CommonMethod_enabled(ptr: KPointer, value: KInt): void {
        console.log("_CommonMethod_enabled")
    }
    _CommonMethod_useSizeType(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_useSizeType")
    }
    _CommonMethod_alignRules0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_alignRules0")
    }
    _CommonMethod_alignRules1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_alignRules1")
    }
    _CommonMethod_aspectRatio(ptr: KPointer, value: number): void {
        console.log("_CommonMethod_aspectRatio")
    }
    _CommonMethod_clickEffect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_clickEffect")
    }
    _CommonMethod_onDragStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_onDragStart")
    }
    _CommonMethod_onDragEnter(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_onDragEnter")
    }
    _CommonMethod_onDragMove(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_onDragMove")
    }
    _CommonMethod_onDragLeave(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_onDragLeave")
    }
    _CommonMethod_onDrop(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_onDrop")
    }
    _CommonMethod_onDragEnd(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_onDragEnd")
    }
    _CommonMethod_allowDrop(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_allowDrop")
    }
    _CommonMethod_draggable(ptr: KPointer, value: KInt): void {
        console.log("_CommonMethod_draggable")
    }
    _CommonMethod_dragPreview(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_dragPreview")
    }
    _CommonMethod_onPreDrag(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_onPreDrag")
    }
    _CommonMethod_linearGradient(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_linearGradient")
    }
    _CommonMethod_sweepGradient(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_sweepGradient")
    }
    _CommonMethod_radialGradient(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_radialGradient")
    }
    _CommonMethod_motionPath(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_motionPath")
    }
    _CommonMethod_shadow(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_shadow")
    }
    _CommonMethod_clip0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_clip0")
    }
    _CommonMethod_clip1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_clip1")
    }
    _CommonMethod_clipShape(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_clipShape")
    }
    _CommonMethod_mask0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_mask0")
    }
    _CommonMethod_mask1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_mask1")
    }
    _CommonMethod_maskShape(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_maskShape")
    }
    _CommonMethod_key(ptr: KPointer, value: KStringPtr): void {
        console.log("_CommonMethod_key")
    }
    _CommonMethod_id(ptr: KPointer, value: KStringPtr): void {
        console.log("_CommonMethod_id")
    }
    _CommonMethod_geometryTransition0(ptr: KPointer, value: KStringPtr): void {
        console.log("_CommonMethod_geometryTransition0")
    }
    _CommonMethod_geometryTransition1(ptr: KPointer, id: KStringPtr, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_geometryTransition1")
    }
    _CommonMethod_stateStyles(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_stateStyles")
    }
    _CommonMethod_restoreId(ptr: KPointer, value: number): void {
        console.log("_CommonMethod_restoreId")
    }
    _CommonMethod_sphericalEffect(ptr: KPointer, value: number): void {
        console.log("_CommonMethod_sphericalEffect")
    }
    _CommonMethod_lightUpEffect(ptr: KPointer, value: number): void {
        console.log("_CommonMethod_lightUpEffect")
    }
    _CommonMethod_pixelStretchEffect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_pixelStretchEffect")
    }
    _CommonMethod_accessibilityGroup0(ptr: KPointer, value: KInt): void {
        console.log("_CommonMethod_accessibilityGroup0")
    }
    _CommonMethod_accessibilityGroup1(ptr: KPointer, isGroup: KInt, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_accessibilityGroup1")
    }
    _CommonMethod_accessibilityText0(ptr: KPointer, value: KStringPtr): void {
        console.log("_CommonMethod_accessibilityText0")
    }
    _CommonMethod_accessibilityText1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_accessibilityText1")
    }
    _CommonMethod_accessibilityTextHint(ptr: KPointer, value: KStringPtr): void {
        console.log("_CommonMethod_accessibilityTextHint")
    }
    _CommonMethod_accessibilityDescription0(ptr: KPointer, value: KStringPtr): void {
        console.log("_CommonMethod_accessibilityDescription0")
    }
    _CommonMethod_accessibilityDescription1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_accessibilityDescription1")
    }
    _CommonMethod_accessibilityLevel(ptr: KPointer, value: KStringPtr): void {
        console.log("_CommonMethod_accessibilityLevel")
    }
    _CommonMethod_accessibilityVirtualNode(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_accessibilityVirtualNode")
    }
    _CommonMethod_accessibilityChecked(ptr: KPointer, value: KInt): void {
        console.log("_CommonMethod_accessibilityChecked")
    }
    _CommonMethod_accessibilitySelected(ptr: KPointer, value: KInt): void {
        console.log("_CommonMethod_accessibilitySelected")
    }
    _CommonMethod_obscured(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_obscured")
    }
    _CommonMethod_reuseId(ptr: KPointer, value: KStringPtr): void {
        console.log("_CommonMethod_reuseId")
    }
    _CommonMethod_renderFit(ptr: KPointer, value: KInt): void {
        console.log("_CommonMethod_renderFit")
    }
    _CommonMethod_gestureModifier(ptr: KPointer, value: KPointer): void {
        console.log("_CommonMethod_gestureModifier")
    }
    _CommonMethod_backgroundBrightness(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_backgroundBrightness")
    }
    _CommonMethod_onGestureJudgeBegin(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_onGestureJudgeBegin")
    }
    _CommonMethod_onGestureRecognizerJudgeBegin0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_onGestureRecognizerJudgeBegin0")
    }
    _CommonMethod_onGestureRecognizerJudgeBegin1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32, exposeInnerGesture: KInt): void {
        console.log("_CommonMethod_onGestureRecognizerJudgeBegin1")
    }
    _CommonMethod_shouldBuiltInRecognizerParallelWith(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_shouldBuiltInRecognizerParallelWith")
    }
    _CommonMethod_monopolizeEvents(ptr: KPointer, value: KInt): void {
        console.log("_CommonMethod_monopolizeEvents")
    }
    _CommonMethod_onTouchIntercept(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_onTouchIntercept")
    }
    _CommonMethod_onSizeChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_onSizeChange")
    }
    _CommonMethod_customProperty(ptr: KPointer, name: KStringPtr, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_customProperty")
    }
    _CommonMethod_expandSafeArea(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_expandSafeArea")
    }
    _CommonMethod_background(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_background")
    }
    _CommonMethod_backgroundImage(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_backgroundImage")
    }
    _CommonMethod_backgroundBlurStyle(ptr: KPointer, value: KInt, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_backgroundBlurStyle")
    }
    _CommonMethod_foregroundBlurStyle(ptr: KPointer, value: KInt, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_foregroundBlurStyle")
    }
    _CommonMethod_focusScopeId0(ptr: KPointer, id: KStringPtr, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_focusScopeId0")
    }
    _CommonMethod_focusScopeId1(ptr: KPointer, id: KStringPtr, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_focusScopeId1")
    }
    _CommonMethod_focusScopePriority(ptr: KPointer, scopeId: KStringPtr, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_focusScopePriority")
    }
    _CommonMethod_gesture(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_gesture")
    }
    _CommonMethod_priorityGesture(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_priorityGesture")
    }
    _CommonMethod_parallelGesture(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_parallelGesture")
    }
    _CommonMethod_blur(ptr: KPointer, value: number, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_blur")
    }
    _CommonMethod_linearGradientBlur(ptr: KPointer, value: number, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_linearGradientBlur")
    }
    _CommonMethod_systemBarEffect(ptr: KPointer): void {
        console.log("_CommonMethod_systemBarEffect")
    }
    _CommonMethod_backdropBlur(ptr: KPointer, value: number, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_backdropBlur")
    }
    _CommonMethod_sharedTransition(ptr: KPointer, id: KStringPtr, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_sharedTransition")
    }
    _CommonMethod_chainMode(ptr: KPointer, direction: KInt, style: KInt): void {
        console.log("_CommonMethod_chainMode")
    }
    _CommonMethod_dragPreviewOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_dragPreviewOptions")
    }
    _CommonMethod_overlay(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_overlay")
    }
    _CommonMethod_blendMode(ptr: KPointer, value: KInt, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_blendMode")
    }
    _CommonMethod_advancedBlendMode(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_advancedBlendMode")
    }
    _CommonMethod_bindPopup(ptr: KPointer, show: KInt, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_bindPopup")
    }
    _CommonMethod_bindMenu0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_bindMenu0")
    }
    _CommonMethod_bindMenu1(ptr: KPointer, isShow: KInt, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_bindMenu1")
    }
    _CommonMethod_bindContextMenu0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32, responseType: KInt): void {
        console.log("_CommonMethod_bindContextMenu0")
    }
    _CommonMethod_bindContextMenu1(ptr: KPointer, isShown: KInt, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_bindContextMenu1")
    }
    _CommonMethod_bindContentCover0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_bindContentCover0")
    }
    _CommonMethod_bindContentCover1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_bindContentCover1")
    }
    _CommonMethod_bindSheet(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_bindSheet")
    }
    _CommonMethod_onVisibleAreaChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_onVisibleAreaChange")
    }
    _CommonMethod_keyboardShortcut(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonMethod_keyboardShortcut")
    }
    _CommonShapeMethod_construct(id: KInt, flags: KInt): KPointer {
        console.log("_CommonShapeMethod_construct")
        return -1
    }
    _CommonShapeMethod_stroke(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonShapeMethod_stroke")
    }
    _CommonShapeMethod_fill(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonShapeMethod_fill")
    }
    _CommonShapeMethod_strokeDashOffset(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonShapeMethod_strokeDashOffset")
    }
    _CommonShapeMethod_strokeLineCap(ptr: KPointer, value: KInt): void {
        console.log("_CommonShapeMethod_strokeLineCap")
    }
    _CommonShapeMethod_strokeLineJoin(ptr: KPointer, value: KInt): void {
        console.log("_CommonShapeMethod_strokeLineJoin")
    }
    _CommonShapeMethod_strokeMiterLimit(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonShapeMethod_strokeMiterLimit")
    }
    _CommonShapeMethod_strokeOpacity(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonShapeMethod_strokeOpacity")
    }
    _CommonShapeMethod_fillOpacity(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonShapeMethod_fillOpacity")
    }
    _CommonShapeMethod_strokeWidth(ptr: KPointer, value: Length): void {
        console.log("_CommonShapeMethod_strokeWidth")
    }
    _CommonShapeMethod_antiAlias(ptr: KPointer, value: KInt): void {
        console.log("_CommonShapeMethod_antiAlias")
    }
    _CommonShapeMethod_strokeDashArray(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CommonShapeMethod_strokeDashArray")
    }
    _Common_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Common_construct")
        return -1
    }
    _CommonInterface_setCommonOptions(ptr: KPointer): void {
        console.log("_CommonInterface_setCommonOptions")
    }
    _ScrollableCommonMethod_construct(id: KInt, flags: KInt): KPointer {
        console.log("_ScrollableCommonMethod_construct")
        return -1
    }
    _ScrollableCommonMethod_scrollBar(ptr: KPointer, value: KInt): void {
        console.log("_ScrollableCommonMethod_scrollBar")
    }
    _ScrollableCommonMethod_scrollBarColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ScrollableCommonMethod_scrollBarColor")
    }
    _ScrollableCommonMethod_scrollBarWidth(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ScrollableCommonMethod_scrollBarWidth")
    }
    _ScrollableCommonMethod_nestedScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ScrollableCommonMethod_nestedScroll")
    }
    _ScrollableCommonMethod_enableScrollInteraction(ptr: KPointer, value: KInt): void {
        console.log("_ScrollableCommonMethod_enableScrollInteraction")
    }
    _ScrollableCommonMethod_friction(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ScrollableCommonMethod_friction")
    }
    _ScrollableCommonMethod_onScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ScrollableCommonMethod_onScroll")
    }
    _ScrollableCommonMethod_onWillScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ScrollableCommonMethod_onWillScroll")
    }
    _ScrollableCommonMethod_onDidScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ScrollableCommonMethod_onDidScroll")
    }
    _ScrollableCommonMethod_onReachStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ScrollableCommonMethod_onReachStart")
    }
    _ScrollableCommonMethod_onReachEnd(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ScrollableCommonMethod_onReachEnd")
    }
    _ScrollableCommonMethod_onScrollStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ScrollableCommonMethod_onScrollStart")
    }
    _ScrollableCommonMethod_onScrollStop(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ScrollableCommonMethod_onScrollStop")
    }
    _ScrollableCommonMethod_flingSpeedLimit(ptr: KPointer, value: number): void {
        console.log("_ScrollableCommonMethod_flingSpeedLimit")
    }
    _ScrollableCommonMethod_clipContent(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ScrollableCommonMethod_clipContent")
    }
    _ScrollableCommonMethod_edgeEffect(ptr: KPointer, edgeEffect: KInt, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ScrollableCommonMethod_edgeEffect")
    }
    _ScrollableCommonMethod_fadingEdge(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ScrollableCommonMethod_fadingEdge")
    }
    _Component3D_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Component3D_construct")
        return -1
    }
    _Component3DInterface_setComponent3DOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_Component3DInterface_setComponent3DOptions")
    }
    _Component3DAttribute_environment(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_Component3DAttribute_environment")
    }
    _Component3DAttribute_shader(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_Component3DAttribute_shader")
    }
    _Component3DAttribute_shaderImageTexture(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_Component3DAttribute_shaderImageTexture")
    }
    _Component3DAttribute_shaderInputBuffer(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_Component3DAttribute_shaderInputBuffer")
    }
    _Component3DAttribute_renderWidth(ptr: KPointer, value: Length): void {
        console.log("_Component3DAttribute_renderWidth")
    }
    _Component3DAttribute_renderHeight(ptr: KPointer, value: Length): void {
        console.log("_Component3DAttribute_renderHeight")
    }
    _Component3DAttribute_customRender(ptr: KPointer, thisArray: Uint8Array, thisLength: int32, selfRenderUpdate: KInt): void {
        console.log("_Component3DAttribute_customRender")
    }
    _ContainerSpan_construct(id: KInt, flags: KInt): KPointer {
        console.log("_ContainerSpan_construct")
        return -1
    }
    _ContainerSpanInterface_setContainerSpanOptions(ptr: KPointer): void {
        console.log("_ContainerSpanInterface_setContainerSpanOptions")
    }
    _ContainerSpanAttribute_textBackgroundStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ContainerSpanAttribute_textBackgroundStyle")
    }
    _Counter_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Counter_construct")
        return -1
    }
    _CounterInterface_setCounterOptions(ptr: KPointer): void {
        console.log("_CounterInterface_setCounterOptions")
    }
    _CounterAttribute_onInc(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CounterAttribute_onInc")
    }
    _CounterAttribute_onDec(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CounterAttribute_onDec")
    }
    _CounterAttribute_enableDec(ptr: KPointer, value: KInt): void {
        console.log("_CounterAttribute_enableDec")
    }
    _CounterAttribute_enableInc(ptr: KPointer, value: KInt): void {
        console.log("_CounterAttribute_enableInc")
    }
    _DataPanel_construct(id: KInt, flags: KInt): KPointer {
        console.log("_DataPanel_construct")
        return -1
    }
    _DataPanelInterface_setDataPanelOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_DataPanelInterface_setDataPanelOptions")
    }
    _DataPanelAttribute_closeEffect(ptr: KPointer, value: KInt): void {
        console.log("_DataPanelAttribute_closeEffect")
    }
    _DataPanelAttribute_valueColors(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_DataPanelAttribute_valueColors")
    }
    _DataPanelAttribute_trackBackgroundColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_DataPanelAttribute_trackBackgroundColor")
    }
    _DataPanelAttribute_strokeWidth(ptr: KPointer, value: Length): void {
        console.log("_DataPanelAttribute_strokeWidth")
    }
    _DataPanelAttribute_trackShadow(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_DataPanelAttribute_trackShadow")
    }
    _DataPanelAttribute_contentModifier(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_DataPanelAttribute_contentModifier")
    }
    _DatePicker_construct(id: KInt, flags: KInt): KPointer {
        console.log("_DatePicker_construct")
        return -1
    }
    _DatePickerInterface_setDatePickerOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_DatePickerInterface_setDatePickerOptions")
    }
    _DatePickerAttribute_lunar(ptr: KPointer, value: KInt): void {
        console.log("_DatePickerAttribute_lunar")
    }
    _DatePickerAttribute_disappearTextStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_DatePickerAttribute_disappearTextStyle")
    }
    _DatePickerAttribute_textStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_DatePickerAttribute_textStyle")
    }
    _DatePickerAttribute_selectedTextStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_DatePickerAttribute_selectedTextStyle")
    }
    _DatePickerAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_DatePickerAttribute_onChange")
    }
    _DatePickerAttribute_onDateChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_DatePickerAttribute_onDateChange")
    }
    _DatePickerAttribute__onChangeEvent_selected(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_DatePickerAttribute__onChangeEvent_selected")
    }
    _Divider_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Divider_construct")
        return -1
    }
    _DividerInterface_setDividerOptions(ptr: KPointer): void {
        console.log("_DividerInterface_setDividerOptions")
    }
    _DividerAttribute_vertical(ptr: KPointer, value: KInt): void {
        console.log("_DividerAttribute_vertical")
    }
    _DividerAttribute_color(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_DividerAttribute_color")
    }
    _DividerAttribute_strokeWidth(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_DividerAttribute_strokeWidth")
    }
    _DividerAttribute_lineCap(ptr: KPointer, value: KInt): void {
        console.log("_DividerAttribute_lineCap")
    }
    _EffectComponent_construct(id: KInt, flags: KInt): KPointer {
        console.log("_EffectComponent_construct")
        return -1
    }
    _EffectComponentInterface_setEffectComponentOptions(ptr: KPointer): void {
        console.log("_EffectComponentInterface_setEffectComponentOptions")
    }
    _Ellipse_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Ellipse_construct")
        return -1
    }
    _EllipseInterface_setEllipseOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_EllipseInterface_setEllipseOptions")
    }
    _EmbeddedComponent_construct(id: KInt, flags: KInt): KPointer {
        console.log("_EmbeddedComponent_construct")
        return -1
    }
    _EmbeddedComponentInterface_setEmbeddedComponentOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32, type: KInt): void {
        console.log("_EmbeddedComponentInterface_setEmbeddedComponentOptions")
    }
    _EmbeddedComponentAttribute_onTerminated(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_EmbeddedComponentAttribute_onTerminated")
    }
    _EmbeddedComponentAttribute_onError(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_EmbeddedComponentAttribute_onError")
    }
    _Flex_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Flex_construct")
        return -1
    }
    _FlexInterface_setFlexOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_FlexInterface_setFlexOptions")
    }
    _FlexAttribute_pointLight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_FlexAttribute_pointLight")
    }
    _FlowItem_construct(id: KInt, flags: KInt): KPointer {
        console.log("_FlowItem_construct")
        return -1
    }
    _FlowItemInterface_setFlowItemOptions(ptr: KPointer): void {
        console.log("_FlowItemInterface_setFlowItemOptions")
    }
    _FolderStack_construct(id: KInt, flags: KInt): KPointer {
        console.log("_FolderStack_construct")
        return -1
    }
    _FolderStackInterface_setFolderStackOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_FolderStackInterface_setFolderStackOptions")
    }
    _FolderStackAttribute_alignContent(ptr: KPointer, value: KInt): void {
        console.log("_FolderStackAttribute_alignContent")
    }
    _FolderStackAttribute_onFolderStateChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_FolderStackAttribute_onFolderStateChange")
    }
    _FolderStackAttribute_onHoverStatusChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_FolderStackAttribute_onHoverStatusChange")
    }
    _FolderStackAttribute_enableAnimation(ptr: KPointer, value: KInt): void {
        console.log("_FolderStackAttribute_enableAnimation")
    }
    _FolderStackAttribute_autoHalfFold(ptr: KPointer, value: KInt): void {
        console.log("_FolderStackAttribute_autoHalfFold")
    }
    _FormComponent_construct(id: KInt, flags: KInt): KPointer {
        console.log("_FormComponent_construct")
        return -1
    }
    _FormComponentInterface_setFormComponentOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_FormComponentInterface_setFormComponentOptions")
    }
    _FormComponentAttribute_size(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_FormComponentAttribute_size")
    }
    _FormComponentAttribute_moduleName(ptr: KPointer, value: KStringPtr): void {
        console.log("_FormComponentAttribute_moduleName")
    }
    _FormComponentAttribute_dimension(ptr: KPointer, value: KInt): void {
        console.log("_FormComponentAttribute_dimension")
    }
    _FormComponentAttribute_allowUpdate(ptr: KPointer, value: KInt): void {
        console.log("_FormComponentAttribute_allowUpdate")
    }
    _FormComponentAttribute_visibility(ptr: KPointer, value: KInt): void {
        console.log("_FormComponentAttribute_visibility")
    }
    _FormComponentAttribute_onAcquired(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_FormComponentAttribute_onAcquired")
    }
    _FormComponentAttribute_onError(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_FormComponentAttribute_onError")
    }
    _FormComponentAttribute_onRouter(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_FormComponentAttribute_onRouter")
    }
    _FormComponentAttribute_onUninstall(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_FormComponentAttribute_onUninstall")
    }
    _FormComponentAttribute_onLoad(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_FormComponentAttribute_onLoad")
    }
    _FormLink_construct(id: KInt, flags: KInt): KPointer {
        console.log("_FormLink_construct")
        return -1
    }
    _FormLinkInterface_setFormLinkOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_FormLinkInterface_setFormLinkOptions")
    }
    _Gauge_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Gauge_construct")
        return -1
    }
    _GaugeInterface_setGaugeOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_GaugeInterface_setGaugeOptions")
    }
    _GaugeAttribute_value(ptr: KPointer, value: number): void {
        console.log("_GaugeAttribute_value")
    }
    _GaugeAttribute_startAngle(ptr: KPointer, value: number): void {
        console.log("_GaugeAttribute_startAngle")
    }
    _GaugeAttribute_endAngle(ptr: KPointer, value: number): void {
        console.log("_GaugeAttribute_endAngle")
    }
    _GaugeAttribute_colors(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_GaugeAttribute_colors")
    }
    _GaugeAttribute_strokeWidth(ptr: KPointer, value: Length): void {
        console.log("_GaugeAttribute_strokeWidth")
    }
    _GaugeAttribute_description(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_GaugeAttribute_description")
    }
    _GaugeAttribute_trackShadow(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_GaugeAttribute_trackShadow")
    }
    _GaugeAttribute_indicator(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_GaugeAttribute_indicator")
    }
    _GaugeAttribute_privacySensitive(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_GaugeAttribute_privacySensitive")
    }
    _GaugeAttribute_contentModifier(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_GaugeAttribute_contentModifier")
    }
    _Grid_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Grid_construct")
        return -1
    }
    _GridInterface_setGridOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_GridInterface_setGridOptions")
    }
    _GridAttribute_columnsTemplate(ptr: KPointer, value: KStringPtr): void {
        console.log("_GridAttribute_columnsTemplate")
    }
    _GridAttribute_rowsTemplate(ptr: KPointer, value: KStringPtr): void {
        console.log("_GridAttribute_rowsTemplate")
    }
    _GridAttribute_columnsGap(ptr: KPointer, value: Length): void {
        console.log("_GridAttribute_columnsGap")
    }
    _GridAttribute_rowsGap(ptr: KPointer, value: Length): void {
        console.log("_GridAttribute_rowsGap")
    }
    _GridAttribute_scrollBarWidth(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_GridAttribute_scrollBarWidth")
    }
    _GridAttribute_scrollBarColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_GridAttribute_scrollBarColor")
    }
    _GridAttribute_scrollBar(ptr: KPointer, value: KInt): void {
        console.log("_GridAttribute_scrollBar")
    }
    _GridAttribute_onScrollBarUpdate(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_GridAttribute_onScrollBarUpdate")
    }
    _GridAttribute_onScrollIndex(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_GridAttribute_onScrollIndex")
    }
    _GridAttribute_cachedCount0(ptr: KPointer, value: number): void {
        console.log("_GridAttribute_cachedCount0")
    }
    _GridAttribute_cachedCount1(ptr: KPointer, count: number, show: KInt): void {
        console.log("_GridAttribute_cachedCount1")
    }
    _GridAttribute_editMode(ptr: KPointer, value: KInt): void {
        console.log("_GridAttribute_editMode")
    }
    _GridAttribute_multiSelectable(ptr: KPointer, value: KInt): void {
        console.log("_GridAttribute_multiSelectable")
    }
    _GridAttribute_maxCount(ptr: KPointer, value: number): void {
        console.log("_GridAttribute_maxCount")
    }
    _GridAttribute_minCount(ptr: KPointer, value: number): void {
        console.log("_GridAttribute_minCount")
    }
    _GridAttribute_cellLength(ptr: KPointer, value: number): void {
        console.log("_GridAttribute_cellLength")
    }
    _GridAttribute_layoutDirection(ptr: KPointer, value: KInt): void {
        console.log("_GridAttribute_layoutDirection")
    }
    _GridAttribute_supportAnimation(ptr: KPointer, value: KInt): void {
        console.log("_GridAttribute_supportAnimation")
    }
    _GridAttribute_onItemDragStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_GridAttribute_onItemDragStart")
    }
    _GridAttribute_onItemDragEnter(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_GridAttribute_onItemDragEnter")
    }
    _GridAttribute_onItemDragMove(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_GridAttribute_onItemDragMove")
    }
    _GridAttribute_onItemDragLeave(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_GridAttribute_onItemDragLeave")
    }
    _GridAttribute_onItemDrop(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_GridAttribute_onItemDrop")
    }
    _GridAttribute_nestedScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_GridAttribute_nestedScroll")
    }
    _GridAttribute_enableScrollInteraction(ptr: KPointer, value: KInt): void {
        console.log("_GridAttribute_enableScrollInteraction")
    }
    _GridAttribute_friction(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_GridAttribute_friction")
    }
    _GridAttribute_alignItems(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_GridAttribute_alignItems")
    }
    _GridAttribute_onScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_GridAttribute_onScroll")
    }
    _GridAttribute_onReachStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_GridAttribute_onReachStart")
    }
    _GridAttribute_onReachEnd(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_GridAttribute_onReachEnd")
    }
    _GridAttribute_onScrollStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_GridAttribute_onScrollStart")
    }
    _GridAttribute_onScrollStop(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_GridAttribute_onScrollStop")
    }
    _GridAttribute_onScrollFrameBegin(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_GridAttribute_onScrollFrameBegin")
    }
    _GridAttribute_edgeEffect(ptr: KPointer, value: KInt, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_GridAttribute_edgeEffect")
    }
    _GridItem_construct(id: KInt, flags: KInt): KPointer {
        console.log("_GridItem_construct")
        return -1
    }
    _GridItemInterface_setGridItemOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_GridItemInterface_setGridItemOptions")
    }
    _GridItemAttribute_rowStart(ptr: KPointer, value: number): void {
        console.log("_GridItemAttribute_rowStart")
    }
    _GridItemAttribute_rowEnd(ptr: KPointer, value: number): void {
        console.log("_GridItemAttribute_rowEnd")
    }
    _GridItemAttribute_columnStart(ptr: KPointer, value: number): void {
        console.log("_GridItemAttribute_columnStart")
    }
    _GridItemAttribute_columnEnd(ptr: KPointer, value: number): void {
        console.log("_GridItemAttribute_columnEnd")
    }
    _GridItemAttribute_forceRebuild(ptr: KPointer, value: KInt): void {
        console.log("_GridItemAttribute_forceRebuild")
    }
    _GridItemAttribute_selectable(ptr: KPointer, value: KInt): void {
        console.log("_GridItemAttribute_selectable")
    }
    _GridItemAttribute_selected(ptr: KPointer, value: KInt): void {
        console.log("_GridItemAttribute_selected")
    }
    _GridItemAttribute_onSelect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_GridItemAttribute_onSelect")
    }
    _GridItemAttribute__onChangeEvent_selected(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_GridItemAttribute__onChangeEvent_selected")
    }
    _GridCol_construct(id: KInt, flags: KInt): KPointer {
        console.log("_GridCol_construct")
        return -1
    }
    _GridColInterface_setGridColOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_GridColInterface_setGridColOptions")
    }
    _GridColAttribute_span(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_GridColAttribute_span")
    }
    _GridColAttribute_gridColOffset(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_GridColAttribute_gridColOffset")
    }
    _GridColAttribute_order(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_GridColAttribute_order")
    }
    _GridContainer_construct(id: KInt, flags: KInt): KPointer {
        console.log("_GridContainer_construct")
        return -1
    }
    _GridContainerInterface_setGridContainerOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_GridContainerInterface_setGridContainerOptions")
    }
    _GridRow_construct(id: KInt, flags: KInt): KPointer {
        console.log("_GridRow_construct")
        return -1
    }
    _GridRowInterface_setGridRowOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_GridRowInterface_setGridRowOptions")
    }
    _GridRowAttribute_onBreakpointChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_GridRowAttribute_onBreakpointChange")
    }
    _GridRowAttribute_alignItems(ptr: KPointer, value: KInt): void {
        console.log("_GridRowAttribute_alignItems")
    }
    _Hyperlink_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Hyperlink_construct")
        return -1
    }
    _HyperlinkInterface_setHyperlinkOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_HyperlinkInterface_setHyperlinkOptions")
    }
    _HyperlinkAttribute_color(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_HyperlinkAttribute_color")
    }
    _Image_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Image_construct")
        return -1
    }
    _ImageInterface_setImageOptions0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ImageInterface_setImageOptions0")
    }
    _ImageInterface_setImageOptions1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ImageInterface_setImageOptions1")
    }
    _ImageInterface_setImageOptions2(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ImageInterface_setImageOptions2")
    }
    _ImageAttribute_alt(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ImageAttribute_alt")
    }
    _ImageAttribute_matchTextDirection(ptr: KPointer, value: KInt): void {
        console.log("_ImageAttribute_matchTextDirection")
    }
    _ImageAttribute_fitOriginalSize(ptr: KPointer, value: KInt): void {
        console.log("_ImageAttribute_fitOriginalSize")
    }
    _ImageAttribute_fillColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ImageAttribute_fillColor")
    }
    _ImageAttribute_objectFit(ptr: KPointer, value: KInt): void {
        console.log("_ImageAttribute_objectFit")
    }
    _ImageAttribute_objectRepeat(ptr: KPointer, value: KInt): void {
        console.log("_ImageAttribute_objectRepeat")
    }
    _ImageAttribute_autoResize(ptr: KPointer, value: KInt): void {
        console.log("_ImageAttribute_autoResize")
    }
    _ImageAttribute_renderMode(ptr: KPointer, value: KInt): void {
        console.log("_ImageAttribute_renderMode")
    }
    _ImageAttribute_dynamicRangeMode(ptr: KPointer, value: KInt): void {
        console.log("_ImageAttribute_dynamicRangeMode")
    }
    _ImageAttribute_interpolation(ptr: KPointer, value: KInt): void {
        console.log("_ImageAttribute_interpolation")
    }
    _ImageAttribute_sourceSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ImageAttribute_sourceSize")
    }
    _ImageAttribute_syncLoad(ptr: KPointer, value: KInt): void {
        console.log("_ImageAttribute_syncLoad")
    }
    _ImageAttribute_colorFilter(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ImageAttribute_colorFilter")
    }
    _ImageAttribute_copyOption(ptr: KPointer, value: KInt): void {
        console.log("_ImageAttribute_copyOption")
    }
    _ImageAttribute_draggable(ptr: KPointer, value: KInt): void {
        console.log("_ImageAttribute_draggable")
    }
    _ImageAttribute_pointLight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ImageAttribute_pointLight")
    }
    _ImageAttribute_edgeAntialiasing(ptr: KPointer, value: number): void {
        console.log("_ImageAttribute_edgeAntialiasing")
    }
    _ImageAttribute_onComplete(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ImageAttribute_onComplete")
    }
    _ImageAttribute_onError(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ImageAttribute_onError")
    }
    _ImageAttribute_onFinish(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ImageAttribute_onFinish")
    }
    _ImageAttribute_enableAnalyzer(ptr: KPointer, value: KInt): void {
        console.log("_ImageAttribute_enableAnalyzer")
    }
    _ImageAttribute_analyzerConfig(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ImageAttribute_analyzerConfig")
    }
    _ImageAttribute_resizable(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ImageAttribute_resizable")
    }
    _ImageAttribute_privacySensitive(ptr: KPointer, value: KInt): void {
        console.log("_ImageAttribute_privacySensitive")
    }
    _ImageAttribute_enhancedImageQuality(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ImageAttribute_enhancedImageQuality")
    }
    _ImageAnimator_construct(id: KInt, flags: KInt): KPointer {
        console.log("_ImageAnimator_construct")
        return -1
    }
    _ImageAnimatorInterface_setImageAnimatorOptions(ptr: KPointer): void {
        console.log("_ImageAnimatorInterface_setImageAnimatorOptions")
    }
    _ImageAnimatorAttribute_images(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ImageAnimatorAttribute_images")
    }
    _ImageAnimatorAttribute_state(ptr: KPointer, value: KInt): void {
        console.log("_ImageAnimatorAttribute_state")
    }
    _ImageAnimatorAttribute_duration(ptr: KPointer, value: number): void {
        console.log("_ImageAnimatorAttribute_duration")
    }
    _ImageAnimatorAttribute_reverse(ptr: KPointer, value: KInt): void {
        console.log("_ImageAnimatorAttribute_reverse")
    }
    _ImageAnimatorAttribute_fixedSize(ptr: KPointer, value: KInt): void {
        console.log("_ImageAnimatorAttribute_fixedSize")
    }
    _ImageAnimatorAttribute_preDecode(ptr: KPointer, value: number): void {
        console.log("_ImageAnimatorAttribute_preDecode")
    }
    _ImageAnimatorAttribute_fillMode(ptr: KPointer, value: KInt): void {
        console.log("_ImageAnimatorAttribute_fillMode")
    }
    _ImageAnimatorAttribute_iterations(ptr: KPointer, value: number): void {
        console.log("_ImageAnimatorAttribute_iterations")
    }
    _ImageAnimatorAttribute_onStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ImageAnimatorAttribute_onStart")
    }
    _ImageAnimatorAttribute_onPause(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ImageAnimatorAttribute_onPause")
    }
    _ImageAnimatorAttribute_onRepeat(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ImageAnimatorAttribute_onRepeat")
    }
    _ImageAnimatorAttribute_onCancel(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ImageAnimatorAttribute_onCancel")
    }
    _ImageAnimatorAttribute_onFinish(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ImageAnimatorAttribute_onFinish")
    }
    _ImageSpan_construct(id: KInt, flags: KInt): KPointer {
        console.log("_ImageSpan_construct")
        return -1
    }
    _ImageSpanInterface_setImageSpanOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ImageSpanInterface_setImageSpanOptions")
    }
    _ImageSpanAttribute_verticalAlign(ptr: KPointer, value: KInt): void {
        console.log("_ImageSpanAttribute_verticalAlign")
    }
    _ImageSpanAttribute_colorFilter(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ImageSpanAttribute_colorFilter")
    }
    _ImageSpanAttribute_objectFit(ptr: KPointer, value: KInt): void {
        console.log("_ImageSpanAttribute_objectFit")
    }
    _ImageSpanAttribute_onComplete(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ImageSpanAttribute_onComplete")
    }
    _ImageSpanAttribute_onError(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ImageSpanAttribute_onError")
    }
    _ImageSpanAttribute_alt(ptr: KPointer, value: KPointer): void {
        console.log("_ImageSpanAttribute_alt")
    }
    _Line_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Line_construct")
        return -1
    }
    _LineInterface_setLineOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_LineInterface_setLineOptions")
    }
    _LineAttribute_startPoint(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_LineAttribute_startPoint")
    }
    _LineAttribute_endPoint(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_LineAttribute_endPoint")
    }
    _List_construct(id: KInt, flags: KInt): KPointer {
        console.log("_List_construct")
        return -1
    }
    _ListInterface_setListOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ListInterface_setListOptions")
    }
    _ListAttribute_alignListItem(ptr: KPointer, value: KInt): void {
        console.log("_ListAttribute_alignListItem")
    }
    _ListAttribute_listDirection(ptr: KPointer, value: KInt): void {
        console.log("_ListAttribute_listDirection")
    }
    _ListAttribute_scrollBar(ptr: KPointer, value: KInt): void {
        console.log("_ListAttribute_scrollBar")
    }
    _ListAttribute_contentStartOffset(ptr: KPointer, value: number): void {
        console.log("_ListAttribute_contentStartOffset")
    }
    _ListAttribute_contentEndOffset(ptr: KPointer, value: number): void {
        console.log("_ListAttribute_contentEndOffset")
    }
    _ListAttribute_divider(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ListAttribute_divider")
    }
    _ListAttribute_editMode(ptr: KPointer, value: KInt): void {
        console.log("_ListAttribute_editMode")
    }
    _ListAttribute_multiSelectable(ptr: KPointer, value: KInt): void {
        console.log("_ListAttribute_multiSelectable")
    }
    _ListAttribute_cachedCount0(ptr: KPointer, value: number): void {
        console.log("_ListAttribute_cachedCount0")
    }
    _ListAttribute_cachedCount1(ptr: KPointer, count: number, show: KInt): void {
        console.log("_ListAttribute_cachedCount1")
    }
    _ListAttribute_chainAnimation(ptr: KPointer, value: KInt): void {
        console.log("_ListAttribute_chainAnimation")
    }
    _ListAttribute_chainAnimationOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ListAttribute_chainAnimationOptions")
    }
    _ListAttribute_sticky(ptr: KPointer, value: KInt): void {
        console.log("_ListAttribute_sticky")
    }
    _ListAttribute_scrollSnapAlign(ptr: KPointer, value: KInt): void {
        console.log("_ListAttribute_scrollSnapAlign")
    }
    _ListAttribute_nestedScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ListAttribute_nestedScroll")
    }
    _ListAttribute_enableScrollInteraction(ptr: KPointer, value: KInt): void {
        console.log("_ListAttribute_enableScrollInteraction")
    }
    _ListAttribute_friction(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ListAttribute_friction")
    }
    _ListAttribute_childrenMainSize(ptr: KPointer, value: KPointer): void {
        console.log("_ListAttribute_childrenMainSize")
    }
    _ListAttribute_maintainVisibleContentPosition(ptr: KPointer, value: KInt): void {
        console.log("_ListAttribute_maintainVisibleContentPosition")
    }
    _ListAttribute_onScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ListAttribute_onScroll")
    }
    _ListAttribute_onScrollIndex(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ListAttribute_onScrollIndex")
    }
    _ListAttribute_onScrollVisibleContentChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ListAttribute_onScrollVisibleContentChange")
    }
    _ListAttribute_onReachStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ListAttribute_onReachStart")
    }
    _ListAttribute_onReachEnd(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ListAttribute_onReachEnd")
    }
    _ListAttribute_onScrollStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ListAttribute_onScrollStart")
    }
    _ListAttribute_onScrollStop(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ListAttribute_onScrollStop")
    }
    _ListAttribute_onItemDelete(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ListAttribute_onItemDelete")
    }
    _ListAttribute_onItemMove(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ListAttribute_onItemMove")
    }
    _ListAttribute_onItemDragStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ListAttribute_onItemDragStart")
    }
    _ListAttribute_onItemDragEnter(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ListAttribute_onItemDragEnter")
    }
    _ListAttribute_onItemDragMove(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ListAttribute_onItemDragMove")
    }
    _ListAttribute_onItemDragLeave(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ListAttribute_onItemDragLeave")
    }
    _ListAttribute_onItemDrop(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ListAttribute_onItemDrop")
    }
    _ListAttribute_onScrollFrameBegin(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ListAttribute_onScrollFrameBegin")
    }
    _ListAttribute_lanes(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ListAttribute_lanes")
    }
    _ListAttribute_edgeEffect(ptr: KPointer, value: KInt, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ListAttribute_edgeEffect")
    }
    _ListItem_construct(id: KInt, flags: KInt): KPointer {
        console.log("_ListItem_construct")
        return -1
    }
    _ListItemInterface_setListItemOptions0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ListItemInterface_setListItemOptions0")
    }
    _ListItemInterface_setListItemOptions1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ListItemInterface_setListItemOptions1")
    }
    _ListItemAttribute_sticky(ptr: KPointer, value: KInt): void {
        console.log("_ListItemAttribute_sticky")
    }
    _ListItemAttribute_editable(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ListItemAttribute_editable")
    }
    _ListItemAttribute_selectable(ptr: KPointer, value: KInt): void {
        console.log("_ListItemAttribute_selectable")
    }
    _ListItemAttribute_selected(ptr: KPointer, value: KInt): void {
        console.log("_ListItemAttribute_selected")
    }
    _ListItemAttribute_swipeAction(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ListItemAttribute_swipeAction")
    }
    _ListItemAttribute_onSelect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ListItemAttribute_onSelect")
    }
    _ListItemAttribute__onChangeEvent_selected(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ListItemAttribute__onChangeEvent_selected")
    }
    _ListItemGroup_construct(id: KInt, flags: KInt): KPointer {
        console.log("_ListItemGroup_construct")
        return -1
    }
    _ListItemGroupInterface_setListItemGroupOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ListItemGroupInterface_setListItemGroupOptions")
    }
    _ListItemGroupAttribute_divider(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ListItemGroupAttribute_divider")
    }
    _ListItemGroupAttribute_childrenMainSize(ptr: KPointer, value: KPointer): void {
        console.log("_ListItemGroupAttribute_childrenMainSize")
    }
    _LoadingProgress_construct(id: KInt, flags: KInt): KPointer {
        console.log("_LoadingProgress_construct")
        return -1
    }
    _LoadingProgressInterface_setLoadingProgressOptions(ptr: KPointer): void {
        console.log("_LoadingProgressInterface_setLoadingProgressOptions")
    }
    _LoadingProgressAttribute_color(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_LoadingProgressAttribute_color")
    }
    _LoadingProgressAttribute_enableLoading(ptr: KPointer, value: KInt): void {
        console.log("_LoadingProgressAttribute_enableLoading")
    }
    _LoadingProgressAttribute_contentModifier(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_LoadingProgressAttribute_contentModifier")
    }
    _LocationButton_construct(id: KInt, flags: KInt): KPointer {
        console.log("_LocationButton_construct")
        return -1
    }
    _LocationButtonInterface_setLocationButtonOptions0(ptr: KPointer): void {
        console.log("_LocationButtonInterface_setLocationButtonOptions0")
    }
    _LocationButtonInterface_setLocationButtonOptions1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_LocationButtonInterface_setLocationButtonOptions1")
    }
    _LocationButtonAttribute_onClick(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_LocationButtonAttribute_onClick")
    }
    _Marquee_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Marquee_construct")
        return -1
    }
    _MarqueeInterface_setMarqueeOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_MarqueeInterface_setMarqueeOptions")
    }
    _MarqueeAttribute_fontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_MarqueeAttribute_fontColor")
    }
    _MarqueeAttribute_fontSize(ptr: KPointer, value: Length): void {
        console.log("_MarqueeAttribute_fontSize")
    }
    _MarqueeAttribute_allowScale(ptr: KPointer, value: KInt): void {
        console.log("_MarqueeAttribute_allowScale")
    }
    _MarqueeAttribute_fontWeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_MarqueeAttribute_fontWeight")
    }
    _MarqueeAttribute_fontFamily(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_MarqueeAttribute_fontFamily")
    }
    _MarqueeAttribute_marqueeUpdateStrategy(ptr: KPointer, value: KInt): void {
        console.log("_MarqueeAttribute_marqueeUpdateStrategy")
    }
    _MarqueeAttribute_onStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_MarqueeAttribute_onStart")
    }
    _MarqueeAttribute_onBounce(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_MarqueeAttribute_onBounce")
    }
    _MarqueeAttribute_onFinish(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_MarqueeAttribute_onFinish")
    }
    _MediaCachedImage_construct(id: KInt, flags: KInt): KPointer {
        console.log("_MediaCachedImage_construct")
        return -1
    }
    _MediaCachedImageInterface_setMediaCachedImageOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_MediaCachedImageInterface_setMediaCachedImageOptions")
    }
    _Menu_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Menu_construct")
        return -1
    }
    _MenuInterface_setMenuOptions(ptr: KPointer): void {
        console.log("_MenuInterface_setMenuOptions")
    }
    _MenuAttribute_fontSize(ptr: KPointer, value: Length): void {
        console.log("_MenuAttribute_fontSize")
    }
    _MenuAttribute_font(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_MenuAttribute_font")
    }
    _MenuAttribute_fontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_MenuAttribute_fontColor")
    }
    _MenuAttribute_radius(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_MenuAttribute_radius")
    }
    _MenuAttribute_menuItemDivider(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_MenuAttribute_menuItemDivider")
    }
    _MenuAttribute_menuItemGroupDivider(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_MenuAttribute_menuItemGroupDivider")
    }
    _MenuAttribute_subMenuExpandingMode(ptr: KPointer, value: KInt): void {
        console.log("_MenuAttribute_subMenuExpandingMode")
    }
    _MenuItem_construct(id: KInt, flags: KInt): KPointer {
        console.log("_MenuItem_construct")
        return -1
    }
    _MenuItemInterface_setMenuItemOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_MenuItemInterface_setMenuItemOptions")
    }
    _MenuItemAttribute_selected(ptr: KPointer, value: KInt): void {
        console.log("_MenuItemAttribute_selected")
    }
    _MenuItemAttribute_selectIcon(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_MenuItemAttribute_selectIcon")
    }
    _MenuItemAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_MenuItemAttribute_onChange")
    }
    _MenuItemAttribute_contentFont(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_MenuItemAttribute_contentFont")
    }
    _MenuItemAttribute_contentFontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_MenuItemAttribute_contentFontColor")
    }
    _MenuItemAttribute_labelFont(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_MenuItemAttribute_labelFont")
    }
    _MenuItemAttribute_labelFontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_MenuItemAttribute_labelFontColor")
    }
    _MenuItemAttribute__onChangeEvent_selected(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_MenuItemAttribute__onChangeEvent_selected")
    }
    _MenuItemGroup_construct(id: KInt, flags: KInt): KPointer {
        console.log("_MenuItemGroup_construct")
        return -1
    }
    _MenuItemGroupInterface_setMenuItemGroupOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_MenuItemGroupInterface_setMenuItemGroupOptions")
    }
    _NavDestination_construct(id: KInt, flags: KInt): KPointer {
        console.log("_NavDestination_construct")
        return -1
    }
    _NavDestinationInterface_setNavDestinationOptions(ptr: KPointer): void {
        console.log("_NavDestinationInterface_setNavDestinationOptions")
    }
    _NavDestinationAttribute_hideTitleBar0(ptr: KPointer, value: KInt): void {
        console.log("_NavDestinationAttribute_hideTitleBar0")
    }
    _NavDestinationAttribute_hideTitleBar1(ptr: KPointer, hide: KInt, animated: KInt): void {
        console.log("_NavDestinationAttribute_hideTitleBar1")
    }
    _NavDestinationAttribute_onShown(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_NavDestinationAttribute_onShown")
    }
    _NavDestinationAttribute_onHidden(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_NavDestinationAttribute_onHidden")
    }
    _NavDestinationAttribute_onBackPressed(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_NavDestinationAttribute_onBackPressed")
    }
    _NavDestinationAttribute_mode(ptr: KPointer, value: KInt): void {
        console.log("_NavDestinationAttribute_mode")
    }
    _NavDestinationAttribute_backButtonIcon(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_NavDestinationAttribute_backButtonIcon")
    }
    _NavDestinationAttribute_menus(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_NavDestinationAttribute_menus")
    }
    _NavDestinationAttribute_onReady(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_NavDestinationAttribute_onReady")
    }
    _NavDestinationAttribute_onWillAppear(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_NavDestinationAttribute_onWillAppear")
    }
    _NavDestinationAttribute_onWillDisappear(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_NavDestinationAttribute_onWillDisappear")
    }
    _NavDestinationAttribute_onWillShow(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_NavDestinationAttribute_onWillShow")
    }
    _NavDestinationAttribute_onWillHide(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_NavDestinationAttribute_onWillHide")
    }
    _NavDestinationAttribute_systemBarStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_NavDestinationAttribute_systemBarStyle")
    }
    _NavDestinationAttribute_recoverable(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_NavDestinationAttribute_recoverable")
    }
    _NavDestinationAttribute_systemTransition(ptr: KPointer, value: KInt): void {
        console.log("_NavDestinationAttribute_systemTransition")
    }
    _NavDestinationAttribute_title(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_NavDestinationAttribute_title")
    }
    _NavDestinationAttribute_toolbarConfiguration(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_NavDestinationAttribute_toolbarConfiguration")
    }
    _NavDestinationAttribute_hideToolBar(ptr: KPointer, hide: KInt, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_NavDestinationAttribute_hideToolBar")
    }
    _NavDestinationAttribute_ignoreLayoutSafeArea(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_NavDestinationAttribute_ignoreLayoutSafeArea")
    }
    _NavRouter_construct(id: KInt, flags: KInt): KPointer {
        console.log("_NavRouter_construct")
        return -1
    }
    _NavRouterInterface_setNavRouterOptions0(ptr: KPointer): void {
        console.log("_NavRouterInterface_setNavRouterOptions0")
    }
    _NavRouterInterface_setNavRouterOptions1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_NavRouterInterface_setNavRouterOptions1")
    }
    _NavRouterAttribute_onStateChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_NavRouterAttribute_onStateChange")
    }
    _NavRouterAttribute_mode(ptr: KPointer, value: KInt): void {
        console.log("_NavRouterAttribute_mode")
    }
    _Navigator_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Navigator_construct")
        return -1
    }
    _NavigatorInterface_setNavigatorOptions0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_NavigatorInterface_setNavigatorOptions0")
    }
    _NavigatorInterface_setNavigatorOptions1(ptr: KPointer): void {
        console.log("_NavigatorInterface_setNavigatorOptions1")
    }
    _NavigatorAttribute_active(ptr: KPointer, value: KInt): void {
        console.log("_NavigatorAttribute_active")
    }
    _NavigatorAttribute_type(ptr: KPointer, value: KInt): void {
        console.log("_NavigatorAttribute_type")
    }
    _NavigatorAttribute_target(ptr: KPointer, value: KStringPtr): void {
        console.log("_NavigatorAttribute_target")
    }
    _NavigatorAttribute_params(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_NavigatorAttribute_params")
    }
    _NodeContainer_construct(id: KInt, flags: KInt): KPointer {
        console.log("_NodeContainer_construct")
        return -1
    }
    _NodeContainerInterface_setNodeContainerOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_NodeContainerInterface_setNodeContainerOptions")
    }
    _Panel_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Panel_construct")
        return -1
    }
    _PanelInterface_setPanelOptions(ptr: KPointer, show: KInt): void {
        console.log("_PanelInterface_setPanelOptions")
    }
    _PanelAttribute_mode(ptr: KPointer, value: KInt): void {
        console.log("_PanelAttribute_mode")
    }
    _PanelAttribute_type(ptr: KPointer, value: KInt): void {
        console.log("_PanelAttribute_type")
    }
    _PanelAttribute_dragBar(ptr: KPointer, value: KInt): void {
        console.log("_PanelAttribute_dragBar")
    }
    _PanelAttribute_customHeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_PanelAttribute_customHeight")
    }
    _PanelAttribute_fullHeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_PanelAttribute_fullHeight")
    }
    _PanelAttribute_halfHeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_PanelAttribute_halfHeight")
    }
    _PanelAttribute_miniHeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_PanelAttribute_miniHeight")
    }
    _PanelAttribute_show(ptr: KPointer, value: KInt): void {
        console.log("_PanelAttribute_show")
    }
    _PanelAttribute_backgroundMask(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_PanelAttribute_backgroundMask")
    }
    _PanelAttribute_showCloseIcon(ptr: KPointer, value: KInt): void {
        console.log("_PanelAttribute_showCloseIcon")
    }
    _PanelAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_PanelAttribute_onChange")
    }
    _PanelAttribute_onHeightChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_PanelAttribute_onHeightChange")
    }
    _PanelAttribute__onChangeEvent_mode(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_PanelAttribute__onChangeEvent_mode")
    }
    _PasteButton_construct(id: KInt, flags: KInt): KPointer {
        console.log("_PasteButton_construct")
        return -1
    }
    _PasteButtonInterface_setPasteButtonOptions0(ptr: KPointer): void {
        console.log("_PasteButtonInterface_setPasteButtonOptions0")
    }
    _PasteButtonInterface_setPasteButtonOptions1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_PasteButtonInterface_setPasteButtonOptions1")
    }
    _PasteButtonAttribute_onClick(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_PasteButtonAttribute_onClick")
    }
    _Path_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Path_construct")
        return -1
    }
    _PathInterface_setPathOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_PathInterface_setPathOptions")
    }
    _PathAttribute_commands(ptr: KPointer, value: KStringPtr): void {
        console.log("_PathAttribute_commands")
    }
    _PatternLock_construct(id: KInt, flags: KInt): KPointer {
        console.log("_PatternLock_construct")
        return -1
    }
    _PatternLockInterface_setPatternLockOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_PatternLockInterface_setPatternLockOptions")
    }
    _PatternLockAttribute_sideLength(ptr: KPointer, value: Length): void {
        console.log("_PatternLockAttribute_sideLength")
    }
    _PatternLockAttribute_circleRadius(ptr: KPointer, value: Length): void {
        console.log("_PatternLockAttribute_circleRadius")
    }
    _PatternLockAttribute_backgroundColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_PatternLockAttribute_backgroundColor")
    }
    _PatternLockAttribute_regularColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_PatternLockAttribute_regularColor")
    }
    _PatternLockAttribute_selectedColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_PatternLockAttribute_selectedColor")
    }
    _PatternLockAttribute_activeColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_PatternLockAttribute_activeColor")
    }
    _PatternLockAttribute_pathColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_PatternLockAttribute_pathColor")
    }
    _PatternLockAttribute_pathStrokeWidth(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_PatternLockAttribute_pathStrokeWidth")
    }
    _PatternLockAttribute_onPatternComplete(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_PatternLockAttribute_onPatternComplete")
    }
    _PatternLockAttribute_autoReset(ptr: KPointer, value: KInt): void {
        console.log("_PatternLockAttribute_autoReset")
    }
    _PatternLockAttribute_onDotConnect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_PatternLockAttribute_onDotConnect")
    }
    _PatternLockAttribute_activateCircleStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_PatternLockAttribute_activateCircleStyle")
    }
    _PluginComponent_construct(id: KInt, flags: KInt): KPointer {
        console.log("_PluginComponent_construct")
        return -1
    }
    _PluginComponentInterface_setPluginComponentOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_PluginComponentInterface_setPluginComponentOptions")
    }
    _PluginComponentAttribute_onComplete(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_PluginComponentAttribute_onComplete")
    }
    _PluginComponentAttribute_onError(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_PluginComponentAttribute_onError")
    }
    _Polygon_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Polygon_construct")
        return -1
    }
    _PolygonInterface_setPolygonOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_PolygonInterface_setPolygonOptions")
    }
    _PolygonAttribute_points(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_PolygonAttribute_points")
    }
    _Polyline_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Polyline_construct")
        return -1
    }
    _PolylineInterface_setPolylineOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_PolylineInterface_setPolylineOptions")
    }
    _PolylineAttribute_points(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_PolylineAttribute_points")
    }
    _Progress_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Progress_construct")
        return -1
    }
    _ProgressInterface_setProgressOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ProgressInterface_setProgressOptions")
    }
    _ProgressAttribute_value(ptr: KPointer, value: number): void {
        console.log("_ProgressAttribute_value")
    }
    _ProgressAttribute_color(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ProgressAttribute_color")
    }
    _ProgressAttribute_style(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ProgressAttribute_style")
    }
    _ProgressAttribute_privacySensitive(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ProgressAttribute_privacySensitive")
    }
    _ProgressAttribute_contentModifier(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ProgressAttribute_contentModifier")
    }
    _QRCode_construct(id: KInt, flags: KInt): KPointer {
        console.log("_QRCode_construct")
        return -1
    }
    _QRCodeInterface_setQRCodeOptions(ptr: KPointer, value: KStringPtr): void {
        console.log("_QRCodeInterface_setQRCodeOptions")
    }
    _QRCodeAttribute_color(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_QRCodeAttribute_color")
    }
    _QRCodeAttribute_backgroundColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_QRCodeAttribute_backgroundColor")
    }
    _QRCodeAttribute_contentOpacity(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_QRCodeAttribute_contentOpacity")
    }
    _Radio_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Radio_construct")
        return -1
    }
    _RadioInterface_setRadioOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RadioInterface_setRadioOptions")
    }
    _RadioAttribute_checked(ptr: KPointer, value: KInt): void {
        console.log("_RadioAttribute_checked")
    }
    _RadioAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RadioAttribute_onChange")
    }
    _RadioAttribute_radioStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RadioAttribute_radioStyle")
    }
    _RadioAttribute_contentModifier(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RadioAttribute_contentModifier")
    }
    _RadioAttribute__onChangeEvent_checked(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RadioAttribute__onChangeEvent_checked")
    }
    _Rating_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Rating_construct")
        return -1
    }
    _RatingInterface_setRatingOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RatingInterface_setRatingOptions")
    }
    _RatingAttribute_stars(ptr: KPointer, value: number): void {
        console.log("_RatingAttribute_stars")
    }
    _RatingAttribute_stepSize(ptr: KPointer, value: number): void {
        console.log("_RatingAttribute_stepSize")
    }
    _RatingAttribute_starStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RatingAttribute_starStyle")
    }
    _RatingAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RatingAttribute_onChange")
    }
    _RatingAttribute_contentModifier(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RatingAttribute_contentModifier")
    }
    _RatingAttribute__onChangeEvent_rating(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RatingAttribute__onChangeEvent_rating")
    }
    _Rect_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Rect_construct")
        return -1
    }
    _RectInterface_setRectOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RectInterface_setRectOptions")
    }
    _RectAttribute_radiusWidth(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RectAttribute_radiusWidth")
    }
    _RectAttribute_radiusHeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RectAttribute_radiusHeight")
    }
    _RectAttribute_radius(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RectAttribute_radius")
    }
    _Refresh_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Refresh_construct")
        return -1
    }
    _RefreshInterface_setRefreshOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RefreshInterface_setRefreshOptions")
    }
    _RefreshAttribute_onStateChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RefreshAttribute_onStateChange")
    }
    _RefreshAttribute_onRefreshing(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RefreshAttribute_onRefreshing")
    }
    _RefreshAttribute_refreshOffset(ptr: KPointer, value: number): void {
        console.log("_RefreshAttribute_refreshOffset")
    }
    _RefreshAttribute_pullToRefresh(ptr: KPointer, value: KInt): void {
        console.log("_RefreshAttribute_pullToRefresh")
    }
    _RefreshAttribute_onOffsetChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RefreshAttribute_onOffsetChange")
    }
    _RefreshAttribute_pullDownRatio(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RefreshAttribute_pullDownRatio")
    }
    _RefreshAttribute__onChangeEvent_refreshing(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RefreshAttribute__onChangeEvent_refreshing")
    }
    _RelativeContainer_construct(id: KInt, flags: KInt): KPointer {
        console.log("_RelativeContainer_construct")
        return -1
    }
    _RelativeContainerInterface_setRelativeContainerOptions(ptr: KPointer): void {
        console.log("_RelativeContainerInterface_setRelativeContainerOptions")
    }
    _RelativeContainerAttribute_guideLine(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RelativeContainerAttribute_guideLine")
    }
    _RelativeContainerAttribute_barrier0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RelativeContainerAttribute_barrier0")
    }
    _RelativeContainerAttribute_barrier1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RelativeContainerAttribute_barrier1")
    }
    _RichEditor_construct(id: KInt, flags: KInt): KPointer {
        console.log("_RichEditor_construct")
        return -1
    }
    _RichEditorInterface_setRichEditorOptions0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RichEditorInterface_setRichEditorOptions0")
    }
    _RichEditorInterface_setRichEditorOptions1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RichEditorInterface_setRichEditorOptions1")
    }
    _RichEditorAttribute_onReady(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RichEditorAttribute_onReady")
    }
    _RichEditorAttribute_onSelect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RichEditorAttribute_onSelect")
    }
    _RichEditorAttribute_onSelectionChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RichEditorAttribute_onSelectionChange")
    }
    _RichEditorAttribute_aboutToIMEInput(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RichEditorAttribute_aboutToIMEInput")
    }
    _RichEditorAttribute_onIMEInputComplete(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RichEditorAttribute_onIMEInputComplete")
    }
    _RichEditorAttribute_onDidIMEInput(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RichEditorAttribute_onDidIMEInput")
    }
    _RichEditorAttribute_aboutToDelete(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RichEditorAttribute_aboutToDelete")
    }
    _RichEditorAttribute_onDeleteComplete(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RichEditorAttribute_onDeleteComplete")
    }
    _RichEditorAttribute_copyOptions(ptr: KPointer, value: KInt): void {
        console.log("_RichEditorAttribute_copyOptions")
    }
    _RichEditorAttribute_onPaste(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RichEditorAttribute_onPaste")
    }
    _RichEditorAttribute_enableDataDetector(ptr: KPointer, value: KInt): void {
        console.log("_RichEditorAttribute_enableDataDetector")
    }
    _RichEditorAttribute_enablePreviewText(ptr: KPointer, value: KInt): void {
        console.log("_RichEditorAttribute_enablePreviewText")
    }
    _RichEditorAttribute_dataDetectorConfig(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RichEditorAttribute_dataDetectorConfig")
    }
    _RichEditorAttribute_caretColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RichEditorAttribute_caretColor")
    }
    _RichEditorAttribute_selectedBackgroundColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RichEditorAttribute_selectedBackgroundColor")
    }
    _RichEditorAttribute_onEditingChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RichEditorAttribute_onEditingChange")
    }
    _RichEditorAttribute_enterKeyType(ptr: KPointer, value: KInt): void {
        console.log("_RichEditorAttribute_enterKeyType")
    }
    _RichEditorAttribute_onSubmit(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RichEditorAttribute_onSubmit")
    }
    _RichEditorAttribute_onWillChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RichEditorAttribute_onWillChange")
    }
    _RichEditorAttribute_onDidChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RichEditorAttribute_onDidChange")
    }
    _RichEditorAttribute_onCut(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RichEditorAttribute_onCut")
    }
    _RichEditorAttribute_onCopy(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RichEditorAttribute_onCopy")
    }
    _RichEditorAttribute_editMenuOptions(ptr: KPointer, value: KPointer): void {
        console.log("_RichEditorAttribute_editMenuOptions")
    }
    _RichEditorAttribute_enableKeyboardOnFocus(ptr: KPointer, value: KInt): void {
        console.log("_RichEditorAttribute_enableKeyboardOnFocus")
    }
    _RichEditorAttribute_enableHapticFeedback(ptr: KPointer, value: KInt): void {
        console.log("_RichEditorAttribute_enableHapticFeedback")
    }
    _RichEditorAttribute_barState(ptr: KPointer, value: KInt): void {
        console.log("_RichEditorAttribute_barState")
    }
    _RichEditorAttribute_bindSelectionMenu(ptr: KPointer, spanType: KInt, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RichEditorAttribute_bindSelectionMenu")
    }
    _RichEditorAttribute_customKeyboard(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RichEditorAttribute_customKeyboard")
    }
    _RichEditorAttribute_placeholder(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RichEditorAttribute_placeholder")
    }
    _RichText_construct(id: KInt, flags: KInt): KPointer {
        console.log("_RichText_construct")
        return -1
    }
    _RichTextInterface_setRichTextOptions(ptr: KPointer, content: KStringPtr): void {
        console.log("_RichTextInterface_setRichTextOptions")
    }
    _RichTextAttribute_onStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RichTextAttribute_onStart")
    }
    _RichTextAttribute_onComplete(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RichTextAttribute_onComplete")
    }
    _RootScene_construct(id: KInt, flags: KInt): KPointer {
        console.log("_RootScene_construct")
        return -1
    }
    _RootSceneInterface_setRootSceneOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RootSceneInterface_setRootSceneOptions")
    }
    _Row_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Row_construct")
        return -1
    }
    _RowInterface_setRowOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RowInterface_setRowOptions")
    }
    _RowAttribute_alignItems(ptr: KPointer, value: KInt): void {
        console.log("_RowAttribute_alignItems")
    }
    _RowAttribute_justifyContent(ptr: KPointer, value: KInt): void {
        console.log("_RowAttribute_justifyContent")
    }
    _RowAttribute_pointLight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RowAttribute_pointLight")
    }
    _RowAttribute_reverse(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RowAttribute_reverse")
    }
    _RowSplit_construct(id: KInt, flags: KInt): KPointer {
        console.log("_RowSplit_construct")
        return -1
    }
    _RowSplitInterface_setRowSplitOptions(ptr: KPointer): void {
        console.log("_RowSplitInterface_setRowSplitOptions")
    }
    _RowSplitAttribute_resizeable(ptr: KPointer, value: KInt): void {
        console.log("_RowSplitAttribute_resizeable")
    }
    _SaveButton_construct(id: KInt, flags: KInt): KPointer {
        console.log("_SaveButton_construct")
        return -1
    }
    _SaveButtonInterface_setSaveButtonOptions0(ptr: KPointer): void {
        console.log("_SaveButtonInterface_setSaveButtonOptions0")
    }
    _SaveButtonInterface_setSaveButtonOptions1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SaveButtonInterface_setSaveButtonOptions1")
    }
    _SaveButtonAttribute_onClick(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SaveButtonAttribute_onClick")
    }
    _Screen_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Screen_construct")
        return -1
    }
    _ScreenInterface_setScreenOptions(ptr: KPointer, screenId: number): void {
        console.log("_ScreenInterface_setScreenOptions")
    }
    _Scroll_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Scroll_construct")
        return -1
    }
    _ScrollInterface_setScrollOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ScrollInterface_setScrollOptions")
    }
    _ScrollAttribute_scrollable(ptr: KPointer, value: KInt): void {
        console.log("_ScrollAttribute_scrollable")
    }
    _ScrollAttribute_onScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ScrollAttribute_onScroll")
    }
    _ScrollAttribute_onWillScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ScrollAttribute_onWillScroll")
    }
    _ScrollAttribute_onDidScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ScrollAttribute_onDidScroll")
    }
    _ScrollAttribute_onScrollEdge(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ScrollAttribute_onScrollEdge")
    }
    _ScrollAttribute_onScrollStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ScrollAttribute_onScrollStart")
    }
    _ScrollAttribute_onScrollEnd(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ScrollAttribute_onScrollEnd")
    }
    _ScrollAttribute_onScrollStop(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ScrollAttribute_onScrollStop")
    }
    _ScrollAttribute_scrollBar(ptr: KPointer, value: KInt): void {
        console.log("_ScrollAttribute_scrollBar")
    }
    _ScrollAttribute_scrollBarColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ScrollAttribute_scrollBarColor")
    }
    _ScrollAttribute_scrollBarWidth(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ScrollAttribute_scrollBarWidth")
    }
    _ScrollAttribute_onScrollFrameBegin(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ScrollAttribute_onScrollFrameBegin")
    }
    _ScrollAttribute_nestedScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ScrollAttribute_nestedScroll")
    }
    _ScrollAttribute_enableScrollInteraction(ptr: KPointer, value: KInt): void {
        console.log("_ScrollAttribute_enableScrollInteraction")
    }
    _ScrollAttribute_friction(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ScrollAttribute_friction")
    }
    _ScrollAttribute_scrollSnap(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ScrollAttribute_scrollSnap")
    }
    _ScrollAttribute_enablePaging(ptr: KPointer, value: KInt): void {
        console.log("_ScrollAttribute_enablePaging")
    }
    _ScrollAttribute_initialOffset(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ScrollAttribute_initialOffset")
    }
    _ScrollAttribute_edgeEffect(ptr: KPointer, edgeEffect: KInt, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ScrollAttribute_edgeEffect")
    }
    _ScrollBar_construct(id: KInt, flags: KInt): KPointer {
        console.log("_ScrollBar_construct")
        return -1
    }
    _ScrollBarInterface_setScrollBarOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ScrollBarInterface_setScrollBarOptions")
    }
    _ScrollBarAttribute_enableNestedScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ScrollBarAttribute_enableNestedScroll")
    }
    _Search_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Search_construct")
        return -1
    }
    _SearchInterface_setSearchOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SearchInterface_setSearchOptions")
    }
    _SearchAttribute_fontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SearchAttribute_fontColor")
    }
    _SearchAttribute_searchIcon(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SearchAttribute_searchIcon")
    }
    _SearchAttribute_cancelButton(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SearchAttribute_cancelButton")
    }
    _SearchAttribute_textIndent(ptr: KPointer, value: Length): void {
        console.log("_SearchAttribute_textIndent")
    }
    _SearchAttribute_onEditChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SearchAttribute_onEditChange")
    }
    _SearchAttribute_selectedBackgroundColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SearchAttribute_selectedBackgroundColor")
    }
    _SearchAttribute_caretStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SearchAttribute_caretStyle")
    }
    _SearchAttribute_placeholderColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SearchAttribute_placeholderColor")
    }
    _SearchAttribute_placeholderFont(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SearchAttribute_placeholderFont")
    }
    _SearchAttribute_textFont(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SearchAttribute_textFont")
    }
    _SearchAttribute_enterKeyType(ptr: KPointer, value: KInt): void {
        console.log("_SearchAttribute_enterKeyType")
    }
    _SearchAttribute_onSubmit0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SearchAttribute_onSubmit0")
    }
    _SearchAttribute_onSubmit1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SearchAttribute_onSubmit1")
    }
    _SearchAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SearchAttribute_onChange")
    }
    _SearchAttribute_onTextSelectionChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SearchAttribute_onTextSelectionChange")
    }
    _SearchAttribute_onContentScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SearchAttribute_onContentScroll")
    }
    _SearchAttribute_onCopy(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SearchAttribute_onCopy")
    }
    _SearchAttribute_onCut(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SearchAttribute_onCut")
    }
    _SearchAttribute_onPaste(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SearchAttribute_onPaste")
    }
    _SearchAttribute_copyOption(ptr: KPointer, value: KInt): void {
        console.log("_SearchAttribute_copyOption")
    }
    _SearchAttribute_maxLength(ptr: KPointer, value: number): void {
        console.log("_SearchAttribute_maxLength")
    }
    _SearchAttribute_textAlign(ptr: KPointer, value: KInt): void {
        console.log("_SearchAttribute_textAlign")
    }
    _SearchAttribute_enableKeyboardOnFocus(ptr: KPointer, value: KInt): void {
        console.log("_SearchAttribute_enableKeyboardOnFocus")
    }
    _SearchAttribute_selectionMenuHidden(ptr: KPointer, value: KInt): void {
        console.log("_SearchAttribute_selectionMenuHidden")
    }
    _SearchAttribute_minFontSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SearchAttribute_minFontSize")
    }
    _SearchAttribute_maxFontSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SearchAttribute_maxFontSize")
    }
    _SearchAttribute_decoration(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SearchAttribute_decoration")
    }
    _SearchAttribute_letterSpacing(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SearchAttribute_letterSpacing")
    }
    _SearchAttribute_lineHeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SearchAttribute_lineHeight")
    }
    _SearchAttribute_type(ptr: KPointer, value: KInt): void {
        console.log("_SearchAttribute_type")
    }
    _SearchAttribute_fontFeature(ptr: KPointer, value: KStringPtr): void {
        console.log("_SearchAttribute_fontFeature")
    }
    _SearchAttribute_onWillInsert(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SearchAttribute_onWillInsert")
    }
    _SearchAttribute_onDidInsert(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SearchAttribute_onDidInsert")
    }
    _SearchAttribute_onWillDelete(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SearchAttribute_onWillDelete")
    }
    _SearchAttribute_onDidDelete(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SearchAttribute_onDidDelete")
    }
    _SearchAttribute_editMenuOptions(ptr: KPointer, value: KPointer): void {
        console.log("_SearchAttribute_editMenuOptions")
    }
    _SearchAttribute_enablePreviewText(ptr: KPointer, value: KInt): void {
        console.log("_SearchAttribute_enablePreviewText")
    }
    _SearchAttribute_enableHapticFeedback(ptr: KPointer, value: KInt): void {
        console.log("_SearchAttribute_enableHapticFeedback")
    }
    _SearchAttribute_searchButton(ptr: KPointer, value: KStringPtr, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SearchAttribute_searchButton")
    }
    _SearchAttribute_inputFilter(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SearchAttribute_inputFilter")
    }
    _SearchAttribute_customKeyboard(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SearchAttribute_customKeyboard")
    }
    _SearchAttribute__onChangeEvent_value(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SearchAttribute__onChangeEvent_value")
    }
    _SecurityComponentMethod_construct(id: KInt, flags: KInt): KPointer {
        console.log("_SecurityComponentMethod_construct")
        return -1
    }
    _SecurityComponentMethod_iconSize(ptr: KPointer, value: Length): void {
        console.log("_SecurityComponentMethod_iconSize")
    }
    _SecurityComponentMethod_layoutDirection(ptr: KPointer, value: KInt): void {
        console.log("_SecurityComponentMethod_layoutDirection")
    }
    _SecurityComponentMethod_position(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SecurityComponentMethod_position")
    }
    _SecurityComponentMethod_markAnchor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SecurityComponentMethod_markAnchor")
    }
    _SecurityComponentMethod_offset(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SecurityComponentMethod_offset")
    }
    _SecurityComponentMethod_fontSize(ptr: KPointer, value: Length): void {
        console.log("_SecurityComponentMethod_fontSize")
    }
    _SecurityComponentMethod_fontStyle(ptr: KPointer, value: KInt): void {
        console.log("_SecurityComponentMethod_fontStyle")
    }
    _SecurityComponentMethod_fontWeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SecurityComponentMethod_fontWeight")
    }
    _SecurityComponentMethod_fontFamily(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SecurityComponentMethod_fontFamily")
    }
    _SecurityComponentMethod_fontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SecurityComponentMethod_fontColor")
    }
    _SecurityComponentMethod_iconColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SecurityComponentMethod_iconColor")
    }
    _SecurityComponentMethod_backgroundColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SecurityComponentMethod_backgroundColor")
    }
    _SecurityComponentMethod_borderStyle(ptr: KPointer, value: KInt): void {
        console.log("_SecurityComponentMethod_borderStyle")
    }
    _SecurityComponentMethod_borderWidth(ptr: KPointer, value: Length): void {
        console.log("_SecurityComponentMethod_borderWidth")
    }
    _SecurityComponentMethod_borderColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SecurityComponentMethod_borderColor")
    }
    _SecurityComponentMethod_borderRadius(ptr: KPointer, value: Length): void {
        console.log("_SecurityComponentMethod_borderRadius")
    }
    _SecurityComponentMethod_padding(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SecurityComponentMethod_padding")
    }
    _SecurityComponentMethod_textIconSpace(ptr: KPointer, value: Length): void {
        console.log("_SecurityComponentMethod_textIconSpace")
    }
    _SecurityComponentMethod_key(ptr: KPointer, value: KStringPtr): void {
        console.log("_SecurityComponentMethod_key")
    }
    _SecurityComponentMethod_width(ptr: KPointer, value: Length): void {
        console.log("_SecurityComponentMethod_width")
    }
    _SecurityComponentMethod_height(ptr: KPointer, value: Length): void {
        console.log("_SecurityComponentMethod_height")
    }
    _SecurityComponentMethod_size(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SecurityComponentMethod_size")
    }
    _SecurityComponentMethod_constraintSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SecurityComponentMethod_constraintSize")
    }
    _Select_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Select_construct")
        return -1
    }
    _SelectInterface_setSelectOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SelectInterface_setSelectOptions")
    }
    _SelectAttribute_selected(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SelectAttribute_selected")
    }
    _SelectAttribute_value(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SelectAttribute_value")
    }
    _SelectAttribute_font(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SelectAttribute_font")
    }
    _SelectAttribute_fontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SelectAttribute_fontColor")
    }
    _SelectAttribute_selectedOptionBgColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SelectAttribute_selectedOptionBgColor")
    }
    _SelectAttribute_selectedOptionFont(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SelectAttribute_selectedOptionFont")
    }
    _SelectAttribute_selectedOptionFontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SelectAttribute_selectedOptionFontColor")
    }
    _SelectAttribute_optionBgColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SelectAttribute_optionBgColor")
    }
    _SelectAttribute_optionFont(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SelectAttribute_optionFont")
    }
    _SelectAttribute_optionFontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SelectAttribute_optionFontColor")
    }
    _SelectAttribute_onSelect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SelectAttribute_onSelect")
    }
    _SelectAttribute_space(ptr: KPointer, value: Length): void {
        console.log("_SelectAttribute_space")
    }
    _SelectAttribute_arrowPosition(ptr: KPointer, value: KInt): void {
        console.log("_SelectAttribute_arrowPosition")
    }
    _SelectAttribute_optionWidth(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SelectAttribute_optionWidth")
    }
    _SelectAttribute_optionHeight(ptr: KPointer, value: Length): void {
        console.log("_SelectAttribute_optionHeight")
    }
    _SelectAttribute_menuBackgroundColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SelectAttribute_menuBackgroundColor")
    }
    _SelectAttribute_menuBackgroundBlurStyle(ptr: KPointer, value: KInt): void {
        console.log("_SelectAttribute_menuBackgroundBlurStyle")
    }
    _SelectAttribute_controlSize(ptr: KPointer, value: KInt): void {
        console.log("_SelectAttribute_controlSize")
    }
    _SelectAttribute_menuItemContentModifier(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SelectAttribute_menuItemContentModifier")
    }
    _SelectAttribute_divider(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SelectAttribute_divider")
    }
    _SelectAttribute_menuAlign(ptr: KPointer, alignType: KInt, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SelectAttribute_menuAlign")
    }
    _SelectAttribute__onChangeEvent_selected(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SelectAttribute__onChangeEvent_selected")
    }
    _SelectAttribute__onChangeEvent_value(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SelectAttribute__onChangeEvent_value")
    }
    _Shape_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Shape_construct")
        return -1
    }
    _ShapeInterface_setShapeOptions0(ptr: KPointer, value: KPointer): void {
        console.log("_ShapeInterface_setShapeOptions0")
    }
    _ShapeInterface_setShapeOptions1(ptr: KPointer): void {
        console.log("_ShapeInterface_setShapeOptions1")
    }
    _ShapeAttribute_viewPort(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ShapeAttribute_viewPort")
    }
    _ShapeAttribute_stroke(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ShapeAttribute_stroke")
    }
    _ShapeAttribute_fill(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ShapeAttribute_fill")
    }
    _ShapeAttribute_strokeDashOffset(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ShapeAttribute_strokeDashOffset")
    }
    _ShapeAttribute_strokeDashArray(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ShapeAttribute_strokeDashArray")
    }
    _ShapeAttribute_strokeLineCap(ptr: KPointer, value: KInt): void {
        console.log("_ShapeAttribute_strokeLineCap")
    }
    _ShapeAttribute_strokeLineJoin(ptr: KPointer, value: KInt): void {
        console.log("_ShapeAttribute_strokeLineJoin")
    }
    _ShapeAttribute_strokeMiterLimit(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ShapeAttribute_strokeMiterLimit")
    }
    _ShapeAttribute_strokeOpacity(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ShapeAttribute_strokeOpacity")
    }
    _ShapeAttribute_fillOpacity(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ShapeAttribute_fillOpacity")
    }
    _ShapeAttribute_strokeWidth(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ShapeAttribute_strokeWidth")
    }
    _ShapeAttribute_antiAlias(ptr: KPointer, value: KInt): void {
        console.log("_ShapeAttribute_antiAlias")
    }
    _ShapeAttribute_mesh(ptr: KPointer, thisArray: Uint8Array, thisLength: int32, column: number, row: number): void {
        console.log("_ShapeAttribute_mesh")
    }
    _Slider_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Slider_construct")
        return -1
    }
    _SliderInterface_setSliderOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SliderInterface_setSliderOptions")
    }
    _SliderAttribute_blockColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SliderAttribute_blockColor")
    }
    _SliderAttribute_trackColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SliderAttribute_trackColor")
    }
    _SliderAttribute_selectedColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SliderAttribute_selectedColor")
    }
    _SliderAttribute_minLabel(ptr: KPointer, value: KStringPtr): void {
        console.log("_SliderAttribute_minLabel")
    }
    _SliderAttribute_maxLabel(ptr: KPointer, value: KStringPtr): void {
        console.log("_SliderAttribute_maxLabel")
    }
    _SliderAttribute_showSteps(ptr: KPointer, value: KInt): void {
        console.log("_SliderAttribute_showSteps")
    }
    _SliderAttribute_trackThickness(ptr: KPointer, value: Length): void {
        console.log("_SliderAttribute_trackThickness")
    }
    _SliderAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SliderAttribute_onChange")
    }
    _SliderAttribute_blockBorderColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SliderAttribute_blockBorderColor")
    }
    _SliderAttribute_blockBorderWidth(ptr: KPointer, value: Length): void {
        console.log("_SliderAttribute_blockBorderWidth")
    }
    _SliderAttribute_stepColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SliderAttribute_stepColor")
    }
    _SliderAttribute_trackBorderRadius(ptr: KPointer, value: Length): void {
        console.log("_SliderAttribute_trackBorderRadius")
    }
    _SliderAttribute_selectedBorderRadius(ptr: KPointer, value: Length): void {
        console.log("_SliderAttribute_selectedBorderRadius")
    }
    _SliderAttribute_blockSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SliderAttribute_blockSize")
    }
    _SliderAttribute_blockStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SliderAttribute_blockStyle")
    }
    _SliderAttribute_stepSize(ptr: KPointer, value: Length): void {
        console.log("_SliderAttribute_stepSize")
    }
    _SliderAttribute_sliderInteractionMode(ptr: KPointer, value: KInt): void {
        console.log("_SliderAttribute_sliderInteractionMode")
    }
    _SliderAttribute_minResponsiveDistance(ptr: KPointer, value: number): void {
        console.log("_SliderAttribute_minResponsiveDistance")
    }
    _SliderAttribute_contentModifier(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SliderAttribute_contentModifier")
    }
    _SliderAttribute_slideRange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SliderAttribute_slideRange")
    }
    _SliderAttribute_showTips(ptr: KPointer, value: KInt, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SliderAttribute_showTips")
    }
    _SliderAttribute__onChangeEvent_value(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SliderAttribute__onChangeEvent_value")
    }
    _BaseSpan_construct(id: KInt, flags: KInt): KPointer {
        console.log("_BaseSpan_construct")
        return -1
    }
    _BaseSpan_textBackgroundStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_BaseSpan_textBackgroundStyle")
    }
    _BaseSpan_baselineOffset(ptr: KPointer, value: KPointer): void {
        console.log("_BaseSpan_baselineOffset")
    }
    _Span_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Span_construct")
        return -1
    }
    _SpanInterface_setSpanOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SpanInterface_setSpanOptions")
    }
    _SpanAttribute_font(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SpanAttribute_font")
    }
    _SpanAttribute_fontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SpanAttribute_fontColor")
    }
    _SpanAttribute_fontSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SpanAttribute_fontSize")
    }
    _SpanAttribute_fontStyle(ptr: KPointer, value: KInt): void {
        console.log("_SpanAttribute_fontStyle")
    }
    _SpanAttribute_fontWeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SpanAttribute_fontWeight")
    }
    _SpanAttribute_fontFamily(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SpanAttribute_fontFamily")
    }
    _SpanAttribute_decoration(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SpanAttribute_decoration")
    }
    _SpanAttribute_letterSpacing(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SpanAttribute_letterSpacing")
    }
    _SpanAttribute_textCase(ptr: KPointer, value: KInt): void {
        console.log("_SpanAttribute_textCase")
    }
    _SpanAttribute_lineHeight(ptr: KPointer, value: Length): void {
        console.log("_SpanAttribute_lineHeight")
    }
    _SpanAttribute_textShadow(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SpanAttribute_textShadow")
    }
    _Stack_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Stack_construct")
        return -1
    }
    _StackInterface_setStackOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_StackInterface_setStackOptions")
    }
    _StackAttribute_alignContent(ptr: KPointer, value: KInt): void {
        console.log("_StackAttribute_alignContent")
    }
    _StackAttribute_pointLight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_StackAttribute_pointLight")
    }
    _Stepper_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Stepper_construct")
        return -1
    }
    _StepperInterface_setStepperOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_StepperInterface_setStepperOptions")
    }
    _StepperAttribute_onFinish(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_StepperAttribute_onFinish")
    }
    _StepperAttribute_onSkip(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_StepperAttribute_onSkip")
    }
    _StepperAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_StepperAttribute_onChange")
    }
    _StepperAttribute_onNext(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_StepperAttribute_onNext")
    }
    _StepperAttribute_onPrevious(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_StepperAttribute_onPrevious")
    }
    _StepperAttribute__onChangeEvent_index(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_StepperAttribute__onChangeEvent_index")
    }
    _StepperItem_construct(id: KInt, flags: KInt): KPointer {
        console.log("_StepperItem_construct")
        return -1
    }
    _StepperItemInterface_setStepperItemOptions(ptr: KPointer): void {
        console.log("_StepperItemInterface_setStepperItemOptions")
    }
    _StepperItemAttribute_prevLabel(ptr: KPointer, value: KStringPtr): void {
        console.log("_StepperItemAttribute_prevLabel")
    }
    _StepperItemAttribute_nextLabel(ptr: KPointer, value: KStringPtr): void {
        console.log("_StepperItemAttribute_nextLabel")
    }
    _StepperItemAttribute_status(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_StepperItemAttribute_status")
    }
    _Swiper_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Swiper_construct")
        return -1
    }
    _SwiperInterface_setSwiperOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SwiperInterface_setSwiperOptions")
    }
    _SwiperAttribute_index(ptr: KPointer, value: number): void {
        console.log("_SwiperAttribute_index")
    }
    _SwiperAttribute_autoPlay(ptr: KPointer, value: KInt): void {
        console.log("_SwiperAttribute_autoPlay")
    }
    _SwiperAttribute_interval(ptr: KPointer, value: number): void {
        console.log("_SwiperAttribute_interval")
    }
    _SwiperAttribute_indicator0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SwiperAttribute_indicator0")
    }
    _SwiperAttribute_indicator1(ptr: KPointer, value: KPointer): void {
        console.log("_SwiperAttribute_indicator1")
    }
    _SwiperAttribute_loop(ptr: KPointer, value: KInt): void {
        console.log("_SwiperAttribute_loop")
    }
    _SwiperAttribute_duration(ptr: KPointer, value: number): void {
        console.log("_SwiperAttribute_duration")
    }
    _SwiperAttribute_vertical(ptr: KPointer, value: KInt): void {
        console.log("_SwiperAttribute_vertical")
    }
    _SwiperAttribute_itemSpace(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SwiperAttribute_itemSpace")
    }
    _SwiperAttribute_displayMode(ptr: KPointer, value: KInt): void {
        console.log("_SwiperAttribute_displayMode")
    }
    _SwiperAttribute_cachedCount(ptr: KPointer, value: number): void {
        console.log("_SwiperAttribute_cachedCount")
    }
    _SwiperAttribute_effectMode(ptr: KPointer, value: KInt): void {
        console.log("_SwiperAttribute_effectMode")
    }
    _SwiperAttribute_disableSwipe(ptr: KPointer, value: KInt): void {
        console.log("_SwiperAttribute_disableSwipe")
    }
    _SwiperAttribute_curve(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SwiperAttribute_curve")
    }
    _SwiperAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SwiperAttribute_onChange")
    }
    _SwiperAttribute_indicatorStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SwiperAttribute_indicatorStyle")
    }
    _SwiperAttribute_onAnimationStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SwiperAttribute_onAnimationStart")
    }
    _SwiperAttribute_onAnimationEnd(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SwiperAttribute_onAnimationEnd")
    }
    _SwiperAttribute_onGestureSwipe(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SwiperAttribute_onGestureSwipe")
    }
    _SwiperAttribute_nestedScroll(ptr: KPointer, value: KInt): void {
        console.log("_SwiperAttribute_nestedScroll")
    }
    _SwiperAttribute_customContentTransition(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SwiperAttribute_customContentTransition")
    }
    _SwiperAttribute_onContentDidScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SwiperAttribute_onContentDidScroll")
    }
    _SwiperAttribute_indicatorInteractive(ptr: KPointer, value: KInt): void {
        console.log("_SwiperAttribute_indicatorInteractive")
    }
    _SwiperAttribute_displayArrow(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SwiperAttribute_displayArrow")
    }
    _SwiperAttribute_displayCount(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SwiperAttribute_displayCount")
    }
    _SwiperAttribute_prevMargin(ptr: KPointer, value: Length, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SwiperAttribute_prevMargin")
    }
    _SwiperAttribute_nextMargin(ptr: KPointer, value: Length, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SwiperAttribute_nextMargin")
    }
    _SwiperAttribute__onChangeEvent_index(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SwiperAttribute__onChangeEvent_index")
    }
    _IndicatorComponent_construct(id: KInt, flags: KInt): KPointer {
        console.log("_IndicatorComponent_construct")
        return -1
    }
    _IndicatorComponentInterface_setIndicatorComponentOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_IndicatorComponentInterface_setIndicatorComponentOptions")
    }
    _IndicatorComponentAttribute_initialIndex(ptr: KPointer, value: number): void {
        console.log("_IndicatorComponentAttribute_initialIndex")
    }
    _IndicatorComponentAttribute_count(ptr: KPointer, value: number): void {
        console.log("_IndicatorComponentAttribute_count")
    }
    _IndicatorComponentAttribute_style(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_IndicatorComponentAttribute_style")
    }
    _IndicatorComponentAttribute_loop(ptr: KPointer, value: KInt): void {
        console.log("_IndicatorComponentAttribute_loop")
    }
    _IndicatorComponentAttribute_vertical(ptr: KPointer, value: KInt): void {
        console.log("_IndicatorComponentAttribute_vertical")
    }
    _IndicatorComponentAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_IndicatorComponentAttribute_onChange")
    }
    _SymbolGlyph_construct(id: KInt, flags: KInt): KPointer {
        console.log("_SymbolGlyph_construct")
        return -1
    }
    _SymbolGlyphInterface_setSymbolGlyphOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SymbolGlyphInterface_setSymbolGlyphOptions")
    }
    _SymbolGlyphAttribute_fontSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SymbolGlyphAttribute_fontSize")
    }
    _SymbolGlyphAttribute_fontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SymbolGlyphAttribute_fontColor")
    }
    _SymbolGlyphAttribute_fontWeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SymbolGlyphAttribute_fontWeight")
    }
    _SymbolGlyphAttribute_effectStrategy(ptr: KPointer, value: KInt): void {
        console.log("_SymbolGlyphAttribute_effectStrategy")
    }
    _SymbolGlyphAttribute_renderingStrategy(ptr: KPointer, value: KInt): void {
        console.log("_SymbolGlyphAttribute_renderingStrategy")
    }
    _SymbolGlyphAttribute_symbolEffect0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SymbolGlyphAttribute_symbolEffect0")
    }
    _SymbolGlyphAttribute_symbolEffect1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SymbolGlyphAttribute_symbolEffect1")
    }
    _SymbolSpan_construct(id: KInt, flags: KInt): KPointer {
        console.log("_SymbolSpan_construct")
        return -1
    }
    _SymbolSpanInterface_setSymbolSpanOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SymbolSpanInterface_setSymbolSpanOptions")
    }
    _SymbolSpanAttribute_fontSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SymbolSpanAttribute_fontSize")
    }
    _SymbolSpanAttribute_fontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SymbolSpanAttribute_fontColor")
    }
    _SymbolSpanAttribute_fontWeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SymbolSpanAttribute_fontWeight")
    }
    _SymbolSpanAttribute_effectStrategy(ptr: KPointer, value: KInt): void {
        console.log("_SymbolSpanAttribute_effectStrategy")
    }
    _SymbolSpanAttribute_renderingStrategy(ptr: KPointer, value: KInt): void {
        console.log("_SymbolSpanAttribute_renderingStrategy")
    }
    _Tabs_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Tabs_construct")
        return -1
    }
    _TabsInterface_setTabsOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TabsInterface_setTabsOptions")
    }
    _TabsAttribute_vertical(ptr: KPointer, value: KInt): void {
        console.log("_TabsAttribute_vertical")
    }
    _TabsAttribute_barPosition(ptr: KPointer, value: KInt): void {
        console.log("_TabsAttribute_barPosition")
    }
    _TabsAttribute_scrollable(ptr: KPointer, value: KInt): void {
        console.log("_TabsAttribute_scrollable")
    }
    _TabsAttribute_barMode0(ptr: KPointer, value: KInt): void {
        console.log("_TabsAttribute_barMode0")
    }
    _TabsAttribute_barMode1(ptr: KPointer, value: KInt, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TabsAttribute_barMode1")
    }
    _TabsAttribute_barWidth(ptr: KPointer, value: Length): void {
        console.log("_TabsAttribute_barWidth")
    }
    _TabsAttribute_barHeight(ptr: KPointer, value: Length): void {
        console.log("_TabsAttribute_barHeight")
    }
    _TabsAttribute_animationDuration(ptr: KPointer, value: number): void {
        console.log("_TabsAttribute_animationDuration")
    }
    _TabsAttribute_animationMode(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TabsAttribute_animationMode")
    }
    _TabsAttribute_edgeEffect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TabsAttribute_edgeEffect")
    }
    _TabsAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TabsAttribute_onChange")
    }
    _TabsAttribute_onTabBarClick(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TabsAttribute_onTabBarClick")
    }
    _TabsAttribute_onAnimationStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TabsAttribute_onAnimationStart")
    }
    _TabsAttribute_onAnimationEnd(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TabsAttribute_onAnimationEnd")
    }
    _TabsAttribute_onGestureSwipe(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TabsAttribute_onGestureSwipe")
    }
    _TabsAttribute_fadingEdge(ptr: KPointer, value: KInt): void {
        console.log("_TabsAttribute_fadingEdge")
    }
    _TabsAttribute_divider(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TabsAttribute_divider")
    }
    _TabsAttribute_barOverlap(ptr: KPointer, value: KInt): void {
        console.log("_TabsAttribute_barOverlap")
    }
    _TabsAttribute_barBackgroundColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TabsAttribute_barBackgroundColor")
    }
    _TabsAttribute_barGridAlign(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TabsAttribute_barGridAlign")
    }
    _TabsAttribute_customContentTransition(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TabsAttribute_customContentTransition")
    }
    _TabsAttribute_barBackgroundBlurStyle0(ptr: KPointer, value: KInt): void {
        console.log("_TabsAttribute_barBackgroundBlurStyle0")
    }
    _TabsAttribute_barBackgroundBlurStyle1(ptr: KPointer, style: KInt, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TabsAttribute_barBackgroundBlurStyle1")
    }
    _TabsAttribute_barBackgroundEffect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TabsAttribute_barBackgroundEffect")
    }
    _TabsAttribute_onContentWillChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TabsAttribute_onContentWillChange")
    }
    _TabsAttribute_barModeScrollable(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TabsAttribute_barModeScrollable")
    }
    _TabsAttribute__onChangeEvent_index(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TabsAttribute__onChangeEvent_index")
    }
    _TabContent_construct(id: KInt, flags: KInt): KPointer {
        console.log("_TabContent_construct")
        return -1
    }
    _TabContentInterface_setTabContentOptions(ptr: KPointer): void {
        console.log("_TabContentInterface_setTabContentOptions")
    }
    _TabContentAttribute_tabBar0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TabContentAttribute_tabBar0")
    }
    _TabContentAttribute_tabBar1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TabContentAttribute_tabBar1")
    }
    _TabContentAttribute_onWillShow(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TabContentAttribute_onWillShow")
    }
    _TabContentAttribute_onWillHide(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TabContentAttribute_onWillHide")
    }
    _Text_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Text_construct")
        return -1
    }
    _TextInterface_setTextOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextInterface_setTextOptions")
    }
    _TextAttribute_font0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAttribute_font0")
    }
    _TextAttribute_font1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAttribute_font1")
    }
    _TextAttribute_fontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAttribute_fontColor")
    }
    _TextAttribute_fontSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAttribute_fontSize")
    }
    _TextAttribute_minFontSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAttribute_minFontSize")
    }
    _TextAttribute_maxFontSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAttribute_maxFontSize")
    }
    _TextAttribute_minFontScale(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAttribute_minFontScale")
    }
    _TextAttribute_maxFontScale(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAttribute_maxFontScale")
    }
    _TextAttribute_fontStyle(ptr: KPointer, value: KInt): void {
        console.log("_TextAttribute_fontStyle")
    }
    _TextAttribute_fontWeight0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAttribute_fontWeight0")
    }
    _TextAttribute_fontWeight1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAttribute_fontWeight1")
    }
    _TextAttribute_lineSpacing(ptr: KPointer, value: KPointer): void {
        console.log("_TextAttribute_lineSpacing")
    }
    _TextAttribute_textAlign(ptr: KPointer, value: KInt): void {
        console.log("_TextAttribute_textAlign")
    }
    _TextAttribute_lineHeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAttribute_lineHeight")
    }
    _TextAttribute_textOverflow(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAttribute_textOverflow")
    }
    _TextAttribute_fontFamily(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAttribute_fontFamily")
    }
    _TextAttribute_maxLines(ptr: KPointer, value: number): void {
        console.log("_TextAttribute_maxLines")
    }
    _TextAttribute_decoration(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAttribute_decoration")
    }
    _TextAttribute_letterSpacing(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAttribute_letterSpacing")
    }
    _TextAttribute_textCase(ptr: KPointer, value: KInt): void {
        console.log("_TextAttribute_textCase")
    }
    _TextAttribute_baselineOffset(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAttribute_baselineOffset")
    }
    _TextAttribute_copyOption(ptr: KPointer, value: KInt): void {
        console.log("_TextAttribute_copyOption")
    }
    _TextAttribute_draggable(ptr: KPointer, value: KInt): void {
        console.log("_TextAttribute_draggable")
    }
    _TextAttribute_textShadow(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAttribute_textShadow")
    }
    _TextAttribute_heightAdaptivePolicy(ptr: KPointer, value: KInt): void {
        console.log("_TextAttribute_heightAdaptivePolicy")
    }
    _TextAttribute_textIndent(ptr: KPointer, value: Length): void {
        console.log("_TextAttribute_textIndent")
    }
    _TextAttribute_wordBreak(ptr: KPointer, value: KInt): void {
        console.log("_TextAttribute_wordBreak")
    }
    _TextAttribute_lineBreakStrategy(ptr: KPointer, value: KInt): void {
        console.log("_TextAttribute_lineBreakStrategy")
    }
    _TextAttribute_onCopy(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAttribute_onCopy")
    }
    _TextAttribute_caretColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAttribute_caretColor")
    }
    _TextAttribute_selectedBackgroundColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAttribute_selectedBackgroundColor")
    }
    _TextAttribute_ellipsisMode(ptr: KPointer, value: KInt): void {
        console.log("_TextAttribute_ellipsisMode")
    }
    _TextAttribute_enableDataDetector(ptr: KPointer, value: KInt): void {
        console.log("_TextAttribute_enableDataDetector")
    }
    _TextAttribute_dataDetectorConfig(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAttribute_dataDetectorConfig")
    }
    _TextAttribute_onTextSelectionChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAttribute_onTextSelectionChange")
    }
    _TextAttribute_fontFeature(ptr: KPointer, value: KStringPtr): void {
        console.log("_TextAttribute_fontFeature")
    }
    _TextAttribute_privacySensitive(ptr: KPointer, value: KInt): void {
        console.log("_TextAttribute_privacySensitive")
    }
    _TextAttribute_textSelectable(ptr: KPointer, value: KInt): void {
        console.log("_TextAttribute_textSelectable")
    }
    _TextAttribute_editMenuOptions(ptr: KPointer, value: KPointer): void {
        console.log("_TextAttribute_editMenuOptions")
    }
    _TextAttribute_halfLeading(ptr: KPointer, value: KInt): void {
        console.log("_TextAttribute_halfLeading")
    }
    _TextAttribute_enableHapticFeedback(ptr: KPointer, value: KInt): void {
        console.log("_TextAttribute_enableHapticFeedback")
    }
    _TextAttribute_selection(ptr: KPointer, selectionStart: number, selectionEnd: number): void {
        console.log("_TextAttribute_selection")
    }
    _TextAttribute_bindSelectionMenu(ptr: KPointer, spanType: KInt, thisArray: Uint8Array, thisLength: int32, responseType: KInt): void {
        console.log("_TextAttribute_bindSelectionMenu")
    }
    _TextArea_construct(id: KInt, flags: KInt): KPointer {
        console.log("_TextArea_construct")
        return -1
    }
    _TextAreaInterface_setTextAreaOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAreaInterface_setTextAreaOptions")
    }
    _TextAreaAttribute_placeholderColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAreaAttribute_placeholderColor")
    }
    _TextAreaAttribute_placeholderFont(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAreaAttribute_placeholderFont")
    }
    _TextAreaAttribute_enterKeyType(ptr: KPointer, value: KInt): void {
        console.log("_TextAreaAttribute_enterKeyType")
    }
    _TextAreaAttribute_textAlign(ptr: KPointer, value: KInt): void {
        console.log("_TextAreaAttribute_textAlign")
    }
    _TextAreaAttribute_caretColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAreaAttribute_caretColor")
    }
    _TextAreaAttribute_fontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAreaAttribute_fontColor")
    }
    _TextAreaAttribute_fontSize(ptr: KPointer, value: Length): void {
        console.log("_TextAreaAttribute_fontSize")
    }
    _TextAreaAttribute_fontStyle(ptr: KPointer, value: KInt): void {
        console.log("_TextAreaAttribute_fontStyle")
    }
    _TextAreaAttribute_fontWeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAreaAttribute_fontWeight")
    }
    _TextAreaAttribute_fontFamily(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAreaAttribute_fontFamily")
    }
    _TextAreaAttribute_textOverflow(ptr: KPointer, value: KInt): void {
        console.log("_TextAreaAttribute_textOverflow")
    }
    _TextAreaAttribute_textIndent(ptr: KPointer, value: Length): void {
        console.log("_TextAreaAttribute_textIndent")
    }
    _TextAreaAttribute_caretStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAreaAttribute_caretStyle")
    }
    _TextAreaAttribute_selectedBackgroundColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAreaAttribute_selectedBackgroundColor")
    }
    _TextAreaAttribute_onSubmit0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAreaAttribute_onSubmit0")
    }
    _TextAreaAttribute_onSubmit1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAreaAttribute_onSubmit1")
    }
    _TextAreaAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAreaAttribute_onChange")
    }
    _TextAreaAttribute_onTextSelectionChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAreaAttribute_onTextSelectionChange")
    }
    _TextAreaAttribute_onContentScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAreaAttribute_onContentScroll")
    }
    _TextAreaAttribute_onEditChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAreaAttribute_onEditChange")
    }
    _TextAreaAttribute_onCopy(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAreaAttribute_onCopy")
    }
    _TextAreaAttribute_onCut(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAreaAttribute_onCut")
    }
    _TextAreaAttribute_onPaste(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAreaAttribute_onPaste")
    }
    _TextAreaAttribute_copyOption(ptr: KPointer, value: KInt): void {
        console.log("_TextAreaAttribute_copyOption")
    }
    _TextAreaAttribute_enableKeyboardOnFocus(ptr: KPointer, value: KInt): void {
        console.log("_TextAreaAttribute_enableKeyboardOnFocus")
    }
    _TextAreaAttribute_maxLength(ptr: KPointer, value: number): void {
        console.log("_TextAreaAttribute_maxLength")
    }
    _TextAreaAttribute_style(ptr: KPointer, value: KInt): void {
        console.log("_TextAreaAttribute_style")
    }
    _TextAreaAttribute_barState(ptr: KPointer, value: KInt): void {
        console.log("_TextAreaAttribute_barState")
    }
    _TextAreaAttribute_selectionMenuHidden(ptr: KPointer, value: KInt): void {
        console.log("_TextAreaAttribute_selectionMenuHidden")
    }
    _TextAreaAttribute_minFontSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAreaAttribute_minFontSize")
    }
    _TextAreaAttribute_maxFontSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAreaAttribute_maxFontSize")
    }
    _TextAreaAttribute_heightAdaptivePolicy(ptr: KPointer, value: KInt): void {
        console.log("_TextAreaAttribute_heightAdaptivePolicy")
    }
    _TextAreaAttribute_maxLines(ptr: KPointer, value: number): void {
        console.log("_TextAreaAttribute_maxLines")
    }
    _TextAreaAttribute_wordBreak(ptr: KPointer, value: KInt): void {
        console.log("_TextAreaAttribute_wordBreak")
    }
    _TextAreaAttribute_lineBreakStrategy(ptr: KPointer, value: KInt): void {
        console.log("_TextAreaAttribute_lineBreakStrategy")
    }
    _TextAreaAttribute_decoration(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAreaAttribute_decoration")
    }
    _TextAreaAttribute_letterSpacing(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAreaAttribute_letterSpacing")
    }
    _TextAreaAttribute_lineSpacing(ptr: KPointer, value: KPointer): void {
        console.log("_TextAreaAttribute_lineSpacing")
    }
    _TextAreaAttribute_lineHeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAreaAttribute_lineHeight")
    }
    _TextAreaAttribute_type(ptr: KPointer, value: KInt): void {
        console.log("_TextAreaAttribute_type")
    }
    _TextAreaAttribute_enableAutoFill(ptr: KPointer, value: KInt): void {
        console.log("_TextAreaAttribute_enableAutoFill")
    }
    _TextAreaAttribute_contentType(ptr: KPointer, value: KInt): void {
        console.log("_TextAreaAttribute_contentType")
    }
    _TextAreaAttribute_fontFeature(ptr: KPointer, value: KStringPtr): void {
        console.log("_TextAreaAttribute_fontFeature")
    }
    _TextAreaAttribute_onWillInsert(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAreaAttribute_onWillInsert")
    }
    _TextAreaAttribute_onDidInsert(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAreaAttribute_onDidInsert")
    }
    _TextAreaAttribute_onWillDelete(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAreaAttribute_onWillDelete")
    }
    _TextAreaAttribute_onDidDelete(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAreaAttribute_onDidDelete")
    }
    _TextAreaAttribute_editMenuOptions(ptr: KPointer, value: KPointer): void {
        console.log("_TextAreaAttribute_editMenuOptions")
    }
    _TextAreaAttribute_enablePreviewText(ptr: KPointer, value: KInt): void {
        console.log("_TextAreaAttribute_enablePreviewText")
    }
    _TextAreaAttribute_enableHapticFeedback(ptr: KPointer, value: KInt): void {
        console.log("_TextAreaAttribute_enableHapticFeedback")
    }
    _TextAreaAttribute_inputFilter(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAreaAttribute_inputFilter")
    }
    _TextAreaAttribute_showCounter(ptr: KPointer, value: KInt, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAreaAttribute_showCounter")
    }
    _TextAreaAttribute_customKeyboard(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAreaAttribute_customKeyboard")
    }
    _TextAreaAttribute__onChangeEvent_text(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAreaAttribute__onChangeEvent_text")
    }
    _TextClock_construct(id: KInt, flags: KInt): KPointer {
        console.log("_TextClock_construct")
        return -1
    }
    _TextClockInterface_setTextClockOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextClockInterface_setTextClockOptions")
    }
    _TextClockAttribute_format(ptr: KPointer, value: KStringPtr): void {
        console.log("_TextClockAttribute_format")
    }
    _TextClockAttribute_onDateChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextClockAttribute_onDateChange")
    }
    _TextClockAttribute_fontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextClockAttribute_fontColor")
    }
    _TextClockAttribute_fontSize(ptr: KPointer, value: Length): void {
        console.log("_TextClockAttribute_fontSize")
    }
    _TextClockAttribute_fontStyle(ptr: KPointer, value: KInt): void {
        console.log("_TextClockAttribute_fontStyle")
    }
    _TextClockAttribute_fontWeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextClockAttribute_fontWeight")
    }
    _TextClockAttribute_fontFamily(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextClockAttribute_fontFamily")
    }
    _TextClockAttribute_textShadow(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextClockAttribute_textShadow")
    }
    _TextClockAttribute_fontFeature(ptr: KPointer, value: KStringPtr): void {
        console.log("_TextClockAttribute_fontFeature")
    }
    _TextClockAttribute_contentModifier(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextClockAttribute_contentModifier")
    }
    _TextClockAttribute_dateTimeOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextClockAttribute_dateTimeOptions")
    }
    _TextInput_construct(id: KInt, flags: KInt): KPointer {
        console.log("_TextInput_construct")
        return -1
    }
    _TextInputInterface_setTextInputOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextInputInterface_setTextInputOptions")
    }
    _TextInputAttribute_type(ptr: KPointer, value: KInt): void {
        console.log("_TextInputAttribute_type")
    }
    _TextInputAttribute_contentType(ptr: KPointer, value: KInt): void {
        console.log("_TextInputAttribute_contentType")
    }
    _TextInputAttribute_placeholderColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextInputAttribute_placeholderColor")
    }
    _TextInputAttribute_textOverflow(ptr: KPointer, value: KInt): void {
        console.log("_TextInputAttribute_textOverflow")
    }
    _TextInputAttribute_textIndent(ptr: KPointer, value: Length): void {
        console.log("_TextInputAttribute_textIndent")
    }
    _TextInputAttribute_placeholderFont(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextInputAttribute_placeholderFont")
    }
    _TextInputAttribute_enterKeyType(ptr: KPointer, value: KInt): void {
        console.log("_TextInputAttribute_enterKeyType")
    }
    _TextInputAttribute_caretColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextInputAttribute_caretColor")
    }
    _TextInputAttribute_onEditChanged(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextInputAttribute_onEditChanged")
    }
    _TextInputAttribute_onEditChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextInputAttribute_onEditChange")
    }
    _TextInputAttribute_onSubmit(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextInputAttribute_onSubmit")
    }
    _TextInputAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextInputAttribute_onChange")
    }
    _TextInputAttribute_onTextSelectionChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextInputAttribute_onTextSelectionChange")
    }
    _TextInputAttribute_onContentScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextInputAttribute_onContentScroll")
    }
    _TextInputAttribute_maxLength(ptr: KPointer, value: number): void {
        console.log("_TextInputAttribute_maxLength")
    }
    _TextInputAttribute_fontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextInputAttribute_fontColor")
    }
    _TextInputAttribute_fontSize(ptr: KPointer, value: Length): void {
        console.log("_TextInputAttribute_fontSize")
    }
    _TextInputAttribute_fontStyle(ptr: KPointer, value: KInt): void {
        console.log("_TextInputAttribute_fontStyle")
    }
    _TextInputAttribute_fontWeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextInputAttribute_fontWeight")
    }
    _TextInputAttribute_fontFamily(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextInputAttribute_fontFamily")
    }
    _TextInputAttribute_onCopy(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextInputAttribute_onCopy")
    }
    _TextInputAttribute_onCut(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextInputAttribute_onCut")
    }
    _TextInputAttribute_onPaste(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextInputAttribute_onPaste")
    }
    _TextInputAttribute_copyOption(ptr: KPointer, value: KInt): void {
        console.log("_TextInputAttribute_copyOption")
    }
    _TextInputAttribute_showPasswordIcon(ptr: KPointer, value: KInt): void {
        console.log("_TextInputAttribute_showPasswordIcon")
    }
    _TextInputAttribute_textAlign(ptr: KPointer, value: KInt): void {
        console.log("_TextInputAttribute_textAlign")
    }
    _TextInputAttribute_style(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextInputAttribute_style")
    }
    _TextInputAttribute_caretStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextInputAttribute_caretStyle")
    }
    _TextInputAttribute_selectedBackgroundColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextInputAttribute_selectedBackgroundColor")
    }
    _TextInputAttribute_caretPosition(ptr: KPointer, value: number): void {
        console.log("_TextInputAttribute_caretPosition")
    }
    _TextInputAttribute_enableKeyboardOnFocus(ptr: KPointer, value: KInt): void {
        console.log("_TextInputAttribute_enableKeyboardOnFocus")
    }
    _TextInputAttribute_passwordIcon(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextInputAttribute_passwordIcon")
    }
    _TextInputAttribute_showError(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextInputAttribute_showError")
    }
    _TextInputAttribute_showUnit(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextInputAttribute_showUnit")
    }
    _TextInputAttribute_showUnderline(ptr: KPointer, value: KInt): void {
        console.log("_TextInputAttribute_showUnderline")
    }
    _TextInputAttribute_underlineColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextInputAttribute_underlineColor")
    }
    _TextInputAttribute_selectionMenuHidden(ptr: KPointer, value: KInt): void {
        console.log("_TextInputAttribute_selectionMenuHidden")
    }
    _TextInputAttribute_barState(ptr: KPointer, value: KInt): void {
        console.log("_TextInputAttribute_barState")
    }
    _TextInputAttribute_maxLines(ptr: KPointer, value: number): void {
        console.log("_TextInputAttribute_maxLines")
    }
    _TextInputAttribute_wordBreak(ptr: KPointer, value: KInt): void {
        console.log("_TextInputAttribute_wordBreak")
    }
    _TextInputAttribute_lineBreakStrategy(ptr: KPointer, value: KInt): void {
        console.log("_TextInputAttribute_lineBreakStrategy")
    }
    _TextInputAttribute_cancelButton0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextInputAttribute_cancelButton0")
    }
    _TextInputAttribute_cancelButton1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextInputAttribute_cancelButton1")
    }
    _TextInputAttribute_selectAll(ptr: KPointer, value: KInt): void {
        console.log("_TextInputAttribute_selectAll")
    }
    _TextInputAttribute_minFontSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextInputAttribute_minFontSize")
    }
    _TextInputAttribute_maxFontSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextInputAttribute_maxFontSize")
    }
    _TextInputAttribute_heightAdaptivePolicy(ptr: KPointer, value: KInt): void {
        console.log("_TextInputAttribute_heightAdaptivePolicy")
    }
    _TextInputAttribute_enableAutoFill(ptr: KPointer, value: KInt): void {
        console.log("_TextInputAttribute_enableAutoFill")
    }
    _TextInputAttribute_decoration(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextInputAttribute_decoration")
    }
    _TextInputAttribute_letterSpacing(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextInputAttribute_letterSpacing")
    }
    _TextInputAttribute_lineHeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextInputAttribute_lineHeight")
    }
    _TextInputAttribute_passwordRules(ptr: KPointer, value: KStringPtr): void {
        console.log("_TextInputAttribute_passwordRules")
    }
    _TextInputAttribute_fontFeature(ptr: KPointer, value: KStringPtr): void {
        console.log("_TextInputAttribute_fontFeature")
    }
    _TextInputAttribute_showPassword(ptr: KPointer, value: KInt): void {
        console.log("_TextInputAttribute_showPassword")
    }
    _TextInputAttribute_onSecurityStateChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextInputAttribute_onSecurityStateChange")
    }
    _TextInputAttribute_onWillInsert(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextInputAttribute_onWillInsert")
    }
    _TextInputAttribute_onDidInsert(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextInputAttribute_onDidInsert")
    }
    _TextInputAttribute_onWillDelete(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextInputAttribute_onWillDelete")
    }
    _TextInputAttribute_onDidDelete(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextInputAttribute_onDidDelete")
    }
    _TextInputAttribute_editMenuOptions(ptr: KPointer, value: KPointer): void {
        console.log("_TextInputAttribute_editMenuOptions")
    }
    _TextInputAttribute_enablePreviewText(ptr: KPointer, value: KInt): void {
        console.log("_TextInputAttribute_enablePreviewText")
    }
    _TextInputAttribute_enableHapticFeedback(ptr: KPointer, value: KInt): void {
        console.log("_TextInputAttribute_enableHapticFeedback")
    }
    _TextInputAttribute_inputFilter(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextInputAttribute_inputFilter")
    }
    _TextInputAttribute_customKeyboard(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextInputAttribute_customKeyboard")
    }
    _TextInputAttribute_showCounter(ptr: KPointer, value: KInt, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextInputAttribute_showCounter")
    }
    _TextInputAttribute__onChangeEvent_text(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextInputAttribute__onChangeEvent_text")
    }
    _TextPicker_construct(id: KInt, flags: KInt): KPointer {
        console.log("_TextPicker_construct")
        return -1
    }
    _TextPickerInterface_setTextPickerOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextPickerInterface_setTextPickerOptions")
    }
    _TextPickerAttribute_defaultPickerItemHeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextPickerAttribute_defaultPickerItemHeight")
    }
    _TextPickerAttribute_canLoop(ptr: KPointer, value: KInt): void {
        console.log("_TextPickerAttribute_canLoop")
    }
    _TextPickerAttribute_disappearTextStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextPickerAttribute_disappearTextStyle")
    }
    _TextPickerAttribute_textStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextPickerAttribute_textStyle")
    }
    _TextPickerAttribute_selectedTextStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextPickerAttribute_selectedTextStyle")
    }
    _TextPickerAttribute_onAccept(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextPickerAttribute_onAccept")
    }
    _TextPickerAttribute_onCancel(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextPickerAttribute_onCancel")
    }
    _TextPickerAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextPickerAttribute_onChange")
    }
    _TextPickerAttribute_selectedIndex(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextPickerAttribute_selectedIndex")
    }
    _TextPickerAttribute_divider(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextPickerAttribute_divider")
    }
    _TextPickerAttribute_gradientHeight(ptr: KPointer, value: Length): void {
        console.log("_TextPickerAttribute_gradientHeight")
    }
    _TextPickerAttribute__onChangeEvent_selected(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextPickerAttribute__onChangeEvent_selected")
    }
    _TextPickerAttribute__onChangeEvent_value(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextPickerAttribute__onChangeEvent_value")
    }
    _TextTimer_construct(id: KInt, flags: KInt): KPointer {
        console.log("_TextTimer_construct")
        return -1
    }
    _TextTimerInterface_setTextTimerOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextTimerInterface_setTextTimerOptions")
    }
    _TextTimerAttribute_format(ptr: KPointer, value: KStringPtr): void {
        console.log("_TextTimerAttribute_format")
    }
    _TextTimerAttribute_fontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextTimerAttribute_fontColor")
    }
    _TextTimerAttribute_fontSize(ptr: KPointer, value: Length): void {
        console.log("_TextTimerAttribute_fontSize")
    }
    _TextTimerAttribute_fontStyle(ptr: KPointer, value: KInt): void {
        console.log("_TextTimerAttribute_fontStyle")
    }
    _TextTimerAttribute_fontWeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextTimerAttribute_fontWeight")
    }
    _TextTimerAttribute_fontFamily(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextTimerAttribute_fontFamily")
    }
    _TextTimerAttribute_onTimer(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextTimerAttribute_onTimer")
    }
    _TextTimerAttribute_textShadow(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextTimerAttribute_textShadow")
    }
    _TextTimerAttribute_contentModifier(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextTimerAttribute_contentModifier")
    }
    _TimePicker_construct(id: KInt, flags: KInt): KPointer {
        console.log("_TimePicker_construct")
        return -1
    }
    _TimePickerInterface_setTimePickerOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TimePickerInterface_setTimePickerOptions")
    }
    _TimePickerAttribute_useMilitaryTime(ptr: KPointer, value: KInt): void {
        console.log("_TimePickerAttribute_useMilitaryTime")
    }
    _TimePickerAttribute_loop(ptr: KPointer, value: KInt): void {
        console.log("_TimePickerAttribute_loop")
    }
    _TimePickerAttribute_disappearTextStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TimePickerAttribute_disappearTextStyle")
    }
    _TimePickerAttribute_textStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TimePickerAttribute_textStyle")
    }
    _TimePickerAttribute_selectedTextStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TimePickerAttribute_selectedTextStyle")
    }
    _TimePickerAttribute_dateTimeOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TimePickerAttribute_dateTimeOptions")
    }
    _TimePickerAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TimePickerAttribute_onChange")
    }
    _TimePickerAttribute_enableHapticFeedback(ptr: KPointer, value: KInt): void {
        console.log("_TimePickerAttribute_enableHapticFeedback")
    }
    _TimePickerAttribute__onChangeEvent_selected(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TimePickerAttribute__onChangeEvent_selected")
    }
    _Toggle_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Toggle_construct")
        return -1
    }
    _ToggleInterface_setToggleOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ToggleInterface_setToggleOptions")
    }
    _ToggleAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ToggleAttribute_onChange")
    }
    _ToggleAttribute_contentModifier(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ToggleAttribute_contentModifier")
    }
    _ToggleAttribute_selectedColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ToggleAttribute_selectedColor")
    }
    _ToggleAttribute_switchPointColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ToggleAttribute_switchPointColor")
    }
    _ToggleAttribute_switchStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ToggleAttribute_switchStyle")
    }
    _ToggleAttribute__onChangeEvent_isOn(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ToggleAttribute__onChangeEvent_isOn")
    }
    _Video_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Video_construct")
        return -1
    }
    _VideoInterface_setVideoOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_VideoInterface_setVideoOptions")
    }
    _VideoAttribute_muted(ptr: KPointer, value: KInt): void {
        console.log("_VideoAttribute_muted")
    }
    _VideoAttribute_autoPlay(ptr: KPointer, value: KInt): void {
        console.log("_VideoAttribute_autoPlay")
    }
    _VideoAttribute_controls(ptr: KPointer, value: KInt): void {
        console.log("_VideoAttribute_controls")
    }
    _VideoAttribute_loop(ptr: KPointer, value: KInt): void {
        console.log("_VideoAttribute_loop")
    }
    _VideoAttribute_objectFit(ptr: KPointer, value: KInt): void {
        console.log("_VideoAttribute_objectFit")
    }
    _VideoAttribute_onStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_VideoAttribute_onStart")
    }
    _VideoAttribute_onPause(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_VideoAttribute_onPause")
    }
    _VideoAttribute_onFinish(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_VideoAttribute_onFinish")
    }
    _VideoAttribute_onFullscreenChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_VideoAttribute_onFullscreenChange")
    }
    _VideoAttribute_onPrepared(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_VideoAttribute_onPrepared")
    }
    _VideoAttribute_onSeeking(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_VideoAttribute_onSeeking")
    }
    _VideoAttribute_onSeeked(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_VideoAttribute_onSeeked")
    }
    _VideoAttribute_onUpdate(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_VideoAttribute_onUpdate")
    }
    _VideoAttribute_onError(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_VideoAttribute_onError")
    }
    _VideoAttribute_onStop(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_VideoAttribute_onStop")
    }
    _VideoAttribute_enableAnalyzer(ptr: KPointer, value: KInt): void {
        console.log("_VideoAttribute_enableAnalyzer")
    }
    _VideoAttribute_analyzerConfig(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_VideoAttribute_analyzerConfig")
    }
    _Web_construct(id: KInt, flags: KInt): KPointer {
        console.log("_Web_construct")
        return -1
    }
    _WebInterface_setWebOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebInterface_setWebOptions")
    }
    _WebAttribute_javaScriptAccess(ptr: KPointer, value: KInt): void {
        console.log("_WebAttribute_javaScriptAccess")
    }
    _WebAttribute_fileAccess(ptr: KPointer, value: KInt): void {
        console.log("_WebAttribute_fileAccess")
    }
    _WebAttribute_onlineImageAccess(ptr: KPointer, value: KInt): void {
        console.log("_WebAttribute_onlineImageAccess")
    }
    _WebAttribute_domStorageAccess(ptr: KPointer, value: KInt): void {
        console.log("_WebAttribute_domStorageAccess")
    }
    _WebAttribute_imageAccess(ptr: KPointer, value: KInt): void {
        console.log("_WebAttribute_imageAccess")
    }
    _WebAttribute_mixedMode(ptr: KPointer, value: KInt): void {
        console.log("_WebAttribute_mixedMode")
    }
    _WebAttribute_zoomAccess(ptr: KPointer, value: KInt): void {
        console.log("_WebAttribute_zoomAccess")
    }
    _WebAttribute_geolocationAccess(ptr: KPointer, value: KInt): void {
        console.log("_WebAttribute_geolocationAccess")
    }
    _WebAttribute_javaScriptProxy(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_javaScriptProxy")
    }
    _WebAttribute_password(ptr: KPointer, value: KInt): void {
        console.log("_WebAttribute_password")
    }
    _WebAttribute_cacheMode(ptr: KPointer, value: KInt): void {
        console.log("_WebAttribute_cacheMode")
    }
    _WebAttribute_darkMode(ptr: KPointer, value: KInt): void {
        console.log("_WebAttribute_darkMode")
    }
    _WebAttribute_forceDarkAccess(ptr: KPointer, value: KInt): void {
        console.log("_WebAttribute_forceDarkAccess")
    }
    _WebAttribute_mediaOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_mediaOptions")
    }
    _WebAttribute_tableData(ptr: KPointer, value: KInt): void {
        console.log("_WebAttribute_tableData")
    }
    _WebAttribute_wideViewModeAccess(ptr: KPointer, value: KInt): void {
        console.log("_WebAttribute_wideViewModeAccess")
    }
    _WebAttribute_overviewModeAccess(ptr: KPointer, value: KInt): void {
        console.log("_WebAttribute_overviewModeAccess")
    }
    _WebAttribute_overScrollMode(ptr: KPointer, value: KInt): void {
        console.log("_WebAttribute_overScrollMode")
    }
    _WebAttribute_textZoomAtio(ptr: KPointer, value: number): void {
        console.log("_WebAttribute_textZoomAtio")
    }
    _WebAttribute_textZoomRatio(ptr: KPointer, value: number): void {
        console.log("_WebAttribute_textZoomRatio")
    }
    _WebAttribute_databaseAccess(ptr: KPointer, value: KInt): void {
        console.log("_WebAttribute_databaseAccess")
    }
    _WebAttribute_initialScale(ptr: KPointer, value: number): void {
        console.log("_WebAttribute_initialScale")
    }
    _WebAttribute_userAgent(ptr: KPointer, value: KStringPtr): void {
        console.log("_WebAttribute_userAgent")
    }
    _WebAttribute_metaViewport(ptr: KPointer, value: KInt): void {
        console.log("_WebAttribute_metaViewport")
    }
    _WebAttribute_onPageEnd(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onPageEnd")
    }
    _WebAttribute_onPageBegin(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onPageBegin")
    }
    _WebAttribute_onProgressChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onProgressChange")
    }
    _WebAttribute_onTitleReceive(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onTitleReceive")
    }
    _WebAttribute_onGeolocationHide(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onGeolocationHide")
    }
    _WebAttribute_onGeolocationShow(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onGeolocationShow")
    }
    _WebAttribute_onRequestSelected(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onRequestSelected")
    }
    _WebAttribute_onAlert(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onAlert")
    }
    _WebAttribute_onBeforeUnload(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onBeforeUnload")
    }
    _WebAttribute_onConfirm(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onConfirm")
    }
    _WebAttribute_onPrompt(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onPrompt")
    }
    _WebAttribute_onConsole(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onConsole")
    }
    _WebAttribute_onErrorReceive(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onErrorReceive")
    }
    _WebAttribute_onHttpErrorReceive(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onHttpErrorReceive")
    }
    _WebAttribute_onDownloadStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onDownloadStart")
    }
    _WebAttribute_onRefreshAccessedHistory(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onRefreshAccessedHistory")
    }
    _WebAttribute_onUrlLoadIntercept(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onUrlLoadIntercept")
    }
    _WebAttribute_onSslErrorReceive(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onSslErrorReceive")
    }
    _WebAttribute_onRenderExited0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onRenderExited0")
    }
    _WebAttribute_onRenderExited1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onRenderExited1")
    }
    _WebAttribute_onShowFileSelector(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onShowFileSelector")
    }
    _WebAttribute_onFileSelectorShow(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onFileSelectorShow")
    }
    _WebAttribute_onResourceLoad(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onResourceLoad")
    }
    _WebAttribute_onFullScreenExit(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onFullScreenExit")
    }
    _WebAttribute_onFullScreenEnter(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onFullScreenEnter")
    }
    _WebAttribute_onScaleChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onScaleChange")
    }
    _WebAttribute_onHttpAuthRequest(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onHttpAuthRequest")
    }
    _WebAttribute_onInterceptRequest(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onInterceptRequest")
    }
    _WebAttribute_onPermissionRequest(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onPermissionRequest")
    }
    _WebAttribute_onScreenCaptureRequest(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onScreenCaptureRequest")
    }
    _WebAttribute_onContextMenuShow(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onContextMenuShow")
    }
    _WebAttribute_onContextMenuHide(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onContextMenuHide")
    }
    _WebAttribute_mediaPlayGestureAccess(ptr: KPointer, value: KInt): void {
        console.log("_WebAttribute_mediaPlayGestureAccess")
    }
    _WebAttribute_onSearchResultReceive(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onSearchResultReceive")
    }
    _WebAttribute_onScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onScroll")
    }
    _WebAttribute_onSslErrorEventReceive(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onSslErrorEventReceive")
    }
    _WebAttribute_onSslErrorEvent(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onSslErrorEvent")
    }
    _WebAttribute_onClientAuthenticationRequest(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onClientAuthenticationRequest")
    }
    _WebAttribute_onWindowNew(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onWindowNew")
    }
    _WebAttribute_onWindowExit(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onWindowExit")
    }
    _WebAttribute_multiWindowAccess(ptr: KPointer, value: KInt): void {
        console.log("_WebAttribute_multiWindowAccess")
    }
    _WebAttribute_onInterceptKeyEvent(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onInterceptKeyEvent")
    }
    _WebAttribute_webStandardFont(ptr: KPointer, value: KStringPtr): void {
        console.log("_WebAttribute_webStandardFont")
    }
    _WebAttribute_webSerifFont(ptr: KPointer, value: KStringPtr): void {
        console.log("_WebAttribute_webSerifFont")
    }
    _WebAttribute_webSansSerifFont(ptr: KPointer, value: KStringPtr): void {
        console.log("_WebAttribute_webSansSerifFont")
    }
    _WebAttribute_webFixedFont(ptr: KPointer, value: KStringPtr): void {
        console.log("_WebAttribute_webFixedFont")
    }
    _WebAttribute_webFantasyFont(ptr: KPointer, value: KStringPtr): void {
        console.log("_WebAttribute_webFantasyFont")
    }
    _WebAttribute_webCursiveFont(ptr: KPointer, value: KStringPtr): void {
        console.log("_WebAttribute_webCursiveFont")
    }
    _WebAttribute_defaultFixedFontSize(ptr: KPointer, value: number): void {
        console.log("_WebAttribute_defaultFixedFontSize")
    }
    _WebAttribute_defaultFontSize(ptr: KPointer, value: number): void {
        console.log("_WebAttribute_defaultFontSize")
    }
    _WebAttribute_minFontSize(ptr: KPointer, value: number): void {
        console.log("_WebAttribute_minFontSize")
    }
    _WebAttribute_minLogicalFontSize(ptr: KPointer, value: number): void {
        console.log("_WebAttribute_minLogicalFontSize")
    }
    _WebAttribute_defaultTextEncodingFormat(ptr: KPointer, value: KStringPtr): void {
        console.log("_WebAttribute_defaultTextEncodingFormat")
    }
    _WebAttribute_forceDisplayScrollBar(ptr: KPointer, value: KInt): void {
        console.log("_WebAttribute_forceDisplayScrollBar")
    }
    _WebAttribute_blockNetwork(ptr: KPointer, value: KInt): void {
        console.log("_WebAttribute_blockNetwork")
    }
    _WebAttribute_horizontalScrollBarAccess(ptr: KPointer, value: KInt): void {
        console.log("_WebAttribute_horizontalScrollBarAccess")
    }
    _WebAttribute_verticalScrollBarAccess(ptr: KPointer, value: KInt): void {
        console.log("_WebAttribute_verticalScrollBarAccess")
    }
    _WebAttribute_onTouchIconUrlReceived(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onTouchIconUrlReceived")
    }
    _WebAttribute_onFaviconReceived(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onFaviconReceived")
    }
    _WebAttribute_onPageVisible(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onPageVisible")
    }
    _WebAttribute_onDataResubmitted(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onDataResubmitted")
    }
    _WebAttribute_pinchSmooth(ptr: KPointer, value: KInt): void {
        console.log("_WebAttribute_pinchSmooth")
    }
    _WebAttribute_allowWindowOpenMethod(ptr: KPointer, value: KInt): void {
        console.log("_WebAttribute_allowWindowOpenMethod")
    }
    _WebAttribute_onAudioStateChanged(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onAudioStateChanged")
    }
    _WebAttribute_onFirstContentfulPaint(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onFirstContentfulPaint")
    }
    _WebAttribute_onFirstMeaningfulPaint(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onFirstMeaningfulPaint")
    }
    _WebAttribute_onLargestContentfulPaint(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onLargestContentfulPaint")
    }
    _WebAttribute_onLoadIntercept(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onLoadIntercept")
    }
    _WebAttribute_onControllerAttached(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onControllerAttached")
    }
    _WebAttribute_onOverScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onOverScroll")
    }
    _WebAttribute_onSafeBrowsingCheckResult(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onSafeBrowsingCheckResult")
    }
    _WebAttribute_onNavigationEntryCommitted(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onNavigationEntryCommitted")
    }
    _WebAttribute_onIntelligentTrackingPreventionResult(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onIntelligentTrackingPreventionResult")
    }
    _WebAttribute_javaScriptOnDocumentStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_javaScriptOnDocumentStart")
    }
    _WebAttribute_javaScriptOnDocumentEnd(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_javaScriptOnDocumentEnd")
    }
    _WebAttribute_layoutMode(ptr: KPointer, value: KInt): void {
        console.log("_WebAttribute_layoutMode")
    }
    _WebAttribute_nestedScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_nestedScroll")
    }
    _WebAttribute_enableNativeEmbedMode(ptr: KPointer, value: KInt): void {
        console.log("_WebAttribute_enableNativeEmbedMode")
    }
    _WebAttribute_onNativeEmbedLifecycleChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onNativeEmbedLifecycleChange")
    }
    _WebAttribute_onNativeEmbedVisibilityChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onNativeEmbedVisibilityChange")
    }
    _WebAttribute_onNativeEmbedGestureEvent(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onNativeEmbedGestureEvent")
    }
    _WebAttribute_copyOptions(ptr: KPointer, value: KInt): void {
        console.log("_WebAttribute_copyOptions")
    }
    _WebAttribute_onOverrideUrlLoading(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onOverrideUrlLoading")
    }
    _WebAttribute_textAutosizing(ptr: KPointer, value: KInt): void {
        console.log("_WebAttribute_textAutosizing")
    }
    _WebAttribute_enableNativeMediaPlayer(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_enableNativeMediaPlayer")
    }
    _WebAttribute_enableSmoothDragResize(ptr: KPointer, value: KInt): void {
        console.log("_WebAttribute_enableSmoothDragResize")
    }
    _WebAttribute_onRenderProcessNotResponding(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onRenderProcessNotResponding")
    }
    _WebAttribute_onRenderProcessResponding(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onRenderProcessResponding")
    }
    _WebAttribute_selectionMenuOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_selectionMenuOptions")
    }
    _WebAttribute_onViewportFitChanged(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onViewportFitChanged")
    }
    _WebAttribute_onInterceptKeyboardAttach(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onInterceptKeyboardAttach")
    }
    _WebAttribute_onAdsBlocked(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebAttribute_onAdsBlocked")
    }
    _WebAttribute_keyboardAvoidMode(ptr: KPointer, value: KInt): void {
        console.log("_WebAttribute_keyboardAvoidMode")
    }
    _WebAttribute_editMenuOptions(ptr: KPointer, value: KPointer): void {
        console.log("_WebAttribute_editMenuOptions")
    }
    _WebAttribute_enableHapticFeedback(ptr: KPointer, value: KInt): void {
        console.log("_WebAttribute_enableHapticFeedback")
    }
    _WebAttribute_registerNativeEmbedRule(ptr: KPointer, tag: KStringPtr, type: KStringPtr): void {
        console.log("_WebAttribute_registerNativeEmbedRule")
    }
    _WebAttribute_bindSelectionMenu(ptr: KPointer, elementType: KInt, thisArray: Uint8Array, thisLength: int32, responseType: KInt): void {
        console.log("_WebAttribute_bindSelectionMenu")
    }
    _WindowScene_construct(id: KInt, flags: KInt): KPointer {
        console.log("_WindowScene_construct")
        return -1
    }
    _WindowSceneInterface_setWindowSceneOptions(ptr: KPointer, persistentId: number): void {
        console.log("_WindowSceneInterface_setWindowSceneOptions")
    }
    _WindowSceneAttribute_attractionEffect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32, fraction: number): void {
        console.log("_WindowSceneAttribute_attractionEffect")
    }
    _XComponent_construct(id: KInt, flags: KInt): KPointer {
        console.log("_XComponent_construct")
        return -1
    }
    _XComponentInterface_setXComponentOptions0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_XComponentInterface_setXComponentOptions0")
    }
    _XComponentInterface_setXComponentOptions1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_XComponentInterface_setXComponentOptions1")
    }
    _XComponentInterface_setXComponentOptions2(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_XComponentInterface_setXComponentOptions2")
    }
    _XComponentAttribute_onLoad(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_XComponentAttribute_onLoad")
    }
    _XComponentAttribute_onDestroy(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_XComponentAttribute_onDestroy")
    }
    _XComponentAttribute_enableAnalyzer(ptr: KPointer, value: KInt): void {
        console.log("_XComponentAttribute_enableAnalyzer")
    }
    _XComponentAttribute_enableSecure(ptr: KPointer, value: KInt): void {
        console.log("_XComponentAttribute_enableSecure")
    }
    _SideBarContainer_construct(id: KInt, flags: KInt): KPointer {
        console.log("_SideBarContainer_construct")
        return -1
    }
    _SideBarContainerInterface_setSideBarContainerOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SideBarContainerInterface_setSideBarContainerOptions")
    }
    _SideBarContainerAttribute_showSideBar(ptr: KPointer, value: KInt): void {
        console.log("_SideBarContainerAttribute_showSideBar")
    }
    _SideBarContainerAttribute_controlButton(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SideBarContainerAttribute_controlButton")
    }
    _SideBarContainerAttribute_showControlButton(ptr: KPointer, value: KInt): void {
        console.log("_SideBarContainerAttribute_showControlButton")
    }
    _SideBarContainerAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SideBarContainerAttribute_onChange")
    }
    _SideBarContainerAttribute_sideBarWidth0(ptr: KPointer, value: number): void {
        console.log("_SideBarContainerAttribute_sideBarWidth0")
    }
    _SideBarContainerAttribute_sideBarWidth1(ptr: KPointer, value: Length): void {
        console.log("_SideBarContainerAttribute_sideBarWidth1")
    }
    _SideBarContainerAttribute_minSideBarWidth0(ptr: KPointer, value: number): void {
        console.log("_SideBarContainerAttribute_minSideBarWidth0")
    }
    _SideBarContainerAttribute_minSideBarWidth1(ptr: KPointer, value: Length): void {
        console.log("_SideBarContainerAttribute_minSideBarWidth1")
    }
    _SideBarContainerAttribute_maxSideBarWidth0(ptr: KPointer, value: number): void {
        console.log("_SideBarContainerAttribute_maxSideBarWidth0")
    }
    _SideBarContainerAttribute_maxSideBarWidth1(ptr: KPointer, value: Length): void {
        console.log("_SideBarContainerAttribute_maxSideBarWidth1")
    }
    _SideBarContainerAttribute_autoHide(ptr: KPointer, value: KInt): void {
        console.log("_SideBarContainerAttribute_autoHide")
    }
    _SideBarContainerAttribute_sideBarPosition(ptr: KPointer, value: KInt): void {
        console.log("_SideBarContainerAttribute_sideBarPosition")
    }
    _SideBarContainerAttribute_divider(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SideBarContainerAttribute_divider")
    }
    _SideBarContainerAttribute_minContentWidth(ptr: KPointer, value: Length): void {
        console.log("_SideBarContainerAttribute_minContentWidth")
    }
    _SideBarContainerAttribute__onChangeEvent_showSideBar(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SideBarContainerAttribute__onChangeEvent_showSideBar")
    }
    _RemoteWindow_construct(id: KInt, flags: KInt): KPointer {
        console.log("_RemoteWindow_construct")
        return -1
    }
    _RemoteWindowInterface_setRemoteWindowOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RemoteWindowInterface_setRemoteWindowOptions")
    }
    _WaterFlow_construct(id: KInt, flags: KInt): KPointer {
        console.log("_WaterFlow_construct")
        return -1
    }
    _WaterFlowInterface_setWaterFlowOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WaterFlowInterface_setWaterFlowOptions")
    }
    _WaterFlowAttribute_columnsTemplate(ptr: KPointer, value: KStringPtr): void {
        console.log("_WaterFlowAttribute_columnsTemplate")
    }
    _WaterFlowAttribute_itemConstraintSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WaterFlowAttribute_itemConstraintSize")
    }
    _WaterFlowAttribute_rowsTemplate(ptr: KPointer, value: KStringPtr): void {
        console.log("_WaterFlowAttribute_rowsTemplate")
    }
    _WaterFlowAttribute_columnsGap(ptr: KPointer, value: Length): void {
        console.log("_WaterFlowAttribute_columnsGap")
    }
    _WaterFlowAttribute_rowsGap(ptr: KPointer, value: Length): void {
        console.log("_WaterFlowAttribute_rowsGap")
    }
    _WaterFlowAttribute_layoutDirection(ptr: KPointer, value: KInt): void {
        console.log("_WaterFlowAttribute_layoutDirection")
    }
    _WaterFlowAttribute_nestedScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WaterFlowAttribute_nestedScroll")
    }
    _WaterFlowAttribute_enableScrollInteraction(ptr: KPointer, value: KInt): void {
        console.log("_WaterFlowAttribute_enableScrollInteraction")
    }
    _WaterFlowAttribute_friction(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WaterFlowAttribute_friction")
    }
    _WaterFlowAttribute_cachedCount0(ptr: KPointer, value: number): void {
        console.log("_WaterFlowAttribute_cachedCount0")
    }
    _WaterFlowAttribute_cachedCount1(ptr: KPointer, count: number, show: KInt): void {
        console.log("_WaterFlowAttribute_cachedCount1")
    }
    _WaterFlowAttribute_onReachStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WaterFlowAttribute_onReachStart")
    }
    _WaterFlowAttribute_onReachEnd(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WaterFlowAttribute_onReachEnd")
    }
    _WaterFlowAttribute_onScrollFrameBegin(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WaterFlowAttribute_onScrollFrameBegin")
    }
    _WaterFlowAttribute_onScrollIndex(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WaterFlowAttribute_onScrollIndex")
    }
    _UIExtensionComponent_construct(id: KInt, flags: KInt): KPointer {
        console.log("_UIExtensionComponent_construct")
        return -1
    }
    _UIExtensionComponentInterface_setUIExtensionComponentOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_UIExtensionComponentInterface_setUIExtensionComponentOptions")
    }
    _UIExtensionComponentAttribute_onRemoteReady(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_UIExtensionComponentAttribute_onRemoteReady")
    }
    _UIExtensionComponentAttribute_onReceive(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_UIExtensionComponentAttribute_onReceive")
    }
    _UIExtensionComponentAttribute_onResult(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_UIExtensionComponentAttribute_onResult")
    }
    _UIExtensionComponentAttribute_onRelease(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_UIExtensionComponentAttribute_onRelease")
    }
    _UIExtensionComponentAttribute_onError(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_UIExtensionComponentAttribute_onError")
    }
    _UIExtensionComponentAttribute_onTerminated(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_UIExtensionComponentAttribute_onTerminated")
    }
    _LinearIndicator_construct(id: KInt, flags: KInt): KPointer {
        console.log("_LinearIndicator_construct")
        return -1
    }
    _LinearIndicatorInterface_setLinearIndicatorOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_LinearIndicatorInterface_setLinearIndicatorOptions")
    }
    _LinearIndicatorAttribute_indicatorStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_LinearIndicatorAttribute_indicatorStyle")
    }
    _LinearIndicatorAttribute_indicatorLoop(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_LinearIndicatorAttribute_indicatorLoop")
    }
    _LinearIndicatorAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_LinearIndicatorAttribute_onChange")
    }
    _AnimationExtender_SetClipRect(node: KPointer, x: KFloat, y: KFloat, width: KFloat, height: KFloat): void {
        console.log("_AnimationExtender_SetClipRect")
    }
    _AnimationExtender_OpenImplicitAnimation(thisArray: Uint8Array, thisLength: int32): void {
        console.log("_AnimationExtender_OpenImplicitAnimation")
    }
    _AnimationExtender_CloseImplicitAnimation(): void {
        console.log("_AnimationExtender_CloseImplicitAnimation")
    }
    _AnimationExtender_StartDoubleAnimation(node: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_AnimationExtender_StartDoubleAnimation")
    }
    _AnimationExtender_AnimationTranslate(node: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_AnimationExtender_AnimationTranslate")
    }
    _UnifiedData_ctor(): KPointer {
        console.log("_UnifiedData_ctor")
        return -1
    }
    _UnifiedData_getFinalizer(): KPointer {
        console.log("_UnifiedData_getFinalizer")
        return -1
    }
    _UnifiedData_hasType(ptr: KPointer, UnifiedData_type: KStringPtr): boolean {
        console.log("_UnifiedData_hasType")
        return false
    }
    _UnifiedData_getTypes(ptr: KPointer): KInteropReturnBuffer {
        console.log("_UnifiedData_getTypes")
        return new Uint8Array()
    }
    _LazyForEachOps_NeedMoreElements(node: KPointer, mark: KPointer, direction: KInt): KPointer {
        console.log("_LazyForEachOps_NeedMoreElements")
        return -1
    }
    _LazyForEachOps_OnRangeUpdate(node: KPointer, totalCount: KInt, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_LazyForEachOps_OnRangeUpdate")
    }
    _LazyForEachOps_SetCurrentIndex(node: KPointer, index: KInt): void {
        console.log("_LazyForEachOps_SetCurrentIndex")
    }
    _LazyForEachOps_Prepare(node: KPointer, itemCount: KInt, offset: KInt): void {
        console.log("_LazyForEachOps_Prepare")
    }
    _LazyForEachOps_NotifyChange(node: KPointer, startIndex: KInt, endIndex: KInt, count: KInt): void {
        console.log("_LazyForEachOps_NotifyChange")
    }
    _SystemOps_StartFrame(): KPointer {
        console.log("_SystemOps_StartFrame")
        return -1
    }
    _SystemOps_EndFrame(root: KPointer): void {
        console.log("_SystemOps_EndFrame")
    }
    _SystemOps_syncInstanceId(instanceId: KInt): void {
        console.log("_SystemOps_syncInstanceId")
    }
    _SystemOps_restoreInstanceId(): void {
        console.log("_SystemOps_restoreInstanceId")
    }
    _DrawingCanvas_ctor(pixelmap: KPointer): KPointer {
        console.log("_DrawingCanvas_ctor")
        return -1
    }
    _DrawingCanvas_getFinalizer(): KPointer {
        console.log("_DrawingCanvas_getFinalizer")
        return -1
    }
    _DrawingCanvas_drawRect(ptr: KPointer, left: number, top: number, right: number, bottom: number): void {
        console.log("_DrawingCanvas_drawRect")
    }
    _LengthMetrics_ctor(): KPointer {
        console.log("_LengthMetrics_ctor")
        return -1
    }
    _LengthMetrics_getFinalizer(): KPointer {
        console.log("_LengthMetrics_getFinalizer")
        return -1
    }
    _LengthMetrics_px(value: number): KPointer {
        console.log("_LengthMetrics_px")
        return -1
    }
    _LengthMetrics_vp(value: number): KPointer {
        console.log("_LengthMetrics_vp")
        return -1
    }
    _LengthMetrics_fp(value: number): KPointer {
        console.log("_LengthMetrics_fp")
        return -1
    }
    _LengthMetrics_percent(value: number): KPointer {
        console.log("_LengthMetrics_percent")
        return -1
    }
    _LengthMetrics_lpx(value: number): KPointer {
        console.log("_LengthMetrics_lpx")
        return -1
    }
    _LengthMetrics_resource(thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_LengthMetrics_resource")
        return -1
    }
    _LengthMetrics_getUnit(ptr: KPointer): KPointer {
        console.log("_LengthMetrics_getUnit")
        return -1
    }
    _LengthMetrics_setUnit(ptr: KPointer, unit: KInt): void {
        console.log("_LengthMetrics_setUnit")
    }
    _LengthMetrics_getValue(ptr: KPointer): number {
        console.log("_LengthMetrics_getValue")
        return 1
    }
    _LengthMetrics_setValue(ptr: KPointer, value: number): void {
        console.log("_LengthMetrics_setValue")
    }
    _ColorMetrics_ctor(): KPointer {
        console.log("_ColorMetrics_ctor")
        return -1
    }
    _ColorMetrics_getFinalizer(): KPointer {
        console.log("_ColorMetrics_getFinalizer")
        return -1
    }
    _ColorMetrics_numeric(value: number): KPointer {
        console.log("_ColorMetrics_numeric")
        return -1
    }
    _ColorMetrics_rgba(red: number, green: number, blue: number, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_ColorMetrics_rgba")
        return -1
    }
    _ColorMetrics_resourceColor(thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_ColorMetrics_resourceColor")
        return -1
    }
    _ColorMetrics_blendColor(ptr: KPointer, overlayColor: KPointer): KPointer {
        console.log("_ColorMetrics_blendColor")
        return -1
    }
    _ColorMetrics_getColor(ptr: KPointer): string {
        console.log("_ColorMetrics_getColor")
        return ""
    }
    _ColorMetrics_getRed(ptr: KPointer): number {
        console.log("_ColorMetrics_getRed")
        return 1
    }
    _ColorMetrics_getGreen(ptr: KPointer): number {
        console.log("_ColorMetrics_getGreen")
        return 1
    }
    _ColorMetrics_getBlue(ptr: KPointer): number {
        console.log("_ColorMetrics_getBlue")
        return 1
    }
    _ColorMetrics_getAlpha(ptr: KPointer): number {
        console.log("_ColorMetrics_getAlpha")
        return 1
    }
    _WebviewController_ctor(): KPointer {
        console.log("_WebviewController_ctor")
        return -1
    }
    _WebviewController_getFinalizer(): KPointer {
        console.log("_WebviewController_getFinalizer")
        return -1
    }
    _WebviewController_initializeWebEngine(): void {
        console.log("_WebviewController_initializeWebEngine")
    }
    _WebviewController_loadUrl(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebviewController_loadUrl")
    }
    _GlobalScope_ohos_arkui_componentSnapshot_get(id: KStringPtr, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_GlobalScope_ohos_arkui_componentSnapshot_get")
    }
    _GlobalScope_ohos_arkui_performanceMonitor_begin(scene: KStringPtr, startInputType: KInt, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_GlobalScope_ohos_arkui_performanceMonitor_begin")
    }
    _GlobalScope_ohos_arkui_performanceMonitor_end(scene: KStringPtr): void {
        console.log("_GlobalScope_ohos_arkui_performanceMonitor_end")
    }
    _GlobalScope_ohos_arkui_performanceMonitor_recordInputEventTime(actionType: KInt, sourceType: KInt, time: number): void {
        console.log("_GlobalScope_ohos_arkui_performanceMonitor_recordInputEventTime")
    }
    _CommonShape_ctor(): KPointer {
        console.log("_CommonShape_ctor")
        return -1
    }
    _CommonShape_getFinalizer(): KPointer {
        console.log("_CommonShape_getFinalizer")
        return -1
    }
    _CommonShape_offset(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_CommonShape_offset")
        return -1
    }
    _CommonShape_fill(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_CommonShape_fill")
        return -1
    }
    _CommonShape_position(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_CommonShape_position")
        return -1
    }
    _BaseShape_ctor(): KPointer {
        console.log("_BaseShape_ctor")
        return -1
    }
    _BaseShape_getFinalizer(): KPointer {
        console.log("_BaseShape_getFinalizer")
        return -1
    }
    _BaseShape_width(ptr: KPointer, width: Length): KPointer {
        console.log("_BaseShape_width")
        return -1
    }
    _BaseShape_height(ptr: KPointer, height: Length): KPointer {
        console.log("_BaseShape_height")
        return -1
    }
    _BaseShape_size(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_BaseShape_size")
        return -1
    }
    _RectShape_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_RectShape_ctor")
        return -1
    }
    _RectShape_getFinalizer(): KPointer {
        console.log("_RectShape_getFinalizer")
        return -1
    }
    _RectShape_offset(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_RectShape_offset")
        return -1
    }
    _RectShape_fill(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_RectShape_fill")
        return -1
    }
    _RectShape_position(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_RectShape_position")
        return -1
    }
    _RectShape_width(ptr: KPointer, width: Length): KPointer {
        console.log("_RectShape_width")
        return -1
    }
    _RectShape_height(ptr: KPointer, height: Length): KPointer {
        console.log("_RectShape_height")
        return -1
    }
    _RectShape_size(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_RectShape_size")
        return -1
    }
    _RectShape_radiusWidth(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_RectShape_radiusWidth")
        return -1
    }
    _RectShape_radiusHeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_RectShape_radiusHeight")
        return -1
    }
    _RectShape_radius(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_RectShape_radius")
        return -1
    }
    _CircleShape_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_CircleShape_ctor")
        return -1
    }
    _CircleShape_getFinalizer(): KPointer {
        console.log("_CircleShape_getFinalizer")
        return -1
    }
    _CircleShape_offset(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_CircleShape_offset")
        return -1
    }
    _CircleShape_fill(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_CircleShape_fill")
        return -1
    }
    _CircleShape_position(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_CircleShape_position")
        return -1
    }
    _CircleShape_width(ptr: KPointer, width: Length): KPointer {
        console.log("_CircleShape_width")
        return -1
    }
    _CircleShape_height(ptr: KPointer, height: Length): KPointer {
        console.log("_CircleShape_height")
        return -1
    }
    _CircleShape_size(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_CircleShape_size")
        return -1
    }
    _EllipseShape_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_EllipseShape_ctor")
        return -1
    }
    _EllipseShape_getFinalizer(): KPointer {
        console.log("_EllipseShape_getFinalizer")
        return -1
    }
    _EllipseShape_offset(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_EllipseShape_offset")
        return -1
    }
    _EllipseShape_fill(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_EllipseShape_fill")
        return -1
    }
    _EllipseShape_position(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_EllipseShape_position")
        return -1
    }
    _EllipseShape_width(ptr: KPointer, width: Length): KPointer {
        console.log("_EllipseShape_width")
        return -1
    }
    _EllipseShape_height(ptr: KPointer, height: Length): KPointer {
        console.log("_EllipseShape_height")
        return -1
    }
    _EllipseShape_size(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_EllipseShape_size")
        return -1
    }
    _PathShape_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_PathShape_ctor")
        return -1
    }
    _PathShape_getFinalizer(): KPointer {
        console.log("_PathShape_getFinalizer")
        return -1
    }
    _PathShape_offset(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_PathShape_offset")
        return -1
    }
    _PathShape_fill(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_PathShape_fill")
        return -1
    }
    _PathShape_position(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_PathShape_position")
        return -1
    }
    _PathShape_commands(ptr: KPointer, commands: KStringPtr): KPointer {
        console.log("_PathShape_commands")
        return -1
    }
    _GlobalScope_ohos_font_registerFont(thisArray: Uint8Array, thisLength: int32): void {
        console.log("_GlobalScope_ohos_font_registerFont")
    }
    _GlobalScope_ohos_font_getSystemFontList(): KInteropReturnBuffer {
        console.log("_GlobalScope_ohos_font_getSystemFontList")
        return new Uint8Array()
    }
    _ScaleSymbolEffect_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_ScaleSymbolEffect_ctor")
        return -1
    }
    _ScaleSymbolEffect_getFinalizer(): KPointer {
        console.log("_ScaleSymbolEffect_getFinalizer")
        return -1
    }
    _ScaleSymbolEffect_getScope(ptr: KPointer): KPointer {
        console.log("_ScaleSymbolEffect_getScope")
        return -1
    }
    _ScaleSymbolEffect_setScope(ptr: KPointer, scope: KInt): void {
        console.log("_ScaleSymbolEffect_setScope")
    }
    _ScaleSymbolEffect_getDirection(ptr: KPointer): KPointer {
        console.log("_ScaleSymbolEffect_getDirection")
        return -1
    }
    _ScaleSymbolEffect_setDirection(ptr: KPointer, direction: KInt): void {
        console.log("_ScaleSymbolEffect_setDirection")
    }
    _ReplaceSymbolEffect_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_ReplaceSymbolEffect_ctor")
        return -1
    }
    _ReplaceSymbolEffect_getFinalizer(): KPointer {
        console.log("_ReplaceSymbolEffect_getFinalizer")
        return -1
    }
    _ReplaceSymbolEffect_getScope(ptr: KPointer): KPointer {
        console.log("_ReplaceSymbolEffect_getScope")
        return -1
    }
    _ReplaceSymbolEffect_setScope(ptr: KPointer, scope: KInt): void {
        console.log("_ReplaceSymbolEffect_setScope")
    }
    _FrameNode_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_FrameNode_ctor")
        return -1
    }
    _FrameNode_getFinalizer(): KPointer {
        console.log("_FrameNode_getFinalizer")
        return -1
    }
    _FrameNode_isModifiable(ptr: KPointer): boolean {
        console.log("_FrameNode_isModifiable")
        return false
    }
    _FrameNode_appendChild(ptr: KPointer, node: KPointer): void {
        console.log("_FrameNode_appendChild")
    }
    _FrameNode_insertChildAfter(ptr: KPointer, child: KPointer, sibling: KPointer): void {
        console.log("_FrameNode_insertChildAfter")
    }
    _FrameNode_removeChild(ptr: KPointer, node: KPointer): void {
        console.log("_FrameNode_removeChild")
    }
    _FrameNode_clearChildren(ptr: KPointer): void {
        console.log("_FrameNode_clearChildren")
    }
    _FrameNode_getChild(ptr: KPointer, index: number): KPointer {
        console.log("_FrameNode_getChild")
        return -1
    }
    _FrameNode_getFirstChild(ptr: KPointer): KPointer {
        console.log("_FrameNode_getFirstChild")
        return -1
    }
    _FrameNode_getNextSibling(ptr: KPointer): KPointer {
        console.log("_FrameNode_getNextSibling")
        return -1
    }
    _FrameNode_getPreviousSibling(ptr: KPointer): KPointer {
        console.log("_FrameNode_getPreviousSibling")
        return -1
    }
    _FrameNode_getParent(ptr: KPointer): KPointer {
        console.log("_FrameNode_getParent")
        return -1
    }
    _FrameNode_getChildrenCount(ptr: KPointer): int32 {
        console.log("_FrameNode_getChildrenCount")
        return 0
    }
    _FrameNode_dispose(ptr: KPointer): void {
        console.log("_FrameNode_dispose")
    }
    _FrameNode_getOpacity(ptr: KPointer): number {
        console.log("_FrameNode_getOpacity")
        return 1
    }
    _FrameNode_getPositionToWindowWithTransform(ptr: KPointer): KInteropReturnBuffer {
        console.log("_FrameNode_getPositionToWindowWithTransform")
        return new Uint8Array()
    }
    _FrameNode_getFrameNodeByKey(name: KStringPtr): KPointer {
        console.log("_FrameNode_getFrameNodeByKey")
        return -1
    }
    _PixelMap_ctor(): KPointer {
        console.log("_PixelMap_ctor")
        return -1
    }
    _PixelMap_getFinalizer(): KPointer {
        console.log("_PixelMap_getFinalizer")
        return -1
    }
    _PixelMap_readPixelsToBufferSync(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_PixelMap_readPixelsToBufferSync")
    }
    _PixelMap_writeBufferToPixels(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_PixelMap_writeBufferToPixels")
    }
    _PixelMap_getIsEditable(ptr: KPointer): boolean {
        console.log("_PixelMap_getIsEditable")
        return false
    }
    _PixelMap_getIsStrideAlignment(ptr: KPointer): boolean {
        console.log("_PixelMap_getIsStrideAlignment")
        return false
    }
    _NavExtender_setUpdateStackCallback(peer: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_NavExtender_setUpdateStackCallback")
    }
    _NavExtender_syncStack(peer: KPointer): void {
        console.log("_NavExtender_syncStack")
    }
    _NavExtender_checkNeedCreate(navigation: KPointer, index: int32): boolean {
        console.log("_NavExtender_checkNeedCreate")
        return false
    }
    _NavExtender_navigationCreate(peer: KInt, flag: KInt): KPointer {
        console.log("_NavExtender_navigationCreate")
        return -1
    }
    _NavExtender_setNavigationOptions(navigation: KPointer, stack: KPointer): void {
        console.log("_NavExtender_setNavigationOptions")
    }
    _NavExtender_setNavDestinationNode(peer: KPointer, index: KInt, node: KPointer): void {
        console.log("_NavExtender_setNavDestinationNode")
    }
    _EventEmulator_emitClickEvent(node: KPointer, event: KPointer): void {
        console.log("_EventEmulator_emitClickEvent")
    }
    _EventEmulator_emitTextInputEvent(node: KPointer, text: KStringPtr): void {
        console.log("_EventEmulator_emitTextInputEvent")
    }
    _ActionSheet_show(thisArray: Uint8Array, thisLength: int32): undefined {
        console.log("_ActionSheet_show")
        return undefined
    }
    _AlertDialog_show(thisArray: Uint8Array, thisLength: int32): undefined {
        console.log("_AlertDialog_show")
        return undefined
    }
    _SpringProp_ctor(mass: number, stiffness: number, damping: number): KPointer {
        console.log("_SpringProp_ctor")
        return -1
    }
    _SpringProp_getFinalizer(): KPointer {
        console.log("_SpringProp_getFinalizer")
        return -1
    }
    _SpringMotion_ctor(start: number, end: number, velocity: number, prop: KPointer): KPointer {
        console.log("_SpringMotion_ctor")
        return -1
    }
    _SpringMotion_getFinalizer(): KPointer {
        console.log("_SpringMotion_getFinalizer")
        return -1
    }
    _FrictionMotion_ctor(friction: number, position: number, velocity: number): KPointer {
        console.log("_FrictionMotion_ctor")
        return -1
    }
    _FrictionMotion_getFinalizer(): KPointer {
        console.log("_FrictionMotion_getFinalizer")
        return -1
    }
    _ScrollMotion_ctor(position: number, velocity: number, min: number, max: number, prop: KPointer): KPointer {
        console.log("_ScrollMotion_ctor")
        return -1
    }
    _ScrollMotion_getFinalizer(): KPointer {
        console.log("_ScrollMotion_getFinalizer")
        return -1
    }
    _CalendarController_ctor(): KPointer {
        console.log("_CalendarController_ctor")
        return -1
    }
    _CalendarController_getFinalizer(): KPointer {
        console.log("_CalendarController_getFinalizer")
        return -1
    }
    _CalendarController_backToToday(ptr: KPointer): undefined {
        console.log("_CalendarController_backToToday")
        return undefined
    }
    _CalendarController_goTo(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): undefined {
        console.log("_CalendarController_goTo")
        return undefined
    }
    _CalendarPickerDialog_show(thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CalendarPickerDialog_show")
    }
    _CanvasGradient_ctor(): KPointer {
        console.log("_CanvasGradient_ctor")
        return -1
    }
    _CanvasGradient_getFinalizer(): KPointer {
        console.log("_CanvasGradient_getFinalizer")
        return -1
    }
    _CanvasGradient_addColorStop(ptr: KPointer, offset: number, color: KStringPtr): void {
        console.log("_CanvasGradient_addColorStop")
    }
    _CanvasPath_ctor(): KPointer {
        console.log("_CanvasPath_ctor")
        return -1
    }
    _CanvasPath_getFinalizer(): KPointer {
        console.log("_CanvasPath_getFinalizer")
        return -1
    }
    _CanvasPath_arc(ptr: KPointer, x: number, y: number, radius: number, startAngle: number, endAngle: number, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CanvasPath_arc")
    }
    _CanvasPath_arcTo(ptr: KPointer, x1: number, y1: number, x2: number, y2: number, radius: number): void {
        console.log("_CanvasPath_arcTo")
    }
    _CanvasPath_bezierCurveTo(ptr: KPointer, cp1x: number, cp1y: number, cp2x: number, cp2y: number, x: number, y: number): void {
        console.log("_CanvasPath_bezierCurveTo")
    }
    _CanvasPath_closePath(ptr: KPointer): void {
        console.log("_CanvasPath_closePath")
    }
    _CanvasPath_ellipse(ptr: KPointer, x: number, y: number, radiusX: number, radiusY: number, rotation: number, startAngle: number, endAngle: number, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CanvasPath_ellipse")
    }
    _CanvasPath_lineTo(ptr: KPointer, x: number, y: number): void {
        console.log("_CanvasPath_lineTo")
    }
    _CanvasPath_moveTo(ptr: KPointer, x: number, y: number): void {
        console.log("_CanvasPath_moveTo")
    }
    _CanvasPath_quadraticCurveTo(ptr: KPointer, cpx: number, cpy: number, x: number, y: number): void {
        console.log("_CanvasPath_quadraticCurveTo")
    }
    _CanvasPath_rect(ptr: KPointer, x: number, y: number, w: number, h: number): void {
        console.log("_CanvasPath_rect")
    }
    _Path2D_ctor(): KPointer {
        console.log("_Path2D_ctor")
        return -1
    }
    _Path2D_getFinalizer(): KPointer {
        console.log("_Path2D_getFinalizer")
        return -1
    }
    _Path2D_addPath(ptr: KPointer, path: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_Path2D_addPath")
    }
    _CanvasPattern_ctor(): KPointer {
        console.log("_CanvasPattern_ctor")
        return -1
    }
    _CanvasPattern_getFinalizer(): KPointer {
        console.log("_CanvasPattern_getFinalizer")
        return -1
    }
    _CanvasPattern_setTransform(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CanvasPattern_setTransform")
    }
    _ImageBitmap_ctor(src: KStringPtr): KPointer {
        console.log("_ImageBitmap_ctor")
        return -1
    }
    _ImageBitmap_getFinalizer(): KPointer {
        console.log("_ImageBitmap_getFinalizer")
        return -1
    }
    _ImageBitmap_close(ptr: KPointer): void {
        console.log("_ImageBitmap_close")
    }
    _ImageBitmap_getHeight(ptr: KPointer): number {
        console.log("_ImageBitmap_getHeight")
        return 1
    }
    _ImageBitmap_getWidth(ptr: KPointer): number {
        console.log("_ImageBitmap_getWidth")
        return 1
    }
    _ImageData_ctor(width: number, height: number, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_ImageData_ctor")
        return -1
    }
    _ImageData_getFinalizer(): KPointer {
        console.log("_ImageData_getFinalizer")
        return -1
    }
    _ImageData_getHeight(ptr: KPointer): number {
        console.log("_ImageData_getHeight")
        return 1
    }
    _ImageData_getWidth(ptr: KPointer): number {
        console.log("_ImageData_getWidth")
        return 1
    }
    _RenderingContextSettings_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_RenderingContextSettings_ctor")
        return -1
    }
    _RenderingContextSettings_getFinalizer(): KPointer {
        console.log("_RenderingContextSettings_getFinalizer")
        return -1
    }
    _RenderingContextSettings_getAntialias(ptr: KPointer): boolean {
        console.log("_RenderingContextSettings_getAntialias")
        return false
    }
    _RenderingContextSettings_setAntialias(ptr: KPointer, antialias: KInt): void {
        console.log("_RenderingContextSettings_setAntialias")
    }
    _CanvasRenderer_ctor(): KPointer {
        console.log("_CanvasRenderer_ctor")
        return -1
    }
    _CanvasRenderer_getFinalizer(): KPointer {
        console.log("_CanvasRenderer_getFinalizer")
        return -1
    }
    _CanvasRenderer_drawImage0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32, dx: number, dy: number): void {
        console.log("_CanvasRenderer_drawImage0")
    }
    _CanvasRenderer_drawImage1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32, dx: number, dy: number, dw: number, dh: number): void {
        console.log("_CanvasRenderer_drawImage1")
    }
    _CanvasRenderer_drawImage2(ptr: KPointer, thisArray: Uint8Array, thisLength: int32, sx: number, sy: number, sw: number, sh: number, dx: number, dy: number, dw: number, dh: number): void {
        console.log("_CanvasRenderer_drawImage2")
    }
    _CanvasRenderer_beginPath(ptr: KPointer): void {
        console.log("_CanvasRenderer_beginPath")
    }
    _CanvasRenderer_clip0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CanvasRenderer_clip0")
    }
    _CanvasRenderer_clip1(ptr: KPointer, path: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CanvasRenderer_clip1")
    }
    _CanvasRenderer_fill0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CanvasRenderer_fill0")
    }
    _CanvasRenderer_fill1(ptr: KPointer, path: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CanvasRenderer_fill1")
    }
    _CanvasRenderer_stroke0(ptr: KPointer): void {
        console.log("_CanvasRenderer_stroke0")
    }
    _CanvasRenderer_stroke1(ptr: KPointer, path: KPointer): void {
        console.log("_CanvasRenderer_stroke1")
    }
    _CanvasRenderer_createLinearGradient(ptr: KPointer, x0: number, y0: number, x1: number, y1: number): KPointer {
        console.log("_CanvasRenderer_createLinearGradient")
        return -1
    }
    _CanvasRenderer_createPattern(ptr: KPointer, image: KPointer, thisArray: Uint8Array, thisLength: int32): KInteropReturnBuffer {
        console.log("_CanvasRenderer_createPattern")
        return -1
    }
    _CanvasRenderer_createRadialGradient(ptr: KPointer, x0: number, y0: number, r0: number, x1: number, y1: number, r1: number): KPointer {
        console.log("_CanvasRenderer_createRadialGradient")
        return -1
    }
    _CanvasRenderer_createConicGradient(ptr: KPointer, startAngle: number, x: number, y: number): KPointer {
        console.log("_CanvasRenderer_createConicGradient")
        return -1
    }
    _CanvasRenderer_createImageData0(ptr: KPointer, sw: number, sh: number): KPointer {
        console.log("_CanvasRenderer_createImageData0")
        return -1
    }
    _CanvasRenderer_createImageData1(ptr: KPointer, imagedata: KPointer): KPointer {
        console.log("_CanvasRenderer_createImageData1")
        return -1
    }
    _CanvasRenderer_getImageData(ptr: KPointer, sx: number, sy: number, sw: number, sh: number): KPointer {
        console.log("_CanvasRenderer_getImageData")
        return -1
    }
    _CanvasRenderer_getPixelMap(ptr: KPointer, sx: number, sy: number, sw: number, sh: number): KPointer {
        console.log("_CanvasRenderer_getPixelMap")
        return -1
    }
    _CanvasRenderer_putImageData0(ptr: KPointer, imagedata: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CanvasRenderer_putImageData0")
    }
    _CanvasRenderer_putImageData1(ptr: KPointer, imagedata: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CanvasRenderer_putImageData1")
    }
    _CanvasRenderer_getLineDash(ptr: KPointer): KInteropReturnBuffer {
        console.log("_CanvasRenderer_getLineDash")
        return new Uint8Array()
    }
    _CanvasRenderer_setLineDash(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CanvasRenderer_setLineDash")
    }
    _CanvasRenderer_clearRect(ptr: KPointer, x: number, y: number, w: number, h: number): void {
        console.log("_CanvasRenderer_clearRect")
    }
    _CanvasRenderer_fillRect(ptr: KPointer, x: number, y: number, w: number, h: number): void {
        console.log("_CanvasRenderer_fillRect")
    }
    _CanvasRenderer_strokeRect(ptr: KPointer, x: number, y: number, w: number, h: number): void {
        console.log("_CanvasRenderer_strokeRect")
    }
    _CanvasRenderer_restore(ptr: KPointer): void {
        console.log("_CanvasRenderer_restore")
    }
    _CanvasRenderer_save(ptr: KPointer): void {
        console.log("_CanvasRenderer_save")
    }
    _CanvasRenderer_fillText(ptr: KPointer, text: KStringPtr, x: number, y: number, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CanvasRenderer_fillText")
    }
    _CanvasRenderer_measureText(ptr: KPointer, text: KStringPtr): KInteropReturnBuffer {
        console.log("_CanvasRenderer_measureText")
        return new Uint8Array()
    }
    _CanvasRenderer_strokeText(ptr: KPointer, text: KStringPtr, x: number, y: number, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CanvasRenderer_strokeText")
    }
    _CanvasRenderer_getTransform(ptr: KPointer): KPointer {
        console.log("_CanvasRenderer_getTransform")
        return -1
    }
    _CanvasRenderer_resetTransform(ptr: KPointer): void {
        console.log("_CanvasRenderer_resetTransform")
    }
    _CanvasRenderer_rotate(ptr: KPointer, angle: number): void {
        console.log("_CanvasRenderer_rotate")
    }
    _CanvasRenderer_scale(ptr: KPointer, x: number, y: number): void {
        console.log("_CanvasRenderer_scale")
    }
    _CanvasRenderer_setTransform0(ptr: KPointer, a: number, b: number, c: number, d: number, e: number, f: number): void {
        console.log("_CanvasRenderer_setTransform0")
    }
    _CanvasRenderer_setTransform1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CanvasRenderer_setTransform1")
    }
    _CanvasRenderer_transform(ptr: KPointer, a: number, b: number, c: number, d: number, e: number, f: number): void {
        console.log("_CanvasRenderer_transform")
    }
    _CanvasRenderer_translate(ptr: KPointer, x: number, y: number): void {
        console.log("_CanvasRenderer_translate")
    }
    _CanvasRenderer_setPixelMap(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CanvasRenderer_setPixelMap")
    }
    _CanvasRenderer_transferFromImageBitmap(ptr: KPointer, bitmap: KPointer): void {
        console.log("_CanvasRenderer_transferFromImageBitmap")
    }
    _CanvasRenderer_saveLayer(ptr: KPointer): void {
        console.log("_CanvasRenderer_saveLayer")
    }
    _CanvasRenderer_restoreLayer(ptr: KPointer): void {
        console.log("_CanvasRenderer_restoreLayer")
    }
    _CanvasRenderer_reset(ptr: KPointer): void {
        console.log("_CanvasRenderer_reset")
    }
    _CanvasRenderer_getGlobalAlpha(ptr: KPointer): number {
        console.log("_CanvasRenderer_getGlobalAlpha")
        return 1
    }
    _CanvasRenderer_setGlobalAlpha(ptr: KPointer, globalAlpha: number): void {
        console.log("_CanvasRenderer_setGlobalAlpha")
    }
    _CanvasRenderer_getGlobalCompositeOperation(ptr: KPointer): string {
        console.log("_CanvasRenderer_getGlobalCompositeOperation")
        return ""
    }
    _CanvasRenderer_setGlobalCompositeOperation(ptr: KPointer, globalCompositeOperation: KStringPtr): void {
        console.log("_CanvasRenderer_setGlobalCompositeOperation")
    }
    _CanvasRenderer_setFillStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CanvasRenderer_setFillStyle")
    }
    _CanvasRenderer_setStrokeStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CanvasRenderer_setStrokeStyle")
    }
    _CanvasRenderer_getFilter(ptr: KPointer): string {
        console.log("_CanvasRenderer_getFilter")
        return ""
    }
    _CanvasRenderer_setFilter(ptr: KPointer, filter: KStringPtr): void {
        console.log("_CanvasRenderer_setFilter")
    }
    _CanvasRenderer_getImageSmoothingEnabled(ptr: KPointer): boolean {
        console.log("_CanvasRenderer_getImageSmoothingEnabled")
        return false
    }
    _CanvasRenderer_setImageSmoothingEnabled(ptr: KPointer, imageSmoothingEnabled: KInt): void {
        console.log("_CanvasRenderer_setImageSmoothingEnabled")
    }
    _CanvasRenderer_getImageSmoothingQuality(ptr: KPointer): KPointer {
        console.log("_CanvasRenderer_getImageSmoothingQuality")
        return -1
    }
    _CanvasRenderer_setImageSmoothingQuality(ptr: KPointer, imageSmoothingQuality: KStringPtr): void {
        console.log("_CanvasRenderer_setImageSmoothingQuality")
    }
    _CanvasRenderer_getLineCap(ptr: KPointer): KPointer {
        console.log("_CanvasRenderer_getLineCap")
        return -1
    }
    _CanvasRenderer_setLineCap(ptr: KPointer, lineCap: KStringPtr): void {
        console.log("_CanvasRenderer_setLineCap")
    }
    _CanvasRenderer_getLineDashOffset(ptr: KPointer): number {
        console.log("_CanvasRenderer_getLineDashOffset")
        return 1
    }
    _CanvasRenderer_setLineDashOffset(ptr: KPointer, lineDashOffset: number): void {
        console.log("_CanvasRenderer_setLineDashOffset")
    }
    _CanvasRenderer_getLineJoin(ptr: KPointer): KPointer {
        console.log("_CanvasRenderer_getLineJoin")
        return -1
    }
    _CanvasRenderer_setLineJoin(ptr: KPointer, lineJoin: KStringPtr): void {
        console.log("_CanvasRenderer_setLineJoin")
    }
    _CanvasRenderer_getLineWidth(ptr: KPointer): number {
        console.log("_CanvasRenderer_getLineWidth")
        return 1
    }
    _CanvasRenderer_setLineWidth(ptr: KPointer, lineWidth: number): void {
        console.log("_CanvasRenderer_setLineWidth")
    }
    _CanvasRenderer_getMiterLimit(ptr: KPointer): number {
        console.log("_CanvasRenderer_getMiterLimit")
        return 1
    }
    _CanvasRenderer_setMiterLimit(ptr: KPointer, miterLimit: number): void {
        console.log("_CanvasRenderer_setMiterLimit")
    }
    _CanvasRenderer_getShadowBlur(ptr: KPointer): number {
        console.log("_CanvasRenderer_getShadowBlur")
        return 1
    }
    _CanvasRenderer_setShadowBlur(ptr: KPointer, shadowBlur: number): void {
        console.log("_CanvasRenderer_setShadowBlur")
    }
    _CanvasRenderer_getShadowColor(ptr: KPointer): string {
        console.log("_CanvasRenderer_getShadowColor")
        return ""
    }
    _CanvasRenderer_setShadowColor(ptr: KPointer, shadowColor: KStringPtr): void {
        console.log("_CanvasRenderer_setShadowColor")
    }
    _CanvasRenderer_getShadowOffsetX(ptr: KPointer): number {
        console.log("_CanvasRenderer_getShadowOffsetX")
        return 1
    }
    _CanvasRenderer_setShadowOffsetX(ptr: KPointer, shadowOffsetX: number): void {
        console.log("_CanvasRenderer_setShadowOffsetX")
    }
    _CanvasRenderer_getShadowOffsetY(ptr: KPointer): number {
        console.log("_CanvasRenderer_getShadowOffsetY")
        return 1
    }
    _CanvasRenderer_setShadowOffsetY(ptr: KPointer, shadowOffsetY: number): void {
        console.log("_CanvasRenderer_setShadowOffsetY")
    }
    _CanvasRenderer_getDirection(ptr: KPointer): KPointer {
        console.log("_CanvasRenderer_getDirection")
        return -1
    }
    _CanvasRenderer_setDirection(ptr: KPointer, direction: KStringPtr): void {
        console.log("_CanvasRenderer_setDirection")
    }
    _CanvasRenderer_getFont(ptr: KPointer): string {
        console.log("_CanvasRenderer_getFont")
        return ""
    }
    _CanvasRenderer_setFont(ptr: KPointer, font: KStringPtr): void {
        console.log("_CanvasRenderer_setFont")
    }
    _CanvasRenderer_getTextAlign(ptr: KPointer): KPointer {
        console.log("_CanvasRenderer_getTextAlign")
        return -1
    }
    _CanvasRenderer_setTextAlign(ptr: KPointer, textAlign: KStringPtr): void {
        console.log("_CanvasRenderer_setTextAlign")
    }
    _CanvasRenderer_getTextBaseline(ptr: KPointer): KPointer {
        console.log("_CanvasRenderer_getTextBaseline")
        return -1
    }
    _CanvasRenderer_setTextBaseline(ptr: KPointer, textBaseline: KStringPtr): void {
        console.log("_CanvasRenderer_setTextBaseline")
    }
    _CanvasRenderingContext2D_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_CanvasRenderingContext2D_ctor")
        return -1
    }
    _CanvasRenderingContext2D_getFinalizer(): KPointer {
        console.log("_CanvasRenderingContext2D_getFinalizer")
        return -1
    }
    _CanvasRenderingContext2D_toDataURL(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): string {
        console.log("_CanvasRenderingContext2D_toDataURL")
        return ""
    }
    _CanvasRenderingContext2D_startImageAnalyzer(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_CanvasRenderingContext2D_startImageAnalyzer")
        return -1
    }
    _CanvasRenderingContext2D_stopImageAnalyzer(ptr: KPointer): void {
        console.log("_CanvasRenderingContext2D_stopImageAnalyzer")
    }
    _CanvasRenderingContext2D_onOnAttach(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CanvasRenderingContext2D_onOnAttach")
    }
    _CanvasRenderingContext2D_offOnAttach(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CanvasRenderingContext2D_offOnAttach")
    }
    _CanvasRenderingContext2D_onOnDetach(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CanvasRenderingContext2D_onOnDetach")
    }
    _CanvasRenderingContext2D_offOnDetach(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CanvasRenderingContext2D_offOnDetach")
    }
    _CanvasRenderingContext2D_getHeight(ptr: KPointer): number {
        console.log("_CanvasRenderingContext2D_getHeight")
        return 1
    }
    _CanvasRenderingContext2D_getWidth(ptr: KPointer): number {
        console.log("_CanvasRenderingContext2D_getWidth")
        return 1
    }
    _CanvasRenderingContext2D_getCanvas(ptr: KPointer): KPointer {
        console.log("_CanvasRenderingContext2D_getCanvas")
        return -1
    }
    _OffscreenCanvasRenderingContext2D_ctor(width: number, height: number, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_OffscreenCanvasRenderingContext2D_ctor")
        return -1
    }
    _OffscreenCanvasRenderingContext2D_getFinalizer(): KPointer {
        console.log("_OffscreenCanvasRenderingContext2D_getFinalizer")
        return -1
    }
    _OffscreenCanvasRenderingContext2D_toDataURL(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): string {
        console.log("_OffscreenCanvasRenderingContext2D_toDataURL")
        return ""
    }
    _OffscreenCanvasRenderingContext2D_transferToImageBitmap(ptr: KPointer): KPointer {
        console.log("_OffscreenCanvasRenderingContext2D_transferToImageBitmap")
        return -1
    }
    _OffscreenCanvas_ctor(width: number, height: number): KPointer {
        console.log("_OffscreenCanvas_ctor")
        return -1
    }
    _OffscreenCanvas_getFinalizer(): KPointer {
        console.log("_OffscreenCanvas_getFinalizer")
        return -1
    }
    _OffscreenCanvas_transferToImageBitmap(ptr: KPointer): KPointer {
        console.log("_OffscreenCanvas_transferToImageBitmap")
        return -1
    }
    _OffscreenCanvas_getContext2d(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_OffscreenCanvas_getContext2d")
        return -1
    }
    _OffscreenCanvas_getHeight(ptr: KPointer): number {
        console.log("_OffscreenCanvas_getHeight")
        return 1
    }
    _OffscreenCanvas_setHeight(ptr: KPointer, height: number): void {
        console.log("_OffscreenCanvas_setHeight")
    }
    _OffscreenCanvas_getWidth(ptr: KPointer): number {
        console.log("_OffscreenCanvas_getWidth")
        return 1
    }
    _OffscreenCanvas_setWidth(ptr: KPointer, width: number): void {
        console.log("_OffscreenCanvas_setWidth")
    }
    _DrawingRenderingContext_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_DrawingRenderingContext_ctor")
        return -1
    }
    _DrawingRenderingContext_getFinalizer(): KPointer {
        console.log("_DrawingRenderingContext_getFinalizer")
        return -1
    }
    _DrawingRenderingContext_invalidate(ptr: KPointer): void {
        console.log("_DrawingRenderingContext_invalidate")
    }
    _DrawingRenderingContext_getCanvas(ptr: KPointer): KPointer {
        console.log("_DrawingRenderingContext_getCanvas")
        return -1
    }
    _ICurve_ctor(): KPointer {
        console.log("_ICurve_ctor")
        return -1
    }
    _ICurve_getFinalizer(): KPointer {
        console.log("_ICurve_getFinalizer")
        return -1
    }
    _ICurve_interpolate(ptr: KPointer, fraction: number): number {
        console.log("_ICurve_interpolate")
        return 1
    }
    _DrawModifier_ctor(): KPointer {
        console.log("_DrawModifier_ctor")
        return -1
    }
    _DrawModifier_getFinalizer(): KPointer {
        console.log("_DrawModifier_getFinalizer")
        return -1
    }
    _DrawModifier_drawBehind(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_DrawModifier_drawBehind")
    }
    _DrawModifier_drawContent(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_DrawModifier_drawContent")
    }
    _DrawModifier_drawFront(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_DrawModifier_drawFront")
    }
    _DrawModifier_invalidate(ptr: KPointer): void {
        console.log("_DrawModifier_invalidate")
    }
    _TransitionEffect_ctor(type: KStringPtr, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_TransitionEffect_ctor")
        return -1
    }
    _TransitionEffect_getFinalizer(): KPointer {
        console.log("_TransitionEffect_getFinalizer")
        return -1
    }
    _TransitionEffect_translate(thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_TransitionEffect_translate")
        return -1
    }
    _TransitionEffect_rotate(thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_TransitionEffect_rotate")
        return -1
    }
    _TransitionEffect_scale(thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_TransitionEffect_scale")
        return -1
    }
    _TransitionEffect_opacity(alpha: number): KPointer {
        console.log("_TransitionEffect_opacity")
        return -1
    }
    _TransitionEffect_move(edge: KInt): KPointer {
        console.log("_TransitionEffect_move")
        return -1
    }
    _TransitionEffect_asymmetric(appear: KPointer, disappear: KPointer): KPointer {
        console.log("_TransitionEffect_asymmetric")
        return -1
    }
    _TransitionEffect_animation(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_TransitionEffect_animation")
        return -1
    }
    _TransitionEffect_combine(ptr: KPointer, transitionEffect: KPointer): KPointer {
        console.log("_TransitionEffect_combine")
        return -1
    }
    _TransitionEffect_getIDENTITY(): KPointer {
        console.log("_TransitionEffect_getIDENTITY")
        return -1
    }
    _TransitionEffect_getOPACITY(): KPointer {
        console.log("_TransitionEffect_getOPACITY")
        return -1
    }
    _TransitionEffect_getSLIDE(): KPointer {
        console.log("_TransitionEffect_getSLIDE")
        return -1
    }
    _TransitionEffect_getSLIDE_SWITCH(): KPointer {
        console.log("_TransitionEffect_getSLIDE_SWITCH")
        return -1
    }
    _BaseEvent_ctor(): KPointer {
        console.log("_BaseEvent_ctor")
        return -1
    }
    _BaseEvent_getFinalizer(): KPointer {
        console.log("_BaseEvent_getFinalizer")
        return -1
    }
    _BaseEvent_getModifierKeyState(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): boolean {
        console.log("_BaseEvent_getModifierKeyState")
        return false
    }
    _BaseEvent_setTarget(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_BaseEvent_setTarget")
    }
    _BaseEvent_getTimestamp(ptr: KPointer): number {
        console.log("_BaseEvent_getTimestamp")
        return 1
    }
    _BaseEvent_setTimestamp(ptr: KPointer, timestamp: number): void {
        console.log("_BaseEvent_setTimestamp")
    }
    _BaseEvent_getSource(ptr: KPointer): KPointer {
        console.log("_BaseEvent_getSource")
        return -1
    }
    _BaseEvent_setSource(ptr: KPointer, source: KInt): void {
        console.log("_BaseEvent_setSource")
    }
    _BaseEvent_getAxisHorizontal(ptr: KPointer): number {
        console.log("_BaseEvent_getAxisHorizontal")
        return 1
    }
    _BaseEvent_setAxisHorizontal(ptr: KPointer, axisHorizontal: number): void {
        console.log("_BaseEvent_setAxisHorizontal")
    }
    _BaseEvent_getAxisVertical(ptr: KPointer): number {
        console.log("_BaseEvent_getAxisVertical")
        return 1
    }
    _BaseEvent_setAxisVertical(ptr: KPointer, axisVertical: number): void {
        console.log("_BaseEvent_setAxisVertical")
    }
    _BaseEvent_getPressure(ptr: KPointer): number {
        console.log("_BaseEvent_getPressure")
        return 1
    }
    _BaseEvent_setPressure(ptr: KPointer, pressure: number): void {
        console.log("_BaseEvent_setPressure")
    }
    _BaseEvent_getTiltX(ptr: KPointer): number {
        console.log("_BaseEvent_getTiltX")
        return 1
    }
    _BaseEvent_setTiltX(ptr: KPointer, tiltX: number): void {
        console.log("_BaseEvent_setTiltX")
    }
    _BaseEvent_getTiltY(ptr: KPointer): number {
        console.log("_BaseEvent_getTiltY")
        return 1
    }
    _BaseEvent_setTiltY(ptr: KPointer, tiltY: number): void {
        console.log("_BaseEvent_setTiltY")
    }
    _BaseEvent_getSourceTool(ptr: KPointer): KPointer {
        console.log("_BaseEvent_getSourceTool")
        return -1
    }
    _BaseEvent_setSourceTool(ptr: KPointer, sourceTool: KInt): void {
        console.log("_BaseEvent_setSourceTool")
    }
    _BaseEvent_getDeviceId(ptr: KPointer): number {
        console.log("_BaseEvent_getDeviceId")
        return 1
    }
    _BaseEvent_setDeviceId(ptr: KPointer, deviceId: number): void {
        console.log("_BaseEvent_setDeviceId")
    }
    _ClickEvent_ctor(): KPointer {
        console.log("_ClickEvent_ctor")
        return -1
    }
    _ClickEvent_getFinalizer(): KPointer {
        console.log("_ClickEvent_getFinalizer")
        return -1
    }
    _ClickEvent_getDisplayX(ptr: KPointer): number {
        console.log("_ClickEvent_getDisplayX")
        return 1
    }
    _ClickEvent_setDisplayX(ptr: KPointer, displayX: number): void {
        console.log("_ClickEvent_setDisplayX")
    }
    _ClickEvent_getDisplayY(ptr: KPointer): number {
        console.log("_ClickEvent_getDisplayY")
        return 1
    }
    _ClickEvent_setDisplayY(ptr: KPointer, displayY: number): void {
        console.log("_ClickEvent_setDisplayY")
    }
    _ClickEvent_getWindowX(ptr: KPointer): number {
        console.log("_ClickEvent_getWindowX")
        return 1
    }
    _ClickEvent_setWindowX(ptr: KPointer, windowX: number): void {
        console.log("_ClickEvent_setWindowX")
    }
    _ClickEvent_getWindowY(ptr: KPointer): number {
        console.log("_ClickEvent_getWindowY")
        return 1
    }
    _ClickEvent_setWindowY(ptr: KPointer, windowY: number): void {
        console.log("_ClickEvent_setWindowY")
    }
    _ClickEvent_getScreenX(ptr: KPointer): number {
        console.log("_ClickEvent_getScreenX")
        return 1
    }
    _ClickEvent_setScreenX(ptr: KPointer, screenX: number): void {
        console.log("_ClickEvent_setScreenX")
    }
    _ClickEvent_getScreenY(ptr: KPointer): number {
        console.log("_ClickEvent_getScreenY")
        return 1
    }
    _ClickEvent_setScreenY(ptr: KPointer, screenY: number): void {
        console.log("_ClickEvent_setScreenY")
    }
    _ClickEvent_getX(ptr: KPointer): number {
        console.log("_ClickEvent_getX")
        return 1
    }
    _ClickEvent_setX(ptr: KPointer, x: number): void {
        console.log("_ClickEvent_setX")
    }
    _ClickEvent_getY(ptr: KPointer): number {
        console.log("_ClickEvent_getY")
        return 1
    }
    _ClickEvent_setY(ptr: KPointer, y: number): void {
        console.log("_ClickEvent_setY")
    }
    _ClickEvent_getPreventDefault(ptr: KPointer): KPointer {
        console.log("_ClickEvent_getPreventDefault")
        return -1
    }
    _ClickEvent_setPreventDefault(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ClickEvent_setPreventDefault")
    }
    _HoverEvent_ctor(): KPointer {
        console.log("_HoverEvent_ctor")
        return -1
    }
    _HoverEvent_getFinalizer(): KPointer {
        console.log("_HoverEvent_getFinalizer")
        return -1
    }
    _HoverEvent_getStopPropagation(ptr: KPointer): KPointer {
        console.log("_HoverEvent_getStopPropagation")
        return -1
    }
    _HoverEvent_setStopPropagation(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_HoverEvent_setStopPropagation")
    }
    _MouseEvent_ctor(): KPointer {
        console.log("_MouseEvent_ctor")
        return -1
    }
    _MouseEvent_getFinalizer(): KPointer {
        console.log("_MouseEvent_getFinalizer")
        return -1
    }
    _MouseEvent_getButton(ptr: KPointer): KPointer {
        console.log("_MouseEvent_getButton")
        return -1
    }
    _MouseEvent_setButton(ptr: KPointer, button: KInt): void {
        console.log("_MouseEvent_setButton")
    }
    _MouseEvent_getAction(ptr: KPointer): KPointer {
        console.log("_MouseEvent_getAction")
        return -1
    }
    _MouseEvent_setAction(ptr: KPointer, action: KInt): void {
        console.log("_MouseEvent_setAction")
    }
    _MouseEvent_getDisplayX(ptr: KPointer): number {
        console.log("_MouseEvent_getDisplayX")
        return 1
    }
    _MouseEvent_setDisplayX(ptr: KPointer, displayX: number): void {
        console.log("_MouseEvent_setDisplayX")
    }
    _MouseEvent_getDisplayY(ptr: KPointer): number {
        console.log("_MouseEvent_getDisplayY")
        return 1
    }
    _MouseEvent_setDisplayY(ptr: KPointer, displayY: number): void {
        console.log("_MouseEvent_setDisplayY")
    }
    _MouseEvent_getWindowX(ptr: KPointer): number {
        console.log("_MouseEvent_getWindowX")
        return 1
    }
    _MouseEvent_setWindowX(ptr: KPointer, windowX: number): void {
        console.log("_MouseEvent_setWindowX")
    }
    _MouseEvent_getWindowY(ptr: KPointer): number {
        console.log("_MouseEvent_getWindowY")
        return 1
    }
    _MouseEvent_setWindowY(ptr: KPointer, windowY: number): void {
        console.log("_MouseEvent_setWindowY")
    }
    _MouseEvent_getScreenX(ptr: KPointer): number {
        console.log("_MouseEvent_getScreenX")
        return 1
    }
    _MouseEvent_setScreenX(ptr: KPointer, screenX: number): void {
        console.log("_MouseEvent_setScreenX")
    }
    _MouseEvent_getScreenY(ptr: KPointer): number {
        console.log("_MouseEvent_getScreenY")
        return 1
    }
    _MouseEvent_setScreenY(ptr: KPointer, screenY: number): void {
        console.log("_MouseEvent_setScreenY")
    }
    _MouseEvent_getX(ptr: KPointer): number {
        console.log("_MouseEvent_getX")
        return 1
    }
    _MouseEvent_setX(ptr: KPointer, x: number): void {
        console.log("_MouseEvent_setX")
    }
    _MouseEvent_getY(ptr: KPointer): number {
        console.log("_MouseEvent_getY")
        return 1
    }
    _MouseEvent_setY(ptr: KPointer, y: number): void {
        console.log("_MouseEvent_setY")
    }
    _MouseEvent_getStopPropagation(ptr: KPointer): KPointer {
        console.log("_MouseEvent_getStopPropagation")
        return -1
    }
    _MouseEvent_setStopPropagation(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_MouseEvent_setStopPropagation")
    }
    _AccessibilityHoverEvent_ctor(): KPointer {
        console.log("_AccessibilityHoverEvent_ctor")
        return -1
    }
    _AccessibilityHoverEvent_getFinalizer(): KPointer {
        console.log("_AccessibilityHoverEvent_getFinalizer")
        return -1
    }
    _AccessibilityHoverEvent_getType(ptr: KPointer): KPointer {
        console.log("_AccessibilityHoverEvent_getType")
        return -1
    }
    _AccessibilityHoverEvent_setType(ptr: KPointer, type: KInt): void {
        console.log("_AccessibilityHoverEvent_setType")
    }
    _AccessibilityHoverEvent_getX(ptr: KPointer): number {
        console.log("_AccessibilityHoverEvent_getX")
        return 1
    }
    _AccessibilityHoverEvent_setX(ptr: KPointer, x: number): void {
        console.log("_AccessibilityHoverEvent_setX")
    }
    _AccessibilityHoverEvent_getY(ptr: KPointer): number {
        console.log("_AccessibilityHoverEvent_getY")
        return 1
    }
    _AccessibilityHoverEvent_setY(ptr: KPointer, y: number): void {
        console.log("_AccessibilityHoverEvent_setY")
    }
    _AccessibilityHoverEvent_getDisplayX(ptr: KPointer): number {
        console.log("_AccessibilityHoverEvent_getDisplayX")
        return 1
    }
    _AccessibilityHoverEvent_setDisplayX(ptr: KPointer, displayX: number): void {
        console.log("_AccessibilityHoverEvent_setDisplayX")
    }
    _AccessibilityHoverEvent_getDisplayY(ptr: KPointer): number {
        console.log("_AccessibilityHoverEvent_getDisplayY")
        return 1
    }
    _AccessibilityHoverEvent_setDisplayY(ptr: KPointer, displayY: number): void {
        console.log("_AccessibilityHoverEvent_setDisplayY")
    }
    _AccessibilityHoverEvent_getWindowX(ptr: KPointer): number {
        console.log("_AccessibilityHoverEvent_getWindowX")
        return 1
    }
    _AccessibilityHoverEvent_setWindowX(ptr: KPointer, windowX: number): void {
        console.log("_AccessibilityHoverEvent_setWindowX")
    }
    _AccessibilityHoverEvent_getWindowY(ptr: KPointer): number {
        console.log("_AccessibilityHoverEvent_getWindowY")
        return 1
    }
    _AccessibilityHoverEvent_setWindowY(ptr: KPointer, windowY: number): void {
        console.log("_AccessibilityHoverEvent_setWindowY")
    }
    _TouchEvent_ctor(): KPointer {
        console.log("_TouchEvent_ctor")
        return -1
    }
    _TouchEvent_getFinalizer(): KPointer {
        console.log("_TouchEvent_getFinalizer")
        return -1
    }
    _TouchEvent_getHistoricalPoints(ptr: KPointer): KInteropReturnBuffer {
        console.log("_TouchEvent_getHistoricalPoints")
        return new Uint8Array()
    }
    _TouchEvent_getType(ptr: KPointer): KPointer {
        console.log("_TouchEvent_getType")
        return -1
    }
    _TouchEvent_setType(ptr: KPointer, type: KInt): void {
        console.log("_TouchEvent_setType")
    }
    _TouchEvent_getTouches(ptr: KPointer): KInteropReturnBuffer {
        console.log("_TouchEvent_getTouches")
        return new Uint8Array()
    }
    _TouchEvent_setTouches(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TouchEvent_setTouches")
    }
    _TouchEvent_getChangedTouches(ptr: KPointer): KInteropReturnBuffer {
        console.log("_TouchEvent_getChangedTouches")
        return new Uint8Array()
    }
    _TouchEvent_setChangedTouches(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TouchEvent_setChangedTouches")
    }
    _TouchEvent_getStopPropagation(ptr: KPointer): KPointer {
        console.log("_TouchEvent_getStopPropagation")
        return -1
    }
    _TouchEvent_setStopPropagation(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TouchEvent_setStopPropagation")
    }
    _TouchEvent_getPreventDefault(ptr: KPointer): KPointer {
        console.log("_TouchEvent_getPreventDefault")
        return -1
    }
    _TouchEvent_setPreventDefault(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TouchEvent_setPreventDefault")
    }
    _PixelMapMock_ctor(): KPointer {
        console.log("_PixelMapMock_ctor")
        return -1
    }
    _PixelMapMock_getFinalizer(): KPointer {
        console.log("_PixelMapMock_getFinalizer")
        return -1
    }
    _PixelMapMock_release(ptr: KPointer): void {
        console.log("_PixelMapMock_release")
    }
    _DragEvent_ctor(): KPointer {
        console.log("_DragEvent_ctor")
        return -1
    }
    _DragEvent_getFinalizer(): KPointer {
        console.log("_DragEvent_getFinalizer")
        return -1
    }
    _DragEvent_getDisplayX(ptr: KPointer): number {
        console.log("_DragEvent_getDisplayX")
        return 1
    }
    _DragEvent_getDisplayY(ptr: KPointer): number {
        console.log("_DragEvent_getDisplayY")
        return 1
    }
    _DragEvent_getWindowX(ptr: KPointer): number {
        console.log("_DragEvent_getWindowX")
        return 1
    }
    _DragEvent_getWindowY(ptr: KPointer): number {
        console.log("_DragEvent_getWindowY")
        return 1
    }
    _DragEvent_getX(ptr: KPointer): number {
        console.log("_DragEvent_getX")
        return 1
    }
    _DragEvent_getY(ptr: KPointer): number {
        console.log("_DragEvent_getY")
        return 1
    }
    _DragEvent_setData(ptr: KPointer, unifiedData: KPointer): void {
        console.log("_DragEvent_setData")
    }
    _DragEvent_getData(ptr: KPointer): KPointer {
        console.log("_DragEvent_getData")
        return -1
    }
    _DragEvent_getSummary(ptr: KPointer): KInteropReturnBuffer {
        console.log("_DragEvent_getSummary")
        return new Uint8Array()
    }
    _DragEvent_setResult(ptr: KPointer, dragResult: KInt): void {
        console.log("_DragEvent_setResult")
    }
    _DragEvent_getResult(ptr: KPointer): KPointer {
        console.log("_DragEvent_getResult")
        return -1
    }
    _DragEvent_getPreviewRect(ptr: KPointer): KInteropReturnBuffer {
        console.log("_DragEvent_getPreviewRect")
        return new Uint8Array()
    }
    _DragEvent_getVelocityX(ptr: KPointer): number {
        console.log("_DragEvent_getVelocityX")
        return 1
    }
    _DragEvent_getVelocityY(ptr: KPointer): number {
        console.log("_DragEvent_getVelocityY")
        return 1
    }
    _DragEvent_getVelocity(ptr: KPointer): number {
        console.log("_DragEvent_getVelocity")
        return 1
    }
    _DragEvent_getModifierKeyState(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): boolean {
        console.log("_DragEvent_getModifierKeyState")
        return false
    }
    _DragEvent_getDragBehavior(ptr: KPointer): KPointer {
        console.log("_DragEvent_getDragBehavior")
        return -1
    }
    _DragEvent_setDragBehavior(ptr: KPointer, dragBehavior: KInt): void {
        console.log("_DragEvent_setDragBehavior")
    }
    _DragEvent_getUseCustomDropAnimation(ptr: KPointer): boolean {
        console.log("_DragEvent_getUseCustomDropAnimation")
        return false
    }
    _DragEvent_setUseCustomDropAnimation(ptr: KPointer, useCustomDropAnimation: KInt): void {
        console.log("_DragEvent_setUseCustomDropAnimation")
    }
    _KeyEvent_ctor(): KPointer {
        console.log("_KeyEvent_ctor")
        return -1
    }
    _KeyEvent_getFinalizer(): KPointer {
        console.log("_KeyEvent_getFinalizer")
        return -1
    }
    _KeyEvent_getModifierKeyState(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): boolean {
        console.log("_KeyEvent_getModifierKeyState")
        return false
    }
    _KeyEvent_getType(ptr: KPointer): KPointer {
        console.log("_KeyEvent_getType")
        return -1
    }
    _KeyEvent_setType(ptr: KPointer, type: KInt): void {
        console.log("_KeyEvent_setType")
    }
    _KeyEvent_getKeyCode(ptr: KPointer): number {
        console.log("_KeyEvent_getKeyCode")
        return 1
    }
    _KeyEvent_setKeyCode(ptr: KPointer, keyCode: number): void {
        console.log("_KeyEvent_setKeyCode")
    }
    _KeyEvent_getKeyText(ptr: KPointer): string {
        console.log("_KeyEvent_getKeyText")
        return ""
    }
    _KeyEvent_setKeyText(ptr: KPointer, keyText: KStringPtr): void {
        console.log("_KeyEvent_setKeyText")
    }
    _KeyEvent_getKeySource(ptr: KPointer): KPointer {
        console.log("_KeyEvent_getKeySource")
        return -1
    }
    _KeyEvent_setKeySource(ptr: KPointer, keySource: KInt): void {
        console.log("_KeyEvent_setKeySource")
    }
    _KeyEvent_getDeviceId(ptr: KPointer): number {
        console.log("_KeyEvent_getDeviceId")
        return 1
    }
    _KeyEvent_setDeviceId(ptr: KPointer, deviceId: number): void {
        console.log("_KeyEvent_setDeviceId")
    }
    _KeyEvent_getMetaKey(ptr: KPointer): number {
        console.log("_KeyEvent_getMetaKey")
        return 1
    }
    _KeyEvent_setMetaKey(ptr: KPointer, metaKey: number): void {
        console.log("_KeyEvent_setMetaKey")
    }
    _KeyEvent_getTimestamp(ptr: KPointer): number {
        console.log("_KeyEvent_getTimestamp")
        return 1
    }
    _KeyEvent_setTimestamp(ptr: KPointer, timestamp: number): void {
        console.log("_KeyEvent_setTimestamp")
    }
    _KeyEvent_getStopPropagation(ptr: KPointer): KPointer {
        console.log("_KeyEvent_getStopPropagation")
        return -1
    }
    _KeyEvent_setStopPropagation(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_KeyEvent_setStopPropagation")
    }
    _KeyEvent_setIntentionCode(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_KeyEvent_setIntentionCode")
    }
    _KeyEvent_getUnicode(ptr: KPointer): number {
        console.log("_KeyEvent_getUnicode")
        return 1
    }
    _KeyEvent_setUnicode(ptr: KPointer, unicode: number): void {
        console.log("_KeyEvent_setUnicode")
    }
    _ProgressMask_ctor(value: number, total: number, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_ProgressMask_ctor")
        return -1
    }
    _ProgressMask_getFinalizer(): KPointer {
        console.log("_ProgressMask_getFinalizer")
        return -1
    }
    _ProgressMask_updateProgress(ptr: KPointer, value: number): void {
        console.log("_ProgressMask_updateProgress")
    }
    _ProgressMask_updateColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ProgressMask_updateColor")
    }
    _ProgressMask_enableBreathingAnimation(ptr: KPointer, value: KInt): void {
        console.log("_ProgressMask_enableBreathingAnimation")
    }
    _Measurable_ctor(): KPointer {
        console.log("_Measurable_ctor")
        return -1
    }
    _Measurable_getFinalizer(): KPointer {
        console.log("_Measurable_getFinalizer")
        return -1
    }
    _Measurable_measure(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KInteropReturnBuffer {
        console.log("_Measurable_measure")
        return new Uint8Array()
    }
    _Measurable_getMargin(ptr: KPointer): KInteropReturnBuffer {
        console.log("_Measurable_getMargin")
        return new Uint8Array()
    }
    _Measurable_getPadding(ptr: KPointer): KInteropReturnBuffer {
        console.log("_Measurable_getPadding")
        return new Uint8Array()
    }
    _Measurable_getBorderWidth(ptr: KPointer): KInteropReturnBuffer {
        console.log("_Measurable_getBorderWidth")
        return new Uint8Array()
    }
    _View_ctor(): KPointer {
        console.log("_View_ctor")
        return -1
    }
    _View_getFinalizer(): KPointer {
        console.log("_View_getFinalizer")
        return -1
    }
    _View_create(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): any {
        console.log("_View_create")
        return ""
    }
    _TextContentControllerBase_ctor(): KPointer {
        console.log("_TextContentControllerBase_ctor")
        return -1
    }
    _TextContentControllerBase_getFinalizer(): KPointer {
        console.log("_TextContentControllerBase_getFinalizer")
        return -1
    }
    _TextContentControllerBase_getCaretOffset(ptr: KPointer): KInteropReturnBuffer {
        console.log("_TextContentControllerBase_getCaretOffset")
        return new Uint8Array()
    }
    _TextContentControllerBase_getTextContentRect(ptr: KPointer): KInteropReturnBuffer {
        console.log("_TextContentControllerBase_getTextContentRect")
        return new Uint8Array()
    }
    _TextContentControllerBase_getTextContentLineCount(ptr: KPointer): number {
        console.log("_TextContentControllerBase_getTextContentLineCount")
        return 1
    }
    _ChildrenMainSize_ctor(childDefaultSize: number): KPointer {
        console.log("_ChildrenMainSize_ctor")
        return -1
    }
    _ChildrenMainSize_getFinalizer(): KPointer {
        console.log("_ChildrenMainSize_getFinalizer")
        return -1
    }
    _ChildrenMainSize_splice(ptr: KPointer, start: number, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ChildrenMainSize_splice")
    }
    _ChildrenMainSize_update(ptr: KPointer, index: number, childSize: number): void {
        console.log("_ChildrenMainSize_update")
    }
    _ChildrenMainSize_getChildDefaultSize(ptr: KPointer): number {
        console.log("_ChildrenMainSize_getChildDefaultSize")
        return 1
    }
    _ChildrenMainSize_setChildDefaultSize(ptr: KPointer, childDefaultSize: number): void {
        console.log("_ChildrenMainSize_setChildDefaultSize")
    }
    _UICommonEvent_ctor(): KPointer {
        console.log("_UICommonEvent_ctor")
        return -1
    }
    _UICommonEvent_getFinalizer(): KPointer {
        console.log("_UICommonEvent_getFinalizer")
        return -1
    }
    _UICommonEvent_setOnClick(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_UICommonEvent_setOnClick")
    }
    _UICommonEvent_setOnTouch(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_UICommonEvent_setOnTouch")
    }
    _UICommonEvent_setOnAppear(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_UICommonEvent_setOnAppear")
    }
    _UICommonEvent_setOnDisappear(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_UICommonEvent_setOnDisappear")
    }
    _UICommonEvent_setOnKeyEvent(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_UICommonEvent_setOnKeyEvent")
    }
    _UICommonEvent_setOnFocus(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_UICommonEvent_setOnFocus")
    }
    _UICommonEvent_setOnBlur(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_UICommonEvent_setOnBlur")
    }
    _UICommonEvent_setOnHover(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_UICommonEvent_setOnHover")
    }
    _UICommonEvent_setOnMouse(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_UICommonEvent_setOnMouse")
    }
    _UICommonEvent_setOnSizeChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_UICommonEvent_setOnSizeChange")
    }
    _UICommonEvent_setOnVisibleAreaApproximateChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_UICommonEvent_setOnVisibleAreaApproximateChange")
    }
    _GestureModifier_ctor(): KPointer {
        console.log("_GestureModifier_ctor")
        return -1
    }
    _GestureModifier_getFinalizer(): KPointer {
        console.log("_GestureModifier_getFinalizer")
        return -1
    }
    _GestureModifier_applyGesture(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_GestureModifier_applyGesture")
    }
    _ContextMenu_close(): undefined {
        console.log("_ContextMenu_close")
        return undefined
    }
    _CustomDialogController_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_CustomDialogController_ctor")
        return -1
    }
    _CustomDialogController_getFinalizer(): KPointer {
        console.log("_CustomDialogController_getFinalizer")
        return -1
    }
    _CustomDialogController_open(ptr: KPointer): undefined {
        console.log("_CustomDialogController_open")
        return undefined
    }
    _CustomDialogController_close(ptr: KPointer): undefined {
        console.log("_CustomDialogController_close")
        return undefined
    }
    _LinearGradient_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_LinearGradient_ctor")
        return -1
    }
    _LinearGradient_getFinalizer(): KPointer {
        console.log("_LinearGradient_getFinalizer")
        return -1
    }
    _DatePickerDialog_show(thisArray: Uint8Array, thisLength: int32): undefined {
        console.log("_DatePickerDialog_show")
        return undefined
    }
    _BaseGestureEvent_ctor(): KPointer {
        console.log("_BaseGestureEvent_ctor")
        return -1
    }
    _BaseGestureEvent_getFinalizer(): KPointer {
        console.log("_BaseGestureEvent_getFinalizer")
        return -1
    }
    _BaseGestureEvent_getFingerList(ptr: KPointer): KInteropReturnBuffer {
        console.log("_BaseGestureEvent_getFingerList")
        return new Uint8Array()
    }
    _BaseGestureEvent_setFingerList(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_BaseGestureEvent_setFingerList")
    }
    _TapGestureEvent_ctor(): KPointer {
        console.log("_TapGestureEvent_ctor")
        return -1
    }
    _TapGestureEvent_getFinalizer(): KPointer {
        console.log("_TapGestureEvent_getFinalizer")
        return -1
    }
    _LongPressGestureEvent_ctor(): KPointer {
        console.log("_LongPressGestureEvent_ctor")
        return -1
    }
    _LongPressGestureEvent_getFinalizer(): KPointer {
        console.log("_LongPressGestureEvent_getFinalizer")
        return -1
    }
    _LongPressGestureEvent_getRepeat(ptr: KPointer): boolean {
        console.log("_LongPressGestureEvent_getRepeat")
        return false
    }
    _LongPressGestureEvent_setRepeat(ptr: KPointer, repeat: KInt): void {
        console.log("_LongPressGestureEvent_setRepeat")
    }
    _PanGestureEvent_ctor(): KPointer {
        console.log("_PanGestureEvent_ctor")
        return -1
    }
    _PanGestureEvent_getFinalizer(): KPointer {
        console.log("_PanGestureEvent_getFinalizer")
        return -1
    }
    _PanGestureEvent_getOffsetX(ptr: KPointer): number {
        console.log("_PanGestureEvent_getOffsetX")
        return 1
    }
    _PanGestureEvent_setOffsetX(ptr: KPointer, offsetX: number): void {
        console.log("_PanGestureEvent_setOffsetX")
    }
    _PanGestureEvent_getOffsetY(ptr: KPointer): number {
        console.log("_PanGestureEvent_getOffsetY")
        return 1
    }
    _PanGestureEvent_setOffsetY(ptr: KPointer, offsetY: number): void {
        console.log("_PanGestureEvent_setOffsetY")
    }
    _PanGestureEvent_getVelocityX(ptr: KPointer): number {
        console.log("_PanGestureEvent_getVelocityX")
        return 1
    }
    _PanGestureEvent_setVelocityX(ptr: KPointer, velocityX: number): void {
        console.log("_PanGestureEvent_setVelocityX")
    }
    _PanGestureEvent_getVelocityY(ptr: KPointer): number {
        console.log("_PanGestureEvent_getVelocityY")
        return 1
    }
    _PanGestureEvent_setVelocityY(ptr: KPointer, velocityY: number): void {
        console.log("_PanGestureEvent_setVelocityY")
    }
    _PanGestureEvent_getVelocity(ptr: KPointer): number {
        console.log("_PanGestureEvent_getVelocity")
        return 1
    }
    _PanGestureEvent_setVelocity(ptr: KPointer, velocity: number): void {
        console.log("_PanGestureEvent_setVelocity")
    }
    _PinchGestureEvent_ctor(): KPointer {
        console.log("_PinchGestureEvent_ctor")
        return -1
    }
    _PinchGestureEvent_getFinalizer(): KPointer {
        console.log("_PinchGestureEvent_getFinalizer")
        return -1
    }
    _PinchGestureEvent_getScale(ptr: KPointer): number {
        console.log("_PinchGestureEvent_getScale")
        return 1
    }
    _PinchGestureEvent_setScale(ptr: KPointer, scale: number): void {
        console.log("_PinchGestureEvent_setScale")
    }
    _PinchGestureEvent_getPinchCenterX(ptr: KPointer): number {
        console.log("_PinchGestureEvent_getPinchCenterX")
        return 1
    }
    _PinchGestureEvent_setPinchCenterX(ptr: KPointer, pinchCenterX: number): void {
        console.log("_PinchGestureEvent_setPinchCenterX")
    }
    _PinchGestureEvent_getPinchCenterY(ptr: KPointer): number {
        console.log("_PinchGestureEvent_getPinchCenterY")
        return 1
    }
    _PinchGestureEvent_setPinchCenterY(ptr: KPointer, pinchCenterY: number): void {
        console.log("_PinchGestureEvent_setPinchCenterY")
    }
    _RotationGestureEvent_ctor(): KPointer {
        console.log("_RotationGestureEvent_ctor")
        return -1
    }
    _RotationGestureEvent_getFinalizer(): KPointer {
        console.log("_RotationGestureEvent_getFinalizer")
        return -1
    }
    _RotationGestureEvent_getAngle(ptr: KPointer): number {
        console.log("_RotationGestureEvent_getAngle")
        return 1
    }
    _RotationGestureEvent_setAngle(ptr: KPointer, angle: number): void {
        console.log("_RotationGestureEvent_setAngle")
    }
    _SwipeGestureEvent_ctor(): KPointer {
        console.log("_SwipeGestureEvent_ctor")
        return -1
    }
    _SwipeGestureEvent_getFinalizer(): KPointer {
        console.log("_SwipeGestureEvent_getFinalizer")
        return -1
    }
    _SwipeGestureEvent_getAngle(ptr: KPointer): number {
        console.log("_SwipeGestureEvent_getAngle")
        return 1
    }
    _SwipeGestureEvent_setAngle(ptr: KPointer, angle: number): void {
        console.log("_SwipeGestureEvent_setAngle")
    }
    _SwipeGestureEvent_getSpeed(ptr: KPointer): number {
        console.log("_SwipeGestureEvent_getSpeed")
        return 1
    }
    _SwipeGestureEvent_setSpeed(ptr: KPointer, speed: number): void {
        console.log("_SwipeGestureEvent_setSpeed")
    }
    _GestureEvent_ctor(): KPointer {
        console.log("_GestureEvent_ctor")
        return -1
    }
    _GestureEvent_getFinalizer(): KPointer {
        console.log("_GestureEvent_getFinalizer")
        return -1
    }
    _GestureEvent_getRepeat(ptr: KPointer): boolean {
        console.log("_GestureEvent_getRepeat")
        return false
    }
    _GestureEvent_setRepeat(ptr: KPointer, repeat: KInt): void {
        console.log("_GestureEvent_setRepeat")
    }
    _GestureEvent_getFingerList(ptr: KPointer): KInteropReturnBuffer {
        console.log("_GestureEvent_getFingerList")
        return new Uint8Array()
    }
    _GestureEvent_setFingerList(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_GestureEvent_setFingerList")
    }
    _GestureEvent_getOffsetX(ptr: KPointer): number {
        console.log("_GestureEvent_getOffsetX")
        return 1
    }
    _GestureEvent_setOffsetX(ptr: KPointer, offsetX: number): void {
        console.log("_GestureEvent_setOffsetX")
    }
    _GestureEvent_getOffsetY(ptr: KPointer): number {
        console.log("_GestureEvent_getOffsetY")
        return 1
    }
    _GestureEvent_setOffsetY(ptr: KPointer, offsetY: number): void {
        console.log("_GestureEvent_setOffsetY")
    }
    _GestureEvent_getAngle(ptr: KPointer): number {
        console.log("_GestureEvent_getAngle")
        return 1
    }
    _GestureEvent_setAngle(ptr: KPointer, angle: number): void {
        console.log("_GestureEvent_setAngle")
    }
    _GestureEvent_getSpeed(ptr: KPointer): number {
        console.log("_GestureEvent_getSpeed")
        return 1
    }
    _GestureEvent_setSpeed(ptr: KPointer, speed: number): void {
        console.log("_GestureEvent_setSpeed")
    }
    _GestureEvent_getScale(ptr: KPointer): number {
        console.log("_GestureEvent_getScale")
        return 1
    }
    _GestureEvent_setScale(ptr: KPointer, scale: number): void {
        console.log("_GestureEvent_setScale")
    }
    _GestureEvent_getPinchCenterX(ptr: KPointer): number {
        console.log("_GestureEvent_getPinchCenterX")
        return 1
    }
    _GestureEvent_setPinchCenterX(ptr: KPointer, pinchCenterX: number): void {
        console.log("_GestureEvent_setPinchCenterX")
    }
    _GestureEvent_getPinchCenterY(ptr: KPointer): number {
        console.log("_GestureEvent_getPinchCenterY")
        return 1
    }
    _GestureEvent_setPinchCenterY(ptr: KPointer, pinchCenterY: number): void {
        console.log("_GestureEvent_setPinchCenterY")
    }
    _GestureEvent_getVelocityX(ptr: KPointer): number {
        console.log("_GestureEvent_getVelocityX")
        return 1
    }
    _GestureEvent_setVelocityX(ptr: KPointer, velocityX: number): void {
        console.log("_GestureEvent_setVelocityX")
    }
    _GestureEvent_getVelocityY(ptr: KPointer): number {
        console.log("_GestureEvent_getVelocityY")
        return 1
    }
    _GestureEvent_setVelocityY(ptr: KPointer, velocityY: number): void {
        console.log("_GestureEvent_setVelocityY")
    }
    _GestureEvent_getVelocity(ptr: KPointer): number {
        console.log("_GestureEvent_getVelocity")
        return 1
    }
    _GestureEvent_setVelocity(ptr: KPointer, velocity: number): void {
        console.log("_GestureEvent_setVelocity")
    }
    _TapGestureInterface_ctor(): KPointer {
        console.log("_TapGestureInterface_ctor")
        return -1
    }
    _TapGestureInterface_getFinalizer(): KPointer {
        console.log("_TapGestureInterface_getFinalizer")
        return -1
    }
    _TapGestureInterface_onAction(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_TapGestureInterface_onAction")
        return -1
    }
    _LongPressGestureInterface_ctor(): KPointer {
        console.log("_LongPressGestureInterface_ctor")
        return -1
    }
    _LongPressGestureInterface_getFinalizer(): KPointer {
        console.log("_LongPressGestureInterface_getFinalizer")
        return -1
    }
    _LongPressGestureInterface_onAction(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_LongPressGestureInterface_onAction")
        return -1
    }
    _LongPressGestureInterface_onActionEnd(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_LongPressGestureInterface_onActionEnd")
        return -1
    }
    _LongPressGestureInterface_onActionCancel(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_LongPressGestureInterface_onActionCancel")
        return -1
    }
    _PanGestureOptions_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_PanGestureOptions_ctor")
        return -1
    }
    _PanGestureOptions_getFinalizer(): KPointer {
        console.log("_PanGestureOptions_getFinalizer")
        return -1
    }
    _PanGestureOptions_setDirection(ptr: KPointer, value: KInt): undefined {
        console.log("_PanGestureOptions_setDirection")
        return undefined
    }
    _PanGestureOptions_setDistance(ptr: KPointer, value: number): undefined {
        console.log("_PanGestureOptions_setDistance")
        return undefined
    }
    _PanGestureOptions_setFingers(ptr: KPointer, value: number): undefined {
        console.log("_PanGestureOptions_setFingers")
        return undefined
    }
    _PanGestureOptions_getDirection(ptr: KPointer): KPointer {
        console.log("_PanGestureOptions_getDirection")
        return -1
    }
    _PanGestureInterface_ctor(): KPointer {
        console.log("_PanGestureInterface_ctor")
        return -1
    }
    _PanGestureInterface_getFinalizer(): KPointer {
        console.log("_PanGestureInterface_getFinalizer")
        return -1
    }
    _PanGestureInterface_onActionStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_PanGestureInterface_onActionStart")
        return -1
    }
    _PanGestureInterface_onActionUpdate(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_PanGestureInterface_onActionUpdate")
        return -1
    }
    _PanGestureInterface_onActionEnd(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_PanGestureInterface_onActionEnd")
        return -1
    }
    _PanGestureInterface_onActionCancel(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_PanGestureInterface_onActionCancel")
        return -1
    }
    _SwipeGestureInterface_ctor(): KPointer {
        console.log("_SwipeGestureInterface_ctor")
        return -1
    }
    _SwipeGestureInterface_getFinalizer(): KPointer {
        console.log("_SwipeGestureInterface_getFinalizer")
        return -1
    }
    _SwipeGestureInterface_onAction(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_SwipeGestureInterface_onAction")
        return -1
    }
    _PinchGestureInterface_ctor(): KPointer {
        console.log("_PinchGestureInterface_ctor")
        return -1
    }
    _PinchGestureInterface_getFinalizer(): KPointer {
        console.log("_PinchGestureInterface_getFinalizer")
        return -1
    }
    _PinchGestureInterface_onActionStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_PinchGestureInterface_onActionStart")
        return -1
    }
    _PinchGestureInterface_onActionUpdate(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_PinchGestureInterface_onActionUpdate")
        return -1
    }
    _PinchGestureInterface_onActionEnd(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_PinchGestureInterface_onActionEnd")
        return -1
    }
    _PinchGestureInterface_onActionCancel(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_PinchGestureInterface_onActionCancel")
        return -1
    }
    _RotationGestureInterface_ctor(): KPointer {
        console.log("_RotationGestureInterface_ctor")
        return -1
    }
    _RotationGestureInterface_getFinalizer(): KPointer {
        console.log("_RotationGestureInterface_getFinalizer")
        return -1
    }
    _RotationGestureInterface_onActionStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_RotationGestureInterface_onActionStart")
        return -1
    }
    _RotationGestureInterface_onActionUpdate(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_RotationGestureInterface_onActionUpdate")
        return -1
    }
    _RotationGestureInterface_onActionEnd(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_RotationGestureInterface_onActionEnd")
        return -1
    }
    _RotationGestureInterface_onActionCancel(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_RotationGestureInterface_onActionCancel")
        return -1
    }
    _GestureGroupInterface_ctor(): KPointer {
        console.log("_GestureGroupInterface_ctor")
        return -1
    }
    _GestureGroupInterface_getFinalizer(): KPointer {
        console.log("_GestureGroupInterface_getFinalizer")
        return -1
    }
    _GestureGroupInterface_onCancel(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_GestureGroupInterface_onCancel")
        return -1
    }
    _ScrollableTargetInfo_ctor(): KPointer {
        console.log("_ScrollableTargetInfo_ctor")
        return -1
    }
    _ScrollableTargetInfo_getFinalizer(): KPointer {
        console.log("_ScrollableTargetInfo_getFinalizer")
        return -1
    }
    _ScrollableTargetInfo_isBegin(ptr: KPointer): boolean {
        console.log("_ScrollableTargetInfo_isBegin")
        return false
    }
    _ScrollableTargetInfo_isEnd(ptr: KPointer): boolean {
        console.log("_ScrollableTargetInfo_isEnd")
        return false
    }
    _EventTargetInfo_ctor(): KPointer {
        console.log("_EventTargetInfo_ctor")
        return -1
    }
    _EventTargetInfo_getFinalizer(): KPointer {
        console.log("_EventTargetInfo_getFinalizer")
        return -1
    }
    _EventTargetInfo_getId(ptr: KPointer): string {
        console.log("_EventTargetInfo_getId")
        return ""
    }
    _GestureRecognizer_ctor(): KPointer {
        console.log("_GestureRecognizer_ctor")
        return -1
    }
    _GestureRecognizer_getFinalizer(): KPointer {
        console.log("_GestureRecognizer_getFinalizer")
        return -1
    }
    _GestureRecognizer_getTag(ptr: KPointer): string {
        console.log("_GestureRecognizer_getTag")
        return ""
    }
    _GestureRecognizer_getType(ptr: KPointer): KPointer {
        console.log("_GestureRecognizer_getType")
        return -1
    }
    _GestureRecognizer_isBuiltIn(ptr: KPointer): boolean {
        console.log("_GestureRecognizer_isBuiltIn")
        return false
    }
    _GestureRecognizer_setEnabled(ptr: KPointer, isEnabled: KInt): void {
        console.log("_GestureRecognizer_setEnabled")
    }
    _GestureRecognizer_isEnabled(ptr: KPointer): boolean {
        console.log("_GestureRecognizer_isEnabled")
        return false
    }
    _GestureRecognizer_getState(ptr: KPointer): KPointer {
        console.log("_GestureRecognizer_getState")
        return -1
    }
    _GestureRecognizer_getEventTargetInfo(ptr: KPointer): KPointer {
        console.log("_GestureRecognizer_getEventTargetInfo")
        return -1
    }
    _GestureRecognizer_isValid(ptr: KPointer): boolean {
        console.log("_GestureRecognizer_isValid")
        return false
    }
    _PanRecognizer_ctor(): KPointer {
        console.log("_PanRecognizer_ctor")
        return -1
    }
    _PanRecognizer_getFinalizer(): KPointer {
        console.log("_PanRecognizer_getFinalizer")
        return -1
    }
    _PanRecognizer_getPanGestureOptions(ptr: KPointer): KPointer {
        console.log("_PanRecognizer_getPanGestureOptions")
        return -1
    }
    _ImageAnalyzerController_ctor(): KPointer {
        console.log("_ImageAnalyzerController_ctor")
        return -1
    }
    _ImageAnalyzerController_getFinalizer(): KPointer {
        console.log("_ImageAnalyzerController_getFinalizer")
        return -1
    }
    _ImageAnalyzerController_getImageAnalyzerSupportTypes(ptr: KPointer): KInteropReturnBuffer {
        console.log("_ImageAnalyzerController_getImageAnalyzerSupportTypes")
        return new Uint8Array()
    }
    _ListScroller_ctor(): KPointer {
        console.log("_ListScroller_ctor")
        return -1
    }
    _ListScroller_getFinalizer(): KPointer {
        console.log("_ListScroller_getFinalizer")
        return -1
    }
    _ListScroller_getItemRectInGroup(ptr: KPointer, index: number, indexInGroup: number): KInteropReturnBuffer {
        console.log("_ListScroller_getItemRectInGroup")
        return new Uint8Array()
    }
    _ListScroller_scrollToItemInGroup(ptr: KPointer, index: number, indexInGroup: number, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ListScroller_scrollToItemInGroup")
    }
    _ListScroller_closeAllSwipeActions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ListScroller_closeAllSwipeActions")
    }
    _ListScroller_getVisibleListContentInfo(ptr: KPointer, x: number, y: number): KInteropReturnBuffer {
        console.log("_ListScroller_getVisibleListContentInfo")
        return new Uint8Array()
    }
    _Matrix2D_ctor(): KPointer {
        console.log("_Matrix2D_ctor")
        return -1
    }
    _Matrix2D_getFinalizer(): KPointer {
        console.log("_Matrix2D_getFinalizer")
        return -1
    }
    _Matrix2D_identity(ptr: KPointer): KPointer {
        console.log("_Matrix2D_identity")
        return -1
    }
    _Matrix2D_invert(ptr: KPointer): KPointer {
        console.log("_Matrix2D_invert")
        return -1
    }
    _Matrix2D_multiply(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_Matrix2D_multiply")
        return -1
    }
    _Matrix2D_rotate0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_Matrix2D_rotate0")
        return -1
    }
    _Matrix2D_rotate1(ptr: KPointer, degree: number, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_Matrix2D_rotate1")
        return -1
    }
    _Matrix2D_translate(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_Matrix2D_translate")
        return -1
    }
    _Matrix2D_scale(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_Matrix2D_scale")
        return -1
    }
    _Matrix2D_getScaleX(ptr: KPointer): number {
        console.log("_Matrix2D_getScaleX")
        return 1
    }
    _Matrix2D_setScaleX(ptr: KPointer, scaleX: number): void {
        console.log("_Matrix2D_setScaleX")
    }
    _Matrix2D_getRotateY(ptr: KPointer): number {
        console.log("_Matrix2D_getRotateY")
        return 1
    }
    _Matrix2D_setRotateY(ptr: KPointer, rotateY: number): void {
        console.log("_Matrix2D_setRotateY")
    }
    _Matrix2D_getRotateX(ptr: KPointer): number {
        console.log("_Matrix2D_getRotateX")
        return 1
    }
    _Matrix2D_setRotateX(ptr: KPointer, rotateX: number): void {
        console.log("_Matrix2D_setRotateX")
    }
    _Matrix2D_getScaleY(ptr: KPointer): number {
        console.log("_Matrix2D_getScaleY")
        return 1
    }
    _Matrix2D_setScaleY(ptr: KPointer, scaleY: number): void {
        console.log("_Matrix2D_setScaleY")
    }
    _Matrix2D_getTranslateX(ptr: KPointer): number {
        console.log("_Matrix2D_getTranslateX")
        return 1
    }
    _Matrix2D_setTranslateX(ptr: KPointer, translateX: number): void {
        console.log("_Matrix2D_setTranslateX")
    }
    _Matrix2D_getTranslateY(ptr: KPointer): number {
        console.log("_Matrix2D_getTranslateY")
        return 1
    }
    _Matrix2D_setTranslateY(ptr: KPointer, translateY: number): void {
        console.log("_Matrix2D_setTranslateY")
    }
    _NavDestinationContext_ctor(): KPointer {
        console.log("_NavDestinationContext_ctor")
        return -1
    }
    _NavDestinationContext_getFinalizer(): KPointer {
        console.log("_NavDestinationContext_getFinalizer")
        return -1
    }
    _NavDestinationContext_getConfigInRouteMap(ptr: KPointer): KPointer {
        console.log("_NavDestinationContext_getConfigInRouteMap")
        return -1
    }
    _NavDestinationContext_getPathInfo(ptr: KPointer): KPointer {
        console.log("_NavDestinationContext_getPathInfo")
        return -1
    }
    _NavDestinationContext_setPathInfo(ptr: KPointer, pathInfo: KPointer): void {
        console.log("_NavDestinationContext_setPathInfo")
    }
    _NavDestinationContext_getPathStack(ptr: KPointer): KPointer {
        console.log("_NavDestinationContext_getPathStack")
        return -1
    }
    _NavDestinationContext_setPathStack(ptr: KPointer, pathStack: KPointer): void {
        console.log("_NavDestinationContext_setPathStack")
    }
    _NavDestinationContext_getNavDestinationId(ptr: KPointer): string {
        console.log("_NavDestinationContext_getNavDestinationId")
        return ""
    }
    _NavDestinationContext_setNavDestinationId(ptr: KPointer, navDestinationId: KStringPtr): void {
        console.log("_NavDestinationContext_setNavDestinationId")
    }
    _NavPathInfo_ctor(name: KStringPtr, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_NavPathInfo_ctor")
        return -1
    }
    _NavPathInfo_getFinalizer(): KPointer {
        console.log("_NavPathInfo_getFinalizer")
        return -1
    }
    _NavPathInfo_getName(ptr: KPointer): string {
        console.log("_NavPathInfo_getName")
        return ""
    }
    _NavPathInfo_setName(ptr: KPointer, name: KStringPtr): void {
        console.log("_NavPathInfo_setName")
    }
    _NavPathInfo_setParam(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_NavPathInfo_setParam")
    }
    _NavPathInfo_getOnPop(ptr: KPointer): KPointer {
        console.log("_NavPathInfo_getOnPop")
        return -1
    }
    _NavPathInfo_setOnPop(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_NavPathInfo_setOnPop")
    }
    _NavPathInfo_getIsEntry(ptr: KPointer): boolean {
        console.log("_NavPathInfo_getIsEntry")
        return false
    }
    _NavPathInfo_setIsEntry(ptr: KPointer, isEntry: KInt): void {
        console.log("_NavPathInfo_setIsEntry")
    }
    _NavPathStack_ctor(): KPointer {
        console.log("_NavPathStack_ctor")
        return -1
    }
    _NavPathStack_getFinalizer(): KPointer {
        console.log("_NavPathStack_getFinalizer")
        return -1
    }
    _NavPathStack_pushPath0(ptr: KPointer, info: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_NavPathStack_pushPath0")
    }
    _NavPathStack_pushPath1(ptr: KPointer, info: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_NavPathStack_pushPath1")
    }
    _NavPathStack_pushDestination0(ptr: KPointer, info: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_NavPathStack_pushDestination0")
        return -1
    }
    _NavPathStack_pushDestination1(ptr: KPointer, info: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_NavPathStack_pushDestination1")
        return -1
    }
    _NavPathStack_pushPathByName0(ptr: KPointer, name: KStringPtr, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_NavPathStack_pushPathByName0")
    }
    _NavPathStack_pushPathByName1(ptr: KPointer, name: KStringPtr, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_NavPathStack_pushPathByName1")
    }
    _NavPathStack_pushDestinationByName0(ptr: KPointer, name: KStringPtr, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_NavPathStack_pushDestinationByName0")
        return -1
    }
    _NavPathStack_pushDestinationByName1(ptr: KPointer, name: KStringPtr, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_NavPathStack_pushDestinationByName1")
        return -1
    }
    _NavPathStack_replacePath0(ptr: KPointer, info: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_NavPathStack_replacePath0")
    }
    _NavPathStack_replacePath1(ptr: KPointer, info: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_NavPathStack_replacePath1")
    }
    _NavPathStack_replaceDestination(ptr: KPointer, info: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_NavPathStack_replaceDestination")
        return -1
    }
    _NavPathStack_replacePathByName(ptr: KPointer, name: KStringPtr, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_NavPathStack_replacePathByName")
    }
    _NavPathStack_removeByIndexes(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): number {
        console.log("_NavPathStack_removeByIndexes")
        return 1
    }
    _NavPathStack_removeByName(ptr: KPointer, name: KStringPtr): number {
        console.log("_NavPathStack_removeByName")
        return 1
    }
    _NavPathStack_removeByNavDestinationId(ptr: KPointer, navDestinationId: KStringPtr): boolean {
        console.log("_NavPathStack_removeByNavDestinationId")
        return false
    }
    _NavPathStack_pop0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_NavPathStack_pop0")
        return -1
    }
    _NavPathStack_pop1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_NavPathStack_pop1")
        return -1
    }
    _NavPathStack_popToName0(ptr: KPointer, name: KStringPtr, thisArray: Uint8Array, thisLength: int32): number {
        console.log("_NavPathStack_popToName0")
        return 1
    }
    _NavPathStack_popToName1(ptr: KPointer, name: KStringPtr, thisArray: Uint8Array, thisLength: int32): number {
        console.log("_NavPathStack_popToName1")
        return 1
    }
    _NavPathStack_popToIndex0(ptr: KPointer, index: number, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_NavPathStack_popToIndex0")
    }
    _NavPathStack_popToIndex1(ptr: KPointer, index: number, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_NavPathStack_popToIndex1")
    }
    _NavPathStack_moveToTop(ptr: KPointer, name: KStringPtr, thisArray: Uint8Array, thisLength: int32): number {
        console.log("_NavPathStack_moveToTop")
        return 1
    }
    _NavPathStack_moveIndexToTop(ptr: KPointer, index: number, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_NavPathStack_moveIndexToTop")
    }
    _NavPathStack_clear(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_NavPathStack_clear")
    }
    _NavPathStack_getAllPathName(ptr: KPointer): KInteropReturnBuffer {
        console.log("_NavPathStack_getAllPathName")
        return new Uint8Array()
    }
    _NavPathStack_getParamByIndex(ptr: KPointer, index: number): KPointer {
        console.log("_NavPathStack_getParamByIndex")
        return -1
    }
    _NavPathStack_getParamByName(ptr: KPointer, name: KStringPtr): KInteropReturnBuffer {
        console.log("_NavPathStack_getParamByName")
        return new Uint8Array()
    }
    _NavPathStack_getIndexByName(ptr: KPointer, name: KStringPtr): KInteropReturnBuffer {
        console.log("_NavPathStack_getIndexByName")
        return new Uint8Array()
    }
    _NavPathStack_getParent(ptr: KPointer): KPointer {
        console.log("_NavPathStack_getParent")
        return -1
    }
    _NavPathStack_size(ptr: KPointer): number {
        console.log("_NavPathStack_size")
        return 1
    }
    _NavPathStack_disableAnimation(ptr: KPointer, value: KInt): void {
        console.log("_NavPathStack_disableAnimation")
    }
    _NavPathStack_setInterception(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_NavPathStack_setInterception")
    }
    _NavigationTransitionProxy_ctor(): KPointer {
        console.log("_NavigationTransitionProxy_ctor")
        return -1
    }
    _NavigationTransitionProxy_getFinalizer(): KPointer {
        console.log("_NavigationTransitionProxy_getFinalizer")
        return -1
    }
    _NavigationTransitionProxy_finishTransition(ptr: KPointer): void {
        console.log("_NavigationTransitionProxy_finishTransition")
    }
    _NavigationTransitionProxy_cancelTransition(ptr: KPointer): void {
        console.log("_NavigationTransitionProxy_cancelTransition")
    }
    _NavigationTransitionProxy_updateTransition(ptr: KPointer, progress: number): void {
        console.log("_NavigationTransitionProxy_updateTransition")
    }
    _NavigationTransitionProxy_setFrom(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_NavigationTransitionProxy_setFrom")
    }
    _NavigationTransitionProxy_setTo(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_NavigationTransitionProxy_setTo")
    }
    _NavigationTransitionProxy_getIsInteractive(ptr: KPointer): boolean {
        console.log("_NavigationTransitionProxy_getIsInteractive")
        return false
    }
    _NavigationTransitionProxy_setIsInteractive(ptr: KPointer, isInteractive: KInt): void {
        console.log("_NavigationTransitionProxy_setIsInteractive")
    }
    _PatternLockController_ctor(): KPointer {
        console.log("_PatternLockController_ctor")
        return -1
    }
    _PatternLockController_getFinalizer(): KPointer {
        console.log("_PatternLockController_getFinalizer")
        return -1
    }
    _PatternLockController_reset(ptr: KPointer): undefined {
        console.log("_PatternLockController_reset")
        return undefined
    }
    _PatternLockController_setChallengeResult(ptr: KPointer, result: KInt): void {
        console.log("_PatternLockController_setChallengeResult")
    }
    _RichEditorBaseController_ctor(): KPointer {
        console.log("_RichEditorBaseController_ctor")
        return -1
    }
    _RichEditorBaseController_getFinalizer(): KPointer {
        console.log("_RichEditorBaseController_getFinalizer")
        return -1
    }
    _RichEditorBaseController_getCaretOffset(ptr: KPointer): number {
        console.log("_RichEditorBaseController_getCaretOffset")
        return 1
    }
    _RichEditorBaseController_setCaretOffset(ptr: KPointer, offset: number): boolean {
        console.log("_RichEditorBaseController_setCaretOffset")
        return false
    }
    _RichEditorBaseController_closeSelectionMenu(ptr: KPointer): void {
        console.log("_RichEditorBaseController_closeSelectionMenu")
    }
    _RichEditorBaseController_getTypingStyle(ptr: KPointer): KInteropReturnBuffer {
        console.log("_RichEditorBaseController_getTypingStyle")
        return new Uint8Array()
    }
    _RichEditorBaseController_setTypingStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RichEditorBaseController_setTypingStyle")
    }
    _RichEditorBaseController_setSelection(ptr: KPointer, selectionStart: number, selectionEnd: number, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RichEditorBaseController_setSelection")
    }
    _RichEditorBaseController_isEditing(ptr: KPointer): boolean {
        console.log("_RichEditorBaseController_isEditing")
        return false
    }
    _RichEditorBaseController_stopEditing(ptr: KPointer): void {
        console.log("_RichEditorBaseController_stopEditing")
    }
    _RichEditorBaseController_getLayoutManager(ptr: KPointer): KPointer {
        console.log("_RichEditorBaseController_getLayoutManager")
        return -1
    }
    _RichEditorBaseController_getPreviewText(ptr: KPointer): KInteropReturnBuffer {
        console.log("_RichEditorBaseController_getPreviewText")
        return new Uint8Array()
    }
    _RichEditorController_ctor(): KPointer {
        console.log("_RichEditorController_ctor")
        return -1
    }
    _RichEditorController_getFinalizer(): KPointer {
        console.log("_RichEditorController_getFinalizer")
        return -1
    }
    _RichEditorController_addTextSpan(ptr: KPointer, value: KStringPtr, thisArray: Uint8Array, thisLength: int32): number {
        console.log("_RichEditorController_addTextSpan")
        return 1
    }
    _RichEditorController_addImageSpan(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): number {
        console.log("_RichEditorController_addImageSpan")
        return 1
    }
    _RichEditorController_addBuilderSpan(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): number {
        console.log("_RichEditorController_addBuilderSpan")
        return 1
    }
    _RichEditorController_addSymbolSpan(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): number {
        console.log("_RichEditorController_addSymbolSpan")
        return 1
    }
    _RichEditorController_updateSpanStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RichEditorController_updateSpanStyle")
    }
    _RichEditorController_updateParagraphStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RichEditorController_updateParagraphStyle")
    }
    _RichEditorController_deleteSpans(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RichEditorController_deleteSpans")
    }
    _RichEditorController_getSpans(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KInteropReturnBuffer {
        console.log("_RichEditorController_getSpans")
        return new Uint8Array()
    }
    _RichEditorController_getParagraphs(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KInteropReturnBuffer {
        console.log("_RichEditorController_getParagraphs")
        return new Uint8Array()
    }
    _RichEditorController_getSelection(ptr: KPointer): KInteropReturnBuffer {
        console.log("_RichEditorController_getSelection")
        return new Uint8Array()
    }
    _RichEditorController_fromStyledString(ptr: KPointer, value: KPointer): KInteropReturnBuffer {
        console.log("_RichEditorController_fromStyledString")
        return new Uint8Array()
    }
    _RichEditorController_toStyledString(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_RichEditorController_toStyledString")
        return -1
    }
    _RichEditorStyledStringController_ctor(): KPointer {
        console.log("_RichEditorStyledStringController_ctor")
        return -1
    }
    _RichEditorStyledStringController_getFinalizer(): KPointer {
        console.log("_RichEditorStyledStringController_getFinalizer")
        return -1
    }
    _RichEditorStyledStringController_setStyledString(ptr: KPointer, styledString: KPointer): void {
        console.log("_RichEditorStyledStringController_setStyledString")
    }
    _RichEditorStyledStringController_getStyledString(ptr: KPointer): KPointer {
        console.log("_RichEditorStyledStringController_getStyledString")
        return -1
    }
    _RichEditorStyledStringController_getSelection(ptr: KPointer): KInteropReturnBuffer {
        console.log("_RichEditorStyledStringController_getSelection")
        return new Uint8Array()
    }
    _RichEditorStyledStringController_onContentChanged(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_RichEditorStyledStringController_onContentChanged")
    }
    _Scroller_ctor(): KPointer {
        console.log("_Scroller_ctor")
        return -1
    }
    _Scroller_getFinalizer(): KPointer {
        console.log("_Scroller_getFinalizer")
        return -1
    }
    _Scroller_scrollTo(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): undefined {
        console.log("_Scroller_scrollTo")
        return undefined
    }
    _Scroller_scrollEdge(ptr: KPointer, value: KInt, thisArray: Uint8Array, thisLength: int32): undefined {
        console.log("_Scroller_scrollEdge")
        return undefined
    }
    _Scroller_fling(ptr: KPointer, velocity: number): void {
        console.log("_Scroller_fling")
    }
    _Scroller_scrollPage0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): undefined {
        console.log("_Scroller_scrollPage0")
        return undefined
    }
    _Scroller_scrollPage1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): undefined {
        console.log("_Scroller_scrollPage1")
        return undefined
    }
    _Scroller_currentOffset(ptr: KPointer): KInteropReturnBuffer {
        console.log("_Scroller_currentOffset")
        return new Uint8Array()
    }
    _Scroller_scrollToIndex(ptr: KPointer, value: number, thisArray: Uint8Array, thisLength: int32): undefined {
        console.log("_Scroller_scrollToIndex")
        return undefined
    }
    _Scroller_scrollBy(ptr: KPointer, dx: Length, dy: Length): undefined {
        console.log("_Scroller_scrollBy")
        return undefined
    }
    _Scroller_isAtEnd(ptr: KPointer): boolean {
        console.log("_Scroller_isAtEnd")
        return false
    }
    _Scroller_getItemRect(ptr: KPointer, index: number): KInteropReturnBuffer {
        console.log("_Scroller_getItemRect")
        return new Uint8Array()
    }
    _Scroller_getItemIndex(ptr: KPointer, x: number, y: number): number {
        console.log("_Scroller_getItemIndex")
        return 1
    }
    _SearchController_ctor(): KPointer {
        console.log("_SearchController_ctor")
        return -1
    }
    _SearchController_getFinalizer(): KPointer {
        console.log("_SearchController_getFinalizer")
        return -1
    }
    _SearchController_caretPosition(ptr: KPointer, value: number): void {
        console.log("_SearchController_caretPosition")
    }
    _SearchController_stopEditing(ptr: KPointer): void {
        console.log("_SearchController_stopEditing")
    }
    _SearchController_setTextSelection(ptr: KPointer, selectionStart: number, selectionEnd: number, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_SearchController_setTextSelection")
    }
    _SwiperController_ctor(): KPointer {
        console.log("_SwiperController_ctor")
        return -1
    }
    _SwiperController_getFinalizer(): KPointer {
        console.log("_SwiperController_getFinalizer")
        return -1
    }
    _SwiperController_showNext(ptr: KPointer): undefined {
        console.log("_SwiperController_showNext")
        return undefined
    }
    _SwiperController_showPrevious(ptr: KPointer): undefined {
        console.log("_SwiperController_showPrevious")
        return undefined
    }
    _SwiperController_changeIndex(ptr: KPointer, index: number, thisArray: Uint8Array, thisLength: int32): undefined {
        console.log("_SwiperController_changeIndex")
        return undefined
    }
    _SwiperController_finishAnimation(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): undefined {
        console.log("_SwiperController_finishAnimation")
        return undefined
    }
    _SwiperContentTransitionProxy_ctor(): KPointer {
        console.log("_SwiperContentTransitionProxy_ctor")
        return -1
    }
    _SwiperContentTransitionProxy_getFinalizer(): KPointer {
        console.log("_SwiperContentTransitionProxy_getFinalizer")
        return -1
    }
    _SwiperContentTransitionProxy_finishTransition(ptr: KPointer): void {
        console.log("_SwiperContentTransitionProxy_finishTransition")
    }
    _SwiperContentTransitionProxy_getSelectedIndex(ptr: KPointer): number {
        console.log("_SwiperContentTransitionProxy_getSelectedIndex")
        return 1
    }
    _SwiperContentTransitionProxy_setSelectedIndex(ptr: KPointer, selectedIndex: number): void {
        console.log("_SwiperContentTransitionProxy_setSelectedIndex")
    }
    _SwiperContentTransitionProxy_getIndex(ptr: KPointer): number {
        console.log("_SwiperContentTransitionProxy_getIndex")
        return 1
    }
    _SwiperContentTransitionProxy_setIndex(ptr: KPointer, index: number): void {
        console.log("_SwiperContentTransitionProxy_setIndex")
    }
    _SwiperContentTransitionProxy_getPosition(ptr: KPointer): number {
        console.log("_SwiperContentTransitionProxy_getPosition")
        return 1
    }
    _SwiperContentTransitionProxy_setPosition(ptr: KPointer, position: number): void {
        console.log("_SwiperContentTransitionProxy_setPosition")
    }
    _SwiperContentTransitionProxy_getMainAxisLength(ptr: KPointer): number {
        console.log("_SwiperContentTransitionProxy_getMainAxisLength")
        return 1
    }
    _SwiperContentTransitionProxy_setMainAxisLength(ptr: KPointer, mainAxisLength: number): void {
        console.log("_SwiperContentTransitionProxy_setMainAxisLength")
    }
    _IndicatorComponentController_ctor(): KPointer {
        console.log("_IndicatorComponentController_ctor")
        return -1
    }
    _IndicatorComponentController_getFinalizer(): KPointer {
        console.log("_IndicatorComponentController_getFinalizer")
        return -1
    }
    _IndicatorComponentController_showNext(ptr: KPointer): void {
        console.log("_IndicatorComponentController_showNext")
    }
    _IndicatorComponentController_showPrevious(ptr: KPointer): void {
        console.log("_IndicatorComponentController_showPrevious")
    }
    _IndicatorComponentController_changeIndex(ptr: KPointer, index: number, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_IndicatorComponentController_changeIndex")
    }
    _HierarchicalSymbolEffect_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_HierarchicalSymbolEffect_ctor")
        return -1
    }
    _HierarchicalSymbolEffect_getFinalizer(): KPointer {
        console.log("_HierarchicalSymbolEffect_getFinalizer")
        return -1
    }
    _HierarchicalSymbolEffect_getFillStyle(ptr: KPointer): KPointer {
        console.log("_HierarchicalSymbolEffect_getFillStyle")
        return -1
    }
    _HierarchicalSymbolEffect_setFillStyle(ptr: KPointer, fillStyle: KInt): void {
        console.log("_HierarchicalSymbolEffect_setFillStyle")
    }
    _AppearSymbolEffect_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_AppearSymbolEffect_ctor")
        return -1
    }
    _AppearSymbolEffect_getFinalizer(): KPointer {
        console.log("_AppearSymbolEffect_getFinalizer")
        return -1
    }
    _AppearSymbolEffect_getScope(ptr: KPointer): KPointer {
        console.log("_AppearSymbolEffect_getScope")
        return -1
    }
    _AppearSymbolEffect_setScope(ptr: KPointer, scope: KInt): void {
        console.log("_AppearSymbolEffect_setScope")
    }
    _DisappearSymbolEffect_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_DisappearSymbolEffect_ctor")
        return -1
    }
    _DisappearSymbolEffect_getFinalizer(): KPointer {
        console.log("_DisappearSymbolEffect_getFinalizer")
        return -1
    }
    _DisappearSymbolEffect_getScope(ptr: KPointer): KPointer {
        console.log("_DisappearSymbolEffect_getScope")
        return -1
    }
    _DisappearSymbolEffect_setScope(ptr: KPointer, scope: KInt): void {
        console.log("_DisappearSymbolEffect_setScope")
    }
    _BounceSymbolEffect_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_BounceSymbolEffect_ctor")
        return -1
    }
    _BounceSymbolEffect_getFinalizer(): KPointer {
        console.log("_BounceSymbolEffect_getFinalizer")
        return -1
    }
    _BounceSymbolEffect_getScope(ptr: KPointer): KPointer {
        console.log("_BounceSymbolEffect_getScope")
        return -1
    }
    _BounceSymbolEffect_setScope(ptr: KPointer, scope: KInt): void {
        console.log("_BounceSymbolEffect_setScope")
    }
    _BounceSymbolEffect_getDirection(ptr: KPointer): KPointer {
        console.log("_BounceSymbolEffect_getDirection")
        return -1
    }
    _BounceSymbolEffect_setDirection(ptr: KPointer, direction: KInt): void {
        console.log("_BounceSymbolEffect_setDirection")
    }
    _TabsController_ctor(): KPointer {
        console.log("_TabsController_ctor")
        return -1
    }
    _TabsController_getFinalizer(): KPointer {
        console.log("_TabsController_getFinalizer")
        return -1
    }
    _TabsController_changeIndex(ptr: KPointer, value: number): void {
        console.log("_TabsController_changeIndex")
    }
    _TabsController_preloadItems(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_TabsController_preloadItems")
        return -1
    }
    _TabsController_setTabBarTranslate(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TabsController_setTabBarTranslate")
    }
    _TabsController_setTabBarOpacity(ptr: KPointer, opacity: number): void {
        console.log("_TabsController_setTabBarOpacity")
    }
    _TabContentTransitionProxy_ctor(): KPointer {
        console.log("_TabContentTransitionProxy_ctor")
        return -1
    }
    _TabContentTransitionProxy_getFinalizer(): KPointer {
        console.log("_TabContentTransitionProxy_getFinalizer")
        return -1
    }
    _TabContentTransitionProxy_finishTransition(ptr: KPointer): void {
        console.log("_TabContentTransitionProxy_finishTransition")
    }
    _TabContentTransitionProxy_getFrom(ptr: KPointer): number {
        console.log("_TabContentTransitionProxy_getFrom")
        return 1
    }
    _TabContentTransitionProxy_setFrom(ptr: KPointer, from: number): void {
        console.log("_TabContentTransitionProxy_setFrom")
    }
    _TabContentTransitionProxy_getTo(ptr: KPointer): number {
        console.log("_TabContentTransitionProxy_getTo")
        return 1
    }
    _TabContentTransitionProxy_setTo(ptr: KPointer, to: number): void {
        console.log("_TabContentTransitionProxy_setTo")
    }
    _TextController_ctor(): KPointer {
        console.log("_TextController_ctor")
        return -1
    }
    _TextController_getFinalizer(): KPointer {
        console.log("_TextController_getFinalizer")
        return -1
    }
    _TextController_closeSelectionMenu(ptr: KPointer): void {
        console.log("_TextController_closeSelectionMenu")
    }
    _TextController_setStyledString(ptr: KPointer, value: KPointer): void {
        console.log("_TextController_setStyledString")
    }
    _TextController_getLayoutManager(ptr: KPointer): KPointer {
        console.log("_TextController_getLayoutManager")
        return -1
    }
    _TextAreaController_ctor(): KPointer {
        console.log("_TextAreaController_ctor")
        return -1
    }
    _TextAreaController_getFinalizer(): KPointer {
        console.log("_TextAreaController_getFinalizer")
        return -1
    }
    _TextAreaController_caretPosition(ptr: KPointer, value: number): void {
        console.log("_TextAreaController_caretPosition")
    }
    _TextAreaController_setTextSelection(ptr: KPointer, selectionStart: number, selectionEnd: number, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextAreaController_setTextSelection")
    }
    _TextAreaController_stopEditing(ptr: KPointer): void {
        console.log("_TextAreaController_stopEditing")
    }
    _TextClockController_ctor(): KPointer {
        console.log("_TextClockController_ctor")
        return -1
    }
    _TextClockController_getFinalizer(): KPointer {
        console.log("_TextClockController_getFinalizer")
        return -1
    }
    _TextClockController_start(ptr: KPointer): undefined {
        console.log("_TextClockController_start")
        return undefined
    }
    _TextClockController_stop(ptr: KPointer): undefined {
        console.log("_TextClockController_stop")
        return undefined
    }
    _TextBaseController_ctor(): KPointer {
        console.log("_TextBaseController_ctor")
        return -1
    }
    _TextBaseController_getFinalizer(): KPointer {
        console.log("_TextBaseController_getFinalizer")
        return -1
    }
    _TextBaseController_setSelection(ptr: KPointer, selectionStart: number, selectionEnd: number, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextBaseController_setSelection")
    }
    _TextBaseController_closeSelectionMenu(ptr: KPointer): void {
        console.log("_TextBaseController_closeSelectionMenu")
    }
    _TextBaseController_getLayoutManager(ptr: KPointer): KPointer {
        console.log("_TextBaseController_getLayoutManager")
        return -1
    }
    _TextEditControllerEx_ctor(): KPointer {
        console.log("_TextEditControllerEx_ctor")
        return -1
    }
    _TextEditControllerEx_getFinalizer(): KPointer {
        console.log("_TextEditControllerEx_getFinalizer")
        return -1
    }
    _TextEditControllerEx_isEditing(ptr: KPointer): boolean {
        console.log("_TextEditControllerEx_isEditing")
        return false
    }
    _TextEditControllerEx_stopEditing(ptr: KPointer): void {
        console.log("_TextEditControllerEx_stopEditing")
    }
    _TextEditControllerEx_setCaretOffset(ptr: KPointer, offset: number): boolean {
        console.log("_TextEditControllerEx_setCaretOffset")
        return false
    }
    _TextEditControllerEx_getCaretOffset(ptr: KPointer): number {
        console.log("_TextEditControllerEx_getCaretOffset")
        return 1
    }
    _TextEditControllerEx_getPreviewText(ptr: KPointer): KInteropReturnBuffer {
        console.log("_TextEditControllerEx_getPreviewText")
        return new Uint8Array()
    }
    _StyledStringController_ctor(): KPointer {
        console.log("_StyledStringController_ctor")
        return -1
    }
    _StyledStringController_getFinalizer(): KPointer {
        console.log("_StyledStringController_getFinalizer")
        return -1
    }
    _StyledStringController_setStyledString(ptr: KPointer, styledString: KPointer): void {
        console.log("_StyledStringController_setStyledString")
    }
    _StyledStringController_getStyledString(ptr: KPointer): KPointer {
        console.log("_StyledStringController_getStyledString")
        return -1
    }
    _LayoutManager_ctor(): KPointer {
        console.log("_LayoutManager_ctor")
        return -1
    }
    _LayoutManager_getFinalizer(): KPointer {
        console.log("_LayoutManager_getFinalizer")
        return -1
    }
    _LayoutManager_getLineCount(ptr: KPointer): number {
        console.log("_LayoutManager_getLineCount")
        return 1
    }
    _LayoutManager_getGlyphPositionAtCoordinate(ptr: KPointer, x: number, y: number): KInteropReturnBuffer {
        console.log("_LayoutManager_getGlyphPositionAtCoordinate")
        return new Uint8Array()
    }
    _LayoutManager_getLineMetrics(ptr: KPointer, lineNumber: number): KInteropReturnBuffer {
        console.log("_LayoutManager_getLineMetrics")
        return new Uint8Array()
    }
    _LayoutManager_getRectsForRange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32, widthStyle: KInt, heightStyle: KInt): KInteropReturnBuffer {
        console.log("_LayoutManager_getRectsForRange")
        return new Uint8Array()
    }
    _TextMenuItemId_ctor(): KPointer {
        console.log("_TextMenuItemId_ctor")
        return -1
    }
    _TextMenuItemId_getFinalizer(): KPointer {
        console.log("_TextMenuItemId_getFinalizer")
        return -1
    }
    _TextMenuItemId_of(thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_TextMenuItemId_of")
        return -1
    }
    _TextMenuItemId_equals(ptr: KPointer, id: KPointer): boolean {
        console.log("_TextMenuItemId_equals")
        return false
    }
    _TextMenuItemId_getCUT(): KPointer {
        console.log("_TextMenuItemId_getCUT")
        return -1
    }
    _TextMenuItemId_getCOPY(): KPointer {
        console.log("_TextMenuItemId_getCOPY")
        return -1
    }
    _TextMenuItemId_getPASTE(): KPointer {
        console.log("_TextMenuItemId_getPASTE")
        return -1
    }
    _TextMenuItemId_getSELECT_ALL(): KPointer {
        console.log("_TextMenuItemId_getSELECT_ALL")
        return -1
    }
    _TextMenuItemId_getCOLLABORATION_SERVICE(): KPointer {
        console.log("_TextMenuItemId_getCOLLABORATION_SERVICE")
        return -1
    }
    _TextMenuItemId_getCAMERA_INPUT(): KPointer {
        console.log("_TextMenuItemId_getCAMERA_INPUT")
        return -1
    }
    _TextMenuItemId_getAI_WRITER(): KPointer {
        console.log("_TextMenuItemId_getAI_WRITER")
        return -1
    }
    _EditMenuOptions_ctor(): KPointer {
        console.log("_EditMenuOptions_ctor")
        return -1
    }
    _EditMenuOptions_getFinalizer(): KPointer {
        console.log("_EditMenuOptions_getFinalizer")
        return -1
    }
    _EditMenuOptions_onCreateMenu(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KInteropReturnBuffer {
        console.log("_EditMenuOptions_onCreateMenu")
        return new Uint8Array()
    }
    _EditMenuOptions_onMenuItemClick(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): boolean {
        console.log("_EditMenuOptions_onMenuItemClick")
        return false
    }
    _SubmitEvent_ctor(): KPointer {
        console.log("_SubmitEvent_ctor")
        return -1
    }
    _SubmitEvent_getFinalizer(): KPointer {
        console.log("_SubmitEvent_getFinalizer")
        return -1
    }
    _SubmitEvent_keepEditableState(ptr: KPointer): void {
        console.log("_SubmitEvent_keepEditableState")
    }
    _SubmitEvent_getText(ptr: KPointer): string {
        console.log("_SubmitEvent_getText")
        return ""
    }
    _SubmitEvent_setText(ptr: KPointer, text: KStringPtr): void {
        console.log("_SubmitEvent_setText")
    }
    _TextInputController_ctor(): KPointer {
        console.log("_TextInputController_ctor")
        return -1
    }
    _TextInputController_getFinalizer(): KPointer {
        console.log("_TextInputController_getFinalizer")
        return -1
    }
    _TextInputController_caretPosition(ptr: KPointer, value: number): void {
        console.log("_TextInputController_caretPosition")
    }
    _TextInputController_setTextSelection(ptr: KPointer, selectionStart: number, selectionEnd: number, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_TextInputController_setTextSelection")
    }
    _TextInputController_stopEditing(ptr: KPointer): void {
        console.log("_TextInputController_stopEditing")
    }
    _TextPickerDialog_show(thisArray: Uint8Array, thisLength: int32): undefined {
        console.log("_TextPickerDialog_show")
        return undefined
    }
    _TextTimerController_ctor(): KPointer {
        console.log("_TextTimerController_ctor")
        return -1
    }
    _TextTimerController_getFinalizer(): KPointer {
        console.log("_TextTimerController_getFinalizer")
        return -1
    }
    _TextTimerController_start(ptr: KPointer): undefined {
        console.log("_TextTimerController_start")
        return undefined
    }
    _TextTimerController_pause(ptr: KPointer): undefined {
        console.log("_TextTimerController_pause")
        return undefined
    }
    _TextTimerController_reset(ptr: KPointer): undefined {
        console.log("_TextTimerController_reset")
        return undefined
    }
    _TimePickerDialog_show(thisArray: Uint8Array, thisLength: int32): undefined {
        console.log("_TimePickerDialog_show")
        return undefined
    }
    _ColorFilter_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_ColorFilter_ctor")
        return -1
    }
    _ColorFilter_getFinalizer(): KPointer {
        console.log("_ColorFilter_getFinalizer")
        return -1
    }
    _VideoController_ctor(): KPointer {
        console.log("_VideoController_ctor")
        return -1
    }
    _VideoController_getFinalizer(): KPointer {
        console.log("_VideoController_getFinalizer")
        return -1
    }
    _VideoController_start(ptr: KPointer): undefined {
        console.log("_VideoController_start")
        return undefined
    }
    _VideoController_pause(ptr: KPointer): undefined {
        console.log("_VideoController_pause")
        return undefined
    }
    _VideoController_stop(ptr: KPointer): undefined {
        console.log("_VideoController_stop")
        return undefined
    }
    _VideoController_setCurrentTime0(ptr: KPointer, value: number): undefined {
        console.log("_VideoController_setCurrentTime0")
        return undefined
    }
    _VideoController_requestFullscreen(ptr: KPointer, value: KInt): undefined {
        console.log("_VideoController_requestFullscreen")
        return undefined
    }
    _VideoController_exitFullscreen(ptr: KPointer): undefined {
        console.log("_VideoController_exitFullscreen")
        return undefined
    }
    _VideoController_setCurrentTime1(ptr: KPointer, value: number, seekMode: KInt): undefined {
        console.log("_VideoController_setCurrentTime1")
        return undefined
    }
    _VideoController_reset(ptr: KPointer): void {
        console.log("_VideoController_reset")
    }
    _WebKeyboardController_ctor(): KPointer {
        console.log("_WebKeyboardController_ctor")
        return -1
    }
    _WebKeyboardController_getFinalizer(): KPointer {
        console.log("_WebKeyboardController_getFinalizer")
        return -1
    }
    _WebKeyboardController_insertText(ptr: KPointer, text: KStringPtr): void {
        console.log("_WebKeyboardController_insertText")
    }
    _WebKeyboardController_deleteForward(ptr: KPointer, length: number): void {
        console.log("_WebKeyboardController_deleteForward")
    }
    _WebKeyboardController_deleteBackward(ptr: KPointer, length: number): void {
        console.log("_WebKeyboardController_deleteBackward")
    }
    _WebKeyboardController_sendFunctionKey(ptr: KPointer, key: number): void {
        console.log("_WebKeyboardController_sendFunctionKey")
    }
    _WebKeyboardController_close(ptr: KPointer): void {
        console.log("_WebKeyboardController_close")
    }
    _FullScreenExitHandler_ctor(): KPointer {
        console.log("_FullScreenExitHandler_ctor")
        return -1
    }
    _FullScreenExitHandler_getFinalizer(): KPointer {
        console.log("_FullScreenExitHandler_getFinalizer")
        return -1
    }
    _FullScreenExitHandler_exitFullScreen(ptr: KPointer): void {
        console.log("_FullScreenExitHandler_exitFullScreen")
    }
    _FileSelectorParam_ctor(): KPointer {
        console.log("_FileSelectorParam_ctor")
        return -1
    }
    _FileSelectorParam_getFinalizer(): KPointer {
        console.log("_FileSelectorParam_getFinalizer")
        return -1
    }
    _FileSelectorParam_getTitle(ptr: KPointer): string {
        console.log("_FileSelectorParam_getTitle")
        return ""
    }
    _FileSelectorParam_getMode(ptr: KPointer): KPointer {
        console.log("_FileSelectorParam_getMode")
        return -1
    }
    _FileSelectorParam_getAcceptType(ptr: KPointer): KInteropReturnBuffer {
        console.log("_FileSelectorParam_getAcceptType")
        return new Uint8Array()
    }
    _FileSelectorParam_isCapture(ptr: KPointer): boolean {
        console.log("_FileSelectorParam_isCapture")
        return false
    }
    _JsResult_ctor(): KPointer {
        console.log("_JsResult_ctor")
        return -1
    }
    _JsResult_getFinalizer(): KPointer {
        console.log("_JsResult_getFinalizer")
        return -1
    }
    _JsResult_handleCancel(ptr: KPointer): void {
        console.log("_JsResult_handleCancel")
    }
    _JsResult_handleConfirm(ptr: KPointer): void {
        console.log("_JsResult_handleConfirm")
    }
    _JsResult_handlePromptConfirm(ptr: KPointer, result: KStringPtr): void {
        console.log("_JsResult_handlePromptConfirm")
    }
    _FileSelectorResult_ctor(): KPointer {
        console.log("_FileSelectorResult_ctor")
        return -1
    }
    _FileSelectorResult_getFinalizer(): KPointer {
        console.log("_FileSelectorResult_getFinalizer")
        return -1
    }
    _FileSelectorResult_handleFileList(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_FileSelectorResult_handleFileList")
    }
    _HttpAuthHandler_ctor(): KPointer {
        console.log("_HttpAuthHandler_ctor")
        return -1
    }
    _HttpAuthHandler_getFinalizer(): KPointer {
        console.log("_HttpAuthHandler_getFinalizer")
        return -1
    }
    _HttpAuthHandler_confirm(ptr: KPointer, userName: KStringPtr, password: KStringPtr): boolean {
        console.log("_HttpAuthHandler_confirm")
        return false
    }
    _HttpAuthHandler_cancel(ptr: KPointer): void {
        console.log("_HttpAuthHandler_cancel")
    }
    _HttpAuthHandler_isHttpAuthInfoSaved(ptr: KPointer): boolean {
        console.log("_HttpAuthHandler_isHttpAuthInfoSaved")
        return false
    }
    _SslErrorHandler_ctor(): KPointer {
        console.log("_SslErrorHandler_ctor")
        return -1
    }
    _SslErrorHandler_getFinalizer(): KPointer {
        console.log("_SslErrorHandler_getFinalizer")
        return -1
    }
    _SslErrorHandler_handleConfirm(ptr: KPointer): void {
        console.log("_SslErrorHandler_handleConfirm")
    }
    _SslErrorHandler_handleCancel(ptr: KPointer): void {
        console.log("_SslErrorHandler_handleCancel")
    }
    _ClientAuthenticationHandler_ctor(): KPointer {
        console.log("_ClientAuthenticationHandler_ctor")
        return -1
    }
    _ClientAuthenticationHandler_getFinalizer(): KPointer {
        console.log("_ClientAuthenticationHandler_getFinalizer")
        return -1
    }
    _ClientAuthenticationHandler_confirm0(ptr: KPointer, priKeyFile: KStringPtr, certChainFile: KStringPtr): void {
        console.log("_ClientAuthenticationHandler_confirm0")
    }
    _ClientAuthenticationHandler_confirm1(ptr: KPointer, authUri: KStringPtr): void {
        console.log("_ClientAuthenticationHandler_confirm1")
    }
    _ClientAuthenticationHandler_cancel(ptr: KPointer): void {
        console.log("_ClientAuthenticationHandler_cancel")
    }
    _ClientAuthenticationHandler_ignore(ptr: KPointer): void {
        console.log("_ClientAuthenticationHandler_ignore")
    }
    _PermissionRequest_ctor(): KPointer {
        console.log("_PermissionRequest_ctor")
        return -1
    }
    _PermissionRequest_getFinalizer(): KPointer {
        console.log("_PermissionRequest_getFinalizer")
        return -1
    }
    _PermissionRequest_deny(ptr: KPointer): void {
        console.log("_PermissionRequest_deny")
    }
    _PermissionRequest_getOrigin(ptr: KPointer): string {
        console.log("_PermissionRequest_getOrigin")
        return ""
    }
    _PermissionRequest_getAccessibleResource(ptr: KPointer): KInteropReturnBuffer {
        console.log("_PermissionRequest_getAccessibleResource")
        return new Uint8Array()
    }
    _PermissionRequest_grant(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_PermissionRequest_grant")
    }
    _ScreenCaptureHandler_ctor(): KPointer {
        console.log("_ScreenCaptureHandler_ctor")
        return -1
    }
    _ScreenCaptureHandler_getFinalizer(): KPointer {
        console.log("_ScreenCaptureHandler_getFinalizer")
        return -1
    }
    _ScreenCaptureHandler_getOrigin(ptr: KPointer): string {
        console.log("_ScreenCaptureHandler_getOrigin")
        return ""
    }
    _ScreenCaptureHandler_grant(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_ScreenCaptureHandler_grant")
    }
    _ScreenCaptureHandler_deny(ptr: KPointer): void {
        console.log("_ScreenCaptureHandler_deny")
    }
    _DataResubmissionHandler_ctor(): KPointer {
        console.log("_DataResubmissionHandler_ctor")
        return -1
    }
    _DataResubmissionHandler_getFinalizer(): KPointer {
        console.log("_DataResubmissionHandler_getFinalizer")
        return -1
    }
    _DataResubmissionHandler_resend(ptr: KPointer): void {
        console.log("_DataResubmissionHandler_resend")
    }
    _DataResubmissionHandler_cancel(ptr: KPointer): void {
        console.log("_DataResubmissionHandler_cancel")
    }
    _ControllerHandler_ctor(): KPointer {
        console.log("_ControllerHandler_ctor")
        return -1
    }
    _ControllerHandler_getFinalizer(): KPointer {
        console.log("_ControllerHandler_getFinalizer")
        return -1
    }
    _ControllerHandler_setWebController(ptr: KPointer, controller: KPointer): void {
        console.log("_ControllerHandler_setWebController")
    }
    _WebContextMenuParam_ctor(): KPointer {
        console.log("_WebContextMenuParam_ctor")
        return -1
    }
    _WebContextMenuParam_getFinalizer(): KPointer {
        console.log("_WebContextMenuParam_getFinalizer")
        return -1
    }
    _WebContextMenuParam_x(ptr: KPointer): number {
        console.log("_WebContextMenuParam_x")
        return 1
    }
    _WebContextMenuParam_y(ptr: KPointer): number {
        console.log("_WebContextMenuParam_y")
        return 1
    }
    _WebContextMenuParam_getLinkUrl(ptr: KPointer): string {
        console.log("_WebContextMenuParam_getLinkUrl")
        return ""
    }
    _WebContextMenuParam_getUnfilteredLinkUrl(ptr: KPointer): string {
        console.log("_WebContextMenuParam_getUnfilteredLinkUrl")
        return ""
    }
    _WebContextMenuParam_getSourceUrl(ptr: KPointer): string {
        console.log("_WebContextMenuParam_getSourceUrl")
        return ""
    }
    _WebContextMenuParam_existsImageContents(ptr: KPointer): boolean {
        console.log("_WebContextMenuParam_existsImageContents")
        return false
    }
    _WebContextMenuParam_getMediaType(ptr: KPointer): KPointer {
        console.log("_WebContextMenuParam_getMediaType")
        return -1
    }
    _WebContextMenuParam_getSelectionText(ptr: KPointer): string {
        console.log("_WebContextMenuParam_getSelectionText")
        return ""
    }
    _WebContextMenuParam_getSourceType(ptr: KPointer): KPointer {
        console.log("_WebContextMenuParam_getSourceType")
        return -1
    }
    _WebContextMenuParam_getInputFieldType(ptr: KPointer): KPointer {
        console.log("_WebContextMenuParam_getInputFieldType")
        return -1
    }
    _WebContextMenuParam_isEditable(ptr: KPointer): boolean {
        console.log("_WebContextMenuParam_isEditable")
        return false
    }
    _WebContextMenuParam_getEditStateFlags(ptr: KPointer): number {
        console.log("_WebContextMenuParam_getEditStateFlags")
        return 1
    }
    _WebContextMenuParam_getPreviewWidth(ptr: KPointer): number {
        console.log("_WebContextMenuParam_getPreviewWidth")
        return 1
    }
    _WebContextMenuParam_getPreviewHeight(ptr: KPointer): number {
        console.log("_WebContextMenuParam_getPreviewHeight")
        return 1
    }
    _WebContextMenuResult_ctor(): KPointer {
        console.log("_WebContextMenuResult_ctor")
        return -1
    }
    _WebContextMenuResult_getFinalizer(): KPointer {
        console.log("_WebContextMenuResult_getFinalizer")
        return -1
    }
    _WebContextMenuResult_closeContextMenu(ptr: KPointer): void {
        console.log("_WebContextMenuResult_closeContextMenu")
    }
    _WebContextMenuResult_copyImage(ptr: KPointer): void {
        console.log("_WebContextMenuResult_copyImage")
    }
    _WebContextMenuResult_copy(ptr: KPointer): void {
        console.log("_WebContextMenuResult_copy")
    }
    _WebContextMenuResult_paste(ptr: KPointer): void {
        console.log("_WebContextMenuResult_paste")
    }
    _WebContextMenuResult_cut(ptr: KPointer): void {
        console.log("_WebContextMenuResult_cut")
    }
    _WebContextMenuResult_selectAll(ptr: KPointer): void {
        console.log("_WebContextMenuResult_selectAll")
    }
    _ConsoleMessage_ctor(message: KStringPtr, sourceId: KStringPtr, lineNumber: number, messageLevel: KInt): KPointer {
        console.log("_ConsoleMessage_ctor")
        return -1
    }
    _ConsoleMessage_getFinalizer(): KPointer {
        console.log("_ConsoleMessage_getFinalizer")
        return -1
    }
    _ConsoleMessage_getMessage(ptr: KPointer): string {
        console.log("_ConsoleMessage_getMessage")
        return ""
    }
    _ConsoleMessage_getSourceId(ptr: KPointer): string {
        console.log("_ConsoleMessage_getSourceId")
        return ""
    }
    _ConsoleMessage_getLineNumber(ptr: KPointer): number {
        console.log("_ConsoleMessage_getLineNumber")
        return 1
    }
    _ConsoleMessage_getMessageLevel(ptr: KPointer): KPointer {
        console.log("_ConsoleMessage_getMessageLevel")
        return -1
    }
    _WebResourceRequest_ctor(): KPointer {
        console.log("_WebResourceRequest_ctor")
        return -1
    }
    _WebResourceRequest_getFinalizer(): KPointer {
        console.log("_WebResourceRequest_getFinalizer")
        return -1
    }
    _WebResourceRequest_getRequestHeader(ptr: KPointer): KInteropReturnBuffer {
        console.log("_WebResourceRequest_getRequestHeader")
        return new Uint8Array()
    }
    _WebResourceRequest_getRequestUrl(ptr: KPointer): string {
        console.log("_WebResourceRequest_getRequestUrl")
        return ""
    }
    _WebResourceRequest_isRequestGesture(ptr: KPointer): boolean {
        console.log("_WebResourceRequest_isRequestGesture")
        return false
    }
    _WebResourceRequest_isMainFrame(ptr: KPointer): boolean {
        console.log("_WebResourceRequest_isMainFrame")
        return false
    }
    _WebResourceRequest_isRedirect(ptr: KPointer): boolean {
        console.log("_WebResourceRequest_isRedirect")
        return false
    }
    _WebResourceRequest_getRequestMethod(ptr: KPointer): string {
        console.log("_WebResourceRequest_getRequestMethod")
        return ""
    }
    _WebResourceResponse_ctor(): KPointer {
        console.log("_WebResourceResponse_ctor")
        return -1
    }
    _WebResourceResponse_getFinalizer(): KPointer {
        console.log("_WebResourceResponse_getFinalizer")
        return -1
    }
    _WebResourceResponse_getResponseData(ptr: KPointer): string {
        console.log("_WebResourceResponse_getResponseData")
        return ""
    }
    _WebResourceResponse_getResponseDataEx(ptr: KPointer): KPointer {
        console.log("_WebResourceResponse_getResponseDataEx")
        return -1
    }
    _WebResourceResponse_getResponseEncoding(ptr: KPointer): string {
        console.log("_WebResourceResponse_getResponseEncoding")
        return ""
    }
    _WebResourceResponse_getResponseMimeType(ptr: KPointer): string {
        console.log("_WebResourceResponse_getResponseMimeType")
        return ""
    }
    _WebResourceResponse_getReasonMessage(ptr: KPointer): string {
        console.log("_WebResourceResponse_getReasonMessage")
        return ""
    }
    _WebResourceResponse_getResponseHeader(ptr: KPointer): KInteropReturnBuffer {
        console.log("_WebResourceResponse_getResponseHeader")
        return new Uint8Array()
    }
    _WebResourceResponse_getResponseCode(ptr: KPointer): number {
        console.log("_WebResourceResponse_getResponseCode")
        return 1
    }
    _WebResourceResponse_setResponseData(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebResourceResponse_setResponseData")
    }
    _WebResourceResponse_setResponseEncoding(ptr: KPointer, encoding: KStringPtr): void {
        console.log("_WebResourceResponse_setResponseEncoding")
    }
    _WebResourceResponse_setResponseMimeType(ptr: KPointer, mimeType: KStringPtr): void {
        console.log("_WebResourceResponse_setResponseMimeType")
    }
    _WebResourceResponse_setReasonMessage(ptr: KPointer, reason: KStringPtr): void {
        console.log("_WebResourceResponse_setReasonMessage")
    }
    _WebResourceResponse_setResponseHeader(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_WebResourceResponse_setResponseHeader")
    }
    _WebResourceResponse_setResponseCode(ptr: KPointer, code: number): void {
        console.log("_WebResourceResponse_setResponseCode")
    }
    _WebResourceResponse_setResponseIsReady(ptr: KPointer, IsReady: KInt): void {
        console.log("_WebResourceResponse_setResponseIsReady")
    }
    _WebResourceResponse_getResponseIsReady(ptr: KPointer): boolean {
        console.log("_WebResourceResponse_getResponseIsReady")
        return false
    }
    _WebResourceError_ctor(): KPointer {
        console.log("_WebResourceError_ctor")
        return -1
    }
    _WebResourceError_getFinalizer(): KPointer {
        console.log("_WebResourceError_getFinalizer")
        return -1
    }
    _WebResourceError_getErrorInfo(ptr: KPointer): string {
        console.log("_WebResourceError_getErrorInfo")
        return ""
    }
    _WebResourceError_getErrorCode(ptr: KPointer): number {
        console.log("_WebResourceError_getErrorCode")
        return 1
    }
    _JsGeolocation_ctor(): KPointer {
        console.log("_JsGeolocation_ctor")
        return -1
    }
    _JsGeolocation_getFinalizer(): KPointer {
        console.log("_JsGeolocation_getFinalizer")
        return -1
    }
    _JsGeolocation_invoke(ptr: KPointer, origin: KStringPtr, allow: KInt, retain: KInt): void {
        console.log("_JsGeolocation_invoke")
    }
    _WebCookie_ctor(): KPointer {
        console.log("_WebCookie_ctor")
        return -1
    }
    _WebCookie_getFinalizer(): KPointer {
        console.log("_WebCookie_getFinalizer")
        return -1
    }
    _WebCookie_setCookie(ptr: KPointer): undefined {
        console.log("_WebCookie_setCookie")
        return undefined
    }
    _WebCookie_saveCookie(ptr: KPointer): undefined {
        console.log("_WebCookie_saveCookie")
        return undefined
    }
    _EventResult_ctor(): KPointer {
        console.log("_EventResult_ctor")
        return -1
    }
    _EventResult_getFinalizer(): KPointer {
        console.log("_EventResult_getFinalizer")
        return -1
    }
    _EventResult_setGestureEventResult(ptr: KPointer, result: KInt): void {
        console.log("_EventResult_setGestureEventResult")
    }
    _WebController_ctor(): KPointer {
        console.log("_WebController_ctor")
        return -1
    }
    _WebController_getFinalizer(): KPointer {
        console.log("_WebController_getFinalizer")
        return -1
    }
    _WebController_onInactive(ptr: KPointer): void {
        console.log("_WebController_onInactive")
    }
    _WebController_onActive(ptr: KPointer): void {
        console.log("_WebController_onActive")
    }
    _WebController_zoom(ptr: KPointer, factor: number): void {
        console.log("_WebController_zoom")
    }
    _WebController_clearHistory(ptr: KPointer): void {
        console.log("_WebController_clearHistory")
    }
    _WebController_runJavaScript(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): undefined {
        console.log("_WebController_runJavaScript")
        return undefined
    }
    _WebController_loadData(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): undefined {
        console.log("_WebController_loadData")
        return undefined
    }
    _WebController_loadUrl(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): undefined {
        console.log("_WebController_loadUrl")
        return undefined
    }
    _WebController_refresh(ptr: KPointer): undefined {
        console.log("_WebController_refresh")
        return undefined
    }
    _WebController_stop(ptr: KPointer): undefined {
        console.log("_WebController_stop")
        return undefined
    }
    _WebController_registerJavaScriptProxy(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): undefined {
        console.log("_WebController_registerJavaScriptProxy")
        return undefined
    }
    _WebController_deleteJavaScriptRegister(ptr: KPointer, name: KStringPtr): undefined {
        console.log("_WebController_deleteJavaScriptRegister")
        return undefined
    }
    _WebController_getHitTest(ptr: KPointer): KPointer {
        console.log("_WebController_getHitTest")
        return -1
    }
    _WebController_requestFocus(ptr: KPointer): undefined {
        console.log("_WebController_requestFocus")
        return undefined
    }
    _WebController_accessBackward(ptr: KPointer): boolean {
        console.log("_WebController_accessBackward")
        return false
    }
    _WebController_accessForward(ptr: KPointer): boolean {
        console.log("_WebController_accessForward")
        return false
    }
    _WebController_accessStep(ptr: KPointer, step: number): boolean {
        console.log("_WebController_accessStep")
        return false
    }
    _WebController_backward(ptr: KPointer): undefined {
        console.log("_WebController_backward")
        return undefined
    }
    _WebController_forward(ptr: KPointer): undefined {
        console.log("_WebController_forward")
        return undefined
    }
    _WebController_getCookieManager(ptr: KPointer): KPointer {
        console.log("_WebController_getCookieManager")
        return -1
    }
    _XComponentController_ctor(): KPointer {
        console.log("_XComponentController_ctor")
        return -1
    }
    _XComponentController_getFinalizer(): KPointer {
        console.log("_XComponentController_getFinalizer")
        return -1
    }
    _XComponentController_getXComponentSurfaceId(ptr: KPointer): string {
        console.log("_XComponentController_getXComponentSurfaceId")
        return ""
    }
    _XComponentController_getXComponentContext(ptr: KPointer): KPointer {
        console.log("_XComponentController_getXComponentContext")
        return -1
    }
    _XComponentController_setXComponentSurfaceSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_XComponentController_setXComponentSurfaceSize")
    }
    _XComponentController_setXComponentSurfaceRect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_XComponentController_setXComponentSurfaceRect")
    }
    _XComponentController_getXComponentSurfaceRect(ptr: KPointer): KInteropReturnBuffer {
        console.log("_XComponentController_getXComponentSurfaceRect")
        return new Uint8Array()
    }
    _XComponentController_setXComponentSurfaceRotation(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_XComponentController_setXComponentSurfaceRotation")
    }
    _XComponentController_getXComponentSurfaceRotation(ptr: KPointer): KInteropReturnBuffer {
        console.log("_XComponentController_getXComponentSurfaceRotation")
        return new Uint8Array()
    }
    _XComponentController_onSurfaceCreated(ptr: KPointer, surfaceId: KStringPtr): void {
        console.log("_XComponentController_onSurfaceCreated")
    }
    _XComponentController_onSurfaceChanged(ptr: KPointer, surfaceId: KStringPtr, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_XComponentController_onSurfaceChanged")
    }
    _XComponentController_onSurfaceDestroyed(ptr: KPointer, surfaceId: KStringPtr): void {
        console.log("_XComponentController_onSurfaceDestroyed")
    }
    _XComponentController_startImageAnalyzer(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_XComponentController_startImageAnalyzer")
        return -1
    }
    _XComponentController_stopImageAnalyzer(ptr: KPointer): void {
        console.log("_XComponentController_stopImageAnalyzer")
    }
    _WaterFlowSections_ctor(): KPointer {
        console.log("_WaterFlowSections_ctor")
        return -1
    }
    _WaterFlowSections_getFinalizer(): KPointer {
        console.log("_WaterFlowSections_getFinalizer")
        return -1
    }
    _WaterFlowSections_splice(ptr: KPointer, start: number, thisArray: Uint8Array, thisLength: int32): boolean {
        console.log("_WaterFlowSections_splice")
        return false
    }
    _WaterFlowSections_push(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): boolean {
        console.log("_WaterFlowSections_push")
        return false
    }
    _WaterFlowSections_update(ptr: KPointer, sectionIndex: number, thisArray: Uint8Array, thisLength: int32): boolean {
        console.log("_WaterFlowSections_update")
        return false
    }
    _WaterFlowSections_values(ptr: KPointer): KInteropReturnBuffer {
        console.log("_WaterFlowSections_values")
        return new Uint8Array()
    }
    _WaterFlowSections_length(ptr: KPointer): number {
        console.log("_WaterFlowSections_length")
        return 1
    }
    _UIExtensionProxy_ctor(): KPointer {
        console.log("_UIExtensionProxy_ctor")
        return -1
    }
    _UIExtensionProxy_getFinalizer(): KPointer {
        console.log("_UIExtensionProxy_getFinalizer")
        return -1
    }
    _UIExtensionProxy_send(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_UIExtensionProxy_send")
    }
    _UIExtensionProxy_sendSync(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KInteropReturnBuffer {
        console.log("_UIExtensionProxy_sendSync")
        return new Uint8Array()
    }
    _UIExtensionProxy_onAsyncReceiverRegister(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_UIExtensionProxy_onAsyncReceiverRegister")
    }
    _UIExtensionProxy_onSyncReceiverRegister(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_UIExtensionProxy_onSyncReceiverRegister")
    }
    _UIExtensionProxy_offAsyncReceiverRegister(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_UIExtensionProxy_offAsyncReceiverRegister")
    }
    _UIExtensionProxy_offSyncReceiverRegister(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_UIExtensionProxy_offSyncReceiverRegister")
    }
    _StyledString_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_StyledString_ctor")
        return -1
    }
    _StyledString_getFinalizer(): KPointer {
        console.log("_StyledString_getFinalizer")
        return -1
    }
    _StyledString_getString(ptr: KPointer): string {
        console.log("_StyledString_getString")
        return ""
    }
    _StyledString_getStyles(ptr: KPointer, start: number, length: number, thisArray: Uint8Array, thisLength: int32): KInteropReturnBuffer {
        console.log("_StyledString_getStyles")
        return new Uint8Array()
    }
    _StyledString_equals(ptr: KPointer, other: KPointer): boolean {
        console.log("_StyledString_equals")
        return false
    }
    _StyledString_subStyledString(ptr: KPointer, start: number, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_StyledString_subStyledString")
        return -1
    }
    _StyledString_fromHtml(html: KStringPtr, thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_StyledString_fromHtml")
        return -1
    }
    _StyledString_toHtml(styledString: KPointer): string {
        console.log("_StyledString_toHtml")
        return ""
    }
    _StyledString_marshalling(styledString: KPointer): KInteropReturnBuffer {
        console.log("_StyledString_marshalling")
        return new Uint8Array()
    }
    _StyledString_unmarshalling(thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_StyledString_unmarshalling")
        return -1
    }
    _StyledString_getLength(ptr: KPointer): number {
        console.log("_StyledString_getLength")
        return 1
    }
    _TextStyle_styled_string_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_TextStyle_styled_string_ctor")
        return -1
    }
    _TextStyle_styled_string_getFinalizer(): KPointer {
        console.log("_TextStyle_styled_string_getFinalizer")
        return -1
    }
    _TextStyle_styled_string_getFontFamily(ptr: KPointer): string {
        console.log("_TextStyle_styled_string_getFontFamily")
        return ""
    }
    _TextStyle_styled_string_getFontSize(ptr: KPointer): number {
        console.log("_TextStyle_styled_string_getFontSize")
        return 1
    }
    _TextStyle_styled_string_getFontWeight(ptr: KPointer): number {
        console.log("_TextStyle_styled_string_getFontWeight")
        return 1
    }
    _TextStyle_styled_string_getFontStyle(ptr: KPointer): KPointer {
        console.log("_TextStyle_styled_string_getFontStyle")
        return -1
    }
    _DecorationStyle_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_DecorationStyle_ctor")
        return -1
    }
    _DecorationStyle_getFinalizer(): KPointer {
        console.log("_DecorationStyle_getFinalizer")
        return -1
    }
    _DecorationStyle_getType(ptr: KPointer): KPointer {
        console.log("_DecorationStyle_getType")
        return -1
    }
    _DecorationStyle_getStyle(ptr: KPointer): KPointer {
        console.log("_DecorationStyle_getStyle")
        return -1
    }
    _BaselineOffsetStyle_ctor(value: KPointer): KPointer {
        console.log("_BaselineOffsetStyle_ctor")
        return -1
    }
    _BaselineOffsetStyle_getFinalizer(): KPointer {
        console.log("_BaselineOffsetStyle_getFinalizer")
        return -1
    }
    _BaselineOffsetStyle_getBaselineOffset(ptr: KPointer): number {
        console.log("_BaselineOffsetStyle_getBaselineOffset")
        return 1
    }
    _LetterSpacingStyle_ctor(value: KPointer): KPointer {
        console.log("_LetterSpacingStyle_ctor")
        return -1
    }
    _LetterSpacingStyle_getFinalizer(): KPointer {
        console.log("_LetterSpacingStyle_getFinalizer")
        return -1
    }
    _LetterSpacingStyle_getLetterSpacing(ptr: KPointer): number {
        console.log("_LetterSpacingStyle_getLetterSpacing")
        return 1
    }
    _TextShadowStyle_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_TextShadowStyle_ctor")
        return -1
    }
    _TextShadowStyle_getFinalizer(): KPointer {
        console.log("_TextShadowStyle_getFinalizer")
        return -1
    }
    _TextShadowStyle_getTextShadow(ptr: KPointer): KInteropReturnBuffer {
        console.log("_TextShadowStyle_getTextShadow")
        return new Uint8Array()
    }
    _BackgroundColorStyle_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_BackgroundColorStyle_ctor")
        return -1
    }
    _BackgroundColorStyle_getFinalizer(): KPointer {
        console.log("_BackgroundColorStyle_getFinalizer")
        return -1
    }
    _GestureStyle_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_GestureStyle_ctor")
        return -1
    }
    _GestureStyle_getFinalizer(): KPointer {
        console.log("_GestureStyle_getFinalizer")
        return -1
    }
    _ParagraphStyle_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_ParagraphStyle_ctor")
        return -1
    }
    _ParagraphStyle_getFinalizer(): KPointer {
        console.log("_ParagraphStyle_getFinalizer")
        return -1
    }
    _ParagraphStyle_getTextAlign(ptr: KPointer): KPointer {
        console.log("_ParagraphStyle_getTextAlign")
        return -1
    }
    _ParagraphStyle_getTextIndent(ptr: KPointer): number {
        console.log("_ParagraphStyle_getTextIndent")
        return 1
    }
    _ParagraphStyle_getMaxLines(ptr: KPointer): number {
        console.log("_ParagraphStyle_getMaxLines")
        return 1
    }
    _ParagraphStyle_getOverflow(ptr: KPointer): KPointer {
        console.log("_ParagraphStyle_getOverflow")
        return -1
    }
    _ParagraphStyle_getWordBreak(ptr: KPointer): KPointer {
        console.log("_ParagraphStyle_getWordBreak")
        return -1
    }
    _LineHeightStyle_ctor(lineHeight: KPointer): KPointer {
        console.log("_LineHeightStyle_ctor")
        return -1
    }
    _LineHeightStyle_getFinalizer(): KPointer {
        console.log("_LineHeightStyle_getFinalizer")
        return -1
    }
    _LineHeightStyle_getLineHeight(ptr: KPointer): number {
        console.log("_LineHeightStyle_getLineHeight")
        return 1
    }
    _UrlStyle_ctor(url: KStringPtr): KPointer {
        console.log("_UrlStyle_ctor")
        return -1
    }
    _UrlStyle_getFinalizer(): KPointer {
        console.log("_UrlStyle_getFinalizer")
        return -1
    }
    _UrlStyle_getUrl(ptr: KPointer): string {
        console.log("_UrlStyle_getUrl")
        return ""
    }
    _MutableStyledString_ctor(): KPointer {
        console.log("_MutableStyledString_ctor")
        return -1
    }
    _MutableStyledString_getFinalizer(): KPointer {
        console.log("_MutableStyledString_getFinalizer")
        return -1
    }
    _MutableStyledString_replaceString(ptr: KPointer, start: number, length: number, other: KStringPtr): void {
        console.log("_MutableStyledString_replaceString")
    }
    _MutableStyledString_insertString(ptr: KPointer, start: number, other: KStringPtr): void {
        console.log("_MutableStyledString_insertString")
    }
    _MutableStyledString_removeString(ptr: KPointer, start: number, length: number): void {
        console.log("_MutableStyledString_removeString")
    }
    _MutableStyledString_replaceStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_MutableStyledString_replaceStyle")
    }
    _MutableStyledString_setStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_MutableStyledString_setStyle")
    }
    _MutableStyledString_removeStyle(ptr: KPointer, start: number, length: number, styledKey: KInt): void {
        console.log("_MutableStyledString_removeStyle")
    }
    _MutableStyledString_removeStyles(ptr: KPointer, start: number, length: number): void {
        console.log("_MutableStyledString_removeStyles")
    }
    _MutableStyledString_clearStyles(ptr: KPointer): void {
        console.log("_MutableStyledString_clearStyles")
    }
    _MutableStyledString_replaceStyledString(ptr: KPointer, start: number, length: number, other: KPointer): void {
        console.log("_MutableStyledString_replaceStyledString")
    }
    _MutableStyledString_insertStyledString(ptr: KPointer, start: number, other: KPointer): void {
        console.log("_MutableStyledString_insertStyledString")
    }
    _MutableStyledString_appendStyledString(ptr: KPointer, other: KPointer): void {
        console.log("_MutableStyledString_appendStyledString")
    }
    _ImageAttachment_ctor(thisArray: Uint8Array, thisLength: int32): KPointer {
        console.log("_ImageAttachment_ctor")
        return -1
    }
    _ImageAttachment_getFinalizer(): KPointer {
        console.log("_ImageAttachment_getFinalizer")
        return -1
    }
    _ImageAttachment_getValue(ptr: KPointer): KPointer {
        console.log("_ImageAttachment_getValue")
        return -1
    }
    _ImageAttachment_getVerticalAlign(ptr: KPointer): KPointer {
        console.log("_ImageAttachment_getVerticalAlign")
        return -1
    }
    _ImageAttachment_getObjectFit(ptr: KPointer): KPointer {
        console.log("_ImageAttachment_getObjectFit")
        return -1
    }
    _CustomSpan_ctor(): KPointer {
        console.log("_CustomSpan_ctor")
        return -1
    }
    _CustomSpan_getFinalizer(): KPointer {
        console.log("_CustomSpan_getFinalizer")
        return -1
    }
    _CustomSpan_onMeasure(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): KInteropReturnBuffer {
        console.log("_CustomSpan_onMeasure")
        return new Uint8Array()
    }
    _CustomSpan_onDraw(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_CustomSpan_onDraw")
    }
    _CustomSpan_invalidate(ptr: KPointer): void {
        console.log("_CustomSpan_invalidate")
    }
    _LinearIndicatorController_ctor(): KPointer {
        console.log("_LinearIndicatorController_ctor")
        return -1
    }
    _LinearIndicatorController_getFinalizer(): KPointer {
        console.log("_LinearIndicatorController_getFinalizer")
        return -1
    }
    _LinearIndicatorController_setProgress(ptr: KPointer, index: number, progress: number): void {
        console.log("_LinearIndicatorController_setProgress")
    }
    _LinearIndicatorController_start(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        console.log("_LinearIndicatorController_start")
    }
    _LinearIndicatorController_pause(ptr: KPointer): void {
        console.log("_LinearIndicatorController_pause")
    }
    _LinearIndicatorController_stop(ptr: KPointer): void {
        console.log("_LinearIndicatorController_stop")
    }
    _GlobalScope_getContext(thisArray: Uint8Array, thisLength: int32): KInteropReturnBuffer {
        console.log("_GlobalScope_getContext")
        return new Uint8Array()
    }
    _GlobalScope_postCardAction(thisArray: Uint8Array, thisLength: int32): void {
        console.log("_GlobalScope_postCardAction")
    }
    _GlobalScope_dollar_r(value: KStringPtr, thisArray: Uint8Array, thisLength: int32): KInteropReturnBuffer {
        console.log("_GlobalScope_dollar_r")
        return new Uint8Array()
    }
    _GlobalScope_dollar_rawfile(value: KStringPtr): KInteropReturnBuffer {
        console.log("_GlobalScope_dollar_rawfile")
        return new Uint8Array()
    }
    _GlobalScope_animateTo(thisArray: Uint8Array, thisLength: int32): void {
        console.log("_GlobalScope_animateTo")
    }
    _GlobalScope_animateToImmediately(thisArray: Uint8Array, thisLength: int32): void {
        console.log("_GlobalScope_animateToImmediately")
    }
    _GlobalScope_vp2px(value: number): number {
        console.log("_GlobalScope_vp2px")
        return 1
    }
    _GlobalScope_px2vp(value: number): number {
        console.log("_GlobalScope_px2vp")
        return 1
    }
    _GlobalScope_fp2px(value: number): number {
        console.log("_GlobalScope_fp2px")
        return 1
    }
    _GlobalScope_px2fp(value: number): number {
        console.log("_GlobalScope_px2fp")
        return 1
    }
    _GlobalScope_lpx2px(value: number): number {
        console.log("_GlobalScope_lpx2px")
        return 1
    }
    _GlobalScope_px2lpx(value: number): number {
        console.log("_GlobalScope_px2lpx")
        return 1
    }
    _GlobalScope_getInspectorNodes(): KPointer {
        console.log("_GlobalScope_getInspectorNodes")
        return -1
    }
    _GlobalScope_getInspectorNodeById(id: number): KPointer {
        console.log("_GlobalScope_getInspectorNodeById")
        return -1
    }
    _GlobalScope_setAppBgColor(value: KStringPtr): void {
        console.log("_GlobalScope_setAppBgColor")
    }
    _GlobalScope_Profiler_registerVsyncCallback(thisArray: Uint8Array, thisLength: int32): void {
        console.log("_GlobalScope_Profiler_registerVsyncCallback")
    }
    _GlobalScope_Profiler_unregisterVsyncCallback(): void {
        console.log("_GlobalScope_Profiler_unregisterVsyncCallback")
    }
    _GlobalScope_cursorControl_setCursor(value: KInt): void {
        console.log("_GlobalScope_cursorControl_setCursor")
    }
    _GlobalScope_cursorControl_restoreDefault(): void {
        console.log("_GlobalScope_cursorControl_restoreDefault")
    }
    _GlobalScope_focusControl_requestFocus(value: KStringPtr): boolean {
        console.log("_GlobalScope_focusControl_requestFocus")
        return false
    }
}