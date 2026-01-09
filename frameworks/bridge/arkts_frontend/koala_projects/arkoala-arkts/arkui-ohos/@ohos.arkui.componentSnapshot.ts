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

import { AsyncCallback } from 'arkui/base';
import { PixelMap } from "#external";
import { DynamicRangeMode } from 'arkui/component/image';
import colorSpaceManager from '@ohos.graphics.colorSpaceManager';

export declare namespace componentSnapshot {
    export interface SnapshotRegion {
        left: double;
        right: double;
        top: double;
        bottom: double;
    }
    export interface LocalizedSnapshotRegion {
        start: double;
        end: double;
        top: double;
        bottom: double;
    }
    export type SnapshotRegionType = SnapshotRegion | LocalizedSnapshotRegion;
    export interface ColorModeOptions {
        colorSpace?: colorSpaceManager.ColorSpace;
        isAuto?: boolean;
    }
    export interface DynamicRangeModeOptions {
        dynamicRangeMode?: DynamicRangeMode;
        isAuto?: boolean;
    }
    export interface SnapshotOptions {
        scale?: double;
        waitUntilRenderFinished?: boolean;
        region?: SnapshotRegionType;
        colorMode?: ColorModeOptions;
        dynamicRangeMode?: DynamicRangeModeOptions;
    }
    export function get(callbackId: string, callback: AsyncCallback<PixelMap>, options?: SnapshotOptions): void;
    export function get(promiseId: string, options?: SnapshotOptions): Promise<PixelMap> | null;
    export function getSync(value: string, options?: SnapshotOptions): PixelMap | null;
    export function getWithUniqueId(uniqueIdValue: int, options?: SnapshotOptions): Promise<PixelMap> | null;
    export function getSyncWithUniqueId(uniqueIdValue: int, options?: SnapshotOptions): PixelMap;
}