import { describe, beforeAll, it,  } from '@ohos/hypium'
import { abilityDelegatorRegistry, Driver } from '@kit.TestKit';
import { ON, Point, Component,  } from '@ohos.UiTest';
import {
  buttonClick,
  getToggle,
  JsonType,
  KeyStruct,
  radioClick,
  scroll,
  Search,
  searchParentBlock,
  searchToggle,
  Slide,
  sliderDrag,
  titleSearch,
  ToggleClick
} from '../../utils';
import { curves } from '@kit.ArkUI';

const TAG = 'SliderBootcamp'

/*初始化滚动距离*/
let scrollHeight: number = 0;

/*初始化滚动判断*/
let enableScrollHeight: boolean = true;

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export default function SliderBootcampTest() {
  describe('SliderBootcampTest', () => {
    /**
     * 打开应用
     */
    beforeAll(async (done: Function) => {
      console.info('beforeAll begin');
      try {
        await delegator.startAbility({
          bundleName: 'cn.ohos.components',
          abilityName: 'EntryAbility'
        });
        await driver.delayMs(1500);
        console.info(TAG + 'SelectBootcamp001' + ' begin');
        let ListItemGroups: Array<Component> = await driver.findComponents(ON.type('ListItemGroup'))
        let width0: Point = await ListItemGroups[0].getBoundsCenter()
        let width1: Point = await ListItemGroups[2].getBoundsCenter()
        await driver.swipe(width0.x, width1.y, width0.x, width0.y, 500)
        await driver.delayMs(2000);
        let atomDisplays: Component = await driver.findComponent(ON.text('按钮与选择'));
        await atomDisplays.click();
        await driver.delayMs(1000);
        let ListItems: Array<Component> = await driver.findComponents(ON.type('ListItem'))
        let width: Point = await ListItems[0].getBoundsCenter()
        let width2: Point = await ListItems[6].getBoundsCenter()
        await driver.swipe(width.x, width2.y, width.x, width.y, 500)
        await driver.delayMs(1500);

        let scrollSearch: Component = await driver.findComponent(ON.text('滑动条/Slider'))
        await scrollSearch.click()
        await driver.delayMs(1000);

        let Buttons: Array<Component> = await driver.findComponents(ON.type('Button'));
        await Buttons[1].click()
        await driver.delayMs(1000);


      } catch (err) {

        console.info(`beforeAll error: ${JSON.stringify(err)}`);

      }
      console.info(`beforeAll end`);
      done();
    })

    //SliderOptions.value
    it('ArkUI_Slider_001', 0, async (done: Function) => {
      await Search('参数列表', 'SliderOptions.value')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Slider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constructor', JsonType.obj),
          new KeyStruct('value', JsonType.value)
        ],
        assertEqual: '100.000000'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Slider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constructor', JsonType.obj),
          new KeyStruct('value', JsonType.value)
        ],
        assertEqual: '0.000000'
      })
      done()
    })
    //SliderOptions.min
    it('ArkUI_Slider_002', 0, async () => {
      await Search('参数列表', 'SliderOptions.min')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Slider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constructor', JsonType.obj),
          new KeyStruct('min', JsonType.value)
        ],
        assertEqual: '99.000000'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Slider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constructor', JsonType.obj),
          new KeyStruct('min', JsonType.value)
        ],
        assertEqual: '0.000000'
      })
    })
    //SliderOptions.max
    it('ArkUI_Slider_003', 0, async () => {
      await Search('参数列表', 'SliderOptions.max')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Slider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constructor', JsonType.obj),
          new KeyStruct('max', JsonType.value)
        ],
        assertEqual: '100.000000'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Slider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constructor', JsonType.obj),
          new KeyStruct('max', JsonType.value)
        ],
        assertEqual: '1.000000'
      })
    })
    //SliderOptions.step
    it('ArkUI_Slider_004', 0, async () => {
      await Search('参数列表', 'SliderOptions.step')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Slider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constructor', JsonType.obj),
          new KeyStruct('step', JsonType.value)
        ],
        assertEqual: '1.000000'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Slider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constructor', JsonType.obj),
          new KeyStruct('step', JsonType.value)
        ],
        assertEqual: '0.020000'
      })
    })
    //SliderOptions.style
    /*
     * 测试组件SliderOptions.style支持设置OutSet且获取属性正确
     */
    it('ArkUI_Slider_005', 0, async (done: Function) => {
      await Search('参数列表', 'SliderOptions.style')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Slider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('style', JsonType.value)
        ],
        assertEqual: 'SliderStyle.OutSet'
      })
      done();
    })
    /*
    * 测试组件SliderOptions.style支持设置InSet且获取属性正确
    */
    it('ArkUI_Slider_006', 0, async (done: Function) => {
      await Search('参数列表', 'SliderOptions.style')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Slider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('style', JsonType.value)
        ],
        assertEqual: 'SliderStyle.InSet'
      })
      done();
    })
    /*
    * 测试组件SliderOptions.style支持设置NONE且获取属性正确
    */
    it('ArkUI_Slider_007', 0, async (done: Function) => {
      await Search('参数列表', 'SliderOptions.style')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Slider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('style', JsonType.value)
        ],
        assertEqual: 'SliderStyle.NONE'
      })
      done();
    })
    //SliderOptions.direction
    /*
     * 测试组件SliderOptions.direction支持设置Vertical且获取属性正确
     */
    it('ArkUI_Slider_008', 0, async (done: Function) => {
      await Search('参数列表', 'SliderOptions.direction')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Slider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constructor', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'Axis.Vertical'
      })
      done();
    })
    /*
     * 测试组件SliderOptions.direction支持设置Horizontal且获取属性正确
     */
    it('ArkUI_Slider_009', 0, async (done: Function) => {
      await Search('参数列表', 'SliderOptions.direction')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Slider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constructor', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'Axis.Horizontal'
      })
      done();
    })
    //SliderOptions.reverse
    /*
     * 测试组件SliderOptions.reverse支持设置false且获取属性正确
     */
    it('ArkUI_Slider_010', 0, async (done: Function) => {
      await Search('参数列表', 'SliderOptions.reverse')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Slider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constructor', JsonType.obj),
          new KeyStruct('reverse', JsonType.value),
        ],
        assertEqual: 'false'
      })
      done();
    })
    /*
     * 测试组件SliderOptions.reverse支持设置true且获取属性正确
     */
    it('ArkUI_Slider_011', 0, async (done: Function) => {
      await Search('参数列表', 'SliderOptions.reverse')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Slider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constructor', JsonType.obj),
          new KeyStruct('reverse', JsonType.value),
        ],
        assertEqual: 'true'
      })
      done();
    })
    //blockColor
    /*
    *测试组件blockColor支持设置量规图的颜色为1号色显示且获取属性正确
    * */
    it('ArkUI_Slider_012 ', 0, async (done: Function) => {
      await Search('参数列表', 'blockColor')
      await buttonClick({
        buttonClickObj: 0,
        id: 'Slider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blockColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })
      done();
    })
    /**
     * 测试组件blockColor支持设置量规图的颜色为2号色显示且获取属性正确
     */
    it('ArkUI_Slider_013 ', 0, async (done: Function) => {
      await Search('参数列表', 'blockColor')
      await buttonClick({
        buttonClickObj: 1,
        id: 'Slider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blockColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })
      done();
    })
    /**
     * 测试组件blockColor支持设置量规图的颜色为3号色显示且获取属性正确
     */
    it('ArkUI_Slider_014 ', 0, async (done: Function) => {
      await Search('参数列表', 'blockColor')
      await buttonClick({
        buttonClickObj: 2,
        id: 'Slider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blockColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })
      done();
    })
    /**
     * 测试组件blockColor支持设置量规图的颜色为4号色显示且获取属性正确
     */
    it('ArkUI_Slider_015 ', 0, async (done: Function) => {
      await Search('参数列表', 'blockColor')
      await buttonClick({
        buttonClickObj: 3,
        id: 'Slider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blockColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })
      done();
    })
    /**
     * 测试组件blockColor支持设置量规图的颜色为5号色显示且获取属性正确
     */
    it('ArkUI_Slider_016 ', 0, async (done: Function) => {
      await Search('参数列表', 'blockColor')
      await buttonClick({
        buttonClickObj: 4,
        id: 'Slider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blockColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })
      done();
    })
    /**
     * 测试组件blockColor支持设置量规图的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_Slider_017 ', 0, async (done: Function) => {
      await Search('参数列表', 'blockColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Slider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blockColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })
      done();
    })
    //trackColor
    /*
    *测试组件trackColor支持设置量规图的颜色为1号色显示且获取属性正确
    * */
    it('ArkUI_Slider_018', 0, async (done: Function) => {
      await Search('参数列表', 'trackColor')
      await buttonClick({
        buttonClickObj: 0,
        id: 'Slider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('trackColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })
      done();
    })
    /**
     * 测试组件trackColor支持设置量规图的颜色为2号色显示且获取属性正确
     */
    it('ArkUI_Slider_019', 0, async (done: Function) => {
      await Search('参数列表', 'trackColor')
      await buttonClick({
        buttonClickObj: 1,
        id: 'Slider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('trackColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })
      done();
    })
    /**
     * 测试组件trackColor支持设置量规图的颜色为3号色显示且获取属性正确
     */
    it('ArkUI_Slider_020', 0, async (done: Function) => {
      await Search('参数列表', 'trackColor')
      await buttonClick({
        buttonClickObj: 2,
        id: 'Slider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('trackColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })
      done();
    })
    /**
     * 测试组件trackColor支持设置量规图的颜色为4号色显示且获取属性正确
     */
    it('ArkUI_Slider_021', 0, async (done: Function) => {
      await Search('参数列表', 'trackColor')
      await buttonClick({
        buttonClickObj: 3,
        id: 'Slider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('trackColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })
      done();
    })
    /**
     * 测试组件trackColor支持设置量规图的颜色为5号色显示且获取属性正确
     */
    it('ArkUI_Slider_022', 0, async (done: Function) => {
      await Search('参数列表', 'trackColor')
      await buttonClick({
        buttonClickObj: 4,
        id: 'Slider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('trackColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })
      done();
    })
    /**
     * 测试组件trackColor支持设置量规图的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_Slider_023', 0, async (done: Function) => {
      await Search('参数列表', 'trackColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Slider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('trackColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })
      done();
    })
    //selectedColor
    /*
    *测试组件selectedColor支持设置量规图的颜色为1号色显示且获取属性正确
    * */
    it('ArkUI_Slider_024', 0, async (done: Function) => {
      await Search('参数列表', 'selectedColor')
      await buttonClick({
        buttonClickObj: 0,
        id: 'Slider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })
      done();
    })
    /**
     * 测试组件selectedColor支持设置量规图的颜色为2号色显示且获取属性正确
     */
    it('ArkUI_Slider_025', 0, async (done: Function) => {
      await Search('参数列表', 'selectedColor')
      await buttonClick({
        buttonClickObj: 1,
        id: 'Slider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })
      done();
    })
    /**
     * 测试组件selectedColor支持设置量规图的颜色为3号色显示且获取属性正确
     */
    it('ArkUI_Slider_026', 0, async (done: Function) => {
      await Search('参数列表', 'selectedColor')
      await buttonClick({
        buttonClickObj: 2,
        id: 'Slider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })
      done();
    })
    /**
     * 测试组件selectedColor支持设置量规图的颜色为4号色显示且获取属性正确
     */
    it('ArkUI_Slider_027', 0, async (done: Function) => {
      await Search('参数列表', 'selectedColor')
      await buttonClick({
        buttonClickObj: 3,
        id: 'Slider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })
      done();
    })
    /**
     * 测试组件selectedColor支持设置量规图的颜色为5号色显示且获取属性正确
     */
    it('ArkUI_Slider_028', 0, async (done: Function) => {
      await Search('参数列表', 'selectedColor')
      await buttonClick({
        buttonClickObj: 4,
        id: 'Slider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })
      done();
    })
    /**
     * 测试组件selectedColor支持设置量规图的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_Slider_029', 0, async (done: Function) => {
      await Search('参数列表', 'selectedColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Slider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })
      done();
    })
    //showSteps
    /*
     * 测试组件showSteps支持设置false且获取属性正确
     */
    it('ArkUI_Slider_030', 0, async (done: Function) => {
      await Search('参数列表', 'showSteps')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Slider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('showSteps', JsonType.value),
        ],
        assertEqual: 'false'
      })
      done();
    })
    /*
     * 测试组件showSteps支持设置true且获取属性正确
     */
    it('ArkUI_Slider_031', 0, async (done: Function) => {
      await Search('参数列表', 'showSteps')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Slider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('showSteps', JsonType.value),
        ],
        assertEqual: 'true'
      })
      done();
    })
    //showTips.value
    /*
     * 测试组件showTips.value支持设置false且获取属性正确
     */
    it('ArkUI_Slider_032', 0, async (done: Function) => {
      await Search('参数列表', 'showTips.value')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Slider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('showTips', JsonType.value),
        ],
        assertEqual: 'false'
      })
      done();
    })
    /*
     * 测试组件showTips.value支持设置true且获取属性正确
     */
    it('ArkUI_Slider_033', 0, async (done: Function) => {
      await Search('参数列表', 'showTips.value')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Slider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('showTips', JsonType.value),
        ],
        assertEqual: 'true'
      })
      done();
    })
    //trackThickness
    it('ArkUI_Slider_034', 0, async (done: Function) => {
      await Search('参数列表', 'trackThickness')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Slider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('trackThickness', JsonType.value)
        ],
        assertEqual: '100.00vp'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Slider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('trackThickness', JsonType.value)
        ],
        assertEqual: '4.00vp'
      })
      done()
    })
    //blockBorderColor
    /*
    *测试组件blockBorderColor支持设置量规图的颜色为1号色显示且获取属性正确
    * */
    it('ArkUI_Slider_035', 0, async (done: Function) => {
      await Search('参数列表', 'blockBorderColor')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Slider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blockBorderColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })
      done();
    })
    /**
     * 测试组件blockBorderColor支持设置量规图的颜色为2号色显示且获取属性正确
     */
    it('ArkUI_Slider_036', 0, async (done: Function) => {
      await Search('参数列表', 'blockBorderColor')
      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Slider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blockBorderColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })
      done();
    })
    /**
     * 测试组件blockBorderColor支持设置量规图的颜色为3号色显示且获取属性正确
     */
    it('ArkUI_Slider_037', 0, async (done: Function) => {
      await Search('参数列表', 'blockBorderColor')
      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Slider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blockBorderColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })
      done();
    })
    /**
     * 测试组件blockBorderColor支持设置量规图的颜色为4号色显示且获取属性正确
     */
    it('ArkUI_Slider_038', 0, async (done: Function) => {
      await Search('参数列表', 'blockBorderColor')
      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Slider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blockBorderColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })
      done();
    })
    /**
     * 测试组件blockBorderColor支持设置量规图的颜色为5号色显示且获取属性正确
     */
    it('ArkUI_Slider_039', 0, async (done: Function) => {
      await Search('参数列表', 'blockBorderColor')
      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Slider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blockBorderColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })
      done();
    })
    /**
     * 测试组件blockBorderColor支持设置量规图的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_Slider_040', 0, async (done: Function) => {
      await Search('参数列表', 'blockBorderColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Slider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blockBorderColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })
      done();
    })
    //blockBorderWidth
    it('ArkUI_Slider_041', 0, async (done: Function) => {
      await Search('参数列表', 'blockBorderWidth')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Slider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blockBorderWidth', JsonType.value)
        ],
        assertEqual: '100.00vp'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Slider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blockBorderWidth', JsonType.value)
        ],
        assertEqual: '0.00vp'
      })
      done()
    })
  })
}