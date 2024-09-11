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

export default async function spanFontTest() {
  /*
   * Span组件 Font属性
   * 找到画面id为spanFont1,spanFont2,spanFont3,spanFont4的Span组件
   * 找到画面文本为SpanFont1,SpanFont2的Button组件
   * 获取span1的Font属性Font.size与期待值30比对
   * 获取span1的Font属性Font.weight与期待值FontWeight.Lighter比对
   * 获取span1的Font属性Font.family与期待值'Arial'比对
   * 获取span1的Font属性Font.style与期待值FontStyle.Normal比对
   * 点击button1，变更span1的Font属性Font.size值为'30px'
   * 变更span1的Font属性Font.weight值为FontWeight.Regular
   * 变更span1的Font属性Font.family值为'TESTFONTRawFile'
   * 变更span1的Font属性Font.style值为FontStyle.Italic
   * 获取span1的Font属性Font.size与期待值'30px'比对
   * 获取span1的Font属性Font.weight与期待值FontWeight.Regular比对
   * 获取span1的Font属性Font.family与期待值'TESTFONTRawFile'比对
   * 获取span1的Font属性Font.style与期待值FontStyle.Italic比对
   * 获取span2的Font属性Font.size与期待值$r('app.string.length')比对
   * 获取span2的Font属性Font.weight与期待值FontWeight.Bolder比对
   * 获取span3的Font属性Font.weight与期待值"500"比对
   * 获取span4的Font属性Font.weight与期待值FontWeight.Normal比对
   * 点击button2，变更span4的Font属性Font.weight值为FontWeight.Regular
   * 获取span4的Font属性Font.weight与期待值FontWeight.Regular比对
   * 点击button2，变更span4的Font属性Font.weight值为FontWeight.Medium
   * 获取span4的Font属性Font.weight与期待值FontWeight.Medium比对
   * 点击button2，变更span4的Font属性Font.weight值为FontWeight.Bold
   * 获取span4的Font属性Font.weight与期待值FontWeight.Bold比对
   * 点击button2，变更span4的Font属性Font.weight值为30
   * 获取span4的Font属性Font.weight与期待值30比对
   */
  defineTest('spanFontTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("spanFontTestDemo running")
    let driver: Tester = Tester.create()
    let span1: Component = await driver.findComponent(Matcher.create().id('spanFont1').enabled(true))
    let span2: Component = await driver.findComponent(Matcher.create().id('spanFont2').enabled(true))
    let span3: Component = await driver.findComponent(Matcher.create().id('spanFont3').enabled(true))
    let span4: Component = await driver.findComponent(Matcher.create().id('spanFont4').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('SpanFont1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('SpanFont2').enabled(true))

    assertFalse(span1 == null)
    let font1: string = await span1.getInspectorInfo()
    assertEqual(JSON.parse(font1).$attrs.font.family, 'Arial')
    assertEqual(JSON.parse(font1).$attrs.font.size, 30)
    assertEqual(JSON.parse(font1).$attrs.font.weight, FontWeight.Lighter)
    assertEqual(JSON.parse(font1).$attrs.font.style, FontStyle.Normal)
    let font2: string = await span2.getInspectorInfo()
    assertEqual(JSON.parse(font2).$attrs.font.size, $r('app.string.length'))
    assertEqual(JSON.parse(font2).$attrs.font.weight, FontWeight.Bolder)
    let font3: string = await span3.getInspectorInfo()
    assertEqual(JSON.parse(font3).$attrs.font.weight, "500")
    let font4: string = await span4.getInspectorInfo()
    assertEqual(JSON.parse(font4).$attrs.font.weight, FontWeight.Normal)

    await button1.tap()
    let font5: string = await span1.getInspectorInfo()
    assertEqual(JSON.parse(font5).$attrs.font.family, 'TESTFONTRawFile')
    assertEqual(JSON.parse(font5).$attrs.font.size, '30px')
    assertEqual(JSON.parse(font5).$attrs.font.weight, FontWeight.Regular)
    assertEqual(JSON.parse(font5).$attrs.font.style, FontStyle.Italic)
    await button2.tap()
    let font6: string = await span4.getInspectorInfo()
    assertEqual(JSON.parse(font6).$attrs.font.weight, FontWeight.Medium)
    await button2.tap()
    let font7: string = await span4.getInspectorInfo()
    assertEqual(JSON.parse(font7).$attrs.font.weight, FontWeight.Bold)
    await button2.tap()
    let font8: string = await span4.getInspectorInfo()
    assertEqual(JSON.parse(font8).$attrs.font.weight, 30)
  }, 0)
}