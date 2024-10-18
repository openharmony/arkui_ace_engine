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
import columnJustifyContentTest from '../MyTest/ColumnJustifyContentTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ColumnJustifyContentSample {
  @State columnJustifyContent: FlexAlign = FlexAlign.SpaceAround

  aboutToAppear(): void {
    loadComponentTestEntry(columnJustifyContentTest)
  }

  build() {
    Column({ space: 5 }) {
      Column() {
        Column().width('90%').height(10).backgroundColor(0xAFEEEE)
        Column().width('90%').height(10).backgroundColor(0x00FFFF)
      }.id('columnJustifyContent1').height(50).border({ width: 1 }).justifyContent(FlexAlign.Start)

      Column() {
        Column().width('90%').height(10).backgroundColor(0xAFEEEE)
        Column().width('90%').height(10).backgroundColor(0x00FFFF)
      }.id('columnJustifyContent2').height(50).border({ width: 1 }).justifyContent(FlexAlign.Center)

      Column() {
        Column().width('90%').height(10).backgroundColor(0xAFEEEE)
        Column().width('90%').height(10).backgroundColor(0x00FFFF)
      }.id('columnJustifyContent3').height(50).border({ width: 1 }).justifyContent(FlexAlign.End)

      Column() {
        Column().width('90%').height(10).backgroundColor(0xAFEEEE)
        Column().width('90%').height(10).backgroundColor(0x00FFFF)
        Column().width('90%').height(10).backgroundColor(0x00FFFF)
      }.id('columnJustifyContent4').height(80).border({ width: 1 }).justifyContent(FlexAlign.SpaceBetween)

      Column() {
        Column().width('90%').height(10).backgroundColor(0xAFEEEE)
        Column().width('90%').height(10).backgroundColor(0x00FFFF)
        Column().width('90%').height(10).backgroundColor(0x00FFFF)
      }.id('columnJustifyContent5').height(80).border({ width: 1 }).justifyContent(this.columnJustifyContent)

      Button('ColumnJustifyContent').onClick(() => {
        this.columnJustifyContent = FlexAlign.SpaceEvenly
      })
    }
  }
}