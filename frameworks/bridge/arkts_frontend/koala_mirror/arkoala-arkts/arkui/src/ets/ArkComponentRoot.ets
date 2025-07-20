import { memo, memo_intrinsic, memo_entry, memo_stable, memo_skip } from "@koalaui/runtime/annotations"
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

import { mutableState, MutableState, NodeAttach, rememberDisposable, remember, RunEffect, scheduleCallback } from "@koalaui/runtime"
import { PeerNode } from "./PeerNode";
import { ArkComponentRootPeer } from "./generated";
import { ArkCustomComponent } from "./ArkCustomComponent"
import { int32 } from "@koalaui/common"
import { CurrentRouterTransitionState, RouterTransitionVisibility } from "./handwritten/Router";

let _isNeedCreate: boolean = false

export function setNeedCreate(isNeedCreate: boolean)
{
    _isNeedCreate = isNeedCreate
}

@memo
export function ArkComponentRoot(
    component: ArkCustomComponent,
    @memo
    content: () => void
) {
    NodeAttach<PeerNode>(
        (): PeerNode => ArkComponentRootPeer.create(),
        (node: PeerNode): void => {
            let state = CurrentRouterTransitionState()
            if (state) {
                RunEffect<RouterTransitionVisibility>(state.visibility, (visibility: RouterTransitionVisibility): void => {
                    switch (visibility.valueOf()) {
                        case RouterTransitionVisibility.Showing.valueOf():
                            component.onPageShow()
                            break
                        case RouterTransitionVisibility.Hiding.valueOf():
                            component.onPageHide()
                            break
                        default: break
                    }
                })
            }
            let shown = rememberDisposable<MutableState<boolean>>((): MutableState<boolean> => {
                let state = mutableState(false)
                scheduleCallback((): void => {
                    component.aboutToAppear()
                    // Improve: page visibility doesn't belong here, remove when router transition state properly maintained.
                    // component.onPageShow()
                    state.value = true
                })
                return state
            }, (_: MutableState<boolean> | undefined): void =>
                scheduleCallback((): void => {
                    component.aboutToDisappear()
                    // Improve: page visibility doesn't belong here, remove when router transition state properly maintained.
                    // component.onPageHide()
                })
            )
            // Do we need it here?
            component.pageTransition()
            if (shown.value) {
                content()
                remember<void>((): void => scheduleCallback((): void => component.onDidBuild()))
            }
        }
    )
}