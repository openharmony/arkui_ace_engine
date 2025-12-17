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
import { CanvasMode, ImageGenerateState } from "../types/Declaration";
import image from "@ohos.multimedia.image";
export declare class styleItem {
    name: ResourceStr;
    resourceAddr?: image.PixelMap | ResourceStr;
}
@ComponentV2
export declare struct CanvasHome {
    @Local
    titleName: string;
    @Local
    currentCanvasMode: CanvasMode;
    @Local
    currentGenerateState: ImageGenerateState;
    @Param
    @Require
    readonly imageInfoArr: Array<imageGeneration.ImageItem>;
    @Param
    @Require
    readonly styles?: Array<imageGeneration.ImageStyle>;
    @Param
    readonly userPrompt: string;
    @Builder
    homeTitleBuilder(): void;
    build(): void;
}
