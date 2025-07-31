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
    GlobalStateManager,
    StateContext,
    ComputableState,
    IncrementalNode,
} from "@koalaui/runtime"
import { ArkUINativeModule } from "#components"
import { KPointer, runtimeType, RuntimeType } from "@koalaui/interop"
import router from "@ohos/router"
import { EntryPoint, UserView, UserViewBuilder } from "arkui/UserView"
import { InteropNativeModule, nullptr } from "@koalaui/interop"
import { findPeerNode, PeerNode } from "../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { JsResultInternal, Visibility } from "../component"
import { Serializer } from "../component/peers/Serializer"
import { RouterExtender } from "./ArkRouterExtenderMaterialized"
import { UIContextImpl } from "./UIContextImpl"
import { UIContextUtil } from "arkui/handwritten/UIContextUtil"

// ----------------------------------------------------------
// TODO: Remove these constants when enums are fixed in Panda
export const VisibilityHidden = 0
export const VisibilityVisible = 1
export const VisibilityShowing = 2
export const VisibilityHiding = 3

const RouteType_NONE = 0
const RouteType_None = 0
const RouteType_PUSH = 1
const RouteType_Push = 1
const RouteType_POP = 2
const RouteType_Pop = 2
// ----------------------------------------------------------

export enum RouterTransitionVisibility {
    Hidden = VisibilityHidden,
    Visible = VisibilityVisible,
    Showing = VisibilityShowing,
    Hiding = VisibilityHiding
}

export interface RouterTransitionState {
    pageId: int32
    visibility: int32 // TODO: Use RouterTransitionVisibility enum when enums are fixed in Panda
    route?: int32 // TODO: Use RouteType enum when enums are fixed in Panda
}

class VisiblePage {
    /** @memo */
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

export interface Router {
    push(options: router.RouterOptions): void

    replace(options: router.RouterOptions): void

    pushUrl(options: router.RouterOptions): Promise<void>

    back(options?: router.RouterOptions): void

    clear(): void

    getLength(): string

    getParams(): Object

    getState(): router.RouterState

    getStateByIndex(index: number): router.RouterState | undefined

    getStateByUrl(url: string): Array<router.RouterState>

    UpdateVisiblePagePeerNode(node: PeerNode, index?: number): void

    getEntryRootValue(): ComputableState<IncrementalNode>

    runStartPage(options: router.RouterOptions, builder: UserViewBuilder): void

    showAlertBeforeBackPage(options: router.EnableAlertOptions): void

    hideAlertBeforeBackPage(): void
}

class RouterImpl implements Router {
    private readonly moduleName: string
    // list of jsViewNode
    private peerNodeList = new Array<KPointer>
    // infos of pages in stack
    public readonly visiblePages = arrayState<VisiblePage>()
    private showingPageIndex : number = 0
    // entry page
    private entryPage: VisiblePage | undefined = undefined;
    // list of container node to contain jsViewNode
    private rootState: Array<ComputableState<IncrementalNode>> = new Array<ComputableState<IncrementalNode>>()

    constructor(moduleName: string) {
        this.moduleName = moduleName
    }

    private getClassName(url: string): string {
        let className: string = this.moduleName + "/src/main/ets/" + url + "/__EntryWrapper";
        return className;
    }

    private getFileInfo(url: string): string {
        let index = url.lastIndexOf('/');
        let result: string = '';
        if (index !== -1) {
            result = url.slice(0, index);
        }
        return result;
    }

    private getPathInfo(url: string): string {
        let index = url.lastIndexOf('/');
        let result: string = '';
        if (index !== -1) {
            result = url.slice(index);
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

    UpdateVisiblePagePeerNode(node: PeerNode, index: number = -1): void {
        InteropNativeModule._NativeLog("AceRouter: router UpdateVisiblePagePeerNode, index: " + index)
        if (index == -1) {
            index = this.visiblePages.length - 1
        }
        if (index < 0 || index > this.showingPageIndex) {
            InteropNativeModule._NativeLog("AceRouter: router page size is incorrect")
            return;
        }
        if (this.visiblePages.length > index && this.peerNodeList.length > index) {
            this.visiblePages.value[index].updatePeerNode(node)
            RouterExtender.moveCommonUnderPageNode(node.peer.ptr, this.peerNodeList[index])
        }
    }

    push(options: router.RouterOptions): void {
        if (options.url === '/') {
            options.url = this.entryPage?.url!;
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
            } catch (e: Error) {
                console.log("AceRouter: create page failed: " + e.stack)
            }
            if (peerNode === undefined) {
                InteropNativeModule._NativeLog("AceRouter:create jsView failed");
                return;
            }
            const jsViewNodePtr = peerNode!.peer.ptr;
            this.rootState.push(stateNode)
            this.peerNodeList.push(jsViewNodePtr);
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
            RouterExtender.routerPush(options, jsViewNodePtr, pagePushTransitionCallback);
        }
    }

    replace(options: router.RouterOptions): void {
        if (options.url === '/') {
            options.url = this.entryPage?.url!;
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
            } catch (e: Error) {
                console.log("AceRouter: create page failed: " + e.stack);
            }
            if (peerNode === undefined) {
                InteropNativeModule._NativeLog("AceRouter:create jsView failed");
                return;
            }
            const jsViewNodePtr = peerNode!.peer.ptr
            this.rootState.push(stateNode);
            this.peerNodeList.push(jsViewNodePtr)
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
            RouterExtender.routerReplace(options, jsViewNodePtr, pageEnterTransitionCallback)
        }
    }

    pushUrl(options: router.RouterOptions): Promise<void> {
        return new Promise<void>(() => {})
    }

    back(options?: router.RouterOptions): void {
        if (this.peerNodeList.length <= 1) {
            RouterExtender.routerBack(options)
            return;
        }
        if (options === undefined) {
            RouterExtender.routerBack(options)
        } else {
            let url = options.url
            if (url === '/') {
                return;
            }
            let removePages = 1;
            let findPage = false;
            for (let i = this.visiblePages.value.length - 2; i >= 0; i--) {
                if (this.visiblePages.value[i].url === url) {
                    findPage = true;
                    break;
                }
                removePages++;
            }
            if (findPage) {
                RouterExtender.routerBack(options);
            }
        }
    }

    clear(): void {
        InteropNativeModule._NativeLog("AceRouter: router clear")
        if (this.peerNodeList.length <= 1) {
            RouterExtender.routerClear();
            return;
        }
        RouterExtender.routerClear();
    }

    getParams(): Object {
        let curPage = this.visiblePages.at(this.showingPageIndex)
        return curPage.params !== undefined ? curPage.params! : new Object()
    }

    getLength(): string {
        return String(this.visiblePages.length)
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

    getStateByIndex(index: number): router.RouterState | undefined {
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
            if (element.url === url) {
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
        return this.rootState.at(this.rootState.length - 1)!
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
        } catch (e: Error) {
            console.log("AceRouter: create page failed: " + e.stack)
        }
        if (peerNode === undefined) {
            InteropNativeModule._NativeLog("AceRouter:create jsView failed");
            return;
        }
        const jsViewNodePtr = peerNode!.peer.ptr
        this.rootState.push(stateNode);
        this.peerNodeList.push(jsViewNodePtr);
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
        RouterExtender.routerRunPage(options, jsViewNodePtr, pagePushTransitionCallback);
    }

    showAlertBeforeBackPage(options: router.EnableAlertOptions): void {
        RouterExtender.routerShowAlertBeforeBackPage(options);
    }

    hideAlertBeforeBackPage(): void {
        RouterExtender.routerHideAlertBeforeBackPage();
    }
}

export function Routed(
    /** @memo */
    initial: () => void,
    moduleName: string,
    initialUrl?: string,
): void {
    let routerImp = new RouterImpl(moduleName)
    // Init default global router.
    router.setRouter(routerImp)
}
