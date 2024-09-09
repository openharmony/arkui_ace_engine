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

export default async function searchSearchIconTest() {
  /*
   * Search组件 SearchIcon属性
   * 找到画面id为searchSearchIcon1,searchSearchIcon2,searchSearchIcon3的Search组件
   * 找到画面文本为SearchSearchIcon1,SearchSearchIcon2的Button组件
   * 获取search1的SearchIcon属性searchIcon.size与期待值'10.00px'比对
   * 获取search1的SearchIcon属性searchIcon.color与期待值'#99182431'比对
   * 获取search1的SearchIcon属性searchIcon.src与期待值"../../../resources/base/media/icon.png"比对
   * 获取search2的SearchIcon属性searchIcon.color与期待值$r('sys.color.ohos_id_color_text_hyperlink')比对
   * 获取search3的SearchIcon属性searchIcon.src与期待值$r('app.media.startIcon')比对
   * 点击button1，变更search1的SearchIcon属性searchIcon.size值为10
   * 变更search1的SearchIcon属性searchIcon.color值为0xffffff
   * 获取search1的SearchIcon属性searchIcon.size与期待值'10.00vp'比对
   * 获取search1的SearchIcon属性searchIcon.color与期待值'[#FFFFFFFF,]'比对
   * 点击button2，变更search1的SearchIcon属性searchIcon.size值为$r('app.string.vp_length')
   * 变更search1的SearchIcon属性searchIcon.color值为'rgb(200,78,90)'
   * 获取search1的SearchIcon属性searchIcon.size与期待值$r('app.string.vp_length')比对
   * 获取search1的SearchIcon属性searchIcon.color与期待值'[#FFC84E5A,]'比对
   */
  defineTest('searchSearchIconTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("searchSearchIconTestDemo running")
    let driver: Tester = Tester.create()
    let search1: Component = await driver.findComponent(Matcher.create().id('searchSearchIcon1').enabled(true))
    let search2: Component = await driver.findComponent(Matcher.create().id('searchSearchIcon2').enabled(true))
    let search3: Component = await driver.findComponent(Matcher.create().id('searchSearchIcon3').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('SearchSearchIcon1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('SearchSearchIcon2').enabled(true))
    let searchIcon1: string = await search1.getInspectorInfo()
    assertEqual(JSON.parse(searchIcon1).$attrs.searchIcon.size, '10.00px')
    assertEqual(JSON.parse(searchIcon1).$attrs.searchIcon.color, '#99182431')
    assertEqual(JSON.parse(searchIcon1).$attrs.searchIcon.src, "../../../resources/base/media/icon.png")
    let searchIcon2: string = await search2.getInspectorInfo()
    assertEqual(JSON.parse(searchIcon2).$attrs.searchIcon.color, $r('sys.color.ohos_id_color_text_hyperlink'))
    let searchIcon3: string = await search3.getInspectorInfo()
    assertEqual(JSON.parse(searchIcon3).$attrs.searchIcon.src, $r('app.media.startIcon'))
    await button1.tap()
    let searchIcon4: string = await search1.getInspectorInfo()
    assertEqual(JSON.parse(searchIcon4).$attrs.searchIcon.size, '10.00vp')
    assertEqual(JSON.parse(searchIcon4).$attrs.searchIcon.color, '[#FFFFFFFF,]')
    await button2.tap()
    let searchIcon5: string = await search1.getInspectorInfo()
    assertEqual(JSON.parse(searchIcon5).$attrs.searchIcon.size, $r('app.string.vp_length'))
    assertEqual(JSON.parse(searchIcon5).$attrs.searchIcon.color, '[#FFC84E5A,]')
  }, 0)
}