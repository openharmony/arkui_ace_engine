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
// 测试代码路径
import rowJustifyContentTest from '../MyTest/RowJustifyContentTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct RowJustifyContentSample {
  @State rowJustifyContent: FlexAlign = FlexAlign.SpaceAround

  aboutToAppear(): void {
    loadComponentTestEntry(rowJustifyContentTest)
  }

  build() {
    Column({ space: 5 }) {
      Row() {
        Row().width('30%').height(50).backgroundColor(0xAFEEEE)
        Row().width('30%').height(50).backgroundColor(0x00FFFF)
      }.id('rowJustifyContent1').width('90%').border({ width: 1 }).justifyContent(FlexAlign.Start)

      Row() {
        Row().width('30%').height(50).backgroundColor(0xAFEEEE)
        Row().width('30%').height(50).backgroundColor(0x00FFFF)
      }.id('rowJustifyContent2').width('90%').border({ width: 1 }).justifyContent(FlexAlign.Center)

      Row() {
        Row().width('30%').height(50).backgroundColor(0xAFEEEE)
        Row().width('30%').height(50).backgroundColor(0x00FFFF)
      }.id('rowJustifyContent3').width('90%').border({ width: 1 }).justifyContent(FlexAlign.End)

      Row() {
        Row().width('30%').height(50).backgroundColor(0xAFEEEE)
        Row().width('30%').height(50).backgroundColor(0x00FFFF)
        Row().width('30%').height(50).backgroundColor(0x00FFFF)
      }.id('rowJustifyContent4').width('90%').border({ width: 1 }).justifyContent(FlexAlign.SpaceBetween)

      Row() {
        Row().width('30%').height(50).backgroundColor(0xAFEEEE)
        Row().width('30%').height(50).backgroundColor(0x00FFFF)
        Row().width('30%').height(50).backgroundColor(0x00FFFF)
      }.id('rowJustifyContent5').width('90%').border({ width: 1 }).justifyContent(this.rowJustifyContent)

      Button('RowJustifyContent').onClick(() => {
        this.rowJustifyContent = FlexAlign.SpaceEvenly
      })
    }
  }
}