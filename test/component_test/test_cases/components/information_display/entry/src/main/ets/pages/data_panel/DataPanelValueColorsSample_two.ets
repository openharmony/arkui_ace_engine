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
import dataPanelValueColorsTest_two from '../MyTest/DataPanelValueColorsTest_two'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct DataPanelValueColorsSample_two {
  public values: number[] = [25, 25, 25, 25]
  @State ResourceColorString1: ResourceColor = '#00FF00'
  @State ResourceColorString2: ResourceColor = '#20e38c8c'
  @State ResourceColorString3: ResourceColor = '#201660e0'
  @State ResourceColorString4: ResourceColor = '#201bf5df'
  public ResourceColorColor1: ResourceColor = Color.Green
  public ResourceColorColor2: ResourceColor = Color.Blue
  public ResourceColorColor3: ResourceColor = Color.Yellow
  public ResourceColorColor4: ResourceColor = Color.Brown
  public ResourceColorNumber1: ResourceColor = 0x0000FF
  public ResourceColorNumber2: ResourceColor = 0xFFA500
  public ResourceColorNumber3: ResourceColor = 0xFFFF00
  public ResourceColorNumber4: ResourceColor = 0x00FF00
  @State ResourceColorColor: Array<ResourceColor> = [this.ResourceColorColor1,
    this.ResourceColorColor2, this.ResourceColorColor3, this.ResourceColorColor4]
  @State ResourceColorNumber: Array<ResourceColor> = [this.ResourceColorNumber1,
    this.ResourceColorNumber2, this.ResourceColorNumber3, this.ResourceColorNumber4]
  @State ResourceColorString: Array<ResourceColor> = [this.ResourceColorString1,
    this.ResourceColorString2, this.ResourceColorString3, this.ResourceColorString4]
  @State ResourceColorResource: Array<ResourceColor> =
    [$r('app.color.data_panel_resource_color3'), $r('app.color.data_panel_resource_color5'),
      $r('app.color.data_panel_resource_color1'), $r('app.color.data_panel_resource_color6')]
  @State valueColors: Array<ResourceColor | LinearGradient> = this.ResourceColorColor

  aboutToAppear(): void {
    loadComponentTestEntry(dataPanelValueColorsTest_two)
  }

  build() {
    Column({ space: 5 }) {
      DataPanel({ values: this.values, max: 100, type: DataPanelType.Line })
        .width(300)
        .height(100)
        .valueColors(this.valueColors)
        .id('dataPanelValueColors1')
      DataPanel({ values: this.values, max: 100, type: DataPanelType.Line })
        .width(300)
        .height(100)
        .valueColors(this.ResourceColorNumber)
        .id('dataPanelValueColors2')
      Button('DataPanelValueColors1')
        .onClick(() => {
          this.valueColors = this.ResourceColorString
        })
      Button('DataPanelValueColors2')
        .onClick(() => {
          this.valueColors = this.ResourceColorResource
        })
    }
  }
}