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

import imageGeneration from '@ohos.arkui.intelligence.imageGeneration';
import { styleItem } from "./CanvasFramework";
import { CanvasLayoutDirection } from "../types/Declaration";
@ComponentV2
export declare struct SelectFuncArea {
    @Param
    @Require
    readonly styles?: Array<imageGeneration.ImageStyle>;
    private tabBarDefaultBgColor;
    @Local
    tabBarStyleBgColor: ResourceColor;
    @Local
    styleItems: Array<styleItem>;
    @Param
    @Require
    readonly imageInfoArr: Array<imageGeneration.ImageItem>;
    @Param
    @Require
    readonly imageMatrixArr: number[][];
    @Provider('functionAreaSelectedIndex')
    selectedIndex: number;
    @Event
    setImgCounts: (count: number) => void;
    @Consumer('globalLayoutDirection')
    curLayoutDirection: CanvasLayoutDirection;
    aboutToAppear(): void;
    build(): void;
}
