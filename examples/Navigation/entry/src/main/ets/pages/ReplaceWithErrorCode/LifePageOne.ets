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
import { observer } from "@kit.TelephonyKit";

@Builder
export function LifePageOneBuilder(name: string, param: Object) {
  LifePageOne()
}

@Component
export struct LifePageOne {
  @Consume('lifepageInfos') lifepageInfos: NavPathStack
  @State message: string = 'UIExtensionAbility'

  build() {
    NavDestination() {
      Column({space: '10vp'}) {
        Button("pushDestination pageTwo").onClick(() => {
          this.lifepageInfos.pushDestination({ name: 'pageTwo' })
            .then(()=>{
              console.log('[pushDestination pageTwo]success.');
            })
            .catch((error: BusinessError)=>{
              console.log(`[pushDestination pageTwo]failed, error code = ${error.code}, error.message = ${error.message}.`);
            });
        })
        Button("replaceDestination pageTwo").onClick(() => {
          this.lifepageInfos.replaceDestination({ name: 'pageTwo' })
            .then(()=>{
              console.log('[replaceDestination pageTwo]success.');
            })
            .catch((error: BusinessError)=>{
              console.log(`[replaceDestination pageTwo]failed, error code = ${error.code}, error.message = ${error.message}.`);
            });
        })
        Button("对照组 replace pageTwo").onClick(() => {
          this.lifepageInfos.replacePath({ name: 'pageTwo' })
        })
        Button("replaceDestination pageThree").onClick(() => {
          this.lifepageInfos.replaceDestination({ name: 'pageThree' })
            .then(()=>{
              console.log('[replaceDestination pageThree]success.');
            })
            .catch((error: BusinessError)=>{
              console.log(`[replaceDestination pageThree]failed, error code = ${error.code}, error.message = ${error.message}.`);
            });
        })
      }
    }
    .backgroundColor("#009933")
    .title("Page one")
    .mode(NavDestinationMode.STANDARD)
    .onAppear(() => {
      console.log('===ReplaceWithErrorCode=== pageOne onAppear')
    })
    .onDisAppear(() => {
      console.log('===ReplaceWithErrorCode=== pageOne onDisAppear')
    })
    .onShown(() => {
      console.log('===ReplaceWithErrorCode=== pageOne onShown')
    })
    .onHidden(() => {
      console.log('===ReplaceWithErrorCode=== pageOne onHidden')
    })
    .onWillAppear(() => {
      console.log('===ReplaceWithErrorCode=== pageOne onWillAppear')
    })
    .onWillDisappear(() => {
      console.log('===ReplaceWithErrorCode=== pageOne onWillDisappear')
    })
    .onWillShow(() => {
      console.log('===ReplaceWithErrorCode=== pageOne onWillShow')
    })
    .onWillHide(() => {
      console.log('===ReplaceWithErrorCode=== pageOne onWillHide')
    })
    .onReady((context: NavDestinationContext) => {
      this.lifepageInfos = context.pathStack;
    })
  }
}