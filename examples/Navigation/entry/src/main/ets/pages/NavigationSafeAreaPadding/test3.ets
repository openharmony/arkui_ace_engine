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
struct Test31 {
  @State pageInfos: NavPathStack = new NavPathStack();
  @State barStyleValue: BarStyle[] = [ BarStyle.STANDARD, BarStyle.STACK, BarStyle.SAFE_AREA_PADDING]
  @State barStyleIndex: number = 0
  @State barStyleIndex2: number = 0
  @State barStyleStr: string[] = ['STANDARD', 'STACK', 'SAFE_AREA_PADDING']
  @State toolBar: ToolbarItem[] = [{value:'toolItem1', icon: $r('app.media.startIcon')},{value:'toolItem2', icon: $r('app.media.startIcon')}]

  build() {
    Navigation(this.pageInfos) {
      Scroll(){
        Column({space:5}){
          Scroll(){
            Column(){
              Button('NavigationToolbarOptions barStyle:' + this.barStyleStr[this.barStyleIndex2])
                .key('NavigationToolbarOptions')
                .onClick(() => {
                  this.barStyleIndex2++
                  if (this.barStyleIndex2 > this.barStyleValue.length - 1) {
                    this.barStyleIndex2 = 0
                  }
                })
              Button('1')
              Button('2')
              Button('3')
              Button('4')
              Button('5')
              Button('6')
              Button('7')
              Button('8')
              Button('9')
              Button('10')
              Button('11')
              Button('12')
              Button('13')
              Button('14')
              Button('15')
              Button('16')
              Button('17')
              Button('18')
              Button('19')
              Button('20')
              Button('21')
              Button('22')
              Button('23')
            }
          }
          .scrollBar(BarState.Off)
        }.width('100%').height('100%')
      }.height('100%')
    }
    .toolbarConfiguration(this.toolBar, {backgroundColor: '#80004AAF', backgroundBlurStyle:BlurStyle.BACKGROUND_THIN,barStyle:this.barStyleValue[this.barStyleIndex2]})
  }
}