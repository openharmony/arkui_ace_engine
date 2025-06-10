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

import { ActionSheetOptions, ActionSheetButtonOptions, SheetInfo, ActionSheetOffset, DismissDialogAction } from "./ArkActionSheetInterfaces"
import { Resource } from "./ArkResourceInterfaces"
import { ResourceStr, VoidCallback, ResourceColor, Dimension, BorderRadiuses, LocalizedBorderRadiuses, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, EdgeStyles, Length } from "./ArkUnitsInterfaces"
import { DialogAlignment } from "./ArkAlertDialogInterfaces"
import { Rectangle, BlurStyle, ShadowOptions, ShadowStyle, HoverModeAreaType, DismissReason, TransitionEffects, TranslateOptions, RotateOptions, ScaleOptions, TransitionEdge, AnimateParam, ShadowType, FinishCallbackType, ExpectedFrameRateRange } from "./ArkCommonInterfaces"
import { TransitionEffect, TransitionEffectInternal } from "./ArkTransitionEffectMaterialized"
import { BorderStyle, DialogButtonStyle, Color, ColoringStrategy, Curve, PlayMode } from "./ArkEnumsInterfaces"
import { LengthMetrics, LengthMetricsInternal } from "./ArkLengthMetricsMaterialized"
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
export class ActionSheet {
    public static show(value: ActionSheetOptions): undefined {
        const value_casted = value as (ActionSheetOptions)
        return ActionSheet.show_serialize(value_casted)
    }
    private static show_serialize(value: ActionSheetOptions): undefined {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeActionSheetOptions(value)
        const retval = ArkUIGeneratedNativeModule._ActionSheet_show(thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
}
