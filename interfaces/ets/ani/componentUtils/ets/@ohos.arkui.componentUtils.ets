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

export default namespace componentUtils {
    loadLibrary("componentUtils_ani");

    export interface Size {
        width: double
        height: double
    }

    export interface Offset {
        x: double
        y: double
    }

    export interface TranslateResult {
        x: double
        y: double
        z: double
    }

    export interface ScaleResult {
        x: double
        y: double
        z: double
        centerX: double
        centerY: double
    }

    export interface RotateResult {
        x: double
        y: double
        z: double
        centerX: double
        centerY: double
        angle: double
    }

    type Matrix4Result = [
        double,
        double,
        double,
        double,
        double,
        double,
        double,
        double,
        double,
        double,
        double,
        double,
        double,
        double,
        double,
        double,
    ];

    export interface ComponentInfo {
        size: Size
        localOffset: Offset
        windowOffset: Offset
        screenOffset: Offset
        translate: TranslateResult
        scale: ScaleResult
        rotate: RotateResult
        transform: Matrix4Result
    }

    class SizeInner implements Size {
        width: double;
        height: double;
        constructor(width: double, height: double) {
            this.width = width;
            this.height = height;
        }
    }

    class OffsetInner implements Offset {
        x: double;
        y: double;
        constructor(x: double, y: double) {
            this.x = x;
            this.y = y;
        }
    }

    class TranslateResultInner implements TranslateResult {
        x: double;
        y: double;
        z: double;
        constructor(x: double, y: double, z: double) {
            this.x = x;
            this.y = y;
            this.z = z;
        }
    }

    class ScaleResultInner implements ScaleResult {
        x: double;
        y: double;
        z: double;
        centerX: double;
        centerY: double;
        constructor(x: double, y: double, z: double, centerX: double, centerY: double) {
            this.x = x;
            this.y = y;
            this.z = z;
            this.centerX = centerX;
            this.centerY = centerY;
        }
    }

    class RotateResultInner implements RotateResult {
        x: double;
        y: double;
        z: double;
        centerX: double;
        centerY: double;
        angle: double;
        constructor(x: double, y: double, z: double, centerX: double, centerY: double, angle: double) {
            this.x = x;
            this.y = y;
            this.z = z;
            this.centerX = centerX;
            this.centerY = centerY;
            this.angle = angle;
        }
    }

    class ComponentInfoInner implements ComponentInfo {
        size: Size;
        localOffset: Offset;
        windowOffset: Offset;
        screenOffset: Offset;
        translate: TranslateResult;
        scale: ScaleResult;
        rotate: RotateResult;
        transform: Matrix4Result;
        constructor(size: Size, localOffset: Offset, windowOffset: Offset, screenOffset: Offset, translate: TranslateResult,
            scale: ScaleResult, rotate: RotateResult, transform: Matrix4Result) {
            this.size = size;
            this.localOffset = localOffset;
            this.windowOffset = windowOffset;
            this.screenOffset = screenOffset;
            this.translate = translate;
            this.scale = scale;
            this.rotate = rotate;
            this.transform = transform;
        }
    }

    export native function getRectangleById(id: string): ComponentInfo;
}