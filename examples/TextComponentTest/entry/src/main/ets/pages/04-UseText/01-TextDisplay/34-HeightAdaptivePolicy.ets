/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

@Entry
@Component
struct heightAdaptivePolicy {
  @State message: string = '混合Hello World! 多行文本 中英文数字混合 1282378283 ~';
  @State fontSize: number = 25;

  build() {
    Column({ space: 10 }) {
      Text(this.message)
        .id('HelloWorld')
        .fontSize(this.fontSize)
        .textOverflow({ overflow: TextOverflow.Ellipsis})
        .border({ width: 1})
        .heightAdaptivePolicy(TextHeightAdaptivePolicy.LAYOUT_CONSTRAINT_FIRST) // 调整自适应布局策略
        .width(300)
        .height(200)
      Row(){
        Button('fontSize+5')
          .onClick(()=>{
            this.fontSize += 5;
          })
        Button('fontSize-5')
          .onClick(()=>{
            this.fontSize -= 5;
          })
      }
    }
    .margin({left: 30, top: 50})
  }
}