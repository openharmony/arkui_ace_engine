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
package KoalaRuntime.animations

import std.collection.*
import std.math.*

public class EasingSupport {
    private let x: Array<Float64>
    private let y: Array<Float64>

    init(size: Int64, xSupplier: (value: Float64) -> Float64, ySupplier: (value: Float64) -> Float64) {
        if (size <= 1) {
            throw IllegalArgumentException("easing size must be integer value greater than 1, but is ${size}")
        }
        this.x = Array<Float64>(size) {
            index => xSupplier(Float64(index) / Float64(size - 1))
        }
        this.y = Array<Float64>(size) {
            index => ySupplier(Float64(index) / Float64(size - 1))
        }
    }

    func convert(value: Float64): Float64 {
        var last = this.x.size - 1
        var left = 0
        if (value < this.x[left]) {
            return this.y[left]
        }
        var right = last
        if (value > this.x[right]) {
            return this.y[right]
        }
        while (left <= right) {
            let center = (left + right) >> 1
            if (value < this.x[center]) {
                right = center - 1
            } else if (value > this.x[center]) {
                left = center + 1
            } else {
                return this.y[center]
            }
        }
        if (left > last) {
            return this.y[last]
        } else {
            return this.y[left]
        }
    }

    static func newCubicBezier(p1x: Float64, p1y: Float64, p2x: Float64, p2y: Float64, size!: Int64 = 1024): EasingSupport {
        if (p1x.isNaN() || p1x.isInf() || p1y.isNaN() || p1y.isInf() || p1x < 0.0 || 1.0 < p1x) {
            throw IllegalArgumentException("illegal point: (${p1x},${p1y}), where 0 <= x <= 1")
        }
        if (p2x.isNaN() || p2x.isInf() || p2y.isNaN() || p2y.isInf() || p2x < 0.0 || 1.0 < p2x) {
            throw IllegalArgumentException("illegal point: (${p2x},${p2y}), where 0 <= x <= 1")
        }
        return EasingSupport(size, {value => cubicBezierValue(value, p1x, p2x)},
            {value => cubicBezierValue(value, p1y, p2y)})
    }
}

func cubicBezierValue(left: Float64, p1: Float64, p2: Float64): Float64 {
    let right = 1.0 - left
    return left * (3.0 * right * (p1 * right + p2 * left) + left * left)
}
