/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
import photoAccessHelper from "@ohos.file.photoAccessHelper";
import hilog from "@ohos.hilog";
const TAG = 'PickerUtilOptions';
const DOMAIN = 0x0f5c;
export class PickerUtil {
    static async selectFilesByPicker(options) {
        let reSelectedUris = [];
        try {
            reSelectedUris = await PickerUtil.photoFileSelect(options, reSelectedUris);
        }
        catch (e) {
            hilog.error(DOMAIN, TAG, `Picker failed.`, e);
        }
        return reSelectedUris;
    }
    static async photoFileSelect(options, reSelectedUris) {
        const photoSelectOptions = new photoAccessHelper.PhotoSelectOptions();
        photoSelectOptions.MIMEType = options.mimeType;
        photoSelectOptions.subWindowName = options.subWindowName;
        photoSelectOptions.maxPhotoSelectNumber = options.maxSelectNumber;
        photoSelectOptions.preselectedUris = options.preSelectedUris;
        const photoViewPicker = new photoAccessHelper.PhotoViewPicker();
        const photoSelectResult = await photoViewPicker.select(photoSelectOptions);
        if (photoSelectResult.photoUris.length !== 0) {
            reSelectedUris = photoSelectResult.photoUris;
        }
        else {
            reSelectedUris = options.preSelectedUris;
        }
        return reSelectedUris;
    }
}