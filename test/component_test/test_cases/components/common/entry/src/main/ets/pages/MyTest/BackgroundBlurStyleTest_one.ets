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
import {
  assertEqual,
  assertFalse,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function backgroundBlurStyleTest_one() {
  /*
  * Scroll组件 BackgroundBlurStyle属性
  * 找到画面id为scrollBackgroundBlurStyle1，scrollBackgroundBlurStyle2，
  * scrollBackgroundBlurStyle3，scrollBackgroundBlurStyle4，
  * scrollBackgroundBlurStyle5，scrollBackgroundBlurStyle9，
  * scrollBackgroundBlurStyle7 的 scroll 组件
  * 获取scrollBackgroundBlurStyle1的BackgroundBlurStyle属性与期待值 BlurStyle.Thin比对
  * 获取scrollBackgroundBlurStyle1的colorMode的属性与期待值 ThemeColorMode.System比对
  * 获取scrollBackgroundBlurStyle1的adaptiveColor的属性与期待值 AdaptiveColor.Default比对
  * 获取scrollBackgroundBlurStyle1的grayscale[0]的属性与期待值 12比对
  * 获取scrollBackgroundBlurStyle1的grayscale[1]的属性与期待值 103比对
  * 获取scrollBackgroundBlurStyle2的BackgroundBlurStyle属性与期待值 BlurStyle.Regular比对
  * 获取scrollBackgroundBlurStyle2的colorMode的属性与期待值 ThemeColorMode.Light比对
  * 获取scrollBackgroundBlurStyle2的adaptiveColor的属性与期待值 AdaptiveColor.Average比对
  * 获取scrollBackgroundBlurStyle3的BackgroundBlurStyle属性与期待值 BlurStyle.Thick比对
  * 获取scrollBackgroundBlurStyle3的colorMode的属性与期待值 AdaptiveColor.Dark比对
  * 获取scrollBackgroundBlurStyle4的BackgroundBlurStyle属性与期待值 BlurStyle.BACKGROUND_THIN比对
  * 获取scrollBackgroundBlurStyle5的BackgroundBlurStyle属性与期待值 BlurStyle.BACKGROUND_REGULAR比对
  * 获取scrollBackgroundBlurStyle6的BackgroundBlurStyle属性与期待值 BlurStyle.BACKGROUND_THICK比对
  * 获取scrollBackgroundBlurStyle7的BackgroundBlurStyle属性与期待值 BlurStyle.BACKGROUND_ULTRA_THICK比对
  */
  defineTest('backgroundBlurStyleTest_oneDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('backgroundBlurStyleTest_oneDemo running')
    let driver: Tester = Tester.create()
    let scrollBackgroundBlurStyle1: Component =
      await driver.findComponent(Matcher.create().id('scrollBackgroundBlurStyle1').enabled(true))
    let scrollBackgroundBlurStyle2: Component =
      await driver.findComponent(Matcher.create().id('scrollBackgroundBlurStyle2').enabled(true))
    let scrollBackgroundBlurStyle3: Component =
      await driver.findComponent(Matcher.create().id('scrollBackgroundBlurStyle3').enabled(true))
    let scrollBackgroundBlurStyle4: Component =
      await driver.findComponent(Matcher.create().id('scrollBackgroundBlurStyle4').enabled(true))
    let scrollBackgroundBlurStyle5: Component =
      await driver.findComponent(Matcher.create().id('scrollBackgroundBlurStyle5').enabled(true))
    let scrollBackgroundBlurStyle6: Component =
      await driver.findComponent(Matcher.create().id('scrollBackgroundBlurStyle6').enabled(true))
    let scrollBackgroundBlurStyle7: Component =
      await driver.findComponent(Matcher.create().id('scrollBackgroundBlurStyle7').enabled(true))
    let backgroundBlurStyle1: string = await scrollBackgroundBlurStyle1.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle1).$attrs.backgroundBlurStyle.value, 'BlurStyle.Thin')
    assertEqual(JSON.parse(backgroundBlurStyle1)
      .$attrs
      .backgroundBlurStyle
      .options
      .colorMode, 'ThemeColorMode.System')
    assertEqual(JSON.parse(backgroundBlurStyle1)
      .$attrs
      .backgroundBlurStyle
      .options
      .adaptiveColor, 'AdaptiveColor.Default')
    assertFalse(JSON.parse(backgroundBlurStyle1)
      .$attrs
      .backgroundBlurStyle
      .options
      .blurOptions == undefined)
    assertEqual(JSON.parse(backgroundBlurStyle1)
      .$attrs
      .backgroundBlurStyle
      .options
      .blurOptions
      .grayscale[0], 12
    )
    assertEqual(JSON.parse(backgroundBlurStyle1)
      .$attrs
      .backgroundBlurStyle
      .options
      .blurOptions
      .grayscale[1], 103
    )

    let backgroundBlurStyle2: string = await scrollBackgroundBlurStyle2.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle2).$attrs.backgroundBlurStyle.value, 'BlurStyle.Regular')
    assertEqual(JSON.parse(backgroundBlurStyle2)
      .$attrs
      .backgroundBlurStyle
      .options
      .colorMode, 'ThemeColorMode.Light')
    assertEqual(JSON.parse(backgroundBlurStyle2)
      .$attrs
      .backgroundBlurStyle
      .options
      .adaptiveColor, 'AdaptiveColor.Average')

    let backgroundBlurStyle3: string = await scrollBackgroundBlurStyle3.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle3).$attrs.backgroundBlurStyle.value, 'BlurStyle.Thick')
    assertEqual(JSON.parse(backgroundBlurStyle3)
      .$attrs
      .backgroundBlurStyle
      .options
      .colorMode, 'ThemeColorMode.Dark')

    let backgroundBlurStyle4: string = await scrollBackgroundBlurStyle4.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle4).$attrs.backgroundBlurStyle.value, 'BlurStyle.BACKGROUND_THIN')

    let backgroundBlurStyle5: string = await scrollBackgroundBlurStyle5.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle5).$attrs.backgroundBlurStyle.value, 'BlurStyle.BACKGROUND_REGULAR')

    let backgroundBlurStyle6: string = await scrollBackgroundBlurStyle6.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle6).$attrs.backgroundBlurStyle.value, 'BlurStyle.BACKGROUND_THICK')

    let backgroundBlurStyle7: string = await scrollBackgroundBlurStyle7.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle7).$attrs.backgroundBlurStyle.value, 'BlurStyle.BACKGROUND_ULTRA_THICK')
  }, 0)
}