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
        Button('pop', { stateEffect: true, type: ButtonType.Capsule })
          .width('80%')
          .height(40)
          .margin(20)
          .onClick(() => {
             this.pageInfos.pop()
          })
        Text('' + this.text)
      }.width(350).height(400).border({width:1}).borderColor(Color.Yellow)
    }.title('pageOne')
    .mode(NavDestinationMode.STANDARD)
    .onShown(()=>{
      console.log("onshow1"+ this.pageInfos.getAllPathName().toString());
    })
    .onHidden(()=>{
      console.log("onHidden1 "+ this.pageInfos.getAllPathName().toString());
    })
    .onAppear(()=>{
      console.log("onAppear1 "+ this.pageInfos.getAllPathName().toString());
    })
    .onDisAppear(()=>{
      console.log("onDisappear1:"+ this.pageInfos.getAllPathName().toString());
    })

  }
}