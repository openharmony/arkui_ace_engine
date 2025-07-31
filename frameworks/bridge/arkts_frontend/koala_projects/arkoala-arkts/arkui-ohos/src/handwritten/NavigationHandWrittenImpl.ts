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

import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { runtimeType, RuntimeType, KPointer, toPeerPtr } from "@koalaui/interop"
import { int32 } from "@koalaui/common"
import { Serializer } from "../component/peers/Serializer"
import { NavigationTitleOptions, NavigationMenuOptions, NavigationMenuItem, NavPathStack, ToolbarItem, CustomBuilder, ResourceStr, NavigationToolbarOptions, NavigationCommonTitle, NavigationCustomTitle } from "../component"
import { SymbolGlyphModifier } from "../SymbolGlyphModifier"
import { Resource } from "global.resource"
import { PixelMap } from "#external"
import { CallbackTransformer } from "../component/peers/CallbackTransformer"

export class NavigationHandWrittenImpl {
    static TitleImpl(node: KPointer, value: ResourceStr | CustomBuilder | NavigationCommonTitle |
        NavigationCustomTitle | undefined, options?: NavigationTitleOptions) {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (value_value_type == RuntimeType.STRING || TypeChecker.isResource(value, false, false, false, false, false)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as ResourceStr
                let value_value_0_type : int32 = RuntimeType.UNDEFINED
                value_value_0_type = runtimeType(value_value_0)
                if (RuntimeType.STRING == value_value_0_type) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_value_0_0  = value_value_0 as string
                    thisSerializer.writeString(value_value_0_0)
                }
                else if (RuntimeType.OBJECT == value_value_0_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_value_0_1  = value_value_0 as Resource
                    thisSerializer.writeResource(value_value_0_1)
                }
            }
            else if (RuntimeType.FUNCTION == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as CustomBuilder
                thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_value_1))
            }
            else if (TypeChecker.isNavigationCommonTitle(value_value, false, false)) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as NavigationCommonTitle
                thisSerializer.writeNavigationCommonTitle(value_value_2)
            }
            else if (TypeChecker.isNavigationCustomTitle(value_value, false, false)) {
                thisSerializer.writeInt8(3 as int32)
                const value_value_3  = value_value as NavigationCustomTitle
                thisSerializer.writeNavigationCustomTitle(value_value_3)
            }
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeNavigationTitleOptions(options_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_title(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }

    static BackButtonIconImpl(node: KPointer, value: string | PixelMap | Resource | SymbolGlyphModifier |
        undefined, accessibilityText?: ResourceStr) {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (TypeChecker.isPixelMap(value_value, false, false)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as PixelMap
                thisSerializer.writePixelMap(value_value_1)
            }
            else if (TypeChecker.isResource(value_value, false, false, false, false, false)) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as Resource
                thisSerializer.writeResource(value_value_2)
            }
            else if (TypeChecker.isSymbolGlyphModifier(value_value)) {
                thisSerializer.writeInt8(3 as int32)
                const value_value_3  = value_value as SymbolGlyphModifier
                thisSerializer.writeSymbolGlyphModifier(value_value_3)
            }
        }
        let accessibilityText_type : int32 = RuntimeType.UNDEFINED
        accessibilityText_type = runtimeType(accessibilityText)
        if ((RuntimeType.UNDEFINED) != (accessibilityText_type)) {
            thisSerializer.writeInt8(accessibilityText_type as int32)
            const accessibilityText_value  = accessibilityText!
            let accessibilityText_value_type : int32 = RuntimeType.UNDEFINED
            accessibilityText_value_type = runtimeType(accessibilityText_value)
            if (RuntimeType.STRING == accessibilityText_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const accessibilityText_value_0  = accessibilityText_value as string
                thisSerializer.writeString(accessibilityText_value_0)
            } else if (TypeChecker.isResource(accessibilityText_value, false, false, false, false, false)) {
                thisSerializer.writeInt8(1 as int32)
                const accessibilityText_value_1  = accessibilityText_value as Resource
                thisSerializer.writeResource(accessibilityText_value_1)
            }
            ArkUIGeneratedNativeModule._NavigationAttribute_backButtonIcon1(node, thisSerializer.asBuffer(), thisSerializer.length())
        } else {
            ArkUIGeneratedNativeModule._NavigationAttribute_backButtonIcon0(node, thisSerializer.asBuffer(), thisSerializer.length())
        }
        thisSerializer.release()
    }

    static HideTitleBarImpl(node: KPointer, value: boolean | undefined, animated?: boolean) {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            thisSerializer.writeInt8(animated_type as int32)
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
            ArkUIGeneratedNativeModule._NavigationAttribute_hideTitleBar1(node, thisSerializer.asBuffer(), thisSerializer.length())
        } else {
            ArkUIGeneratedNativeModule._NavigationAttribute_hideTitleBar0(node, thisSerializer.asBuffer(), thisSerializer.length())
        }
        thisSerializer.release()
    }

    static MenusImpl(node: KPointer, value: Array<NavigationMenuItem> | CustomBuilder | undefined,
        options?: NavigationMenuOptions) {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Array<NavigationMenuItem>
                thisSerializer.writeInt32(value_value_0.length as int32)
                for (let i = 0; i < value_value_0.length; i++) {
                    const value_value_0_element : NavigationMenuItem = value_value_0[i]
                    thisSerializer.writeNavigationMenuItem(value_value_0_element)
                }
            } else if (RuntimeType.FUNCTION == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as CustomBuilder
                thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_value_1))
            }
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            thisSerializer.writeInt8(options_type as int32)
            const options_value  = options!
            thisSerializer.writeNavigationMenuOptions(options_value)
            ArkUIGeneratedNativeModule._NavigationAttribute_menus1(node, thisSerializer.asBuffer(), thisSerializer.length())
        } else {
            ArkUIGeneratedNativeModule._NavigationAttribute_menus0(node, thisSerializer.asBuffer(), thisSerializer.length())
        }
        thisSerializer.release()
    }

    static ToolbarConfigurationImpl(node: KPointer, value: Array<ToolbarItem> | CustomBuilder | undefined,
        options?: NavigationToolbarOptions) {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Array<ToolbarItem>
                thisSerializer.writeInt32(value_value_0.length as int32)
                for (let i = 0; i < value_value_0.length; i++) {
                    const value_value_0_element : ToolbarItem = value_value_0[i]
                    thisSerializer.writeToolbarItem(value_value_0_element)
                }
            }
            else if (RuntimeType.FUNCTION == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as CustomBuilder
                thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_value_1))
            }
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeNavigationToolbarOptions(options_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_toolbarConfiguration(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }

    static SetNavigationOptionsImpl(node: KPointer, value: NavPathStack) {
        ArkUIGeneratedNativeModule._NavigationInterface_setNavigationOptions1(node, toPeerPtr(value))
    }
}