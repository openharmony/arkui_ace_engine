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
struct NavigationSafeAreaPaddingTest1 {
  @State pageInfos: NavPathStack = new NavPathStack();
  @State barStyleValue: BarStyle[] = [ BarStyle.STANDARD, BarStyle.STACK, BarStyle.SAFE_AREA_PADDING]
  @State barStyleIndex: number = 0
  @State barStyleIndex2: number = 0
  @State barStyleIndex3: number = 0
  @State barStyleIndex4: number = 0
  @State barStyleStr: string[] = ['STANDARD', 'STACK', 'SAFE_AREA_PADDING']

  @Builder
  TiTle() {
    Column(){
      Text('CustomBuilderTitle')
    }
  }

  @Builder
  TiTlePageOne() {
    Column(){
      Text('PageOne_CustomBuilderTitle')
    }
  }

  @Builder
  ToolBar() {
    Row({space:5}){
      Image($r('app.media.startIcon')).width('30vp').height('30vp')
      Image($r('app.media.startIcon')).width('30vp').height('30vp')
    }
  }

  @Builder
  ToolBarPageOne() {
    Row({space:5}){
      Image($r('app.media.cat')).width('30vp').height('30vp')
      Image($r('app.media.cat')).width('30vp').height('30vp')
    }
  }



  @Builder
  pageOneTmp() {
    NavDestination() {
      Column({ space: 5 }) {
        Scroll(){
          Column(){
            Button('占位1')
            Button('占位2')
            Button('占位3')
            Button('占位4')
            Button('占位5')
            Button('占位6')
            Button('占位1')
            Button('占位2')
            Button('占位3')
            Button('占位4')
            Button('占位5')
            Button('占位6')
            Button('NavigationTitleOptions barStyle:' + this.barStyleStr[this.barStyleIndex3])
              .onClick(() => {
                this.barStyleIndex3++
                if (this.barStyleIndex3 > this.barStyleValue.length - 1) {
                  this.barStyleIndex3 = 0
                }
              })

            Button('NavigationToolbarOptions barStyle:' + this.barStyleStr[this.barStyleIndex4])
              .onClick(() => {
                this.barStyleIndex4++
                if (this.barStyleIndex4 > this.barStyleValue.length - 1) {
                  this.barStyleIndex4 = 0
                }
              })

            Button('占位1')
            Button('占位2')
            Button('占位3')
            Button('占位4')
            Button('占位5')
            Button('占位6')
            Button('占位1')
            Button('占位2')
            Button('占位3')
            Button('占位4')
            Button('占位5')
            Button('占位6')
          }
        }
      }
    }
    .title(this.TiTlePageOne, {backgroundColor: '#80004AAF', backgroundBlurStyle:BlurStyle.BACKGROUND_THIN, barStyle:this.barStyleValue[this.barStyleIndex3]})
    .toolbarConfiguration(this.ToolBarPageOne, {backgroundColor: '#80004AAF', backgroundBlurStyle:BlurStyle.BACKGROUND_THIN, barStyle:this.barStyleValue[this.barStyleIndex4]})
  }

  @Builder
  PageMap(name: string) {
    if (name === 'pageOne') {
      this.pageOneTmp()
    }
  }



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
              Button('6')
              Button('1')
              Button('NavigationTitleOptions barStyle:' + this.barStyleStr[this.barStyleIndex])
                .key('NavigationTitleOptions')
                .onClick(() => {
                  this.barStyleIndex++
                  if (this.barStyleIndex > this.barStyleValue.length - 1) {
                    this.barStyleIndex = 0
                  }
                })

              Button('NavigationToolbarOptions barStyle:' + this.barStyleStr[this.barStyleIndex2])
                .key('NavigationToolbarOptions')
                .onClick(() => {
                  this.barStyleIndex2++
                  if (this.barStyleIndex2 > this.barStyleValue.length - 1) {
                    this.barStyleIndex2 = 0
                  }
                })

              Button('push pageOne')
                .onClick(()=>{
                  this.pageInfos.pushPath({name:'pageOne',param:'mes'})
                })
              Button('2')
              Button('3')
              Button('4')
              Button('5')
              Button('6')
              Button('1')
              Button('2')
              Button('3')
              Button('4')
              Button('5')
              Button('6')
              Button('1')
              Button('2')
              Button('3')
              Button('4')
              Button('5')
              Button('6')
            }
          }
          .scrollBar(BarState.Off)
        }.width('100%').height('100%')
      }.height('100%')
    }
    .title(this.TiTle, {backgroundColor: "#80004AAF", backgroundBlurStyle:BlurStyle.BACKGROUND_THIN, barStyle:this.barStyleValue[this.barStyleIndex]})
    .toolbarConfiguration(this.ToolBar, {backgroundColor: '#80004AAF', backgroundBlurStyle:BlurStyle.BACKGROUND_THIN,barStyle:this.barStyleValue[this.barStyleIndex2]})
    .navDestination(this.PageMap)
  }
}