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

// Mock for @ohos/arkui/observer
export class UIObserver {
    on(type: string, callback: Function): void {}
    off(type: string, callback?: Function): void {}
}
export let uiObserver = new UIObserver();
export default uiObserver;

// Mock for @ohos/arkui/UIContext
export class UIContext {
    getInstanceId(): int { return 0; }
    checkThread(instanceId?: int): boolean { return true; }
}

// Mock for @ohos.window
export class WindowStage {}
export class Window {
    static getLastWindow(): Promise<Window> {
        return new Promise<Window>((resolve: (value: Window) => void) => { resolve(new Window()); });
    }
    getUIContext(): UIContext {
        return new UIContext();
    }
}
// Removed windowDefault - caused type inference error

// Mock for @ohos.arkui.component
export enum HeightBreakpoint {
    HEIGHT_SM = 0,
    HEIGHT_MD = 1,
    HEIGHT_LG = 2,
}

export enum WidthBreakpoint {
    WIDTH_XS = 0,
    WIDTH_SM = 1,
    WIDTH_MD = 2,
    WIDTH_LG = 3,
    WIDTH_XL = 4,
}

// Mock for @ohos.base
export class BusinessError<T = void> extends Error {
    data?: T;
    constructor(code: Int, msg?: Error) {
        super(msg?.message ?? '');
    }
}
