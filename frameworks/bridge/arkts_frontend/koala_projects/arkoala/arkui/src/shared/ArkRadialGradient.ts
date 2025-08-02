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

import { Equable, GeoLength, parseDimension, flattenFloatColors } from "./basic";

/** @memo:stable */
export class ArkRadialGradient implements Equable {
    x: GeoLength
    y: GeoLength
    radius: GeoLength
    repeat: boolean = false
    colors: Float32Array

    constructor(x: GeoLength,
                y: GeoLength,
                radius: GeoLength,
                repeat: boolean,
                colors: any[]) {
        this.x = x
        this.y = y
        this.radius = radius
        this.repeat = repeat
        this.colors = flattenFloatColors(colors)
    }

    isEqual(value: ArkRadialGradient): boolean {
        return this.x.isEqual(value.x) &&
               this.y.isEqual(value.y) &&
               this.radius.isEqual(value.radius) &&
               this.repeat == value.repeat &&
               this.colors == value.colors // <- This is strange. Using reference comparison in equals !
    }
}

export function translateRadialGradientToArkRadialGradient(value: {
    center: Array<any>
    radius: number | string
    colors: Array<any>
    repeating?: boolean
}): ArkRadialGradient {
    const x = parseDimension(value.center[0])
    const y = parseDimension(value.center[1])
    const radius = parseDimension(value.radius)

    return new ArkRadialGradient(x, y, radius, value.repeating ?? false, value.colors)
}
