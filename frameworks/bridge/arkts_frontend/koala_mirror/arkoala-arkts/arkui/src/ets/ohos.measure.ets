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

import { GlobalScope_ohos_measure_utils, MeasureOptions } from "./generated";
import { SizeOptions } from "./component/units";

export class MeasureText {
    public static measureText(options: MeasureOptions) : number {
        return GlobalScope_ohos_measure_utils.measureText(options);
    }
    public static measureTextSize(options: MeasureOptions) : SizeOptions {
        return GlobalScope_ohos_measure_utils.measureTextSize(options);
    }
}