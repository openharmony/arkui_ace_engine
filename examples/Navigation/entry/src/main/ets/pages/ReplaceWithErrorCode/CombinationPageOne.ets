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
export function CombinationPageOneBuilder(name: string, param: Object) {
  CombinationPageOne()
}

@Component
export struct CombinationPageOne {
  @Consume('CombinationpageInfos') CombinationpageInfos: NavPathStack

  build() {
    NavDestination() {
      Column({space: '10vp'}) {
        Button("replaceDestination pageTwo").onClick(() => {
          this.CombinationpageInfos.replaceDestination({ name: 'pageTwo' })
            .then(()=>{
              console.log('[replaceDestination pageTwo]success.');
            })
            .catch((error: BusinessError)=>{
              console.log(`[replaceDestination pageTwo]failed, error code = ${error.code}, error.message = ${error.message}.`);
            });

        })
        Button("replaceDestination*50 pageTwo+clear").onClick(() => {
          for (let i = 0; i < 50; i++) {
            this.CombinationpageInfos.replaceDestination({ name: 'pageTwo' })
              .then(()=>{
                console.log('[replaceDestination*50 pageTwo+clear]success.');
              })
              .catch((error: BusinessError)=>{
                console.log(`[replaceDestination*50 pageTwo+clear]failed, error code = ${error.code}, error.message = ${error.message}.`);
              });
          }
          this.CombinationpageInfos.clear()
        })
        Button("pushDestination pageTwo").onClick(() => {
          this.CombinationpageInfos.pushDestination({ name: 'pageTwo' })
        })
        Button("replaceDestination pageTwo+pushByName pageOne").onClick(() => {
          this.CombinationpageInfos.replaceDestination({ name: 'pageTwo' })
            .then(()=>{
              console.log('[replaceDestination pageTwo+pushByName pageOne]success.');
            })
            .catch((error: BusinessError)=>{
              console.log(`[replaceDestination pageTwo+pushByName pageOne]failed, error code = ${error.code}, error.message = ${error.message}.`);
            });
          this.CombinationpageInfos.pushPathByName('pageOne', null)
        })
        Button("对照组：replace pageTwo+pushByName pageOne").onClick(() => {
          this.CombinationpageInfos.replacePath({ name: 'pageTwo' })
          this.CombinationpageInfos.pushPathByName('pageOne', null)
        })

        Button("replaceDestination*50 pageFive").onClick(() => {
          for (let i = 0; i < 50; i++) {
            this.CombinationpageInfos.replaceDestination({ name: 'pageFive' })
              .then(()=>{
                console.log('[replaceDestination*50 pageFive]success.');
              })
              .catch((error: BusinessError)=>{
                console.log(`[replaceDestination*50 pageFive]failed, error code = ${error.code}, error.message = ${error.message}.`);
              });
          }
        })

        Button("replaceDestination*50 pageFour").onClick(() => {
          for (let i = 0; i < 50; i++) {
            this.CombinationpageInfos.replaceDestination({ name: 'pageFour' })
              .then(()=>{
                console.log('[replaceDestination*50 pageFour]success.');
              })
              .catch((error: BusinessError)=>{
                console.log(`[replaceDestination*50 pageFour]failed, error code = ${error.code}, error.message = ${error.message}.`);
              });
          }
        })
        Button("replaceDestination pageTwo + pop").onClick(() => {

          this.CombinationpageInfos.replaceDestination({ name: 'pageTwo' })
            .then(()=>{
              console.log('[replaceDestination pageFour]success.');
            })
            .catch((error: BusinessError)=>{
              console.log(`[replaceDestination pageFour]failed, error code = ${error.code}, error.message = ${error.message}.`);
            });
          this.CombinationpageInfos.pop()
        })
        Button("replace pageOne").onClick(() => {

          this.CombinationpageInfos.replacePath({ name: 'pageOne' })

        })
        Button("replace*50 pageOne").onClick(() => {
          for(let i:number=0;i<=50;i++){
            this.CombinationpageInfos.replacePath({ name: 'pageOne' })
          }

        })
        Button("replaceDestination pageOne").onClick(() => {

          this.CombinationpageInfos.replaceDestination({ name: 'pageOne' })
            .then(()=>{
              console.log('[replaceDestination pageOne]success.');
            })
            .catch((error: BusinessError)=>{
              console.log(`[replaceDestination pageOne]failed, error code = ${error.code}, error.message = ${error.message}.`);
            });

        })
        Button("replaceDestination*50 pageOne").onClick(() => {
          for(let i:number=0;i<=50;i++){
            this.CombinationpageInfos.replaceDestination({ name: 'pageOne' })
              .then(()=>{
                console.log('[replaceDestination pageOne]success.');
              })
              .catch((error: BusinessError)=>{
                console.log(`[replaceDestination pageOne]failed, error code = ${error.code}, error.message = ${error.message}.`);
              });
          }

        })
        Button("内存泄漏对照组：push+pop pageOne").onClick(() => {
          this.CombinationpageInfos.pushPath({ name: 'pageOne' })
          this.CombinationpageInfos.pop()
        })
      }
    }
    .backgroundColor("#FF33CC")
    .title("Page one")
    .onReady((context: NavDestinationContext) => {
      this.CombinationpageInfos = context.pathStack;
    })
  }
}