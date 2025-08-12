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

import { int32 } from "@koalaui/common"
import { contextNode, remember, scheduleCallback } from "@koalaui/runtime"
import { PeerNode, PeerNodeType } from "../PeerNode"
import {
    CurrentRouter,
    CurrentRouterTransitionState
} from "./Router"
import {
    ArkPageTransitionData,
    ArkPageTransitionEnterComponent,
    ArkPageTransitionExitComponent,
} from "./ArkPageTransitionData"
import { PageTransitionOptions } from "../generated"

// TODO: import it when panda is fixed.
enum RouterTransitionVisibility {
    Hidden,
    Visible,
    Showing,
    Hiding
}

/** @memo */
function NotifyPageTransition(pageId: int32, style: ArkPageTransitionData, state: RouterTransitionVisibility) {
    const node = contextNode<PeerNode>(PeerNodeType)
    // console.log("NotifyPageTransition: shall notify", "page", pageId, "state is", RouterTransitionVisibility[state])
    const router = CurrentRouter()
    scheduleCallback(() => {
        // TODO: make it driven by actual animation.
        /*
            TODO SHOPPING: time: int32 (params.duration is double)
         */
        // const time: int32 = (style.params.duration ?? 300) + (style.params.delay ?? 0)
        // if (time > 0) {
        //     setTimeout(() => {
        //         router?.onPageTransitionEnd(pageId)
        //     }, time)
        // } else {
        //     router?.onPageTransitionEnd(pageId)
        // }
    })
}

/** @memo */
export function ArkPageTransitionEnter(
    /** @memo */
    style: ((attributes: ArkPageTransitionEnterComponent) => void) | undefined,
    contentUnused: (() => void) | undefined,
    params: PageTransitionOptions /* TODO SHOPPING: it was Partial<PageTransitionOptions> */
) {
    const receiver = remember(() => new ArkPageTransitionEnterComponent(params))
    style?.(receiver)
    const state = CurrentRouterTransitionState()
    if (state !== undefined && state.visibility == RouterTransitionVisibility.Showing) {
        NotifyPageTransition(state.pageId, receiver, RouterTransitionVisibility.Showing)
    }
}

/** @memo */
export function ArkPageTransitionExit(
    /** @memo */
    style: ((attributes: ArkPageTransitionExitComponent) => void) | undefined,
    contentUnused: (() => void) | undefined,
    params: PageTransitionOptions /* TODO SHOPPING: it was Partial<PageTransitionOptions> */
) {
    const receiver = remember(() => new ArkPageTransitionExitComponent(params))
    style?.(receiver)
    const state = CurrentRouterTransitionState()
        if (state !== undefined && state.visibility == RouterTransitionVisibility.Hiding) {
            NotifyPageTransition(state.pageId, receiver, RouterTransitionVisibility.Hiding)
    }
}
