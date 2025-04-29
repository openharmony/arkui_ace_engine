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

export default async function searchPlaceholderFontTest() {
  /*
* Search组件 PlaceholderFont属性
* 找到画面id为searchPlaceholderFont1,searchPlaceholderFont2,searchPlaceholderFont3的Search组件
* 找到画面文本为SearchPlaceholderFont1,SearchPlaceholderFont2的Button组件
* 获取search1的PlaceholderFont属性PlaceholderFont.size与期待值'50px'比对
* 获取search1的PlaceholderFont属性PlaceholderFont.weight与期待值FontWeight.Lighter比对
* 获取search1的PlaceholderFont属性PlaceholderFont.family与期待值'Arial'比对
* 获取search1的PlaceholderFont属性PlaceholderFont.style与期待值FontStyle.Normal比对
* 点击button1，变更search1的PlaceholderFont属性PlaceholderFont.size值为40
* 变更search1的PlaceholderFont属性PlaceholderFont.weight值为FontWeight.Normal
* 变更search1的PlaceholderFont属性PlaceholderFont.family值为'TESTFONTRawFile'
* 变更search1的PlaceholderFont属性PlaceholderFont.style值为FontStyle.Italic
* 获取search1的PlaceholderFont属性PlaceholderFont.size与期待值40比对
* 获取search1的PlaceholderFont属性PlaceholderFont.weight与期待值FontWeight.Normal比对
* 获取search1的PlaceholderFont属性PlaceholderFont.family与期待值'TESTFONTRawFile'比对
* 获取search1的PlaceholderFont属性PlaceholderFont.style与期待值FontStyle.Italic比对
* 获取search2的PlaceholderFont属性PlaceholderFont.size与期待值$r('app.string.length')比对
* 获取search2的PlaceholderFont属性PlaceholderFont.weight与期待值"900"比对
* 获取search3的PlaceholderFont属性PlaceholderFont.weight与期待值100比对
* 点击button2，变更search2的PlaceholderFont属性PlaceholderFont.weight值为FontWeight.Regular
* 获取search2的PlaceholderFont属性PlaceholderFont.weight与期待值FontWeight.Regular比对
* 点击button2，变更search2的PlaceholderFont属性PlaceholderFont.weight值为FontWeight.Medium
* 获取search2的PlaceholderFont属性PlaceholderFont.weight与期待值FontWeight.Medium比对
* 点击button2，变更search2的PlaceholderFont属性PlaceholderFont.weight值为FontWeight.Bold
* 获取search2的PlaceholderFont属性PlaceholderFont.weight与期待值FontWeight.Bold比对
* 点击button2，变更search2的PlaceholderFont属性PlaceholderFont.weight值为FontWeight.Bolder
* 获取search2的PlaceholderFont属性PlaceholderFont.weight与期待值FontWeight.Bolder比对
*/
  defineTest('searchPlaceholderFontTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("searchPlaceholderFontTestDemo running")
    let driver: Tester = Tester.create()
    let search1: Component = await driver.findComponent(Matcher.create().id('searchPlaceholderFont1').enabled(true))
    let search2: Component = await driver.findComponent(Matcher.create().id('searchPlaceholderFont2').enabled(true))
    let search3: Component = await driver.findComponent(Matcher.create().id('searchPlaceholderFont3').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('SearchPlaceholderFont1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('SearchPlaceholderFont2').enabled(true))

    let placeholderFont1: string = await search1.getInspectorInfo()
    assertEqual(JSON.parse(placeholderFont1).$attrs.placeholderFont,
      '{"style":"FontStyle.Normal","size":"50.00px","fontWeight":"FontWeight.Lighter","fontFamily":"Arial"}')
    let placeholderFont2: string = await search2.getInspectorInfo()
    assertEqual(JSON.parse(placeholderFont2).$attrs.placeholderFont,
      '{"style":"FontStyle.Normal","size":"10.00fp","weight":"900","fontFamily":"sans-serif"}')
    let placeholderFont3: string = await search3.getInspectorInfo()
    assertEqual(JSON.parse(placeholderFont3).$attrs.placeholderFont,
      '{"style":"FontStyle.Normal","size":"16.00fp","weight":"100","fontFamily":"sans-serif"}')

    await button1.tap()
    let placeholderFont4: string = await search1.getInspectorInfo()
    assertEqual(JSON.parse(placeholderFont4).$attrs.placeholderFont,
      '{"style":"FontStyle.Italic","size":"40.00fp","fontWeight":"FontWeight.Normal","fontFamily":"TESTFONTRawFile"}')
    await button2.tap()
    let placeholderFont5: string = await search3.getInspectorInfo()
    assertEqual(JSON.parse(placeholderFont5).$attrs.placeholderFont,
      '{"style":"FontStyle.Normal","size":"16.00fp","fontWeight":"FontWeight.Regular","fontFamily":"sans-serif"}')
    await button2.tap()
    let placeholderFont6: string = await search3.getInspectorInfo()
    assertEqual(JSON.parse(placeholderFont6).$attrs.placeholderFont,
      '{"style":"FontStyle.Normal","size":"16.00fp","fontWeight":"FontWeight.Medium","fontFamily":"sans-serif"}')
    await button2.tap()
    let placeholderFont7: string = await search3.getInspectorInfo()
    assertEqual(JSON.parse(placeholderFont7).$attrs.placeholderFont,
      '{"style":"FontStyle.Normal","size":"16.00fp","fontWeight":"FontWeight.Bold","fontFamily":"sans-serif"}')
    await button2.tap()
    let placeholderFont8: string = await search3.getInspectorInfo()
    assertEqual(JSON.parse(placeholderFont8).$attrs.placeholderFont,
      '{"style":"FontStyle.Normal","size":"16.00fp","fontWeight":"FontWeight.Bolder","fontFamily":"sans-serif"}')
  }, 0)
}