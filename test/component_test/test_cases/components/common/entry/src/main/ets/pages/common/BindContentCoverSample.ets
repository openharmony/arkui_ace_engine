/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

import bindContentCoverTest from '../MyTest/BindContentCoverTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct BindContentCoverSample { //全屏模态转场，必须设置背景
  @State isShow: boolean = false
  @State isShowTwo: boolean = false
  @State isShowThree: boolean = false

  @Builder
  myBuilder3() {
    Column() {
      Button("BindContent1")
        .id('buttonBindContentCover1')
        .margin(10)
        .fontSize(20)
        .onClick(() => {
          this.isShowThree = !this.isShowThree;
        })
    }
    .width('100%')
    .height('100%')
  }

  @Builder
  myBuilder2() {
    Column() {
      Button("BindContent2")
        .id('buttonBindContentCover2')
        .margin(10)
        .fontSize(20)
        .onClick(() => {
          this.isShowTwo = !this.isShowTwo;
        })
    }
    .width('100%')
    .height('100%')
  }

  @Builder
  myBuilder() {
    Column() {
      Button("BindContent3")
        .id('buttonBindContentCover3')
        .margin(10)
        .fontSize(20)
        .onClick(() => {
          this.isShowTwo = !this.isShowTwo;
        })
        .bindContentCover(this.isShowTwo, this.myBuilder2(), {
          modalTransition: ModalTransition.DEFAULT,
          backgroundColor: Color.Pink
        })

      Button("BindContent4")
        .id('buttonBindContentCover4')
        .margin(10)
        .fontSize(20)
        .onClick(() => {
          this.isShowThree = !this.isShowThree;
        })
        .bindContentCover(this.isShowThree, this.myBuilder3(), {
          modalTransition: ModalTransition.ALPHA,
          backgroundColor: Color.Blue
        })

      Button("BindContent5")
        .id('buttonBindContentCover5')
        .margin(10)
        .fontSize(20)
        .onClick(() => {
          this.isShow = !this.isShow;
        })
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
  }

  aboutToAppear(): void {
    loadComponentTestEntry(bindContentCoverTest)
  }

  build() {
    Column() {
      Button("ButtonBindContent6")
        .onClick(() => {
          this.isShow = !this.isShow
        })
        .id('buttonBindContentCover6')
        .fontSize(20)
        .margin(10)
        .bindContentCover(this.isShow, this.myBuilder(), {
          modalTransition: ModalTransition.NONE,
          backgroundColor: Color.Orange
        })
    }
    .justifyContent(FlexAlign.Center)
    .backgroundColor("#ff49c8ab")
    .width('100%')
    .height('100%')
  }
}

