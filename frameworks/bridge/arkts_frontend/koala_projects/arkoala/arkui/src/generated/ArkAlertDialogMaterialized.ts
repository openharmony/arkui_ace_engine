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

import { AlertDialogParamWithConfirm, AlertDialogParamWithButtons, AlertDialogParamWithOptions, AlertDialogParam, DialogAlignment, TextStyle_alert_dialog, AlertDialogButtonBaseOptions, AlertDialogButtonOptions, DialogButtonDirection } from "./ArkAlertDialogInterfaces"
import { ResourceStr, VoidCallback, Offset, ResourceColor, Dimension, BorderRadiuses, LocalizedBorderRadiuses, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, EdgeStyles, Length } from "./ArkUnitsInterfaces"
import { Rectangle, BlurStyle, ShadowOptions, ShadowStyle, HoverModeAreaType, DismissReason, TransitionEffects, TranslateOptions, RotateOptions, ScaleOptions, TransitionEdge, AnimateParam, ShadowType, FinishCallbackType, ExpectedFrameRateRange } from "./ArkCommonInterfaces"
import { TransitionEffect, TransitionEffectInternal } from "./ArkTransitionEffectMaterialized"
import { BorderStyle, Color, ColoringStrategy, WordBreak, Curve, PlayMode, DialogButtonStyle } from "./ArkEnumsInterfaces"
import { DismissDialogAction } from "./ArkActionSheetInterfaces"
import { LengthMetrics, LengthMetricsInternal } from "./ArkLengthMetricsMaterialized"
import { Resource } from "./ArkResourceInterfaces"
import { ICurve, ICurveInternal } from "./ArkICurveMaterialized"
import { LengthUnit } from "./ArkArkuiExternalInterfaces"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, isInstanceOf } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { isResource, isPadding } from "./../utils"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export class AlertDialog {
    public static show(value: AlertDialogParamWithConfirm | AlertDialogParamWithButtons | AlertDialogParamWithOptions): undefined {
        const value_casted = value as (AlertDialogParamWithConfirm | AlertDialogParamWithButtons | AlertDialogParamWithOptions)
        return AlertDialog.show_serialize(value_casted)
    }
    private static show_serialize(value: AlertDialogParamWithConfirm | AlertDialogParamWithButtons | AlertDialogParamWithOptions): undefined {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (((RuntimeType.OBJECT) == (value_type)) && ((value!.hasOwnProperty("confirm")))) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<AlertDialogParamWithConfirm>(value)
            thisSerializer.writeAlertDialogParamWithConfirm(value_0)
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && ((value!.hasOwnProperty("primaryButton")))) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<AlertDialogParamWithButtons>(value)
            thisSerializer.writeAlertDialogParamWithButtons(value_1)
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && ((value!.hasOwnProperty("buttons")))) {
            thisSerializer.writeInt8(2)
            const value_2 = unsafeCast<AlertDialogParamWithOptions>(value)
            thisSerializer.writeAlertDialogParamWithOptions(value_2)
        }
        const retval = ArkUIGeneratedNativeModule._AlertDialog_show(thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
}
