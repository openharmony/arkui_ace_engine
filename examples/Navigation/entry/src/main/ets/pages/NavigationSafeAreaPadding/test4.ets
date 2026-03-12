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
struct Test41 {
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
             Button('1')
             Button('2')
             Button('3')
             Button('4')
             Button('5')
             Button('NavigationTitleOptions barStyle:' + this.barStyleStr[this.barStyleIndex])
               .key('NavigationTitleOptions')
               .onClick(() => {
                 this.barStyleIndex++
                 if (this.barStyleIndex > this.barStyleValue.length - 1) {
                   this.barStyleIndex = 0
                 }
               })
           }
         }

        }.width('100%').height('100%')
      }.height('100%')
    }
    .title({main:'NavigationCommonTitle', sub:'subTitle'}, {backgroundColor: '#80004AAF', backgroundBlurStyle:BlurStyle.BACKGROUND_THIN,barStyle:this.barStyleValue[this.barStyleIndex]})
  }
}