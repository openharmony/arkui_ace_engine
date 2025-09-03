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

import { SizeOptions } from "arkui/component/units"
import { GlobalScope_ohos_measure_utils } from "arkui/component/arkui-external"
import { Resource } from "global.resource"
import { FontStyle, FontWeight, TextAlign, TextOverflow, TextCase, WordBreak } from "arkui/component/enums"

export interface MeasureOptions {
    textContent: string | Resource;
    constraintWidth?: number | string | Resource;
    fontSize?: number | string | Resource;
    fontStyle?: number | FontStyle;
    fontWeight?: number | string | FontWeight;
    fontFamily?: string | Resource;
    letterSpacing?: number | string;
    textAlign?: number | TextAlign;
    overflow?: number | TextOverflow;
    maxLines?: number;
    lineHeight?: number | string | Resource;
    baselineOffset?: number | string;
    textCase?: number | TextCase;
    textIndent?: number | string;
    wordBreak?: WordBreak;
}

export class MeasureText {
    public static measureText(options: MeasureOptions) : number {
        return GlobalScope_ohos_measure_utils.measureText(options);
    }
    public static measureTextSize(options: MeasureOptions) : SizeOptions {
        return GlobalScope_ohos_measure_utils.measureTextSize(options);
    }
}