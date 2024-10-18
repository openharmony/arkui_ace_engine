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

export default async function buttonLabelStyleTest() {
  /*
   * Button组件 LabelStyle属性
   * 找到画面id为buttonLabelStyle1，buttonLabelStyle2，buttonLabelStyle3，...，buttonLabelStyle14，buttonLabelStyle15的Button组件
   * 找到画面文本为ButtonFontWeight8，ButtonLabelStyle15的Button组件
   * 获取buttonLabelStyle1的LabelStyle属性与期待值TextOverflow.None比对
   * 获取buttonLabelStyle2的LabelStyle属性与期待值TextOverflow.Clip比对
   * 获取buttonLabelStyle3的LabelStyle属性与期待值TextOverflow.Ellipsis比对
   * 获取buttonLabelStyle4的LabelStyle属性与期待值{maxLines: '3', minFontSize: '5.00fp',maxFontSize: '5.00fp'}对比
   * 获取buttonLabelStyle5的LabelStyle属性与期待值{maxLines: '3', minFontSize: '5.00px',maxFontSize: '10.00px'}对比
   * 获取buttonLabelStyle6的LabelStyle属性与期待值{maxLines: '3', minFontSize: $r('app.string.minFont_size'), maxFontSize: $r('app.string.maxFont_size')}对比
   * 获取buttonLabelStyle7的LabelStyle属性与期待值{maxLines: '3',minFontSize: '-1.00fp',maxFontSize: '5.00fp',heightAdaptivePolicy: 'TextHeightAdaptivePolicy.MAX_LINES_FIRST'}对比
   * 获取buttonLabelStyle8的LabelStyle属性与期待值{heightAdaptivePolicy: 'TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST'}对比
   * 获取buttonLabelStyle9的LabelStyle属性与期待值{font: {weight: 'FontWeight.Lighter'}}对比
   * 获取buttonLabelStyle10的LabelStyle属性与期待值{font: {weight: 'FontWeight.Normal'}}对比
   * 获取buttonLabelStyle11的LabelStyle属性与期待值{font: {weight: 'FontWeight.Regular'}}对比
   * 获取buttonLabelStyle12的LabelStyle属性与期待值{font: {weight: 'FontWeight.Medium'}}对比
   * 获取buttonLabelStyle13的LabelStyle属性与期待值{font: {weight: 'FontWeight.Bold',size: $r('app.string.size')}}对比
   * 获取buttonLabelStyle14的LabelStyle属性与期待值{font: {weight: 'FontWeight.Bolder',size: '10.00fp',family: 'Arial',style: 'FontStyle.Normal'}}对比
   * 获取buttonLabelStyle15的LabelStyle属性与期待值{font: {weight: '100',size: '20.00fp',family: 'TESTFONT'}}对比
   * 点击button1，变更buttonLabelStyle3的LabelStyle属性值为TextOverflow.MARQUEE，变更buttonLabelStyle8的LabelStyle属性值为{heightAdaptivePolicy: 'TextHeightAdaptivePolicy.LAYOUT_CONSTRAINT_FIRST'}
   * 获取buttonLabelStyle3的LabelStyle属性与期待值TextOverflow.MARQUEE比对，获取buttonLabelStyle8的LabelStyle属性与期待值{heightAdaptivePolicy: 'TextHeightAdaptivePolicy.LAYOUT_CONSTRAINT_FIRST'}比对
   * 点击button2，变更buttonLabelStyle15的LabelStyle属性值为{font: {weight: '200',size: '40.00fp'}}，变更buttonLabelStyle14的LabelStyle属性值为{font: { style: 'FontStyle.Italic'}}
   * 获取buttonLabelStyle15的LabelStyle属性与期待值{font: {weight: '200',size: '40.00fp'}}比对，获取buttonLabelStyle14的LabelStyle属性与期待值{font: { style: 'FontStyle.Italic'}}比对
   */
  defineTest('buttonLabelStyleTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('buttonLabelStyleTestDemo running')
    let driver: Tester = Tester.create()
    let buttonLabelStyle1: Component =
      await driver.findComponent(Matcher.create().id('buttonLabelStyle1').enabled(true))
    let buttonLabelStyle2: Component =
      await driver.findComponent(Matcher.create().id('buttonLabelStyle2').enabled(true))
    let buttonLabelStyle3: Component =
      await driver.findComponent(Matcher.create().id('buttonLabelStyle3').enabled(true))
    let buttonLabelStyle4: Component =
      await driver.findComponent(Matcher.create().id('buttonLabelStyle4').enabled(true))
    let buttonLabelStyle5: Component =
      await driver.findComponent(Matcher.create().id('buttonLabelStyle5').enabled(true))
    let buttonLabelStyle6: Component =
      await driver.findComponent(Matcher.create().id('buttonLabelStyle6').enabled(true))
    let buttonLabelStyle7: Component =
      await driver.findComponent(Matcher.create().id('buttonLabelStyle7').enabled(true))
    let buttonLabelStyle8: Component =
      await driver.findComponent(Matcher.create().id('buttonLabelStyle8').enabled(true))
    let buttonLabelStyle9: Component =
      await driver.findComponent(Matcher.create().id('buttonLabelStyle9').enabled(true))
    let buttonLabelStyle10: Component =
      await driver.findComponent(Matcher.create().id('buttonLabelStyle10').enabled(true))
    let buttonLabelStyle11: Component =
      await driver.findComponent(Matcher.create().id('buttonLabelStyle11').enabled(true))
    let buttonLabelStyle12: Component =
      await driver.findComponent(Matcher.create().id('buttonLabelStyle12').enabled(true))
    let buttonLabelStyle13: Component =
      await driver.findComponent(Matcher.create().id('buttonLabelStyle13').enabled(true))
    let buttonLabelStyle14: Component =
      await driver.findComponent(Matcher.create().id('buttonLabelStyle14').enabled(true))
    let buttonLabelStyle15: Component =
      await driver.findComponent(Matcher.create().id('buttonLabelStyle15').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonLabelStyle8').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ButtonLabelStyle15').enabled(true))

    let labelStyle1: string = await buttonLabelStyle1.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(labelStyle1).$attrs.labelStyle).overflow, 'TextOverflow.None')

    let labelStyle2: string = await buttonLabelStyle2.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(labelStyle2).$attrs.labelStyle).overflow, 'TextOverflow.Clip')

    let labelStyle3: string = await buttonLabelStyle3.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(labelStyle3).$attrs.labelStyle).overflow, 'TextOverflow.Ellipsis')

    let labelStyle4: string = await buttonLabelStyle4.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(labelStyle4).$attrs.labelStyle).maxLines, '3')
    assertEqual(JSON.parse(JSON.parse(labelStyle4).$attrs.labelStyle).minFontSize, '5.00fp')
    assertEqual(JSON.parse(JSON.parse(labelStyle4).$attrs.labelStyle).maxFontSize, '5.00fp')

    let labelStyle5: string = await buttonLabelStyle5.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(labelStyle5).$attrs.labelStyle).maxLines, '3')
    assertEqual(JSON.parse(JSON.parse(labelStyle5).$attrs.labelStyle).minFontSize, '5.00px')
    assertEqual(JSON.parse(JSON.parse(labelStyle5).$attrs.labelStyle).maxFontSize, '10.00px')

    let labelStyle6: string = await buttonLabelStyle6.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(labelStyle6).$attrs.labelStyle).maxLines, '3')
    assertEqual(JSON.parse(JSON.parse(labelStyle6).$attrs.labelStyle).minFontSize, $r('app.string.minFont_size'))
    assertEqual(JSON.parse(JSON.parse(labelStyle6).$attrs.labelStyle).maxFontSize, $r('app.string.maxFont_size'))

    let labelStyle7: string = await buttonLabelStyle7.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(labelStyle7).$attrs.labelStyle).maxLines, '3')
    assertEqual(JSON.parse(JSON.parse(labelStyle7).$attrs.labelStyle).minFontSize, '-1.00fp')
    assertEqual(JSON.parse(JSON.parse(labelStyle7).$attrs.labelStyle).maxFontSize, '5.00fp')
    assertEqual(JSON.parse(JSON.parse(labelStyle7).$attrs.labelStyle).heightAdaptivePolicy,
      'TextHeightAdaptivePolicy.MAX_LINES_FIRST')

    let labelStyle8: string = await buttonLabelStyle8.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(labelStyle8).$attrs.labelStyle).heightAdaptivePolicy,
      'TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST')

    let labelStyle9: string = await buttonLabelStyle9.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(JSON.parse(labelStyle9).$attrs.labelStyle).font).weight, 'FontWeight.Lighter')

    let labelStyle10: string = await buttonLabelStyle10.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(JSON.parse(labelStyle10).$attrs.labelStyle).font).weight, 'FontWeight.Normal')

    let labelStyle11: string = await buttonLabelStyle11.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(JSON.parse(labelStyle11).$attrs.labelStyle).font).weight, 'FontWeight.Regular')

    let labelStyle12: string = await buttonLabelStyle12.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(JSON.parse(labelStyle12).$attrs.labelStyle).font).weight, 'FontWeight.Medium')

    let labelStyle13: string = await buttonLabelStyle13.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(JSON.parse(labelStyle13).$attrs.labelStyle).font).weight, 'FontWeight.Bold')
    assertEqual(JSON.parse(JSON.parse(JSON.parse(labelStyle13).$attrs.labelStyle).font).size, $r('app.string.size'))

    let labelStyle14: string = await buttonLabelStyle14.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(JSON.parse(labelStyle14).$attrs.labelStyle).font).weight, 'FontWeight.Bolder')
    assertEqual(JSON.parse(JSON.parse(JSON.parse(labelStyle14).$attrs.labelStyle).font).size, '10.00fp')
    assertEqual(JSON.parse(JSON.parse(JSON.parse(labelStyle14).$attrs.labelStyle).font).family, 'Arial')
    assertEqual(JSON.parse(JSON.parse(JSON.parse(labelStyle14).$attrs.labelStyle).font).style, 'FontStyle.Normal')

    let labelStyle15: string = await buttonLabelStyle15.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(JSON.parse(labelStyle15).$attrs.labelStyle).font).weight, '100')
    assertEqual(JSON.parse(JSON.parse(JSON.parse(labelStyle15).$attrs.labelStyle).font).size, '20.00fp')
    assertEqual(JSON.parse(JSON.parse(JSON.parse(labelStyle15).$attrs.labelStyle).font).family, 'TESTFONT')

    await button1.tap()
    let labelStyle16: string = await buttonLabelStyle3.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(labelStyle16).$attrs.labelStyle).overflow, 'TextOverflow.Marquee')
    let labelStyle17: string = await buttonLabelStyle8.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(labelStyle17).$attrs.labelStyle).heightAdaptivePolicy,
      'TextHeightAdaptivePolicy.LAYOUT_CONSTRAINT_FIRST')

    await button2.tap()
    let labelStyle18: string = await buttonLabelStyle15.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(JSON.parse(labelStyle18).$attrs.labelStyle).font).weight, '200')
    let labelStyle19: string = await buttonLabelStyle15.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(JSON.parse(labelStyle19).$attrs.labelStyle).font).size, '40.00fp')
    let labelStyle20: string = await buttonLabelStyle14.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(JSON.parse(labelStyle20).$attrs.labelStyle).font).style, 'FontStyle.Italic')
  }, 0)
}