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

  })
}


