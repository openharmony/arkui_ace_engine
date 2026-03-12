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
export function CombinationPageTwoBuilder(name: string, param: Object) {
  CombinationPageTwo()
}

@Component
export struct CombinationPageTwo {

  @Consume('CombinationpageInfos') CombinationpageInfos: NavPathStack

  build() {
    NavDestination() {
      Column({space: '10vp'}) {
        Button("replaceDestination pageThree").onClick(() => {
          this.CombinationpageInfos.replaceDestination({ name: 'pageThree' })
            .then(()=>{
              console.log('[replaceDestination pageThree]success.');
            })
            .catch((error: BusinessError)=>{
              console.log(`[replaceDestination pageThree]failed, error code = ${error.code}, error.message = ${error.message}.`);
            });

        })
        Button("replaceDestination pageFive + moveToTop pageOne").onClick(() => {
          this.CombinationpageInfos.replaceDestination({ name: 'pageFive' })
            .then(()=>{
              console.log('[replaceDestination pageThree+moveToTop pageOne]success.');
            })
            .catch((error: BusinessError)=>{
              console.log(`[replaceDestination pageThree+moveToTop pageOne]failed, error code = ${error.code}, error.message = ${error.message}.`);
            });
          this.CombinationpageInfos.moveToTop('pageOne')
        })

        Button("moveToTop pageOne + replaceDestination Three").onClick(() => {
          this.CombinationpageInfos.moveToTop('pageOne')
          this.CombinationpageInfos.replaceDestination({ name: 'pageThree' })
            .then(()=>{
              console.log('[moveToTop pageOne + replaceDestination Three]success.');
            })
            .catch((error: BusinessError)=>{
              console.log(`[moveToTop pageOne + replaceDestination Three]failed, error code = ${error.code}, error.message = ${error.message}.`);
            });
        })

        Button("pop + replaceDestination Three").onClick(() => {
          this.CombinationpageInfos.pop()
          this.CombinationpageInfos.replaceDestination({ name: 'pageThree' })
            .then(()=>{
              console.log('[pop + replaceDestination Three]success.');
            })
            .catch((error: BusinessError)=>{
              console.log(`[pop + replaceDestination Three]failed, error code = ${error.code}, error.message = ${error.message}.`);
            });
        })
      }
    }
    .title("Page Two")
    .backgroundColor("#99CCFF")
    .onReady((context: NavDestinationContext) => {
      this.CombinationpageInfos = context.pathStack;
    })
  }
}