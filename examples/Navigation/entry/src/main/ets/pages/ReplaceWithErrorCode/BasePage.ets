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
import { PageOne } from './pageOne';
import { PageTwo } from './pageTwo';
import { BusinessError } from '@kit.BasicServicesKit';
@ObservedV2
class SampleClass {
  @Trace p: number = 0;
}
@Entry
@Component
struct BasePage {
  @Provide pageInfos: NavPathStack = new NavPathStack()

  @Builder
  pageMap(name: string) {
    if (name == 'pageOne') {
      PageOne()
    }
    else if (name == 'pageTwo') {
      PageTwo()
    }
  }
  @State buildMapSelect: boolean = true
  @State selectBuildMapText: string = "关闭buildMap函数"
  @Provide("result") result:string = ""

  build() {
    Column() {
      if (this.buildMapSelect) {
        Navigation(this.pageInfos) {
          Column({ space: '10vp' }) {
            Button(this.selectBuildMapText)
              .width("80%")
              .height(40)
              .margin(5)
              .onClick(() => {
                this.buildMapSelect = !this.buildMapSelect
                this.result = ""
                if (this.buildMapSelect) {
                  this.selectBuildMapText = "关闭buildMap函数"
                } else {
                  this.selectBuildMapText = "设置buildMap函数"
                }
              })
            Button("pushDestination pageOne").onClick(() => {
              this.pageInfos.pushDestination({ name: 'pageOne' })
                .then(() => {
                  console.log('[pushDestination pageOne]success.');
                })
                .catch((error: BusinessError) => {
                  console.log(`[pushDestination pageOne]failed, error code = ${error.code}, error.message = ${error.message}.`);
                });
            })
            Button("replaceDestination pageOne").onClick(() => {
              this.pageInfos.replaceDestination({ name: 'pageOne' })
                .then(() => {
                  console.log('[pushDestination pageOne]success.');
                })
                .catch((error: BusinessError) => {
                  console.log(`[pushDestination pageOne]failed, error code = ${error.code}, error.message = ${error.message}.`);
                });
            })
            Button("replaceDestination*50 pageOne").onClick(() => {
              for(let i:number=0;i<50;i++){
                this.pageInfos.replaceDestination({ name: 'pageOne' })
                  .then(() => {
                    console.log('[pushDestination pageOne]success.');
                  })
                  .catch((error: BusinessError) => {
                    console.log(`[pushDestination pageOne]failed, error code = ${error.code}, error.message = ${error.message}.`);
                  });
              }
            })
          }
        }
        .title('基础场景')
        .navDestination(this.pageMap)
      } else {
        Navigation(this.pageInfos) {
          Column({ space: '10vp' }) {
            Button(this.selectBuildMapText)
              .width("80%")
              .height(40)
              .margin(5)
              .onClick(() => {
                this.buildMapSelect = !this.buildMapSelect
                this.result = ""
                if (this.buildMapSelect) {
                  this.selectBuildMapText = "关闭buildMap函数"
                } else {
                  this.selectBuildMapText = "设置buildMap函数"
                }
              })
            Button("pushDestination pageOne").onClick(() => {
              this.pageInfos.pushDestination({ name: 'pageOne' })
                .then(() => {
                  console.log('[pushDestination pageOne]success.');
                })
                .catch((error: BusinessError) => {
                  console.log(`[pushDestination pageOne]failed, error code = ${error.code}, error.message = ${error.message}.`);
                });
            })
            Button("replaceDestination pageOne").onClick(() => {
              this.pageInfos.replaceDestination({ name: 'pageOne' })
                .then(() => {
                  console.log('[replaceDestination pageOne]success.');
                })
                .catch((error: BusinessError) => {
                  console.log(`[replaceDestination pageOne]failed, error code = ${error.code}, error.message = ${error.message}.`);
                });
            })
            Button("replaceDestination*50 pageOne").onClick(() => {
              for(let i:number=0;i<50;i++){
                this.pageInfos.replaceDestination({ name: 'pageOne' })
                  .then(() => {
                    console.log('[replaceDestination pageOne]success.');
                  })
                  .catch((error: BusinessError) => {
                    console.log(`[replaceDestination pageOne]failed, error code = ${error.code}, error.message = ${error.message}.`);
                  });
              }
            })
          }
        }
        .title('基础场景')
      }
    }
  }
}