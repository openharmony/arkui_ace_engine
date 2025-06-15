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


// WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!

import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"

export class SideBarContainerOps {
    public static registerShowSideBarCallback(node: KPointer, value: boolean, callback: ShowSideBarCallback): KPointer {
        const node_casted = node as (KPointer)
        const value_casted = value as (boolean)
        const callback_casted = callback as (ShowSideBarCallback)
        return SideBarContainerOps.registerShowSideBarCallback_serialize(node_casted, value_casted, callback_casted)
    }
    public static registerSideBarWidthCallback(node: KPointer, value: number, callback: SideBarWidthCallback): KPointer {
        const node_casted = node as (KPointer)
        const value_casted = value as (number)
        const callback_casted = callback as (SideBarWidthCallback)
        return SideBarContainerOps.registerSideBarWidthCallback_serialize(node_casted, value_casted, callback_casted)
    }
    private static registerShowSideBarCallback_serialize(node: KPointer, value: boolean, callback: ShowSideBarCallback): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback)
        const retval  = ArkUIGeneratedNativeModule._SideBarContainerOps_registerShowSideBarCallback(node, value ? 1 : 0, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static registerSideBarWidthCallback_serialize(node: KPointer, value: number, callback: SideBarWidthCallback): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback)
        const retval  = ArkUIGeneratedNativeModule._SideBarContainerOps_registerSideBarWidthCallback(node, value, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
}
export type ShowSideBarCallback = (showSideBar: boolean) => void;
export type SideBarWidthCallback = (sideBarWidth: number) => void;
