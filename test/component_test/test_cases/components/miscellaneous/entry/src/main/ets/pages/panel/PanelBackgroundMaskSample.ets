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
//测试代码路径
import panelBackgroundMaskTest from '../MyTest/PanelBackgroundMaskTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct PanelBackgroundMaskSample {
  @State panelBackgroundMask: ResourceColor = Color.Blue

  aboutToAppear(): void {
    loadComponentTestEntry(panelBackgroundMaskTest)
  }

  build() {
    Column() {
      Panel(true) {
      }.backgroundMask(this.panelBackgroundMask).width(120).height(120)
      .id('panelBackgroundMask1')

      Panel(true) {
      }.backgroundMask(0xff8000).width(120).height(120)
      .id('panelBackgroundMask2')

      Button('PanelBackgroundMask1')
        .onClick(() => {
          this.panelBackgroundMask = 'rgb(255, 100, 255)'
        })
      Button('PanelBackgroundMask2')
        .onClick(() => {
          this.panelBackgroundMask = $r('sys.color.ohos_id_color_text_hyperlink')
        })
    }
  }
}