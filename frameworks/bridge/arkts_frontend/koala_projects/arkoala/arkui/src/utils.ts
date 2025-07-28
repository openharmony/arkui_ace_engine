/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

export function isResource(value: unknown): boolean {
    return typeof value === 'object'
        && value !== null
        && value.hasOwnProperty("bundleName")
        && value.hasOwnProperty("moduleName")
}

export function isPadding(value: unknown): boolean {
    function isLength(value: unknown): boolean {
        return typeof value === 'number'
            || typeof value === 'string'
            || isResource(value)
    }
    function hasLengthProperty(value: object, prop: string): boolean {
        return value.hasOwnProperty(prop) && isLength(value[prop as keyof object])
    }
    return typeof value === 'object'
        && value !== null
        && (hasLengthProperty(value, "top")
        ||  hasLengthProperty(value, "left")
        ||  hasLengthProperty(value, "bottom")
        ||  hasLengthProperty(value, "right"))
}
