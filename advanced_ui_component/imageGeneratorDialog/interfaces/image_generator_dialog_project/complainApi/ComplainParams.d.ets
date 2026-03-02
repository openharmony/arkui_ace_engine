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
import uiExtensionHost from "@ohos.uiExtensionHost";
import window from "@ohos.window";
import { ComplainPageContext } from "./ComplainUtils";
import { IGrsClient } from "./IGrsClient";
export declare class EmphasizedColor {
    backgroundLight?: string;
    backgroundDark?: string;
    textLight?: string;
    textDark?: string;
}
export declare enum RefreshATEnum {
    PREFER_CACHE = 0,
    REMOTE = 1
}
export declare class ComplainParams {
    sheetMode?: SheetMode;
    appId: string;
    customTitle?: Resource;
    context?: ComplainPageContext;
    pathInfo: NavPathStack;
    setComplainAccessToken?: (mode?: RefreshATEnum) => Promise<string>;
    SetComplainSessionId?: () => Promise<string>;
    afterSubmit?: (jsonString?: string) => void;
    onBackPressed?: () => void;
    onHistoryBack?: () => void;
    sceneId: string;
    subSceneId: string;
    deviceId?: string;
    jwtToken?: string;
    channelId?: string;
    grsClien?: IGrsClient;
    emphasizedColor?: EmphasizedColor;
    theme?: Record<string, string>;
    fileList?: string[];
    colorMode?: ColorMode;
    businessKey?: string;
    disableContactInfo?: boolean;
    disableUserUpload?: boolean;
    additionalContext: Record<string, string>;
    windowStage?: window.WindowStage;
    windowProxy?: uiExtensionHost.UIExtensionHostWindowProxy;
    isFullPage?: boolean;
    fromSheet?: boolean;
    topPadding?: number;
    hdsCloseBindSheet?: Callback<void>;
}
export declare const PAGE_COMPLAIN = "WISE_SUPPORT_COMPLAIN";