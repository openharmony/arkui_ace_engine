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

export default namespace performanceMonitor {
    loadLibrary("performanceMonitor_ani");
    export enum ActionType {
        LAST_DOWN = 0,
        LAST_UP = 1,
        FIRST_MOVE = 2
    };
    export enum SourceType {
        PERF_TOUCH_EVENT = 0,
        PERF_MOUSE_EVENT = 1,
        PERF_TOUCHPAD_EVENT = 2,
        PERF_JOYSTICK_EVENT = 3,
        PERF_KEY_EVENT = 4
    };
    export native function begin(scene: string, startInputType: ActionType, note?: string): void;
    export native function end(scene: string): void;
    export native function recordInputEventTime(type: ActionType, sourceType: SourceType, time: number): void;
}
