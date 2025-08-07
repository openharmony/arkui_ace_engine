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

@Preview
@Component
export struct MyComponent {
  title: string = 'test'
  func: () => void = () => {}

  @Styles pressedStyle(){
    .backgroundColor(0x238E23)
  }

  @Styles normalStyles() {
    .backgroundColor(0x0000ff)
  }

  build() {
    Text(this.title)
      .key(this.title)
      .fontSize(20)
      .backgroundColor(0x0000ff)
      .fontColor(0xffffff)
      .padding(5)
      .onClick(this.func)
      .stateStyles({pressed: this.pressedStyle, normal: this.normalStyles})
  }
}