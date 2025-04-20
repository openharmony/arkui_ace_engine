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
import { PanDirection, SwipeDirection, GestureMode, GestureMask, Callback_GestureEvent_Void } from "./../component/gesture";
import { GestureEvent, GestureEventInternal } from "./../component/gesture";
import { SourceTool } from "./../component/common";
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components";
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop";
import { unsafeCast, int32, int64, float32 } from "@koalaui/common";
import { Serializer } from "./peers/Serializer";
import { CallbackKind } from "./peers/CallbackKind";
import { Deserializer } from "./peers/Deserializer";
import { CallbackTransformer } from "./peers/CallbackTransformer";
export class GestureOps {
    public static createTapGesture(fingers: number, count: number, distanceThreshold: number, isFingerCountLimited: boolean): KPointer {
        const fingers_casted = fingers as (number);
        const count_casted = count as (number);
        const distanceThreshold_casted = distanceThreshold as (number);
        const isFingerCountLimited_casted = isFingerCountLimited as (boolean);
        return GestureOps.createTapGesture_serialize(fingers_casted, count_casted, distanceThreshold_casted, isFingerCountLimited_casted);
    }
    public static createLongPressGesture(fingers: number, repeat: boolean, duration: number, isFingerCountLimited: boolean): KPointer {
        const fingers_casted = fingers as (number);
        const repeat_casted = repeat as (boolean);
        const duration_casted = duration as (number);
        const isFingerCountLimited_casted = isFingerCountLimited as (boolean);
        return GestureOps.createLongPressGesture_serialize(fingers_casted, repeat_casted, duration_casted, isFingerCountLimited_casted);
    }
    public static createPanGesture(fingers: number, direction: PanDirection, distance: number, isFingerCountLimited: boolean): KPointer {
        const fingers_casted = fingers as (number);
        const direction_casted = direction as (PanDirection);
        const distance_casted = distance as (number);
        const isFingerCountLimited_casted = isFingerCountLimited as (boolean);
        return GestureOps.createPanGesture_serialize(fingers_casted, direction_casted, distance_casted, isFingerCountLimited_casted);
    }
    public static createPinchGesture(fingers: number, distance: number, isFingerCountLimited: boolean): KPointer {
        const fingers_casted = fingers as (number);
        const distance_casted = distance as (number);
        const isFingerCountLimited_casted = isFingerCountLimited as (boolean);
        return GestureOps.createPinchGesture_serialize(fingers_casted, distance_casted, isFingerCountLimited_casted);
    }
    public static createRotationGesture(fingers: number, angle: number, isFingerCountLimited: boolean): KPointer {
        const fingers_casted = fingers as (number);
        const angle_casted = angle as (number);
        const isFingerCountLimited_casted = isFingerCountLimited as (boolean);
        return GestureOps.createRotationGesture_serialize(fingers_casted, angle_casted, isFingerCountLimited_casted);
    }
    public static createSwipeGesture(fingers: number, direction: SwipeDirection, speed: number, isFingerCountLimited: boolean): KPointer {
        const fingers_casted = fingers as (number);
        const direction_casted = direction as (SwipeDirection);
        const speed_casted = speed as (number);
        const isFingerCountLimited_casted = isFingerCountLimited as (boolean);
        return GestureOps.createSwipeGesture_serialize(fingers_casted, direction_casted, speed_casted, isFingerCountLimited_casted);
    }
    public static createGestureGroup(mode: GestureMode): KPointer {
        const mode_casted = mode as (GestureMode);
        return GestureOps.createGestureGroup_serialize(mode_casted);
    }
    public static setOnAction(gesture: KPointer, onAction: ((event: GestureEvent) => void)): void {
        const gesture_casted = gesture as (KPointer);
        const onAction_casted = onAction as (((event: GestureEvent) => void));
        GestureOps.setOnAction_serialize(gesture_casted, onAction_casted);
        return;
    }
    public static setOnActionStart(gesture: KPointer, onActionStart: ((event: GestureEvent) => void)): void {
        const gesture_casted = gesture as (KPointer);
        const onActionStart_casted = onActionStart as (((event: GestureEvent) => void));
        GestureOps.setOnActionStart_serialize(gesture_casted, onActionStart_casted);
        return;
    }
    public static setOnActionUpdate(gesture: KPointer, onActionUpdate: ((event: GestureEvent) => void)): void {
        const gesture_casted = gesture as (KPointer);
        const onActionUpdate_casted = onActionUpdate as (((event: GestureEvent) => void));
        GestureOps.setOnActionUpdate_serialize(gesture_casted, onActionUpdate_casted);
        return;
    }
    public static setOnActionEnd(gesture: KPointer, onActionEnd: ((event: GestureEvent) => void)): void {
        const gesture_casted = gesture as (KPointer);
        const onActionEnd_casted = onActionEnd as (((event: GestureEvent) => void));
        GestureOps.setOnActionEnd_serialize(gesture_casted, onActionEnd_casted);
        return;
    }
    public static setOnActionCancel(gesture: KPointer, onActionCancel: (() => void)): void {
        const gesture_casted = gesture as (KPointer);
        const onActionCancel_casted = onActionCancel as ((() => void));
        GestureOps.setOnActionCancel_serialize(gesture_casted, onActionCancel_casted);
        return;
    }
    public static setGestureTag(gesture: KPointer, tag: string): void {
        const gesture_casted = gesture as (KPointer);
        const tag_casted = tag as (string);
        GestureOps.setGestureTag_serialize(gesture_casted, tag_casted);
        return;
    }
    public static setAllowedTypes(gesture: KPointer, types: Array<SourceTool>): void {
        const gesture_casted = gesture as (KPointer);
        const types_casted = types as (Array<SourceTool>);
        GestureOps.setAllowedTypes_serialize(gesture_casted, types_casted);
        return;
    }
    public static addGestureToNode(node: KPointer, priority: number, mask: GestureMask, gesture: KPointer): void {
        const node_casted = node as (KPointer);
        const priority_casted = priority as (number);
        const mask_casted = mask as (GestureMask);
        const gesture_casted = gesture as (KPointer);
        GestureOps.addGestureToNode_serialize(node_casted, priority_casted, mask_casted, gesture_casted);
        return;
    }
    public static addGestureToGroup(group: KPointer, gesture: KPointer): void {
        const group_casted = group as (KPointer);
        const gesture_casted = gesture as (KPointer);
        GestureOps.addGestureToGroup_serialize(group_casted, gesture_casted);
        return;
    }
    private static createTapGesture_serialize(fingers: number, count: number, distanceThreshold: number, isFingerCountLimited: boolean): KPointer {
        const retval = ArkUIGeneratedNativeModule._GestureOps_createTapGesture(fingers, count, distanceThreshold, isFingerCountLimited ? 1 : 0);
        return retval;
    }
    private static createLongPressGesture_serialize(fingers: number, repeat: boolean, duration: number, isFingerCountLimited: boolean): KPointer {
        const retval = ArkUIGeneratedNativeModule._GestureOps_createLongPressGesture(fingers, repeat ? 1 : 0, duration, isFingerCountLimited ? 1 : 0);
        return retval;
    }
    private static createPanGesture_serialize(fingers: number, direction: PanDirection, distance: number, isFingerCountLimited: boolean): KPointer {
        const retval = ArkUIGeneratedNativeModule._GestureOps_createPanGesture(fingers, direction.valueOf(), distance, isFingerCountLimited ? 1 : 0);
        return retval;
    }
    private static createPinchGesture_serialize(fingers: number, distance: number, isFingerCountLimited: boolean): KPointer {
        const retval = ArkUIGeneratedNativeModule._GestureOps_createPinchGesture(fingers, distance, isFingerCountLimited ? 1 : 0);
        return retval;
    }
    private static createRotationGesture_serialize(fingers: number, angle: number, isFingerCountLimited: boolean): KPointer {
        const retval = ArkUIGeneratedNativeModule._GestureOps_createRotationGesture(fingers, angle, isFingerCountLimited ? 1 : 0);
        return retval;
    }
    private static createSwipeGesture_serialize(fingers: number, direction: SwipeDirection, speed: number, isFingerCountLimited: boolean): KPointer {
        const retval = ArkUIGeneratedNativeModule._GestureOps_createSwipeGesture(fingers, direction.valueOf(), speed, isFingerCountLimited ? 1 : 0);
        return retval;
    }
    private static createGestureGroup_serialize(mode: GestureMode): KPointer {
        const retval = ArkUIGeneratedNativeModule._GestureOps_createGestureGroup(mode.valueOf());
        return retval;
    }
    private static setOnAction_serialize(gesture: KPointer, onAction: ((event: GestureEvent) => void)): void {
        const thisSerializer: Serializer = Serializer.hold();
        thisSerializer.holdAndWriteCallback(onAction);
        ArkUIGeneratedNativeModule._GestureOps_setOnAction(gesture, thisSerializer.asBuffer(), thisSerializer.length());
        thisSerializer.release();
    }
    private static setOnActionStart_serialize(gesture: KPointer, onActionStart: ((event: GestureEvent) => void)): void {
        const thisSerializer: Serializer = Serializer.hold();
        thisSerializer.holdAndWriteCallback(onActionStart);
        ArkUIGeneratedNativeModule._GestureOps_setOnActionStart(gesture, thisSerializer.asBuffer(), thisSerializer.length());
        thisSerializer.release();
    }
    private static setOnActionUpdate_serialize(gesture: KPointer, onActionUpdate: ((event: GestureEvent) => void)): void {
        const thisSerializer: Serializer = Serializer.hold();
        thisSerializer.holdAndWriteCallback(onActionUpdate);
        ArkUIGeneratedNativeModule._GestureOps_setOnActionUpdate(gesture, thisSerializer.asBuffer(), thisSerializer.length());
        thisSerializer.release();
    }
    private static setOnActionEnd_serialize(gesture: KPointer, onActionEnd: ((event: GestureEvent) => void)): void {
        const thisSerializer: Serializer = Serializer.hold();
        thisSerializer.holdAndWriteCallback(onActionEnd);
        ArkUIGeneratedNativeModule._GestureOps_setOnActionEnd(gesture, thisSerializer.asBuffer(), thisSerializer.length());
        thisSerializer.release();
    }
    private static setOnActionCancel_serialize(gesture: KPointer, onActionCancel: (() => void)): void {
        const thisSerializer: Serializer = Serializer.hold();
        thisSerializer.holdAndWriteCallback(onActionCancel);
        ArkUIGeneratedNativeModule._GestureOps_setOnActionCancel(gesture, thisSerializer.asBuffer(), thisSerializer.length());
        thisSerializer.release();
    }
    private static setGestureTag_serialize(gesture: KPointer, tag: string): void {
        ArkUIGeneratedNativeModule._GestureOps_setGestureTag(gesture, tag);
    }
    private static setAllowedTypes_serialize(gesture: KPointer, types: Array<SourceTool>): void {
        const thisSerializer: Serializer = Serializer.hold();
        thisSerializer.writeInt32(types.length as int32);
        for (let i = 0; i < types.length; i++) {
            const types_element: SourceTool = types[i];
            thisSerializer.writeInt32(types_element.valueOf());
        }
        ArkUIGeneratedNativeModule._GestureOps_setAllowedTypes(gesture, thisSerializer.asBuffer(), thisSerializer.length());
        thisSerializer.release();
    }
    private static addGestureToNode_serialize(node: KPointer, priority: number, mask: GestureMask, gesture: KPointer): void {
        ArkUIGeneratedNativeModule._GestureOps_addGestureToNode(node, priority, mask.valueOf(), gesture);
    }
    private static addGestureToGroup_serialize(group: KPointer, gesture: KPointer): void {
        ArkUIGeneratedNativeModule._GestureOps_addGestureToGroup(group, gesture);
    }
}
