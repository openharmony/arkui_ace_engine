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
struct CalendarPickerExample006 {
  build() {
    Column() {
        /*
         * expected : The matchParent priority is higher than constraintSize.
         * The CalendarPicker has the same width and height as the parent component.
         */
        CalendarPicker()
        .width(LayoutPolicy.matchParent)
        .height(LayoutPolicy.matchParent)
        .constraintSize({maxWidth: '500px', maxHeight: '500px'})
        .backgroundColor('#FF8FC66C')
    }
    .width('100%')
    .height('100%')
  }
}
