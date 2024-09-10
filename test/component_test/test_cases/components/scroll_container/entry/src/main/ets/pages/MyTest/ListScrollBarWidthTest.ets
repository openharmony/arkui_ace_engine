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

export default async function listScrollBarWidthTest() {
  /*
   * List组件 ScrollBarWidth属性
   * 找到画面id为listScrollBarWidth的List组件
   * 找到画面文本为ListScrollBarWidth的Button组件
   * 获取list的ScrollBarWidth属性与期待值20.00vp比对
   * 点击button，变更list的ScrollBarWidth属性值为'10.00vp'
   * 获取list的ScrollBarWidth属性与期待值'10.00vp'比对
   */
  defineTest('listScrollBarWidthTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('listScrollBarWidthTestDemo running')
    let driver: Tester = Tester.create()
    let list: Component = await driver.findComponent(Matcher.create().id('listScrollBarWidth').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ListScrollBarWidth').enabled(true))

    let scrollBarWidth1: string = await list.getInspectorInfo()
    assertEqual(JSON.parse(scrollBarWidth1).$attrs.scrollBarWidth, '20.00vp')
    await button.tap()
    let scrollBarWidth2: string = await list.getInspectorInfo()
    assertEqual(JSON.parse(scrollBarWidth2).$attrs.scrollBarWidth, '10.00vp')
  }, 0)
}