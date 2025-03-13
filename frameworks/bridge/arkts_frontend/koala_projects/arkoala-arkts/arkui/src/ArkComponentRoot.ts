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

import { mutableState, MutableState, NodeAttach, rememberDisposable, rememberMutableState, RunEffect, scheduleCallback } from "@koalaui/runtime"
import { PeerNode } from "./PeerNode";
import { ArkComponentRootPeer } from "./generated/peers/ArkStaticComponentsPeer";
import { ArkCustomComponent } from "./ArkCustomComponent"
import { int32 } from "@koalaui/common"
import { CurrentRouterTransitionState, VisibilityHiding, VisibilityShowing, WithRouterTransitionState } from "./handwritten/Router";

/** @memo */
export function ArkComponentRoot(
    component: ArkCustomComponent,
    /** @memo */
    content: () => void
) {
    NodeAttach<PeerNode>(
        () => ArkComponentRootPeer.create(),
        (node: PeerNode) => {
            let state = CurrentRouterTransitionState()
            if (state) {
                RunEffect<int32>(state.visibility, (visibility: int32) => {
                    switch (visibility) {
                        case VisibilityShowing:
                            component.onPageShow()
                            break
                        case VisibilityHiding:
                            component.onPageHide()
                            break
                        default: break
                    }
                })
            } else {
                content();
            }
            let shown = rememberDisposable(() => {
                let state = mutableState(false)
                scheduleCallback(() => {
                    component.aboutToAppear()
                    // TODO: page visibility doesn't belong here, remove when router transition state properly maintained.
                    // component.onPageShow()
                    state.value = true
                })
                return state
            }, (_: MutableState<boolean> | undefined) =>
                scheduleCallback(() => {
                    component.aboutToDisappear()
                    // TODO: page visibility doesn't belong here, remove when router transition state properly maintained.
                    // component.onPageHide()
                })
            )
            // Do we need it here?
            component.pageTransition()
            if (shown.value) content() // skip first frame and hide router state
        }
    )
}