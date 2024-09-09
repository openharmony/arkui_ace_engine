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

export default async function searchTypeTest() {
  /*
   * Search组件 Type属性
   * 找到画面id为searchType1,searchType2的Search组件
   * 找到画面文本为SearchType1,SearchType2的Button组件
   * 获取search1的Type属性与期待值'SearchType.EMAIL'比对
   * 获取search2的Type属性与期待值'SearchType.NORMAL'比对
   * 点击button1，变更search2的Type属性值为SearchType.NUMBER
   * 获取search2的Type属性与期待值'SearchType.NUMBER'比对
   * 点击button2，变更search2的Type属性值为SearchType.PHONE_NUMBER
   * 获取search2的Type属性与期待值'SearchType.PHONE_NUMBER'比对
   */
  defineTest('searchTypeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("searchTypeTestDemo running")
    let driver: Tester = Tester.create()
    let search1: Component = await driver.findComponent(Matcher.create().id('searchType1').enabled(true))
    let search2: Component = await driver.findComponent(Matcher.create().id('searchType2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('SearchType1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('SearchType2').enabled(true))

    let type1: string = await search1.getInspectorInfo()
    assertEqual(JSON.parse(type1).$attrs.type, 'SearchType.EMAIL')
    let type2: string = await search2.getInspectorInfo()
    assertEqual(JSON.parse(type2).$attrs.type, 'SearchType.NORMAL')

    await button1.tap()
    let type3: string = await search2.getInspectorInfo()
    assertEqual(JSON.parse(type3).$attrs.type, 'SearchType.NUMBER')
    await button2.tap()
    let type4: string = await search2.getInspectorInfo()
    assertEqual(JSON.parse(type4).$attrs.type, 'SearchType.PHONE_NUMBER')
  }, 0)
}