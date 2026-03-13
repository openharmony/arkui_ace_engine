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

import { BusinessError } from '@ohos.base'
import { pageOneTmp } from './pageOne'
import { pageTwoTmp } from './pageTwo'
import { pageFourTmp } from './pageFour'
import { pageFiveTmp } from './pageFive'
import { pageSixTmp } from './pageSix'
@Entry
@Component
struct Main {
  @Provide('pageInfos') pageInfos: NavPathStack = new NavPathStack()
  @Provide("result") result:string = ""
  @State buildMapSelect: boolean = true
  @State selectBuildMapText: string = "关闭buildMap函数"

  @Builder
  PageMap(name: string) {
    if (name === 'pageOne') {
      pageOneTmp()
    } else if (name === 'pageTwo') {
      pageTwoTmp()
    } else if (name === 'pageFour') {
      pageFourTmp()
    }else if (name === 'pageFive') {
      pageFiveTmp()
    }else if (name === 'pageSix') {
      pageSixTmp()
    }
  }

  build() {
    Column(){
      if (this.buildMapSelect){
        Navigation(this.pageInfos) {
          Column() {
            Text("result = " + this.result)
          }
        }.title('Index').navDestination(this.PageMap).height(300)
      }else {
        Navigation(this.pageInfos) {
          Column() {
            Text("result = " + this.result)
          }
        }.title('Index').height(300)
      }

      Scroll(){
        Column(){
          Button(this.selectBuildMapText)
            .width("80%")
            .height(40)
            .margin(5)
            .onClick(()=>{
              this.buildMapSelect = !this.buildMapSelect
              this.result = ""
              if (this.buildMapSelect) {
                this.selectBuildMapText = "关闭buildMap函数"
              } else {
                this.selectBuildMapText = "设置buildMap函数"
              }
            })

          Text("-----------------------------------")
          Text("result = " + this.result)

          Row(){
            Button('pushPageOne')
              .key('pushPageOne')
              .onClick(() => {
                this.pageInfos.pushDestination({ name: 'pageOne', param: null, onPop: (popInfo: PopInfo) => {} })
                  .then((data)=>{
                    this.result = "Success"
                    console.error("DSZ:: pushPathByName pageOne ok! data = " + JSON.stringify(data));
                  }).catch((error: BusinessError)=>{
                  console.error( "DSZ:: error.code is ",  typeof error.code)
                  this.result = `${error.code} ${error.message}`
                  console.error(`DSZ:: pushPathByName pageOne failed! error.code = ${error.code}, error.message = ${error.message}` );
                })
              })
              .width("33%")
            Button('pushPageTwo')
              .key('pushPageTwo')
              .onClick(() => {
                this.pageInfos.pushDestination({ name: 'pageTwo', param: null, onPop: (popInfo: PopInfo) => {} })
                  .then((data)=>{
                    this.result = "Success"
                    console.error("DSZ:: pushPathByName pageTwo ok! data = " + JSON.stringify(data));
                  }).catch((error: BusinessError)=>{
                  console.error( "DSZ:: error.code is ",  typeof error.code)
                  this.result = `${error.code} ${error.message}`
                  console.error(`DSZ:: pushPathByName pageOne failed! error.code = ${error.code}, error.message = ${error.message}` );
                })
              })
              .width("33%")
            Button('pushPageThree')
              .key('pushPageThree')
              .onClick(() => {
                this.pageInfos.pushDestination({ name: 'pageThree', param: null, onPop: (popInfo: PopInfo) => {} })
                  .then((data)=>{
                    this.result = "Success"
                    console.error("DSZ:: pushPathByName pageThree ok! data = " + JSON.stringify(data));
                  }).catch((error: BusinessError)=>{
                  this.result = `${error.code} ${error.message}`
                  console.error(`DSZ:: pushPathByName pageThree failed! error.code = ${error.code}, error.message = ${error.message}` );
                })
              })
              .width("33%")
          }

          Row(){
            Button('pushPageFour')
              .key('pushPageFour')
              .onClick(() => {
                this.pageInfos.pushDestination({ name: 'pageFour', param: null, onPop: (popInfo: PopInfo) => {} })
                  .then((data)=>{
                    this.result = "Success"
                    console.error("DSZ:: pushPathByName pageFour ok! data = " + JSON.stringify(data));
                  }).catch((error: BusinessError)=>{
                  console.error( "DSZ:: error.code is ",  typeof error.code)
                  this.result = `${error.code} ${error.message}`
                  console.error(`DSZ:: pushPathByName pageOne failed! error.code = ${error.code}, error.message = ${error.message}` );
                })
              })
              .width("33%")
            Button('pushPageFive')
              .key('pushPageFive')
              .onClick(() => {
                this.pageInfos.pushDestination({ name: 'pageFive', param: null, onPop: (popInfo: PopInfo) => {} })
                  .then((data)=>{
                    this.result = "Success"
                    console.error("DSZ:: pushPathByName pageFive ok! data = " + JSON.stringify(data));
                  }).catch((error: BusinessError)=>{
                  console.error( "DSZ:: error.code is ",  typeof error.code)
                  this.result = `${error.code} ${error.message}`
                  console.error(`DSZ:: pushPathByName pageOne failed! error.code = ${error.code}, error.message = ${error.message}` );
                })
              })
              .width("33%")
            Button('pushPageSix')
              .key('pushPageSix')
              .onClick(() => {
                this.pageInfos.pushDestination({ name: 'pageSix', param: null, onPop: (popInfo: PopInfo) => {} })
                  .then((data)=>{
                    this.result = "Success"
                    console.error("DSZ:: pushPathByName pageSix ok! data = " + JSON.stringify(data));
                  }).catch((error: BusinessError)=>{
                  console.error( "DSZ:: error.code is ",  typeof error.code)
                  this.result = `${error.code} ${error.message}`
                  console.error(`DSZ:: pushPathByName pageOne failed! error.code = ${error.code}, error.message = ${error.message}` );
                })
              })
              .width("33%")
          }

          Row(){
            Button('pushByNamePageOne')
              .key('pushByNamePageOne')
              .onClick(() => {
                this.pageInfos.pushDestinationByName( 'pageOne', null)
                  .then((data)=>{
                    this.result = "Success"
                    console.error("DSZ:: pushPathByName pageOne ok! data = " + JSON.stringify(data));
                  }).catch((error: BusinessError)=>{
                  console.error( "DSZ:: error.code is ",  typeof error.code)
                  this.result = `${error.code} ${error.message}`
                  console.error(`DSZ:: pushPathByName pageOne failed! error.code = ${error.code}, error.message = ${error.message}` );
                })
              })
              .width("33%")
            Button('pushByNamePageTwo')
              .key('pushByNamePageTwo')
              .onClick(() => {
                this.pageInfos.pushDestinationByName('pageTwo',  null )
                  .then((data)=>{
                    this.result = "Success"
                    console.error("DSZ:: pushPathByName pageOne ok! data = " + JSON.stringify(data));
                  }).catch((error: BusinessError)=>{
                  console.error( "DSZ:: error.code is ",  typeof error.code)
                  this.result = `${error.code} ${error.message}`
                  console.error(`DSZ:: pushPathByName pageOne failed! error.code = ${error.code}, error.message = ${error.message}` );
                })
              })
              .width("33%")
            Button('pushByNamePageThree')
              .key('pushByNamePageThree')
              .onClick(() => {
                this.pageInfos.pushDestinationByName('pageThree', null )
                  .then((data)=>{
                    this.result = "Success"
                    console.error("DSZ:: pushPathByName pageThree ok! data = " + JSON.stringify(data));
                  }).catch((error: BusinessError)=>{
                  this.result = `${error.code} ${error.message}`
                  console.error(`DSZ:: pushPathByName pageThree failed! error.code = ${error.code}, error.message = ${error.message}` );
                })
              })
              .width("33%")
          }

          Row(){
            Button('pushByNamePageFour')
              .key('pushByNamePageFour')
              .onClick(() => {
                this.pageInfos.pushDestinationByName( 'pageFour',  null )
                  .then((data)=>{
                    this.result = "Success"
                    console.error("DSZ:: pushPathByName pageFour ok! data = " + JSON.stringify(data));
                  }).catch((error: BusinessError)=>{
                  console.error( "DSZ:: error.code is ",  typeof error.code)
                  this.result = `${error.code} ${error.message}`
                  console.error(`DSZ:: pushPathByName pageOne failed! error.code = ${error.code}, error.message = ${error.message}` );
                })
              })
              .width("33%")
            Button('pushByNamePageFive')
              .key('pushByNamePageFive')
              .onClick(() => {
                this.pageInfos.pushDestinationByName( 'pageFive',  null )
                  .then((data)=>{
                    this.result = "Success"
                    console.error("DSZ:: pushPathByName pageFive ok! data = " + JSON.stringify(data));
                  }).catch((error: BusinessError)=>{
                  console.error( "DSZ:: error.code is ",  typeof error.code)
                  this.result = `${error.code} ${error.message}`
                  console.error(`DSZ:: pushPathByName pageOne failed! error.code = ${error.code}, error.message = ${error.message}` );
                })
              })
              .width("33%")
            Button('pushByNamePageSix')
              .key('pushByNamePageSix')
              .onClick(() => {
                this.pageInfos.pushDestinationByName( 'pageSix', null )
                  .then((data)=>{
                    this.result = "Success"
                    console.error("DSZ:: pushPathByName pageSix ok! data = " + JSON.stringify(data));
                  }).catch((error: BusinessError)=>{
                  console.error( "DSZ:: error.code is ",  typeof error.code)
                  this.result = `${error.code} ${error.message}`
                  console.error(`DSZ:: pushPathByName pageOne failed! error.code = ${error.code}, error.message = ${error.message}` );
                })
              })
              .width("33%")
          }

          Row() {
            Button('pushByNameWithOnPopPageOne')
              .key('pushByNameWithOnPopPageOne')
              .onClick(() => {
                this.pageInfos.pushDestinationByName( 'pageOne', null,  (popInfo: PopInfo) => {} )
                  .then((data)=>{
                    this.result = "Success"
                    console.error("DSZ:: pushPathByName pageOne ok! data = " + JSON.stringify(data));
                  }).catch((error: BusinessError)=>{
                  console.error( "DSZ:: error.code is ",  typeof error.code)
                  this.result = `${error.code} ${error.message}`
                  console.error(`DSZ:: pushPathByName pageOne failed! error.code = ${error.code}, error.message = ${error.message}` );
                })
              })
              .width("33%")
            Button('pushByNameWithOnPopPageTwo')
              .key('pushByNameWithOnPopPageTwo')
              .onClick(() => {
                this.pageInfos.pushDestinationByName('pageTwo', null,  (popInfo: PopInfo) => {} )
                  .then((data)=>{
                    this.result = "Success"
                    console.error("DSZ:: pushPathByName pageOne ok! data = " + JSON.stringify(data));
                  }).catch((error: BusinessError)=>{
                  console.error( "DSZ:: error.code is ",  typeof error.code)
                  this.result = `${error.code} ${error.message}`
                  console.error(`DSZ:: pushPathByName pageOne failed! error.code = ${error.code}, error.message = ${error.message}` );
                })
              })
              .width("33%")
            Button('pushByNameWithOnPopPageThree')
              .key('pushByNameWithOnPopPageThree')
              .onClick(() => {
                this.pageInfos.pushDestinationByName( 'pageThree', null,(popInfo: PopInfo) => {} )
                  .then((data)=>{
                    this.result = "Success"
                    console.error("DSZ:: pushPathByName pageThree ok! data = " + JSON.stringify(data));
                  }).catch((error: BusinessError)=>{
                  this.result = `${error.code} ${error.message}`
                  console.error(`DSZ:: pushPathByName pageThree failed! error.code = ${error.code}, error.message = ${error.message}` );
                })
              })
              .width("33%")
          }
          Row() {
            Button('pushByNameWithOnPopPageFour')
              .key('pushByNameWithOnPopPageFour')
              .onClick(() => {
                this.pageInfos.pushDestinationByName( 'pageFour',  null, (popInfo: PopInfo) => {} )
                  .then((data)=>{
                    this.result = "Success"
                    console.error("DSZ:: pushPathByName pageOne ok! data = " + JSON.stringify(data));
                  }).catch((error: BusinessError)=>{
                  console.error( "DSZ:: error.code is ",  typeof error.code)
                  this.result = `${error.code} ${error.message}`
                  console.error(`DSZ:: pushPathByName pageOne failed! error.code = ${error.code}, error.message = ${error.message}` );
                })
              })
              .width("33%")
            Button('pushByNameWithOnPopPageFive')
              .key('pushByNameWithOnPopPageFive')
              .onClick(() => {
                this.pageInfos.pushDestinationByName( 'pageFive',  null , (popInfo: PopInfo) => {})
                  .then((data)=>{
                    this.result = "Success"
                    console.error("DSZ:: pushPathByName pageFive ok! data = " + JSON.stringify(data));
                  }).catch((error: BusinessError)=>{
                  console.error( "DSZ:: error.code is ",  typeof error.code)
                  this.result = `${error.code} ${error.message}`
                  console.error(`DSZ:: pushPathByName pageOne failed! error.code = ${error.code}, error.message = ${error.message}` );
                })
              })
              .width("33%")
            Button('pushByNameWithOnPopPageSix')
              .key('pushByNameWithOnPopPageSix')
              .onClick(() => {
                this.pageInfos.pushDestinationByName( 'pageSix',  null , (popInfo: PopInfo) => {})
                  .then((data)=>{
                    this.result = "Success"
                    console.error("DSZ:: pushPathByName pageSix ok! data = " + JSON.stringify(data));
                  }).catch((error: BusinessError)=>{
                  console.error( "DSZ:: error.code is ",  typeof error.code)
                  this.result = `${error.code} ${error.message}`
                  console.error(`DSZ:: pushPathByName pageOne failed! error.code = ${error.code}, error.message = ${error.message}` );
                })
              })
              .width("33%")
          }
        }
      }.height(450)
    }
  }
}