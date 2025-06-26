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

import { describe, beforeEach, it, Size } from "@ohos/hypium"

declare namespace globalThis {
    let __OpenHarmony: boolean
    let __generateGolden: boolean
}

globalThis.__OpenHarmony = true

type Fn = () => void

const suiteMap = new Map<string, Fn>()

export function startTests(generateGolden: boolean = false) {
    globalThis.__generateGolden = generateGolden
    suiteMap.forEach((fn: Fn, title: string) => {
        describe(title, function () {
            fn()
        })
    })
}

(suiteSetup as any) = (title: string, fn: Fn): void => {
    beforeEach(fn)
}

(suite as any) = (title: string, fn: Fn): void => {
    suiteMap.set(title, fn)
}

(test as any) = (title: string, fn?: Fn): void => {
    it(fn ? title : `[SKIP] ${title}`, Size.MEDIUMTEST, fn ? fn : () => { })
}

(test as any).skip = (title: string, fn?: Fn): void => {
    it(`[SKIP] ${title}`, Size.MEDIUMTEST, () => { })
}


interface TimeFn {
    now: () => number
}

(performance as TimeFn) = {
    now: (): number => {
        return Date.now()
    }
}
