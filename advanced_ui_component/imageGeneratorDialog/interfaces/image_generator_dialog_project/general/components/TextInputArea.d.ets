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
    @Local
    userPrompt: string;
    @Local
    inputController: TextAreaController;
    private textAreaPadding;
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
    @Local
    imgCounts: number;
    @Local
    isEnableTouchUp: boolean;
    @Local
    isShowTouchUp: boolean;
    @Local
    stack: NavPathStack | undefined;
    @Local
    updateInputText: string;
    @Monitor('imgCounts', 'isClickKeepLayout', 'updateInputText', 'isSelectedPatches')
    watchKeepLayout(v8: IMonitor): void;
    @Monitor('userPrompt')
    watchUserPromptChange(u8: IMonitor): void;
    aboutToAppear(): void;
    build(): void;
}
