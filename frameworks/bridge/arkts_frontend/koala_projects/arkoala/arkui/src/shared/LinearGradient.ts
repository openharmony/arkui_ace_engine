/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

import { parseDimension } from "./basic"
import { translateColorToArkoalaColor } from "./ArkoalaColor"
import { float32, int32 } from "@koalaui/common"


export class LinearGradient {
    gradientColors: Int32Array
    offsets: Float32Array
    colors: Array<int32>
    constructor(colorStops: ColorStop[]) {
        let _colors = new Array<int32>()
        let _offsets = new Array<float32>()
        if (Array.isArray(colorStops)) {
            (colorStops || []).forEach((colorStop: ColorStop) => {
                _colors.push(translateColorToArkoalaColor(colorStop.color).value)
                _offsets.push(parseDimension(colorStop.offset).value)
            })
        }
        this.colors = _colors
        this.gradientColors = new Int32Array(_colors)
        this.offsets = new Float32Array(_offsets)
    }
}
