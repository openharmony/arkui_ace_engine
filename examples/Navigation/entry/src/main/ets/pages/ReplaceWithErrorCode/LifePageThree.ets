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
import { BusinessError } from "@kit.BasicServicesKit"

@Builder
export function LifePageThreeBuilder(name: string, param: Object) {
  LifePageThree()
}

@Component
export struct LifePageThree {

  build() {
    NavDestination() {
      Column({space: '10vp'}) {
        Text("LifePageThree")
      }

    }
    .backgroundColor('rgba(82,19,19,0.5)')
    .title("Page three")
    .mode(NavDestinationMode.DIALOG)
    .onAppear(() => {
      console.log('===ReplaceWithErrorCode=== pageThree onAppear')
    })
    .onDisAppear(() => {
      console.log('===ReplaceWithErrorCode=== pageThree onDisAppear')
    })
    .onShown(() => {
      console.log('===ReplaceWithErrorCode=== pageThree onShown')
    })
    .onHidden(() => {
      console.log('===ReplaceWithErrorCode=== pageThree onHidden')
    })
    .onWillAppear(() => {
      console.log('===ReplaceWithErrorCode=== pageThree onWillAppear')
    })
    .onWillDisappear(() => {
      console.log('===ReplaceWithErrorCode=== pageThree onWillDisappear')
    })
    .onWillShow(() => {
      console.log('===ReplaceWithErrorCode=== pageThree onWillShow')
    })
    .onWillHide(() => {
      console.log('===ReplaceWithErrorCode=== pageThree onWillHide')
    })
  }
}