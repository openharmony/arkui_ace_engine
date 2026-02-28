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
import { ComplainMediaService } from "./ComplainUtils";
import { PickerUtil } from "./PickerUtil";
export class ComplainFileSelectUtil {
    static async selectFiles(canUploadCount, configVo) {
        const fileSuffixFilters = [ComplainMediaService.getFileSuffixFilters()];
        const pickerUtilOptions = {
            maxSelectNumber: canUploadCount,
            context: configVo.context,
            subWindowName: configVo.subWindowName,
            mimeType: photoAccessHelper.PhotoViewMIMETypes.IMAGE_VIDEO_TYPE,
            preSelectedUris: [],
            fileSuffixFilters: fileSuffixFilters
        };
        return await PickerUtil.selectFilesByPicker(pickerUtilOptions);
    }
}