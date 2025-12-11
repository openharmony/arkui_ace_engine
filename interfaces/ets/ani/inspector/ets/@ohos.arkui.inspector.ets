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
 const TAG = 'InspetorTreeSerializeTool';
 
 export default namespace inspector {
    loadLibrary("inspector_ani");
    
    export function getInspectorTree(): RecordData {
        let inspectorTree: string = getInspectorTreeNative();
        return InspetorTreeSerializeTool.parseNoThrow(inspectorTree);
    }
    
    export native function createComponentObserver(id: string): ComponentObserver | undefined;
    export native function getInspectorByKey(id: string): string;
    export native function sendEventByKey(id: string, action: int, params: string): boolean;
    native function getInspectorTreeNative(): string;
    export native function getFilteredInspectorTree(filters?: Array<string>): string;
    export native function getFilteredInspectorTreeById(id: string, depth: int, filters?: Array<string>): string;

    export class ComponentObserver
    {
        private nativeComponentObserver:long = 0;
        
        constructor(nativeAddr:long) {
            if (this.nativeComponentObserver == 0) {
                this.nativeComponentObserver = nativeAddr;
            }
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
        
        public native on(type: string, callback: VoidCallback) : void;

        public native off(type: string, callback?: VoidCallback) : void;
    }
 }
 
 class InspetorTreeSerializeTool {
    public static stringifyNoThrow(obj: Record<string, Object>): String {
        try {
            return JSON.stringify(obj as Object as Record<string, NullishType>);
        } catch (err) {
            hilog.error(DOMAIN_ID, TAG, `InspetorTreeSerializeTool.stringify error: ${err}`);
            return '';
        }
    }

    public static parseNoThrow(inspectorTree: string): RecordData {
        try {
            let jsonValue = JSONParser.parse(inspectorTree);
            let res = InspetorTreeSerializeTool.jsonValue2Object(jsonValue);
            if (!(res instanceof Record)) {
                hilog.error(DOMAIN_ID, TAG, `InspetorTreeSerializeTool.parse not Record`);
                return new Record<string, Object>();
            }
            return res as Record<string, RecordData>;
        } catch (err) {
            hilog.error(DOMAIN_ID, TAG, `InspetorTreeSerializeTool.parse error: ${err}`);
            return new Record<string, Object>();
        }
    }

    private static jsonValue2Object(value: JSONValue): RecordData {
        if (value instanceof JSONString) {
            return value.value;
        } else if (value instanceof JSONNumber) {
            return new Double(value.value);
        } else if (value instanceof JSONTrue) {
            return new Boolean(true);
        } else if (value instanceof JSONFalse) {
            return new Boolean(false);
        } else if (value instanceof JSONNull) {
            return null;
        } else if (value instanceof JSONArray) {
            let obj = value as JSONArray;
            let values = obj.values;
            let result: Array<RecordData> = new Array<RecordData>();
            for (let i: int = 0; i < values.length; i++) {
                result.push(InspetorTreeSerializeTool.jsonValue2Object(values[i]));
            }
            return result;
        } else if (value instanceof JSONObject) {
            let obj = value as JSONObject;
            let keys: Array<JSONString> = obj.keys_;
            let values: Array<JSONValue> = obj.values;
            let result: Record<string, RecordData> = new Record<string, RecordData>();
            for (let i: int = 0; i < keys.length; i++) {
                result[keys[i].value] = InspetorTreeSerializeTool.jsonValue2Object(values[i]);
            }
            return result;
        } else {
            throw new TypeError('unknown JSONValue');
        }
    }
 }
 
 export const GETINSPECTORBYKEY = inspector.getInspectorByKey;
 export const GETINSPECTORTREE = inspector.sendEventByKey;
 export const SENDEVENTBYKEY = inspector.getInspectorTree;