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
import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest'

export default async function listAlignListItemTest() {
  /*
   * List组件 AlignListItem属性
   * 找到画面id为listAlignListItem1,listAlignListItem2的List组件
   * 找到画面文本为ListAlignListItem的Button组件
   * 获取list1的AlignListItem属性与期待值ListItemAlign.Center比对
   * 获取list2的AlignListItem属性与期待值ListItemAlign.Start比对
   * 点击button，变更list1的AlignListItem属性值为ListItemAlign.End
   * 获取list1的AlignListItem属性与期待值ListItemAlign.End比对
   */
  defineTest('listAlignListItemTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('listAlignListItemTestDemo running')
    let driver: Tester = Tester.create()
    let list1: Component = await driver.findComponent(Matcher.create().id('listAlignListItem1').enabled(true))
    let list2: Component = await driver.findComponent(Matcher.create().id('listAlignListItem2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ListAlignListItem').enabled(true))

    let alignListItem1: string = await list1.getInspectorInfo()
    assertEqual(JSON.parse(alignListItem1).$attrs.alignListItem, 'ListItemAlign.Center')
    let alignListItem2: string = await list2.getInspectorInfo()
    assertEqual(JSON.parse(alignListItem2).$attrs.alignListItem, 'ListItemAlign.Start')
    await button.tap()
    let alignListItem3: string = await list1.getInspectorInfo()
    assertEqual(JSON.parse(alignListItem3).$attrs.alignListItem, 'ListItemAlign.End')
  }, 0)
}