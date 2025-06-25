/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { LengthMetrics} from '@kit.ArkUI';

@Entry
@Component
struct TimePickerExample013 {
  build() {
    Column() {
        /*
         * expected : The size of the TimePicker component is set to the size of the parent component without
         * safeAreaPadding.
         */
        TimePicker()
        .width(LayoutPolicy.matchParent)
        .height(LayoutPolicy.matchParent)
        .backgroundColor('#FF8FC66C')
    }
    .width('100%')
    .height('100%')
    .safeAreaPadding(LengthMetrics.px(50))
  }
}
