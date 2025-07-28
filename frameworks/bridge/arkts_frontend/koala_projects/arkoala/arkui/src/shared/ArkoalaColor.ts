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

import { Equable } from "./basic";
import { isResourceColor } from "./utils";

export class ArkoalaColor implements Equable {
    readonly value: number // uint32  argb
    /**
     * Red color component, value from 0-255 inclusive.
     */
    get red(): number { return 0xFF & (this.value >> 16) }
    /**
     * Green color component, value from 0-255 inclusive.
     */
    get green(): number { return 0xFF & (this.value >> 8) }
    /**
     * Blue color component, value from 0-255 inclusive.
     */
    get blue(): number { return 0xFF & (this.value) }
    /**
     * Alpha component, value from 0-255 inclusive, 255 is fully opaque.
     */
    get alpha(): number { return 0xFF & (this.value) >> 24 }

    /**
     * The opacity of a given color in range [0, 1], where 0 is an
     * opacity of fully transparent color.
     */
    get opacity(): number { return this.alpha / 255 } // [0..1]

    static White = new ArkoalaColor(0xFFFFFFFF)
    static Black = new ArkoalaColor(0xFF000000)
    static Blue = new ArkoalaColor(0xFF0000FF)
    static Brown = new ArkoalaColor(0xFFA52A2A)
    static Gray = new ArkoalaColor(0xFF808080)
    static Green = new ArkoalaColor(0xFF008000)
    static Orange = new ArkoalaColor(0xFFFFA500)
    static Pink = new ArkoalaColor(0xFFFFC0CB)
    static Red = new ArkoalaColor(0xFFFF0000)
    static Yellow = new ArkoalaColor(0xFFFFFF00)

    static rgb(red: number, green: number, blue: number, alpha: number = 255): ArkoalaColor {
        red = valid("red", red, 0, 255, Math.round(red)) // [0..255]
        green = valid("green", green, 0, 255, Math.round(green)) // [0..255]
        blue = valid("blue", blue, 0, 255, Math.round(blue)) // [0..255]
        alpha = valid("alpha", alpha, 0, 255, Math.round(alpha)) // [0..255]
        return new ArkoalaColor(toARGB(red, green, blue, alpha))
    }

    static parse(s: string): ArkoalaColor | undefined {
        const i = s.startsWith("#") ? 1 : s.startsWith("0x") ? 2 : 0
        switch (s.length - i) {
            case 3: // https://en.wikipedia.org/wiki/Web_colors#Shorthand_hexadecimal_form
                return ArkoalaColor.rgb(parse1(s, i), parse1(s, i + 1), parse1(s, i + 2))
            case 4: // shorthand form with alpha
                return ArkoalaColor.rgb(parse1(s, i + 1), parse1(s, i + 2), parse1(s, i + 3), parse1(s, i))
            case 6: // hex triplet
                return ArkoalaColor.rgb(parse2(s, i), parse2(s, i + 2), parse2(s, i + 4))
            case 8: // hex triplet with alpha
                return ArkoalaColor.rgb(parse2(s, i + 2), parse2(s, i + 4), parse2(s, i + 6), parse2(s, i))
        }
        throw new Error("invalid hex string: " + s)
    }

    static create(value: number): ArkoalaColor {
        if (!isInteger(value, 0, 0xFFFFFFFF)) throw new Error("invalid color value: " + value)
        return new ArkoalaColor(value <= 0xFFFFFF ? 0xFF000000 | value : value)
    }

    private constructor(value: number) {
        this.value = value & 0xFFFFFFFF
    }

    isEqual(color: ArkoalaColor): boolean {
        return this.value == color.value
    }
    withAlpha(alpha: number): ArkoalaColor {
        alpha = valid("alpha", alpha, 0, 255, Math.round(alpha))
        return new ArkoalaColor(((alpha & 0xFF) << 24) | (this.value & 0xFFFFFF))
    }

    withOpacity(opacity: number): ArkoalaColor {
        opacity = valid("opacity", opacity, 0, 1)
        return new ArkoalaColor((((opacity * 255) & 0xFF) << 24) | (this.value & 0xFFFFFF))
    }

    toString(): string {
        const s = toHexString(this.red) + toHexString(this.green) + toHexString(this.blue)
        const alpha = this.alpha
        return alpha < 255 ? s + toHexString(this.alpha) : s
    }
}

function toHexString(value: number): string {
    const hex = value.toString(16)
    return hex.length == 1 ? "0" + hex : hex
}

function toARGB(red: number, green: number, blue: number, alpha: number = 255): number {
    return ((alpha & 0xFF) << 24) | ((red & 0xFF) << 16) | ((green & 0xFF) << 8) | (blue & 0xFF)
}

function isInteger(value: number, min: number, max: number) {
    return Number.isInteger(value) && min <= value && value <= max
}

function parse1(s: string, index: number): number {
    const value = parseInt(s.substring(index, index + 1), 16) * 17
    if (isInteger(value, 0, 255)) return value
    throw new Error("invalid hex string: " + s)
}

function parse2(s: string, index: number): number {
    const value = parseInt(s.substring(index, index + 2), 16)
    if (isInteger(value, 0, 255)) return value
    throw new Error("invalid hex string: " + s)
}

function valid(name: string, value: number, min: number, max: number, v = value): number {
    if (isFinite(v) && min <= v && v <= max) return v
    throw new Error("invalid " + name + ": " + value)
}

export function translateColorToArkoalaColor(color: ResourceColor): ArkoalaColor {
    if (isResourceColor(color)) {
        return ArkoalaColor.Black
    }
    if (typeof color === "string") {
        return parseColor(color as string) ?? ArkoalaColor.White
    } else {
        switch (color) {
            case Color.WHITE: {
                return ArkoalaColor.White
            }
            case Color.BLACK: {
                return ArkoalaColor.Black
            }
            case Color.BLUE: {
                return ArkoalaColor.Blue
            }
            case Color.BROWN: {
                return ArkoalaColor.Brown
            }
            case Color.GRAY: {
                return ArkoalaColor.Gray
            }
            case Color.GREEN: {
                return ArkoalaColor.Green
            }
            case Color.GREY: {
                return ArkoalaColor.Gray
            }
            case Color.ORANGE: {
                return ArkoalaColor.Orange
            }
            case Color.PINK: {
                return ArkoalaColor.Pink
            }
            case Color.RED: {
                return ArkoalaColor.Red
            }
            case Color.YELLOW: {
                return ArkoalaColor.Yellow
            }
            default:
                return typeof color === "number"
                    ? ArkoalaColor.create(color)
                    : ArkoalaColor.White
        }
    }
}

const COMMA_SPLITTER = new RegExp(",\\s*")

export function parseColor(arkValue: string): ArkoalaColor | undefined {
    const field = (ArkoalaColor as any)[arkValue]
    if (field instanceof ArkoalaColor) return field
    if (arkValue.startsWith("rgb(") && arkValue.endsWith(")")) {
        const colors = arkValue.substring(4, arkValue.length - 1).split(COMMA_SPLITTER)
        if (colors.length == 3) {
            return ArkoalaColor.rgb(parseInt(colors[0]), parseInt(colors[1]), parseInt(colors[2]))
        } else {
            throw new Error("Incorrect rgb notation: " + arkValue)
        }
    } else if (arkValue.startsWith("rgba(") && arkValue.endsWith(")")) {
        const colors = arkValue.substring(5, arkValue.length - 1).split(COMMA_SPLITTER)
        if (colors.length == 4) {
            return ArkoalaColor.rgb(parseInt(colors[0]), parseInt(colors[1]), parseInt(colors[2])).withOpacity(parseFloat(colors[3]))
        } else {
            throw new Error("Incorrect rgb notation: " + arkValue)
        }
    } else {

        return ArkoalaColor.parse(arkValue)
    }
}
