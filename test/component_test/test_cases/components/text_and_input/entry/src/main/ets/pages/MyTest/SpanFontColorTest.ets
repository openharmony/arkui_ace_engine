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

export default async function spanFontColorTest() {
  /*
   * Span组件 FontColor属性
   * 找到画面id为spanFontColor1,spanFontColor2的Span组件
   * 找到画面文本为SpanFontColor1,SpanFontColor2的Button组件
   * 获取span1的FontColor属性与期待值Color.Blue比对
   * 获取span2的FontColor属性与期待值0x0000FF比对
   * 点击button1，变更span2的FontColor属性值为'rgb(255, 100, 255)'
   * 获取span2的FontColor属性与期待值'rgb(255, 100, 255)'比对
   * 点击button2，变更span2的FontColor属性值为$r('sys.color.ohos_id_color_text_hyperlink')
   * 获取span2的FontColor属性与期待值$r('sys.color.ohos_id_color_text_hyperlink')比对
   */
  defineTest('spanFontColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("spanFontColorTestDemo running")
    let driver: Tester = Tester.create()
    let span1: Component = await driver.findComponent(Matcher.create().id('spanFontColor1').enabled(true))
    let span2: Component = await driver.findComponent(Matcher.create().id('spanFontColor2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('SpanFontColor1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('SpanFontColor2').enabled(true))

    assertFalse(span1 == null)
    let fontColor1: string = await span1.getInspectorInfo()
    assertEqual(JSON.parse(fontColor1).$attrs.fontColor, Color.Blue)
    let fontColor2: string = await span2.getInspectorInfo()
    assertEqual(JSON.parse(fontColor2).$attrs.fontColor, 0x0000FF)

    await button1.tap()
    let fontColor3: string = await span2.getInspectorInfo()
    assertEqual(JSON.parse(fontColor3).$attrs.fontColor, 'rgb(255, 100, 255)')
    await button2.tap()
    let fontColor4: string = await span2.getInspectorInfo()
    assertEqual(JSON.parse(fontColor4).$attrs.fontColor, $r('sys.color.ohos_id_color_text_hyperlink'))
  }, 0)
}