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
import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest'

export default async function backgroundBlurStyleTest_two() {
  /*
  * Scroll组件 BackgroundBlurStyle属性
  * 找到画面id为scrollBackgroundBlurStyle9，scrollBackgroundBlurStyle10
  * scrollBackgroundBlurStyle11,scrollBackgroundBlurStyle12,
  * scrollBackgroundBlurStyle13的Scroll组件
  * 获取scrollBackgroundBlurStyle9的BackgroundBlurStyle属性与期待值 BlurStyle.COMPONENT_ULTRA_THIN比对
  * 获取scrollBackgroundBlurStyle10的BackgroundBlurStyle属性与期待值 BlurStyle.COMPONENT_THIN比对
  * 获取scrollBackgroundBlurStyle11的BackgroundBlurStyle属性与期待值 BlurStyle.COMPONENT_REGULAR比对
  * 获取scrollBackgroundBlurStyle12的BackgroundBlurStyle属性与期待值 BlurStyle.COMPONENT_THICK比对
  * 获取scrollBackgroundBlurStyle13的BackgroundBlurStyle属性与期待值 BlurStyle.COMPONENT_ULTRA_THICK比对
  */
  defineTest('backgroundBlurStyleTest_twoDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('backgroundBlurStyleTest_twoDemo running')
    let driver: Tester = Tester.create()
    let scrollBackgroundBlurStyle9: Component =
      await driver.findComponent(Matcher.create().id('scrollBackgroundBlurStyle9').enabled(true))
    let scrollBackgroundBlurStyle10: Component =
      await driver.findComponent(Matcher.create().id('scrollBackgroundBlurStyle10').enabled(true))
    let scrollBackgroundBlurStyle11: Component =
      await driver.findComponent(Matcher.create().id('scrollBackgroundBlurStyle11').enabled(true))
    let scrollBackgroundBlurStyle12: Component =
      await driver.findComponent(Matcher.create().id('scrollBackgroundBlurStyle12').enabled(true))
    let scrollBackgroundBlurStyle13: Component =
      await driver.findComponent(Matcher.create().id('scrollBackgroundBlurStyle13').enabled(true))

    let backgroundBlurStyle9: string = await scrollBackgroundBlurStyle9.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle9).$attrs.backgroundBlurStyle.value, 'BlurStyle.COMPONENT_ULTRA_THIN')

    let backgroundBlurStyle10: string = await scrollBackgroundBlurStyle10.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle10).$attrs.backgroundBlurStyle.value, 'BlurStyle.COMPONENT_THIN')

    let backgroundBlurStyle11: string = await scrollBackgroundBlurStyle11.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle11).$attrs.backgroundBlurStyle.value, 'BlurStyle.COMPONENT_REGULAR')

    let backgroundBlurStyle12: string = await scrollBackgroundBlurStyle12.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle12).$attrs.backgroundBlurStyle.value, 'BlurStyle.COMPONENT_THICK')

    let backgroundBlurStyle13: string = await scrollBackgroundBlurStyle13.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle13).$attrs.backgroundBlurStyle.value, 'BlurStyle.COMPONENT_ULTRA_THICK')
  }, 0)
}