import { memo, memo_intrinsic, memo_entry, memo_stable, memo_skip } from "@koalaui/runtime/annotations"
/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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


import { int32 } from "@koalaui/common"
import {
    MutableState,
    contextLocal,
    contextLocalScope,
    mutableState,
    remember,
    RepeatByArray,
    arrayState,
    RunEffect,
    memoEntry,
    scheduleCallback,
    GlobalStateManager,
    ComputableState,
    IncrementalNode
} from "@koalaui/runtime"
import { StateContext } from 'arkui.incremental.runtime.state';
import { KPointer, runtimeType, RuntimeType } from "@koalaui/interop"
import { UserViewBuilder, UserView } from "../UserView"
import { EntryPoint, NavInterface } from '../component/customComponent';
import { ArkUINativeModule } from "#components"
import { CommonMethod, CustomBuilder, Dimension, LayoutSafeAreaEdge, LayoutSafeAreaType, Length, NavBarPosition, NavContentInfo, NavigationAnimatedTransition, NavigationCommonTitle, NavigationCustomTitle, NavigationMenuItem, NavigationMode, NavigationOperation, NavigationTitleMode, NavigationTitleOptions, NavigationToolbarOptions, PixelMap, Resource, ResourceStr, SystemBarStyle, ToolbarItem } from "#generated"
import { RouteType } from "#generated"
import { findPeerNode, PeerNode } from "arkui/PeerNode"
import router from "@ohos/router"
import { InteropNativeModule, nullptr } from "@koalaui/interop"
import { RouterExtender, PageRouterOptions, RouterOptionsInner } from "#generated"
import { UIContextUtil } from "arkui/base/UIContextUtil"
import { UIContextImpl } from "arkui/base/UIContextImpl"
import { AsyncCallback, BusinessError } from "@ohos.base"
import { UIContext } from "@ohos/arkui/UIContext"

/**
 * THEORY OF OPERATIONS
 *
 * Router is designed to navigate between multiple logical pages back and forth,
 * with the following abilities:
 *  - keeping state when returning back
 *  - ability to modify navigation stack
 *  - ability to show several pages at once to allow cross-page animations
 *
 * We took the following approach in design:
 *  - router fully in managed code
 *  - router manipulates with arbitrary builder functions as its roots
 *  - router can dynamically load class containing page implementation
 *  - mapping between page name and implementation class is dynamic and can be customized
 *  - policy for controlling alive and disposed pages in history is controllable by router
 *
 * Important implementation details:
 *   - main interface is Router, which is maintained in context local variable and can be overwritten for inner routers
 *   - inner visible/cached pages storage is maintained by RouterState.visiblePages
 *   - pushOrReplace() is for adding or modifying pages stack items
 */

export enum RouterTransitionVisibility {
    Hidden = 0,
    Visible = 1,
    Showing = 2,
    Hiding = 3,
}

export interface RouterTransitionState {
    pageId: int32
    visibility: RouterTransitionVisibility
    route?: RouteType
}

class VisiblePage {
    @memo
    page: UserViewBuilder
    url: string
    path: string
    params: jsonx.JsonElement | undefined
    peerNode: PeerNode | undefined

    constructor(
        page: UserViewBuilder,
        url: string,
        path: string,
        params?: jsonx.JsonElement
    ) {
        this.page = page
        this.url = url
        this.path = path
        this.params = params
        this.peerNode = undefined
    }

    updatePeerNode(node: PeerNode): void {
        this.peerNode = node
    }
}

class RouterState {
    readonly visiblePages = arrayState<VisiblePage>()
    currentActivePage = mutableState(0)
    constructor(
        page: UserViewBuilder,
        url: string,
        params?: jsonx.JsonElement,
        resolve?: (dummy: undefined) => void
    ) {
        this.page = page
        this.url = url
        this.params = params
        this.resolve = resolve
        // this.visiblePages.push(new VisiblePage(page, this.version.value, RouterTransitionVisibility.Visible))
    }
    @memo
    page: UserViewBuilder
    url: string
    params?: jsonx.JsonElement
    resolve?: (dummy: undefined) => void
    version = mutableState(0)
}

class RouterStackEntry {
    public url: string
    public page: UserViewBuilder
    public params?: Map<string, jsonx.JsonElement>

    constructor(
        url: string,
        page: UserViewBuilder,
        params?: Map<string, jsonx.JsonElement>,
    ) {
        this.url = url
        this.page = page
        this.params = params
    }
}

class RouterRegistryEntry {
    public url: string
    public page: UserViewBuilder

    constructor(
        url: string,
        page: UserViewBuilder
    ) {
        this.url = url
        this.page = page
    }
}

export class RouterPage {
    public depth: number
    public page: string
    constructor(depth: number, page: string) {
        this.depth = depth
        this.page = page
    }
}

export type PageTransition = () => void
export type PageClassNameResolver = (page:string) => string | undefined

class NamedRouterInfo {
    entryPoint: EntryPoint;
    pagePath: string;
    constructor(pagePath: string, entryPoint: EntryPoint) {
        this.pagePath = pagePath;
        this.entryPoint = entryPoint;
    }
}

export interface Router {
    push(options: router.RouterOptions, mode?: router.RouterMode): Promise<void>

    pushAsync(options: router.RouterOptions, callback: AsyncCallback<void>, mode?: router.RouterMode): void

    pushNamedRoute(options: router.NamedRouterOptions, mode?: router.RouterMode): Promise<void>

    pushNamedRouteAsync(options: router.NamedRouterOptions, callback: AsyncCallback<void>, mode?: router.RouterMode): void

    replace(options: router.RouterOptions, mode?: router.RouterMode): Promise<void>

    replaceAsync(options: router.RouterOptions, callback: AsyncCallback<void>, mode?: router.RouterMode): void

    replaceNamedRoute(options: router.NamedRouterOptions, mode?: router.RouterMode): Promise<void>

    replaceNamedRouteAsync(options: router.NamedRouterOptions, callback: AsyncCallback<void>, mode?: router.RouterMode): void

    back(options?: router.RouterOptions): void

    back(index: int, params?: jsonx.JsonElement): void

    clear(): void

    getLength(): string

    getStackSize(): int

    getParams(): jsonx.JsonElement

    getState(): router.RouterState

    getStateByIndex(index: int): router.RouterState | undefined

    getStateByUrl(url: string): Array<router.RouterState>

    UpdateVisiblePagePeerNode(node: PeerNode, index?: int): void

    getEntryRootValue(): ComputableState<IncrementalNode>

    getPreState(): ComputableState<IncrementalNode> | undefined;

    runStartPage(options: router.RouterOptions, builder: UserViewBuilder): void

    showAlertBeforeBackPage(options: router.EnableAlertOptions): void

    hideAlertBeforeBackPage(): void
}

const CURRENT_ROUTER = "ohos.arkoala.router"
const CURRENT_ROUTER_TRANSITION = "ohos.arkoala.router.transition"

class MockEntryPoint extends EntryPoint {
    constructor() {
        super()
    }

    /** @memo */
    entry(): void {
    }
}

export class RouterImpl implements Router {
    private readonly moduleName: string
    // list of jsViewNode
    private peerNodeList = new Array<KPointer>
    // infos of pages in stack
    public readonly visiblePages = arrayState<VisiblePage>()
    private showingPageIndex : int = 0
    // entry page
    private entryPage: VisiblePage | undefined = undefined;
    // list of container node to contain jsViewNode
    private rootState: Array<ComputableState<IncrementalNode>> = new Array<ComputableState<IncrementalNode>>()
    // map of namedRouter
    private static namedRouter: Map<string, NamedRouterInfo> = new Map<string, NamedRouterInfo>
    private runtimeLinker: RuntimeLinker | undefined = undefined;

    constructor(moduleName: string) {
        this.moduleName = moduleName
    }

    public GetRuntimeLinker(): RuntimeLinker | undefined {
        return this.runtimeLinker;
    }
    public SetRuntimeLinker(linker: RuntimeLinker | undefined): void {
        this.runtimeLinker = linker;
    }

    public static StringifyParams(params: jsonx.JsonElement | undefined | null): string {
        if (params == undefined) {
            return "";
        } else if (params.jsonType != jsonx.JsonType.JsonArray && params.jsonType != jsonx.JsonType.JsonObject) {
            console.log(`AceRouter: only array or object type of JsonElement was supported stringify in router`);
            return "";
        }
        try {
            return JSON.stringifyJsonElement(params!);
        } catch (e: Error) {
            console.log(`AceRouter: failed to stringifyParams, name: ${e.name}, msg: ${e.message}`);
            console.log(e.stack);
            return "";
        }
    }

    private getClassName(url: string): string {
        let className: string = this.moduleName + "/src/main/ets/" + url + "/__EntryWrapper";
        return className.replaceAll('/', '.');
    }

    private getPathInfo(url: string): string {
        let index = url.lastIndexOf('/');
        let result: string = '';
        if (index !== -1) {
            result = url.slice(0, index + 1);
        }
        return result;
    }

    private getFileInfo(url: string): string {
        let index = url.lastIndexOf('/');
        let result: string = '';
        if (index !== -1) {
            result = url.slice(index + 1);
        }
        return result;
    }

    private RunPage(url: string): EntryPoint | undefined {
        try {
            //@ts-ignore
            let runtimeLinker: RuntimeLinker | undefined = undefined;
            if (this.runtimeLinker) {
                runtimeLinker = this.runtimeLinker;
            } else {
                runtimeLinker = getNearestNonBootRuntimeLinker();
            }
            let entryClass = runtimeLinker?.loadClass(url.replaceChar(c'/', c'.'), false);
            if (!entryClass) {
                InteropNativeModule._NativeLog("AceRouter: load entryClass failed")
            } else {
                let entryInstance = entryClass.createInstance();
                let entryPoint = entryInstance as EntryPoint;
                return entryPoint
            }
        }
        //@ts-ignore
        catch (e: Error) {
            InteropNativeModule._NativeLog("AceRouter: catch RunPage error: " + e)
        }
        return undefined
    }

    private findPageInStack(url: string, isReplace: boolean = false): boolean {
        let index = this.visiblePages.value.findLastIndex(page => (page.path + page.url) === url);
        if (index === -1) {
            return false;
        }
        const element = this.visiblePages.splice(index as Int, 1);
        const stateNode = this.rootState.splice(index, 1);
        const peerNode = this.peerNodeList.splice(index, 1);
        if (isReplace) {
            this.visiblePages.pop();
            this.rootState.pop();
            this.peerNodeList.pop();
        }
        this.visiblePages.push(element.at(0)!);
        this.rootState.push(stateNode[0]);
        this.peerNodeList.push(peerNode[0]);
        return true;
    }

    static registerNamedRouter(routerName: string, instance: EntryPoint, param: NavInterface): void {
        let info: NamedRouterInfo = new NamedRouterInfo(param.pagePath, instance);
        RouterImpl.namedRouter.set(routerName, info);
    }

    UpdateVisiblePagePeerNode(node: PeerNode, index: int = -1): void {
        InteropNativeModule._NativeLog("AceRouter: router UpdateVisiblePagePeerNode, index: " + index)
        if (index == -1) {
            index = this.visiblePages.length - 1
        }
        if (index < 0 || index > this.showingPageIndex) {
            InteropNativeModule._NativeLog("AceRouter: router page size is incorrect")
            return;
        }
    }

    pushDynamic(options: router.RouterOptions): Promise<void> {
        let optionsInner: RouterOptionsInner = {
            url: options.url,
            params: RouterImpl.StringifyParams(options.params),
            recoverable: options.recoverable
        };
        let pageNode = RouterExtender.createDynamic(optionsInner);
        if (!pageNode) {
            InteropNativeModule._NativeLog(`AceRouter: failed to create dynamicPage in pushDynamic`);
            return Promise.reject({
                code: 100002,
                message: "The uri of router is not exist."});
        }
        let entryObject = new MockEntryPoint();
        let manager = GlobalStateManager.instance
        let stateNode = manager.updatableNode<IncrementalNode>(new IncrementalNode(), (context: StateContext) => {
            const frozen = manager.frozen
            manager.frozen = true
            memoEntry<void>(context, 0, () => {
            })
            manager.frozen = frozen
        })
        this.rootState.push(stateNode)
        this.peerNodeList.push(pageNode)
        let pagePushTransitionCallback = (pageNode: KPointer) => {
            let index = this.peerNodeList.indexOf(pageNode);
            if (index !== -1) {
                this.peerNodeList.splice(index, 1);
                this.visiblePages.splice(index, 1);
                this.rootState.splice(index, 1);
                this.showingPageIndex = this.showingPageIndex - 1;
            }
        };
        let newPage = new VisiblePage(entryObject.entry, this.getFileInfo(options.url), this.getPathInfo(options.url), options.params);
        this.visiblePages.splice(this.showingPageIndex + 1, 0, newPage);
        this.showingPageIndex += 1;
        let pageOptions: PageRouterOptions = { options: optionsInner };
        return RouterExtender.pushDynamic(pageNode, pageOptions, pagePushTransitionCallback);
    }

    push(options: router.RouterOptions, mode?: router.RouterMode): Promise<void> {
        if (options.url === '/') {
            options.url = this.entryPage?.path! + this.entryPage?.url!;
        }
        let optionsInner: RouterOptionsInner = {
            url: options.url,
            params: RouterImpl.StringifyParams(options.params),
            recoverable: options.recoverable
        };
        if (mode !== undefined && mode === router.RouterMode.Single && this.findPageInStack(options.url)) {
            let pagePushTransitionCallback = (jsNode: KPointer) => {
                let index = this.peerNodeList.indexOf(jsNode);
                if (index !== -1) {
                    this.peerNodeList.splice(index, 1);
                    this.visiblePages.splice(index, 1);
                    this.rootState.splice(index, 1);
                    this.showingPageIndex = this.showingPageIndex - 1;
                }
            };
            let pageOptions: PageRouterOptions = { options: optionsInner, mode: mode };
            const jsViewNodePtr = this.peerNodeList.at(this.peerNodeList.length - 1);
            return RouterExtender.push(jsViewNodePtr!, pageOptions, pagePushTransitionCallback);
        }
        let className = this.getClassName(options.url);
        let entryObject = this.RunPage(className);
        if (entryObject) {
            let manager = GlobalStateManager.instance
            let stateNode = manager.updatableNode<IncrementalNode>(new IncrementalNode(), (context: StateContext) => {
                const frozen = manager.frozen
                manager.frozen = true
                memoEntry<void>(context, 0, () => {
                    entryObject!.entry()
                })
                manager.frozen = frozen
            })
            let peerNode: PeerNode | undefined = undefined;
            try {
                const incNode = stateNode.value;
                peerNode = findPeerNode(incNode);
            }
            //@ts-ignore
            catch (e: Error) {
                console.log("AceRouter: create page failed, name: " + e.name + " message: " + e.message);
                console.log(e.stack);
            }
            if (peerNode === undefined) {
                InteropNativeModule._NativeLog("AceRouter:create jsView failed");
                return Promise.reject({
                    code: 100001,
                    message: "Internal error."});
            }
            const jsViewNodePtr = peerNode!.peer.ptr;
            this.rootState.push(stateNode)
            this.peerNodeList.push(jsViewNodePtr);
            let context = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
            context.getDetachedRootEntryManager().setDetachedRootNode(jsViewNodePtr, stateNode);
            let pagePushTransitionCallback = (jsNode: KPointer) => {
                let index = this.peerNodeList.indexOf(jsNode);
                if (index !== -1) {
                    this.peerNodeList.splice(index, 1);
                    this.visiblePages.splice(index, 1);
                    this.rootState.splice(index, 1);
                    this.showingPageIndex = this.showingPageIndex - 1;
                }
            };
            let newPage = new VisiblePage(entryObject.entry, this.getFileInfo(options.url), this.getPathInfo(options.url), options.params);
            this.visiblePages.splice(this.showingPageIndex + 1, 0, newPage);
            this.showingPageIndex += 1;
            let pageOptions: PageRouterOptions = { options: optionsInner, mode: mode };
            return RouterExtender.push(jsViewNodePtr, pageOptions, pagePushTransitionCallback);
        } else {
            // maybe new page is arkts1.1 page
            InteropNativeModule._NativeLog("AceRouter: try to push with DynamicPage");
            return this.pushDynamic(options);
        }
    }

    pushDynamicAsync(options: router.RouterOptions, callback: AsyncCallback<void>): void {
        let optionsInner: RouterOptionsInner = {
            url: options.url,
            params: RouterImpl.StringifyParams(options.params),
            recoverable: options.recoverable
        };
        let pageNode = RouterExtender.createDynamic(optionsInner);
        if (!pageNode) {
            InteropNativeModule._NativeLog(`AceRouter: failed to create dynamicPage in pushDynamic`);
            let error: BusinessError = new BusinessError(100002,
                "Uri error. The URI of the page to redirect is incorrect or does not exist.");
            callback(error, undefined);
            return;
        }
        let asyncCallback = (code: int32, message: string) => {
            if (code != 0) {
                let error: BusinessError = new BusinessError(code, message);
                callback(error, undefined);
            } else {
                callback(null, undefined)
            }
        }
        let entryObject = new MockEntryPoint();
        let manager = GlobalStateManager.instance
        let stateNode = manager.updatableNode<IncrementalNode>(new IncrementalNode(), (context: StateContext) => {
            const frozen = manager.frozen
            manager.frozen = true
            memoEntry<void>(context, 0, () => {
            })
            manager.frozen = frozen
        })
        this.rootState.push(stateNode)
        let pagePushTransitionCallback = (pageNode: KPointer) => {
            let index = this.peerNodeList.indexOf(pageNode);
            if (index !== -1) {
                this.peerNodeList.splice(index, 1);
                this.visiblePages.splice(index, 1);
                this.rootState.splice(index, 1);
                this.showingPageIndex = this.showingPageIndex - 1;
            }
        };
        let newPage = new VisiblePage(entryObject.entry, this.getFileInfo(options.url), this.getPathInfo(options.url), options.params);
        this.visiblePages.splice(this.showingPageIndex + 1, 0, newPage);
        this.showingPageIndex += 1;
        let pageOptions: PageRouterOptions = { options: optionsInner };
        RouterExtender.pushDynamic(pageNode, pageOptions, pagePushTransitionCallback, asyncCallback);
    }

    pushAsync(options: router.RouterOptions, callback: AsyncCallback<void>, mode?: router.RouterMode): void {
        if (options.url === '/') {
            options.url = this.entryPage?.path! + this.entryPage?.url!;
        }
        let optionsInner: RouterOptionsInner = {
            url: options.url,
            params: RouterImpl.StringifyParams(options.params),
            recoverable: options.recoverable
        };
        let asyncCallback = (code: int32, message: string) => {
            if (code != 0) {
                let error: BusinessError = new BusinessError(code, message);
                callback(error, undefined);
            } else {
                callback(null, undefined)
            }
        }
        if (mode !== undefined && mode === router.RouterMode.Single && this.findPageInStack(options.url)) {
            let pagePushTransitionCallback = (jsNode: KPointer) => {
                let index = this.peerNodeList.indexOf(jsNode);
                if (index !== -1) {
                    this.peerNodeList.splice(index, 1);
                    this.visiblePages.splice(index, 1);
                    this.rootState.splice(index, 1);
                    this.showingPageIndex = this.showingPageIndex - 1;
                }
            };
            let pageOptions: PageRouterOptions = { options: optionsInner, mode: mode };
            const jsViewNodePtr = this.peerNodeList.at(this.peerNodeList.length - 1);
            RouterExtender.push(jsViewNodePtr!, pageOptions, pagePushTransitionCallback, asyncCallback);
            return;
        }
        let className = this.getClassName(options.url);
        let entryObject = this.RunPage(className);
        if (entryObject) {
            let manager = GlobalStateManager.instance
            let stateNode = manager.updatableNode<IncrementalNode>(new IncrementalNode(), (context: StateContext) => {
                const frozen = manager.frozen
                manager.frozen = true
                memoEntry<void>(context, 0, () => {
                    entryObject!.entry()
                })
                manager.frozen = frozen
            })
            let peerNode: PeerNode | undefined = undefined;
            try {
                const incNode = stateNode.value;
                peerNode = findPeerNode(incNode);
            }
            //@ts-ignore
            catch (e: Error) {
                console.log("AceRouter: create page failed, name: " + e.name + " message: " + e.message);
                console.log(e.stack);
            }
            if (peerNode === undefined) {
                InteropNativeModule._NativeLog("AceRouter:create jsView failed");
                let error: BusinessError = new BusinessError(100001, "Internal error.");
                callback(error, undefined);
                return;
            }
            const jsViewNodePtr = peerNode!.peer.ptr;
            this.rootState.push(stateNode)
            this.peerNodeList.push(jsViewNodePtr);
            let context = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
            context.getDetachedRootEntryManager().setDetachedRootNode(jsViewNodePtr, stateNode);
            let pagePushTransitionCallback = (jsNode: KPointer) => {
                let index = this.peerNodeList.indexOf(jsNode);
                if (index !== -1) {
                    this.peerNodeList.splice(index, 1);
                    this.visiblePages.splice(index, 1);
                    this.rootState.splice(index, 1);
                    this.showingPageIndex = this.showingPageIndex - 1;
                }
            };
            let newPage = new VisiblePage(entryObject.entry, this.getFileInfo(options.url), this.getPathInfo(options.url), options.params);
            this.visiblePages.splice(this.showingPageIndex + 1, 0, newPage);
            this.showingPageIndex += 1;
            let pageOptions: PageRouterOptions = { options: optionsInner };
            RouterExtender.push(jsViewNodePtr, pageOptions, pagePushTransitionCallback, asyncCallback);
            return;
        }
        // maybe new page is arkts1.1 page
        InteropNativeModule._NativeLog("AceRouter: try to push with DynamicPage");
        this.pushDynamicAsync(options, callback);
    }

    pushNamedRoute(options: router.NamedRouterOptions, mode?: router.RouterMode): Promise<void> {
        let optionsInner: RouterOptionsInner = {
            url: options.name,
            params: RouterImpl.StringifyParams(options.params),
            recoverable: options.recoverable
        };
        if (mode !== undefined && mode === router.RouterMode.Single && this.findPageInStack(options.name)) {
            let pagePushTransitionCallback = (jsNode: KPointer) => {
                let index = this.peerNodeList.indexOf(jsNode);
                if (index !== -1) {
                    this.peerNodeList.splice(index, 1);
                    this.visiblePages.splice(index, 1);
                    this.rootState.splice(index, 1);
                    this.showingPageIndex = this.showingPageIndex - 1;
                }
            };
            let pageOptions: PageRouterOptions = { options: optionsInner, mode: mode };
            const jsViewNodePtr = this.peerNodeList.at(this.peerNodeList.length - 1);
            return RouterExtender.pushNamedRoute(jsViewNodePtr!, pageOptions, pagePushTransitionCallback);
        }
        let className = options.name;
        let entryInfo = RouterImpl.namedRouter.get(className);
        let entryObject = entryInfo?.entryPoint;
        if (entryObject) {
            let manager = GlobalStateManager.instance
            let stateNode = manager.updatableNode<IncrementalNode>(new IncrementalNode(), (context: StateContext) => {
                const frozen = manager.frozen
                manager.frozen = true
                memoEntry<void>(context, 0, () => {
                    entryObject!.entry()
                })
                manager.frozen = frozen
            })
            let peerNode: PeerNode | undefined = undefined;
            try {
                const incNode = stateNode.value;
                peerNode = findPeerNode(incNode);
            }
            //@ts-ignore
            catch (e: Error) {
                console.log("AceRouter: create page failed, name: " + e.name + " message: " + e.message);
                console.log(e.stack);
            }
            if (peerNode === undefined) {
                InteropNativeModule._NativeLog("AceRouter:create jsView failed");
                return Promise.reject({
                    code: 100001,
                    message: "Internal error."});
            }
            const jsViewNodePtr = peerNode!.peer.ptr;
            this.rootState.push(stateNode)
            this.peerNodeList.push(jsViewNodePtr);
            let context = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
            context.getDetachedRootEntryManager().setDetachedRootNode(jsViewNodePtr, stateNode);
            let pagePushTransitionCallback = (jsNode: KPointer) => {
                let index = this.peerNodeList.indexOf(jsNode);
                if (index !== -1) {
                    this.peerNodeList.splice(index, 1);
                    this.visiblePages.splice(index, 1);
                    this.rootState.splice(index, 1);
                    this.showingPageIndex = this.showingPageIndex - 1;
                }
            };
            let newPage = new VisiblePage(entryObject.entry, this.getFileInfo(options.name), this.getPathInfo(options.name), options.params);
            this.visiblePages.splice(this.showingPageIndex + 1, 0, newPage);
            this.showingPageIndex += 1;
            let pageOptions: PageRouterOptions = { options: optionsInner };
            return RouterExtender.pushNamedRoute(jsViewNodePtr, pageOptions, pagePushTransitionCallback);
        }
        return Promise.reject({
            code: 100004,
            message: "Named route error. The named route does not exist."});
    }

    pushNamedRouteAsync(options: router.NamedRouterOptions, callback: AsyncCallback<void>, mode?: router.RouterMode): void {
        let asyncCallback = (code: int32, message: string) => {
            if (code != 0) {
                let error: BusinessError = new BusinessError(code, message);
                callback(error, undefined);
            } else {
                callback(null, undefined)
            }
        }
        let optionsInner: RouterOptionsInner = {
            url: options.name,
            params: RouterImpl.StringifyParams(options.params),
            recoverable: options.recoverable
        };
        if (mode !== undefined && mode === router.RouterMode.Single && this.findPageInStack(options.name)) {
            let pagePushTransitionCallback = (jsNode: KPointer) => {
                let index = this.peerNodeList.indexOf(jsNode);
                if (index !== -1) {
                    this.peerNodeList.splice(index, 1);
                    this.visiblePages.splice(index, 1);
                    this.rootState.splice(index, 1);
                    this.showingPageIndex = this.showingPageIndex - 1;
                }
            };
            let pageOptions: PageRouterOptions = { options: optionsInner, mode: mode };
            const jsViewNodePtr = this.peerNodeList.at(this.peerNodeList.length - 1);
            RouterExtender.pushNamedRoute(jsViewNodePtr!, pageOptions, pagePushTransitionCallback, asyncCallback);
            return;
        }
        let className = options.name;
        let entryInfo = RouterImpl.namedRouter.get(className);
        let entryObject = entryInfo?.entryPoint;
        if (entryObject) {
            let manager = GlobalStateManager.instance
            let stateNode = manager.updatableNode<IncrementalNode>(new IncrementalNode(), (context: StateContext) => {
                const frozen = manager.frozen
                manager.frozen = true
                memoEntry<void>(context, 0, () => {
                    entryObject!.entry()
                })
                manager.frozen = frozen
            })
            let peerNode: PeerNode | undefined = undefined;
            try {
                const incNode = stateNode.value;
                peerNode = findPeerNode(incNode);
            }
            //@ts-ignore
            catch (e: Error) {
                console.log("AceRouter: create page failed, name: " + e.name + " message: " + e.message);
                console.log(e.stack);
            }
            if (peerNode === undefined) {
                InteropNativeModule._NativeLog("AceRouter:create jsView failed");
                let error: BusinessError = new BusinessError(100001, "Internal error.");
                callback(error, undefined);
                return;
            }
            const jsViewNodePtr = peerNode!.peer.ptr;
            this.rootState.push(stateNode)
            this.peerNodeList.push(jsViewNodePtr);
            let context = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
            context.getDetachedRootEntryManager().setDetachedRootNode(jsViewNodePtr, stateNode);
            let pagePushTransitionCallback = (jsNode: KPointer) => {
                let index = this.peerNodeList.indexOf(jsNode);
                if (index !== -1) {
                    this.peerNodeList.splice(index, 1);
                    this.visiblePages.splice(index, 1);
                    this.rootState.splice(index, 1);
                    this.showingPageIndex = this.showingPageIndex - 1;
                }
            };
            let newPage = new VisiblePage(entryObject.entry, this.getFileInfo(options.name), this.getPathInfo(options.name), options.params);
            this.visiblePages.splice(this.showingPageIndex + 1, 0, newPage);
            this.showingPageIndex += 1;
            let pageOptions: PageRouterOptions = { options: optionsInner };
            RouterExtender.pushNamedRoute(jsViewNodePtr, pageOptions, pagePushTransitionCallback, asyncCallback);
            return;
        }
        let error: BusinessError = new BusinessError(100004,
            "Named route error. The named route does not exist.");
        callback(error, undefined);
    }

    replaceDynamic(options: router.RouterOptions): Promise<void> {
        let optionsInner: RouterOptionsInner = {
            url: options.url,
            params: RouterImpl.StringifyParams(options.params),
            recoverable: options.recoverable
        };
        let pageNode = RouterExtender.createDynamic(optionsInner);
        if (!pageNode) {
            InteropNativeModule._NativeLog(`AceRouter: failed to create dynamicPage in replaceDynamic`);
            return Promise.reject({
                code: 200002,
                message: "Uri error. The URI of the page to be used for replacement is incorrect or does not exist."
            });
        }
        let entryObject = new MockEntryPoint();
        let manager = GlobalStateManager.instance
        let stateNode = manager.updatableNode<IncrementalNode>(new IncrementalNode(), (context: StateContext) => {
            const frozen = manager.frozen
            manager.frozen = true
            memoEntry<void>(context, 0, () => {
            })
            manager.frozen = frozen
        })
        this.rootState.push(stateNode);
        this.peerNodeList.push(pageNode)
        let context = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
        context.getDetachedRootEntryManager().setDetachedRootNode(pageNode, stateNode);
        let pageEnterTransitionCallback = (pageNode: KPointer) => {
            let index = this.peerNodeList.indexOf(pageNode);
            if (index !== -1) {
                this.peerNodeList.splice(index, 1);
                this.visiblePages.splice(index, 1);
                this.rootState.splice(index, 1);
                this.showingPageIndex = this.showingPageIndex - 1;
            }
        };
        let newPage = new VisiblePage(entryObject.entry, this.getFileInfo(options.url), this.getPathInfo(options.url), options.params);
        this.visiblePages.push(newPage)
        this.showingPageIndex += 1
        let pageOptions: PageRouterOptions = { options: optionsInner };
        return RouterExtender.replaceDynamic(pageNode, pageOptions, pageEnterTransitionCallback);
    }

    replace(options: router.RouterOptions, mode?: router.RouterMode): Promise<void> {
        if (options.url === '/') {
            options.url = this.entryPage?.path! + this.entryPage?.url!;
        }
        let optionsInner: RouterOptionsInner = {
            url: options.url,
            params: RouterImpl.StringifyParams(options.params),
            recoverable: options.recoverable
        };
        if (mode !== undefined && mode === router.RouterMode.Single && this.findPageInStack(options.url, true)) {
            let pagePushTransitionCallback = (jsNode: KPointer) => {
                let index = this.peerNodeList.indexOf(jsNode);
                if (index !== -1) {
                    this.peerNodeList.splice(index, 1);
                    this.visiblePages.splice(index, 1);
                    this.rootState.splice(index, 1);
                    this.showingPageIndex = this.showingPageIndex - 1;
                }
            };
            let pageOptions: PageRouterOptions = { options: optionsInner, mode: mode };
            const jsViewNodePtr = this.peerNodeList.at(this.peerNodeList.length - 1);
            return RouterExtender.replace(jsViewNodePtr!, pageOptions, pagePushTransitionCallback);
        }
        let className = this.getClassName(options.url);
        let entryObject = this.RunPage(className);
        if (entryObject) {
            let manager = GlobalStateManager.instance
            let stateNode = manager.updatableNode<IncrementalNode>(new IncrementalNode(), (context: StateContext) => {
                const frozen = manager.frozen
                manager.frozen = true
                memoEntry<void>(context, 0, () => {
                    entryObject!.entry()
                })
                manager.frozen = frozen
            })
            let peerNode: PeerNode | undefined = undefined;
            try {
                const incNode = stateNode.value;
                peerNode = findPeerNode(incNode);
            }
            //@ts-ignore
            catch (e: Error) {
                console.log("AceRouter: create page failed, name: " + e.name + " message: " + e.message);
                console.log(e.stack);
            }
            if (peerNode === undefined) {
                InteropNativeModule._NativeLog("AceRouter:create jsView failed");
                return Promise.reject({
                    code: 200002,
                    message: "Uri error. The URI of the page to be used for replacement is incorrect or does not exist."
                });
            }
            const jsViewNodePtr = peerNode!.peer.ptr
            this.rootState.push(stateNode);
            this.peerNodeList.push(jsViewNodePtr)
            let context = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
            context.getDetachedRootEntryManager().setDetachedRootNode(jsViewNodePtr, stateNode);
            let pageEnterTransitionCallback = (jsNode: KPointer) => {
                let index = this.peerNodeList.indexOf(jsNode);
                if (index !== -1) {
                    this.peerNodeList.splice(index, 1);
                    this.visiblePages.splice(index, 1);
                    this.rootState.splice(index, 1);
                    this.showingPageIndex = this.showingPageIndex - 1;
                }
            };
            let newPage = new VisiblePage(entryObject.entry, this.getFileInfo(options.url), this.getPathInfo(options.url), options.params);
            this.visiblePages.push(newPage)
            this.showingPageIndex += 1
            let pageOptions: PageRouterOptions = { options: optionsInner };
            return RouterExtender.replace(jsViewNodePtr, pageOptions, pageEnterTransitionCallback);
        }
        // maybe new page is arkts1.1 page
        InteropNativeModule._NativeLog("AceRouter: try to replace with DynamicPage");
        return this.replaceDynamic(options);
    }

    replaceDynamicAsync(options: router.RouterOptions, callback: AsyncCallback<void>, mode?: router.RouterMode): void {
        let optionsInner: RouterOptionsInner = {
            url: options.url,
            params: RouterImpl.StringifyParams(options.params),
            recoverable: options.recoverable
        };
        let pageNode = RouterExtender.createDynamic(optionsInner);
        if (!pageNode) {
            InteropNativeModule._NativeLog(`AceRouter: failed to create dynamicPage in replaceDynamic`);
            let error: BusinessError = new BusinessError(200002,
                "Uri error. The URI of the page to be used for replacement is incorrect or does not exist.");
            callback(error, undefined);
            return;
        }
        let asyncCallback = (code: int32, message: string) => {
            if (code != 0) {
                let error: BusinessError = new BusinessError(code, message);
                callback(error, undefined);
            } else {
                callback(null, undefined)
            }
        }
        let entryObject = new MockEntryPoint();
        let manager = GlobalStateManager.instance
        let stateNode = manager.updatableNode<IncrementalNode>(new IncrementalNode(), (context: StateContext) => {
            const frozen = manager.frozen
            manager.frozen = true
            memoEntry<void>(context, 0, () => {
            })
            manager.frozen = frozen
        })
        this.rootState.push(stateNode);
        this.peerNodeList.push(pageNode)
        let context = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
        context.getDetachedRootEntryManager().setDetachedRootNode(pageNode, stateNode);
        let pageEnterTransitionCallback = (pageNode: KPointer) => {
            let index = this.peerNodeList.indexOf(pageNode);
            if (index !== -1) {
                this.peerNodeList.splice(index, 1);
                this.visiblePages.splice(index, 1);
                this.rootState.splice(index, 1);
                this.showingPageIndex = this.showingPageIndex - 1;
            }
        };
        let newPage = new VisiblePage(entryObject.entry, this.getFileInfo(options.url), this.getPathInfo(options.url), options.params);
        this.visiblePages.push(newPage)
        this.showingPageIndex += 1
        let pageOptions: PageRouterOptions = { options: optionsInner };
        if (mode != undefined) {
            pageOptions.mode = mode;
        }
        RouterExtender.replaceDynamic(pageNode, pageOptions, pageEnterTransitionCallback, asyncCallback);
    }

    replaceAsync(options: router.RouterOptions, callback: AsyncCallback<void>, mode?: router.RouterMode): void {
        if (options.url === '/') {
            options.url = this.entryPage?.path! + this.entryPage?.url!;
        }
        let optionsInner: RouterOptionsInner = {
            url: options.url,
            params: RouterImpl.StringifyParams(options.params),
            recoverable: options.recoverable
        };
        let asyncCallback = (code: int32, message: string) => {
            if (code != 0) {
                let error: BusinessError = new BusinessError(code, message);
                callback(error, undefined);
            } else {
                callback(null, undefined)
            }
        }
        if (mode !== undefined && mode === router.RouterMode.Single && this.findPageInStack(options.url, true)) {
            let pagePushTransitionCallback = (jsNode: KPointer) => {
                let index = this.peerNodeList.indexOf(jsNode);
                if (index !== -1) {
                    this.peerNodeList.splice(index, 1);
                    this.visiblePages.splice(index, 1);
                    this.rootState.splice(index, 1);
                    this.showingPageIndex = this.showingPageIndex - 1;
                }
            };
            let pageOptions: PageRouterOptions = { options: optionsInner, mode: mode };
            const jsViewNodePtr = this.peerNodeList.at(this.peerNodeList.length - 1);
            RouterExtender.replace(jsViewNodePtr!, pageOptions, pagePushTransitionCallback, asyncCallback);
            return;
        }
        let className = this.getClassName(options.url);
        let entryObject = this.RunPage(className);
        if (entryObject) {
            let manager = GlobalStateManager.instance
            let stateNode = manager.updatableNode<IncrementalNode>(new IncrementalNode(), (context: StateContext) => {
                const frozen = manager.frozen
                manager.frozen = true
                memoEntry<void>(context, 0, () => {
                    entryObject!.entry()
                })
                manager.frozen = frozen
            })
            
            let peerNode: PeerNode | undefined = undefined;
            try {
                const incNode = stateNode.value;
                peerNode = findPeerNode(incNode);
            }
            //@ts-ignore
            catch (e: Error) {
                console.log("AceRouter: create page failed, name: " + e.name + " message: " + e.message);
                console.log(e.stack);
            }
            if (peerNode === undefined) {
                InteropNativeModule._NativeLog("AceRouter:create jsView failed");
                let error: BusinessError = new BusinessError(200002,
                    "Uri error. The URI of the page to be used for replacement is incorrect or does not exist.");
                callback(error, undefined);
                return;
            }
            const jsViewNodePtr = peerNode!.peer.ptr
            this.rootState.push(stateNode);
            this.peerNodeList.push(jsViewNodePtr)
            let context = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
            context.getDetachedRootEntryManager().setDetachedRootNode(jsViewNodePtr, stateNode);
            let pageEnterTransitionCallback = (jsNode: KPointer) => {
                let index = this.peerNodeList.indexOf(jsNode);
                if (index !== -1) {
                    this.peerNodeList.splice(index, 1);
                    this.visiblePages.splice(index, 1);
                    this.rootState.splice(index, 1);
                    this.showingPageIndex = this.showingPageIndex - 1;
                }
            };
            let newPage = new VisiblePage(entryObject.entry, this.getFileInfo(options.url), this.getPathInfo(options.url), options.params);
            this.visiblePages.push(newPage)
            this.showingPageIndex += 1
            let pageOptions: PageRouterOptions = { options: optionsInner };
            if (mode != undefined) {
                pageOptions.mode = mode;
            }
            RouterExtender.replace(jsViewNodePtr, pageOptions, pageEnterTransitionCallback, asyncCallback);
            return;
        }
        // maybe new page is arkts1.1 page
        InteropNativeModule._NativeLog("AceRouter: try to replace with DynamicPage");
        this.replaceDynamicAsync(options, callback, mode);
    }

    replaceNamedRoute(options: router.NamedRouterOptions, mode?: router.RouterMode): Promise<void> {
        let optionsInner: RouterOptionsInner = {
            url: options.name,
            params: RouterImpl.StringifyParams(options.params),
            recoverable: options.recoverable
        };
        if (mode !== undefined && mode === router.RouterMode.Single && this.findPageInStack(options.name, true)) {
            let pagePushTransitionCallback = (jsNode: KPointer) => {
                let index = this.peerNodeList.indexOf(jsNode);
                if (index !== -1) {
                    this.peerNodeList.splice(index, 1);
                    this.visiblePages.splice(index, 1);
                    this.rootState.splice(index, 1);
                    this.showingPageIndex = this.showingPageIndex - 1;
                }
            };
            let pageOptions: PageRouterOptions = { options: optionsInner, mode: mode };
            const jsViewNodePtr = this.peerNodeList.at(this.peerNodeList.length - 1);
            return RouterExtender.replaceNamedRoute(jsViewNodePtr!, pageOptions, pagePushTransitionCallback);
        }
        let className = options.name;
        let entryInfo = RouterImpl.namedRouter.get(className);
        let entryObject = entryInfo?.entryPoint;
        if (entryObject) {
            let manager = GlobalStateManager.instance
            let stateNode = manager.updatableNode<IncrementalNode>(new IncrementalNode(), (context: StateContext) => {
                const frozen = manager.frozen
                manager.frozen = true
                memoEntry<void>(context, 0, () => {
                    entryObject!.entry()
                })
                manager.frozen = frozen
            })
            
            let peerNode: PeerNode | undefined = undefined;
            try {
                const incNode = stateNode.value;
                peerNode = findPeerNode(incNode);
            }
            //@ts-ignore
            catch (e: Error) {
                console.log("AceRouter: create page failed, name: " + e.name + " message: " + e.message);
                console.log(e.stack);
            }
            if (peerNode === undefined) {
                InteropNativeModule._NativeLog("AceRouter:create jsView failed");
                return Promise.reject({
                    code: 100004,
                    message: "Named route error. The named route does not exist."});
            }
            const jsViewNodePtr = peerNode!.peer.ptr
            this.rootState.push(stateNode);
            this.peerNodeList.push(jsViewNodePtr)
            let context = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
            context.getDetachedRootEntryManager().setDetachedRootNode(jsViewNodePtr, stateNode);
            let pageEnterTransitionCallback = (jsNode: KPointer) => {
                let index = this.peerNodeList.indexOf(jsNode);
                if (index !== -1) {
                    this.peerNodeList.splice(index, 1);
                    this.visiblePages.splice(index, 1);
                    this.rootState.splice(index, 1);
                    this.showingPageIndex = this.showingPageIndex - 1;
                }
            };
            let newPage = new VisiblePage(entryObject.entry, this.getFileInfo(options.name), this.getPathInfo(options.name), options.params);
            this.visiblePages.push(newPage)
            this.showingPageIndex += 1
            let pageOptions: PageRouterOptions = { options: optionsInner };
            if (mode != undefined) {
                pageOptions.mode = mode;
            }
            return RouterExtender.replaceNamedRoute(jsViewNodePtr, pageOptions, pageEnterTransitionCallback)
        }
        return Promise.reject({
            code: 100004,
            message: "Named route error. The named route does not exist."});
    }

    replaceNamedRouteAsync(options: router.NamedRouterOptions, callback: AsyncCallback<void>, mode?: router.RouterMode): void {
        let optionsInner: RouterOptionsInner = {
            url: options.name,
            params: RouterImpl.StringifyParams(options.params),
            recoverable: options.recoverable
        };
        let asyncCallback = (code: int32, message: string) => {
            if (code != 0) {
                let error: BusinessError = new BusinessError(code, message);
                callback(error, undefined);
            } else {
                callback(null, undefined)
            }
        }
        if (mode !== undefined && mode === router.RouterMode.Single && this.findPageInStack(options.name, true)) {
            let pagePushTransitionCallback = (jsNode: KPointer) => {
                let index = this.peerNodeList.indexOf(jsNode);
                if (index !== -1) {
                    this.peerNodeList.splice(index, 1);
                    this.visiblePages.splice(index, 1);
                    this.rootState.splice(index, 1);
                    this.showingPageIndex = this.showingPageIndex - 1;
                }
            };
            let pageOptions: PageRouterOptions = { options: optionsInner, mode: mode };
            const jsViewNodePtr = this.peerNodeList.at(this.peerNodeList.length - 1);
            RouterExtender.replaceNamedRoute(jsViewNodePtr!, pageOptions, pagePushTransitionCallback, asyncCallback);
            return;
        }
        let className = options.name;
        let entryInfo = RouterImpl.namedRouter.get(className);
        let entryObject = entryInfo?.entryPoint;
        if (entryObject) {
            let manager = GlobalStateManager.instance
            let stateNode = manager.updatableNode<IncrementalNode>(new IncrementalNode(), (context: StateContext) => {
                const frozen = manager.frozen
                manager.frozen = true
                memoEntry<void>(context, 0, () => {
                    entryObject!.entry()
                })
                manager.frozen = frozen
            })
            
            let peerNode: PeerNode | undefined = undefined;
            try {
                const incNode = stateNode.value;
                peerNode = findPeerNode(incNode);
            }
            //@ts-ignore
            catch (e: Error) {
                console.log("AceRouter: create page failed, name: " + e.name + " message: " + e.message);
                console.log(e.stack);
            }
            if (peerNode === undefined) {
                InteropNativeModule._NativeLog("AceRouter:create jsView failed");
                let error: BusinessError = new BusinessError(100004,
                    "Named route error. The named route does not exist.");
                callback(error, undefined);
                return;
            }
            const jsViewNodePtr = peerNode!.peer.ptr
            this.rootState.push(stateNode);
            this.peerNodeList.push(jsViewNodePtr)
            let context = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
            context.getDetachedRootEntryManager().setDetachedRootNode(jsViewNodePtr, stateNode);
            let pageEnterTransitionCallback = (jsNode: KPointer) => {
                let index = this.peerNodeList.indexOf(jsNode);
                if (index !== -1) {
                    this.peerNodeList.splice(index, 1);
                    this.visiblePages.splice(index, 1);
                    this.rootState.splice(index, 1);
                    this.showingPageIndex = this.showingPageIndex - 1;
                }
            };
            let newPage = new VisiblePage(entryObject.entry, this.getFileInfo(options.name), this.getPathInfo(options.name), options.params);
            this.visiblePages.push(newPage)
            this.showingPageIndex += 1
            let pageOptions: PageRouterOptions = { options: optionsInner };
            if (mode != undefined) {
                pageOptions.mode = mode;
            }
            RouterExtender.replaceNamedRoute(jsViewNodePtr, pageOptions, pageEnterTransitionCallback, asyncCallback);
            return;
        }
        let error: BusinessError = new BusinessError(100004,
            "Named route error. The named route does not exist.");
        callback(error, undefined);
    }

    back(options?: router.RouterOptions): void {
        let optionsInner: RouterOptionsInner | undefined;
        if (options) {
            optionsInner = {
                url: options.url,
                params: RouterImpl.StringifyParams(options.params),
                recoverable: options.recoverable
            };
        }
        RouterExtender.back(optionsInner);
        if (options) {
            let url = options?.url;
            let index = this.visiblePages.value.findLastIndex(element => (element.path + element.url) === url);
            if (index != -1) {
                let pageInfo = this.visiblePages.at(index.toInt());
                if (pageInfo) {
                    pageInfo.params = (options?.params === undefined ? undefined : options?.params);
                }
            }
        }
    }

    back(index: int, param?: jsonx.JsonElement): void {
        let paramsInner = RouterImpl.StringifyParams(param);
        RouterExtender.back(index, paramsInner);
        if (index >= 1 && index <= this.showingPageIndex) {
            let pageInfo = this.visiblePages.at(index - 1);
            if (pageInfo) {
                pageInfo.params = param;
            }
        }
    }

    clear(): void {
        InteropNativeModule._NativeLog("AceRouter: router clear")
        if (this.peerNodeList.length <= 1) {
            RouterExtender.clear();
            return;
        }
        RouterExtender.clear();
    }

    getParams(): jsonx.JsonElement {
        let curPage = this.visiblePages.at(this.showingPageIndex)
        return curPage.params !== undefined ? curPage.params! : new jsonx.JsonElement()
    }

    getLength(): string {
        return String(this.visiblePages.length)
    }

    getStackSize(): int {
        return this.visiblePages.length
    }

    getState(): router.RouterState {
        let curPage = this.visiblePages.at(this.showingPageIndex)
        // routerState index is started from 1. 
        let state: router.RouterState = {
            index: this.showingPageIndex + 1,
            name: curPage.url,
            path: curPage.path,
            params: curPage.params !== undefined ? curPage.params! : new jsonx.JsonElement()
        } as router.RouterState
        return state
    }

    getStateByIndex(index: int): router.RouterState | undefined {
        if (index > this.showingPageIndex + 1 || index <= 0) {
            return undefined
        }
        let page = this.visiblePages.at(index - 1);
        let state: router.RouterState = {
            index: index,
            name: page.url,
            path: page.path,
            params: page.params !== undefined ? page.params! : new jsonx.JsonElement()
        } as router.RouterState
        return state
    }

    getStateByUrl(url: string): Array<router.RouterState> {
        let retVal: Array<router.RouterState> = new Array<router.RouterState>()
        this.visiblePages.value.forEach((element, index) => {
            if ((element.path + element.url) === url) {
                // routerState index is started from 1. 
                let state: router.RouterState = {
                    index: index.toInt() + 1,
                    name: element.url,
                    path: element.path,
                    params: element.params !== undefined ? element.params! : new jsonx.JsonElement()
                } as router.RouterState
                retVal.push(state)
            }
        })
        return retVal
    }

    getEntryRootValue(): ComputableState<IncrementalNode> {
        if (this.rootState.length - 1 < 0) {
            InteropNativeModule._NativeLog("get invalid rootValue" + this.rootState.length);
        }
        InteropNativeModule._NativeLog("get normal rootValue" + this.rootState.length);
        return this.rootState.at(this.rootState.length - 1)!
    }

    getPreState(): ComputableState<IncrementalNode> | undefined {
        if (this.rootState.length < 2) {
            return undefined;
        }
        return this.rootState.at(this.rootState.length - 2)!
    }

    runStartPage(options: router.RouterOptions, builder: UserViewBuilder): void {
        let manager = GlobalStateManager.instance
        let stateNode = manager.updatableNode<IncrementalNode>(new IncrementalNode(), (context: StateContext) => {
            const frozen = manager.frozen
            manager.frozen = true
            memoEntry<void>(context, 0, builder)
            manager.frozen = frozen
        })

        let peerNode: PeerNode | undefined = undefined;
        try {
            const incNode = stateNode.value;
            peerNode = findPeerNode(incNode);
        }
        //@ts-ignore
        catch (e: Error) {
            console.log("AceRouter: create page failed, name: " + e.name + " message: " + e.message);
            console.log(e.stack);
        }
        if (peerNode === undefined) {
            InteropNativeModule._NativeLog("AceRouter:create jsView failed");
            return;
        }
        const jsViewNodePtr = peerNode!.peer.ptr
        this.rootState.push(stateNode)
        this.peerNodeList.push(jsViewNodePtr);
        let context = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
        context.getDetachedRootEntryManager().setDetachedRootNode(jsViewNodePtr, stateNode);
        let pagePushTransitionCallback = (jsNode: KPointer) => {
            let index = this.peerNodeList.indexOf(jsNode);
            if (index !== -1) {
                this.peerNodeList.splice(index, 1);
                this.visiblePages.splice(index, 1);
                this.rootState.splice(index, 1);
                this.showingPageIndex = this.showingPageIndex - 1;
            }
        };
        let newPage = new VisiblePage(builder, this.getFileInfo(options.url), this.getPathInfo(options.url), options.params)
        this.entryPage = newPage;
        this.visiblePages.splice(0, 0, newPage)
        let optionsInner: RouterOptionsInner = {
            url: options.url,
            params: RouterImpl.StringifyParams(options.params),
            recoverable: options.recoverable
        };
        let pageOptions: PageRouterOptions = { options: optionsInner };
        RouterExtender.runPage(jsViewNodePtr, pageOptions, pagePushTransitionCallback);
    }

    showAlertBeforeBackPage(options: router.EnableAlertOptions): void {
        RouterExtender.showAlertBeforeBackPage(options.message);
    }

    hideAlertBeforeBackPage(): void {
        RouterExtender.hideAlertBeforeBackPage();
    }

    static getBuilderByName(name: string): EntryPoint {
        return RouterImpl.namedRouter.get(name)!.entryPoint;
    }
}
export function Routed(
    @memo
    initial: () => void,
    moduleName: string,
    initialUrl?: string,
): void {
    let routerImp = new RouterImpl(moduleName)
    // Init default global router.
    router.setRouter(routerImp)
}

export interface InnerRouterState {
    index: number;
    name: string;
    path: string;
    params: string;
}

export class RouterUtil {
    static pushFromDynamic(instanceId: int32, url: string, params: string, linker?: RuntimeLinker): void {
        let context: UIContext = UIContextUtil.getOrCreateUIContextById(instanceId);
        let router = context.getRouter();
        let routerImpl = router.getRouter() as RouterImpl;
        if (!routerImpl) {
            console.log(`AceRouter: failed to getRouter in pushFromDynamic with instanceId: ${instanceId}`)
            return;
        }
        let jsonParams: jsonx.JsonElement | undefined = undefined;
        if (params.length != 0) {
            try {
                jsonParams = JSON.parseJsonElement(params);
            } catch (error) {
                InteropNativeModule._NativeLog(`AceRouter failed to parse params: ${params} error:` + error)
            }
        }
        let options: router.RouterOptions = { url: url, params: jsonParams };
        let backupLinker = routerImpl.GetRuntimeLinker();
        let tempLinker: RuntimeLinker = linker as RuntimeLinker;
        routerImpl.SetRuntimeLinker(linker);
        try {
            router.pushUrl(options);
        } catch (e: Error) {
            console.log("AceRouter: pushUrl failed, name: " + e.name + " message: " + e.message);
            console.log(e.stack);
        }
        routerImpl.SetRuntimeLinker(backupLinker);
    }

    static replaceFromDynamic(instanceId: int32, url: string, params: string, linker?: RuntimeLinker): void {
        let context: UIContext = UIContextUtil.getOrCreateUIContextById(instanceId);
        let router = context.getRouter();
        let routerImpl = router.getRouter() as RouterImpl;
        if (!routerImpl) {
            console.log(`AceRouter: failed to getRouter in replaceFromDynamic with instanceId: ${instanceId}`)
            return;
        }
        let jsonParams: jsonx.JsonElement | undefined = undefined;
        if (params.length != 0) {
            try {
                jsonParams = JSON.parseJsonElement(params);
            } catch (error) {
                InteropNativeModule._NativeLog(`AceRouter failed to parse params: ${params} error:` + error)
            }
        }
        let options: router.RouterOptions = { url: url, params: jsonParams };
        let backupLinker = routerImpl.GetRuntimeLinker();
        let tempLinker: RuntimeLinker = linker as RuntimeLinker;
        routerImpl.SetRuntimeLinker(linker);
        try {
            router.replaceUrl(options);
        } catch (e: Error) {
            console.log("AceRouter: replaceUrl failed, name: " + e.name + " message: " + e.message);
            console.log(e.stack);
        }
        routerImpl.SetRuntimeLinker(backupLinker);
    }

    static backFromDynamic(instanceId: int32, url: string, params: string, linker?: RuntimeLinker): void {
        let context: UIContext = UIContextUtil.getOrCreateUIContextById(instanceId);
        let router = context.getRouter();
        let routerImpl = router.getRouter() as RouterImpl;
        if (!routerImpl) {
            console.log(`AceRouter: failed to getRouter in backFromDynamic with instanceId: ${instanceId}`)
            return;
        }
        let jsonParams: jsonx.JsonElement | undefined = undefined;
        if (params.length != 0) {
            try {
                jsonParams = JSON.parseJsonElement(params);
            } catch (error) {
                InteropNativeModule._NativeLog(`AceRouter failed to parse params: ${params} error:` + error)
            }
        }
        let options: router.RouterOptions = { url: url, params: jsonParams };
        let backupLinker = routerImpl.GetRuntimeLinker();
        let tempLinker: RuntimeLinker = linker as RuntimeLinker;
        routerImpl.SetRuntimeLinker(linker);
        try {
            router.back(options);
        } catch (e: Error) {
            console.log("AceRouter: back failed, name: " + e.name + " message: " + e.message);
            console.log(e.stack);
        }
        routerImpl.SetRuntimeLinker(backupLinker);
    }

    static clearFromDynamic(instanceId: int32, linker?: RuntimeLinker): void {
        let context: UIContext = UIContextUtil.getOrCreateUIContextById(instanceId);
        let router = context.getRouter();
        let routerImpl = router.getRouter() as RouterImpl;
        if (!routerImpl) {
            console.log(`AceRouter: failed to getRouter in clearFromDynamic with instanceId: ${instanceId}`)
            return;
        }
        let backupLinker = routerImpl.GetRuntimeLinker();
        let tempLinker: RuntimeLinker = linker as RuntimeLinker;
        routerImpl.SetRuntimeLinker(linker);
        try {
            router.clear();
        } catch (e: Error) {
            console.log("AceRouter: clear failed, name: " + e.name + " message: " + e.message);
            console.log(e.stack);
        }
        routerImpl.SetRuntimeLinker(backupLinker);
    }

    static getLengthFromDynamic(instanceId: int32): string {
        try {
            let context: UIContext = UIContextUtil.getOrCreateUIContextById(instanceId);
            let router = context.getRouter();
            let routerImpl = router.getRouter() as RouterImpl;
            if (!routerImpl) {
                console.log(`AceRouter: failed to getRouter in getLengthFromDynamic with instanceId: ${instanceId}`)
                return "0";
            }
            let len = routerImpl.getLength();
            return len;
        } catch (e: Error) {
            console.log(`AceRouter: getLength error, name: ${e.name} message: ${e.message}`);
            console.log(e.stack);
            return "0";
        }
    }

    static getStackSizeFromDynamic(instanceId: int32): int32 {
        try {
            let context: UIContext = UIContextUtil.getOrCreateUIContextById(instanceId);
            let router = context.getRouter();
            let routerImpl = router.getRouter() as RouterImpl;
            if (!routerImpl) {
                console.error(`AceRouter: failed to getRouter in getStackSizeFromDynamic with instanceId: ${instanceId}`)
                return 0;
            }
            return routerImpl.getStackSize();
        } catch (e: Error) {
            console.error(`AceRouter: getStackSize error, name: ${e.name} message: ${e.message}`);
            console.error(e.stack);
            return 0;
        }
    }

    static getParamsFromDynamic(instanceId: int32): string {
        try {
            let context: UIContext = UIContextUtil.getOrCreateUIContextById(instanceId);
            let router = context.getRouter();
            let routerImpl = router.getRouter() as RouterImpl;
            if (!routerImpl) {
                console.log(`AceRouter: failed to getRouter in getParamsFromDynamic with instanceId: ${instanceId}`)
                return "";
            }
            let params = routerImpl.getParams();
            let paramsStr = RouterImpl.StringifyParams(params);
            return paramsStr;
        } catch (e: Error) {
            console.log(`AceRouter: getParams error, name: ${e.name} message: ${e.message}`);
            console.log(e.stack);
            return "";
        }
    }

    static getStateByUrlFromDynamic(instanceId: int32, url: string): Array<InnerRouterState> {
        try {
            let context: UIContext = UIContextUtil.getOrCreateUIContextById(instanceId);
            let router = context.getRouter();
            let routerImpl = router.getRouter() as RouterImpl;
            if (!routerImpl) {
                console.log(`AceRouter: failed to getRouter in getStateByUrlFromDynamic with instanceId: ${instanceId}`)
                return new Array<InnerRouterState>();
            }
            let result = new Array<InnerRouterState>();
            let states: Array<router.RouterState> = routerImpl.getStateByUrl(url);
            console.log(`AceRouter: states.length: ${states.length}`);
            for (let i = 0; i < states.length; ++i) {
                let innerState: InnerRouterState = {
                    index: states[i].index,
                    name: states[i].name,
                    path: states[i].path,
                    params: RouterImpl.StringifyParams(states[i].params)
                } as InnerRouterState;
                result.push(innerState);
            }
            return result;
        } catch (e: Error) {
            console.log(`AceRouter: getStateByUrl error, name: ${e.name} message: ${e.message}`);
            console.log(e.stack);
            return new Array<InnerRouterState>();
        }
    }

    static getStateByIndexFromDynamic(instanceId: int32, index: int): InnerRouterState | undefined {
        try {
            let context: UIContext = UIContextUtil.getOrCreateUIContextById(instanceId);
            let router = context.getRouter();
            let routerImpl = router.getRouter() as RouterImpl;
            if (!routerImpl) {
                console.log(`AceRouter: failed to getRouter in getStateByIndexFromDynamic with instanceId: ${instanceId}`)
                return undefined;
            }
            let state: router.RouterState | undefined = routerImpl.getStateByIndex(index);
            if (!state) {
                return undefined;
            }
            let innerState: InnerRouterState = {
                index: state!.index,
                name: state!.name,
                path: state!.path,
                params: RouterImpl.StringifyParams(state!.params)
            } as InnerRouterState;
            return innerState;
        } catch (e: Error) {
            console.log(`AceRouter: getStateByIndex error, name: ${e.name} message: ${e.message}`);
            console.log(e.stack);
            return undefined;
        }
    }

    static getStateFromDynamic(instanceId: int32): InnerRouterState | undefined {
        try {
            let context: UIContext = UIContextUtil.getOrCreateUIContextById(instanceId);
            let router = context.getRouter();
            let routerImpl = router.getRouter() as RouterImpl;
            if (!routerImpl) {
                console.log(`AceRouter: failed to getRouter in getStateFromDynamic with instanceId: ${instanceId}`)
                return undefined;
            }
            let state: router.RouterState = routerImpl.getState();
            let innerState: InnerRouterState = {
                index: state.index,
                name: state.name,
                path: state.path,
                params: RouterImpl.StringifyParams(state.params)
            } as InnerRouterState;
            return innerState;
        } catch (e: Error) {
            console.log(`AceRouter: getState error, name: ${e.name} message: ${e.message}`);
            console.log(e.stack);
            return undefined;
        }
    }
}

@memo
export function CurrentRouter(): Router | undefined {
    return contextLocal<Router>(CURRENT_ROUTER)?.value
}

@memo
export function CurrentRouterTransitionState(): RouterTransitionState | undefined {
    return contextLocal<RouterTransitionState | undefined>(CURRENT_ROUTER_TRANSITION)?.value
}

@memo
export function WithRouterTransitionState(
    transition: RouterTransitionState | undefined,
    @memo
    content: () => void
) {
    contextLocalScope(CURRENT_ROUTER_TRANSITION, transition, content)
}
