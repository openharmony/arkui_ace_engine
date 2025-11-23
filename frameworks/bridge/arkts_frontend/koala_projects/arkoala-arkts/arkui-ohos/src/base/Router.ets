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
import { RouterExtender, PageRouterOptions } from "#generated"
import { UIContextUtil } from "arkui/base/UIContextUtil"
import { UIContextImpl } from "arkui/base/UIContextImpl"
import { AsyncCallback, BusinessError } from "@ohos.base"
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
    params: Object | undefined
    peerNode: PeerNode | undefined

    constructor(
        page: UserViewBuilder,
        url: string,
        path: string,
        params?: Object
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
        params?: Map<string, Object>,
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
    params?: Map<string, Object>
    resolve?: (dummy: undefined) => void
    version = mutableState(0)
}

class RouterStackEntry {
    public url: string
    public page: UserViewBuilder
    public params?: Map<string, Object>

    constructor(
        url: string,
        page: UserViewBuilder,
        params?: Map<string, Object>,
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

    back(index: int, params?: Object): void

    clear(): void

    getLength(): int

    getParams(): Object

    getState(): router.RouterState

    getStateByIndex(index: int): router.RouterState | undefined

    getStateByUrl(url: string): Array<router.RouterState>

    UpdateVisiblePagePeerNode(node: PeerNode, index?: int): void

    getEntryRootValue(): ComputableState<IncrementalNode>

    getPreState(): ComputableState<IncrementalNode> | undefined;

    registerNamedRouter(routerName: string, instance: EntryPoint, param: NavInterface): void;

    runStartPage(options: router.RouterOptions, builder: UserViewBuilder): void

    showAlertBeforeBackPage(options: router.EnableAlertOptions): void

    hideAlertBeforeBackPage(): void
}

const CURRENT_ROUTER = "ohos.arkoala.router"
const CURRENT_ROUTER_TRANSITION = "ohos.arkoala.router.transition"

class RouterImpl implements Router {
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
    private namedRouter: Map<string, EntryPoint> = new Map<string, EntryPoint>

    constructor(moduleName: string) {
        this.moduleName = moduleName
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
            let runtimeLinker = getNearestNonBootRuntimeLinker();
            let entryClass = runtimeLinker?.loadClass(url, false);
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
        const index = this.visiblePages.value.findLastIndex(page => (page.path + page.url) === url);
        if (index === -1) {
            return false;
        }
        const element = this.visiblePages.splice(index, 1);
        const stateNode = this.rootState.splice(index, 1);
        const peerNode = this.peerNodeList.splice(index, 1);
        if (isReplace) {
            this.visiblePages.pop();
            this.rootState.pop();
            this.peerNodeList.pop();
        }
        this.visiblePages.push(element[0]);
        this.rootState.push(stateNode[0]);
        this.peerNodeList.push(peerNode[0]);
        return true;
    }

    registerNamedRouter(routerName: string, instance: EntryPoint, param: NavInterface): void {
        this.namedRouter.set(routerName, instance)
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

    push(options: router.RouterOptions, mode?: router.RouterMode): Promise<void> {
        if (options.url === '/') {
            options.url = this.entryPage?.path! + this.entryPage?.url!;
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
            let pageOptions: PageRouterOptions = { options, mode };
            const jsViewNodePtr = this.peerNodeList.at(this.peerNodeList.length - 1);
            return RouterExtender.push(jsViewNodePtr, pageOptions, pagePushTransitionCallback);
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
            let pageOptions: PageRouterOptions = { options };
            return RouterExtender.push(jsViewNodePtr, pageOptions, pagePushTransitionCallback);
        }
        return Promise.reject({
            code: 100002,
            message: "The uri of router is not exist."});
    }

    pushAsync(options: router.RouterOptions, callback: AsyncCallback<void>, mode?: router.RouterMode): void {
        if (options.url === '/') {
            options.url = this.entryPage?.path! + this.entryPage?.url!;
        }
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
            let pageOptions: PageRouterOptions = { options, mode };
            const jsViewNodePtr = this.peerNodeList.at(this.peerNodeList.length - 1);
            RouterExtender.push(jsViewNodePtr, pageOptions, pagePushTransitionCallback, asyncCallback);
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
            let pageOptions: PageRouterOptions = { options };
            RouterExtender.push(jsViewNodePtr, pageOptions, pagePushTransitionCallback, asyncCallback);
            return;
        }
        let error: BusinessError = new BusinessError(100002,
            "Uri error. The URI of the page to redirect is incorrect or does not exist.");
        callback(error, undefined);
    }

    pushNamedRoute(options: router.NamedRouterOptions, mode?: router.RouterMode): Promise<void> {
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
            let pageOptions: PageRouterOptions = { options: {
                    url: options.name,
                    params: options.params,
                    recoverable: options.recoverable
                },
                mode: mode
            };
            const jsViewNodePtr = this.peerNodeList.at(this.peerNodeList.length - 1);
            return RouterExtender.pushNamedRoute(jsViewNodePtr, pageOptions, pagePushTransitionCallback);
        }
        let className = options.name;
        let entryObject = this.namedRouter.get(className);
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
            let pageOptions: PageRouterOptions = { options: {
                    url: options.name,
                    params: options.params,
                    recoverable: options.recoverable
                }
            };
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
            let pageOptions: PageRouterOptions = { options: {
                    url: options.name,
                    params: options.params,
                    recoverable: options.recoverable
                },
                mode: mode
            };
            const jsViewNodePtr = this.peerNodeList.at(this.peerNodeList.length - 1);
            RouterExtender.pushNamedRoute(jsViewNodePtr, pageOptions, pagePushTransitionCallback, asyncCallback);
            return;
        }
        let className = options.name;
        let entryObject = this.namedRouter.get(className);
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
            let pageOptions: PageRouterOptions = { options: {
                    url: options.name,
                    params: options.params,
                    recoverable: options.recoverable
                }
            };
            RouterExtender.pushNamedRoute(jsViewNodePtr, pageOptions, pagePushTransitionCallback, asyncCallback);
            return;
        }
        let error: BusinessError = new BusinessError(100004,
            "Named route error. The named route does not exist.");
        callback(error, undefined);
    }

    replace(options: router.RouterOptions, mode?: router.RouterMode): Promise<void> {
        if (options.url === '/') {
            options.url = this.entryPage?.path! + this.entryPage?.url!;
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
            let pageOptions: PageRouterOptions = { options, mode };
            const jsViewNodePtr = this.peerNodeList.at(this.peerNodeList.length - 1);
            return RouterExtender.replace(jsViewNodePtr, pageOptions, pagePushTransitionCallback);
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
            let pageOptions: PageRouterOptions = { options };
            return RouterExtender.replace(jsViewNodePtr, pageOptions, pageEnterTransitionCallback);
        }
        return Promise.reject({
            code: 200002,
            message: "Uri error. The URI of the page to be used for replacement is incorrect or does not exist."
        });
    }

    replaceAsync(options: router.RouterOptions, callback: AsyncCallback<void>, mode?: router.RouterMode): void {
        if (options.url === '/') {
            options.url = this.entryPage?.path! + this.entryPage?.url!;
        }
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
            let pageOptions: PageRouterOptions = { options, mode };
            const jsViewNodePtr = this.peerNodeList.at(this.peerNodeList.length - 1);
            RouterExtender.replace(jsViewNodePtr, pageOptions, pagePushTransitionCallback, asyncCallback);
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
            let pageOptions: PageRouterOptions = { options };
            if (mode != undefined) {
                pageOptions.mode = mode;
            }
            RouterExtender.replace(jsViewNodePtr, pageOptions, pageEnterTransitionCallback, asyncCallback);
            return;
        }
        let error: BusinessError = new BusinessError(200002,
            "Uri error. The URI of the page to be used for replacement is incorrect or does not exist.");
        callback(error, undefined);
    }

    replaceNamedRoute(options: router.NamedRouterOptions, mode?: router.RouterMode): Promise<void> {
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
            let pageOptions: PageRouterOptions = { options: {
                    url: options.name,
                    params: options.params,
                    recoverable: options.recoverable
                },
                mode: mode
            };
            const jsViewNodePtr = this.peerNodeList.at(this.peerNodeList.length - 1);
            return RouterExtender.replaceNamedRoute(jsViewNodePtr, pageOptions, pagePushTransitionCallback);
        }
        let className = options.name;
        let entryObject = this.namedRouter.get(className);
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
            let pageOptions: PageRouterOptions = { options: {
                    url: options.name,
                    params: options.params,
                    recoverable: options.recoverable
                }
            };
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
            let pageOptions: PageRouterOptions = { options: {
                    url: options.name,
                    params: options.params,
                    recoverable: options.recoverable
                },
                mode: mode
            };
            const jsViewNodePtr = this.peerNodeList.at(this.peerNodeList.length - 1);
            RouterExtender.replaceNamedRoute(jsViewNodePtr, pageOptions, pagePushTransitionCallback, asyncCallback);
            return;
        }
        let className = options.name;
        let entryObject = this.namedRouter.get(className);
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
            let pageOptions: PageRouterOptions = { options: {
                    url: options.name,
                    params: options.params,
                    recoverable: options.recoverable
                }
            };
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
        RouterExtender.back(options);
        if (options) {
            let url = options?.url;
            let index = this.visiblePages.value.findLastIndex(element => (element.path + element.url) === url);
            if (index != -1) {
                let pageInfo = this.visiblePages.at(index);
                if (pageInfo) {
                    pageInfo.params = (options?.params === undefined ? undefined : options?.params);
                }
            }
        }
    }

    back(index: int, param?: object): void {
        RouterExtender.back(index, param);
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

    getParams(): Object {
        let curPage = this.visiblePages.at(this.showingPageIndex)
        return curPage.params !== undefined ? curPage.params! : new Object()
    }

    getLength(): int {
        return this.visiblePages.length
    }

    getState(): router.RouterState {
        let curPage = this.visiblePages.at(this.showingPageIndex)
        // routerState index is started from 1. 
        let state: router.RouterState = {
            index: this.showingPageIndex + 1,
            name: curPage.url,
            path: curPage.path,
            params: curPage.params !== undefined ? curPage.params! : new Object()
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
            params: page.params !== undefined ? page.params! : new Object()
        } as router.RouterState
        return state
    }

    getStateByUrl(url: string): Array<router.RouterState> {
        let retVal: Array<router.RouterState> = new Array<router.RouterState>()
        this.visiblePages.value.forEach((element, index) => {
            if ((element.path + element.url) === url) {
                // routerState index is started from 1. 
                let state: router.RouterState = {
                    index: index + 1,
                    name: element.url,
                    path: element.path,
                    params: element.params !== undefined ? element.params! : new Object()
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
        let pageOptions: PageRouterOptions = { options };
        RouterExtender.runPage(jsViewNodePtr, pageOptions, pagePushTransitionCallback);
    }

    showAlertBeforeBackPage(options: router.EnableAlertOptions): void {
        RouterExtender.showAlertBeforeBackPage(options.message);
    }

    hideAlertBeforeBackPage(): void {
        RouterExtender.hideAlertBeforeBackPage();
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
