/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
    namespace CanvasRendererModifier {
        Ark_NativePointer CtorImpl() {
            return 0;
        }
        Ark_NativePointer GetFinalizerImpl() {
            return 0;
        }
        void DrawImage_ImageBitmapPixelMap_number_numberImpl(CanvasRendererPeer* peer, const Union_ImageBitmap_PixelMap* image, const Ark_Number* dx, const Ark_Number* dy) {
        }
        void DrawImage_ImageBitmapPixelMap_number_number_number_numberImpl(CanvasRendererPeer* peer, const Union_ImageBitmap_PixelMap* image, const Ark_Number* dx, const Ark_Number* dy, const Ark_Number* dw, const Ark_Number* dh) {
        }
        void DrawImage_ImageBitmapPixelMap_number_number_number_number_number_number_number_numberImpl(CanvasRendererPeer* peer, const Union_ImageBitmap_PixelMap* image, const Ark_Number* sx, const Ark_Number* sy, const Ark_Number* sw, const Ark_Number* sh, const Ark_Number* dx, const Ark_Number* dy, const Ark_Number* dw, const Ark_Number* dh) {
        }
        void BeginPathImpl(CanvasRendererPeer* peer) {
        }
        void Clip_CanvasFillRuleImpl(CanvasRendererPeer* peer, const Opt_CanvasFillRule* fillRule) {
        }
        void Clip_PathD_CanvasFillRuleImpl(CanvasRendererPeer* peer, const Ark_Materialized* path, const Opt_CanvasFillRule* fillRule) {
        }
        void Fill_CanvasFillRuleImpl(CanvasRendererPeer* peer, const Opt_CanvasFillRule* fillRule) {
        }
        void Fill_PathD_CanvasFillRuleImpl(CanvasRendererPeer* peer, const Ark_Materialized* path, const Opt_CanvasFillRule* fillRule) {
        }
        void Stroke_Impl(CanvasRendererPeer* peer) {
        }
        void Stroke_PathDImpl(CanvasRendererPeer* peer, const Ark_Materialized* path) {
        }
        Ark_NativePointer CreateLinearGradientImpl(CanvasRendererPeer* peer, const Ark_Number* x0, const Ark_Number* y0, const Ark_Number* x1, const Ark_Number* y1) {
            return 0;
        }
        Ark_NativePointer CreatePatternImpl(CanvasRendererPeer* peer, const Ark_Materialized* image, const Union_Ark_String_Ark_Undefined* repetition) {
            return 0;
        }
        Ark_NativePointer CreateRadialGradientImpl(CanvasRendererPeer* peer, const Ark_Number* x0, const Ark_Number* y0, const Ark_Number* r0, const Ark_Number* x1, const Ark_Number* y1, const Ark_Number* r1) {
            return 0;
        }
        Ark_NativePointer CreateConicGradientImpl(CanvasRendererPeer* peer, const Ark_Number* startAngle, const Ark_Number* x, const Ark_Number* y) {
            return 0;
        }
        Ark_NativePointer CreateImageData_number_numberImpl(CanvasRendererPeer* peer, const Ark_Number* sw, const Ark_Number* sh) {
            return 0;
        }
        Ark_NativePointer CreateImageData_ImageDataImpl(CanvasRendererPeer* peer, const ImageData* imagedata) {
            return 0;
        }
        Ark_NativePointer GetImageDataImpl(CanvasRendererPeer* peer, const Ark_Number* sx, const Ark_Number* sy, const Ark_Number* sw, const Ark_Number* sh) {
            return 0;
        }
        Ark_NativePointer GetPixelMapImpl(CanvasRendererPeer* peer, const Ark_Number* sx, const Ark_Number* sy, const Ark_Number* sw, const Ark_Number* sh) {
            return 0;
        }
        void PutImageData_ImageData_numberstring_numberstringImpl(CanvasRendererPeer* peer, const ImageData* imagedata, const Union_Ark_Number_Ark_String* dx, const Union_Ark_Number_Ark_String* dy) {
        }
        void PutImageData_ImageData_numberstring_numberstring_numberstring_numberstring_numberstring_numberstringImpl(CanvasRendererPeer* peer, const ImageData* imagedata, const Union_Ark_Number_Ark_String* dx, const Union_Ark_Number_Ark_String* dy, const Union_Ark_Number_Ark_String* dirtyX, const Union_Ark_Number_Ark_String* dirtyY, const Union_Ark_Number_Ark_String* dirtyWidth, const Union_Ark_Number_Ark_String* dirtyHeight) {
        }
        void GetLineDashImpl(CanvasRendererPeer* peer) {
        }
        void SetLineDashImpl(CanvasRendererPeer* peer, const Array_Ark_Number* segments) {
        }
        void ClearRectImpl(CanvasRendererPeer* peer, const Ark_Number* x, const Ark_Number* y, const Ark_Number* w, const Ark_Number* h) {
        }
        void FillRectImpl(CanvasRendererPeer* peer, const Ark_Number* x, const Ark_Number* y, const Ark_Number* w, const Ark_Number* h) {
        }
        void StrokeRectImpl(CanvasRendererPeer* peer, const Ark_Number* x, const Ark_Number* y, const Ark_Number* w, const Ark_Number* h) {
        }
        void RestoreImpl(CanvasRendererPeer* peer) {
        }
        void SaveImpl(CanvasRendererPeer* peer) {
        }
        void FillTextImpl(CanvasRendererPeer* peer, const Ark_String* text, const Ark_Number* x, const Ark_Number* y, const Opt_Ark_Number* maxWidth) {
        }
        Ark_NativePointer MeasureTextImpl(CanvasRendererPeer* peer, const Ark_String* text) {
            return 0;
        }
        void StrokeTextImpl(CanvasRendererPeer* peer, const Ark_String* text, const Ark_Number* x, const Ark_Number* y, const Opt_Ark_Number* maxWidth) {
        }
        Ark_NativePointer GetTransformImpl(CanvasRendererPeer* peer) {
            return 0;
        }
        void ResetTransformImpl(CanvasRendererPeer* peer) {
        }
        void RotateImpl(CanvasRendererPeer* peer, const Ark_Number* angle) {
        }
        void ScaleImpl(CanvasRendererPeer* peer, const Ark_Number* x, const Ark_Number* y) {
        }
        void SetTransform_number_number_number_number_number_numberImpl(CanvasRendererPeer* peer, const Ark_Number* a, const Ark_Number* b, const Ark_Number* c, const Ark_Number* d, const Ark_Number* e, const Ark_Number* f) {
        }
        void SetTransform_MatrixDImpl(CanvasRendererPeer* peer, const Opt_Matrix2D* transform) {
        }
        void TransformImpl(CanvasRendererPeer* peer, const Ark_Number* a, const Ark_Number* b, const Ark_Number* c, const Ark_Number* d, const Ark_Number* e, const Ark_Number* f) {
        }
        void TranslateImpl(CanvasRendererPeer* peer, const Ark_Number* x, const Ark_Number* y) {
        }
        void SetPixelMapImpl(CanvasRendererPeer* peer, const Opt_PixelMap* value) {
        }
        void TransferFromImageBitmapImpl(CanvasRendererPeer* peer, const Ark_Materialized* bitmap) {
        }
        void SaveLayerImpl(CanvasRendererPeer* peer) {
        }
        void RestoreLayerImpl(CanvasRendererPeer* peer) {
        }
        void ResetImpl(CanvasRendererPeer* peer) {
        }
    } // CanvasRendererModifier
    const GENERATED_ArkUICanvasRendererAccessor* GetCanvasRendererAccessor() {
        static const GENERATED_ArkUICanvasRendererAccessor CanvasRendererAccessorImpl {
            CanvasRendererModifier::CtorImpl,
            CanvasRendererModifier::GetFinalizerImpl,
            CanvasRendererModifier::DrawImage_ImageBitmapPixelMap_number_numberImpl,
            CanvasRendererModifier::DrawImage_ImageBitmapPixelMap_number_number_number_numberImpl,
            CanvasRendererModifier::DrawImage_ImageBitmapPixelMap_number_number_number_number_number_number_number_numberImpl,
            CanvasRendererModifier::BeginPathImpl,
            CanvasRendererModifier::Clip_CanvasFillRuleImpl,
            CanvasRendererModifier::Clip_PathD_CanvasFillRuleImpl,
            CanvasRendererModifier::Fill_CanvasFillRuleImpl,
            CanvasRendererModifier::Fill_PathD_CanvasFillRuleImpl,
            CanvasRendererModifier::Stroke_Impl,
            CanvasRendererModifier::Stroke_PathDImpl,
            CanvasRendererModifier::CreateLinearGradientImpl,
            CanvasRendererModifier::CreatePatternImpl,
            CanvasRendererModifier::CreateRadialGradientImpl,
            CanvasRendererModifier::CreateConicGradientImpl,
            CanvasRendererModifier::CreateImageData_number_numberImpl,
            CanvasRendererModifier::CreateImageData_ImageDataImpl,
            CanvasRendererModifier::GetImageDataImpl,
            CanvasRendererModifier::GetPixelMapImpl,
            CanvasRendererModifier::PutImageData_ImageData_numberstring_numberstringImpl,
            CanvasRendererModifier::PutImageData_ImageData_numberstring_numberstring_numberstring_numberstring_numberstring_numberstringImpl,
            CanvasRendererModifier::GetLineDashImpl,
            CanvasRendererModifier::SetLineDashImpl,
            CanvasRendererModifier::ClearRectImpl,
            CanvasRendererModifier::FillRectImpl,
            CanvasRendererModifier::StrokeRectImpl,
            CanvasRendererModifier::RestoreImpl,
            CanvasRendererModifier::SaveImpl,
            CanvasRendererModifier::FillTextImpl,
            CanvasRendererModifier::MeasureTextImpl,
            CanvasRendererModifier::StrokeTextImpl,
            CanvasRendererModifier::GetTransformImpl,
            CanvasRendererModifier::ResetTransformImpl,
            CanvasRendererModifier::RotateImpl,
            CanvasRendererModifier::ScaleImpl,
            CanvasRendererModifier::SetTransform_number_number_number_number_number_numberImpl,
            CanvasRendererModifier::SetTransform_MatrixDImpl,
            CanvasRendererModifier::TransformImpl,
            CanvasRendererModifier::TranslateImpl,
            CanvasRendererModifier::SetPixelMapImpl,
            CanvasRendererModifier::TransferFromImageBitmapImpl,
            CanvasRendererModifier::SaveLayerImpl,
            CanvasRendererModifier::RestoreLayerImpl,
            CanvasRendererModifier::ResetImpl,
        };
        return &CanvasRendererAccessorImpl;
    }

}
