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
import OhosRouter from "../ohos.router"
import { UserView } from "../UserView"
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

export type MemoFunction =
/** @memo */
    () => void

export interface RouterTransitionState {
    pageId: int32
    visibility: int32 // TODO: Use RouterTransitionVisibility enum when enums are fixed in Panda
    route?: int32 // TODO: Use RouteType enum when enums are fixed in Panda
}

class VisiblePage {
    /** @memo */
    page: MemoFunction
    version: int32
    private transitionState: MutableState<RouterTransitionState>

    constructor(
        page: MemoFunction,
        version: int32,
        visibility: int32, // TODO: Use RouterTransitionVisibility enum when enums are fixed in Panda
        route?: int32 // TODO: Use RouteType enum when enums are fixed in Panda
    ) {
        this.page = page
        this.version = version
        this.transitionState = mutableState<RouterTransitionState>({ pageId: version, visibility, route } as RouterTransitionState)
    }

    setTransitionState(visibility: int32, route?: int32) {
        this.transitionState.value = { pageId: this.version, visibility, route } as RouterTransitionState
    }

    get transition(): RouterTransitionState {
        return this.transitionState.value
    }
}

class RouterState {
    readonly visiblePages = arrayState<VisiblePage>()
    currentActivePage = mutableState(0)
    constructor(
        page: MemoFunction,
        url: string,
        params?: Map<string, Object>,
        resolve?: () => void
    ) {
        this.page = page
        this.url = url
        this.params = params
        this.resolve = resolve
        this.visiblePages.push(new VisiblePage(page, this.version.value, VisibilityVisible))
    }
    /** @memo */
    page: MemoFunction
    url: string
    params?: Map<string, Object>
    resolve?: () => void
    version = mutableState(0)
}

class RouterStackEntry {
    public url: string
    public page: MemoFunction
    public params?: Map<string, Object>

    constructor(
        url: string,
        page: MemoFunction,
        params?: Map<string, Object>,
    ) {
        this.url = url
        this.page = page
        this.params = params
    }
}

class RouterRegistryEntry {
    public url: string
    public page: MemoFunction

    constructor(
        url: string,
        page: MemoFunction
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

export interface Router {
    register(
        url: string, page: MemoFunction
    ): void

    provideResolver(resolver: PageRouteResolver): void

    push(url: string, params?: Map<string, Object>): Promise<void>

    replace(url: string, params?: Map<string, Object>): Promise<void>

    back(url?: string, params?: Map<string, Object>): Promise<void>

    clear(): void

    getParam(key: string): Object | undefined

    depth: number

    pageInfo: PageInfo

    onPageTransitionEnd(pageId: int32): void
}

const CURRENT_ROUTER = "ohos.arkoala.router"
const CURRENT_ROUTER_TRANSITION = "ohos.arkoala.router.transition"

class RouterImpl implements Router {
    stack = new Array<RouterStackEntry>()
    registry = new Map<string, RouterRegistryEntry>()
    currentLocals?: Map<string, Object>
    resolver?: PageRouteResolver
    private readonly state: RouterState

    constructor(state: RouterState) {
        this.state = state
    }

    register(url: string, page: MemoFunction): void {
        this.registry.set(url, new RouterRegistryEntry(url, page))
    }

    provideResolver(resolver: PageRouteResolver): void {
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

    pushOrReplace(url: string, push: boolean, params?: Map<string, Object>): Promise<void> {
        return new Promise<void>((
            resolve: (value: undefined) => void,
            reject: (reason: string | undefined) => void
        ): Promise<void> | undefined => {
            let entry = this.registry.get(url)
            console.log(push ? "push" : "replace", url, entry)
            if (entry) {
                if (push) {
                    this.stack.push(new RouterStackEntry(this.state.url, this.state.page, this.state.params))
                }
                // TODO: Use RouteType enum values when enums are fixed in Panda
                this.activate(entry, push ? RouteType_Push : RouteType_None, params, () => resolve(undefined))
            } else {
                const memoPromise = this.resolver?.resolve(url)
                if (memoPromise !== undefined) {
                    return memoPromise
                        .then<void>((view: UserView) => {
                            let page: MemoFunction = view.getBuilder()
                            if (push) {
                                this.stack.push(new RouterStackEntry(this.state.url, this.state.page, this.state.params))
                            }
                            this.activate(new RouterRegistryEntry(url, page), push ? RouteType_Push : RouteType_None, params, () => resolve(undefined))
                        })
                        .catch<void>((error: string | undefined): void => reject(error))
                }
                // console.error(`${url} is not registered`)
                reject(`${url} is not registered`)
            }
            return undefined
        })
    }

    showingPage: number = -1
    hidingPage: number = -1

    // TODO: Use RouteType enum as route parameter when enums are fixed in Panda
    private activate(entry: RouterRegistryEntry, route: int32, params: Map<string, Object> | undefined, resolve: () => void) {
        const state = this.state
        state.version.value++
        // console.log("activating", RouteType[route], entry.url, "version", state.version.value)
        let previousVisiblePageIndex = this.findIndexByVersion(state.currentActivePage.value)
        let previousVisiblePage = state.visiblePages.value[previousVisiblePageIndex]
        if (previousVisiblePage) previousVisiblePage.setTransitionState(VisibilityHiding, route)
        state.page = entry.page
        state.url = entry.url
        state.params = params
        state.resolve = resolve
        let newVisiblePage: VisiblePage

        switch (route) {
            case RouteType_Push: {
                newVisiblePage = new VisiblePage(entry.page, state.version.value, VisibilityShowing, route)
                state.visiblePages.splice(previousVisiblePageIndex + 1, 0, newVisiblePage)
                break
            }
            case RouteType_Pop: {
                const index = this.stack.length // TODO: store uid in registry to find a page
                newVisiblePage = state.visiblePages.value[index]
                newVisiblePage.setTransitionState(VisibilityShowing, route)
                // remove all hidden pages removed from the stack
                for (let i = state.visiblePages.length - 1; i > index; i--) {
                    const visibility = state.visiblePages.value[i].transition.visibility
                    if (visibility == VisibilityHidden) state.visiblePages.splice(i, undefined)
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

    push(url: string, params?: Map<string, Object>): Promise<void> {
        return this.pushOrReplace(url, true, params)
    }

    replace(url: string, params?: Map<string, Object>): Promise<void> {
        return this.pushOrReplace(url, false, params)
    }

    back(url?: string, params?: Map<string, Object>): Promise<void> {
        return new Promise<void>((
            resolve: () => void,
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
        this.stack.splice(0, this.stack.length -1)
    }

    getParam(key: string): Object | undefined {
        return this.state.params?.get(key)
    }
}

export interface PageRouteResolver {
    resolve(route: string): Promise<UserView>
}

class TrivialResolver implements PageRouteResolver {
    private map: Map<string, string>
    constructor(map: Map<string, string>) {
        this.map = map
    }
    resolve(route: string): Promise<UserView> {
        return new Promise<UserView>(
            (resolvePromise: (value: UserView) => void, rejectPromise: (e: Error) => void) => {
            let className = this.map.get(route)
            if (!className) {
                rejectPromise(new Error(`Unknown URL ${route}`))
                return
            }
            // TODO: parameters.
            let view = ArkUINativeModule._LoadUserView(className, "")
            if (!view) {
                rejectPromise(new Error(`Cannot load class ${className}`))
                return
            }
            resolvePromise(view as UserView)
        })
    }
}

/** @memo */
export function Routed(
    /** @memo */
    initial: () => void,
    initialUrl?: string,
): void {
    const routerState = remember<RouterState>(() => new RouterState(initial, initialUrl ?? "_initial_"))
    const router = remember<RouterImpl>(() => {
        let router = new RouterImpl(routerState)
        // Install default global router.
        OhosRouter.setRouter(router)
        router.provideResolver(new TrivialResolver(new Map<string, string>([
            ["page1", "ComExampleTrivialApplication"],
            ["page2", "ComExampleTrivialApplicationPage2"]
        ])))
        return router
    })
    RunEffect<(() => void) | undefined>(routerState.resolve, (resolve?: () => void): void => { resolve?.() })
    contextLocalScope(CURRENT_ROUTER, router, () => {
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
