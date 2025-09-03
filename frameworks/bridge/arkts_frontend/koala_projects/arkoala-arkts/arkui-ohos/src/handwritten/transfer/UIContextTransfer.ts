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

import { UIContextImpl } from '../UIContextImpl';
import { int32 } from "@koalaui/common"

export class UIContextTransfer {

    static transferStatic(input: Any): Object {
        const instanceId = ESValue.wrap(input).getProperty("instanceId_").toNumber();
        let uiContext = new UIContextImpl(instanceId as int32);
        return uiContext;
    }
    static transferDynamic(input: Object): Any {
        let uiContextImpl = input as UIContextImpl;
        let instaceId = uiContextImpl.instanceId_;
        return UIContextTransfer.createDynamic(instaceId);
    }
    static createDynamic(instanceId: int32): Any {
        let global = ESValue.getGlobal();
        let uiContextCreateFunc = global.getProperty('__getUIContext__');
        let uiContextWrapper = uiContextCreateFunc.invoke(instanceId);
        return uiContextWrapper.unwrap();
    }
}