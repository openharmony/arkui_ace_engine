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

@Entry
@Component
struct DatePickerExample005 {
  build() {
    Column() {
        /*
         * expected : The aspectRatio priority is higher than matchParent.
         * The width is the same as the parent component, and the height is one third of the width.
         */
        DatePicker()
        .width(LayoutPolicy.matchParent)
        .aspectRatio(3)
        .backgroundColor('#FF8FC66C')
    }
    .width('100%')
    .height('100%')
  }
}
