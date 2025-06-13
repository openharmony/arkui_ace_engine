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

import { Array_from_number, float32, float64 } from "@koalaui/compat"

export function mat33(array?: Float32Array): Matrix33 {
    return (array == undefined) ? new Matrix33 () : new Matrix33(array)
}

const tolerance: float32 = (1.0 / (1 << 12))

export class Matrix33 {
    public readonly array: Float32Array
    constructor (array: Float32Array = new Float32Array(Array_from_number([
        1.0, 0.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 0.0, 1.0
    ]))) {
        this.array = array.slice()
    }

    static zero(): Matrix33 {
        return new Matrix33(new Float32Array(Array_from_number([0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0])))
    }

    static makeTranslate(dx: float32, dy: float32): Matrix33 {
        return new Matrix33(new Float32Array(Array_from_number([1.0, 0.0, dx as float64, 0.0, 1.0, dy as float64, 0.0, 0.0, 1.0])))
    }

    static makeScale(dx: float32, dy: float32 = dx): Matrix33 {
        return new Matrix33(new Float32Array(Array_from_number([dx as float64, 0.0, 0.0, 0.0, dy as float64, 0.0, 0.0, 0.0, 1.0])))
    }

    static makeRotate(degrees: float32, pivotX?: float32, pivotY?: float32): Matrix33 {
        let rads = degrees * Math.PI / 180
        let cos = Math.cos(rads)
        let sin = Math.sin(rads)
        if (Math.abs(sin) <= tolerance) sin = 0.0
        if (Math.abs(cos) <= tolerance) cos = 0.0
        if (pivotX !== undefined && pivotY != undefined) {
            let dx = pivotX - pivotX * cos + pivotY * sin
            let dy = pivotY - pivotY * cos - pivotX * sin
            return new Matrix33(new Float32Array(Array_from_number([cos, -sin, dx, sin, cos, dy, 0.0, 0.0, 1.0])))
        } else {
            return new Matrix33(new Float32Array(Array_from_number([cos, -sin, 0.0, sin, cos, 0.0, 0.0, 0.0, 1.0])))
        }
    }

    static makeSkew(sx: float32, sy: float32): Matrix33 {
        return new Matrix33(new Float32Array(Array_from_number([1.0, sx, 0.0, sy, 1.0, 0.0, 0.0, 0.0, 1.0])))
    }

    makeConcat(rhs: Matrix33): Matrix33 {
        return new Matrix33(new Float32Array(Array_from_number([
            this.array[0] * rhs.array[0] + this.array[1] * rhs.array[3] + this.array[2] * rhs.array[6],
            this.array[0] * rhs.array[1] + this.array[1] * rhs.array[4] + this.array[2] * rhs.array[7],
            this.array[0] * rhs.array[2] + this.array[1] * rhs.array[5] + this.array[2] * rhs.array[8],
            this.array[3] * rhs.array[0] + this.array[4] * rhs.array[3] + this.array[5] * rhs.array[6],
            this.array[3] * rhs.array[1] + this.array[4] * rhs.array[4] + this.array[5] * rhs.array[7],
            this.array[3] * rhs.array[2] + this.array[4] * rhs.array[5] + this.array[5] * rhs.array[8],
            this.array[6] * rhs.array[0] + this.array[7] * rhs.array[3] + this.array[8] * rhs.array[6],
            this.array[6] * rhs.array[1] + this.array[7] * rhs.array[4] + this.array[8] * rhs.array[7],
            this.array[6] * rhs.array[2] + this.array[7] * rhs.array[5] + this.array[8] * rhs.array[8],
        ])))
    }

    makeTranspose(): Matrix33{
        return new Matrix33(new Float32Array(Array_from_number([
            this.array[0], this.array[3], this.array[6],
            this.array[1], this.array[4], this.array[7],
            this.array[2], this.array[5], this.array[8]
        ])))
    }
}