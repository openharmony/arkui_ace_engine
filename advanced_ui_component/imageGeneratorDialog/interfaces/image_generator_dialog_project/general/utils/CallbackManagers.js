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
    constructor() {
        this.callbacks = [];
    }
    addCallback(callback) {
        this.callbacks.push(callback);
    }
    removeCallback(callback) {
        let index = this.callbacks.findIndex(element => element === callback);
        if (index === -1) {
            return;
        }
        this.callbacks.splice(index, 1);
    }
    executeCallback(size) {
        let callbacksCopy = this.callbacks;
        for (let index = 0; index < callbacksCopy.length; index++) {
            callbacksCopy[index](size);
        }
    }
    destroy() {
        this.callbacks = [];
        WinSizeChangeCallbackManager.instance__ = undefined;
    }
    static getOrCreateInstance() {
        if (!WinSizeChangeCallbackManager.instance__) {
            WinSizeChangeCallbackManager.instance__ = new WinSizeChangeCallbackManager();
        }
        return WinSizeChangeCallbackManager.instance__;
    }
}
