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
import { __memo_context_type , __memo_id_type  } from "arkui.stateManagement.runtime";
import {
    MutableState,
    contextLocal,
    contextLocalScope,
    mutableState,
    remember,
    RepeatByArray,
    arrayState,
    RunEffect,
    __context, 
    __id,
    memoEntry,
    GlobalStateManager,
    StateContext,
    ComputableState,
} from "@koalaui/runtime"
import { ArkUINativeModule } from "#components"
import { KPointer, runtimeType, RuntimeType } from "@koalaui/interop"
import router from "@ohos/router"
import { EntryPoint, UserView, UserViewBuilder } from "../UserView"
import { InteropNativeModule, nullptr } from "@koalaui/interop"
import { PeerNode } from "../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { Visibility } from "../component"
import { Serializer } from "../component/peers/Serializer"
import { RouterExtender } from "./ArkRouterExtenderMaterialized"

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

    getEntryRootValue(): Array<ComputableState<PeerNode>>

    runPage(options: router.RouterOptions, builder: UserViewBuilder): void
}

class ArkRouter implements Router {
    private readonly moduleName: string
    private peerNodeList = new Array<KPointer>
    public readonly visiblePages = arrayState<VisiblePage>()
    private showingPageIndex : number = 0
    private rootState: Array<ComputableState<PeerNode>> = new Array<ComputableState<PeerNode>>()

    constructor(moduleName: string) {
        this.moduleName = moduleName
    }

    private getClassName(url: string): string {
        let className: string = this.moduleName + "/src/main/ets/" + url + "/__EntryWrapper";
        return className;
    }

    private getPathInfo(url: string): string {
        let pathInfo = this.moduleName + "/src/main/ets/" + url + ".js"
        return pathInfo
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
        let className = this.getClassName(options.url)
        let entryObject = this.RunPage(className)
        if (entryObject) {
            let manager = GlobalStateManager.instance
            let peerNode = PeerNode.generateRootPeer()
            let stateNode = manager.updatableNode<PeerNode>(peerNode, (context: StateContext) => {
                const frozen = manager.frozen
                manager.frozen = true
                memoEntry<void>(context, 0, () => {
                    entryObject!.entry()
                })
                manager.frozen = frozen
            })
            this.rootState.push(stateNode)
            let pageNode = RouterExtender.routerPush(options)
            if (pageNode === nullptr) {
                InteropNativeModule._NativeLog("AceRouter:push page failed")
                this.rootState.pop()
                return
            }
            this.peerNodeList.splice(this.peerNodeList.length, 0, pageNode)

            let newPage = new VisiblePage(entryObject.entry, options.url, this.getPathInfo(options.url), options.params)
            this.visiblePages.splice(this.showingPageIndex + 1, 0, newPage)
            this.showingPageIndex += 1
        }
    }

    replace(options: router.RouterOptions): void {
        let className = this.getClassName(options.url)
        let entryObject = this.RunPage(className)
        if (entryObject) {
            let manager = GlobalStateManager.instance
            let peerNode = PeerNode.generateRootPeer()
            let stateNode = manager.updatableNode<PeerNode>(peerNode, (context: StateContext) => {
                const frozen = manager.frozen
                manager.frozen = true
                memoEntry<void>(context, 0, () => {
                    entryObject!.entry()
                })
                manager.frozen = frozen
            })
            
            this.rootState.push(stateNode)
            let pageTransiTionFinishCallback = () => {
                this.peerNodeList.splice(this.showingPageIndex - 1, 1)
                this.visiblePages.splice(this.showingPageIndex - 1, 1)
                let preNodeList = this.rootState.splice(this.showingPageIndex - 1, 1)
                if (preNodeList.length > 0 &&  preNodeList[0]) {
                    preNodeList[0].dispose();
                }
                this.showingPageIndex -= 1
            }
            let pageNode = RouterExtender.routerReplace(options, pageTransiTionFinishCallback)
            if (pageNode === nullptr) {
                InteropNativeModule._NativeLog("AceRouter:replace page failed")
                this.rootState.pop()
                return
            }
            this.peerNodeList.push(pageNode)

            let newPage = new VisiblePage(entryObject.entry, options.url, this.getPathInfo(options.url), options.params)
            this.visiblePages.push(newPage)
            this.showingPageIndex += 1
        }
    }

    pushUrl(options: router.RouterOptions): Promise<void> {
        return new Promise<void>(() => {})
    }

    back(options?: router.RouterOptions): void {
        if (this.peerNodeList.length <= 1) {
            return;
        }
        this.showingPageIndex = this.showingPageIndex - 1
        this.peerNodeList.pop()
        RouterExtender.routerBack(options)
        this.visiblePages.pop()
        let preNode = this.rootState.pop()
        if (preNode) {
            preNode?.dispose();
        }
    }

    clear(): void {
        InteropNativeModule._NativeLog("AceRouter: router clear")
        if (this.peerNodeList.length <= 1) {
            return;
        }
        this.peerNodeList.splice(0, this.showingPageIndex)
        this.visiblePages.splice(0, this.showingPageIndex)
        this.rootState.splice(0, this.showingPageIndex)
        RouterExtender.routerClear();
        this.showingPageIndex = 0
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
        let state: router.RouterState = {
            index: this.showingPageIndex,
            name: curPage.url,
            path: curPage.path,
            params: curPage.params !== undefined ? curPage.params! : new Object()
        } as router.RouterState
        return state
    }

    getStateByIndex(index: number): router.RouterState | undefined {
        if (index > this.showingPageIndex) {
            return undefined
        }
        let page = this.visiblePages.at(index)
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
                let state: router.RouterState = {
                    index: index,
                    name: element.url,
                    path: element.path,
                    params: element.params !== undefined ? element.params! : new Object()
                } as router.RouterState
                retVal.push(state)
            }
        })
        return retVal
    }

    getEntryRootValue(): Array<ComputableState<PeerNode>> {
        return this.rootState
    }

    runPage(options: router.RouterOptions, builder: UserViewBuilder): void {
        let manager = GlobalStateManager.instance
        let peerNode = PeerNode.generateRootPeer()
        let stateNode = manager.updatableNode<PeerNode>(peerNode, (context: StateContext) => {
            const frozen = manager.frozen
            manager.frozen = true
            memoEntry<void>(context, 0, builder)
            manager.frozen = frozen
        })

        let pageNode = RouterExtender.routerRunPage(options)
        let node: PeerNode = stateNode.value
        this.rootState.push(stateNode)
        this.peerNodeList.splice(this.peerNodeList.length, 0, pageNode)

        let newPage = new VisiblePage(builder, options.url, this.getPathInfo(options.url), options.params)
        this.visiblePages.splice(0, 0, newPage)
        this.visiblePages.value[this.showingPageIndex].updatePeerNode(node)
        RouterExtender.moveCommonUnderPageNode(node.peer.ptr, this.peerNodeList[this.showingPageIndex])
    }
}

export function Routed(
    /** @memo */
    initial: () => void,
    moduleName: string,
    rootPeer: PeerNode,
    initialUrl?: string,
): void {
    let routerImp = new ArkRouter(moduleName)
    // Install default global router.
    router.setRouter(routerImp)
}
