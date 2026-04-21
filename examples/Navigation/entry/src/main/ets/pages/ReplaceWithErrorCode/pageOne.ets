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
export function PageOneBuilder(name: string, param: Object) {
  PageOne()
}

@Component
export struct PageOne {
  @Consume('pageInfos') pageInfos: NavPathStack

  build() {
    NavDestination() {
      Column({space: '10vp'}) {
        Button("replaceDestination pageTwo").onClick(() => {
          this.pageInfos.replaceDestination({ name: 'pageTwo',param:"This is the parameter of the pageTwo page." })
            .then(()=>{
              console.log('[replaceDestination pageTwo]success.');
            })
            .catch((error: BusinessError)=>{
              console.log(`[replaceDestination pageTwo]failed, error code = ${error.code}, error.message = ${error.message}.`);
            });
        })
        Button("对照组：replacePath pageTwo").onClick(() => {
          this.pageInfos.replacePath({ name: 'pageTwo',param:"This is the parameter of the pageTwo page." })
        })
        Button("replaceDestination null").onClick(() => {
          this.pageInfos.replaceDestination({ name: null })
            .then(()=>{
              console.log('[replaceDestination null]success.');
            })
            .catch((error: BusinessError)=>{
              console.log(`[replaceDestination null]failed, error code = ${error.code}, error.message = ${error.message}.`);
            });
        })
        Button("replaceDestination undefined").onClick(() => {
          this.pageInfos.replaceDestination({ name: undefined })
            .then(()=>{
              console.log('[replaceDestination undefined]success.');
            })
            .catch((error: BusinessError)=>{
              console.log(`[replaceDestination undefined]failed, error code = ${error.code}, error.message = ${error.message}.`);
            });
        })

        Button("replaceDestination pageFive").onClick(() => {
          this.pageInfos.replaceDestination({ name: 'pageFive' })
            .then(()=>{
              console.log('[replaceDestination pageFive]success.');
            })
            .catch((error: BusinessError)=>{
              console.log(`[replaceDestination pageFive]failed, error code = ${error.code}, error.message = ${error.message}.`);
            });
        })
      }
    }
    .title("Page one")
    .backgroundColor("#FFCC66")
    .onReady((context: NavDestinationContext) => {
      this.pageInfos = context.pathStack;
    })
  }
}