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

export default async function gridScrollBarWidthTest() {
  /*
  * Grid组件 ScrollBarWidth属性
  * 找到画面id为gridScrollBarWidth的Grid组件
  * 找到画面文本为GridScrollBarWidth的Button组件
  * 获取gridScrollBarWidth的ScrollBarWidth属性与期待值'10.00px'比对
  * 点击button，变更gridScrollBarWidth的ScrollBarWidth属性值为'10.00vp'
  * 获取gridScrollBarWidth的ScrollBarWidth属性与期待值'10.00vp'比对
  */
  defineTest('gridScrollBarWidthTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('gridScrollBarWidthTestDemo running')
    let driver: Tester = Tester.create()
    let gridScrollBarWidth: Component =
      await driver.findComponent(Matcher.create().id('gridScrollBarWidth').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('GridScrollBarWidth').enabled(true))
    let scrollBarWidth1: string = await gridScrollBarWidth.getInspectorInfo()
    assertEqual(JSON.parse(scrollBarWidth1).$attrs.scrollBarWidth, '10.00px')
    await button.tap()
    let scrollBarWidth2: string = await gridScrollBarWidth.getInspectorInfo()
    assertEqual(JSON.parse(scrollBarWidth2).$attrs.scrollBarWidth, '10.00vp')
  }, 0)
}