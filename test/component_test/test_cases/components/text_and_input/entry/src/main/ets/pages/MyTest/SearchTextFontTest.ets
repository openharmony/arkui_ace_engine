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

export default async function searchTextFontTest() {
  /*
   * Search组件 TextFont属性
   * 找到画面id为searchFont1,searchFont2,searchFont3的Search组件
   * 找到画面文本为SearchFont1,SearchFont2的Button组件
   * 获取search1的TextFont属性textFont.size与期待值12.00fp比对
   * 获取search1的TextFont属性textFont.weight与期待值600比对
   * 获取search1的TextFont属性textFont.family与期待值'Arial'比对
   * 获取search1的TextFont属性textFont.style与期待值FontStyle.Normal比对
   * 获取search2的TextFont属性textFont.size与期待值10.00fp比对
   * 获取search2的TextFont属性textFont.weight与期待值FontWeight.Normal比对
   * 获取search2的TextFont属性textFont.family与期待值'Arial'比对
   * 获取search2的TextFont属性textFont.style与期待值FontStyle.Normal比对
   * 获取search3的TextFont属性textFont.size与期待值16.00fp比对
   * 获取search3的TextFont属性textFont.weight与期待值FontWeight.Lighter比对
   * 获取search3的TextFont属性textFont.family与期待值'Arial'比对
   * 获取search3的TextFont属性textFont.style与期待值FontStyle.Normal比对
   * 点击button1，变更search1的TextFont属性textFont.size值为'10px'
   * 变更search1的TextFont属性textFont.weight值为'100'
   * 变更search1的TextFont属性textFont.family值为'TESTFONTRawFile'
   * 变更search1的TextFont属性textFont.style值为FontStyle.Italic
   * 获取search1的TextFont属性textFont.size与期待值'10px'比对
   * 获取search1的TextFont属性textFont.weight与期待值'100'比对
   * 获取search1的TextFont属性textFont.family与期待值'TESTFONTRawFile'比对
   * 获取search1的TextFont属性textFont.style与期待值FontStyle.Italic比对
   * 点击button2，变更search2的TextFont属性Font.weight值为FontWeight.Regular
   * 获取search2的TextFont属性Font.weight与期待值'FontWeight.Regular'比对
   * 点击button2，变更search2的TextFont属性Font.weight值为FontWeight.Medium
   * 获取search2的TextFont属性Font.weight与期待值'FontWeight.Medium'比对
   * 点击button2，变更search2的TextFont属性Font.weight值为FontWeight.Bold
   * 获取search2的TextFont属性Font.weight与期待值'FontWeight.Bold'比对
   * 点击button2，变更search2的TextFont属性Font.weight值为FontWeight.Bolder
   * 获取search2的TextFont属性Font.weight与期待值'FontWeight.Bolder'比对
   */
  defineTest('searchTextFontTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("searchTextFontTestDemo running")
    let driver: Tester = Tester.create()
    let search1: Component = await driver.findComponent(Matcher.create().id('searchTextFont1').enabled(true))
    let search2: Component = await driver.findComponent(Matcher.create().id('searchTextFont2').enabled(true))
    let search3: Component = await driver.findComponent(Matcher.create().id('searchTextFont3').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('SearchTextFont1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('SearchTextFont2').enabled(true))

    let textFont1: string = await search1.getInspectorInfo()
    assertEqual(JSON.parse(textFont1).$attrs.textFont,
      '{"fontSize":"12.00fp","fontStyle":"FontStyle.Normal","fontWeight":"600","fontFamily":"Arial"}')
    let textFont2: string = await search2.getInspectorInfo()
    assertEqual(JSON.parse(textFont2).$attrs.textFont,
      '{"fontSize":"10.00fp","fontStyle":"FontStyle.Normal","fontWeight":"FontWeight.Lighter","fontFamily":"Arial"}')
    let textFont3: string = await search3.getInspectorInfo()
    assertEqual(JSON.parse(textFont3).$attrs.textFont,
      '{"fontSize":"16.00fp","fontStyle":"FontStyle.Normal","fontWeight":"FontWeight.Normal","fontFamily":"Arial"}')

    await button1.tap()
    let textFont4: string = await search1.getInspectorInfo()
    assertEqual(JSON.parse(textFont4).$attrs.textFont,
      '{"fontSize":"10.00px","fontStyle":"FontStyle.Italic","fontWeight":"100","fontFamily":"TESTFONTRawFile"}')
    await button2.tap()
    let textFont5: string = await search3.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(textFont5).$attrs.textFont).fontWeight, 'FontWeight.Regular')
    await button2.tap()
    let textFont6: string = await search3.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(textFont6).$attrs.textFont).fontWeight, 'FontWeight.Medium')
    await button2.tap()
    let textFont7: string = await search3.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(textFont7).$attrs.textFont).fontWeight, 'FontWeight.Bold')
    await button2.tap()
    let textFont8: string = await search3.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(textFont8).$attrs.textFont).fontWeight, 'FontWeight.Bolder')
  }, 0)
}