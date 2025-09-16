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

import {ArkUIGeneratedNativeModule } from "#components"
import { runtimeType, RuntimeType, KPointer } from "@koalaui/interop"
import { int32 } from "@koalaui/common"
import { Serializer } from "../component/peers/Serializer"
import { Length } from "../component"
import { DividerStyle } from "../component/sidebar"

export class SideBarContainerHandWrittenImpl {
    static SideBarWidthImpl(node: KPointer, value: number | Length | undefined) {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.NUMBER) == (value_type)) {
            const value_value  = value! as number
            thisSerializer.writeNumber(value_value)
            ArkUIGeneratedNativeModule._SideBarContainerAttribute_sideBarWidth0(node, thisSerializer.asBuffer(), thisSerializer.length())
        } else if ((RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type)) {
            const value_value  = value!
            thisSerializer.writeLength(value_value)
            ArkUIGeneratedNativeModule._SideBarContainerAttribute_sideBarWidth1(node, thisSerializer.asBuffer(), thisSerializer.length())
        } else {
            ArkUIGeneratedNativeModule._SideBarContainerAttribute_sideBarWidth0(node, thisSerializer.asBuffer(), thisSerializer.length())
        }
        thisSerializer.release()
    }

    static MinSideBarWidthImpl(node: KPointer, value: number | Length | undefined) {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.NUMBER) == (value_type)) {
            const value_value  = value! as number
            thisSerializer.writeNumber(value_value)
            ArkUIGeneratedNativeModule._SideBarContainerAttribute_minSideBarWidth0(node, thisSerializer.asBuffer(), thisSerializer.length())
        } else if ((RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type)) {
            const value_value  = value!
            thisSerializer.writeLength(value_value)
            ArkUIGeneratedNativeModule._SideBarContainerAttribute_minSideBarWidth1(node, thisSerializer.asBuffer(), thisSerializer.length())
        } else {
            ArkUIGeneratedNativeModule._SideBarContainerAttribute_minSideBarWidth0(node, thisSerializer.asBuffer(), thisSerializer.length())
        }
        thisSerializer.release()
    }

    static MaxSideBarWidthImpl(node: KPointer, value: number | Length | undefined) {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.NUMBER) == (value_type)) {
            const value_value  = value! as number
            thisSerializer.writeNumber(value_value)
            ArkUIGeneratedNativeModule._SideBarContainerAttribute_maxSideBarWidth0(node, thisSerializer.asBuffer(), thisSerializer.length())
        } else if ((RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type)) {
            const value_value  = value!
            thisSerializer.writeLength(value_value)
            ArkUIGeneratedNativeModule._SideBarContainerAttribute_maxSideBarWidth1(node, thisSerializer.asBuffer(), thisSerializer.length())
        } else {
            ArkUIGeneratedNativeModule._SideBarContainerAttribute_maxSideBarWidth0(node, thisSerializer.asBuffer(), thisSerializer.length())
        }
        thisSerializer.release()
    }

    static DividerImpl(node: KPointer, value: DividerStyle | null | undefined) {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeDividerStyleSidebar(value_value)
        }
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_divider(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}