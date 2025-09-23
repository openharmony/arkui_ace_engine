/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { KPointer } from "@koalaui/interop"
import { NavigationTitleOptions, NavigationMenuOptions, NavigationMenuItem, NavPathStack, ToolbarItem, CustomBuilder, ResourceStr, NavigationToolbarOptions, NavigationCommonTitle, NavigationCustomTitle } from "../component"
import { SymbolGlyphModifier } from "../SymbolGlyphModifier"
import { Resource } from "global.resource"
import { PixelMap } from "#external"
import { NavigationHandWrittenImpl } from "./NavigationHandWrittenImpl"

export function hookNavigationTitleImpl(node: KPointer, value: ResourceStr | CustomBuilder | NavigationCommonTitle |
    NavigationCustomTitle | undefined, options?: NavigationTitleOptions) {
    NavigationHandWrittenImpl.TitleImpl(node, value, options)
}

export function hookNavigationBackButtonIconImpl(node: KPointer, value: string | PixelMap | Resource | SymbolGlyphModifier |
    undefined, accessibilityText?: ResourceStr) {
    NavigationHandWrittenImpl.BackButtonIconImpl(node, value, accessibilityText)
}

export function hookNavigationHideTitleBarImpl(node: KPointer, value: boolean | undefined, animated?: boolean) {
    NavigationHandWrittenImpl.HideTitleBarImpl(node, value, animated)
}

export function hookNavigationMenusImpl(node: KPointer, value: Array<NavigationMenuItem> | CustomBuilder | undefined,
    options?: NavigationMenuOptions) {
    NavigationHandWrittenImpl.MenusImpl(node, value, options)
}

export function hookNavigationToolbarConfigurationImpl(node: KPointer, value: Array<ToolbarItem> | CustomBuilder | undefined,
    options?: NavigationToolbarOptions) {
    NavigationHandWrittenImpl.ToolbarConfigurationImpl(node, value, options)
}

export function hookNavigationSetNavigationOptionsImpl(node: KPointer, value: NavPathStack) {
    NavigationHandWrittenImpl.SetNavigationOptionsImpl(node, value)
}