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
import actionSheetMaskRectTest from '../MyTest/ActionSheetMaskRectTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ActionSheetMaskRectSample {
  @State maskRect_x: string | Resource = '5px'
  @State maskRect_y: string | Resource = '6px'
  @State maskRect_width: string | Resource = '400px'
  @State maskRect_height: string | Resource = '500px'
  @State string: string = 'actionText'

  aboutToAppear(): void {
    loadComponentTestEntry(actionSheetMaskRectTest)
  }

  build() {
    Column() {
      Text(this.string)
      Button('ActionSheetMaskRectTest1')
        .onClick(() => {
          ActionSheet.show({
            title: 'title1',
            message: 'message1',
            maskRect: {
              x: 1,
              y: 2,
              width: 200,
              height: 300
            },
            sheets: [{
              title: 'sheetsTitle1', action: () => {
                this.string = 'actionText1'
              }
            },]
          })
        })
      Button('ActionSheetMaskRectTest2')
        .onClick(() => {
          ActionSheet.show({
            title: 'title2',
            message: 'message2',
            maskRect: {
              x: this.maskRect_x,
              y: this.maskRect_y,
              width: this.maskRect_width,
              height: this.maskRect_height
            },
            sheets: [{
              title: 'sheetsTitle2', action: () => {
                this.string = 'actionText2'
              }
            },]
          })
        })
      Button('ActionSheetMaskRectTest3')
        .onClick(() => {
          ActionSheet.show({
            title: 'title3',
            message: 'message3',
            showInSubWindow: true,
            maskRect: {
              x: 1,
              y: 2,
              width: 200,
              height: 300
            },
            sheets: [{
              title: 'sheetsTitle3', action: () => {
                this.string = 'actionText3'
              }
            },]
          })
        })
      Button('ActionSheetMaskRect1').onClick(() => {
        this.maskRect_x = $r('app.float.actionSheet_maskRect_dx')
        this.maskRect_y = $r('app.float.actionSheet_maskRect_dy')
        this.maskRect_width = $r('app.integer.actionSheet_maskRect_width')
        this.maskRect_height = $r('app.integer.actionSheet_maskRect_height')
      })
    }
  }
}