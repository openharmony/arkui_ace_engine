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

@Entry
@Component
struct Test71 {
  @State pageInfos: NavPathStack = new NavPathStack();
  @State pageInfos2: NavPathStack = new NavPathStack();
  @State barStyleValue: BarStyle[] = [ BarStyle.STANDARD, BarStyle.STACK, BarStyle.SAFE_AREA_PADDING]
  @State barStyleIndex: number = 0
  @State barStyleIndex2: number = 0
  @State barStyleIndex3: number = 0
  @State barStyleIndex4: number = 0
  @State barStyleStr: string[] = ['STANDARD', 'STACK', 'SAFE_AREA_PADDING']
  @State toolBar: ToolbarItem[] = [{value:'toolItem1', icon: $r('app.media.startIcon')},{value:'toolItem2', icon: $r('app.media.startIcon')}]

  build() {
    Navigation(this.pageInfos) {
      Column({space:5}){
        Scroll(){
          Column(){
            Button('1')
            Button('2')
            Button('3').margin({bottom: 10})
            Button('父 NavigationTitleOptions barStyle:' + this.barStyleStr[this.barStyleIndex])
              .onClick(() => {
                this.barStyleIndex++
                if (this.barStyleIndex > this.barStyleValue.length - 1) {
                  this.barStyleIndex = 0
                }
              })

            Button('父 NavigationToolbarOptions barStyle:' + this.barStyleStr[this.barStyleIndex2])
              .onClick(() => {
                this.barStyleIndex2++
                if (this.barStyleIndex2 > this.barStyleValue.length - 1) {
                  this.barStyleIndex2 = 0
                }
              })

            Navigation(this.pageInfos2) {
              Scroll(){
                Column({space:5}){
                  Scroll(){
                    Column(){
                      Button('1')
                      Button('2')
                      Button('3').margin({bottom: 10})
                      Button('子 NavigationTitleOptions barStyle:' + this.barStyleStr[this.barStyleIndex3])
                        .onClick(() => {
                          this.barStyleIndex3++
                          if (this.barStyleIndex3 > this.barStyleValue.length - 1) {
                            this.barStyleIndex3 = 0
                          }
                        })
                      Button('子 NavigationToolbarOptions barStyle:' + this.barStyleStr[this.barStyleIndex4])
                        .onClick(() => {
                          this.barStyleIndex4++
                          if (this.barStyleIndex4 > this.barStyleValue.length - 1) {
                            this.barStyleIndex4 = 0
                          }
                        })
                      Button('6')
                      Button('7')
                      Button('8')
                    }
                  }

                }.width('100%').height('100%')
              }.height('100%')
            }
            .title({main:'子NavigationCommonTitle', sub:'subTitle'}, {backgroundColor: '#80004AAF', backgroundBlurStyle:BlurStyle.BACKGROUND_THIN,barStyle:this.barStyleValue[this.barStyleIndex3]})
            .toolbarConfiguration(this.toolBar, {backgroundColor: '#80004AAF', backgroundBlurStyle:BlurStyle.BACKGROUND_THIN, barStyle:this.barStyleValue[this.barStyleIndex4]})
            .backgroundColor(Color.Pink)
          }
        }
        .scrollBar(BarState.Off)

      }.width('100%').height('100%')
    }
    .title({main:'父NavigationCommonTitle', sub:'subTitle'}, {backgroundColor: '#80004AAF', backgroundBlurStyle:BlurStyle.BACKGROUND_THIN,barStyle:this.barStyleValue[this.barStyleIndex]})
    .toolbarConfiguration(this.toolBar, {backgroundColor: '#80004AAF', backgroundBlurStyle:BlurStyle.BACKGROUND_THIN,barStyle:this.barStyleValue[this.barStyleIndex2]})
  }
}

