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

package arkui.component.customComponent;

import {
    AnimateParam,
    ArkComponentRootPeer,
    ArkColumnPeer,
    PageTransitionOptions,
    LayoutChild,
    ConstraintSizeOptions,
    GeometryInfo,
    Layoutable,
    Measurable,
    SizeResult,
    PageLifeCycle,
    LayoutCallback,
    CommonMethod
} from "../../generated"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { rememberDisposable, remember, mutableState, MutableState, NodeAttach, RunEffect } from "@koalaui/runtime"
import { addPartialUpdate } from '../../ArkUIEntry'
import { CurrentRouterTransitionState, RouterTransitionVisibility } from "../Router";
import { PeerNode } from "../../PeerNode";
import { PageTransitionEnter, PageTransitionExit } from "../ArkPageTransition"
import { ExtendableComponent, UIContext } from './extendableComponent'

export interface AttributeModifier<T> {
    isUpdater(): boolean;
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

export abstract class BaseCustomComponent extends ExtendableComponent {
    /**
     * aboutToRecycle Method.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @crossplatform
     * @atomicservice
     * @since 20
     */
    abstract aboutToRecycle(): void;
}
export class CustomComponent<T extends CustomComponent<T, OptionsT>, OptionsT extends Object> extends BaseCustomComponent {
    @memo
    static $_instantiate<S extends CustomComponent<S, OptionsS>, OptionsS extends Object>(
        @memo builder: ((instance: S) => void) | undefined,
        factory: () => S,
        options?: OptionsS,
        reuseId?: string,
        @memo content?: () => void
    ): void {
        @memo const create = (): S => {
            return rememberDisposable<S>(
                (): S => {
                    const instance = factory()
                    instance.__initializeStruct(options, content)
                    return instance
                }, (instance: S | undefined): void => {
                    instance?.aboutToDisappear()
                    instance?.__disposeStruct()
                }
            )
        }

        if (reuseId) {
            /* need to wrap both states and build() of @Component */
            NodeAttach<PeerNode>(
                // temporarily using Column, will replace with purely frontend node
                (): PeerNode => ArkColumnPeer.create(),
                (node: PeerNode): void => {
                    const receiver = create()
                    node.setOnRecycle(() => {
                        receiver.aboutToRecycle()
                    })
                    node.setOnReuse(() => {
                        receiver.aboutToReuse(receiver.__toRecord(options))
                    })
                    receiver.__buildWrapper(builder, options, content)
                },
                reuseId
            )
        } else {
            const receiver = create()
            receiver.__buildWrapper(builder, options, content)
        }
    }

    @memo
    private __buildWrapper(
        @memo builder: ((instance: T) => void) | undefined,
        options?: OptionsT,
        @memo content?: () => void
    ): void {
        NodeAttach<PeerNode>(
            (): PeerNode => ArkComponentRootPeer.create(),
            (node: PeerNode): void => {
                const appeared = remember<MutableState<boolean>>(
                    (): MutableState<boolean> => {
                        const state = mutableState(false)
                        addPartialUpdate(() => {
                            this.aboutToAppear()
                            state.value = true
                        }, this, () => {})
                        return state
                    }
                )
                if (!appeared.value) {
                    return
                }

                if (this.isEntry()) {
                    const state = CurrentRouterTransitionState()
                    if (state) {
                        RunEffect<RouterTransitionVisibility>(state.visibility, (visibility: RouterTransitionVisibility): void => {
                            switch (visibility.valueOf()) {
                                case RouterTransitionVisibility.Showing.valueOf():
                                    this.onPageShow()
                                    break
                                case RouterTransitionVisibility.Hiding.valueOf():
                                    this.onPageHide()
                                    break
                                default: break
                            }
                        })
                    }
                    this.pageTransition()
                }

                builder?.(this as T)
                this.__updateStruct(options)
                this._build(builder, content, options)
                this.onDidBuild()
            }
        )
    }

    protected __initializeStruct(
        initializers?: Object,
        @memo
        content?: () => void
    ): void {}

    /**
     * This method is called when the component is completely removed from the UI tree.
     * It can be used to clean up dependencies, such as added listeners.
     */
    protected __disposeStruct(): void {}

    /**
     * This method is used when the component is going to be reused
     */
    protected __toRecord(initializers?: OptionsT): Record<string, Object> {
        return {}
    }

    @memo
    protected __updateStruct(initializers?: OptionsT): void {}

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
        options: Object | undefined
    ): void {
        throw new Error("The struct _build() must have a valid override")
    }

    /**
     * This method defines whether component is a page entry point
     */
    protected isEntry(): boolean {
        return this instanceof PageLifeCycle
    }

    /**
     * This method defines whether component customizes layout of its child components
     */
    protected isCustomLayoutComponent(): boolean {
        return this instanceof LayoutCallback
    }

    aboutToAppear(): void {}
    aboutToDisappear(): void {}
    aboutToReuse(params: Record<string, Object>): void {}
    aboutToRecycle(): void {}
    onDidBuild(): void {}

    getUIContext(): UIContext { return new UIContext() }
    getUniqueId(): int { return 666 }

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

// Improve: implement this
export interface SubscribaleAbstract { }
export interface CommonTransition { }
export interface IPropertySubscriber { }
export interface ISinglePropertyChangeSubscriber { }

export interface CustomComponentV2 {}

export type CustomStyles = (instance:CommonMethod) => void
