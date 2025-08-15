/*
 * Copyright (C) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
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
/**
 * @file
 * @kit ArkUI
 */

export namespace image {

    export enum ResolutionQuality {
        LOW = 1,
        MEDIUM = 2,
        HIGH = 3
    }

    export interface PixelMap {
        readonly isEditable: boolean
        readonly isStrideAlignment: boolean
        readPixelsToBufferSync(dst: ArrayBuffer): void
        writeBufferToPixels(src: ArrayBuffer): void
    }

    class PixelMapInner implements PixelMap {

        private nativeObj: long = 0;

        readonly isEditable: boolean = true
        readonly isStrideAlignment: boolean = true

        constructor(context: long) {
            if (this.nativeObj == 0) {
                this.nativeObj = context;
            }
        }

        readPixelsToBufferSync(dst: ArrayBuffer): void {
            console.log(`call PixelMapInner.readPixelsToBufferSync(...)`)
        }

        writeBufferToPixels(src: ArrayBuffer): void {
            console.log(`call PixelMapInner.writeBufferToPixels(...)`)
        }
    }
}