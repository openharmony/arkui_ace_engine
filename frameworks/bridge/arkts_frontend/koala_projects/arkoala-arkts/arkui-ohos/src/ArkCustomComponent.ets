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
    ConstraintSizeOptions,
    GeometryInfo,
    Layoutable,
    Measurable,
    SizeResult,
} from "#generated"
import { PeerNode } from "./PeerNode"
import { Theme } from '@ohos/arkui/theme';
import { int32 } from '@koalaui/common';

/**
 * This is basically the CustomComponent
 */
export interface ArkCustomComponent {
    setPeer(peer: PeerNode): void
    getPeer(): PeerNode | undefined

    // Life cycle
    /** @memo */
    build(): void;
    aboutToAppear(): void;
    aboutToDisappear(): void;
    onDidBuild(): void;
    onCleanup(): void;

    // Page life cycle
    onPageShow(): void
    onPageHide(): void
    onBackPress(): boolean;
    pageTransition(): void;
    onNewParam(param: object | undefined | null): void;

    // Custom layout
    onPlaceChildren(selfLayoutInfo: GeometryInfo, children: Array<Layoutable>, constraint: ConstraintSizeOptions): void
    onMeasureSize(selfLayoutInfo: GeometryInfo, children: Array<Measurable>, constraint: ConstraintSizeOptions): SizeResult

    // Theme
    onWillApplyTheme(theme: Theme): void
    onGlobalThemeChanged(theme: Theme): void
    setThemeScopeId(themeScopeId: int32): void
    getThemeScopeId(): int32 | undefined

    // Form recover
    onFormRecycle(): string
    onFormRecover(statusData: string): void;

    // dump info
    onDumpInspector(): string;

    readonly isCustomLayout: boolean;
}
