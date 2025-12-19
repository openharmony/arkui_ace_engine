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

export const LogTag = '[imageGenerator]';
export var CanvasMode;
(function (CanvasMode) {
    CanvasMode[CanvasMode["GENERAL_MODE"] = 0] = "GENERAL_MODE";
    CanvasMode[CanvasMode["DOODLE_MODE"] = 1] = "DOODLE_MODE";
    CanvasMode[CanvasMode["DEFAULT"] = 0] = "DEFAULT";
})(CanvasMode || (CanvasMode = {}));
export var CanvasLayoutDirection;
(function (CanvasLayoutDirection) {
    CanvasLayoutDirection[CanvasLayoutDirection["HORIZONTAL"] = 0] = "HORIZONTAL";
    CanvasLayoutDirection[CanvasLayoutDirection["VERTICAL"] = 1] = "VERTICAL";
    CanvasLayoutDirection[CanvasLayoutDirection["DEFAULT"] = 0] = "DEFAULT";
})(CanvasLayoutDirection || (CanvasLayoutDirection = {}));
export var ImageGenerateState;
(function (ImageGenerateState) {
    ImageGenerateState[ImageGenerateState["CONFIGURATION"] = 0] = "CONFIGURATION";
    ImageGenerateState[ImageGenerateState["GENERATING"] = 1] = "GENERATING";
    ImageGenerateState[ImageGenerateState["BEFORE_GENERATED"] = 2] = "BEFORE_GENERATED";
    ImageGenerateState[ImageGenerateState["GENERATED"] = 3] = "GENERATED";
    ImageGenerateState[ImageGenerateState["MINIMIZED"] = 4] = "MINIMIZED";
})(ImageGenerateState || (ImageGenerateState = {}));
