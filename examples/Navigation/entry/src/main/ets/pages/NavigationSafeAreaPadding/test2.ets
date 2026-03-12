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
import base from '@ohos.base';

@Entry
@Component
struct Test2 {
  private myWindow: window.Window | null = null;
  @State pageInfos: NavPathStack = new NavPathStack();
  @State barStyleValue: BarStyle[] = [ BarStyle.STANDARD, BarStyle.STACK, BarStyle.SAFE_AREA_PADDING]
  @State barStyleIndex: number = 0
  @State barStyleIndex2: number = 0
  @State barStyleIndex3: number = 0
  @State barStyleIndex4: number = 0
  @State barStyleIndex5: number = 0
  @State barStyleIndex6: number = 0
  @State barStyleStr: string[] = ['STANDARD', 'STACK', 'SAFE_AREA_PADDING']
  @State barStyleStr1: string[] = ['STANDARD', 'STACK', 'SAFE_AREA_PADDING']
  @State barStyleStr2: string[] = ['STANDARD', 'STACK', 'SAFE_AREA_PADDING']
  @State toolBar: ToolbarItem[] = [{value:'toolItem1', icon: $r('app.media.startIcon')},{value:'toolItem2', icon: $r('app.media.startIcon')}]
  @State toolBar2: ToolbarItem[] = [{value:'toolItem1', icon: $r('app.media.cat')},{value:'toolItem2', icon: $r('app.media.cat')}]
  @State toolBar3: ToolbarItem[] = [{value:'toolItem1', icon: $r('app.media.ic_public_highlightsed')},{value:'toolItem2', icon: $r('app.media.ic_public_highlightsed')}]

  @State hideTitleBarValue: boolean = false
  @State hideToolBarValue: boolean = false

  @State hideTitleBarValue2: boolean = false
  @State hideToolBarValue2: boolean = false

  @State titleModeValue: NavigationTitleMode[] = [NavigationTitleMode.Free, NavigationTitleMode.Mini, NavigationTitleMode.Full]
  @State titleModeValueIndex: number = 0
  @State titleModeValueStr: string[] = ['NavigationTitleMode.Free', 'NavigationTitleMode.Mini', 'NavigationTitleMode.Full']

  @State modeValue: NavigationMode[] = [ NavigationMode.Stack,  NavigationMode.Split,  NavigationMode.Auto]
  @State modeValueIndex: number = 0
  @State modeValueStr: string[] = ['NavigationMode.Stack', 'NavigationMode.Split', 'NavigationMode.Auto']

  @State navBarPositionValue:NavBarPosition[] = [NavBarPosition.Start, NavBarPosition.End]
  @State navBarPositionValueStr:string[] = ['NavBarPosition.Start', 'NavBarPosition.End']
  @State navBarPositionValueIndex:number = 0

  @State edge: LayoutSafeAreaEdge[][] = [[LayoutSafeAreaEdge.TOP, LayoutSafeAreaEdge.BOTTOM],[LayoutSafeAreaEdge.TOP,],[LayoutSafeAreaEdge.BOTTOM],[]];
  @State edgeIndex:number = 0
  @State edgeIndex2:number = 0
  @State edgeStr: string[] = ['[TOP,BOTTOM]','[TOP]','[BOTTOM]','[]'];


  @State paddingValue: (Length | Padding | LocalizedPadding)[] = [0, 10, 30]
  @State paddingValueIndex: number = 0
  @State paddingValueIndex2: number = 0

  @State heightValue: Length[] = ['100%', '90%']
  @State heightValueIndex: number = 0
  @State heightValueStr: string[] = ['全屏', '非全屏']

  createWindow() {
    try {
      window.createWindow({name: "testWindow", windowType: window.WindowType.TYPE_DIALOG, ctx: getContext(this)})
        .then((windowObj: window.Window) => {
          console.log(`testTag success to createWindow`)
          this.myWindow = windowObj;
          this.myWindow.showWindow().then(() => {
            console.log(`testTag success to showWindow`)
            this.myWindow?.resize(1000, 2200);
            this.myWindow?.moveWindowTo(50, 200);
            let ls = new LocalStorage();
            this.myWindow?.loadContent('pages/NavigationSafeAreaPadding/test2', ls)
              .then(() => {
                console.log(`testTag success to loadContent`)
              }).catch((e: base.BusinessError) => {
              console.log(`testTag failed to loadContent: ${JSON.stringify(e)}`)
            })
          }).catch((e: base.BusinessError) => {
            console.log(`testTag failed to showWindow: ${JSON.stringify(e)}`)
          });
        }).catch((e: base.BusinessError) => {
        console.log(`testTag failed to createWindow: ${JSON.stringify(e)}`)
      })
    } catch (e) {
      console.log(`testTag catch exception: ${JSON.stringify(e)}`)
    }
  }

  @Builder
  pageOneTmp() {
    NavDestination() {
      Column({ space: 10 }) {
        Button('占位6')
        Button('占位1')
        Button('占位5')
        Button('占位6')
        Button('NavgationTitleOptions barStyle:' + this.barStyleStr[this.barStyleIndex5])
          .key('NavigationTitleOptions')
          .onClick(() => {
            this.barStyleIndex5++
            if (this.barStyleIndex5 > this.barStyleValue.length - 1) {
              this.barStyleIndex5 = 0
            }
          })

        Button('NavigationToolbarOptions barStyle:' + this.barStyleStr[this.barStyleIndex6])
          .key('NavigationToolbarOptions')
          .onClick(() => {
            this.barStyleIndex6++
            if (this.barStyleIndex6 > this.barStyleValue.length - 1) {
              this.barStyleIndex6 = 0
            }
          })
        Button('占位1')
        Button('占位2')
        Button('占位3')
      }
    }
    .title({main:'NavDestinationCommonTitle', sub:'subTitle'}, {backgroundColor: '#80004AAF', backgroundBlurStyle:BlurStyle.BACKGROUND_THIN,barStyle:this.barStyleValue[this.barStyleIndex5]})
    .toolbarConfiguration(this.toolBar3, {backgroundColor:'#80004AAF', backgroundBlurStyle:BlurStyle.BACKGROUND_THIN, barStyle:this.barStyleValue[this.barStyleIndex6]})
    .mode(NavDestinationMode.DIALOG)
  }


  @Builder
  pageTwoTmp() {
    NavDestination() {
      Scroll() {
        Column({ space: 5 }) {
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
          Button('开启子窗口')
            .onClick(() => {
              this.createWindow();
            })

          Button('NavigationTitleOptions barStyle:' + this.barStyleStr[this.barStyleIndex3])
            .key('NavigationTitleOptions')
            .onClick(() => {
              this.barStyleIndex3++
              if (this.barStyleIndex3 > this.barStyleValue.length - 1) {
                this.barStyleIndex3 = 0
              }
            })

          Button('NavigationToolbarOptions barStyle:' + this.barStyleStr[this.barStyleIndex4])
            .key('NavigationToolbarOptions')
            .onClick(() => {
              this.barStyleIndex4++
              if (this.barStyleIndex4 > this.barStyleValue.length - 1) {
                this.barStyleIndex4 = 0
              }
            })

          Button('hideTitleBar:' + this.hideTitleBarValue2)
            .onClick(() => {
              this.hideTitleBarValue2 = !this.hideTitleBarValue2
            })

          Button('hideToolBar:' + this.hideToolBarValue2)
            .onClick(() => {
              this.hideToolBarValue2 = !this.hideToolBarValue2
            })

          Button('ignoreLayoutSafeArea edges:' + this.edgeStr[this.edgeIndex2])
            .onClick(() => {
              this.edgeIndex2++
              if (this.edgeIndex2 > this.edge.length - 1) {
                this.edgeIndex2 = 0
              }
            })

          Button('padding:' + this.paddingValue[this.paddingValueIndex2])
            .onClick(() => {
              this.paddingValueIndex2++
              if (this.paddingValueIndex2 > this.paddingValue.length - 1) {
                this.paddingValueIndex2 = 0
              }
            })

          Button('是否全屏:' + this.heightValueStr[this.heightValueIndex])
            .onClick(() => {
              this.heightValueIndex++
              if (this.heightValueIndex > this.heightValue.length - 1) {
                this.heightValueIndex = 0
              }
            })
          Button('获取栈信息')
            .onClick(() => {
              console.log('获取栈信息'+this.pageInfos.getAllPathName())
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
    .ignoreLayoutSafeArea([LayoutSafeAreaType.SYSTEM], this.edge[this.edgeIndex2])
    .padding(this.paddingValue[this.paddingValueIndex2])
    .hideTitleBar(this.hideTitleBarValue2)
    .hideToolBar(this.hideToolBarValue2)
    .title({main:'NavDestinationCommonTitle', sub:'subTitle'},
      {backgroundColor: '#80004AAF', backgroundBlurStyle:BlurStyle.BACKGROUND_THIN, barStyle:this.barStyleValue[this.barStyleIndex3]})
    .toolbarConfiguration(this.toolBar2,
      {backgroundColor: '#80004AAF', backgroundBlurStyle:BlurStyle.BACKGROUND_THIN,barStyle:this.barStyleValue[this.barStyleIndex4]})
  }


  @Builder
  PageMap(name: string) {
    if (name === 'pageOne') {
      this.pageOneTmp()
    } else if (name === 'pageTwo') {
      this.pageTwoTmp()
    }
  }


  build() {
    Navigation(this.pageInfos) {
      Scroll(){
        Column({space:5}){
          Scroll(){
            Column(){
              Button('占位1')
              Button('占位2')
              Button('占位')
              Button('占位')
              Row() {
                Button('开启子窗口')
                  .onClick(() => {
                    this.createWindow();
                  })
                Button('全屏')
                  .onClick(() => {
                    this.heightValueIndex = 0
                  })
                Button('非全屏' )
                  .onClick(() => {
                    this.heightValueIndex = 1
                  })
              }

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

              Row() {
                Button('hideTitleBar:true')
                  .onClick(()=>{
                    this.hideTitleBarValue = true
                  })

                Button('hideToolBar:true')
                  .key('hideToolBar')
                  .onClick(()=>{
                    this.hideToolBarValue = true
                  })
              }

              Button('titleMode:' + this.titleModeValueStr[this.titleModeValueIndex] )
                .key('titleMode')
                .onClick(()=>{
                  this.titleModeValueIndex ++
                  if(this.titleModeValueIndex > this.titleModeValue.length -1 ){
                    this.titleModeValueIndex = 0
                  }
                })

              Button('mode:' + this.modeValueStr[this.modeValueIndex] )
                .key('mode')
                .onClick(()=>{
                  this.modeValueIndex ++
                  if(this.modeValueIndex > this.modeValue.length -1 ){
                    this.modeValueIndex = 0
                  }
                })

              Button('navBarPosition:start')
                .onClick(() => {
                  this.navBarPositionValueIndex = 0
                })
              Button('navBarPosition:end')
                .onClick(() => {
                  this.navBarPositionValueIndex = 1
                })
              Row() {
                Button('padding:0')
                  .onClick(() => {
                    this.paddingValueIndex = 0
                  })
                Button('padding:10')
                  .onClick(() => {
                    this.paddingValueIndex = 1
                  })
                Button('padding:30')
                  .onClick(() => {
                    this.paddingValueIndex = 2
                  })
              }

              Button('ignoreLayoutSafeArea edges:' + this.edgeStr[this.edgeIndex])
                .key('ignoreLayoutSafeArea')
                .onClick(() => {
                  this.edgeIndex++
                  if (this.edgeIndex > this.edge.length - 1) {
                    this.edgeIndex = 0
                  }
                })



              Button('push pageTwo')
                .onClick(()=>{
                  this.pageInfos.pushPath({name:'pageTwo',param:'mes'})
                })

              Button('push pageDialog')
                .onClick(()=>{
                  this.pageInfos.pushPath({name:'pageOne',param:'mes'})
                })

              Button('获取栈信息')
                .onClick(() => {
                  console.log('获取栈信息'+this.pageInfos.getAllPathName())
                })
              Button('占位1')
              Button('占位1')
              Button('占位1')
              Button('占位1')
              Button('占位1')
              Button('占位1')
              Button('占位1')
            }
          }
          .scrollBar(BarState.Off)
        }.width('100%').height('100%')
      }.height('100%')
    }
    .hideTitleBar(this.hideTitleBarValue)
    .hideToolBar(this.hideToolBarValue)
    .titleMode(this.titleModeValue[this.titleModeValueIndex])
    .mode(this.modeValue[this.modeValueIndex])
    .navBarPosition(this.navBarPositionValue[this.navBarPositionValueIndex])
    .ignoreLayoutSafeArea([LayoutSafeAreaType.SYSTEM], this.edge[this.edgeIndex])
    .title({main:'NavigationCommonTitle', sub:'subTitle'}, {backgroundColor: '#00000000', backgroundBlurStyle:BlurStyle.BACKGROUND_THIN,barStyle:this.barStyleValue[this.barStyleIndex]})
    .toolbarConfiguration(this.toolBar, {backgroundColor: '#80004AAF', backgroundBlurStyle:BlurStyle.BACKGROUND_THIN,barStyle:this.barStyleValue[this.barStyleIndex2]})
    .padding(this.paddingValue[this.paddingValueIndex])
    .height(this.heightValue[this.heightValueIndex]).backgroundColor(Color.Pink).navDestination(this.PageMap)
  }
}