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
        width: number
        height: number
    }

    export interface Offset {
        x: number
        y: number
    }

    export interface TranslateResult {
        x: number
        y: number
        z: number
    }

    export interface ScaleResult {
        x: number
        y: number
        z: number
        centerX: number
        centerY: number
    }

    export interface RotateResult {
        x: number
        y: number
        z: number
        centerX: number
        centerY: number
        angle: number
    }

    type Matrix4Result = [
        number,
        number,
        number,
        number,
        number,
        number,
        number,
        number,
        number,
        number,
        number,
        number,
        number,
        number,
        number,
        number,
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
        width: number = 0.0
        height: number = 0.0
    }

    class OffsetInner implements Offset {
        x: number = 0.0
        y: number = 0.0
    }

    class TranslateResultInner implements TranslateResult {
        x: number = 0.0
        y: number = 0.0
        z: number = 0.0
    }

    class ScaleResultInner implements ScaleResult {
        x: number = 0.0
        y: number = 0.0
        z: number = 0.0
        centerX: number = 0.0
        centerY: number = 0.0
    }

    class RotateResultInner implements RotateResult {
        x: number = 0.0
        y: number = 0.0
        z: number = 0.0
        centerX: number = 0.0
        centerY: number = 0.0
        angle: number = 0.0
    }

    class ComponentInfoInner implements ComponentInfo {
        size: Size = { width: 0.0, height: 0.0 };
        localOffset: Offset  = { x: 0.0, y: 0.0 };
        windowOffset: Offset = { x: 0.0, y: 0.0 };
        screenOffset: Offset = { x: 0.0, y: 0.0 };
        translate: TranslateResult = { x: 0.0, y: 0.0, z: 0.0 };
        scale: ScaleResult = { x: 0.0, y: 0.0, z: 0.0, centerX:0.0, centerY:0.0 };
        rotate: RotateResult = { x: 0.0, y: 0.0, z: 0.0, centerX:0.0, centerY:0.0, angle: 0.0 };
        transform: Matrix4Result = [
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        ];
    }

    export native function getRectangleById(id: string): ComponentInfo;
}