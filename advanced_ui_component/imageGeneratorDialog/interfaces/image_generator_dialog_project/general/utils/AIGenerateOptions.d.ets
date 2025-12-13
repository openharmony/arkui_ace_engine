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

import common2D from "@ohos.graphics.common2D";
import imageGeneration from '@ohos.arkui.intelligence.imageGeneration';
import image from '@ohos.multimedia.image';
export declare class AIGenerateOptions {
    action: number;
    userPrompt: string;
    images: Array<imageGeneration.ImageItem> | undefined;
    layoutImage: imageGeneration.ImageItem | undefined;
    shapePath: Array<common2D.Point> | undefined;
    style: string | undefined;
    type: number;
    resolution: image.Size;
    ratio: string;
    version: string;
    private static instance;
    static getInstance(): AIGenerateOptions;
    setImages(f18: Array<imageGeneration.ImageItem>): void;
    updateRelativeLayout(d18: boolean): void;
    updateUserPrompt(c18: string): void;
    updateShapePath(b18: Array<common2D.Point>): void;
    updateStyle(a18: string): void;
    updateResolution(z17: image.Size): void;
    updateRatio(y17: string): void;
    updateType(x17: number): void;
    updateVersion(w17: string): void;
}
