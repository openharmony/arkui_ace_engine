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
    scheduleCallback,
} from "@koalaui/runtime"
import OhosRouter from "../ohos/router"
import { UserViewBuilder, UserView } from "../UserView"
import { ArkUINativeModule } from "#components"
import { CommonMethod, CustomBuilder, Dimension, LayoutSafeAreaEdge, LayoutSafeAreaType, Length, NavBarPosition, NavContentInfo, NavigationAnimatedTransition, NavigationCommonTitle, NavigationCustomTitle, NavigationMenuItem, NavigationMode, NavigationOperation, NavigationTitleMode, NavigationTitleOptions, NavigationToolbarOptions, PixelMap, Resource, ResourceStr, SymbolGlyphModifier, SystemBarStyle, ToolbarItem } from "../generated"
import { RouteType } from "../generated"

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
    version: int32
    private transitionState: MutableState<RouterTransitionState>

    constructor(
        page: UserViewBuilder,
        version: int32,
        visibility: RouterTransitionVisibility,
        route?: RouteType
    ) {
        this.page = page
        this.version = version
        this.transitionState = mutableState<RouterTransitionState>({ pageId: version, visibility, route } as RouterTransitionState)
    }

    setTransitionState(visibility: RouterTransitionVisibility, route?: RouteType) {
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
        page: UserViewBuilder,
        url: string,
        params?: Map<string, Object>,
        resolve?: (dummy: undefined) => void
    ) {
        this.page = page
        this.url = url
        this.params = params
        this.resolve = resolve
        this.visiblePages.push(new VisiblePage(page, this.version.value, RouterTransitionVisibility.Visible))
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
    provideClassNameResolver(resolver: PageClassNameResolver): void

    push(url: string, params?: Map<string, Object>): Promise<void>

    replace(url: string, params?: Map<string, Object>): Promise<void>

    back(url?: string, params?: Map<string, Object>): Promise<void>

    clear(): void

    getParam(key: string): Object | undefined

    depth: number

    routerPage: RouterPage

    onPageTransitionEnd(pageId: int32, targetVisibility: RouterTransitionVisibility): void
    schedulePageTransition(pageId: int32, transition: PageTransition): void
}

const CURRENT_ROUTER = "ohos.arkoala.router"
const CURRENT_ROUTER_TRANSITION = "ohos.arkoala.router.transition"

class RouterImpl implements Router {
    stack = new Array<RouterStackEntry>()
    currentLocals?: Map<string, Object>
    resolver?: PageClassNameResolver
    private readonly state: RouterState

    constructor(state: RouterState) {
        this.state = state
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

    get routerPage(): RouterPage {
        return new RouterPage(this.stack.length, this.state.url)
    }

    set routerPage(page: RouterPage) {
        /*
            TODO SHOPPING: readonly properties don't work
         */
    }

    resolve(route: string): Promise<UserView> {
        return new Promise<UserView>(
            (resolvePromise: (value: UserView) => void, rejectPromise: (e: Error) => void) => {
                let rejectIssueMessage = `Unknown URL ${route}`
                let className = this.resolver?.(route)
                if (className) {
                    rejectIssueMessage = `missing user linker`
                    const linker = getNearestNonBootRuntimeLinker()
                    if (linker) {
                        rejectIssueMessage = `Cannot load class ${className}`
                        const cls = linker.loadClass(className, true);
                        const view = cls.createInstance();
                        resolvePromise(view as UserView);
                        return
                    }
                }
            rejectPromise(new Error(rejectIssueMessage));
        })
    }

    pushOrReplace(url: string, push: boolean, params?: Map<string, Object>): Promise<void> {
        return new Promise<void>((
            resolve: (value: undefined) => void,
            reject: (reason: string | undefined) => void
        ): Promise<void> => {
            return this.resolve(url)
                .then<void>((view: UserView) => {
                    let page: UserViewBuilder = view.getBuilder()
                    if (push) {
                        this.stack.push(new RouterStackEntry(this.state.url, this.state.page, this.state.params))
                    }
                    this.activate(new RouterRegistryEntry(url, page), push ? RouteType.Push : RouteType.None, params, resolve)
                })
                .catch<void>((error: string | undefined): void => reject(error))
        })
    }

    showingPage: number = -1
    hidingPage: number = -1

    private activate(entry: RouterRegistryEntry, route: RouteType, params: Map<string, Object> | undefined, resolve: (dummy: undefined) => void) {
        const state = this.state
        state.version.value++

        let previousVisiblePageIndex = this.findIndexByVersion(state.currentActivePage.value)
        let previousVisiblePage = state.visiblePages.value[previousVisiblePageIndex]
        if (previousVisiblePage) previousVisiblePage.setTransitionState(RouterTransitionVisibility.Hiding, route)
        state.page = entry.page
        state.url = entry.url
        state.params = params
        state.resolve = resolve
        let newVisiblePage: VisiblePage

        switch (route.valueOf()) {
            case RouteType.Push.valueOf(): {
                newVisiblePage = new VisiblePage(entry.page, state.version.value, RouterTransitionVisibility.Showing, route)
                state.visiblePages.splice(previousVisiblePageIndex + 1, 0, newVisiblePage)
                break
            }
            case RouteType.Pop.valueOf(): {
                const index = this.stack.length // Improve: store uid in registry to find a page
                newVisiblePage = state.visiblePages.value[index]
                newVisiblePage.setTransitionState(RouterTransitionVisibility.Showing, route)
                // remove all hidden pages removed from the stack
                for (let i = state.visiblePages.length - 1; i > index; i--) {
                    const visibility = state.visiblePages.value[i].transition.visibility
                    if (visibility == RouterTransitionVisibility.Hidden) {
                        state.visiblePages.splice(i, undefined)
                    }
                }
                break
            }
            case RouteType.None.valueOf(): {
                // Improve: can/shall we animate replace?
                newVisiblePage = new VisiblePage(entry.page, state.version.value, RouterTransitionVisibility.Showing, route)
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

    private pageTransitionMap = new Map<int32, Array<PageTransition>>()

    schedulePageTransition(pageId: int32, transition: PageTransition): void {
        let queuedTransitions = this.pageTransitionMap.get(pageId)
        if (queuedTransitions === undefined) {
            queuedTransitions = new Array<PageTransition>()
            this.pageTransitionMap.set(pageId, queuedTransitions)
        }

        const length = queuedTransitions.length
        queuedTransitions.splice(length, 0, transition)

        if (length == 0) {
            scheduleCallback(transition)
        }
    }

    onPageTransitionEnd(pageId: int32, targetVisibility: RouterTransitionVisibility): void {
        const index = this.findIndexByVersion(pageId)
        if (index < 0) return
        const page = this.state.visiblePages.value[index]
        if (page.transition.visibility == targetVisibility) {
            if (page.transition.visibility == RouterTransitionVisibility.Showing) {
                if (pageId == this.state.currentActivePage.value) {
                    console.log("PAGE VISIBLE:", page.transition.pageId)
                    page.setTransitionState(RouterTransitionVisibility.Visible)
                } else {
                    page.setTransitionState(RouterTransitionVisibility.Hidden)
                }
            } else if (page.transition.visibility == RouterTransitionVisibility.Hiding) {
                if (index < this.stack.length) {
                    console.log("PAGE HIDDEN:", page.transition.pageId)
                    page.setTransitionState(RouterTransitionVisibility.Hidden)
                } else {
                    console.log("PAGE REMOVED:", page.transition.pageId)
                    this.state.visiblePages.splice(index, 1)
                }
            } else {
                console.log("ERROR: no page transition: pageId = ", pageId, ", visibility = ", page.transition.visibility)
            }
        } // Otherwise ignore transition because it has been updated during this animation period
    }

    push(url: string, params?: Map<string, Object>): Promise<void> {
        return this.pushOrReplace(url, true, params)
    }

    replace(url: string, params?: Map<string, Object>): Promise<void> {
        return this.pushOrReplace(url, false, params)
    }

    back(url?: string, params?: Map<string, Object>): Promise<void> {
        return new Promise<void>((
            resolve: (value: undefined) => void,
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
                    RouteType.Pop,
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

@memo
export function Routed(
    @memo
    initial: () => void,
    initialUrl?: string,
): void {
    const routerState = remember<RouterState>((): RouterState => new RouterState(initial, initialUrl ?? "_initial_"))
    const router = remember<RouterImpl>((): RouterImpl => {
        let router = new RouterImpl(routerState)
        // Install default global router.
        OhosRouter.setRouter(router)
        return router
    })
    RunEffect<((dummy: undefined) => void) | undefined>(routerState.resolve,
        (resolve?: (dummy: undefined) => void): void => { resolve?.(undefined) })
    contextLocalScope(CURRENT_ROUTER, router, (): void => {
        RepeatByArray(
            routerState.visiblePages.value,
            (page: VisiblePage, index: int32): int32 => { return page.version },
            (page: VisiblePage, index: int32): void => {
                WithRouterTransitionState(page.transition, (): void => {
                    page.page()
                })
            }
        )
    })
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
