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

import { NodeAttach, rememberDisposable, rememberMutableState, scheduleCallback } from "@koalaui/runtime"
import { PeerNode } from "./PeerNode";
import { ArkComponentRootPeer } from "./generated/peers/ArkStaticComponentsPeer";
import { ArkCustomComponent } from "./ArkCustomComponent"

/** @memo */
export function ArkComponentRoot(
    component: ArkCustomComponent,
    /** @memo */
    content: () => void
) {
    // emulate lifecycle of ArkUI component
    const appear = rememberMutableState<boolean>(true)
    /* <string> to workaround compiler bug №21318, since `void | undefined` is not allowed */
    rememberDisposable<string>(
        () => {
            scheduleCallback(() => {
                appear.value = false
                component.aboutToAppear()
                component.onPageShow()
            })
            return ""
        },
        (_: string | undefined)=> {
            scheduleCallback((): void => {
                component.onPageHide()
                component.aboutToDisappear()
            })
        }
    )
    NodeAttach<PeerNode>(
        () => ArkComponentRootPeer.create(),
        (node: PeerNode) => {
            content()
            // const state = CurrentRouterTransitionState()
            // if (state) {
            //     RunEffect(state.visibility, visibility => {
            //         if (visibility == RouterTransitionVisibility.Showing) component.onPageShow?.()
            //         else if (visibility == RouterTransitionVisibility.Hiding) component.onPageHide?.()
            //     })
            //     component.pageTransition?.()
            // }
            // if (!appear.value) WithRouterTransitionState(undefined, content) // skip first frame and hide router state
        }
    )
}