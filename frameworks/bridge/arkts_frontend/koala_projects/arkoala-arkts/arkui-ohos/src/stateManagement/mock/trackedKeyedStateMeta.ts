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

import { MutableKeyedStateMeta } from '../base/mutableStateMeta';
import { IObservedObject } from '../decorator';
import { int32 } from '@koalaui/common';

export class TestMutableKeyedStateMeta extends MutableKeyedStateMeta {

    constructor(info: string, observed?: IObservedObject) {
        super(info, observed);
    }

    private refsMap: Map<string, int> = new Map<string, int>();
    private fireChangeMap: Map<string, int32> = new Map<string, int32>();

    public override addRef(key: string): void {
        if (this.refsMap.get(key) === undefined) {
            this.refsMap.set(key, 0);
        }
        this.refsMap.set(key, this.refsMap.get(key)! + 1);

        super.addRef(key);
    }


    public override fireChange(key: string): void {
        if (this.fireChangeMap.get(key) === undefined) {
            this.fireChangeMap.set(key, 0);
        }
        this.fireChangeMap.set(key, this.fireChangeMap.get(key)! + 1);

        super.fireChange(key);
    }

    public getFireChangeCnt(key: string): int32 {
        const dep = this.fireChangeMap.get(key);
        return dep ?? 0;
    }

    public getRefCnt(key: string): int32 {
        return this.refsMap.get(key) ?? 0;
    }
}
