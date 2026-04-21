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

import { int32 } from "@koalaui/common"
import { UIContext } from "@ohos/arkui/UIContext"
import { ArkUIAniModule } from "arkui.ani";

export class UIContextUtil {
    static contextMap_: Map<int32, UIContext> = new Map<int32, UIContext>();
    public static envContextMap: Map<int32, Map<string, Object>> = new Map<int32, Map<string, Object>>();

    static getOrCreateCurrentUIContext(): UIContext {
        let id: int32 = ArkUIAniModule._Common_Get_Current_InstanceId();
        return UIContextUtil.getOrCreateUIContextById(id);
    }

    static getCurrentInstanceId(): int32 {
        return ArkUIAniModule._Common_Get_Current_InstanceId();
    }

    static getOrCreateUIContextById(instanceId: int32): UIContext {
        let context = UIContextUtil.getUIContextById(instanceId);
        if (context === undefined) {
            context = new UIContext(instanceId);
            UIContextUtil.addUIContext(instanceId, context);
        }
        return context;
    }

    static isAvailableCountMap_: Map<int32, int32> = new Map<int32, int32>();
    static availableInstanceIds_: Set<int32> = new Set<int32>();

    static addAvailableInstanceId(instanceId: int32): void {
        if (!UIContextUtil.isAvailableCountMap_.has(instanceId)) {
            UIContextUtil.isAvailableCountMap_.set(instanceId, 1);
        }
        const value = UIContextUtil.isAvailableCountMap_.get(instanceId);

        if (value === 1){
            if (instanceId >= 0) {
                UIContextUtil.isAvailableCountMap_.set(instanceId, 0);
                UIContextUtil.availableInstanceIds_.add(instanceId);
            }
        } else if (value === 0) {
            UIContextUtil.isAvailableCountMap_.set(instanceId, 1);
        }  
    }

    static removeAvailableInstanceId(instanceId: int32): void {
        const value = UIContextUtil.isAvailableCountMap_.get(instanceId);
        if (value === 0){
            if (instanceId >= 0) {
                UIContextUtil.isAvailableCountMap_.set(instanceId, 1);
                UIContextUtil.availableInstanceIds_.delete(instanceId);
            }
        } else if (value === 1) {
            UIContextUtil.isAvailableCountMap_.set(instanceId, 0);
        }
    }

    static addUIContext(instanceId: int32, uiContext: UIContext): void {
        UIContextUtil.contextMap_.set(instanceId, uiContext);
    }

    static removeUIContext(instanceId: int32): void {
        UIContextUtil.contextMap_.delete(instanceId);
    }

    static getUIContextById(instanceId: int32): UIContext | undefined {
        if (UIContextUtil.contextMap_.has(instanceId)) {
            return UIContextUtil.contextMap_.get(instanceId);
        }
        return undefined;
    }
    static checkCurrentThread(): boolean {
        let instanceId = UIContextUtil.getCurrentInstanceId();
        return ArkUIAniModule._CheckIsUIThread(instanceId) !== 0;
    }
    static resolveUIContext(): Array<int> {
        return ArkUIAniModule._ResolveUIContext();
    }
    static setEnvContextById(instanceId: int32, envValue: string, envProperty: Object): void {
        if (!UIContextUtil.envContextMap.has(instanceId)) {
            const tempEnvMap: Map<string, Object> = new Map<string, Object>();
            tempEnvMap.set(envValue, envProperty);
            UIContextUtil.envContextMap.set(instanceId, tempEnvMap);
        } else {
            UIContextUtil.envContextMap.get(instanceId)!.set(envValue, envProperty);
        }
    }
    static getEnvContextById(instanceId: int32, envValue: string): Object | undefined {
        if (!UIContextUtil.envContextMap.has(instanceId) ||
            !UIContextUtil.envContextMap.get(instanceId)!.has(envValue)) {
            return undefined;
        }
        return UIContextUtil.envContextMap.get(instanceId)!.get(envValue);
    }
}