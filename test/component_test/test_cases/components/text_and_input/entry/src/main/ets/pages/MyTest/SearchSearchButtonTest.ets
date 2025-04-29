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

export default async function searchSearchButtonTest() {
  /*
   * Search组件 SearchButton属性
   * 找到画面id为searchSearchButton1,searchSearchButton2,searchSearchButton3的Search组件
   * 找到画面文本为SearchSearchButton1,SearchSearchButton2的Button组件
   * 获取search1的SearchButton属性SearchButton.value与期待值'SEARCH'比对
   * 获取search1的SearchButton属性SearchButton.option.fontColor与期待值#FFFF0000比对
   * 获取search1的SearchButton属性SearchButton.option.fontSize与期待值'10.00px'比对
   * 获取search2的SearchButton属性SearchButton.value与期待值'搜索'比对
   * 获取search2的SearchButton属性SearchButton.option.fontColor与期待值$r('sys.color.ohos_id_color_text_hyperlink')比对
   * 获取search3的SearchButton属性SearchButton.value与期待值''比对
   * 点击button1,变更search1的SearchButton属性SearchButton.option.fontColor值为0xffffff
   * 变更search1的SearchButton属性SearchButton.option.fontSize值为50
   * 获取search1的SearchButton属性SearchButton.value与期待值'SEARCH'比对
   * 获取search1的SearchButton属性SearchButton.option.fontColor与期待值#FFFFFFFF比对
   * 获取search1的SearchButton属性SearchButton.option.fontSize与期待值50.00fp比对
   * 点击button2，变更search2的SearchButton属性SearchButton.option.fontColor值为'rgba(100, 50, 255, 0.5)'
   * 变更search2的SearchButton属性SearchButton.option.fontSize值为$r('app.string.fp_length')
   * 获取search2的SearchButton属性SearchButton.option.fontColor与期待值#806432FF比对
   * 获取search2的SearchButton属性SearchButton.option.fontSize与期待值$r('app.string.fp_length')比对
   */
  defineTest('searchSearchButtonTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("searchSearchButtonTestDemo running")
    let driver: Tester = Tester.create()
    let search1: Component = await driver.findComponent(Matcher.create().id('searchSearchButton1').enabled(true))
    let search2: Component = await driver.findComponent(Matcher.create().id('searchSearchButton2').enabled(true))
    let search3: Component = await driver.findComponent(Matcher.create().id('searchSearchButton3').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('SearchSearchButton1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('SearchSearchButton2').enabled(true))

    let searchButton1: string = await search1.getInspectorInfo()
    assertEqual(JSON.parse(searchButton1).$attrs.searchButton, 'SEARCH')
    assertEqual(JSON.parse(searchButton1).$attrs.searchButtonOption.fontColor, '#FFFF0000')
    assertEqual(JSON.parse(searchButton1).$attrs.searchButtonOption.fontSize, '10.00px')
    let searchButton2: string = await search2.getInspectorInfo()
    assertEqual(JSON.parse(searchButton2).$attrs.searchButton, '搜索')
    assertEqual(JSON.parse(searchButton2).$attrs.searchButtonOption.fontColor,
      $r('sys.color.ohos_id_color_text_hyperlink'))

    let searchButton3: string = await search3.getInspectorInfo()
    assertEqual(JSON.parse(searchButton3).$attrs.searchButton, '')

    await button1.tap()
    let searchButton4: string = await search1.getInspectorInfo()
    assertEqual(JSON.parse(searchButton4).$attrs.searchButton, 'SEARCH')
    assertEqual(JSON.parse(searchButton4).$attrs.searchButtonOption.fontColor, '#FFFFFFFF')
    assertEqual(JSON.parse(searchButton4).$attrs.searchButtonOption.fontSize, '50.00fp')

    await button2.tap()
    let searchButton5: string = await search1.getInspectorInfo()
    assertEqual(JSON.parse(searchButton5).$attrs.searchButtonOption.fontColor, '#806432FF')
    assertEqual(JSON.parse(searchButton5).$attrs.searchButtonOption.fontSize, $r('app.string.fp_length'))
  }, 0)
}