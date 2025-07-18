/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

import { uint8, int32, CustomTextEncoder } from "@koalaui/common"
import { decodeToString } from "@koalaui/interop";

export function red(value: number): uint8 { return 0xFF & (value >> 16) }

export function green(value: number): uint8 { return 0xFF & (value >> 8) }

export function blue(value: number): uint8 { return 0xFF & (value) }

export function alpha(value: number): uint8 { return 0xFF & (value >> 24) }

export function toHexString(value: number): string {
    const hex = value.toString(16)
    return hex.length == 1 ? "0" + hex : hex
}

export function toColor(value: number): string {
    value = value <= 0xFFFFFF ? 0xFF000000 | value : value
    const s = toHexString(red(value)) + toHexString(green(value)) + toHexString(blue(value))
    const a = alpha(value)
    return "#" + (a < 255 ? s + toHexString(alpha(value)) : s)
}

export function toArrayStrings(array: Uint8Array): Array<string> {
    let strings: Array<string> = []
    let arraySize = CustomTextEncoder.getHeaderLength(array.slice(0, CustomTextEncoder.HeaderLen))
    let offset = CustomTextEncoder.HeaderLen
    for (let i = 0; i < arraySize; i++) {
        let len = CustomTextEncoder.getHeaderLength(array.slice(offset, offset + CustomTextEncoder.HeaderLen))
        offset += CustomTextEncoder.HeaderLen
        let decoded = decodeToString(array.slice(offset, offset + len))
        strings.push(decoded)
        offset += len
    }
    return strings
}

export function unitName(value: int32): string {
    switch (value) {
        case 0: return "px"
        case 1: return "vp"
        case 2: return "fp"
        case 3: return "%"
        case 4: return "lpx"
    }
    throw new Error(`Unsupported unit ${value}`)
}

export class TypeExpose {

    static selectMenuAlignTypeName(value: int32): string {
        switch (value) {
            case 0: return "START"
            case 1: return "CENTER"
            case 2: return "END"
        }
        throw new Error(`Unsupported MenuAlignType ${value}`)
    }
    
    static selectArrowPositionName(value: int32): string {
        switch (value) {
            case 0: return "START"
            case 1: return "END"
        }
        throw new Error(`Unsupported ArrowPosition ${value}`)
    }

    static textOverflow(value: int32): string {
        switch (value) {
            case 0: return "NONE"
            case 1: return "CLIP"
            case 2: return "ELLIPSIS"
            case 3: return "MARQUEE"
        }
        throw new Error(`Unsupported textOverflow ${value}`)
    }

    static textAlign(value: int32): string {
        switch (value) {
            case 0: return "Start"
            case 1: return "Center"
            case 2: return "End"
            case 3: return "JUSTIFY"
        }
        throw new Error(`Unsupported textAlign ${value}`)
    }
    
    static copyOption(value: int32): string {
        switch (value) {
            case 0: return "None"
            case 1: return "InApp"
            case 2: return "LocalDevice"
            case 3: return "CROSS_DEVICE"
        }
        throw new Error(`Unsupported copyOption ${value}`)
    }

    static heightAdaptivePolicy(value: int32): string {
        switch (value) {
            case 0: return "MAX_LINES_FIRST"
            case 1: return "MIN_FONT_SIZE_FIRST"
            case 2: return "LAYOUT_CONSTRAINT_FIRST"
        }
        throw new Error(`Unsupported heightAdaptivePolicy ${value}`)
    }

    static wordBreak(value: int32): string {
        switch (value) {
            case 0: return "NORMAL"
            case 1: return "BREAK_ALL"
            case 2: return "BREAK_WORD"
        }
        throw new Error(`Unsupported wordBreak ${value}`)
    }

    static shadowType(value: int32): string {
        switch (value) {
            case 0: return "COLOR"
            case 1: return "BLUR"
        }
        throw new Error(`Unsupported shadowType ${value}`)
    }

    static ellipsisMode(value: int32): string {
        switch (value) {
            case 0: return "START"
            case 1: return "CENTER"
            case 2: return "END"
        }
        throw new Error(`Unsupported ellipsisMode ${value}`)
    }

    static decorationType(value: int32): string {
        switch (value) {
            case 0: return "None"
            case 1: return "Underline"
            case 2: return "Overline"
            case 3: return "LineThrough"
        }
        throw new Error(`Unsupported fontStyle ${value}`)
    }

    static fontWeight(value: int32): string {
        switch (value) {
            case 0: return "W100"
            case 1: return "W200"
            case 2: return "W300"
            case 3: return "W400/Normal"
            case 4: return "W500"
            case 5: return "W600"
            case 6: return "W700"
            case 7: return "W800"
            case 8: return "W900"
            case 9: return "Bold"
            case 10: return "Normal"
            case 11: return "Bolder"
            case 12: return "Lighter"
            case 13: return "Medium"
            case 14: return "Regular"
        }
        throw new Error(`Unsupported fontWeight ${value}`)
    }

    static FillModeName(value: int32): string {
        switch (value) {
            case 0: return "None"
            case 1: return "Forwards"
            case 2: return "Backwards"
            case 3: return "Both"
        }
        throw new Error(`Unsupported FillMode ${value}`)
    }

    static AnimationStatusName(value: int32): string {
        switch (value) {
            case 0: return "Initial"
            case 1: return "Running"
            case 2: return "Paused"
            case 3: return "Stopped"
        }
        throw new Error(`Unsupported AnimationStatus ${value}`)
    }

    static barState(value: int32): string {
        switch (value) {
            case 0: return "Off"
            case 1: return "Auto"
            case 2: return "On"
        }
        throw new Error(`Unsupported BarState ${value}`)
    }

    static textContentStyle(value: int32): string {
        switch (value) {
            case 0: return "DEFAULT"
            case 1: return "INLINE"
        }
        throw new Error(`Unsupported TextContentStyle ${value}`)
    }

    static textInputStyle(value: int32): string {
        switch (value) {
            case 0: return "Default"
            case 1: return "Inline"
        }
        throw new Error(`Unsupported TextInputStyle ${value}`)
    }

    static textAreaType(value: int32): string {
        switch (value) {
            case 0: return "NORMAL"
            case 2: return "NUMBER"
            case 3: return "PHONE_NUMBER"
            case 5: return "EMAIL"
        }
        throw new Error(`Unsupported TextAreaType ${value}`)
    }

    static textInputType(value: int32): string {
        switch (value) {
            case 0: return "Normal"
            case 1: return "Number"
            case 2: return "PhoneNumber"
            case 3: return "Email"
            case 4: return "Password"
            case 8: return "NUMBER_PASSWORD"
            case 9: return "SCREEN_LOCK_PASSWORD"
            case 10: return "USER_NAME"
            case 11: return "NEW_PASSWORD"
            case 12: return "NUMBER_DECIMAL"
        }
        throw new Error(`Unsupported TextInputType ${value}`)
    }

    static textInputCancelButtonStyle(value: int32): string {
        switch (value) {
            case 0: return "CONSTANT"
            case 1: return "INVISIBLE"
            case 2: return "INPUT"
        }
        throw new Error(`Unsupported CancelButtonStyle ${value}`)
    }

    static enterKeyType(value: int32): string {
        switch (value) {
            case 0: return "Go"
            case 1: return "Search"
            case 2: return "Send"
            case 3: return "Next"
            case 4: return "Done"
            case 7: return "PREVIOUS"
            case 8: return "NEW_LINE"
        }
        throw new Error(`Unsupported EnterKeyType ${value}`)
    }

    static displayMode(value: int32): string {
        switch (value) {
            case 0: return "Stretch"
            case 1: return "AutoLinear"
            case 2: return "STRETCH"
            case 3: "AUTO_LINEAR"
        }
        throw new Error(`Unsupported DisplayMode ${value}`)
    }

    static edgeEffect(value: int32): string {
        switch (value) {
            case 0: return "Spring"
            case 1: return "Fade"
            case 2: return "None"
        }
        throw new Error(`Unsupported EdgeEffect ${value}`)
    }

    static swiperNestedScrollMode(value: int32) {
        switch (value) {
            case 0: return "SELF_ONLY"
            case 1: return "SELF_FIRST"
        }
        throw new Error(`Unsupported SwiperNestedScrollMode ${value}`)
    }

    static hoverEffect(value: int32): string {
        switch (value) {
            case 0: return "Auto"
            case 1: return "Scale"
            case 2: return "Highlight"
            case 3: return "None"
        }
        throw new Error(`Unsupported HoverEffect ${value}`)
    }

    static flexDirection(value: int32) {
        switch (value) {
            case 0: return "Row"
            case 1: return "Column"
            case 2: return "RowReverse"
            case 3: return "ColumnReverse"
        }
        throw new Error(`Unsupported FlexDirection ${value}`)
    }

    static flexWrap(value: int32) {
        switch (value) {
            case 0: return "NoWrap"
            case 1: return "Wrap"
            case 2: return "WrapReverse"
        }
        throw new Error(`Unsupported FlexWrap ${value}`)
    }

    static flexAlign(value: int32) {
        switch (value) {
            case 1: return "Start"
            case 2: return "Center"
            case 3: return "End"
            case 6: return "SpaceBetween"
            case 7: return "SpaceAround"
            case 8: return "SpaceEvenly"
        }
        throw new Error(`Unsupported FlexAlign ${value}`)
    }

    static itemAlign(value: int32) {
        switch (value) {
            case 0: return "Auto"
            case 1: return "Start"
            case 2: return "Center"
            case 3: return "End"
            case 4: return "Baseline"
            case 5: return "Stretch"
        }
        throw new Error(`Unsupported ItemAlign ${value}`)
    }

    static buttonType(value: int32) {
        switch (value) {
            case 0: return "Capsule"
            case 1: return "Circle"
            case 2: return "Normal"
        }
        throw new Error(`Unsupported ButtonType ${value}`)
    }

    static buttonStyle(value: int32) {
        switch (value) {
            case 0: return "NORMAL"
            case 1: return "EMPHASIZED"
            case 2: return "TEXTUAL"
        }
        throw new Error(`Unsupported ButtonStyleMode ${value}`)
    }

    static controlSize(value: int32) {
        switch (value) {
            case 0: return "SMALL"
            case 1: return "NORMAL"
        }
        throw new Error(`Unsupported ControlSize ${value}`)
    }

    static textDataDetectorType(value: int32) {
        switch (value) {
            case 0: return "PHONE_NUMBER"
            case 1: return "URL"
            case 2: return "EMAIL"
            case 3: return "ADDRESS"
        }
        throw new Error(`Unsupported TextDataDetectorType ${value}`)
    }

    static timePickerFormat(value: int32) {
        switch (value) {
            case 0: return "HOUR_MINUTE"
            case 1: return "HOUR_MINUTE_SECOND"
        }
        throw new Error(`Unsupported TimePickerFormat ${value}`)
    }

}
