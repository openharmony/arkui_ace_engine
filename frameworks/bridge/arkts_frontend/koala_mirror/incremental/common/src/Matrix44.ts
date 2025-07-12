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

import { Array_from_number, float32 } from "@koalaui/compat"
import { Matrix33 } from "./Matrix33"
import { Point3 } from "./Point3"


export interface RotateOptions {
    angle?: float32
    x?: float32
    y?: float32
    z?: float32
    pivotX?: float32
    pivotY?: float32
    pivotZ?: float32
}

export interface ScaleOptions {
    x?: float32
    y?: float32
    z?: float32
    pivotX?: float32
    pivotY?: float32
    pivotZ?: float32
}

export interface TranslateOptions {
    x?: float32
    y?: float32
    z?: float32
}

// TODO: this is because ArkTS doesn allow interface literal instances.
class TranslateOptionsImpl implements TranslateOptions {
    _x: float32 | undefined
    _y: float32 | undefined
    _z: float32 | undefined

    get x(): float32 | undefined { return this._x }
    get y(): float32 | undefined { return this._y }
    get z(): float32 | undefined { return this._z }

    set x(x: float32 | undefined) { this._x = x }
    set y(y: float32 | undefined) { this._y = y }
    set z(z: float32 | undefined) { this._z = z }

    constructor(
        x: float32 | undefined,
        y: float32 | undefined,
        z: float32 | undefined
    ) {
        this._x = x
        this._y = y
        this._z = z
    }
}

export function mat44(array?: Float32Array): Matrix44 {
    return (array == undefined)? new Matrix44() : new Matrix44(array)
}
/**
 * 4x4 matrix with right-handed coordinate system:
 * +x goes to the right
 * +y goes down
 * +z goes into the screen (away from the viewer)
 */
export class Matrix44 {
    public readonly array: Float32Array
    constructor (array: Float32Array = new Float32Array(Array_from_number([
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    ]))) {
        this.array = array.slice()
    }

    public static identity(): Matrix44 {
        return mat44()
    }

    static zero(): Matrix44 {
        return mat44(new Float32Array(Array_from_number([
            0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0,
        ])))
    }

    public static lookAt(eye: Point3, center: Point3, up: Point3): Matrix44 {
        const f = center.subtract(eye).normalize()
        const u = up.normalize()
        const s = f.cross(u).normalize()
        const sf = s.cross(f)
        return new Matrix44(new Float32Array(Array_from_number([
            s.x, sf.x, -f.x, eye.x,
            s.y, sf.y, -f.y, eye.y,
            s.z, sf.z, -f.z, eye.z,
            0,   0,     0,   1,
        ]))).invert()
    }

    public static perspective(depth: float32): Matrix44 {
        return new Matrix44(new Float32Array(Array_from_number([
            1.0, 0.0, 0.0, 0.0,
            0.0, 1.0, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, -1.0 / depth, 1.0,
        ])))
    }

    public static perspectiveFov(fov: float32, near: float32, far: float32): Matrix44 {
        const denomInv = (far - near)
        const halfAngle = fov * 0.5;
        const cot = Math.cos(halfAngle) / Math.sin(halfAngle)
        return new Matrix44(new Float32Array(Array_from_number([
            cot, 0.0, 0.0, 0.0,
            0.0, cot, 0.0, 0.0,
            0.0, 0.0, (far + near) * denomInv, 2 * far * near * denomInv,
            0.0, 0.0, -1.0, 0.0,
        ])))
    }

    /**
     * Returns new matrix, made from Matrix33.
     *
     * @param matrix - 3x3 matrix
     * @returns the new instance of Matrix44
     *
     */
    public static makeFromMatrix33(matrix: Matrix33): Matrix44{
        return new Matrix44(new Float32Array(Array_from_number([
            matrix.array[0], matrix.array[1], 0.0, matrix.array[2],
            matrix.array[3], matrix.array[4], 0.0, matrix.array[5],
            0.0,             0.0,             1.0,           0.0,
            matrix.array[6], matrix.array[7], 0.0, matrix.array[8]
        ])))
    }

    /**
     * Returns new 3x3 matrix, made from this matrix by dropping the third row and the third column.
     *
     * @returns the new instance of Matrix33
     *
     */
    public asMatrix33(): Matrix33{
        return new Matrix33(new Float32Array(Array_from_number([
            this.array[0],  this.array[1],  this.array[3],
            this.array[4],  this.array[5],  this.array[7],
            this.array[12], this.array[13], this.array[15]
        ])))
    }

    public copy(): Matrix44 {
        return new Matrix44(new Float32Array(Array_from_number([
            this.array[0],  this.array[1],  this.array[2],  this.array[3],
            this.array[4],  this.array[5],  this.array[6],  this.array[7],
            this.array[8],  this.array[9],  this.array[10], this.array[11],
            this.array[12], this.array[13], this.array[14], this.array[15]
        ])))
    }

    concat(matrix: Matrix44): Matrix44 {
        const result: Float32Array = new Float32Array(Array_from_number([
            1.0, 0.0, 0.0, 0.0,
            0.0, 1.0, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0,
        ]))
        for (let row = 0; row < 4; row++) {
            for (let col = 0; col < 4; col++) {
                let num: float32 = 0
                for (let k = 0; k < 4; k++) {
                    num += this.array[row * 4 + k] * matrix.array[col + 4 * k]
                }
                result[row * 4 + col] = num
            }
        }
        for (let i = 0; i < this.array.length; i++) {
            this.array[i] = result[i]
        }
        return this
    }

    public scale(options: ScaleOptions): Matrix44 {
        const scaled = new Matrix44()
        scaled.array[0] = options.x ?? 1.0 as float32
        scaled.array[5] = options.y ?? 1.0 as float32
        scaled.array[10] = options.z ?? 1.0 as float32

        this.translate(new TranslateOptionsImpl(
            -(options.pivotX ?? 0.0 as float32) * (options.x ?? 1.0 as float32) + (options.pivotX ?? 0.0 as float32),
            -(options.pivotY ?? 0.0 as float32) * (options.y ?? 1.0 as float32) + (options.pivotY ?? 0.0 as float32),
            undefined
        )).concat(scaled)

        return this
    }

    public rotate(options: RotateOptions): Matrix44 {
        const translationToPivot = mat44().translate(new TranslateOptionsImpl(
             (options.pivotX ?? 0.0 as float32),
             (options.pivotY ?? 0.0 as float32),
             (options.pivotZ ?? 0.0 as float32),
        ))
        const translationToBack = mat44().translate(new TranslateOptionsImpl(
            -(options.pivotX ?? 0.0 as float32),
            -(options.pivotY ?? 0.0 as float32),
            -(options.pivotZ ?? 0.0 as float32),
        ))

        const vec = new Point3(options.x ?? 0.0 as float32, options.y ?? 0.0 as float32, options.z ?? 0.0 as float32).normalize()
        const rads = (options.angle ?? 0.0 as float32) * Math.PI / 180
        let c = Math.cos(rads)
        let s = Math.sin(rads)
        const tolerance = (1.0 / (1 << 12))
        if (Math.abs(s) <= tolerance) s = 0.0
        if (Math.abs(c) <= tolerance) c = 0.0
        let t = 1 - c
        const x = vec.x
        const y = vec.y
        const z = vec.z

        const rotation = mat44()
        rotation.array[0] = t * x * x + c
        rotation.array[1] = t * x * y - s * z
        rotation.array[2] = t * x * z + s * y
        rotation.array[3] = 0
        rotation.array[4] = t * x * y + s * z
        rotation.array[5] = t * y * y + c
        rotation.array[6] = t * y * z - s * x
        rotation.array[7] = 0
        rotation.array[8] = t * x * z - s * y
        rotation.array[9] = t * y * z + s * x
        rotation.array[10] = t * z * z + c
        rotation.array[11] = 0
        rotation.array[12] = 0
        rotation.array[13] = 0
        rotation.array[14] = 0
        rotation.array[15] = 1

        this.concat(translationToPivot).concat(rotation).concat(translationToBack)

        return this
    }

    public translate(options: TranslateOptions): Matrix44 {
        this.array[3] = options.x ?? 0.0 as float32
        this.array[7] = options.y ?? 0.0 as float32
        this.array[11] = options.z ?? 0.0 as float32
        return this
    }

    public invert(): Matrix44 {
        const result: Float32Array = new Float32Array(16)

        let a00 = this.array[0]
        let a01 = this.array[1]
        let a02 = this.array[2]
        let a03 = this.array[3]
        let a10 = this.array[4]
        let a11 = this.array[5]
        let a12 = this.array[6]
        let a13 = this.array[7]
        let a20 = this.array[8]
        let a21 = this.array[9]
        let a22 = this.array[10]
        let a23 = this.array[11]
        let a30 = this.array[12]
        let a31 = this.array[13]
        let a32 = this.array[14]
        let a33 = this.array[15]

        let b00 = a00 * a11 - a01 * a10
        let b01 = a00 * a12 - a02 * a10
        let b02 = a00 * a13 - a03 * a10
        let b03 = a01 * a12 - a02 * a11
        let b04 = a01 * a13 - a03 * a11
        let b05 = a02 * a13 - a03 * a12
        let b06 = a20 * a31 - a21 * a30
        let b07 = a20 * a32 - a22 * a30
        let b08 = a20 * a33 - a23 * a30
        let b09 = a21 * a32 - a22 * a31
        let b10 = a21 * a33 - a23 * a31
        let b11 = a22 * a33 - a23 * a32

        let determinant = b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06
        let invdet = 1.0 / determinant
        b00 *= invdet
        b01 *= invdet
        b02 *= invdet
        b03 *= invdet
        b04 *= invdet
        b05 *= invdet
        b06 *= invdet
        b07 *= invdet
        b08 *= invdet
        b09 *= invdet
        b10 *= invdet
        b11 *= invdet

        result[0]  = a11 * b11 - a12 * b10 + a13 * b09
        result[1]  = a02 * b10 - a01 * b11 - a03 * b09
        result[2]  = a31 * b05 - a32 * b04 + a33 * b03
        result[3]  = a22 * b04 - a21 * b05 - a23 * b03
        result[4]  = a12 * b08 - a10 * b11 - a13 * b07
        result[5]  = a00 * b11 - a02 * b08 + a03 * b07
        result[6]  = a32 * b02 - a30 * b05 - a33 * b01
        result[7]  = a20 * b05 - a22 * b02 + a23 * b01
        result[8]  = a10 * b10 - a11 * b08 + a13 * b06
        result[9]  = a01 * b08 - a00 * b10 - a03 * b06
        result[10] = a30 * b04 - a31 * b02 + a33 * b00
        result[11] = a21 * b02 - a20 * b04 - a23 * b00
        result[12] = a11 * b07 - a10 * b09 - a12 * b06
        result[13] = a00 * b09 - a01 * b07 + a02 * b06
        result[14] = a31 * b01 - a30 * b03 - a32 * b00
        result[15] = a20 * b03 - a21 * b01 + a22 * b00

        // If 1/det overflows to infinity (i.e. det is denormalized) or any of the inverted matrix
        // values is non-finite, return zero to indicate a non-invertible matrix.
        let prod = 0
        for (let i = 0; i < result.length; ++i) {
            prod *= result[i]
        }
        // At this point, prod will either be NaN or 0
        // if prod is NaN, this check will return false
        if (prod == 0) {
            for (let i = 0; i < this.array.length; i++) {
                this.array[i] = result[i]
            }
        }
        return this
    }

    public transpose(): Matrix44 {
        const result: Float32Array = new Float32Array(16)

        result[0] = this.array[0]
        result[1] = this.array[4]
        result[2] = this.array[8]
        result[3] = this.array[12]
        result[4] = this.array[1]
        result[5] = this.array[5]
        result[6] = this.array[9]
        result[7] = this.array[13]
        result[8] = this.array[2]
        result[9] = this.array[6]
        result[10] = this.array[10]
        result[11] = this.array[14]
        result[12] = this.array[3]
        result[13] = this.array[7]
        result[14] = this.array[11]
        result[15] = this.array[15]

        for (let i = 0; i < this.array.length; i++) {
            this.array[i] = result[i]
        }

        return this
    }

    public skew(x?: float32, y?: float32): Matrix44 {
        this.array[1] += x ?? 0.0 as float32
        this.array[4] += y ?? 0.0 as float32
        return this
    }
}
