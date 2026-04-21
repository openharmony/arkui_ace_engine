/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
 
import window from '@ohos.window';
import { BusinessError } from '@ohos.base';
@Entry
@Component
struct SubTest {
  @State pageInfos: NavPathStack = new NavPathStack();
  private curWindow: window.Window | null = null;
  @State barStyleValue: BarStyle[] = [ BarStyle.STANDARD, BarStyle.STACK, BarStyle.SAFE_AREA_PADDING]
  @State barStyleIndex: number = 0
  @State barStyleIndex2: number = 0
  @State barStyleStr: string[] = ['STANDARD', 'STACK', 'SAFE_AREA_PADDING']
  @State toolBar: ToolbarItem[] = [{value:'toolItem1', icon: $r('app.media.startIcon')},{value:'toolItem2', icon: $r('app.media.startIcon')}]

  closeWindow() {
    console.log(`testTag prepare to close Window`)
    try {
      this.curWindow = window.findWindow('testWindow');
      if (!this.curWindow) {
        console.log(`testTag failed to findWindow`);
        return;
      }

      this.curWindow.destroyWindow().then(() => {
        console.log(`testTag success to destroy curWindow`);
      }).catch((err: BusinessError) => {
        console.log(`failed to destroy curWindow`)
      })
    } catch (e) {
      console.log(`testTag catch exception when find Window: ${JSON.stringify(e)}`)
    }
  }

  build() {
    Navigation(this.pageInfos) {
      Scroll(){
        Column({space:5}){
          Button('关闭子窗口')
            .onClick(() => {
              this.closeWindow();
            })

          Button('NavigationTitleOptions barStyle:' + this.barStyleStr[this.barStyleIndex])
            .onClick(() => {
              this.barStyleIndex++
              if (this.barStyleIndex > this.barStyleValue.length - 1) {
                this.barStyleIndex = 0
              }
            })

          Button('NavigationToolbarOptions barStyle:' + this.barStyleStr[this.barStyleIndex2])
            .onClick(() => {
              this.barStyleIndex2++
              if (this.barStyleIndex2 > this.barStyleValue.length - 1) {
                this.barStyleIndex2 = 0
              }
            })

        }.width('100%').height('100%')
      }.height('100%')
    }

    .title({main:'NavigationCommonTitle', sub:'subTitle'}, {backgroundColor:Color.Orange, barStyle:this.barStyleValue[this.barStyleIndex]})
    .toolbarConfiguration(this.toolBar, {backgroundColor:Color.Orange, barStyle:this.barStyleValue[this.barStyleIndex2]})
  }
}

