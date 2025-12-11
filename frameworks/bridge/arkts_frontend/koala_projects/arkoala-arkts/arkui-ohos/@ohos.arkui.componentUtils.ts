/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

export declare namespace componentUtils {
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
    // rename 'rectId' back to 'id' when libarkts gets updated
    export function getRectangleById(rectId: string): ComponentInfo;
}