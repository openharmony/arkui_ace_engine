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
import { CanvasLayoutDirection, CanvasMode } from '../types/Declaration';
@ComponentV2
export declare struct ImageGeneratorDialog {
    stack: NavPathStack;
    @Param
    @Require
    readonly options?: imageGeneration.GeneratorDialogOptions;
    @Local
    width_: Dimension;
    @Local
    height_: Dimension;
    private MAX_IMAGE_COUNT;
    @Local
    imageInfoArr: Array<imageGeneration.ImageItem>;
    @Local
    stylesArr: Array<imageGeneration.ImageStyle>;
    @Local
    userPrompt: string;
    private curWindow?;
    @Provider('globalCanvasMode')
    curCanvasMode: CanvasMode;
    @Provider('globalSheetType')
    curSheetType: SheetType;
    @Provider('globalLayoutDirection')
    curLayoutDirection: CanvasLayoutDirection;
    updateCanvasLayoutProperties: (size: Size) => void;
    onWinSizeChangForAll: (size: Size) => void;
    private initWinSizeChangeCallback;
    private initLayoutProperties;
    @Builder
    pageMap(name: string): void;
    private initImageInfoArr;
    private initUserPrompt;
    aboutToAppear(): void;
    aboutToDisappear(): void;
    build(): void;
}
