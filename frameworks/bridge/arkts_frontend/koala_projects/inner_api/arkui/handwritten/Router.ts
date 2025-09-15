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

import { PeerNode } from 'arkui.PeerNode';
import { int32 } from '@koalaui/compat';

export type PageClassNameResolver = (page: string) => string | undefined;

export declare class PageInfo {
    public depth: number;
    public page: string;
    constructor(depth: number, page: string);
}

export interface Router {
    provideClassNameResolver(resolver: PageClassNameResolver): void;

    push(url: string, params?: Map<string, Object>): Promise<void>;

    replace(url: string, params?: Map<string, Object>): Promise<void>;

    back(url?: string, params?: Map<string, Object>): Promise<void>;

    clear(): void;

    getParam(key: string): Object | undefined;

    depth: number;

    pageInfo: PageInfo;

    onPageTransitionEnd(pageId: int32): void;

    UpdateVisiblePagePeerNode(node: PeerNode, index?: number): void;
}
