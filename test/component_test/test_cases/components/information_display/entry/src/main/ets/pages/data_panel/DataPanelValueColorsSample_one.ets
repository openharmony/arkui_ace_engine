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
import dataPanelValueColorsTest_one from '../MyTest/DataPanelValueColorsTest_one'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct DataPanelValueColorsSample_one {
  public values: number[] = [25, 25, 25, 25]
  public LinearGradientString1: LinearGradient =
    new LinearGradient([{ color: "#65EEC9A3", offset: $r('app.float.data_panel_offset_min') },
      { color: "#FFEF629F", offset: $r('app.float.data_panel_offset_max') }])
  public LinearGradientString2: LinearGradient =
    new LinearGradient([{ color: "#FF67F9D4", offset: $r('app.float.data_panel_offset_min') },
      { color: "#FFFF9554", offset: $r('app.float.data_panel_offset_max') }])
  public LinearGradientString3: LinearGradient =
    new LinearGradient([{ color: "#6572B513", offset: $r('app.float.data_panel_offset_min') },
      { color: "#6508efa6", offset: $r('app.float.data_panel_offset_max') }])
  public LinearGradientString4: LinearGradient =
    new LinearGradient([{ color: "#65ed08f5", offset: $r('app.float.data_panel_offset_min') },
      { color: "#65ef0849", offset: $r('app.float.data_panel_offset_max') }])
  public LinearGradientColor1: LinearGradient = new LinearGradient([{ color: Color.Gray, offset: '0%' },
    { color: Color.Blue, offset: '100%' }])
  public LinearGradientColor2: LinearGradient = new LinearGradient([{ color: Color.Green, offset: '0%' },
    { color: Color.Orange, offset: '100%' }])
  public LinearGradientColor3: LinearGradient = new LinearGradient([{ color: Color.Pink, offset: '0%' },
    { color: Color.Yellow, offset: '100%' }])
  public LinearGradientColor4: LinearGradient = new LinearGradient([{ color: Color.Red, offset: '0%' },
    { color: Color.Brown, offset: '100%' }])
  public LinearGradientNumber1: LinearGradient = new LinearGradient([{ color: 0x317AF7, offset: 0 },
    { color: 0x5BA854, offset: 1 }])
  public LinearGradientNumber2: LinearGradient = new LinearGradient([{ color: 0xE08C3A, offset: 0 },
    { color: 0xFFA500, offset: 1 }])
  public LinearGradientNumber3: LinearGradient = new LinearGradient([{ color: 0xFFFF00, offset: 0 },
    { color: 0x008000, offset: 1 }])
  public LinearGradientNumber4: LinearGradient = new LinearGradient([{ color: 0xFFA500, offset: 0 },
    { color: 0xFFFF00, offset: 1 }])
  public LinearGradientResource1: LinearGradient =
    new LinearGradient([{ color: $r('app.color.data_panel_resource_color2'), offset: 0 },
      { color: $r('app.color.data_panel_resource_color8'), offset: 1 }])
  public LinearGradientResource2: LinearGradient =
    new LinearGradient([{ color: $r('app.color.data_panel_resource_color1'), offset: 0 },
      { color: $r('app.color.data_panel_resource_color5'), offset: 1 }])
  public LinearGradientResource3: LinearGradient =
    new LinearGradient([{ color: $r('app.color.data_panel_resource_color4'), offset: 0 },
      { color: $r('app.color.data_panel_resource_color6'), offset: 1 }])
  public LinearGradientResource4: LinearGradient =
    new LinearGradient([{ color: $r('app.color.data_panel_resource_color7'), offset: 0 },
      { color: $r('app.color.data_panel_resource_color3'), offset: 1 }])
  @State LinearGradientString: Array<LinearGradient> = [this.LinearGradientString1,
    this.LinearGradientString2, this.LinearGradientString3, this.LinearGradientString4]
  @State LinearGradientColor: Array<LinearGradient> = [this.LinearGradientColor1,
    this.LinearGradientColor2, this.LinearGradientColor3, this.LinearGradientColor4]
  @State LinearGradientNumber: Array<LinearGradient> = [this.LinearGradientNumber1,
    this.LinearGradientNumber2, this.LinearGradientNumber3, this.LinearGradientNumber4]
  @State LinearGradientResource: Array<LinearGradient> = [this.LinearGradientResource1,
    this.LinearGradientResource2, this.LinearGradientResource3, this.LinearGradientResource4]
  @State valueColors: Array<ResourceColor | LinearGradient> = this.LinearGradientColor

  aboutToAppear(): void {
    loadComponentTestEntry(dataPanelValueColorsTest_one)
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
        .valueColors(this.LinearGradientString)
        .id('dataPanelValueColors2')
      Button('DataPanelValueColors1')
        .onClick(() => {
          this.valueColors = this.LinearGradientNumber
        })
      Button('DataPanelValueColors2')
        .onClick(() => {
          this.valueColors = this.LinearGradientResource
        })
    }
  }
}