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

import KoalaRuntime.core.*

import std.math.*
import std.collection.*

public const DEFAULT_ANIMATION_DURATION: UInt32 = 300

/**
 * This interface specifies animations in AnimatedState (or MutableAnimatedState).
 * Its methods should not be used directly.
 */
public interface TimeAnimation<Value> {
    func isRunning(): Bool
    func getValue(time: UInt64): Value
    func onStart(time: UInt64): Unit
    func onPause(time: UInt64): Unit
}

/**
 * This interface allows to control various settings of a duration-based animation.
 */
public class AnimationSpec {
    public let duration: UInt32
    public let delay: UInt32
    public let easing: EasingCurve
    public let onEdge: OnEdge
    public let onPause: OnPause
    public let iterations: ?UInt32 // an amount of iterations of the specified function
    public let onStart: ?(() -> Unit) // called when the animation has started
    public let onEnd: ?(() -> Unit) // called when the animation has reached the target value
    public let onReset: ?(() -> Unit) // called when the animation is reset to the initial value

    init(
        duration: UInt32,
        delay: UInt32,
        easing: EasingCurve,
        onEdge: OnEdge,
        onPause: OnPause,
        iterations: ?UInt32,
        onStart: ?(() -> Unit),
        onEnd: ?(() -> Unit),
        onReset: ?(() -> Unit)
    ) {
        this.duration = duration
        this.delay = delay
        this.easing = easing
        this.onEdge = onEdge
        this.onPause = onPause
        this.iterations = iterations
        this.onStart = onStart
        this.onEnd = onEnd
        this.onReset = onReset
    }
}

public class PartialAnimationSpec {
    public let duration: ?UInt32
    public let delay: ?UInt32
    public let easing: ?EasingCurve
    public let onEdge: ?OnEdge
    public let onPause: ?OnPause
    public let iterations: ?UInt32 // an amount of iterations of the specified function
    public let onStart: ?(() -> Unit) // called when the animation has started
    public let onEnd: ?(() -> Unit) // called when the animation has reached the target value
    public let onReset: ?(() -> Unit) // called when the animation is reset to the initial value

    init(
        duration: UInt32,
        delay: ?UInt32,
        easing: ?EasingCurve,
        onEdge: ?OnEdge,
        onPause: ?OnPause,
        iterations: ?UInt32,
        onStart: ?(() -> Unit),
        onEnd: ?(() -> Unit),
        onReset: ?(() -> Unit)
    ) {
        this.duration = duration
        this.delay = delay
        this.easing = easing
        this.onEdge = onEdge
        this.onPause = onPause
        this.iterations = iterations
        this.onStart = onStart
        this.onEnd = onEnd
        this.onReset = onReset
    }
}

/**
 * This enumeration specifies the animation behavior when duration is expired.
 */
public enum OnEdge {
    | DoNothing // the value stops changing
    | Reverse // the value starts changing to the initial state
    | Restart // the value starts changing from the initial state again
}

/**
 * This enumeration specifies the animation behavior on pause requested.
 */
public enum OnPause {
    | DoNothing // the value stops changing immediately
    | Reset // the value resets to the initial state and stops changing
    | Fade // the value starts changing to the initial state and then stops changing
}

/**
 * @param value - value constantly returned by the animation
 * @returns animation that always produces the same value
 */
public func constAnimation<Value>(value: Value): TimeAnimation<Value> {
    return ConstAnimationImpl(value)
}

/**
 * @param compute - value supplier to be computed for every frame
 * @param initialTime - initial time value of the animation
 * @returns simple time-based animation that starts with 0
 */
public func timeAnimation<Value>(compute: (time: Int64) -> Value): TimeAnimation<Value> {
    return TimeAnimationImpl(compute, 0)
}

public func timeAnimation<Value>(compute: (time: Int64) -> Value, initialTime: Int64): TimeAnimation<Value> {
    if (!Float32(initialTime).isNormal()) {
        throw IllegalArgumentException("illegal initial time: ${initialTime}")
    }
    return TimeAnimationImpl(compute, initialTime)
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
public func smoothAnimation(period: UInt32): TimeAnimation<Float32> {
    if (!Float32(period).isNormal() || (period < 1)) {
        throw IllegalArgumentException("illegal period: ${period}")
    }
    return TimeAnimationImpl<Float32>({time: Int64 => 1.0 - cos(Float32(time) / Float32(period) * Float32.PI) / 2.0})
}

public func smoothAnimation(period: UInt32, isfrom: Float32, to: Float32): TimeAnimation<Float32> {
    if (!Float32(period).isNormal() || (period < 1)) {
        throw IllegalArgumentException("illegal period: ${period}")
    }
    if (isfrom >= to) {
        throw IllegalArgumentException("`from` must be smaller than `to`")
    }
    return TimeAnimationImpl<Float32>(
        {time: Int64 => 1.0 - cos(Float32(time) / Float32(period) * Float32.PI) / 2.0 * (to - isfrom) + isfrom})
}

/**
 * @param period - number of milliseconds after which the animated state toggles boolean value
 * @param initialValue - initial blinking state of the animation
 * @returns animation of boolean value that is toggled periodically
 */
public func blinkAnimation(period: UInt32): TimeAnimation<Bool> {
    return periodicAnimation(period, {count: Int64 => (count % 2) != 0}, 0)
}

public func blinkAnimation(period: UInt32, initialValue: Bool): TimeAnimation<Bool> {
    return periodicAnimation(period, {count: Int64 => (count % 2) != 0}, if (initialValue) {
        1
    } else {
        0
    })
}

/**
 * @param period - number of milliseconds after which the animated state increments number value
 * @param initialCount - initial counter value of the animation
 * @returns animation of integer value that is incremented periodically
 */
public func countAnimation(period: UInt32): TimeAnimation<Int64> {
    return periodicAnimation(period, {count: Int64 => count}, 0)
}

public func countAnimation(period: UInt32, initialCount: Int64): TimeAnimation<Int64> {
    return periodicAnimation(period, {count: Int64 => count}, initialCount)
}

/**
 * @param period - number of milliseconds after which the animated state computes its value from period counter
 * @param compute - value supplier to be computed every `period` milliseconds
 * @param initialCount - initial counter value of the animation
 * @returns animation of integer value that is computed periodically from counter
 */
public func periodicAnimation<Value>(period: UInt32, compute: (count: Int64) -> Value): TimeAnimation<Value> {
    if (!Float32(period).isNormal() || (period < 1)) {
        throw IllegalArgumentException("illegal time period: ${period}")
    }
    return PeriodicAnimationImpl(0, period, compute, initial: 0)
}

public func periodicAnimation<Value>(period: UInt32, compute: (count: Int64) -> Value, initialCount: Int64): TimeAnimation<Value> {
    if (!Float32(period).isNormal() || (period < 1)) {
        throw IllegalArgumentException("illegal time period: ${period}")
    }
    if (!Float32(initialCount).isNormal()) {
        throw IllegalArgumentException("illegal initial count: ${initialCount}")
    }
    return PeriodicAnimationImpl(0, period, compute, initial: initialCount)
}

/**
 * @param delay - number of milliseconds after which the animated state computes its first value
 * @param period - number of milliseconds after which the animated state computes its value from period counter
 * @param compute - value supplier to be computed every `period` milliseconds
 * @param initialCount - initial counter value of the animation
 * @returns animation of integer value that is computed periodically from counter
 */
public func periodicAnimationWithDelay<Value>(
    delay: UInt32,
    period: UInt32,
    compute: (count: Int64) -> Value
): TimeAnimation<Value> {
    if (!Float32(period).isNormal() || (period < 1)) {
        throw IllegalArgumentException("illegal time period: ${period}")
    }
    if (!Float32(delay).isNormal() || (delay < 1)) {
        throw IllegalArgumentException("illegal time delay: ${delay}")
    }
    return PeriodicAnimationImpl<Value>(delay - period, period, compute, initial: 0)
}

public func periodicAnimationWithDelay<Value>(
    delay: UInt32,
    period: UInt32,
    compute: (count: Int64) -> Value,
    initialCount: Int64
): TimeAnimation<Value> {
    if (!Float32(period).isNormal() || (period < 1)) {
        throw IllegalArgumentException("illegal time period: ${period}")
    }
    if (!Float32(delay).isNormal() || (delay < 1)) {
        throw IllegalArgumentException("illegal time delay: ${initialCount}")
    }
    if (!Float32(initialCount).isNormal()) {
        throw IllegalArgumentException("illegal initial count: ${initialCount}")
    }
    return PeriodicAnimationImpl<Value>(delay - period, period, compute, initial: initialCount)
}

/**
 * @param frameTime - array of frame durations in milliseconds
 * @param compute - value supplier to be computed when frame index is changed
 * @returns frame-based animation
 */
public func frameAnimation<Value>(frameTime: Array<UInt32>, compute: (index: Int64) -> Value): TimeAnimation<Value> {
    var count = frameTime.size
    if (count == 1) {
        return constAnimation<Value>(compute(0))
    }
    if (count < 2) {
        throw IllegalArgumentException("illegal frames count: ${count}")
    }
    let time = ArrayList<UInt32>(count)
    for (index in 0..count - 1) {
        let value = frameTime[index]
        if (!Float32(value).isNormal() || (value < 1)) {
            throw IllegalArgumentException("illegal time of frame ${index}: ${value}")
        }
        time[index] = if (index > 0) {
            time[index - 1] + value
        } else {
            value
        }
    }
    return FrameAnimationImpl(time, compute)
}

/**
 * @param spec - the animation specification
 * @param from - a first base array that corresponds to the `0` state
 * @param to - a second base array that corresponds to the `1` state
 * @returns duration-based animation of number value
 */
public func numberAnimation(spec: PartialAnimationSpec): TimeAnimation<Float32> {
    return animation(spec, NumberAnimationRange(0.0, 1.0))
}

public func numberAnimation(spec: PartialAnimationSpec, to: Float32, isfrom: Float32): TimeAnimation<Float32> {
    return animation(spec, NumberAnimationRange(isfrom, to))
}

/**
 * @param spec - the animation specification
 * @param compute - value supplier to be computed when state animated from 0 to 1
 * @param initialState - initial inner state of the animation (-1..1]
 * @returns duration-based animation
 */
public func animation<Value>(spec: PartialAnimationSpec, compute: AnimationRange<Value>): TimeAnimation<Value> {
    var duration: UInt32 = if (let Some(duration) <- spec.duration) {
        duration
    } else {
        DEFAULT_ANIMATION_DURATION
    }
    if (!Float32(duration).isNormal() || (duration < 0)) {
        throw IllegalArgumentException("duration must not be negative, but is ${spec.duration}")
    }
    var delay: UInt32 = spec.delay ?? 0
    if (!Float32(delay).isNormal() || (delay < 0)) {
        throw IllegalArgumentException("delay must not be negative, but is ${spec.delay}")
    }
    var easing = spec.easing ?? Easing.Linear
    var onEdge = if (let Some(onEdge) <- spec.onEdge) {
        onEdge
    } else {
        OnEdge.DoNothing
    }
    var iterations = spec.iterations
    if (let Some(iterations) <- iterations) {
        if (iterations < 1) {
            throw IllegalArgumentException("iterations must be positive integer, but is ${spec.iterations}")
        }
        if (match (onEdge) {
            case OnEdge.Reverse => true
            case _ => false
        }) {
            easing = Easing.thereAndBackAgain(easing)
            duration *= 2
        }
        if (iterations > 1) {
            easing = Easing.repeated(easing, iterations)
            duration *= iterations
        }
        if (match (onEdge) {
            case OnEdge.Restart => true
            case _ => false
        }) {
            easing = Easing.restarted(easing)
        }
        onEdge = OnEdge.DoNothing
    }
    if (duration == 0 && match (onEdge) {
        case OnEdge.Restart => true
        case OnEdge.Reverse => true
        case OnEdge.DoNothing => false
    }) {
        throw IllegalArgumentException("cyclic animation must have a positive duration, but has ${spec.duration}")
    }
    return AnimationImpl(
        AnimationSpec(
            duration,
            delay,
            easing,
            onEdge,
            if (let Some(onPause) <- spec.onPause) {
                onPause
            } else {
                OnPause.DoNothing
            },
            iterations,
            spec.onStart,
            spec.onEnd,
            spec.onReset
        ),
        compute,
        0.0
    )
}

public func animation<Value>(spec: PartialAnimationSpec, compute: AnimationRange<Value>, initialState: Float32): TimeAnimation<Value> {
    if (!Float32(initialState).isNormal() || (initialState <= -1.0) || (initialState > 1.0)) {
        throw IllegalArgumentException("illegal initial state: ${initialState}")
    }
    var duration: UInt32 = if (let Some(duration) <- spec.duration) {
        duration
    } else {
        DEFAULT_ANIMATION_DURATION
    }
    if (!Float32(duration).isNormal() || (duration < 0)) {
        throw IllegalArgumentException("duration must not be negative, but is ${spec.duration}")
    }
    var delay: UInt32 = spec.delay ?? 0
    if (!Float32(delay).isNormal() || (delay < 0)) {
        throw IllegalArgumentException("delay must not be negative, but is ${spec.delay}")
    }
    var easing = spec.easing ?? Easing.Linear
    var onEdge = if (let Some(onEdge) <- spec.onEdge) {
        onEdge
    } else {
        OnEdge.DoNothing
    }
    var iterations = spec.iterations
    if (let Some(iterations) <- iterations) {
        if (iterations < 1) {
            throw IllegalArgumentException("iterations must be positive integer, but is ${spec.iterations}")
        }
        if (match (onEdge) {
            case OnEdge.Reverse => true
            case _ => false
        }) {
            easing = Easing.thereAndBackAgain(easing)
            duration *= 2
        }
        if (iterations > 1) {
            easing = Easing.repeated(easing, iterations)
            duration *= iterations
        }
        if (match (onEdge) {
            case OnEdge.Restart => true
            case _ => false
        }) {
            easing = Easing.restarted(easing)
        }
        onEdge = OnEdge.DoNothing
    }
    if (duration == 0 && match (onEdge) {
        case OnEdge.Restart => true
        case OnEdge.Reverse => true
        case OnEdge.DoNothing => false
    }) {
        throw IllegalArgumentException("cyclic animation must have a positive duration, but has ${spec.duration}")
    }
    return AnimationImpl(
        AnimationSpec(
            duration,
            delay,
            easing,
            onEdge,
            if (let Some(onPause) <- spec.onPause) {
                onPause
            } else {
                OnPause.DoNothing
            },
            iterations,
            spec.onStart,
            spec.onEnd,
            spec.onReset
        ),
        compute,
        initialState
    )
}

/**
 * @param duration - duration of state transition from 0 to 1
 * @param easing - a way in which a motion tween proceeds
 * @param compute - value supplier to be computed when state animated from 0 to 1
 * @param initialState - initial inner state of the animation (-1..1]
 * @returns duration-based value transition
 */
public func transition<Value>(
    duration: UInt32,
    easing: EasingCurve,
    compute: AnimationRange<Value>
): TimeAnimation<Value> {
    return animation<Value>(
        PartialAnimationSpec(
            duration,
            Option.None,
            easing,
            Option.None,
            OnPause.Fade,
            Option<UInt32>.None,
            Option<() -> Unit>.None,
            Option<() -> Unit>.None,
            Option<() -> Unit>.None
        ),
        compute,
        0.0
    )
}

public func transition<Value>(
    duration: UInt32,
    easing: EasingCurve,
    compute: AnimationRange<Value>,
    initialState: Int64
): TimeAnimation<Value> {
    return animation<Value>(
        PartialAnimationSpec(
            duration,
            Option.None,
            easing,
            Option.None,
            OnPause.Fade,
            Option<UInt32>.None,
            Option<() -> Unit>.None,
            Option<() -> Unit>.None,
            Option<() -> Unit>.None
        ),
        compute,
        Float32(initialState)
    )
}

/**
 * @param duration - duration of state transition from 0 to 1
 * @param compute - value supplier to be computed when state animated from 0 to 1
 * @param initialState - initial inner state of the animation (-1..1]
 * @returns duration-based value transition
 */
public func linearTransition<Value>(duration: UInt32, compute: AnimationRange<Value>): TimeAnimation<Value> {
    return transition(duration, Easing.Linear, compute, 0)
}

public func linearTransition<Value>(duration: UInt32, compute: AnimationRange<Value>, initialState: Int64): TimeAnimation<Value> {
    return transition(duration, Easing.Linear, compute, initialState)
}

// IMPLEMENTATION DETAILS: DO NOT USE IT DIRECTLY

public open class TimeAnimationImpl<Value> <: TimeAnimation<Value> {
    private var startTime: ?UInt64 = Option.None
    private var lastState: Int64
    private var lastValue: Value
    private let compute: (time: Int64) -> Value
    private var running: Bool = false

    init(compute: (time: Int64) -> Value) {
        this.lastState = 0
        this.lastValue = compute(0)
        this.compute = compute
    }

    init(compute: (time: Int64) -> Value, initial: Int64) {
        this.lastState = initial
        this.lastValue = compute(initial)
        this.compute = compute
    }

    public func isRunning(): Bool {
        return this.running
    }

    public func getLastState(): Int64 {
        return this.lastState
    }

    public open func getState(startTime: UInt64, currentTime: UInt64): Int64 {
        this.startTime = currentTime
        return this.lastState + Int64(currentTime - startTime)
    }

    public func getValue(time: UInt64): Value {
        if (this.startTime.isNone()) {
            return this.lastValue
        } // paused
        if (let Some(startTime) <- this.startTime) {
            if (startTime >= time) {
                return this.lastValue
            }
        } // delayed
        let state = if (let Some(startTime) <- this.startTime) {
            this.getState(startTime, time)
        } else {
            throw IllegalArgumentException("Function getState did not return a proper value.")
        }
        if (this.lastState == state) {
            return this.lastValue
        } // not changed
        this.lastState = state
        this.lastValue = this.compute(state)
        return this.lastValue
    }

    public open func onStart(time: UInt64): Unit {
        this.startTime = time
        this.running = true
    }

    public func onPause(time: UInt64): Unit {
        this.startTime = Option.None
        this.running = false
    }
}

class PeriodicAnimationImpl<Value> <: TimeAnimationImpl<Value> {
    private let period: UInt32
    private var delay: UInt32

    init(delay: UInt32, period: UInt32, compute: (count: Int64) -> Value, initial!: Int64 = 0) {
        super(compute, initial)
        this.period = period
        this.delay = delay
    }

    public func getState(startTime: UInt64, currentTime: UInt64): Int64 {
        var result = this.getLastState()
        var passedTime = currentTime - startTime
        if (passedTime > UInt64(this.period)) {
            result += Int64(floor(Float64(passedTime) / Float64(this.period)))
            passedTime = passedTime % UInt64(this.period)
            // tune start time for long animations
            super.onStart(currentTime - passedTime)
        }
        return result
    }

    public func onStart(time: UInt64) {
        super.onStart(time + UInt64(this.delay))
    }
}

class ConstAnimationImpl<Value> <: TimeAnimation<Value> {
    private var lastValue: Value
    let running: Bool = false

    init(value: Value) {
        this.lastValue = value
    }

    public func isRunning(): Bool {
        return this.running
    }

    public func getValue(time: UInt64): Value {
        return this.lastValue
    }

    public func onStart(time: UInt64): Unit {
    }

    public func onPause(time: UInt64): Unit {
    }
}

class FrameAnimationImpl<Value> <: TimeAnimationImpl<Value> {
    private var time: ArrayList<UInt32>

    init(time: ArrayList<UInt32>, compute: (time: Int64) -> Value) {
        super(compute)
        this.time = time
    }

    public func getState(startTime: UInt64, currentTime: UInt64): Int64 {
        let cycleTime = this.time[this.time.size - 1]

        var passedTime = currentTime - startTime
        if (passedTime > UInt64(cycleTime)) {
            passedTime = passedTime % UInt64(cycleTime)
            // tune start time for long animations
            super.onStart(currentTime - passedTime)
        }
        for (index in 0..this.time.size - 1) {
            if (passedTime < UInt64(this.time[index])) {
                return index
            }
        }
        return 0
    }
}

class AnimationImpl<Value> <: TimeAnimation<Value> {
    private var startTime: ?UInt64 = Option.None
    private var lastState: Float32
    private var lastValue: Value
    private let compute: AnimationRange<Value>
    private var isPauseRequested = false
    private var spec: AnimationSpec
    private var running: Bool = false

    init(spec: AnimationSpec, compute: AnimationRange<Value>) {
        this.lastState = 0.0
        this.lastValue = compute(0.0)
        this.compute = {state: Float32 => compute(Float32(spec.easing(abs(Float64(state)))))}
        this.spec = spec
    }

    init(spec: AnimationSpec, compute: AnimationRange<Value>, initial: Float32) {
        this.lastState = initial
        this.lastValue = compute(initial)
        this.compute = {state: Float32 => compute(Float32(spec.easing(abs(Float64(state)))))}
        this.spec = spec
    }

    public func isRunning(): Bool {
        return this.running
    }

    public func getState(startTime: UInt64, currentTime: UInt64): Float32 {
        let onPause = if (let v <- this.isPauseRequested) {
            this.spec.onPause
        } else {
            OnPause.DoNothing
        }
        match (onPause) {
            case OnPause.Reset => return this.onPauseReset()
            case _ => ()
        } // pause

        let cycleTime: UInt64 = match (onPause) {
            case OnPause.Fade => UInt64(this.spec.duration) * 2
            case _ => match (this.spec.onEdge) {
                case OnEdge.Reverse => UInt64(this.spec.duration) * 2
                case _ => UInt64(this.spec.duration)
            }
        }

        var passedTime = currentTime - startTime
        if (passedTime > cycleTime) {
            match (onPause) {
                case OnPause.Fade => return this.onPauseReset()
                case _ => ()
            } // fade stopped
            match (this.spec.onEdge) {
                case OnEdge.DoNothing => return this.onEdgeReached()
                case _ => ()
            } // tune start time for long animations
            this.running = true
            this.startTime = currentTime - passedTime
        }
        var state = passedTime / UInt64(this.spec.duration)
        if (state > 1) {
            return Float32(state - 2)
        } else {
            return Float32(state)
        }
    }

    public func getValue(time: UInt64): Value {
        if (this.startTime == Option.None) {
            return this.lastValue
        } // paused
        if (let Some(startTime) <- this.startTime) {
            if (startTime >= time) {
                return this.lastValue
            }
        } // delayed
        let state = if (let Some(startTime) <- this.startTime) {
            this.getState(startTime, time)
        } else {
            throw IllegalArgumentException("Function getState did not return a proper value.")
        }
        if (this.lastState == state) {
            return this.lastValue
        } // not changed
        this.lastState = state
        this.lastValue = this.compute(state)
        return this.lastValue
    }

    public func onStart(time: UInt64): Unit {
        if (let Some(onStart) <- this.spec.onStart) {
            scheduleCallback(onStart)
        }
        if (this.isPauseRequested) {
            this.isPauseRequested = false
            if (this.lastState < 0.0) {
                // tune start time on direction change
                this.running = true
                this.startTime = time + UInt64(this.lastState * Float32(this.spec.duration))
            }
        } else {
            // set start time to continue animation from the current state
            this.running = true
            this.startTime = time - UInt64(if (this.lastState < 0.0) {
                    (2 + UInt32(this.lastState)) * this.spec.duration
                } else {
                    if (this.lastState > 0.0) {
                        UInt32(this.lastState) * this.spec.duration
                    } else {
                        (0 - this.spec.delay)
                    }
                }) // add delay for the state 0 only
        }
    }

    public func onPause(time: UInt64): Unit {
        if (this.lastState != 0.0 && match (this.spec.onPause) {
            case OnPause.Reset => true
            case _ => false
        }) {
            this.isPauseRequested = true
        } else if (this.lastState != 0.0 && match (this.spec.onPause) {
            case OnPause.Fade => true
            case _ => false
        }) {
            this.isPauseRequested = true
            if (this.lastState > 0.0) {
                // tune start time on direction change
                this.running = true
                this.startTime = time - UInt64(this.spec.duration * UInt32(2.0 - this.lastState))
            }
        } else {
            this.running = false
            this.startTime = Option.None
        }
    }

    private func onPauseReset(): Float32 {
        this.running = false
        this.startTime = Option.None
        this.isPauseRequested = false
        if (let Some(onReset) <- this.spec.onReset) {
            scheduleCallback(onReset)
        }
        return 0.0
    }

    private func onEdgeReached(): Float32 {
        if (this.running) {
            this.running = false
            if (let Some(onEnd) <- this.spec.onEnd) {
                scheduleCallback(onEnd)
            }
        }
        return 1.0
    }
}
