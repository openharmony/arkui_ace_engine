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
// pageTwo.ets

export class pages {
  names: string = ""
  values: NavPathStack | null = null
}

@Component
export struct pageTwoTmp {
  @Consume('pageInfos') pageInfos: NavPathStack
  @State text :string = ''
  @State number :number = 0

  build() {
    NavDestination() {
      Column() {
        Button('pushPathByName', { stateEffect: true, type: ButtonType.Capsule })
          .width('80%')
          .height(40)
          .margin(20)
          .onClick(() => {
            this.text = this.pageInfos.getAllPathName().toString()
            console.log("===DialogDestination=== pageTwo Click accept");
          })
        Text('' + this.text)
        Button('getSize222', { stateEffect: true, type: ButtonType.Capsule })
          .width('80%')
          .height(40)
          .margin(20)
          .onClick(() => {
            this.number = this.pageInfos.size()
            console.log("===DialogDestination=== pageTwo getSize222 Click accept");
          })
        Text('' + this.number)
      }.width(300).height(350).border({width:1}).borderColor(Color.Red)
    }.title('pageTwo')
    .mode(NavDestinationMode.DIALOG)
    .onBackPressed(() => {
      console.log(`===DialogDestination=== testTag pageTwo onBackPress`)
      this.pageInfos.pop()
      return true
    })
    .onWillAppear(()=>{
      console.log("===DialogDestination=== testTag pageTwo onWillAppear")
    })
    .onAppear(()=>{
      console.log("===DialogDestination=== testTag pageTwo onAppear")
    })
    .onWillShow(()=>{
      console.log("===DialogDestination=== testTag pageTwo onWillShow")
    })
    .onShown(()=>{
      console.log("===DialogDestination=== testTag pageTwo onShown")
    })
    .onWillHide(()=>{
      console.log("===DialogDestination=== testTag pageTwo onWillHide")
    })
    .onHidden(()=>{
      console.log("===DialogDestination=== testTag pageTwo onHidden")
    })
    .onWillDisappear(()=>{
      console.log("===DialogDestination=== testTag pageTwo onWillDisappear")
    })
    .onDisAppear(()=>{
      console.log("===DialogDestination=== testTag pageTwo onDisAppear")
    })
  }
}