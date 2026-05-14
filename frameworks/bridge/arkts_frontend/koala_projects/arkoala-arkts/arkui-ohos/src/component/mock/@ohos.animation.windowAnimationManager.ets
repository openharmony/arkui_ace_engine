 /*
* Copyright (c) 2026 Huawei Device Co., Ltd.
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

// Stub module for @ohos.animation.windowAnimationManager — previewer only.
// ArkTS strict mode: all params and return types require annotations.

export namespace windowAnimationManager {
    export interface RRect {
        left: double;
        top: double;
        width: double;
        height: double;
        radius: double;
    }

    export interface WindowAnimationTarget {
        readonly bundleName: string;
        readonly abilityName: string;
        readonly windowBounds: RRect;
        readonly missionId: int;
    }

    export interface WindowAnimationFinishedCallback {
        onAnimationFinish(): void;
    }

    export interface WindowAnimationController {
        onStartAppFromLauncher?: (startingWindowTarget: WindowAnimationTarget, finishCallback: WindowAnimationFinishedCallback) => void;
        onStartAppFromRecent?: (startingWindowTarget: WindowAnimationTarget, finishCallback: WindowAnimationFinishedCallback) => void;
        onStartAppFromOther?: (startingWindowTarget: WindowAnimationTarget, finishCallback: WindowAnimationFinishedCallback) => void;
        onAppTransition?: (fromWindowTarget: WindowAnimationTarget, toWindowTarget: WindowAnimationTarget, finishCallback: WindowAnimationFinishedCallback) => void;
        onMinimizeWindow?: (minimizingWindowTarget: WindowAnimationTarget, finishCallback: WindowAnimationFinishedCallback) => void;
        onCloseWindow?: (closingWindowTarget: WindowAnimationTarget, finishCallback: WindowAnimationFinishedCallback) => void;
        onScreenUnlock?: (finishCallback: WindowAnimationFinishedCallback) => void;
        onWindowAnimationTargetsUpdate?: (fullScreenWindowTarget: WindowAnimationTarget, floatingWindowTargets: WindowAnimationTarget[]) => void;
    }

    export function setController(controller: WindowAnimationController): void {}
}

export default windowAnimationManager;
