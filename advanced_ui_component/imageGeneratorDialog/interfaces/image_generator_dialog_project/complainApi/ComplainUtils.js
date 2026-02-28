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
import util from "@ohos.util";
export class UploadCountVo {
    constructor() {
        this.canUploadCount = 5;
        this.limit = 5;
    }
}
export class ComplainMediaService {
    static getFileSuffixFilters() {
        let fileSuffixFilters = ComplainMediaService.IMAGE_SUFFIX.toString() + ',' + ComplainMediaService.VIDEO_SUFFIX.toString();
        return fileSuffixFilters;
    }
}
ComplainMediaService.IMAGE_SUFFIX = ['bmp', 'jpg', 'jpeg', 'png', 'gif', '3gp', 'mpg', 'mpe', 'mng', 'asf', 'wmv', 'wmx', 'wvx', 'ts', 'rv', 'mkv',
    'webp', 'heic', 'heif'];
ComplainMediaService.VIDEO_SUFFIX = ['mp4', 'avi', 'mov', 'wmv', 'movie', 'rmvb', 'flv', 'mkv'];
export class ConfigVo {
    constructor() {
        this.isFullPage = false;
        this.topPadding = 0;
        this.aiBarHeight = 0;
        this.sidePadding = 0;
        this.keyBoardHeight = 0;
        this.bottomPadding = 0;
        this.windowIsActive = true;
        this.subWindowName = '';
    }
}
ConfigVo.bundleName = '';
export function generateUUID() {
    return util.generateRandomUUID(true).replace(new RegExp('-', 'g'), '');
}