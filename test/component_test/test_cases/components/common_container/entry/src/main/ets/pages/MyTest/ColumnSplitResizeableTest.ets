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
  assertFalse,
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function columnSplitResizeableTest() {
  /*
   * ColumnSplit组件 Resizeable属性
   * 找到id为columnSplitResizeable1的Column组件
   * 找到画面文本为ColumnSplitResizeable的Button组件
   * 获取column1的Resizeable属性与期待值true比对
   * 点击button，变更column1的Resizeable属性值为false
   * 获取column1的Resizeable属性与期待值false比对
   */
  defineTest('columnSplitResizeableTest', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('columnSplitResizeableTestDemo running')
    let driver: Tester = Tester.create()
    let columnSplitResizeable1: Component = await driver.findComponent(Matcher.create()
      .id('columnSplitResizeable1')
      .enabled(true))
    let button: Component = await driver.findComponent((Matcher.create().text('ColumnSplitResizeable').enabled(true)))

    let resizeable1: string = await columnSplitResizeable1.getInspectorInfo()
    assertTrue(JSON.parse(resizeable1).$attrs.resizeable)
    await button.tap()
    let resizeable2: string = await columnSplitResizeable1.getInspectorInfo()
    assertFalse(JSON.parse(resizeable2).$attrs.resizeable)
  }, 0)
}