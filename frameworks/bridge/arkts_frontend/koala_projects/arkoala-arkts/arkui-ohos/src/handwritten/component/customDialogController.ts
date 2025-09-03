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

import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
import { CustomBuilder, Rectangle, AnimateParam, ShadowOptions, ShadowStyle, BlurStyle, BackgroundBlurStyleOptions, BackgroundEffectOptions, KeyboardAvoidMode, HoverModeAreaType } from "./common"
import { DialogAlignment } from "./alertDialog"
import { Offset, ResourceColor, Dimension, BorderRadiuses, EdgeWidths, EdgeColors, EdgeStyles } from "./units"
import { Callback_DismissDialogAction_Void, DismissDialogAction} from "./actionSheet"
import { BorderStyle } from "./enums"
import { LengthMetrics } from "../Graphics"
import { ExtendableComponent } from "./extendableComponent";
import { ImmersiveMode, LevelMode, LevelOrder } from "@ohos/promptAction"
export class CustomDialogControllerInternal {
    public static fromPtr(ptr: KPointer): CustomDialogController {
        const obj : CustomDialogController = new CustomDialogController(undefined)
        obj.peer = new Finalizable(ptr, CustomDialogController.getFinalizer())
        return obj
    }
}
export class CustomDialogController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    customComponent?: ExtendableComponent | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_customdialogcontroller(value: CustomDialogControllerOptions): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeCustomDialogControllerOptions(value)
        const retval  = ArkUIGeneratedNativeModule._CustomDialogController_ctor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(value?: CustomDialogControllerOptions) {
        if ((value) !== (undefined) && (value.baseComponent) !== (undefined))
        {
            const ctorPtr : KPointer = CustomDialogController.ctor_customdialogcontroller((value)!)
            this.peer = new Finalizable(ctorPtr, CustomDialogController.getFinalizer())
            this.customComponent = (value.baseComponent)!
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._CustomDialogController_getFinalizer()
    }
    public open(): void {
        this.open_serialize()
    }
    public close(): void {
        this.close_serialize()
    }
    public getExternalOptions(): CustomDialogControllerExternalOptions {
        return this.getExternalOptions_serialize()
    }
    private open_serialize(): void {
        if (this.customComponent) {
            const peerNode = this.customComponent!.getPeerNode()
            if (peerNode) {
                ArkUIGeneratedNativeModule._CustomDialogController_setOwnerView(this.peer!.ptr, peerNode!.getPeerPtr())
                ArkUIGeneratedNativeModule._CustomDialogController_open(this.peer!.ptr)
            }
        }
    }
    private close_serialize(): void {
        ArkUIGeneratedNativeModule._CustomDialogController_close(this.peer!.ptr)
    }
    private getExternalOptions_serialize(): CustomDialogControllerExternalOptions {
        // @ts-ignore
        const retval = ArkUIGeneratedNativeModule._CustomDialogController_getExternalOptions(this.peer!.ptr) as FixedArray<byte>
        // @ts-ignore
        let exactRetValue: byte[] = new Array<byte>
        for (let i = 0; i < retval.length; i++) {
            // @ts-ignore
            exactRetValue.push(new Byte(retval[i]))
        }
        let retvalDeserializer : Deserializer = new Deserializer(exactRetValue, exactRetValue.length as int32)
        const returnResult : CustomDialogControllerExternalOptions = retvalDeserializer.readCustomDialogControllerExternalOptions()
        return returnResult
    }
}
export interface CustomDialogControllerOptions {
    builder: CustomBuilder;
    cancel?: (() => void);
    autoCancel?: boolean;
    alignment?: DialogAlignment;
    offset?: Offset;
    customStyle?: boolean;
    gridCount?: number;
    maskColor?: ResourceColor;
    maskRect?: Rectangle;
    openAnimation?: AnimateParam;
    closeAnimation?: AnimateParam;
    showInSubWindow?: boolean;
    backgroundColor?: ResourceColor;
    cornerRadius?: Dimension | BorderRadiuses;
    isModal?: boolean;
    onWillDismiss?: ((parameter: DismissDialogAction) => void);
    width?: Dimension;
    height?: Dimension;
    borderWidth?: Dimension | EdgeWidths;
    borderColor?: ResourceColor | EdgeColors;
    borderStyle?: BorderStyle | EdgeStyles;
    shadow?: ShadowOptions | ShadowStyle;
    backgroundBlurStyle?: BlurStyle;
    backgroundBlurStyleOptions?: BackgroundBlurStyleOptions;
    backgroundEffect?: BackgroundEffectOptions;
    keyboardAvoidMode?: KeyboardAvoidMode;
    enableHoverMode?: boolean;
    hoverModeArea?: HoverModeAreaType;
    onDidAppear?: ((data: undefined) => void);
    onDidDisappear?: ((data: undefined) => void);
    onWillAppear?: ((data: undefined) => void);
    onWillDisappear?: ((data: undefined) => void);
    keyboardAvoidDistance?: LengthMetrics;
    levelMode?: LevelMode;
    levelUniqueId?: number;
    immersiveMode?: ImmersiveMode;
    levelOrder?: LevelOrder;
    focusable?: boolean;
    baseComponent?: ExtendableComponent;
}

export interface CustomDialogControllerExternalOptions {
    customStyle?: boolean;
}