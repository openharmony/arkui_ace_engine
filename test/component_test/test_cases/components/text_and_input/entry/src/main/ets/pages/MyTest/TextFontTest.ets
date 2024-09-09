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
import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest';

export default async function textFontTest() {
  /*
   * Text组件 Font属性
   * 找到画面id为spanFont1,spanFont2,spanFont3,spanFont4的Text组件
   * 找到画面文本为TextFont的Button组件
   * 获取span1的Font属性与期待值{size:10,weight:10,family:'Arial',style:FontStyle.Normal}比对
   * 获取span2的Font属性与期待值{size:'20px',weight:"20",family:'fontRawFile',style:FontStyle.Italic}比对
   * 获取span3的Font属性与期待值{size:$r('app.string.text'),weight:FontWeight.Lighter}比对
   * 获取span4的Font属性Font.weight与期待值'FontWeight.Normal'比对
   * 点击button，变更span4的Font属性Font.weight值为FontWeight.Medium
   * 获取span4的Font属性Font.weight与期待值'FontWeight.Medium'比对
   * 点击button，变更span4的Font属性Font.weight值为FontWeight.Bold
   * 获取span4的Font属性Font.weight与期待值'FontWeight.Bold'比对
   * 点击button，变更span4的Font属性Font.weight值为FontWeight.Bolder
   * 获取span4的Font属性Font.weight与期待值'FontWeight.Bolder'比对
   * 点击button，变更span4的Font属性Font.weight值为FontWeight.Regular
   * 获取span4的Font属性Font.weight与期待值'FontWeight.Regular'比对
   */
  defineTest('textFontTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textFontTestDemo running")
    let driver: Tester = Tester.create()
    let text1: Component = await driver.findComponent(Matcher.create().id('textFont1').enabled(true))
    let text2: Component = await driver.findComponent(Matcher.create().id('textFont2').enabled(true))
    let text3: Component = await driver.findComponent(Matcher.create().id('textFont3').enabled(true))
    let text4: Component = await driver.findComponent(Matcher.create().id('textFont4').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('TextFont').enabled(true))

    let font1: string = await text1.getInspectorInfo()
    assertEqual(JSON.parse(font1).$attrs.fontSize, '10.00fp')
    assertEqual(JSON.parse(font1).$attrs.fontWeight, 'FontWeight.Normal')
    assertEqual(JSON.parse(font1).$attrs.fontFamily, 'Arial')
    assertEqual(JSON.parse(font1).$attrs.fontStyle, 'FontStyle.Normal')
    let font2: string = await text2.getInspectorInfo()
    assertEqual(JSON.parse(font2).$attrs.fontSize, '20.00px')
    assertEqual(JSON.parse(font2).$attrs.fontWeight, 'FontWeight.Normal')
    assertEqual(JSON.parse(font2).$attrs.fontFamily, 'fontRawFile')
    assertEqual(JSON.parse(font2).$attrs.fontStyle, 'FontStyle.Italic')
    let font3: string = await text3.getInspectorInfo()
    assertEqual(JSON.parse(font3).$attrs.fontSize, $r('app.string.fp_text'))
    assertEqual(JSON.parse(font3).$attrs.fontWeight, 'FontWeight.Lighter')
    let font4: string = await text4.getInspectorInfo()
    assertEqual(JSON.parse(font4).$attrs.fontWeight, 'FontWeight.Normal')
    await button.tap()
    let font5: string = await text4.getInspectorInfo()
    assertEqual(JSON.parse(font5).$attrs.fontWeight, 'FontWeight.Medium')
    await button.tap()
    let font6: string = await text4.getInspectorInfo()
    assertEqual(JSON.parse(font6).$attrs.fontWeight, 'FontWeight.Bold')
    await button.tap()
    let font7: string = await text4.getInspectorInfo()
    assertEqual(JSON.parse(font7).$attrs.fontWeight, 'FontWeight.Bolder')
    await button.tap()
    let font8: string = await text4.getInspectorInfo()
    assertEqual(JSON.parse(font8).$attrs.fontWeight, 'FontWeight.Regular')
  }, 0)
}