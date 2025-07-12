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

import { float32 } from "@koalaui/compat"

export class Point {
    coordinates: Float32Array

    constructor (x: float32, y: float32) {
        this.coordinates = new Float32Array(2)
        this.coordinates[0] = x
        this.coordinates[1] = y
    }

    get x(): float32 {
        return this.coordinates[0] as float32
    }

    get y(): float32 {
        return this.coordinates[1] as float32
    }

    offsetXY(dx: float32, dy: float32): Point {
        return new Point(this.x + dx, this.y + dy)
    }

    offset(vec: Point): Point {
        return this.offsetXY(vec.x, vec.y)
    }

    scale(scale: float32): Point {
        return this.scaleXY(scale, scale)
    }

    scaleXY(sx: float32, sy: float32): Point {
        return new Point(this.x * sx, this.y * sy)
    }

    static ZERO = new Point(0.0 as float32, 0.0 as float32)

    toArray(): Float32Array {
        return this.coordinates
    }

    static flattenArray(points: Array<Point>): Float32Array {
        let array = new Float32Array(points.length * 2)
        for (let i = 0; i < points.length; i++) {
            array[i * 2] = points[i].x
            array[i * 2 + 1] = points[i].y
        }
        return array
    }

    static fromArray(points: Float32Array): Array<Point> {
        if (points.length % 2 != 0)
            throw new Error("Expected " + points.length + " % 2 == 0")

        let array = new Array<Point>(points.length / 2)
        for (let i = 0; i < points.length / 2; i++) {
            array[i] = new Point(points[i * 2] as float32, points[i * 2 + 1] as float32)
        }
        return array
    }
}
