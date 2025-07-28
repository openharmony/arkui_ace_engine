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
 export default namespace inspector {
    loadLibrary("inspector_ani");
    
    export native function createComponentObserver(id: string): ComponentObserver;
    export native function getInspectorByKey(id: string): string;
    export native function sendEventByKey(id: string, action: number, params: string): boolean;
    export native function getInspectorTree(): Object;
    
    export default interface ComponentObserver
    {
        on(type: string, callback: ()=>void) : void;

        off(type: string, callback?: ()=>void) : void;
    }
    
    class ComponentObserverImpl implements ComponentObserver
    {
        private nativeComponentObserver:long = 0;
        
        constructor(nativeAddr:long) {
            if (this.nativeComponentObserver == 0) {
                this.nativeComponentObserver = nativeAddr;
            }
        }
        
        public native on(type: string, callback: ()=>void) : void;

        public native off(type: string, callback?: ()=>void) : void;
    }
 }