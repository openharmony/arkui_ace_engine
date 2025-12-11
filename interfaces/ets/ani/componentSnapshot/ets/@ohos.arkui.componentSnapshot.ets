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

import image from '@ohos.multimedia.image';
import { BusinessError, AsyncCallback } from '@ohos.base';
import { CustomBuilder, DynamicRangeMode } from '@ohos.arkui.component';
import { ComponentContent } from '@ohos.arkui.node';
import colorSpaceManager from '@ohos.graphics.colorSpaceManager';

export default namespace componentSnapshot {

    loadLibrary("componentSnapshot_ani");

    export enum SnapshotRegionMode {
        COMMON,
        LOCALIZED,
        NO_REGION
    };
    
    export interface LocalizedSnapshotRegion {
        start: double
        top: double
        end: double
        bottom: double
    }

    export interface SnapshotRegion {
        left: double
        right: double
        top: double
        bottom: double
    }

    export type SnapshotRegionType = SnapshotRegion | LocalizedSnapshotRegion;

    export interface ColorModeOptions {  
        colorSpace?: colorSpaceManager.ColorSpace
        isAuto?: boolean
    }

    export interface DynamicRangeModeOptions {
        dynamicRangeMode?: DynamicRangeMode
        isAuto?: boolean
    }

    export interface SnapshotOptions {
        scale?: double
        waitUntilRenderFinished?: boolean
        region?: SnapshotRegionType
        colorMode?: ColorModeOptions
        dynamicRangeMode?: DynamicRangeModeOptions
    }

    export native function get(id: string, callback: AsyncCallback<image.PixelMap>, options?: SnapshotOptions): void;
    export native function get(id: string, options?: SnapshotOptions): Promise<image.PixelMap> | null;
    export native function getSync(id: string, options?: SnapshotOptions): image.PixelMap | null;
    export native function getWithUniqueId(uniqueId: number, options?: SnapshotOptions): Promise<image.PixelMap> | null;
    export native function getSyncWithUniqueId(uniqueId: number, options?: SnapshotOptions): image.PixelMap;
}