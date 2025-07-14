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

export enum LifecycleEventKind {
    SHOW_FRAME,
    HIDE_FRAME,
    CLOSE_FRAME,
    ON_APPEAR,
    ON_DISAPPEAR,
    SHOW_COMPONENT,
    HIDE_COMPONENT,
    BACK,
    FOCUS_FRAME,
    UNFOCUS_FRAME
}

export class LifecycleEvent {
    kind: LifecycleEventKind
    constructor(kind: LifecycleEventKind) {
        this.kind = kind
    }
}