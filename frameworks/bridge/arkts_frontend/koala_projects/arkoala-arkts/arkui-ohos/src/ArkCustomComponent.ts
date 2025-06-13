/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

import {
    Theme,
    LayoutChild,
    ConstraintSizeOptions,
    GeometryInfo,
    Layoutable,
    Measurable,
    SizeResult,
    NavigationInfo,
    NavDestinationInfo,
    RouterPageInfo
} from "./generated"
import { UIContext } from "@ohos.arkui.UIContext"

/**
 * This is basically the CustomComponent, which doesn't extend CommonAttribute
 *
 * memo markup according to arkui-common/config/tsconfig.base.json
 *
 * "render": {
 *     "method": [
 *         "build",
 *         "pageTransition"
 *     ]
 * }
 */
export interface ArkCustomComponent {
    /** @memo */
    build(): void;
    aboutToAppear/* ? */(): void;
    aboutToDisappear/* ? */(): void;
    aboutToReuse/* ? */(params: Record<string, Object>): void;
    aboutToRecycle/* ? */(): void
    onWillApplyTheme/* ? */(theme: Theme): void
    onLayout/* ? */(children: Array<LayoutChild>, constraint: ConstraintSizeOptions): void
    onPlaceChildren/* ? */(selfLayoutInfo: GeometryInfo, children: Array<Layoutable>, constraint: ConstraintSizeOptions): void
    onMeasure/* ? */(children: Array<LayoutChild>, constraint: ConstraintSizeOptions): void
    onMeasureSize/* ? */(selfLayoutInfo: GeometryInfo, children: Array<Measurable>, constraint: ConstraintSizeOptions): SizeResult
    onPageShow/* ? */(): void
    onPageHide/* ? */(): void
    onFormRecycle/* ? */(): string
    onFormRecover/* ? */(statusData: string): void;
    onBackPress/* ? */(): boolean;
    /** @memo */
    pageTransition/* ? */(): void;
    getUIContext(): UIContext;
    getUniqueId(): number;
    queryNavDestinationInfo(): NavDestinationInfo | undefined;
    queryNavigationInfo(): NavigationInfo | undefined;
    queryRouterPageInfo(): RouterPageInfo | undefined;
    onDidBuild/* ? */(): void;
}

export class ArkCustomComponentImpl implements ArkCustomComponent {
    /** @memo */
    build(): void {
    }
    aboutToAppear(): void {
    }
    aboutToDisappear(): void {
    }
    aboutToReuse(params: Record<string, Object>): void {
    }
    aboutToRecycle(): void {
    }
    onWillApplyTheme(theme: Theme): void {
    }
    onLayout(children: Array<LayoutChild>, constraint: ConstraintSizeOptions): void {
    }
    onPlaceChildren(selfLayoutInfo: GeometryInfo, children: Array<Layoutable>, constraint: ConstraintSizeOptions): void {
    }
    onMeasure(children: Array<LayoutChild>, constraint: ConstraintSizeOptions): void {
    }
    onMeasureSize(selfLayoutInfo: GeometryInfo, children: Array<Measurable>, constraint: ConstraintSizeOptions): SizeResult {
        throw new Error("Unexpected use of base class method")
    }
    onPageShow(): void {
    }
    onPageHide(): void {
    }
    onFormRecycle(): string {
        throw new Error("Unexpected use of base class method")
    }
    onFormRecover(statusData: string): void {
    }
    onBackPress(): boolean {
        throw new Error("Unexpected use of base class method")
    }
    /** @memo */
    pageTransition(): void {
    }
    getUIContext(): UIContext {
        return new UIContext(100000);
    }
    getUniqueId(): number {
        throw new Error("Unexpected use of base class method")
    }
    queryNavDestinationInfo(): NavDestinationInfo | undefined {
        return undefined
    }
    queryNavigationInfo(): NavigationInfo | undefined {
        return undefined
    }
    queryRouterPageInfo(): RouterPageInfo | undefined {
        return undefined
    }
    onDidBuild(): void {
    }
}
