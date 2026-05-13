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

import { int32 } from '@koalaui/common';
import { MutableState } from '@koalaui/runtime';
import { MutableStateMeta, MonitorTarget } from '../base/mutableStateMeta';
import { ObserveSingleton } from '../base/observeSingleton';
import { StateTracker } from '../tests/lib/stateTracker';

// TrackedMutableStateMeta is used only by the unit test framework
// (FactoryInternalImpl in mock/factoryInternal.ts).
export class TrackedMutableStateMeta extends MutableStateMeta {
    constructor(info: string, target?: MonitorTarget, metaDependency?: MutableState<int32>) {
        super(info, target, metaDependency);
    }

    public addRef(): void {
        const rc = ObserveSingleton.instance.renderingComponent;
        if (
            rc === ObserveSingleton.RenderingMonitor ||
            rc === ObserveSingleton.RenderingComputed ||
            rc === ObserveSingleton.RenderingPersistentStorage
        ) {
        } else {
            StateTracker.increaseRefCnt();
        }
        super.addRef();
    }

    public fireChange(): void {
        // Count every fireChange call so unit tests can verify behavior even
        // outside a render scope. The previous guard
        // (`if (this.shouldFireChange())`) only counted fires that had
        // registered render dependencies via the koalaui MutableState — those
        // are never present in non-render unit tests, so the counter stayed
        // at 0 regardless of how many fireChange calls actually executed.
        StateTracker.increaseFireChangeCnt();
        super.fireChange();
    }
}
