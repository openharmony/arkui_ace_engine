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
    namespace Matrix2DModifier {
        Ark_NativePointer CtorImpl() {
            return 0;
        }
        Ark_NativePointer GetFinalizerImpl() {
            return 0;
        }
        Ark_NativePointer IdentityImpl(Matrix2DPeer* peer) {
            return 0;
        }
        Ark_NativePointer InvertImpl(Matrix2DPeer* peer) {
            return 0;
        }
        Ark_NativePointer MultiplyImpl(Matrix2DPeer* peer, const Opt_Matrix2D* other) {
            return 0;
        }
        Ark_NativePointer Rotate_number_numberImpl(Matrix2DPeer* peer, const Opt_Ark_Number* rx, const Opt_Ark_Number* ry) {
            return 0;
        }
        Ark_NativePointer Rotate_number_number_numberImpl(Matrix2DPeer* peer, const Ark_Number* degree, const Opt_Ark_Number* rx, const Opt_Ark_Number* ry) {
            return 0;
        }
        Ark_NativePointer TranslateImpl(Matrix2DPeer* peer, const Opt_Ark_Number* tx, const Opt_Ark_Number* ty) {
            return 0;
        }
        Ark_NativePointer ScaleImpl(Matrix2DPeer* peer, const Opt_Ark_Number* sx, const Opt_Ark_Number* sy) {
            return 0;
        }
    } // Matrix2DModifier
    const GENERATED_ArkUIMatrix2DAccessor* GetMatrix2DAccessor() {
        static const GENERATED_ArkUIMatrix2DAccessor Matrix2DAccessorImpl {
            Matrix2DModifier::CtorImpl,
            Matrix2DModifier::GetFinalizerImpl,
            Matrix2DModifier::IdentityImpl,
            Matrix2DModifier::InvertImpl,
            Matrix2DModifier::MultiplyImpl,
            Matrix2DModifier::Rotate_number_numberImpl,
            Matrix2DModifier::Rotate_number_number_numberImpl,
            Matrix2DModifier::TranslateImpl,
            Matrix2DModifier::ScaleImpl,
        };
        return &Matrix2DAccessorImpl;
    }

}
