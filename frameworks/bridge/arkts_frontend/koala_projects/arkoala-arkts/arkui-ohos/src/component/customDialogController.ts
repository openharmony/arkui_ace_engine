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
import { DialogAlignment, LevelOrder } from "./alertDialog"
import { Offset, ResourceColor, Dimension, BorderRadiuses, EdgeWidths, EdgeColors, EdgeStyles } from "./units"
import { Callback_DismissDialogAction_Void, DismissDialogAction, LevelMode, ImmersiveMode } from "./actionSheet"
import { BorderStyle } from "./enums"
import { LengthMetrics } from "../Graphics"
export class CustomDialogControllerInternal {
    public static fromPtr(ptr: KPointer): CustomDialogController {
        const obj : CustomDialogController = new CustomDialogController(undefined)
        obj.peer = new Finalizable(ptr, CustomDialogController.getFinalizer())
        return obj
    }
}
export class CustomDialogController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
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
        if ((value) !== (undefined))
        {
            const ctorPtr : KPointer = CustomDialogController.ctor_customdialogcontroller((value)!)
            this.peer = new Finalizable(ctorPtr, CustomDialogController.getFinalizer())
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._CustomDialogController_getFinalizer()
    }
    public open(): undefined {
        return this.open_serialize()
    }
    public close(): undefined {
        return this.close_serialize()
    }
    private open_serialize(): undefined {
        const retval  = ArkUIGeneratedNativeModule._CustomDialogController_open(this.peer!.ptr)
        return retval
    }
    private close_serialize(): undefined {
        const retval  = ArkUIGeneratedNativeModule._CustomDialogController_close(this.peer!.ptr)
        return retval
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
    onDidAppear?: (() => void);
    onDidDisappear?: (() => void);
    onWillAppear?: (() => void);
    onWillDisappear?: (() => void);
    keyboardAvoidDistance?: LengthMetrics;
    levelMode?: LevelMode;
    levelUniqueId?: number;
    immersiveMode?: ImmersiveMode;
    levelOrder?: LevelOrder;
    focusable?: boolean;
}
