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


// WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!

import { contextLocalScope, MutableState, NodeAttach, remember, rememberMutableState } from "@koalaui/runtime"
import { ArkCommonMethodComponent } from "./generated/ArkCommon"
import { ArkNavigationPeer } from "./peers/ArkNavigationPeer"
import { runtimeType, RuntimeType } from "@koalaui/interop"
import { NavPathStack } from "./generated/ArkNavPathStackMaterialized"
import { NavExtender } from "./generated/ArkNavExtenderMaterialized"
import { PathData } from "./handwritten"

/** @memo:stable */
export class ArkNavigationComponent extends ArkCommonMethodComponent {
    getPeer(): ArkNavigationPeer {
        return (this.peer as ArkNavigationPeer)
    }
    private _navPathStack: MutableState<NavPathStack> | undefined = undefined
    /** @memo */
    setNavigationOptions(pathInfos?: NavPathStack): this {
        console.log("Call ArkNavigationComponent.setNavigationOptions()")
        if (this.checkPriority("setNavigationOptions")) {
            const pathInfos_type = runtimeType(pathInfos)
            if ((((RuntimeType.OBJECT == pathInfos_type)))) {
                const pathInfos_casted = pathInfos as (NavPathStack)
                this._navPathStack = rememberMutableState<NavPathStack>(pathInfos_casted)
                return this
            }
            if ((((RuntimeType.UNDEFINED == pathInfos_type)))) {
                this.getPeer()?.setNavigationOptions0Attribute()
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    navBarWidth(value: Length): this {
        console.log("Call ArkNavigationComponent.navBarWidth()")
        if (this.checkPriority("navBarWidth")) {
            const value_casted = value as (Length)
            this.getPeer()?.navBarWidthAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    navBarPosition(value: NavBarPosition): this {
        console.log("Call ArkNavigationComponent.navBarPosition()")
        if (this.checkPriority("navBarPosition")) {
            const value_casted = value as (NavBarPosition)
            this.getPeer()?.navBarPositionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    navBarWidthRange(value: [ Dimension, Dimension ]): this {
        console.log("Call ArkNavigationComponent.navBarWidthRange()")
        if (this.checkPriority("navBarWidthRange")) {
            const value_casted = value as ([ Dimension, Dimension ])
            this.getPeer()?.navBarWidthRangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    minContentWidth(value: Dimension): this {
        console.log("Call ArkNavigationComponent.minContentWidth()")
        if (this.checkPriority("minContentWidth")) {
            const value_casted = value as (Dimension)
            this.getPeer()?.minContentWidthAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    mode(value: NavigationMode): this {
        console.log("Call ArkNavigationComponent.mode()")
        if (this.checkPriority("mode")) {
            const value_casted = value as (NavigationMode)
            this.getPeer()?.modeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    backButtonIcon(value: string | PixelMap | Resource | SymbolGlyphModifier): this {
        console.log("Call ArkNavigationComponent.backButtonIcon()")
        if (this.checkPriority("backButtonIcon")) {
            const value_casted = value as (string | PixelMap | Resource | SymbolGlyphModifier)
            this.getPeer()?.backButtonIconAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    hideNavBar(value: boolean): this {
        console.log("Call ArkNavigationComponent.hideNavBar()")
        if (this.checkPriority("hideNavBar")) {
            const value_casted = value as (boolean)
            this.getPeer()?.hideNavBarAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    subTitle(value: string): this {
        console.log("Call ArkNavigationComponent.subTitle()")
        if (this.checkPriority("subTitle")) {
            const value_casted = value as (string)
            this.getPeer()?.subTitleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    hideTitleBar(hide: boolean, animated?: boolean): this {
        console.log("Call ArkNavigationComponent.hideTitleBar()")
        if (this.checkPriority("hideTitleBar")) {
            const hide_type = runtimeType(hide)
            const animated_type = runtimeType(animated)
            if ((((RuntimeType.BOOLEAN == hide_type))) && (((RuntimeType.BOOLEAN == animated_type)))) {
                const hide_casted = hide as (boolean)
                const animated_casted = animated as (boolean)
                this.getPeer()?.hideTitleBar1Attribute(hide_casted, animated_casted)
                return this
            }
            if ((((RuntimeType.BOOLEAN == hide_type))) && (((RuntimeType.UNDEFINED == animated_type)))) {
                const hide_casted = hide as (boolean)
                this.getPeer()?.hideTitleBar0Attribute(hide_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    hideBackButton(value: boolean): this {
        console.log("Call ArkNavigationComponent.hideBackButton()")
        if (this.checkPriority("hideBackButton")) {
            const value_casted = value as (boolean)
            this.getPeer()?.hideBackButtonAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    titleMode(value: NavigationTitleMode): this {
        console.log("Call ArkNavigationComponent.titleMode()")
        if (this.checkPriority("titleMode")) {
            const value_casted = value as (NavigationTitleMode)
            this.getPeer()?.titleModeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    menus(value: Array<NavigationMenuItem> | CustomBuilder): this {
        console.log("Call ArkNavigationComponent.menus()")
        if (this.checkPriority("menus")) {
            const value_casted = value as (Array<NavigationMenuItem> | CustomBuilder)
            this.getPeer()?.menusAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    toolBar(value: Object | CustomBuilder): this {
        console.log("Call ArkNavigationComponent.toolBar()")
        if (this.checkPriority("toolBar")) {
            const value_casted = value as (Object | CustomBuilder)
            this.getPeer()?.toolBarAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    hideToolBar(hide: boolean, animated?: boolean): this {
        console.log("Call ArkNavigationComponent.hideToolBar()")
        if (this.checkPriority("hideToolBar")) {
            const hide_type = runtimeType(hide)
            const animated_type = runtimeType(animated)
            if ((((RuntimeType.BOOLEAN == hide_type))) && (((RuntimeType.BOOLEAN == animated_type)))) {
                const hide_casted = hide as (boolean)
                const animated_casted = animated as (boolean)
                this.getPeer()?.hideToolBar1Attribute(hide_casted, animated_casted)
                return this
            }
            if ((((RuntimeType.BOOLEAN == hide_type))) && (((RuntimeType.UNDEFINED == animated_type)))) {
                const hide_casted = hide as (boolean)
                this.getPeer()?.hideToolBar0Attribute(hide_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    onTitleModeChange(value: (a1: NavigationTitleMode) => void): this {
        console.log("Call ArkNavigationComponent.onTitleModeChange()")
        if (this.checkPriority("onTitleModeChange")) {
            const value_casted = value as ((a1: NavigationTitleMode) => void)
            this.getPeer()?.onTitleModeChangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    onNavBarStateChange(value: (a1: boolean) => void): this {
        console.log("Call ArkNavigationComponent.onNavBarStateChange()")
        if (this.checkPriority("onNavBarStateChange")) {
            const value_casted = value as ((a1: boolean) => void)
            this.getPeer()?.onNavBarStateChangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    onNavigationModeChange(value: (a1: NavigationMode) => void): this {
        console.log("Call ArkNavigationComponent.onNavigationModeChange()")
        if (this.checkPriority("onNavigationModeChange")) {
            const value_casted = value as ((a1: NavigationMode) => void)
            this.getPeer()?.onNavigationModeChangeAttribute(value_casted)
            return this
        }
        return this
    }

    /** @memo */
    _navDestination:
        (arg0: string, arg1: object) => void =
            /** @memo */
            (arg0: string, arg1: object) => { console.log("_navDestination is undefined.") }

    /** @memo */
    navDestination(
        /** @memo */
        value: ((arg0: string, arg1: object) => void) | undefined
    ): this {
        if (value != undefined) {
            this._navDestination = value!
        }
        return this
    }

    /** @memo */
    customNavContentTransition(value: (a1: NavContentInfo, a2: NavContentInfo, a3: NavigationOperation) => NavigationAnimatedTransition | undefined): this {
        console.log("Call ArkNavigationComponent.customNavContentTransition()")
        if (this.checkPriority("customNavContentTransition")) {
            const value_casted = value as ((a1: NavContentInfo, a2: NavContentInfo, a3: NavigationOperation) => NavigationAnimatedTransition | undefined)
            this.getPeer()?.customNavContentTransitionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    systemBarStyle(value?: SystemBarStyle): this {
        console.log("Call ArkNavigationComponent.systemBarStyle()")
        if (this.checkPriority("systemBarStyle")) {
            const value_casted = value as (SystemBarStyle | undefined)
            this.getPeer()?.systemBarStyleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    recoverable(value?: boolean): this {
        console.log("Call ArkNavigationComponent.recoverable()")
        if (this.checkPriority("recoverable")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.recoverableAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    enableDragBar(value?: boolean): this {
        console.log("Call ArkNavigationComponent.enableDragBar()")
        if (this.checkPriority("enableDragBar")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.enableDragBarAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    title(value: ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle, options?: NavigationTitleOptions): this {
        console.log("Call ArkNavigationComponent.title()")
        if (this.checkPriority("title")) {
            const value_casted = value as (ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle)
            const options_casted = options as (NavigationTitleOptions | undefined)
            this.getPeer()?.titleAttribute(value_casted, options_casted)
            return this
        }
        return this
    }
    /** @memo */
    toolbarConfiguration(value: Array<ToolbarItem> | CustomBuilder, options?: NavigationToolbarOptions): this {
        console.log("Call ArkNavigationComponent.toolbarConfiguration()")
        if (this.checkPriority("toolbarConfiguration")) {
            const value_casted = value as (Array<ToolbarItem> | CustomBuilder)
            const options_casted = options as (NavigationToolbarOptions | undefined)
            this.getPeer()?.toolbarConfigurationAttribute(value_casted, options_casted)
            return this
        }
        return this
    }
    /** @memo */
    ignoreLayoutSafeArea(types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): this {
        console.log("Call ArkNavigationComponent.ignoreLayoutSafeArea()")
        if (this.checkPriority("ignoreLayoutSafeArea")) {
            const types_casted = types as (Array<LayoutSafeAreaType> | undefined)
            const edges_casted = edges as (Array<LayoutSafeAreaEdge> | undefined)
            this.getPeer()?.ignoreLayoutSafeAreaAttribute(types_casted, edges_casted)
            return this
        }
        return this
    }
    public applyAttributesFinish(): void {
        // we calls this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

/** @memo */
export function ArkNavigation(
  /** @memo */
  style: ((attributes: ArkNavigationComponent) => void) | undefined,
  /** @memo */
  content_: (() => void) | undefined,
  pathInfos?: NavPathStack | undefined
) {
    const receiver = remember(() => {
        return new ArkNavigationComponent()
    })
    //NodeAttach<ArkNavigationPeer>((): ArkNavigationPeer => ArkNavigationPeer.create(ArkUINodeType.CustomNode, receiver), (_: ArkNavigationPeer) => {
    NodeAttach<ArkNavigationPeer>((): ArkNavigationPeer => ArkNavigationPeer.create(receiver), (_: ArkNavigationPeer) => {
            receiver.setNavigationOptions(pathInfos)
        style?.(receiver)
        content_?.()
        if (pathInfos != undefined) {
            const data = rememberMutableState<PathData>(PathData.EMPTY)
            remember(() => {
                const updater: (name: string) => void =
                    (name: string) => {
                        // Object deserialization is not implemented so param is empty array
                        const params = pathInfos!.getParamByName(name)
                        data.value = new PathData(name, params)
                    }
                const value_casted = updater as (((name: string) => void))
                NavExtender.setUpdateStackCallback(pathInfos!, value_casted)
            })
            withNavData(data.value, () => {
                receiver._navDestination(
                    data.value.name,
                    data.value.param
                )
            })
        }
        receiver.applyAttributesFinish()
    })
}

/** @memo */
function withNavData(
    pathInfo: PathData,
    /** @memo */
    content_: () => void,
) {
    contextLocalScope("NavPathStack", pathInfo, content_)
}
