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
//测试代码路径
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'
import textTextOverflowTest from '../MyTest/TextTextOverflowTest'

@Entry
@Component
struct TextTextOverflowSample {
  @State textOverFlowValue: TextOverflow = TextOverflow.Ellipsis

  aboutToAppear(): void {
    loadComponentTestEntry(textTextOverflowTest)
  }

  build() {
    Column() {
      Text('This is the setting of textOverflow to Clip text content This is the setting of textOverflow to None text content. This is the setting of textOverflow to Clip text content This is the setting of textOverflow to None text content.')
        .textOverflow({ overflow: TextOverflow.None })
        .id('textTextOverflow1')
      Text('This is the setting of textOverflow to Clip text content This is the setting of textOverflow to None text content. This is the setting of textOverflow to Clip text content This is the setting of textOverflow to None text content.')
        .textOverflow({ overflow: TextOverflow.Clip })
        .id('textTextOverflow2')
      Text('This is the setting of textOverflow to Clip text content This is the setting of textOverflow to None text content. This is the setting of textOverflow to Clip text content This is the setting of textOverflow to None text content.')
        .textOverflow({ overflow: this.textOverFlowValue })
        .id('textTextOverflow3')
      Button('TextTextOverflow')
        .onClick(() => {
          this.textOverFlowValue = TextOverflow.MARQUEE
        })
    }.height(300).width(335).padding({ left: 35, right: 35, top: 35 })
  }
}