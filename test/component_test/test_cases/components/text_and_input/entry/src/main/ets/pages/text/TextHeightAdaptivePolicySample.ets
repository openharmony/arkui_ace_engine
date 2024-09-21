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
import textHeightAdaptivePolicyTest from '../MyTest/TextHeightAdaptivePolicyTest'

@Entry
@Component
struct TextHeightAdaptivePolicySample {
  @State heightAdaptivePolicyValue: TextHeightAdaptivePolicy = TextHeightAdaptivePolicy.MAX_LINES_FIRST

  aboutToAppear(): void {
    loadComponentTestEntry(textHeightAdaptivePolicyTest)
  }

  build() {
    Column() {
      Text('text text text text text text text text text text text text text text text text text text text text text text')
        .width('80%')
        .height(90)
        .borderWidth(1)
        .minFontSize(10)
        .maxFontSize(30)
        .maxLines(3)
        .textOverflow({ overflow: TextOverflow.Ellipsis })
        .heightAdaptivePolicy(TextHeightAdaptivePolicy.LAYOUT_CONSTRAINT_FIRST)
        .id('textHeightAdaptivePolicy1')
      Text('text text text text text text text text text text text text text text text text text text text text text text')
        .width('80%')
        .height(90)
        .borderWidth(1)
        .minFontSize(10)
        .maxFontSize(30)
        .maxLines(3)
        .textOverflow({ overflow: TextOverflow.Ellipsis })
        .heightAdaptivePolicy(this.heightAdaptivePolicyValue)
        .id('textHeightAdaptivePolicy2')
      Button('TextHeightAdaptivePolicy')
        .onClick(() => {
          this.heightAdaptivePolicyValue = TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST
        })
    }
  }
}