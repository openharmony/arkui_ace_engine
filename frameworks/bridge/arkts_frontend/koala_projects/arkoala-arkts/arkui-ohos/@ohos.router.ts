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

import { Router } from "arkui/base"
import { PeerNode } from "arkui/PeerNode"
import { UserViewBuilder } from "arkui/UserView"
import { ComputableState, IncrementalNode } from "@koalaui/runtime"
import { UIContextImpl } from "arkui/base/UIContextImpl"
import { UIContextUtil } from "arkui/base/UIContextUtil"

namespace router {
    export interface RouterOptions {
        url: string
        params?: Object
        recoverable?: boolean
    }
    
    export enum RouterMode {
        Standard,
        Single
    }

    export interface RouterState {
        index: int;
        name: string;
        path: string;
        params: Object;
    }

    export interface EnableAlertOptions {
        message: string;
    }

    export interface NamedRouterOptions {
        name: string;
        params?: Object;
        recoverable?: boolean;
    }

    export function error(prefix: string, e: Object|null|undefined): string {
        throw new Error("TBD")
    }

    let pageEntries: Map<string, string>

    export function setRouter(routerImp: Router): void {
        let uiContext: UIContextImpl = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
        uiContext.setRouter(routerImp)
    }

    export function getParams(): Object {
        throw new Error("TBD")
    }

    export function clear(): void {
        throw new Error("TBD")
    }

    export function getLength(): string {
        throw new Error("TBD")
    }

    export function getState(): RouterState {
        throw new Error("TBD")
    }

    export function getStateByIndex(index: int): RouterState | undefined {
        throw new Error("TBD")
    }

    export function getStateByUrl(url: string): Array<RouterState> {
        throw new Error("TBD")
    }

    export function showAlertBeforeBackPage(options: router.EnableAlertOptions): void {
        throw new Error("TBD")
    }

    export function hideAlertBeforeBackPage(): void {
        throw new Error("TBD")
    }

    export function pushUrl(options: RouterOptions): void {
        throw new Error("TBD")
    }

    export function replaceUrl(options: RouterOptions): void {
        throw new Error("TBD")
    }

    export function push(options: RouterOptions): void {
        throw new Error("TBD")
    }

    export function back(options?: RouterOptions): void {
        throw new Error("TBD")
    }

    export function UpdateVisiblePagePeerNode(node: PeerNode, index: int = -1): void {
        throw new Error("TBD")
    }

    export function getStateRoot(): ComputableState<IncrementalNode> {
        throw new Error("TBD")
    }

    export function runPage(options: RouterOptions, builder: UserViewBuilder): void {
        let uiContext : UIContextImpl = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
        const globalRouterImpl = uiContext.getRouter().getRouter();
        globalRouterImpl.runStartPage(options, builder);
    }
}

export default router