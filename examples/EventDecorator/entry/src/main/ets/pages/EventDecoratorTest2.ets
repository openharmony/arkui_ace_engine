/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
// [Start EventDecoratorTest2]
import { hilog } from '@kit.PerformanceAnalysisKit';
const TAG = '[Sample_EventDecorator]';
const DOMAIN = 0xF811;
@ComponentV2
struct Child2 {
  @Param index: number = 0;
  @Event changeIndex: (val: number) => void;

  build() {
    Column() {
      Text(`Child index: ${this.index}`)
        .fontSize(20)
        .margin(10)
        .onClick(() => {
          this.changeIndex(20);
          // 输出子组件this.index，验证调用@Event后值不会立即同步回子组件
          hilog.info(DOMAIN, TAG, `after changeIndex ${this.index}`);
        })
    }
    .width('100%')
  }
}
@Entry
@ComponentV2
struct Index2 {
  @Local index: number = 0;

  build() {
    Column() {
      Child2({
        index: this.index,
        changeIndex: (val: number) => {
          this.index = val;
          // 输出父组件的index，用于对比子组件侧日志
          hilog.info(DOMAIN, TAG, `in changeIndex ${this.index}`);
        }
      })
    }
    .width('100%')
  }
}
// [End EventDecoratorTest2]