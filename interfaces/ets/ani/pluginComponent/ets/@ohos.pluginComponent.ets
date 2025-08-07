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
import Want from '@ohos.app.ability.Want';
import { AsyncCallback, BusinessError } from '@ohos.base';

interface PluginComponentTemplate {
    source: string;
    ability: string;
}
class PluginComponentTemplateImpl implements PluginComponentTemplate {
    source: string = "";
    ability: string = "";
}

export default namespace pluginComponentManager {
    loadLibrary("pluginComponent_ani");
    type KVObject = Record<string, Object>;
    type PushCallback = (errCode: int) => void;
    type RequestCallback = (errCode: int, componentTemplate: PluginComponentTemplate, data: KVObject, extraData: KVObject) => void;
    type OnPushEventCallback = (source: Want, template: PluginComponentTemplate, data: KVObject, extraData: KVObject) => void;
    type OnRequestEventCallback = (source: Want, name: string, data: KVObject) => RequestEventResult;
    
    export interface RequestCallbackParameters {
        componentTemplate: PluginComponentTemplate;
        data: KVObject;
        extraData: KVObject;
    }

    export interface RequestEventResult {
        template?: string;
        data?: KVObject;
        extraData?: KVObject;
    }

    export interface PushParameterForStage {
        target: Want;
        owner: Want;
        name: string;
        data: KVObject;
        extraData: KVObject;
        jsonPath?: string;
    }

    export interface RequestParameterForStage {
        target: Want;
        owner: Want;
        name: string;
        data: KVObject;
        jsonPath?: string;
    }

    export interface PushParameters {
        want: Want;
        name: string;
        data: KVObject;
        extraData: KVObject;
        jsonPath?: string;
    }

    export interface RequestParameters {
        want: Want;
        name: string;
        data: KVObject;
        jsonPath?: string;
    }

    export function push(param: PushParameters, callback: AsyncCallback<void>): void {
        return;
    }

    export function request(param: RequestParameters, callback: AsyncCallback<RequestCallbackParameters>): void {
        return;
    }

    export function push(param: PushParameterForStage, callback: AsyncCallback<void>): void {
        pushNative(param, (errCode: int) => {
            const businessErr = {
                code: errCode
            } as BusinessError
            callback(businessErr, undefined);
        });
    }

    export function request(param: RequestParameterForStage, callback: AsyncCallback<RequestCallbackParameters>): void {
        requestNative(param, (errCode: int, componentTemplate: PluginComponentTemplate, data: KVObject, extraData: KVObject) => {
            const businessErr = {
                code: errCode
            } as BusinessError
            callback(businessErr, {
                componentTemplate: componentTemplate,
                data: data,
                extraData: extraData
            } as RequestCallbackParameters)
        });
    }

    native function pushNative(param: PushParameterForStage, callback: PushCallback): void;
    native function requestNative(param: RequestParameterForStage, callback: RequestCallback): void;
    export native function on(eventType: string, callback: OnPushEventCallback | OnRequestEventCallback): void;
}

