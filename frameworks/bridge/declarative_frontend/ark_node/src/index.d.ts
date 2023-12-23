/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

declare class UIContext {
    instanceId_: number;
}

declare interface TouchEvent {
}

declare type UpdateFunc = (elmtId: number, isFirstRender: boolean) => void;

interface UpdateFuncRecord {

    updateFunc: UpdateFunc;
    componentName: string;
    node?: object;
}

declare function wrapBuilder<Args extends Object[]>(
    builder: (...args: Args) => void
): WrappedBuilder<Args>;

declare class WrappedBuilder<Args extends Object[]> {
    builder: (...args: Args) => void;
    constructor(builder: (...args: Args) => void);
}

declare class ViewStackProcessor {
    static AllocateNewElmetIdForNextComponent(): number;
    static StartGetAccessRecordingFor(elmId: number): void;
    static StopGetAccessRecording(): void;
}

declare class __JSScopeUtil__ {
    static syncInstanceId(instanceId: number): void;
    static restoreInstanceId(): void;
}

declare interface Size {
    width: number;
    height: number;
}

declare abstract class ViewPU { }
