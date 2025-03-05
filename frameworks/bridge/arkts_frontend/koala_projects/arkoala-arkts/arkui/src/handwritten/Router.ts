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


import { int32, observableProxyArray } from "@koalaui/common"
import {
    MutableState,
    contextLocal,
    contextLocalScope,
    mutableState
} from "@koalaui/runtime"
import { RouteType} from "../generated"

export enum RouterTransitionVisibility {
    Hidden,
    Visible,
    Showing,
    Hiding,
}

export type MemoFunction =
/** @memo */
    () => void

export interface RouterTransitionState {
    pageId: int32
    visibility: RouterTransitionVisibility
    route?: RouteType
}

class VisiblePage {
    /** @memo */
    page: MemoFunction
    version: int32
    private transitionState: MutableState<RouterTransitionState>

    constructor(
        page: MemoFunction,
        version: int32,
        visibility: RouterTransitionVisibility,
        route?: RouteType
    ) {
        this.page = page
        this.version = version
        this.transitionState = mutableState<RouterTransitionState>({ pageId: version, visibility, route } as RouterTransitionState)
    }

    setTransitionState(visibility: RouterTransitionVisibility, route?: RouteType) {
        this.transitionState.value = { pageId: this.version, visibility, route }
    }

    get transition(): RouterTransitionState {
        return this.transitionState.value
    }
}

class RouterState {
    readonly visiblePages = observableProxyArray<VisiblePage>()
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

    provideResolver(resolver: (route: string) => Promise<MemoFunction>): void

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
    resolver?: (route: string) => Promise<MemoFunction>
    private readonly state: RouterState

    constructor(state: RouterState) {
        this.state = state
    }

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
            resolve: () => void,
            reject: (reason: string | undefined) => void
        ): Promise<void> | undefined => {
            let entry = this.registry.get(url)
            console.log(push ? "push" : "replace", url, entry)
            if (entry) {
                if (push) {
                    this.stack.push(new RouterStackEntry(this.state.url, this.state.page, this.state.params))
                }
                this.activate(entry, push ? RouteType.Push : RouteType.None, params, resolve)
            } else {
                const resolver = this.resolver
                if (resolver !== undefined) {
                    return resolver(url)
                        .then<void>((page: MemoFunction) => {
                            if (push) {
                                this.stack.push(new RouterStackEntry(this.state.url, this.state.page, this.state.params))
                            }
                            this.activate(new RouterRegistryEntry(url, page), push ? RouteType.Push : RouteType.None, params, resolve)
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

    private activate(entry: RouterRegistryEntry, route: RouteType, params: Map<string, Object> | undefined, resolve: () => void) {
        const state = this.state
        state.version.value++
        // console.log("activating", RouteType[route], entry.url, "version", state.version.value)
        let previousVisiblePageIndex = this.findIndexByVersion(state.currentActivePage.value)
        let previousVisiblePage = state.visiblePages[previousVisiblePageIndex]
        if (previousVisiblePage) previousVisiblePage.setTransitionState(RouterTransitionVisibility.Hiding, route)
        state.page = entry.page
        state.url = entry.url
        state.params = params
        state.resolve = resolve
        let newVisiblePage: VisiblePage
        /*
             TODO SHOPPING: transform switch to ifs
         */
        console.log(`TODO SHOPPING: activate`)
        // switch (route) {
        //     case RouteType.Push: {
        //         newVisiblePage = new VisiblePage(entry.page, state.version.value, RouterTransitionVisibility.Showing, route)
        //         state.visiblePages.splice(previousVisiblePageIndex + 1, 0, newVisiblePage)
        //         break
        //     }
        //     case RouteType.Pop: {
        //         const index = this.stack.length // TODO: store uid in registry to find a page
        //         newVisiblePage = state.visiblePages[index]
        //         newVisiblePage.setTransitionState(RouterTransitionVisibility.Showing, route)
        //         // remove all hidden pages removed from the stack
        //         for (let i = state.visiblePages.length - 1; i > index; i--) {
        //             const visibility = state.visiblePages[i].transition.visibility
        //             if (visibility == RouterTransitionVisibility.Hidden) state.visiblePages.splice(i)
        //         }
        //         break
        //     }
        //     case RouteType.None: {
        //         // TODO: can/shall we animate replace?
        //         newVisiblePage = new VisiblePage(entry.page, state.version.value, RouterTransitionVisibility.Showing, route)
        //         state.visiblePages[previousVisiblePageIndex] = newVisiblePage
        //         break
        //     }
        //     default:
        //         throw new Error("Illegal RouteType: " + route)
        // }
        // this.hidingPage = previousVisiblePage?.version ?? -1
        // this.showingPage = newVisiblePage.version
        // state.currentActivePage.value = newVisiblePage.version
    }

    findIndexByVersion(version: int32): int32 {
        const array = this.state.visiblePages
        const length = array.length
        for (let i = 0; i < length; i++) {
            if (array[i].version == version) return i
        }
        return -1
    }

    onPageTransitionEnd(pageId: int32): void {
        const index = this.findIndexByVersion(pageId)
        if (index < 0) return
        const page = this.state.visiblePages[index]
        if (page.transition.visibility == RouterTransitionVisibility.Showing) {
            if (pageId == this.state.currentActivePage.value) {
                console.log("PAGE VISIBLE:", page.transition.pageId)
                page.setTransitionState(RouterTransitionVisibility.Visible)
            } else {
                // console.log("ERROR: showing page cannot be shown:", page.transition.route ? RouteType[page.transition.route] : "unknown")
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
            // console.log("ERROR: no page transition:", RouterTransitionVisibility[page.transition.visibility], page.transition.route ? RouteType[page.transition.route] : "unknown")
        }
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

/** @memo */
// export function Routed(
//     /** @memo */
//     initial: () => void,
//     /** @memo */
//     contentOwner: (
//         /** @memo */
//         content: () => void
//     ) => void,
//     initialUrl?: string,
// ) {
//     const routerState = remember<RouterState>(() => new RouterState(initial, initialUrl ?? "_initial_"))
//     const router = remember<RouterImpl>(() => new RouterImpl(routerState))
//     RunEffect<() => void>(routerState.resolve!, (resolve?: () => void): void => { resolve?.() })
//     contextLocalScope(CURRENT_ROUTER, router, (): void => {
//         contentOwner(
//             /** @memo */
//             (): void => {
//                 RepeatByArray(
//                     routerState.visiblePages,
//                     (page: VisiblePage): int32 => { return page.version },
//                     (page: VisiblePage): void => {
//                         WithRouterTransitionState(page.transition, () => {
//                             page.page()
//                         })
//                     }
//                 )
//             }
//         )
//     })
// }

/** @memo */
export function CurrentRouter(): Router | undefined {
    return contextLocal<Router>(CURRENT_ROUTER)?.value
}

/** @memo */
export function CurrentRouterTransitionState(): RouterTransitionState | undefined {
    return contextLocal<RouterTransitionState>(CURRENT_ROUTER_TRANSITION)?.value
}

/** @memo */
export function WithRouterTransitionState(
    transition: RouterTransitionState | undefined,
    /** @memo */
    content: () => void
) {
    contextLocalScope(CURRENT_ROUTER_TRANSITION, transition, content)
}
