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

import matrix4 from "@ohos.matrix4"
import image from "@ohos.multimedia.image"
import _Want from "@ohos.app.ability.Want"
import webview from "@ohos.web.webview"
import common from "@ohos.app.ability.common"
import pointer from '@ohos.multimodalInput.pointer'
import unifiedDataChannel from "@ohos.data.unifiedDataChannel"
import uniformTypeDescriptor from "@ohos.data.uniformTypeDescriptor"
import uiEffect from "@ohos.graphics.uiEffect"
import curves from "@ohos.curves"

export * from "@ohos.base"
export * from "@ohos.arkui.drawableDescriptor"

export type TranslateOption = matrix4.TranslateOption
export type ScaleOption = matrix4.ScaleOption
export type RotateOption = matrix4.RotateOption
export type PolyToPolyOptions = matrix4.PolyToPolyOptions
export type Matrix4Transit = matrix4.Matrix4Transit
export type Filter = uiEffect.Filter
export type VisualEffect = uiEffect.VisualEffect
export type BrightnessBlender = uiEffect.BrightnessBlender
export type PixelMap = image.PixelMap
export type AbilityWant = _Want
export type WebviewController = webview.WebviewController
export type Context = common.Context
export type ICurve = curves.ICurve
export type Curve = curves.Curve
export type PointerStyle = pointer.PointerStyle
export type UnifiedData = unifiedDataChannel.UnifiedData
export type Summary = unifiedDataChannel.Summary
export type DataSyncOptions = unifiedDataChannel.GetDataParams
export type UniformDataType = uniformTypeDescriptor.UniformDataType
export type UIAbilityContext = common.UIAbilityContext
export type ExtensionContext = common.ExtensionContext
