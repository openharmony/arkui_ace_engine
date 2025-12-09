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
import { UIContextImpl } from "./UIContextImpl";
import { ArkUIAniModule } from "arkui.ani";

export class UIContextUtil {
    static contextMap_: Map<int32, UIContext> = new Map<int32, UIContext>();

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
            context = new UIContextImpl(instanceId);
            UIContextUtil.addUIContext(instanceId, context);
        }
        return context;
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
}