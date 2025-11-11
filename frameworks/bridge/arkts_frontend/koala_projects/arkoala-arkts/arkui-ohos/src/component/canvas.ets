/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { ArkUIAniModule } from "arkui.ani";
import { LengthMetricsUnit as arkui_component_units_LengthMetricsUnit } from '#generated'

const DIFF: number = 1e-10
const int_MAX: number = 2147483647
const PIXEL_SIZE: int = 4
export function getSystemDensity(): number {
    return ArkUIAniModule._GetSystemDensity()
}
export class ImageDataInternal {
}
export class ImageData {
    private data_val: Uint8ClampedArray = new Uint8ClampedArray()
    private finalWidth: int = 0
    private finalHeight: int = 0
    private unit_val: arkui_component_units_LengthMetricsUnit = arkui_component_units_LengthMetricsUnit.DEFAULT

    get data(): Uint8ClampedArray {
        return this.data_val
    }
    get height(): int {
        return this.finalHeight
    }
    get width(): int {
        return this.finalWidth
    }
    constructor(width: number, height: number, data?: Uint8ClampedArray, unit?: arkui_component_units_LengthMetricsUnit) {
        if (width == undefined || height == undefined) {
            return
        }
        if (width < 0.0 || height < 0.0) {
            return
        }
        if (unit != undefined) {
            this.unit_val = unit
        }
        const density = this.GetDensity()
        let width_value: number = width * density + DIFF
        let height_value: number = height * density + DIFF
        if ((width_value > int_MAX) || (height_value > int_MAX) ||
            ((width_value > 0) && (height_value > (int_MAX / width_value / PIXEL_SIZE)))) {
            return
        }
        this.finalWidth = width_value as int
        this.finalHeight = height_value as int
        const length: int = this.finalWidth * this.finalHeight * PIXEL_SIZE
        if (data == undefined) {
            this.data_val = new Uint8ClampedArray(length)
        } else {
            if (this.unit_val == arkui_component_units_LengthMetricsUnit.PX && data.length != length) {
                return
            }
            this.data_val = data
        }
    }
    private GetDensity(): number {
        const density = getSystemDensity()
        if ((this.unit_val == arkui_component_units_LengthMetricsUnit.DEFAULT) && density !== 0.0) {
            return density
        } else {
            return 1.0
        }
    }
}