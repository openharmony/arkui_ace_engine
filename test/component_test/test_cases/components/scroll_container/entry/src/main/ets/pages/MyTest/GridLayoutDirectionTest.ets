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

export default async function gridLayoutDirectionTest() {
  /*
  * Grid组件 LayoutDirection属性
  * 找到画面id为gridLayoutDirection1，gridLayoutDirection2的Grid组件
  * 找到画面文本为GridLayoutDirection的Button组件
  * 获取gridLayoutDirection1的LayoutDirection属性与期待值gridLayoutDirectionDirection.Row比对
  * 获取gridLayoutDirection2的LayoutDirection属性与期待值gridLayoutDirectionDirection.Column比对
  * 点击button，变更gridLayoutDirection2的LayoutDirection属性值为GridDirection.RowReverse
  * 获取gridLayoutDirection2的LayoutDirection属性与期待值GridDirection.RowReverse比对
  * 点击button，变更gridLayoutDirection2的LayoutDirection属性值为GridDirection.ColumnReverse
  * 获取gridLayoutDirection2的LayoutDirection属性与期待值GridDirection.ColumnReverse比对
  */
  defineTest('gridLayoutDirectionTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('gridLayoutDirectionTestDemo running')
    let driver: Tester = Tester.create()
    let gridLayoutDirection1: Component =
      await driver.findComponent(Matcher.create().id('gridLayoutDirection1').enabled(true))
    let gridLayoutDirection2: Component =
      await driver.findComponent(Matcher.create().id('gridLayoutDirection2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('GridLayoutDirection').enabled(true))

    let layoutDirection1: string = await gridLayoutDirection1.getInspectorInfo()
    assertEqual(JSON.parse(layoutDirection1).$attrs.layoutDirection, 'GridDirection.Row')
    let layoutDirection2: string = await gridLayoutDirection2.getInspectorInfo()
    assertEqual(JSON.parse(layoutDirection2).$attrs.layoutDirection, 'GridDirection.Column')
    await button.tap()
    let layoutDirection3: string = await gridLayoutDirection2.getInspectorInfo()
    assertEqual(JSON.parse(layoutDirection3).$attrs.layoutDirection, 'GridDirection.RowReverse')
    await button.tap()
    let layoutDirection4: string = await gridLayoutDirection2.getInspectorInfo()
    assertEqual(JSON.parse(layoutDirection4).$attrs.layoutDirection, 'GridDirection.ColumnReverse')
  }, 0)
}