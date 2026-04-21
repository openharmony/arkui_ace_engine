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
export function LifePageTwoBuilder(name: string, param: Object) {
  LifePageTwo()
}

@Component
export struct LifePageTwo {
  @Consume('lifepageInfos') lifepageInfos: NavPathStack

  build() {
    NavDestination() {
      Column({space: '10vp'}) {
        Text('无感监听page two')
        Button("replaceDestination pageThree").onClick(() => {
          this.lifepageInfos.replaceDestination({ name: 'pageThree' })
            .then(()=>{
              console.log('[pushDestination pageThree]success.');
            })
            .catch((error: BusinessError)=>{
              console.log(`[pushDestination pageThree]failed, error code = ${error.code}, error.message = ${error.message}.`);
            });
        })
      }
    }
    .backgroundColor("#99CCCC")
    .title("Page Two")
    .mode(NavDestinationMode.STANDARD)
    .onAppear(() => {
      console.log('===ReplaceWithErrorCode=== pageTwo onAppear')
    })
    .onDisAppear(() => {
      console.log('===ReplaceWithErrorCode=== pageTwo onDisAppear')
    })
    .onShown(() => {
      console.log('===ReplaceWithErrorCode=== pageTwo onShown')
    })
    .onHidden(() => {
      console.log('===ReplaceWithErrorCode=== pageTwo onHidden')
    })
    .onWillAppear(() => {
      console.log('===ReplaceWithErrorCode=== pageTwo onWillAppear')
    })
    .onWillDisappear(() => {
      console.log('===ReplaceWithErrorCode=== pageTwo onWillDisappear')
    })
    .onWillShow(() => {
      console.log('===ReplaceWithErrorCode=== pageTwo onWillShow')
    })
    .onWillHide(() => {
      console.log('===ReplaceWithErrorCode=== pageTwo onWillHide')
    })
  }
}