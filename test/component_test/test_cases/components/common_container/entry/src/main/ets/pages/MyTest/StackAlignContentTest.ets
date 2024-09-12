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

export default async function StackAlignContentTest() {
  /*
   * Stack组件 AlignContent属性
   * 找到画面id为stackAlignContent1、stackAlignContent2、stackAlignContent3、stackAlignContent4、stackAlignContent5、stackAlignContent16的AlignContent组件
   * 找到画面文本为StackAlignContent1、StackAlignContent2、StackAlignContent3、StackAlignContent4的Button组件
   * 获取stack1的AlignContent属性与期待值Alignment.Center比对
   * 获取stack2的AlignContent属性与期待值Alignment.Bottom比对
   * 获取stack2的align属性与期待值Alignment.Top比对
   * 获取stack3的AlignContent属性与期待值Alignment.Bottom比对
   * 获取stack4的AlignContent属性与期待值Alignment.BottomStart比对
   * 获取stack5的AlignContent属性与期待值Alignment.BottomEnd比对
   * 获取stack6的AlignContent属性与期待值Alignment.End比对
   * 点击button1，变更stack1的AlignContent属性值为Alignment.Start
   * 获取stack1的AlignContent属性与期待值Alignment.Start比对
   * 点击button2，变更stack1的AlignContent属性值为Alignment.TopEnd
   * 获取stack1的AlignContent属性与期待值Alignment.TopEnd比对
   * 点击button3，变更stack1的AlignContent属性值为Alignment.Top
   * 获取stack1的AlignContent属性与期待值Alignment.Top比对
   * 点击button4，变更stack1的AlignContent属性值为Alignment.TopStart
   * 获取stack1的AlignContent属性与期待值Alignment.TopStart比对
   */
  defineTest('StackAlignContentTest', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('stackAlignContentTestDemo running')
    let driver: Tester = Tester.create()
    let stack1: Component = await driver.findComponent(Matcher.create().id('stackAlignContent1').enabled(true))
    let stack2: Component = await driver.findComponent(Matcher.create().id('stackAlignContent2').enabled(true))
    let stack3: Component = await driver.findComponent(Matcher.create().id('stackAlignContent3').enabled(true))
    let stack4: Component = await driver.findComponent(Matcher.create().id('stackAlignContent4').enabled(true))
    let stack5: Component = await driver.findComponent(Matcher.create().id('stackAlignContent5').enabled(true))
    let stack6: Component = await driver.findComponent(Matcher.create().id('stackAlignContent6').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('StackAlignContent1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('StackAlignContent2').enabled(true))
    let button3: Component = await driver.findComponent(Matcher.create().text('StackAlignContent3').enabled(true))
    let button4: Component = await driver.findComponent(Matcher.create().text('StackAlignContent4').enabled(true))

    let alignContent1: string = await stack1.getInspectorInfo()
    assertEqual(JSON.parse(alignContent1).$attrs.alignContent, 'Alignment.Center')

    let alignContent2: string = await stack2.getInspectorInfo()
    assertEqual(JSON.parse(alignContent2).$attrs.alignContent, 'Alignment.Top')

    let alignContent3: string = await stack3.getInspectorInfo()
    assertEqual(JSON.parse(alignContent3).$attrs.alignContent, 'Alignment.Bottom')

    let alignContent4: string = await stack4.getInspectorInfo()
    assertEqual(JSON.parse(alignContent4).$attrs.alignContent, 'Alignment.BottomStart')

    let alignContent5: string = await stack5.getInspectorInfo()
    assertEqual(JSON.parse(alignContent5).$attrs.alignContent, 'Alignment.BottomEnd')

    let alignContent6: string = await stack6.getInspectorInfo()
    assertEqual(JSON.parse(alignContent6).$attrs.alignContent, 'Alignment.End')

    await button1.tap()
    let alignContent7: string = await stack1.getInspectorInfo()
    assertEqual(JSON.parse(alignContent7).$attrs.alignContent, 'Alignment.Start')

    await button2.tap()
    let alignContent8: string = await stack1.getInspectorInfo()
    assertEqual(JSON.parse(alignContent8).$attrs.alignContent, 'Alignment.TopEnd')

    await button3.tap()
    let alignContent9: string = await stack1.getInspectorInfo()
    assertEqual(JSON.parse(alignContent9).$attrs.alignContent, 'Alignment.Top')

    await button4.tap()
    let alignContent10: string = await stack1.getInspectorInfo()
    assertEqual(JSON.parse(alignContent10).$attrs.alignContent, 'Alignment.TopStart')
  })
}