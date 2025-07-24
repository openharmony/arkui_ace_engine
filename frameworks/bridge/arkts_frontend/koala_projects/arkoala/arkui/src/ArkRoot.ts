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

import { CurrentControl } from "@koalaui/arkoala"
import { CurrentRouter, Routed, setArkRouter } from "@koalaui/arkui-common"
import { memoBind2, remember } from "@koalaui/runtime"

/** @memo */
export function ArkRoot(
    /** @memo */
    content?: () => void,
    url?: string,
) {
    Routed(
        () => {
            content?.()
        },
        (
            /** @memo */
            routedContent: () => void
        ) => {
            const router = CurrentRouter()!
            const control = CurrentControl()!
            remember(() => {
                console.log("[arkoala] control is", control)
                setArkRouter(router)
                control.addListener("arkoala.router.register", (args) => {
                    let anyArgs = args as any
                    console.log("[arkoala] router register", anyArgs.url)
                    router.register(anyArgs.url, anyArgs.page)
                })
                control.addListener("arkoala.router.push", (args) => {
                    let anyArgs = args as any
                    console.log("[arkoala] router push", anyArgs.url)
                    router.push(anyArgs.url, anyArgs.params)
                        .then(() => anyArgs.callback?.())
                    return
                })
                control.addListener("arkoala.router.back", (args) => {
                    let anyArgs = args as any
                    router.back(anyArgs.url, anyArgs.params)
                        .then(() => anyArgs.callback?.())
                    return
                })
                control.addListener("arkoala.router.replace", (args) => {
                    let anyArgs = args as any
                    router.replace(anyArgs.url, anyArgs.params)
                        .then(() => anyArgs.callback?.())
                    return
                })
            })
            routedContent()
        },
        url
    )
}

export function ArkRooted(
    /** @memo */
    content?: () => void,
    url?: string,
):
    /** @memo */
    () => void {
    return memoBind2(ArkRoot, content, url)
}