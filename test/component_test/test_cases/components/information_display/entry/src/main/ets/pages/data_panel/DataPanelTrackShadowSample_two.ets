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
import dataPanelTrackShadowTest_two from '../MyTest/DataPanelTrackShadowTest_two'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct DataPanelTrackShadowSample_two {
  public values: number[] = [20, 20, 20, 20]
  @State ResourceColorString1: ResourceColor = '#FF00FF00'
  @State ResourceColorString2: ResourceColor = '#20e38c8c'
  @State ResourceColorString3: ResourceColor = '#201660e0'
  @State ResourceColorString4: ResourceColor = '#201bf5df'
  public ResourceColorColor1: ResourceColor = Color.White
  public ResourceColorColor2: ResourceColor = Color.Blue
  public ResourceColorColor3: ResourceColor = Color.Yellow
  public ResourceColorColor4: ResourceColor = Color.Brown
  public ResourceColorNumber1: ResourceColor = 0xffffff
  public ResourceColorNumber2: ResourceColor = 0xFFA500
  public ResourceColorNumber3: ResourceColor = 0xFFFF00
  public ResourceColorNumber4: ResourceColor = 0x00FF00
  @State ResourceColorColor: Array<ResourceColor> = [this.ResourceColorColor1,
    this.ResourceColorColor2, this.ResourceColorColor3, this.ResourceColorColor4]
  @State ResourceColorNumber: Array<ResourceColor> = [this.ResourceColorNumber1,
    this.ResourceColorNumber2, this.ResourceColorNumber3, this.ResourceColorNumber4]
  @State ResourceColorString: Array<ResourceColor> = [this.ResourceColorString1,
    this.ResourceColorString2, this.ResourceColorString3, this.ResourceColorString4]
  @State ResourceColorResource: Array<ResourceColor> = [$r('app.color.data_panel_resource_color8'),
    $r('app.color.data_panel_resource_color3'),
    $r('app.color.data_panel_resource_color5')]
  @State trackShadowStatus: DataPanelShadowOptions | null = {
    radius: 50,
    colors: this.ResourceColorColor,
    offsetX: $r("app.string.data_panel_number"),
    offsetY: $r("app.string.data_panel_number")
  }

  aboutToAppear(): void {
    loadComponentTestEntry(dataPanelTrackShadowTest_two)
  }

  build() {
    Column({ space: 5 }) {
      Row() {
        Stack() {
          Column() {
            DataPanel({ values: this.values, max: 100, type: DataPanelType.Circle })
              .width(150)
              .height(150)
              .trackShadow(this.trackShadowStatus)
              .id('dataPanelTrackShadow1')
            DataPanel({ values: this.values, max: 100, type: DataPanelType.Circle })
              .width(150)
              .height(150)
              .trackShadow({
                radius: $r("app.string.data_panel_number"),
                colors: this.ResourceColorString,
                offsetX: 100,
                offsetY: 100
              })
              .id('dataPanelTrackShadow2')
            Button('DataPanelTrackShadow1')
              .onClick(() => {
                this.trackShadowStatus = {
                  radius: 50,
                  colors: this.ResourceColorNumber,
                  offsetX: $r("app.string.data_panel_number"),
                  offsetY: $r("app.string.data_panel_number")
                }
              })
            Button('DataPanelTrackShadow2')
              .onClick(() => {
                this.trackShadowStatus = {
                  radius: 50,
                  colors: this.ResourceColorResource,
                  offsetX: $r("app.string.data_panel_number"),
                  offsetY: $r("app.string.data_panel_number")
                }
              })
            Button('DataPanelTrackShadow3')
              .onClick(() => {
                this.trackShadowStatus = null
              })
          }
        }
      }
    }
  }
}