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

import { DismissReason, Rectangle, BlurStyle, BackgroundBlurStyleOptions, BackgroundEffectOptions, TransitionEffect, ShadowOptions, ShadowStyle, HoverModeAreaType } from "./common"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr, DeserializerBase, CallbackResource, InteropNativeModule, Tags, nullptr, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { Resource } from "./../generated/resource"
import { VoidCallback, ResourceStr, ResourceColor, Dimension, BorderRadiuses, LocalizedBorderRadiuses, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, EdgeStyles } from "./units"
import { DialogButtonStyle, Color, BorderStyle } from "./enums"
import { DialogAlignment } from "./alertDialog"
import { LevelMode, ImmersiveMode, LevelOrder } from "./../generated/ohos.promptAction"
export interface DismissDialogAction {
    reason: DismissReason
    dismiss(): void
}
export class DismissDialogActionInternal implements MaterializedBase,DismissDialogAction {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get reason(): DismissReason {
        return this.getReason()
    }
    set reason(reason: DismissReason) {
        this.setReason(reason)
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, DismissDialogActionInternal.getFinalizer())
    }
    constructor() {
        this(DismissDialogActionInternal.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._DismissDialogAction_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._DismissDialogAction_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): DismissDialogActionInternal {
        return new DismissDialogActionInternal(ptr)
    }
    public dismiss(): void {
        this.dismiss_serialize()
        return
    }
    private getReason(): DismissReason {
        return this.getReason_serialize()
    }
    private setReason(reason: DismissReason): void {
        const reason_casted = reason as (DismissReason)
        this.setReason_serialize(reason_casted)
        return
    }
    private dismiss_serialize(): void {
        ArkUIGeneratedNativeModule._DismissDialogAction_dismiss(this.peer!.ptr)
    }
    private getReason_serialize(): DismissReason {
        const retval  = ArkUIGeneratedNativeModule._DismissDialogAction_getReason(this.peer!.ptr)
        return TypeChecker.DismissReason_FromNumeric(retval)
    }
    private setReason_serialize(reason: DismissReason): void {
        ArkUIGeneratedNativeModule._DismissDialogAction_setReason(this.peer!.ptr, TypeChecker.DismissReason_ToNumeric(reason))
    }
}
export interface SheetInfo {
    title: string | Resource;
    icon?: string | Resource;
    action: VoidCallback;
}
export interface ActionSheetButtonOptions {
    enabled?: boolean;
    defaultFocus?: boolean;
    style?: DialogButtonStyle;
    value: string | Resource;
    action: VoidCallback;
}
export interface ActionSheetOffset {
    dx: number | string | Resource;
    dy: number | string | Resource;
}
export interface ActionSheetOptions {
    title: string | Resource;
    subtitle?: ResourceStr;
    message: string | Resource;
    confirm?: ActionSheetButtonOptions;
    cancel?: VoidCallback;
    sheets: Array<SheetInfo>;
    autoCancel?: boolean;
    alignment?: DialogAlignment;
    offset?: ActionSheetOffset;
    maskRect?: Rectangle;
    showInSubWindow?: boolean;
    isModal?: boolean;
    backgroundColor?: ResourceColor;
    backgroundBlurStyle?: BlurStyle;
    backgroundBlurStyleOptions?: BackgroundBlurStyleOptions;
    backgroundEffect?: BackgroundEffectOptions;
    onWillDismiss?: ((value0: DismissDialogAction) => void);
    transition?: TransitionEffect;
    cornerRadius?: Dimension | BorderRadiuses | LocalizedBorderRadiuses;
    width?: Dimension;
    height?: Dimension;
    borderWidth?: Dimension | EdgeWidths | LocalizedEdgeWidths;
    borderColor?: ResourceColor | EdgeColors | LocalizedEdgeColors;
    borderStyle?: BorderStyle | EdgeStyles;
    shadow?: ShadowOptions | ShadowStyle;
    enableHoverMode?: boolean;
    hoverModeArea?: HoverModeAreaType;
    onDidAppear?: (() => void);
    onDidDisappear?: (() => void);
    onWillAppear?: (() => void);
    onWillDisappear?: (() => void);
    levelMode?: LevelMode;
    levelUniqueId?: number;
    immersiveMode?: ImmersiveMode;
    levelOrder?: LevelOrder;
}
export class DismissDialogAction_serializer {
    public static write(buffer: SerializerBase, value: DismissDialogAction): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): DismissDialogAction {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return DismissDialogActionInternal.fromPtr(ptr)
    }
}
