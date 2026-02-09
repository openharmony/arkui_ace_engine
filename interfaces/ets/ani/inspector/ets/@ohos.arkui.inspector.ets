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
 import { Callback, RecordData } from '@ohos.base';
 import { VoidCallback } from './arkui.component.units';
 import hilog from '@ohos.hilog';
 
 const DOMAIN_ID = 0x0000;
 const TAG = 'InspectorTreeSerializeTool';
 
 export default namespace inspector {
    loadLibrary("inspector_ani");
    
    export function getInspectorTree(): RecordData {
        let inspectorTree: string = getInspectorTreeNative();
        return InspectorTreeSerializeTool.parseNoThrow(inspectorTree);
    }
    
    export native function createComponentObserver(id: string | int): ComponentObserver;
    native function deleteComponentObserver(ptr: long): string;
    export native function getInspectorByKey(id: string): string;
    export native function sendEventByKey(id: string, action: int, params: string): boolean;
    native function getInspectorTreeNative(): string;
    export native function getFilteredInspectorTree(filters?: Array<string>): string;
    export native function getFilteredInspectorTreeById(id: string, depth: int, filters?: Array<string>): string;

    class Cleaner {
        private ptr: long = 0;
        constructor(ptr: long) {
            this.ptr = ptr;
        }
        public clean(): void {
            deleteComponentObserver(this.ptr)
        }
    }

    export function callback(cleaner: Cleaner): void {
        cleaner.clean()
    }

    let destroyRegister = new FinalizationRegistry<Cleaner>(callback)

    export class ComponentObserver
    {
        private nativeComponentObserver:long = 0;
        private cleaner: Cleaner | null = null;
        constructor(nativeAddr:long) {
            if (this.nativeComponentObserver == 0) {
                this.nativeComponentObserver = nativeAddr;
            }
            this.registerCleaner(nativeAddr)
        }

        registerCleaner(ptr: long): void {
            this.cleaner = new Cleaner(ptr);
            destroyRegister.register(this, this.cleaner!, this);
        }

        unregisterCleaner(): void {
            destroyRegister.unregister(this);
        }
        
        public onLayout(callback: VoidCallback): void {
            this.on('layout', callback);
        }
        
        public offLayout(callback?: VoidCallback): void {
            this.off('layout', callback);
        }
        
        public onDraw(callback: VoidCallback): void {
            this.on('draw', callback);
        }
        
        public offDraw(callback?: VoidCallback): void {
            this.off('draw', callback);
        }

        public onDrawChildren(callback: VoidCallback): void {
            this.on('drawChildren', callback);
        }
        
        public offDrawChildren(callback?: VoidCallback): void {
            this.off('drawChildren', callback);
        }

        public onLayoutChildren(callback: VoidCallback): void {
            this.on('layoutChildren', callback);
        }
        
        public offLayoutChildren(callback?: VoidCallback): void {
            this.off('layoutChildren', callback);
        }
        
        public native on(type: string, callback: VoidCallback) : void;

        public native off(type: string, callback?: VoidCallback) : void;
    }
 }
 
class InspectorTreeSerializeTool {
    public static stringifyNoThrow(obj: Record<string, Object>): String {
        try {
            return JSON.stringify(obj as Object as Record<string, Any>);
        } catch (err) {
            hilog.error(DOMAIN_ID, TAG, `InspectorTreeSerializeTool.stringify error: ${err}`);
            return '';
        }
    }

    public static parseNoThrow(inspectorTree: string): RecordData {
        try {
            let jsonValue = JSON.parseJsonElement(inspectorTree);
            let res = InspectorTreeSerializeTool.jsonValue2Object(jsonValue);
            if (!(res instanceof Record)) {
                hilog.error(DOMAIN_ID, TAG, `InspectorTreeSerializeTool.parse not Record`);
                return new Record<string, Object>();
            }
            return res as Record<string, RecordData>;
        } catch (err) {
            hilog.error(DOMAIN_ID, TAG, `InspectorTreeSerializeTool.parse error: ${err}`);
            return new Record<string, Object>();
        }
    }

    private static jsonValue2Object(value: jsonx.JsonElement): RecordData {
        let vType: jsonx.JsonType = value.jsonType;
        if (vType === jsonx.JsonType.JsonString) {
            return value.asString();
        } else if (vType === jsonx.JsonType.JsonNumber) {
            return value.asDouble();
        } else if (vType === jsonx.JsonType.JsonTrue) {
            return new Boolean(true);
        } else if (vType === jsonx.JsonType.JsonFalse) {
            return new Boolean(false);
        } else if (vType === jsonx.JsonType.JsonNull) {
            return null;
        } else if (vType === jsonx.JsonType.JsonArray) {
            let values: Array<jsonx.JsonElement> = value.asArray();
            let result: Array<RecordData> = new Array<RecordData>();
            for (let i: int = 0; i < values.length; i++) {
                result.push(InspectorTreeSerializeTool.jsonValue2Object(values[i]));
            }
            return result;
        } else if (vType === jsonx.JsonType.JsonObject) {
            let iterVal: IterableIterator<[string, jsonx.JsonElement]> = value.$_iterator();
            let result: Record<string, RecordData> = new Record<string, RecordData>();
            for (let t of iterVal) {
                result[t[0]] = InspectorTreeSerializeTool.jsonValue2Object(t[1]);
            }
            return result;
        } else {
            throw new TypeError('unknown JSONElement type');
        }
    }
}
 
 export const GETINSPECTORBYKEY = inspector.getInspectorByKey;
 export const GETINSPECTORTREE = inspector.sendEventByKey;
 export const SENDEVENTBYKEY = inspector.getInspectorTree;
