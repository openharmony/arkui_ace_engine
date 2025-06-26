/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import {
    AnimateParam,
    ArkComponentRootPeer,
    PageTransitionOptions,
    LayoutChild,
    ConstraintSizeOptions,
    GeometryInfo,
    Layoutable,
    Measurable,
    SizeResult
} from "../generated"
import { BuilderLambda } from "@koalaui/builderLambda"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { rememberDisposable, remember, mutableState, MutableState, NodeAttach, RunEffect } from "@koalaui/runtime"
import { addPartialUpdate } from '../Application'
import { CurrentRouterTransitionState, RouterTransitionVisibility } from "./Router";
import { PeerNode } from "../PeerNode";
import { PageTransitionEnter, PageTransitionExit } from "./ArkPageTransition"

export interface AttributeModifier<T> {
    isUpdater: boolean;
    applyNormalAttribute(instance: T): void;
    applyPressedAttribute(instance: T): void;
    applyFocusedAttribute(instance: T): void;
    applyDisabledAttribute(instance: T): void;
    applySelectedAttribute(instance: T): void;
}

export interface UICommonBase {
    @memo
__applyStyle<T, A>(
    @memo
        style: (instance: T, args: A) => T,
    arg: A
): T

@memo
__applyAnimatableExtend<T, A>(
    @memo
        func: (instance: T, arg: A) => T,
    arg: A
): T

animationStart(param: AnimateParam): this
animationEnd(): this
}

export function $r(str: string): string {
    return str
}

export function $rawfile(arg: string): string {
    return arg
}

export class StructBase<T, OptionsT> {
    @memo
    @BuilderLambda("StructBase.instantiateImpl")
    static $_instantiate<S extends StructBase<S, OptionsS>, OptionsS>(
        factory: () => S,
        options?: OptionsS,
        @memo content?: () => void
    ): S {
        throw new Error("This method should only be called through a @BuilderLambda redirect")
    }

    @memo
    static instantiateImpl<S extends StructBase<S, OptionsS>, OptionsS>(
        @memo builder: ((instance: S) => void) | undefined,
        factory: () => S,
        options?: OptionsS,
        @memo content?: () => void
    ): void {
        const receiver = rememberDisposable<S>(
            (): S => {
                const instance = factory()
                instance.__initializeStruct(options, content)
                return instance
            }, (instance: S | undefined): void => {
                instance?.aboutToDisappear()
                instance?.__disposeStruct()
            }
        )

        NodeAttach<PeerNode>(
            (): PeerNode => ArkComponentRootPeer.create(),
            (node: PeerNode): void => {
                const inited = remember<MutableState<boolean>>(
                    (): MutableState<boolean> => {
                        const state = mutableState(false)
                        addPartialUpdate(() => {
                            receiver.aboutToAppear()
                            state.value = true
                        }, receiver, () => {})
                        return state
                    }
                )
                if (!inited.value) {
                    return
                }

                if (receiver.isEntry()) {
                    const state = CurrentRouterTransitionState()
                    if (state) {
                        RunEffect<RouterTransitionVisibility>(state.visibility, (visibility: RouterTransitionVisibility): void => {
                            switch (visibility.valueOf()) {
                                case RouterTransitionVisibility.Showing.valueOf():
                                    receiver.onPageShow()
                                    break
                                case RouterTransitionVisibility.Hiding.valueOf():
                                    receiver.onPageHide()
                                    break
                                default: break
                            }
                        })
                    }
                    receiver.pageTransition()
                }

                builder?.(receiver)
                receiver._build(builder, content, options)
                receiver.onDidBuild()
            }
        )
    }

    protected __initializeStruct(
        initializers?: OptionsT,
        @memo
        content?: () => void
    ): void {}

    /**
     * This method is called when the component is completely removed from the UI tree.
     * It can be used to clean up dependencies, such as added listeners.
     */
    protected __disposeStruct(): void {}

    @memo
    build(): void {
        throw new Error("The struct build() should never be executed directly")
    }

    @memo
    protected _build(
        @memo
        style: ((instance: T) => void) | undefined,
        @memo
        content: (() => void) | undefined,
        options: OptionsT | undefined
    ): void {
        throw new Error("The struct _build() must have a valid override")
    }

    /**
     * This method defines whether component is a page entry point
     */
    protected isEntry(): boolean {
        return false
    }

    /**
     * This method defines whether component customizes layout of its child components
     */
    protected isCustomLayoutComponent(): boolean {
        return false
    }

    aboutToAppear(): void {}
    aboutToDisappear(): void {}
    aboutToReuse(params: Record<string, Object>): void {}
    aboutToRecycle(): void {}
    onDidBuild(): void {}

    onLayout(children: Array<LayoutChild>, constraint: ConstraintSizeOptions): void {}
    onMeasure(children: Array<LayoutChild>, constraint: ConstraintSizeOptions): void {}

    onPlaceChildren(selfLayoutInfo: GeometryInfo, children: Array<Layoutable>, constraint: ConstraintSizeOptions): void {}
    onMeasureSize(selfLayoutInfo: GeometryInfo, children: Array<Measurable>, constraint: ConstraintSizeOptions): SizeResult {
        throw new Error("Unexpected use of base class method")
    }

    onPageShow(): void {}
    onPageHide(): void {}
    onBackPress(): boolean { return false }
    @memo
    pageTransition(): void {
        PageTransitionEnter({ delay: 100 } as PageTransitionOptions)
        PageTransitionExit({ delay: 100 } as PageTransitionOptions)
    }
}

// TODO: implement this
export interface SubscribaleAbstract { }
export interface CommonTransition { }
export { AbstractProperty } from "@koalaui/arkui-common"
export interface CustomComponent { }
export interface IPropertySubscriber { }
export interface ISinglePropertyChangeSubscriber { }

