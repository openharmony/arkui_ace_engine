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

export default async function listListDirectionTest() {
  /*
   * List组件 ListDirection属性
   * 找到画面id为listListDirection的List组件
   * 找到画面文本为ListListDirection的Button组件
   * 获取list的ListDirection属性与期待值Axis.Vertical比对
   * 点击button，变更list的ListDirection属性值为Axis.Horizontal
   * 获取list的ListDirection属性与期待值Axis.Horizontal比对
   */
  defineTest('listListDirectionTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('listListDirectionTestDemo running')
    let driver: Tester = Tester.create()
    let list: Component = await driver.findComponent(Matcher.create().id('listListDirection').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ListListDirection').enabled(true))
    let listListDirection1: string = await list.getInspectorInfo()
    assertEqual(JSON.parse(listListDirection1).$attrs.listDirection, 'Axis.Vertical')
    await button.tap()
    let listListDirection2: string = await list.getInspectorInfo()
    assertEqual(JSON.parse(listListDirection2).$attrs.listDirection, 'Axis.Horizontal')
  }, 0)
}