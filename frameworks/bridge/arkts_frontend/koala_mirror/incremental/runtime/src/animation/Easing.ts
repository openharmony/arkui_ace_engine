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

import { float64, uint32 } from "@koalaui/common"
import { EasingSupport } from "./EasingSupport"

/**
 * Easing functions specify the rate of change of a parameter over time.
 * Our animations call them with input value in the ranging [0..1].
 * Usually easing functions return a value in the same range,
 * but some of them may exceed that range.
 */
export type EasingCurve = (value: float64) => float64

/**
 * This namespace provides predefined easing functions
 * to use with {@link animation} and {@link transition}.
 */
export class Easing {
    static readonly Linear: EasingCurve = (value: float64) => value
    static readonly LinearReversed: EasingCurve = (value: float64) => 1 - value
    static readonly EaseInSine: EasingCurve = (value: float64) => 1 - Math.cos(value * Math.PI / 2)
    static readonly EaseOutSine: EasingCurve = (value: float64) => Math.sin(value * Math.PI / 2)
    static readonly EaseInOutSine: EasingCurve = (value: float64) => (1 - Math.cos(value * Math.PI)) / 2
    static readonly Ease = Easing.cubicBezier(.25, .1, .25, 1) // https://cubic-bezier.com/#.25,.1,.25,1
    static readonly EaseIn = Easing.cubicBezier(.42, 0, 1, 1) // https://cubic-bezier.com/#.42,0,1,1
    static readonly EaseOut = Easing.cubicBezier(0, 0, .58, 1) // https://cubic-bezier.com/#0,0,.58,1
    static readonly EaseInOut = Easing.cubicBezier(.42, 0, .58, 1) // https://cubic-bezier.com/#.42,0,.58,1
    static readonly ViscousFluid = Easing.viscousFluid()
    static readonly Bubble = Easing.cubicBezier(.32, 2.2, .72, 2.2) // https://cubic-bezier.com/#.32,2.2,.72,2.2

    /**
     * @param easing - an easing function to invert
     * @returns easing function that reflects all points of the original shape
     *                               through the central point (0.5;0.5)
     */
    static inverted(easing: EasingCurve): EasingCurve {
        return (value: float64) => 1 - easing(1 - value)
    }

    /**
     * @param easing - an easing function to reverse
     * @returns easing function that reflects all points of the original shape
     *                               through the central vertical axis (0.5)
     */
    static reversed(easing: EasingCurve): EasingCurve {
        return (value: float64) => easing(1 - value)
    }

    /**
     * @param easing - an easing function to modify
     * @returns easing function that returns minimal value instead of maximal one
     * @internal
     */
    static restarted(easing: EasingCurve): EasingCurve {
        return (value: float64) => easing(value < 1 ? value : 0)
    }

    /**
     * @param easing - an easing function to join
     * @param count - an amount of iterations of the specified function
     * @returns easing function that repeats the specified one several times
     */
    static repeated(easing: EasingCurve, count: uint32): EasingCurve {
        if (count == 1) return easing
        if (!Number.isInteger(count) || (count < 1)) throw new Error("unexpected iteration count: " + count)
        return (value: float64) => {
            if (value <= 0) return easing(0)
            if (value < 1) {
                value *= count
                const index = Math.floor(value)
                if (index < count) return easing(value - index)
            }
            return easing(1)
        }
    }

    /**
     * @param easing - easing functions to join
     * @returns easing function that applies specified functions one by one
     */
    static joined(...easing: EasingCurve[]): EasingCurve {
        if (easing.length == 0) throw new Error("no easing functions to join")
        if (easing.length == 1) return easing[0]
        return (value: float64) => {
            if (value <= 0) return easing[0](0)
            if (value < 1) {
                value *= easing.length
                const index = Math.floor(value)
                if (index < easing.length) return easing[index as uint32](value - index)
            }
            return easing[easing.length - 1](1)
        }
    }

    /**
     * @param easing - an easing function to join
     * @returns easing function that joins the specified function with its reversed variant
     */
    static thereAndBackAgain(easing: EasingCurve): EasingCurve {
        return (value: float64) => value < 0.5 ? easing(2 * value) : easing(2 - 2 * value)
    }

    /**
     * @param p1x the horizontal position of the first point
     * @param p1y the vertical position of the first point
     * @param p2x the horizontal position of the second point
     * @param p2y the vertical position of the second point
     * @returns easing function based on the cubic bezier curve
     */
    static cubicBezier(p1x: float64, p1y: float64, p2x: float64, p2y: float64): EasingCurve {
        const matrix = EasingSupport.newCubicBezier(p1x, p1y, p2x, p2y)
        return (value: float64) => matrix.convert(value)
    }

    /**
     * @param stops - a number of frames with constant values
     * @param jump - a preferred method to generate these values
     * @returns easing function that displays an animation iteration along the specified stops,
     *                               displaying each stop for equal lengths of time
     * @see EasingStepJump
     */
    static steps(stops: uint32, jump:EasingStepJump = EasingStepJump.None): EasingCurve {
        if (stops == 1) {
            switch (jump) {
                case EasingStepJump.Start: return (value: float64) => 1.0
                case EasingStepJump.End: return (value: float64) => 0.0
                case EasingStepJump.Both: return (value: float64) => 0.5
                case EasingStepJump.None: throw new Error("easing with one stop must use jump other than EasingStepJump.None")
            }
        }
        if (!Number.isInteger(stops) || stops <= 1) throw new Error("easing stops must be a positive integer, but is " + stops)
        const delta = jump == EasingStepJump.None || jump == EasingStepJump.End ? 0 : 1
        const count: uint32 = jump == EasingStepJump.None ? stops - 1 : jump == EasingStepJump.Both ? stops + 1 : stops
        return (value: float64) => (value > 0 ? Math.min(stops - 1, Math.floor(stops * value)) + delta : delta) / count
    }

    static viscousFluid(v0: float64 = 1, f: float64 = 3): EasingCurve {
        return (value: float64) => (v0 / (-4.2) * f) * (Math.exp((-4.2) * value * f) - 1)
    }
}

// https://developer.mozilla.org/en-US/docs/Web/CSS/animation-timing-function
export enum EasingStepJump {
    /** Denotes a left-continuous function, so that the first jump happens when the animation begins. */
    Start,
    /** Denotes a right-continuous function, so that the last jump happens when the animation ends. */
    End,
    /** There is no jump on either end. Instead, holding at both the 0% mark and the 100% mark, each for 1/n of the duration. */
    None,
    /** Includes pauses at both the 0% and 100% marks, effectively adding a step during the animation iteration. */
    Both,
}
