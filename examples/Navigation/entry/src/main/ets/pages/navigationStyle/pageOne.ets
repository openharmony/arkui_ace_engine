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

class tmpClass{
  count:number=10
}

@Component
export struct pageOneTmp {
  @Consume('pageInfos') pageInfos: NavPathStack;
  @State hideTitleBar:boolean = false
  @State mode:NavDestinationMode = NavDestinationMode.DIALOG

  @Builder Title(){
    Column(){
      Text('pageOne')
        .fontColor('#182431')
        .fontSize(30)
    }.backgroundColor(Color.Pink)
  }

  build() {
    NavDestination() {
      Column() {
        Button(this.hideTitleBar? 'show title': 'hide title').backgroundColor('#4198b7')
          .onClick(() => {
            this.hideTitleBar = !this.hideTitleBar
          })
        Text('DIALOG' ).fontColor(Color.Red)

      }.width('100%').height('100%')
    }
    .title(this.Title)
    .hideTitleBar(this.hideTitleBar)
    .mode(this.mode)
    .border({width:1})
    .borderColor(Color.Yellow)
    .width(200)
    .height(400)
    .onBackPressed(() => {
      this.pageInfos.pop()
      return true
    })
  }
}