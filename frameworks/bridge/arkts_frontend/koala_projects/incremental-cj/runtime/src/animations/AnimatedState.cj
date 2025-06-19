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
import KoalaRuntime.util.*

/**
 * This interface represents a pauseable animated state,
 * which value is changed according to the given animation.
 */
public interface AnimatedState<Value> <: State<Value> {
    func getAnimation(): TimeAnimation<Value>
    func setAnimation(animation: TimeAnimation<Value>): Unit
    func isRunning(): Bool
    func isPaused(): Bool
}

/**
 * Creates animated state that could later berbnf used as data source for animations.
 *
 * @param animation - animation definition
 * @param startNow - if animation shall start immediately after creation
 * @param timeProvider - custom time provider for testing purposes
 * @returns animated state with the specified animation
 */
public func animatedState<V>(animation: TimeAnimation<V>, timeProvider: (() -> UInt64)): AnimatedState<V> {
    return AnimatedStateImpl(animation, false, timeProvider).initValueState()
}
/**
 * Creates animated state that could later berbnf used as data source for animations.
 *
 * @param animation - animation definition
 * @param startNow - if animation shall start immediately after creation
 * @param timeProvider - custom time provider for testing purposes
 * @returns animated state with the specified animation
 */
public func animatedState<V>(animation: TimeAnimation<V>, startNow: Bool, timeProvider: (() -> UInt64)): AnimatedState<V> {
    return AnimatedStateImpl(animation, startNow, timeProvider).initValueState()
}

/**
 * This interface represents a mutable animated state,
 * which value is changed according to the given animation.
 * If its value is changed by user, a animation is requested
 * to change the current value to the target one.
 */
public interface MutableAnimatedState<Value> <: MutableState<Value> {
    func getAnimation(): TimeAnimation<Value>
    func setAnimation(animation: TimeAnimation<Value>): Unit
    func isRunning(): Bool
}

/**
 * Creates and remembers a mutable state that automatically animates the value as it changes.
 *
 * @param initial - initial value
 * @param animationProvider - factory producing a animation from the current value and the target one
 * @returns a mutable state that automatically animates the value as it changes
 */
public func mutableAnimatedState<Value>(initial: Value, animationProvider: ImplicitAnimationProvider<Value>): MutableAnimatedState<Value> {
    return MutableAnimatedStateImpl(initial, animationProvider)
}

/**
 * A factory producing a animation from the current value and the target one.
 * @param from - start value for animation
 * @param to - end value for animation
 * @returns a animation from the current value and the target one
 */
public type ImplicitAnimationProvider<Value> = (isfrom: Value, to: Value) -> TimeAnimation<Value>

/**
 * This interface represents a value provider with ability to choose value animation by parameter.
 */
public interface StateAnimator<Parameter, Value> {
    func getParameter(): Parameter
    func getValue(): Value
    func onValueChange(action: (newValue: Value) -> Unit): Unit
}

/**
 * Creates state animator with controllable parameter.
 * When parameter is changed, the animation is recreated.
 *
 * @param parameter - initial value for controlling parameter
 * @param animationProvider - factory producing a animation when parameter changed
 * @returns state animator with the animation created for given parameter
 */
public func stateAnimator<P, V>(parameter: P, animationProvider: ParametrizedAnimationProvider<P, V>): StateAnimator<P, V> {
    return StateAnimatorImpl(parameter, animationProvider)
}

/**
 * A factory producing a animation when parameter changed.
 * @param parameter - controlling parameter
 * @param value - previous value of the animator if exists
 * @returns a animation when parameter changed
 */
public type ParametrizedAnimationProvider<P, V> = (parameter: P, value: ?V) -> TimeAnimation<V>

// IMPLEMENTATION DETAILS: DO NOT USE IT DIRECTLY

class AnimatedStateImpl<Value> <: Disposable & AnimatedState<Value> {
    private var timeProvider: () -> UInt64
    private var runningState: MutableState<Bool>
    private var pausedState: MutableState<Bool>
    private var valueState: ?ComputableState<Value> = Option<ComputableState<Value>>.None
    private var myAnimation: TimeAnimation<Value>

    var action: ?((newValue: Value) -> Unit) = {newValue: Value =>}

    public func dispose() {
        this.runningState.dispose()
        this.pausedState.dispose()
        if (let Some(valueState) <- this.valueState) {
            valueState.dispose()
        }
    }

    public func isDisposed(): Bool {
        if (let Some(vs) <- this.valueState) {
            vs.isDisposed()
        } else {
            false
        }
    }

    public func isModified(): Bool {
        if (let Some(vs) <- this.valueState) {
            vs.isModified()
        } else {
            false
        }
    }

    public func getValue(): Value {
        if (let Some(vs) <- this.valueState) {
            vs.getValue()
        } else {
            throw IllegalArgumentException("Animated state has no value")
        }
    }

    public func isRunning(): Bool {
        this.runningState.getValue()
    }

    public func isPaused(): Bool {
        this.pausedState.getValue()
    }

    public func setPaused(v: Bool): Unit {
        this.pausedState.setValue(v)
    }

    public func getAnimation(): TimeAnimation<Value> {
        this.myAnimation
    }

    public func setAnimation(animation: TimeAnimation<Value>) {
        if (equalValues(this.myAnimation, animation)) {
            return
        } // nothing to change
        this.myAnimation = animation
        if (!this.isPaused()) {
            animation.onStart(this.timeProvider())
        }
    }

    init(myAnimation: TimeAnimation<Value>, startNow: Bool, timeProvider: () -> UInt64) {
        this.timeProvider = timeProvider
        this.myAnimation = myAnimation
        this.runningState = mutableState(startNow)
        this.pausedState = mutableState(!startNow)
    }

    init(myAnimation: TimeAnimation<Value>, startNow: Bool) {
        this.timeProvider = {
            =>
            let timer = getAnimationTimer()
            if (let timer <- Some(timer)) {
                timer
            }
            return 0
        }
        this.myAnimation = myAnimation
        this.runningState = mutableState(startNow)
        this.pausedState = mutableState(!startNow)
    }

    public func initValueState(): AnimatedStateImpl<Value> {
        this.valueState = GlobalStateManager.computableState(
            {
            => (try {
                let time = this.timeProvider()
                let paused = this.pausedState.getValue()
                if (this.pausedState.isModified()) {
                    if (paused) {
                        this.getAnimation().onPause(time)
                    } else {
                        this.getAnimation().onStart(time)
                    }
                }
                // compute value from the time provided
                var newValue = this.getAnimation().getValue(time)
                this.action?(newValue)
                return newValue
            } finally {
                // update running state if needed
                this.runningState.setValue(this.getAnimation().isRunning())
            })
        })
        return this
    }

    func onValueChange(action: (newValue: Value) -> Unit): Unit {
        this.action = action
    }
}

class MutableAnimatedStateImpl<Value> <: MutableAnimatedState<Value> {
    private var animatedState: AnimatedStateImpl<Value>
    private let animationProvider: ImplicitAnimationProvider<Value>

    public func dispose(): Unit {
        this.animatedState.dispose()
    }

    init(initial: Value, animationProvider: ImplicitAnimationProvider<Value>) {
        this.animatedState = AnimatedStateImpl(constAnimation(initial), true)
        this.animationProvider = animationProvider
    }

    public func isDisposed() {
        this.animatedState.isDisposed()
    }

    public func isModified() {
        return this.animatedState.isModified()
    }

    public func getValue() {
        this.animatedState.getValue()
    }

    public func setValue(value: Value) {
        this.animatedState.setAnimation(this.animationProvider(this.getValue(), value))
    }

    public func isRunning(): Bool {
        this.animatedState.isRunning()
    }

    public func getAnimation() {
        this.animatedState.getAnimation()
    }

    public func setAnimation(animation: TimeAnimation<Value>) {
        this.animatedState.setAnimation(animation)
    }
}

class StateAnimatorImpl<P, V> <: StateAnimator<P, V> {
    private var parameterState: MutableState<P>
    private var animatedState: AnimatedStateImpl<V>
    private let animationProvider: ParametrizedAnimationProvider<P, V>

    init(parameter: P, animationProvider: ParametrizedAnimationProvider<P, V>) {
        this.parameterState = mutableState(parameter)
        this.animatedState = AnimatedStateImpl(animationProvider(parameter, Option<V>.None), true)
        this.animationProvider = animationProvider
    }

    public func getParameter(): P {
        this.parameterState.getValue()
    }

    public func setParameter(parameter: P) {
        if (equalValues<P>(this.parameterState.getValue(), parameter)) {
            return
        } // nothing to change
        this.parameterState.setValue(parameter)
        this.animatedState.setAnimation(this.animationProvider(parameter, this.animatedState.getValue()))
    }

    public func getValue(): V {
        this.animatedState.getValue()
    }

    public func onValueChange(action: (newValue: V) -> Unit): Unit {
        // TODO: rethink how we'd better subscribe appropriate scope on value change.
        this.getValue()
        this.animatedState.onValueChange(action)
    }
}
