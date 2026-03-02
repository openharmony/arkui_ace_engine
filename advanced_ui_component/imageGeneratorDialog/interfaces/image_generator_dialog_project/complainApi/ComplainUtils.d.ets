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
import common from "@ohos.app.ability.common";
import uiExtensionHost from "@ohos.uiExtensionHost";
import window from "@ohos.window";
export type ComplainPageContext = common.UIAbilityContext | common.UIExtensionContext;
export declare class UploadCountVo {
    canUploadCount: number;
    limit: number;
}
export declare class ComplainMediaService {
    private static readonly IMAGE_SUFFIX;
    private static readonly VIDEO_SUFFIX;
    static getFileSuffixFilters(): string;
}
export declare class ConfigVo {
    windowStage?: window.WindowStage;
    windowProxy?: uiExtensionHost.UIExtensionHostWindowProxy;
    isFullPage?: boolean;
    topPadding: number;
    aiBarHeight: number;
    sidePadding: number;
    keyBoardHeight: number;
    static bundleName: string;
    bottomPadding: number;
    windowIsActive: boolean;
    context: ComplainPageContext;
    subWindowName: string;
}
export declare function generateUUID(): string;