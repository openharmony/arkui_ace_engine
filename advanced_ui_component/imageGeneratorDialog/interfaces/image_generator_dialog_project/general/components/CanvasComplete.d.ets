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
import image from "@ohos.multimedia.image";
/**
 * ResultImageShowArea - Result image display area with zoom and pan support
 * Supports: pinch to zoom, single finger drag, double-tap to zoom in/out
 */
@ComponentV2
export declare struct ResultImageShowArea {
    @Param
    readonly pixelMap?: image.PixelMap | undefined;
    @Local
    imageScale: number;
    private minScale;
    private maxScale;
    @Local
    offsetX: number;
    @Local
    offsetY: number;
    @Local
    initialScale: number;
    @Local
    initialOffsetX: number;
    @Local
    initialOffsetY: number;
    @Local
    isPinching: boolean;
    @Local
    focusX: number;
    @Local
    focusY: number;
    @Local
    focalPointX: number;
    @Local
    focalPointY: number;
    @Local
    imageWidth: number;
    @Local
    imageHeight: number;
    @Local
    containerWidth: number;
    @Local
    containerHeight: number;
    @Local
    imageAspectRatio: number;
    aboutToAppear(): void;
    snapScaleToBounds(): void;
    snapOffsetToBounds(): void;
    build(): void;
}
@ComponentV2
export declare struct ContinueOperateArea {
    @Param
    readonly currentGenerateState: ImageGenerateState | undefined;
    @Event
    changeGenerateState: (state: ImageGenerateState) => void;
    private limit;
    build(): void;
}
@ComponentV2
export declare struct HistoryArea {
    @Param
    readonly resultList: string[];
    private selectIndex;
    build(): void;
}
