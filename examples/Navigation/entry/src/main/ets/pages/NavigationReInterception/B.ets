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
// PageOne.ets
import { JSON } from '@kit.ArkTS';

class TmpClass{
  count:number=10
}
@Entry
@Component
export struct BTmp {
  pageInfos: NavPathStack = new NavPathStack();
  @State isChange: boolean = false;
  @State text1: string = ''
  @State text2: string = ''
  build() {
    NavDestination() {
      Scroll(){
        Column() {
          Text('返回信息:' + this.text1)
          Button('B跳转到C，调用willshow，popToIndex到B页面`').margin(10).onClick(() => {
            this.pageInfos.pushPath({name:'C'})
            this.pageInfos.setInterception({
              willShow: (from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {
                this.pageInfos.popToIndex(0)
              }
            });
          })

          Button('B页面pushPathByName到C页面(携带onPop)，调用willshow，popToIndex到B页面`').margin(10).onClick(() => {
            this.pageInfos.pushPathByName('c',TmpClass,(popInfo:PopInfo) => {
              this.text1 = JSON.stringify(popInfo)
              console.info(popInfo.info.name)
            })
            this.pageInfos.setInterception({
              willShow: (from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {
                let result = TmpClass
                this.pageInfos.popToIndex(0,result)
              }
            });
          })

          Button('B页面push到C页面,调用willshow，moveToTop到B页面到栈顶，使用getAllPathName')
            .width('80%')
            .height(40)
            .margin(10)
            .onClick(() => {
              this.pageInfos.pushPath({name:'C'})
              this.pageInfos.setInterception({
                willShow: (from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {
                  this.pageInfos.moveToTop("B")
                  this.text2 = JSON.stringify(this.pageInfos.getAllPathName())
                }
              });
            })
          Button('B页面push到C页面,调用willshow，moveIndexToTop到B页面到栈顶，使用getAllPathName')
            .width('80%')
            .height(40)
            .margin(10)
            .onClick(() => {
              this.pageInfos.pushPath({name:'C'})
              this.pageInfos.setInterception({
                willShow: (from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {
                  this.pageInfos.moveIndexToTop(0)
                  this.text2 = JSON.stringify(this.pageInfos.getAllPathName())
                }
              });
            })
          Text('获取栈中所有NavDestination页面的名称:' + this.text2)

        }.width('100%').height('100%')
      }.height(300)

    }.title('B页面')
    .onAppear(() => {
      console.log(`testTag pageTwo onAppear`)
    })
    .onDisAppear(() => {
      console.log(`testTag pageTwo onDisAppear`)
    })
    .onShown(() => {
      console.log(`testTag pageTwo onShown`)
    })
    .onHidden(() => {
      console.log(`testTag pageTwo onHidden`)
    })
    .onReady((context: NavDestinationContext) => {
      this.pageInfos = context.pathStack;
    })
  }
}