/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
declare interface DatePickerResult {
    year?: number;
    month?: number;
    day?: number;
}
declare enum DatePickerMode {
    DATE = 0,
    YEAR_AND_MONTH = 1,
    MONTH_AND_DAY = 2
}
declare interface DatePickerOptions {
    start?: Date;
    end?: Date;
    selected?: Date;
    mode?: DatePickerMode;
}
interface DatePickerInterface {
    (options?: DatePickerOptions): DatePickerAttribute;
}
declare class DatePickerAttribute extends CommonMethod<DatePickerAttribute> {
    disappearTextStyle(value: PickerTextStyle): DatePickerAttribute;
    disappearTextStyle(style: Optional<PickerTextStyle>): DatePickerAttribute;
    textStyle(value: PickerTextStyle): DatePickerAttribute;
    textStyle(style: Optional<PickerTextStyle>): DatePickerAttribute;
    selectedTextStyle(value: PickerTextStyle): DatePickerAttribute;
    selectedTextStyle(style: Optional<PickerTextStyle>): DatePickerAttribute;
    onChange(callback: (value: DatePickerResult) => void): DatePickerAttribute;
    onDateChange(callback: Callback<Date>): DatePickerAttribute;
    onDateChange(callback: Optional<Callback<Date>>): DatePickerAttribute;
    digitalCrownSensitivity(sensitivity: Optional<CrownSensitivity>): DatePickerAttribute;
    enableHapticFeedback(enable: Optional<boolean>): DatePickerAttribute;
}
declare interface LunarSwitchStyle {
    selectedColor?: ResourceColor;
    unselectedColor?: ResourceColor;
    strokeColor?: ResourceColor;
}
declare interface DatePickerDialogOptions extends DatePickerOptions {
    lunar?: boolean;
    lunarSwitch?: boolean;
    lunarSwitchStyle?: LunarSwitchStyle;
    showTime?: boolean;
    useMilitaryTime?: boolean;
    disappearTextStyle?: PickerTextStyle;
    textStyle?: PickerTextStyle;
    acceptButtonStyle?: PickerDialogButtonStyle;
    cancelButtonStyle?: PickerDialogButtonStyle;
    selectedTextStyle?: PickerTextStyle;
    maskRect?: Rectangle;
    alignment?: DialogAlignment;
    offset?: Offset;
    onAccept?: (value: DatePickerResult) => void;
    onCancel?: VoidCallback;
    onChange?: (value: DatePickerResult) => void;
    onDateAccept?: Callback<Date>;
    onDateChange?: Callback<Date>;
    backgroundColor?: ResourceColor;
    backgroundBlurStyle?: BlurStyle;
    backgroundBlurStyleOptions?: BackgroundBlurStyleOptions;
    backgroundEffect?: BackgroundEffectOptions;
    onDidAppear?: VoidCallback;
    onDidDisappear?: VoidCallback;
    onWillAppear?: VoidCallback;
    onWillDisappear?: VoidCallback;
    shadow?: ShadowOptions | ShadowStyle;
    dateTimeOptions?: DateTimeOptions;
    enableHoverMode?: boolean;
    hoverModeArea?: HoverModeAreaType;
    enableHapticFeedback?: boolean;
    canLoop?: boolean;
}
declare class DatePickerDialog {
    static show(options?: DatePickerDialogOptions);
}
declare const DatePicker: DatePickerInterface;
declare const DatePickerInstance: DatePickerAttribute;
