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

// 测试代码路径
import radioRadioStyleTest from '../MyTest/RadioRadioStyleTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct RadioRadioStyleSample {
  @State radioStyleColor: ResourceColor = 'rgb(142, 255, 101)'
  @State radioColor: ResourceColor = 'rgb(10, 10, 25)'

  aboutToAppear(): void {
    loadComponentTestEntry(radioRadioStyleTest)
  }

  build() {
    Flex() {
      Radio({ value: 'Radio1', group: 'radioGroup' })
        .radioStyle({ checkedBackgroundColor: Color.Gray })
        .id('radioRadioStyle1')
      Radio({ value: 'Radio1', group: 'radioGroup' })
        .radioStyle({ uncheckedBorderColor: Color.Green })
        .id('radioRadioStyle2')
      Radio({ value: 'Radio1', group: 'radioGroup' }).radioStyle({ indicatorColor: Color.Pink }).id('radioRadioStyle3')
      Radio({ value: 'Radio2', group: 'radioGroup' })
        .radioStyle({ checkedBackgroundColor: 0xa52a2a })
        .id('radioRadioStyle4')
      Radio({ value: 'Radio2', group: 'radioGroup' })
        .radioStyle({ uncheckedBorderColor: 0xffa500 })
        .id('radioRadioStyle5')
      Radio({ value: 'Radio2', group: 'radioGroup' })
        .radioStyle({ indicatorColor: this.radioStyleColor })
        .id('radioRadioStyle6')
      Radio({ value: 'Radio3', group: 'radioGroup' }).radioStyle({
        checkedBackgroundColor: $r('sys.color.ohos_fa_palette1')
      }).id('radioRadioStyle7')
      Radio({ value: 'Radio3', group: 'radioGroup' }).radioStyle({
        uncheckedBorderColor: $r('sys.color.ohos_id_shadow_floating_md_dark')
      }).id('radioRadioStyle8')
      Radio({ value: 'Radio3', group: 'radioGroup' }).radioStyle({
        indicatorColor: $r('sys.color.ohos_id_shadow_floating_md')
      }).id('radioRadioStyle9')
      Radio({ value: 'Radio4', group: 'radioGroup' })
        .radioStyle({ checkedBackgroundColor: 'rgba(10, 110, 70, 1.00)' })
        .id('radioRadioStyle10')
      Radio({ value: 'Radio4', group: 'radioGroup' })
        .radioStyle({ uncheckedBorderColor: this.radioColor })
        .id('radioRadioStyle11')

      Button('RadioStyle').onClick(() => {
        this.radioStyleColor = $r('sys.color.ohos_fa_palette1')
        this.radioColor = $r('sys.color.ohos_id_color_badge_red_dark')
      })
    }.padding({ top: 30 })
  }
}