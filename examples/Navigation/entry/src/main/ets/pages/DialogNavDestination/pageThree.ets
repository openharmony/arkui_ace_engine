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
export struct pageThreeTmp {
  @Consume('pageInfos') pageInfos: NavPathStack
  @State text :string = ''
  @State number :number = 0
  @State number2 :number = 0
  build() {
    NavDestination() {
      Column() {
        Button('getSize11', { stateEffect: true, type: ButtonType.Capsule})
          .width('80%')
          .height(40)
          .margin(20)
          .onClick(() => {
            this.number2 = this.pageInfos.size()
            console.log("===DialogDestination=== pageThree getSize11 Click accept")
          })
        Text('' + this.number2).fontSize(30).fontColor(Color.Red)

        Button('getAllPathName', { stateEffect: true, type: ButtonType.Capsule})
          .width('80%')
          .height(40)
          .margin(20)
          .onClick(() => {
            this.text = this.pageInfos.getAllPathName().toString()
            console.log("===DialogDestination=== pageThree getAllPathName Click accept");
          })
        Text('' + this.text)

        Button('getSize222', { stateEffect: true, type: ButtonType.Capsule })
          .width('80%')
          .height(40)
          .margin(20)
          .onClick(() => {
            this.number = this.pageInfos.size()
            console.log("===DialogDestination=== pageThree getSize222 Click accept");
          })
        Text('' + this.number)
      }.width(300).height(300).border({width:1})
    }.title('pageThree')
    .mode(NavDestinationMode.STANDARD)
    .onBackPressed(() => {
      console.log(`===DialogDestination=== testTag pageThree onBackPress`)
      this.pageInfos.pop()
      return true
    })
    .onWillAppear(()=>{
      console.log("===DialogDestination=== testTag pageThree onWillAppear")
    })
    .onAppear(()=>{
      console.log("===DialogDestination=== testTag pageThree onAppear")
    })
    .onWillShow(()=>{
      console.log("===DialogDestination=== testTag pageThree onWillShow")
    })
    .onShown(()=>{
      console.log("===DialogDestination=== testTag pageThree onShown")
    })
    .onWillHide(()=>{
      console.log("===DialogDestination=== testTag pageThree onWillHide")
    })
    .onHidden(()=>{
      console.log("===DialogDestination=== testTag pageThree onHidden")
    })
    .onWillDisappear(()=>{
      console.log("===DialogDestination=== testTag pageThree onWillDisappear")
    })
    .onDisAppear(()=>{
      console.log("===DialogDestination=== testTag pageThree onDisAppear")
    })

  }
}