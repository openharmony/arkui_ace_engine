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

import { SerializerBase, runtimeType, RuntimeType, pointer } from '@koalaui/interop';
import { ArkUIGeneratedNativeModule } from '#components';
import { ArkPasteButtonComponent, ResourceStr, ArkPasteButtonPeer, PasteButtonCallback, PasteButtonOnClickResult } from '#generated';
import { ArkUIAniModule } from 'arkui.ani';

export class PasteButtonOpsHandWritten {
    static hookPasteButtonOnClickImpl(
        receiver: ArkPasteButtonComponent | ArkPasteButtonPeer, value: PasteButtonCallback | undefined): void {
        let peerPtr: pointer;
        if (receiver instanceof ArkPasteButtonComponent) {
            peerPtr = receiver.getPeer().peer.ptr;
        } else if (receiver instanceof ArkPasteButtonPeer) {
            peerPtr = receiver.peer.ptr;
        }
        if (peerPtr === undefined) {
            return;
        }
        ArkUIAniModule._PasteButton_SetOnClickCallback(peerPtr, value);
    }
}