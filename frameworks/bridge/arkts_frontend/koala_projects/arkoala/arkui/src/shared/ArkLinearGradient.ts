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

import { Equable, flattenFloatColors } from "./basic";

/** @memo:stable */
export class ArkLinearGradient implements Equable {
    angle: number = 180
    direction: number = GradientDirection.NONE
    repeat: boolean = false
    colors: Float32Array

    constructor(angle: number,
                direction: number,
                repeat: boolean,
                colors: any[]) {
        this.angle = angle
        this.direction = direction
        this.repeat = repeat
        this.colors = flattenFloatColors(colors)
    }

    isEqual(value: ArkLinearGradient): boolean {
        return this.angle == value.angle &&
               this.direction == value.direction &&
               this.repeat == value.repeat &&
               this.colors == value.colors // <- This is strange. Using reference comparison in equals !

    }
}

function angleFromDirection(direction: GradientDirection | undefined) {
    if (direction == undefined) return 180 // To bottom
    else if (direction === GradientDirection.TOP) return 0
    else if (direction === GradientDirection.RIGHT_TOP) return 45
    else if (direction === GradientDirection.RIGHT) return 90
    else if (direction === GradientDirection.RIGHT_BOTTOM) return 135
    else if (direction === GradientDirection.BOTTOM) return 180
    else if (direction === GradientDirection.LEFT_BOTTOM) return 225
    else if (direction === GradientDirection.LEFT) return 270
    else if (direction === GradientDirection.LEFT_TOP) return 315
    else return 180
}

export function translateLinearGradientToArkLinearGradient(value: {
    angle?: string | number | undefined
    direction?: GradientDirection | undefined
    colors: any[]
    repeating?: boolean | undefined
}): ArkLinearGradient {
    const angle = value.angle !== undefined ? parseAngle(value.angle) : angleFromDirection(value.direction)
    return new ArkLinearGradient(angle,
        value.direction !== undefined ? value.direction : GradientDirection.BOTTOM,
        value.repeating !== undefined ? value.repeating : false,
        value.colors)
}

export function parseAngle(value: string | number): number {
    if (typeof value === 'number') {
        return value
    } else {
        if (/([0-9]+)deg/.test(value)) {
            return parseFloat(RegExp.$1)
        } else if (/([0-9]+)grad/.test(value)) {
            return parseFloat(RegExp.$1) * 400 / 360
        } else if (/([0-9]+)rad/.test(value)) {
            return parseFloat(RegExp.$1) * 2 * Math.PI / 360
        } else if (/([0-9]+)turn/.test(value)) {
            return parseFloat(RegExp.$1) * 360
        } else {
            return parseFloat(value);
        }
    }
}