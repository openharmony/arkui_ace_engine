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
 * Sequentially repeats the {@link action}.
 *
 * An {@link action} unit accepts a sequential index as an argument.
 *
 * @param count the number of {@link action}'s to repeat, 0 by default
 * @param action an action to repeat
 *
 * @see RepeatWithKey
 * @see RepeatByArray
 * @memo:intrinsic
 */
public func Repeat(count: Int64, action: (index: Int64) -> Unit): Unit {
    memo2(getCallsiteKey(), count, action) {
        count: State<Int64>, action: State<(index: Int64) -> Unit> =>
        let max = count.getValue()
        var min = 0
        while (min < max) {
            memo1(UInt64(min), min) {
                index: State<Int64> => action.getValue()(index.getValue())
            }
            min++
        }
    }
}

/**
 * Sequentially repeats the {@link action} using the {@link key} callback.
 *
 * By default, each {@link action} has an implicit key which provides the {@link action}'s
 * result uniqueness. The {@link key} callback can be used to provide a custom key per
 * {@link action}, based on the {@link action}'s index accepted as an argument.
 *
 * @param count the number of {@link action}'s to repeat, 0 by default
 * @param key a callback to provide custom keys
 * @param action an action to repeat
 *
 * @see Repeat
 * @memo:intrinsic
 */
public func RepeatWithKey(
    count: Int64,
    key: (index: Int64) -> CallsiteKey,
    action: (index: Int64) -> Unit
): Unit {
    memo3(getCallsiteKey(), count, key, action) {
        count: State<Int64>, key: State<(index: Int64) -> CallsiteKey>, action: State<(index: Int64) -> Unit> =>
        let max = count.getValue()
        var min = 0
        while (min < max) {
            memo1(key.getValue()(min), min) {
                index: State<Int64> => action.getValue()(index.getValue())
            }
            min++
        }
    }
}

/**
 * Sequentially repeats the {@link action} by iterating the {@link array},
 * passing an element of the {@link array} as the {@link action}'s argument.
 *
 * @param array the array to iterate
 * @param key a callback to provide custom keys
 * @param action an action to repeat
 *
 * @see RepeatWithKey
 * @memo:intrinsic
 */
public func RepeatByArray<T>(
    array: Array<T>,
    key: (element: T, index: Int64) -> CallsiteKey,
    action: (element: T, index: Int64) -> Unit
): Unit {
    memo3(getCallsiteKey(), array, key, action) {
        state: State<Array<T>>, key: State<(element: T, index: Int64) -> CallsiteKey>, action: State<(element: T,
        index: Int64) -> Unit> =>
        let array = state.getValue()
        let max = array.size
        var min = 0
        while (min < max) {
            let element = array[min]
            memo2(key.getValue()(element, min), element, min) {
                e: State<T>, i: State<Int64> => action.getValue()(e.getValue(), i.getValue())
            }
            min++
        }
    }
}

/**
 * Sequentially repeats the {@link action} for every element in the given range.
 *
 * @param start - the start index, inclusive
 * @param end - the end index, exclusive
 * @param element - the function to provide an element by its index
 * @param key - the function to provide a key for the element
 * @param action - the memo function to be invoked for every element
 *
 * @memo:intrinsic
 */
public func RepeatRange<T>(
    start: Int64,
    end: Int64,
    element: (index: Int64) -> T,
    key: (element: T, index: Int64) -> CallsiteKey,
    action: (element: T, index: Int64) -> Unit
): Unit {
    memo4(getCallsiteKey(), start, end, key, action) {
        start: State<Int64>, end: State<Int64>, key: State<(element: T, index: Int64) -> CallsiteKey>, action: State<(element: T,
        index: Int64) -> Unit> =>
        let max = end.getValue()
        var min = start.getValue()
        while (min < max) {
            let element = element(min)
            memo2(key.getValue()(element, min), element, min) {
                e: State<T>, i: State<Int64> => action.getValue()(e.getValue(), i.getValue())
            }
            min++
        }
    }
}
