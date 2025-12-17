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

import { ImageGenerateState } from "../types/Declaration";
import { MeasureUtils } from "@ohos.arkui.UIContext";
@ComponentV2
export declare struct TextInputArea {
    @Event
    changeGenerateState: (state: ImageGenerateState) => void;
    @Local
    isTextEdit: boolean;
    @Local
    inputText: string;
    @Param
    readonly userPrompt: string;
    @Local
    inputController: TextAreaController;
    private setMaxLines;
    @Local
    originText: string;
    @Local
    uiContext: UIContext;
    @Local
    uiContextMeasure: MeasureUtils;
    textSize: SizeOptions;
    @Local
    textMaxLines: number;
    @Local
    textOverflow: TextOverflow;
    private patchesStr;
    private keepLayoutStr;
    @Local
    isSelectedPatches: boolean;
    @Local
    isClickKeepLayout: boolean;
    @Local
    inputHeight: Length;
    @Param
    readonly imgCounts: number;
    @Local
    isEnableTouchUp: boolean;
    @Local
    isShowTouchUp: boolean;
    @Local
    stack: NavPathStack | undefined;
    @Local
    updateInputText: string;
    @Local
    textMaxLength: number;
    private getTextMaxLength;
    @Monitor('imgCounts', 'isClickKeepLayout', 'updateInputText', 'isSelectedPatches')
    watchKeepLayout(monitor: IMonitor): void;
    @Monitor('userPrompt')
    watchUserPromptChange(monitor: IMonitor): void;
    aboutToAppear(): void;
    private getDataFromUdmfRetry;
    private getDataFromUdmf;
    build(): void;
}
