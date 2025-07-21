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

import { KInt, KLong, KBoolean, KFloat, KUInt, KStringPtr, KPointer, KNativePointer, KInt32ArrayPtr, KUint8ArrayPtr, KFloat32ArrayPtr, pointer, KInteropReturnBuffer, KSerializerBuffer, loadNativeModuleLibrary, NativeBuffer } from "@koalaui/interop"
import { int32, int64, float32 } from "@koalaui/common"
export class ArkUIGeneratedNativeModule {
    static {
        loadNativeModuleLibrary("ArkUIGeneratedNativeModule")
    }
    @ani.unsafe.Direct
    native static _AlphabetIndexer_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _AlphabetIndexerInterface_setAlphabetIndexerOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_setColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_setSelectedColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_setPopupColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_setSelectedBackgroundColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_setPopupBackground(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_setPopupSelectedColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_setPopupUnselectedColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_setPopupItemBackgroundColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_setUsingPopup(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_setSelectedFont(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_setPopupFont(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_setPopupItemFont(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_setItemSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_setFont(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_setOnSelect(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_setOnRequestPopupData(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_setOnPopupSelect(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_setSelected(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_setPopupPosition(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_setAutoCollapse(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_setPopupItemBorderRadius(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_setItemBorderRadius(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_setPopupBackgroundBlurStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_setPopupTitleBackground(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_setEnableHapticFeedback(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_setAlignStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AlphabetIndexerAttribute_set_onChangeEvent_selected(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Animator_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Quick
    native static _AnimatorInterface_setAnimatorOptions(ptr: KPointer, value: KStringPtr): void
    @ani.unsafe.Direct
    native static _AnimatorAttribute_setState(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AnimatorAttribute_setDuration(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AnimatorAttribute_setCurve(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AnimatorAttribute_setDelay(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AnimatorAttribute_setFillMode(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AnimatorAttribute_setIterations(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AnimatorAttribute_setPlayMode(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AnimatorAttribute_setMotion(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AnimatorAttribute_setOnStart(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AnimatorAttribute_setOnPause(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AnimatorAttribute_setOnRepeat(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AnimatorAttribute_setOnCancel(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AnimatorAttribute_setOnFinish(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AnimatorAttribute_setOnFrame(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
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
    native static _BlankAttribute_setColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Button_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _ButtonInterface_setButtonOptions0(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _ButtonInterface_setButtonOptions1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ButtonInterface_setButtonOptions2(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ButtonAttribute_setType(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ButtonAttribute_setStateEffect(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ButtonAttribute_setButtonStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ButtonAttribute_setControlSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ButtonAttribute_setRole(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ButtonAttribute_setFontColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ButtonAttribute_setFontSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ButtonAttribute_setFontWeight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ButtonAttribute_setFontStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ButtonAttribute_setFontFamily(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ButtonAttribute_setContentModifier(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ButtonAttribute_setLabelStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ButtonAttribute_setMinFontScale(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ButtonAttribute_setMaxFontScale(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CalendarPicker_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _CalendarPickerInterface_setCalendarPickerOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CalendarPickerAttribute_setTextStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CalendarPickerAttribute_setOnChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CalendarPickerAttribute_setMarkToday(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CalendarPickerAttribute_setEdgeAlign(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Canvas_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _CanvasInterface_setCanvasOptions0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CanvasInterface_setCanvasOptions1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CanvasAttribute_setOnReady(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CanvasAttribute_setEnableAnalyzer(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Checkbox_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _CheckboxInterface_setCheckboxOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CheckboxAttribute_setSelect(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CheckboxAttribute_setSelectedColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CheckboxAttribute_setShape(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CheckboxAttribute_setUnselectedColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CheckboxAttribute_setMark(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CheckboxAttribute_setOnChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CheckboxAttribute_setContentModifier(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CheckboxAttribute_set_onChangeEvent_select(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CheckboxGroup_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _CheckboxGroupInterface_setCheckboxGroupOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CheckboxGroupAttribute_setSelectAll(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CheckboxGroupAttribute_setSelectedColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CheckboxGroupAttribute_setUnselectedColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CheckboxGroupAttribute_setMark(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CheckboxGroupAttribute_setOnChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CheckboxGroupAttribute_setCheckboxShape(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CheckboxGroupAttribute_set_onChangeEvent_selectAll(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Circle_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _CircleInterface_setCircleOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Column_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _ColumnInterface_setColumnOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ColumnAttribute_setAlignItems(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ColumnAttribute_setJustifyContent(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ColumnAttribute_setPointLight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ColumnAttribute_setReverse(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ColumnSplit_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _ColumnSplitInterface_setColumnSplitOptions(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _ColumnSplitAttribute_setResizeable(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ColumnSplitAttribute_setDivider(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _CommonMethod_setWidth(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setHeight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setDrawModifier(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setResponseRegion(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setMouseResponseRegion(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setConstraintSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setHitTestBehavior(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setOnChildTouchTest(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setLayoutWeight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setChainWeight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setPadding(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setSafeAreaPadding(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setMargin(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setBackgroundColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setPixelRound(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setBackgroundImageSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setBackgroundImagePosition(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setBackgroundEffect0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setBackgroundImageResizable(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setForegroundEffect(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setVisualEffect(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setBackgroundFilter(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setForegroundFilter(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setCompositingFilter(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setOpacity(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setBorder(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setBorderStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setBorderWidth(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setBorderColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setBorderRadius(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setBorderImage(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setOutline(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setOutlineStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setOutlineWidth(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setOutlineColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setOutlineRadius(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setForegroundColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setOnClick0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setOnHover(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setOnHoverMove(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setOnAccessibilityHover(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setHoverEffect(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setOnMouse(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setOnTouch(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setOnKeyEvent(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setOnDigitalCrown(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setOnKeyPreIme(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setOnKeyEventDispatch(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setOnFocusAxisEvent(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setOnAxisEvent(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setFocusable(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setNextFocus(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setTabStop(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setOnFocus(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setOnBlur(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setTabIndex(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setDefaultFocus(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setGroupDefaultFocus(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setFocusOnTouch(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setFocusBox(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setAnimation(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setTransition0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setMotionBlur(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setBrightness(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setContrast(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setGrayscale(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setColorBlend(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setSaturate(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setSepia(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setInvert(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setHueRotate(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setUseShadowBatching(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setUseEffect0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setRenderGroup(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setFreeze(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setTranslate(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setScale(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setRotate(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setTransform(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setOnAppear(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setOnDisAppear(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setOnAttach(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setOnDetach(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setOnAreaChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setVisibility(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setFlexGrow(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setFlexShrink(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setFlexBasis(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setAlignSelf(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setDisplayPriority(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setZIndex(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setDirection(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setAlign(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setPosition(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setMarkAnchor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setOffset(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setEnabled(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setAlignRules0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setAlignRules1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setAspectRatio(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setClickEffect(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setOnDragStart(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setOnDragEnter(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setOnDragMove(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setOnDragLeave(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setOnDrop0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setOnDragEnd(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setAllowDrop(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setDraggable(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setDragPreview0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setOnPreDrag(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setLinearGradient(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setSweepGradient(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setRadialGradient(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setMotionPath(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setShadow(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setClip(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setClipShape(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setMask(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setMaskShape(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setKey(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setId(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setGeometryTransition0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setStateStyles(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setRestoreId(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setSphericalEffect(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setLightUpEffect(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setPixelStretchEffect(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setAccessibilityGroup0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setAccessibilityText0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setAccessibilityNextFocusId(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setAccessibilityDefaultFocus(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setAccessibilityUseSamePage(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setAccessibilityScrollTriggerable(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setAccessibilityText1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setAccessibilityRole(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setOnAccessibilityFocus(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setAccessibilityTextHint(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setAccessibilityDescription0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setAccessibilityDescription1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setAccessibilityLevel(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setAccessibilityVirtualNode(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setAccessibilityChecked(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setAccessibilitySelected(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setObscured(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setReuseId(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setReuse(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setRenderFit(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setGestureModifier(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setBackgroundBrightness(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setOnGestureJudgeBegin(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setOnGestureRecognizerJudgeBegin0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setShouldBuiltInRecognizerParallelWith(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setMonopolizeEvents(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setOnTouchIntercept(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setOnSizeChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setAccessibilityFocusDrawLevel(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setCustomProperty(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setExpandSafeArea(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setBackground(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setBackgroundImage0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setBackgroundImage1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setBackgroundBlurStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setBackgroundEffect1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setForegroundBlurStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setOnClick1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setFocusScopeId(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setFocusScopePriority(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setTransition1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setGesture(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setPriorityGesture(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setParallelGesture(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setBlur(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setLinearGradientBlur(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setSystemBarEffect(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _CommonMethod_setUseEffect1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setBackdropBlur(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setSharedTransition(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setChainMode(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setOnDrop1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setDragPreview1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setDragPreviewOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setOverlay(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setBlendMode(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setAdvancedBlendMode(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setGeometryTransition1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setBindTips(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setBindPopup(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setBindMenu0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setBindMenu1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setBindContextMenu0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setBindContextMenu1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setBindContentCover0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setBindContentCover1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setBindSheet(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setOnVisibleAreaChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setOnVisibleAreaApproximateChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setKeyboardShortcut(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setAccessibilityGroup1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonMethod_setOnGestureRecognizerJudgeBegin1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonShapeMethod_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _CommonShapeMethod_setStroke(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonShapeMethod_setFill(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonShapeMethod_setStrokeDashOffset(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonShapeMethod_setStrokeLineCap(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonShapeMethod_setStrokeLineJoin(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonShapeMethod_setStrokeMiterLimit(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonShapeMethod_setStrokeOpacity(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonShapeMethod_setFillOpacity(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonShapeMethod_setStrokeWidth(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonShapeMethod_setAntiAlias(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CommonShapeMethod_setStrokeDashArray(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollableCommonMethod_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _ScrollableCommonMethod_setScrollBar(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollableCommonMethod_setScrollBarColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollableCommonMethod_setScrollBarWidth(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollableCommonMethod_setNestedScroll(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollableCommonMethod_setEnableScrollInteraction(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollableCommonMethod_setFriction(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollableCommonMethod_setOnReachStart(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollableCommonMethod_setOnReachEnd(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollableCommonMethod_setOnScrollStart(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollableCommonMethod_setOnScrollStop(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollableCommonMethod_setFlingSpeedLimit(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollableCommonMethod_setClipContent(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollableCommonMethod_setDigitalCrownSensitivity(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollableCommonMethod_setBackToTop(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollableCommonMethod_setEdgeEffect(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollableCommonMethod_setFadingEdge(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ContainerSpan_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _ContainerSpanInterface_setContainerSpanOptions(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _ContainerSpanAttribute_setTextBackgroundStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Counter_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _CounterInterface_setCounterOptions(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _CounterAttribute_setOnInc(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CounterAttribute_setOnDec(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CounterAttribute_setEnableDec(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CounterAttribute_setEnableInc(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _DataPanel_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _DataPanelInterface_setDataPanelOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _DataPanelAttribute_setCloseEffect(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _DataPanelAttribute_setValueColors(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _DataPanelAttribute_setTrackBackgroundColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _DataPanelAttribute_setStrokeWidth(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _DataPanelAttribute_setTrackShadow(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _DataPanelAttribute_setContentModifier(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _DatePicker_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _DatePickerInterface_setDatePickerOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _DatePickerAttribute_setLunar(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _DatePickerAttribute_setDisappearTextStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _DatePickerAttribute_setTextStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _DatePickerAttribute_setSelectedTextStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _DatePickerAttribute_setOnDateChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _DatePickerAttribute_setDigitalCrownSensitivity(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _DatePickerAttribute_setEnableHapticFeedback(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _DatePickerAttribute_set_onChangeEvent_selected(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Divider_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _DividerInterface_setDividerOptions(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _DividerAttribute_setVertical(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _DividerAttribute_setColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _DividerAttribute_setStrokeWidth(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _DividerAttribute_setLineCap(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
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
    native static _EmbeddedComponentAttribute_setOnTerminated(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _EmbeddedComponentAttribute_setOnError(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Flex_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _FlexInterface_setFlexOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _FlexAttribute_setPointLight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _FlowItem_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _FlowItemInterface_setFlowItemOptions(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _FolderStack_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _FolderStackInterface_setFolderStackOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _FolderStackAttribute_setAlignContent(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _FolderStackAttribute_setOnFolderStateChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _FolderStackAttribute_setOnHoverStatusChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _FolderStackAttribute_setEnableAnimation(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _FolderStackAttribute_setAutoHalfFold(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _FormComponent_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _FormComponentInterface_setFormComponentOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _FormComponentAttribute_setSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _FormComponentAttribute_setModuleName(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _FormComponentAttribute_setDimension(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _FormComponentAttribute_setAllowUpdate(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _FormComponentAttribute_setVisibility(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _FormComponentAttribute_setOnAcquired(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _FormComponentAttribute_setOnError(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _FormComponentAttribute_setOnRouter(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _FormComponentAttribute_setOnUninstall(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _FormComponentAttribute_setOnLoad(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _FormComponentAttribute_setOnUpdate(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _FormLink_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _FormLinkInterface_setFormLinkOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Gauge_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _GaugeInterface_setGaugeOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GaugeAttribute_setValue(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GaugeAttribute_setStartAngle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GaugeAttribute_setEndAngle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GaugeAttribute_setColors(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GaugeAttribute_setStrokeWidth(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GaugeAttribute_setDescription(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GaugeAttribute_setTrackShadow(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GaugeAttribute_setIndicator(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GaugeAttribute_setPrivacySensitive(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GaugeAttribute_setContentModifier(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Grid_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _GridInterface_setGridOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridAttribute_setColumnsTemplate(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridAttribute_setRowsTemplate(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridAttribute_setColumnsGap(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridAttribute_setRowsGap(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridAttribute_setOnScrollBarUpdate(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridAttribute_setOnScrollIndex(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridAttribute_setCachedCount0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridAttribute_setEditMode(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridAttribute_setMultiSelectable(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridAttribute_setMaxCount(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridAttribute_setMinCount(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridAttribute_setCellLength(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridAttribute_setLayoutDirection(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridAttribute_setSupportAnimation(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridAttribute_setOnItemDragStart(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridAttribute_setOnItemDragEnter(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridAttribute_setOnItemDragMove(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridAttribute_setOnItemDragLeave(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridAttribute_setOnItemDrop(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridAttribute_setAlignItems(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridAttribute_setOnScrollFrameBegin(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridAttribute_setOnWillScroll(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridAttribute_setOnDidScroll(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridAttribute_setCachedCount1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridCol_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _GridColInterface_setGridColOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridColAttribute_setSpan(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridColAttribute_setGridColOffset(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridColAttribute_setOrder(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridItem_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _GridItemInterface_setGridItemOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridItemAttribute_setRowStart(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridItemAttribute_setRowEnd(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridItemAttribute_setColumnStart(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridItemAttribute_setColumnEnd(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridItemAttribute_setSelectable(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridItemAttribute_setSelected(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridItemAttribute_setOnSelect(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridItemAttribute_set_onChangeEvent_selected(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridRow_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _GridRowInterface_setGridRowOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridRowAttribute_setOnBreakpointChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GridRowAttribute_setAlignItems(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Hyperlink_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _HyperlinkInterface_setHyperlinkOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _HyperlinkAttribute_setColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Image_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _ImageInterface_setImageOptions0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageInterface_setImageOptions1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAttribute_setAlt(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAttribute_setMatchTextDirection(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAttribute_setFitOriginalSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAttribute_setFillColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAttribute_setObjectFit(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAttribute_setImageMatrix(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAttribute_setObjectRepeat(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAttribute_setAutoResize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAttribute_setRenderMode(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAttribute_setDynamicRangeMode(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAttribute_setInterpolation(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAttribute_setSourceSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAttribute_setSyncLoad(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAttribute_setColorFilter(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAttribute_setCopyOption(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAttribute_setDraggable(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAttribute_setPointLight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAttribute_setEdgeAntialiasing(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAttribute_setOnComplete(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAttribute_setOnError(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAttribute_setOnFinish(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAttribute_setEnableAnalyzer(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAttribute_setAnalyzerConfig(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAttribute_setResizable(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAttribute_setPrivacySensitive(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAttribute_setEnhancedImageQuality(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAttribute_setOrientation(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAnimator_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _ImageAnimatorInterface_setImageAnimatorOptions(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _ImageAnimatorAttribute_setImages(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAnimatorAttribute_setState(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAnimatorAttribute_setDuration(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAnimatorAttribute_setReverse(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAnimatorAttribute_setFixedSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAnimatorAttribute_setFillMode(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAnimatorAttribute_setIterations(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAnimatorAttribute_setMonitorInvisibleArea(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAnimatorAttribute_setOnStart(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAnimatorAttribute_setOnPause(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAnimatorAttribute_setOnRepeat(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAnimatorAttribute_setOnCancel(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageAnimatorAttribute_setOnFinish(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageSpan_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _ImageSpanInterface_setImageSpanOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageSpanAttribute_setVerticalAlign(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageSpanAttribute_setColorFilter(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageSpanAttribute_setObjectFit(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageSpanAttribute_setOnComplete(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageSpanAttribute_setOnError(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageSpanAttribute_setAlt(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _IndicatorComponent_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _IndicatorComponentInterface_setIndicatorComponentOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _IndicatorComponentAttribute_setInitialIndex(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _IndicatorComponentAttribute_setCount(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _IndicatorComponentAttribute_setStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _IndicatorComponentAttribute_setLoop(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _IndicatorComponentAttribute_setVertical(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _IndicatorComponentAttribute_setOnChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Line_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _LineInterface_setLineOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _LineAttribute_setStartPoint(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _LineAttribute_setEndPoint(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _LinearIndicator_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _LinearIndicatorInterface_setLinearIndicatorOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _LinearIndicatorAttribute_setIndicatorStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _LinearIndicatorAttribute_setIndicatorLoop(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _LinearIndicatorAttribute_setOnChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _List_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _ListInterface_setListOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_setAlignListItem(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_setListDirection(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_setContentStartOffset(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_setContentEndOffset(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_setDivider(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_setMultiSelectable(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_setCachedCount0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_setChainAnimation(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_setChainAnimationOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_setSticky(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_setScrollSnapAlign(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_setChildrenMainSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_setMaintainVisibleContentPosition(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_setStackFromEnd(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_setOnScrollIndex(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_setOnScrollVisibleContentChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_setOnItemMove(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_setOnItemDragStart(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_setOnItemDragEnter(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_setOnItemDragMove(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_setOnItemDragLeave(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_setOnItemDrop(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_setOnScrollFrameBegin(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_setOnWillScroll(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_setOnDidScroll(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_setLanes(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListAttribute_setCachedCount1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListItem_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _ListItemInterface_setListItemOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListItemAttribute_setSelectable(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListItemAttribute_setSelected(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListItemAttribute_setSwipeAction(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListItemAttribute_setOnSelect(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListItemAttribute_set_onChangeEvent_selected(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListItemGroup_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _ListItemGroupInterface_setListItemGroupOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListItemGroupAttribute_setDivider(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ListItemGroupAttribute_setChildrenMainSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _LoadingProgress_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _LoadingProgressInterface_setLoadingProgressOptions(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _LoadingProgressAttribute_setColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _LoadingProgressAttribute_setEnableLoading(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _LoadingProgressAttribute_setContentModifier(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Marquee_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _MarqueeInterface_setMarqueeOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MarqueeAttribute_setFontColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MarqueeAttribute_setFontSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MarqueeAttribute_setAllowScale(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MarqueeAttribute_setFontWeight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MarqueeAttribute_setFontFamily(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MarqueeAttribute_setMarqueeUpdateStrategy(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MarqueeAttribute_setOnStart(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MarqueeAttribute_setOnBounce(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MarqueeAttribute_setOnFinish(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MediaCachedImage_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _MediaCachedImageInterface_setMediaCachedImageOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Menu_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _MenuInterface_setMenuOptions(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _MenuAttribute_setFont(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MenuAttribute_setFontColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MenuAttribute_setRadius(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MenuAttribute_setMenuItemDivider(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MenuAttribute_setMenuItemGroupDivider(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MenuAttribute_setSubMenuExpandingMode(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MenuItem_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _MenuItemInterface_setMenuItemOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MenuItemAttribute_setSelected(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MenuItemAttribute_setSelectIcon(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MenuItemAttribute_setOnChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MenuItemAttribute_setContentFont(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MenuItemAttribute_setContentFontColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MenuItemAttribute_setLabelFont(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MenuItemAttribute_setLabelFontColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MenuItemAttribute_set_onChangeEvent_selected(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MenuItemGroup_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _MenuItemGroupInterface_setMenuItemGroupOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestination_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _NavDestinationInterface_setNavDestinationOptions(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_setHideTitleBar0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_setHideBackButton(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_setOnShown(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_setOnHidden(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_setOnBackPressed(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_setOnResult(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_setMode(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_setBackButtonIcon0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_setMenus0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_setOnReady(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_setOnWillAppear(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_setOnWillDisappear(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_setOnWillShow(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_setOnWillHide(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_setSystemBarStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_setRecoverable(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_setSystemTransition(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_setBindToScrollable(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_setBindToNestedScrollable(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_setOnActive(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_setOnInactive(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_setCustomTransition(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_setOnNewParam(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_setPreferredOrientation(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_setEnableNavigationIndicator(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_setTitle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_setHideTitleBar1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_setBackButtonIcon1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_setMenus1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_setToolbarConfiguration(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_setHideToolBar(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_setIgnoreLayoutSafeArea(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavDestinationAttribute_setEnableStatusBar(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Navigation_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _NavigationInterface_setNavigationOptions0(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _NavigationInterface_setNavigationOptions1(ptr: KPointer, pathInfos: KPointer): void
    @ani.unsafe.Direct
    native static _NavigationAttribute_setNavBarWidth(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavigationAttribute_setNavBarPosition(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavigationAttribute_setNavBarWidthRange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavigationAttribute_setMinContentWidth(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavigationAttribute_setMode(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavigationAttribute_setBackButtonIcon0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavigationAttribute_setHideNavBar(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavigationAttribute_setHideTitleBar0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavigationAttribute_setHideBackButton(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavigationAttribute_setTitleMode(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavigationAttribute_setMenus0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavigationAttribute_setHideToolBar0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavigationAttribute_setEnableToolBarAdaptation(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavigationAttribute_setOnTitleModeChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavigationAttribute_setOnNavBarStateChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavigationAttribute_setOnNavigationModeChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavigationAttribute_setNavDestination(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavigationAttribute_setCustomNavContentTransition(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavigationAttribute_setSystemBarStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavigationAttribute_setRecoverable(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavigationAttribute_setEnableDragBar(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavigationAttribute_setEnableModeChangeAnimation(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavigationAttribute_setBackButtonIcon1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavigationAttribute_setTitle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavigationAttribute_setHideTitleBar1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavigationAttribute_setMenus1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavigationAttribute_setToolbarConfiguration(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavigationAttribute_setHideToolBar1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavigationAttribute_setIgnoreLayoutSafeArea(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NodeContainer_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _NodeContainerInterface_setNodeContainerOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Path_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _PathInterface_setPathOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _PatternLock_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _PatternLockInterface_setPatternLockOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _PatternLockAttribute_setSideLength(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _PatternLockAttribute_setCircleRadius(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _PatternLockAttribute_setBackgroundColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _PatternLockAttribute_setRegularColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _PatternLockAttribute_setSelectedColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _PatternLockAttribute_setActiveColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _PatternLockAttribute_setPathColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _PatternLockAttribute_setPathStrokeWidth(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _PatternLockAttribute_setOnPatternComplete(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _PatternLockAttribute_setAutoReset(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _PatternLockAttribute_setOnDotConnect(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _PatternLockAttribute_setActivateCircleStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _PatternLockAttribute_setSkipUnselectedPoint(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _PluginComponent_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _PluginComponentInterface_setPluginComponentOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _PluginComponentAttribute_setOnComplete(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _PluginComponentAttribute_setOnError(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Polygon_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _PolygonInterface_setPolygonOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _PolygonAttribute_setPoints(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Polyline_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _PolylineInterface_setPolylineOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _PolylineAttribute_setPoints(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Progress_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _ProgressInterface_setProgressOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ProgressAttribute_setValue(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ProgressAttribute_setColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ProgressAttribute_setStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ProgressAttribute_setPrivacySensitive(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ProgressAttribute_setContentModifier(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _QRCode_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _QRCodeInterface_setQRCodeOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _QRCodeAttribute_setColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _QRCodeAttribute_setBackgroundColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _QRCodeAttribute_setContentOpacity(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Radio_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _RadioInterface_setRadioOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RadioAttribute_setChecked(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RadioAttribute_setOnChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RadioAttribute_setRadioStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RadioAttribute_setContentModifier(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RadioAttribute_set_onChangeEvent_checked(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Rating_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _RatingInterface_setRatingOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RatingAttribute_setStars(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RatingAttribute_setStepSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RatingAttribute_setStarStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RatingAttribute_setOnChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RatingAttribute_setContentModifier(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RatingAttribute_set_onChangeEvent_rating(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Rect_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _RectInterface_setRectOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RectAttribute_setRadius(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Refresh_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _RefreshInterface_setRefreshOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RefreshAttribute_setOnStateChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RefreshAttribute_setOnRefreshing(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RefreshAttribute_setRefreshOffset(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RefreshAttribute_setPullToRefresh(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RefreshAttribute_setOnOffsetChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RefreshAttribute_setPullDownRatio(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RefreshAttribute_set_onChangeEvent_refreshing(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RelativeContainer_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _RelativeContainerInterface_setRelativeContainerOptions(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _RelativeContainerAttribute_setGuideLine(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RelativeContainerAttribute_setBarrier(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RemoteWindow_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _RemoteWindowInterface_setRemoteWindowOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditor_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _RichEditorInterface_setRichEditorOptions0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorInterface_setRichEditorOptions1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_setOnReady(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_setOnSelect(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_setOnSelectionChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_setAboutToIMEInput(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_setOnIMEInputComplete(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_setOnDidIMEInput(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_setAboutToDelete(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_setOnDeleteComplete(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_setCopyOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_setOnPaste(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_setEnableDataDetector(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_setEnablePreviewText(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_setDataDetectorConfig(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_setCaretColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_setSelectedBackgroundColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_setOnEditingChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_setEnterKeyType(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_setOnSubmit(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_setOnWillChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_setOnDidChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_setOnCut(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_setOnCopy(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_setEditMenuOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_setEnableKeyboardOnFocus(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_setEnableHapticFeedback(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_setBarState(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_setMaxLength(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_setMaxLines(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_setKeyboardAppearance(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_setStopBackPress(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_setBindSelectionMenu(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_setCustomKeyboard(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorAttribute_setPlaceholder(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichText_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Quick
    native static _RichTextInterface_setRichTextOptions(ptr: KPointer, content: KStringPtr): void
    @ani.unsafe.Direct
    native static _RichTextAttribute_setOnStart(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichTextAttribute_setOnComplete(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RootScene_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _RootSceneInterface_setRootSceneOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Row_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _RowInterface_setRowOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RowAttribute_setAlignItems(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RowAttribute_setJustifyContent(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RowAttribute_setPointLight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RowAttribute_setReverse(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RowSplit_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _RowSplitInterface_setRowSplitOptions(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _RowSplitAttribute_setResizeable(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Screen_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _ScreenInterface_setScreenOptions(ptr: KPointer, screenId: number): void
    @ani.unsafe.Direct
    native static _Scroll_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _ScrollInterface_setScrollOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollAttribute_setScrollable(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollAttribute_setOnWillScroll(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollAttribute_setOnDidScroll(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollAttribute_setOnScrollEdge(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollAttribute_setOnScrollStart(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollAttribute_setOnScrollStop(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollAttribute_setScrollBar(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollAttribute_setScrollBarColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollAttribute_setScrollBarWidth(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollAttribute_setOnScrollFrameBegin(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollAttribute_setNestedScroll(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollAttribute_setEnableScrollInteraction(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollAttribute_setFriction(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollAttribute_setScrollSnap(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollAttribute_setEnablePaging(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollAttribute_setInitialOffset(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollAttribute_setEdgeEffect(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollBar_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _ScrollBarInterface_setScrollBarOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScrollBarAttribute_setEnableNestedScroll(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Search_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _SearchInterface_setSearchOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_setFontColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_setSearchIcon(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_setCancelButton(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_setTextIndent(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_setOnEditChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_setSelectedBackgroundColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_setCaretStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_setPlaceholderColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_setPlaceholderFont(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_setTextFont(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_setEnterKeyType(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_setOnSubmit(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_setOnChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_setOnTextSelectionChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_setOnContentScroll(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_setOnCopy(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_setOnCut(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_setOnPaste(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_setCopyOption(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_setMaxLength(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_setTextAlign(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_setEnableKeyboardOnFocus(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_setSelectionMenuHidden(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_setMinFontSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_setMaxFontSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_setMinFontScale(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_setMaxFontScale(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_setDecoration(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_setLetterSpacing(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_setLineHeight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_setType(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_setFontFeature(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_setOnWillInsert(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_setOnDidInsert(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_setOnWillDelete(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_setOnDidDelete(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_setEditMenuOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_setEnablePreviewText(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_setEnableHapticFeedback(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_setAutoCapitalizationMode(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_setHalfLeading(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_setStopBackPress(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_setOnWillChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_setKeyboardAppearance(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_setSearchButton(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_setInputFilter(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_setCustomKeyboard(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SearchAttribute_set_onChangeEvent_value(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Select_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _SelectInterface_setSelectOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SelectAttribute_setSelected(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SelectAttribute_setValue(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SelectAttribute_setFont(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SelectAttribute_setFontColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SelectAttribute_setSelectedOptionBgColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SelectAttribute_setSelectedOptionFont(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SelectAttribute_setSelectedOptionFontColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SelectAttribute_setOptionBgColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SelectAttribute_setOptionFont(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SelectAttribute_setOptionFontColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SelectAttribute_setOnSelect(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SelectAttribute_setSpace(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SelectAttribute_setArrowPosition(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SelectAttribute_setOptionWidth(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SelectAttribute_setOptionHeight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SelectAttribute_setMenuBackgroundColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SelectAttribute_setMenuBackgroundBlurStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SelectAttribute_setControlSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SelectAttribute_setMenuItemContentModifier(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SelectAttribute_setDivider(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SelectAttribute_setTextModifier(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SelectAttribute_setArrowModifier(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SelectAttribute_setOptionTextModifier(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SelectAttribute_setSelectedOptionTextModifier(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SelectAttribute_setDividerStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SelectAttribute_setAvoidance(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SelectAttribute_setMenuOutline(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SelectAttribute_setMenuAlign(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SelectAttribute_set_onChangeEvent_selected(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SelectAttribute_set_onChangeEvent_value(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Shape_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _ShapeInterface_setShapeOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ShapeAttribute_setViewPort(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ShapeAttribute_setStroke(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ShapeAttribute_setFill(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ShapeAttribute_setStrokeDashOffset(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ShapeAttribute_setStrokeDashArray(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ShapeAttribute_setStrokeLineCap(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ShapeAttribute_setStrokeLineJoin(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ShapeAttribute_setStrokeMiterLimit(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ShapeAttribute_setStrokeOpacity(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ShapeAttribute_setFillOpacity(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ShapeAttribute_setStrokeWidth(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ShapeAttribute_setAntiAlias(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ShapeAttribute_setMesh(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SideBarContainer_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _SideBarContainerInterface_setSideBarContainerOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SideBarContainerAttribute_setShowSideBar(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SideBarContainerAttribute_setControlButton(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SideBarContainerAttribute_setShowControlButton(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SideBarContainerAttribute_setOnChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SideBarContainerAttribute_setSideBarWidth0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SideBarContainerAttribute_setMinSideBarWidth0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SideBarContainerAttribute_setMaxSideBarWidth0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SideBarContainerAttribute_setSideBarWidth1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SideBarContainerAttribute_setMinSideBarWidth1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SideBarContainerAttribute_setMaxSideBarWidth1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SideBarContainerAttribute_setAutoHide(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SideBarContainerAttribute_setSideBarPosition(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SideBarContainerAttribute_setDivider(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SideBarContainerAttribute_setMinContentWidth(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SideBarContainerAttribute_set_onChangeEvent_showSideBar(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Slider_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _SliderInterface_setSliderOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SliderAttribute_setBlockColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SliderAttribute_setTrackColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SliderAttribute_setSelectedColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SliderAttribute_setShowSteps(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SliderAttribute_setTrackThickness(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SliderAttribute_setOnChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SliderAttribute_setBlockBorderColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SliderAttribute_setBlockBorderWidth(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SliderAttribute_setStepColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SliderAttribute_setTrackBorderRadius(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SliderAttribute_setSelectedBorderRadius(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SliderAttribute_setBlockSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SliderAttribute_setBlockStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SliderAttribute_setStepSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SliderAttribute_setSliderInteractionMode(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SliderAttribute_setMinResponsiveDistance(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SliderAttribute_setContentModifier(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SliderAttribute_setSlideRange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SliderAttribute_setDigitalCrownSensitivity(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SliderAttribute_setEnableHapticFeedback(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SliderAttribute_setShowTips(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SliderAttribute_set_onChangeEvent_value(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _BaseSpan_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _BaseSpan_setTextBackgroundStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _BaseSpan_setBaselineOffset(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Span_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _SpanInterface_setSpanOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SpanAttribute_setFont(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SpanAttribute_setFontColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SpanAttribute_setFontSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SpanAttribute_setFontStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SpanAttribute_setFontFamily(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SpanAttribute_setDecoration(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SpanAttribute_setTextCase(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SpanAttribute_setLineHeight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SpanAttribute_setTextShadow(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Stack_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _StackInterface_setStackOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _StackAttribute_setAlignContent(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _StackAttribute_setPointLight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Stepper_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _StepperInterface_setStepperOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _StepperAttribute_setOnFinish(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _StepperAttribute_setOnSkip(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _StepperAttribute_setOnChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _StepperAttribute_setOnNext(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _StepperAttribute_setOnPrevious(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _StepperAttribute_set_onChangeEvent_index(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _StepperItem_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _StepperItemInterface_setStepperItemOptions(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _StepperItemAttribute_setPrevLabel(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _StepperItemAttribute_setNextLabel(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _StepperItemAttribute_setStatus(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Swiper_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _SwiperInterface_setSwiperOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_setIndex(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_setInterval(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_setIndicator(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_setLoop(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_setDuration(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_setVertical(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_setItemSpace(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_setDisplayMode(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_setCachedCount0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_setEffectMode(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_setDisableSwipe(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_setCurve(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_setOnChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_setOnSelected(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_setOnUnselected(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_setOnAnimationStart(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_setOnAnimationEnd(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_setOnGestureSwipe(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_setNestedScroll(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_setCustomContentTransition(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_setOnContentDidScroll(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_setIndicatorInteractive(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_setPageFlipMode(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_setOnContentWillScroll(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_setAutoPlay(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_setDisplayArrow(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_setCachedCount1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_setDisplayCount(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_setPrevMargin(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_setNextMargin(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SwiperAttribute_set_onChangeEvent_index(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SymbolGlyph_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _SymbolGlyphInterface_setSymbolGlyphOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SymbolGlyphAttribute_setFontSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SymbolGlyphAttribute_setFontColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SymbolGlyphAttribute_setFontWeight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SymbolGlyphAttribute_setEffectStrategy(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SymbolGlyphAttribute_setRenderingStrategy(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SymbolGlyphAttribute_setMinFontScale(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SymbolGlyphAttribute_setMaxFontScale(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SymbolGlyphAttribute_setSymbolEffect(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SymbolSpan_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _SymbolSpanInterface_setSymbolSpanOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SymbolSpanAttribute_setFontSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SymbolSpanAttribute_setFontColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SymbolSpanAttribute_setFontWeight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SymbolSpanAttribute_setEffectStrategy(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SymbolSpanAttribute_setRenderingStrategy(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabContent_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _TabContentInterface_setTabContentOptions(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _TabContentAttribute_setTabBar(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabContentAttribute_setOnWillShow(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabContentAttribute_setOnWillHide(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Tabs_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _TabsInterface_setTabsOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabsAttribute_setVertical(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabsAttribute_setBarPosition(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabsAttribute_setScrollable(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabsAttribute_setBarWidth(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabsAttribute_setBarHeight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabsAttribute_setAnimationDuration(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabsAttribute_setAnimationMode(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabsAttribute_setEdgeEffect(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabsAttribute_setOnChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabsAttribute_setOnSelected(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabsAttribute_setOnTabBarClick(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabsAttribute_setOnUnselected(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabsAttribute_setOnAnimationStart(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabsAttribute_setOnAnimationEnd(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabsAttribute_setOnGestureSwipe(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabsAttribute_setFadingEdge(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabsAttribute_setDivider(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabsAttribute_setBarOverlap(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabsAttribute_setBarBackgroundColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabsAttribute_setBarGridAlign(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabsAttribute_setCustomContentTransition(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabsAttribute_setBarBackgroundBlurStyle0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabsAttribute_setPageFlipMode(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabsAttribute_setBarBackgroundEffect(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabsAttribute_setOnContentWillChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabsAttribute_setBarMode(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabsAttribute_setBarBackgroundBlurStyle1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabsAttribute_setCachedMaxCount(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabsAttribute_set_onChangeEvent_index(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Text_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _TextInterface_setTextOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_setFontColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_setFontSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_setMinFontSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_setMaxFontSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_setMinFontScale(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_setMaxFontScale(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_setFontStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_setLineSpacing(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_setTextAlign(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_setLineHeight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_setTextOverflow(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_setFontFamily(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_setMaxLines(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_setDecoration(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_setLetterSpacing(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_setTextCase(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_setBaselineOffset(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_setCopyOption(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_setDraggable(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_setTextShadow(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_setHeightAdaptivePolicy(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_setTextIndent(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_setWordBreak(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_setLineBreakStrategy(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_setOnCopy(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_setCaretColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_setSelectedBackgroundColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_setEllipsisMode(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_setEnableDataDetector(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_setDataDetectorConfig(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_setOnTextSelectionChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_setFontFeature(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_setMarqueeOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_setOnMarqueeStateChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_setPrivacySensitive(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_setTextSelectable(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_setEditMenuOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_setHalfLeading(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_setEnableHapticFeedback(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_setFont(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_setFontWeight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_setSelection(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAttribute_setBindSelectionMenu(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextArea_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _TextAreaInterface_setTextAreaOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setPlaceholderColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setPlaceholderFont(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setEnterKeyType(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setTextAlign(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setCaretColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setFontColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setFontSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setFontStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setFontWeight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setFontFamily(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setTextOverflow(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setTextIndent(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setCaretStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setSelectedBackgroundColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setOnSubmit(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setOnChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setOnTextSelectionChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setOnContentScroll(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setOnEditChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setOnCopy(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setOnCut(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setOnPaste(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setCopyOption(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setEnableKeyboardOnFocus(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setMaxLength(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setBarState(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setSelectionMenuHidden(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setMinFontSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setMaxFontSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setMinFontScale(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setMaxFontScale(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setHeightAdaptivePolicy(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setMaxLines(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setWordBreak(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setLineBreakStrategy(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setDecoration(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setLetterSpacing(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setLineSpacing(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setLineHeight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setType(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setEnableAutoFill(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setContentType(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setFontFeature(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setOnWillInsert(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setOnDidInsert(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setOnWillDelete(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setOnDidDelete(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setEditMenuOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setEnablePreviewText(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setEnableHapticFeedback(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setAutoCapitalizationMode(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setHalfLeading(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setEllipsisMode(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setStopBackPress(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setOnWillChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setKeyboardAppearance(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setInputFilter(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setShowCounter(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_setCustomKeyboard(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaAttribute_set_onChangeEvent_text(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextClock_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _TextClockInterface_setTextClockOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextClockAttribute_setFormat(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextClockAttribute_setOnDateChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextClockAttribute_setFontColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextClockAttribute_setFontSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextClockAttribute_setFontStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextClockAttribute_setFontWeight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextClockAttribute_setFontFamily(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextClockAttribute_setTextShadow(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextClockAttribute_setFontFeature(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextClockAttribute_setContentModifier(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextClockAttribute_setDateTimeOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInput_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _TextInputInterface_setTextInputOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setType(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setContentType(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setPlaceholderColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setTextOverflow(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setTextIndent(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setPlaceholderFont(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setEnterKeyType(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setCaretColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setOnEditChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setOnSubmit(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setOnChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setOnTextSelectionChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setOnContentScroll(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setMaxLength(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setFontColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setFontSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setFontStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setFontWeight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setFontFamily(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setOnCopy(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setOnCut(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setOnPaste(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setCopyOption(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setShowPasswordIcon(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setTextAlign(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setCaretStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setSelectedBackgroundColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setCaretPosition(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setEnableKeyboardOnFocus(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setPasswordIcon(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setShowError(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setShowUnit(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setShowUnderline(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setUnderlineColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setSelectionMenuHidden(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setBarState(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setMaxLines(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setWordBreak(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setLineBreakStrategy(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setCancelButton(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setSelectAll(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setMinFontSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setMaxFontSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setMinFontScale(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setMaxFontScale(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setHeightAdaptivePolicy(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setEnableAutoFill(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setDecoration(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setLetterSpacing(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setLineHeight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setPasswordRules(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setFontFeature(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setShowPassword(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setOnSecurityStateChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setOnWillInsert(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setOnDidInsert(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setOnWillDelete(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setOnDidDelete(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setEditMenuOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setEnablePreviewText(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setEnableHapticFeedback(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setAutoCapitalizationMode(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setHalfLeading(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setEllipsisMode(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setStopBackPress(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setOnWillChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setKeyboardAppearance(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setInputFilter(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setCustomKeyboard(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_setShowCounter(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputAttribute_set_onChangeEvent_text(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextPicker_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _TextPickerInterface_setTextPickerOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextPickerAttribute_setDefaultPickerItemHeight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextPickerAttribute_setCanLoop(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextPickerAttribute_setDisappearTextStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextPickerAttribute_setTextStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextPickerAttribute_setSelectedTextStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextPickerAttribute_setDisableTextStyleAnimation(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextPickerAttribute_setDefaultTextStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextPickerAttribute_setOnChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextPickerAttribute_setOnScrollStop(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextPickerAttribute_setOnEnterSelectedArea(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextPickerAttribute_setSelectedIndex(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextPickerAttribute_setDivider(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextPickerAttribute_setGradientHeight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextPickerAttribute_setEnableHapticFeedback(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextPickerAttribute_setDigitalCrownSensitivity(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextPickerAttribute_set_onChangeEvent_selected(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextPickerAttribute_set_onChangeEvent_value(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextTimer_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _TextTimerInterface_setTextTimerOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextTimerAttribute_setFormat(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextTimerAttribute_setFontColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextTimerAttribute_setFontSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextTimerAttribute_setFontStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextTimerAttribute_setFontWeight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextTimerAttribute_setFontFamily(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextTimerAttribute_setOnTimer(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextTimerAttribute_setTextShadow(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextTimerAttribute_setContentModifier(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TimePicker_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _TimePickerInterface_setTimePickerOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TimePickerAttribute_setUseMilitaryTime(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TimePickerAttribute_setLoop(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TimePickerAttribute_setDisappearTextStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TimePickerAttribute_setTextStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TimePickerAttribute_setSelectedTextStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TimePickerAttribute_setDateTimeOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TimePickerAttribute_setOnChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TimePickerAttribute_setOnEnterSelectedArea(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TimePickerAttribute_setEnableHapticFeedback(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TimePickerAttribute_setDigitalCrownSensitivity(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TimePickerAttribute_setEnableCascade(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TimePickerAttribute_set_onChangeEvent_selected(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Toggle_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _ToggleInterface_setToggleOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ToggleAttribute_setOnChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ToggleAttribute_setContentModifier(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ToggleAttribute_setSelectedColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ToggleAttribute_setSwitchPointColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ToggleAttribute_setSwitchStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ToggleAttribute_set_onChangeEvent_isOn(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _UIExtensionComponent_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _UIExtensionComponentInterface_setUIExtensionComponentOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _UIExtensionComponentAttribute_setOnRemoteReady(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _UIExtensionComponentAttribute_setOnReceive(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _UIExtensionComponentAttribute_setOnError(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _UIExtensionComponentAttribute_setOnTerminated(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _UIExtensionComponentAttribute_setOnDrawReady(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Video_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _VideoInterface_setVideoOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _VideoAttribute_setMuted(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _VideoAttribute_setAutoPlay(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _VideoAttribute_setControls(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _VideoAttribute_setLoop(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _VideoAttribute_setObjectFit(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _VideoAttribute_setOnStart(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _VideoAttribute_setOnPause(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _VideoAttribute_setOnFinish(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _VideoAttribute_setOnFullscreenChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _VideoAttribute_setOnPrepared(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _VideoAttribute_setOnSeeking(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _VideoAttribute_setOnSeeked(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _VideoAttribute_setOnUpdate(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _VideoAttribute_setOnError(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _VideoAttribute_setOnStop(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _VideoAttribute_setEnableAnalyzer(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _VideoAttribute_setAnalyzerConfig(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _VideoAttribute_setSurfaceBackgroundColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _VideoAttribute_setEnableShortcutKey(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WaterFlow_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _WaterFlowInterface_setWaterFlowOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WaterFlowAttribute_setColumnsTemplate(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WaterFlowAttribute_setItemConstraintSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WaterFlowAttribute_setRowsTemplate(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WaterFlowAttribute_setColumnsGap(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WaterFlowAttribute_setRowsGap(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WaterFlowAttribute_setLayoutDirection(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WaterFlowAttribute_setCachedCount0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WaterFlowAttribute_setOnScrollFrameBegin(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WaterFlowAttribute_setOnScrollIndex(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WaterFlowAttribute_setOnWillScroll(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WaterFlowAttribute_setOnDidScroll(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WaterFlowAttribute_setCachedCount1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Web_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _WebInterface_setWebOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setJavaScriptAccess(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setFileAccess(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnlineImageAccess(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setDomStorageAccess(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setImageAccess(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setMixedMode(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setZoomAccess(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setGeolocationAccess(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setJavaScriptProxy(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setCacheMode(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setDarkMode(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setForceDarkAccess(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setMediaOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOverviewModeAccess(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOverScrollMode(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setBlurOnKeyboardHideMode(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setTextZoomRatio(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setDatabaseAccess(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setInitialScale(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setMetaViewport(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnPageEnd(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnPageBegin(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnProgressChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnTitleReceive(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnGeolocationHide(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnGeolocationShow(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnRequestSelected(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnAlert(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnBeforeUnload(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnConfirm(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnPrompt(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnConsole(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnErrorReceive(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnHttpErrorReceive(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnDownloadStart(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnRefreshAccessedHistory(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnRenderExited(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnShowFileSelector(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnResourceLoad(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnFullScreenExit(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnFullScreenEnter(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnScaleChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnHttpAuthRequest(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnInterceptRequest(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnPermissionRequest(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnScreenCaptureRequest(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnContextMenuShow(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnContextMenuHide(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setMediaPlayGestureAccess(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnSearchResultReceive(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnScroll(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnSslErrorEventReceive(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnSslErrorEvent(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnClientAuthenticationRequest(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnWindowNew(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnWindowExit(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setMultiWindowAccess(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnInterceptKeyEvent(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setWebStandardFont(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setWebSerifFont(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setWebSansSerifFont(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setWebFixedFont(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setWebFantasyFont(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setWebCursiveFont(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setDefaultFixedFontSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setDefaultFontSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setMinFontSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setMinLogicalFontSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setDefaultTextEncodingFormat(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setForceDisplayScrollBar(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setBlockNetwork(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setHorizontalScrollBarAccess(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setVerticalScrollBarAccess(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnTouchIconUrlReceived(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnFaviconReceived(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnPageVisible(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnDataResubmitted(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setPinchSmooth(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setAllowWindowOpenMethod(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnAudioStateChanged(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnFirstContentfulPaint(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnFirstMeaningfulPaint(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnLargestContentfulPaint(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnLoadIntercept(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnControllerAttached(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnOverScroll(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnSafeBrowsingCheckResult(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnNavigationEntryCommitted(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnIntelligentTrackingPreventionResult(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setJavaScriptOnDocumentStart(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setJavaScriptOnDocumentEnd(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setLayoutMode(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setNestedScroll(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setEnableNativeEmbedMode(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnNativeEmbedLifecycleChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnNativeEmbedVisibilityChange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnNativeEmbedGestureEvent(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setCopyOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnOverrideUrlLoading(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setTextAutosizing(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setEnableNativeMediaPlayer(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnRenderProcessNotResponding(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnRenderProcessResponding(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnViewportFitChanged(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnInterceptKeyboardAttach(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOnAdsBlocked(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setKeyboardAvoidMode(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setEditMenuOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setEnableHapticFeedback(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setOptimizeParserBudget(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setEnableFollowSystemFontWeight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setEnableWebAVSession(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setRunJavaScriptOnDocumentStart(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setRunJavaScriptOnDocumentEnd(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setRunJavaScriptOnHeadEnd(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setNativeEmbedOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setRegisterNativeEmbedRule(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WebAttribute_setBindSelectionMenu(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _WindowScene_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _WindowSceneInterface_setWindowSceneOptions(ptr: KPointer, persistentId: number): void
    @ani.unsafe.Direct
    native static _WindowSceneAttribute_setAttractionEffect(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _XComponent_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _XComponentInterface_setXComponentOptions0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _XComponentInterface_setXComponentOptions1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _XComponentInterface_setXComponentOptions2(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _XComponentAttribute_setOnLoad(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _XComponentAttribute_setOnDestroy(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _XComponentAttribute_setEnableAnalyzer(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _XComponentAttribute_setEnableSecure(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _XComponentAttribute_setHdrBrightness(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _XComponentAttribute_setEnableTransparentLayer(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Root_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _ComponentRoot_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _CustomLayoutRoot_construct(id: KInt, flags: KInt): KPointer
    @ani.unsafe.Direct
    native static _CustomLayoutRoot_setSubscribeOnMeasureSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CustomLayoutRoot_setSubscribeOnPlaceChildren(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AccessibilityHoverEvent_construct(): KPointer
    @ani.unsafe.Direct
    native static _AccessibilityHoverEvent_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _AccessibilityHoverEvent_getType(ptr: KPointer): int32
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
    native static _AppearSymbolEffect_construct(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _AppearSymbolEffect_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _AppearSymbolEffect_getScope(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _AppearSymbolEffect_setScope(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AxisEvent_construct(): KPointer
    @ani.unsafe.Direct
    native static _AxisEvent_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _AxisEvent_getHorizontalAxisValue(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _AxisEvent_getVerticalAxisValue(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _AxisEvent_getAction(ptr: KPointer): int32
    @ani.unsafe.Direct
    native static _AxisEvent_setAction(ptr: KPointer, action: KInt): void
    @ani.unsafe.Direct
    native static _AxisEvent_getDisplayX(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _AxisEvent_setDisplayX(ptr: KPointer, displayX: number): void
    @ani.unsafe.Direct
    native static _AxisEvent_getDisplayY(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _AxisEvent_setDisplayY(ptr: KPointer, displayY: number): void
    @ani.unsafe.Direct
    native static _AxisEvent_getWindowX(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _AxisEvent_setWindowX(ptr: KPointer, windowX: number): void
    @ani.unsafe.Direct
    native static _AxisEvent_getWindowY(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _AxisEvent_setWindowY(ptr: KPointer, windowY: number): void
    @ani.unsafe.Direct
    native static _AxisEvent_getX(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _AxisEvent_setX(ptr: KPointer, x: number): void
    @ani.unsafe.Direct
    native static _AxisEvent_getY(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _AxisEvent_setY(ptr: KPointer, y: number): void
    @ani.unsafe.Quick
    native static _AxisEvent_getScrollStep(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _AxisEvent_setScrollStep(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _AxisEvent_getPropagation(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _AxisEvent_setPropagation(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _BackgroundColorStyle_construct(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _BackgroundColorStyle_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _BackgroundColorStyle_getTextBackgroundStyle(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _BaseContext_construct(): KPointer
    @ani.unsafe.Direct
    native static _BaseContext_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _BaseCustomDialog_construct(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _BaseCustomDialog_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _BaseCustomDialog_$_instantiate(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _BaseEvent_construct(): KPointer
    @ani.unsafe.Direct
    native static _BaseEvent_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _BaseEvent_getTarget(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _BaseEvent_setTarget(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _BaseEvent_getTimestamp(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _BaseEvent_setTimestamp(ptr: KPointer, timestamp: number): void
    @ani.unsafe.Direct
    native static _BaseEvent_getSource(ptr: KPointer): int32
    @ani.unsafe.Direct
    native static _BaseEvent_setSource(ptr: KPointer, source: KInt): void
    @ani.unsafe.Quick
    native static _BaseEvent_getAxisHorizontal(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _BaseEvent_setAxisHorizontal(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _BaseEvent_getAxisVertical(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _BaseEvent_setAxisVertical(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
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
    @ani.unsafe.Quick
    native static _BaseEvent_getRollAngle(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _BaseEvent_setRollAngle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _BaseEvent_getSourceTool(ptr: KPointer): int32
    @ani.unsafe.Direct
    native static _BaseEvent_setSourceTool(ptr: KPointer, sourceTool: KInt): void
    @ani.unsafe.Quick
    native static _BaseEvent_getGetModifierKeyState(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _BaseEvent_setGetModifierKeyState(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _BaseEvent_getDeviceId(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _BaseEvent_setDeviceId(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _BaseEvent_getTargetDisplayId(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _BaseEvent_setTargetDisplayId(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _BaseGestureEvent_construct(): KPointer
    @ani.unsafe.Direct
    native static _BaseGestureEvent_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _BaseGestureEvent_getFingerList(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _BaseGestureEvent_setFingerList(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _BaselineOffsetStyle_construct(value: KPointer): KPointer
    @ani.unsafe.Direct
    native static _BaselineOffsetStyle_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _BaselineOffsetStyle_getBaselineOffset(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _BaseShape_construct(): KPointer
    @ani.unsafe.Direct
    native static _BaseShape_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _BaseShape_width(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _BaseShape_height(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _BaseShape_size(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _BounceSymbolEffect_construct(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _BounceSymbolEffect_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _BounceSymbolEffect_getScope(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _BounceSymbolEffect_setScope(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _BounceSymbolEffect_getDirection(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _BounceSymbolEffect_setDirection(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _BuilderNodeOps_construct(): KPointer
    @ani.unsafe.Direct
    native static _BuilderNodeOps_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _BuilderNodeOps_create(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _BuilderNodeOps_disposeNode(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _BuilderNodeOps_setUpdateConfigurationCallback(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _BuilderNodeOps_setOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _BuilderNodeOps_postTouchEvent(ptr: KPointer, event: KPointer): boolean
    @ani.unsafe.Direct
    native static _BuilderNodeOps_setRootFrameNodeInBuilderNode(ptr: KPointer, node: KPointer): KPointer
    @ani.unsafe.Direct
    native static _CalendarPickerDialog_construct(): KPointer
    @ani.unsafe.Direct
    native static _CalendarPickerDialog_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _CalendarPickerDialog_show(thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CanvasGradient_construct(): KPointer
    @ani.unsafe.Direct
    native static _CanvasGradient_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _CanvasGradient_addColorStop(ptr: KPointer, offset: number, color: KStringPtr): void
    @ani.unsafe.Direct
    native static _CanvasPath_construct(): KPointer
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
    native static _CanvasPattern_construct(): KPointer
    @ani.unsafe.Direct
    native static _CanvasPattern_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _CanvasPattern_setTransform(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CanvasRenderer_construct(): KPointer
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
    native static _CanvasRenderer_stroke(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CanvasRenderer_createLinearGradient(ptr: KPointer, x0: number, y0: number, x1: number, y1: number): KPointer
    @ani.unsafe.Quick
    native static _CanvasRenderer_createPattern(ptr: KPointer, image: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KInteropReturnBuffer
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
    @ani.unsafe.Quick
    native static _CanvasRenderer_getLetterSpacing(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _CanvasRenderer_setLetterSpacing(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CanvasRenderer_getGlobalAlpha(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _CanvasRenderer_setGlobalAlpha(ptr: KPointer, globalAlpha: number): void
    @ani.unsafe.Quick
    native static _CanvasRenderer_getGlobalCompositeOperation(ptr: KPointer): string
    @ani.unsafe.Quick
    native static _CanvasRenderer_setGlobalCompositeOperation(ptr: KPointer, globalCompositeOperation: KStringPtr): void
    @ani.unsafe.Quick
    native static _CanvasRenderer_getFillStyle(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _CanvasRenderer_setFillStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _CanvasRenderer_getStrokeStyle(ptr: KPointer): KInteropReturnBuffer
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
    native static _CanvasRenderingContext2D_construct(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _CanvasRenderingContext2D_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _CanvasRenderingContext2D_toDataURL(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): string
    native static _CanvasRenderingContext2D_startImageAnalyzer(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _CanvasRenderingContext2D_stopImageAnalyzer(ptr: KPointer): void
    native static _CanvasRenderingContext2D_onOnAttach(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    native static _CanvasRenderingContext2D_offOnAttach(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CanvasRenderingContext2D_onOnDetach(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CanvasRenderingContext2D_offOnDetach(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CanvasRenderingContext2D_getHeight(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _CanvasRenderingContext2D_setHeight(ptr: KPointer, height: number): void
    @ani.unsafe.Direct
    native static _CanvasRenderingContext2D_getWidth(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _CanvasRenderingContext2D_setWidth(ptr: KPointer, width: number): void
    @ani.unsafe.Direct
    native static _CanvasRenderingContext2D_getCanvas(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _CanvasRenderingContext2D_setCanvas(ptr: KPointer, canvas: KPointer): void
    @ani.unsafe.Direct
    native static _ChildrenMainSize_construct(childDefaultSize: number): KPointer
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
    native static _CircleShape_construct(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _CircleShape_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _CircleShape_offset(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _CircleShape_fill(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _CircleShape_position(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _CircleShape_width(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _CircleShape_height(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _CircleShape_size(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _ClickEvent_construct(): KPointer
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
    native static _ClickEvent_getX(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _ClickEvent_setX(ptr: KPointer, x: number): void
    @ani.unsafe.Direct
    native static _ClickEvent_getY(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _ClickEvent_setY(ptr: KPointer, y: number): void
    @ani.unsafe.Quick
    native static _ClickEvent_getHand(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _ClickEvent_setHand(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ClickEvent_getPreventDefault(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _ClickEvent_setPreventDefault(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ClientAuthenticationHandler_construct(): KPointer
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
    native static _ColorContent_construct(): KPointer
    @ani.unsafe.Direct
    native static _ColorContent_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _ColorContent_getORIGIN(): KPointer
    @ani.unsafe.Direct
    native static _ColorFilter_construct(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _ColorFilter_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _ColorMetrics_construct(): KPointer
    @ani.unsafe.Direct
    native static _ColorMetrics_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _ColorMetrics_numeric(value: number): KPointer
    @ani.unsafe.Direct
    native static _ColorMetrics_rgba(red: number, green: number, blue: number, alpha: number): KPointer
    @ani.unsafe.Direct
    native static _ColorMetrics_resourceColor(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _ColorMetrics_blendColor(ptr: KPointer, overlayColor: KPointer): KPointer
    @ani.unsafe.Quick
    native static _ColorMetrics_color(ptr: KPointer): string
    @ani.unsafe.Direct
    native static _ColorMetrics_red(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _ColorMetrics_green(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _ColorMetrics_blue(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _ColorMetrics_alpha(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _common_Context_construct(): KPointer
    @ani.unsafe.Direct
    native static _common_Context_getFinalizer(): KPointer
    native static _common_Context_createBundleContext(ptr: KPointer, bundleName: KStringPtr): KPointer
    native static _common_Context_createModuleContext0(ptr: KPointer, moduleName: KStringPtr): KPointer
    native static _common_Context_createModuleContext1(ptr: KPointer, bundleName: KStringPtr, moduleName: KStringPtr): KPointer
    native static _common_Context_getGroupDir0(ptr: KPointer, dataGroupID: KStringPtr, thisArray: KSerializerBuffer, thisLength: int32): void
    native static _common_Context_getGroupDir1(ptr: KPointer, dataGroupID: KStringPtr, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Quick
    native static _common_Context_getCacheDir(ptr: KPointer): string
    @ani.unsafe.Quick
    native static _common_Context_setCacheDir(ptr: KPointer, cacheDir: KStringPtr): void
    @ani.unsafe.Quick
    native static _common_Context_getTempDir(ptr: KPointer): string
    @ani.unsafe.Quick
    native static _common_Context_setTempDir(ptr: KPointer, tempDir: KStringPtr): void
    @ani.unsafe.Quick
    native static _common_Context_getFilesDir(ptr: KPointer): string
    @ani.unsafe.Quick
    native static _common_Context_setFilesDir(ptr: KPointer, filesDir: KStringPtr): void
    @ani.unsafe.Quick
    native static _common_Context_getDatabaseDir(ptr: KPointer): string
    @ani.unsafe.Quick
    native static _common_Context_setDatabaseDir(ptr: KPointer, databaseDir: KStringPtr): void
    @ani.unsafe.Quick
    native static _common_Context_getPreferencesDir(ptr: KPointer): string
    @ani.unsafe.Quick
    native static _common_Context_setPreferencesDir(ptr: KPointer, preferencesDir: KStringPtr): void
    @ani.unsafe.Quick
    native static _common_Context_getBundleCodeDir(ptr: KPointer): string
    @ani.unsafe.Quick
    native static _common_Context_setBundleCodeDir(ptr: KPointer, bundleCodeDir: KStringPtr): void
    @ani.unsafe.Quick
    native static _common_Context_getDistributedFilesDir(ptr: KPointer): string
    @ani.unsafe.Quick
    native static _common_Context_setDistributedFilesDir(ptr: KPointer, distributedFilesDir: KStringPtr): void
    @ani.unsafe.Quick
    native static _common_Context_getResourceDir(ptr: KPointer): string
    @ani.unsafe.Quick
    native static _common_Context_setResourceDir(ptr: KPointer, resourceDir: KStringPtr): void
    @ani.unsafe.Quick
    native static _common_Context_getCloudFileDir(ptr: KPointer): string
    @ani.unsafe.Quick
    native static _common_Context_setCloudFileDir(ptr: KPointer, cloudFileDir: KStringPtr): void
    @ani.unsafe.Direct
    native static _CommonShape_construct(): KPointer
    @ani.unsafe.Direct
    native static _CommonShape_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _CommonShape_offset(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _CommonShape_fill(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _CommonShape_position(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _ComponentContent_construct(): KPointer
    @ani.unsafe.Direct
    native static _ComponentContent_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _ComponentContent_update(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ComponentContent_reuse(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ComponentContent_recycle(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _ComponentContent_dispose(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _ComponentContent_updateConfiguration(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _ConsoleMessage_construct(): KPointer
    @ani.unsafe.Direct
    native static _ConsoleMessage_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _ConsoleMessage_getMessage(ptr: KPointer): string
    @ani.unsafe.Quick
    native static _ConsoleMessage_getSourceId(ptr: KPointer): string
    @ani.unsafe.Direct
    native static _ConsoleMessage_getLineNumber(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _ConsoleMessage_getMessageLevel(ptr: KPointer): int32
    @ani.unsafe.Direct
    native static _ContentModifierHelper_contentModifierButton(node: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ContentModifierHelper_contentModifierCheckBox(node: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ContentModifierHelper_contentModifierDataPanel(node: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ContentModifierHelper_contentModifierGauge(node: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ContentModifierHelper_contentModifierLoadingProgress(node: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ContentModifierHelper_contentModifierProgress(node: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ContentModifierHelper_contentModifierRadio(node: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ContentModifierHelper_contentModifierRating(node: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ContentModifierHelper_contentModifierMenuItem(node: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ContentModifierHelper_contentModifierSlider(node: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ContentModifierHelper_contentModifierTextClock(node: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ContentModifierHelper_contentModifierTextTimer(node: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ContentModifierHelper_contentModifierToggle(node: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Context_construct(): KPointer
    @ani.unsafe.Direct
    native static _Context_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _ControllerHandler_construct(): KPointer
    @ani.unsafe.Direct
    native static _ControllerHandler_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _ControllerHandler_setWebController(ptr: KPointer, controller: KPointer): void
    @ani.unsafe.Direct
    native static _curves_ICurve_construct(): KPointer
    @ani.unsafe.Direct
    native static _curves_ICurve_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _curves_ICurve_interpolate(ptr: KPointer, fraction: number): number
    @ani.unsafe.Direct
    native static _CustomDialogController_construct(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _CustomDialogController_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _CustomDialogController_open(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _CustomDialogController_close(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _CustomSpan_construct(): KPointer
    @ani.unsafe.Direct
    native static _CustomSpan_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _CustomSpan_invalidate(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _CustomSpan_getOnMeasure(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _CustomSpan_setOnMeasure(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _CustomSpan_getOnDraw(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _CustomSpan_setOnDraw(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _DataResubmissionHandler_construct(): KPointer
    @ani.unsafe.Direct
    native static _DataResubmissionHandler_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _DataResubmissionHandler_resend(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _DataResubmissionHandler_cancel(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _DatePickerDialog_construct(): KPointer
    @ani.unsafe.Direct
    native static _DatePickerDialog_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _DecorationStyle_construct(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _DecorationStyle_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _DecorationStyle_getType(ptr: KPointer): int32
    @ani.unsafe.Quick
    native static _DecorationStyle_getColor(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _DecorationStyle_getStyle(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _DisappearSymbolEffect_construct(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _DisappearSymbolEffect_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _DisappearSymbolEffect_getScope(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _DisappearSymbolEffect_setScope(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _DismissDialogAction_construct(): KPointer
    @ani.unsafe.Direct
    native static _DismissDialogAction_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _DismissDialogAction_dismiss(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _DismissDialogAction_getReason(ptr: KPointer): int32
    @ani.unsafe.Direct
    native static _DismissDialogAction_setReason(ptr: KPointer, reason: KInt): void
    @ani.unsafe.Direct
    native static _DismissPopupAction_construct(): KPointer
    @ani.unsafe.Direct
    native static _DismissPopupAction_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _DismissPopupAction_dismiss(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _DismissPopupAction_getReason(ptr: KPointer): int32
    @ani.unsafe.Direct
    native static _DismissPopupAction_setReason(ptr: KPointer, reason: KInt): void
    @ani.unsafe.Direct
    native static _DragEvent_construct(): KPointer
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
    native static _DragEvent_setData(ptr: KPointer, unifiedData: KPointer): void
    @ani.unsafe.Direct
    native static _DragEvent_getData(ptr: KPointer): KPointer
    @ani.unsafe.Quick
    native static _DragEvent_getSummary(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _DragEvent_setResult(ptr: KPointer, dragResult: KInt): void
    @ani.unsafe.Direct
    native static _DragEvent_getResult(ptr: KPointer): int32
    @ani.unsafe.Quick
    native static _DragEvent_getPreviewRect(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _DragEvent_getVelocityX(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _DragEvent_getVelocityY(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _DragEvent_getVelocity(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _DragEvent_executeDropAnimation(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _DragEvent_getDragBehavior(ptr: KPointer): int32
    @ani.unsafe.Direct
    native static _DragEvent_setDragBehavior(ptr: KPointer, dragBehavior: KInt): void
    @ani.unsafe.Direct
    native static _DragEvent_getUseCustomDropAnimation(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _DragEvent_setUseCustomDropAnimation(ptr: KPointer, useCustomDropAnimation: KInt): void
    @ani.unsafe.Quick
    native static _DragEvent_getGetModifierKeyState(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _DragEvent_setGetModifierKeyState(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _DrawableDescriptor_construct(): KPointer
    @ani.unsafe.Direct
    native static _DrawableDescriptor_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _DrawableDescriptor_getPixelMap(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _DrawContext_construct(): KPointer
    @ani.unsafe.Direct
    native static _DrawContext_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _DrawContext_size(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _DrawContext_sizeInPixel(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _DrawContext_canvas(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _drawing_Brush_construct0(): KPointer
    @ani.unsafe.Direct
    native static _drawing_Brush_construct1(brush: KPointer): KPointer
    @ani.unsafe.Direct
    native static _drawing_Brush_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _drawing_Brush_setColor0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _drawing_Brush_setColor1(ptr: KPointer, color: number): void
    @ani.unsafe.Direct
    native static _drawing_Brush_setColor2(ptr: KPointer, alpha: number, red: number, green: number, blue: number): void
    @ani.unsafe.Quick
    native static _drawing_Brush_getColor(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _drawing_Brush_getHexColor(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _drawing_Brush_setAntiAlias(ptr: KPointer, aa: KInt): void
    @ani.unsafe.Direct
    native static _drawing_Brush_isAntiAlias(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _drawing_Brush_setAlpha(ptr: KPointer, alpha: number): void
    @ani.unsafe.Direct
    native static _drawing_Brush_getAlpha(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _drawing_Brush_setColorFilter(ptr: KPointer, filter: KPointer): void
    @ani.unsafe.Direct
    native static _drawing_Brush_getColorFilter(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _drawing_Brush_setImageFilter(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _drawing_Brush_setMaskFilter(ptr: KPointer, filter: KPointer): void
    @ani.unsafe.Direct
    native static _drawing_Brush_setShadowLayer(ptr: KPointer, shadowLayer: KPointer): void
    @ani.unsafe.Direct
    native static _drawing_Brush_setShaderEffect(ptr: KPointer, shaderEffect: KPointer): void
    @ani.unsafe.Direct
    native static _drawing_Brush_setBlendMode(ptr: KPointer, mode: KInt): void
    @ani.unsafe.Direct
    native static _drawing_Brush_reset(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _drawing_Canvas_construct(pixelmap: KPointer): KPointer
    @ani.unsafe.Direct
    native static _drawing_Canvas_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _drawing_Canvas_drawRect0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _drawing_Canvas_drawRect1(ptr: KPointer, left: number, top: number, right: number, bottom: number): void
    @ani.unsafe.Direct
    native static _drawing_Canvas_drawRoundRect(ptr: KPointer, roundRect: KPointer): void
    @ani.unsafe.Direct
    native static _drawing_Canvas_drawNestedRoundRect(ptr: KPointer, outer: KPointer, inner: KPointer): void
    @ani.unsafe.Direct
    native static _drawing_Canvas_drawBackground(ptr: KPointer, brush: KPointer): void
    @ani.unsafe.Direct
    native static _drawing_Canvas_drawShadow0(ptr: KPointer, path: KPointer, thisArray: KSerializerBuffer, thisLength: int32, lightRadius: number, flag: KInt): void
    @ani.unsafe.Direct
    native static _drawing_Canvas_drawShadow1(ptr: KPointer, path: KPointer, thisArray: KSerializerBuffer, thisLength: int32, lightRadius: number, ambientColor: number, spotColor: number, flag: KInt): void
    @ani.unsafe.Direct
    native static _drawing_Canvas_drawCircle(ptr: KPointer, x: number, y: number, radius: number): void
    @ani.unsafe.Direct
    native static _drawing_Canvas_drawImage(ptr: KPointer, pixelmap: KPointer, left: number, top: number, samplingOptions: KPointer): void
    @ani.unsafe.Direct
    native static _drawing_Canvas_drawImageRect(ptr: KPointer, pixelmap: KPointer, thisArray: KSerializerBuffer, thisLength: int32, samplingOptions: KPointer): void
    @ani.unsafe.Direct
    native static _drawing_Canvas_drawImageRectWithSrc(ptr: KPointer, pixelmap: KPointer, thisArray: KSerializerBuffer, thisLength: int32, samplingOptions: KPointer, constraint: KInt): void
    @ani.unsafe.Direct
    native static _drawing_Canvas_drawColor0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32, blendMode: KInt): void
    @ani.unsafe.Direct
    native static _drawing_Canvas_drawColor1(ptr: KPointer, color: number, blendMode: KInt): void
    @ani.unsafe.Direct
    native static _drawing_Canvas_drawColor2(ptr: KPointer, alpha: number, red: number, green: number, blue: number, blendMode: KInt): void
    @ani.unsafe.Direct
    native static _drawing_Canvas_drawOval(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _drawing_Canvas_drawArc(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32, startAngle: number, sweepAngle: number): void
    @ani.unsafe.Direct
    native static _drawing_Canvas_drawPoint(ptr: KPointer, x: number, y: number): void
    @ani.unsafe.Direct
    native static _drawing_Canvas_drawPoints(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32, mode: KInt): void
    @ani.unsafe.Direct
    native static _drawing_Canvas_drawPath(ptr: KPointer, path: KPointer): void
    @ani.unsafe.Direct
    native static _drawing_Canvas_drawLine(ptr: KPointer, x0: number, y0: number, x1: number, y1: number): void
    @ani.unsafe.Quick
    native static _drawing_Canvas_drawSingleCharacter(ptr: KPointer, text: KStringPtr, font: KPointer, x: number, y: number): void
    @ani.unsafe.Direct
    native static _drawing_Canvas_drawTextBlob(ptr: KPointer, blob: KPointer, x: number, y: number): void
    @ani.unsafe.Direct
    native static _drawing_Canvas_drawPixelMapMesh(ptr: KPointer, pixelmap: KPointer, meshWidth: number, meshHeight: number, thisArray: KSerializerBuffer, thisLength: int32, vertOffset: number, colorOffset: number): void
    @ani.unsafe.Direct
    native static _drawing_Canvas_drawRegion(ptr: KPointer, region: KPointer): void
    @ani.unsafe.Direct
    native static _drawing_Canvas_attachPen(ptr: KPointer, pen: KPointer): void
    @ani.unsafe.Direct
    native static _drawing_Canvas_attachBrush(ptr: KPointer, brush: KPointer): void
    @ani.unsafe.Direct
    native static _drawing_Canvas_detachPen(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _drawing_Canvas_detachBrush(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _drawing_Canvas_save(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _drawing_Canvas_saveLayer(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): number
    @ani.unsafe.Direct
    native static _drawing_Canvas_clear0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _drawing_Canvas_clear1(ptr: KPointer, color: number): void
    @ani.unsafe.Direct
    native static _drawing_Canvas_restore(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _drawing_Canvas_restoreToCount(ptr: KPointer, count: number): void
    @ani.unsafe.Direct
    native static _drawing_Canvas_getSaveCount(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _drawing_Canvas_getWidth(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _drawing_Canvas_getHeight(ptr: KPointer): number
    @ani.unsafe.Quick
    native static _drawing_Canvas_getLocalClipBounds(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _drawing_Canvas_getTotalMatrix(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _drawing_Canvas_scale(ptr: KPointer, sx: number, sy: number): void
    @ani.unsafe.Direct
    native static _drawing_Canvas_skew(ptr: KPointer, sx: number, sy: number): void
    @ani.unsafe.Direct
    native static _drawing_Canvas_rotate(ptr: KPointer, degrees: number, sx: number, sy: number): void
    @ani.unsafe.Direct
    native static _drawing_Canvas_translate(ptr: KPointer, dx: number, dy: number): void
    @ani.unsafe.Direct
    native static _drawing_Canvas_clipPath(ptr: KPointer, path: KPointer, clipOp: KInt, doAntiAlias: KInt): void
    @ani.unsafe.Direct
    native static _drawing_Canvas_clipRect(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32, clipOp: KInt, doAntiAlias: KInt): void
    @ani.unsafe.Direct
    native static _drawing_Canvas_concatMatrix(ptr: KPointer, matrix: KPointer): void
    @ani.unsafe.Direct
    native static _drawing_Canvas_clipRegion(ptr: KPointer, region: KPointer, clipOp: KInt): void
    @ani.unsafe.Direct
    native static _drawing_Canvas_clipRoundRect(ptr: KPointer, roundRect: KPointer, clipOp: KInt, doAntiAlias: KInt): void
    @ani.unsafe.Direct
    native static _drawing_Canvas_isClipEmpty(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _drawing_Canvas_setMatrix(ptr: KPointer, matrix: KPointer): void
    @ani.unsafe.Direct
    native static _drawing_Canvas_resetMatrix(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _drawing_ColorFilter_construct(): KPointer
    @ani.unsafe.Direct
    native static _drawing_ColorFilter_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _drawing_ColorFilter_createBlendModeColorFilter0(thisArray: KSerializerBuffer, thisLength: int32, mode: KInt): KPointer
    @ani.unsafe.Direct
    native static _drawing_ColorFilter_createBlendModeColorFilter1(color: number, mode: KInt): KPointer
    @ani.unsafe.Direct
    native static _drawing_ColorFilter_createComposeColorFilter(outer: KPointer, inner: KPointer): KPointer
    @ani.unsafe.Direct
    native static _drawing_ColorFilter_createLinearToSRGBGamma(): KPointer
    @ani.unsafe.Direct
    native static _drawing_ColorFilter_createSRGBGammaToLinear(): KPointer
    @ani.unsafe.Direct
    native static _drawing_ColorFilter_createLumaColorFilter(): KPointer
    @ani.unsafe.Direct
    native static _drawing_ColorFilter_createMatrixColorFilter(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _drawing_Font_construct(): KPointer
    @ani.unsafe.Direct
    native static _drawing_Font_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _drawing_Font_enableSubpixel(ptr: KPointer, isSubpixel: KInt): void
    @ani.unsafe.Direct
    native static _drawing_Font_enableEmbolden(ptr: KPointer, isEmbolden: KInt): void
    @ani.unsafe.Direct
    native static _drawing_Font_enableLinearMetrics(ptr: KPointer, isLinearMetrics: KInt): void
    @ani.unsafe.Direct
    native static _drawing_Font_setSize(ptr: KPointer, textSize: number): void
    @ani.unsafe.Direct
    native static _drawing_Font_getSize(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _drawing_Font_setTypeface(ptr: KPointer, typeface: KPointer): void
    @ani.unsafe.Direct
    native static _drawing_Font_getTypeface(ptr: KPointer): KPointer
    @ani.unsafe.Quick
    native static _drawing_Font_getMetrics(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _drawing_Font_measureSingleCharacter(ptr: KPointer, text: KStringPtr): number
    @ani.unsafe.Quick
    native static _drawing_Font_measureText(ptr: KPointer, text: KStringPtr, encoding: KInt): number
    @ani.unsafe.Direct
    native static _drawing_Font_setScaleX(ptr: KPointer, scaleX: number): void
    @ani.unsafe.Direct
    native static _drawing_Font_setSkewX(ptr: KPointer, skewX: number): void
    @ani.unsafe.Direct
    native static _drawing_Font_setEdging(ptr: KPointer, edging: KInt): void
    @ani.unsafe.Direct
    native static _drawing_Font_setHinting(ptr: KPointer, hinting: KInt): void
    @ani.unsafe.Quick
    native static _drawing_Font_countText(ptr: KPointer, text: KStringPtr): number
    @ani.unsafe.Direct
    native static _drawing_Font_setBaselineSnap(ptr: KPointer, isBaselineSnap: KInt): void
    @ani.unsafe.Direct
    native static _drawing_Font_isBaselineSnap(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _drawing_Font_setEmbeddedBitmaps(ptr: KPointer, isEmbeddedBitmaps: KInt): void
    @ani.unsafe.Direct
    native static _drawing_Font_isEmbeddedBitmaps(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _drawing_Font_setForceAutoHinting(ptr: KPointer, isForceAutoHinting: KInt): void
    @ani.unsafe.Direct
    native static _drawing_Font_isForceAutoHinting(ptr: KPointer): boolean
    @ani.unsafe.Quick
    native static _drawing_Font_getWidths(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _drawing_Font_textToGlyphs(ptr: KPointer, text: KStringPtr, glyphCount: number): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _drawing_Font_isSubpixel(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _drawing_Font_isLinearMetrics(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _drawing_Font_getSkewX(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _drawing_Font_isEmbolden(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _drawing_Font_getScaleX(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _drawing_Font_getHinting(ptr: KPointer): int32
    @ani.unsafe.Direct
    native static _drawing_Font_getEdging(ptr: KPointer): int32
    @ani.unsafe.Direct
    native static _drawing_Font_createPathForGlyph(ptr: KPointer, index: number): KPointer
    @ani.unsafe.Quick
    native static _drawing_Font_getBounds(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _drawing_Font_getTextPath(ptr: KPointer, text: KStringPtr, byteLength: number, x: number, y: number): KPointer
    @ani.unsafe.Direct
    native static _drawing_ImageFilter_construct(): KPointer
    @ani.unsafe.Direct
    native static _drawing_ImageFilter_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _drawing_ImageFilter_createBlurImageFilter(sigmaX: number, sigmaY: number, tileMode: KInt, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _drawing_ImageFilter_createFromColorFilter(colorFilter: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _drawing_Lattice_construct(): KPointer
    @ani.unsafe.Direct
    native static _drawing_Lattice_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _drawing_Lattice_createImageLattice(thisArray: KSerializerBuffer, thisLength: int32, fXCount: number, fYCount: number): KPointer
    @ani.unsafe.Direct
    native static _drawing_MaskFilter_construct(): KPointer
    @ani.unsafe.Direct
    native static _drawing_MaskFilter_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _drawing_MaskFilter_createBlurMaskFilter(blurType: KInt, sigma: number): KPointer
    @ani.unsafe.Direct
    native static _drawing_Matrix_construct(): KPointer
    @ani.unsafe.Direct
    native static _drawing_Matrix_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _drawing_Matrix_setRotation(ptr: KPointer, degree: number, px: number, py: number): void
    @ani.unsafe.Direct
    native static _drawing_Matrix_setScale(ptr: KPointer, sx: number, sy: number, px: number, py: number): void
    @ani.unsafe.Direct
    native static _drawing_Matrix_setTranslation(ptr: KPointer, dx: number, dy: number): void
    @ani.unsafe.Direct
    native static _drawing_Matrix_setMatrix(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _drawing_Matrix_preConcat(ptr: KPointer, matrix: KPointer): void
    @ani.unsafe.Direct
    native static _drawing_Matrix_isEqual(ptr: KPointer, matrix: KPointer): boolean
    @ani.unsafe.Direct
    native static _drawing_Matrix_invert(ptr: KPointer, matrix: KPointer): boolean
    @ani.unsafe.Direct
    native static _drawing_Matrix_isIdentity(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _drawing_Matrix_getValue(ptr: KPointer, index: number): number
    @ani.unsafe.Direct
    native static _drawing_Matrix_postRotate(ptr: KPointer, degree: number, px: number, py: number): void
    @ani.unsafe.Direct
    native static _drawing_Matrix_postScale(ptr: KPointer, sx: number, sy: number, px: number, py: number): void
    @ani.unsafe.Direct
    native static _drawing_Matrix_postTranslate(ptr: KPointer, dx: number, dy: number): void
    @ani.unsafe.Direct
    native static _drawing_Matrix_preRotate(ptr: KPointer, degree: number, px: number, py: number): void
    @ani.unsafe.Direct
    native static _drawing_Matrix_preScale(ptr: KPointer, sx: number, sy: number, px: number, py: number): void
    @ani.unsafe.Direct
    native static _drawing_Matrix_preTranslate(ptr: KPointer, dx: number, dy: number): void
    @ani.unsafe.Direct
    native static _drawing_Matrix_reset(ptr: KPointer): void
    @ani.unsafe.Quick
    native static _drawing_Matrix_mapPoints(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _drawing_Matrix_getAll(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _drawing_Matrix_mapRect(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): boolean
    @ani.unsafe.Direct
    native static _drawing_Matrix_setRectToRect(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32, scaleToFit: KInt): boolean
    @ani.unsafe.Direct
    native static _drawing_Matrix_setPolyToPoly(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32, count: number): boolean
    @ani.unsafe.Direct
    native static _drawing_Path_construct0(): KPointer
    @ani.unsafe.Direct
    native static _drawing_Path_construct1(path: KPointer): KPointer
    @ani.unsafe.Direct
    native static _drawing_Path_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _drawing_Path_moveTo(ptr: KPointer, x: number, y: number): void
    @ani.unsafe.Direct
    native static _drawing_Path_lineTo(ptr: KPointer, x: number, y: number): void
    @ani.unsafe.Direct
    native static _drawing_Path_arcTo(ptr: KPointer, x1: number, y1: number, x2: number, y2: number, startDeg: number, sweepDeg: number): void
    @ani.unsafe.Direct
    native static _drawing_Path_quadTo(ptr: KPointer, ctrlX: number, ctrlY: number, endX: number, endY: number): void
    @ani.unsafe.Direct
    native static _drawing_Path_conicTo(ptr: KPointer, ctrlX: number, ctrlY: number, endX: number, endY: number, weight: number): void
    @ani.unsafe.Direct
    native static _drawing_Path_cubicTo(ptr: KPointer, ctrlX1: number, ctrlY1: number, ctrlX2: number, ctrlY2: number, endX: number, endY: number): void
    @ani.unsafe.Direct
    native static _drawing_Path_rMoveTo(ptr: KPointer, dx: number, dy: number): void
    @ani.unsafe.Direct
    native static _drawing_Path_rLineTo(ptr: KPointer, dx: number, dy: number): void
    @ani.unsafe.Direct
    native static _drawing_Path_rQuadTo(ptr: KPointer, dx1: number, dy1: number, dx2: number, dy2: number): void
    @ani.unsafe.Direct
    native static _drawing_Path_rConicTo(ptr: KPointer, ctrlX: number, ctrlY: number, endX: number, endY: number, weight: number): void
    @ani.unsafe.Direct
    native static _drawing_Path_rCubicTo(ptr: KPointer, ctrlX1: number, ctrlY1: number, ctrlX2: number, ctrlY2: number, endX: number, endY: number): void
    @ani.unsafe.Direct
    native static _drawing_Path_addPolygon(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32, close: KInt): void
    @ani.unsafe.Direct
    native static _drawing_Path_op(ptr: KPointer, path: KPointer, pathOp: KInt): boolean
    @ani.unsafe.Direct
    native static _drawing_Path_addArc(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32, startAngle: number, sweepAngle: number): void
    @ani.unsafe.Direct
    native static _drawing_Path_addCircle(ptr: KPointer, x: number, y: number, radius: number, pathDirection: KInt): void
    @ani.unsafe.Direct
    native static _drawing_Path_addOval(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32, start: number, pathDirection: KInt): void
    @ani.unsafe.Direct
    native static _drawing_Path_addRect(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32, pathDirection: KInt): void
    @ani.unsafe.Direct
    native static _drawing_Path_addRoundRect(ptr: KPointer, roundRect: KPointer, pathDirection: KInt): void
    @ani.unsafe.Direct
    native static _drawing_Path_addPath(ptr: KPointer, path: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _drawing_Path_transform(ptr: KPointer, matrix: KPointer): void
    @ani.unsafe.Direct
    native static _drawing_Path_contains(ptr: KPointer, x: number, y: number): boolean
    @ani.unsafe.Direct
    native static _drawing_Path_setFillType(ptr: KPointer, pathFillType: KInt): void
    @ani.unsafe.Quick
    native static _drawing_Path_getBounds(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _drawing_Path_close(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _drawing_Path_offset(ptr: KPointer, dx: number, dy: number): KPointer
    @ani.unsafe.Direct
    native static _drawing_Path_reset(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _drawing_Path_getLength(ptr: KPointer, forceClosed: KInt): number
    @ani.unsafe.Direct
    native static _drawing_Path_getPositionAndTangent(ptr: KPointer, forceClosed: KInt, distance: number, thisArray: KSerializerBuffer, thisLength: int32): boolean
    @ani.unsafe.Direct
    native static _drawing_Path_isClosed(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _drawing_Path_getMatrix(ptr: KPointer, forceClosed: KInt, distance: number, matrix: KPointer, flags: KInt): boolean
    @ani.unsafe.Quick
    native static _drawing_Path_buildFromSvgString(ptr: KPointer, str: KStringPtr): boolean
    @ani.unsafe.Direct
    native static _drawing_PathEffect_construct(): KPointer
    @ani.unsafe.Direct
    native static _drawing_PathEffect_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _drawing_PathEffect_createDashPathEffect(thisArray: KSerializerBuffer, thisLength: int32, phase: number): KPointer
    @ani.unsafe.Direct
    native static _drawing_PathEffect_createCornerPathEffect(radius: number): KPointer
    @ani.unsafe.Direct
    native static _drawing_Pen_construct0(): KPointer
    @ani.unsafe.Direct
    native static _drawing_Pen_construct1(pen: KPointer): KPointer
    @ani.unsafe.Direct
    native static _drawing_Pen_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _drawing_Pen_setMiterLimit(ptr: KPointer, miter: number): void
    @ani.unsafe.Direct
    native static _drawing_Pen_getMiterLimit(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _drawing_Pen_setShaderEffect(ptr: KPointer, shaderEffect: KPointer): void
    @ani.unsafe.Direct
    native static _drawing_Pen_setColor0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _drawing_Pen_setColor1(ptr: KPointer, color: number): void
    @ani.unsafe.Direct
    native static _drawing_Pen_setColor2(ptr: KPointer, alpha: number, red: number, green: number, blue: number): void
    @ani.unsafe.Quick
    native static _drawing_Pen_getColor(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _drawing_Pen_getHexColor(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _drawing_Pen_setStrokeWidth(ptr: KPointer, width: number): void
    @ani.unsafe.Direct
    native static _drawing_Pen_getWidth(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _drawing_Pen_setAntiAlias(ptr: KPointer, aa: KInt): void
    @ani.unsafe.Direct
    native static _drawing_Pen_isAntiAlias(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _drawing_Pen_setAlpha(ptr: KPointer, alpha: number): void
    @ani.unsafe.Direct
    native static _drawing_Pen_getAlpha(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _drawing_Pen_setColorFilter(ptr: KPointer, filter: KPointer): void
    @ani.unsafe.Direct
    native static _drawing_Pen_getColorFilter(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _drawing_Pen_setImageFilter(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _drawing_Pen_setMaskFilter(ptr: KPointer, filter: KPointer): void
    @ani.unsafe.Direct
    native static _drawing_Pen_setPathEffect(ptr: KPointer, effect: KPointer): void
    @ani.unsafe.Direct
    native static _drawing_Pen_setShadowLayer(ptr: KPointer, shadowLayer: KPointer): void
    @ani.unsafe.Direct
    native static _drawing_Pen_setBlendMode(ptr: KPointer, mode: KInt): void
    @ani.unsafe.Direct
    native static _drawing_Pen_setDither(ptr: KPointer, dither: KInt): void
    @ani.unsafe.Direct
    native static _drawing_Pen_setJoinStyle(ptr: KPointer, style: KInt): void
    @ani.unsafe.Direct
    native static _drawing_Pen_getJoinStyle(ptr: KPointer): int32
    @ani.unsafe.Direct
    native static _drawing_Pen_setCapStyle(ptr: KPointer, style: KInt): void
    @ani.unsafe.Direct
    native static _drawing_Pen_getCapStyle(ptr: KPointer): int32
    @ani.unsafe.Direct
    native static _drawing_Pen_reset(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _drawing_Pen_getFillPath(ptr: KPointer, src: KPointer, dst: KPointer): boolean
    @ani.unsafe.Direct
    native static _drawing_Region_construct(): KPointer
    @ani.unsafe.Direct
    native static _drawing_Region_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _drawing_Region_isPointContained(ptr: KPointer, x: number, y: number): boolean
    @ani.unsafe.Direct
    native static _drawing_Region_isRegionContained(ptr: KPointer, other: KPointer): boolean
    @ani.unsafe.Direct
    native static _drawing_Region_op(ptr: KPointer, region: KPointer, regionOp: KInt): boolean
    @ani.unsafe.Direct
    native static _drawing_Region_quickReject(ptr: KPointer, left: number, top: number, right: number, bottom: number): boolean
    @ani.unsafe.Direct
    native static _drawing_Region_setPath(ptr: KPointer, path: KPointer, clip: KPointer): boolean
    @ani.unsafe.Direct
    native static _drawing_Region_setRect(ptr: KPointer, left: number, top: number, right: number, bottom: number): boolean
    @ani.unsafe.Direct
    native static _drawing_RoundRect_construct(thisArray: KSerializerBuffer, thisLength: int32, xRadii: number, yRadii: number): KPointer
    @ani.unsafe.Direct
    native static _drawing_RoundRect_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _drawing_RoundRect_setCorner(ptr: KPointer, pos: KInt, x: number, y: number): void
    @ani.unsafe.Quick
    native static _drawing_RoundRect_getCorner(ptr: KPointer, pos: KInt): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _drawing_RoundRect_offset(ptr: KPointer, dx: number, dy: number): void
    @ani.unsafe.Direct
    native static _drawing_SamplingOptions_construct0(): KPointer
    @ani.unsafe.Direct
    native static _drawing_SamplingOptions_construct1(filterMode: KInt): KPointer
    @ani.unsafe.Direct
    native static _drawing_SamplingOptions_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _drawing_ShaderEffect_construct(): KPointer
    @ani.unsafe.Direct
    native static _drawing_ShaderEffect_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _drawing_ShaderEffect_createColorShader(color: number): KPointer
    @ani.unsafe.Direct
    native static _drawing_ShaderEffect_createLinearGradient(thisArray: KSerializerBuffer, thisLength: int32, mode: KInt): KPointer
    @ani.unsafe.Direct
    native static _drawing_ShaderEffect_createRadialGradient(thisArray: KSerializerBuffer, thisLength: int32, radius: number, mode: KInt): KPointer
    @ani.unsafe.Direct
    native static _drawing_ShaderEffect_createSweepGradient(thisArray: KSerializerBuffer, thisLength: int32, mode: KInt, startAngle: number, endAngle: number): KPointer
    @ani.unsafe.Direct
    native static _drawing_ShaderEffect_createConicalGradient(thisArray: KSerializerBuffer, thisLength: int32, startRadius: number, endRadius: number, mode: KInt): KPointer
    @ani.unsafe.Direct
    native static _drawing_ShadowLayer_construct(): KPointer
    @ani.unsafe.Direct
    native static _drawing_ShadowLayer_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _drawing_ShadowLayer_create0(blurRadius: number, x: number, y: number, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _drawing_ShadowLayer_create1(blurRadius: number, x: number, y: number, color: number): KPointer
    @ani.unsafe.Direct
    native static _drawing_TextBlob_construct(): KPointer
    @ani.unsafe.Direct
    native static _drawing_TextBlob_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _drawing_TextBlob_makeFromString(text: KStringPtr, font: KPointer, encoding: KInt): KPointer
    @ani.unsafe.Quick
    native static _drawing_TextBlob_makeFromPosText(text: KStringPtr, len: number, thisArray: KSerializerBuffer, thisLength: int32, font: KPointer): KPointer
    @ani.unsafe.Direct
    native static _drawing_TextBlob_makeFromRunBuffer(thisArray: KSerializerBuffer, thisLength: int32, font: KPointer): KPointer
    @ani.unsafe.Quick
    native static _drawing_TextBlob_bounds(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _drawing_TextBlob_uniqueID(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _drawing_Typeface_construct(): KPointer
    @ani.unsafe.Direct
    native static _drawing_Typeface_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _drawing_Typeface_getFamilyName(ptr: KPointer): string
    @ani.unsafe.Quick
    native static _drawing_Typeface_makeFromFile(filePath: KStringPtr): KPointer
    @ani.unsafe.Direct
    native static _DrawingRenderingContext_construct(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _DrawingRenderingContext_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _DrawingRenderingContext_invalidate(ptr: KPointer): void
    @ani.unsafe.Quick
    native static _DrawingRenderingContext_getSize(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _DrawingRenderingContext_setSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _DrawModifier_construct(): KPointer
    @ani.unsafe.Direct
    native static _DrawModifier_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _DrawModifier_invalidate(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _DrawModifier_getDrawBehind_callback(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _DrawModifier_setDrawBehind_callback(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _DrawModifier_getDrawContent_callback(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _DrawModifier_setDrawContent_callback(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _EllipseShape_construct(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _EllipseShape_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _EllipseShape_offset(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _EllipseShape_fill(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _EllipseShape_position(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _EllipseShape_width(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _EllipseShape_height(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _EllipseShape_size(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _EventEmulator_emitClickEvent(node: KPointer, event: KPointer): void
    @ani.unsafe.Quick
    native static _EventEmulator_emitTextInputEvent(node: KPointer, text: KStringPtr): void
    @ani.unsafe.Direct
    native static _EventResult_construct(): KPointer
    @ani.unsafe.Direct
    native static _EventResult_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _EventResult_setGestureEventResult0(ptr: KPointer, result: KInt): void
    @ani.unsafe.Direct
    native static _EventResult_setGestureEventResult1(ptr: KPointer, result: KInt, stopPropagation: KInt): void
    @ani.unsafe.Direct
    native static _EventTargetInfo_construct(): KPointer
    @ani.unsafe.Direct
    native static _EventTargetInfo_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _EventTargetInfo_getId(ptr: KPointer): string
    @ani.unsafe.Direct
    native static _ExtendableComponent_construct(): KPointer
    @ani.unsafe.Direct
    native static _ExtendableComponent_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _ExtendableComponent_getUIContext(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _ExtendableComponent_getUniqueId(ptr: KPointer): int32
    @ani.unsafe.Direct
    native static _FileSelectorParam_construct(): KPointer
    @ani.unsafe.Direct
    native static _FileSelectorParam_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _FileSelectorParam_getTitle(ptr: KPointer): string
    @ani.unsafe.Direct
    native static _FileSelectorParam_getMode(ptr: KPointer): int32
    @ani.unsafe.Quick
    native static _FileSelectorParam_getAcceptType(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _FileSelectorParam_isCapture(ptr: KPointer): boolean
    @ani.unsafe.Quick
    native static _FileSelectorParam_getMimeTypes(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _FileSelectorResult_construct(): KPointer
    @ani.unsafe.Direct
    native static _FileSelectorResult_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _FileSelectorResult_handleFileList(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _FocusAxisEvent_construct(): KPointer
    @ani.unsafe.Direct
    native static _FocusAxisEvent_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _FocusAxisEvent_getAxisMap(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _FocusAxisEvent_setAxisMap(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _FocusAxisEvent_getStopPropagation(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _FocusAxisEvent_setStopPropagation(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _FocusController_requestFocus(key: KStringPtr): void
    @ani.unsafe.Direct
    native static _FrameNode_construct(uiContext: KPointer): KPointer
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
    native static _FrameNode_getChild(ptr: KPointer, index: number, expandMode: number): KPointer
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
    @ani.unsafe.Quick
    native static _FrameNode_getId(ptr: KPointer): string
    @ani.unsafe.Direct
    native static _FrameNode_getUniqueId(ptr: KPointer): number
    @ani.unsafe.Quick
    native static _FrameNode_getNodeType(ptr: KPointer): string
    @ani.unsafe.Direct
    native static _FrameNode_getOpacity(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _FrameNode_isVisible(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _FrameNode_isClipToFrame(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _FrameNode_isAttached(ptr: KPointer): boolean
    @ani.unsafe.Quick
    native static _FrameNode_getInspectorInfo(ptr: KPointer): Object
    @ani.unsafe.Direct
    native static _FrameNode_invalidate(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _FrameNode_disposeTree(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _FrameNode_setCrossLanguageOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _FrameNode_getCrossLanguageOptions(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _FrameNode_setMeasuredSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _FrameNode_setLayoutPosition(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _FrameNode_measure(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _FrameNode_layout(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _FrameNode_setNeedsLayout(ptr: KPointer): void
    @ani.unsafe.Quick
    native static _FrameNode_getPositionToWindowWithTransform(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _FrameNode_getFrameNodeByKey(name: KStringPtr): KPointer
    @ani.unsafe.Direct
    native static _FrameNode_getIdByFrameNode(ptr: KPointer, node: KPointer): number
    @ani.unsafe.Direct
    native static _FrameNode_moveTo(ptr: KPointer, targetParent: KPointer, index: number): void
    @ani.unsafe.Direct
    native static _FrameNode_getFirstChildIndexWithoutExpand(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _FrameNode_getLastChildIndexWithoutExpand(ptr: KPointer): number
    @ani.unsafe.Quick
    native static _FrameNode_getAttachedFrameNodeById(id: KStringPtr): KPointer
    @ani.unsafe.Direct
    native static _FrameNode_getFrameNodeById(id: number): KPointer
    @ani.unsafe.Direct
    native static _FrameNode_getFrameNodeByUniqueId(id: number): KPointer
    @ani.unsafe.Direct
    native static _FrameNode_reuse(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _FrameNode_recycle(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _FrameNode_getFrameNodePtr(node: KPointer): KPointer
    @ani.unsafe.Quick
    native static _FrameNode_createTypedFrameNode(type: KStringPtr): KPointer
    @ani.unsafe.Direct
    native static _FrictionMotion_construct(friction: number, position: number, velocity: number): KPointer
    @ani.unsafe.Direct
    native static _FrictionMotion_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _FullScreenExitHandler_construct(): KPointer
    @ani.unsafe.Direct
    native static _FullScreenExitHandler_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _FullScreenExitHandler_exitFullScreen(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _Gesture_construct(): KPointer
    @ani.unsafe.Direct
    native static _Gesture_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _Gesture_tag(ptr: KPointer, tag: KStringPtr): void
    @ani.unsafe.Direct
    native static _Gesture_allowedTypes(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GestureEvent_construct(): KPointer
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
    native static _GestureGroupInterface_construct(mode: KInt, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _GestureGroupInterface_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _GestureGroupInterface_onCancel(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _GestureModifier_construct(): KPointer
    @ani.unsafe.Direct
    native static _GestureModifier_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _GestureModifier_applyGesture(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GestureRecognizer_construct(): KPointer
    @ani.unsafe.Direct
    native static _GestureRecognizer_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _GestureRecognizer_getTag(ptr: KPointer): string
    @ani.unsafe.Direct
    native static _GestureRecognizer_getType(ptr: KPointer): int32
    @ani.unsafe.Direct
    native static _GestureRecognizer_isBuiltIn(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _GestureRecognizer_setEnabled(ptr: KPointer, isEnabled: KInt): void
    @ani.unsafe.Direct
    native static _GestureRecognizer_isEnabled(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _GestureRecognizer_getState(ptr: KPointer): int32
    @ani.unsafe.Direct
    native static _GestureRecognizer_getEventTargetInfo(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _GestureRecognizer_isValid(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _GestureRecognizer_getFingerCount(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _GestureRecognizer_isFingerCountLimit(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _GestureStyle_construct(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _GestureStyle_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _GlobalScope_ohos_arkui_componentSnapshot_get(id: KStringPtr, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _GlobalScope_ohos_arkui_performanceMonitor_begin(scene: KStringPtr, startInputType: KInt, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _GlobalScope_ohos_arkui_performanceMonitor_end(scene: KStringPtr): void
    @ani.unsafe.Direct
    native static _GlobalScope_ohos_arkui_performanceMonitor_recordInputEventTime(actionType: KInt, sourceType: KInt, time: KLong): void
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
    native static _HierarchicalSymbolEffect_construct(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _HierarchicalSymbolEffect_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _HierarchicalSymbolEffect_getFillStyle(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _HierarchicalSymbolEffect_setFillStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _HoverEvent_construct(): KPointer
    @ani.unsafe.Direct
    native static _HoverEvent_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _HoverEvent_getX(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _HoverEvent_setX(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _HoverEvent_getY(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _HoverEvent_setY(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _HoverEvent_getWindowX(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _HoverEvent_setWindowX(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _HoverEvent_getWindowY(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _HoverEvent_setWindowY(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _HoverEvent_getDisplayX(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _HoverEvent_setDisplayX(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _HoverEvent_getDisplayY(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _HoverEvent_setDisplayY(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _HoverEvent_getStopPropagation(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _HoverEvent_setStopPropagation(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _HttpAuthHandler_construct(): KPointer
    @ani.unsafe.Direct
    native static _HttpAuthHandler_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _HttpAuthHandler_confirm(ptr: KPointer, userName: KStringPtr, password: KStringPtr): boolean
    @ani.unsafe.Direct
    native static _HttpAuthHandler_cancel(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _HttpAuthHandler_isHttpAuthInfoSaved(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _image_PixelMap_construct(): KPointer
    @ani.unsafe.Direct
    native static _image_PixelMap_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _image_PixelMap_readPixelsToBufferSync(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _image_PixelMap_writeBufferToPixels(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _image_PixelMap_getIsEditable(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _image_PixelMap_getIsStrideAlignment(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _ImageAnalyzerController_construct(): KPointer
    @ani.unsafe.Direct
    native static _ImageAnalyzerController_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _ImageAnalyzerController_getImageAnalyzerSupportTypes(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _ImageAttachment_construct(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _ImageAttachment_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _ImageAttachment_getValue(ptr: KPointer): KPointer
    @ani.unsafe.Quick
    native static _ImageAttachment_getSize(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _ImageAttachment_getVerticalAlign(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _ImageAttachment_getObjectFit(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _ImageAttachment_getLayoutStyle(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _ImageAttachment_getColorFilter(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _ImageBitmap_construct(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _ImageBitmap_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _ImageBitmap_close(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _ImageBitmap_getHeight(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _ImageBitmap_setHeight(ptr: KPointer, height: number): void
    @ani.unsafe.Direct
    native static _ImageBitmap_getWidth(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _ImageBitmap_setWidth(ptr: KPointer, width: number): void
    @ani.unsafe.Direct
    native static _ImageData_construct(width: number, height: number, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _ImageData_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _ImageData_getData(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _ImageData_setData(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ImageData_getHeight(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _ImageData_setHeight(ptr: KPointer, height: number): void
    @ani.unsafe.Direct
    native static _ImageData_getWidth(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _ImageData_setWidth(ptr: KPointer, width: number): void
    @ani.unsafe.Direct
    native static _IndicatorComponentController_construct(): KPointer
    @ani.unsafe.Direct
    native static _IndicatorComponentController_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _IndicatorComponentController_showNext(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _IndicatorComponentController_showPrevious(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _IndicatorComponentController_changeIndex(ptr: KPointer, index: number, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _IUIContext_freezeUINode0(id: KStringPtr, isFrozen: KInt): void
    @ani.unsafe.Direct
    native static _IUIContext_freezeUINode1(id: number, isFrozen: KInt): void
    @ani.unsafe.Direct
    native static _JsGeolocation_construct(): KPointer
    @ani.unsafe.Direct
    native static _JsGeolocation_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _JsGeolocation_invoke(ptr: KPointer, origin: KStringPtr, allow: KInt, retain: KInt): void
    @ani.unsafe.Direct
    native static _JsResult_construct(): KPointer
    @ani.unsafe.Direct
    native static _JsResult_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _JsResult_handleCancel(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _JsResult_handleConfirm(ptr: KPointer): void
    @ani.unsafe.Quick
    native static _JsResult_handlePromptConfirm(ptr: KPointer, result: KStringPtr): void
    @ani.unsafe.Direct
    native static _KeyEvent_construct(): KPointer
    @ani.unsafe.Direct
    native static _KeyEvent_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _KeyEvent_getType(ptr: KPointer): int32
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
    native static _KeyEvent_getKeySource(ptr: KPointer): int32
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
    @ani.unsafe.Direct
    native static _KeyEvent_getIntentionCode(ptr: KPointer): int32
    @ani.unsafe.Direct
    native static _KeyEvent_setIntentionCode(ptr: KPointer, intentionCode: KInt): void
    @ani.unsafe.Quick
    native static _KeyEvent_getGetModifierKeyState(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _KeyEvent_setGetModifierKeyState(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _KeyEvent_getUnicode(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _KeyEvent_setUnicode(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Layoutable_construct(): KPointer
    @ani.unsafe.Direct
    native static _Layoutable_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _Layoutable_layout(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _Layoutable_getMargin(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _Layoutable_getPadding(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _Layoutable_getBorderWidth(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _Layoutable_getMeasureResult(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _Layoutable_setMeasureResult(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _Layoutable_getUniqueId(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _Layoutable_setUniqueId(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _LayoutCallback_construct(): KPointer
    @ani.unsafe.Direct
    native static _LayoutCallback_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _LayoutCallback_onPlaceChildren(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _LayoutCallback_onMeasureSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _LayoutChild_construct(): KPointer
    @ani.unsafe.Direct
    native static _LayoutChild_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _LayoutChild_measure(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _LayoutChild_getName(ptr: KPointer): string
    @ani.unsafe.Quick
    native static _LayoutChild_setName(ptr: KPointer, name: KStringPtr): void
    @ani.unsafe.Quick
    native static _LayoutChild_getId(ptr: KPointer): string
    @ani.unsafe.Quick
    native static _LayoutChild_setId(ptr: KPointer, id: KStringPtr): void
    @ani.unsafe.Quick
    native static _LayoutChild_getPosition(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _LayoutChild_setPosition(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _LayoutManager_construct(): KPointer
    @ani.unsafe.Direct
    native static _LayoutManager_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _LayoutManager_getLineCount(ptr: KPointer): number
    @ani.unsafe.Quick
    native static _LayoutManager_getGlyphPositionAtCoordinate(ptr: KPointer, x: number, y: number): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _LayoutPolicy_construct(): KPointer
    @ani.unsafe.Direct
    native static _LayoutPolicy_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _LayoutPolicy_getMatchParent(): KPointer
    @ani.unsafe.Direct
    native static _LazyForEachOps_Sync(node: KPointer, totalCount: KInt, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _LengthMetrics_construct(value: number, unit: KInt): KPointer
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
    native static _LengthMetrics_getUnit(ptr: KPointer): int32
    @ani.unsafe.Direct
    native static _LengthMetrics_setUnit(ptr: KPointer, unit: KInt): void
    @ani.unsafe.Direct
    native static _LengthMetrics_getValue(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _LengthMetrics_setValue(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _LetterSpacingStyle_construct(value: KPointer): KPointer
    @ani.unsafe.Direct
    native static _LetterSpacingStyle_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _LetterSpacingStyle_getLetterSpacing(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _LevelOrder_construct(): KPointer
    @ani.unsafe.Direct
    native static _LevelOrder_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _LevelOrder_clamp(order: number): KPointer
    @ani.unsafe.Direct
    native static _LevelOrder_getOrder(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _LifeCycle_construct(): KPointer
    @ani.unsafe.Direct
    native static _LifeCycle_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _LifeCycle_aboutToAppear(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _LifeCycle_aboutToDisappear(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _LifeCycle_onDidBuild(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _LifeCycle_build(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _LinearGradient_construct(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _LinearGradient_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _LinearIndicatorController_construct(): KPointer
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
    @ani.unsafe.Direct
    native static _LineHeightStyle_construct(lineHeight: KPointer): KPointer
    @ani.unsafe.Direct
    native static _LineHeightStyle_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _LineHeightStyle_getLineHeight(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _ListScroller_construct(): KPointer
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
    native static _LongPressGestureEvent_construct(): KPointer
    @ani.unsafe.Direct
    native static _LongPressGestureEvent_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _LongPressGestureEvent_getRepeat(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _LongPressGestureEvent_setRepeat(ptr: KPointer, repeat: KInt): void
    @ani.unsafe.Direct
    native static _LongPressGestureInterface_construct(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _LongPressGestureInterface_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _LongPressGestureInterface_onAction(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _LongPressGestureInterface_onActionEnd(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _LongPressGestureInterface_onActionCancel0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _LongPressGestureInterface_onActionCancel1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _LongPressRecognizer_construct(): KPointer
    @ani.unsafe.Direct
    native static _LongPressRecognizer_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _LongPressRecognizer_isRepeat(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _LongPressRecognizer_getDuration(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _Matrix2D_construct0(): KPointer
    @ani.unsafe.Direct
    native static _Matrix2D_construct1(unit: KInt): KPointer
    @ani.unsafe.Direct
    native static _Matrix2D_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _Matrix2D_identity(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _Matrix2D_invert(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _Matrix2D_rotate(ptr: KPointer, degree: number, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _Matrix2D_translate(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _Matrix2D_scale(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Quick
    native static _Matrix2D_getScaleX(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _Matrix2D_setScaleX(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _Matrix2D_getRotateY(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _Matrix2D_setRotateY(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _Matrix2D_getRotateX(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _Matrix2D_setRotateX(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _Matrix2D_getScaleY(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _Matrix2D_setScaleY(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _Matrix2D_getTranslateX(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _Matrix2D_setTranslateX(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _Matrix2D_getTranslateY(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _Matrix2D_setTranslateY(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _matrix4_Matrix4Transit_construct(): KPointer
    @ani.unsafe.Direct
    native static _matrix4_Matrix4Transit_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _matrix4_Matrix4Transit_copy(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _matrix4_Matrix4Transit_invert(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _matrix4_Matrix4Transit_combine(ptr: KPointer, options: KPointer): KPointer
    @ani.unsafe.Direct
    native static _matrix4_Matrix4Transit_translate(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _matrix4_Matrix4Transit_scale(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _matrix4_Matrix4Transit_skew(ptr: KPointer, x: number, y: number): KPointer
    @ani.unsafe.Direct
    native static _matrix4_Matrix4Transit_rotate(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Quick
    native static _matrix4_Matrix4Transit_transformPoint(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _matrix4_Matrix4Transit_setPolyToPoly(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _Measurable_construct(): KPointer
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
    @ani.unsafe.Quick
    native static _Measurable_getUniqueId(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _Measurable_setUniqueId(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MouseEvent_construct(): KPointer
    @ani.unsafe.Direct
    native static _MouseEvent_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _MouseEvent_getButton(ptr: KPointer): int32
    @ani.unsafe.Direct
    native static _MouseEvent_setButton(ptr: KPointer, button: KInt): void
    @ani.unsafe.Direct
    native static _MouseEvent_getAction(ptr: KPointer): int32
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
    @ani.unsafe.Quick
    native static _MouseEvent_getRawDeltaX(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _MouseEvent_setRawDeltaX(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _MouseEvent_getRawDeltaY(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _MouseEvent_setRawDeltaY(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _MouseEvent_getPressedButtons(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _MouseEvent_setPressedButtons(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _MutableStyledString_construct(thisArray: KSerializerBuffer, thisLength: int32): KPointer
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
    native static _NavDestinationContext_construct(): KPointer
    @ani.unsafe.Direct
    native static _NavDestinationContext_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _NavDestinationContext_getConfigInRouteMap(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _NavDestinationContext_getPathInfo(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _NavDestinationContext_setPathInfo(ptr: KPointer, pathInfo: KPointer): void
    @ani.unsafe.Direct
    native static _NavDestinationContext_getPathStack(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _NavDestinationContext_setPathStack(ptr: KPointer, pathStack: KPointer): void
    @ani.unsafe.Quick
    native static _NavDestinationContext_getNavDestinationId(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _NavDestinationContext_setNavDestinationId(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavExtender_setNavigationOptions(ptr: KPointer, pathStack: KPointer): void
    @ani.unsafe.Direct
    native static _NavExtender_setUpdateStackCallback(peer: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavExtender_syncStack(peer: KPointer): void
    @ani.unsafe.Direct
    native static _NavExtender_checkNeedCreate(navigation: KPointer, index: KInt): boolean
    @ani.unsafe.Direct
    native static _NavExtender_setNavDestinationNode(peer: KPointer, index: KInt, node: KPointer): void
    @ani.unsafe.Direct
    native static _NavExtender_pushPath(pathStack: KPointer, info: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavExtender_replacePath(pathStack: KPointer, info: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _NavExtender_pop(pathStack: KPointer, animated: KInt): string
    @ani.unsafe.Direct
    native static _NavExtender_setOnPopCallback(pathStack: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _NavExtender_getIdByIndex(pathStack: KPointer, index: KInt): string
    @ani.unsafe.Quick
    native static _NavExtender_getIdByName(pathStack: KPointer, name: KStringPtr): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _NavExtender_popToIndex(pathStack: KPointer, index: KInt, animated: KInt): void
    @ani.unsafe.Quick
    native static _NavExtender_popToName(pathStack: KPointer, name: KStringPtr, animated: KInt): number
    @ani.unsafe.Direct
    native static _NavigationTransitionProxy_construct(): KPointer
    @ani.unsafe.Direct
    native static _NavigationTransitionProxy_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _NavigationTransitionProxy_finishTransition(ptr: KPointer): void
    @ani.unsafe.Quick
    native static _NavigationTransitionProxy_getFrom(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _NavigationTransitionProxy_setFrom(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _NavigationTransitionProxy_getTo(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _NavigationTransitionProxy_setTo(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _NavigationTransitionProxy_getIsInteractive(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _NavigationTransitionProxy_setIsInteractive(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _NavigationTransitionProxy_getCancelTransition(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _NavigationTransitionProxy_setCancelTransition(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _NavigationTransitionProxy_getUpdateTransition(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _NavigationTransitionProxy_setUpdateTransition(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _NavPathInfo_construct(name: KStringPtr, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _NavPathInfo_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _NavPathInfo_getName(ptr: KPointer): string
    @ani.unsafe.Quick
    native static _NavPathInfo_setName(ptr: KPointer, name: KStringPtr): void
    @ani.unsafe.Quick
    native static _NavPathInfo_getParam(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _NavPathInfo_setParam(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _NavPathInfo_getOnPop(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _NavPathInfo_setOnPop(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _NavPathInfo_getIsEntry(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _NavPathInfo_setIsEntry(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _NavPathInfo_getNavDestinationId(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _NavPathInfo_setNavDestinationId(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavPathStack_construct(): KPointer
    @ani.unsafe.Direct
    native static _NavPathStack_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _NavPathStack_pushPath0(ptr: KPointer, info: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavPathStack_pushPath1(ptr: KPointer, info: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    native static _NavPathStack_pushDestination0(ptr: KPointer, info: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    native static _NavPathStack_pushDestination1(ptr: KPointer, info: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Quick
    native static _NavPathStack_pushPathByName0(ptr: KPointer, name: KStringPtr, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _NavPathStack_pushPathByName1(ptr: KPointer, name: KStringPtr, thisArray: KSerializerBuffer, thisLength: int32): void
    native static _NavPathStack_pushDestinationByName0(ptr: KPointer, name: KStringPtr, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    native static _NavPathStack_pushDestinationByName1(ptr: KPointer, name: KStringPtr, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _NavPathStack_replacePath0(ptr: KPointer, info: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavPathStack_replacePath1(ptr: KPointer, info: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    native static _NavPathStack_replaceDestination(ptr: KPointer, info: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Quick
    native static _NavPathStack_replacePathByName(ptr: KPointer, name: KStringPtr, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NavPathStack_removeByIndexes(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): number
    @ani.unsafe.Quick
    native static _NavPathStack_removeByName(ptr: KPointer, name: KStringPtr): number
    @ani.unsafe.Quick
    native static _NavPathStack_removeByNavDestinationId(ptr: KPointer, navDestinationId: KStringPtr): boolean
    @ani.unsafe.Quick
    native static _NavPathStack_pop0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _NavPathStack_pop1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KInteropReturnBuffer
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
    @ani.unsafe.Quick
    native static _NavPathStack_getParamByIndex(ptr: KPointer, index: number): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _NavPathStack_getParamByName(ptr: KPointer, name: KStringPtr): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _NavPathStack_getIndexByName(ptr: KPointer, name: KStringPtr): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _NavPathStack_getParent(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _NavPathStack_size(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _NavPathStack_disableAnimation(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _NavPathStack_setInterception(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _NavPathStack_getPathStack(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _NavPathStack_setPathStack(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _NodeContent_construct(): KPointer
    @ani.unsafe.Direct
    native static _NodeContent_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _NodeContent_addFrameNode(ptr: KPointer, node: KPointer): void
    @ani.unsafe.Direct
    native static _NodeContent_removeFrameNode(ptr: KPointer, node: KPointer): void
    @ani.unsafe.Direct
    native static _OffscreenCanvas_construct(width: number, height: number, thisArray: KSerializerBuffer, thisLength: int32): KPointer
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
    native static _OffscreenCanvasRenderingContext2D_construct(width: number, height: number, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _OffscreenCanvasRenderingContext2D_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _OffscreenCanvasRenderingContext2D_toDataURL(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): string
    @ani.unsafe.Direct
    native static _OffscreenCanvasRenderingContext2D_transferToImageBitmap(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _PageLifeCycle_construct(): KPointer
    @ani.unsafe.Direct
    native static _PageLifeCycle_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _PageLifeCycle_onPageShow(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _PageLifeCycle_onPageHide(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _PageLifeCycle_onBackPress(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _PageLifeCycle_pageTransition(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _PageLifeCycle_onNewParam(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _PanGestureEvent_construct(): KPointer
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
    native static _PanGestureInterface_construct(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _PanGestureInterface_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _PanGestureInterface_onActionStart(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _PanGestureInterface_onActionUpdate(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _PanGestureInterface_onActionEnd(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _PanGestureInterface_onActionCancel0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _PanGestureInterface_onActionCancel1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _PanGestureOptions_construct(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _PanGestureOptions_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _PanGestureOptions_setDirection(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _PanGestureOptions_setDistance(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _PanGestureOptions_setFingers(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _PanGestureOptions_getDirection(ptr: KPointer): int32
    @ani.unsafe.Direct
    native static _PanGestureOptions_getDistance(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _PanRecognizer_construct(): KPointer
    @ani.unsafe.Direct
    native static _PanRecognizer_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _PanRecognizer_getPanGestureOptions(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _ParagraphStyle_construct(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _ParagraphStyle_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _ParagraphStyle_getTextAlign(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _ParagraphStyle_getTextIndent(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _ParagraphStyle_getMaxLines(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _ParagraphStyle_getOverflow(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _ParagraphStyle_getWordBreak(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _ParagraphStyle_getLeadingMargin(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _ParagraphStyle_getParagraphSpacing(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _Path2D_construct0(): KPointer
    @ani.unsafe.Direct
    native static _Path2D_construct1(unit: KInt): KPointer
    @ani.unsafe.Direct
    native static _Path2D_construct2(path: KPointer): KPointer
    @ani.unsafe.Direct
    native static _Path2D_construct3(path: KPointer, unit: KInt): KPointer
    @ani.unsafe.Quick
    native static _Path2D_construct4(d: KStringPtr): KPointer
    @ani.unsafe.Quick
    native static _Path2D_construct5(description: KStringPtr, unit: KInt): KPointer
    @ani.unsafe.Direct
    native static _Path2D_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _Path2D_addPath(ptr: KPointer, path: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _PathShape_construct(thisArray: KSerializerBuffer, thisLength: int32): KPointer
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
    native static _PatternLockController_construct(): KPointer
    @ani.unsafe.Direct
    native static _PatternLockController_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _PatternLockController_reset(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _PatternLockController_setChallengeResult(ptr: KPointer, result: KInt): void
    @ani.unsafe.Direct
    native static _PermissionRequest_construct(): KPointer
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
    native static _PinchGestureEvent_construct(): KPointer
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
    native static _PinchGestureInterface_construct(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _PinchGestureInterface_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _PinchGestureInterface_onActionStart(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _PinchGestureInterface_onActionUpdate(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _PinchGestureInterface_onActionEnd(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _PinchGestureInterface_onActionCancel0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _PinchGestureInterface_onActionCancel1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _PinchRecognizer_construct(): KPointer
    @ani.unsafe.Direct
    native static _PinchRecognizer_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _PinchRecognizer_getDistance(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _PixelMapMock_construct(): KPointer
    @ani.unsafe.Direct
    native static _PixelMapMock_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _PixelMapMock_release(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _ProgressMask_construct(value: number, total: number, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _ProgressMask_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _ProgressMask_updateProgress(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _ProgressMask_updateColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ProgressMask_enableBreathingAnimation(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _PromptAction_construct(): KPointer
    @ani.unsafe.Direct
    native static _PromptAction_getFinalizer(): KPointer
    native static _PromptAction_openPopup(ptr: KPointer, content: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    native static _PromptAction_upatePopup(ptr: KPointer, content: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    native static _PromptAction_closePopup(ptr: KPointer, content: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    native static _PromptAction_openMenu(ptr: KPointer, content: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    native static _PromptAction_updateMenu(ptr: KPointer, content: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    native static _PromptAction_closeMenu(ptr: KPointer, content: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _RectShape_construct(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _RectShape_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _RectShape_offset(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _RectShape_fill(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _RectShape_position(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _RectShape_width(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _RectShape_height(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _RectShape_size(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _RectShape_radiusWidth(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _RectShape_radiusHeight(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _RectShape_radius(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _RenderingContextSettings_construct(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _RenderingContextSettings_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _RenderingContextSettings_getAntialias(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _RenderingContextSettings_setAntialias(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RenderNode_construct(): KPointer
    @ani.unsafe.Direct
    native static _RenderNode_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _RenderNode_appendChild(ptr: KPointer, node: KPointer): void
    @ani.unsafe.Direct
    native static _RenderNode_insertChildAfter(ptr: KPointer, child: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RenderNode_removeChild(ptr: KPointer, node: KPointer): void
    @ani.unsafe.Direct
    native static _RenderNode_clearChildren(ptr: KPointer): void
    @ani.unsafe.Quick
    native static _RenderNode_getChild(ptr: KPointer, index: number): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _RenderNode_getFirstChild(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _RenderNode_getNextSibling(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _RenderNode_getPreviousSibling(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _RenderNode_draw(ptr: KPointer, context: KPointer): void
    @ani.unsafe.Direct
    native static _RenderNode_invalidate(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _RenderNode_dispose(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _RenderNode_getBackgroundColor(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _RenderNode_setBackgroundColor(ptr: KPointer, backgroundColor: number): void
    @ani.unsafe.Direct
    native static _RenderNode_getClipToFrame(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _RenderNode_setClipToFrame(ptr: KPointer, clipToFrame: KInt): void
    @ani.unsafe.Direct
    native static _RenderNode_getOpacity(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _RenderNode_setOpacity(ptr: KPointer, opacity: number): void
    @ani.unsafe.Quick
    native static _RenderNode_getSize(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _RenderNode_setSize(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _RenderNode_getPosition(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _RenderNode_setPosition(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _RenderNode_getFrame(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _RenderNode_setFrame(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _RenderNode_getPivot(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _RenderNode_setPivot(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _RenderNode_getScale(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _RenderNode_setScale(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _RenderNode_getTranslation(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _RenderNode_setTranslation(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _RenderNode_getRotation(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _RenderNode_setRotation(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _RenderNode_getTransform(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _RenderNode_setTransform(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RenderNode_getShadowColor(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _RenderNode_setShadowColor(ptr: KPointer, shadowColor: number): void
    @ani.unsafe.Quick
    native static _RenderNode_getShadowOffset(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _RenderNode_setShadowOffset(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _RenderNode_getLabel(ptr: KPointer): string
    @ani.unsafe.Quick
    native static _RenderNode_setLabel(ptr: KPointer, label: KStringPtr): void
    @ani.unsafe.Direct
    native static _RenderNode_getShadowAlpha(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _RenderNode_setShadowAlpha(ptr: KPointer, shadowAlpha: number): void
    @ani.unsafe.Direct
    native static _RenderNode_getShadowElevation(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _RenderNode_setShadowElevation(ptr: KPointer, shadowElevation: number): void
    @ani.unsafe.Direct
    native static _RenderNode_getShadowRadius(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _RenderNode_setShadowRadius(ptr: KPointer, shadowRadius: number): void
    @ani.unsafe.Quick
    native static _RenderNode_getBorderStyle(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _RenderNode_setBorderStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _RenderNode_getBorderWidth(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _RenderNode_setBorderWidth(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _RenderNode_getBorderColor(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _RenderNode_setBorderColor(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _RenderNode_getBorderRadius(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _RenderNode_setBorderRadius(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RenderNode_getShapeMask(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _RenderNode_setShapeMask(ptr: KPointer, shapeMask: KPointer): void
    @ani.unsafe.Direct
    native static _RenderNode_getShapeClip(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _RenderNode_setShapeClip(ptr: KPointer, shapeClip: KPointer): void
    @ani.unsafe.Direct
    native static _RenderNode_getMarkNodeGroup(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _RenderNode_setMarkNodeGroup(ptr: KPointer, markNodeGroup: KInt): void
    @ani.unsafe.Direct
    native static _RenderNode_getLengthMetricsUnit(ptr: KPointer): int32
    @ani.unsafe.Direct
    native static _RenderNode_setLengthMetricsUnit(ptr: KPointer, lengthMetricsUnit: KInt): void
    @ani.unsafe.Quick
    native static _RenderServiceNode_getNodeId(nodeId: KStringPtr): int32
    @ani.unsafe.Direct
    native static _ReplaceSymbolEffect_construct(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _ReplaceSymbolEffect_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _ReplaceSymbolEffect_getScope(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _ReplaceSymbolEffect_setScope(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _RestrictedWorker_construct(scriptURL: KStringPtr, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _RestrictedWorker_getFinalizer(): KPointer
    native static _RestrictedWorker_postMessage0(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    native static _RestrictedWorker_postMessage1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    native static _RestrictedWorker_postMessageWithSharedSendable(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    native static _RestrictedWorker_on(ptr: KPointer, Type: KStringPtr, thisArray: KSerializerBuffer, thisLength: int32): void
    native static _RestrictedWorker_once(ptr: KPointer, Type: KStringPtr, thisArray: KSerializerBuffer, thisLength: int32): void
    native static _RestrictedWorker_off(ptr: KPointer, Type: KStringPtr, thisArray: KSerializerBuffer, thisLength: int32): void
    native static _RestrictedWorker_terminate(ptr: KPointer): void
    native static _RestrictedWorker_addEventListener(ptr: KPointer, Type: KStringPtr, thisArray: KSerializerBuffer, thisLength: int32): void
    native static _RestrictedWorker_dispatchEvent(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): boolean
    native static _RestrictedWorker_removeEventListener(ptr: KPointer, Type: KStringPtr, thisArray: KSerializerBuffer, thisLength: int32): void
    native static _RestrictedWorker_removeAllListener(ptr: KPointer): void
    native static _RestrictedWorker_registerGlobalCallObject(ptr: KPointer, instanceName: KStringPtr, thisArray: KSerializerBuffer, thisLength: int32): void
    native static _RestrictedWorker_unregisterGlobalCallObject(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _RestrictedWorker_getOnexit(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _RestrictedWorker_setOnexit(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _RestrictedWorker_getOnerror(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _RestrictedWorker_setOnerror(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _RestrictedWorker_getOnmessage(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _RestrictedWorker_setOnmessage(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _RestrictedWorker_getOnmessageerror(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _RestrictedWorker_setOnmessageerror(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RichEditorBaseController_construct(): KPointer
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
    @ani.unsafe.Quick
    native static _RichEditorBaseController_getCaretRect(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _RichEditorController_construct(): KPointer
    @ani.unsafe.Direct
    native static _RichEditorController_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _RichEditorController_addTextSpan(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): number
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
    native static _RichEditorStyledStringController_construct(): KPointer
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
    native static _RotationGesture_construct(): KPointer
    @ani.unsafe.Direct
    native static _RotationGesture_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _RotationGesture_$_instantiate(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _RotationGesture_onActionStart(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RotationGesture_onActionUpdate(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RotationGesture_onActionEnd(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RotationGesture_onActionCancel(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _RotationGestureEvent_construct(): KPointer
    @ani.unsafe.Direct
    native static _RotationGestureEvent_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _RotationGestureEvent_getAngle(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _RotationGestureEvent_setAngle(ptr: KPointer, angle: number): void
    @ani.unsafe.Direct
    native static _RotationRecognizer_construct(): KPointer
    @ani.unsafe.Direct
    native static _RotationRecognizer_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _RotationRecognizer_getAngle(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _ScaleSymbolEffect_construct(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _ScaleSymbolEffect_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _ScaleSymbolEffect_getScope(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _ScaleSymbolEffect_setScope(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _ScaleSymbolEffect_getDirection(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _ScaleSymbolEffect_setDirection(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Scene_construct(): KPointer
    @ani.unsafe.Direct
    native static _Scene_getFinalizer(): KPointer
    native static _Scene_load(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _Scene_destroy(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _ScreenCaptureHandler_construct(): KPointer
    @ani.unsafe.Direct
    native static _ScreenCaptureHandler_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _ScreenCaptureHandler_getOrigin(ptr: KPointer): string
    @ani.unsafe.Direct
    native static _ScreenCaptureHandler_grant(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ScreenCaptureHandler_deny(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _ScrollableTargetInfo_construct(): KPointer
    @ani.unsafe.Direct
    native static _ScrollableTargetInfo_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _ScrollableTargetInfo_isBegin(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _ScrollableTargetInfo_isEnd(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _Scroller_construct(): KPointer
    @ani.unsafe.Direct
    native static _Scroller_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _Scroller_scrollTo(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Scroller_scrollEdge(ptr: KPointer, value: KInt, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Scroller_fling(ptr: KPointer, velocity: number): void
    @ani.unsafe.Direct
    native static _Scroller_scrollPage(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _Scroller_currentOffset(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _Scroller_scrollToIndex(ptr: KPointer, value: number, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Scroller_scrollBy(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _Scroller_isAtEnd(ptr: KPointer): boolean
    @ani.unsafe.Quick
    native static _Scroller_getItemRect(ptr: KPointer, index: number): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _Scroller_getItemIndex(ptr: KPointer, x: number, y: number): number
    @ani.unsafe.Direct
    native static _ScrollMotion_construct(position: number, velocity: number, min: number, max: number, prop: KPointer): KPointer
    @ani.unsafe.Direct
    native static _ScrollMotion_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _ScrollResult_construct(): KPointer
    @ani.unsafe.Direct
    native static _ScrollResult_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _ScrollResult_getOffsetRemain(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _ScrollResult_setOffsetRemain(ptr: KPointer, offsetRemain: number): void
    @ani.unsafe.Direct
    native static _SearchController_construct(): KPointer
    @ani.unsafe.Direct
    native static _SearchController_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _SearchController_caretPosition(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _SearchController_stopEditing(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _SearchController_setTextSelection(ptr: KPointer, selectionStart: number, selectionEnd: number, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _SearchOps_registerSearchValueCallback(node: KPointer, value: KStringPtr, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _ShapeClip_construct(): KPointer
    @ani.unsafe.Direct
    native static _ShapeClip_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _ShapeClip_setRectShape(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ShapeClip_setRoundRectShape(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ShapeClip_setCircleShape(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ShapeClip_setOvalShape(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ShapeClip_setCommandPath(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ShapeMask_construct(): KPointer
    @ani.unsafe.Direct
    native static _ShapeMask_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _ShapeMask_setRectShape(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ShapeMask_setRoundRectShape(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ShapeMask_setCircleShape(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ShapeMask_setOvalShape(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ShapeMask_setCommandPath(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _ShapeMask_getFillColor(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _ShapeMask_setFillColor(ptr: KPointer, fillColor: number): void
    @ani.unsafe.Direct
    native static _ShapeMask_getStrokeColor(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _ShapeMask_setStrokeColor(ptr: KPointer, strokeColor: number): void
    @ani.unsafe.Direct
    native static _ShapeMask_getStrokeWidth(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _ShapeMask_setStrokeWidth(ptr: KPointer, strokeWidth: number): void
    @ani.unsafe.Direct
    native static _SpringMotion_construct(start: number, end: number, velocity: number, prop: KPointer): KPointer
    @ani.unsafe.Direct
    native static _SpringMotion_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _SpringProp_construct(mass: number, stiffness: number, damping: number): KPointer
    @ani.unsafe.Direct
    native static _SpringProp_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _SslErrorHandler_construct(): KPointer
    @ani.unsafe.Direct
    native static _SslErrorHandler_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _SslErrorHandler_handleConfirm(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _SslErrorHandler_handleCancel(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _StateStylesOps_onStateStyleChange(node: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _StyledString_construct(thisArray: KSerializerBuffer, thisLength: int32): KPointer
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
    native static _StyledString_fromHtml(html: KStringPtr, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Quick
    native static _StyledString_toHtml(styledString: KPointer): string
    @ani.unsafe.Quick
    native static _StyledString_marshalling0(styledString: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KInteropReturnBuffer
    native static _StyledString_unmarshalling0(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Quick
    native static _StyledString_marshalling1(styledString: KPointer): KInteropReturnBuffer
    native static _StyledString_unmarshalling1(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _StyledString_getLength(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _StyledStringController_construct(): KPointer
    @ani.unsafe.Direct
    native static _StyledStringController_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _StyledStringController_setStyledString(ptr: KPointer, styledString: KPointer): void
    @ani.unsafe.Direct
    native static _StyledStringController_getStyledString(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _SubmitEvent_construct(): KPointer
    @ani.unsafe.Direct
    native static _SubmitEvent_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _SubmitEvent_keepEditableState(ptr: KPointer): void
    @ani.unsafe.Quick
    native static _SubmitEvent_getText(ptr: KPointer): string
    @ani.unsafe.Quick
    native static _SubmitEvent_setText(ptr: KPointer, text: KStringPtr): void
    @ani.unsafe.Direct
    native static _SwipeGesture_construct(): KPointer
    @ani.unsafe.Direct
    native static _SwipeGesture_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _SwipeGesture_$_instantiate(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _SwipeGesture_onAction(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SwipeGestureEvent_construct(): KPointer
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
    native static _SwiperContentTransitionProxy_construct(): KPointer
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
    native static _SwiperController_construct(): KPointer
    @ani.unsafe.Direct
    native static _SwiperController_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _SwiperController_showNext(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _SwiperController_showPrevious(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _SwiperController_changeIndex(ptr: KPointer, index: number, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _SwiperController_finishAnimation(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    native static _SwiperController_preloadItems(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _SwipeRecognizer_construct(): KPointer
    @ani.unsafe.Direct
    native static _SwipeRecognizer_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _SwipeRecognizer_getVelocityThreshold(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _SwipeRecognizer_getDirection(ptr: KPointer): int32
    @ani.unsafe.Direct
    native static _SymbolEffect_construct(): KPointer
    @ani.unsafe.Direct
    native static _SymbolEffect_getFinalizer(): KPointer
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
    @ani.unsafe.Direct
    native static _SystemOps_resourceManagerReset(): void
    @ani.unsafe.Direct
    native static _SystemOps_setFrameCallback(thisArray: KSerializerBuffer, thisLength: int32, delayTime: number): void
    @ani.unsafe.Quick
    native static _SystemOps_colorMetricsResourceColor(thisArray: KSerializerBuffer, thisLength: int32): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _TabBarSymbol_construct(): KPointer
    @ani.unsafe.Direct
    native static _TabBarSymbol_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _TabBarSymbol_getNormal(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _TabBarSymbol_setNormal(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _TabBarSymbol_getSelected(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _TabBarSymbol_setSelected(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabContentTransitionProxy_construct(): KPointer
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
    native static _TabsController_construct(): KPointer
    @ani.unsafe.Direct
    native static _TabsController_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _TabsController_changeIndex(ptr: KPointer, value: number): void
    native static _TabsController_preloadItems(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _TabsController_setTabBarTranslate(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TabsController_setTabBarOpacity(ptr: KPointer, opacity: number): void
    @ani.unsafe.Direct
    native static _TapGestureEvent_construct(): KPointer
    @ani.unsafe.Direct
    native static _TapGestureEvent_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _TapGestureInterface_construct(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _TapGestureInterface_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _TapGestureInterface_onAction(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _TapRecognizer_construct(): KPointer
    @ani.unsafe.Direct
    native static _TapRecognizer_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _TapRecognizer_getTapCount(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _text_FontCollection_construct(): KPointer
    @ani.unsafe.Direct
    native static _text_FontCollection_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _text_FontCollection_getGlobalInstance(): KPointer
    @ani.unsafe.Quick
    native static _text_FontCollection_loadFontSync(ptr: KPointer, name: KStringPtr, thisArray: KSerializerBuffer, thisLength: int32): void
    native static _text_FontCollection_loadFont(ptr: KPointer, name: KStringPtr, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _text_FontCollection_clearCaches(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _text_LineTypeset_construct(): KPointer
    @ani.unsafe.Direct
    native static _text_LineTypeset_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _text_LineTypeset_getLineBreak(ptr: KPointer, startIndex: number, width: number): number
    @ani.unsafe.Direct
    native static _text_LineTypeset_createLine(ptr: KPointer, startIndex: number, count: number): KPointer
    @ani.unsafe.Direct
    native static _text_Paragraph_construct(): KPointer
    @ani.unsafe.Direct
    native static _text_Paragraph_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _text_Paragraph_layoutSync(ptr: KPointer, width: number): void
    native static _text_Paragraph_layout(ptr: KPointer, width: number, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _text_Paragraph_paint(ptr: KPointer, canvas: KPointer, x: number, y: number): void
    @ani.unsafe.Direct
    native static _text_Paragraph_paintOnPath(ptr: KPointer, canvas: KPointer, path: KPointer, hOffset: number, vOffset: number): void
    @ani.unsafe.Direct
    native static _text_Paragraph_getMaxWidth(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _text_Paragraph_getHeight(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _text_Paragraph_getLongestLine(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _text_Paragraph_getLongestLineWithIndent(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _text_Paragraph_getMinIntrinsicWidth(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _text_Paragraph_getMaxIntrinsicWidth(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _text_Paragraph_getAlphabeticBaseline(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _text_Paragraph_getIdeographicBaseline(ptr: KPointer): number
    @ani.unsafe.Quick
    native static _text_Paragraph_getRectsForRange(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32, widthStyle: KInt, heightStyle: KInt): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _text_Paragraph_getRectsForPlaceholders(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _text_Paragraph_getGlyphPositionAtCoordinate(ptr: KPointer, x: number, y: number): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _text_Paragraph_getWordBoundary(ptr: KPointer, offset: number): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _text_Paragraph_getLineCount(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _text_Paragraph_getLineHeight(ptr: KPointer, line: number): number
    @ani.unsafe.Direct
    native static _text_Paragraph_getLineWidth(ptr: KPointer, line: number): number
    @ani.unsafe.Direct
    native static _text_Paragraph_didExceedMaxLines(ptr: KPointer): boolean
    @ani.unsafe.Quick
    native static _text_Paragraph_getTextLines(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _text_Paragraph_getActualTextRange(ptr: KPointer, lineNumber: number, includeSpaces: KInt): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _text_Paragraph_getLineMetrics0(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _text_Paragraph_getLineMetrics1(ptr: KPointer, lineNumber: number): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _text_ParagraphBuilder_construct(thisArray: KSerializerBuffer, thisLength: int32, fontCollection: KPointer): KPointer
    @ani.unsafe.Direct
    native static _text_ParagraphBuilder_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _text_ParagraphBuilder_pushStyle(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _text_ParagraphBuilder_popStyle(ptr: KPointer): void
    @ani.unsafe.Quick
    native static _text_ParagraphBuilder_addText(ptr: KPointer, text: KStringPtr): void
    @ani.unsafe.Direct
    native static _text_ParagraphBuilder_addPlaceholder(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _text_ParagraphBuilder_build(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _text_ParagraphBuilder_buildLineTypeset(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _text_ParagraphBuilder_addSymbol(ptr: KPointer, symbolId: number): void
    @ani.unsafe.Direct
    native static _text_Run_construct(): KPointer
    @ani.unsafe.Direct
    native static _text_Run_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _text_Run_getGlyphCount(ptr: KPointer): number
    @ani.unsafe.Quick
    native static _text_Run_getGlyphs0(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _text_Run_getGlyphs1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _text_Run_getPositions0(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _text_Run_getPositions1(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _text_Run_getOffsets(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _text_Run_getFont(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _text_Run_paint(ptr: KPointer, canvas: KPointer, x: number, y: number): void
    @ani.unsafe.Quick
    native static _text_Run_getStringIndices(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _text_Run_getStringRange(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _text_Run_getTypographicBounds(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _text_Run_getImageBounds(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _text_TextLine_construct(): KPointer
    @ani.unsafe.Direct
    native static _text_TextLine_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _text_TextLine_getGlyphCount(ptr: KPointer): number
    @ani.unsafe.Quick
    native static _text_TextLine_getTextRange(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _text_TextLine_getGlyphRuns(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _text_TextLine_paint(ptr: KPointer, canvas: KPointer, x: number, y: number): void
    @ani.unsafe.Quick
    native static _text_TextLine_createTruncatedLine(ptr: KPointer, width: number, ellipsisMode: KInt, ellipsis: KStringPtr): KPointer
    @ani.unsafe.Quick
    native static _text_TextLine_getTypographicBounds(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _text_TextLine_getImageBounds(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _text_TextLine_getTrailingSpaceWidth(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _text_TextLine_getStringIndexForPosition(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): number
    @ani.unsafe.Direct
    native static _text_TextLine_getOffsetForStringIndex(ptr: KPointer, index: number): number
    @ani.unsafe.Direct
    native static _text_TextLine_enumerateCaretOffsets(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _text_TextLine_getAlignmentOffset(ptr: KPointer, alignmentFactor: number, alignmentWidth: number): number
    @ani.unsafe.Direct
    native static _TextAreaController_construct(): KPointer
    @ani.unsafe.Direct
    native static _TextAreaController_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _TextAreaController_caretPosition(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _TextAreaController_setTextSelection(ptr: KPointer, selectionStart: number, selectionEnd: number, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextAreaController_stopEditing(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _TextBaseController_construct(): KPointer
    @ani.unsafe.Direct
    native static _TextBaseController_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _TextBaseController_setSelection(ptr: KPointer, selectionStart: number, selectionEnd: number, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextBaseController_closeSelectionMenu(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _TextBaseController_getLayoutManager(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _TextClockController_construct(): KPointer
    @ani.unsafe.Direct
    native static _TextClockController_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _TextClockController_start(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _TextClockController_stop(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _TextContentControllerBase_construct(): KPointer
    @ani.unsafe.Direct
    native static _TextContentControllerBase_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _TextContentControllerBase_getCaretOffset(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _TextContentControllerBase_getTextContentRect(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _TextContentControllerBase_getTextContentLineCount(ptr: KPointer): number
    @ani.unsafe.Quick
    native static _TextContentControllerBase_addText(ptr: KPointer, text: KStringPtr, thisArray: KSerializerBuffer, thisLength: int32): number
    @ani.unsafe.Direct
    native static _TextContentControllerBase_deleteText(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _TextContentControllerBase_getSelection(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _TextContentControllerBase_clearPreviewText(ptr: KPointer): void
    @ani.unsafe.Quick
    native static _TextContentControllerBase_getText(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): string
    @ani.unsafe.Direct
    native static _TextController_construct(): KPointer
    @ani.unsafe.Direct
    native static _TextController_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _TextController_closeSelectionMenu(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _TextController_setStyledString(ptr: KPointer, value: KPointer): void
    @ani.unsafe.Direct
    native static _TextController_getLayoutManager(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _TextEditControllerEx_construct(): KPointer
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
    native static _TextFieldOps_registerTextFieldValueCallback(node: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _TextFieldOps_textFieldOpsSetWidth(node: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _TextFieldOps_textFieldOpsSetHeight(node: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _TextFieldOps_textFieldOpsSetPadding(node: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _TextFieldOps_textFieldOpsSetMargin(node: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _TextFieldOps_textFieldOpsSetBorder(node: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _TextFieldOps_textFieldOpsSetBorderWidth(node: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _TextFieldOps_textFieldOpsSetBorderColor(node: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _TextFieldOps_textFieldOpsSetBorderStyle(node: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _TextFieldOps_textFieldOpsSetBorderRadius(node: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _TextFieldOps_textFieldOpsSetBackgroundColor(node: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _TextInputController_construct(): KPointer
    @ani.unsafe.Direct
    native static _TextInputController_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _TextInputController_caretPosition(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _TextInputController_setTextSelection(ptr: KPointer, selectionStart: number, selectionEnd: number, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextInputController_stopEditing(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _TextMenuController_construct(): KPointer
    @ani.unsafe.Direct
    native static _TextMenuController_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _TextMenuController_setMenuOptions(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TextMenuItemId_construct(): KPointer
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
    native static _TextMenuItemId_getTRANSLATE(): KPointer
    @ani.unsafe.Direct
    native static _TextMenuItemId_getSEARCH(): KPointer
    @ani.unsafe.Direct
    native static _TextMenuItemId_getSHARE(): KPointer
    @ani.unsafe.Direct
    native static _TextPickerDialog_construct(): KPointer
    @ani.unsafe.Direct
    native static _TextPickerDialog_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _TextShadowStyle_construct(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _TextShadowStyle_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _TextShadowStyle_getTextShadow(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _TextStyle_construct(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _TextStyle_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _TextStyle_getFontColor(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _TextStyle_getFontFamily(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _TextStyle_getFontSize(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _TextStyle_getFontWeight(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _TextStyle_getFontStyle(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _TextTimerController_construct(): KPointer
    @ani.unsafe.Direct
    native static _TextTimerController_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _TextTimerController_start(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _TextTimerController_pause(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _TextTimerController_reset(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _ThemeControl_construct(): KPointer
    @ani.unsafe.Direct
    native static _ThemeControl_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _ThemeControl_setDefaultTheme(thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _TimePickerDialog_construct(): KPointer
    @ani.unsafe.Direct
    native static _TimePickerDialog_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _TouchEvent_construct(): KPointer
    @ani.unsafe.Direct
    native static _TouchEvent_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _TouchEvent_getHistoricalPoints(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _TouchEvent_getType(ptr: KPointer): int32
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
    @ani.unsafe.Quick
    native static _TransitionEffect_construct0(type: KStringPtr): KPointer
    @ani.unsafe.Direct
    native static _TransitionEffect_construct1(effect: number): KPointer
    @ani.unsafe.Direct
    native static _TransitionEffect_construct2(effect: KInt): KPointer
    @ani.unsafe.Direct
    native static _TransitionEffect_construct3(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _TransitionEffect_construct4(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _TransitionEffect_construct5(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _TransitionEffect_construct6(thisArray: KSerializerBuffer, thisLength: int32): KPointer
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
    native static _TransitionEffect_getIDENTITY(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _TransitionEffect_setIDENTITY(ptr: KPointer, IDENTITY: KPointer): void
    @ani.unsafe.Direct
    native static _TransitionEffect_getOPACITY(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _TransitionEffect_setOPACITY(ptr: KPointer, OPACITY: KPointer): void
    @ani.unsafe.Direct
    native static _TransitionEffect_getSLIDE(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _TransitionEffect_setSLIDE(ptr: KPointer, SLIDE: KPointer): void
    @ani.unsafe.Direct
    native static _TransitionEffect_getSLIDE_SWITCH(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _TransitionEffect_setSLIDE_SWITCH(ptr: KPointer, SLIDE_SWITCH: KPointer): void
    @ani.unsafe.Direct
    native static _UICommonEvent_construct(): KPointer
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
    native static _UIContext_construct(): KPointer
    @ani.unsafe.Direct
    native static _UIContext_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _UIContext_getFont(ptr: KPointer): KPointer
    native static _UIContext_getFilteredInspectorTree(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): string
    native static _UIContext_getFilteredInspectorTreeById(ptr: KPointer, id: KStringPtr, depth: number, thisArray: KSerializerBuffer, thisLength: int32): string
    @ani.unsafe.Direct
    native static _UIContext_animateTo(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _UIContext_showTextPickerDialog(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _UIContext_runScopedTask(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _UIContext_animateToImmediately(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _UIContext_getFrameNodeById(ptr: KPointer, id: KStringPtr): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _UIContext_getAttachedFrameNodeById(ptr: KPointer, id: KStringPtr): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _UIContext_getFrameNodeByUniqueId(ptr: KPointer, id: number): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _UIContext_vp2px(ptr: KPointer, value: number): number
    @ani.unsafe.Direct
    native static _UIContext_px2vp(ptr: KPointer, value: number): number
    @ani.unsafe.Direct
    native static _UIContext_fp2px(ptr: KPointer, value: number): number
    @ani.unsafe.Direct
    native static _UIContext_px2fp(ptr: KPointer, value: number): number
    @ani.unsafe.Direct
    native static _UIContext_lpx2px(ptr: KPointer, value: number): number
    @ani.unsafe.Direct
    native static _UIContext_px2lpx(ptr: KPointer, value: number): number
    @ani.unsafe.Quick
    native static _UIContext_getHostContext(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _UIContext_setDynamicDimming(ptr: KPointer, id: KStringPtr, value: number): void
    @ani.unsafe.Quick
    native static _UIContext_getWindowName(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _UIContext_getWindowWidthBreakpoint(ptr: KPointer): int32
    @ani.unsafe.Direct
    native static _UIContext_getWindowHeightBreakpoint(ptr: KPointer): int32
    native static _UIContext_openBindSheet(ptr: KPointer, bindSheetContent: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    native static _UIContext_updateBindSheet(ptr: KPointer, bindSheetContent: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    native static _UIContext_closeBindSheet(ptr: KPointer, bindSheetContent: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    native static _UIContext_clearResourceCache(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _UIContext_isFollowingSystemFontScale(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _UIContext_getMaxFontScale(ptr: KPointer): number
    @ani.unsafe.Quick
    native static _UIContextAtomicServiceBar_getBarRect(): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _uiEffect_VisualEffect_construct(): KPointer
    @ani.unsafe.Direct
    native static _uiEffect_VisualEffect_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _uiEffect_VisualEffect_backgroundColorBlender(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _UIExtensionProxy_construct(): KPointer
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
    native static _unifiedDataChannel_UnifiedData_construct(): KPointer
    @ani.unsafe.Direct
    native static _unifiedDataChannel_UnifiedData_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _unifiedDataChannel_UnifiedData_hasType(ptr: KPointer, UnifiedData_type: KStringPtr): boolean
    @ani.unsafe.Quick
    native static _unifiedDataChannel_UnifiedData_getTypes(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _UrlStyle_construct(url: KStringPtr): KPointer
    @ani.unsafe.Direct
    native static _UrlStyle_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _UrlStyle_getUrl(ptr: KPointer): string
    @ani.unsafe.Direct
    native static _UserDataSpan_construct(): KPointer
    @ani.unsafe.Direct
    native static _UserDataSpan_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _VideoController_construct(): KPointer
    @ani.unsafe.Direct
    native static _VideoController_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _VideoController_start(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _VideoController_pause(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _VideoController_stop(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _VideoController_setCurrentTime0(ptr: KPointer, value: number): void
    @ani.unsafe.Direct
    native static _VideoController_requestFullscreen(ptr: KPointer, value: KInt): void
    @ani.unsafe.Direct
    native static _VideoController_exitFullscreen(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _VideoController_setCurrentTime1(ptr: KPointer, value: number, seekMode: KInt): void
    @ani.unsafe.Direct
    native static _VideoController_reset(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _WaterFlowSections_construct(): KPointer
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
    native static _WebContextMenuParam_construct(): KPointer
    @ani.unsafe.Direct
    native static _WebContextMenuParam_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _WebContextMenuParam_x(ptr: KPointer): int32
    @ani.unsafe.Direct
    native static _WebContextMenuParam_y(ptr: KPointer): int32
    @ani.unsafe.Quick
    native static _WebContextMenuParam_getLinkUrl(ptr: KPointer): string
    @ani.unsafe.Quick
    native static _WebContextMenuParam_getUnfilteredLinkUrl(ptr: KPointer): string
    @ani.unsafe.Quick
    native static _WebContextMenuParam_getSourceUrl(ptr: KPointer): string
    @ani.unsafe.Direct
    native static _WebContextMenuParam_existsImageContents(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _WebContextMenuParam_getMediaType(ptr: KPointer): int32
    @ani.unsafe.Quick
    native static _WebContextMenuParam_getSelectionText(ptr: KPointer): string
    @ani.unsafe.Direct
    native static _WebContextMenuParam_getSourceType(ptr: KPointer): int32
    @ani.unsafe.Direct
    native static _WebContextMenuParam_getInputFieldType(ptr: KPointer): int32
    @ani.unsafe.Direct
    native static _WebContextMenuParam_isEditable(ptr: KPointer): boolean
    @ani.unsafe.Direct
    native static _WebContextMenuParam_getEditStateFlags(ptr: KPointer): int32
    @ani.unsafe.Direct
    native static _WebContextMenuParam_getPreviewWidth(ptr: KPointer): int32
    @ani.unsafe.Direct
    native static _WebContextMenuParam_getPreviewHeight(ptr: KPointer): int32
    @ani.unsafe.Direct
    native static _WebContextMenuResult_construct(): KPointer
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
    @ani.unsafe.Direct
    native static _WebCookie_construct(): KPointer
    @ani.unsafe.Direct
    native static _WebCookie_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _WebCookie_setCookie(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _WebCookie_saveCookie(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _WebKeyboardController_construct(): KPointer
    @ani.unsafe.Direct
    native static _WebKeyboardController_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _WebKeyboardController_insertText(ptr: KPointer, text: KStringPtr): void
    @ani.unsafe.Direct
    native static _WebKeyboardController_deleteForward(ptr: KPointer, length: KInt): void
    @ani.unsafe.Direct
    native static _WebKeyboardController_deleteBackward(ptr: KPointer, length: KInt): void
    @ani.unsafe.Direct
    native static _WebKeyboardController_sendFunctionKey(ptr: KPointer, key: KInt): void
    @ani.unsafe.Direct
    native static _WebKeyboardController_close(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _WebResourceError_construct(): KPointer
    @ani.unsafe.Direct
    native static _WebResourceError_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _WebResourceError_getErrorInfo(ptr: KPointer): string
    @ani.unsafe.Direct
    native static _WebResourceError_getErrorCode(ptr: KPointer): number
    @ani.unsafe.Direct
    native static _WebResourceRequest_construct(): KPointer
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
    native static _WebResourceResponse_construct(): KPointer
    @ani.unsafe.Direct
    native static _WebResourceResponse_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _WebResourceResponse_getResponseData(ptr: KPointer): string
    @ani.unsafe.Quick
    native static _WebResourceResponse_getResponseDataEx(ptr: KPointer): KInteropReturnBuffer
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
    native static _webview_WebviewController_construct(): KPointer
    @ani.unsafe.Direct
    native static _webview_WebviewController_getFinalizer(): KPointer
    @ani.unsafe.Direct
    native static _webview_WebviewController_initializeWebEngine(): void
    @ani.unsafe.Direct
    native static _webview_WebviewController_loadUrl(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _XComponentController_construct(): KPointer
    @ani.unsafe.Direct
    native static _XComponentController_getFinalizer(): KPointer
    @ani.unsafe.Quick
    native static _XComponentController_getXComponentSurfaceId(ptr: KPointer): string
    @ani.unsafe.Quick
    native static _XComponentController_getXComponentContext(ptr: KPointer): Object
    @ani.unsafe.Direct
    native static _XComponentController_setXComponentSurfaceRect(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _XComponentController_getXComponentSurfaceRect(ptr: KPointer): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _XComponentController_setXComponentSurfaceRotation(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _XComponentController_getXComponentSurfaceRotation(ptr: KPointer): KInteropReturnBuffer
    native static _XComponentController_startImageAnalyzer(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _XComponentController_stopImageAnalyzer(ptr: KPointer): void
    @ani.unsafe.Direct
    native static _XComponentController_getOnSurfaceCreated(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _XComponentController_setOnSurfaceCreated(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _XComponentController_getOnSurfaceChanged(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _XComponentController_setOnSurfaceChanged(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _XComponentController_getOnSurfaceDestroyed(ptr: KPointer): KPointer
    @ani.unsafe.Direct
    native static _XComponentController_setOnSurfaceDestroyed(ptr: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _GlobalScope_edgeColors(all: number): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _GlobalScope_edgeWidths(all: number): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _GlobalScope_borderStyles(all: KInt): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _GlobalScope_borderRadiuses(all: number): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _GlobalScope_postCardAction(thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _GlobalScope_$r(value: KStringPtr, thisArray: KSerializerBuffer, thisLength: int32): KInteropReturnBuffer
    @ani.unsafe.Quick
    native static _GlobalScope_$rawfile(value: KStringPtr): KInteropReturnBuffer
    @ani.unsafe.Direct
    native static _GlobalScope_animateTo(thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GlobalScope_animateToImmediately(thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GlobalScope_vp2px(value: number): number
    @ani.unsafe.Direct
    native static _GlobalScope_px2vp(value: number): number
    @ani.unsafe.Direct
    native static _GlobalScope_applyStyles(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Quick
    native static _GlobalScope_setAppBgColor(value: KStringPtr): void
    @ani.unsafe.Direct
    native static _GlobalScope_compatibleComponent(thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GlobalScope_bindCompatibleProvideCallback(component: KPointer, thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Direct
    native static _GlobalScope_getCompatibleState(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Direct
    native static _GlobalScope_compatibleWrappedBuilder(thisArray: KSerializerBuffer, thisLength: int32): void
    @ani.unsafe.Quick
    native static _GlobalScope_getRectangleById(id: KStringPtr): KInteropReturnBuffer
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
    @ani.unsafe.Direct
    native static _GlobalScope_uiEffect_createEffect(): KPointer
    @ani.unsafe.Quick
    native static _GlobalScope_uiEffect_createBrightnessBlender(thisArray: KSerializerBuffer, thisLength: int32): KInteropReturnBuffer
    native static _GlobalScope_text_getSystemFontFullNamesByType(fontType: KInt, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    native static _GlobalScope_text_getFontDescriptorByFullName(fullName: KStringPtr, fontType: KInt, thisArray: KSerializerBuffer, thisLength: int32): KPointer
    native static _GlobalScope_text_matchFontDescriptors(thisArray: KSerializerBuffer, thisLength: int32): KPointer
    @ani.unsafe.Quick
    native static _GlobalScope_font_getUIFontConfig(): KInteropReturnBuffer
}
