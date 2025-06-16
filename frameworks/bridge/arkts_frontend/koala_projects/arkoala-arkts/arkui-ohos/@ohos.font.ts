/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { Resource } from "global.resource"
import { GlobalScope_ohos_font } from "arkui/component/arkui-external"

export namespace font {

export interface FontOptions {
    familyName: string | Resource;
    familySrc: string | Resource;
}

export interface FontInfo {
    path: string;
    postScriptName: string;
    fullName: string;
    family: string;
    subfamily: string;
    weight: number;
    width: number;
    italic: boolean;
    monoSpace: boolean;
    symbolic: boolean;
}

export interface UIFontFallbackInfo {
    language: string;
    family: string;
}

export interface UIFontAliasInfo {
    name: string;
    weight: number;
}

export interface UIFontAdjustInfo {
    weight: number;
    to: number;
}

export interface UIFontGenericInfo {
    family: string;
    alias: Array<UIFontAliasInfo>;
    adjust: Array<UIFontAdjustInfo>;
}

export interface UIFontFallbackGroupInfo {
    fontSetName: string;
    fallback: Array<UIFontFallbackInfo>;
}

export interface UIFontConfig {
    fontDir: Array<string>;
    generic: Array<UIFontGenericInfo>;
    fallbackGroups: Array<UIFontFallbackGroupInfo>;
}

function getUIFontConfig() : UIFontConfig {
    return GlobalScope_ohos_font.getInternalUIFontConfig();
}
}
export type FontOptions = font.FontOptions;
export type FontInfo = font.FontInfo;
export type UIFontFallbackInfo = font.UIFontFallbackInfo;
export type UIFontAliasInfo = font.UIFontAliasInfo;
export type UIFontAdjustInfo = font.UIFontAdjustInfo;
export type UIFontGenericInfo = font.UIFontGenericInfo;
export type UIFontFallbackGroupInfo = font.UIFontFallbackGroupInfo;
export type UIFontConfig = font.UIFontConfig;
