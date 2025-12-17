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

import { ImageGenerateState } from '../types/Declaration';
@ComponentV2
export declare struct GenerateProgress {
    @Param
    readonly currentGenerateState: ImageGenerateState | undefined;
    @Event
    changeCurrentState: (state: ImageGenerateState) => void;
    @Param
    readonly imageNumber: number;
    @Local
    progressValue: number;
    @Local
    isGenerateSuccess: boolean;
    @Local
    isGenerateTimeout: boolean;
    private total;
    private timerCnt;
    private timerId;
    private goToBackGroundTimeStamp;
    private goToBackProgressValue;
    private estimatedTime;
    private isForeground;
    private canvasGenerateProgressChangeCallback;
    @Monitor('currentGenerateState')
    currentGenerateStateChangeMonitor(h5: IMonitor): void;
    getEstimatedTime(f5: number): number;
    aboutToAppear(): void;
    aboutToDisappear(): void;
    createApplicationListener(): void;
    clearApplicationListener(): void;
    createTimer(): void;
    clearTimer(): void;
    onSuccess(): void;
    onTimeOut(): void;
    build(): void;
}
@ComponentV2
export declare struct MinimizeButton {
    build(): void;
}
@ComponentV2
export declare struct GeneratingArea {
    @Param
    readonly currentGenerateState: ImageGenerateState | undefined;
    @Event
    changeGenerateState: (state: ImageGenerateState) => void;
    build(): void;
}