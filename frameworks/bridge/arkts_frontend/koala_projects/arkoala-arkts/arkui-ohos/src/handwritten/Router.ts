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
} from "@koalaui/runtime"
import { ArkUINativeModule } from "#components"
import { runtimeType, RuntimeType } from "@koalaui/interop"
import router from "../../ohos.router"
import { EntryPoint, UserView, UserViewBuilder } from "../UserView"
import { InteropNativeModule, nullptr } from "@koalaui/interop"
import { PeerNode } from "../../src/PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { Visibility } from "../component"
import { Serializer } from "../component/peers/Serializer"
//import { RouteType} from "../generated/ArkPageTransitionInterfaces"

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
    version: int32
    private transitionState: MutableState<RouterTransitionState>
    peerNode: PeerNode | undefined

    constructor(
        page: UserViewBuilder,
        version: int32,
        visibility: int32, // TODO: Use RouterTransitionVisibility enum when enums are fixed in Panda
        route?: int32 // TODO: Use RouteType enum when enums are fixed in Panda
    ) {
        this.page = page
        this.version = version
        this.transitionState = mutableState<RouterTransitionState>({ pageId: version, visibility, route } as RouterTransitionState)
        this.peerNode = undefined
    }

    setTransitionState(visibility: int32, route?: int32) {
        this.transitionState.value = { pageId: this.version, visibility, route } as RouterTransitionState
    }

    get transition(): RouterTransitionState {
        return this.transitionState.value
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
        this.visiblePages.push(new VisiblePage(page, this.version.value, VisibilityVisible))
    }
    /** @memo */
    page: UserViewBuilder
    url: string
    params?: Map<string, Object>
    resolve?: (dummy: undefined) => void
    version = mutableState(0)

    updateVisiblePagePeerNode(node: PeerNode, index: number): void {
        InteropNativeModule._NativeLog("AceRouter:enter RouterState UpdateVisiblePagePeerNode")
        this.visiblePages.value[index].updatePeerNode(node)
    }
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

export class PageInfo {
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
    provideClassNameResolver(resolver: PageClassNameResolver): void

    push(url: string, params?: Map<string, Object>): Promise<void>

    replace(url: string, params?: Map<string, Object>): Promise<void>

    back(url?: string, params?: Map<string, Object>): Promise<void>

    clear(): void

    getParam(key: string): Object | undefined

    depth: number

    pageInfo: PageInfo

    onPageTransitionEnd(pageId: int32): void

    UpdateVisiblePagePeerNode(node: PeerNode, index?: number): void
}

const CURRENT_ROUTER = "ohos.arkoala.router"
const CURRENT_ROUTER_TRANSITION = "ohos.arkoala.router.transition"

class RouterImpl implements Router {
    stack = new Array<RouterStackEntry>()
    currentLocals?: Map<string, Object>
    resolver?: PageClassNameResolver
    private readonly state: RouterState
    private readonly moduleName: string

    constructor(state: RouterState, moduleName: string) {
        this.state = state
        this.moduleName = moduleName
    }

    provideClassNameResolver(resolver: PageClassNameResolver): void {
        this.resolver = resolver
    }

    get depth(): number {
        this.state.version.value
        return this.stack.length
    }

    set depth(depth: number) {
        /*
            TODO SHOPPING: readonly properties don't work
         */
    }

    get pageInfo(): PageInfo {
        return new PageInfo(this.stack.length, this.state.url)
    }

    set pageInfo(pageInfo: PageInfo) {
        /*
            TODO SHOPPING: readonly properties don't work
         */
    }

    resolve(route: string): Promise<UserView | EntryPoint> {
        return new Promise<UserView | EntryPoint>(
            (resolvePromise: (value: UserView | EntryPoint) => void, rejectPromise: (e: Error) => void) => {
                let className: string | undefined = "";
                className = this.resolver?.(route)
                if (className) {
                    InteropNativeModule._NativeLog("AceRouter:resolve className: " + route + " " + className)
                    // TODO: parameters.
                    let view = ArkUINativeModule._LoadUserView(className, "")
                    if (view) {
                        resolvePromise(view as UserView)
                    } else {
                        rejectPromise(new Error(`Cannot load class ${className}`))
                    }
                } else {
                    InteropNativeModule._NativeLog("AceRouter:resolve url: " + route);
                    let className: string = this.getClassName(route)
                    InteropNativeModule._NativeLog("AceRouter:resolve generated className: " + className);
                    /** @memo */
                    let entry = this.RunPage(className)
                    if (entry) {
                        resolvePromise(entry)
                    } else {
                        rejectPromise(new Error(`Cannot load class ${className}`))
                    }
                    rejectPromise(new Error(`Unknown URL ${route}`))
                }
        })
    }

    private getClassName(url: string): string {
        let className: string = this.moduleName + "/src/main/ets/" + url + "/__EntryWrapper";
        return className;
    }

    private RunPage(url: string): EntryPoint {
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
        return new EntryPoint()
    }

    pushOrReplace(url: string, push: boolean, params?: Map<string, Object>): Promise<void> {
        return new Promise<void>((
            resolve: (value: undefined) => void,
            reject: (reason: string | undefined) => void
        ): Promise<void> => {
        return this.resolve(url)
            .then<void>((view: UserView | EntryPoint) => {
                if (view instanceof UserView) {
                    InteropNativeModule._NativeLog("AceRouter: load page as UserView")
                    let page: UserViewBuilder = view.getBuilder()
                    if (push) {
                        this.stack.push(new RouterStackEntry(this.state.url, this.state.page, this.state.params))
                    }
                    this.activate(new RouterRegistryEntry(url, page), push ? RouteType_Push : RouteType_None, params, resolve)
                } else if (view instanceof EntryPoint) {
                    InteropNativeModule._NativeLog("AceRouter: load page as EntryPoint")
                    let page = view.entry
                    if (push) {
                        this.stack.push(new RouterStackEntry(this.state.url, this.state.page, this.state.params))
                    }
                    this.activate(new RouterRegistryEntry(url, page), push ? RouteType_Push : RouteType_None, params, resolve)
                }
            })
            .catch<void>((error: string | undefined): void => reject(error))
        })
    }

    showingPage: number = -1
    hidingPage: number = -1

    // TODO: Use RouteType enum as route parameter when enums are fixed in Panda
    private activate(entry: RouterRegistryEntry, route: int32, params: Map<string, Object> | undefined, resolve: (dummy: undefined) => void) {
        const state = this.state
        state.version.value++
        // console.log("activating", RouteType[route], entry.url, "version", state.version.value)
        // let previousVisiblePageIndex = this.findIndexByVersion(state.currentActivePage.value)
        let previousVisiblePageIndex = state.visiblePages.length - 1
        let previousVisiblePage = state.visiblePages.value[previousVisiblePageIndex]
        InteropNativeModule._NativeLog("AceRouter: previousVisiblePage index " + previousVisiblePageIndex);
        if (previousVisiblePage) {
            // previousVisiblePage.setTransitionState(VisibilityHiding, route)
            previousVisiblePage.transition.visibility = VisibilityHidden
            previousVisiblePage.transition.route = RouteType_Pop
            InteropNativeModule._NativeLog("AceRouter: previousVisiblePage visibility " + previousVisiblePage.transition.visibility);
        }
        state.page = entry.page
        state.url = entry.url
        state.params = params
        state.resolve = resolve
        let newVisiblePage: VisiblePage

        switch (route) {
            case RouteType_Push: {
                newVisiblePage = new VisiblePage(entry.page, state.version.value, VisibilityShowing, route)
                state.visiblePages.splice(previousVisiblePageIndex + 1, 0, newVisiblePage)
                let peerNode = state.visiblePages.value[previousVisiblePageIndex].peerNode
                if (peerNode) {
                    InteropNativeModule._NativeLog("AceRouter: push and previous page peerNode set invisible");
                    let visibleValue: Visibility = Visibility.HIDDEN
                    const thisSerializer : Serializer = Serializer.hold()
                    let value_type : int32 = RuntimeType.UNDEFINED
                    value_type = runtimeType(visibleValue)
                    thisSerializer.writeInt8(value_type as int32)
                    if ((RuntimeType.UNDEFINED) != (value_type)) {
                        const value_value  = (visibleValue as Visibility)
                        thisSerializer.writeInt32(TypeChecker.Visibility_ToNumeric(value_value))
                    }
                    ArkUIGeneratedNativeModule._CommonMethod_visibility(peerNode.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
                    thisSerializer.release()
                }
                break
            }
            case RouteType_Pop: {
                const index = this.stack.length // TODO: store uid in registry to find a page
                newVisiblePage = state.visiblePages.value[index]
                newVisiblePage.setTransitionState(VisibilityShowing, route)
                let peerNode = newVisiblePage.peerNode
                if (peerNode) {
                    InteropNativeModule._NativeLog("AceRouter: pop and previous page peerNode set visible");
                    let visibleValue: Visibility = Visibility.VISIBLE
                    const thisSerializer : Serializer = Serializer.hold()
                    let value_type : int32 = RuntimeType.UNDEFINED
                    value_type = runtimeType(visibleValue)
                    thisSerializer.writeInt8(value_type as int32)
                    if ((RuntimeType.UNDEFINED) != (value_type)) {
                        const value_value  = (visibleValue as Visibility)
                        thisSerializer.writeInt32(TypeChecker.Visibility_ToNumeric(value_value))
                    }
                    ArkUIGeneratedNativeModule._CommonMethod_visibility(peerNode.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
                    thisSerializer.release()
                }
                // remove all hidden pages removed from the stack
                for (let i = state.visiblePages.length - 1; i > index; i--) {
                    const visibility = state.visiblePages.value[i].transition.visibility
                    if (visibility == VisibilityHidden) {
                        InteropNativeModule._NativeLog("AceRouter: dispose page, index: " + i)
                        // state.visiblePages.value[i].peerNode?.dispose()
                        state.visiblePages.splice(i, undefined)
                    }
                }
                break
            }
            case RouteType_None: {
                // TODO: can/shall we animate replace?
                newVisiblePage = new VisiblePage(entry.page, state.version.value, VisibilityShowing, route)
                state.visiblePages.set(previousVisiblePageIndex, newVisiblePage)
                break
            }
            default:
                throw new Error("Illegal RouteType: " + route)
        }
        this.hidingPage = previousVisiblePage?.version ?? -1
        this.showingPage = newVisiblePage.version
        state.currentActivePage.value = newVisiblePage.version
    }

    findIndexByVersion(version: int32): int32 {
        const array = this.state.visiblePages
        const length = array.length
        for (let i = 0; i < length; i++) {
            if (array.value[i].version == version) return i
        }
        return -1
    }

    onPageTransitionEnd(pageId: int32): void {
        const index = this.findIndexByVersion(pageId)
        if (index < 0) return
        const page = this.state.visiblePages.value[index]
        if (page.transition.visibility == VisibilityShowing) {
            if (pageId == this.state.currentActivePage.value) {
                console.log("PAGE VISIBLE:", page.transition.pageId)
                page.setTransitionState(VisibilityVisible)
            } else {
                page.setTransitionState(VisibilityHidden)
            }
        } else if (page.transition.visibility == VisibilityHiding) {
            if (index < this.stack.length) {
                console.log("PAGE HIDDEN:", page.transition.pageId)
                page.setTransitionState(VisibilityHidden)
            } else {
                console.log("PAGE REMOVED:", page.transition.pageId)
                this.state.visiblePages.splice(index, 1)
            }
        }
        // else {
        //     // console.log("ERROR: no page transition:", RouterTransitionVisibility[page.transition.visibility], page.transition.route ? RouteType[page.transition.route] : "unknown")
        // }
    }

    UpdateVisiblePagePeerNode(node: PeerNode, index: number = -1): void {
        InteropNativeModule._NativeLog("AceRouter: router UpdateVisiblePagePeerNode, index: " + index)
        if (index == -1) {
            index = this.state.visiblePages.length - 1
        }
        if (index < 0) {
            InteropNativeModule._NativeLog("AceRouter: router page size is zero")
            return;
        }
        this.state.updateVisiblePagePeerNode(node, index)
    }

    push(url: string, params?: Map<string, Object>): Promise<void> {
        InteropNativeModule._NativeLog("AceRouter: router push")
        return this.pushOrReplace(url, true, params)
    }

    replace(url: string, params?: Map<string, Object>): Promise<void> {
        return this.pushOrReplace(url, false, params)
    }

    back(url?: string, params?: Map<string, Object>): Promise<void> {
        InteropNativeModule._NativeLog("AceRouter: router back")
        return new Promise<void>((
            resolve: (dummy: undefined) => void,
            reject: (reason: string | undefined) => void
        ): void => {
            let entry: RouterStackEntry | undefined = undefined
            if (url) {
                for (let i = this.stack.length - 1; i >= 0; i--) {
                    let element = this.stack[i]
                    if (element.url == url) {
                        entry = element
                        this.stack.splice(i)
                        break
                    }
                }
            } else {
                entry = this.stack.length > 0 ? this.stack.pop() : undefined
            }
            if (entry) {
                this.activate(
                    new RouterRegistryEntry(entry.url, entry.page),
                    RouteType_Pop,
                    params ?? entry.params,
                    resolve
                )
            } else {
                reject(`history is empty`)
            }
        })
    }

    clear(): void {
        InteropNativeModule._NativeLog("AceRouter: router clear")
        for (let i = 0; i < this.state.visiblePages.length - 1; i++) {
            this.state.visiblePages.value[i].peerNode?.dispose();
        }
        if (this.state.visiblePages.length > 1) {
            this.state.visiblePages.splice(0, this.state.visiblePages.length - 1)
        }
        if (this.stack.length > 1) {
            this.stack.splice(0, this.stack.length -1)
        }
    }

    getParam(key: string): Object | undefined {
        return this.state.params?.get(key)
    }
}

/** @memo */
export function Routed(
    /** @memo */
    initial: () => void,
    moduleName: string,
    initialUrl?: string,
): void {
    const routerState = remember<RouterState>(() => new RouterState(initial, initialUrl ?? "_initial_"))
    const routerImp = remember<RouterImpl>(() => {
        let routerImp = new RouterImpl(routerState, moduleName)
        // Install default global router.
        router.setRouter(routerImp)
        return routerImp
    })
    RunEffect<((dummy: undefined) => void) | undefined>(routerState.resolve, (resolve?: (dummy: undefined) => void): void => { resolve?.(undefined) })
    contextLocalScope(CURRENT_ROUTER, routerImp, () => {
        RepeatByArray(
            routerState.visiblePages.value,
            (page: VisiblePage, index: int32): int32 => { return page.version },
            (page: VisiblePage, index: int32): void => {
                WithRouterTransitionState(page.transition, () => {
                    page.page()
                })
            }
        )
    })
}

/** @memo */
export function CurrentRouter(): Router | undefined {
    return contextLocal<Router>(CURRENT_ROUTER)?.value
}

/** @memo */
export function CurrentRouterTransitionState(): RouterTransitionState | undefined {
    return contextLocal<RouterTransitionState | undefined>(CURRENT_ROUTER_TRANSITION)?.value
}

/** @memo */
export function WithRouterTransitionState(
    transition: RouterTransitionState | undefined,
    /** @memo */
    content: () => void
) {
    contextLocalScope(CURRENT_ROUTER_TRANSITION, transition, content)
}
