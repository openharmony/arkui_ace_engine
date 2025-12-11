/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
import { OverlayManagerOptions } from "@ohos.arkui.UIContext"
import { LevelOrder } from "@ohos.promptAction"

export default namespace overlayManager {
    loadLibrary("overlayManager_ani");

    export native function setOverlayManagerOptions(options: OverlayManagerOptions): boolean;

    export native function getOverlayManagerOptions(): OverlayManagerOptions;

    export native function addComponentContent(contentNode: long, index: int): void;

    export native function addComponentContentWithOrder(contentNode: long, levelOrder: LevelOrder): void;

    export native function removeComponentContent(contentNode: long): void;

    export native function showComponentContent(contentNode: long): void;

    export native function hideComponentContent(contentNode: long): void;

    export native function showAllComponentContents(): void;

    export native function hideAllComponentContents(): void;
}