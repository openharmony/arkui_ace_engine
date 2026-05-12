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

export class Rect {
    left: int = 0;
    top: int = 0;
    width: int = 0;
    height: int = 0;
}

export class RectInVP {
    left: number = 0;
    top: number = 0;
    width: number = 0;
    height: number = 0;
}

export class Size {
    width: int = 0;
    height: int = 0;
}

export class SizeInVP {
    width: number = 0;
    height: number = 0;
}

export class AvoidArea {
    visible: boolean = false;
    leftRect: Rect = new Rect();
    topRect: Rect = new Rect();
    rightRect: Rect = new Rect();
    bottomRect: Rect = new Rect();
}

export class AvoidAreaOptions {
    type?: AvoidAreaType;
}

export enum AvoidAreaType {
    TYPE_SYSTEM = 0,
    TYPE_CUTOUT = 1,
    TYPE_SYSTEM_GESTURE = 2,
    TYPE_KEYBOARD = 3,
    TYPE_NAVIGATION_INDICATOR = 4,
}

export interface UIEnvWindowAvoidAreaInfoPX {
}

export interface UIEnvWindowAvoidAreaInfoVP {
}

export interface UIEnvAvoidAreaVP {
}

export class Window {
    getWindowAvoidArea(type: AvoidAreaType): AvoidArea {
        return new AvoidArea();
    }
    on(type: string, callback: Function): void {}
    off(type: string, callback?: Function): void {}
}

export function findWindow(name: string): Window {
    return new Window();
}
