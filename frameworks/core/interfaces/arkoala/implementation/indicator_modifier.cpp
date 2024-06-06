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
  Ark_NativePointer Indicator_ctor() {
    return 0;
  }
  Ark_NativePointer Indicator_getFinalizer() {
    return 0;
  }
  void Indicator_left(IndicatorPeer* peer, const Ark_Length* value) {
  }
  void Indicator_top(IndicatorPeer* peer, const Ark_Length* value) {
  }
  void Indicator_right(IndicatorPeer* peer, const Ark_Length* value) {
  }
  void Indicator_bottom(IndicatorPeer* peer, const Ark_Length* value) {
  }
  Ark_NativePointer Indicator_dot() {
    return 0;
  }
  Ark_NativePointer Indicator_digit() {
    return 0;
  }
  GENERATED_ArkUIIndicatorAccessor IndicatorAccessorImpl {
    Indicator_ctor,
    Indicator_getFinalizer,
    Indicator_left,
    Indicator_top,
    Indicator_right,
    Indicator_bottom,
    Indicator_dot,
    Indicator_digit,
  };

  const GENERATED_ArkUIIndicatorAccessor* GetIndicatorAccessor() { return &IndicatorAccessorImpl; }


}
