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
export interface Header { headerKey: string, headerValue: string }

export class WebResourceRequestPeer {
    constructor() {}
    getRequestHeader(): Array<Header> {
        throw new Error("[WebResourceRequestPeer.getRequestHeader] - method not implemented.")
    }
    getRequestUrl(): string {
        throw new Error("[WebResourceRequestPeer.getRequestUrl] - method not implemented.")
    }
    isRequestGesture(): boolean {
        throw new Error("[WebResourceRequestPeer.isRequestGesture] - method not implemented.")
    }
    isMainFrame(): boolean {
        throw new Error("[WebResourceRequestPeer.isMainFrame] - method not implemented.")
    }
    isRedirect(): boolean {
        throw new Error("[WebResourceRequestPeer.isRedirect] - method not implemented.")
    }
    getRequestMethod(): string {
        throw new Error("[WebResourceRequestPeer.getRequestMethod] - method not implemented.")
    }
}

export interface WebLoadInterceptDataType { data: WebResourceRequestPeer }
