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

/**
 * @returns the number of milliseconds elapsed since midnight,
 *          January 1, 1970 Universal Coordinated Time (UTC).
 */
export function timeNow(): number {
    return Date.now()
}

/**
 * @param fractionDigits - number of digits after the decimal point [0 - 20]
 * @returns a string representing a number in fixed-point notation
 */
export function numberToFixed(value: number, fractionDigits: number): string {
    return new Number(value).toFixed(fractionDigits)
}
