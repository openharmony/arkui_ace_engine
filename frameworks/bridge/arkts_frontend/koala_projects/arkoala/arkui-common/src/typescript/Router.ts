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
    RunEffect,
    contextLocal,
    contextLocalScope,
    mutableState,
    remember,
    RepeatByArray,
    arrayState,
    scheduleCallback,
} from "@koalaui/runtime"

export enum RouterTransitionVisibility {
    Hidden,
    Visible,
    Showing,
    Hiding,
}

enum RouteType {
    NONE,
    None = NONE,
    PUSH = 1,
    Push = PUSH,
    POP = 2,
    Pop = POP,
}

export type MemoFunction =
/** @memo */
() => void

export interface RouterTransitionState {
    readonly visibility: RouterTransitionVisibility
    readonly pageId: int32
    readonly route?: RouteType
}

class VisiblePage {
    /** @memo */
    page: MemoFunction
    version: number
    private transitionState: MutableState<RouterTransitionState>

    constructor(
        page: MemoFunction,
        version: number,
        visibility: RouterTransitionVisibility,
        route?: RouteType
    ) {
        this.page = page
        this.version = version
        this.transitionState = mutableState<RouterTransitionState>({ pageId: version, visibility, route })
    }

    setTransitionState(visibility: RouterTransitionVisibility, route?: RouteType) {
        this.transitionState.value = { pageId: this.version, visibility, route }
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
        params?: Map<string, any>,
        resolve?: () => void
    ) {
        this.page = page
        this.url = url
        this.params = params
        this.resolve = resolve
        this.visiblePages.push(new VisiblePage(page, this.version.value, RouterTransitionVisibility.Visible))
    }
    /** @memo */
    page: MemoFunction
    url: string
    params?: Map<string, Object>
    resolve?: () => void
    version = mutableState(0)
}

class RouterStackEntry {
    constructor(
        public url: string,
        public page: MemoFunction,
        public params?: Map<string, Object>,
    ) { }
}

class RouterRegistryEntry {
    constructor(
        public url: string,
        public page: MemoFunction
    ) { }
}

/**
 * Descriptor of page in router.
 */
export class PageInfo {
    /**
     * Create new page info.
     *
     * @param depth of page in stack
     * @param page url of the page
     */
    constructor(public depth: number, public page: string) { }
}

export type PageTransition = () => void

/**
 * Interface providing page routing functionality.
 */
export interface Router {
    /**
     * Registers the given UI function to be called when the URL provided is pushed.
     * Router can be accessed with CurrentRouter() function.
     *
     * @see CurrentRouter
     *
     * @param url - locator of the page
     * @param page - UI function to call
     */
    register(
        url: string, page: MemoFunction
    ): void
    /**
     * Set dynamic page resolver.
     */
    provideResolver(resolver: (route: string) => Promise<MemoFunction>): void
    /**
     * Pushes the URL to the history of the router, so that page could become visible.
     * Promise is resolved when the page becomes visible.
     *
     * @param url Pushed the URL to the history of the router.
     * @param params - parameters of the page.
     *
     * @returns - promise resolved when the page is visible
     */
    push(url: string, params?: Map<string, Object>): Promise<void>

    /**
     * Replaces the current page.
     * Promise is resolved when the page becomes visible.
     *
     * @param url Pushed the URL to the history of the router.
     * @param params - parameters of the page.
     *
     * @returns - promise resolved when the page is visible
     */
    replace(url: string, params?: Map<string, Object>): Promise<void>

    /**
     * Navigates back in history.
     *
     *  @param url The URL of a page navigated back to.
     *
     * @returns promise resolved when previous page is visible, or rejected if already on initial page
     */
    back(url?: string, params?: Map<string, Object>): Promise<void>

    /**
     * Clears all historical pages and retains only the current page at the top of the stack.
     */
    clear(): void

    /**
     * Retrieves parameter passed to the page in push() or replace() call.
     *
     * @see push
     * @see replace
     *
     * @param key - the name of the parameter
     */
    getParam(key: string): Object | undefined

    /**
     * Current history depth of the router.
     */
    depth: number

    /**
     * Current page info.
     */
    pageInfo: PageInfo

    onPageTransitionEnd(pageId: int32, targetVisibility: RouterTransitionVisibility): void
    schedulePageTransition(pageId: int32, transition: PageTransition): void
}

const CURRENT_ROUTER = "ohos.arkoala.router"
const CURRENT_ROUTER_TRANSITION = "ohos.arkoala.router.transition"

class RouterImpl implements Router {
    stack = new Array<RouterStackEntry>()
    registry = new Map<string, RouterRegistryEntry>()
    currentLocals?: Map<string, Object>
    resolver?: (route: string) => Promise<MemoFunction>

    constructor(private state: RouterState) { }

    register(url: string, page: MemoFunction): void {
        this.registry.set(url, new RouterRegistryEntry(url, page))
    }

    provideResolver(resolver: (route: string) => Promise<MemoFunction>): void {
        this.resolver = resolver
    }

    get depth(): number {
        this.state.version.value
        return this.stack.length
    }

    get pageInfo(): PageInfo {
        return new PageInfo(this.stack.length, this.state.url)
    }

    pushOrReplace(url: string, push: boolean, params?: Map<string, Object>): Promise<void> {
        return new Promise<void>((resolve, reject) => {
            let entry = this.registry.get(url)
            console.log(push ? "push" : "replace", url, entry)
            if (entry) {
                if (push) {
                    this.stack.push(new RouterStackEntry(this.state.url, this.state.page, this.state.params))
                }
                this.activate(entry, push ? RouteType.Push : RouteType.None, params, resolve)
            } else {
                if (this.resolver) {
                    return this
                        .resolver(url)
                        .then(page => {
                            if (push) {
                                this.stack.push(new RouterStackEntry(this.state.url, this.state.page, this.state.params))
                            }
                            this.activate(new RouterRegistryEntry(url, page), push ? RouteType.Push : RouteType.None, params, resolve)
                        })
                        .catch(error => reject(error))
                }
                console.error(`${url} is not registered`)
                reject(`${url} is not registered`)
            }
        })
    }

    showingPage: number = -1
    hidingPage: number = -1

    private activate(entry: RouterRegistryEntry, route: RouteType, params: Map<string, Object> | undefined, resolve: () => void) {
        const state = this.state
        state.version.value++
        console.log("activating", RouteType[route], entry.url, "version", state.version.value)
        let previousVisiblePageIndex = this.findIndexByVersion(state.currentActivePage.value)
        let previousVisiblePage = state.visiblePages.value[previousVisiblePageIndex]
        if (previousVisiblePage) previousVisiblePage.setTransitionState(RouterTransitionVisibility.Hiding, route)
        state.page = entry.page
        state.url = entry.url
        state.params = params
        state.resolve = resolve
        let newVisiblePage: VisiblePage
        switch (route) {
            case RouteType.Push: {
                newVisiblePage = new VisiblePage(entry.page, state.version.value, RouterTransitionVisibility.Showing, route)
                state.visiblePages.splice(previousVisiblePageIndex + 1, 0, newVisiblePage)
                break
            }
            case RouteType.Pop: {
                const index = this.stack.length // TODO: store uid in registry to find a page
                newVisiblePage = state.visiblePages.value[index]
                newVisiblePage.setTransitionState(RouterTransitionVisibility.Showing, route)
                // remove all hidden pages removed from the stack
                for (let i = state.visiblePages.length - 1; i > index; i--) {
                    const visibility = state.visiblePages.value[i].transition.visibility
                    if (visibility == RouterTransitionVisibility.Hidden) state.visiblePages.splice(i, undefined)
                }
                break
            }
            case RouteType.None: {
                // TODO: can/shall we animate replace?
                newVisiblePage = new VisiblePage(entry.page, state.version.value, RouterTransitionVisibility.Showing, route)
                state.visiblePages.set(previousVisiblePageIndex, newVisiblePage)
                break
            }
            default:
                throw new Error("Illegal ArkRouteType: " + route)
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
            queuedTransitions = []
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
        if (index >= 0) {
            const page = this.state.visiblePages.value[index]
            if (page.transition.visibility == targetVisibility) {
                if (page.transition.visibility == RouterTransitionVisibility.Showing) {
                    if (pageId == this.state.currentActivePage.value) {
                        page.setTransitionState(RouterTransitionVisibility.Visible)
                    } else {
                        console.log("ERROR: showing page cannot be shown:", page.transition.route ? RouteType[page.transition.route] : "unknown")
                        page.setTransitionState(RouterTransitionVisibility.Hidden)
                    }
                } else if (page.transition.visibility == RouterTransitionVisibility.Hiding) {
                    if (index < this.stack.length) {
                        console.log("PAGE HIDDEN:", page.transition.pageId)
                        page.setTransitionState(RouterTransitionVisibility.Hidden)
                    } else {
                            this.state.visiblePages.splice(index, 1)
                            console.log("PAGE REMOVED:", page.transition.pageId)
                    }
                } else {
                    console.log("ERROR: no page transition:", pageId, RouterTransitionVisibility[page.transition.visibility], page.transition.route ? RouteType[page.transition.route] : "unknown")
                }
            } // Otherwise ignore transition because it has been updated during this animation period
        }

        let queuedTransitions = this.pageTransitionMap.get(pageId)
        if (queuedTransitions && queuedTransitions.length > 0) {
            queuedTransitions.splice(0, 1) // Remove current transition
            if (queuedTransitions.length == 0) {
                this.pageTransitionMap.delete(pageId)
            }

            if (queuedTransitions.length > 0) {
                scheduleCallback(queuedTransitions[0])
            }
        }
    }

    push(url: string, params?: Map<string, Object>): Promise<void> {
        return this.pushOrReplace(url, true, params)
    }

    replace(url: string, params?: Map<string, Object>): Promise<void> {
        return this.pushOrReplace(url, false, params)
    }

    back(url?: string, params?: Map<string, Object>): Promise<void> {
        return new Promise<void>((resolve, reject) => {
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
                this.activate(entry, RouteType.Pop, params ?? entry.params, resolve)
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

/** @memo */
export function Routed(
    /** @memo */
    initial: () => void,
    /** @memo */
    contentOwner: (
        /** @memo */
        content: () => void
    ) => void,
    initialUrl?: string,
) {
    const routerState = remember<RouterState>(() => new RouterState(initial, initialUrl ?? "_initial_"))
    const router = remember<RouterImpl>(() => new RouterImpl(routerState))
    RunEffect(routerState.resolve, (resolve?: () => void) => resolve?.())
    contextLocalScope(CURRENT_ROUTER, router, () => {
        contentOwner(
            /** @memo */
            () => {
                RepeatByArray(
                    routerState.visiblePages.value,
                    (page) => page.version,
                    (page: VisiblePage) => {
                        WithRouterTransitionState(page.transition, () => {
                            page.page()
                        })
                    }
                )
            }
        )
    })
}

/**
 * Get the reference to current context's router. Could be undefined, if not in the routed context.
 *
 * @returns the current router if defined
 */
/** @memo */
export function CurrentRouter(): Router | undefined {
    return contextLocal<Router>(CURRENT_ROUTER)?.value
}

/** @memo */
export function CurrentRouterTransitionState(): RouterTransitionState | undefined {
    return contextLocal<RouterTransitionState>(CURRENT_ROUTER_TRANSITION)?.value
}

/**
 * @internal
 */
/** @memo */
export function WithRouterTransitionState(
    transition: RouterTransitionState | undefined,
    /** @memo */
    content: () => void
) {
    contextLocalScope(CURRENT_ROUTER_TRANSITION, transition, content)
}
