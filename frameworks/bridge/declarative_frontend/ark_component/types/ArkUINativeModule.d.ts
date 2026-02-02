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
/// <reference path="index.d.ts" />
declare class ArkUINativeModule {
    // global methods
    static getFrameNodeById(elmtId: number): KNode;
    static getFrameNodeByUniqueId(uniqueId: number): KNode;
    static getPageInfoByUniqueId(uniqueId: number): any;
    static getNavigationInfoByUniqueId(uniqueId: number): NavigationInfo;
    static getUIState(node: KNode): any;
    static setSupportedUIState(states: Array<string>): void;
    static getFrameNodeByKey(nodeKey: string): any;
    static getAttachedFrameNodeById(nodeId: number): any;
    static requireDynamicSyncScene(nodeId: number, sceneName: string): boolean;
    static setFrameRateRange(minFrameRate: number, maxFrameRate: number): void;
    static setMarqueeFrameRateRange(): void;
    static loadNativeModule(moduleName: string): any;
}

declare function getArkUINativeModule(): ArkUINativeModule;