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

export default async function gridRowsTemplateTest() {
  /*
  * Grid组件 RowsTemplate属性
  * 找到画面id为gridRowsTemplate1，的Grid组件
  * 找到画面文本为GridRowsTemplate的Button组件
  * 获取gridRowsTemplate1的RowsTemplate属性与期待值'1fr 1fr'比对
  * 点击button，变更gridRowsTemplate1的RowsTemplate属性值为'0fr'
  * 获取gridRowsTemplate1的RowsTemplate属性与期待值'0fr'比对
  */
  defineTest('gridRowsTemplateTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('gridRowsTemplateTestDemo running')
    let driver: Tester = Tester.create()
    let gridRowsTemplate1: Component =
      await driver.findComponent(Matcher.create().id('gridRowsTemplate1').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('GridRowsTemplate').enabled(true))
    let rowsTemplate1: string = await gridRowsTemplate1.getInspectorInfo()
    assertEqual(JSON.parse(rowsTemplate1).$attrs.rowsTemplate, '1fr 1fr')
    await button.tap()
    let rowsTemplate2: string = await gridRowsTemplate1.getInspectorInfo()
    assertEqual(JSON.parse(rowsTemplate2).$attrs.rowsTemplate, '0fr')
  }, 0)
}