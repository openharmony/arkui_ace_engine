import { describe, beforeAll, beforeEach, afterEach, afterAll, it, expect } from '@ohos/hypium'
import { abilityDelegatorRegistry, Component, Driver, ON } from '@kit.TestKit';

import {
  buttonClick,
  JsonType,
  Search,
  KeyStruct,
  radioClick,
  Slide,
  sliderDrag,
  ToggleClick,
  scroll,
  titleSearch,
  searchToggle,
  getToggle,
  searchParentBlock
} from '../../utils';
import { Point } from '@ohos.UiTest';


const TAG = 'GaugeBootcampTest'

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();


export default function GaugeBootcampTest() {

  describe('GaugeBootcampTest', () => {
    /**
     * 打开应用
     */
    beforeAll(async (done: Function) => {
      // Presets an action, which is performed only once before all test cases of the test suite start.
      // This API supports only one parameter: preset action function.
      console.info('beforeAll begin');


        await delegator.startAbility({
          bundleName: 'cn.ohos.components',
          abilityName: 'EntryAbility'
        });

        await driver.delayMs(5000);
        console.info(TAG + 'GaugeBootcamp001' + ' begin');

        let ListItemGroup: Array<Component> = await driver.findComponents(ON.type('ListItemGroup'))
        console.info(TAG + 'ListItemGroup' + ListItemGroup.toString());
        let ListItemGroup1: Point = await ListItemGroup[0].getBoundsCenter()
        let ListItemGroup2: Point = await ListItemGroup[2].getBoundsCenter()
        await driver.swipe(ListItemGroup1.x, ListItemGroup2.y, ListItemGroup1.x, ListItemGroup1.y, 2000)
        await driver.delayMs(1000);


        let atomDisplays: Component = await driver.findComponent(ON.text('信息展示'));
        await atomDisplays.click();
        await driver.delayMs(1000);

        let ListItems: Array<Component> = await driver.findComponents(ON.type('ListItem'))
        let width: Point = await ListItems[0].getBoundsCenter()
        let width2: Point = await ListItems[2].getBoundsCenter()
        await driver.swipe(width.x, width2.y, width.x, width.y, 1000)
        await driver.delayMs(1000);

        let scrollSearch: Component = await driver.findComponent(ON.text('数据量规图/Gauge'))
        await scrollSearch.click()
        await driver.delayMs(1000);

        let Buttons: Array<Component> = await driver.findComponents(ON.type('Button'));
        await Buttons[1].click()
        await driver.delayMs(1000);

      console.info(`beforeAll end`);
      done();
    })

    /**
     * 测试组件show.ChildComponents支持设置包含单个子组件为true且获取属性正确
     */
    it('ArkUI_Gauge_001', 0, async (done: Function) => {
      await titleSearch('参数列表', 'show.ChildComponents')
      // 无法取到子组件状态
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      done();

    })

    /**
     * 测试组件show.ChildComponents支持设置包含单个子组件为false且获取属性正确
     */
    it('ArkUI_Gauge_002', 0, async (done: Function) => {
      await titleSearch('参数列表', 'show.ChildComponents')
      // 无法取到子组件状态
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done();

    })

    /**
     * 测试组件value支持设置量规图的数据值且获取属性正确
     */
    it('ArkUI_Gauge_003 ', 0, async (done: Function) => {

      await titleSearch('参数列表', 'value')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('value', JsonType.value),
        ],
        assertEqual: '100.00'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('value', JsonType.value),
        ],
        assertEqual: '0.00'
      })

      done();

    })

    /**
     * 测试组件min支持设置当前数据段最小值且获取属性正确
     */
    it('ArkUI_Gauge_004 ', 0, async (done: Function) => {

      await titleSearch('参数列表', 'min')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('min', JsonType.value),
        ],
        assertEqual: '100.00'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('min', JsonType.value),
        ],
        assertEqual: '0.00'
      })

      done();

    })

    /**
     * 测试组件max支持设置当前数据段最大值且获取属性正确
     */
    it('ArkUI_Gauge_005 ', 0, async (done: Function) => {

      await titleSearch('参数列表', 'max')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('max', JsonType.value),
        ],
        assertEqual: '400.00'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('max', JsonType.value),
        ],
        assertEqual: '100.00'
      })

      done();

    })

    /**
     * 测试组件startAngle支持设置起始角度位置且获取属性正确
     */
    it('ArkUI_Gauge_006 ', 0, async (done: Function) => {

      await titleSearch('参数列表', 'startAngle')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('startAngle', JsonType.value),
        ],
        assertEqual: '100.00'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('startAngle', JsonType.value),
        ],
        assertEqual: '0.00'
      })

      done();

    })

    /**
     * 测试组件endAngle支持设置终止角度位置且获取属性正确
     */
    it('ArkUI_Gauge_007 ', 0, async (done: Function) => {

      await titleSearch('参数列表', 'endAngle')

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('endAngle', JsonType.value),
        ],
        assertEqual: '100.00'
      })

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('endAngle', JsonType.value),
        ],
        assertEqual: '360.00'
      })

      done();

    })

    /**
     * 测试组件colors支持设置量规图的颜色为1号色显示且获取属性正确
     */
    it('ArkUI_Gauge_008 ', 0, async (done: Function) => {

      await titleSearch('参数列表', 'colors')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('colors', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();

    })

    /**
     * 测试组件colors支持设置量规图的颜色为2号色显示且获取属性正确
     */
    it('ArkUI_Gauge_009 ', 0, async (done: Function) => {

      await titleSearch('参数列表', 'colors')

      await buttonClick({
        buttonClickObj: 1,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('colors', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })

    /**
     * 测试组件colors支持设置量规图的颜色为3号色显示且获取属性正确
     */
    it('ArkUI_Gauge_010 ', 0, async (done: Function) => {

      await titleSearch('参数列表', 'colors')

      await buttonClick({
        buttonClickObj: 2,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('colors', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();

    })

    /**
     * 测试组件colors支持设置量规图的颜色为4号色显示且获取属性正确
     */
    it('ArkUI_Gauge_011 ', 0, async (done: Function) => {

      await titleSearch('参数列表', 'colors')

      await buttonClick({
        buttonClickObj: 3,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('colors', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })

    /**
     * 测试组件colors支持设置量规图的颜色为5号色显示且获取属性正确
     */
    it('ArkUI_Gauge_012 ', 0, async (done: Function) => {

      await titleSearch('参数列表', 'colors')

      await buttonClick({
        buttonClickObj: 4,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('colors', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })

    /**
     * 测试组件colors支持设置量规图的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_Gauge_013 ', 0, async (done: Function) => {

      await titleSearch('参数列表', 'colors')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('colors', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();

    })

    /**
     * 测试组件strokeWidth支持设置环形量规图的环形厚度且获取属性正确
     */
    it('ArkUI_Gauge_014 ', 0, async (done: Function) => {

      await titleSearch('参数列表', 'strokeWidth')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('strokeWidth', JsonType.value),
        ],
        assertEqual: '10.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('strokeWidth', JsonType.value),
        ],
        assertEqual: '4.00vp'
      })

      done();

    })

    /**
     * 测试组件description支持设置说明内容为true且获取属性正确
     */
    it('ArkUI_Gauge_015 ', 0, async (done: Function) => {

      await titleSearch('参数列表', 'description')

      // 取不到 description值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      done();

    })

    /**
     * 测试组件description支持设置说明内容为false且获取属性正确
     */
    it('ArkUI_Gauge_016 ', 0, async (done: Function) => {

      await titleSearch('参数列表', 'description')

      // 取不到 description值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done();

    })

    /**
     * 测试组件trackShadow.radius支持设置投影模糊半径且获取属性正确
     */
    it('ArkUI_Gauge_017 ', 0, async (done: Function) => {

      await titleSearch('参数列表', 'trackShadow.radius')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('trackShadow', JsonType.obj),
          new KeyStruct('radius', JsonType.value),
        ],
        assertEqual: '50.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('trackShadow', JsonType.obj),
          new KeyStruct('radius', JsonType.value),
        ],
        assertEqual: '20.000000'
      })

      done();

    })

    /**
     * 测试组件trackShadow.OffsetX支持设置X轴的偏移量且获取属性正确
     */
    it('ArkUI_Gauge_018 ', 0, async (done: Function) => {

      await titleSearch('参数列表', 'trackShadow.OffsetX')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('trackShadow', JsonType.obj),
          new KeyStruct('offsetX', JsonType.value),
        ],
        assertEqual: '15.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('trackShadow', JsonType.obj),
          new KeyStruct('offsetX', JsonType.value),
        ],
        assertEqual: '5.000000'
      })

      done();

    })

    /**
     * 测试组件trackShadow.OffsetY支持设置Y轴的偏移量且获取属性正确
     */
    it('ArkUI_Gauge_019', 0, async (done: Function) => {

      await titleSearch('参数列表', 'trackShadow.OffsetY')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'trackShadow.OffsetY'
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('trackShadow', JsonType.obj),
          new KeyStruct('offsetY', JsonType.value),
        ],
        assertEqual: '15.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'trackShadow.OffsetY'
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('trackShadow', JsonType.obj),
          new KeyStruct('offsetY', JsonType.value),
        ],
        assertEqual: '5.000000'
      })

      done();

    })

    /**
     * 测试组件indicator.icon支持设置指针样式为手机图标显示且获取属性正确
     */
    it('ArkUI_Gauge_020', 0, async (done: Function) => {

      await titleSearch('参数列表', 'indicator.icon')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'indicator.icon'
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
          new KeyStruct('icon', JsonType.value),
        ],
        assertEqual: 'resource:///125830212.svg'
      })

      done();

    })

    /**
     * 测试组件indicator.icon支持设置指针样式为平板图标显示且获取属性正确
     */
    it('ArkUI_Gauge_021 ', 0, async (done: Function) => {

      await titleSearch('参数列表', 'indicator.icon')

      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'indicator.icon'
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
          new KeyStruct('icon', JsonType.value),
        ],
        assertEqual: 'resource:///125830209.svg'
      })

      done();

    })

    /**
     * 测试组件indicator.icon支持设置指针样式为屏幕图标显示且获取属性正确
     */
    it('ArkUI_Gauge_022 ', 0, async (done: Function) => {

      await titleSearch('参数列表', 'indicator.icon')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'indicator.icon'
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
          new KeyStruct('icon', JsonType.value),
        ],
        assertEqual: 'resource:///125830210.svg'
      })

      done();

    })

    /**
     * 测试组件indicator.icon支持设置指针样式为电脑图标显示且获取属性正确
     */
    it('ArkUI_Gauge_023 ', 0, async (done: Function) => {

      await titleSearch('参数列表', 'indicator.icon')

      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'indicator.icon'
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
          new KeyStruct('icon', JsonType.value),
        ],
        assertEqual: 'resource:///125830208.svg'
      })

      done();

    })

    /**
     * 测试组件indicator.icon支持设置指针样式为手表图标显示且获取属性正确
     */
    it('ArkUI_Gauge_024 ', 0, async (done: Function) => {

      await titleSearch('参数列表', 'indicator.icon')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'indicator.icon'
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
          new KeyStruct('icon', JsonType.value),
        ],
        assertEqual: 'resource:///125830211.svg'
      })

      done();

    })

    /**
     * 测试组件indicator.icon支持设置指针样式为鼠标图标显示且获取属性正确
     */
    it('ArkUI_Gauge_025 ', 0, async (done: Function) => {

      await titleSearch('参数列表', 'indicator.icon')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'indicator.icon'
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
          new KeyStruct('icon', JsonType.value),
        ],
        assertEqual: 'resource:///125831214.svg'
      })

      done();

    })

    /**
     * 测试组件indicator.space支持设置指针距离圆环外边的间距且获取属性正确
     */
    it('ArkUI_Gauge_026', 0, async (done: Function) => {

      await titleSearch('参数列表', 'indicator.space')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'indicator.space'
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
          new KeyStruct('space', JsonType.value),
        ],
        assertEqual: '20.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'indicator.space'
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
          new KeyStruct('space', JsonType.value),
        ],
        assertEqual: '8.00vp'
      })

      done();

    })

    /**
     * 测试组件width且获取属性正确
     */
    it('ArkUI_Gauge_Comp_0001', 0, async (done: Function) => {
      await titleSearch('基础属性', 'width');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('width', JsonType.value),
        ],
        assertEqual: '500.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('width', JsonType.value),
        ],
        assertEqual: '100.00vp'
      })

      done();
    })
    /**
     * 测试组件height且获取属性正确
     */
    it('ArkUI_Gauge_Comp_0002', 0, async (done: Function) => {
      await titleSearch('基础属性', 'height');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('height', JsonType.value),
        ],
        assertEqual: '500.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('height', JsonType.value),
        ],
        assertEqual: '100.00vp'
      })

      done();
    })
    /**
     * 测试组件padding且获取属性正确
     */
    it('ArkUI_Gauge_Comp_0003', 0, async (done: Function) => {
      await titleSearch('基础属性', 'padding');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        // id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('padding', JsonType.value),
        ],
        assertEqual: '100.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('padding', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
    /**
     * 测试组件margin且获取属性正确
     */
    it('ArkUI_Gauge_Comp_0004', 0, async (done: Function) => {
      await titleSearch('基础属性', 'margin');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('margin', JsonType.value),
        ],
        assertEqual: '100.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('margin', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
    /**
     * 测试开启constraintSize
     */
    it('ArkUI_Gauge_Comp_0005', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')))
      await toggle[0].click()
      await driver.delayMs(1000);
      done();
    })
    /**
     * 测试组件constraintSize.minWidth且获取属性正确
     */
    it('ArkUI_Gauge_Comp_0006', 0, async (done: Function) => {
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'constraintSize.minWidth');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"500.00vp","minHeight":"0.00vp","maxWidth":"Infinityvp","maxHeight":"Infinityvp"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"100.00vp","minHeight":"0.00vp","maxWidth":"Infinityvp","maxHeight":"Infinityvp"}'
      })

      done();
    })
    /**
     * 测试组件constraintSize.minHeight且获取属性正确
     */
    it('ArkUI_Gauge_Comp_0007', 0, async (done: Function) => {
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'constraintSize.minHeight');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"500.00vp","maxWidth":"Infinityvp","maxHeight":"Infinityvp"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"100.00vp","maxWidth":"Infinityvp","maxHeight":"Infinityvp"}'
      })

      done();
    })
    /**
     * 测试组件constraintSize.maxWidth且获取属性正确
     */
    it('ArkUI_Gauge_Comp_0008', 0, async (done: Function) => {
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'constraintSize.maxWidth');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"0.00vp","maxWidth":"500.00vp","maxHeight":"Infinityvp"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"0.00vp","maxWidth":"100.00vp","maxHeight":"Infinityvp"}'
      })

      done();
    })
    /**
     * 测试组件constraintSize.maxHeight且获取属性正确
     */
    it('ArkUI_Gauge_Comp_0009', 0, async (done: Function) => {
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'constraintSize.maxHeight');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"0.00vp","maxWidth":"Infinityvp","maxHeight":"500.00vp"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"0.00vp","maxWidth":"Infinityvp","maxHeight":"100.00vp"}'
      })

      done();
    })
    /**
     * 测试关闭constraintSize,无断言
     */
    it('ArkUI_Gauge_Comp_0010', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')));
      if (await toggle[0].isChecked() === true) {
        await toggle[0].click()
      }
      await driver.delayMs(1000);

      done();
    })
    /**
     * 测试开启position
     */
    it('ArkUI_Gauge_Comp_0011', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'position');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')))
      await toggle[0].click()
      await driver.delayMs(1000);
      done();
    })
    /**
     * 测试组件position.top且获取属性正确
     */
    it('ArkUI_Gauge_Comp_0012', 0, async (done: Function) => {
      //无值，只有xy的值
      await titleSearch('基础属性', 'position');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'position.top');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件position.bottom且获取属性正确
     */
    it('ArkUI_Gauge_Comp_0013', 0, async (done: Function) => {
      //无值，只有xy的值
      await titleSearch('基础属性', 'position');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'position.bottom');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件position.left且获取属性正确
     */
    it('ArkUI_Gauge_Comp_0014', 0, async (done: Function) => {
      await titleSearch('基础属性', 'position');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'position.left');
      //无值，只有xy的值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件position.right且获取属性正确
     */
    it('ArkUI_Gauge_Comp_0015', 0, async (done: Function) => {
      //无值，只有xy的值
      await titleSearch('基础属性', 'position');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'position.right');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试关闭position
     */
    it('ArkUI_Gauge_Comp_0016', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'position');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')));
      if (await toggle[0].isChecked() === true) {
        await toggle[0].click()
      }
      await driver.delayMs(1000);

      done();
    })
    /**
     * 测试开启markAnchor
     */
    it('ArkUI_Gauge_Comp_0017', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'markAnchor');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('markAnchor')))
      await toggle[0].click()
      await driver.delayMs(1000);
      done();
    })
    /**
     * 测试组件markAnchor.x且获取属性正确
     */
    it('ArkUI_Gauge_Comp_0018', 0, async (done: Function) => {
      await titleSearch('基础属性', 'position');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('markAnchor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'markAnchor.x');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('markAnchor', JsonType.obj),
          new KeyStruct('x', JsonType.value)
        ],
        assertEqual: '500.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('markAnchor', JsonType.obj),
          new KeyStruct('x', JsonType.value)
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
    /**
     * 测试组件markAnchor.y且获取属性正确
     */
    it('ArkUI_Gauge_Comp_0019', 0, async (done: Function) => {
      await titleSearch('基础属性', 'position');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('markAnchor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'markAnchor.y');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('markAnchor', JsonType.obj),
          new KeyStruct('y', JsonType.value)
        ],
        assertEqual: '500.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('markAnchor', JsonType.obj),
          new KeyStruct('y', JsonType.value)
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
    /**
     * 测试关闭markAnchor
     */
    it('ArkUI_Gauge_Comp_0020', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'markAnchor');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('markAnchor')));
      if (await toggle[0].isChecked() === true) {
        await toggle[0].click()
      }
      await driver.delayMs(1000);

      done();
    })
    /**
     * 测试开启offset
     */
    it('ArkUI_Gauge_Comp_0021', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'offset');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('offset')))
      await toggle[0].click()
      await driver.delayMs(1000);
      done();
    })
    /**
     * 测试组件offset.x且获取属性正确
     */
    it('ArkUI_Gauge_Comp_0022', 0, async (done: Function) => {
      await titleSearch('基础属性', 'offset');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('offset')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'offset.x');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('offset', JsonType.obj),
          new KeyStruct('x', JsonType.value)
        ],
        assertEqual: '500.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('offset', JsonType.obj),
          new KeyStruct('x', JsonType.value)
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
    /**
     * 测试组件offset.y且获取属性正确
     */
    it('ArkUI_Gauge_Comp_0023', 0, async (done: Function) => {
      await titleSearch('基础属性', 'offset');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('offset')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'offset.y');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('offset', JsonType.obj),
          new KeyStruct('y', JsonType.value)
        ],
        assertEqual: '500.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('offset', JsonType.obj),
          new KeyStruct('y', JsonType.value)
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
    /**
     * 测试关闭offset
     */
    it('ArkUI_Gauge_Comp_0024', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'offset');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('offset')));
      if (await toggle[0].isChecked() === true) {
        await toggle[0].click()
      }
      await driver.delayMs(1000);

      done();
    })
    /**
     * 测试组件borderStyle
     */
    it('ArkUI_Gauge_Comp_0025', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderStyle');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderStyle', JsonType.value)
        ],
        assertEqual: 'BorderStyle.Dotted'
      })
      done();
    })
    it('ArkUI_Gauge_Comp_0026', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderStyle');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderStyle')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 1,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderStyle', JsonType.value)
        ],
        assertEqual: 'BorderStyle.Dashed'
      })
      done();
    })
    it('ArkUI_Gauge_Comp_0027', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderStyle');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderStyle')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderStyle', JsonType.value)
        ],
        assertEqual: 'BorderStyle.Solid'
      })
      done();
    })
    /**
     * 测试组件borderWidth
     */
    it('ArkUI_Gauge_Comp_0028', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderWidth');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderWidth', JsonType.value),
        ],
        assertEqual: '20.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderWidth', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })

      done();

    })
    /**
     * 测试组件borderColor
     */
    it('ArkUI_Gauge_Comp_0029', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderColor');
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0030', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 1,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0031', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 2,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();
    })
    it('ArkUI_Gauge_Comp_0032', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 3,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0033', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 4,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0034', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();

    })
    /**
     * 测试组件borderRadius
     */
    it('ArkUI_Gauge_Comp_0035', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderRadius');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderWidth', JsonType.value),
        ],
        assertEqual: '0.00px'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderWidth', JsonType.value),
        ],
        assertEqual: '0.00px'
      })

      done();

    })
    /**
     * 测试组件background.align
     */
    it('ArkUI_Gauge_Comp_0036', 0, async (done: Function) => {
      await titleSearch('基础属性', 'background.align');
      // 无法取到子组件状态
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })
      done();
    })
    it('ArkUI_Gauge_Comp_0037', 0, async (done: Function) => {
      // 无法取到子组件状态
      await titleSearch('基础属性', 'background.align');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('background.align')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })
    it('ArkUI_Gauge_Comp_0038', 0, async (done: Function) => {
      // 无法取到子组件状态
      await titleSearch('基础属性', 'background.align');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('background.align')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 2,
      })
      done();
    })
    it('ArkUI_Gauge_Comp_0039', 0, async (done: Function) => {
      // 无法取到子组件状态
      await titleSearch('基础属性', 'background.align');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('background.align')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 3,
      })
      done();
    })
    it('ArkUI_Gauge_Comp_0040', 0, async (done: Function) => {
      // 无法取到子组件状态
      await titleSearch('基础属性', 'background.align');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('background.align')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 4,
      })
      done();
    })
    it('ArkUI_Gauge_Comp_0041', 0, async (done: Function) => {
      // 无法取到子组件状态
      await titleSearch('基础属性', 'background.align');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('background.align')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 5,
      })
      done();
    })
    it('ArkUI_Gauge_Comp_0042', 0, async (done: Function) => {
      // 无法取到子组件状态
      await titleSearch('基础属性', 'background.align');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('background.align')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 6,
      })
      done();
    })
    it('ArkUI_Gauge_Comp_0043', 0, async (done: Function) => {
      // 无法取到子组件状态
      await titleSearch('基础属性', 'background.align');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('background.align')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 7,
      })
      done();
    })
    it('ArkUI_Gauge_Comp_0044', 0, async (done: Function) => {
      // 无法取到子组件状态
      await titleSearch('基础属性', 'background.align');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('background.align')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 8,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })
      done();
    })
    /**
     * 测试组件backgroundColor
     */
    it('ArkUI_Gauge_Comp_0045', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundColor');
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0046', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 1,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0047', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 2,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0048', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 3,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0049', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 4,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0050', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();

    })
    /**
     * 测试组件backgroundImage.src
     */
    it('ArkUI_Gauge_Comp_0051', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundImage.src');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundImage.src')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await driver.delayMs(1000)
      done();
    })
    it('ArkUI_Gauge_Comp_0052', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundImage.src');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundImage.src')))
      if (await toggle.isChecked() === true) {
        await toggle.click();
      }
      await driver.delayMs(1000)
      done();
    })
    /**
     * 测试组件backgroundImage.repeat
     */
    it('ArkUI_Gauge_Comp_0053', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundImage.repeat');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundImage', JsonType.value),
        ],
        assertEqual: ', ImageRepeat.NoRepeat'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0054', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundImage.repeat');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundImage.repeat')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 1,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundImage', JsonType.value),
        ],
        assertEqual: ', ImageRepeat.X'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0055', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundImage.repeat');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundImage.repeat')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 2,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundImage', JsonType.value),
        ],
        assertEqual: ', ImageRepeat.Y'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0056', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundImage.repeat');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundImage.repeat')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundImage', JsonType.value),
        ],
        assertEqual: ', ImageRepeat.XY'
      })

      done();

    })
    /**
     * 测试组件backgroundImageSize
     */
    it('ArkUI_Gauge_Comp_0057', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundImageSize');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundImageSize', JsonType.value),
        ],
        assertEqual: 'ImageSize.Auto'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0058', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundImageSize');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundImageSize')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 1,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundImageSize', JsonType.value),
        ],
        assertEqual: 'ImageSize.Cover'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0059', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundImageSize');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundImageSize')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 2,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundImageSize', JsonType.value),
        ],
        assertEqual: 'ImageSize.Contain'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0060', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundImageSize');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundImageSize')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundImageSize', JsonType.value),
        ],
        assertEqual: 'ImageSize.FILL'
      })

      done();

    })
    /**
     * 测试组件backgroundImagePosition.x
     */
    it('ArkUI_Gauge_Comp_0061', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('基础属性', 'backgroundImagePosition.x');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();

    })
    /**
     * 测试组件backgroundImagePosition.y
     */
    it('ArkUI_Gauge_Comp_0062', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('基础属性', 'backgroundImagePosition.y');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();

    })
    /**
     * 测试组件backgroundBlurStyle
     */
    it('ArkUI_Gauge_Comp_0063', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('基础属性', 'backgroundBlurStyle');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0064', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('基础属性', 'backgroundBlurStyle');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundBlurStyle')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 1,
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0065', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('基础属性', 'backgroundBlurStyle');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundBlurStyle')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 2,
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0066', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('基础属性', 'backgroundBlurStyle');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundBlurStyle')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 3,
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0067', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('基础属性', 'backgroundBlurStyle');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundBlurStyle')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 4,
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0068', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('基础属性', 'backgroundBlurStyle');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundBlurStyle')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 5,
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0069', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('基础属性', 'backgroundBlurStyle');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundBlurStyle')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 6,
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0070', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('基础属性', 'backgroundBlurStyle');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundBlurStyle')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 7,
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0071', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('基础属性', 'backgroundBlurStyle');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundBlurStyle')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 8,
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0072', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('基础属性', 'backgroundBlurStyle');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundBlurStyle')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 9,
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0073', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('基础属性', 'backgroundBlurStyle');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundBlurStyle')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 10,
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0074', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('基础属性', 'backgroundBlurStyle');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundBlurStyle')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 11,
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0075', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('基础属性', 'backgroundBlurStyle');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundBlurStyle')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 12,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();

    })
    /**
     * 测试组件backgroundBlurStyle.options
     */
    it('ArkUI_Gauge_Comp_0076', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'backgroundBlurStyleParams.options.params');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundBlurStyleParams.options.params')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      done();

    })
    it('ArkUI_Gauge_Comp_0077', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundBlurStyleParams.options.params');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundBlurStyleParams.options.params')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backgroundBlurStyleParams.options.params.colorMode');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundBlurStyle', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('colorMode', JsonType.value)
        ],
        assertEqual: 'ThemeColorMode.System'
      })
      done();
    })
    it('ArkUI_Gauge_Comp_0078', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundBlurStyleParams.options.params');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundBlurStyleParams.options.params')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backgroundBlurStyleParams.options.params.colorMode');
      // 获取不到新值
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })
    it('ArkUI_Gauge_Comp_0079', 0, async (done: Function) => {
      // 获取不到新值
      await titleSearch('基础属性', 'backgroundBlurStyleParams.options.params');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundBlurStyleParams.options.params')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backgroundBlurStyleParams.options.params.colorMode');
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    it('ArkUI_Gauge_Comp_0080', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundBlurStyleParams.options.params');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundBlurStyleParams.options.params')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backgroundBlurStyleParams.options.params.adaptiveColor');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundBlurStyle', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('adaptiveColor', JsonType.value)
        ],
        assertEqual: 'AdaptiveColor.Default'
      })
      done();
    })
    it('ArkUI_Gauge_Comp_0081', 0, async (done: Function) => {
      // 获取不到新值
      await titleSearch('基础属性', 'backgroundBlurStyleParams.options.params');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundBlurStyleParams.options.params')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backgroundBlurStyleParams.options.params.adaptiveColor');
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    it('ArkUI_Gauge_Comp_0082', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('基础属性', 'backgroundBlurStyleParams.options.params');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundBlurStyleParams.options.params')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backgroundBlurStyleParams.options.params.blurOptions.left');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0083', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('基础属性', 'backgroundBlurStyleParams.options.params');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundBlurStyleParams.options.params')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backgroundBlurStyleParams.options.params.blurOptions.right');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0084', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundBlurStyleParams.options.params');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundBlurStyleParams.options.params')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backgroundBlurStyleParams.options.params.scale');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundBlurStyle', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('scale', JsonType.value)
        ],
        assertEqual: 1
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundBlurStyle', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('scale', JsonType.value)
        ],
        assertEqual: 1
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0085', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'backgroundBlurStyleParams.options.params');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundBlurStyleParams.options.params')))
      if (await toggle.isChecked() === true) {
        await toggle.click();
      }
      done();

    })
    /**
     * 测试组件backdropBlur
     */
    it('ArkUI_Gauge_Comp_0086', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backdropBlur');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backdropBlur', JsonType.value),
        ],
        assertEqual: 0
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backdropBlur', JsonType.value),
        ],
        assertEqual: 0
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0087', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'backdropBlur.options.grayscale');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backdropBlur.options.grayscale')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      done();

    })
    it('ArkUI_Gauge_Comp_0088', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('基础属性', 'backdropBlur.options.grayscale');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backdropBlur.options.grayscale')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backdropBlur.options.grayscale.left');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0089', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('基础属性', 'backdropBlur.options.grayscale');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backdropBlur.options.grayscale')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backdropBlur.options.grayscale.right');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0090', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backdropBlur.options.grayscale');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backdropBlur.options.grayscale')))
      if (await toggle.isChecked() === true) {
        await toggle.click();
      }
      done();

    })
    /**
     * 测试组件backgroundEffect
     */
    it('ArkUI_Gauge_Comp_0091', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'backgroundEffect');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundEffect')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      done();

    })
    it('ArkUI_Gauge_Comp_0092', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundEffect');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundEffect')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backgroundEffect.radius');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundEffect', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('radius', JsonType.value)
        ],
        assertEqual: 100
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundEffect', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('radius', JsonType.value)
        ],
        assertEqual: 0
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0093', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundEffect');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundEffect')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backgroundEffect.saturation');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundEffect', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('saturation', JsonType.value)
        ],
        assertEqual: 50
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundEffect', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('saturation', JsonType.value)
        ],
        assertEqual: 0
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0094', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundEffect');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundEffect')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backgroundEffect.brightness');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundEffect', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('brightness', JsonType.value)
        ],
        assertEqual: 2
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundEffect', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('brightness', JsonType.value)
        ],
        assertEqual: 0
      })
      done();

    })
    it('ArkUI_Gauge_Comp_0095', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundEffect');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundEffect')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backgroundEffect.color');
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundEffect', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FF0A59F7'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0096', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundEffect');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundEffect')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backgroundEffect.color');
      toggle = await driver.findComponent(ON.type('Toggle')
        .within(ON.type('Scroll'))
        .isAfter(ON.text('backgroundEffect.color')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 1,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundEffect', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0097', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundEffect');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundEffect')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backgroundEffect.color');
      toggle = await driver.findComponent(ON.type('Toggle')
        .within(ON.type('Scroll'))
        .isAfter(ON.text('backgroundEffect.color')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 2,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundEffect', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FFFE7062'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0098', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundEffect');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundEffect')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backgroundEffect.color');
      toggle = await driver.findComponent(ON.type('Toggle')
        .within(ON.type('Scroll'))
        .isAfter(ON.text('backgroundEffect.color')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 3,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundEffect', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0099', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundEffect');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundEffect')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backgroundEffect.color');
      toggle = await driver.findComponent(ON.type('Toggle')
        .within(ON.type('Scroll'))
        .isAfter(ON.text('backgroundEffect.color')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 4,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundEffect', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0100', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundEffect');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundEffect')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backgroundEffect.color');
      toggle = await driver.findComponent(ON.type('Toggle')
        .within(ON.type('Scroll'))
        .isAfter(ON.text('backgroundEffect.color')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 5,
        id: 'Gauge',
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundEffect', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0101', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundEffect');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundEffect')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backgroundEffect.adaptiveColor');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundEffect', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('adaptiveColor', JsonType.value)
        ],
        assertEqual: 'AdaptiveColor.Default'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0102', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundEffect');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundEffect')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backgroundEffect.adaptiveColor');
      toggle = await driver.findComponent(ON.type('Toggle')
        .within(ON.type('Scroll'))
        .isAfter(ON.text('backgroundEffect.adaptiveColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundEffect', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('adaptiveColor', JsonType.value)
        ],
        assertEqual: 'AdaptiveColor.Average'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0103', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundEffect');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundEffect')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backgroundEffect.blurOptions.grayscale.left');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundEffect', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('blurOption', JsonType.value)
        ],
        assertEqual: '[127.000000,0.000000]'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundEffect', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('blurOption', JsonType.value)
        ],
        assertEqual: '[0.000000,0.000000]'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0104', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundEffect');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundEffect')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backgroundEffect.blurOptions.grayscale.right');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundEffect', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('blurOption', JsonType.value)
        ],
        assertEqual: '[0.000000,127.000000]'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundEffect', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('blurOption', JsonType.value)
        ],
        assertEqual: '[0.000000,0.000000]'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0105', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'backgroundEffect');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundEffect')))
      if (await toggle.isChecked() === true) {
        await toggle.click();
      }
      done();

      done();

    })
    /**
     * 测试组件backgroundImageResizable
     */
    it('ArkUI_Gauge_Comp_0106', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'backgroundImageResizable');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundImageResizable')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      done();

    })
    it('ArkUI_Gauge_Comp_0107', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundImageResizable');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundImageResizable')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backgroundImageResizable.slice.top');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundImageResizable', JsonType.value)
        ],
        assertEqual: 'ImageResizableSlice: {left: 0.00px, right: 0.00px, top: 300.00vp, bottom: 0.00px}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundImageResizable', JsonType.value)
        ],
        assertEqual: 'ImageResizableSlice: {left: 0.00px, right: 0.00px, top: 0.00px, bottom: 0.00px}'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0108', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundImageResizable');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundImageResizable')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backgroundImageResizable.slice.bottom');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundImageResizable', JsonType.value)
        ],
        assertEqual: 'ImageResizableSlice: {left: 0.00px, right: 0.00px, top: 0.00px, bottom: 300.00vp}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundImageResizable', JsonType.value)
        ],
        assertEqual: 'ImageResizableSlice: {left: 0.00px, right: 0.00px, top: 0.00px, bottom: 0.00px}'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0109', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundImageResizable');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundImageResizable')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backgroundImageResizable.slice.left');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundImageResizable', JsonType.value)
        ],
        assertEqual: 'ImageResizableSlice: {left: 300.00vp, right: 0.00px, top: 0.00px, bottom: 0.00px}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundImageResizable', JsonType.value)
        ],
        assertEqual: 'ImageResizableSlice: {left: 0.00px, right: 0.00px, top: 0.00px, bottom: 0.00px}'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0110', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundImageResizable');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundImageResizable')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backgroundImageResizable.slice.right');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundImageResizable', JsonType.value)
        ],
        assertEqual: 'ImageResizableSlice: {left: 0.00px, right: 300.00vp, top: 0.00px, bottom: 0.00px}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundImageResizable', JsonType.value)
        ],
        assertEqual: 'ImageResizableSlice: {left: 0.00px, right: 0.00px, top: 0.00px, bottom: 0.00px}'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0111', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'backgroundImageResizable');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundImageResizable')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backgroundImageResizable.lattice');
      toggle = await driver.findComponent(ON.type('Toggle')
        .within(ON.type('Scroll'))
        .isAfter(ON.text('backgroundImageResizable.lattice')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      done();

    })
    it('ArkUI_Gauge_Comp_0112', 0, async (done: Function) => {
      // 获取不到
      await searchParentBlock('backgroundImageResizable', true)
      await searchParentBlock('backgroundImageResizable.lattice', true)
      await Search('基础属性', 'backgroundImageResizable.lattice.xDivs');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })
      done();

    })
    it('ArkUI_Gauge_Comp_0113', 0, async (done: Function) => {
      // 获取不到
      await searchParentBlock('backgroundImageResizable', true)
      await searchParentBlock('backgroundImageResizable.lattice', true)
      await searchParentBlock('backgroundImageResizable.lattice.xDivs', true)
      await radioClick({
        radioClickObj: 1,
      })
      done();

    })
    it('ArkUI_Gauge_Comp_0114', 0, async (done: Function) => {
      // 获取不到
      await searchParentBlock('backgroundImageResizable', true)
      await searchParentBlock('backgroundImageResizable.lattice', true)
      await searchParentBlock('backgroundImageResizable.lattice.xDivs', true)
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();

    })
    it('ArkUI_Gauge_Comp_0115', 0, async (done: Function) => {
      // 获取不到
      await searchParentBlock('backgroundImageResizable', true)
      await searchParentBlock('backgroundImageResizable.lattice', true)
      await searchParentBlock('backgroundImageResizable.lattice.yDivs', false)
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })
      done();

    })
    it('ArkUI_Gauge_Comp_0116', 0, async (done: Function) => {
      // 获取不到
      await searchParentBlock('backgroundImageResizable', true)
      await searchParentBlock('backgroundImageResizable.lattice', true)
      await searchParentBlock('backgroundImageResizable.lattice.yDivs', true)
      await radioClick({
        radioClickObj: 1,
      })
      done();

    })
    it('ArkUI_Gauge_Comp_0117', 0, async (done: Function) => {
      // 获取不到
      await searchParentBlock('backgroundImageResizable', true)
      await searchParentBlock('backgroundImageResizable.lattice', true)
      await searchParentBlock('backgroundImageResizable.lattice.yDivs', true)
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();

    })
    it('ArkUI_Gauge_Comp_0118', 0, async (done: Function) => {
      // 获取不到
      await searchParentBlock('backgroundImageResizable', true)
      await searchParentBlock('backgroundImageResizable.lattice', true)
      await searchParentBlock('backgroundImageResizable.lattice.fXCount', false)
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0119', 0, async (done: Function) => {
      // 获取不到
      await searchParentBlock('backgroundImageResizable', true)
      await searchParentBlock('backgroundImageResizable.lattice', true)
      await searchParentBlock('backgroundImageResizable.lattice.fYCount', false)
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0120', 0, async (done: Function) => {
      // 获取不到
      await searchParentBlock('backgroundImageResizable', true)
      await searchParentBlock('backgroundImageResizable.lattice', true)
      await searchParentBlock('backgroundImageResizable.lattice.fBounds', true)
      done();

    })
    it('ArkUI_Gauge_Comp_0121', 0, async (done: Function) => {
      // 获取不到
      await searchParentBlock('backgroundImageResizable', true)
      await searchParentBlock('backgroundImageResizable.lattice', true)
      await searchParentBlock('backgroundImageResizable.lattice.fBounds', true)
      await searchParentBlock('backgroundImageResizable.lattice.fBounds.left', false)
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0122', 0, async (done: Function) => {
      // 获取不到
      await searchParentBlock('backgroundImageResizable', true)
      await searchParentBlock('backgroundImageResizable.lattice', true)
      await searchParentBlock('backgroundImageResizable.lattice.fBounds', true)
      await searchParentBlock('backgroundImageResizable.lattice.fBounds.top', false)
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0123', 0, async (done: Function) => {
      // 获取不到
      await searchParentBlock('backgroundImageResizable', true)
      await searchParentBlock('backgroundImageResizable.lattice', true)
      await searchParentBlock('backgroundImageResizable.lattice.fBounds', true)
      await searchParentBlock('backgroundImageResizable.lattice.fBounds.right', false)
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0124', 0, async (done: Function) => {
      // 获取不到
      await searchParentBlock('backgroundImageResizable', true)
      await searchParentBlock('backgroundImageResizable.lattice', true)
      await searchParentBlock('backgroundImageResizable.lattice.fBounds', true)
      await searchParentBlock('backgroundImageResizable.lattice.fBounds.bottom', false)
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0125', 0, async (done: Function) => {
      // 获取不到
      await searchParentBlock('backgroundImageResizable', true)
      await searchParentBlock('backgroundImageResizable.lattice', true)
      await searchParentBlock('backgroundImageResizable.lattice.fBounds', false)
      done();

    })
    it('ArkUI_Gauge_Comp_0126', 0, async (done: Function) => {
      // 获取不到
      await searchParentBlock('backgroundImageResizable', true)
      await searchParentBlock('backgroundImageResizable.lattice', true)
      await searchParentBlock('backgroundImageResizable.lattice.fColors', false)
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })
      done();

    })
    it('ArkUI_Gauge_Comp_0127', 0, async (done: Function) => {
      // 获取不到
      await searchParentBlock('backgroundImageResizable', true)
      await searchParentBlock('backgroundImageResizable.lattice', true)
      await searchParentBlock('backgroundImageResizable.lattice.fColors', true)
      await radioClick({
        radioClickObj: 1
      })
      done();

    })
    it('ArkUI_Gauge_Comp_0128', 0, async (done: Function) => {
      // 获取不到
      await searchParentBlock('backgroundImageResizable', true)
      await searchParentBlock('backgroundImageResizable.lattice', true)
      await searchParentBlock('backgroundImageResizable.lattice.fColors', true)
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();

    })
    it('ArkUI_Gauge_Comp_0129', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('backgroundImageResizable', true)
      await searchParentBlock('backgroundImageResizable.lattice', false)
      done();

    })
    it('ArkUI_Gauge_Comp_0130', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('backgroundImageResizable', false)
      done();

    })
    /**
     * 测试组件backgroundBrightness
     */
    it('ArkUI_Gauge_Comp_0131', 0, async (done: Function) => {
      await Search('基础属性', 'backgroundBrightness.rate');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('BackgroundBrightness', JsonType.obj),
          new KeyStruct('dynamicLightUpRate', JsonType.value)
        ],
        assertEqual: 5
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('BackgroundBrightness', JsonType.obj),
          new KeyStruct('dynamicLightUpRate', JsonType.value)
        ],
        assertEqual: 0
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0132', 0, async (done: Function) => {
      await Search('基础属性', 'backgroundBrightness.lightUpDegree');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('BackgroundBrightness', JsonType.obj),
          new KeyStruct('dynamicLightUpDegree', JsonType.value)
        ],
        assertEqual: 1
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('BackgroundBrightness', JsonType.obj),
          new KeyStruct('dynamicLightUpDegree', JsonType.value)
        ],
        assertEqual: -1
      })

      done();

    })
    /**
     * 测试组件opacity
     */
    it('ArkUI_Gauge_Comp_0133', 0, async (done: Function) => {
      await Search('基础属性', 'opacity');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('opacity', JsonType.value),
        ],
        assertEqual: 1
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('opacity', JsonType.value),
        ],
        assertEqual: 0
      })

      done();

    })
    /**
     * 测试组件aspectRatio且获取属性正确
     */
    it('ArkUI_Gauge_Comp_0134', 0, async (done: Function) => {
      await Search('基础属性', 'aspectRatio', '通用属性1');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('aspectRatio', JsonType.value)
        ],
        assertEqual: 5
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('aspectRatio', JsonType.value)
        ],
        assertEqual: ''
      })
      done();
    })
    /**
     * 测试开启pixelRound
     */
    it('ArkUI_Gauge_Comp_0135', 0, async (done: Function) => {
      await searchParentBlock('pixelRound', true, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件pixelRound.start
     */
    it('ArkUI_Gauge_Comp_0136', 0, async (done: Function) => {
      await searchParentBlock('pixelRound', true, '基础属性', '通用属性1')
      await searchParentBlock('pixelRound.start', false);
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.value)
        ],
        assertEqual: '{"start":"PixelRoundCalcPolicy.NO_FORCE_ROUND","top":"PixelRoundCalcPolicy.NO_FORCE_ROUND","end":"PixelRoundCalcPolicy.NO_FORCE_ROUND","bottom":"PixelRoundCalcPolicy.NO_FORCE_ROUND"}'
      })
      done();
    })
    it('ArkUI_Gauge_Comp_0137', 0, async (done: Function) => {
      await searchParentBlock('pixelRound', true, '基础属性', '通用属性1')
      await searchParentBlock('pixelRound.start', true);
      await radioClick({
        radioClickObj: 1,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.value)
        ],
        assertEqual: '{"start":"PixelRoundCalcPolicy.FORCE_CEIL","top":"PixelRoundCalcPolicy.NO_FORCE_ROUND","end":"PixelRoundCalcPolicy.NO_FORCE_ROUND","bottom":"PixelRoundCalcPolicy.NO_FORCE_ROUND"}'
      })
      done();
    })
    it('ArkUI_Gauge_Comp_0138', 0, async (done: Function) => {
      await searchParentBlock('pixelRound', true, '基础属性', '通用属性1')
      await searchParentBlock('pixelRound.start', true);
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.value)
        ],
        assertEqual: '{"start":"PixelRoundCalcPolicy.FORCE_FLOOR","top":"PixelRoundCalcPolicy.NO_FORCE_ROUND","end":"PixelRoundCalcPolicy.NO_FORCE_ROUND","bottom":"PixelRoundCalcPolicy.NO_FORCE_ROUND"}'
      })
      done();
    })
    /**
     * 测试组件pixelRound.bottom
     */
    it('ArkUI_Gauge_Comp_0139', 0, async (done: Function) => {
      await searchParentBlock('pixelRound', true, '基础属性', '通用属性1')
      await searchParentBlock('pixelRound.bottom', false);
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.value)
        ],
        assertEqual: '{"start":"PixelRoundCalcPolicy.NO_FORCE_ROUND","top":"PixelRoundCalcPolicy.NO_FORCE_ROUND","end":"PixelRoundCalcPolicy.NO_FORCE_ROUND","bottom":"PixelRoundCalcPolicy.NO_FORCE_ROUND"}'
      })
      done();
    })
    it('ArkUI_Gauge_Comp_0140', 0, async (done: Function) => {
      await searchParentBlock('pixelRound', true, '基础属性', '通用属性1')
      await searchParentBlock('pixelRound.bottom', true);
      await radioClick({
        radioClickObj: 1,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.value)
        ],
        assertEqual: '{"start":"PixelRoundCalcPolicy.NO_FORCE_ROUND","top":"PixelRoundCalcPolicy.NO_FORCE_ROUND","end":"PixelRoundCalcPolicy.NO_FORCE_ROUND","bottom":"PixelRoundCalcPolicy.FORCE_CEIL"}'
      })
      done();
    })
    it('ArkUI_Gauge_Comp_0141', 0, async (done: Function) => {
      await searchParentBlock('pixelRound', true, '基础属性', '通用属性1')
      await searchParentBlock('pixelRound.bottom', true);
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.value)
        ],
        assertEqual: '{"start":"PixelRoundCalcPolicy.NO_FORCE_ROUND","top":"PixelRoundCalcPolicy.NO_FORCE_ROUND","end":"PixelRoundCalcPolicy.NO_FORCE_ROUND","bottom":"PixelRoundCalcPolicy.FORCE_FLOOR"}'
      })
      done();
    })

    /**
     * 测试组件pixelRound.top
     */
    it('ArkUI_Gauge_Comp_0142', 0, async (done: Function) => {
      await searchParentBlock('pixelRound', true, '基础属性', '通用属性1')
      await searchParentBlock('pixelRound.top', false);
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.value)
        ],
        assertEqual: '{"start":"PixelRoundCalcPolicy.NO_FORCE_ROUND","top":"PixelRoundCalcPolicy.NO_FORCE_ROUND","end":"PixelRoundCalcPolicy.NO_FORCE_ROUND","bottom":"PixelRoundCalcPolicy.NO_FORCE_ROUND"}'
      })
      done();
    })
    it('ArkUI_Gauge_Comp_0143', 0, async (done: Function) => {
      await searchParentBlock('pixelRound', true, '基础属性', '通用属性1')
      await searchParentBlock('pixelRound.top', true);
      await radioClick({
        radioClickObj: 1,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.value)
        ],
        assertEqual: '{"start":"PixelRoundCalcPolicy.NO_FORCE_ROUND","top":"PixelRoundCalcPolicy.FORCE_CEIL","end":"PixelRoundCalcPolicy.NO_FORCE_ROUND","bottom":"PixelRoundCalcPolicy.NO_FORCE_ROUND"}'
      })
      done();
    })
    it('ArkUI_Gauge_Comp_0144', 0, async (done: Function) => {
      await searchParentBlock('pixelRound', true, '基础属性', '通用属性1')
      await searchParentBlock('pixelRound.top', true);
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.value)
        ],
        assertEqual: '{"start":"PixelRoundCalcPolicy.NO_FORCE_ROUND","top":"PixelRoundCalcPolicy.FORCE_FLOOR","end":"PixelRoundCalcPolicy.NO_FORCE_ROUND","bottom":"PixelRoundCalcPolicy.NO_FORCE_ROUND"}'
      })
      await driver.delayMs(1000);
      done();
    })
    /**
     * 测试组件pixelRound.end
     */
    it('ArkUI_Gauge_Comp_0145', 0, async (done: Function) => {
      await searchParentBlock('pixelRound', true, '基础属性', '通用属性1')
      await searchParentBlock('pixelRound.end', false);
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.value)
        ],
        assertEqual: '{"start":"PixelRoundCalcPolicy.NO_FORCE_ROUND","top":"PixelRoundCalcPolicy.NO_FORCE_ROUND","end":"PixelRoundCalcPolicy.NO_FORCE_ROUND","bottom":"PixelRoundCalcPolicy.NO_FORCE_ROUND"}'
      })
      done();
    })
    it('ArkUI_Gauge_Comp_0146', 0, async (done: Function) => {
      await searchParentBlock('pixelRound', true, '基础属性', '通用属性1')
      await searchParentBlock('pixelRound.end', true);
      await radioClick({
        radioClickObj: 1,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.value)
        ],
        assertEqual: '{"start":"PixelRoundCalcPolicy.NO_FORCE_ROUND","top":"PixelRoundCalcPolicy.NO_FORCE_ROUND","end":"PixelRoundCalcPolicy.FORCE_CEIL","bottom":"PixelRoundCalcPolicy.NO_FORCE_ROUND"}'
      })
      done();
    })
    it('ArkUI_Gauge_Comp_0147', 0, async (done: Function) => {
      await searchParentBlock('pixelRound', true, '基础属性', '通用属性1')
      await searchParentBlock('pixelRound.end', true);
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.value)
        ],
        assertEqual: '{"start":"PixelRoundCalcPolicy.NO_FORCE_ROUND","top":"PixelRoundCalcPolicy.NO_FORCE_ROUND","end":"PixelRoundCalcPolicy.FORCE_FLOOR","bottom":"PixelRoundCalcPolicy.NO_FORCE_ROUND"}'
      })
      done();
    })
    /**
     * 测试关闭pixelRound
     */
    it('ArkUI_Gauge_Comp_0148', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('pixelRound', false, '基础属性', '通用属性1')
      done();

      done();
    })
    /**
     * 测试开启borderImage
     */
    it('ArkUI_Gauge_Comp_0149', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试开启关闭borderImage.source
     */
    it('ArkUI_Gauge_Comp_0150', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.source', true, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_Gauge_Comp_0151', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.source', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试开启borderImage.slice
     */
    it('ArkUI_Gauge_Comp_0152', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.slice', true, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件borderImage.slice.top
     */
    it('ArkUI_Gauge_Comp_0153', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.slice', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.slice.top', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderImage', JsonType.value),
        ],
        assertEqual: '{"source":"","slice":"left: [0.00px] right: [0.00px] top: [300.00vp] bottom: [0.00px]","width":"0.00vp","outset":"0.00vp","repeat":"RepeatMode.Stretch","fill":"false"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderWidth', JsonType.value),
        ],
        assertEqual: '0.00px'
      })

      done();

    })
    /**
     * 测试组件borderImage.slice.bottom
     */
    it('ArkUI_Gauge_Comp_0154', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.slice', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.slice.bottom', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderImage', JsonType.value),
        ],
        assertEqual: '{"source":"","slice":"left: [0.00px] right: [0.00px] top: [0.00px] bottom: [300.00vp]","width":"0.00vp","outset":"0.00vp","repeat":"RepeatMode.Stretch","fill":"false"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderWidth', JsonType.value),
        ],
        assertEqual: '0.00px'
      })

      done();

    })
    /**
     * 测试组件borderImage.slice.left
     */
    it('ArkUI_Gauge_Comp_0155', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.slice', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.slice.left', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderImage', JsonType.value),
        ],
        assertEqual: '{"source":"","slice":"left: [300.00vp] right: [0.00px] top: [0.00px] bottom: [0.00px]","width":"0.00vp","outset":"0.00vp","repeat":"RepeatMode.Stretch","fill":"false"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderWidth', JsonType.value),
        ],
        assertEqual: '0.00px'
      })

      done();

    })
    /**
     * 测试组件borderImage.slice.right
     */
    it('ArkUI_Gauge_Comp_0156', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.slice', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.slice.right', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderImage', JsonType.value),
        ],
        assertEqual: '{"source":"","slice":"left: [0.00px] right: [300.00vp] top: [0.00px] bottom: [0.00px]","width":"0.00vp","outset":"0.00vp","repeat":"RepeatMode.Stretch","fill":"false"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderWidth', JsonType.value),
        ],
        assertEqual: '0.00px'
      })

      done();

    })
    /**
     * 测试关闭borderImage.slice
     */
    it('ArkUI_Gauge_Comp_0157', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.slice', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试开启borderImage.width
     */
    it('ArkUI_Gauge_Comp_0158', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.width', true, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件borderImage.width.top
     */
    it('ArkUI_Gauge_Comp_0159', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.width', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.width.top', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderImage', JsonType.value),
        ],
        assertEqual: '{"source":"","slice":"0.00vp","width":"left: [0.00px] right: [0.00px] top: [300.00vp] bottom: [0.00px]","outset":"0.00vp","repeat":"RepeatMode.Stretch","fill":"false"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderWidth', JsonType.value),
        ],
        assertEqual: '0.00px'
      })

      done();

    })
    /**
     * 测试组件borderImage.width.bottom
     */
    it('ArkUI_Gauge_Comp_0160', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.width', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.width.bottom', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderImage', JsonType.value),
        ],
        assertEqual: '{"source":"","slice":"0.00vp","width":"left: [0.00px] right: [0.00px] top: [0.00px] bottom: [300.00vp]","outset":"0.00vp","repeat":"RepeatMode.Stretch","fill":"false"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderWidth', JsonType.value),
        ],
        assertEqual: '0.00px'
      })

      done();

    })
    /**
     * 测试组件borderImage.width.left
     */
    it('ArkUI_Gauge_Comp_0161', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.width', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.width.left', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderImage', JsonType.value),
        ],
        assertEqual: '{"source":"","slice":"0.00vp","width":"left: [300.00vp] right: [0.00px] top: [0.00px] bottom: [0.00px]","outset":"0.00vp","repeat":"RepeatMode.Stretch","fill":"false"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderWidth', JsonType.value),
        ],
        assertEqual: '0.00px'
      })

      done();

    })
    /**
     * 测试组件borderImage.width.right
     */
    it('ArkUI_Gauge_Comp_0162', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.width', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.width.right', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderImage', JsonType.value),
        ],
        assertEqual: '{"source":"","slice":"0.00vp","width":"left: [0.00px] right: [300.00vp] top: [0.00px] bottom: [0.00px]","outset":"0.00vp","repeat":"RepeatMode.Stretch","fill":"false"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderWidth', JsonType.value),
        ],
        assertEqual: '0.00px'
      })

      done();

    })
    /**
     * 测试关闭borderImage.width
     */
    it('ArkUI_Gauge_Comp_0163', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.width', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试开启borderImage.outset
     */
    it('ArkUI_Gauge_Comp_0164', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.outset', true, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件borderImage.outset.top
     */
    it('ArkUI_Gauge_Comp_0165', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.outset', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.outset.top', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderImage', JsonType.value),
        ],
        assertEqual: '{"source":"","slice":"0.00vp","width":"0.00vp","outset":"left: [0.00px] right: [0.00px] top: [300.00vp] bottom: [0.00px]","repeat":"RepeatMode.Stretch","fill":"false"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderWidth', JsonType.value),
        ],
        assertEqual: '0.00px'
      })

      done();

    })
    /**
     * 测试组件borderImage.outset.bottom
     */
    it('ArkUI_Gauge_Comp_0166', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.outset', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.outset.bottom', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderImage', JsonType.value),
        ],
        assertEqual: '{"source":"","slice":"0.00vp","width":"0.00vp","outset":"left: [0.00px] right: [0.00px] top: [0.00px] bottom: [300.00vp]","repeat":"RepeatMode.Stretch","fill":"false"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderWidth', JsonType.value),
        ],
        assertEqual: '0.00px'
      })

      done();

    })
    /**
     * 测试组件borderImage.outset.left
     */
    it('ArkUI_Gauge_Comp_0167', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.outset', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.outset.left', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderImage', JsonType.value),
        ],
        assertEqual: '{"source":"","slice":"0.00vp","width":"0.00vp","outset":"left: [300.00vp] right: [0.00px] top: [0.00px] bottom: [0.00px]","repeat":"RepeatMode.Stretch","fill":"false"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderWidth', JsonType.value),
        ],
        assertEqual: '0.00px'
      })

      done();

    })
    /**
     * 测试组件borderImage.outset.right
     */
    it('ArkUI_Gauge_Comp_0168', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.outset', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.outset.right', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderImage', JsonType.value),
        ],
        assertEqual: '{"source":"","slice":"0.00vp","width":"0.00vp","outset":"left: [0.00px] right: [300.00vp] top: [0.00px] bottom: [0.00px]","repeat":"RepeatMode.Stretch","fill":"false"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderWidth', JsonType.value),
        ],
        assertEqual: '0.00px'
      })

      done();

    })
    /**
     * 测试关闭borderImage.outset
     */
    it('ArkUI_Gauge_Comp_0169', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.outset', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件borderImage.repeat
     */
    it('ArkUI_Gauge_Comp_0170', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.repeat', false, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderImage', JsonType.value),
        ],
        assertEqual: '{"source":"","slice":"0.00vp","width":"0.00vp","outset":"0.00vp","repeat":"RepeatMode.Repeat","fill":"false"}'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0171', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.repeat', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 1,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderImage', JsonType.value),
        ],
        assertEqual: '{"source":"","slice":"0.00vp","width":"0.00vp","outset":"0.00vp","repeat":"RepeatMode.Stretch","fill":"false"}'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0172', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.repeat', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 2,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderImage', JsonType.value),
        ],
        assertEqual: '{"source":"","slice":"0.00vp","width":"0.00vp","outset":"0.00vp","repeat":"RepeatMode.Round","fill":"false"}'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0173', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.repeat', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderImage', JsonType.value),
        ],
        assertEqual: '{"source":"","slice":"0.00vp","width":"0.00vp","outset":"0.00vp","repeat":"RepeatMode.Space","fill":"false"}'
      })

      done();

    })
    /**
     * 测试组件borderImage.fill
     */
    it('ArkUI_Gauge_Comp_0174', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.fill', true, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_Gauge_Comp_0175', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.fill', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试关闭borderImage
     */
    it('ArkUI_Gauge_Comp_0176', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('borderImage', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件visibility
     */
    it('ArkUI_Gauge_Comp_0177', 0, async (done: Function) => {
      await searchParentBlock('visibility', false, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('visibility', JsonType.value),
        ],
        assertEqual: 'Visibility.Visible'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0178', 0, async (done: Function) => {
      await searchParentBlock('visibility', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 1,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('visibility', JsonType.value),
        ],
        assertEqual: 'Visibility.Hidden'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0179', 0, async (done: Function) => {
      await searchParentBlock('visibility', true, '基础属性', '通用属性1')
      // 组件没了，没有状态
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();

    })
    /**
     * 测试组件enable
     */
    it('ArkUI_Gauge_Comp_0180', 0, async (done: Function) => {
      await searchParentBlock('enabled', false, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('enabled', JsonType.value),
        ],
        assertEqual: true
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0181', 0, async (done: Function) => {
      await searchParentBlock('enabled', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('enabled', JsonType.value),
        ],
        assertEqual: false
      })

      done();
    })
    /**
     * 测试组件overlay
     */
    it('ArkUI_Gauge_Comp_0182', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_Gauge_Comp_0183', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', true, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_Gauge_Comp_0184', 0, async (done: Function) => {
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options.align', false, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('overlay', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('align', JsonType.value)
        ],
        assertEqual: 'Alignment.TopStart'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0185', 0, async (done: Function) => {
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options.align', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 1,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('overlay', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('align', JsonType.value)
        ],
        assertEqual: 'Alignment.Top'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0186', 0, async (done: Function) => {
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options.align', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 2,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('overlay', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('align', JsonType.value)
        ],
        assertEqual: 'Alignment.TopEnd'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0187', 0, async (done: Function) => {
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options.align', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 3,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('overlay', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('align', JsonType.value)
        ],
        assertEqual: 'Alignment.Start'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0188', 0, async (done: Function) => {
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options.align', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 4,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('overlay', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('align', JsonType.value)
        ],
        assertEqual: 'Alignment.Center'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0189', 0, async (done: Function) => {
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options.align', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 5,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('overlay', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('align', JsonType.value)
        ],
        assertEqual: 'Alignment.End'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0190', 0, async (done: Function) => {
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options.align', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 6,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('overlay', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('align', JsonType.value)
        ],
        assertEqual: 'Alignment.BottomStart'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0191', 0, async (done: Function) => {
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options.align', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 7,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('overlay', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('align', JsonType.value)
        ],
        assertEqual: 'Alignment.Bottom'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0192', 0, async (done: Function) => {
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options.align', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 8,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('overlay', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('align', JsonType.value)
        ],
        assertEqual: 'Alignment.BottomEnd'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0193', 0, async (done: Function) => {
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options.offset.x', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('overlay', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('offset', JsonType.obj),
          new KeyStruct('x', JsonType.value)
        ],
        assertEqual: '100.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('overlay', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('offset', JsonType.obj),
          new KeyStruct('x', JsonType.value)
        ],
        assertEqual: '0.00vp'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0194', 0, async (done: Function) => {
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options.offset.y', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('overlay', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('offset', JsonType.obj),
          new KeyStruct('y', JsonType.value)
        ],
        assertEqual: '100.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('overlay', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('offset', JsonType.obj),
          new KeyStruct('y', JsonType.value)
        ],
        assertEqual: '0.00vp'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0195', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', false, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_Gauge_Comp_0196', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('overlay', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件zIndex
     */
    it('ArkUI_Gauge_Comp_0197', 0, async (done: Function) => {
      await searchParentBlock('zIndex', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('zIndex', JsonType.value),
        ],
        assertEqual: 100
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('zIndex', JsonType.value),
        ],
        assertEqual: -100
      })

      done();

    })
    /**
     * 测试组件rotate
     */
    it('ArkUI_Gauge_Comp_0198', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('rotate', true, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_Gauge_Comp_0199', 0, async (done: Function) => {
      await searchParentBlock('rotate', true, '基础属性', '通用属性1')
      await searchParentBlock('rotate.x', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('x', JsonType.value),
        ],
        assertEqual: '0.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('x', JsonType.value),
        ],
        assertEqual: '0.000000'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0200', 0, async (done: Function) => {
      await searchParentBlock('rotate', true, '基础属性', '通用属性1')
      await searchParentBlock('rotate.y', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('y', JsonType.value),
        ],
        assertEqual: '0.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('y', JsonType.value),
        ],
        assertEqual: '0.000000'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0201', 0, async (done: Function) => {
      await searchParentBlock('rotate', true, '基础属性', '通用属性1')
      await searchParentBlock('rotate.z', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('z', JsonType.value),
        ],
        assertEqual: '0.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('z', JsonType.value),
        ],
        assertEqual: '0.000000'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0202', 0, async (done: Function) => {
      await searchParentBlock('rotate', true, '基础属性', '通用属性1')
      await searchParentBlock('rotate.angle', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('angle', JsonType.value),
        ],
        assertEqual: '360.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('angle', JsonType.value),
        ],
        assertEqual: '0.000000'
      })
      done();

    })
    it('ArkUI_Gauge_Comp_0203', 0, async (done: Function) => {
      await searchParentBlock('rotate', true, '基础属性', '通用属性1')
      await searchParentBlock('rotate.centerX', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('centerX', JsonType.value),
        ],
        assertEqual: '50.00%'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('centerX', JsonType.value),
        ],
        assertEqual: '50.00%'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0204', 0, async (done: Function) => {
      await searchParentBlock('rotate', true, '基础属性', '通用属性1')
      await searchParentBlock('rotate.centerY', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('centerY', JsonType.value),
        ],
        assertEqual: '50.00%'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('centerY', JsonType.value),
        ],
        assertEqual: '50.00%'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0205', 0, async (done: Function) => {
      // 读取不到属性值
      await searchParentBlock('rotate', true, '基础属性', '通用属性1')
      await searchParentBlock('rotate.centerZ', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0206', 0, async (done: Function) => {
      await searchParentBlock('rotate', true, '基础属性', '通用属性1')
      await searchParentBlock('rotate.perspective', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('perspective', JsonType.value),
        ],
        assertEqual: '0.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('perspective', JsonType.value),
        ],
        assertEqual: '0.000000'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0207', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('rotate', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件translate
     */
    it('ArkUI_Gauge_Comp_0208', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('translate', true, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_Gauge_Comp_0209', 0, async (done: Function) => {
      await searchParentBlock('translate', true, '基础属性', '通用属性1')
      await searchParentBlock('translate.x', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('translate', JsonType.obj),
          new KeyStruct('x', JsonType.value),
        ],
        assertEqual: '300.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('translate', JsonType.obj),
          new KeyStruct('x', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0210', 0, async (done: Function) => {
      await searchParentBlock('translate', true, '基础属性', '通用属性1')
      await searchParentBlock('translate.y', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('translate', JsonType.obj),
          new KeyStruct('y', JsonType.value),
        ],
        assertEqual: '300.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('translate', JsonType.obj),
          new KeyStruct('y', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0211', 0, async (done: Function) => {
      await searchParentBlock('translate', true, '基础属性', '通用属性1')
      await searchParentBlock('translate.z', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('translate', JsonType.obj),
          new KeyStruct('z', JsonType.value),
        ],
        assertEqual: '300.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('translate', JsonType.obj),
          new KeyStruct('z', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0212', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('translate', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件scale
     */
    it('ArkUI_Gauge_Comp_0213', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('scale', true, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_Gauge_Comp_0214', 0, async (done: Function) => {
      await searchParentBlock('scale', true, '基础属性', '通用属性1')
      await searchParentBlock('scale.x', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scale', JsonType.obj),
          new KeyStruct('x', JsonType.value),
        ],
        assertEqual: '300.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scale', JsonType.obj),
          new KeyStruct('x', JsonType.value),
        ],
        assertEqual: '0.000000'
      })

      done();

    })

    it('ArkUI_Gauge_Comp_0215', 0, async (done: Function) => {
      await searchParentBlock('scale', true, '基础属性', '通用属性1')
      await searchParentBlock('scale.y', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scale', JsonType.obj),
          new KeyStruct('y', JsonType.value),
        ],
        assertEqual: '300.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scale', JsonType.obj),
          new KeyStruct('y', JsonType.value),
        ],
        assertEqual: '0.000000'
      })
      done();

    })

    it('ArkUI_Gauge_Comp_0216', 0, async (done: Function) => {
      // 获取不到
      await searchParentBlock('scale', true, '基础属性', '通用属性1')
      await searchParentBlock('scale.z', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();

    })
    it('ArkUI_Gauge_Comp_0217', 0, async (done: Function) => {
      await searchParentBlock('scale', true, '基础属性', '通用属性1')
      await searchParentBlock('scale.centerX', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scale', JsonType.obj),
          new KeyStruct('centerX', JsonType.value),
        ],
        assertEqual: '300.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scale', JsonType.obj),
          new KeyStruct('centerX', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })
      done();

    })
    it('ArkUI_Gauge_Comp_0218', 0, async (done: Function) => {
      await searchParentBlock('scale', true, '基础属性', '通用属性1')
      await searchParentBlock('scale.centerY', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scale', JsonType.obj),
          new KeyStruct('centerY', JsonType.value),
        ],
        assertEqual: '300.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scale', JsonType.obj),
          new KeyStruct('centerY', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })
      done();

    })
    it('ArkUI_Gauge_Comp_0219', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('scale', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件transform
     */
    it('ArkUI_Gauge_Comp_0220', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('transform', true, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_Gauge_Comp_0221', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('transform', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件clip
     */
    it('ArkUI_Gauge_Comp_0222', 0, async (done: Function) => {
      await searchParentBlock('clip', false, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('clip', JsonType.value),
        ],
        assertEqual: 'true'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0223', 0, async (done: Function) => {
      await searchParentBlock('clip', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('clip', JsonType.value),
        ],
        assertEqual: 'false'
      })

      done();

    })
    /**
     * 测试组件clipShape
     */
    it('ArkUI_Gauge_Comp_0224', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('clipShape', true, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_Gauge_Comp_0225', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('clipShape', true, '基础属性', '通用属性1')
      await searchParentBlock('clipShape.width', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0226', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('clipShape', true, '基础属性', '通用属性1')
      await searchParentBlock('clipShape.height', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0227', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('clipShape', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件mask
     */
    it('ArkUI_Gauge_Comp_0228', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('mask', true, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_Gauge_Comp_0229', 0, async (done: Function) => {
      //读取不到
      await searchParentBlock('mask', true, '基础属性', '通用属性1')
      await searchParentBlock('mask.value', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0230', 0, async (done: Function) => {
      //读取不到
      await searchParentBlock('mask', true, '基础属性', '通用属性1')
      await searchParentBlock('mask.color', false, '基础属性', '通用属性1')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0231', 0, async (done: Function) => {
      //读取不到
      await searchParentBlock('mask', true, '基础属性', '通用属性1')
      await searchParentBlock('mask.color', true, '基础属性', '通用属性1')
      await buttonClick({
        buttonClickObj: 1,
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0232', 0, async (done: Function) => {
      //读取不到
      await searchParentBlock('mask', true, '基础属性', '通用属性1')
      await searchParentBlock('mask.color', true, '基础属性', '通用属性1')
      await buttonClick({
        buttonClickObj: 2,
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0233', 0, async (done: Function) => {
      //读取不到
      await searchParentBlock('mask', true, '基础属性', '通用属性1')
      await searchParentBlock('mask.color', true, '基础属性', '通用属性1')
      await buttonClick({
        buttonClickObj: 3,
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0234', 0, async (done: Function) => {
      //读取不到
      await searchParentBlock('mask', true, '基础属性', '通用属性1')
      await searchParentBlock('mask.color', true, '基础属性', '通用属性1')
      await buttonClick({
        buttonClickObj: 4,
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0235', 0, async (done: Function) => {
      //读取不到
      await searchParentBlock('mask', true, '基础属性', '通用属性1')
      await searchParentBlock('mask.color', true, '基础属性', '通用属性1')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0236', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('mask', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件maskShape
     */
    it('ArkUI_Gauge_Comp_0237', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('maskShape', true, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_Gauge_Comp_0238', 0, async (done: Function) => {
      //读取不到
      await searchParentBlock('maskShape', true, '基础属性', '通用属性1')
      await searchParentBlock('maskShape.width', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0239', 0, async (done: Function) => {
      //读取不到
      await searchParentBlock('maskShape', true, '基础属性', '通用属性1')
      await searchParentBlock('maskShape.height', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0240', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('maskShape', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件blur
     */
    it('ArkUI_Gauge_Comp_0241', 0, async (done: Function) => {
      await Search('基础属性', 'blur.value', '通用属性2');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blur', JsonType.value),
        ],
        assertEqual: 0
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blur', JsonType.value),
        ],
        assertEqual: 0
      })

      done();
    })
    it('ArkUI_Gauge_Comp_0242', 0, async (done: Function) => {
      await Search('基础属性', 'blur.options.grayscale.number1', '通用属性2');
      // 读取不到
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();
    })
    it('ArkUI_Gauge_Comp_0243', 0, async (done: Function) => {
      // 读取不到
      await Search('基础属性', 'blur.options.grayscale.number2', '通用属性2');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();
    })
    /**
     * 测试组件shadow
     */
    it('ArkUI_Gauge_Comp_0244', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.radius', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('radius', JsonType.value)
        ],
        assertEqual: '100.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('radius', JsonType.value)
        ],
        assertEqual: '0.000000'
      })

      done();
    })
    it('ArkUI_Gauge_Comp_0245', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.type', false, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('type', JsonType.value)
        ],
        assertEqual: '0'
      })
      done();
    })
    it('ArkUI_Gauge_Comp_0246', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.type', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('type', JsonType.value)
        ],
        assertEqual: '1'
      })
      done();
    })
    it('ArkUI_Gauge_Comp_0247', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.color', false, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FF0A59F7'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0248', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.color', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 1,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0249', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.color', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 2,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FFFE7062'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0250', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.color', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 3,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0251', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.color', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 4,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0252', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.color', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0253', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.offsetX', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('offsetX', JsonType.value)
        ],
        assertEqual: '100.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('offsetX', JsonType.value)
        ],
        assertEqual: '0.000000'
      })

      done();
    })
    it('ArkUI_Gauge_Comp_0254', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.offsetY', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('offsetY', JsonType.value)
        ],
        assertEqual: '100.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('offsetY', JsonType.value)
        ],
        assertEqual: '0.000000'
      })

      done();
    })
    it('ArkUI_Gauge_Comp_0255', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.fill', false, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('fill', JsonType.value)
        ],
        assertEqual: '1'
      })
      done();
    })
    it('ArkUI_Gauge_Comp_0256', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.fill', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('fill', JsonType.value)
        ],
        assertEqual: '0'
      })
      done();
    })
    /**
     * 测试组件grayscale
     */
    it('ArkUI_Gauge_Comp_0257', 0, async (done: Function) => {
      await searchParentBlock('grayscale', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('grayscale', JsonType.value)
        ],
        assertEqual: 1
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('grayscale', JsonType.value)
        ],
        assertEqual: 0
      })

      done();
    })
    /**
     * 测试组件brightness
     */
    it('ArkUI_Gauge_Comp_0258', 0, async (done: Function) => {
      await searchParentBlock('brightness', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('brightness', JsonType.value)
        ],
        assertEqual: 2
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('brightness', JsonType.value)
        ],
        assertEqual: 0
      })

      done();
    })
    /**
     * 测试组件saturate
     */
    it('ArkUI_Gauge_Comp_0259', 0, async (done: Function) => {
      await searchParentBlock('saturate', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('saturate', JsonType.value)
        ],
        assertEqual: 50
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('saturate', JsonType.value)
        ],
        assertEqual: 0
      })

      done();
    })
    /**
     * 测试组件contrast
     */
    it('ArkUI_Gauge_Comp_0260', 0, async (done: Function) => {
      await searchParentBlock('contrast', false, '基础属性', '通用属性2')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('contrast', JsonType.value)
        ],
        assertEqual: 10
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('contrast', JsonType.value)
        ],
        assertEqual: 0
      })

      done();
    })
    /**
     * 测试组件invert
     */
    it('ArkUI_Gauge_Comp_0261', 0, async (done: Function) => {
      await searchParentBlock('invert', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('invert', JsonType.value)
        ],
        assertEqual: 1
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('invert', JsonType.value)
        ],
        assertEqual: 0
      })

      done();
    })
    /**
     * 测试组件sepia
     */
    it('ArkUI_Gauge_Comp_0262', 0, async (done: Function) => {
      await searchParentBlock('sepia', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('sepia', JsonType.value)
        ],
        assertEqual: 1
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('sepia', JsonType.value)
        ],
        assertEqual: 0
      })

      done();
    })
    /**
     * 测试组件hueRotate
     */
    it('ArkUI_Gauge_Comp_0263', 0, async (done: Function) => {
      await searchParentBlock('hueRotate', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hueRotate', JsonType.value)
        ],
        assertEqual: 180
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hueRotate', JsonType.value)
        ],
        assertEqual: 180
      })

      done();
    })
    /**
     * 测试组件colorBlend
     */
    it('ArkUI_Gauge_Comp_0264', 0, async (done: Function) => {
      await searchParentBlock('colorBlend', false, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('colorBlend', JsonType.value)
        ],
        assertEqual: '#FF0A59F7'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0265', 0, async (done: Function) => {
      await searchParentBlock('colorBlend', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 1,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('colorBlend', JsonType.value)
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0266', 0, async (done: Function) => {
      await searchParentBlock('colorBlend', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 2,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('colorBlend', JsonType.value)
        ],
        assertEqual: '#FFFE7062'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0267', 0, async (done: Function) => {
      await searchParentBlock('colorBlend', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 3,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('colorBlend', JsonType.value)
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0268', 0, async (done: Function) => {
      await searchParentBlock('colorBlend', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 4,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('colorBlend', JsonType.value)
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0269', 0, async (done: Function) => {
      await searchParentBlock('colorBlend', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('colorBlend', JsonType.value)
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();

    })
    /**
     * 测试组件linearGradientBlur
     */
    it('ArkUI_Gauge_Comp_0270', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.value', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradientBlur', JsonType.obj),
          new KeyStruct('value', JsonType.value)
        ],
        assertEqual: '60.00px'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradientBlur', JsonType.obj),
          new KeyStruct('value', JsonType.value)
        ],
        assertEqual: '0.00px'
      })

      done();
    })
    it('ArkUI_Gauge_Comp_0271', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.options.fractionStops', false, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradientBlur', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('fractionStops', JsonType.obj),
        ],
        assertEqual: ['0.100000,0.000000', '0.200000,1.000000']
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0272', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.options.fractionStops', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 1,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradientBlur', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('fractionStops', JsonType.obj),
        ],
        assertEqual: ['0.100000,0.330000', '0.200000,0.660000', '0.300000,1.000000']
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0273', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.options.fractionStops', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradientBlur', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('fractionStops', JsonType.obj),
        ],
        assertEqual: ['0.400000,0.250000', '0.300000,0.500000', '0.200000,0.750000', '0.100000,1.000000']
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0274', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.options.direction', false, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradientBlur', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('direction', JsonType.obj),
        ],
        assertEqual: 'LEFT'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0275', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.options.direction', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 1,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradientBlur', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('direction', JsonType.obj),
        ],
        assertEqual: 'LEFT'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0276', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.options.direction', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 2,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradientBlur', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('direction', JsonType.obj),
        ],
        assertEqual: 'RIGHT'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0277', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.options.direction', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 3,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradientBlur', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('direction', JsonType.obj),
        ],
        assertEqual: 'BOTTOM'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0278', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.options.direction', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 4,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradientBlur', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('direction', JsonType.obj),
        ],
        assertEqual: 'LEFT_TOP'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0279', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.options.direction', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 5,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradientBlur', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('direction', JsonType.obj),
        ],
        assertEqual: 'LEFT_BOTTOM'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0280', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.options.direction', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 6,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradientBlur', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('direction', JsonType.obj),
        ],
        assertEqual: 'RIGHT_TOP'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0281', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.options.direction', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 7,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradientBlur', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('direction', JsonType.obj),
        ],
        assertEqual: 'RIGHT_BOTTOM'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0282', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.options.direction', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 1,
        id: 'Gauge',
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradientBlur', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('direction', JsonType.obj),
        ],
        assertEqual: 'LEFT'
      })

      done();

    })
    // renderGroup
    it('ArkUI_Gauge_Comp_0283', 0, async (done: Function) => {
      await searchParentBlock('renderGroup', false, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderGroup', JsonType.obj)
        ],
        assertEqual: 'true'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0284', 0, async (done: Function) => {
      await searchParentBlock('renderGroup', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderGroup', JsonType.obj)
        ],
        assertEqual: 'false'
      })

      done();

    })
    // blendMode
    it('ArkUI_Gauge_Comp_0285', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', false, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 0
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0286', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 1,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 1
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0287', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 2,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 2
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0288', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 3,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 3
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0289', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 4,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 4
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0290', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 5,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 5
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0291', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 6,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 6
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0292', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 7,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 7
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0293', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 8,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 8
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0294', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 9,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 9
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0295', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 10,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 10
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0296', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 11,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 11
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0297', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 12,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 12
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0298', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 13,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 13
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0299', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 14,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 14
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0300', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 15,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 15
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0301', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 16,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 16
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0302', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 17,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 17
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0303', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 18,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 18
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0304', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 19,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 19
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0305', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 20,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 20
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0306', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 21,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 21
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0307', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 22,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 22
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0308', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 23,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 23
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0309', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 24,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 24
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0310', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 25,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 25
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0311', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 26,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 26
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0312', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 27,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 27
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0313', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 28,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 28
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0314', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 'LUMINOSITY',
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 29
      }, 'blendMode.value', '基础属性', '通用属性2')
      done();


    })

    it('ArkUI_Gauge_Comp_0315', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('基础属性','blendMode.type','通用属性2')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })
      done();

    })
    it('ArkUI_Gauge_Comp_0316', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('基础属性','blendMode.type','通用属性2')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();

    })
    it('ArkUI_Gauge_Comp_0317', 0, async (done: Function) => {
      await searchParentBlock('useShadowBatching', false, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('useShadowBatching', JsonType.obj)
        ],
        assertEqual: 'true'
      })
      done();

    })
    it('ArkUI_Gauge_Comp_0318', 0, async (done: Function) => {
      await searchParentBlock('useShadowBatching', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('useShadowBatching', JsonType.obj)
        ],
        assertEqual: 'false'
      })
      done();

    })
    // sphericalEffect
    it('ArkUI_Gauge_Comp_0319', 0, async (done: Function) => {
      await searchParentBlock('sphericalEffect', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('sphericalEffect', JsonType.value)
        ],
        assertEqual: 1
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('sphericalEffect', JsonType.value)
        ],
        assertEqual: 0
      })

      done();
    })
    //   lightUpEffect
    it('ArkUI_Gauge_Comp_0320', 0, async (done: Function) => {
      await searchParentBlock('lightUpEffect', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('lightUpEffect', JsonType.value)
        ],
        assertEqual: 1
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('lightUpEffect', JsonType.value)
        ],
        assertEqual: 0
      })

      done();
    })
    //   pixelStretchEffect
    it('ArkUI_Gauge_Comp_0321', 0, async (done: Function) => {
      await searchParentBlock('pixelStretchEffect.options.left', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelStretchEffect', JsonType.obj),
          new KeyStruct('left', JsonType.obj)
        ],
        assertEqual: '20.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelStretchEffect', JsonType.obj),
          new KeyStruct('left', JsonType.obj)
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
    it('ArkUI_Gauge_Comp_0322', 0, async (done: Function) => {
      await searchParentBlock('pixelStretchEffect.options.right', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelStretchEffect', JsonType.obj),
          new KeyStruct('right', JsonType.obj)
        ],
        assertEqual: '20.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelStretchEffect', JsonType.obj),
          new KeyStruct('right', JsonType.obj)
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
    it('ArkUI_Gauge_Comp_0323', 0, async (done: Function) => {
      await searchParentBlock('pixelStretchEffect.options.top', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelStretchEffect', JsonType.obj),
          new KeyStruct('top', JsonType.obj)
        ],
        assertEqual: '20.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelStretchEffect', JsonType.obj),
          new KeyStruct('top', JsonType.obj)
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
    it('ArkUI_Gauge_Comp_0324', 0, async (done: Function) => {
      await searchParentBlock('pixelStretchEffect.options.bottom', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelStretchEffect', JsonType.obj),
          new KeyStruct('bottom', JsonType.obj)
        ],
        assertEqual: '20.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelStretchEffect', JsonType.obj),
          new KeyStruct('bottom', JsonType.obj)
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
    //   freeze
    it('ArkUI_Gauge_Comp_0325', 0, async (done: Function) => {
      // 获取不到
      await searchParentBlock('freeze', false, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })
      done();

    })

    it('ArkUI_Gauge_Comp_0326', 0, async (done: Function) => {
      // 获取不到
      await searchParentBlock('freeze', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();

    })

    // linearGradient
    // linearGradient.angle
    it('ArkUI_Gauge_Comp_0327', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.angle', '通用属性3')

      await sliderDrag({
        slideStar: Slide.start,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('angle', JsonType.value),
        ],
        assertEqual: '360.00px'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('angle', JsonType.value),
        ],
        assertEqual: '0.00px'
      })

      done();
    })

    // linearGradient.direction
    it('ArkUI_Gauge_Comp_0328', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.direction', '通用属性3')

      await radioClick({
        radioClickObj: 0,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'GradientDirection.Left'
      })

      done();

    })

    it('ArkUI_Gauge_Comp_0329', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.direction', '通用属性3')

      await radioClick({
        radioClickObj: 1,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'GradientDirection.Top'
      })

      done();

    })

    it('ArkUI_Gauge_Comp_0330', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.direction', '通用属性3')

      await radioClick({
        radioClickObj: 2,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'GradientDirection.Right'
      })

      done();

    })

    it('ArkUI_Gauge_Comp_0331', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.direction', '通用属性3')

      await radioClick({
        radioClickObj: 3,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'GradientDirection.Bottom'
      })

      done();

    })

    it('ArkUI_Gauge_Comp_0332', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.direction', '通用属性3')

      await radioClick({
        radioClickObj: 4,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'GradientDirection.LeftTop'
      })

      done();

    })

    it('ArkUI_Gauge_Comp_0333', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.direction', '通用属性3')

      await radioClick({
        radioClickObj: 5,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'GradientDirection.LeftBottom'
      })

      done();

    })

    it('ArkUI_Gauge_Comp_0334', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.direction', '通用属性3')

      await radioClick({
        radioClickObj: 6,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'GradientDirection.RightTop'
      })

      done();

    })

    it('ArkUI_Gauge_Comp_0335', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.direction', '通用属性3')

      await radioClick({
        radioClickObj: 7,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'GradientDirection.RightBottom'
      })

      done();

    })

    it('ArkUI_Gauge_Comp_0336', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.direction', '通用属性3')

      await radioClick({
        radioClickObj: 8,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'GradientDirection.None'
      })

      done();

    })

    //linearGradient.color1
    it('ArkUI_Gauge_Comp_0337', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color1', '通用属性3')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('colors', JsonType.array),
          new KeyStruct('0', JsonType.array),
          new KeyStruct('0', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();

    })

    it('ArkUI_Gauge_Comp_0338', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color1', '通用属性3')

      await buttonClick({
        buttonClickObj: 1,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('colors', JsonType.array),
          new KeyStruct('0', JsonType.array),
          new KeyStruct('0', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })

    it('ArkUI_Gauge_Comp_0339', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color1', '通用属性3')

      await buttonClick({
        buttonClickObj: 2,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('colors', JsonType.array),
          new KeyStruct('0', JsonType.array),
          new KeyStruct('0', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();

    })

    it('ArkUI_Gauge_Comp_0340', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color1', '通用属性3')

      await buttonClick({
        buttonClickObj: 3,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('colors', JsonType.array),
          new KeyStruct('0', JsonType.array),
          new KeyStruct('0', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })

    it('ArkUI_Gauge_Comp_0341', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color1', '通用属性3')

      await buttonClick({
        buttonClickObj: 4,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('colors', JsonType.array),
          new KeyStruct('0', JsonType.array),
          new KeyStruct('0', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })

    it('ArkUI_Gauge_Comp_0342', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color1', '通用属性3')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('colors', JsonType.array),
          new KeyStruct('0', JsonType.array),
          new KeyStruct('0', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();

    })

    // linearGradient.number1
    it('ArkUI_Gauge_Comp_0343', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.number1', '通用属性3')

      //取不到值需要，设置颜色获取
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done();
    })

    // linearGradient.color2
    it('ArkUI_Gauge_Comp_0344', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color2', '通用属性3')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('colors', JsonType.array),
          new KeyStruct('0', JsonType.array),
          new KeyStruct('0', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();

    })

    it('ArkUI_Gauge_Comp_0345', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color2', '通用属性3')

      await buttonClick({
        buttonClickObj: 1,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('colors', JsonType.array),
          new KeyStruct('0', JsonType.array),
          new KeyStruct('0', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })

    it('ArkUI_Gauge_Comp_0346', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color2', '通用属性3')

      await buttonClick({
        buttonClickObj: 2,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('colors', JsonType.array),
          new KeyStruct('0', JsonType.array),
          new KeyStruct('0', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();

    })

    it('ArkUI_Gauge_Comp_0347', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color2', '通用属性3')

      await buttonClick({
        buttonClickObj: 3,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('colors', JsonType.array),
          new KeyStruct('0', JsonType.array),
          new KeyStruct('0', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })

    it('ArkUI_Gauge_Comp_0348', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color2', '通用属性3')

      await buttonClick({
        buttonClickObj: 4,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('colors', JsonType.array),
          new KeyStruct('0', JsonType.array),
          new KeyStruct('0', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })

    it('ArkUI_Gauge_Comp_0349', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color2', '通用属性3')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('colors', JsonType.array),
          new KeyStruct('0', JsonType.array),
          new KeyStruct('0', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();

    })

    // linearGradient.number2
    it('ArkUI_Gauge_Comp_0350', 0, async (done: Function) => {
      await titleSearch('基础属性', 'linearGradient.number2', '通用属性3')
      //取不到值需要，设置颜色获取
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done();
    })

    // linearGradient.repeating
    it('ArkUI_Gauge_Comp_0351', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.repeating', '通用属性3')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('repeating', JsonType.value),
        ],
        assertEqual: 'true'
      })

      done();

    })

    it('ArkUI_Gauge_Comp_0352', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.repeating', '通用属性3')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('repeating', JsonType.value),
        ],
        assertEqual: 'false'
      })

      done();

    })

    // BindPopup
    // show.button
    it('ArkUI_Gauge_Comp_0353', 0, async (done: Function) => {

      await titleSearch('基础属性', 'show.button', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done();

    })

    it('ArkUI_Gauge_Comp_0354', 0, async (done: Function) => {

      await titleSearch('基础属性', 'show.button', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done();

    })

    // bindPopup.arrowOffset
    it('ArkUI_Gauge_Comp_0355', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.arrowOffset', '通用属性3')

      //取不到bindPopup属性值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done();
    })

    // bindPopup.showInSubWindow
    it('ArkUI_Gauge_Comp_0356', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.showInSubWindow', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0357', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.showInSubWindow', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.maskType
    it('ArkUI_Gauge_Comp_0358', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.maskType', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    // bindPopup.maskType
    it('ArkUI_Gauge_Comp_0359', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.maskType', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.mask.color
    it('ArkUI_Gauge_Comp_0360', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.mask.color'))

      if (!title) {
        await Search('基础属性', 'bindPopup.maskType', '通用属性3')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.mask.color', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0361', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.mask.color'))

      if (!title) {
        await Search('基础属性', 'bindPopup.maskType', '通用属性3')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.mask.color', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 1,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0362', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.mask.color'))

      if (!title) {
        await Search('基础属性', 'bindPopup.maskType', '通用属性3')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.mask.color', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 2,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0363', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.mask.color'))

      if (!title) {
        await Search('基础属性', 'bindPopup.maskType', '通用属性3')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.mask.color', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 3,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0364', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.mask.color'))

      if (!title) {
        await Search('基础属性', 'bindPopup.maskType', '通用属性3')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.mask.color', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 4,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0365', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.mask.color'))

      if (!title) {
        await Search('基础属性', 'bindPopup.maskType', '通用属性3')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.mask.color', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      await titleSearch('基础属性', 'bindPopup.maskType', '通用属性3')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.mask.boolean
    it('ArkUI_Gauge_Comp_0366', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.mask.boolean', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0367', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.mask.boolean', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.messageOptions.textColor
    it('ArkUI_Gauge_Comp_0368', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.textColor', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0369', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.textColor', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 1,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0370', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.textColor', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 2,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0371', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.textColor', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 3,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0372', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.textColor', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 4,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0373', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.textColor', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.messageOptions.font.size
    it('ArkUI_Gauge_Comp_0374', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.font.size', '通用属性3')

      //取不到bindPopup属性值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.messageOptions.font.weight
    it('ArkUI_Gauge_Comp_0375', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.font.weight', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0376', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.font.weight', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0377', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.font.weight', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 2,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0378', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.font.weight', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 3,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0379', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.font.weight', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 4,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0380', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.font.weight', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.messageOptions.font.style
    it('ArkUI_Gauge_Comp_0381', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.font.style', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0382', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.font.style', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.targetSpace
    it('ArkUI_Gauge_Comp_0383', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.targetSpace', '通用属性3')

      //取不到bindPopup属性值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.placement
    it('ArkUI_Gauge_Comp_0384', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.placement', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0385', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.placement', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0386', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.placement', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 2,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0387', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.placement', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 3,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0388', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.placement', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 4,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0389', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.placement', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 5,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0390', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.placement', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 6,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0391', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.placement', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 7,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0392', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.placement', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 8,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0393', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.placement', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 9,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.offsetX
    it('ArkUI_Gauge_Comp_0394', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.offsetX', '通用属性3')

      //取不到bindPopup属性值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.offsetY
    it('ArkUI_Gauge_Comp_0395', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.offsetY', '通用属性3')

      //取不到bindPopup属性值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    //bindPopup.enableArrow
    it('ArkUI_Gauge_Comp_0396', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.enableArrow', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0397', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.enableArrow', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    //bindPopup.popupColor
    it('ArkUI_Gauge_Comp_0398', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.popupColor', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0399', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.popupColor', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 1,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0400', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.popupColor', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 2,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0401', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.popupColor', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 3,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0402', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.popupColor', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 4,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0403', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.popupColor', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.autoCancel
    it('ArkUI_Gauge_Comp_0404', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.autoCancel', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0405', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.autoCancel', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()

    })

    // bindPopup.width
    it('ArkUI_Gauge_Comp_0406', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.width', '通用属性3')

      //取不到bindPopup属性值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.arrowPointPosition
    it('ArkUI_Gauge_Comp_0407', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.arrowPointPosition', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0408', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.arrowPointPosition', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 2,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0409', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.arrowPointPosition', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.shadowType
    it('ArkUI_Gauge_Comp_0410', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.shadowType', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    // bindPopup.shadowType
    it('ArkUI_Gauge_Comp_0411', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.shadowType', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.shadowType.shadowOptions.radius
    it('ArkUI_Gauge_Comp_0412', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.shadowType.shadowOptions.radius'))

      if (!title) {
        await Search('基础属性', 'bindPopup.shadowType', '通用属性3')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }


      await titleSearch('基础属性', 'bindPopup.shadowType.shadowOptions.radius', '通用属性3')

      //取不到bindPopup属性值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.shadowType.shadowOptions.type
    it('ArkUI_Gauge_Comp_0413', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.shadowType.shadowOptions.type'))

      if (!title) {
        await Search('基础属性', 'bindPopup.shadowType', '通用属性3')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowOptions.type', '通用属性3')
      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0414', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.shadowType.shadowOptions.type'))

      if (!title) {
        await Search('基础属性', 'bindPopup.shadowType', '通用属性3')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowOptions.type', '通用属性3')
      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.shadowType.shadowOptions.color
    it('ArkUI_Gauge_Comp_0415', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.shadowType.shadowOptions.type'))

      if (!title) {
        await Search('基础属性', 'bindPopup.shadowType', '通用属性3')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowOptions.color', '通用属性3')
      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0416', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.shadowType.shadowOptions.type'))

      if (!title) {
        await Search('基础属性', 'bindPopup.shadowType', '通用属性3')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowOptions.color', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 1,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0417', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.shadowType.shadowOptions.type'))

      if (!title) {
        await Search('基础属性', 'bindPopup.shadowType', '通用属性3')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowOptions.color', '通用属性3')
      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 2,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0418', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.shadowType.shadowOptions.type'))

      if (!title) {
        await Search('基础属性', 'bindPopup.shadowType', '通用属性3')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowOptions.color', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 3,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0419', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.shadowType.shadowOptions.type'))

      if (!title) {
        await Search('基础属性', 'bindPopup.shadowType', '通用属性3')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowOptions.color', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 4,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0420', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.shadowType.shadowOptions.type'))

      if (!title) {
        await Search('基础属性', 'bindPopup.shadowType', '通用属性3')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowOptions.color', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.shadowType.shadowOptions.offsetX
    it('ArkUI_Gauge_Comp_0421', 0, async (done: Function) => {
      let title = await driver.findComponent(ON.text('bindPopup.shadowType.shadowOptions.offsetX'))

      if (!title) {
        await Search('基础属性', 'bindPopup.shadowType', '通用属性3')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowOptions.offsetX', '通用属性3')
      //取不到bindPopup属性值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.shadowType.shadowOptions.offsetY
    it('ArkUI_Gauge_Comp_0422', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.shadowType.shadowOptions.offsetY'))

      if (!title) {
        await Search('基础属性', 'bindPopup.shadowType', '通用属性3')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowOptions.offsetY', '通用属性3')
      //取不到bindPopup属性值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.shadowType.shadowOptions.fill
    it('ArkUI_Gauge_Comp_0423', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.shadowType.shadowOptions.fill'))

      if (!title) {
        await Search('基础属性', 'bindPopup.shadowType', '通用属性3')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowOptions.fill', '通用属性3')
      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0424', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.shadowType.shadowOptions.fill'))

      if (!title) {
        await Search('基础属性', 'bindPopup.shadowType', '通用属性3')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowOptions.fill', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      await titleSearch('基础属性', 'bindPopup.shadowType', '通用属性3')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })


      done()
    })

    // bindPopup.shadowType.shadowStyle
    it('ArkUI_Gauge_Comp_0425', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0426', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0427', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 2,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0428', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 3,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0429', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 4,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0430', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.BackgroundBlurStyle
    it('ArkUI_Gauge_Comp_0431', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0432', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0433', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 2,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0434', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 3,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0435', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 4,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0436', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 5,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0437', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 6,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0438', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 7,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0439', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 8,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0440', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 9,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0441', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 10,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0442', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 11,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.transition.opacity
    it('ArkUI_Gauge_Comp_0443', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.opacity', '通用属性3')

      //取不到bindPopup属性值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.transition.translateX
    it('ArkUI_Gauge_Comp_0444', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.translateX', '通用属性3')

      //取不到bindPopup属性值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.transition.translateY
    it('ArkUI_Gauge_Comp_0445', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.translateY', '通用属性3')

      //取不到bindPopup属性值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.transition.translateZ
    it('ArkUI_Gauge_Comp_0446', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.translateZ', '通用属性3')

      //取不到bindPopup属性值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.transition.scaleX
    it('ArkUI_Gauge_Comp_0447', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.scaleX', '通用属性3')

      //取不到bindPopup属性值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.transition.scaleY
    it('ArkUI_Gauge_Comp_0448', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.scaleY', '通用属性3')

      //取不到bindPopup属性值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.transition.scaleZ
    it('ArkUI_Gauge_Comp_0449', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.scaleZ', '通用属性3')

      //取不到bindPopup属性值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.transition.scale.centerX
    it('ArkUI_Gauge_Comp_0450', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.scale.centerX', '通用属性3')

      //取不到bindPopup属性值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.transition.scale.centerY
    it('ArkUI_Gauge_Comp_0451', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.scale.centerY', '通用属性3')

      //取不到bindPopup属性值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.transition.RotateX
    it('ArkUI_Gauge_Comp_0452', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.RotateX', '通用属性3')

      //取不到bindPopup属性值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.transition.RotateY
    it('ArkUI_Gauge_Comp_0453', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.RotateY', '通用属性3')

      //取不到bindPopup属性值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.transition.RotateZ
    it('ArkUI_Gauge_Comp_0454', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.RotateZ', '通用属性3')

      //取不到bindPopup属性值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.transition.Rotate.CenterX
    it('ArkUI_Gauge_Comp_0455', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.Rotate.CenterX', '通用属性3')

      //取不到bindPopup属性值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.transition.Rotate.CenterY
    it('ArkUI_Gauge_Comp_0456', 0, async (done: Function) => {

      await titleSearch('基础属性', ' bindPopup.transition.Rotate.CenterY', '通用属性3')

      //取不到bindPopup属性值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.transition.move
    it('ArkUI_Gauge_Comp_0457', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.move', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0458', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.move', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0459', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.move', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 2,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0460', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.move', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    //focusable
    it('ArkUI_Gauge_Comp_0461', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusable', '通用属性3')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('focusable', JsonType.value)
        ],
        assertEqual: true
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0462', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusable', '通用属性3')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('focusable', JsonType.value)
        ],
        assertEqual: false
      })

      done()
    })

    // defaultFocus
    it('ArkUI_Gauge_Comp_0463', 0, async (done: Function) => {
      //设置当前组件是否为当前页面上的默认焦点，仅在初次创建的页面第一次进入时生效。
      await titleSearch('基础属性', 'defaultFocus', '通用属性3')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0464', 0, async (done: Function) => {

      await titleSearch('基础属性', 'defaultFocus', '通用属性3')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // groupDefaultFocus
    it('ArkUI_Gauge_Comp_0465', 0, async (done: Function) => {

      await titleSearch('基础属性', 'groupDefaultFocus', '通用属性3')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('groupDefaultFocus', JsonType.value)
        ],
        assertEqual: true
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0466', 0, async (done: Function) => {

      await titleSearch('基础属性', 'groupDefaultFocus', '通用属性3')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('groupDefaultFocus', JsonType.value)
        ],
        assertEqual: false
      })

      done()
    })

    // focusOnTouch
    it('ArkUI_Gauge_Comp_0467', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusOnTouch', '通用属性3')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('focusOnTouch', JsonType.value)
        ],
        assertEqual: true
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0468', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusOnTouch', '通用属性3')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('focusOnTouch', JsonType.value)
        ],
        assertEqual: false
      })

      done()
    })

    // focusBox.margin
    it('ArkUI_Gauge_Comp_0469', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusBox.margin', '通用属性3')

      //取不到focusBox值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // focusBox.strokeColor
    it('ArkUI_Gauge_Comp_0470', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusBox.strokeColor', '通用属性3')

      //取不到focusBox值
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0471', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusBox.strokeColor', '通用属性3')

      //取不到focusBox值
      await buttonClick({
        buttonClickObj: 1,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0472', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusBox.strokeColor', '通用属性3')

      //取不到focusBox值
      await buttonClick({
        buttonClickObj: 2,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0473', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusBox.strokeColor', '通用属性3')

      //取不到focusBox值
      await buttonClick({
        buttonClickObj: 3,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0474', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusBox.strokeColor', '通用属性3')

      //取不到focusBox值
      await buttonClick({
        buttonClickObj: 4,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0475', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusBox.strokeColor', '通用属性3')

      //取不到focusBox值
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // focusBox.strokeWidth
    it('ArkUI_Gauge_Comp_0476', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusBox.strokeWidth', '通用属性3')

      //取不到focusBox值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindMenu.font.size
    it('ArkUI_Gauge_Comp_0477', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.font.size', '通用属性4')

      //取不到bindMenu属性值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done()
    })

    // bindMenu.font.weight
    it('ArkUI_Gauge_Comp_0478', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.font.weight', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0479', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.font.weight', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 1,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0480', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.font.weight', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 2,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0481', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.font.weight', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 3,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0482', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.font.weight', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 4,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0483', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.font.weight', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindMenu.font.style
    it('ArkUI_Gauge_Comp_0484', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.font.style', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0485', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.font.style', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done()
    })

    // bindMenu.fontColor
    it('ArkUI_Gauge_Comp_0486', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.fontColor', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0487', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.fontColor', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 1,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0488', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.fontColor', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 2,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0489', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.fontColor', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 3,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0490', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.fontColor', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 4,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0491', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.fontColor', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done()
    })

    // bindMenu.radius
    it('ArkUI_Gauge_Comp_0492', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.radius', '通用属性4')

      //取不到bindMenu属性值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done()
    })

    // bindMenu.width
    it('ArkUI_Gauge_Comp_0493', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.width', '通用属性4')

      //取不到bindMenu属性值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done()
    })

    // bindMenu.height
    it('ArkUI_Gauge_Comp_0494', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.height', '通用属性4')

      //取不到bindMenu属性值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done()
    })

    // bindMenu.menuItemDivider.color
    it('ArkUI_Gauge_Comp_0495', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemDivider.color', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0496', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemDivider.color', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 1,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0497', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemDivider.color', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 2,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0498', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemDivider.color', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 3,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0499', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemDivider.color', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 4,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0500', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemDivider.color', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindMenu.menuItemDivider.strokeWidth
    it('ArkUI_Gauge_Comp_0501', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemDivider.strokeWidth', '通用属性4')

      //取不到bindMenu属性值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindMenu.menuItemDivider.startMargin
    it('ArkUI_Gauge_Comp_0502', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemDivider.startMargin', '通用属性4')

      //取不到bindMenu属性值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindMenu.menuItemDivider.endMargin
    it('ArkUI_Gauge_Comp_0503', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemDivider.endMargin', '通用属性4')

      //取不到bindMenu属性值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindMenu.menuItemGroupDivider.strokeWidth
    it('ArkUI_Gauge_Comp_0504', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemGroupDivider.strokeWidth', '通用属性4')

      //取不到bindMenu属性值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindMenu.menuItemGroupDivider.color
    it('ArkUI_Gauge_Comp_0505', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemGroupDivider.color', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0506', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemGroupDivider.color', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 1,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0507', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemGroupDivider.color', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 2,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0508', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemGroupDivider.color', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 3,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0509', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemGroupDivider.color', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 4,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0510', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemGroupDivider.color', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindMenu.menuItemGroupDivider.startMargin
    it('ArkUI_Gauge_Comp_0511', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemGroupDivider.startMargin', '通用属性4')

      //取不到bindMenu属性值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindMenu.menuItemGroupDivider.endMargin
    it('ArkUI_Gauge_Comp_0512', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemGroupDivider.endMargin', '通用属性4')

      //取不到bindMenu属性值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindMenu.SubMenuExpandingMode
    it('ArkUI_Gauge_Comp_0513', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.SubMenuExpandingMode', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0514', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.SubMenuExpandingMode', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 1,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0515', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.SubMenuExpandingMode', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindMenu.direction
    it('ArkUI_Gauge_Comp_0516', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.direction', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0517', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.direction', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 1,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0518', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.direction', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindMenu.菜单项1是否选中
    it('ArkUI_Gauge_Comp_0519', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.菜单项1是否选中', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()

    })

    it('ArkUI_Gauge_Comp_0520', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.菜单项1是否选中', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindMenu.是否显示选中图标
    it('ArkUI_Gauge_Comp_0521', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项1是否选中', '通用属性4')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0522', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项1是否选中', '通用属性4')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 1,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0523', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项1是否选中', '通用属性4')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 2,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0524', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项1是否选中', '通用属性4')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 3,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0525', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项1是否选中', '通用属性4')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 4,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0526', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项1是否选中', '通用属性4')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      await Search('基础属性', 'bindMenu.菜单项1是否选中', '通用属性4')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })


      done()
    })

    // bindMenu.菜单项2是否选中
    it('ArkUI_Gauge_Comp_0527', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.菜单项2是否选中', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0528', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.菜单项2是否选中', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindMenu.是否显示选中图标
    it('ArkUI_Gauge_Comp_0529', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项2是否选中', '通用属性4')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性4')
      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0530', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项2是否选中', '通用属性4')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 1,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0531', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项2是否选中', '通用属性4')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 2,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0532', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项2是否选中', '通用属性4')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性4')
      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 3,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0533', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项2是否选中', '通用属性4')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性4')
      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 4,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0534', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项2是否选中', '通用属性4')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性4')
      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })


      await Search('基础属性', 'bindMenu.菜单项2是否选中', '通用属性4')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindMenu.菜单项3是否选中
    it('ArkUI_Gauge_Comp_0535', 0, async (done: Function) => {


      await titleSearch('基础属性', 'bindMenu.菜单项3是否选中', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()

    })

    it('ArkUI_Gauge_Comp_0536', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.菜单项3是否选中', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindMenu.是否显示选中图标
    it('ArkUI_Gauge_Comp_0537', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项3是否选中', '通用属性4')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性4')
      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0538', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项3是否选中', '通用属性4')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 1,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0539', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项3是否选中', '通用属性4')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 2,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0540', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项3是否选中', '通用属性4')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性4')
      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 3,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0541', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项3是否选中', '通用属性4')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性4')
      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 4,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0542', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项3是否选中', '通用属性4')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性4')
      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      await Search('基础属性', 'bindMenu.菜单项3是否选中', '通用属性4')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindMenu.菜单项4是否选中
    it('ArkUI_Gauge_Comp_0543', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.菜单项4是否选中', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0544', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.菜单项4是否选中', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindMenu.是否显示选中图标
    it('ArkUI_Gauge_Comp_0545', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项4是否选中', '通用属性4')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性4')
      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0546', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项4是否选中', '通用属性4')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 1,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0547', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项4是否选中', '通用属性4')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 2,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0548', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项4是否选中', '通用属性4')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性4')
      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 3,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0549', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项4是否选中', '通用属性4')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性4')
      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 4,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0550', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项4是否选中', '通用属性4')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性4')
      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      await Search('基础属性', 'bindMenu.菜单项4是否选中', '通用属性4')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindMenu.item中是否显示右侧图标
    it('ArkUI_Gauge_Comp_0551', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.item中是否显示右侧图标', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0552', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.item中是否显示右侧图标', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindMenu.Opacity
    it('ArkUI_Gauge_Comp_0553', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.Opacity', '通用属性4')

      //取不到bindMenu属性值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindMenu.Visibility
    it('ArkUI_Gauge_Comp_0554', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.Visibility', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0555', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.Visibility', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()

    })

    // bindMenu.Padding
    it('ArkUI_Gauge_Comp_0556', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.Padding', '通用属性4')

      //取不到bindMenu属性值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindMenu.Margin
    it('ArkUI_Gauge_Comp_0557', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.Margin', '通用属性4')

      //取不到bindMenu属性值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // hoverEffect
    it('ArkUI_Gauge_Comp_0558', 0, async (done: Function) => {

      await titleSearch('基础属性', 'hoverEffect', '通用属性4')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hoverEffect', JsonType.value)
        ],
        assertEqual: 'HoverEffect.Scale'
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0559', 0, async (done: Function) => {

      await titleSearch('基础属性', 'hoverEffect', '通用属性4')

      await radioClick({
        radioClickObj: 2,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hoverEffect', JsonType.value)
        ],
        assertEqual: 'HoverEffect.Highlight'
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0560', 0, async (done: Function) => {

      await titleSearch('基础属性', 'hoverEffect', '通用属性4')


      await radioClick({
        radioClickObj: 3,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hoverEffect', JsonType.value)
        ],
        assertEqual: 'HoverEffect.None'
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0561', 0, async (done: Function) => {

      await titleSearch('基础属性', 'hoverEffect', '通用属性4')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hoverEffect', JsonType.value)
        ],
        assertEqual: 'HoverEffect.Auto'
      })

      done()
    })

    // id
    it('ArkUI_Gauge_Comp_0562', 0, async (done: Function) => {

      await titleSearch('基础属性', 'id', '通用属性4')

      // key优先级比id高会覆盖
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()

    })

    it('ArkUI_Gauge_Comp_0563', 0, async (done: Function) => {

      await titleSearch('基础属性', 'id', '通用属性4')

      // key优先级比id高会覆盖
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()

    })

    // key
    it('ArkUI_Gauge_Comp_0564', 0, async (done: Function) => {

      await titleSearch('基础属性', 'key', '通用属性4')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: '2',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('id', JsonType.value)
        ],
        assertEqual: '2'
      })

      done()

    })

    it('ArkUI_Gauge_Comp_0565', 0, async (done: Function) => {

      await titleSearch('基础属性', 'key', '通用属性4')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: '1',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('id', JsonType.value)
        ],
        assertEqual: '1'
      })

      done()
    })

    // reuseId
    it('ArkUI_Gauge_Comp_0566', 0, async (done: Function) => {

      await titleSearch('基础属性', 'reuseId', '通用属性4')

      // 取不到reuseId属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0567', 0, async (done: Function) => {

      await titleSearch('基础属性', 'reuseId', '通用属性4')

      // 取不到reuseId属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // restoreId
    it('ArkUI_Gauge_Comp_0568', 0, async (done: Function) => {

      await titleSearch('基础属性', 'restoreId', '通用属性4')

      // 取不到restoreId属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'restoreId'
        }
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0569', 0, async (done: Function) => {

      await titleSearch('基础属性', 'restoreId', '通用属性4')

      // 取不到restoreId属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'restoreId'
        }
      })

      done()
    })

    // foregroundEffect.radius
    it('ArkUI_Gauge_Comp_0570', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundEffect.radius', '通用属性5')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('foregroundEffect', JsonType.obj),
          new KeyStruct('radius', JsonType.value)
        ],
        assertEqual: '100.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('foregroundEffect', JsonType.obj),
          new KeyStruct('radius', JsonType.value)
        ],
        assertEqual: '0.000000'
      })

      done()
    })

    // foregroundBlurStyle.value
    it('ArkUI_Gauge_Comp_0571', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0572', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 1,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0573', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 2,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0574', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 3,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0575', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 4,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0576', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 5,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0577', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 6,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0578', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 7,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0579', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 8,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0580', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')


      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 9,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0581', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')


      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 10,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0582', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')


      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 11,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // foregroundBlurStyle.options.colorMode
    it('ArkUI_Gauge_Comp_0583', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.options.colorMode', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0584', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.options.colorMode', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 2,
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0585', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.options.colorMode', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // foregroundBlurStyle.options.adaptiveColor
    it('ArkUI_Gauge_Comp_0586', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.options.adaptiveColor', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0587', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.options.adaptiveColor', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // foregroundBlurStyle.options.blurOptions
    it('ArkUI_Gauge_Comp_0588', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.options.blurOptions', '通用属性5')

      // 取不到foregroundBlurStyle值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // foregroundBlurStyle.options.scale
    it('ArkUI_Gauge_Comp_0589', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.options.blurOptions', '通用属性5')

      // 取不到foregroundBlurStyle值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // motionBlur.radius
    it('ArkUI_Gauge_Comp_0590', 0, async (done: Function) => {

      await titleSearch('基础属性', 'motionBlur.radius', '通用属性5')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('motionBlur', JsonType.obj),
          new KeyStruct('radius', JsonType.value),
        ],
        assertEqual: 100
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('motionBlur', JsonType.obj),
          new KeyStruct('radius', JsonType.value),
        ],
        assertEqual: 0
      })

      done()
    })

    // motionBlur.anchorX
    it('ArkUI_Gauge_Comp_0591', 0, async (done: Function) => {

      await titleSearch('基础属性', 'motionBlur.anchorX', '通用属性5')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('motionBlur', JsonType.obj),
          new KeyStruct('anchor', JsonType.obj),
          new KeyStruct('x', JsonType.value)
        ],
        assertEqual: 1
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('motionBlur', JsonType.obj),
          new KeyStruct('anchor', JsonType.obj),
          new KeyStruct('x', JsonType.value)
        ],
        assertEqual: 0
      })

      done()
    })

    // motionBlur.anchorY
    it('ArkUI_Gauge_Comp_0592', 0, async (done: Function) => {

      await titleSearch('基础属性', 'motionBlur.anchorY', '通用属性5')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('motionBlur', JsonType.obj),
          new KeyStruct('anchor', JsonType.obj),
          new KeyStruct('y', JsonType.value)
        ],
        assertEqual: 1
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('motionBlur', JsonType.obj),
          new KeyStruct('anchor', JsonType.obj),
          new KeyStruct('y', JsonType.value)
        ],
        assertEqual: 0
      })

      done()
    })

    // clickEffect
    it('ArkUI_Gauge_Comp_0593', 0, async (done: Function) => {

      await titleSearch('基础属性', 'clickEffect', '通用属性5')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0594', 0, async (done: Function) => {

      await titleSearch('基础属性', 'clickEffect', '通用属性5')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    //clickEffect.level
    it('ArkUI_Gauge_Comp_0595', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('clickEffect.level'))

      if (!title) {

        await Search('基础属性', 'clickEffect', '通用属性5')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'clickEffect.level', '通用属性5')


      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('clickEffect', JsonType.obj),
          new KeyStruct('level', JsonType.value),
        ],
        assertEqual: '1'
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0596', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('clickEffect.level'))

      if (!title) {

        await Search('基础属性', 'clickEffect', '通用属性5')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'clickEffect.level', '通用属性5')

      await radioClick({
        radioClickObj: 2,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('clickEffect', JsonType.obj),
          new KeyStruct('level', JsonType.value),
        ],
        assertEqual: '2'
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0597', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('clickEffect.level'))

      if (!title) {

        await Search('基础属性', 'clickEffect', '通用属性5')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'clickEffect.level', '通用属性5')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('clickEffect', JsonType.obj),
          new KeyStruct('level', JsonType.value),
        ],
        assertEqual: '0'
      })

      done()
    })

    // clickEffect.scale
    it('ArkUI_Gauge_Comp_0598', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('clickEffect.scale'))

      if (!title) {

        await Search('基础属性', 'clickEffect', '通用属性5')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'clickEffect.scale', '通用属性5')

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('clickEffect', JsonType.obj),
          new KeyStruct('scale', JsonType.value),
        ],
        assertEqual: '0.000000'
      })

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('clickEffect', JsonType.obj),
          new KeyStruct('scale', JsonType.value),
        ],
        assertEqual: '1.000000'
      })

      await Search('基础属性', 'clickEffect', '通用属性5')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })


      done()
    })

    // accessibilityGroup
    it('ArkUI_Gauge_Comp_0599', 0, async (done: Function) => {

      await titleSearch('基础属性', 'accessibilityGroup', '通用属性5')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('accessibilityGroup', JsonType.value),
        ],
        assertEqual: true
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0600', 0, async (done: Function) => {

      await titleSearch('基础属性', 'accessibilityGroup', '通用属性5')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('accessibilityGroup', JsonType.value),
        ],
        assertEqual: false
      })

      done()
    })

    //accessibilityText
    it('ArkUI_Gauge_Comp_0601', 0, async (done: Function) => {

      await titleSearch('基础属性', 'accessibilityText', '通用属性5')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('accessibilityText', JsonType.value),
        ],
        assertEqual: '组件被选中时，仅播报无障碍文本内容'
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0602', 0, async (done: Function) => {

      await titleSearch('基础属性', 'accessibilityText', '通用属性5')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('accessibilityText', JsonType.value),
        ],
        assertEqual: '无障碍文本'
      })

      done()
    })

    // accessibilityDescription
    it('ArkUI_Gauge_Comp_0603', 0, async (done: Function) => {

      await titleSearch('基础属性', 'accessibilityDescription', '通用属性5')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('accessibilityDescription', JsonType.value),
        ],
        assertEqual: '用于为用户进一步说明当前组件'
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0604', 0, async (done: Function) => {

      await titleSearch('基础属性', 'accessibilityDescription', '通用属性5')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('accessibilityDescription', JsonType.value),
        ],
        assertEqual: '无障碍说明'
      })

      done()
    })

    // accessibilityLevel
    it('ArkUI_Gauge_Comp_0605', 0, async (done: Function) => {

      await titleSearch('基础属性', 'accessibilityLevel', '通用属性5')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'accessibilityLevel'
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('accessibilityLevel', JsonType.value),
        ],
        assertEqual: 'yes'
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0606', 0, async (done: Function) => {

      await titleSearch('基础属性', 'accessibilityLevel', '通用属性5')

      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'accessibilityLevel'
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('accessibilityLevel', JsonType.value),
        ],
        assertEqual: 'no'
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0607', 0, async (done: Function) => {

      await titleSearch('基础属性', 'accessibilityLevel', '通用属性5')

      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'accessibilityLevel'
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('accessibilityLevel', JsonType.value),
        ],
        assertEqual: 'no-hide-descendants'
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0608', 0, async (done: Function) => {

      await titleSearch('基础属性', 'accessibilityLevel', '通用属性5')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'accessibilityLevel'
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('accessibilityLevel', JsonType.value),
        ],
        assertEqual: 'auto'
      })

      done()
    })

    // attributeModifier
    it('ArkUI_Gauge_Comp_0609', 0, async (done: Function) => {

      await titleSearch('基础属性', 'attributeModifier', '通用属性5')

      // 取不到attributeModifier属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'attributeModifier'
        }
      })

      done()
    })

    it('ArkUI_Gauge_Comp_0610', 0, async (done: Function) => {

      await titleSearch('基础属性', 'attributeModifier', '通用属性5')

      // 取不到attributeModifier属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'attributeModifier'
        }
      })

      done()
    })

    //gestureModifier
    /*
    * 测试组件gestureModifier支持设置为true且获取属性正确
    */
    it('ArkUI_Gauge_Comp_0611', 0, async (done: Function) => {
      // 无法取到属性值
      await titleSearch('基础属性', 'gestureModifier', '通用属性6')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
    *测试组件gestureModifier支持设置包含单个子组件为false且获取属性正确
    */
    it('ArkUI_Gauge_Comp_0612', 0, async (done: Function) => {
      // 无法取到属性值
      await titleSearch('基础属性', 'gestureModifier', '通用属性6')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //outline.value.width
    it('ArkUI_Gauge_Comp_0613', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.width', '通用属性6')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('outlineWidth', JsonType.value)
        ],
        assertEqual: '32.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('outlineWidth', JsonType.value)
        ],
        assertEqual: '0.00vp'
      })
      done();
    })
    //outline.value.color
    /**
     * 测试组件outline.value.color支持设置量规图的颜色为1号色显示且获取属性正确
     */
    it('ArkUI_Gauge_Comp_0614', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.color', '通用属性6')
      await buttonClick({
        buttonClickObj: 0,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('outlineColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })
      done();
    })
    /*
     * 测试组件outline.value.color支持设置量规图的颜色为2号色显示且获取属性正确
    */
    it('ArkUI_Gauge_Comp_0615', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.color', '通用属性6')
      await buttonClick({
        buttonClickObj: 1,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('outlineColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })
      done();
    })
    /**
     * 测试组件outline.value.color支持设置量规图的颜色为3号色显示且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0616', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.color', '通用属性6')
      await buttonClick({
        buttonClickObj: 2,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('outlineColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();

    })
    /*
     * 测试组件outline.value.color支持设置量规图的颜色为4号色显示且获取属性正确
    */
    it('ArkUI_Gauge_Comp_0617', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.color', '通用属性6')
      await buttonClick({
        buttonClickObj: 3,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('outlineColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })
      done();
    })
    /**
     * 测试组件outline.value.color支持设置量规图的颜色为5号色显示且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0618', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.color', '通用属性6')
      await buttonClick({
        buttonClickObj: 4,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('outlineColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })
      done();
    })
    /**
     * 测试组件outline.value.color支持设置量规图的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_Gauge_Comp_0619', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.color', '通用属性6')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('outlineColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })
      done();
    })
    /*
     * outline.value.radius
    */
    it('ArkUI_Gauge_Comp_0620', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.radius', '通用属性6')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('outlineRadius', JsonType.value)
        ],
        assertEqual: '32.00vp'
      })
      await sliderDrag({
        slideStar: Slide.end,
        id: 'Gauge',
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('outlineRadius', JsonType.value)
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
    //outline.value.style
    /*
     * 测试组件outline.value.style支持设置SOLID且获取属性正确
    */
    it('ArkUI_Gauge_Comp_0621', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.style', '通用属性6')
      await radioClick({
        radioClickObj: 0,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('outlineStyle', JsonType.value)
        ],
        assertEqual: 'OutlineStyle.SOLID'
      })
      done();
    })
    /*
    *测试组件outline.value.style支持设置DASHED且获取属性正确
    */
    it('ArkUI_Gauge_Comp_0622', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.style', '通用属性6')
      await radioClick({
        radioClickObj: 1,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('outlineStyle', JsonType.value)
        ],
        assertEqual: 'OutlineStyle.DASHED'
      })
      done();
    })
    /*
    *测试组件outline.value.style支持设置DOTTED且获取属性正确
    */
    it('ArkUI_Gauge_Comp_0623', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.style', '通用属性6')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('outlineStyle', JsonType.value)
        ],
        assertEqual: 'OutlineStyle.DOTTED'
      })
      done();
    })
    /*
     * outline.value.width展开属性测试完成，关闭outline.value.width，无需断言
     * */
    it('ArkUI_Gauge_Comp_0624', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.width', '通用属性6')
      await getToggle(ToggleClick.Close)
      done();
    })
    // visualEffect
    /*
     *测试组件visualEffect支持设置true且获取属性正确
    */
    it('ArkUI_Gauge_Comp_0625', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'visualEffect', '通用属性6')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })
    /*
    *测试组件visualEffect支持设置false且获取属性正确
   */
    it('ArkUI_Gauge_Comp_0626', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'visualEffect', '通用属性6')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })
      done();
    })
    //backgroundFilter
    /*
    *测试组件backgroundFilter支持设置true且获取属性正确
    */
    it('ArkUI_Gauge_Comp_0627', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'backgroundFilter', '通用属性6')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
    *测试组件backgroundFilter支持设置false且获取属性正确
    */
    it('ArkUI_Gauge_Comp_0628', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'backgroundFilter', '通用属性6')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //foregroundFilter
    /*
    *测试组件foregroundFilter支持设置true且获取属性正确
    */
    it('ArkUI_Gauge_Comp_0629', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'foregroundFilter', '通用属性6')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
    *测试组件foregroundFilter支持设置false且获取属性正确
    */
    it('ArkUI_Gauge_Comp_0630', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'foregroundFilter', '通用属性6')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //compositingFilter
    /*
    *测试组件compositingFilter支持设置true且获取属性正确
    */
    it('ArkUI_Gauge_Comp_0631', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'compositingFilter', '通用属性6')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
    *测试组件compositingFilter支持设置false且获取属性正确
    */
    it('ArkUI_Gauge_Comp_0632', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'compositingFilter', '通用属性6')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //responseRegion.value.x
    it('ArkUI_Gauge_Comp_0633', 0, async (done: Function) => {
      //需要前置条件responseRegion.value.x、responseRegion.value.y、responseRegion.value.width、responseRegion.value.height四个toggle打开，获取不到参数值
      await titleSearch('基础属性', 'responseRegion.value.x', '通用属性6')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //responseRegion.value.y
    it('ArkUI_Gauge_Comp_0634', 0, async (done: Function) => {
      //需要前置条件responseRegion.value.x、responseRegion.value.y、responseRegion.value.width、responseRegion.value.height四个toggle打开，获取不到参数值
      await titleSearch('基础属性', 'responseRegion.value.y', '通用属性6')
      await sliderDrag({
        slideStar: Slide.start,
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //responseRegion.value.width
    /*
    * 测试组件responseRegion.value.width支持设置0%且获取属性正确
    */
    it('ArkUI_Gauge_Comp_0635', 0, async (done: Function) => {
      //需要前置条件responseRegion.value.x、responseRegion.value.y、responseRegion.value.width、responseRegion.value.height四个toggle打开，获取不到参数值
      await titleSearch('基础属性', 'responseRegion.value.width', '通用属性6')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'responseRegion.value.width'
        }
      })
      done();
    })
    /*
    * 测试组件responseRegion.value.width支持设置30%且获取属性正确
    */
    it('ArkUI_Gauge_Comp_0636', 0, async (done: Function) => {
      //需要前置条件responseRegion.value.x、responseRegion.value.y、responseRegion.value.width、responseRegion.value.height四个toggle打开，获取不到参数值
      await titleSearch('基础属性', 'responseRegion.value.width', '通用属性6')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'responseRegion.value.width'
        }
      })
      done();
    })
    /*
     * 测试组件responseRegion.value.width支持设置60%且获取属性正确
     */
    it('ArkUI_Gauge_Comp_0637', 0, async (done: Function) => {
      //需要前置条件responseRegion.value.x、responseRegion.value.y、responseRegion.value.width、responseRegion.value.height四个toggle打开，获取不到参数值
      await titleSearch('基础属性', 'responseRegion.value.width', '通用属性6')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'responseRegion.value.width'
        }
      })
      done();
    })
    /*
     * 测试组件responseRegion.value.width支持设置90%且获取属性正确
     */
    it('ArkUI_Gauge_Comp_0638', 0, async (done: Function) => {
      //需要前置条件responseRegion.value.x、responseRegion.value.y、responseRegion.value.width、responseRegion.value.height四个toggle打开，获取不到参数值
      await titleSearch('基础属性', 'responseRegion.value.width', '通用属性6')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'responseRegion.value.width'
        }
      })
      done();
    })
    /*
     * 测试组件responseRegion.value.width支持设置100%且获取属性正确
     */
    it('ArkUI_Gauge_Comp_0639', 0, async (done: Function) => {
      //需要前置条件responseRegion.value.x、responseRegion.value.y、responseRegion.value.width、responseRegion.value.height四个toggle打开，获取不到参数值
      await titleSearch('基础属性', 'responseRegion.value.width', '通用属性6')
      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'responseRegion.value.width'
        }
      })
      done();
    })
    //responseRegion.value.height
    /*
    * 测试组件responseRegion.value.height支持设置0%且获取属性正确
    */
    it('ArkUI_Gauge_Comp_0640', 0, async (done: Function) => {
      //需要前置条件responseRegion.value.x、responseRegion.value.y、responseRegion.value.width、responseRegion.value.height四个toggle打开，获取不到参数值
      await titleSearch('基础属性', 'responseRegion.value.height', '通用属性6')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'responseRegion.value.height'
        }
      })
      done();
    })
    /*
    * 测试组件responseRegion.value.height支持设置30%且获取属性正确
    */
    it('ArkUI_Gauge_Comp_0641', 0, async (done: Function) => {
      //需要前置条件responseRegion.value.x、responseRegion.value.y、responseRegion.value.width、responseRegion.value.height四个toggle打开，获取不到参数值
      await titleSearch('基础属性', 'responseRegion.value.height', '通用属性6')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'responseRegion.value.height'
        }
      })
      done();
    })
    /*
     * 测试组件responseRegion.value.height支持设置60%且获取属性正确
     */
    it('ArkUI_Gauge_Comp_0642', 0, async (done: Function) => {
      //需要前置条件responseRegion.value.x、responseRegion.value.y、responseRegion.value.width、responseRegion.value.height四个toggle打开，获取不到参数值
      await titleSearch('基础属性', 'responseRegion.value.height', '通用属性6')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'responseRegion.value.height'
        }
      })
      done();
    })
    /*
     * 测试组件responseRegion.value.height支持设置90%且获取属性正确
     */
    it('ArkUI_Gauge_Comp_0643', 0, async (done: Function) => {
      //需要前置条件responseRegion.value.x、responseRegion.value.y、responseRegion.value.width、responseRegion.value.height四个toggle打开，获取不到参数值
      await titleSearch('基础属性', 'responseRegion.value.height', '通用属性6')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'responseRegion.value.height'
        }
      })
      done();
    })
    /*
     * 测试组件responseRegion.value.height支持设置100%且获取属性正确
     */
    it('ArkUI_Gauge_Comp_0644', 0, async (done: Function) => {
      //需要前置条件responseRegion.value.x、responseRegion.value.y、responseRegion.value.width、responseRegion.value.height四个toggle打开，获取不到参数值
      await titleSearch('基础属性', 'responseRegion.value.height', '通用属性6')
      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'responseRegion.value.height'
        }
      })
      done();
    })
    //hitTestBehavior
    /*
     * 测试组件hitTestBehavior支持设置Default且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0645', 0, async (done: Function) => {
      await titleSearch('基础属性', 'hitTestBehavior', '通用属性6')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'hitTestBehavior'
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hitTestBehavior', JsonType.value)
        ],
        assertEqual: 'HitTestMode.Default'
      })
      done();
    })
    /*
     * 测试组件hitTestBehavior支持设置Block且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0646', 0, async (done: Function) => {
      await titleSearch('基础属性', 'hitTestBehavior', '通用属性6')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'hitTestBehavior'
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hitTestBehavior', JsonType.value)
        ],
        assertEqual: 'HitTestMode.Block'
      })
      done();
    })
    /*
     * 测试组件hitTestBehavior支持设置Transparent且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0647', 0, async (done: Function) => {
      await titleSearch('基础属性', 'hitTestBehavior', '通用属性6')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'hitTestBehavior'
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hitTestBehavior', JsonType.value)
        ],
        assertEqual: 'HitTestMode.Transparent'
      })
      done();
    })
    /*
     * 测试组件hitTestBehavior支持设置None且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0648', 0, async (done: Function) => {
      await titleSearch('基础属性', 'hitTestBehavior', '通用属性6')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'hitTestBehavior'
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hitTestBehavior', JsonType.value)
        ],
        assertEqual: 'HitTestMode.None'
      })
      done();
    })
    //bindContentCover.isShow
    /*
     * 测试组件bindContentCover.isShow支持设置true且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0649', 0, async (done: Function) => {
      //无法获取属性
      await titleSearch('基础属性', 'bindContentCover.isShow', '通用属性7')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })
    /*
     * 测试组件bindContentCover.isShow支持设置false且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0650', 0, async (done: Function) => {
      //无法获取属性
      await titleSearch('基础属性', 'bindContentCover.isShow', '通用属性7')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })
    // bindContentCover.options.modalTransition
    /*
     * 测试组件bindContentCover.options.modalTransition支持设置DEAULT且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0651', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.modalTransition', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.modalTransition', '通用属性7')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.modalTransition支持设置NONE且获取属性正确
     */
    it('ArkUI_Gauge_Comp_0652', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.modalTransition', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.modalTransition', '通用属性7')
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })
    /*
    * 测试组件bindContentCover.options.modalTransition支持设置ALPHA且获取属性正确
    */
    it('ArkUI_Gauge_Comp_0653', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.modalTransition', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.modalTransition', '通用属性7')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover.options.transition.opacity
    it('ArkUI_Gauge_Comp_0654', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.opacity', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.opacity', '通用属性7')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover.options.transition.translate.x
    it('ArkUI_Gauge_Comp_0655', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.translate.x', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.translate.x', '通用属性7')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover.options.transition.translate.y
    it('ArkUI_Gauge_Comp_0656', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.translate.y', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.translate.y', '通用属性7')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover.options.transition.translate.z
    it('ArkUI_Gauge_Comp_0657', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.translate.z', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.translate.z', '通用属性7')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        id: 'Gauge_Comp_',
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover.options.transition.scale.x
    it('ArkUI_Gauge_Comp_0658', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.scale.x', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.scale.x', '通用属性7')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover.options.transition.scale.y
    it('ArkUI_Gauge_Comp_0659', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.scale.y', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.scale.y', '通用属性7')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })
      done();
    })
    //bindContentCover.options.transition.scale.z
    it('ArkUI_Gauge_Comp_0660', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.scale.z', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.scale.z', '通用属性7')
      await sliderDrag({
        slideStar: Slide.start,
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })
      done();
    })
    //bindContentCover.options.transition.scale.centerX
    it('ArkUI_Gauge_Comp_0661', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.scale.centerX', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.scale.centerX', '通用属性7')
      await sliderDrag({
        slideStar: Slide.start,
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover.options.transition.scale.centerY
    it('ArkUI_Gauge_Comp_0662', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.scale.centerY', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.scale.centerY', '通用属性7')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover.options.transition.rotate.x
    it('ArkUI_Gauge_Comp_0663', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.rotate.x', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.rotate.x', '通用属性7')
      await sliderDrag({
        slideStar: Slide.start,
      })
      await sliderDrag({
        slideStar: Slide.end,
        id: 'Gauge_Comp',
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover.options.transition.rotate.y
    it('ArkUI_Gauge_Comp_0664', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.rotate.y', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.rotate.y', '通用属性7')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover.options.transition.rotate.z
    it('ArkUI_Gauge_Comp_0665', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.rotate.z', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.rotate.z', '通用属性7')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover.options.transition.rotate.centerX
    it('ArkUI_Gauge_Comp_0666', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.rotate.centerX', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.rotate.centerX', '通用属性7')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover.options.transition.rotate.centerY
    it('ArkUI_Gauge_Comp_0667', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.rotate.centerY', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.rotate.centerY', '通用属性7')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover.options.transition.rotate.centerZ
    it('ArkUI_Gauge_Comp_0668', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.rotate.centerZ', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.rotate.centerZ', '通用属性7')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    // bindContentCover.options.transition.rotate.perspective
    it('ArkUI_Gauge_Comp_0669', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.rotate.perspective',
        '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.rotate.perspective', '通用属性7')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover.options.transition.move
    /*
     * 测试组件bindContentCover.options.transition.move支持设置TOP且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0670', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.move', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.move', '通用属性7')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.move支持设置BOTTOM且获取属性正确
     */
    it('ArkUI_Gauge_Comp_0671', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.move', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.move', '通用属性7')
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })
    /*
    * 测试组件bindContentCover.options.transition.move支持设置START且获取属性正确
    */
    it('ArkUI_Gauge_Comp_0672', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.move', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.move', '通用属性7')
      await radioClick({
        radioClickObj: 2
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.move支持设置END且获取属性正确
     */
    it('ArkUI_Gauge_Comp_0673', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.move', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.move', '通用属性7')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover.options.transition.animation.duration
    it('ArkUI_Gauge_Comp_0674', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.duration',
        '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.duration', '通用属性7')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover.options.transition.animation.tempo
    it('ArkUI_Gauge_Comp_0675', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.tempo', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.tempo', '通用属性7')
      await sliderDrag({
        slideStar: Slide.start,
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover.options.transition.animation.curve
    /*
     * 测试组件bindContentCover.options.transition.animation.curve支持设置Linear且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0676', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.curve支持设置Ease且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0677', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.curve支持设置EaseIn且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0678', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await radioClick({
        radioClickObj: 2
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.curve支持设置EaseOut且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0679', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await radioClick({
        radioClickObj: 3
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.curve支持设置EaseInOut且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0680', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await radioClick({
        radioClickObj: 4
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.curve支持设置FastOutSlowIn且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0681', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await radioClick({
        radioClickObj: 5
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.curve支持设置LinearOutSlowIn且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0682', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await radioClick({
        radioClickObj: 6
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.curve支持设置FastOutLinearIn且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0683', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await radioClick({
        radioClickObj: 7
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.curve支持设置ExtremeDeceleration且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0684', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await radioClick({
        radioClickObj: 8
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.curve支持设置Sharp且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0685', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await radioClick({
        radioClickObj: 9
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.curve支持设置Rhythm且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0686', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await radioClick({
        radioClickObj: 10
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.curve支持设置Smooth且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0687', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await radioClick({
        radioClickObj: 11
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.curve支持设置Friction且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0688', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await radioClick({
        radioClickObj: 12,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover.options.transition.animation.delay
    it('ArkUI_Gauge_Comp_0689', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.delay', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.delay', '通用属性7')
      await sliderDrag({
        slideStar: Slide.start,
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover.options.transition.animation.iterations
    it('ArkUI_Gauge_Comp_0690', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.iterations',
        '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.iterations', '通用属性7')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover.options.transition.animation.playMode
    /*
     * 测试组件bindContentCover.options.transition.animation.playMode支持设置Normal且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0691', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.playMode',
        '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.playMode', '通用属性7')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.playMode支持设置Reverse且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0692', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.playMode',
        '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.playMode', '通用属性7')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.playMode支持设置Alternate且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0693', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.playMode',
        '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.playMode', '通用属性7')
      await radioClick({
        radioClickObj: 2
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.playMode支持设置AlternateReverse且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0694', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.playMode',
        '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.playMode', '通用属性7')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover.options.transition.animation.expectedFrameRateRange.max
    it('ArkUI_Gauge_Comp_0695', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow',
        'bindContentCover.options.transition.animation.expectedFrameRateRange.max', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.expectedFrameRateRange.max',
        '通用属性7')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })
      done();
    })
    //bindContentCover.options.transition.animation.expectedFrameRateRange.min
    it('ArkUI_Gauge_Comp_0696', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow',
        'bindContentCover.options.transition.animation.expectedFrameRateRange.min', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.expectedFrameRateRange.min',
        '通用属性7')
      await sliderDrag({
        slideStar: Slide.start,
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover.options.transition.animation.expectedFrameRateRange.expected
    it('ArkUI_Gauge_Comp_0697', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow',
        'bindContentCover.options.transition.animation.expectedFrameRateRange.expected', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.expectedFrameRateRange.expected',
        '通用属性7')
      await sliderDrag({
        slideStar: Slide.start,
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover相关属性测试完毕，关闭bindContentCover.isShow Toggle,无需断言
    it('ArkUI_Gauge_Comp_0698', 0, async (done: Function) => {
      await titleSearch('基础属性', 'bindContentCover.isShow', '通用属性7')
      await getToggle(ToggleClick.Close)
      done();
    })
    //bindSheet.isShow
    /*
     * 测试组件bindSheet.isShow支持设置true且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0699', 0, async (done: Function) => {
      //无法获取属性
      await titleSearch('基础属性', 'bindSheet.isShow', '通用属性7')
      await radioClick({
        radioClickObj: 0
      })
      await driver.delayMs(1000);
      await driver.click(645, 115)
      done();
    })
    /*
     * 测试组件bindSheet.isShow支持设置false且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0700', 0, async (done: Function) => {
      //无法获取属性
      await titleSearch('基础属性', 'bindSheet.isShow', '通用属性7')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })
    //bindSheet.options.height
    /*
     * 测试组件bindSheet.options.height支持设置MEDIUM且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0701', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.height', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.height', '通用属性7')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.height支持设置LARGE且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0702', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.height', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.height', '通用属性7')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.height支持设置FIT_CONTENT且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0703', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.height', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.height', '通用属性7')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindSheet.options.detents
    /*
     * 测试组件bindSheet.options.detents支持设置MEDIUM,LARGE,FIT_CONTENT且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0704', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.detents', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.detents', '通用属性7')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.detents支持设置LARGE,FIT_CONTENT且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0705', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.detents', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.detents', '通用属性7')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.detents支持设置FIT_CONTENT且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0706', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.detents', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.detents', '通用属性7')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindSheet.options.preferType
    /*
     * 测试组件bindSheet.options.preferType支持设置BOTTOM且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0707', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.preferType', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.preferType', '通用属性7')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.preferType支持设置CENTER且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0708', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.preferType', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.preferType', '通用属性7')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.preferType支持设置POPUP且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0709', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.preferType', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.preferType', '通用属性7')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindSheet.options.showClose
    /*
     * 测试组件bindSheet.options.showClose支持设置true且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0710', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.showClose', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.showClose', '通用属性7')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.showClose支持设置false且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0711', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.showClose', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.showClose', '通用属性7')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindSheet.options.dragBar
    /*
     * 测试组件bindSheet.options.dragBar支持设置true且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0712', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.dragBar', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.dragBar', '通用属性7')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.dragBar支持设置false且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0713', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.dragBar', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.dragBar', '通用属性7')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindSheet.options.blurStyle
    /*
     * 测试组件bindSheet.options.blurStyle支持设置Thin且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0714', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.blurStyle', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.blurStyle', '通用属性7')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.blurStyle支持设置Regular且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0715', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.blurStyle', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.blurStyle', '通用属性7')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.blurStyle支持设置Thick且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0716', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.blurStyle', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.blurStyle', '通用属性7')
      await radioClick({
        radioClickObj: 2
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.blurStyle支持设置BACKGROUND_THIN且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0717', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.blurStyle', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.blurStyle', '通用属性7')
      await radioClick({
        radioClickObj: 3
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.blurStyle支持设置BACKGROUND_REGULAR且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0718', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.blurStyle', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.blurStyle', '通用属性7')
      await radioClick({
        radioClickObj: 4
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.blurStyle支持设置BACKGROUND_THICK且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0719', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.blurStyle', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.blurStyle', '通用属性7')
      await radioClick({
        radioClickObj: 5
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.blurStyle支持设置BACKGROUND_ULTRA_THICK且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0720', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.blurStyle', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.blurStyle', '通用属性7')
      await radioClick({
        radioClickObj: 6
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.blurStyle支持设置NONE且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0721', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.blurStyle', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.blurStyle', '通用属性7')
      await radioClick({
        radioClickObj: 7
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.blurStyle支持设置COMPONENT_ULTRA_THIN且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0722', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.blurStyle', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.blurStyle', '通用属性7')
      await radioClick({
        radioClickObj: 8
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.blurStyle支持设置COMPONENT_THIN且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0723', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.blurStyle', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.blurStyle', '通用属性7')
      await radioClick({
        radioClickObj: 9
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.blurStyle支持设置COMPONENT_REGULAR且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0724', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.blurStyle', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.blurStyle', '通用属性7')
      await radioClick({
        radioClickObj: 10
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.blurStyle支持设置COMPONENT_THICK且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0725', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.blurStyle', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.blurStyle', '通用属性7')
      await radioClick({
        radioClickObj: 11
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.blurStyle支持设置COMPONENT_ULTRA_THICK且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0726', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.blurStyle', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.blurStyle', '通用属性7')
      await radioClick({
        radioClickObj: 12,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindSheet.options.maskColor
    /**
     * 测试组件bindSheet.options.maskColor支持设置量规图的颜色为1号色显示且获取属性正确
     */
    it('ArkUI_Gauge_Comp_0727', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.maskColor', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.maskColor', '通用属性7')
      await buttonClick({
        buttonClickObj: 0
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.maskColor支持设置量规图的颜色为2号色显示且获取属性正确
    */
    it('ArkUI_Gauge_Comp_0728', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.maskColor', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.maskColor', '通用属性7')
      await buttonClick({
        buttonClickObj: 1
      })
      done();
    })
    /**
     * 测试组件bindSheet.options.maskColor支持设置量规图的颜色为3号色显示且获取属性正确*/
    it('ArkUI_Gauge_Comp_0729', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.maskColor', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.maskColor', '通用属性7')
      await buttonClick({
        buttonClickObj: 2
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.maskColor支持设置量规图的颜色为4号色显示且获取属性正确
    */
    it('ArkUI_Gauge_Comp_0730', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.maskColor', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.maskColor', '通用属性7')
      await buttonClick({
        buttonClickObj: 3
      })
      done();
    })
    /**
     * 测试组件bindSheet.options.maskColor支持设置量规图的颜色为5号色显示且获取属性正确*/
    it('ArkUI_Gauge_Comp_0731', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.maskColor', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.maskColor', '通用属性7')
      await buttonClick({
        buttonClickObj: 4
      })
      done();
    })
    /**
     * 测试组件bindSheet.options.maskColor支持设置量规图的颜色为6号色显示且获取属性正确*/
    it('ArkUI_Gauge_Comp_0732', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.maskColor', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.maskColor', '通用属性7')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    // bindSheet.options.title.title
    /*
     * 测试组件bindSheet.options.title.title支持设置true且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0733', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.title.title', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.title.title', '通用属性7')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.title.title支持设置false且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0734', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.title.title', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.title.title', '通用属性7')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindSheet.options.title.subtitle
    /*
     * 测试组件bindSheet.options.title.subtitle支持设置true且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0735', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.title.subtitle', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.title.subtitle', '通用属性7')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.title.subtitle支持设置false且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0736', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.title.subtitle', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.title.subtitle', '通用属性7')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindSheet.options.enableOutsideInteractive
    /*
     * 测试组件bindSheet.options.enableOutsideInteractive支持设置true且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0737', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.enableOutsideInteractive', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.enableOutsideInteractive', '通用属性7')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.enableOutsideInteractive支持设置false且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0738', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.enableOutsideInteractive', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.enableOutsideInteractive', '通用属性7')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindSheet.options.borderWidth
    it('ArkUI_Gauge_Comp_0739', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.borderWidth', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.borderWidth', '通用属性7')
      await sliderDrag({
        slideStar: Slide.start,
        slideDragObj: 0
      })
      await sliderDrag({
        slideStar: Slide.end,
        slideDragObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindSheet.options.borderColor
    /**
     * 测试组件bindSheet.options.borderColor支持设置量规图的颜色为1号色显示且获取属性正确
     */
    it('ArkUI_Gauge_Comp_0740', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.borderColor', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.borderColor', '通用属性7')
      await buttonClick({
        buttonClickObj: 0
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.borderColor支持设置量规图的颜色为2号色显示且获取属性正确
    */
    it('ArkUI_Gauge_Comp_0741', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.borderColor', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.borderColor', '通用属性7')
      await buttonClick({
        buttonClickObj: 1
      })
      done();
    })
    /**
     * 测试组件bindSheet.options.borderColor支持设置量规图的颜色为3号色显示且获取属性正确*/
    it('ArkUI_Gauge_Comp_0742', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.borderColor', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.borderColor', '通用属性7')
      await buttonClick({
        buttonClickObj: 2
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.borderColor支持设置量规图的颜色为4号色显示且获取属性正确
    */
    it('ArkUI_Gauge_Comp_0743', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.borderColor', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.borderColor', '通用属性7')
      await buttonClick({
        buttonClickObj: 3
      })
      done();
    })
    /**
     * 测试组件bindSheet.options.borderColor支持设置量规图的颜色为5号色显示且获取属性正确*/
    it('ArkUI_Gauge_Comp_0744', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.borderColor', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.borderColor', '通用属性7')
      await buttonClick({
        buttonClickObj: 4
      })
      done();
    })
    /**
     * 测试组件bindSheet.options.borderColor支持设置量规图的颜色为6号色显示且获取属性正确*/
    it('ArkUI_Gauge_Comp_0745', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.borderColor', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.borderColor', '通用属性7')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindSheet.options.borderStyle
    /*
     * 测试组件bindSheet.options.borderStyle支持设置Dotted且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0746', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.borderStyle', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.borderStyle', '通用属性7')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.borderStyle支持设置Dashed且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0747', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.borderStyle', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.borderStyle', '通用属性7')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.borderStyle支持设置Solid且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0748', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.borderStyle', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.borderStyle', '通用属性7')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindSheet.options.width
    it('ArkUI_Gauge_Comp_0749', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.width', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.width', '通用属性7')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindSheet.options.shadow
    /*
     * 测试组件bindSheet.options.shadow支持设置OUTER_DEFAULT_XS且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0750', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.shadow', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.shadow', '通用属性7')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.shadow支持设置OUTER_DEFAULT_SM且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0751', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.shadow', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.shadow', '通用属性7')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.shadow支持设置OUTER_DEFAULT_MD且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0752', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.shadow', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.shadow', '通用属性7')
      await radioClick({
        radioClickObj: 2
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.shadow支持设置OUTER_DEFAULT_LG且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0753', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.shadow', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.shadow', '通用属性7')
      await radioClick({
        radioClickObj: 3
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.shadow支持设置OUTER_FLOATING_SM且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0754', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.shadow', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.shadow', '通用属性7')
      await radioClick({
        radioClickObj: 4
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.shadow支持设置OUTER_FLOATING_MD且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0755', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.shadow', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.shadow', '通用属性7')
      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindSheet.options.mode
    /*
     * 测试组件bindSheet.options.mode支持设置OVERLAY且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0756', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.mode', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.mode', '通用属性7')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.mode支持设置EMBEDDED且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0757', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.mode', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.mode', '通用属性7')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindSheet.options.scrollSizeMode
    /*
     * 测试组件bindSheet.options.scrollSizeMode支持设置DOLLOW_DETENT且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0758', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.scrollSizeMode', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.scrollSizeMode', '通用属性7')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.scrollSizeMode支持设置CONTINUOUS且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0759', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.scrollSizeMode', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.scrollSizeMode', '通用属性7')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindSheet相关属性测试完毕，关闭bindSheet.isShow开关，无需断言
    it('ArkUI_Gauge_Comp_0760', 0, async (done: Function) => {
      await titleSearch('基础属性', 'bindSheet.isShow', '通用属性7')
      await getToggle(ToggleClick.Close)
      done();
    })
    // obscured
    /*
     * 测试组件obscured支持设置null且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0761', 0, async (done: Function) => {
      //获取不到属性值无法进行断言
      await titleSearch('基础属性', 'obscured', '通用属性7')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件obscured支持设置PLACEHOLDER且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0762', 0, async (done: Function) => {
      //获取不到属性值无法进行断言
      await titleSearch('基础属性', 'obscured', '通用属性7')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //renderFit
    /*
     * 测试组件renderFit支持设置CENTER且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0763', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 0,
        id: "Gauge",
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderFit', JsonType.value)
        ],
        assertEqual: 'RenderFit.CENTER'
      })
      done();
    })
    /*
     * 测试组件renderFit支持设置TOP且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0764', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 1,
        id: "Gauge",
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderFit', JsonType.value)
        ],
        assertEqual: 'RenderFit.TOP'
      })
      done();
    })
    /*
     * 测试组件renderFit支持设置BOTTOM且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0765', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 2,
        id: "Gauge",
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderFit', JsonType.value)
        ],
        assertEqual: 'RenderFit.BOTTOM'
      })
      done();
    })
    /*
     * 测试组件renderFit支持设置LEFT且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0766', 0, async (done: Function) => {
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 3,
        id: "Gauge",
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderFit', JsonType.value)
        ],
        assertEqual: 'RenderFit.LEFT'
      })
      done();
    })
    /*
     * 测试组件renderFit支持设置RIGHT且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0767', 0, async (done: Function) => {
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 4,
        id: "Gauge",
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderFit', JsonType.value)
        ],
        assertEqual: 'RenderFit.RIGHT'
      })
      done();
    })
    /*
     * 测试组件renderFit支持设置TOP_LEFT且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0768', 0, async (done: Function) => {
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 5,
        id: "Gauge",
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderFit', JsonType.value)
        ],
        assertEqual: 'RenderFit.TOP_LEFT'
      })
      done();
    })
    /*
     * 测试组件renderFit支持设置TOP_RIGHT且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0769', 0, async (done: Function) => {
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 6,
        id: "Gauge",
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderFit', JsonType.value)
        ],
        assertEqual: 'RenderFit.TOP_RIGHT'
      })
      done();
    })
    /*
     * 测试组件renderFit支持设置BOTTOM_LEFT且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0770', 0, async (done: Function) => {
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 7,
        id: "Gauge",
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderFit', JsonType.value)
        ],
        assertEqual: 'RenderFit.BOTTOM_LEFT'
      })
      done();
    })
    /*
     * 测试组件renderFit支持设置BOTTOM_RIGHT且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0771', 0, async (done: Function) => {
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 8,
        id: "Gauge",
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderFit', JsonType.value)
        ],
        assertEqual: 'RenderFit.BOTTOM_RIGHT'
      })
      done();
    })
    /*
     * 测试组件renderFit支持设置RESIZE_FILL且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0772', 0, async (done: Function) => {
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 9,
        id: "Gauge",
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderFit', JsonType.value)
        ],
        assertEqual: 'RenderFit.RESIZE_FILL'
      })
      done();
    })
    /*
     * 测试组件renderFit支持设置RESIZE_CONTAIN且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0773', 0, async (done: Function) => {
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 10,
        id: "Gauge",
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderFit', JsonType.value)
        ],
        assertEqual: 'RenderFit.RESIZE_CONTAIN'
      })
      done();
    })
    /*
     * 测试组件renderFit支持设置RESIZE_CONTAIN_TOP_LEFT且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0774', 0, async (done: Function) => {
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 11,
        id: "Gauge",
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderFit', JsonType.value)
        ],
        assertEqual: 'RenderFit.RESIZE_CONTAIN_TOP_LEFT'
      })
      done();
    })
    /*
     * 测试组件renderFit支持设置RESIZE_CONTAIN_BOTTOM_RIGHT且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0775', 0, async (done: Function) => {
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 12,
        id: "Gauge",
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderFit', JsonType.value)
        ],
        assertEqual: 'RenderFit.RESIZE_CONTAIN_BOTTOM_RIGHT'
      })
      done();
    })
    /*
     * 测试组件renderFit支持设置RESIZE_COVER且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0776', 0, async (done: Function) => {
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 13,
        id: "Gauge",
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderFit', JsonType.value)
        ],
        assertEqual: 'RenderFit.RESIZE_COVER'
      })
      done();
    })
    /*
     * 测试组件renderFit支持设置RESIZE_COVER_TOP_LEFT且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0777', 0, async (done: Function) => {
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 14,
        id: "Gauge",
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderFit', JsonType.value)
        ],
        assertEqual: 'RenderFit.RESIZE_COVER_TOP_LEFT'
      })
      done();
    })
    /*
     * 测试组件renderFit支持设置RESIZE_COVER_BOTTOM_RIGHT且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0778', 0, async (done: Function) => {
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 15,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: "Gauge",
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderFit', JsonType.value)
        ],
        assertEqual: 'RenderFit.RESIZE_COVER_BOTTOM_RIGHT'
      })
      done();
    })
    // monopolizeEvents
    /*
     * 测试组件monopolizeEvents支持设置true且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0779', 0, async (done: Function) => {
      await titleSearch('基础属性', 'monopolizeEvents', '通用属性7')
      await radioClick({
        radioClickObj: 0,
        id: "Gauge",
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('monopolizeEvents', JsonType.value)
        ],
        assertEqual: true
      })
      done();
    })
    /*
     * 测试组件monopolizeEvents支持设置false且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0780', 0, async (done: Function) => {
      await titleSearch('基础属性', 'monopolizeEvents', '通用属性7')
      await radioClick({
        radioClickObj: 1,
        id: "Gauge",
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('monopolizeEvents', JsonType.value)
        ],
        assertEqual: false
      })
      done();
    })
    //cursorControl
    /*
     * 测试组件cursorControl支持设置DEFAULT且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0781', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置EAST且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0782', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置WEST且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0783', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 2
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置SOUTH且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0784', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 3
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置NORTH且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0785', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 4
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置WEST_EAST且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0786', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 5
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置NORTH_SOUTH且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0787', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 6
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置NORTH_EAST且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0788', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 7
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置NORTH_WEST且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0789', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 8
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置SOUTH_EAST且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0790', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 9
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置SOUTH_WEST且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0791', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 10
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置NORTH_EAST_SOUTH_WEST且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0792', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 11
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置NORTH_WEST_SOUTH_EAST且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0793', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 12
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置CROSS且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0794', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 13
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置CURSOR_COPY且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0795', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 14
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置CURSOR_FORBID且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0796', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 15
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置COLOR_SUCKER且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0797', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 16
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置HAND_GRABBING且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0798', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 17
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置HAND_OPEN且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0799', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 18
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置HAND_POINTING且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0800', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 19
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置HELP且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0801', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 20
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置MOVE且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0802', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 21
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置RESIZE_LEFT_RIGHT且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0803', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 22
      })
      done();
    })
    /*
    * 测试组件cursorControl支持设置RESIZE_UP_DOWN且获取属性正确
    * */
    it('ArkUI_Gauge_Comp_0804', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 'RESIZE_UP_DOWN'
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置SCREENSHOT_CHOOSE且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0805', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 'SCREENSHOT_CHOOSE'
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置SCREENSHOT_CURSOR且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0806', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 'SCREENSHOT_CURSOR'
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置TEXT_CURSOR且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0807', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 'TEXT_CURSOR'
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置ZOOM_IN且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0808', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 'ZOOM_IN'
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置ZOOM_OUT且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0809', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 'ZOOM_OUT'
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置MIDDLE_BTN_EAST且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0810', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 'MIDDLE_BTN_EAST'
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置MIDDLE_BTN_WEST且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0811', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 'MIDDLE_BTN_WEST'
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置MIDDLE_BTN_SOUTH且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0812', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 'MIDDLE_BTN_SOUTH'
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置MIDDLE_BTN_NORTH且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0813', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 'MIDDLE_BTN_NORTH'
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置MIDDLE_BTN_NORTH_SOUTH且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0814', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 'MIDDLE_BTN_NORTH_SOUTH'
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置MIDDLE_BTN_NORTH_EAST且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0815', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 'MIDDLE_BTN_NORTH_EAST'
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置MIDDLE_BTN_NORTH_WEST且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0816', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 'MIDDLE_BTN_NORTH_WEST'
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置MIDDLE_BTN_SOUTH_EAST且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0817', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 'MIDDLE_BTN_SOUTH_EAST'
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置MIDDLE_BTN_SOUTH_WEST且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0818', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 'MIDDLE_BTN_SOUTH_WEST'
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置MIDDLE_BTN_NORTH_SOUTH_WEST_EAST且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0819', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 'MIDDLE_BTN_NORTH_SOUTH_WEST_EAST'
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置HORIZONTAL_TEXT_CURSOR获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0820', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 'HORIZONTAL_TEXT_CURSOR'
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置CURSOR_CROSS且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0821', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 'CURSOR_CROSS'
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置CURSOR_CIRCLE且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0822', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 'CURSOR_CIRCLE'
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置LOADING且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0823', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 'LOADING'
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置RUNNING且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0824', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 'RUNNING'
      })
      done();
    })
    /*
     * 滑到cursorControl位置，关闭按钮，无需断言
     * */
    it('ArkUI_Gauge_Comp_0825', 0, async (done: Function) => {
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await getToggle(ToggleClick.Close)
      done();
    })
    //useEffect
    /*
     * 测试组件useEffect支持设置true且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0826', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'useEffect', '通用属性7')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'useEffect'
        }
      })
      done();
    })
    /*
     * 测试组件useEffect支持设置true且获取属性正确
     * */
    it('ArkUI_Gauge_Comp_0827', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'useEffect', '通用属性7')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'useEffect'
        }
      })
      done();
    })


  })
}


