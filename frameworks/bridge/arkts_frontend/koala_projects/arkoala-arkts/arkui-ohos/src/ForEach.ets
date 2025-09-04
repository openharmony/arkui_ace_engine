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

import { hashCodeFromString } from "@koalaui/common"
import { RepeatByArray } from "@koalaui/runtime"
import { memo } from "@koalaui/runtime/annotations"

@memo
export function ForEach<T>(data: Array<T>,
    @memo
    itemGenerator: (item: T, index?: int) => void,
    keyGenerator?: (item: T, index?: int) => string,
) {
    RepeatByArray<T>(data,
        (element: T, index: int): int => keyGenerator ? hashCodeFromString(keyGenerator!(element, index)) : index,
        (element: T, index: int): void => { itemGenerator(element, (index)) })
}