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

export default async function rowSplitResizeableTest() {
  /*
   * RowSplit组件 Resizeable属性
   * 找到id为rowSplitResizeable1的Row组件
   * 找到画面文本为RowSplitResizeable的Button组件
   * 获取row1的Resizeable属性与期待值false比对
   * 点击button，变更row1的Resizeable属性值为true
   * 获取row1的Resizeable属性与期待值true比对
   */
  defineTest('rowSplitResizeableTest', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('rowSplitResizeableTestDemo running')
    let driver: Tester = Tester.create()
    let rowSplitResizeable1: Component = await driver.findComponent(Matcher.create()
      .id('rowSplitResizeable1')
      .enabled(true))
    let button: Component = await driver.findComponent((Matcher.create().text('RowSplitResizeable').enabled(true)))

    let resizeable1: string = await rowSplitResizeable1.getInspectorInfo()
    assertFalse(JSON.parse(resizeable1).$attrs.resizeable)
    await button.tap()
    let resizeable2: string = await rowSplitResizeable1.getInspectorInfo()
    assertTrue(JSON.parse(resizeable2).$attrs.resizeable)
  }, 0)
}