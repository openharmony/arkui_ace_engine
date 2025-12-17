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

import { Position } from '@ohos.arkui.node';
import imageGeneration from '@ohos.arkui.intelligence.imageGeneration';
export declare function calcAABB(input: imageGeneration.ImageItem[], width: number, height: number): number[][];
export declare function mat4toImageItem(matrix: number[], width: number, height: number): imageGeneration.ImageItem;
@ComponentV2
export declare struct ImageOperate {
    @Param
    @Require
    readonly pixelMap: PixelMap | ImageContent;
    @Param
    @Require
    readonly preTransform: number[];
    @Param
    @Require
    readonly imageWidth: number | string;
    @Param
    @Require
    readonly imageAspectRito: number;
    @Local
    imageClick: boolean;
    @Local
    to00: Position;
    ImageW: number;
    ImageH: number;
    lockRotate: boolean;
    storeTouchPos: Position;
    blockFatherTouch: boolean;
    @Local
    matrix: number[];
    @Param
    readonly setMatrixCallback: Function | undefined;
    @Monitor('matrix')
    onMatrixChanged(): void;
    @Local
    storeMatrix: number[];
    toWindowPos: Position;
    traceId0: number;
    traceId1: number;
    store0Pos: Position;
    store1Pos: Position;
    touches: Map<number, Position>;
    aboutToAppear(): void;
    calcMatrix(): void;
    handleTouchOpt(id: number, type: TouchType, pos: Position): void;
    calcPointPos(input: Position): Position;
    build(): void;
}
