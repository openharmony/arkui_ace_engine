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

import { float64, int32, int64, isFiniteNumber, uint32 } from "@koalaui/common"
import { AnimationRange, NumberAnimationRange } from "./AnimationRange"
import { Easing, EasingCurve } from "./Easing"
import { scheduleCallback } from "../states/GlobalStateManager"

export const DEFAULT_ANIMATION_DURATION: uint32 = 300

/**
 * This interface specifies animations in AnimatedState (or MutableAnimatedState).
 * Its methods should not be used directly.
 */
export interface TimeAnimation<Value> {
    readonly running: boolean
    getValue(time: int64): Value
    onStart(time: int64): void
    onPause(time: int64): void
}

/**
 * This interface allows to control various settings of a duration-based animation.
 */
export interface AnimationSpec {
    readonly duration: uint32
    readonly delay: uint32
    readonly easing: EasingCurve
    readonly onEdge: OnEdge
    readonly onPause: OnPause
    readonly iterations: int32 | undefined // an amount of iterations of the specified function
    readonly onStart: (() => void) | undefined // called when the animation has started
    readonly onEnd: (() => void) | undefined // called when the animation has reached the target value
    readonly onReset: (() => void) | undefined // called when the animation is reset to the initial value
}

/**
 * This enumeration specifies the animation behavior when duration is expired.
 */
export class OnEdge {
    static Nothing = new OnEdge("Nothing") // the value stops changing
    static Reverse = new OnEdge("Reverse") // the value starts changing to the initial state
    static Restart = new OnEdge("Restart") // the value starts changing from the initial state again
    private constructor(name: string) {
    }
}

/**
 * This enumeration specifies the animation behavior on pause requested.
 */
export class OnPause {
    static Nothing = new OnPause("Nothing") // the value stops changing immediately
    static Reset = new OnPause("Reset") // the value resets to the initial state and stops changing
    static Fade = new OnPause("Fade") // the value starts changing to the initial state and then stops changing
    private constructor(name: string) {
    }
}


/**
 * @param value - value constantly returned by the animation
 * @returns animation that always produces the same value
 */
export function constAnimation<Value>(value: Value): TimeAnimation<Value> {
    return new ConstAnimationImpl<Value>(value)
}

/**
 * @param compute - value supplier to be computed for every frame
 * @param initialTime - initial time value of the animation
 * @returns simple time-based animation that starts with 0
 */
export function timeAnimation<Value>(compute: (time: int64) => Value, initialTime: int64 = 0): TimeAnimation<Value> {
    if (!isFiniteNumber(initialTime)) throw new Error("illegal initial time: " + initialTime)
    return new TimeAnimationImpl<Value>(compute, initialTime)
}

/**
 * Computes smoothly changing values from `from` to `to` with given period in milliseconds.
 * Current law of change is sinus.
 *
 * @param period during which value changes from `from` back to `from`
 * @param from which value animation starts, default is 0.0
 * @param to which value animation reaches, default is 1.0
 * @returns animated value in 0.0 to 1.0 range
 */
export function smoothAnimation(period: uint32, from: float64 = 0.0, to: float64 = 1.0): TimeAnimation<float64> {
    if (!isFiniteNumber(period) || (period < 1)) throw new Error("illegal period: " + period)
    if (from >= to) throw new Error("`from` must be smaller than `to`")
    return new TimeAnimationImpl<float64>((time: int64): float64 => (1 - Math.cos(time / period * Math.PI)) / 2 * (to - from) + from)
}

/**
 * @param period - number of milliseconds after which the animated state toggles boolean value
 * @param initialValue - initial blinking state of the animation
 * @returns animation of boolean value that is toggled periodically
 */
export function blinkAnimation(period: uint32, initialValue: boolean = false): TimeAnimation<boolean> {
    return periodicAnimation<boolean>(period, (count: int64): boolean => (count % 2) != 0, initialValue ? 1 : 0)
}

/**
 * @param period - number of milliseconds after which the animated state increments number value
 * @param initialCount - initial counter value of the animation
 * @returns animation of integer value that is incremented periodically
 */
export function countAnimation(period: uint32, initialCount: int64 = 0): TimeAnimation<int64> {
    return periodicAnimation<int64>(period, (count: int64): int64 => count, initialCount)
}

/**
 * @param period - number of milliseconds after which the animated state computes its value from period counter
 * @param compute - value supplier to be computed every `period` milliseconds
 * @param initialCount - initial counter value of the animation
 * @returns animation of integer value that is computed periodically from counter
 */
export function periodicAnimation<Value>(period: uint32, compute: (count: int64) => Value, initialCount: int64 = 0): TimeAnimation<Value> {
    if (!isFiniteNumber(period) || (period < 1)) throw new Error("illegal time period: " + period)
    if (!isFiniteNumber(initialCount)) throw new Error("illegal initial count: " + initialCount)
    return new PeriodicAnimationImpl<Value>(0, period, compute, initialCount)
}

/**
 * @param delay - number of milliseconds after which the animated state computes its first value
 * @param period - number of milliseconds after which the animated state computes its value from period counter
 * @param compute - value supplier to be computed every `period` milliseconds
 * @param initialCount - initial counter value of the animation
 * @returns animation of integer value that is computed periodically from counter
 */
export function periodicAnimationWithDelay<Value>(delay: uint32, period: uint32, compute: (count: int64) => Value, initialCount: int64 = 0): TimeAnimation<Value> {
    if (!isFiniteNumber(period) || (period < 1)) throw new Error("illegal time period: " + period)
    if (!isFiniteNumber(delay) || (delay < 1)) throw new Error("illegal time delay: " + delay)
    if (!isFiniteNumber(initialCount)) throw new Error("illegal initial count: " + initialCount)
    return new PeriodicAnimationImpl<Value>(delay - period, period, compute, initialCount)
}


/**
 * @param frameTime - array of frame durations in milliseconds
 * @param compute - value supplier to be computed when frame index is changed
 * @returns frame-based animation
 */
export function frameAnimation<Value>(frameTime: ReadonlyArray<uint32>, compute: (index: int64) => Value): TimeAnimation<Value> {
    const count = frameTime.length
    if (count == 1) return constAnimation<Value>(compute(0))
    if (count < 2) throw new Error("illegal frames count: " + count)
    const time = new Array<uint32>(count)
    for (let index = 0; index < count; index++) {
        const value = frameTime[index]
        if (!isFiniteNumber(value) || (value < 1)) throw new Error("illegal time of frame " + index + ": " + value)
        time[index] = index > 0 ? time[index - 1] + value : value
    }
    return new FrameAnimationImpl<Value>(time, compute)
}


/**
 * @param spec - the animation specification
 * @param from - a first base array that corresponds to the `0` state
 * @param to - a second base array that corresponds to the `1` state
 * @returns duration-based animation of number value
 */
export function numberAnimation(spec: Partial<AnimationSpec>, to: float64 = 1.0, from: float64 = 0.0): TimeAnimation<float64> {
    return animation<float64>(spec, NumberAnimationRange(from, to))
}

/**
 * @param spec - the animation specification
 * @param compute - value supplier to be computed when state animated from 0 to 1
 * @param initialState - initial inner state of the animation (-1..1]
 * @returns duration-based animation
 */
export function animation<Value>(spec: Partial<AnimationSpec>, compute: AnimationRange<Value>, initialState: float64 = 0): TimeAnimation<Value> {
    if (!isFiniteNumber(initialState) || (initialState <= -1) || (initialState > 1)) throw new Error("illegal initial state: " + initialState)
    let duration: uint32 = spec?.duration ?? DEFAULT_ANIMATION_DURATION
    if (!isFiniteNumber(duration) || (duration < 0)) throw new Error("duration must not be negative, but is " + spec.duration)
    let delay: uint32 = spec?.delay ?? 0
    if (!isFiniteNumber(delay) || (delay < 0)) throw new Error("delay must not be negative, but is " + spec.delay)
    let easing = spec.easing ?? Easing.Linear
    let onEdge: OnEdge = spec?.onEdge ?? OnEdge.Nothing
    let iterations: int32 | undefined = spec?.iterations
    if (iterations !== undefined) {
        if (!Number.isInteger(iterations) || (iterations < 1)) throw new Error("iterations must be positive integer, but is " + spec.iterations)
        if (onEdge == OnEdge.Reverse) {
            easing = Easing.thereAndBackAgain(easing)
            duration *= 2
        }
        if (iterations > 1) {
            easing = Easing.repeated(easing, iterations)
            duration *= iterations
        }
        if (onEdge == OnEdge.Restart) {
            easing = Easing.restarted(easing)
        }
        onEdge = OnEdge.Nothing
    }
    if (duration == 0 && onEdge != OnEdge.Nothing) {
        throw new Error("cyclic animation must have a positive duration, but has " + spec.duration)
    }
    return new AnimationImpl<Value>(
        duration, delay, easing, onEdge, spec?.onPause ?? OnPause.Nothing,
        spec.onStart, spec.onEnd, spec.onReset, compute, initialState)
}


/**
 * @param duration - duration of state transition from 0 to 1
 * @param easing - a way in which a motion tween proceeds
 * @param compute - value supplier to be computed when state animated from 0 to 1
 * @param initialState - initial inner state of the animation (-1..1]
 * @returns duration-based value transition
 */
export function transition<Value>(duration: uint32, easing: EasingCurve, compute: AnimationRange<Value>, initialState: int64 = 0): TimeAnimation<Value> {
    if (!isFiniteNumber(initialState) || (initialState <= -1) || (initialState > 1)) throw new Error("illegal initial state: " + initialState)
    if (!isFiniteNumber(duration) || (duration <= 0)) throw new Error("duration must be positive, but is " + duration)
    return new AnimationImpl<Value>(duration, 0, easing, OnEdge.Nothing, OnPause.Fade, undefined, undefined, undefined, compute, initialState)
}

/**
 * @param duration - duration of state transition from 0 to 1
 * @param compute - value supplier to be computed when state animated from 0 to 1
 * @param initialState - initial inner state of the animation (-1..1]
 * @returns duration-based value transition
 */
export function linearTransition<Value>(duration: uint32, compute: AnimationRange<Value>, initialState: int64 = 0): TimeAnimation<Value> {
    return transition<Value>(duration, Easing.Linear, compute, initialState)
}


// IMPLEMENTATION DETAILS: DO NOT USE IT DIRECTLY


class TimeAnimationImpl<Value> implements TimeAnimation<Value> {
    private startTime: int64 | undefined
    private lastState: int64
    private lastValue: Value
    private readonly compute: (time: int64) => Value

    running: boolean = false

    constructor(
        compute: (time: int64) => Value,
        initial: int64 = 0
    ) {
        this.lastState = initial
        this.lastValue = compute(initial)
        this.compute = compute
    }

    get state(): int64 {
        return this.lastState
    }

    getState(startTime: int64, currentTime: int64): int64 {
        this.startTime = currentTime
        return this.lastState + (currentTime - startTime)
    }

    getValue(time: int64): Value {
        const startTime = this.startTime
        if (startTime === undefined) return this.lastValue // paused
        if (startTime >= time) return this.lastValue // delayed
        const state = this.getState(startTime, time)
        if (this.lastState == state) return this.lastValue // not changed
        this.lastState = state
        this.lastValue = this.compute(state)
        return this.lastValue
    }

    onStart(time: int64): void {
        this.startTime = time
        this.running = true
    }

    onPause(time: int64): void {
        this.startTime = undefined
        this.running = false
    }
}


class PeriodicAnimationImpl<Value> implements TimeAnimation<Value> {
    private startTime: int64 | undefined
    private lastState: int64
    private lastValue: Value
    private readonly compute: (time: int64) => Value
    private readonly period: uint32
    private readonly delay: int32

    running: boolean = false

    constructor(
        delay: int32,
        period: uint32,
        compute: (count: int64) => Value,
        initial: int64 = 0
    ) {
        this.lastState = initial
        this.lastValue = compute(initial)
        this.compute = compute
        this.period = period
        this.delay = delay
    }

    get state(): int64 {
        return this.lastState
    }

    getState(startTime: int64, currentTime: int64): int64 {
        let result = this.state
        let passedTime = currentTime - startTime
        if (passedTime > this.period) {
            result += Math.floor(passedTime / this.period) as int64
            passedTime = passedTime % this.period
            // tune start time for long animations
            this.startTime = currentTime - passedTime
            this.running = true
        }
        return result
    }

    getValue(time: int64): Value {
        const startTime = this.startTime
        if (startTime === undefined) return this.lastValue // paused
        if (startTime >= time) return this.lastValue // delayed
        const state = this.getState(startTime, time)
        if (this.lastState == state) return this.lastValue // not changed
        this.lastState = state
        this.lastValue = this.compute(state)
        return this.lastValue
    }

    onStart(time: int64): void {
        this.startTime = time + this.delay
        this.running = true
    }

    onPause(time: int64): void {
        this.startTime = undefined
        this.running = false
    }
}


class ConstAnimationImpl<Value> implements TimeAnimation<Value> {
    private lastValue: Value

    constructor(value: Value) {
        this.lastValue = value
    }

    running: boolean = false

    getValue(time: int64): Value {
        return this.lastValue
    }

    onStart(time: int64): void {
    }

    onPause(time: int64): void {
    }
}


class FrameAnimationImpl<Value> implements TimeAnimation<Value> {
    private startTime: int64 | undefined
    private lastState: int64
    private lastValue: Value
    private readonly compute: (time: int64) => Value
    private readonly time: ReadonlyArray<uint32>

    running: boolean = false

    constructor(time: ReadonlyArray<uint32>, compute: (time: int64) => Value) {
        this.lastState = 0
        this.lastValue = compute(0)
        this.compute = compute
        this.time = time
    }

    get state(): int64 {
        return this.lastState
    }

    getState(startTime: int64, currentTime: int64): int64 {
        const cycleTime = this.time[this.time.length - 1]

        let passedTime = currentTime - startTime
        if (passedTime > cycleTime) {
            passedTime = passedTime % cycleTime
            // tune start time for long animations
            this.startTime = currentTime - passedTime
            this.running = true
        }
        for (let index = 0; index < this.time.length; index++) {
            if (passedTime < this.time[index]) return index
        }
        return 0
    }

    getValue(time: int64): Value {
        const startTime = this.startTime
        if (startTime === undefined) return this.lastValue // paused
        if (startTime >= time) return this.lastValue // delayed
        const state = this.getState(startTime, time)
        if (this.lastState == state) return this.lastValue // not changed
        this.lastState = state
        this.lastValue = this.compute(state)
        return this.lastValue
    }

    onStart(time: int64): void {
        this.startTime = time
        this.running = true
    }

    onPause(time: int64): void {
        this.startTime = undefined
        this.running = false
    }
}


class AnimationImpl<Value> implements TimeAnimation<Value> {
    private startTime: int64 | undefined
    private lastState: float64
    private lastValue: Value
    private readonly duration: uint32
    private readonly delay: uint32
    private readonly onEdgePolicy: OnEdge
    private readonly onPausePolicy: OnPause
    private readonly onStartCallback: (() => void) | undefined
    private readonly onEndCallback: (() => void) | undefined
    private readonly onResetCallback: (() => void) | undefined
    private readonly compute: AnimationRange<Value>
    private isPauseRequested = false

    running: boolean = false

    constructor(
        duration: uint32,
        delay: uint32,
        easing: EasingCurve,
        onEdge: OnEdge,
        onPause: OnPause,
        onStart: (() => void) | undefined,
        onEnd: (() => void) | undefined,
        onReset: (() => void) | undefined,
        compute: AnimationRange<Value>,
        initial: float64 = 0
    ) {
        this.duration = duration
        this.delay = delay
        this.onEdgePolicy = onEdge
        this.onPausePolicy = onPause
        this.onStartCallback = onStart
        this.onEndCallback = onEnd
        this.onResetCallback = onReset
        this.compute = (state: float64): Value => compute(easing(Math.abs(state)))
        this.lastState = initial
        this.lastValue = this.compute(initial)
    }

    getState(startTime: int64, currentTime: int64): float64 {
        const onPause = this.isPauseRequested ? this.onPausePolicy : OnPause.Nothing
        if (onPause == OnPause.Reset) return this.onPauseReset() // pause
        if (this.duration == 0) return this.onEdgeReached() // stop immediately

        const cycleTime: int64 = onPause == OnPause.Fade || this.onEdgePolicy == OnEdge.Reverse
            ? this.duration * 2
            : this.duration

        let passedTime = currentTime - startTime
        if (passedTime > cycleTime) {
            if (onPause == OnPause.Fade) return this.onPauseReset() // fade stopped
            if (this.onEdgePolicy == OnEdge.Nothing) return this.onEdgeReached() // stop on the edge
            passedTime = passedTime % cycleTime
            // tune start time for long animations
            this.running = true
            this.startTime = currentTime - passedTime
        }
        let state = passedTime / this.duration
        return state > 1 ? state - 2 : state
    }

    getValue(time: int64): Value {
        const startTime = this.startTime
        if (startTime === undefined) return this.lastValue // paused
        if (startTime >= time) return this.lastValue // delayed
        const state = this.getState(startTime, time)
        if (this.lastState == state) return this.lastValue // not changed
        this.lastState = state
        this.lastValue = this.compute(state)
        return this.lastValue
    }

    onStart(time: int64): void {
        scheduleCallback(this.onStartCallback)
        if (this.isPauseRequested) {
            this.isPauseRequested = false
            if (this.lastState < 0) {
                // tune start time on direction change
                this.running = true
                this.startTime = time + (this.lastState * this.duration) as int64
            }
        }
        else {
            // set start time to continue animation from the current state
            this.running = true
            this.startTime = time - (
                this.lastState < 0
                    ? (2 + this.lastState) * this.duration
                    : this.lastState > 0
                        ? this.lastState * this.duration
                        : (0 - this.delay) // add delay for the state 0 only
            ) as int64
        }
    }

    onPause(time: int64): void {
        if (this.lastState && this.onPausePolicy == OnPause.Reset) {
            this.isPauseRequested = true
        }
        else if (this.lastState && this.onPausePolicy == OnPause.Fade) {
            this.isPauseRequested = true
            if (this.lastState > 0) {
                // tune start time on direction change
                this.running = true
                this.startTime = time - (this.duration * (2 - this.lastState)) as int64
            }
        }
        else {
            this.running = false
            this.startTime = undefined
        }
    }

    private onPauseReset(): float64 {
        this.running = false
        this.startTime = undefined
        this.isPauseRequested = false
        scheduleCallback(this.onResetCallback)
        return 0
    }

    private onEdgeReached(): float64 {
        if (this.running) {
            this.running = false
            scheduleCallback(this.onEndCallback)
        }
        return 1
    }
}
