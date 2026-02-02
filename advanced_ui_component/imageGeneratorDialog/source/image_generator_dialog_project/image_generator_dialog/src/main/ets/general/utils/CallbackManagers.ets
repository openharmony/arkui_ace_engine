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

export class WinSizeChangeCallbackManager {
    private static instance__: WinSizeChangeCallbackManager | undefined;
    private callbacks: Array<WindowSizeChangeCallback> = [];

    public addCallback(callback: WindowSizeChangeCallback) {
        this.callbacks.push(callback);
    }

    public removeCallback(callback: WindowSizeChangeCallback) {
        let index = this.callbacks.findIndex(element => element === callback);
        if (index === -1) {
            return;
        }
        this.callbacks.splice(index, 1);
    }

    public executeCallback(size: Size) {
        let callbacksCopy = this.callbacks;
        for (let index = 0; index < callbacksCopy.length; index++) {
            callbacksCopy[index](size);
        }
    }

    public destroy() {
        this.callbacks = [];
        WinSizeChangeCallbackManager.instance__ = undefined;
    }

    public static getOrCreateInstance(): WinSizeChangeCallbackManager {
        if (!WinSizeChangeCallbackManager.instance__) {
            WinSizeChangeCallbackManager.instance__ = new WinSizeChangeCallbackManager();
        }
        return WinSizeChangeCallbackManager.instance__;
    }
}

declare type WindowSizeChangeCallback = (size: Size) => void;