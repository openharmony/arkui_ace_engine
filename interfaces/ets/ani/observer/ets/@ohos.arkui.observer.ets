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
 import type { Callback } from '@ohos.base';
 
 export default namespace uiObserver {
    loadLibrary("observer_ani");
    export native function createUIObserver(id: number): UIObserver;
    export class DensityInfo {
        density: number;
    }
    export default interface UIObserver
    {
        on(type: string, callback: ()=>void) : void;
        on(type: 'densityUpdate', callback: Callback<DensityInfo>): void;
        off(type: string, callback?: ()=>void) : void;
    }
    
    class UIObserverImpl implements UIObserver
    {
        private nativeObserverAddr:long = 0;
        
        constructor(nativeAddr:long) {
            if (this.nativeObserverAddr == 0) {
                this.nativeObserverAddr = nativeAddr;
            }
        }
        
        public native on(type: string, callback: ()=>void) : void;
        public native on(type: 'densityUpdate', callback: Callback<DensityInfo>): void;
        public native off(type: string, callback?: ()=>void) : void;
    }
 }
