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
package KoalaRuntime.core

/**
 * It computes the value of the given lambda and caches its result.
 * In contrast to the `memo` function, the given lambda is computed only once
 * even if it uses values of states (including parameters of @memo-functions).
 *
 * @param compute - a function to compute cacheable result
 * @returns the last computed value
 * @see memo0
 * @memo:intrinsic
 */
public func remember<Value>(compute: () -> Value): Value {
    getMemoScope<Value>(getCallsiteKey(), 0, None, compute, None, true).getValue() // do not recompute if used states were updated
}

/**
 * It computes the value of the given lambda, caches its result,
 * and notifies, that this method is removed from the composition.
 *
 * @param compute - a function to compute cacheable result
 * @param cleanup - a function to cleanup computed result on dispose
 * @returns the last computed value
 * @see remember
 * @memo:intrinsic
 */
public func rememberDisposable<Value>(compute: () -> Value, cleanup: (value: ?Value) -> Unit): Value {
    getMemoScope<Value>(getCallsiteKey(), 0, None, compute, cleanup, true).getValue() // do not recompute if used states were updated
}

/**
 * Creates remembered state which can be updated from anywhere,
 * and if changed - all depending memo functions recache automatically.
 * This method can be used for for primitive values,
 * which do not require computations or memory allocation.
 *
 * @param initial - initial value used on the state creation
 * @returns a state remembered for the current code position
 * @memo:intrinsic
 */
public func rememberMutableState<Value>(initial: Value): MutableState<Value> {
    let scope = getMemoScope<MutableState<Value>>(getCallsiteKey(), 0, None, None, None, true) // do not recompute if used states were updated
    if (scope.isUnchanged()) {
        scope.getCached()
    } else {
        scope.recache(mutableState(initial))
    }
}

/**
 * Creates remembered state which can be updated from anywhere,
 * and if changed - all depending memo functions recache automatically.
 * This method should be used for for non-primitive values,
 * which require computations or memory allocation.
 *
 * @param initial - initial value supplier used on the state creation
 * @returns a state remembered for the current code position
 * @memo:intrinsic
 */
public func rememberMutableState<Value>(initial: () -> Value): MutableState<Value> {
    let scope = getMemoScope<MutableState<Value>>(getCallsiteKey(), 0, None, None, None, true) // do not recompute if used states were updated
    if (scope.isUnchanged()) {
        scope.getCached()
    } else {
        scope.recache(mutableState(initial()))
    }
}
