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

import { int32 } from "@koalaui/compat";
import { KPointer } from "@koalaui/interop"
import { OverlayManagerOptions } from "@ohos/arkui/UIContext"
import { LevelOrder } from "@ohos/promptAction"

export default declare namespace overlayManager {
    loadLibrary("overlayManager_ani");

    export function setOverlayManagerOptions(options: OverlayManagerOptions): boolean;

    export function getOverlayManagerOptions(): OverlayManagerOptions;

    export function addComponentContent(contentNode: KPointer, index: int32): void;

    export function addComponentContentWithOrder(contentNode: KPointer, levelOrder: LevelOrder): void;

    export function removeComponentContent(contentNode: KPointer): void;

    export function showComponentContent(contentNode: KPointer): void;

    export function hideComponentContent(contentNode: KPointer): void;

    export function showAllComponentContents(): void;

    export function hideAllComponentContents(): void;
}