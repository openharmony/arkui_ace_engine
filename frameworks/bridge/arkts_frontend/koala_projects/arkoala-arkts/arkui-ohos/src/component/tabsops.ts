/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

import { BarMode, ScrollableBarModeOptions } from "./tabs"
import { BlurStyle, BackgroundBlurStyleOptions } from "./common"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
export class TabsOps {
    public static registerBarMode(node: KPointer, value: BarMode | undefined, options: ScrollableBarModeOptions | undefined): KPointer {
        const node_casted = node as (KPointer)
        const value_casted = value as (BarMode | undefined)
        const options_casted = options as (ScrollableBarModeOptions | undefined)
        return TabsOps.registerBarMode_serialize(node_casted, value_casted, options_casted)
    }
    public static registerBarBackgroundBlurStyle(node: KPointer, style: BlurStyle | undefined, options: BackgroundBlurStyleOptions | undefined): KPointer {
        const node_casted = node as (KPointer)
        const style_casted = style as (BlurStyle | undefined)
        const options_casted = options as (BackgroundBlurStyleOptions | undefined)
        return TabsOps.registerBarBackgroundBlurStyle_serialize(node_casted, style_casted, options_casted)
    }
    private static registerBarMode_serialize(node: KPointer, value: BarMode | undefined, options: ScrollableBarModeOptions | undefined): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as BarMode)
            thisSerializer.writeInt32(TypeChecker.BarMode_ToNumeric(value_value))
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeScrollableBarModeOptions(options_value)
        }
        const retval  = ArkUIGeneratedNativeModule._TabsOps_registerBarMode(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static registerBarBackgroundBlurStyle_serialize(node: KPointer, style: BlurStyle | undefined, options: BackgroundBlurStyleOptions | undefined): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let style_type : int32 = RuntimeType.UNDEFINED
        style_type = runtimeType(style)
        thisSerializer.writeInt8(style_type)
        if ((RuntimeType.UNDEFINED) != (style_type)) {
            const style_value  = (style as BlurStyle)
            thisSerializer.writeInt32(TypeChecker.BlurStyle_ToNumeric(style_value))
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeBackgroundBlurStyleOptions(options_value)
        }
        const retval  = ArkUIGeneratedNativeModule._TabsOps_registerBarBackgroundBlurStyle(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
}
