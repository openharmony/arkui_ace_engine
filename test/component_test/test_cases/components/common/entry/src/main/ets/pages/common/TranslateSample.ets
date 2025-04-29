/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

import translateTest from '../MyTest/TranslateTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct TranslateSample {
  @State translateOptions: number | string = 50

  aboutToAppear(): void {
    loadComponentTestEntry(translateTest)
  }

  build() {
    Column() {

      Radio({ value: 'Radio1', group: 'radioGroup' })
        .height(50)
        .width(50)
        .id('radio1')
        .translate({ x: this.translateOptions, y: this.translateOptions, z: this.translateOptions })

      Button('ButtonTranslate')
        .onClick((event: ClickEvent) => {
          this.translateOptions = '80%'
        })
    }
  }
}