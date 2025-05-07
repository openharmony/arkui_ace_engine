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

@Builder
export function SliderNormalBuilder(name: string, param: Object) {
  SliderNormalExample()
}

@Component
struct SliderNormalExample {
  pathStack: NavPathStack = new NavPathStack()
  @State logStr: string = ''

  build() {
    NavDestination() {
      Flex({ direction: FlexDirection.Column }) {

        Text('点击轨道只会发送Begin跟End,即 0 2')
          .margin({ top: 100 })

        Slider({ min: 0, max: 5, value: 2 })
          .sliderInteractionMode(SliderInteraction.SLIDE_ONLY)
          .width(300)
          .margin({ top: 100 })
          .onChange((value: number, mode: SliderChangeMode) => {
            this.logStr += mode + ','
          })

        Text(this.logStr)
      }
    }
    .title('SliderNormal')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}

export { SliderNormalExample };