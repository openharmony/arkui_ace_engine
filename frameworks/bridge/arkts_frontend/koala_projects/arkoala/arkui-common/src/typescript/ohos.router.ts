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

import { Router } from "./Router"
import { ArkAsyncCallback } from "../basic"

let arkRouter: Router | undefined = undefined
const arkuiEntries = new Map<
    string,
    /** @memo */
    () => void
>()

// These two are provided by a Rollup plugins during HAR packaging, check arkoala-har/arkoala-har-bundle/rollup.config.mjs
declare function __LOAD_PAGE__(url: string): Promise<void>
const __ARKOALA_HAR__ = false

export function setArkRouter(router: Router) {
    arkRouter = router
    arkuiEntries.forEach((value, key) => {
        router.register(key, value)
    })
    router.provideResolver(url => {
        if (__ARKOALA_HAR__) {
            return __LOAD_PAGE__(url).then(() => arkuiEntries.get(url)!)
        }
        console.log(`dynamic resolve ${url}`)
        return Promise.reject(`${url} not found`)
    })
}

export async function getArkuiEntry(page: string): Promise<
    /** @memo */
    () => void
> {
    if (__ARKOALA_HAR__) {
        if (!arkuiEntries.has(page)) {
            await __LOAD_PAGE__(page)
        }
    }
    const content = arkuiEntries.get(page)
    if (!content) {
        throw new Error(`No registered page for url ${JSON.stringify(page)}`)
    }

    return content
}

export function registerArkuiEntry(
    /** @memo */
    content: () => void,
    page: string
) {
    arkuiEntries.set(page, content)
}

export namespace router {
    /**
     * Router Mode
     * @since 9
     */
    export enum RouterMode {
        /**
         * Default route mode.
         * @since 9
         */
        Standard,
        /**
         * single mode.
         * @since 9
         */
        Single
    }
    /**
     * @since 8
     */
    export interface RouterOptions {
        /**
         * URI of the destination page, which supports the following formats:
         * 1. Absolute path of the page, which is provided by the pages list in the config.json file.
         *    Example:
         *      pages/index/index
         *      pages/detail/detail
         * 2. Particular path. If the URI is a slash (/), the home page is displayed.
         * @syscap SystemCapability.ArkUI.ArkUI.Lite
         * @since 8
         */
        url: string;
        /**
         * Data that needs to be passed to the destination page during navigation.
         * After the destination page is displayed, the parameter can be directly used for the page.
         * For example, this.data1 (data1 is the key value of the params used for page navigation.)
         * @syscap SystemCapability.ArkUI.ArkUI.Lite
         * @since 8
         */
        params?: Object;
    }
    /**
     * @since 8
     */
    export interface RouterState {
        /**
         * Index of the current page in the stack.
         * NOTE: The index starts from 1 from the bottom to the top of the stack.
         * @since 8
         */
        index: number;
        /**
         * Name of the current page, that is, the file name.
         * @since 8
         */
        name: string;
        /**
         * Path of the current page.
         * @since 8
         */
        path: string;
    }
    /**
     * @since 8
     */
    export interface EnableAlertOptions {
        /**
         * dialog context.
         * @since 8
         */
        message: string;
    }
    /**
    * Navigates to a specified page in the application based on the page URL and parameters.
    * @param { RouterOptions } options - Options.
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 8
    * @deprecated since 9
    * @useinstead ohos.router.router#pushUrl
    */
    export function push(options: RouterOptions): void {
        // TODO: do smth with `mode`
        arkRouter!.push(options.url, toKoalaOptions(options))
            .catch((e) => console.log("Router cannot navigate to '" + options.url + "'"))
    }
    /**
     * Navigates to a specified page in the application based on the page URL and parameters.
     *
     * @param { RouterOptions } options - Options.
     * @param { ArkAsyncCallback<void> } callback - the callback of pushUrl.
     * @throws { ArkBusinessError } 401 - if the number of parameters is less than 1 or the type of the url parameter is not string.
     * @throws { ArkBusinessError } 100001 - if UI execution context not found.
     * @throws { ArkBusinessError } 100002 - if the uri is not exist.
     * @throws { ArkBusinessError } 100003 - if the pages are pushed too much.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @crossplatform
     * @since 10
     */
    export function pushUrl(options: RouterOptions, callback: ArkAsyncCallback<void>): void;
    /**
     * Navigates to a specified page in the application based on the page URL and parameters.
     *
     * @param { RouterOptions } options - Options.
     * @param { RouterMode } mode - RouterMode.
     * @param { ArkAsyncCallback<void> } callback - the callback of pushUrl.
     * @throws { ArkBusinessError } 401 - if the number of parameters is less than 1 or the type of the url parameter is not string.
     * @throws { ArkBusinessError } 100001 - if UI execution context not found.
     * @throws { ArkBusinessError } 100002 - if the uri is not exist.
     * @throws { ArkBusinessError } 100003 - if the pages are pushed too much.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @crossplatform
     * @since 10
     */
    export function pushUrl(options: RouterOptions, mode: RouterMode, callback: ArkAsyncCallback<void>): void;
    /**
     * Navigates to a specified page in the application based on the page URL and parameters.
     *
     * @param { RouterOptions } options - Options.
     * @param { RouterMode } mode - RouterMode or undefined.
     * @returns { Promise<void> } the promise returned by the function.
     * @throws { ArkBusinessError } 401 - if the number of parameters is less than 1 or the type of the url parameter is not string.
     * @throws { ArkBusinessError } 100001 - if UI execution context not found.
     * @throws { ArkBusinessError } 100002 - if the uri is not exist.
     * @throws { ArkBusinessError } 100003 - if the pages are pushed too much.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @crossplatform
     * @since 10
     */
    export function pushUrl(options: RouterOptions, mode?: RouterMode): Promise<void>;
    export function pushUrl(
        options: RouterOptions,
        modeOrCallback?: RouterMode|ArkAsyncCallback<void>,
        callback?: ArkAsyncCallback<void>
    ): Promise<void>|void {
        const [_mode, _callback] = typeof modeOrCallback === "function"
            ? [undefined, modeOrCallback] : [modeOrCallback, callback]
        if (_mode) {
            console.log("TODO: implement router.pushUrl with RouterMode")
        }
        const result = arkRouter!.push(options.url, toKoalaOptions(options))
        if (_callback) {
            result
                .then(() => _callback(undefined!))
                .catch(() => _callback({ // TODO. Simplified.
                    name: "Error",
                    message: "Router cannot navigate to '" + options.url + "'",
                    code: 100002
                }))
        } else {
            return result
        }
    }

    /**
     * Replaces the current page with another one in the application. The current page is destroyed after replacement.
     *
     * @param { RouterOptions } options - Options.
     * @syscap SystemCapability.ArkUI.ArkUI.Lite
     * @since 8
     * @deprecated since 9
     * @useinstead ohos.router.router#replaceUrl
     */
    export function replace(options: RouterOptions, mode?: RouterMode): void {
        arkRouter!.replace(options.url, toKoalaOptions(options))
            .catch((e) => console.log("Router cannot navigate to '" + options.url + "'"))
    }
    /**
     * Replaces the current page with another one in the application. The current page is destroyed after replacement.
     *
     * @param { RouterOptions } options - Options.
     * @param { ArkAsyncCallback<void> } callback - the callback of replaceUrl.
     * @throws { ArkBusinessError } 401 - if the number of parameters is less than 1 or the type of the url parameter is not string.
     * @throws { ArkBusinessError } 100001 - if UI execution context not found, only throw in standard system.
     * @throws { ArkBusinessError } 200002 - if the uri is not exist.
     * @syscap SystemCapability.ArkUI.ArkUI.Lite
     * @since 9
     */
    export function replaceUrl(options: RouterOptions, callback: ArkAsyncCallback<void>): void;
    /**
     * Replaces the current page with another one in the application. The current page is destroyed after replacement.
     *
     * @param { RouterOptions } options - Options.
     * @param { RouterMode } mode - RouterMode.
     * @param { ArkAsyncCallback<void> } callback - the callback of replaceUrl.
     * @throws { ArkBusinessError } 401 - if the number of parameters is less than 1 or the type of the url parameter is not string.
     * @throws { ArkBusinessError } 100001 - if UI execution context not found, only throw in standard system.
     * @throws { ArkBusinessError } 200002 - if the uri is not exist.
     * @syscap SystemCapability.ArkUI.ArkUI.Lite
     * @since 9
     */
    export function replaceUrl(options: RouterOptions, mode: RouterMode, callback: ArkAsyncCallback<void>): void;
    /**
     * Replaces the current page with another one in the application. The current page is destroyed after replacement.
     *
     * @param { RouterOptions } options - Options.
     * @param { RouterMode } mode - RouterMode or undefined.
     * @returns { Promise<void> } the promise returned by the function.
     * @throws { ArkBusinessError } 401 - if the number of parameters is less than 1 or the type of the url parameter is not string.
     * @throws { ArkBusinessError } 100001 - if can not get the delegate, only throw in standard system.
     * @throws { ArkBusinessError } 200002 - if the uri is not exist.
     * @syscap SystemCapability.ArkUI.ArkUI.Lite
     * @since 9
     */
    export function replaceUrl(options: RouterOptions, mode?: RouterMode): Promise<void>;
    export function replaceUrl(
        options: RouterOptions,
        modeOrCallback?: RouterMode|ArkAsyncCallback<void>,
        callback?: ArkAsyncCallback<void>
    ): Promise<void>|void {
        const [_mode, _callback] = typeof modeOrCallback === "function"
            ? [undefined, modeOrCallback] : [modeOrCallback, callback]
        if (_mode) {
            console.log("TODO: implement router.replaceUrl with RouterMode")
        }
        const result = arkRouter!.replace(options.url, toKoalaOptions(options))
        if (_callback) {
            result
                .then(() => _callback(undefined!))
                .catch(() => _callback({ // TODO. Simplified.
                    name: "Error",
                    message: "Router cannot navigate to '" + options.url + "'",
                    code: 100002
                }))
        } else {
            return result
        }
    }


    /**
     * Returns to the previous page or a specified page.
     * @param options Options.
     * @since 8
     */
    export function back(options?: RouterOptions, mode?: RouterMode): void {
        backAsync(options, mode)
            .catch((e) => console.log("Cannot go back in router"))

    }

    export function backAsync(options?: RouterOptions, mode?: RouterMode): Promise<void> {
        return arkRouter!.back(options?.url, options?.params ? toKoalaOptions(options) : undefined)
    }
    /**
     * Clears all historical pages and retains only the current page at the top of the stack.
     * @since 8
     */
    export function clear(): void {
        return arkRouter?.clear()
    }
    /**
     * Obtains the number of pages in the current stack.
     * @returns Number of pages in the stack. The maximum value is 32.
     * @since 8
     */
    export function getLength(): string {
        return arkRouter!.depth.toString()
    }
    /**
     * Obtains information about the current page state.
     * @returns Page state.
     * @since 8
     */
    export function getState(): RouterState {
        let pageInfo = arkRouter!.pageInfo
        const slashIndex = pageInfo.page.lastIndexOf("/") + 1
        return {
            index: pageInfo.depth,
            name: pageInfo.page.substring(slashIndex),
            path: pageInfo.page.substring(0, slashIndex)
        }
    }
    /**
     * Pop up dialog to ask whether to back
     * @param options Options.
     * @since 8
     */
    export function enableAlertBeforeBackPage(options: EnableAlertOptions): void {
        throw new Error("TODO: implement router.enableAlertBeforeBackPage")
    }
    /**
     * Pop up alert dialog to ask whether to back
     *
     * @param { EnableAlertOptions } options - Options.
     * @throws { ArkBusinessError } 401 - if the type of the parameter is not object or the type of the message is not string.
     * @throws { ArkBusinessError } 100001 - if UI execution context not found.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @crossplatform
     * @since 10
     */
    export function showAlertBeforeBackPage(options: EnableAlertOptions): void {
        throw new Error("TODO: implement router.showAlertBeforeBackPage")
    }
    /**
     * cancel enableAlertBeforeBackPage
     * @since 8
     */
    export function disableAlertBeforeBackPage(): void {
        throw new Error("TODO: implement router.disableAlertBeforeBackPage")
    }
    /**
     * Hide alert before back page
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @crossplatform
     * @since 10
     */
    export function hideAlertBeforeBackPage(): void {
        throw new Error("TODO: implement router.hideAlertBeforeBackPage")
    }
    /**
     * Obtains information about the current page params.
     * @returns Page params.
     * @since 8
     */
    export function getParams(): any {
        return arkRouter!.getParam("arkuiOptions")
    }

    /**
     * @typedef NamedRouterOptions
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @crossplatform
     * @since 10
     */
    export interface NamedRouterOptions {
        /**
         * Name of the destination named route.
         *
         * @type { string }
         * @syscap SystemCapability.ArkUI.ArkUI.Full
         * @crossplatform
         * @since 10
         */
        name: string;
        /**
         * Data that needs to be passed to the destination page during navigation.
         *
         * @type { ?Object }
         * @syscap SystemCapability.ArkUI.ArkUI.Full
         * @crossplatform
         * @since 10
         */
        params?: Object;
    }

    /**
     * Navigates to a specified page in the application based on the page URL and parameters.
     *
     * @param { NamedRouterOptions } options - Options.
     * @param { ArkAsyncCallback<void> } callback - the callback of pushNamedRoute.
     * @throws { ArkBusinessError } 401 - if the number of parameters is less than 1 or the type of the url parameter is not string.
     * @throws { ArkBusinessError } 100001 - if UI execution context not found.
     * @throws { ArkBusinessError } 100003 - if the pages are pushed too much.
     * @throws { ArkBusinessError } 100004 - if the named route is not exist.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @crossplatform
     * @since 10
     */
    export function pushNamedRoute(options: NamedRouterOptions, callback: ArkAsyncCallback<void>): void;
    /**
     * Navigates to a specified page in the application based on the page URL and parameters.
     *
     * @param { NamedRouterOptions } options - Options.
     * @param { RouterMode } mode - RouterMode.
     * @param { ArkAsyncCallback<void> } callback - the callback of pushNamedRoute.
     * @throws { ArkBusinessError } 401 - if the number of parameters is less than 1 or the type of the url parameter is not string.
     * @throws { ArkBusinessError } 100001 - if UI execution context not found.
     * @throws { ArkBusinessError } 100003 - if the pages are pushed too much.
     * @throws { ArkBusinessError } 100004 - if the named route is not exist.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @crossplatform
     * @since 10
     */
    export function pushNamedRoute(options: NamedRouterOptions, mode: RouterMode, callback: ArkAsyncCallback<void>): void;
    /**
     * Navigates to a specified page in the application based on the page URL and parameters.
     *
     * @param { NamedRouterOptions } options - Options.
     * @param { RouterMode } mode - RouterMode or undefined.
     * @returns { Promise<void> } the promise returned by the function.
     * @throws { ArkBusinessError } 401 - if the number of parameters is less than 1 or the type of the url parameter is not string.
     * @throws { ArkBusinessError } 100001 - if UI execution context not found.
     * @throws { ArkBusinessError } 100003 - if the pages are pushed too much.
     * @throws { ArkBusinessError } 100004 - if the named route is not exist.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @crossplatform
     * @since 10
     */
    export function pushNamedRoute(options: NamedRouterOptions, mode?: RouterMode): Promise<void>;
    export function pushNamedRoute(
        options: NamedRouterOptions,
        modeOrCallback?: RouterMode|ArkAsyncCallback<void>,
        callback?: ArkAsyncCallback<void>
    ): Promise<void>|void {
        throw new Error("TODO: implement router.pushNamedRoute")
    }
    /**
     * Replaces the current page with another one in the application. The current page is destroyed after replacement.
     *
     * @param { NamedRouterOptions } options - Options.
     * @param { ArkAsyncCallback<void> } callback - the callback of replaceNamedRoute.
     * @throws { ArkBusinessError } 401 - if the number of parameters is less than 1 or the type of the url parameter is not string.
     * @throws { ArkBusinessError } 100001 - if UI execution context not found, only throw in standard system.
     * @throws { ArkBusinessError } 100004 - if the named route is not exist.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @crossplatform
     * @since 10
     */
    export function replaceNamedRoute(options: NamedRouterOptions, callback: ArkAsyncCallback<void>): void;
    /**
     * Replaces the current page with another one in the application. The current page is destroyed after replacement.
     *
     * @param { NamedRouterOptions } options - Options.
     * @param { RouterMode } mode - RouterMode.
     * @param { ArkAsyncCallback<void> } callback - the callback of replaceNamedRoute.
     * @throws { ArkBusinessError } 401 - if the number of parameters is less than 1 or the type of the url parameter is not string.
     * @throws { ArkBusinessError } 100001 - if UI execution context not found, only throw in standard system.
     * @throws { ArkBusinessError } 100004 - if the named route is not exist.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @crossplatform
     * @since 10
     */
    export function replaceNamedRoute(options: NamedRouterOptions, mode: RouterMode, callback: ArkAsyncCallback<void>): void;
    /**
     * Replaces the current page with another one in the application. The current page is destroyed after replacement.
     *
     * @param { NamedRouterOptions } options - Options.
     * @param { RouterMode } mode - RouterMode or undefined.
     * @returns { Promise<void> } the promise returned by the function.
     * @throws { ArkBusinessError } 401 - if the number of parameters is less than 1 or the type of the url parameter is not string.
     * @throws { ArkBusinessError } 100001 - if it can not get the delegate, only throw in standard system.
     * @throws { ArkBusinessError } 100004 - if the named route is not exist.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @crossplatform
     * @since 10
     */
    export function replaceNamedRoute(options: NamedRouterOptions, mode?: RouterMode): Promise<void>;
    export function replaceNamedRoute(
        options: NamedRouterOptions,
        modeOrCallback?: RouterMode|ArkAsyncCallback<void>,
        callback?: ArkAsyncCallback<void>
    ): Promise<void>|void {
        throw new Error("TODO: implement router.replaceNamedRoute")
    }

    function toKoalaOptions(options: RouterOptions | undefined): Map<string, any> {
        let koalaOptions = new Map<string, any>()
        koalaOptions.set("arkuiOptions", options?.params)
        return koalaOptions
    }
}

export default router