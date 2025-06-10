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

import { KInt, KLong, KBoolean, KFloat, KUInt, KStringPtr, KPointer, KNativePointer, KInt32ArrayPtr, KUint8ArrayPtr, KFloat32ArrayPtr, pointer, KInteropReturnBuffer, NativeBuffer, KSerializerBuffer, loadNativeModuleLibrary } from "@koalaui/interop"
import { int32, int64, float32 } from "@koalaui/common"
import { Length } from "../../component/units"

export class ArkUIGeneratedNativeModule {
    static {
        loadNativeModuleLibrary("ArkUIGeneratedNativeModule")
    }
    @ani.unsafe.Direct
    native static _Root_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _CommonMethod_requestFrame(): void
    @ani.unsafe.Direct
    native static _ComponentRoot_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _AbilityComponent_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _AbilityComponentInterface_setAbilityComponentOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AbilityComponentAttribute_onConnect(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AbilityComponentAttribute_onDisconnect(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexer_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _AlphabetIndexerInterface_setAlphabetIndexerOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_onSelected(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_color(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_selectedColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_popupColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_selectedBackgroundColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_popupBackground(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_popupSelectedColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_popupUnselectedColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_popupItemBackgroundColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_usingPopup(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_selectedFont(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_popupFont(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_popupItemFont(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_itemSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_font(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_onSelect(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_onRequestPopupData(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_onPopupSelect(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_selected(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_popupPosition(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_autoCollapse(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_popupItemBorderRadius(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_itemBorderRadius(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_popupBackgroundBlurStyle(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_popupTitleBackground(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_enableHapticFeedback(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_alignStyle(ptr: KPointer, value: KInt, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute__onChangeEvent_selected(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Animator_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Quick
    native static _AnimatorInterface_setAnimatorOptions(ptr: KPointer, value: KStringPtr): void
    @ani.unsafe.Direct
    native static _AnimatorAttribute_state(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _AnimatorAttribute_duration(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _AnimatorAttribute_curve(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _AnimatorAttribute_delay(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _AnimatorAttribute_fillMode(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _AnimatorAttribute_iterations(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _AnimatorAttribute_playMode(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _AnimatorAttribute_motion(ptr: KPointer, value: KPointer): void
    @ani.unsafe.Direct
    native static _AnimatorAttribute_onStart(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AnimatorAttribute_onPause(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AnimatorAttribute_onRepeat(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AnimatorAttribute_onCancel(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AnimatorAttribute_onFinish(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AnimatorAttribute_onFrame(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Badge_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _BadgeInterface_setBadgeOptions0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _BadgeInterface_setBadgeOptions1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Blank_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _BlankInterface_setBlankOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _BlankAttribute_color(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Button_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _ButtonInterface_setButtonOptions0(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _ButtonInterface_setButtonOptions1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ButtonInterface_setButtonOptions2(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ButtonAttribute_type(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ButtonAttribute_stateEffect(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ButtonAttribute_buttonStyle(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ButtonAttribute_controlSize(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ButtonAttribute_role(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ButtonAttribute_fontColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _ButtonAttribute_fontSize(ptr: KPointer, value: Length): void
    @ani.unsafe.Direct
    native static _ButtonAttribute_fontWeight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ButtonAttribute_fontStyle(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ButtonAttribute_fontFamily(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ButtonAttribute_contentModifier(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ButtonAttribute_labelStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Calendar_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _CalendarInterface_setCalendarOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CalendarAttribute_showLunar(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _CalendarAttribute_showHoliday(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _CalendarAttribute_needSlide(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _CalendarAttribute_startOfWeek(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _CalendarAttribute_offDays(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _CalendarAttribute_direction(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _CalendarAttribute_currentDayStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CalendarAttribute_nonCurrentDayStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CalendarAttribute_todayStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CalendarAttribute_weekStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CalendarAttribute_workStateStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CalendarAttribute_onSelectChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CalendarAttribute_onRequestData(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CalendarPicker_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _CalendarPickerInterface_setCalendarPickerOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CalendarPickerAttribute_textStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CalendarPickerAttribute_onChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CalendarPickerAttribute_edgeAlign(ptr: KPointer, alignType: KInt, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Canvas_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _CanvasInterface_setCanvasOptions0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CanvasInterface_setCanvasOptions1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CanvasAttribute_onReady(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CanvasAttribute_enableAnalyzer(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _Checkbox_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _CheckboxInterface_setCheckboxOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CheckboxAttribute_select(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _CheckboxAttribute_selectedColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CheckboxAttribute_shape(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _CheckboxAttribute_unselectedColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CheckboxAttribute_mark(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CheckboxAttribute_onChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CheckboxAttribute_contentModifier(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CheckboxAttribute__onChangeEvent_select(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CheckboxGroup_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _CheckboxGroupInterface_setCheckboxGroupOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CheckboxGroupAttribute_selectAll(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _CheckboxGroupAttribute_selectedColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CheckboxGroupAttribute_unselectedColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CheckboxGroupAttribute_mark(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CheckboxGroupAttribute_onChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CheckboxGroupAttribute_checkboxShape(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _CheckboxGroupAttribute__onChangeEvent_selectAll(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Circle_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _CircleInterface_setCircleOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Column_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _ColumnInterface_setColumnOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ColumnAttribute_alignItems(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ColumnAttribute_justifyContent(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ColumnAttribute_pointLight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ColumnAttribute_reverse(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ColumnSplit_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _ColumnSplitInterface_setColumnSplitOptions(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _ColumnSplitAttribute_resizeable(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ColumnSplitAttribute_divider(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Quick
    native static _CommonMethod_width(ptr: KPointer, value: Length): void
    @ani.unsafe.Quick
    native static _CommonMethod_height(ptr: KPointer, value: Length): void
    @ani.unsafe.Direct
    native static _CommonMethod_drawModifier(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_responseRegion(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_mouseResponseRegion(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_size(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_constraintSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_touchable(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _CommonMethod_hitTestBehavior(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _CommonMethod_onChildTouchTest(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_layoutWeight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_chainWeight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_padding(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_safeAreaPadding(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_margin(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_backgroundColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_pixelRound(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_backgroundImageSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_backgroundImagePosition(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_backgroundEffect(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_backgroundImageResizable(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_foregroundEffect(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_visualEffect(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_backgroundFilter(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_foregroundFilter(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_compositingFilter(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_opacity(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_border(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_borderStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_borderWidth(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_borderColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_borderRadius(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_borderImage(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_outline(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_outlineStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_outlineWidth(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_outlineColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_outlineRadius(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_foregroundColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_onClick0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_onClick1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32, distanceThreshold: number): void
    @ani.unsafe.Direct
    native static _CommonMethod_onHover(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_onAccessibilityHover(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_hoverEffect(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _CommonMethod_onMouse(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_onTouch(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_onKeyEvent(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_onKeyPreIme(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_focusable(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _CommonMethod_onFocus(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_onBlur(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_tabIndex(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _CommonMethod_defaultFocus(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _CommonMethod_groupDefaultFocus(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _CommonMethod_focusOnTouch(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _CommonMethod_focusBox(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_animation(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_transition0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_transition1(ptr: KPointer, effect: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_motionBlur(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_brightness(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _CommonMethod_contrast(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _CommonMethod_grayscale(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _CommonMethod_colorBlend(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_saturate(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _CommonMethod_sepia(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _CommonMethod_invert(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_hueRotate(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_useShadowBatching(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _CommonMethod_useEffect0(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _CommonMethod_useEffect1(ptr: KPointer, useEffect: KInt, effectType: KInt): void
    @ani.unsafe.Direct
    native static _CommonMethod_renderGroup(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _CommonMethod_freeze(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _CommonMethod_translate(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_scale(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_gridSpan(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _CommonMethod_gridOffset(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _CommonMethod_rotate(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_transform(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_onAppear(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_onDisAppear(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_onAttach(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_onDetach(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_onAreaChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_visibility(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _CommonMethod_flexGrow(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _CommonMethod_flexShrink(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _CommonMethod_flexBasis(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_alignSelf(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _CommonMethod_displayPriority(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _CommonMethod_zIndex(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _CommonMethod_direction(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _CommonMethod_align(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _CommonMethod_position(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_markAnchor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_offset(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_enabled(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _CommonMethod_useSizeType(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_alignRules0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_alignRules1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_aspectRatio(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _CommonMethod_clickEffect(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_onDragStart(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_onDragEnter(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_onDragMove(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_onDragLeave(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_onDrop(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_onDragEnd(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_allowDrop(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_draggable(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _CommonMethod_dragPreview(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_onPreDrag(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_linearGradient(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_sweepGradient(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_radialGradient(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_motionPath(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_shadow(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_clip0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_clip1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_clipShape(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_mask0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_mask1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_maskShape(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _CommonMethod_key(ptr: KPointer, value: KStringPtr): void
    @ani.unsafe.Quick
    native static _CommonMethod_id(ptr: KPointer, value: KStringPtr): void
    @ani.unsafe.Quick
    native static _CommonMethod_geometryTransition0(ptr: KPointer, value: KStringPtr): void
    @ani.unsafe.Quick
    native static _CommonMethod_geometryTransition1(ptr: KPointer, id: KStringPtr, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_stateStyles(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_restoreId(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _CommonMethod_sphericalEffect(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _CommonMethod_lightUpEffect(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _CommonMethod_pixelStretchEffect(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_accessibilityGroup0(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _CommonMethod_accessibilityGroup1(ptr: KPointer, isGroup: KInt, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _CommonMethod_accessibilityText0(ptr: KPointer, value: KStringPtr): void
    @ani.unsafe.Direct
    native static _CommonMethod_accessibilityText1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _CommonMethod_accessibilityTextHint(ptr: KPointer, value: KStringPtr): void
    @ani.unsafe.Quick
    native static _CommonMethod_accessibilityDescription0(ptr: KPointer, value: KStringPtr): void
    @ani.unsafe.Direct
    native static _CommonMethod_accessibilityDescription1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _CommonMethod_accessibilityLevel(ptr: KPointer, value: KStringPtr): void
    @ani.unsafe.Direct
    native static _CommonMethod_accessibilityVirtualNode(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_accessibilityChecked(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _CommonMethod_accessibilitySelected(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _CommonMethod_obscured(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _CommonMethod_reuseId(ptr: KPointer, value: KStringPtr): void
    @ani.unsafe.Direct
    native static _CommonMethod_renderFit(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _CommonMethod_gestureModifier(ptr: KPointer, value: KPointer): void
    @ani.unsafe.Direct
    native static _CommonMethod_backgroundBrightness(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_onGestureJudgeBegin(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_onGestureRecognizerJudgeBegin0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_onGestureRecognizerJudgeBegin1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32, exposeInnerGesture: KInt): void
    @ani.unsafe.Direct
    native static _CommonMethod_shouldBuiltInRecognizerParallelWith(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_monopolizeEvents(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _CommonMethod_onTouchIntercept(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_onSizeChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _CommonMethod_customProperty(ptr: KPointer, name: KStringPtr, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_expandSafeArea(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_background(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_backgroundImage(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_backgroundBlurStyle(ptr: KPointer, value: KInt, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_foregroundBlurStyle(ptr: KPointer, value: KInt, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _CommonMethod_focusScopeId0(ptr: KPointer, id: KStringPtr, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _CommonMethod_focusScopeId1(ptr: KPointer, id: KStringPtr, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _CommonMethod_focusScopePriority(ptr: KPointer, scopeId: KStringPtr, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_gesture(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_priorityGesture(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_parallelGesture(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_blur(ptr: KPointer, value: number, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_linearGradientBlur(ptr: KPointer, value: number, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_systemBarEffect(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _CommonMethod_backdropBlur(ptr: KPointer, value: number, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _CommonMethod_sharedTransition(ptr: KPointer, id: KStringPtr, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_chainMode(ptr: KPointer, direction: KInt, style: KInt): void
    @ani.unsafe.Direct
    native static _CommonMethod_dragPreviewOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_overlay(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_blendMode(ptr: KPointer, value: KInt, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_advancedBlendMode(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_bindPopup(ptr: KPointer, show: KInt, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_bindMenu0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_bindMenu1(ptr: KPointer, isShow: KInt, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_bindContextMenu0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32, responseType: KInt): void
    @ani.unsafe.Direct
    native static _CommonMethod_bindContextMenu1(ptr: KPointer, isShown: KInt, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_bindContentCover0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_bindContentCover1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_bindSheet(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_onVisibleAreaChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_keyboardShortcut(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonShapeMethod_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _CommonShapeMethod_stroke(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonShapeMethod_fill(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonShapeMethod_strokeDashOffset(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonShapeMethod_strokeLineCap(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _CommonShapeMethod_strokeLineJoin(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _CommonShapeMethod_strokeMiterLimit(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonShapeMethod_strokeOpacity(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonShapeMethod_fillOpacity(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _CommonShapeMethod_strokeWidth(ptr: KPointer, value: Length): void
    @ani.unsafe.Direct
    native static _CommonShapeMethod_antiAlias(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _CommonShapeMethod_strokeDashArray(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Common_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _CommonInterface_setCommonOptions(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _ScrollableCommonMethod_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _ScrollableCommonMethod_scrollBar(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ScrollableCommonMethod_scrollBarColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollableCommonMethod_scrollBarWidth(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollableCommonMethod_nestedScroll(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollableCommonMethod_enableScrollInteraction(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ScrollableCommonMethod_friction(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollableCommonMethod_onScroll(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollableCommonMethod_onWillScroll(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollableCommonMethod_onReachStart(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollableCommonMethod_onReachEnd(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollableCommonMethod_onScrollStart(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollableCommonMethod_onScrollStop(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollableCommonMethod_flingSpeedLimit(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _ScrollableCommonMethod_clipContent(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollableCommonMethod_edgeEffect(ptr: KPointer, edgeEffect: KInt, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollableCommonMethod_fadingEdge(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Component3D_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _Component3DInterface_setComponent3DOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Component3DAttribute_environment(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Component3DAttribute_shader(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Component3DAttribute_shaderImageTexture(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Component3DAttribute_shaderInputBuffer(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _Component3DAttribute_renderWidth(ptr: KPointer, value: Length): void
    @ani.unsafe.Quick
    native static _Component3DAttribute_renderHeight(ptr: KPointer, value: Length): void
    @ani.unsafe.Direct
    native static _Component3DAttribute_customRender(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32, selfRenderUpdate: KInt): void
    @ani.unsafe.Direct
    native static _ContainerSpan_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _ContainerSpanInterface_setContainerSpanOptions(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _ContainerSpanAttribute_textBackgroundStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Counter_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _CounterInterface_setCounterOptions(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _CounterAttribute_onInc(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CounterAttribute_onDec(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CounterAttribute_enableDec(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _CounterAttribute_enableInc(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _DataPanel_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _DataPanelInterface_setDataPanelOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _DataPanelAttribute_closeEffect(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _DataPanelAttribute_valueColors(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _DataPanelAttribute_trackBackgroundColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _DataPanelAttribute_strokeWidth(ptr: KPointer, value: Length): void
    @ani.unsafe.Direct
    native static _DataPanelAttribute_trackShadow(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _DataPanelAttribute_contentModifier(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _DatePicker_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _DatePickerInterface_setDatePickerOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _DatePickerAttribute_lunar(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _DatePickerAttribute_disappearTextStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _DatePickerAttribute_textStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _DatePickerAttribute_selectedTextStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _DatePickerAttribute_onChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _DatePickerAttribute_onDateChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _DatePickerAttribute__onChangeEvent_selected(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Divider_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _DividerInterface_setDividerOptions(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _DividerAttribute_vertical(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _DividerAttribute_color(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _DividerAttribute_strokeWidth(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _DividerAttribute_lineCap(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _EffectComponent_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _EffectComponentInterface_setEffectComponentOptions(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _Ellipse_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _EllipseInterface_setEllipseOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _EmbeddedComponent_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _EmbeddedComponentInterface_setEmbeddedComponentOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32, type: KInt): void
    @ani.unsafe.Direct
    native static _EmbeddedComponentAttribute_onTerminated(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _EmbeddedComponentAttribute_onError(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Flex_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _FlexInterface_setFlexOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _FlexAttribute_pointLight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _FlowItem_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _FlowItemInterface_setFlowItemOptions(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _FolderStack_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _FolderStackInterface_setFolderStackOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _FolderStackAttribute_alignContent(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _FolderStackAttribute_onFolderStateChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _FolderStackAttribute_onHoverStatusChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _FolderStackAttribute_enableAnimation(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _FolderStackAttribute_autoHalfFold(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _FormComponent_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _FormComponentInterface_setFormComponentOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _FormComponentAttribute_size(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _FormComponentAttribute_moduleName(ptr: KPointer, value: KStringPtr): void
    @ani.unsafe.Direct
    native static _FormComponentAttribute_dimension(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _FormComponentAttribute_allowUpdate(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _FormComponentAttribute_visibility(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _FormComponentAttribute_onAcquired(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _FormComponentAttribute_onError(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _FormComponentAttribute_onRouter(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _FormComponentAttribute_onUninstall(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _FormComponentAttribute_onLoad(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _FormLink_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _FormLinkInterface_setFormLinkOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Gauge_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _GaugeInterface_setGaugeOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GaugeAttribute_value(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _GaugeAttribute_startAngle(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _GaugeAttribute_endAngle(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _GaugeAttribute_colors(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _GaugeAttribute_strokeWidth(ptr: KPointer, value: Length): void
    @ani.unsafe.Direct
    native static _GaugeAttribute_description(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GaugeAttribute_trackShadow(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GaugeAttribute_indicator(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GaugeAttribute_privacySensitive(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GaugeAttribute_contentModifier(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Grid_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _GridInterface_setGridOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _GridAttribute_columnsTemplate(ptr: KPointer, value: KStringPtr): void
    @ani.unsafe.Quick
    native static _GridAttribute_rowsTemplate(ptr: KPointer, value: KStringPtr): void
    @ani.unsafe.Quick
    native static _GridAttribute_columnsGap(ptr: KPointer, value: Length): void
    @ani.unsafe.Quick
    native static _GridAttribute_rowsGap(ptr: KPointer, value: Length): void
    @ani.unsafe.Direct
    native static _GridAttribute_scrollBarWidth(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridAttribute_scrollBarColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridAttribute_scrollBar(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _GridAttribute_onScrollBarUpdate(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridAttribute_onScrollIndex(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridAttribute_cachedCount0(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _GridAttribute_cachedCount1(ptr: KPointer, count: number, show: KInt): void
    @ani.unsafe.Direct
    native static _GridAttribute_editMode(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _GridAttribute_multiSelectable(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _GridAttribute_maxCount(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _GridAttribute_minCount(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _GridAttribute_cellLength(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _GridAttribute_layoutDirection(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _GridAttribute_supportAnimation(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _GridAttribute_onItemDragStart(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridAttribute_onItemDragEnter(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridAttribute_onItemDragMove(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridAttribute_onItemDragLeave(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridAttribute_onItemDrop(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridAttribute_nestedScroll(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridAttribute_enableScrollInteraction(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _GridAttribute_friction(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridAttribute_alignItems(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridAttribute_onScroll(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridAttribute_onDidScroll(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridAttribute_onReachStart(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridAttribute_onReachEnd(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridAttribute_onScrollStart(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridAttribute_onScrollStop(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridAttribute_onScrollFrameBegin(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridAttribute_edgeEffect(ptr: KPointer, value: KInt, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridItem_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _GridItemInterface_setGridItemOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridItemAttribute_rowStart(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _GridItemAttribute_rowEnd(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _GridItemAttribute_columnStart(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _GridItemAttribute_columnEnd(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _GridItemAttribute_forceRebuild(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _GridItemAttribute_selectable(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _GridItemAttribute_selected(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _GridItemAttribute_onSelect(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridItemAttribute__onChangeEvent_selected(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridCol_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _GridColInterface_setGridColOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridColAttribute_span(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridColAttribute_gridColOffset(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridColAttribute_order(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridContainer_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _GridContainerInterface_setGridContainerOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridRow_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _GridRowInterface_setGridRowOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridRowAttribute_onBreakpointChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridRowAttribute_alignItems(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _Hyperlink_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _HyperlinkInterface_setHyperlinkOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _HyperlinkAttribute_color(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Image_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _ImageInterface_setImageOptions0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageInterface_setImageOptions1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageInterface_setImageOptions2(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAttribute_alt(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAttribute_matchTextDirection(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ImageAttribute_fitOriginalSize(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ImageAttribute_fillColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAttribute_objectFit(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ImageAttribute_objectRepeat(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ImageAttribute_autoResize(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ImageAttribute_renderMode(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ImageAttribute_dynamicRangeMode(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ImageAttribute_interpolation(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ImageAttribute_sourceSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAttribute_syncLoad(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ImageAttribute_colorFilter(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAttribute_copyOption(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ImageAttribute_draggable(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ImageAttribute_pointLight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAttribute_edgeAntialiasing(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _ImageAttribute_onComplete(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAttribute_onError(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAttribute_onFinish(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAttribute_enableAnalyzer(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ImageAttribute_analyzerConfig(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAttribute_resizable(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAttribute_privacySensitive(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ImageAttribute_enhancedImageQuality(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAnimator_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _ImageAnimatorInterface_setImageAnimatorOptions(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _ImageAnimatorAttribute_images(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAnimatorAttribute_state(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ImageAnimatorAttribute_duration(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _ImageAnimatorAttribute_reverse(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ImageAnimatorAttribute_fixedSize(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ImageAnimatorAttribute_preDecode(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _ImageAnimatorAttribute_fillMode(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ImageAnimatorAttribute_iterations(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _ImageAnimatorAttribute_onStart(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAnimatorAttribute_onPause(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAnimatorAttribute_onRepeat(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAnimatorAttribute_onCancel(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAnimatorAttribute_onFinish(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageSpan_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _ImageSpanInterface_setImageSpanOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageSpanAttribute_verticalAlign(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ImageSpanAttribute_colorFilter(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageSpanAttribute_objectFit(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ImageSpanAttribute_onComplete(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageSpanAttribute_onError(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageSpanAttribute_alt(ptr: KPointer, value: KPointer): void
    @ani.unsafe.Direct
    native static _Line_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _LineInterface_setLineOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _LineAttribute_startPoint(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _LineAttribute_endPoint(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _List_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _ListInterface_setListOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_alignListItem(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ListAttribute_listDirection(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ListAttribute_scrollBar(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ListAttribute_contentStartOffset(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _ListAttribute_contentEndOffset(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _ListAttribute_divider(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_editMode(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ListAttribute_multiSelectable(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ListAttribute_cachedCount0(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _ListAttribute_cachedCount1(ptr: KPointer, count: number, show: KInt): void
    @ani.unsafe.Direct
    native static _ListAttribute_chainAnimation(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ListAttribute_chainAnimationOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_sticky(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ListAttribute_scrollSnapAlign(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ListAttribute_nestedScroll(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_enableScrollInteraction(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ListAttribute_friction(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_childrenMainSize(ptr: KPointer, value: KPointer): void
    @ani.unsafe.Direct
    native static _ListAttribute_maintainVisibleContentPosition(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ListAttribute_onScroll(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_onScrollIndex(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_onScrollVisibleContentChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_onDidScroll(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_onReachStart(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_onReachEnd(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_onScrollStart(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_onScrollStop(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_onItemDelete(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_onItemMove(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_onItemDragStart(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_onItemDragEnter(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_onItemDragMove(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_onItemDragLeave(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_onItemDrop(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_onScrollFrameBegin(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_lanes(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_edgeEffect(ptr: KPointer, value: KInt, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListItem_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _ListItemInterface_setListItemOptions0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListItemInterface_setListItemOptions1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListItemAttribute_sticky(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ListItemAttribute_editable(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListItemAttribute_selectable(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ListItemAttribute_selected(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ListItemAttribute_swipeAction(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListItemAttribute_onSelect(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListItemAttribute__onChangeEvent_selected(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListItemGroup_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _ListItemGroupInterface_setListItemGroupOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListItemGroupAttribute_divider(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListItemGroupAttribute_childrenMainSize(ptr: KPointer, value: KPointer): void
    @ani.unsafe.Direct
    native static _LoadingProgress_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _LoadingProgressInterface_setLoadingProgressOptions(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _LoadingProgressAttribute_color(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _LoadingProgressAttribute_enableLoading(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _LoadingProgressAttribute_contentModifier(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _LocationButton_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _LocationButtonInterface_setLocationButtonOptions0(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _LocationButtonInterface_setLocationButtonOptions1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _LocationButtonAttribute_onClick(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Marquee_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _MarqueeInterface_setMarqueeOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MarqueeAttribute_fontColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _MarqueeAttribute_fontSize(ptr: KPointer, value: Length): void
    @ani.unsafe.Direct
    native static _MarqueeAttribute_allowScale(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _MarqueeAttribute_fontWeight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MarqueeAttribute_fontFamily(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MarqueeAttribute_marqueeUpdateStrategy(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _MarqueeAttribute_onStart(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MarqueeAttribute_onBounce(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MarqueeAttribute_onFinish(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MediaCachedImage_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _MediaCachedImageInterface_setMediaCachedImageOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Menu_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _MenuInterface_setMenuOptions(ptr: KPointer): void
    @ani.unsafe.Quick
    native static _MenuAttribute_fontSize(ptr: KPointer, value: Length): void
    @ani.unsafe.Direct
    native static _MenuAttribute_font(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MenuAttribute_fontColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MenuAttribute_radius(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MenuAttribute_menuItemDivider(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MenuAttribute_menuItemGroupDivider(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MenuAttribute_subMenuExpandingMode(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _MenuItem_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _MenuItemInterface_setMenuItemOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MenuItemAttribute_selected(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _MenuItemAttribute_selectIcon(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MenuItemAttribute_onChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MenuItemAttribute_contentFont(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MenuItemAttribute_contentFontColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MenuItemAttribute_labelFont(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MenuItemAttribute_labelFontColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MenuItemAttribute__onChangeEvent_selected(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MenuItemGroup_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _MenuItemGroupInterface_setMenuItemGroupOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestination_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _NavDestinationInterface_setNavDestinationOptions(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_hideTitleBar0(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_hideTitleBar1(ptr: KPointer, hide: KInt, animated: KInt): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_onShown(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_onHidden(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_onBackPressed(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_mode(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_backButtonIcon(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_menus(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_onReady(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_onWillAppear(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_onWillDisappear(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_onWillShow(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_onWillHide(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_systemBarStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_recoverable(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_systemTransition(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_title(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_toolbarConfiguration(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_hideToolBar(ptr: KPointer, hide: KInt, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_ignoreLayoutSafeArea(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavRouter_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _NavRouterInterface_setNavRouterOptions0(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _NavRouterInterface_setNavRouterOptions1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavRouterAttribute_onStateChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavRouterAttribute_mode(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _Navigator_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _NavigatorInterface_setNavigatorOptions0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavigatorInterface_setNavigatorOptions1(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _NavigatorAttribute_active(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _NavigatorAttribute_type(ptr: KPointer, value: KInt): void
    @ani.unsafe.Quick
    native static _NavigatorAttribute_target(ptr: KPointer, value: KStringPtr): void
    @ani.unsafe.Direct
    native static _NavigatorAttribute_params(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NodeContainer_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _NodeContainerInterface_setNodeContainerOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Panel_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _PanelInterface_setPanelOptions(ptr: KPointer, show: KInt): void
    @ani.unsafe.Direct
    native static _PanelAttribute_mode(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _PanelAttribute_type(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _PanelAttribute_dragBar(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _PanelAttribute_customHeight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _PanelAttribute_fullHeight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _PanelAttribute_halfHeight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _PanelAttribute_miniHeight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _PanelAttribute_show(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _PanelAttribute_backgroundMask(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _PanelAttribute_showCloseIcon(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _PanelAttribute_onChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _PanelAttribute_onHeightChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _PanelAttribute__onChangeEvent_mode(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _PasteButton_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _PasteButtonInterface_setPasteButtonOptions0(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _PasteButtonInterface_setPasteButtonOptions1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _PasteButtonAttribute_onClick(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Path_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _PathInterface_setPathOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _PathAttribute_commands(ptr: KPointer, value: KStringPtr): void
    @ani.unsafe.Direct
    native static _PatternLock_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _PatternLockInterface_setPatternLockOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _PatternLockAttribute_sideLength(ptr: KPointer, value: Length): void
    @ani.unsafe.Quick
    native static _PatternLockAttribute_circleRadius(ptr: KPointer, value: Length): void
    @ani.unsafe.Direct
    native static _PatternLockAttribute_backgroundColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _PatternLockAttribute_regularColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _PatternLockAttribute_selectedColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _PatternLockAttribute_activeColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _PatternLockAttribute_pathColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _PatternLockAttribute_pathStrokeWidth(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _PatternLockAttribute_onPatternComplete(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _PatternLockAttribute_autoReset(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _PatternLockAttribute_onDotConnect(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _PatternLockAttribute_activateCircleStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _PluginComponent_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _PluginComponentInterface_setPluginComponentOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _PluginComponentAttribute_onComplete(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _PluginComponentAttribute_onError(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Polygon_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _PolygonInterface_setPolygonOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _PolygonAttribute_points(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Polyline_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _PolylineInterface_setPolylineOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _PolylineAttribute_points(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Progress_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _ProgressInterface_setProgressOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ProgressAttribute_value(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _ProgressAttribute_color(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ProgressAttribute_style(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ProgressAttribute_privacySensitive(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ProgressAttribute_contentModifier(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _QRCode_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Quick
    native static _QRCodeInterface_setQRCodeOptions(ptr: KPointer, value: KStringPtr): void
    @ani.unsafe.Direct
    native static _QRCodeAttribute_color(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _QRCodeAttribute_backgroundColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _QRCodeAttribute_contentOpacity(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Radio_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _RadioInterface_setRadioOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RadioAttribute_checked(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _RadioAttribute_onChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RadioAttribute_radioStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RadioAttribute_contentModifier(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RadioAttribute__onChangeEvent_checked(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Rating_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _RatingInterface_setRatingOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RatingAttribute_stars(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _RatingAttribute_stepSize(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _RatingAttribute_starStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RatingAttribute_onChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RatingAttribute_contentModifier(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RatingAttribute__onChangeEvent_rating(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Rect_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _RectInterface_setRectOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RectAttribute_radiusWidth(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RectAttribute_radiusHeight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RectAttribute_radius(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Refresh_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _RefreshInterface_setRefreshOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RefreshAttribute_onStateChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RefreshAttribute_onRefreshing(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RefreshAttribute_refreshOffset(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _RefreshAttribute_pullToRefresh(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _RefreshAttribute_onOffsetChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RefreshAttribute_pullDownRatio(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RefreshAttribute__onChangeEvent_refreshing(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RelativeContainer_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _RelativeContainerInterface_setRelativeContainerOptions(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _RelativeContainerAttribute_guideLine(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RelativeContainerAttribute_barrier0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RelativeContainerAttribute_barrier1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditor_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _RichEditorInterface_setRichEditorOptions0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorInterface_setRichEditorOptions1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_onReady(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_onSelect(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_onSelectionChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_aboutToIMEInput(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_onIMEInputComplete(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_onDidIMEInput(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_aboutToDelete(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_onDeleteComplete(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_copyOptions(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_onPaste(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_enableDataDetector(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_enablePreviewText(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_dataDetectorConfig(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_caretColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_selectedBackgroundColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_onEditingChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_enterKeyType(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_onSubmit(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_onWillChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_onDidChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_onCut(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_onCopy(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_editMenuOptions(ptr: KPointer, value: KPointer): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_enableKeyboardOnFocus(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_enableHapticFeedback(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_barState(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_bindSelectionMenu(ptr: KPointer, spanType: KInt, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_customKeyboard(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_placeholder(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichText_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Quick
    native static _RichTextInterface_setRichTextOptions(ptr: KPointer, content: KStringPtr): void
    @ani.unsafe.Direct
    native static _RichTextAttribute_onStart(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichTextAttribute_onComplete(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RootScene_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _RootSceneInterface_setRootSceneOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Row_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _RowInterface_setRowOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RowAttribute_alignItems(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _RowAttribute_justifyContent(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _RowAttribute_pointLight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RowAttribute_reverse(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RowSplit_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _RowSplitInterface_setRowSplitOptions(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _RowSplitAttribute_resizeable(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _SaveButton_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _SaveButtonInterface_setSaveButtonOptions0(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _SaveButtonInterface_setSaveButtonOptions1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SaveButtonAttribute_onClick(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Screen_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _ScreenInterface_setScreenOptions(ptr: KPointer, screenId: number): void
    @ani.unsafe.Direct
    native static _Scroll_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _ScrollInterface_setScrollOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollAttribute_scrollable(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ScrollAttribute_onScroll(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollAttribute_onWillScroll(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollAttribute_onDidScroll(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollAttribute_onScrollEdge(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollAttribute_onScrollStart(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollAttribute_onScrollEnd(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollAttribute_onScrollStop(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollAttribute_scrollBar(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ScrollAttribute_scrollBarColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollAttribute_scrollBarWidth(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollAttribute_onScrollFrameBegin(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollAttribute_nestedScroll(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollAttribute_enableScrollInteraction(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ScrollAttribute_friction(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollAttribute_scrollSnap(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollAttribute_enablePaging(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ScrollAttribute_initialOffset(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollAttribute_edgeEffect(ptr: KPointer, edgeEffect: KInt, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollBar_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _ScrollBarInterface_setScrollBarOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollBarAttribute_enableNestedScroll(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Search_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _SearchInterface_setSearchOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_fontColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_searchIcon(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_cancelButton(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _SearchAttribute_textIndent(ptr: KPointer, value: Length): void
    @ani.unsafe.Direct
    native static _SearchAttribute_onEditChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_selectedBackgroundColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_caretStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_placeholderColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_placeholderFont(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_textFont(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_enterKeyType(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _SearchAttribute_onSubmit0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_onSubmit1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_onChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_onTextSelectionChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_onContentScroll(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_onCopy(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_onCut(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_onPaste(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_copyOption(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _SearchAttribute_maxLength(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _SearchAttribute_textAlign(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _SearchAttribute_enableKeyboardOnFocus(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _SearchAttribute_selectionMenuHidden(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _SearchAttribute_minFontSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_maxFontSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_decoration(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_letterSpacing(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_lineHeight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_type(ptr: KPointer, value: KInt): void
    @ani.unsafe.Quick
    native static _SearchAttribute_fontFeature(ptr: KPointer, value: KStringPtr): void
    @ani.unsafe.Direct
    native static _SearchAttribute_onWillInsert(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_onDidInsert(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_onWillDelete(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_onDidDelete(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_editMenuOptions(ptr: KPointer, value: KPointer): void
    @ani.unsafe.Direct
    native static _SearchAttribute_enablePreviewText(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _SearchAttribute_enableHapticFeedback(ptr: KPointer, value: KInt): void
    @ani.unsafe.Quick
    native static _SearchAttribute_searchButton(ptr: KPointer, value: KStringPtr, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_inputFilter(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_customKeyboard(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute__onChangeEvent_value(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SecurityComponentMethod_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Quick
    native static _SecurityComponentMethod_iconSize(ptr: KPointer, value: Length): void
    @ani.unsafe.Direct
    native static _SecurityComponentMethod_layoutDirection(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _SecurityComponentMethod_position(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SecurityComponentMethod_markAnchor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SecurityComponentMethod_offset(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _SecurityComponentMethod_fontSize(ptr: KPointer, value: Length): void
    @ani.unsafe.Direct
    native static _SecurityComponentMethod_fontStyle(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _SecurityComponentMethod_fontWeight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SecurityComponentMethod_fontFamily(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SecurityComponentMethod_fontColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SecurityComponentMethod_iconColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SecurityComponentMethod_backgroundColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SecurityComponentMethod_borderStyle(ptr: KPointer, value: KInt): void
    @ani.unsafe.Quick
    native static _SecurityComponentMethod_borderWidth(ptr: KPointer, value: Length): void
    @ani.unsafe.Direct
    native static _SecurityComponentMethod_borderColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _SecurityComponentMethod_borderRadius(ptr: KPointer, value: Length): void
    @ani.unsafe.Direct
    native static _SecurityComponentMethod_padding(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _SecurityComponentMethod_textIconSpace(ptr: KPointer, value: Length): void
    @ani.unsafe.Quick
    native static _SecurityComponentMethod_key(ptr: KPointer, value: KStringPtr): void
    @ani.unsafe.Quick
    native static _SecurityComponentMethod_width(ptr: KPointer, value: Length): void
    @ani.unsafe.Quick
    native static _SecurityComponentMethod_height(ptr: KPointer, value: Length): void
    @ani.unsafe.Direct
    native static _SecurityComponentMethod_size(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SecurityComponentMethod_constraintSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Select_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _SelectInterface_setSelectOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SelectAttribute_selected(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SelectAttribute_value(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SelectAttribute_font(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SelectAttribute_fontColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SelectAttribute_selectedOptionBgColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SelectAttribute_selectedOptionFont(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SelectAttribute_selectedOptionFontColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SelectAttribute_optionBgColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SelectAttribute_optionFont(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SelectAttribute_optionFontColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SelectAttribute_onSelect(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _SelectAttribute_space(ptr: KPointer, value: Length): void
    @ani.unsafe.Direct
    native static _SelectAttribute_arrowPosition(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _SelectAttribute_optionWidth(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _SelectAttribute_optionHeight(ptr: KPointer, value: Length): void
    @ani.unsafe.Direct
    native static _SelectAttribute_menuBackgroundColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SelectAttribute_menuBackgroundBlurStyle(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _SelectAttribute_controlSize(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _SelectAttribute_menuItemContentModifier(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SelectAttribute_divider(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SelectAttribute_menuAlign(ptr: KPointer, alignType: KInt, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SelectAttribute__onChangeEvent_selected(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SelectAttribute__onChangeEvent_value(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Shape_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _ShapeInterface_setShapeOptions0(ptr: KPointer, value: KPointer): void
    @ani.unsafe.Direct
    native static _ShapeInterface_setShapeOptions1(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _ShapeAttribute_viewPort(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ShapeAttribute_stroke(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ShapeAttribute_fill(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ShapeAttribute_strokeDashOffset(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ShapeAttribute_strokeDashArray(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ShapeAttribute_strokeLineCap(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ShapeAttribute_strokeLineJoin(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ShapeAttribute_strokeMiterLimit(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ShapeAttribute_strokeOpacity(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ShapeAttribute_fillOpacity(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ShapeAttribute_strokeWidth(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ShapeAttribute_antiAlias(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _ShapeAttribute_mesh(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32, column: number, row: number): void
    @ani.unsafe.Direct
    native static _Slider_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _SliderInterface_setSliderOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SliderAttribute_blockColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SliderAttribute_trackColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SliderAttribute_selectedColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _SliderAttribute_minLabel(ptr: KPointer, value: KStringPtr): void
    @ani.unsafe.Quick
    native static _SliderAttribute_maxLabel(ptr: KPointer, value: KStringPtr): void
    @ani.unsafe.Direct
    native static _SliderAttribute_showSteps(ptr: KPointer, value: KInt): void
    @ani.unsafe.Quick
    native static _SliderAttribute_trackThickness(ptr: KPointer, value: Length): void
    @ani.unsafe.Direct
    native static _SliderAttribute_onChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SliderAttribute_blockBorderColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _SliderAttribute_blockBorderWidth(ptr: KPointer, value: Length): void
    @ani.unsafe.Direct
    native static _SliderAttribute_stepColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _SliderAttribute_trackBorderRadius(ptr: KPointer, value: Length): void
    @ani.unsafe.Quick
    native static _SliderAttribute_selectedBorderRadius(ptr: KPointer, value: Length): void
    @ani.unsafe.Direct
    native static _SliderAttribute_blockSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SliderAttribute_blockStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _SliderAttribute_stepSize(ptr: KPointer, value: Length): void
    @ani.unsafe.Direct
    native static _SliderAttribute_sliderInteractionMode(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _SliderAttribute_minResponsiveDistance(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _SliderAttribute_contentModifier(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SliderAttribute_slideRange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SliderAttribute_showTips(ptr: KPointer, value: KInt, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SliderAttribute__onChangeEvent_value(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _BaseSpan_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _BaseSpan_textBackgroundStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _BaseSpan_baselineOffset(ptr: KPointer, value: KPointer): void
    @ani.unsafe.Direct
    native static _Span_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _SpanInterface_setSpanOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SpanAttribute_font(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SpanAttribute_fontColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SpanAttribute_fontSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SpanAttribute_fontStyle(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _SpanAttribute_fontWeight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SpanAttribute_fontFamily(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SpanAttribute_decoration(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SpanAttribute_letterSpacing(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SpanAttribute_textCase(ptr: KPointer, value: KInt): void
    @ani.unsafe.Quick
    native static _SpanAttribute_lineHeight(ptr: KPointer, value: Length): void
    @ani.unsafe.Direct
    native static _SpanAttribute_textShadow(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Stack_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _StackInterface_setStackOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _StackAttribute_alignContent(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _StackAttribute_pointLight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Stepper_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _StepperInterface_setStepperOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _StepperAttribute_onFinish(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _StepperAttribute_onSkip(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _StepperAttribute_onChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _StepperAttribute_onNext(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _StepperAttribute_onPrevious(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _StepperAttribute__onChangeEvent_index(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _StepperItem_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _StepperItemInterface_setStepperItemOptions(ptr: KPointer): void
    @ani.unsafe.Quick
    native static _StepperItemAttribute_prevLabel(ptr: KPointer, value: KStringPtr): void
    @ani.unsafe.Quick
    native static _StepperItemAttribute_nextLabel(ptr: KPointer, value: KStringPtr): void
    @ani.unsafe.Direct
    native static _StepperItemAttribute_status(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Swiper_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _SwiperInterface_setSwiperOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_index(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_autoPlay(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_interval(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_indicator0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_indicator1(ptr: KPointer, value: KPointer): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_loop(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_duration(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_vertical(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_itemSpace(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_displayMode(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_cachedCount(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_effectMode(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_disableSwipe(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_curve(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_onChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_indicatorStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_onAnimationStart(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_onAnimationEnd(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_onGestureSwipe(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_nestedScroll(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_customContentTransition(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_onContentDidScroll(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_indicatorInteractive(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_displayArrow(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_displayCount(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _SwiperAttribute_prevMargin(ptr: KPointer, value: Length, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _SwiperAttribute_nextMargin(ptr: KPointer, value: Length, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SwiperAttribute__onChangeEvent_index(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _IndicatorComponent_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _IndicatorComponentInterface_setIndicatorComponentOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _IndicatorComponentAttribute_initialIndex(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _IndicatorComponentAttribute_count(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _IndicatorComponentAttribute_style(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _IndicatorComponentAttribute_loop(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _IndicatorComponentAttribute_vertical(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _IndicatorComponentAttribute_onChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SymbolGlyph_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _SymbolGlyphInterface_setSymbolGlyphOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SymbolGlyphAttribute_fontSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SymbolGlyphAttribute_fontColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SymbolGlyphAttribute_fontWeight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SymbolGlyphAttribute_effectStrategy(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _SymbolGlyphAttribute_renderingStrategy(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _SymbolGlyphAttribute_symbolEffect0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SymbolGlyphAttribute_symbolEffect1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SymbolSpan_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _SymbolSpanInterface_setSymbolSpanOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SymbolSpanAttribute_fontSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SymbolSpanAttribute_fontColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SymbolSpanAttribute_fontWeight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SymbolSpanAttribute_effectStrategy(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _SymbolSpanAttribute_renderingStrategy(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _Tabs_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _TabsInterface_setTabsOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabsAttribute_vertical(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TabsAttribute_barPosition(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TabsAttribute_scrollable(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TabsAttribute_barMode0(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TabsAttribute_barMode1(ptr: KPointer, value: KInt, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _TabsAttribute_barWidth(ptr: KPointer, value: Length): void
    @ani.unsafe.Quick
    native static _TabsAttribute_barHeight(ptr: KPointer, value: Length): void
    @ani.unsafe.Direct
    native static _TabsAttribute_animationDuration(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _TabsAttribute_animationMode(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabsAttribute_edgeEffect(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabsAttribute_onChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabsAttribute_onTabBarClick(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabsAttribute_onAnimationStart(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabsAttribute_onAnimationEnd(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabsAttribute_onGestureSwipe(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabsAttribute_fadingEdge(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TabsAttribute_divider(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabsAttribute_barOverlap(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TabsAttribute_barBackgroundColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabsAttribute_barGridAlign(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabsAttribute_customContentTransition(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabsAttribute_barBackgroundBlurStyle0(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TabsAttribute_barBackgroundBlurStyle1(ptr: KPointer, style: KInt, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabsAttribute_barBackgroundEffect(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabsAttribute_onContentWillChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabsAttribute_barModeScrollable(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabsAttribute__onChangeEvent_index(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabContent_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _TabContentInterface_setTabContentOptions(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _TabContentAttribute_tabBar0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabContentAttribute_tabBar1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabContentAttribute_onWillShow(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabContentAttribute_onWillHide(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Text_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _TextInterface_setTextOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_font0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_font1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_fontColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_fontSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_minFontSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_maxFontSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_minFontScale(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_maxFontScale(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_fontStyle(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextAttribute_fontWeight0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_fontWeight1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_lineSpacing(ptr: KPointer, value: KPointer): void
    @ani.unsafe.Direct
    native static _TextAttribute_textAlign(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextAttribute_lineHeight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_textOverflow(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_fontFamily(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_maxLines(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _TextAttribute_decoration(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_letterSpacing(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_textCase(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextAttribute_baselineOffset(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_copyOption(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextAttribute_draggable(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextAttribute_textShadow(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_heightAdaptivePolicy(ptr: KPointer, value: KInt): void
    @ani.unsafe.Quick
    native static _TextAttribute_textIndent(ptr: KPointer, value: Length): void
    @ani.unsafe.Direct
    native static _TextAttribute_wordBreak(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextAttribute_lineBreakStrategy(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextAttribute_onCopy(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_caretColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_selectedBackgroundColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_ellipsisMode(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextAttribute_enableDataDetector(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextAttribute_dataDetectorConfig(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_onTextSelectionChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _TextAttribute_fontFeature(ptr: KPointer, value: KStringPtr): void
    @ani.unsafe.Direct
    native static _TextAttribute_privacySensitive(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextAttribute_textSelectable(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextAttribute_editMenuOptions(ptr: KPointer, value: KPointer): void
    @ani.unsafe.Direct
    native static _TextAttribute_halfLeading(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextAttribute_enableHapticFeedback(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextAttribute_selection(ptr: KPointer, selectionStart: number, selectionEnd: number): void
    @ani.unsafe.Direct
    native static _TextAttribute_bindSelectionMenu(ptr: KPointer, spanType: KInt, thisArray: KSerializerBuffer, thisLength: int32, responseType: KInt): void
    @ani.unsafe.Direct
    native static _TextArea_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _TextAreaInterface_setTextAreaOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_placeholderColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_placeholderFont(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_enterKeyType(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_textAlign(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_caretColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_fontColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _TextAreaAttribute_fontSize(ptr: KPointer, value: Length): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_fontStyle(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_fontWeight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_fontFamily(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_textOverflow(ptr: KPointer, value: KInt): void
    @ani.unsafe.Quick
    native static _TextAreaAttribute_textIndent(ptr: KPointer, value: Length): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_caretStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_selectedBackgroundColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_onSubmit0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_onSubmit1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_onChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_onTextSelectionChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_onContentScroll(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_onEditChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_onCopy(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_onCut(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_onPaste(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_copyOption(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_enableKeyboardOnFocus(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_maxLength(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_style(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_barState(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_selectionMenuHidden(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_minFontSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_maxFontSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_heightAdaptivePolicy(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_maxLines(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_wordBreak(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_lineBreakStrategy(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_decoration(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_letterSpacing(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_lineSpacing(ptr: KPointer, value: KPointer): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_lineHeight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_type(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_enableAutoFill(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_contentType(ptr: KPointer, value: KInt): void
    @ani.unsafe.Quick
    native static _TextAreaAttribute_fontFeature(ptr: KPointer, value: KStringPtr): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_onWillInsert(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_onDidInsert(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_onWillDelete(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_onDidDelete(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_editMenuOptions(ptr: KPointer, value: KPointer): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_enablePreviewText(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_enableHapticFeedback(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_inputFilter(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_showCounter(ptr: KPointer, value: KInt, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_customKeyboard(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute__onChangeEvent_text(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextClock_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _TextClockInterface_setTextClockOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _TextClockAttribute_format(ptr: KPointer, value: KStringPtr): void
    @ani.unsafe.Direct
    native static _TextClockAttribute_onDateChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextClockAttribute_fontColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _TextClockAttribute_fontSize(ptr: KPointer, value: Length): void
    @ani.unsafe.Direct
    native static _TextClockAttribute_fontStyle(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextClockAttribute_fontWeight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextClockAttribute_fontFamily(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextClockAttribute_textShadow(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _TextClockAttribute_fontFeature(ptr: KPointer, value: KStringPtr): void
    @ani.unsafe.Direct
    native static _TextClockAttribute_contentModifier(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextClockAttribute_dateTimeOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInput_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _TextInputInterface_setTextInputOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_type(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_contentType(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_placeholderColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_textOverflow(ptr: KPointer, value: KInt): void
    @ani.unsafe.Quick
    native static _TextInputAttribute_textIndent(ptr: KPointer, value: Length): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_placeholderFont(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_enterKeyType(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_caretColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_onEditChanged(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_onEditChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_onSubmit(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_onChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_onTextSelectionChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_onContentScroll(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_maxLength(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_fontColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _TextInputAttribute_fontSize(ptr: KPointer, value: Length): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_fontStyle(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_fontWeight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_fontFamily(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_onCopy(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_onCut(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_onPaste(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_copyOption(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_showPasswordIcon(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_textAlign(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_style(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_caretStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_selectedBackgroundColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_caretPosition(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_enableKeyboardOnFocus(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_passwordIcon(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_showError(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_showUnit(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_showUnderline(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_underlineColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_selectionMenuHidden(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_barState(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_maxLines(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_wordBreak(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_lineBreakStrategy(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_cancelButton0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_cancelButton1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_selectAll(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_minFontSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_maxFontSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_heightAdaptivePolicy(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_enableAutoFill(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_decoration(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_letterSpacing(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_lineHeight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _TextInputAttribute_passwordRules(ptr: KPointer, value: KStringPtr): void
    @ani.unsafe.Quick
    native static _TextInputAttribute_fontFeature(ptr: KPointer, value: KStringPtr): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_showPassword(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_onSecurityStateChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_onWillInsert(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_onDidInsert(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_onWillDelete(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_onDidDelete(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_editMenuOptions(ptr: KPointer, value: KPointer): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_enablePreviewText(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_enableHapticFeedback(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_inputFilter(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_customKeyboard(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_showCounter(ptr: KPointer, value: KInt, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute__onChangeEvent_text(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextPicker_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _TextPickerInterface_setTextPickerOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextPickerAttribute_defaultPickerItemHeight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextPickerAttribute_canLoop(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextPickerAttribute_disappearTextStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextPickerAttribute_textStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextPickerAttribute_selectedTextStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextPickerAttribute_onAccept(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextPickerAttribute_onCancel(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextPickerAttribute_onChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextPickerAttribute_selectedIndex(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextPickerAttribute_divider(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _TextPickerAttribute_gradientHeight(ptr: KPointer, value: Length): void
    @ani.unsafe.Direct
    native static _TextPickerAttribute__onChangeEvent_selected(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextPickerAttribute__onChangeEvent_value(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextTimer_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _TextTimerInterface_setTextTimerOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _TextTimerAttribute_format(ptr: KPointer, value: KStringPtr): void
    @ani.unsafe.Direct
    native static _TextTimerAttribute_fontColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _TextTimerAttribute_fontSize(ptr: KPointer, value: Length): void
    @ani.unsafe.Direct
    native static _TextTimerAttribute_fontStyle(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TextTimerAttribute_fontWeight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextTimerAttribute_fontFamily(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextTimerAttribute_onTimer(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextTimerAttribute_textShadow(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextTimerAttribute_contentModifier(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TimePicker_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _TimePickerInterface_setTimePickerOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TimePickerAttribute_useMilitaryTime(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TimePickerAttribute_loop(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TimePickerAttribute_disappearTextStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TimePickerAttribute_textStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TimePickerAttribute_selectedTextStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TimePickerAttribute_dateTimeOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TimePickerAttribute_onChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TimePickerAttribute_enableHapticFeedback(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _TimePickerAttribute__onChangeEvent_selected(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Toggle_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _ToggleInterface_setToggleOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ToggleAttribute_onChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ToggleAttribute_contentModifier(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ToggleAttribute_selectedColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ToggleAttribute_switchPointColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ToggleAttribute_switchStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ToggleAttribute__onChangeEvent_isOn(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Video_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _VideoInterface_setVideoOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _VideoAttribute_muted(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _VideoAttribute_autoPlay(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _VideoAttribute_controls(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _VideoAttribute_loop(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _VideoAttribute_objectFit(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _VideoAttribute_onStart(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _VideoAttribute_onPause(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _VideoAttribute_onFinish(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _VideoAttribute_onFullscreenChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _VideoAttribute_onPrepared(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _VideoAttribute_onSeeking(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _VideoAttribute_onSeeked(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _VideoAttribute_onUpdate(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _VideoAttribute_onError(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _VideoAttribute_onStop(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _VideoAttribute_enableAnalyzer(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _VideoAttribute_analyzerConfig(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Web_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _WebInterface_setWebOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_javaScriptAccess(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _WebAttribute_fileAccess(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _WebAttribute_onlineImageAccess(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _WebAttribute_domStorageAccess(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _WebAttribute_imageAccess(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _WebAttribute_mixedMode(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _WebAttribute_zoomAccess(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _WebAttribute_geolocationAccess(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _WebAttribute_javaScriptProxy(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_password(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _WebAttribute_cacheMode(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _WebAttribute_darkMode(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _WebAttribute_forceDarkAccess(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _WebAttribute_mediaOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_tableData(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _WebAttribute_wideViewModeAccess(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _WebAttribute_overviewModeAccess(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _WebAttribute_overScrollMode(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _WebAttribute_textZoomAtio(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _WebAttribute_textZoomRatio(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _WebAttribute_databaseAccess(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _WebAttribute_initialScale(ptr: KPointer, value: number): void
    @ani.unsafe.Quick
    native static _WebAttribute_userAgent(ptr: KPointer, value: KStringPtr): void
    @ani.unsafe.Direct
    native static _WebAttribute_metaViewport(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _WebAttribute_onPageEnd(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onPageBegin(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onProgressChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onTitleReceive(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onGeolocationHide(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onGeolocationShow(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onRequestSelected(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onAlert(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onBeforeUnload(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onConfirm(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onPrompt(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onConsole(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onErrorReceive(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onHttpErrorReceive(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onDownloadStart(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onRefreshAccessedHistory(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onUrlLoadIntercept(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onSslErrorReceive(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onRenderExited0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onRenderExited1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onShowFileSelector(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onFileSelectorShow(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onResourceLoad(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onFullScreenExit(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onFullScreenEnter(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onScaleChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onHttpAuthRequest(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onInterceptRequest(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onPermissionRequest(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onScreenCaptureRequest(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onContextMenuShow(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onContextMenuHide(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_mediaPlayGestureAccess(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _WebAttribute_onSearchResultReceive(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onScroll(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onSslErrorEventReceive(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onSslErrorEvent(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onClientAuthenticationRequest(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onWindowNew(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onWindowExit(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_multiWindowAccess(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _WebAttribute_onInterceptKeyEvent(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _WebAttribute_webStandardFont(ptr: KPointer, value: KStringPtr): void
    @ani.unsafe.Quick
    native static _WebAttribute_webSerifFont(ptr: KPointer, value: KStringPtr): void
    @ani.unsafe.Quick
    native static _WebAttribute_webSansSerifFont(ptr: KPointer, value: KStringPtr): void
    @ani.unsafe.Quick
    native static _WebAttribute_webFixedFont(ptr: KPointer, value: KStringPtr): void
    @ani.unsafe.Quick
    native static _WebAttribute_webFantasyFont(ptr: KPointer, value: KStringPtr): void
    @ani.unsafe.Quick
    native static _WebAttribute_webCursiveFont(ptr: KPointer, value: KStringPtr): void
    @ani.unsafe.Direct
    native static _WebAttribute_defaultFixedFontSize(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _WebAttribute_defaultFontSize(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _WebAttribute_minFontSize(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _WebAttribute_minLogicalFontSize(ptr: KPointer, value: number): void
    @ani.unsafe.Quick
    native static _WebAttribute_defaultTextEncodingFormat(ptr: KPointer, value: KStringPtr): void
    @ani.unsafe.Direct
    native static _WebAttribute_forceDisplayScrollBar(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _WebAttribute_blockNetwork(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _WebAttribute_horizontalScrollBarAccess(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _WebAttribute_verticalScrollBarAccess(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _WebAttribute_onTouchIconUrlReceived(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onFaviconReceived(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onPageVisible(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onDataResubmitted(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_pinchSmooth(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _WebAttribute_allowWindowOpenMethod(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _WebAttribute_onAudioStateChanged(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onFirstContentfulPaint(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onFirstMeaningfulPaint(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onLargestContentfulPaint(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onLoadIntercept(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onControllerAttached(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onOverScroll(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onSafeBrowsingCheckResult(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onNavigationEntryCommitted(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onIntelligentTrackingPreventionResult(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_javaScriptOnDocumentStart(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_javaScriptOnDocumentEnd(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_layoutMode(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _WebAttribute_nestedScroll(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_enableNativeEmbedMode(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _WebAttribute_onNativeEmbedLifecycleChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onNativeEmbedVisibilityChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onNativeEmbedGestureEvent(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_copyOptions(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _WebAttribute_onOverrideUrlLoading(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_textAutosizing(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _WebAttribute_enableNativeMediaPlayer(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onRenderProcessNotResponding(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onRenderProcessResponding(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_selectionMenuOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onViewportFitChanged(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onInterceptKeyboardAttach(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_onAdsBlocked(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_keyboardAvoidMode(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _WebAttribute_editMenuOptions(ptr: KPointer, value: KPointer): void
    @ani.unsafe.Direct
    native static _WebAttribute_enableHapticFeedback(ptr: KPointer, value: KInt): void
    @ani.unsafe.Quick
    native static _WebAttribute_registerNativeEmbedRule(ptr: KPointer, tag: KStringPtr, type: KStringPtr): void
    @ani.unsafe.Direct
    native static _WebAttribute_bindSelectionMenu(ptr: KPointer, elementType: KInt, thisArray: KSerializerBuffer, thisLength: int32, responseType: KInt): void
    @ani.unsafe.Direct
    native static _WindowScene_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _WindowSceneInterface_setWindowSceneOptions(ptr: KPointer, persistentId: number): void
    @ani.unsafe.Direct
    native static _WindowSceneAttribute_attractionEffect(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32, fraction: number): void
    @ani.unsafe.Direct
    native static _XComponent_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _XComponentInterface_setXComponentOptions0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _XComponentInterface_setXComponentOptions1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _XComponentInterface_setXComponentOptions2(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _XComponentAttribute_onLoad(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _XComponentAttribute_onDestroy(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _XComponentAttribute_enableAnalyzer(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _XComponentAttribute_enableSecure(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _SideBarContainer_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _SideBarContainerInterface_setSideBarContainerOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SideBarContainerAttribute_showSideBar(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _SideBarContainerAttribute_controlButton(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SideBarContainerAttribute_showControlButton(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _SideBarContainerAttribute_onChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SideBarContainerAttribute_sideBarWidth0(ptr: KPointer, value: number): void
    @ani.unsafe.Quick
    native static _SideBarContainerAttribute_sideBarWidth1(ptr: KPointer, value: Length): void
    @ani.unsafe.Direct
    native static _SideBarContainerAttribute_minSideBarWidth0(ptr: KPointer, value: number): void
    @ani.unsafe.Quick
    native static _SideBarContainerAttribute_minSideBarWidth1(ptr: KPointer, value: Length): void
    @ani.unsafe.Direct
    native static _SideBarContainerAttribute_maxSideBarWidth0(ptr: KPointer, value: number): void
    @ani.unsafe.Quick
    native static _SideBarContainerAttribute_maxSideBarWidth1(ptr: KPointer, value: Length): void
    @ani.unsafe.Direct
    native static _SideBarContainerAttribute_autoHide(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _SideBarContainerAttribute_sideBarPosition(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _SideBarContainerAttribute_divider(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _SideBarContainerAttribute_minContentWidth(ptr: KPointer, value: Length): void
    @ani.unsafe.Direct
    native static _SideBarContainerAttribute__onChangeEvent_showSideBar(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RemoteWindow_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _RemoteWindowInterface_setRemoteWindowOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WaterFlow_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _WaterFlowInterface_setWaterFlowOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _WaterFlowAttribute_columnsTemplate(ptr: KPointer, value: KStringPtr): void
    @ani.unsafe.Direct
    native static _WaterFlowAttribute_itemConstraintSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _WaterFlowAttribute_rowsTemplate(ptr: KPointer, value: KStringPtr): void
    @ani.unsafe.Quick
    native static _WaterFlowAttribute_columnsGap(ptr: KPointer, value: Length): void
    @ani.unsafe.Quick
    native static _WaterFlowAttribute_rowsGap(ptr: KPointer, value: Length): void
    @ani.unsafe.Direct
    native static _WaterFlowAttribute_layoutDirection(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _WaterFlowAttribute_nestedScroll(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WaterFlowAttribute_enableScrollInteraction(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _WaterFlowAttribute_friction(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WaterFlowAttribute_cachedCount0(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _WaterFlowAttribute_cachedCount1(ptr: KPointer, count: number, show: KInt): void
    @ani.unsafe.Direct
    native static _WaterFlowAttribute_onDidScroll(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WaterFlowAttribute_onReachStart(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WaterFlowAttribute_onReachEnd(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WaterFlowAttribute_onScrollFrameBegin(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WaterFlowAttribute_onScrollIndex(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _UIExtensionComponent_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _UIExtensionComponentInterface_setUIExtensionComponentOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _UIExtensionComponentAttribute_onRemoteReady(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _UIExtensionComponentAttribute_onReceive(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _UIExtensionComponentAttribute_onResult(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _UIExtensionComponentAttribute_onRelease(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _UIExtensionComponentAttribute_onError(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _UIExtensionComponentAttribute_onTerminated(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _LinearIndicator_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _LinearIndicatorInterface_setLinearIndicatorOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _LinearIndicatorAttribute_indicatorStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _LinearIndicatorAttribute_indicatorLoop(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _LinearIndicatorAttribute_onChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AnimationExtender_SetClipRect(node: KPointer, x: KFloat, y: KFloat, width: KFloat, height: KFloat): void
    @ani.unsafe.Direct
    native static _AnimationExtender_OpenImplicitAnimation(thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AnimationExtender_CloseImplicitAnimation(): void
    @ani.unsafe.Direct
    native static _AnimationExtender_StartDoubleAnimation(node: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AnimationExtender_AnimationTranslate(node: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _UnifiedData_ctor(): KPointer
    @ani.unsafe.Direct
    native static _UnifiedData_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _UnifiedData_hasType(ptr: KPointer, UnifiedData_type: KStringPtr): boolean
    @ani.unsafe.Quick
    native static _UnifiedData_getTypes(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _LazyForEachOps_NeedMoreElements(node: KPointer, mark: KPointer, direction: KInt): KPointer
    @ani.unsafe.Direct
    native static _LazyForEachOps_OnRangeUpdate(node: KPointer, totalCount: KInt, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _LazyForEachOps_SetCurrentIndex(node: KPointer, index: KInt): void
    @ani.unsafe.Direct
    native static _LazyForEachOps_Prepare(node: KPointer, itemCount: KInt, offset: KInt): void
    @ani.unsafe.Direct
    native static _LazyForEachOps_NotifyChange(node: KPointer, startIndex: KInt, endIndex: KInt, count: KInt): void
    @ani.unsafe.Direct
    native static _SystemOps_StartFrame(): KPointer
    @ani.unsafe.Direct
    native static _SystemOps_EndFrame(root: KPointer): void
    @ani.unsafe.Direct
    native static _SystemOps_syncInstanceId(instanceId: KInt): void
    @ani.unsafe.Direct
    native static _SystemOps_restoreInstanceId(): void
    @ani.unsafe.Quick
    native static _SystemOps_getResourceId(bundleName: KStringPtr, moduleName: KStringPtr, thisArray: KSerializerBuffer, thisLength: int32): int32
    @ani.unsafe.Quick
    native static _FocusController_requestFocus(key: KStringPtr): void
    @ani.unsafe.Direct
    native static _DrawingCanvas_ctor(pixelmap: KPointer): KPointer
    @ani.unsafe.Direct
    native static _DrawingCanvas_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _DrawingCanvas_drawRect(ptr: KPointer, left: number, top: number, right: number, bottom: number): void
    @ani.unsafe.Direct
    native static _LengthMetrics_ctor(): KPointer
    @ani.unsafe.Direct
    native static _LengthMetrics_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _LengthMetrics_px(value: number): KPointer
    @ani.unsafe.Direct
    native static _LengthMetrics_vp(value: number): KPointer
    @ani.unsafe.Direct
    native static _LengthMetrics_fp(value: number): KPointer
    @ani.unsafe.Direct
    native static _LengthMetrics_percent(value: number): KPointer
    @ani.unsafe.Direct
    native static _LengthMetrics_lpx(value: number): KPointer
    @ani.unsafe.Direct
    native static _LengthMetrics_resource(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _LengthMetrics_getUnit(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _LengthMetrics_setUnit(ptr: KPointer, unit: KInt): void
    @ani.unsafe.Direct
    native static _LengthMetrics_getValue(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _LengthMetrics_setValue(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _ColorMetrics_ctor(): KPointer
    @ani.unsafe.Direct
    native static _ColorMetrics_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _ColorMetrics_numeric(value: number): KPointer
    @ani.unsafe.Direct
    native static _ColorMetrics_rgba(red: number, green: number, blue: number, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _ColorMetrics_resourceColor(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _ColorMetrics_blendColor(ptr: KPointer, overlayColor: KPointer): KPointer
    @ani.unsafe.Quick
    native static _ColorMetrics_getColor(ptr: KPointer): string
    @ani.unsafe.Direct
    native static _ColorMetrics_getRed(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _ColorMetrics_getGreen(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _ColorMetrics_getBlue(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _ColorMetrics_getAlpha(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _WebviewController_ctor(): KPointer
    @ani.unsafe.Direct
    native static _WebviewController_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _WebviewController_initializeWebEngine(): void
    @ani.unsafe.Direct
    native static _WebviewController_loadUrl(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _GlobalScope_ohos_arkui_componentSnapshot_get(id: KStringPtr, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _GlobalScope_ohos_arkui_performanceMonitor_begin(scene: KStringPtr, startInputType: KInt, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _GlobalScope_ohos_arkui_performanceMonitor_end(scene: KStringPtr): void
    @ani.unsafe.Direct
    native static _GlobalScope_ohos_arkui_performanceMonitor_recordInputEventTime(actionType: KInt, sourceType: KInt, time: number): void
    @ani.unsafe.Direct
    native static _CommonShape_ctor(): KPointer
    @ani.unsafe.Direct
    native static _CommonShape_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _CommonShape_offset(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _CommonShape_fill(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _CommonShape_position(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _BaseShape_ctor(): KPointer
    @ani.unsafe.Direct
    native static _BaseShape_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _BaseShape_width(ptr: KPointer, width: Length): KPointer
    @ani.unsafe.Quick
    native static _BaseShape_height(ptr: KPointer, height: Length): KPointer
    @ani.unsafe.Direct
    native static _BaseShape_size(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _RectShape_ctor(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _RectShape_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _RectShape_offset(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _RectShape_fill(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _RectShape_position(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Quick
    native static _RectShape_width(ptr: KPointer, width: Length): KPointer
    @ani.unsafe.Quick
    native static _RectShape_height(ptr: KPointer, height: Length): KPointer
    @ani.unsafe.Direct
    native static _RectShape_size(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _RectShape_radiusWidth(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _RectShape_radiusHeight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _RectShape_radius(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _CircleShape_ctor(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _CircleShape_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _CircleShape_offset(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _CircleShape_fill(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _CircleShape_position(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Quick
    native static _CircleShape_width(ptr: KPointer, width: Length): KPointer
    @ani.unsafe.Quick
    native static _CircleShape_height(ptr: KPointer, height: Length): KPointer
    @ani.unsafe.Direct
    native static _CircleShape_size(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _EllipseShape_ctor(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _EllipseShape_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _EllipseShape_offset(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _EllipseShape_fill(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _EllipseShape_position(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Quick
    native static _EllipseShape_width(ptr: KPointer, width: Length): KPointer
    @ani.unsafe.Quick
    native static _EllipseShape_height(ptr: KPointer, height: Length): KPointer
    @ani.unsafe.Direct
    native static _EllipseShape_size(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _PathShape_ctor(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _PathShape_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _PathShape_offset(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _PathShape_fill(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _PathShape_position(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Quick
    native static _PathShape_commands(ptr: KPointer, commands: KStringPtr): KPointer
    @ani.unsafe.Direct
    native static _GlobalScope_ohos_font_registerFont(thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _GlobalScope_ohos_font_getSystemFontList(): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _GlobalScope_ohos_font_getFontByName(fontName: KStringPtr): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _GlobalScope_ohos_measure_utils_measureText(thisArray: KSerializerBuffer, thisLength: int32): number
    @ani.unsafe.Quick
    native static _GlobalScope_ohos_measure_utils_measureTextSize(thisArray: KSerializerBuffer, thisLength: int32): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _ScaleSymbolEffect_ctor(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _ScaleSymbolEffect_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _ScaleSymbolEffect_getScope(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _ScaleSymbolEffect_setScope(ptr: KPointer, scope: KInt): void
    @ani.unsafe.Direct
    native static _ScaleSymbolEffect_getDirection(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _ScaleSymbolEffect_setDirection(ptr: KPointer, direction: KInt): void
    @ani.unsafe.Direct
    native static _ReplaceSymbolEffect_ctor(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _ReplaceSymbolEffect_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _ReplaceSymbolEffect_getScope(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _ReplaceSymbolEffect_setScope(ptr: KPointer, scope: KInt): void
    @ani.unsafe.Direct
    native static _FrameNode_ctor(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _FrameNode_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _FrameNode_isModifiable(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _FrameNode_appendChild(ptr: KPointer, node: KPointer): void
    @ani.unsafe.Direct
    native static _FrameNode_insertChildAfter(ptr: KPointer, child: KPointer, sibling: KPointer): void
    @ani.unsafe.Direct
    native static _FrameNode_removeChild(ptr: KPointer, node: KPointer): void
    @ani.unsafe.Direct
    native static _FrameNode_clearChildren(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _FrameNode_getChild(ptr: KPointer, index: number): KPointer
    @ani.unsafe.Direct
    native static _FrameNode_getFirstChild(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _FrameNode_getNextSibling(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _FrameNode_getPreviousSibling(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _FrameNode_getParent(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _FrameNode_getChildrenCount(ptr: KPointer): int32
    @ani.unsafe.Direct
    native static _FrameNode_dispose(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _FrameNode_getOpacity(ptr: KPointer): number
    @ani.unsafe.Quick
    native static _FrameNode_getPositionToWindowWithTransform(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _FrameNode_getFrameNodeByKey(name: KStringPtr): KPointer
    @ani.unsafe.Direct
    native static _PixelMap_ctor(): KPointer
    @ani.unsafe.Direct
    native static _PixelMap_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _PixelMap_readPixelsToBufferSync(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _PixelMap_writeBufferToPixels(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _PixelMap_getIsEditable(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _PixelMap_getIsStrideAlignment(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _NavExtender_setUpdateStackCallback(peer: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavExtender_syncStack(peer: KPointer): void
    @ani.unsafe.Direct
    native static _NavExtender_checkNeedCreate(navigation: KPointer, index: KInt): boolean
    @ani.unsafe.Direct
    native static _NavExtender_navigationCreate(peer: KInt, flag: KInt): KPointer
    @ani.unsafe.Direct
    native static _NavExtender_setNavigationOptions(navigation: KPointer, stack: KPointer): void
    @ani.unsafe.Direct
    native static _NavExtender_setNavDestinationNode(peer: KPointer, index: KInt, node: KPointer): void
    @ani.unsafe.Direct
    native static _EventEmulator_emitClickEvent(node: KPointer, event: KPointer): void
    @ani.unsafe.Quick
    native static _EventEmulator_emitTextInputEvent(node: KPointer, text: KStringPtr): void
    @ani.unsafe.Direct
    native static _ActionSheet_show(thisArray: KSerializerBuffer, thisLength: int32): undefined
    @ani.unsafe.Direct
    native static _AlertDialog_show(thisArray: KSerializerBuffer, thisLength: int32): undefined
    @ani.unsafe.Direct
    native static _SpringProp_ctor(mass: number, stiffness: number, damping: number): KPointer
    @ani.unsafe.Direct
    native static _SpringProp_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _SpringMotion_ctor(start: number, end: number, velocity: number, prop: KPointer): KPointer
    @ani.unsafe.Direct
    native static _SpringMotion_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _FrictionMotion_ctor(friction: number, position: number, velocity: number): KPointer
    @ani.unsafe.Direct
    native static _FrictionMotion_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _ScrollMotion_ctor(position: number, velocity: number, min: number, max: number, prop: KPointer): KPointer
    @ani.unsafe.Direct
    native static _ScrollMotion_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _CalendarController_ctor(): KPointer
    @ani.unsafe.Direct
    native static _CalendarController_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _CalendarController_backToToday(ptr: KPointer): undefined
    @ani.unsafe.Direct
    native static _CalendarController_goTo(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): undefined
    @ani.unsafe.Direct
    native static _CalendarPickerDialog_show(thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CanvasGradient_ctor(): KPointer
    @ani.unsafe.Direct
    native static _CanvasGradient_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _CanvasGradient_addColorStop(ptr: KPointer, offset: number, color: KStringPtr): void
    @ani.unsafe.Direct
    native static _CanvasPath_ctor(): KPointer
    @ani.unsafe.Direct
    native static _CanvasPath_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _CanvasPath_arc(ptr: KPointer, x: number, y: number, radius: number, startAngle: number, endAngle: number, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CanvasPath_arcTo(ptr: KPointer, x1: number, y1: number, x2: number, y2: number, radius: number): void
    @ani.unsafe.Direct
    native static _CanvasPath_bezierCurveTo(ptr: KPointer, cp1x: number, cp1y: number, cp2x: number, cp2y: number, x: number, y: number): void
    @ani.unsafe.Direct
    native static _CanvasPath_closePath(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _CanvasPath_ellipse(ptr: KPointer, x: number, y: number, radiusX: number, radiusY: number, rotation: number, startAngle: number, endAngle: number, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CanvasPath_lineTo(ptr: KPointer, x: number, y: number): void
    @ani.unsafe.Direct
    native static _CanvasPath_moveTo(ptr: KPointer, x: number, y: number): void
    @ani.unsafe.Direct
    native static _CanvasPath_quadraticCurveTo(ptr: KPointer, cpx: number, cpy: number, x: number, y: number): void
    @ani.unsafe.Direct
    native static _CanvasPath_rect(ptr: KPointer, x: number, y: number, w: number, h: number): void
    @ani.unsafe.Direct
    native static _Path2D_ctor(): KPointer
    @ani.unsafe.Direct
    native static _Path2D_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _Path2D_addPath(ptr: KPointer, path: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CanvasPattern_ctor(): KPointer
    @ani.unsafe.Direct
    native static _CanvasPattern_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _CanvasPattern_setTransform(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _ImageBitmap_ctor(src: KStringPtr): KPointer
    @ani.unsafe.Direct
    native static _ImageBitmap_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _ImageBitmap_close(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _ImageBitmap_getHeight(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _ImageBitmap_getWidth(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _ImageData_ctor(width: number, height: number, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _ImageData_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _ImageData_getData(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _ImageData_getHeight(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _ImageData_getWidth(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _RenderingContextSettings_ctor(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _RenderingContextSettings_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _RenderingContextSettings_getAntialias(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _RenderingContextSettings_setAntialias(ptr: KPointer, antialias: KInt): void
    @ani.unsafe.Direct
    native static _CanvasRenderer_ctor(): KPointer
    @ani.unsafe.Direct
    native static _CanvasRenderer_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _CanvasRenderer_drawImage0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32, dx: number, dy: number): void
    @ani.unsafe.Direct
    native static _CanvasRenderer_drawImage1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32, dx: number, dy: number, dw: number, dh: number): void
    @ani.unsafe.Direct
    native static _CanvasRenderer_drawImage2(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32, sx: number, sy: number, sw: number, sh: number, dx: number, dy: number, dw: number, dh: number): void
    @ani.unsafe.Direct
    native static _CanvasRenderer_beginPath(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _CanvasRenderer_clip0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CanvasRenderer_clip1(ptr: KPointer, path: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CanvasRenderer_fill0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CanvasRenderer_fill1(ptr: KPointer, path: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CanvasRenderer_stroke0(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _CanvasRenderer_stroke1(ptr: KPointer, path: KPointer): void
    @ani.unsafe.Direct
    native static _CanvasRenderer_createLinearGradient(ptr: KPointer, x0: number, y0: number, x1: number, y1: number): KPointer
    @ani.unsafe.Direct
    native static _CanvasRenderer_createPattern(ptr: KPointer, image: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _CanvasRenderer_createRadialGradient(ptr: KPointer, x0: number, y0: number, r0: number, x1: number, y1: number, r1: number): KPointer
    @ani.unsafe.Direct
    native static _CanvasRenderer_createConicGradient(ptr: KPointer, startAngle: number, x: number, y: number): KPointer
    @ani.unsafe.Direct
    native static _CanvasRenderer_createImageData0(ptr: KPointer, sw: number, sh: number): KPointer
    @ani.unsafe.Direct
    native static _CanvasRenderer_createImageData1(ptr: KPointer, imagedata: KPointer): KPointer
    @ani.unsafe.Direct
    native static _CanvasRenderer_getImageData(ptr: KPointer, sx: number, sy: number, sw: number, sh: number): KPointer
    @ani.unsafe.Direct
    native static _CanvasRenderer_getPixelMap(ptr: KPointer, sx: number, sy: number, sw: number, sh: number): KPointer
    @ani.unsafe.Direct
    native static _CanvasRenderer_putImageData0(ptr: KPointer, imagedata: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CanvasRenderer_putImageData1(ptr: KPointer, imagedata: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _CanvasRenderer_getLineDash(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _CanvasRenderer_setLineDash(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CanvasRenderer_clearRect(ptr: KPointer, x: number, y: number, w: number, h: number): void
    @ani.unsafe.Direct
    native static _CanvasRenderer_fillRect(ptr: KPointer, x: number, y: number, w: number, h: number): void
    @ani.unsafe.Direct
    native static _CanvasRenderer_strokeRect(ptr: KPointer, x: number, y: number, w: number, h: number): void
    @ani.unsafe.Direct
    native static _CanvasRenderer_restore(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _CanvasRenderer_save(ptr: KPointer): void
    @ani.unsafe.Quick
    native static _CanvasRenderer_fillText(ptr: KPointer, text: KStringPtr, x: number, y: number, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _CanvasRenderer_measureText(ptr: KPointer, text: KStringPtr): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _CanvasRenderer_strokeText(ptr: KPointer, text: KStringPtr, x: number, y: number, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CanvasRenderer_getTransform(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _CanvasRenderer_resetTransform(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _CanvasRenderer_rotate(ptr: KPointer, angle: number): void
    @ani.unsafe.Direct
    native static _CanvasRenderer_scale(ptr: KPointer, x: number, y: number): void
    @ani.unsafe.Direct
    native static _CanvasRenderer_setTransform0(ptr: KPointer, a: number, b: number, c: number, d: number, e: number, f: number): void
    @ani.unsafe.Direct
    native static _CanvasRenderer_setTransform1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CanvasRenderer_transform(ptr: KPointer, a: number, b: number, c: number, d: number, e: number, f: number): void
    @ani.unsafe.Direct
    native static _CanvasRenderer_translate(ptr: KPointer, x: number, y: number): void
    @ani.unsafe.Direct
    native static _CanvasRenderer_setPixelMap(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CanvasRenderer_transferFromImageBitmap(ptr: KPointer, bitmap: KPointer): void
    @ani.unsafe.Direct
    native static _CanvasRenderer_saveLayer(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _CanvasRenderer_restoreLayer(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _CanvasRenderer_reset(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _CanvasRenderer_getGlobalAlpha(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _CanvasRenderer_setGlobalAlpha(ptr: KPointer, globalAlpha: number): void
    @ani.unsafe.Quick
    native static _CanvasRenderer_getGlobalCompositeOperation(ptr: KPointer): string
    @ani.unsafe.Quick
    native static _CanvasRenderer_setGlobalCompositeOperation(ptr: KPointer, globalCompositeOperation: KStringPtr): void
    @ani.unsafe.Direct
    native static _CanvasRenderer_getFillStyle(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _CanvasRenderer_setFillStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CanvasRenderer_getStrokeStyle(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _CanvasRenderer_setStrokeStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _CanvasRenderer_getFilter(ptr: KPointer): string
    @ani.unsafe.Quick
    native static _CanvasRenderer_setFilter(ptr: KPointer, filter: KStringPtr): void
    @ani.unsafe.Direct
    native static _CanvasRenderer_getImageSmoothingEnabled(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _CanvasRenderer_setImageSmoothingEnabled(ptr: KPointer, imageSmoothingEnabled: KInt): void
    @ani.unsafe.Direct
    native static _CanvasRenderer_getImageSmoothingQuality(ptr: KPointer): KPointer
    @ani.unsafe.Quick
    native static _CanvasRenderer_setImageSmoothingQuality(ptr: KPointer, imageSmoothingQuality: KStringPtr): void
    @ani.unsafe.Direct
    native static _CanvasRenderer_getLineCap(ptr: KPointer): KPointer
    @ani.unsafe.Quick
    native static _CanvasRenderer_setLineCap(ptr: KPointer, lineCap: KStringPtr): void
    @ani.unsafe.Direct
    native static _CanvasRenderer_getLineDashOffset(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _CanvasRenderer_setLineDashOffset(ptr: KPointer, lineDashOffset: number): void
    @ani.unsafe.Direct
    native static _CanvasRenderer_getLineJoin(ptr: KPointer): KPointer
    @ani.unsafe.Quick
    native static _CanvasRenderer_setLineJoin(ptr: KPointer, lineJoin: KStringPtr): void
    @ani.unsafe.Direct
    native static _CanvasRenderer_getLineWidth(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _CanvasRenderer_setLineWidth(ptr: KPointer, lineWidth: number): void
    @ani.unsafe.Direct
    native static _CanvasRenderer_getMiterLimit(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _CanvasRenderer_setMiterLimit(ptr: KPointer, miterLimit: number): void
    @ani.unsafe.Direct
    native static _CanvasRenderer_getShadowBlur(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _CanvasRenderer_setShadowBlur(ptr: KPointer, shadowBlur: number): void
    @ani.unsafe.Quick
    native static _CanvasRenderer_getShadowColor(ptr: KPointer): string
    @ani.unsafe.Quick
    native static _CanvasRenderer_setShadowColor(ptr: KPointer, shadowColor: KStringPtr): void
    @ani.unsafe.Direct
    native static _CanvasRenderer_getShadowOffsetX(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _CanvasRenderer_setShadowOffsetX(ptr: KPointer, shadowOffsetX: number): void
    @ani.unsafe.Direct
    native static _CanvasRenderer_getShadowOffsetY(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _CanvasRenderer_setShadowOffsetY(ptr: KPointer, shadowOffsetY: number): void
    @ani.unsafe.Direct
    native static _CanvasRenderer_getDirection(ptr: KPointer): KPointer
    @ani.unsafe.Quick
    native static _CanvasRenderer_setDirection(ptr: KPointer, direction: KStringPtr): void
    @ani.unsafe.Quick
    native static _CanvasRenderer_getFont(ptr: KPointer): string
    @ani.unsafe.Quick
    native static _CanvasRenderer_setFont(ptr: KPointer, font: KStringPtr): void
    @ani.unsafe.Direct
    native static _CanvasRenderer_getTextAlign(ptr: KPointer): KPointer
    @ani.unsafe.Quick
    native static _CanvasRenderer_setTextAlign(ptr: KPointer, textAlign: KStringPtr): void
    @ani.unsafe.Direct
    native static _CanvasRenderer_getTextBaseline(ptr: KPointer): KPointer
    @ani.unsafe.Quick
    native static _CanvasRenderer_setTextBaseline(ptr: KPointer, textBaseline: KStringPtr): void
    @ani.unsafe.Direct
    native static _CanvasRenderingContext2D_ctor(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _CanvasRenderingContext2D_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _CanvasRenderingContext2D_toDataURL(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): string
    @ani.unsafe.Direct
    native static _CanvasRenderingContext2D_startImageAnalyzer(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _CanvasRenderingContext2D_stopImageAnalyzer(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _CanvasRenderingContext2D_onOnAttach(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CanvasRenderingContext2D_offOnAttach(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CanvasRenderingContext2D_onOnDetach(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CanvasRenderingContext2D_offOnDetach(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CanvasRenderingContext2D_getHeight(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _CanvasRenderingContext2D_getWidth(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _CanvasRenderingContext2D_getCanvas(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _OffscreenCanvasRenderingContext2D_ctor(width: number, height: number, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _OffscreenCanvasRenderingContext2D_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _OffscreenCanvasRenderingContext2D_toDataURL(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): string
    @ani.unsafe.Direct
    native static _OffscreenCanvasRenderingContext2D_transferToImageBitmap(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _OffscreenCanvas_ctor(width: number, height: number): KPointer
    @ani.unsafe.Direct
    native static _OffscreenCanvas_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _OffscreenCanvas_transferToImageBitmap(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _OffscreenCanvas_getContext2d(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _OffscreenCanvas_getHeight(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _OffscreenCanvas_setHeight(ptr: KPointer, height: number): void
    @ani.unsafe.Direct
    native static _OffscreenCanvas_getWidth(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _OffscreenCanvas_setWidth(ptr: KPointer, width: number): void
    @ani.unsafe.Direct
    native static _DrawingRenderingContext_ctor(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _DrawingRenderingContext_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _DrawingRenderingContext_invalidate(ptr: KPointer): void
    @ani.unsafe.Quick
    native static _DrawingRenderingContext_getSize(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _DrawingRenderingContext_getCanvas(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _ICurve_ctor(): KPointer
    @ani.unsafe.Direct
    native static _ICurve_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _ICurve_interpolate(ptr: KPointer, fraction: number): number
    @ani.unsafe.Direct
    native static _DrawModifier_ctor(): KPointer
    @ani.unsafe.Direct
    native static _DrawModifier_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _DrawModifier_drawBehind(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _DrawModifier_drawContent(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _DrawModifier_drawFront(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _DrawModifier_invalidate(ptr: KPointer): void
    @ani.unsafe.Quick
    native static _TransitionEffect_ctor(type: KStringPtr, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _TransitionEffect_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _TransitionEffect_translate(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _TransitionEffect_rotate(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _TransitionEffect_scale(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _TransitionEffect_opacity(alpha: number): KPointer
    @ani.unsafe.Direct
    native static _TransitionEffect_move(edge: KInt): KPointer
    @ani.unsafe.Direct
    native static _TransitionEffect_asymmetric(appear: KPointer, disappear: KPointer): KPointer
    @ani.unsafe.Direct
    native static _TransitionEffect_animation(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _TransitionEffect_combine(ptr: KPointer, transitionEffect: KPointer): KPointer
    @ani.unsafe.Direct
    native static _TransitionEffect_getIDENTITY(): KPointer
    @ani.unsafe.Direct
    native static _TransitionEffect_getOPACITY(): KPointer
    @ani.unsafe.Direct
    native static _TransitionEffect_getSLIDE(): KPointer
    @ani.unsafe.Direct
    native static _TransitionEffect_getSLIDE_SWITCH(): KPointer
    @ani.unsafe.Direct
    native static _BaseEvent_ctor(): KPointer
    @ani.unsafe.Direct
    native static _BaseEvent_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _BaseEvent_getModifierKeyState(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): boolean
    @ani.unsafe.Quick
    native static _BaseEvent_getTarget(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _BaseEvent_setTarget(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _BaseEvent_getTimestamp(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _BaseEvent_setTimestamp(ptr: KPointer, timestamp: number): void
    @ani.unsafe.Direct
    native static _BaseEvent_getSource(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _BaseEvent_setSource(ptr: KPointer, source: KInt): void
    @ani.unsafe.Direct
    native static _BaseEvent_getAxisHorizontal(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _BaseEvent_setAxisHorizontal(ptr: KPointer, axisHorizontal: number): void
    @ani.unsafe.Direct
    native static _BaseEvent_getAxisVertical(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _BaseEvent_setAxisVertical(ptr: KPointer, axisVertical: number): void
    @ani.unsafe.Direct
    native static _BaseEvent_getPressure(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _BaseEvent_setPressure(ptr: KPointer, pressure: number): void
    @ani.unsafe.Direct
    native static _BaseEvent_getTiltX(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _BaseEvent_setTiltX(ptr: KPointer, tiltX: number): void
    @ani.unsafe.Direct
    native static _BaseEvent_getTiltY(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _BaseEvent_setTiltY(ptr: KPointer, tiltY: number): void
    @ani.unsafe.Direct
    native static _BaseEvent_getSourceTool(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _BaseEvent_setSourceTool(ptr: KPointer, sourceTool: KInt): void
    @ani.unsafe.Direct
    native static _BaseEvent_getDeviceId(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _BaseEvent_setDeviceId(ptr: KPointer, deviceId: number): void
    @ani.unsafe.Direct
    native static _ClickEvent_ctor(): KPointer
    @ani.unsafe.Direct
    native static _ClickEvent_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _ClickEvent_getDisplayX(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _ClickEvent_setDisplayX(ptr: KPointer, displayX: number): void
    @ani.unsafe.Direct
    native static _ClickEvent_getDisplayY(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _ClickEvent_setDisplayY(ptr: KPointer, displayY: number): void
    @ani.unsafe.Direct
    native static _ClickEvent_getWindowX(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _ClickEvent_setWindowX(ptr: KPointer, windowX: number): void
    @ani.unsafe.Direct
    native static _ClickEvent_getWindowY(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _ClickEvent_setWindowY(ptr: KPointer, windowY: number): void
    @ani.unsafe.Direct
    native static _ClickEvent_getScreenX(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _ClickEvent_setScreenX(ptr: KPointer, screenX: number): void
    @ani.unsafe.Direct
    native static _ClickEvent_getScreenY(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _ClickEvent_setScreenY(ptr: KPointer, screenY: number): void
    @ani.unsafe.Direct
    native static _ClickEvent_getX(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _ClickEvent_setX(ptr: KPointer, x: number): void
    @ani.unsafe.Direct
    native static _ClickEvent_getY(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _ClickEvent_setY(ptr: KPointer, y: number): void
    @ani.unsafe.Direct
    native static _ClickEvent_getPreventDefault(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _ClickEvent_setPreventDefault(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _HoverEvent_ctor(): KPointer
    @ani.unsafe.Direct
    native static _HoverEvent_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _HoverEvent_getStopPropagation(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _HoverEvent_setStopPropagation(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MouseEvent_ctor(): KPointer
    @ani.unsafe.Direct
    native static _MouseEvent_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _MouseEvent_getButton(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _MouseEvent_setButton(ptr: KPointer, button: KInt): void
    @ani.unsafe.Direct
    native static _MouseEvent_getAction(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _MouseEvent_setAction(ptr: KPointer, action: KInt): void
    @ani.unsafe.Direct
    native static _MouseEvent_getDisplayX(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _MouseEvent_setDisplayX(ptr: KPointer, displayX: number): void
    @ani.unsafe.Direct
    native static _MouseEvent_getDisplayY(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _MouseEvent_setDisplayY(ptr: KPointer, displayY: number): void
    @ani.unsafe.Direct
    native static _MouseEvent_getWindowX(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _MouseEvent_setWindowX(ptr: KPointer, windowX: number): void
    @ani.unsafe.Direct
    native static _MouseEvent_getWindowY(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _MouseEvent_setWindowY(ptr: KPointer, windowY: number): void
    @ani.unsafe.Direct
    native static _MouseEvent_getScreenX(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _MouseEvent_setScreenX(ptr: KPointer, screenX: number): void
    @ani.unsafe.Direct
    native static _MouseEvent_getScreenY(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _MouseEvent_setScreenY(ptr: KPointer, screenY: number): void
    @ani.unsafe.Direct
    native static _MouseEvent_getX(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _MouseEvent_setX(ptr: KPointer, x: number): void
    @ani.unsafe.Direct
    native static _MouseEvent_getY(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _MouseEvent_setY(ptr: KPointer, y: number): void
    @ani.unsafe.Direct
    native static _MouseEvent_getStopPropagation(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _MouseEvent_setStopPropagation(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AccessibilityHoverEvent_ctor(): KPointer
    @ani.unsafe.Direct
    native static _AccessibilityHoverEvent_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _AccessibilityHoverEvent_getType(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _AccessibilityHoverEvent_setType(ptr: KPointer, type: KInt): void
    @ani.unsafe.Direct
    native static _AccessibilityHoverEvent_getX(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _AccessibilityHoverEvent_setX(ptr: KPointer, x: number): void
    @ani.unsafe.Direct
    native static _AccessibilityHoverEvent_getY(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _AccessibilityHoverEvent_setY(ptr: KPointer, y: number): void
    @ani.unsafe.Direct
    native static _AccessibilityHoverEvent_getDisplayX(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _AccessibilityHoverEvent_setDisplayX(ptr: KPointer, displayX: number): void
    @ani.unsafe.Direct
    native static _AccessibilityHoverEvent_getDisplayY(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _AccessibilityHoverEvent_setDisplayY(ptr: KPointer, displayY: number): void
    @ani.unsafe.Direct
    native static _AccessibilityHoverEvent_getWindowX(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _AccessibilityHoverEvent_setWindowX(ptr: KPointer, windowX: number): void
    @ani.unsafe.Direct
    native static _AccessibilityHoverEvent_getWindowY(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _AccessibilityHoverEvent_setWindowY(ptr: KPointer, windowY: number): void
    @ani.unsafe.Direct
    native static _TouchEvent_ctor(): KPointer
    @ani.unsafe.Direct
    native static _TouchEvent_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _TouchEvent_getHistoricalPoints(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _TouchEvent_getType(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _TouchEvent_setType(ptr: KPointer, type: KInt): void
    @ani.unsafe.Quick
    native static _TouchEvent_getTouches(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _TouchEvent_setTouches(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _TouchEvent_getChangedTouches(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _TouchEvent_setChangedTouches(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TouchEvent_getStopPropagation(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _TouchEvent_setStopPropagation(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TouchEvent_getPreventDefault(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _TouchEvent_setPreventDefault(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _PixelMapMock_ctor(): KPointer
    @ani.unsafe.Direct
    native static _PixelMapMock_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _PixelMapMock_release(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _DragEvent_ctor(): KPointer
    @ani.unsafe.Direct
    native static _DragEvent_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _DragEvent_getDisplayX(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _DragEvent_getDisplayY(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _DragEvent_getWindowX(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _DragEvent_getWindowY(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _DragEvent_getX(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _DragEvent_getY(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _DragEvent_setData(ptr: KPointer, unifiedData: KPointer): void
    @ani.unsafe.Direct
    native static _DragEvent_getData(ptr: KPointer): KPointer
    @ani.unsafe.Quick
    native static _DragEvent_getSummary(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _DragEvent_setResult(ptr: KPointer, dragResult: KInt): void
    @ani.unsafe.Direct
    native static _DragEvent_getResult(ptr: KPointer): KPointer
    @ani.unsafe.Quick
    native static _DragEvent_getPreviewRect(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _DragEvent_getVelocityX(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _DragEvent_getVelocityY(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _DragEvent_getVelocity(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _DragEvent_getModifierKeyState(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): boolean
    @ani.unsafe.Direct
    native static _DragEvent_getDragBehavior(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _DragEvent_setDragBehavior(ptr: KPointer, dragBehavior: KInt): void
    @ani.unsafe.Direct
    native static _DragEvent_getUseCustomDropAnimation(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _DragEvent_setUseCustomDropAnimation(ptr: KPointer, useCustomDropAnimation: KInt): void
    @ani.unsafe.Direct
    native static _KeyEvent_ctor(): KPointer
    @ani.unsafe.Direct
    native static _KeyEvent_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _KeyEvent_getModifierKeyState(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): boolean
    @ani.unsafe.Direct
    native static _KeyEvent_getType(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _KeyEvent_setType(ptr: KPointer, type: KInt): void
    @ani.unsafe.Direct
    native static _KeyEvent_getKeyCode(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _KeyEvent_setKeyCode(ptr: KPointer, keyCode: number): void
    @ani.unsafe.Quick
    native static _KeyEvent_getKeyText(ptr: KPointer): string
    @ani.unsafe.Quick
    native static _KeyEvent_setKeyText(ptr: KPointer, keyText: KStringPtr): void
    @ani.unsafe.Direct
    native static _KeyEvent_getKeySource(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _KeyEvent_setKeySource(ptr: KPointer, keySource: KInt): void
    @ani.unsafe.Direct
    native static _KeyEvent_getDeviceId(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _KeyEvent_setDeviceId(ptr: KPointer, deviceId: number): void
    @ani.unsafe.Direct
    native static _KeyEvent_getMetaKey(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _KeyEvent_setMetaKey(ptr: KPointer, metaKey: number): void
    @ani.unsafe.Direct
    native static _KeyEvent_getTimestamp(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _KeyEvent_setTimestamp(ptr: KPointer, timestamp: number): void
    @ani.unsafe.Direct
    native static _KeyEvent_getStopPropagation(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _KeyEvent_setStopPropagation(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _KeyEvent_getIntentionCode(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _KeyEvent_setIntentionCode(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _KeyEvent_getUnicode(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _KeyEvent_setUnicode(ptr: KPointer, unicode: number): void
    @ani.unsafe.Direct
    native static _ProgressMask_ctor(value: number, total: number, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _ProgressMask_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _ProgressMask_updateProgress(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _ProgressMask_updateColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ProgressMask_enableBreathingAnimation(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _Measurable_ctor(): KPointer
    @ani.unsafe.Direct
    native static _Measurable_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _Measurable_measure(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _Measurable_getMargin(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _Measurable_getPadding(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _Measurable_getBorderWidth(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _View_ctor(): KPointer
    @ani.unsafe.Direct
    native static _View_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _View_create(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): object
    @ani.unsafe.Direct
    native static _TextContentControllerBase_ctor(): KPointer
    @ani.unsafe.Direct
    native static _TextContentControllerBase_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _TextContentControllerBase_getCaretOffset(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _TextContentControllerBase_getTextContentRect(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _TextContentControllerBase_getTextContentLineCount(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _ChildrenMainSize_ctor(childDefaultSize: number): KPointer
    @ani.unsafe.Direct
    native static _ChildrenMainSize_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _ChildrenMainSize_splice(ptr: KPointer, start: number, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ChildrenMainSize_update(ptr: KPointer, index: number, childSize: number): void
    @ani.unsafe.Direct
    native static _ChildrenMainSize_getChildDefaultSize(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _ChildrenMainSize_setChildDefaultSize(ptr: KPointer, childDefaultSize: number): void
    @ani.unsafe.Direct
    native static _UICommonEvent_ctor(): KPointer
    @ani.unsafe.Direct
    native static _UICommonEvent_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _UICommonEvent_setOnClick(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _UICommonEvent_setOnTouch(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _UICommonEvent_setOnAppear(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _UICommonEvent_setOnDisappear(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _UICommonEvent_setOnKeyEvent(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _UICommonEvent_setOnFocus(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _UICommonEvent_setOnBlur(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _UICommonEvent_setOnHover(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _UICommonEvent_setOnMouse(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _UICommonEvent_setOnSizeChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _UICommonEvent_setOnVisibleAreaApproximateChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GestureModifier_ctor(): KPointer
    @ani.unsafe.Direct
    native static _GestureModifier_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _GestureModifier_applyGesture(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ContextMenu_close(): undefined
    @ani.unsafe.Direct
    native static _CustomDialogController_ctor(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _CustomDialogController_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _CustomDialogController_open(ptr: KPointer): undefined
    @ani.unsafe.Direct
    native static _CustomDialogController_close(ptr: KPointer): undefined
    @ani.unsafe.Direct
    native static _LinearGradient_ctor(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _LinearGradient_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _DatePickerDialog_show(thisArray: KSerializerBuffer, thisLength: int32): undefined
    @ani.unsafe.Direct
    native static _BaseGestureEvent_ctor(): KPointer
    @ani.unsafe.Direct
    native static _BaseGestureEvent_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _BaseGestureEvent_getFingerList(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _BaseGestureEvent_setFingerList(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TapGestureEvent_ctor(): KPointer
    @ani.unsafe.Direct
    native static _TapGestureEvent_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _LongPressGestureEvent_ctor(): KPointer
    @ani.unsafe.Direct
    native static _LongPressGestureEvent_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _LongPressGestureEvent_getRepeat(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _LongPressGestureEvent_setRepeat(ptr: KPointer, repeat: KInt): void
    @ani.unsafe.Direct
    native static _PanGestureEvent_ctor(): KPointer
    @ani.unsafe.Direct
    native static _PanGestureEvent_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _PanGestureEvent_getOffsetX(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _PanGestureEvent_setOffsetX(ptr: KPointer, offsetX: number): void
    @ani.unsafe.Direct
    native static _PanGestureEvent_getOffsetY(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _PanGestureEvent_setOffsetY(ptr: KPointer, offsetY: number): void
    @ani.unsafe.Direct
    native static _PanGestureEvent_getVelocityX(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _PanGestureEvent_setVelocityX(ptr: KPointer, velocityX: number): void
    @ani.unsafe.Direct
    native static _PanGestureEvent_getVelocityY(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _PanGestureEvent_setVelocityY(ptr: KPointer, velocityY: number): void
    @ani.unsafe.Direct
    native static _PanGestureEvent_getVelocity(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _PanGestureEvent_setVelocity(ptr: KPointer, velocity: number): void
    @ani.unsafe.Direct
    native static _PinchGestureEvent_ctor(): KPointer
    @ani.unsafe.Direct
    native static _PinchGestureEvent_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _PinchGestureEvent_getScale(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _PinchGestureEvent_setScale(ptr: KPointer, scale: number): void
    @ani.unsafe.Direct
    native static _PinchGestureEvent_getPinchCenterX(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _PinchGestureEvent_setPinchCenterX(ptr: KPointer, pinchCenterX: number): void
    @ani.unsafe.Direct
    native static _PinchGestureEvent_getPinchCenterY(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _PinchGestureEvent_setPinchCenterY(ptr: KPointer, pinchCenterY: number): void
    @ani.unsafe.Direct
    native static _RotationGestureEvent_ctor(): KPointer
    @ani.unsafe.Direct
    native static _RotationGestureEvent_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _RotationGestureEvent_getAngle(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _RotationGestureEvent_setAngle(ptr: KPointer, angle: number): void
    @ani.unsafe.Direct
    native static _SwipeGestureEvent_ctor(): KPointer
    @ani.unsafe.Direct
    native static _SwipeGestureEvent_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _SwipeGestureEvent_getAngle(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _SwipeGestureEvent_setAngle(ptr: KPointer, angle: number): void
    @ani.unsafe.Direct
    native static _SwipeGestureEvent_getSpeed(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _SwipeGestureEvent_setSpeed(ptr: KPointer, speed: number): void
    @ani.unsafe.Direct
    native static _GestureEvent_ctor(): KPointer
    @ani.unsafe.Direct
    native static _GestureEvent_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _GestureEvent_getRepeat(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _GestureEvent_setRepeat(ptr: KPointer, repeat: KInt): void
    @ani.unsafe.Quick
    native static _GestureEvent_getFingerList(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _GestureEvent_setFingerList(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GestureEvent_getOffsetX(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _GestureEvent_setOffsetX(ptr: KPointer, offsetX: number): void
    @ani.unsafe.Direct
    native static _GestureEvent_getOffsetY(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _GestureEvent_setOffsetY(ptr: KPointer, offsetY: number): void
    @ani.unsafe.Direct
    native static _GestureEvent_getAngle(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _GestureEvent_setAngle(ptr: KPointer, angle: number): void
    @ani.unsafe.Direct
    native static _GestureEvent_getSpeed(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _GestureEvent_setSpeed(ptr: KPointer, speed: number): void
    @ani.unsafe.Direct
    native static _GestureEvent_getScale(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _GestureEvent_setScale(ptr: KPointer, scale: number): void
    @ani.unsafe.Direct
    native static _GestureEvent_getPinchCenterX(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _GestureEvent_setPinchCenterX(ptr: KPointer, pinchCenterX: number): void
    @ani.unsafe.Direct
    native static _GestureEvent_getPinchCenterY(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _GestureEvent_setPinchCenterY(ptr: KPointer, pinchCenterY: number): void
    @ani.unsafe.Direct
    native static _GestureEvent_getVelocityX(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _GestureEvent_setVelocityX(ptr: KPointer, velocityX: number): void
    @ani.unsafe.Direct
    native static _GestureEvent_getVelocityY(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _GestureEvent_setVelocityY(ptr: KPointer, velocityY: number): void
    @ani.unsafe.Direct
    native static _GestureEvent_getVelocity(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _GestureEvent_setVelocity(ptr: KPointer, velocity: number): void
    @ani.unsafe.Direct
    native static _TapGestureInterface_ctor(): KPointer
    @ani.unsafe.Direct
    native static _TapGestureInterface_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _TapGestureInterface_onAction(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _LongPressGestureInterface_ctor(): KPointer
    @ani.unsafe.Direct
    native static _LongPressGestureInterface_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _LongPressGestureInterface_onAction(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _LongPressGestureInterface_onActionEnd(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _LongPressGestureInterface_onActionCancel(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _PanGestureOptions_ctor(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _PanGestureOptions_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _PanGestureOptions_setDirection(ptr: KPointer, value: KInt): undefined
    @ani.unsafe.Direct
    native static _PanGestureOptions_setDistance(ptr: KPointer, value: number): undefined
    @ani.unsafe.Direct
    native static _PanGestureOptions_setFingers(ptr: KPointer, value: number): undefined
    @ani.unsafe.Direct
    native static _PanGestureOptions_getDirection(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _PanGestureInterface_ctor(): KPointer
    @ani.unsafe.Direct
    native static _PanGestureInterface_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _PanGestureInterface_onActionStart(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _PanGestureInterface_onActionUpdate(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _PanGestureInterface_onActionEnd(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _PanGestureInterface_onActionCancel(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _SwipeGestureInterface_ctor(): KPointer
    @ani.unsafe.Direct
    native static _SwipeGestureInterface_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _SwipeGestureInterface_onAction(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _PinchGestureInterface_ctor(): KPointer
    @ani.unsafe.Direct
    native static _PinchGestureInterface_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _PinchGestureInterface_onActionStart(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _PinchGestureInterface_onActionUpdate(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _PinchGestureInterface_onActionEnd(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _PinchGestureInterface_onActionCancel(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _RotationGestureInterface_ctor(): KPointer
    @ani.unsafe.Direct
    native static _RotationGestureInterface_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _RotationGestureInterface_onActionStart(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _RotationGestureInterface_onActionUpdate(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _RotationGestureInterface_onActionEnd(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _RotationGestureInterface_onActionCancel(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _GestureGroupInterface_ctor(): KPointer
    @ani.unsafe.Direct
    native static _GestureGroupInterface_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _GestureGroupInterface_onCancel(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _ScrollableTargetInfo_ctor(): KPointer
    @ani.unsafe.Direct
    native static _ScrollableTargetInfo_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _ScrollableTargetInfo_isBegin(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _ScrollableTargetInfo_isEnd(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _EventTargetInfo_ctor(): KPointer
    @ani.unsafe.Direct
    native static _EventTargetInfo_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _EventTargetInfo_getId(ptr: KPointer): string
    @ani.unsafe.Direct
    native static _GestureRecognizer_ctor(): KPointer
    @ani.unsafe.Direct
    native static _GestureRecognizer_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _GestureRecognizer_getTag(ptr: KPointer): string
    @ani.unsafe.Direct
    native static _GestureRecognizer_getType(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _GestureRecognizer_isBuiltIn(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _GestureRecognizer_setEnabled(ptr: KPointer, isEnabled: KInt): void
    @ani.unsafe.Direct
    native static _GestureRecognizer_isEnabled(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _GestureRecognizer_getState(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _GestureRecognizer_getEventTargetInfo(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _GestureRecognizer_isValid(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _PanRecognizer_ctor(): KPointer
    @ani.unsafe.Direct
    native static _PanRecognizer_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _PanRecognizer_getPanGestureOptions(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _ImageAnalyzerController_ctor(): KPointer
    @ani.unsafe.Direct
    native static _ImageAnalyzerController_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _ImageAnalyzerController_getImageAnalyzerSupportTypes(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _ListScroller_ctor(): KPointer
    @ani.unsafe.Direct
    native static _ListScroller_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _ListScroller_getItemRectInGroup(ptr: KPointer, index: number, indexInGroup: number): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _ListScroller_scrollToItemInGroup(ptr: KPointer, index: number, indexInGroup: number, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListScroller_closeAllSwipeActions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _ListScroller_getVisibleListContentInfo(ptr: KPointer, x: number, y: number): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _Matrix2D_ctor(): KPointer
    @ani.unsafe.Direct
    native static _Matrix2D_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _Matrix2D_identity(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _Matrix2D_invert(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _Matrix2D_multiply(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _Matrix2D_rotate0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _Matrix2D_rotate1(ptr: KPointer, degree: number, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _Matrix2D_translate(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _Matrix2D_scale(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _Matrix2D_getScaleX(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _Matrix2D_setScaleX(ptr: KPointer, scaleX: number): void
    @ani.unsafe.Direct
    native static _Matrix2D_getRotateY(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _Matrix2D_setRotateY(ptr: KPointer, rotateY: number): void
    @ani.unsafe.Direct
    native static _Matrix2D_getRotateX(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _Matrix2D_setRotateX(ptr: KPointer, rotateX: number): void
    @ani.unsafe.Direct
    native static _Matrix2D_getScaleY(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _Matrix2D_setScaleY(ptr: KPointer, scaleY: number): void
    @ani.unsafe.Direct
    native static _Matrix2D_getTranslateX(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _Matrix2D_setTranslateX(ptr: KPointer, translateX: number): void
    @ani.unsafe.Direct
    native static _Matrix2D_getTranslateY(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _Matrix2D_setTranslateY(ptr: KPointer, translateY: number): void
    @ani.unsafe.Direct
    native static _NavDestinationContext_ctor(): KPointer
    @ani.unsafe.Direct
    native static _NavDestinationContext_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _NavDestinationContext_getConfigInRouteMap(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _NavDestinationContext_getPathInfo(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _NavDestinationContext_setPathInfo(ptr: KPointer, pathInfo: KPointer): void
    @ani.unsafe.Direct
    native static _NavDestinationContext_getPathStack(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _NavDestinationContext_setPathStack(ptr: KPointer, pathStack: KPointer): void
    @ani.unsafe.Quick
    native static _NavDestinationContext_getNavDestinationId(ptr: KPointer): string
    @ani.unsafe.Quick
    native static _NavDestinationContext_setNavDestinationId(ptr: KPointer, navDestinationId: KStringPtr): void
    @ani.unsafe.Quick
    native static _NavPathInfo_ctor(name: KStringPtr, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _NavPathInfo_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _NavPathInfo_getName(ptr: KPointer): string
    @ani.unsafe.Quick
    native static _NavPathInfo_setName(ptr: KPointer, name: KStringPtr): void
    @ani.unsafe.Quick
    native static _NavPathInfo_getParam(ptr: KPointer): object
    @ani.unsafe.Direct
    native static _NavPathInfo_setParam(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavPathInfo_getOnPop(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _NavPathInfo_setOnPop(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavPathInfo_getIsEntry(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _NavPathInfo_setIsEntry(ptr: KPointer, isEntry: KInt): void
    @ani.unsafe.Direct
    native static _NavPathStack_ctor(): KPointer
    @ani.unsafe.Direct
    native static _NavPathStack_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _NavPathStack_pushPath0(ptr: KPointer, info: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavPathStack_pushPath1(ptr: KPointer, info: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavPathStack_pushDestination0(ptr: KPointer, info: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _NavPathStack_pushDestination1(ptr: KPointer, info: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Quick
    native static _NavPathStack_pushPathByName0(ptr: KPointer, name: KStringPtr, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _NavPathStack_pushPathByName1(ptr: KPointer, name: KStringPtr, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _NavPathStack_pushDestinationByName0(ptr: KPointer, name: KStringPtr, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Quick
    native static _NavPathStack_pushDestinationByName1(ptr: KPointer, name: KStringPtr, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _NavPathStack_replacePath0(ptr: KPointer, info: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavPathStack_replacePath1(ptr: KPointer, info: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavPathStack_replaceDestination(ptr: KPointer, info: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Quick
    native static _NavPathStack_replacePathByName(ptr: KPointer, name: KStringPtr, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavPathStack_removeByIndexes(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): number
    @ani.unsafe.Quick
    native static _NavPathStack_removeByName(ptr: KPointer, name: KStringPtr): number
    @ani.unsafe.Quick
    native static _NavPathStack_removeByNavDestinationId(ptr: KPointer, navDestinationId: KStringPtr): boolean
    @ani.unsafe.Direct
    native static _NavPathStack_pop0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _NavPathStack_pop1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Quick
    native static _NavPathStack_popToName0(ptr: KPointer, name: KStringPtr, thisArray: KSerializerBuffer, thisLength: int32): number
    @ani.unsafe.Quick
    native static _NavPathStack_popToName1(ptr: KPointer, name: KStringPtr, thisArray: KSerializerBuffer, thisLength: int32): number
    @ani.unsafe.Direct
    native static _NavPathStack_popToIndex0(ptr: KPointer, index: number, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavPathStack_popToIndex1(ptr: KPointer, index: number, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _NavPathStack_moveToTop(ptr: KPointer, name: KStringPtr, thisArray: KSerializerBuffer, thisLength: int32): number
    @ani.unsafe.Direct
    native static _NavPathStack_moveIndexToTop(ptr: KPointer, index: number, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavPathStack_clear(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _NavPathStack_getAllPathName(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _NavPathStack_getParamByIndex(ptr: KPointer, index: number): KPointer
    @ani.unsafe.Quick
    native static _NavPathStack_getParamByName(ptr: KPointer, name: KStringPtr): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _NavPathStack_getIndexByName(ptr: KPointer, name: KStringPtr): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _NavPathStack_getParent(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _NavPathStack_size(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _NavPathStack_disableAnimation(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _NavPathStack_setInterception(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavigationTransitionProxy_ctor(): KPointer
    @ani.unsafe.Direct
    native static _NavigationTransitionProxy_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _NavigationTransitionProxy_finishTransition(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _NavigationTransitionProxy_cancelTransition(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _NavigationTransitionProxy_updateTransition(ptr: KPointer, progress: number): void
    @ani.unsafe.Quick
    native static _NavigationTransitionProxy_getFrom(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _NavigationTransitionProxy_setFrom(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _NavigationTransitionProxy_getTo(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _NavigationTransitionProxy_setTo(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavigationTransitionProxy_getIsInteractive(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _NavigationTransitionProxy_setIsInteractive(ptr: KPointer, isInteractive: KInt): void
    @ani.unsafe.Direct
    native static _PatternLockController_ctor(): KPointer
    @ani.unsafe.Direct
    native static _PatternLockController_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _PatternLockController_reset(ptr: KPointer): undefined
    @ani.unsafe.Direct
    native static _PatternLockController_setChallengeResult(ptr: KPointer, result: KInt): void
    @ani.unsafe.Direct
    native static _RichEditorBaseController_ctor(): KPointer
    @ani.unsafe.Direct
    native static _RichEditorBaseController_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _RichEditorBaseController_getCaretOffset(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _RichEditorBaseController_setCaretOffset(ptr: KPointer, offset: number): boolean
    @ani.unsafe.Direct
    native static _RichEditorBaseController_closeSelectionMenu(ptr: KPointer): void
    @ani.unsafe.Quick
    native static _RichEditorBaseController_getTypingStyle(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _RichEditorBaseController_setTypingStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorBaseController_setSelection(ptr: KPointer, selectionStart: number, selectionEnd: number, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorBaseController_isEditing(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _RichEditorBaseController_stopEditing(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _RichEditorBaseController_getLayoutManager(ptr: KPointer): KPointer
    @ani.unsafe.Quick
    native static _RichEditorBaseController_getPreviewText(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _RichEditorController_ctor(): KPointer
    @ani.unsafe.Direct
    native static _RichEditorController_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _RichEditorController_addTextSpan(ptr: KPointer, value: KStringPtr, thisArray: KSerializerBuffer, thisLength: int32): number
    @ani.unsafe.Direct
    native static _RichEditorController_addImageSpan(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): number
    @ani.unsafe.Direct
    native static _RichEditorController_addBuilderSpan(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): number
    @ani.unsafe.Direct
    native static _RichEditorController_addSymbolSpan(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): number
    @ani.unsafe.Direct
    native static _RichEditorController_updateSpanStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorController_updateParagraphStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorController_deleteSpans(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _RichEditorController_getSpans(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _RichEditorController_getParagraphs(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _RichEditorController_getSelection(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _RichEditorController_fromStyledString(ptr: KPointer, value: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _RichEditorController_toStyledString(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _RichEditorStyledStringController_ctor(): KPointer
    @ani.unsafe.Direct
    native static _RichEditorStyledStringController_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _RichEditorStyledStringController_setStyledString(ptr: KPointer, styledString: KPointer): void
    @ani.unsafe.Direct
    native static _RichEditorStyledStringController_getStyledString(ptr: KPointer): KPointer
    @ani.unsafe.Quick
    native static _RichEditorStyledStringController_getSelection(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _RichEditorStyledStringController_onContentChanged(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Scroller_ctor(): KPointer
    @ani.unsafe.Direct
    native static _Scroller_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _Scroller_scrollTo(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): undefined
    @ani.unsafe.Direct
    native static _Scroller_scrollEdge(ptr: KPointer, value: KInt, thisArray: KSerializerBuffer, thisLength: int32): undefined
    @ani.unsafe.Direct
    native static _Scroller_fling(ptr: KPointer, velocity: number): void
    @ani.unsafe.Direct
    native static _Scroller_scrollPage0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): undefined
    @ani.unsafe.Direct
    native static _Scroller_scrollPage1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): undefined
    @ani.unsafe.Quick
    native static _Scroller_currentOffset(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _Scroller_scrollToIndex(ptr: KPointer, value: number, thisArray: KSerializerBuffer, thisLength: int32): undefined
    @ani.unsafe.Quick
    native static _Scroller_scrollBy(ptr: KPointer, dx: Length, dy: Length): undefined
    @ani.unsafe.Direct
    native static _Scroller_isAtEnd(ptr: KPointer): boolean
    @ani.unsafe.Quick
    native static _Scroller_getItemRect(ptr: KPointer, index: number): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _Scroller_getItemIndex(ptr: KPointer, x: number, y: number): number
    @ani.unsafe.Direct
    native static _SearchController_ctor(): KPointer
    @ani.unsafe.Direct
    native static _SearchController_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _SearchController_caretPosition(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _SearchController_stopEditing(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _SearchController_setTextSelection(ptr: KPointer, selectionStart: number, selectionEnd: number, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SwiperController_ctor(): KPointer
    @ani.unsafe.Direct
    native static _SwiperController_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _SwiperController_showNext(ptr: KPointer): undefined
    @ani.unsafe.Direct
    native static _SwiperController_showPrevious(ptr: KPointer): undefined
    @ani.unsafe.Direct
    native static _SwiperController_changeIndex(ptr: KPointer, index: number, thisArray: KSerializerBuffer, thisLength: int32): undefined
    @ani.unsafe.Direct
    native static _SwiperController_finishAnimation(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): undefined
    @ani.unsafe.Direct
    native static _SwiperContentTransitionProxy_ctor(): KPointer
    @ani.unsafe.Direct
    native static _SwiperContentTransitionProxy_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _SwiperContentTransitionProxy_finishTransition(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _SwiperContentTransitionProxy_getSelectedIndex(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _SwiperContentTransitionProxy_setSelectedIndex(ptr: KPointer, selectedIndex: number): void
    @ani.unsafe.Direct
    native static _SwiperContentTransitionProxy_getIndex(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _SwiperContentTransitionProxy_setIndex(ptr: KPointer, index: number): void
    @ani.unsafe.Direct
    native static _SwiperContentTransitionProxy_getPosition(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _SwiperContentTransitionProxy_setPosition(ptr: KPointer, position: number): void
    @ani.unsafe.Direct
    native static _SwiperContentTransitionProxy_getMainAxisLength(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _SwiperContentTransitionProxy_setMainAxisLength(ptr: KPointer, mainAxisLength: number): void
    @ani.unsafe.Direct
    native static _IndicatorComponentController_ctor(): KPointer
    @ani.unsafe.Direct
    native static _IndicatorComponentController_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _IndicatorComponentController_showNext(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _IndicatorComponentController_showPrevious(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _IndicatorComponentController_changeIndex(ptr: KPointer, index: number, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _HierarchicalSymbolEffect_ctor(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _HierarchicalSymbolEffect_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _HierarchicalSymbolEffect_getFillStyle(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _HierarchicalSymbolEffect_setFillStyle(ptr: KPointer, fillStyle: KInt): void
    @ani.unsafe.Direct
    native static _AppearSymbolEffect_ctor(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _AppearSymbolEffect_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _AppearSymbolEffect_getScope(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _AppearSymbolEffect_setScope(ptr: KPointer, scope: KInt): void
    @ani.unsafe.Direct
    native static _DisappearSymbolEffect_ctor(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _DisappearSymbolEffect_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _DisappearSymbolEffect_getScope(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _DisappearSymbolEffect_setScope(ptr: KPointer, scope: KInt): void
    @ani.unsafe.Direct
    native static _BounceSymbolEffect_ctor(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _BounceSymbolEffect_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _BounceSymbolEffect_getScope(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _BounceSymbolEffect_setScope(ptr: KPointer, scope: KInt): void
    @ani.unsafe.Direct
    native static _BounceSymbolEffect_getDirection(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _BounceSymbolEffect_setDirection(ptr: KPointer, direction: KInt): void
    @ani.unsafe.Direct
    native static _TabsController_ctor(): KPointer
    @ani.unsafe.Direct
    native static _TabsController_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _TabsController_changeIndex(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _TabsController_preloadItems(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _TabsController_setTabBarTranslate(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabsController_setTabBarOpacity(ptr: KPointer, opacity: number): void
    @ani.unsafe.Direct
    native static _TabContentTransitionProxy_ctor(): KPointer
    @ani.unsafe.Direct
    native static _TabContentTransitionProxy_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _TabContentTransitionProxy_finishTransition(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _TabContentTransitionProxy_getFrom(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _TabContentTransitionProxy_setFrom(ptr: KPointer, from: number): void
    @ani.unsafe.Direct
    native static _TabContentTransitionProxy_getTo(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _TabContentTransitionProxy_setTo(ptr: KPointer, to: number): void
    @ani.unsafe.Direct
    native static _TextController_ctor(): KPointer
    @ani.unsafe.Direct
    native static _TextController_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _TextController_closeSelectionMenu(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _TextController_setStyledString(ptr: KPointer, value: KPointer): void
    @ani.unsafe.Direct
    native static _TextController_getLayoutManager(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _TextAreaController_ctor(): KPointer
    @ani.unsafe.Direct
    native static _TextAreaController_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _TextAreaController_caretPosition(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _TextAreaController_setTextSelection(ptr: KPointer, selectionStart: number, selectionEnd: number, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaController_stopEditing(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _TextClockController_ctor(): KPointer
    @ani.unsafe.Direct
    native static _TextClockController_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _TextClockController_start(ptr: KPointer): undefined
    @ani.unsafe.Direct
    native static _TextClockController_stop(ptr: KPointer): undefined
    @ani.unsafe.Direct
    native static _TextBaseController_ctor(): KPointer
    @ani.unsafe.Direct
    native static _TextBaseController_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _TextBaseController_setSelection(ptr: KPointer, selectionStart: number, selectionEnd: number, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextBaseController_closeSelectionMenu(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _TextBaseController_getLayoutManager(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _TextEditControllerEx_ctor(): KPointer
    @ani.unsafe.Direct
    native static _TextEditControllerEx_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _TextEditControllerEx_isEditing(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _TextEditControllerEx_stopEditing(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _TextEditControllerEx_setCaretOffset(ptr: KPointer, offset: number): boolean
    @ani.unsafe.Direct
    native static _TextEditControllerEx_getCaretOffset(ptr: KPointer): number
    @ani.unsafe.Quick
    native static _TextEditControllerEx_getPreviewText(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _StyledStringController_ctor(): KPointer
    @ani.unsafe.Direct
    native static _StyledStringController_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _StyledStringController_setStyledString(ptr: KPointer, styledString: KPointer): void
    @ani.unsafe.Direct
    native static _StyledStringController_getStyledString(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _LayoutManager_ctor(): KPointer
    @ani.unsafe.Direct
    native static _LayoutManager_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _LayoutManager_getLineCount(ptr: KPointer): number
    @ani.unsafe.Quick
    native static _LayoutManager_getGlyphPositionAtCoordinate(ptr: KPointer, x: number, y: number): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _LayoutManager_getLineMetrics(ptr: KPointer, lineNumber: number): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _LayoutManager_getRectsForRange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32, widthStyle: KInt, heightStyle: KInt): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _TextMenuItemId_ctor(): KPointer
    @ani.unsafe.Direct
    native static _TextMenuItemId_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _TextMenuItemId_of(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _TextMenuItemId_equals(ptr: KPointer, id: KPointer): boolean
    @ani.unsafe.Direct
    native static _TextMenuItemId_getCUT(): KPointer
    @ani.unsafe.Direct
    native static _TextMenuItemId_getCOPY(): KPointer
    @ani.unsafe.Direct
    native static _TextMenuItemId_getPASTE(): KPointer
    @ani.unsafe.Direct
    native static _TextMenuItemId_getSELECT_ALL(): KPointer
    @ani.unsafe.Direct
    native static _TextMenuItemId_getCOLLABORATION_SERVICE(): KPointer
    @ani.unsafe.Direct
    native static _TextMenuItemId_getCAMERA_INPUT(): KPointer
    @ani.unsafe.Direct
    native static _TextMenuItemId_getAI_WRITER(): KPointer
    @ani.unsafe.Direct
    native static _EditMenuOptions_ctor(): KPointer
    @ani.unsafe.Direct
    native static _EditMenuOptions_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _EditMenuOptions_onCreateMenu(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _EditMenuOptions_onMenuItemClick(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): boolean
    @ani.unsafe.Direct
    native static _SubmitEvent_ctor(): KPointer
    @ani.unsafe.Direct
    native static _SubmitEvent_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _SubmitEvent_keepEditableState(ptr: KPointer): void
    @ani.unsafe.Quick
    native static _SubmitEvent_getText(ptr: KPointer): string
    @ani.unsafe.Quick
    native static _SubmitEvent_setText(ptr: KPointer, text: KStringPtr): void
    @ani.unsafe.Direct
    native static _TextInputController_ctor(): KPointer
    @ani.unsafe.Direct
    native static _TextInputController_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _TextInputController_caretPosition(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _TextInputController_setTextSelection(ptr: KPointer, selectionStart: number, selectionEnd: number, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputController_stopEditing(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _TextPickerDialog_show(thisArray: KSerializerBuffer, thisLength: int32): undefined
    @ani.unsafe.Direct
    native static _TextTimerController_ctor(): KPointer
    @ani.unsafe.Direct
    native static _TextTimerController_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _TextTimerController_start(ptr: KPointer): undefined
    @ani.unsafe.Direct
    native static _TextTimerController_pause(ptr: KPointer): undefined
    @ani.unsafe.Direct
    native static _TextTimerController_reset(ptr: KPointer): undefined
    @ani.unsafe.Direct
    native static _TimePickerDialog_show(thisArray: KSerializerBuffer, thisLength: int32): undefined
    @ani.unsafe.Direct
    native static _ColorFilter_ctor(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _ColorFilter_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _VideoController_ctor(): KPointer
    @ani.unsafe.Direct
    native static _VideoController_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _VideoController_start(ptr: KPointer): undefined
    @ani.unsafe.Direct
    native static _VideoController_pause(ptr: KPointer): undefined
    @ani.unsafe.Direct
    native static _VideoController_stop(ptr: KPointer): undefined
    @ani.unsafe.Direct
    native static _VideoController_setCurrentTime0(ptr: KPointer, value: number): undefined
    @ani.unsafe.Direct
    native static _VideoController_requestFullscreen(ptr: KPointer, value: KInt): undefined
    @ani.unsafe.Direct
    native static _VideoController_exitFullscreen(ptr: KPointer): undefined
    @ani.unsafe.Direct
    native static _VideoController_setCurrentTime1(ptr: KPointer, value: number, seekMode: KInt): undefined
    @ani.unsafe.Direct
    native static _VideoController_reset(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _WebKeyboardController_ctor(): KPointer
    @ani.unsafe.Direct
    native static _WebKeyboardController_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _WebKeyboardController_insertText(ptr: KPointer, text: KStringPtr): void
    @ani.unsafe.Direct
    native static _WebKeyboardController_deleteForward(ptr: KPointer, length: number): void
    @ani.unsafe.Direct
    native static _WebKeyboardController_deleteBackward(ptr: KPointer, length: number): void
    @ani.unsafe.Direct
    native static _WebKeyboardController_sendFunctionKey(ptr: KPointer, key: number): void
    @ani.unsafe.Direct
    native static _WebKeyboardController_close(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _FullScreenExitHandler_ctor(): KPointer
    @ani.unsafe.Direct
    native static _FullScreenExitHandler_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _FullScreenExitHandler_exitFullScreen(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _FileSelectorParam_ctor(): KPointer
    @ani.unsafe.Direct
    native static _FileSelectorParam_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _FileSelectorParam_getTitle(ptr: KPointer): string
    @ani.unsafe.Direct
    native static _FileSelectorParam_getMode(ptr: KPointer): KPointer
    @ani.unsafe.Quick
    native static _FileSelectorParam_getAcceptType(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _FileSelectorParam_isCapture(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _JsResult_ctor(): KPointer
    @ani.unsafe.Direct
    native static _JsResult_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _JsResult_handleCancel(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _JsResult_handleConfirm(ptr: KPointer): void
    @ani.unsafe.Quick
    native static _JsResult_handlePromptConfirm(ptr: KPointer, result: KStringPtr): void
    @ani.unsafe.Direct
    native static _FileSelectorResult_ctor(): KPointer
    @ani.unsafe.Direct
    native static _FileSelectorResult_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _FileSelectorResult_handleFileList(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _HttpAuthHandler_ctor(): KPointer
    @ani.unsafe.Direct
    native static _HttpAuthHandler_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _HttpAuthHandler_confirm(ptr: KPointer, userName: KStringPtr, password: KStringPtr): boolean
    @ani.unsafe.Direct
    native static _HttpAuthHandler_cancel(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _HttpAuthHandler_isHttpAuthInfoSaved(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _SslErrorHandler_ctor(): KPointer
    @ani.unsafe.Direct
    native static _SslErrorHandler_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _SslErrorHandler_handleConfirm(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _SslErrorHandler_handleCancel(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _ClientAuthenticationHandler_ctor(): KPointer
    @ani.unsafe.Direct
    native static _ClientAuthenticationHandler_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _ClientAuthenticationHandler_confirm0(ptr: KPointer, priKeyFile: KStringPtr, certChainFile: KStringPtr): void
    @ani.unsafe.Quick
    native static _ClientAuthenticationHandler_confirm1(ptr: KPointer, authUri: KStringPtr): void
    @ani.unsafe.Direct
    native static _ClientAuthenticationHandler_cancel(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _ClientAuthenticationHandler_ignore(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _PermissionRequest_ctor(): KPointer
    @ani.unsafe.Direct
    native static _PermissionRequest_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _PermissionRequest_deny(ptr: KPointer): void
    @ani.unsafe.Quick
    native static _PermissionRequest_getOrigin(ptr: KPointer): string
    @ani.unsafe.Quick
    native static _PermissionRequest_getAccessibleResource(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _PermissionRequest_grant(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScreenCaptureHandler_ctor(): KPointer
    @ani.unsafe.Direct
    native static _ScreenCaptureHandler_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _ScreenCaptureHandler_getOrigin(ptr: KPointer): string
    @ani.unsafe.Direct
    native static _ScreenCaptureHandler_grant(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScreenCaptureHandler_deny(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _DataResubmissionHandler_ctor(): KPointer
    @ani.unsafe.Direct
    native static _DataResubmissionHandler_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _DataResubmissionHandler_resend(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _DataResubmissionHandler_cancel(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _ControllerHandler_ctor(): KPointer
    @ani.unsafe.Direct
    native static _ControllerHandler_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _ControllerHandler_setWebController(ptr: KPointer, controller: KPointer): void
    @ani.unsafe.Direct
    native static _WebContextMenuParam_ctor(): KPointer
    @ani.unsafe.Direct
    native static _WebContextMenuParam_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _WebContextMenuParam_x(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _WebContextMenuParam_y(ptr: KPointer): number
    @ani.unsafe.Quick
    native static _WebContextMenuParam_getLinkUrl(ptr: KPointer): string
    @ani.unsafe.Quick
    native static _WebContextMenuParam_getUnfilteredLinkUrl(ptr: KPointer): string
    @ani.unsafe.Quick
    native static _WebContextMenuParam_getSourceUrl(ptr: KPointer): string
    @ani.unsafe.Direct
    native static _WebContextMenuParam_existsImageContents(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _WebContextMenuParam_getMediaType(ptr: KPointer): KPointer
    @ani.unsafe.Quick
    native static _WebContextMenuParam_getSelectionText(ptr: KPointer): string
    @ani.unsafe.Direct
    native static _WebContextMenuParam_getSourceType(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _WebContextMenuParam_getInputFieldType(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _WebContextMenuParam_isEditable(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _WebContextMenuParam_getEditStateFlags(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _WebContextMenuParam_getPreviewWidth(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _WebContextMenuParam_getPreviewHeight(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _WebContextMenuResult_ctor(): KPointer
    @ani.unsafe.Direct
    native static _WebContextMenuResult_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _WebContextMenuResult_closeContextMenu(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _WebContextMenuResult_copyImage(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _WebContextMenuResult_copy(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _WebContextMenuResult_paste(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _WebContextMenuResult_cut(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _WebContextMenuResult_selectAll(ptr: KPointer): void
    @ani.unsafe.Quick
    native static _ConsoleMessage_ctor(message: KStringPtr, sourceId: KStringPtr, lineNumber: number, messageLevel: KInt): KPointer
    @ani.unsafe.Direct
    native static _ConsoleMessage_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _ConsoleMessage_getMessage(ptr: KPointer): string
    @ani.unsafe.Quick
    native static _ConsoleMessage_getSourceId(ptr: KPointer): string
    @ani.unsafe.Direct
    native static _ConsoleMessage_getLineNumber(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _ConsoleMessage_getMessageLevel(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _WebResourceRequest_ctor(): KPointer
    @ani.unsafe.Direct
    native static _WebResourceRequest_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _WebResourceRequest_getRequestHeader(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _WebResourceRequest_getRequestUrl(ptr: KPointer): string
    @ani.unsafe.Direct
    native static _WebResourceRequest_isRequestGesture(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _WebResourceRequest_isMainFrame(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _WebResourceRequest_isRedirect(ptr: KPointer): boolean
    @ani.unsafe.Quick
    native static _WebResourceRequest_getRequestMethod(ptr: KPointer): string
    @ani.unsafe.Direct
    native static _WebResourceResponse_ctor(): KPointer
    @ani.unsafe.Direct
    native static _WebResourceResponse_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _WebResourceResponse_getResponseData(ptr: KPointer): string
    @ani.unsafe.Direct
    native static _WebResourceResponse_getResponseDataEx(ptr: KPointer): KPointer
    @ani.unsafe.Quick
    native static _WebResourceResponse_getResponseEncoding(ptr: KPointer): string
    @ani.unsafe.Quick
    native static _WebResourceResponse_getResponseMimeType(ptr: KPointer): string
    @ani.unsafe.Quick
    native static _WebResourceResponse_getReasonMessage(ptr: KPointer): string
    @ani.unsafe.Quick
    native static _WebResourceResponse_getResponseHeader(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _WebResourceResponse_getResponseCode(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _WebResourceResponse_setResponseData(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _WebResourceResponse_setResponseEncoding(ptr: KPointer, encoding: KStringPtr): void
    @ani.unsafe.Quick
    native static _WebResourceResponse_setResponseMimeType(ptr: KPointer, mimeType: KStringPtr): void
    @ani.unsafe.Quick
    native static _WebResourceResponse_setReasonMessage(ptr: KPointer, reason: KStringPtr): void
    @ani.unsafe.Direct
    native static _WebResourceResponse_setResponseHeader(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebResourceResponse_setResponseCode(ptr: KPointer, code: number): void
    @ani.unsafe.Direct
    native static _WebResourceResponse_setResponseIsReady(ptr: KPointer, IsReady: KInt): void
    @ani.unsafe.Direct
    native static _WebResourceResponse_getResponseIsReady(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _WebResourceError_ctor(): KPointer
    @ani.unsafe.Direct
    native static _WebResourceError_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _WebResourceError_getErrorInfo(ptr: KPointer): string
    @ani.unsafe.Direct
    native static _WebResourceError_getErrorCode(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _JsGeolocation_ctor(): KPointer
    @ani.unsafe.Direct
    native static _JsGeolocation_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _JsGeolocation_invoke(ptr: KPointer, origin: KStringPtr, allow: KInt, retain: KInt): void
    @ani.unsafe.Direct
    native static _WebCookie_ctor(): KPointer
    @ani.unsafe.Direct
    native static _WebCookie_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _WebCookie_setCookie(ptr: KPointer): undefined
    @ani.unsafe.Direct
    native static _WebCookie_saveCookie(ptr: KPointer): undefined
    @ani.unsafe.Direct
    native static _EventResult_ctor(): KPointer
    @ani.unsafe.Direct
    native static _EventResult_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _EventResult_setGestureEventResult(ptr: KPointer, result: KInt): void
    @ani.unsafe.Direct
    native static _WebController_ctor(): KPointer
    @ani.unsafe.Direct
    native static _WebController_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _WebController_onInactive(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _WebController_onActive(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _WebController_zoom(ptr: KPointer, factor: number): void
    @ani.unsafe.Direct
    native static _WebController_clearHistory(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _WebController_runJavaScript(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): undefined
    @ani.unsafe.Direct
    native static _WebController_loadData(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): undefined
    @ani.unsafe.Direct
    native static _WebController_loadUrl(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): undefined
    @ani.unsafe.Direct
    native static _WebController_refresh(ptr: KPointer): undefined
    @ani.unsafe.Direct
    native static _WebController_stop(ptr: KPointer): undefined
    @ani.unsafe.Direct
    native static _WebController_registerJavaScriptProxy(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): undefined
    @ani.unsafe.Quick
    native static _WebController_deleteJavaScriptRegister(ptr: KPointer, name: KStringPtr): undefined
    @ani.unsafe.Direct
    native static _WebController_getHitTest(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _WebController_requestFocus(ptr: KPointer): undefined
    @ani.unsafe.Direct
    native static _WebController_accessBackward(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _WebController_accessForward(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _WebController_accessStep(ptr: KPointer, step: number): boolean
    @ani.unsafe.Direct
    native static _WebController_backward(ptr: KPointer): undefined
    @ani.unsafe.Direct
    native static _WebController_forward(ptr: KPointer): undefined
    @ani.unsafe.Direct
    native static _WebController_getCookieManager(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _XComponentController_ctor(): KPointer
    @ani.unsafe.Direct
    native static _XComponentController_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _XComponentController_getXComponentSurfaceId(ptr: KPointer): string
    @ani.unsafe.Direct
    native static _XComponentController_getXComponentContext(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _XComponentController_setXComponentSurfaceSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _XComponentController_setXComponentSurfaceRect(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _XComponentController_getXComponentSurfaceRect(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _XComponentController_setXComponentSurfaceRotation(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _XComponentController_getXComponentSurfaceRotation(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _XComponentController_onSurfaceCreated(ptr: KPointer, surfaceId: KStringPtr): void
    @ani.unsafe.Quick
    native static _XComponentController_onSurfaceChanged(ptr: KPointer, surfaceId: KStringPtr, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _XComponentController_onSurfaceDestroyed(ptr: KPointer, surfaceId: KStringPtr): void
    @ani.unsafe.Direct
    native static _XComponentController_startImageAnalyzer(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _XComponentController_stopImageAnalyzer(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _WaterFlowSections_ctor(): KPointer
    @ani.unsafe.Direct
    native static _WaterFlowSections_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _WaterFlowSections_splice(ptr: KPointer, start: number, thisArray: KSerializerBuffer, thisLength: int32): boolean
    @ani.unsafe.Direct
    native static _WaterFlowSections_push(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): boolean
    @ani.unsafe.Direct
    native static _WaterFlowSections_update(ptr: KPointer, sectionIndex: number, thisArray: KSerializerBuffer, thisLength: int32): boolean
    @ani.unsafe.Quick
    native static _WaterFlowSections_values(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _WaterFlowSections_length(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _UIExtensionProxy_ctor(): KPointer
    @ani.unsafe.Direct
    native static _UIExtensionProxy_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _UIExtensionProxy_send(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _UIExtensionProxy_sendSync(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _UIExtensionProxy_onAsyncReceiverRegister(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _UIExtensionProxy_onSyncReceiverRegister(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _UIExtensionProxy_offAsyncReceiverRegister(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _UIExtensionProxy_offSyncReceiverRegister(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _StyledString_ctor(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _StyledString_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _StyledString_getString(ptr: KPointer): string
    @ani.unsafe.Quick
    native static _StyledString_getStyles(ptr: KPointer, start: number, length: number, thisArray: KSerializerBuffer, thisLength: int32): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _StyledString_equals(ptr: KPointer, other: KPointer): boolean
    @ani.unsafe.Direct
    native static _StyledString_subStyledString(ptr: KPointer, start: number, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Quick
    native static _StyledString_fromHtml(html: KStringPtr, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Quick
    native static _StyledString_toHtml(styledString: KPointer): string
    @ani.unsafe.Quick
    native static _StyledString_marshalling(styledString: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _StyledString_unmarshalling(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _StyledString_getLength(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _TextStyle_styled_string_ctor(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _TextStyle_styled_string_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _TextStyle_styled_string_getFontColor(ptr: KPointer): KPointer
    @ani.unsafe.Quick
    native static _TextStyle_styled_string_getFontFamily(ptr: KPointer): string
    @ani.unsafe.Direct
    native static _TextStyle_styled_string_getFontSize(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _TextStyle_styled_string_getFontWeight(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _TextStyle_styled_string_getFontStyle(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _DecorationStyle_ctor(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _DecorationStyle_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _DecorationStyle_getType(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _DecorationStyle_getColor(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _DecorationStyle_getStyle(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _BaselineOffsetStyle_ctor(value: KPointer): KPointer
    @ani.unsafe.Direct
    native static _BaselineOffsetStyle_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _BaselineOffsetStyle_getBaselineOffset(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _LetterSpacingStyle_ctor(value: KPointer): KPointer
    @ani.unsafe.Direct
    native static _LetterSpacingStyle_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _LetterSpacingStyle_getLetterSpacing(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _TextShadowStyle_ctor(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _TextShadowStyle_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _TextShadowStyle_getTextShadow(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _BackgroundColorStyle_ctor(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _BackgroundColorStyle_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _BackgroundColorStyle_getTextBackgroundStyle(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _GestureStyle_ctor(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _GestureStyle_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _ParagraphStyle_ctor(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _ParagraphStyle_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _ParagraphStyle_getTextAlign(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _ParagraphStyle_getTextIndent(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _ParagraphStyle_getMaxLines(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _ParagraphStyle_getOverflow(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _ParagraphStyle_getWordBreak(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _ParagraphStyle_getLeadingMargin(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _LineHeightStyle_ctor(lineHeight: KPointer): KPointer
    @ani.unsafe.Direct
    native static _LineHeightStyle_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _LineHeightStyle_getLineHeight(ptr: KPointer): number
    @ani.unsafe.Quick
    native static _UrlStyle_ctor(url: KStringPtr): KPointer
    @ani.unsafe.Direct
    native static _UrlStyle_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _UrlStyle_getUrl(ptr: KPointer): string
    @ani.unsafe.Direct
    native static _MutableStyledString_ctor(): KPointer
    @ani.unsafe.Direct
    native static _MutableStyledString_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _MutableStyledString_replaceString(ptr: KPointer, start: number, length: number, other: KStringPtr): void
    @ani.unsafe.Quick
    native static _MutableStyledString_insertString(ptr: KPointer, start: number, other: KStringPtr): void
    @ani.unsafe.Direct
    native static _MutableStyledString_removeString(ptr: KPointer, start: number, length: number): void
    @ani.unsafe.Direct
    native static _MutableStyledString_replaceStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MutableStyledString_setStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MutableStyledString_removeStyle(ptr: KPointer, start: number, length: number, styledKey: KInt): void
    @ani.unsafe.Direct
    native static _MutableStyledString_removeStyles(ptr: KPointer, start: number, length: number): void
    @ani.unsafe.Direct
    native static _MutableStyledString_clearStyles(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _MutableStyledString_replaceStyledString(ptr: KPointer, start: number, length: number, other: KPointer): void
    @ani.unsafe.Direct
    native static _MutableStyledString_insertStyledString(ptr: KPointer, start: number, other: KPointer): void
    @ani.unsafe.Direct
    native static _MutableStyledString_appendStyledString(ptr: KPointer, other: KPointer): void
    @ani.unsafe.Direct
    native static _ImageAttachment_ctor(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _ImageAttachment_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _ImageAttachment_getValue(ptr: KPointer): KPointer
    @ani.unsafe.Quick
    native static _ImageAttachment_getSize(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _ImageAttachment_getVerticalAlign(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _ImageAttachment_getObjectFit(ptr: KPointer): KPointer
    @ani.unsafe.Quick
    native static _ImageAttachment_getLayoutStyle(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _CustomSpan_ctor(): KPointer
    @ani.unsafe.Direct
    native static _CustomSpan_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _CustomSpan_onMeasure(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _CustomSpan_onDraw(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CustomSpan_invalidate(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _LinearIndicatorController_ctor(): KPointer
    @ani.unsafe.Direct
    native static _LinearIndicatorController_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _LinearIndicatorController_setProgress(ptr: KPointer, index: number, progress: number): void
    @ani.unsafe.Direct
    native static _LinearIndicatorController_start(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _LinearIndicatorController_pause(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _LinearIndicatorController_stop(ptr: KPointer): void
    @ani.unsafe.Quick
    native static _GlobalScope_getContext(thisArray: KSerializerBuffer, thisLength: int32): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _GlobalScope_postCardAction(thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _GlobalScope_dollar_r(value: KStringPtr, thisArray: KSerializerBuffer, thisLength: int32): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _GlobalScope_dollar_rawfile(value: KStringPtr): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _GlobalScope_animateTo(thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GlobalScope_animateToImmediately(thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GlobalScope_vp2px(value: number): number
    @ani.unsafe.Direct
    native static _GlobalScope_px2vp(value: number): number
    @ani.unsafe.Direct
    native static _GlobalScope_fp2px(value: number): number
    @ani.unsafe.Direct
    native static _GlobalScope_px2fp(value: number): number
    @ani.unsafe.Direct
    native static _GlobalScope_lpx2px(value: number): number
    @ani.unsafe.Direct
    native static _GlobalScope_px2lpx(value: number): number
    @ani.unsafe.Direct
    native static _GlobalScope_getInspectorNodes(): KPointer
    @ani.unsafe.Direct
    native static _GlobalScope_getInspectorNodeById(id: number): KPointer
    @ani.unsafe.Quick
    native static _GlobalScope_setAppBgColor(value: KStringPtr): void
    @ani.unsafe.Direct
    native static _GlobalScope_Profiler_registerVsyncCallback(thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GlobalScope_Profiler_unregisterVsyncCallback(): void
    @ani.unsafe.Direct
    native static _GlobalScope_cursorControl_setCursor(value: KInt): void
    @ani.unsafe.Direct
    native static _GlobalScope_cursorControl_restoreDefault(): void
    @ani.unsafe.Quick
    native static _GlobalScope_focusControl_requestFocus(value: KStringPtr): boolean
    @ani.unsafe.Quick
    native static _UIStateGet(value: KPointer): int64
}