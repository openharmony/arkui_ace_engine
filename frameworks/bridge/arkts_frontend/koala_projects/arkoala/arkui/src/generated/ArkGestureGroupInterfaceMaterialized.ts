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

import { GestureMode, GestureType, GestureInterface, TapGestureParameters, PanDirection, SwipeDirection, FingerInfo } from "./ArkGestureInterfaces"
import { TapGestureInterface, TapGestureInterfaceInternal } from "./ArkTapGestureInterfaceMaterialized"
import { LongPressGestureInterface, LongPressGestureInterfaceInternal } from "./ArkLongPressGestureInterfaceMaterialized"
import { PanGestureInterface, PanGestureInterfaceInternal } from "./ArkPanGestureInterfaceMaterialized"
import { PinchGestureInterface, PinchGestureInterfaceInternal } from "./ArkPinchGestureInterfaceMaterialized"
import { SwipeGestureInterface, SwipeGestureInterfaceInternal } from "./ArkSwipeGestureInterfaceMaterialized"
import { RotationGestureInterface, RotationGestureInterfaceInternal } from "./ArkRotationGestureInterfaceMaterialized"
import { SourceTool, EventTarget, SourceType } from "./ArkCommonInterfaces"
import { PanGestureOptions, PanGestureOptionsInternal } from "./ArkPanGestureOptionsMaterialized"
import { GestureEvent, GestureEventInternal } from "./ArkGestureEventMaterialized"
import { BaseEvent, BaseEventInternal } from "./ArkBaseEventMaterialized"
import { Area, Length, Position } from "./ArkUnitsInterfaces"
import { Resource } from "./ArkResourceInterfaces"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, isInstanceOf } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { isResource, isPadding } from "./../utils"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export interface GestureGroupInterface {
    onCancel(event: (() => void)): GestureGroupInterface
}
export class GestureGroupInterfaceInternal implements MaterializedBase,GestureGroupInterface {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_gesturegroupinterface(): KPointer {
        const retval = ArkUIGeneratedNativeModule._GestureGroupInterface_ctor()
        return retval
    }
     constructor() {
        const ctorPtr: KPointer = GestureGroupInterfaceInternal.ctor_gesturegroupinterface()
        this.peer = new Finalizable(ctorPtr, GestureGroupInterfaceInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._GestureGroupInterface_getFinalizer()
    }
    public onCancel(event: (() => void)): GestureGroupInterface {
        const event_casted = event as ((() => void))
        return this.onCancel_serialize(event_casted)
    }
    private onCancel_serialize(event: (() => void)): GestureGroupInterface {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval = ArkUIGeneratedNativeModule._GestureGroupInterface_onCancel(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        const obj: GestureGroupInterface = GestureGroupInterfaceInternal.fromPtr(retval)
        return obj
    }
    public static fromPtr(ptr: KPointer): GestureGroupInterfaceInternal {
        const obj: GestureGroupInterfaceInternal = new GestureGroupInterfaceInternal()
        obj.peer = new Finalizable(ptr, GestureGroupInterfaceInternal.getFinalizer())
        return obj
    }
}
