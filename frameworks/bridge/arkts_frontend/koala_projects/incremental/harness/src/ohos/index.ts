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

export { Assert } from "./chai"
export { startTests } from "./mocha"

export function test(title: any, fn?: any) {
    throw new Error("unsupported test: " + title)
}

export function suite(title: any, fn?: any) {
    throw new Error("unsupported suite: " + title)
}

export function suiteSetup(title: any, fn?: any) {
    throw new Error("unsupported suiteSetup: " + title)
}
