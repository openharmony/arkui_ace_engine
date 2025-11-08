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
import { WatchFuncType, WatchFunc } from '../index';
import { UIContextImpl } from 'arkui/base/UIContextImpl';
import { UIContextUtil } from 'arkui/base/UIContextUtil';

export class InteropWatchFunc extends WatchFunc {
    checkThread: () => boolean = () => {
        throw new Error('not implement');
    };

    constructor(func: WatchFuncType) {
        super(func);
        let uiContext: UIContextImpl = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
        let instanceId = uiContext.getInstanceId();
        this.checkThread = (): boolean => uiContext.checkThread(instanceId);
    }

    execute(propertyName: string): void {
        if (!this.checkThread()) {
            throw new Error('prohibited to modify a state which binds to UI when not in UI thread');
        }
        this.func_(propertyName);
    }
}
