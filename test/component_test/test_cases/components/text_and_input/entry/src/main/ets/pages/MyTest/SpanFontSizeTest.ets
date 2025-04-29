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

export default async function spanFontSizeTest() {
  /*
   * Span组件 FontSize属性
   * 找到画面id为spanFontSize1的Span组件
   * 找到画面文本为SpanFontSize1,SpanFontSize2的Button组件
   * 获取span的FontSize属性与期待值'50px'比对
   * 点击button1，变更span的FontSize属性值为50
   * 获取span的FontSize属性与期待值50比对
   * 点击button2，变更span的FontSize属性值为$r('app.string.length')
   * 获取span的FontSize属性与期待值$r('app.string.length')比对
   */
  defineTest('spanFontSizeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("spanFontSizeTestDemo running")
    let driver: Tester = Tester.create()
    let span: Component = await driver.findComponent(Matcher.create().id('spanFontSize1').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('SpanFontSize1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('SpanFontSize2').enabled(true))

    assertFalse(span == null)
    let fontSize1: string = await span.getInspectorInfo()
    assertEqual(JSON.parse(fontSize1).$attrs.fontSize, '50px')

    await button1.tap()
    let fontSize2: string = await span.getInspectorInfo()
    assertEqual(JSON.parse(fontSize2).$attrs.fontSize, 50)
    await button2.tap()
    let fontSize3: string = await span.getInspectorInfo()
    assertEqual(JSON.parse(fontSize3).$attrs.fontSize, $r('app.string.length'))
  }, 0)
}