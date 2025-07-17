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
import { runtimeType, RuntimeType, KPointer } from "@koalaui/interop"
import { int32 } from "@koalaui/common"
import { Serializer } from "../component/peers/Serializer"
import { NavigationTitleOptions, NavDestinationContext, CustomBuilder, NavDestinationCommonTitle, NavDestinationCustomTitle, ResourceStr, Callback } from "../component"
import { SymbolGlyphModifier } from "../SymbolGlyphModifier"
import { Resource } from "global.resource"
import { PixelMap } from "#external"
import { CallbackTransformer } from "../component/peers/CallbackTransformer"

export class NavDestinationHandWrittenImpl {
    static TitleImpl(node: KPointer, value: string | CustomBuilder | NavDestinationCommonTitle |
            NavDestinationCustomTitle | Resource | undefined, options?: NavigationTitleOptions) {
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
            else if (RuntimeType.FUNCTION == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as CustomBuilder
                thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_value_1))
            }
            else if (TypeChecker.isNavDestinationCommonTitle(value_value, false, false)) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as NavDestinationCommonTitle
                thisSerializer.writeNavDestinationCommonTitle(value_value_2)
            }
            else if (TypeChecker.isNavDestinationCustomTitle(value_value, false, false)) {
                thisSerializer.writeInt8(3 as int32)
                const value_value_3  = value_value as NavDestinationCustomTitle
                thisSerializer.writeNavDestinationCustomTitle(value_value_3)
            }
            else if (TypeChecker.isResource(value_value, false, false, false, false, false)) {
                thisSerializer.writeInt8(4 as int32)
                const value_value_4  = value_value as Resource
                thisSerializer.writeResource(value_value_4)
            }
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeNavigationTitleOptions(options_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_title(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }

    static BackButtonIconImpl(node: KPointer, value: ResourceStr | PixelMap | SymbolGlyphModifier | undefined, accessibilityText?: ResourceStr) {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if ((RuntimeType.STRING == value_value_type) || TypeChecker.isResource(value_value, false, false, false, false, false)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as ResourceStr
                let value_value_0_type : int32 = RuntimeType.UNDEFINED
                value_value_0_type = runtimeType(value_value_0)
                if (RuntimeType.STRING == value_value_0_type) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_value_0_0  = value_value_0 as string
                    thisSerializer.writeString(value_value_0_0)
                } else if (TypeChecker.isResource(value_value, false, false, false, false, false)) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_value_0_1  = value_value_0 as Resource
                    thisSerializer.writeResource(value_value_0_1)
                }
            } else if (TypeChecker.isPixelMap(value_value, false, false)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as PixelMap
                thisSerializer.writePixelMap(value_value_1)
            } else if (TypeChecker.isSymbolGlyphModifier(value_value)) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as SymbolGlyphModifier
                thisSerializer.writeSymbolGlyphModifier(value_value_2)
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
            } else if (RuntimeType.OBJECT == accessibilityText_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const accessibilityText_value_1  = accessibilityText_value as Resource
                thisSerializer.writeResource(accessibilityText_value_1)
            }
            ArkUIGeneratedNativeModule._NavDestinationAttribute_backButtonIcon1(node, thisSerializer.asBuffer(), thisSerializer.length())
        } else {
            ArkUIGeneratedNativeModule._NavDestinationAttribute_backButtonIcon0(node, thisSerializer.asBuffer(), thisSerializer.length())
        }
        thisSerializer.release()
    }

    static OnWillAppearImpl(node: KPointer, value: Callback<void> | undefined) {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_onWillAppear(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }

    static OnWillDisappearImpl(node: KPointer, value: Callback<void> | undefined) {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_onWillDisappear(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }

    static OnWillShowImpl(node: KPointer, value: Callback<void> | undefined) {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_onWillShow(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }

    static OnWillHideImpl(node: KPointer, value: Callback<void> | undefined) {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_onWillHide(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }

    static OnReadyImpl(node: KPointer, value: Callback<NavDestinationContext> | undefined) {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_onReady(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }

    static OnNewParamImpl(node: KPointer, value: ((parameter: Object | null | undefined) => void) | undefined) {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_onNewParam(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}