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
class TmpClass{
  count:number=10
}
@Entry
@Component
export struct CTmp {
  pageInfos: NavPathStack = new NavPathStack();
  @State isChange: boolean = false;

  build() {
    NavDestination() {
      Column() {

      }.width('100%').height('100%')
    }.title('C页面')
    .onAppear(() => {
      console.log(`testTag pageThree onAppear`)
    })
    .onDisAppear(() => {
      console.log(`testTag pageThree onDisAppear`)
    })
    .onShown(() => {
      console.log(`testTag pageThree onShown`)
    })
    .onHidden(() => {
      console.log(`testTag pageThree onHidden`)
    })
    .onReady((context: NavDestinationContext) => {
      this.pageInfos = context.pathStack;
    })
  }
}