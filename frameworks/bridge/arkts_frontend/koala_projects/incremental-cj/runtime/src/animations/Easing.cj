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

import std.math.*
/**
 * Easing functions specify the rate of change of a parameter over time.
 * Our animations call them with input value in the ranging [0..1].
 * Usually easing functions return a value in the same range,
 * but some of them may exceed that range.
 */
public type EasingCurve = (value: Float64) -> Float64

/**
 * This namespace provides predefined easing functions
 * to use with {@link animation} and {@link transition}.
 */
public class Easing {
    static let Linear: EasingCurve = {value: Float64 => value}
    static let LinearReversed: EasingCurve = {value: Float64 => 1.0 - value}
    static let EaseInSine: EasingCurve = {value: Float64 => 1.0 - cos(value * Float64.PI / 2.0)}
    static let EaseOutSine: EasingCurve = {value: Float64 => sin(value * Float64.PI / 2.0)}
    static let EaseInOutSine: EasingCurve = {value: Float64 => (1.0 - cos(value * Float64.PI)) / 2.0}
    static let Ease = Easing.cubicBezier(0.25, 0.1, 0.25, 1.0) // https://cubic-bezier.com/#.25,.1,.25,1
    static let EaseIn = Easing.cubicBezier(0.42, 0.0, 1.0, 1.0) // https://cubic-bezier.com/#.42,0,1,1
    static let EaseOut = Easing.cubicBezier(0.0, 0.0, 0.58, 1.0) // https://cubic-bezier.com/#0,0,.58,1
    static let EaseInOut = Easing.cubicBezier(0.42, 0.0, 0.58, 1.0) // https://cubic-bezier.com/#.42,0,.58,1
    static let ViscousFluid = Easing.viscousFluid()
    static let Bubble = Easing.cubicBezier(.32, 2.2, .72, 2.2) // https://cubic-bezier.com/#.32,2.2,.72,2.2

    /**
     * @param easing - an easing function to invert
     * @returns easing function that reflects all points of the original shape
     *                               through the central point (0.5;0.5)
     */
    static func inverted(easing: EasingCurve): EasingCurve {
        return {value: Float64 => 1.0 - easing(1.0 - value)}
    }

    /**
     * @param easing - an easing function to reverse
     * @returns easing function that reflects all points of the original shape
     *                               through the central vertical axis (0.5)
     */
    static func reversed(easing: EasingCurve): EasingCurve {
        return {value: Float64 => easing(1.0 - value)}
    }

    /**
     * @param easing - an easing function to modify
     * @returns easing function that returns minimal value instead of maximal one
     * @internal
     */
    static func restarted(easing: EasingCurve): EasingCurve {
        return {
            value: Float64 => if (value < 1.0) {
                return easing(value)
            } else {
                return easing(0.0)
            }
        }
    }

    /**
     * @param easing - an easing function to join
     * @param count - an amount of iterations of the specified function
     * @returns easing function that repeats the specified one several times
     */
    static func repeated(easing: EasingCurve, count: UInt32): EasingCurve {
        if (count == 1) {
            return easing
        }
        if (count < 1) {
            throw IllegalArgumentException("unexpected iteration count: ${count}")
        }
        return {
            value: Float64 =>
            if (value <= 0.0) {
                return easing(0.0)
            }
            if (value < 1.0) {
                let index = floor(value * Float64(count))
                if (index < Float64(count)) {
                    return easing(value * Float64(count) - index)
                }
            }
            return easing(1.0)
        }
    }

    /**
     * @param easing - easing functions to join
     * @returns easing function that applies specified functions one by one
     */
    static func joined(easing: Array<EasingCurve>): EasingCurve {
        match (easing.size) {
            case 0 => throw IllegalArgumentException("no easing functions to join")
            case 1 => easing[0]
            case size => {
                value: Float64 =>
                if (value <= 0.0) {
                    return easing[0](0.0)
                }
                if (value < 1.0) {
                    let max = value * Float64(size)
                    let min = floor(max)
                    let index = Int64(min)
                    if (index < size) {
                        return easing[index](max - min)
                    }
                }
                return easing[size - 1](1.0)
            }
        }
    }

    /**
     * @param easing - an easing function to join
     * @returns easing function that joins the specified function with its reversed variant
     */
    static func thereAndBackAgain(easing: EasingCurve): EasingCurve {
        return {
            value: Float64 => if (value < 0.5) {
                return easing(2.0 * value)
            } else {
                return easing(2.0 - 2.0 * value)
            }
        }
    }

    /**
     * @param p1x the horizontal position of the first point
     * @param p1y the vertical position of the first point
     * @param p2x the horizontal position of the second point
     * @param p2y the vertical position of the second point
     * @returns easing function based on the cubic bezier curve
     */
    static func cubicBezier(p1x: Float64, p1y: Float64, p2x: Float64, p2y: Float64): EasingCurve {
        let matrix = EasingSupport.newCubicBezier(p1x, p1y, p2x, p2y)
        return {value: Float64 => matrix.convert(value)}
    }

    /**
     * @param stops - a number of frames with constant values
     * @returns easing function that displays an animation iteration along the specified stops,
     *                               displaying each stop for equal lengths of time
     */
    static func steps(stops: UInt32): EasingCurve {
        steps(stops, EasingStepJump.None)
    }

    /**
     * @param stops - a number of frames with constant values
     * @param jump - a preferred method to generate these values
     * @returns easing function that displays an animation iteration along the specified stops,
     *                               displaying each stop for equal lengths of time
     * @see EasingStepJump
     */
    static func steps(stops: UInt32, jump: EasingStepJump): EasingCurve {
        if (stops == 1) {
            match (jump) {
                case EasingStepJump.Start => return {value: Float64 => 1.0}
                case EasingStepJump.End => return {value: Float64 => 0.0}
                case EasingStepJump.Both => return {value: Float64 => 0.5}
                case EasingStepJump.None => throw IllegalArgumentException(
                    "easing with one stop must use jump other than EasingStepJump.None")
            }
        }
        if (stops <= 1) {
            throw IllegalArgumentException("easing stops must be a positive integer, but is ${stops}")
        }
        let delta = match (jump) {
            case None => 0.0
            case End => 0.0
            case Both => 1.0
            case Start => 1.0
        }
        let count: UInt32 = match (jump) {
            case None => stops - 1
            case Both => stops + 1
            case Start => stops
            case End => stops
        }
        return {
            value: Float64 => if (value > 0.0) {
                return min(Float64(stops - 1), floor(Float64(stops) * value) + delta) / Float64(count)
            } else {
                return delta / Float64(count)
            }
        }
    }

    static func viscousFluid(): EasingCurve {
        return {value: Float64 => (1.0 / (-4.2) * 3.0) * (exp((-4.2) * value * 3.0) - 1.0)}
    }

    static func viscousFluid(v0: Float64): EasingCurve {
        return {value: Float64 => (v0 / (-4.2) * 3.0) * (exp((-4.2) * value * 3.0) - 1.0)}
    }

    static func viscousFluid(v0: Float64, f: Float64): EasingCurve {
        return {value: Float64 => (v0 / (-4.2) * f) * (exp((-4.2) * value * f) - 1.0)}
    }
}

// https://developer.mozilla.org/en-US/docs/Web/CSS/animation-timing-function
enum EasingStepJump {
    /** Denotes a left-continuous function, so that the first jump happens when the animation begins. */
    | Start
    /** Denotes a right-continuous function, so that the last jump happens when the animation ends. */
    | End
    /** There is no jump on either end. Instead, holding at both the 0% mark and the 100% mark, each for 1/n of the duration. */
    | None
    /** Includes pauses at both the 0% and 100% marks, effectively adding a step during the animation iteration. */
    | Both
}
