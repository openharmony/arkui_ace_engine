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

import { float64, isFiniteNumber, uint32 } from "@koalaui/common"

export class EasingSupport {
    private x: Float64Array
    private y: Float64Array

    private constructor(size: uint32, xSupplier: (value: float64) => float64, ySupplier: (value: float64) => float64) {
        if (!Number.isInteger(size) || size <= 1) throw new Error("easing size must be integer value greater than 1, but is " + size)
        this.x = new Float64Array(size)
        this.y = new Float64Array(size)
        this.x[0] = xSupplier(0)
        this.y[0] = ySupplier(0)
        const last = size - 1
        this.x[last] = xSupplier(1)
        this.y[last] = ySupplier(1)
        for (let i = 1; i < last; i++) {
            const value = (i as float64) / last
            this.x[i] = xSupplier(value)
            this.y[i] = ySupplier(value)
        }
    }

    convert(value: float64): float64 {
        let last = (this.x.length - 1) as uint32
        let left = 0 as uint32
        if (value < this.x[left]) return this.y[left]
        let right = last
        if (value > this.x[right]) return this.y[right]
        while (left <= right) {
            const center = ((left + right) >>> 1) as uint32
            if (value < this.x[center]) right = center - 1
            else if (value > this.x[center]) left = center + 1
            else return this.y[center]
        }
        return this.y[left > last ? last : left]
    }

    static newCubicBezier(p1x: float64, p1y: float64, p2x: float64, p2y: float64, size: uint32 = 1024): EasingSupport {
        if (!isFiniteNumber(p1x) || !isFiniteNumber(p1y) || p1x < 0 || 1 < p1x) throw new Error(`illegal point: (${p1x},${p1y}), where 0 <= x <= 1`)
        if (!isFiniteNumber(p2x) || !isFiniteNumber(p2y) || p2x < 0 || 1 < p2x) throw new Error(`illegal point: (${p2x},${p2y}), where 0 <= x <= 1`)
        return new EasingSupport(size, (value: float64) => cubicBezierValue(value, p1x, p2x), (value: float64) => cubicBezierValue(value, p1y, p2y))
    }
}

function cubicBezierValue(left: float64, p1: float64, p2: float64): float64 {
    const right = 1 - left
    return left * (3 * right * (p1 * right + p2 * left) + left * left)
}
