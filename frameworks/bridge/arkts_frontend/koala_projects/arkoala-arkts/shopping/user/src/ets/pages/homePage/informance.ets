/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

import { InformationModel } from '../../model/homeModel'
import { informationData } from '../../data/homeData'
import { callFetchWithEACoroutine, callFetchWithCoroutine, callFetchWithTaskPool} from '../../arkcompilerPOC/concurrency'
import { callRDBWithManagedEACoroutine, callRDBWithNativeEACoroutine, GetAll } from '../../arkcompilerPOC/concurrency2'

import { TestOperators,
         TestConversion,
         TestFuncCallArg,
         TestFuncCallReturnType,
         TestImportStatements,
         TestMethodCallArg,
         TestMethodCallReturnType,
         TestSimpleException
       } from '../../arkcompilerPOC/interopTests'
@Component
export struct Information {
  @State color1: string = '#ff0000'
  @State color2: string = '#00ff00'
  @State information: Array<InformationModel> = informationData
  @Prop ratio: number

  build() {
      Column() {
          Button("CallFetchWithCoroutine")
              .backgroundColor(this.color1)
              .width(200).height(100)
              .onClick((e?: ClickEvent) => {
                  this.swap();
                  callFetchWithCoroutine();
                  })
          Button("CallFetchWithTaskPool")
              .backgroundColor(this.color2)
              .width(200).height(100)
              .onClick((e?: ClickEvent) => {
                  this.swap()
                  callFetchWithTaskPool();
              })
          Button("CallFetchWithEACoroutine")
              .width(200).height(100)
              .onClick((e?: ClickEvent) => {
                  callFetchWithEACoroutine();
              })
          Button(`CallRDBWithManagedEACoroutine`)
              .width(200).height(100)
              .onClick((e?: ClickEvent) => {
                  callRDBWithManagedEACoroutine(()=>{
                    GetAll((prs: number) => {
                        console.log(`inserted prs: ${prs}`)
                    })
                  })
                  })
          Button("RunInteropTest")
              .width(200).height(100)
              .onClick((e?: ClickEvent) => {
                  TestOperators();
                  TestMethodCallArg();
                  TestMethodCallReturnType();
                  TestConversion();
                  TestFuncCallArg();
                  TestFuncCallReturnType();
                  TestImportStatements();
                  TestSimpleException();
              })
      }
      .width('100%').height('100%')
      .backgroundColor(Color.Gray)
      .justifyContent(FlexAlign.Center)
  }

  swap(): void {
      console.log("#### Swap")
      let tmp = this.color1
      this.color1 = this.color2
      this.color2 = tmp
  }
}