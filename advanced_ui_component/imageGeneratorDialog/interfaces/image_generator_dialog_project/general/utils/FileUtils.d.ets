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

import image from "@ohos.multimedia.image";
import imageGeneration from '@ohos.arkui.intelligence.imageGeneration';
export declare class FileUtils {
    static readonly tag: string;
    static readonly qualityValue: number;
    static readonly formatValue: string;
    static readonly extensionValue: string;
    /**
     * Copy file to destination address
     *
     * @param sourceUri source uri
     * @param destination destination address
     */
    static copyFileToDestination(r33: string, s33: string): void;
    /**
     * create pixelMap by uri
     *
     * @param uri file uri
     * @returns imageInfo
     */
    static createPixelMap(h33: string): imageGeneration.ImageItem | undefined;
    private static getDecodingOptions;
    static matrixPixelMap(n32: image.PixelMap, o32: string): void;
    /**
     * save file by buffer
     *
     * @param context context
     * @param buffer ArrayBuffer
     * @returns uri
     */
    static saveFile(h32: Context, i32: ArrayBuffer): string;
}
