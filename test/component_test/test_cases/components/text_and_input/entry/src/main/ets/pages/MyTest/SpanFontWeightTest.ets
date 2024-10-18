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
} from '@ohos.arkui.componentTest';

export default async function spanFontWeightTest() {
  /*
   * Span组件 FontWeight属性
   * 找到画面id为spanFontWeight1,spanFontWeight2,spanFontWeight3,spanFontWeight4的Span组件
   * 找到画面文本为SpanFontWeight的Button组件
   * 获取span1的FontWeight属性Font.weight与期待值FontWeight.Regular比对
   * 点击button，变更span1的FontWeight属性Font.weight值为FontWeight.Bold
   * 获取span1的FontWeight属性Font.weight与期待值FontWeight.Bold比对
   * 点击button，变更span1的FontWeight属性Font.weight值为FontWeight.Medium
   * 获取span1的FontWeight属性Font.weight与期待值FontWeight.Medium比对
   * 点击button，变更span1的FontWeight属性Font.weight值为FontWeight.Bolder
   * 获取span1的FontWeight属性Font.weight与期待值FontWeight.Bolder比对
   * 点击button，变更span1的FontWeight属性Font.weight值为100
   * 获取span1的FontWeight属性Font.weight与期待值100比对
   * 获取span2的FontWeight属性FontWeight.weight与期待值FontWeight.Lighter比对
   * 获取span3的FontWeight属性Font.weight与期待值FontWeight.Normal比对
   * 获取span4的FontWeight属性Font.weight与期待值"600"比对
   */
  defineTest('spanFontWeightTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("spanFontWeightTestDemo running")
    let driver: Tester = Tester.create()
    let span1: Component = await driver.findComponent(Matcher.create().id('spanFontWeight1').enabled(true))
    let span2: Component = await driver.findComponent(Matcher.create().id('spanFontWeight2').enabled(true))
    let span3: Component = await driver.findComponent(Matcher.create().id('spanFontWeight3').enabled(true))
    let span4: Component = await driver.findComponent(Matcher.create().id('spanFontWeight4').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('SpanFontWeight').enabled(true))

    assertFalse(span1 == null)
    let fontWeight1: string = await span1.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight1).$attrs.fontWeight, FontWeight.Regular)
    let fontWeight2: string = await span2.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight2).$attrs.fontWeight, FontWeight.Lighter)
    let fontWeight3: string = await span3.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight3).$attrs.fontWeight, FontWeight.Normal)
    let fontWeight4: string = await span4.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight4).$attrs.fontWeight, "600")

    await button.tap()
    let fontWeight5: string = await span1.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight5).$attrs.fontWeight, FontWeight.Bold)
    await button.tap()
    let fontWeight6: string = await span1.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight6).$attrs.fontWeight, FontWeight.Medium)
    await button.tap()
    let fontWeight7: string = await span1.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight7).$attrs.fontWeight, FontWeight.Bolder)
    await button.tap()
    let fontWeight8: string = await span1.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight8).$attrs.fontWeight, 100)
  }, 0)
}