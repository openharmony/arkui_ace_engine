/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import router from '@ohos.router';
export class TestListOption {
  title: string = ''
  url: string= ''
  key: string= ''
}
const testList:TestListOption[] = [
  { title: 'animation', url: 'pages/animation', key:'animation' },
  { title: 'animateTo', url: 'pages/animateTo', key:'animateTo' },
  { title: 'keyframeAnimateTo', url: 'pages/keyframeAnimateTo', key:'keyframeAnimateTo' },
  { title: 'pageTransition', url: 'pages/pageTransition', key:'pageTransition' },
  { title: 'transition', url: 'pages/transition', key:'transition' },
  { title: 'sharedTransition', url: 'pages/sharedTransition/sharedTransition1', key:'sharedTransition' },
  { title: 'geometryTransition', url: 'pages/geometryTransition', key:'geometryTransition' },
  { title: 'motionPath', url: 'pages/motionPath', key:'motionPath' },
  { title: 'Particle', url: 'pages/Particle', key:'Particle' },
  { title: 'animateToImmediately', url: 'pages/animateToImmediately', key:'animateToImmediately' },
  { title: '视效', url: 'pages/Common/Home', key:'Common' },
  { title: 'animtor', url: 'pages/animator', key:'animator' },
]

@Entry
@Component
struct Index {
  scroll: Scroller = new Scroller()

  build() {
    Column() {
      Scroll(this.scroll) {
        Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Center, justifyContent: FlexAlign.Center }) {
          ForEach(testList, (item:TestListOption) => {
            Button(item.title)
              .width(300)
              .height(50)
              .margin(10)
              .padding({ top: 5, bottom: 5 })
              .onClick(() => {
                router.pushUrl({ url: item.url }, router.RouterMode.Single)
              })
          }, (item:TestListOption) => item.title)
        }
        .width('100%')
      }

    }
  }
}