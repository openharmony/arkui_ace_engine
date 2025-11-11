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

import { mutableState, MutableState, NodeAttach, rememberDisposable, RunEffect, scheduleCallback } from '@koalaui/runtime';
import { PeerNode } from './PeerNode';
import { ArkCustomComponentRootPeer } from '#generated';
import { ArkCustomComponent } from './ArkCustomComponent';
import { InteropNativeModule } from '@koalaui/interop';
import { __context, GlobalStateManager, StateManager } from '@koalaui/runtime';
import { ObserveSingleton } from '@ohos.arkui.stateManagement';

export function setNeedCreate(isNeedCreate: boolean): boolean {
    const temp = GlobalStateManager.instance._isNeedCreate
    GlobalStateManager.instance._isNeedCreate = isNeedCreate
    return temp
}

@memo
export function ArkComponentRoot(
    component: ArkCustomComponent,
    @memo
    content: (node: PeerNode) => void
) {
    InteropNativeModule._NativeLog(`ArkTS ArkComponentRoot enter`)
    NodeAttach<PeerNode>(
        () => ArkCustomComponentRootPeer.create(component),
        (node: PeerNode) => {
             rememberDisposable(() => {
                 ObserveSingleton.instance.applyTaskDelayMutableStateChange(() => {
                     component.aboutToAppear();
                 });
                 return true;
             }, (_: boolean | undefined) => {
                 scheduleCallback(() => {
                     component.aboutToDisappear()
                 });
             });
             content(node);
             return;
        }
    );
}
