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
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function progressStyleCapsuleStyleOptionsTest() {
  /*
* Progress组件 Style属性
* 找到画面id为progressStyleCapsuleStyleOptions的Progress组件
* 找到画面文本为ProgressStyleCapsuleStyleOptions1,ProgressStyleCapsuleStyleOptions2,ProgressStyleCapsuleStyleOptions3组件
* 获取progress的Style.CapsuleStyleOptions属性与期待值{ borderColor: 0x0000ff, borderWidth: '10px', content: 'hello', font: { size: '5px', weight: FontWeight.Lighter, family: $rawfile('TESTFONT.TTF'),
* style: FontStyle.Italic }, fontColor: 0x666666, enableScanEffect: false, enableSmoothEffect: true, showDefaultPercentage: true比对
* 点击button1，变更progress的Style.CapsuleStyleOptions属性值为{ borderColor: 0x0000ff, borderWidth: '10px', content: 'hello', font: { size: '5px', weight: FontWeight.Lighter, family: $rawfile('TESTFONT.TTF'),
*  style: FontStyle.Italic }, fontColor: 0x666666, enableScanEffect: false, enableSmoothEffect: true, showDefaultPercentage: true}
* 获取progress的Style.CapsuleStyleOptions属性与期待值0x0000ff比对
* 获取progress的Style.CapsuleStyleOptions属性与期待值{ borderColor: 0x0000ff, borderWidth: '10px', content: 'hello', font: { size: '5px', weight: FontWeight.Lighter, family: $rawfile('TESTFONT.TTF'),
*  style: FontStyle.Italic }, fontColor: 0x666666, enableScanEffect: false, enableSmoothEffect: true, showDefaultPercentage: true}比对
* 点击button2，变更progress的Style.CapsuleStyleOptions属性值为{ borderColor: '#0000ff', borderWidth: $r('app.integer.borderWidth_Length'), content :'test', font: { size: $r('app.integer.fontSize_Progress'), weight: '5px', family: 'Arial', style: FontStyle.Italic },
*  fontColor: '#fff888', enableScanEffect: false, enableSmoothEffect: false, showDefaultPercentage: true}
* 获取progress的Style.CapsuleStyleOptions属性与期待值{ borderColor: '#0000ff', borderWidth: $r('app.integer.borderWidth_Length'), content :'test', font: { size: $r('app.integer.fontSize_Progress'), weight: '5px', family: 'Arial', style: FontStyle.Italic },
*  fontColor: '#fff888', enableScanEffect: false, enableSmoothEffect: false, showDefaultPercentage: true}比对
* 点击button3，变更progress的Style.CapsuleStyleOptions属性值为{ borderColor: $r('app.color.borderColor'), borderWidth: 10, font: { size: 5, weight: 500, family: 'Arial', style: FontStyle.Italic },
*  fontColor: Color.Pink, enableScanEffect: true, enableSmoothEffect: true, showDefaultPercentage: false}
* 获取progress的Style.CapsuleStyleOptions属性与期待值{ borderColor: $r('app.color.borderColor'), borderWidth: 10, font: { size: 5, weight: 500, family: 'Arial', style: FontStyle.Italic },
*  fontColor: Color.Pink, enableScanEffect: true, enableSmoothEffect: true, showDefaultPercentage: false}比对
*/
  defineTest('progressStyleCapsuleStyleOptionsTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("progressStyleCapsuleStyleOptionsTestDemo running")
    let driver: Tester = Tester.create()
    let progress: Component =
      await driver.findComponent(Matcher.create().id('progressStyleCapsuleStyleOptions').enabled(true))
    let button1: Component =
      await driver.findComponent(Matcher.create().text('ProgressStyleCapsuleStyleOptions1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('ProgressStyleCapsuleStyleOptions2').enabled(true))
    let button3: Component =
      await driver.findComponent(Matcher.create().text('ProgressStyleCapsuleStyleOptions3').enabled(true))
    let styleCapsuleStyleOptions1: string = await progress.getInspectorInfo()
    assertEqual(JSON.parse(styleCapsuleStyleOptions1)
      .$attrs
      .capsuleStyle
      .borderColor
      .toLowerCase(), Color.Green)
    assertEqual(JSON.parse(styleCapsuleStyleOptions1)
      .$attrs
      .capsuleStyle
      .borderWidth, '10.00vp')
    assertEqual(JSON.parse(styleCapsuleStyleOptions1)
      .$attrs
      .capsuleStyle
      .content, 'hello')
    assertEqual(JSON.parse(styleCapsuleStyleOptions1)
      .$attrs
      .capsuleStyle
      .font
      .size, '5.00fp')
    assertEqual(JSON.parse(styleCapsuleStyleOptions1)
      .$attrs
      .capsuleStyle
      .font
      .weight, '300')
    assertEqual(JSON.parse(styleCapsuleStyleOptions1)
      .$attrs
      .capsuleStyle
      .font
      .family, 'Arial')
    assertEqual(JSON.parse(styleCapsuleStyleOptions1)
      .$attrs
      .capsuleStyle
      .font
      .style, 'FontStyle.Normal')
    assertEqual(JSON.parse(styleCapsuleStyleOptions1)
      .$attrs
      .capsuleStyle
      .fontColor
      .toLowerCase(), Color.Orange)
    assertFalse(JSON.parse(styleCapsuleStyleOptions1)
      .$attrs
      .capsuleStyle
      .enableScanEffect)
    assertFalse(JSON.parse(styleCapsuleStyleOptions1)
      .$attrs
      .capsuleStyle
      .enableSmoothEffect == undefined)
    assertTrue(JSON.parse(styleCapsuleStyleOptions1)
      .$attrs
      .capsuleStyle
      .enableSmoothEffect)
    assertTrue(JSON.parse(styleCapsuleStyleOptions1)
      .$attrs
      .capsuleStyle
      .showDefaultPercentage)

    await button1.tap()
    let styleCapsuleStyleOptions2: string = await progress.getInspectorInfo()
    assertEqual(JSON.parse(styleCapsuleStyleOptions2)
      .$attrs
      .capsuleStyle
      .borderColor, '#FF0000FF')
    assertEqual(JSON.parse(styleCapsuleStyleOptions2)
      .$attrs
      .capsuleStyle
      .borderWidth, '10.00px')
    assertEqual(JSON.parse(styleCapsuleStyleOptions2)
      .$attrs
      .capsuleStyle
      .content, 'hello')
    assertEqual(JSON.parse(styleCapsuleStyleOptions2)
      .$attrs
      .capsuleStyle
      .font
      .size, '5.00px')
    assertEqual(JSON.parse(styleCapsuleStyleOptions2)
      .$attrs
      .capsuleStyle
      .font
      .weight, 'FontWeight.Lighter')
    assertEqual(JSON.parse(styleCapsuleStyleOptions2)
      .$attrs
      .capsuleStyle
      .font
      .family, $rawfile('TESTFONT.TTF'))
    assertEqual(JSON.parse(styleCapsuleStyleOptions2)
      .$attrs
      .capsuleStyle
      .font
      .style, 'FontStyle.Italic')
    assertEqual(JSON.parse(styleCapsuleStyleOptions2)
      .$attrs
      .capsuleStyle
      .fontColor, '#FF666666')
    assertFalse(JSON.parse(styleCapsuleStyleOptions2)
      .$attrs
      .capsuleStyle
      .enableScanEffect)
    assertTrue(JSON.parse(styleCapsuleStyleOptions2)
      .$attrs
      .capsuleStyle
      .enableSmoothEffect)
    assertTrue(JSON.parse(styleCapsuleStyleOptions2)
      .$attrs
      .capsuleStyle
      .showDefaultPercentage)
    await button2.tap()
    let styleCapsuleStyleOptions3: string = await progress.getInspectorInfo()
    assertEqual(JSON.parse(styleCapsuleStyleOptions3)
      .$attrs
      .capsuleStyle
      .borderColor, '#FF0000FF')
    assertEqual(JSON.parse(styleCapsuleStyleOptions3)
      .$attrs
      .capsuleStyle
      .borderWidth, $r("app.string.border_width_length"))
    assertEqual(JSON.parse(styleCapsuleStyleOptions3)
      .$attrs
      .capsuleStyle
      .content, 'test')
    assertEqual(JSON.parse(styleCapsuleStyleOptions3)
      .$attrs
      .capsuleStyle
      .font
      .size, $r("app.string.font_size_progress"))
    assertEqual(JSON.parse(styleCapsuleStyleOptions3)
      .$attrs
      .capsuleStyle
      .font
      .family, 'Arial')
    assertEqual(JSON.parse(styleCapsuleStyleOptions3)
      .$attrs
      .capsuleStyle
      .font
      .style, 'FontStyle.Italic')
    assertEqual(JSON.parse(styleCapsuleStyleOptions3)
      .$attrs
      .capsuleStyle
      .fontColor, '#FFFFF888')
    assertFalse(JSON.parse(styleCapsuleStyleOptions3)
      .$attrs
      .capsuleStyle
      .enableScanEffect)
    assertFalse(JSON.parse(styleCapsuleStyleOptions3)
      .$attrs
      .capsuleStyle
      .enableSmoothEffect)
    assertTrue(JSON.parse(styleCapsuleStyleOptions3)
      .$attrs
      .capsuleStyle
      .showDefaultPercentage)
    await button3.tap()
    let styleCapsuleStyleOptions4: string = await progress.getInspectorInfo()
    assertEqual(JSON.parse(styleCapsuleStyleOptions4)
      .$attrs
      .capsuleStyle
      .borderColor, $r('app.color.borderColor'))
    assertEqual(JSON.parse(styleCapsuleStyleOptions4)
      .$attrs
      .capsuleStyle
      .borderWidth, '10.00vp')
    assertEqual(JSON.parse(styleCapsuleStyleOptions4)
      .$attrs
      .capsuleStyle
      .font
      .size, '5.00fp')
    assertEqual(JSON.parse(styleCapsuleStyleOptions4)
      .$attrs
      .capsuleStyle
      .font
      .weight, '500')
    assertEqual(JSON.parse(styleCapsuleStyleOptions4)
      .$attrs
      .capsuleStyle
      .font
      .family, 'Arial')
    assertEqual(JSON.parse(styleCapsuleStyleOptions4)
      .$attrs
      .capsuleStyle
      .font
      .style, 'FontStyle.Italic')
    assertEqual(JSON.parse(styleCapsuleStyleOptions4)
      .$attrs
      .capsuleStyle
      .fontColor
      .toLowerCase(), Color.Pink)
    assertTrue(JSON.parse(styleCapsuleStyleOptions4)
      .$attrs
      .capsuleStyle
      .enableScanEffect)
    assertTrue(JSON.parse(styleCapsuleStyleOptions4)
      .$attrs
      .capsuleStyle
      .enableSmoothEffect)
    assertFalse(JSON.parse(styleCapsuleStyleOptions4)
      .$attrs
      .capsuleStyle
      .showDefaultPercentage)
  }, 0)
}