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
import { ComplainInfo } from '../../complainApi/ComplainInfo';
import { ComplainParams } from '../../complainApi/ComplainParams';
@Component
export declare struct complainSheetComponents {
    stack: NavPathStack;
    private webviewController;
    params: ComplainParams;
    fromSheet: boolean;
    @State
    mediaPreviewTitleVisible: boolean;
    @State
    complainInfo: ComplainInfo;
    @State
    customTitle: ResourceStr;
    @State
    title: ResourceStr;
    private isWeb;
    @State
    isShowLoading: boolean;
    private isFinished;
    private complainUrl;
    private configVo;
    private deviceType;
    private productEnvStr;
    private devEnvStr;
    private mirrorEnvStr;
    private tmpEnvStr;
    private canUploadCount;
    private context;
    private themeStorage;
    aboutToAppear(): Promise<void>;
    initComplainParams(): Promise<void>;
    initComplainInfo(): Promise<void>;
    refreshComplainUrl(): Promise<void>;
    init(): Promise<void>;
    selectFile(result: FileSelectorResult): Promise<void>;
    @Builder
    web(): void;
    private buildNavDestinationContent;
    back: () => boolean;
    build(): void;
}