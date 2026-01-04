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

import { Router } from 'arkui/handwritten/Router';
import { PeerNode } from 'arkui/PeerNode';
declare namespace router {
    interface RouterOptions {
        url: string;
        params?: jsonx.JsonElement;
    }
    enum RouterMode {
        Standard = 0,
        Single = 1,
    }
    function registerPage(page: string, className: string): void;
    function error(prefix: string, e: Object | null | undefined): string;
    function setRouter(routerImp: Router): void;
    function getParams(): jsonx.JsonElement | undefined;
    function clear(): void;
    function pushUrl(options: RouterOptions): void;
    function push(options: RouterOptions): void;
    function back(options?: RouterOptions): void;
    function UpdateVisiblePagePeerNode(node: PeerNode, index?: number): void;
}
export default router;
