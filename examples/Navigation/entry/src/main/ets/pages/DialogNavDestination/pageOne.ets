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
// pageOne.ets
export class pages {
  names: string = ""
  values: NavPathStack | null = null
}
@Component
export struct pageOneTmp {
  @Consume('pageInfos') pageInfos: NavPathStack;
  @State text :string = ''

  build() {
    NavDestination() {
      Column() {
        Button('pushPathByName', { stateEffect: true, type: ButtonType.Capsule })
          .width('80%')
          .height(40)
          .margin(20)
          .onClick(() => {
            this.text = this.pageInfos.getAllPathName().toString()

          })
        Text('' + this.text)
      }.width(350).height(400).border({width:1}).borderColor(Color.Yellow)
    }.title('pageOne')
    .hitTestBehavior(HitTestMode.None)
    .mode(NavDestinationMode.DIALOG)
    .onBackPressed(() => {
      console.log(`===DialogDestination=== testTag pageOne onBackPress`)
      this.pageInfos.pop()
      return true
    })
    .onWillAppear(()=>{
      console.log("===DialogDestination=== testTag pageOne onWillAppear")
    })
    .onAppear(()=>{
      console.log("===DialogDestination=== testTag pageOne onAppear")
    })
    .onWillShow(()=>{
      console.log("===DialogDestination=== testTag pageOne onWillShow")
    })
    .onShown(()=>{
      console.log("===DialogDestination=== testTag pageOne onShown")
    })
    .onWillHide(()=>{
      console.log("===DialogDestination=== testTag pageOne onWillHide")
    })
    .onHidden(()=>{
      console.log("===DialogDestination=== testTag pageOne onHidden")
    })
    .onWillDisappear(()=>{
      console.log("===DialogDestination=== testTag pageOne onWillDisappear")
    })
    .onDisAppear(()=>{
      console.log("===DialogDestination=== testTag pageOne onDisAppear")
    })
  }
}