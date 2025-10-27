/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { router } from '@kit.ArkUI';

@Entry
@Component
struct pageTwo{
  @Provide pageInfos:NavPathStack = new NavPathStack()
  @State height1:string = '100%'
  @State mode:NavigationMode = NavigationMode.Stack
  @State launchMode:LaunchMode = LaunchMode.STANDARD

  build() {
    Column(){
      Navigation(this.pageInfos){
        NavDestination(){
          Button('router push test1').onClick((event: ClickEvent) => {
            router.pushUrl({url:'pages/34-ssasdadsadsa/test1'})
          })
          Button('router push test1').onClick((event: ClickEvent) => {
            router.pushUrl({url:'pages/34-ssasdadsadsa/pageOne'})
          })
          Button('router push test1').onClick((event: ClickEvent) => {
            router.pushUrl({url:'pages/34-ssasdadsadsa/pageTwo'})
          })
          Button('router clear').onClick((event: ClickEvent) => {
            router.clear()
          })
        }.title('pageTwo')
      }
      .mode(this.mode)
      .height(this.height1)
      .border({width:1})
    }

  }
}

