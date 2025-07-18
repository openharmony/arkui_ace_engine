/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

import { float64, int64, uint32 } from "@koalaui/common"
import { RunEffect } from "../memo/changeListener"
import { remember } from "../memo/remember"
import { AnimatedState, ImplicitAnimationProvider, MutableAnimatedState, ParametrizedAnimationProvider, StateAnimator, animatedState, mutableAnimatedState, stateAnimator } from "./AnimatedState"
import { AnimationRange, NumberAnimationRange } from "./AnimationRange"
import { Easing, EasingCurve } from "./Easing"
import { AnimationSpec, TimeAnimation, animation, constAnimation, periodicAnimation, transition } from "./TimeAnimation"

/**
 * Function allowing to sample particular function with given rate.
 *
 * @param sampleRate number of milliseconds between samples
 * @param generator dirty function that produces values we interested in
 *
 * @returns value of generator function taken once in sampleRate ms
 */
/** @memo */
export function sampledValue<V>(sampleRate: uint32, generator: (tick: int64) => V): V {
    return rememberAnimatedState<V>((): TimeAnimation<V> => periodicAnimation<V>(sampleRate, generator), true).value
}


/**
 * Creates and remembers animated state that could later be used as data source for animations.
 *
 * @param animation - supplier of the animation definition
 * @param startNow - if animation shall start immediately after creation
 * @returns animated state with the specified animation
 */
/** @memo */
export function rememberAnimatedState<V>(animation: () => TimeAnimation<V>, startNow: boolean = false): AnimatedState<V> {
    return remember((): AnimatedState<V> => animatedState<V>(animation(), startNow))
}

/**
 * Creates and remembers number transition that could later be used as data source for animations.
 *
 * @param on - specifies the direction of the animation (false to 0, true to 1)
 * @param duration - duration of state transition from 0 to 1
 * @param easing - a way in which a motion tween proceeds
 * @param to - a target value that corresponds to the 1 state
 * @param from - a initial value that corresponds to the 0 state
 * @returns animated state with the specified transition
 */
/** @memo */
export function rememberNumberTransition(on: boolean, duration: uint32, easing: EasingCurve = Easing.Linear, to: float64 = 1.0, from: float64 = 0.0): AnimatedState<float64> {
    return rememberTransition<float64>(on, duration, easing, NumberAnimationRange(from, to))
}

/**
 * Creates and remembers value transition that could later be used as data source for animations.
 * If it is needed to start the transition on appearing,
 * the `on` and `initial` parameters must have different values.
 *
 * @param on - specifies the direction of the animation (false to 0, true to 1)
 * @param duration - duration of state transition from 0 to 1
 * @param easing - a way in which a motion tween proceeds
 * @param compute - value supplier to be computed when state animated from 0 to 1
 * @param initial - initial state of the transition (false to 0, true to 1)
 * @returns animated state with the specified transition
 */
/** @memo */
export function rememberTransition<Value>(on: boolean, duration: uint32, easing: EasingCurve, compute: AnimationRange<Value>, initial: boolean = on): AnimatedState<Value> {
    const state = rememberAnimatedState<Value>((): TimeAnimation<Value> => transition<Value>(duration, easing, compute, initial ? 1 : 0), on)
    RunEffect(!on, (paused: boolean): void => { state.setPaused(paused) })
    return state
}


/**
 * Creates and remembers a mutable state that automatically animates the value as it changes.
 *
 * @param initial - initial value
 * @param animationProvider - factory producing a new animation from the current value and the target one
 * @returns a mutable state that automatically animates the value as it changes
 */
/** @memo */
export function rememberMutableAnimatedState<Value>(initial: Value, animationProvider: ImplicitAnimationProvider<Value>): MutableAnimatedState<Value> {
    return remember((): MutableAnimatedState<Value>  => mutableAnimatedState<Value>(initial, animationProvider))
}

/**
 * Creates and remembers a mutable state that automatically animates the number value as it changes.
 *
 * @param initial - initial value
 * @param animationSpec - the animation specification that does not depend on changed values
 * @returns a mutable state that automatically animates the number value as it changes
 * @see rememberMutableAnimatedState
 */
/** @memo */
export function rememberMutableAnimatedStateNumber(initial: float64, animationSpec: Partial<AnimationSpec>): MutableAnimatedState<float64> {
    return remember((): MutableAnimatedState<float64> => mutableAnimatedState(initial, (from: float64, to: float64) => from == to
        ? constAnimation(to)
        : animation(animationSpec, NumberAnimationRange(from, to))))
}


/**
 * Creates and remembers state animator with controllable parameter.
 * When parameter is changed, the animation is recreated.
 *
 * @param parameter - initial value for controlling parameter
 * @param animationProvider - factory producing a new animation when parameter changed
 * @returns state animator with the animation created for given parameter
 */
/** @memo */
export function rememberAnimator<P, V>(parameter: P, animationProvider: ParametrizedAnimationProvider<P, V>): StateAnimator<P, V> {
    return remember((): StateAnimator<P, V> => stateAnimator<P, V>(parameter, animationProvider))
}
