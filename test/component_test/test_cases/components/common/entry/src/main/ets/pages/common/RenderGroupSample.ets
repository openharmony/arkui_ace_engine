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

import renderGroupTest from '../MyTest/RenderGroupTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Component
struct RenderGroup {
  @Prop renderGroupValue: boolean;

  build() {
    Row() {
      Row() {
        Button()
      }
      .width(150)
      .height(150)
      .justifyContent(FlexAlign.Center)
      .opacity(0.6)
      .renderGroup(this.renderGroupValue)
      .id('rowRenderGroup1')
    }
    .backgroundColor(Color.Pink)
    .width(200)
    .height(200)
    .justifyContent(FlexAlign.Center)
    .opacity(1)
  }
}

@Entry
@Component
struct RenderGroupSample {
  @State boolean: boolean = true

  aboutToAppear(): void {
    loadComponentTestEntry(renderGroupTest)
  }

  build() {
    Column() {
      RenderGroup({ renderGroupValue: this.boolean })
        .margin(20)
      Button('ButtonRenderGroup1')
        .onClick(() => {
          this.boolean = !this.boolean
        })
    }
    .width("100%")
    .height("100%")
    .alignItems(HorizontalAlign.Center)
  }
}
