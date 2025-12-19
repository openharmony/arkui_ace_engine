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

import imageGeneration from '@ohos.arkui.intelligence.imageGeneration';
export declare const LogTag: string;
export declare enum CanvasMode {
    GENERAL_MODE = 0,
    DOODLE_MODE = 1,
    DEFAULT = 0
}
export declare enum CanvasLayoutDirection {
    HORIZONTAL = 0,
    VERTICAL = 1,
    DEFAULT = 0
}
export declare enum ImageGenerateState {
    CONFIGURATION = 0,
    GENERATING = 1,
    BEFORE_GENERATED = 2,
    GENERATED = 3,
    MINIMIZED = 4
}
export interface AIGenerateCallBack {
    onReady: () => void;
    onError: () => void;
    onResult: ((result: imageGeneration.GenerateTextTaskPartialResult) => void) | undefined;
    onComplete: ((result: string[]) => void) | undefined;
}
