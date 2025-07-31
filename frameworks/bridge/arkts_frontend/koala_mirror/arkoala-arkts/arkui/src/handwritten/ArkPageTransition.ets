import { memo, memo_intrinsic, memo_entry, memo_stable, memo_skip } from "@koalaui/runtime/annotations"
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

import { int32, float32 } from "@koalaui/common"
import { contextNode, remember } from "@koalaui/runtime"
import { PeerNode, PeerNodeType } from "../PeerNode"
import {
    CurrentRouter,
    CurrentRouterTransitionState,
    RouterTransitionVisibility,
    Router,
} from "./Router"
import {
    ArkPageTransitionData,
    ArkPageTransitionEnterComponent,
    ArkPageTransitionExitComponent,
} from "./ArkPageTransitionData"
import { AnimationExtender, Curve, DoubleAnimationParam, PageTransitionCallback, PageTransitionOptions } from "../generated"
import { ArkCommonMethodPeer } from "../generated"
import { ArkComponentRootPeer } from "../generated"
import { SizeOptions } from "../generated"
import { ScaleOptions, TranslateOptions } from "../generated"
import { ArkUINativeModule } from "#components"
import { RouteType, SlideEffect } from "../generated"

interface PageTransitionCommonInterface {
    slide(value: SlideEffect): this
    translate(value: TranslateOptions): this
    scale(value: ScaleOptions): this
    opacity(value: number): this
}
export interface PageTransitionEnterInterface extends PageTransitionCommonInterface {
    onEnter(event: PageTransitionCallback): this
}
export interface PageTransitionExitInterface extends PageTransitionCommonInterface {
    onExit(event: PageTransitionCallback): this
}

const NO_SCALE:ScaleOptions = { x: 1.0, y: 1.0, z: 1.0, centerX: "50%", centerY: "50%" } as ScaleOptions
const ZERO_TRANSLATE:TranslateOptions = { x: 0.0, y: 0.0, z:0.0 } as TranslateOptions
const KEY_PAGE_TRANSITION_PROPERTY = "pageTransitionProperty" // See frameworks/core/components_ng/pattern/stage/page_pattern.cpp

function sizeNotEmpty(size: SizeOptions): boolean {
    const w = size.width !== undefined ? size.width as number : 0
    const h = size.height !== undefined ? size.height as number : 0
    return w > 0 && h > 0
}

// see rosen_render_context.cpp:SlideTransitionEffect in ace_engine
function slideTransition(size: SizeOptions, value: SlideEffect) : TranslateOptions {
    if (sizeNotEmpty(size)) {
        let xOffset:number = 0
        let yOffset:number = 0
        switch (value.valueOf()) {
            case SlideEffect.Left.valueOf():
                xOffset = -(size.width as number)
                break
            case SlideEffect.Right.valueOf():
                xOffset = size.width as number
                break
            case SlideEffect.Top.valueOf():
                yOffset = -(size.height as number)
                break
            case SlideEffect.Bottom.valueOf():
                yOffset = size.height as number
                break
            case SlideEffect.START.valueOf():
                xOffset = -(size.width as number) // Improve: support RTL applications with x = width
                break
            case SlideEffect.END.valueOf():
                xOffset = size.width as number // Improve: support RTL applications with x = -width
                break
        }

        return { x: xOffset, y: yOffset, z: 0 } as TranslateOptions
    } else {
        throw Error("Size is empty of has undefined components")
    }
}

function progressAnimation(state: RouterTransitionVisibility, style: ArkPageTransitionData): DoubleAnimationParam | undefined {
    if (state == RouterTransitionVisibility.Hiding && style._onExit != undefined ||
        state == RouterTransitionVisibility.Showing && style._onEnter != undefined)
    {
        return {
            propertyName: KEY_PAGE_TRANSITION_PROPERTY,
            startValue: 0 as float32,
            endValue: 1.0 as float32,
            duration: (style.params.duration ?? 0) as int32,
            delay: (style.params.delay ?? 0) as int32,
            curve: style.params.curve ?? Curve.EASE_OUT,
            onProgress: (state == RouterTransitionVisibility.Hiding && style._onExit != undefined) ?
                (progress: float32) => style._onExit!(RouteType.Pop, progress) :
                (progress: float32) => style._onEnter!(RouteType.Push, progress),

            onFinish: () => {}
        } as DoubleAnimationParam
    } else {
        return undefined
    }
}

function findContainerNode(node: PeerNode): ArkCommonMethodPeer | undefined {
    for (let child = node.firstChild; child != undefined; child = child!.nextSibling) {
        if (child!.isKind(PeerNodeType)) return child as ArkCommonMethodPeer
    }
    return undefined
}

function getNodeSize(ptr: PeerNode): SizeOptions {
    return { width: ArkUINativeModule._GetMeasureWidth(ptr.getPeerPtr()),
             height: ArkUINativeModule._GetMeasureHeight(ptr.getPeerPtr())} as SizeOptions
}

function launchTransitionForSize(node: ArkCommonMethodPeer, router: Router | undefined, size: SizeOptions,
                                 pageId: int32, style: ArkPageTransitionData, state: RouterTransitionVisibility) {
    router?.schedulePageTransition(pageId, () => {
        // console.log("#### Page transition animation: pageID =", pageId, " duration =", style.params.duration,
        //             " curve = ", style.params.curve === undefined || (typeof style.params.curve === "string") ? style.params.curve : Curve[style.params.curve],
        //             " delay = ", style.params.delay,
        //             " state = ", RouterTransitionVisibility[state],
        //             " opacity = ", style._opacity,
        //             " slide = ", style._slide !== undefined ? SlideEffect[style._slide] : "undefined",
        //             " scale = ", style._scale,
        //             " translate = ", style._translate)

        if (style._opacity !== undefined) {
            if (state == RouterTransitionVisibility.Hiding) {
                node.setOpacityAttribute(1.0)
            } else if (state == RouterTransitionVisibility.Showing) {
                node.setOpacityAttribute(style._opacity ?? 1.0)
            }
        }

        if (style._slide !== undefined || style._translate !== undefined || style._scale !== undefined) {
            if (state == RouterTransitionVisibility.Hiding) {
                node.setScaleAttribute(NO_SCALE)
                AnimationExtender.AnimationTranslate(node.getPeerPtr(), ZERO_TRANSLATE)
            } else if (state == RouterTransitionVisibility.Showing) {
                if (style._scale !== undefined) {
                    node.setScaleAttribute(style._scale ?? NO_SCALE)
                }

                if (style._slide !== undefined) {
                    const translate = slideTransition(size, style._slide as SlideEffect)
                    AnimationExtender.AnimationTranslate(node.getPeerPtr(), translate)
                } else if (style._translate !== undefined) {
                    AnimationExtender.AnimationTranslate(node.getPeerPtr(), style._translate ?? ZERO_TRANSLATE)
                }
            }
        }

        AnimationExtender.SetClipRect(node.getPeerPtr(), 0, 0, 10000, 10000)

        AnimationExtender.OpenImplicitAnimation({
            duration: style.params.duration,
            curve:style.params.curve,
            delay: style.params.delay,
            onFinish: (): void => router!.onPageTransitionEnd(pageId, state)
        })

        if (style._opacity !== undefined) {
            if (state == RouterTransitionVisibility.Hiding) {
                node.setOpacityAttribute(style._opacity ?? 1.0)
            } else if (state == RouterTransitionVisibility.Showing) {
                node.setOpacityAttribute(1.0)
            }
        }

        if (style._slide !== undefined || style._translate !== undefined || style._scale !== undefined) {
            if (state == RouterTransitionVisibility.Hiding) {
                if (style._scale !== undefined) {
                    node.setScaleAttribute(style._scale ?? NO_SCALE)
                }

                if (style._slide !== undefined) {
                    const translate = slideTransition(size, style._slide as SlideEffect)
                    AnimationExtender.AnimationTranslate(node.getPeerPtr(), translate)
                } else if (style._translate !== undefined) {
                    AnimationExtender.AnimationTranslate(node.getPeerPtr(), style._translate ?? ZERO_TRANSLATE)
                }
            } else if (state == RouterTransitionVisibility.Showing) {
                node.setScaleAttribute(NO_SCALE)
                AnimationExtender.AnimationTranslate(node.getPeerPtr(), ZERO_TRANSLATE)
            }
        }

        AnimationExtender.SetClipRect(node.getPeerPtr(), 0, 0, 10000, 10000)
        AnimationExtender.CloseImplicitAnimation()

        const doubleParams = progressAnimation(state, style)
        if (doubleParams) {
            AnimationExtender.StartDoubleAnimation(node.getPeerPtr(), doubleParams)
        }
    })
}

@memo
function NotifyPageTransition(pageId: int32, style: ArkPageTransitionData, state: RouterTransitionVisibility) {
    const node = findContainerNode(contextNode<ArkComponentRootPeer>(PeerNodeType))
    if (node != undefined) {
        const size = getNodeSize(node)
        const router = CurrentRouter()

        if (sizeNotEmpty(size)) {
            launchTransitionForSize(node, router, size, pageId, style, state)
        } else {
            node!.setOnSizeChangeAttribute((oldSize:SizeOptions, newSize:SizeOptions):void => {
                if (sizeNotEmpty(newSize) && oldSize.width != newSize.width && oldSize.height != newSize.height) {
                    launchTransitionForSize(node!, router, newSize, pageId, style, state)
                }
            })
        }
    }
}


@memo
export function PageTransitionEnter(params: PageTransitionOptions): PageTransitionEnterInterface {
    console.log("Implement PageTransitionEnter()")
    return new ArkPageTransitionEnterComponent({})
}

@memo
export function PageTransitionExit(params: PageTransitionOptions): PageTransitionExitInterface {
    console.log("Implement PageTransitionExit()")
    return new ArkPageTransitionExitComponent({})
}

@memo
export function PageTransitionEnterImpl(
    @memo
    style: ((attributes: PageTransitionEnterInterface) => void) | undefined,
    params: PageTransitionOptions
) {
    const receiver = remember<ArkPageTransitionEnterComponent>((): ArkPageTransitionEnterComponent => new ArkPageTransitionEnterComponent(params))
    style?.(receiver)
    const state = CurrentRouterTransitionState()
    if (state !== undefined && state.visibility == RouterTransitionVisibility.Showing) {
        NotifyPageTransition(state.pageId, receiver, RouterTransitionVisibility.Showing)
    }
}

@memo
export function PageTransitionExitImpl(
    @memo
    style: ((attributes: PageTransitionExitInterface) => void) | undefined,
    params: PageTransitionOptions
) {
    const receiver = remember<ArkPageTransitionExitComponent>((): ArkPageTransitionExitComponent => new ArkPageTransitionExitComponent(params))
    style?.(receiver)
    const state = CurrentRouterTransitionState()
    if (state !== undefined && state.visibility == RouterTransitionVisibility.Hiding) {
        NotifyPageTransition(state.pageId, receiver, RouterTransitionVisibility.Hiding)
    }
}
