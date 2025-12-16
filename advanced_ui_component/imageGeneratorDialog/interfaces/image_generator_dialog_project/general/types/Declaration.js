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

export var CanvasMode;
(function (x12) {
    x12[x12["GENERAL_MODE"] = 0] = "GENERAL_MODE";
    x12[x12["DOODLE_MODE"] = 1] = "DOODLE_MODE";
})(CanvasMode || (CanvasMode = {}));
export var ImageGenerateState;
(function (w12) {
    w12[w12["CONFIGURATION"] = 0] = "CONFIGURATION";
    w12[w12["GENERATING"] = 1] = "GENERATING";
    w12[w12["BEFORE_GENERATED"] = 2] = "BEFORE_GENERATED";
    w12[w12["GENERATED"] = 3] = "GENERATED";
    w12[w12["MINIMIZED"] = 4] = "MINIMIZED";
})(ImageGenerateState || (ImageGenerateState = {}));