/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
class stateMgmtDFX {

    // enable profile
    public static enableProfiler_: boolean = false;
    public static inRenderingElementId_: Array<number> = new Array<number>();
}

function setProfilerStatus(profilerStatus: boolean): void {
    stateMgmtConsole.warn(`${profilerStatus ? `start` : `stop`} stateMgmt Profiler`);
    stateMgmtDFX.enableProfiler_ = profilerStatus;
}
type PropertyDependenciesInfo = {
    mode: string,
    trackPropertiesDependencies: MapItem<string, Array<ElementType | number | string>>[],
    propertyDependencies: Array<ElementType>
}

type ElementType = {
    elementId: number,
    elementTag: string,
    isCustomNode: boolean,
}

// Data struct send to profiler or Inspector
type ViewPUInfo = { componentName: string, id: number };
type ObservedPropertyInfo<T> = {
    decorator: string, propertyName: string, value: any, id: number, changeId?: number, inRenderingElementId?: number,
    changedTrackPropertyName?: string | undefined,
    dependentElementIds: PropertyDependenciesInfo,
    owningView?: ViewPUInfo, syncPeers?: ObservedPropertyInfo<T>[]
};

class DumpInfo {
    public viewInfo?: ViewPUInfo;
    public observedPropertiesInfo: ObservedPropertyInfo<any>[] = []
}