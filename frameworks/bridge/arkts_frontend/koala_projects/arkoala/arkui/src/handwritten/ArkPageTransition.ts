/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

import { ArkUINativeModule, PeerNode, PeerNodeType } from "@koalaui/arkoala"
import { CurrentRouter, CurrentRouterTransitionState, Router, RouterTransitionVisibility } from "@koalaui/arkui-common"
import { int32 } from "@koalaui/common"
import { remember, contextNode } from "@koalaui/runtime"
import { ArkCommonMethodPeer } from "../generated/peers/ArkCommonPeer"
import { ArkComponentRootPeer } from "../generated/peers/ArkStaticComponentsPeer"
import { TranslateOptions, ScaleOptions } from "../generated/ArkCommonInterfaces"
import { PageTransitionOptions, SlideEffect, RouteType } from "../generated/ArkPageTransitionInterfaces"
import { AnimationExtender } from "../generated/ArkAnimationExtenderMaterialized"

const NO_SCALE:ScaleOptions = { x: 1.0, y: 1.0, z: 1.0, centerX: "50%", centerY: "50%" }
const ZERO_TRANSLATE:TranslateOptions = { x: 0.0, y: 0.0, z:0.0 }
const KEY_PAGE_TRANSITION_PROPERTY = "pageTransitionProperty" // See frameworks/core/components_ng/pattern/stage/page_pattern.cpp

function sizeNotEmpty(size: SizeOptions): boolean {
    const w = (size?.width as number) ?? 0
    const h = (size?.height as number) ?? 0
    return w > 0 && h > 0
}

function getNodeSize(ptr: PeerNode): SizeOptions {
    return { width: ArkUINativeModule._GetMeasureWidth(ptr.getPeerPtr()),
             height: ArkUINativeModule._GetMeasureHeight(ptr.getPeerPtr())}
}

// see rosen_render_context.cpp:SlideTransitionEffect in ace_engine
function slideTransition(size: SizeOptions, value: SlideEffect) : TranslateOptions {
    if (sizeNotEmpty(size)) {
        let xOffset = 0
        let yOffset = 0
        switch (value) {
            case SlideEffect.Left:
                xOffset = -(size.width as number)
                break
            case SlideEffect.Right:
                xOffset = size.width as number
                break
            case SlideEffect.Top:
                yOffset = -(size.height as number)
                break
            case SlideEffect.Bottom:
                yOffset = size.height as number
                break
            case SlideEffect.START:
                xOffset = -(size.width as number) // TODO: support RTL applications with x = width
                break
            case SlideEffect.END:
                xOffset = size.width as number //  TODO: support RTL applications with x = -width
                break
        }

        return { x: xOffset, y: yOffset, z: 0 }
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
            startValue: 0,
            endValue: 1.0,
            duration: style.params.duration ?? 0,
            delay: style.params.delay ?? 0,
            curve: style.params.curve as Curve,
            onProgress: (state == RouterTransitionVisibility.Hiding && style._onExit != undefined) ?
                progress => style._onExit?.(RouteType.Pop, progress) :
                progress => style._onEnter?.(RouteType.Push, progress),

            onFinish: () => {}
        }
    } else {
        return undefined
    }
}

function findContainerNode(node: PeerNode): ArkCommonMethodPeer | undefined {
    for (let child = node.firstChild; child; child = child.nextSibling) {
        if (child.isKind(PeerNodeType)) return child as ArkCommonMethodPeer
    }
    return undefined
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
                node.opacityAttribute(1.0)
            } else if (state == RouterTransitionVisibility.Showing) {
                node.opacityAttribute(style._opacity)
            }
        }

        if (style._slide !== undefined || style._translate !== undefined || style._scale !== undefined) {
            if (state == RouterTransitionVisibility.Hiding) {
                node.scaleAttribute(NO_SCALE)
                AnimationExtender.AnimationTranslate(node.getPeerPtr(), ZERO_TRANSLATE)
            } else if (state == RouterTransitionVisibility.Showing) {
                if (style._scale !== undefined) {
                    node.scaleAttribute(style._scale)
                }

                if (style._slide !== undefined) {
                    const translate = slideTransition(size, style._slide)
                    AnimationExtender.AnimationTranslate(node.getPeerPtr(), translate)
                } else if (style._translate !== undefined) {
                    AnimationExtender.AnimationTranslate(node.getPeerPtr(), style._translate)
                }
            }
        }

        AnimationExtender.SetClipRect(node.getPeerPtr(), 0, 0, 10000, 10000)

        AnimationExtender.OpenImplicitAnimation({
            duration: style.params.duration,
            curve:style.params.curve,
            delay: style.params.delay,
            onFinish: () => router?.onPageTransitionEnd(pageId, state)
        })

        if (style._opacity !== undefined) {
            if (state == RouterTransitionVisibility.Hiding) {
                node.opacityAttribute(style._opacity)
            } else if (state == RouterTransitionVisibility.Showing) {
                node.opacityAttribute(1.0)
            }
        }

        if (style._slide !== undefined || style._translate !== undefined || style._scale !== undefined) {
            if (state == RouterTransitionVisibility.Hiding) {
                if (style._scale !== undefined) {
                    node.scaleAttribute(style._scale)
                }

                if (style._slide !== undefined) {
                    const translate = slideTransition(size, style._slide)
                    AnimationExtender.AnimationTranslate(node.getPeerPtr(), translate)
                } else if (style._translate !== undefined) {
                    AnimationExtender.AnimationTranslate(node.getPeerPtr(), style._translate)
                }
            } else if (state == RouterTransitionVisibility.Showing) {
                node.scaleAttribute(NO_SCALE)
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

/**
 * @memo
 */
function NotifyPageTransition(pageId: int32, style: ArkPageTransitionData, state: RouterTransitionVisibility) {
    const node = findContainerNode(contextNode<ArkComponentRootPeer>(PeerNodeType))
    if (node) {
        const size = getNodeSize(node)
        const router = CurrentRouter()
        if (sizeNotEmpty(size)) {
            launchTransitionForSize(node, router, size, pageId, style, state)
        } else {
            node.onSizeChangeAttribute((oldSize, newSize) => {
                if (sizeNotEmpty(newSize) && oldSize.width != newSize.width && oldSize.height != newSize.height) {
                    launchTransitionForSize(node, router, newSize, pageId, style, state)
                }
            })
        }
    }
}

export type ProgressCallback = (type: RouteType, progress: number) => void

export class ArkPageTransitionData {
    params: PageTransitionOptions
    _onEnter?: ProgressCallback
    _onExit?: ProgressCallback
    _slide?: SlideEffect
    _translate?: TranslateOptions
    _scale?: ScaleOptions
    _opacity?: number

    constructor(params: PageTransitionOptions) {
        this.params = params
    }
    onEnter(event: ProgressCallback): this {
        this._onEnter = event
        return this
    }
    onExit(event: ProgressCallback): this {
        this._onExit = event
        return this
    }
    slide(value: SlideEffect): this {
        this._slide = value
        return this
    }
    translate(value: TranslateOptions): this {
        this._translate = value
        return this
    }
    opacity(value: number): this {
        this._opacity = value
        return this
    }
    scale(value: ScaleOptions): this {
        this._scale = value
        return this
    }
}

export class ArkPageTransitionEnterComponent extends ArkPageTransitionData {
    constructor(params: PageTransitionOptions) {
        super(params)
    }
}

export class ArkPageTransitionExitComponent extends ArkPageTransitionData {
    constructor(params: PageTransitionOptions) {
        super(params)
    }
}

/**
 * @memo
 */
export function ArkPageTransitionEnter(
    /** @memo */
    style: ((attributes: ArkPageTransitionEnterComponent) => void) | undefined,
    contentUnused: (() => void) | undefined,
    params: PageTransitionOptions
) {
    const receiver = remember(() => new ArkPageTransitionEnterComponent(params))
    style?.(receiver)
    const state = CurrentRouterTransitionState()
    if (state !== undefined && state.visibility == RouterTransitionVisibility.Showing) {
        NotifyPageTransition(state.pageId, receiver, RouterTransitionVisibility.Showing)
    }
}

/**
 * @memo
 */
export function ArkPageTransitionExit(
    /** @memo */
    style: ((attributes: ArkPageTransitionExitComponent) => void) | undefined,
    contentUnused: (() => void) | undefined,
    params: PageTransitionOptions
) {
    const receiver = remember(() => new ArkPageTransitionExitComponent(params))
    style?.(receiver)
    const state = CurrentRouterTransitionState()
    if (state !== undefined && state.visibility == RouterTransitionVisibility.Hiding) {
        NotifyPageTransition(state.pageId, receiver, RouterTransitionVisibility.Hiding)
    }
}