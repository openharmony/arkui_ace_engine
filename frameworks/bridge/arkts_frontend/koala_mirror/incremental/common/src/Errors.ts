/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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


// "assert" is a reserved keyword in ArkTS :-(
export function assertion(condition: boolean, message: string) {
    if (!condition) throw new Error(message)
}

// The unknonwn type support in ArkTS compiler is not ready yet.
// When it is ready move from
//    ensure(value, message)
// to
//    value ?? error(message)
// which is much more readable
export function ensure<T>(value: T|undefined, message: string): T {
    if (value == undefined) throw new Error(message)
    return value as T
}
