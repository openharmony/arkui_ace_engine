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

import { mutableState, MutableState, NodeAttach, rememberDisposable, RunEffect, scheduleCallback } from "@koalaui/runtime"
import { PeerNode } from "./PeerNode";
import { ArkComponentRootPeer } from "./component";
import { ArkCustomComponent } from "./ArkCustomComponent"
import { int32 } from "@koalaui/common"
import { InteropNativeModule } from "@koalaui/interop"
import router from "@ohos/router"

let _isNeedCreate: boolean = false

export function setNeedCreate(isNeedCreate: boolean): boolean
{
    const temp = _isNeedCreate
    _isNeedCreate = isNeedCreate
    return temp
}

/** @memo */
export function ArkComponentRoot(
    component: ArkCustomComponent,
    /** @memo */
    content: () => void
) {
    InteropNativeModule._NativeLog(`ArkTS ArkComponentRoot enter`)
    NodeAttach<PeerNode>(
        () => ArkComponentRootPeer.create(undefined),
        (node: PeerNode) => {
            if (_isNeedCreate) {
                rememberDisposable(() => {
                    let state = mutableState(false)
                    scheduleCallback(() => {})
                    return state;
                }, (_: MutableState<boolean> | undefined) => {
                    scheduleCallback(() => {
                        component.aboutToDisappear()
                    })
                })
                component.aboutToAppear()
                InteropNativeModule._NativeLog(`ArkTS ArkComponentRoot NodeAttach before content`)
                content()
                InteropNativeModule._NativeLog(`ArkTS ArkComponentRoot NodeAttach after content`)
                return
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
            if (shown.value) {
                InteropNativeModule._NativeLog(`ArkTS ArkComponentRoot NodeAttach before WithRouterTransitionState`)
                InteropNativeModule._NativeLog("AceRouter:ArkComponentRoot NodeAttach, UpdateRouter page visibility state")
                content();
                router.UpdateVisiblePagePeerNode(node);
                InteropNativeModule._NativeLog(`ArkTS ArkComponentRoot NodeAttach after WithRouterTransitionState`)
            }
        }
    )
}