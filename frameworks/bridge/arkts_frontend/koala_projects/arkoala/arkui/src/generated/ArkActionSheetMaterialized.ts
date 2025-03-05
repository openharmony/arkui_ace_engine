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
import { Finalizable, isResource, isInstanceOf, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, KPointer, MaterializedBase } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export class ActionSheetInternal {
    public static fromPtr(ptr: KPointer): ActionSheet {
        const obj: ActionSheet = new ActionSheet()
        obj.peer = new Finalizable(ptr, ActionSheet.getFinalizer())
        return obj
    }
}
export class ActionSheet implements MaterializedBase {
    peer?: Finalizable | undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_actionsheet(): KPointer {
        const retval = ArkUIGeneratedNativeModule._ActionSheet_ctor()
        return retval
    }
     constructor() {
        // Constructor does not have parameters.
        // It means that the static method call invokes ctor method as well
        // when all arguments are undefined.
        const ctorPtr: KPointer = ActionSheet.ctor_actionsheet()
        this.peer = new Finalizable(ctorPtr, ActionSheet.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ActionSheet_getFinalizer()
    }
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
