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
import { CombinationPageOne } from './CombinationPageOne';
import { CombinationPageThree } from './CombinationPageThree';
import { CombinationPageTwo } from './CombinationPageTwo';
import { BusinessError } from '@kit.BasicServicesKit';


@Entry
@Component
struct CombinationPage {
  @Provide CombinationpageInfos: NavPathStack = new NavPathStack();

  @Builder
  pageMap(name: string) {
    if (name == 'pageOne') {
      CombinationPageOne()
    }
    else if (name == 'pageTwo') {
      CombinationPageTwo()
    }
    else if (name == 'pageThree') {
      CombinationPageThree()
    }
  }

  build() {
    Navigation(this.CombinationpageInfos){
      Column({space: '10vp'}) {
        Button("pushDestination pageThree").onClick(() => {
          this.CombinationpageInfos.pushDestination({ name: 'pageThree' })
        })
        Button("pushDestination pageOne").onClick(() => {
          this.CombinationpageInfos.pushDestination({ name: 'pageOne' })
        })

        Button("pushDestination pageOne +replaceDestination pageTwo").onClick(() => {
          this.CombinationpageInfos.pushDestination({ name: 'pageOne' })
          this.CombinationpageInfos.replaceDestination({ name: 'pageTwo' })
            .catch((error: BusinessError)=>{
              console.log(`[pushDestination pageOne +replaceDestination pageTwo]failed, error code = ${error.code}, error.message = ${error.message}.`);
            }).then(()=>{
              console.log('[pushDestination pageOne +replaceDestination pageTwo]success.');
            });
        })
      }
    }
    .backgroundColor("#CC00FF")
    .title('栈操作组合')
    .navDestination(this.pageMap)
  }
}