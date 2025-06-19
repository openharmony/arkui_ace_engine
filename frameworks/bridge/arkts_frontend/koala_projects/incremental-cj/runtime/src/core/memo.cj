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
 * It computes the value of the given lambda and caches the result.
 * In contrast to the `remember` function, the given lambda can be recomputed
 * if it uses values of states (including parameters of @memo-functions).
 * If the given lambda does not use any state, it will be computed only once.
 *
 * @param compute - a function to compute cacheable result
 * @returns the last computed value
 * @memo:intrinsic
 * @see remember
 */
public func memo<Value>(compute: () -> Value): Value {
    memo(getCallsiteKey(), compute)
}

/**
 * It computes the value of the given lambda and caches the result with the given callsite key.
 * In contrast to the `remember` function, the given lambda can be recomputed
 * if it uses values of states (including parameters of @memo-functions).
 * If the given lambda does not use any state, it will be computed only once.
 *
 * @param key - a callsite key, which identifies a place where the outer function is called
 * @param compute - a function to compute cacheable result
 * @returns the last computed value
 * @memo:intrinsic
 * @see remember
 */
public func memo<Value>(key: CallsiteKey, compute: () -> Value): Value {
    getMemoScope<Value>(key, 0, None, compute, None, false).getValue()
}

func memo1<P1, Value>(key: CallsiteKey, p1: P1, compute: (s1: State<P1>) -> Value): Value {
    let scope = getMemoScope<Value>(key, 1, None, None, None, false)
    let s1 = scope.param(0, p1)
    if (scope.isUnchanged()) {
        scope.getCached()
    } else {
        scope.recache(compute(s1))
    }
}

func memo2<P1, P2, Value>(key: CallsiteKey, p1: P1, p2: P2, compute: (s1: State<P1>, s2: State<P2>) -> Value): Value {
    let scope = getMemoScope<Value>(key, 2, None, None, None, false)
    let s1 = scope.param(0, p1)
    let s2 = scope.param(1, p2)
    if (scope.isUnchanged()) {
        scope.getCached()
    } else {
        scope.recache(compute(s1, s2))
    }
}

func memo3<P1, P2, P3, Value>(key: CallsiteKey, p1: P1, p2: P2, p3: P3,
    compute: (s1: State<P1>, s2: State<P2>, s3: State<P3>) -> Value): Value {
    let scope = getMemoScope<Value>(key, 3, None, None, None, false)
    let s1 = scope.param(0, p1)
    let s2 = scope.param(1, p2)
    let s3 = scope.param(2, p3)
    if (scope.isUnchanged()) {
        scope.getCached()
    } else {
        scope.recache(compute(s1, s2, s3))
    }
}

func memo4<P1, P2, P3, P4, Value>(key: CallsiteKey, p1: P1, p2: P2, p3: P3, p4: P4,
    compute: (s1: State<P1>, s2: State<P2>, s3: State<P3>, s4: State<P4>) -> Value): Value {
    let scope = getMemoScope<Value>(key, 4, None, None, None, false)
    let s1 = scope.param(0, p1)
    let s2 = scope.param(1, p2)
    let s3 = scope.param(2, p3)
    let s4 = scope.param(3, p4)
    if (scope.isUnchanged()) {
        scope.getCached()
    } else {
        scope.recache(compute(s1, s2, s3, s4))
    }
}
