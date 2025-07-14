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

import { int32 } from "@koalaui/common"

export interface ArkoalaControl {
    sendMessage(topic: string, event: Object): void
    addListener(topic: string, handler: (args: Object) => void): void
}

export interface UIElement {
    id: int32
    kind: string
    children: Array<UIElement> | undefined
    width: string | undefined
    height: string | undefined
    borderWidth: string | undefined
    alignment: string | undefined
    color: string | number | undefined
    backgroundColor: string | undefined
    elementId: string | undefined
}

export interface WaitFramesEvent {
    skipFrames: int32
    callback: () => void
}
