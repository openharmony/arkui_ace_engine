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
import toggleSwitchPointColorTest from '../MyTest/ToggleSwitchPointColorTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ToggleSwitchPointColorSample {
  @State pointColor: ResourceColor = 'rgb(142, 255, 101)'

  aboutToAppear(): void {
    loadComponentTestEntry(toggleSwitchPointColorTest)
  }

  build() {
    Column() {
      Toggle({ type: ToggleType.Switch, isOn: false }).switchPointColor(Color.Black).id('toggleSwitchPointColor1')
      Toggle({ type: ToggleType.Switch, isOn: false }).switchPointColor(0xa52a2a).id('toggleSwitchPointColor2')
      Toggle({ type: ToggleType.Switch, isOn: false }).switchPointColor(this.pointColor).id('toggleSwitchPointColor3')

      Button('ToggleSwitchPointColor').onClick(() => {
        this.pointColor = $r('sys.color.ohos_fa_palette1')
      })
    }
  }
}