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

import { int64, refEqual } from "@koalaui/common"
import { getAnimationTimer } from "./GlobalTimer"
import { TimeAnimation, constAnimation } from "./TimeAnimation"
import { Disposable } from "../states/Disposable"
import { GlobalStateManager } from "../states/GlobalStateManager"
import { ComputableState, MutableState, State, StateContext } from "../states/State"


/**
 * This interface represents a pauseable animated state,
 * which value is changed according to the given animation.
 */
export interface AnimatedState<Value> extends State<Value> {
    getAnimation(): TimeAnimation<Value>
    setAnimation(value: TimeAnimation<Value>): void
    readonly running: boolean
    getPaused(): boolean
    setPaused(value: boolean): void

}

/**
 * Creates animated state that could later be used as data source for animations.
 *
 * @param animation - animation definition
 * @param startNow - if animation shall start immediately after creation
 * @param timeProvider - custom time provider for testing purposes
 * @returns animated state with the specified animation
 */
export function animatedState<V>(animation: TimeAnimation<V>, startNow: boolean = false, timeProvider?: () => int64): AnimatedState<V> {
    return new AnimatedStateImpl<V>(animation, startNow, timeProvider)
}


/**
 * This interface represents a mutable animated state,
 * which value is changed according to the given animation.
 * If its value is changed by user, a new animation is requested
 * to change the current value to the target one.
 */
export interface MutableAnimatedState<Value> extends MutableState<Value> {
    getAnimation(): TimeAnimation<Value>
    setAnimation(value: TimeAnimation<Value>): void
    readonly running: boolean
}

/**
 * Creates and remembers a mutable state that automatically animates the value as it changes.
 *
 * @param initial - initial value
 * @param animationProvider - factory producing a new animation from the current value and the target one
 * @returns a mutable state that automatically animates the value as it changes
 */
export function mutableAnimatedState<Value>(initial: Value, animationProvider: ImplicitAnimationProvider<Value>): MutableAnimatedState<Value> {
    return new MutableAnimatedStateImpl<Value>(initial, animationProvider)
}

/**
 * A factory producing a new animation from the current value and the target one.
 * @param from - start value for animation
 * @param to - end value for animation
 * @returns a new animation from the current value and the target one
 */
export type ImplicitAnimationProvider<Value> = (from: Value, to: Value) => TimeAnimation<Value>


/**
 * This interface represents a value provider with ability to choose value animation by parameter.
 */
export interface StateAnimator<Parameter, Value> {
    parameter: Parameter
    readonly value: Value
    onValueChange(action: (newValue: Value) => void): void
}

/**
 * Creates state animator with controllable parameter.
 * When parameter is changed, the animation is recreated.
 *
 * @param parameter - initial value for controlling parameter
 * @param animationProvider - factory producing a new animation when parameter changed
 * @returns state animator with the animation created for given parameter
 */
export function stateAnimator<P, V>(parameter: P, animationProvider: ParametrizedAnimationProvider<P, V>): StateAnimator<P, V> {
    return new StateAnimatorImpl<P, V>(parameter, animationProvider)
}

/**
 * A factory producing a new animation when parameter changed.
 * @param parameter - controlling parameter
 * @param value - previous value of the animator if exists
 * @returns a new animation when parameter changed
 */
export type ParametrizedAnimationProvider<P, V> = (parameter: P, value: V | undefined) => TimeAnimation<V>


// IMPLEMENTATION DETAILS: DO NOT USE IT DIRECTLY


class AnimatedStateImpl<Value> implements Disposable, AnimatedState<Value> {
    private readonly timeProvider: () => int64
    private runningState: MutableState<boolean>
    private pausedState: MutableState<boolean>
    private valueState: ComputableState<Value>
    private myAnimation: TimeAnimation<Value>

    dispose() {
        this.runningState.dispose()
        this.pausedState.dispose()
        this.valueState.dispose()
    }

    get disposed(): boolean {
        return this.valueState.disposed
    }

    get modified(): boolean {
        return this.valueState.modified
    }

    get value(): Value {
        return this.valueState.value
    }

    get running(): boolean {
        return this.runningState.value
    }

    getPaused(): boolean {
        return this.pausedState.value
    }

    setPaused(paused: boolean) {
        this.pausedState.value = paused
    }

    getAnimation(): TimeAnimation<Value> {
        return this.myAnimation
    }

    setAnimation(animation: TimeAnimation<Value>): void {
        if (this.myAnimation === animation) return // nothing to change
        this.myAnimation = animation
        if (!this.getPaused()) animation.onStart(this.timeProvider())
    }

    constructor(myAnimation: TimeAnimation<Value>, startNow: boolean, timeProvider: (() => int64)|undefined) {
        const manager = GlobalStateManager.instance
        if (timeProvider) {
            this.timeProvider = timeProvider
        } else {
            this.timeProvider = (): int64 => {
                const timer = getAnimationTimer(manager)
                if (timer) return timer.value
                console.log("global animation timer is not specified yet")
                return 0
            }
        }
        this.myAnimation = myAnimation
        this.runningState = manager.mutableState<boolean>(startNow)
        this.pausedState = manager.mutableState<boolean>(!startNow)
        this.valueState = manager.computableState<Value>((_context: StateContext): Value => {
            try {
                const time = this.timeProvider()
                const paused = this.pausedState.value
                if (this.pausedState.modified) {
                    if (paused) {
                        this.getAnimation().onPause(time)
                    } else {
                        this.getAnimation().onStart(time)
                    }
                }
                // compute value from the time provided
                let newValue = this.getAnimation().getValue(time)
                this.action?.(newValue)
                return newValue
            } finally {
                // update running state if needed
                this.runningState.value = this.getAnimation().running
            }
        })
        if (startNow) {
            this.getAnimation().onStart(this.timeProvider())
        }
    }

    onValueChange(action: (newValue: Value) => void): void {
        this.action = action
    }

    action: ((newValue: Value) => void) | undefined = undefined
}


class MutableAnimatedStateImpl<Value> implements MutableAnimatedState<Value> {
    private animatedState: AnimatedStateImpl<Value>
    private readonly animationProvider: ImplicitAnimationProvider<Value>

    dispose(): void {
        this.animatedState.dispose()
    }

    constructor(initial: Value, animationProvider: ImplicitAnimationProvider<Value>) {
        this.animatedState = new AnimatedStateImpl<Value>(constAnimation(initial), true, undefined)
        this.animationProvider = animationProvider
    }

    get disposed(): boolean {
        return this.animatedState.disposed
    }

    get modified(): boolean {
        return this.animatedState.modified
    }

    get value(): Value {
        return this.animatedState.value
    }

    set value(value: Value) {
        this.animatedState.setAnimation(this.animationProvider(this.animatedState.value, value))
    }

    get running(): boolean {
        return this.animatedState.running
    }

    getAnimation(): TimeAnimation<Value> {
        return this.animatedState.getAnimation()
    }

    setAnimation(animation: TimeAnimation<Value>): void {
        this.animatedState.setAnimation(animation)
    }
}


class StateAnimatorImpl<P, V> implements StateAnimator<P, V> {
    private parameterState: MutableState<P>
    private animatedState: AnimatedStateImpl<V>
    private readonly animationProvider: ParametrizedAnimationProvider<P, V>

    constructor(parameter: P, animationProvider: ParametrizedAnimationProvider<P, V>) {
        this.parameterState = GlobalStateManager.instance.mutableState<P>(parameter)
        this.animatedState = new AnimatedStateImpl<V>(animationProvider(parameter, undefined), true, undefined)
        this.animationProvider = animationProvider
    }

    get parameter(): P {
        return this.parameterState.value
    }

    set parameter(parameter: P) {
        if (refEqual(this.parameterState.value, parameter)) return // nothing to change
        this.parameterState.value = parameter
        this.animatedState.setAnimation(this.animationProvider(parameter, this.animatedState.value))
    }

    get value(): V {
        return this.animatedState.value
    }

    onValueChange(action: (newValue: V) => void): void {
        // Improve: rethink how we'd better subscribe appropriate scope on value change.
        this.value
        this.animatedState.onValueChange(action)
    }
}
