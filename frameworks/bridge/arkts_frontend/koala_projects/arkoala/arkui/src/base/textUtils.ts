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

//* text_style.h
enum BackendFontWeight {
    W100 = 0,
    W200,
    W300,
    W400,
    W500,
    W600,
    W700,
    W800,
    W900,
    BOLD,
    NORMAL,
    BOLDER,
    LIGHTER,
    MEDIUM,
    REGULAR
};
let fontWeightValues = new Map([
    ["Bold", BackendFontWeight.BOLD],
    ["Normal", BackendFontWeight.NORMAL],
    ["Bolder", BackendFontWeight.BOLDER],
    ["Lighter", BackendFontWeight.LIGHTER],
    ["Medium", BackendFontWeight.MEDIUM],
    ["Regular", BackendFontWeight.REGULAR]
]);
enum FontWeight {
    Lighter,
    Normal,
    Regular,
    Medium,
    Bold,
    Bolder
}
let fontWeightEnumValues = new Map([
    [FontWeight.Bold, BackendFontWeight.BOLD],
    [FontWeight.Normal, BackendFontWeight.NORMAL],
    [FontWeight.Bolder, BackendFontWeight.BOLDER],
    [FontWeight.Lighter, BackendFontWeight.LIGHTER],
    [FontWeight.Medium, BackendFontWeight.MEDIUM],
    [FontWeight.Regular, BackendFontWeight.REGULAR],
])

export function parseFontWeight(fontWeight: number | FontWeight | string): number {
    if (typeof fontWeight === 'string') {
        let value = fontWeightValues.get(fontWeight);
        return (value != undefined) ? value : BackendFontWeight.NORMAL
    }
    else if (fontWeight >= FontWeight.Lighter && fontWeight <= FontWeight.Bolder) {
        let value = fontWeightEnumValues.get(fontWeight)
        return (value != undefined) ? value : BackendFontWeight.NORMAL
    }
    else if (fontWeight >= 100 && fontWeight <= 900) {
        return BackendFontWeight.W100 + (fontWeight / 100) - 1
    }
    // default value is 400 | FontWeight.Normal
    return BackendFontWeight.NORMAL
}

export function fontWeightString(fontWeight: number | FontWeight | string): string {
    if (typeof fontWeight === 'string') {
        return fontWeight
    }
    if (fontWeight >= FontWeight.Lighter && fontWeight <= FontWeight.Bolder) {
        return FontWeight[fontWeight]
    }
    return fontWeight.toString()
}

enum BackendTextAlign {
    START,
    CENTER,
    END,
    JUSTIFY,
};

export function parseTextAlign(textAlign: TextAlign): number {
    if (textAlign == TextAlign.CENTER) {
        return BackendTextAlign.CENTER;
    }
    else if (textAlign == TextAlign.START) {
        return BackendTextAlign.START;
    }
    else if (textAlign == TextAlign.END) {
        return BackendTextAlign.END;
    }
    else if (textAlign == TextAlign.JUSTIFY) {
        return BackendTextAlign.JUSTIFY;
    }
    return BackendTextAlign.START;
}

enum BackendTextOverflow {
    NONE,
    CLIP,
    ELLIPSIS,
    MARQUEE,
}
enum TextOverflow {
    Clip,
    Ellipsis,
    None,
    MARQUEE
}
let textOverflowValues = new Map([
    [TextOverflow.Clip, BackendTextOverflow.CLIP],
    [TextOverflow.Ellipsis, BackendTextOverflow.ELLIPSIS],
    [TextOverflow.None, BackendTextOverflow.NONE],
    [TextOverflow.MARQUEE, BackendTextOverflow.MARQUEE]
])
export function parseTextOverflow(value: TextOverflow): number {
    let overflow = textOverflowValues.get(value);
    return (overflow != undefined) ? overflow : BackendTextOverflow.CLIP;
}
