import { describe, beforeAll, it } from '@ohos/hypium'
import { abilityDelegatorRegistry, Driver, Component } from '@kit.TestKit';
import { ON, Point } from '@ohos.UiTest';
import {
  buttonClick,
  JsonType,
  KeyStruct,
  radioClick,
  searchParentBlock,
  Slide,
  sliderDrag,
  titleSearch,
  ToggleClick,
  Search,
  getToggle,
  searchToggle
} from '../utils';

const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()
const driver = Driver.create();

export default function TabsBootcampTest() {
  describe('TabsBootcampTest', () => {
    /**
     * 打开应用
     */
    beforeAll(async (done: Function) => {
      try {
        await delegator.startAbility({
          bundleName: 'cn.ohos.components',
          abilityName: 'EntryAbility'
        });
        await driver.delayMs(4500);

        let atomNavigates: Component = await driver.findComponent(ON.text('导航与切换'));
        await atomNavigates.click();
        await driver.delayMs(3500);

        let ListItems: Array<Component> = await driver.findComponents(ON.type('ListItem'))
        let width: Point = await ListItems[0].getBoundsCenter()
        let width2: Point = await ListItems[2].getBoundsCenter()
        await driver.swipe(width.x, width2.y, width.x, width.y, 1000)
        await driver.delayMs(5000);

        let scrollSearch: Component = await driver.findComponent(ON.text('页签容器/Tabs'))
        await scrollSearch.click()
        await driver.delayMs(3500);

        let Buttons: Array<Component> = await driver.findComponents(ON.type('Button'));
        await Buttons[1].click()
        await driver.delayMs(3500);

      } catch (err) {
        console.info(`beforeAll error: ${JSON.stringify(err)}`);
      }
      done();
    })

    /**
     * 测试组件'barPosition'支持设置包含单个子组件为'Start'且获取属性正确
     */
    it('ArkUI_Tabs_001', 0, async (done: Function) => {
      await titleSearch('参数列表', 'barPosition')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('barPosition', JsonType.value),
        ],
        assertEqual: 'BarPosition.Start'
      })
      done();
    })

    /**
     * 测试组件'barPosition'支持设置包含单个子组件为'End'且获取属性正确
     */
    it('ArkUI_Tabs_002', 0, async (done: Function) => {
      await titleSearch('参数列表', 'barPosition')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('barPosition', JsonType.value),
        ],
        assertEqual: 'BarPosition.End'
      })
      done();
    })

    /**
     * 测试组件'vertical'支持设置包含单个子组件为'true'且获取属性正确
     */
    it('ArkUI_Tabs_003', 0, async (done: Function) => {
      await titleSearch('参数列表', 'vertical')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('vertical', JsonType.value),
        ],
        assertEqual: 'true'
      })
      done();
    })

    /**
     * 测试组件'vertical'支持设置包含单个子组件为'false'且获取属性正确
     */
    it('ArkUI_Tabs_004', 0, async (done: Function) => {
      await titleSearch('参数列表', 'vertical')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('vertical', JsonType.value),
        ],
        assertEqual: 'false'
      })
      done();
    })

    /**
     * 测试组件'scrollable'支持设置包含单个子组件为'true'且获取属性正确
     */
    it('ArkUI_Tabs_005', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'scrollable')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'scrollable'支持设置包含单个子组件为'false'且获取属性正确
     */
    it('ArkUI_Tabs_006', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'scrollable')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'barMode.value'支持设置包含单个子组件为'Scrollable'且获取属性正确
     */
    it('ArkUI_Tabs_007', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'barMode.value')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'barMode.value'支持设置包含单个子组件为'Fixed'且获取属性正确
     */
    it('ArkUI_Tabs_008', 0, async (done: Function) => {
      await titleSearch('参数列表', 'barMode.value')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('barMode', JsonType.value),
        ],
        assertEqual: 'BarMode.Fixed'
      })
      done();
    })

    /**
     * 测试组件'barMode.options.margin'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_Tabs_009', 0, async (done: Function) => {
      //没有断言参数
      await titleSearch('参数列表', 'barMode.options.margin')
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
      done();
    })

    /**
     * 测试组件'barMode.options.nonScrollableLayoutStyle'支持设置包含单个子组件为'ALWAYS_CENTER'且获取属性正确
     */
    it('ArkUI_Tabs_010', 0, async (done: Function) => {
      //没有断言参数
      await titleSearch('参数列表', 'barMode.options.nonScrollableLayoutStyle')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'barMode.options.nonScrollableLayoutStyle'支持设置包含单个子组件为'ALWAYS_AVERAGE_SPLIT'且获取属性正确
     */
    it('ArkUI_Tabs_011', 0, async (done: Function) => {
      //没有断言参数
      await titleSearch('参数列表', 'barMode.options.nonScrollableLayoutStyle')
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })

    /**
     * 测试组件'barMode.options.nonScrollableLayoutStyle'支持设置包含单个子组件为'SPACE_BETWEEN_OR_CENTER'且获取属性正确
     */
    it('ArkUI_Tabs_012', 0, async (done: Function) => {
      //没有断言参数
      await titleSearch('参数列表', 'barMode.options.nonScrollableLayoutStyle')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'barWidth'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_Tabs_013', 0, async (done: Function) => {
      await titleSearch('参数列表', 'barWidth')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('barWidth', JsonType.value),
        ],
        assertEqual: '100.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('barWidth', JsonType.value),
        ],
        assertEqual: '50.000000'
      })
      done();
    })

    /**
     * 测试组件'barHeight'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_Tabs_014', 0, async (done: Function) => {
      await titleSearch('参数列表', 'barHeight')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('barHeight', JsonType.value),
        ],
        assertEqual: '100.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('barHeight', JsonType.value),
        ],
        assertEqual: '50.000000'
      })
      done();
    })

    /**
     * 测试组件'animationDuration'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_Tabs_015', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'animationDuration')
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
      done();
    })

    /**
     * 测试组件'animationMode'持设置包含单个子组件为'CONTENT_FIRST'且获取属性正确
     */
    it('ArkUI_Tabs_016', 0, async (done: Function) => {
      await titleSearch('参数列表', 'animationMode')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('animationMode', JsonType.value),
        ],
        assertEqual: 'AnimationMode.CONTENT_FIRST'
      })
      done();
    })

    /**
     * 测试组件'animationMode'支持设置包含单个子组件为'ACTION_FIRST'且获取属性正确
     */
    it('ArkUI_Tabs_017', 0, async (done: Function) => {
      await titleSearch('参数列表', 'animationMode')
      await radioClick({
        radioClickObj: 1,
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('animationMode', JsonType.value),
        ],
        assertEqual: 'AnimationMode.ACTION_FIRST'
      })
      done();
    })

    /**
     * 测试组件'animationMode'支持设置包含单个子组件为'NO_ANIMATION'且获取属性正确
     */
    it('ArkUI_Tabs_018', 0, async (done: Function) => {
      await titleSearch('参数列表', 'animationMode')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('animationMode', JsonType.value),
        ],
        assertEqual: 'AnimationMode.NO_ANIMATION'
      })
      done();
    })


    /**
     * 测试组件'divider.strokeWidth'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_Tabs_019', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'divider.strokeWidth')
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
      done();
    })

    /**
     * 测试组件'divider.color'支持设置页签容器的颜色为1号色显示且获取属性正确
     */
    it('ArkUI_Tabs_020', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'divider.color')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'divider.color'支持设置页签容器的颜色为2号色显示且获取属性正确
     */
    it('ArkUI_Tabs_021', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'divider.color')
      await buttonClick({
        buttonClickObj: 1,
      })
      done();
    })

    /**
     * 测试组件'divider.color'支持设置页签容器的颜色为3号色显示且获取属性正确
     */
    it('ArkUI_Tabs_022', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'divider.color')
      await buttonClick({
        buttonClickObj: 2,
      })
      done();
    })

    /**
     * 测试组件'divider.color'支持设置页签容器的颜色为4号色显示且获取属性正确
     */
    it('ArkUI_Tabs_023', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'divider.color')
      await buttonClick({
        buttonClickObj: 3,
      })
      done();
    })

    /**
     * 测试组件'divider.color'支持设置页签容器的颜色为5号色显示且获取属性正确
     */
    it('ArkUI_Tabs_024', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'divider.color')
      await buttonClick({
        buttonClickObj: 4,
      })
      done();
    })


    /**
     * 测试组件'divider.color'支持设置页签容器的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_Tabs_025', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'divider.color')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })


    /**
     * 测试组件'divider.startMargin'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_Tabs_026', 0, async (done: Function) => {
      await titleSearch('参数列表', 'divider.startMargin')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('divider', JsonType.obj),
          new KeyStruct('startMargin', JsonType.value),
        ],
        assertEqual: '10.00px'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('divider', JsonType.obj),
          new KeyStruct('startMargin', JsonType.value),
        ],
        assertEqual: '0.00px'
      })
      done();
    })

    /**
     * 测试组件'divider.endMargin'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_Tabs_027', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'divider.endMargin')
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
      done();
    })


    /**
     * 测试组件'fadingEdge'支持设置包含单个子组件为'true'且获取属性正确
     */
    it('ArkUI_Tabs_028', 0, async (done: Function) => {
      await titleSearch('参数列表', 'fadingEdge')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fadingEdge', JsonType.value),
        ],
        assertEqual: 'true'
      })
      done();
    })

    /**
     * 测试组件'fadingEdge'支持设置包含单个子组件为'false'且获取属性正确
     */
    it('ArkUI_Tabs_029', 0, async (done: Function) => {
      await titleSearch('参数列表', 'fadingEdge')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fadingEdge', JsonType.value),
        ],
        assertEqual: 'false'
      })
      done();
    })

    /**
     * 测试组件'barOverlap'支持设置包含单个子组件为'true'且获取属性正确
     */
    it('ArkUI_Tabs_030', 0, async (done: Function) => {
      await titleSearch('参数列表', 'barOverlap')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('barOverlap', JsonType.value),
        ],
        assertEqual: 'true'
      })
      done();
    })

    /**
     * 测试组件'barOverlap'支持设置包含单个子组件为'false'且获取属性正确
     */
    it('ArkUI_Tabs_031', 0, async (done: Function) => {
      await titleSearch('参数列表', 'barOverlap')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('barOverlap', JsonType.value),
        ],
        assertEqual: 'false'
      })
      done();
    })

    /**
     * 测试组件'barBackgroundColor'支持设置量规图的颜色为1号色显示且获取属性正确
     */
    it('ArkUI_Tabs_032', 0, async (done: Function) => {

      await titleSearch('参数列表', 'barBackgroundColor')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('barBackgroundColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })
      done();
    })

    /**
     * 测试组件'barBackgroundColor'支持设置量规图的颜色为2号色显示且获取属性正确
     */
    it('ArkUI_Tabs_033', 0, async (done: Function) => {
      await titleSearch('参数列表', 'barBackgroundColor')
      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('barBackgroundColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })
      done();
    })

    /**
     * 测试组件'barBackgroundColor'支持设置量规图的颜色为3号色显示且获取属性正确
     */
    it('ArkUI_Tabs_034', 0, async (done: Function) => {
      await titleSearch('参数列表', 'barBackgroundColor')
      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('barBackgroundColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })
      done();
    })

    /**
     * 测试组件'barBackgroundColor'支持设置量规图的颜色为4号色显示且获取属性正确
     */
    it('ArkUI_Tabs_035', 0, async (done: Function) => {
      await titleSearch('参数列表', 'barBackgroundColor')
      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('barBackgroundColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })
      done();
    })

    /**
     * 测试组件'barBackgroundColor'支持设置量规图的颜色为5号色显示且获取属性正确
     */
    it('ArkUI_Tabs_036', 0, async (done: Function) => {
      await titleSearch('参数列表', 'barBackgroundColor')
      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('barBackgroundColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })
      done();
    })


    /**
     * 测试组件'barBackgroundColor'支持设置量规图的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_Tabs_037', 0, async (done: Function) => {
      await titleSearch('参数列表', 'barBackgroundColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('barBackgroundColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })
      done();
    })

    /**
     * 测试组件'barBackgroundBlurStyle'支持设置包含单个子组件为'NONE'且获取属性正确
     */
    it('ArkUI_Tabs_038', 0, async (done: Function) => {
      await titleSearch('参数列表', 'barBackgroundBlurStyle')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('barBackgroundBlurStyle', JsonType.value),
        ],
        assertEqual: 'BlurStyle.NONE'
      })
      done();
    })

    /**
     * 测试组件'barBackgroundBlurStyle'支持设置包含单个子组件为'Thin'且获取属性正确
     */
    it('ArkUI_Tabs_039', 0, async (done: Function) => {
      await titleSearch('参数列表', 'barBackgroundBlurStyle')
      await radioClick({
        radioClickObj: 1,
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('barBackgroundBlurStyle', JsonType.value),
        ],
        assertEqual: 'BlurStyle.Thin'
      })
      done();
    })

    /**
     * 测试组件'barBackgroundBlurStyle'支持设置包含单个子组件为'Regular'且获取属性正确
     */
    it('ArkUI_Tabs_040', 0, async (done: Function) => {
      await titleSearch('参数列表', 'barBackgroundBlurStyle')
      await radioClick({
        radioClickObj: 2,
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('barBackgroundBlurStyle', JsonType.value),
        ],
        assertEqual: 'BlurStyle.Regular'
      })
      done();
    })

    /**
     * 测试组件'barBackgroundBlurStyle'支持设置包含单个子组件为'Thick'且获取属性正确
     */
    it('ArkUI_Tabs_041', 0, async (done: Function) => {
      await titleSearch('参数列表', 'barBackgroundBlurStyle')
      await radioClick({
        radioClickObj: 3,
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('barBackgroundBlurStyle', JsonType.value),
        ],
        assertEqual: 'BlurStyle.Thick'
      })
      done();
    })

    /**
     * 测试组件'barBackgroundBlurStyle'支持设置包含单个子组件为'BACKGROUND_THIN'且获取属性正确
     */
    it('ArkUI_Tabs_042', 0, async (done: Function) => {
      await titleSearch('参数列表', 'barBackgroundBlurStyle')
      await radioClick({
        radioClickObj: 4,
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('barBackgroundBlurStyle', JsonType.value),
        ],
        assertEqual: 'BlurStyle.BACKGROUND_THIN'
      })
      done();
    })

    /**
     * 测试组件'barBackgroundBlurStyle'支持设置包含单个子组件为'BACKGROUND_REGULAR'且获取属性正确
     */
    it('ArkUI_Tabs_043', 0, async (done: Function) => {
      await titleSearch('参数列表', 'barBackgroundBlurStyle')
      await radioClick({
        radioClickObj: 5,
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('barBackgroundBlurStyle', JsonType.value),
        ],
        assertEqual: 'BlurStyle.BACKGROUND_REGULAR'
      })
      done();
    })

    /**
     * 测试组件'barBackgroundBlurStyle'支持设置包含单个子组件为'BACKGROUND_THICK'且获取属性正确
     */
    it('ArkUI_Tabs_044', 0, async (done: Function) => {
      await titleSearch('参数列表', 'barBackgroundBlurStyle')
      await radioClick({
        radioClickObj: 6,
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('barBackgroundBlurStyle', JsonType.value),
        ],
        assertEqual: 'BlurStyle.BACKGROUND_THICK'
      })
      done();
    })

    /**
     * 测试组件'barBackgroundBlurStyle'支持设置包含单个子组件为'BACKGROUND_ULTRA_THICK'且获取属性正确
     */
    it('ArkUI_Tabs_045', 0, async (done: Function) => {
      await titleSearch('参数列表', 'barBackgroundBlurStyle')
      await radioClick({
        radioClickObj: 7,
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('barBackgroundBlurStyle', JsonType.value),
        ],
        assertEqual: 'BlurStyle.BACKGROUND_ULTRA_THICK'
      })
      done();
    })

    /**
     * 测试组件'barBackgroundBlurStyle'支持设置包含单个子组件为'COMPONENT_ULTRA_THIN'且获取属性正确
     */
    it('ArkUI_Tabs_046', 0, async (done: Function) => {
      await titleSearch('参数列表', 'barBackgroundBlurStyle')
      await radioClick({
        radioClickObj: 8,
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('barBackgroundBlurStyle', JsonType.value),
        ],
        assertEqual: 'BlurStyle.COMPONENT_ULTRA_THIN'
      })
      done();
    })

    /**
     * 测试组件'barBackgroundBlurStyle'支持设置包含单个子组件为'COMPONENT_THIN'且获取属性正确
     */
    it('ArkUI_Tabs_047', 0, async (done: Function) => {
      await titleSearch('参数列表', 'barBackgroundBlurStyle')
      await radioClick({
        radioClickObj: 9,
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('barBackgroundBlurStyle', JsonType.value),
        ],
        assertEqual: 'BlurStyle.COMPONENT_THIN'
      })
      done();
    })

    /**
     * 测试组件'barBackgroundBlurStyle'支持设置包含单个子组件为'COMPONENT_REGULAR'且获取属性正确
     */
    it('ArkUI_Tabs_048', 0, async (done: Function) => {
      await titleSearch('参数列表', 'barBackgroundBlurStyle')
      await radioClick({
        radioClickObj: 10,
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('barBackgroundBlurStyle', JsonType.value),
        ],
        assertEqual: 'BlurStyle.COMPONENT_REGULAR'
      })
      done();
    })

    /**
     * 测试组件'barBackgroundBlurStyle'支持设置包含单个子组件为'COMPONENT_THICK'且获取属性正确
     */
    it('ArkUI_Tabs_049', 0, async (done: Function) => {
      await titleSearch('参数列表', 'barBackgroundBlurStyle')
      await radioClick({
        radioClickObj: 11,
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('barBackgroundBlurStyle', JsonType.value),
        ],
        assertEqual: 'BlurStyle.COMPONENT_THICK'
      })
      done();
    })

    /**
     * 测试组件'barBackgroundBlurStyle'支持设置包含单个子组件为'COMPONENT_ULTRA_THICK'且获取属性正确
     */
    it('ArkUI_Tabs_050', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'barBackgroundBlurStyle')
      await radioClick({
        radioClickObj: 12,
        id: 'Tabs',
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'barGridAlign'支持设置包含单个子组件为'true'且获取属性正确
     */
    it('ArkUI_Tabs_051', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'barGridAlign')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'barGridAlign'支持设置包含单个子组件为'false'且获取属性正确
     */
    it('ArkUI_Tabs_052', 0, async (done: Function) => {
      await titleSearch('参数列表', 'barGridAlign')
      //获取不到断言参数
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'barGridAlign.margin'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_Tabs_053', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'barGridAlign.margin')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await sliderDrag({
        //获取不到断言参数
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'barGridAlign.gutter'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_Tabs_054', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'barGridAlign.gutter')
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
      done();
    })

    /**
     * 测试组件'barGridAlign.sm'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_Tabs_055', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'barGridAlign.sm')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'barGridAlign.sm'
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'barGridAlign.sm'
        },
      })
      done();
    })

    /**
     * 测试组件'barGridAlign.md'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_Tabs_056', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'barGridAlign.md')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'barGridAlign.md'
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'barGridAlign.md'
        },
      })
      done();
    })

    /**
     * 测试组件'barGridAlign.lg'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_Tabs_057', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'barGridAlign.lg')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'barGridAlign.lg'
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'barGridAlign.lg'
        },
      })
      done();
    })

    /**
     * 测试组件'edgeEffect'支持设置包含单个子组件为'Spring'且获取属性正确
     */
    it('ArkUI_Tabs_058', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'edgeEffect')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'edgeEffect'
        },
      })
      done();
    })

    /**
     * 测试组件'edgeEffect'支持设置包含单个子组件为'Fade'且获取属性正确
     */
    it('ArkUI_Tabs_059', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'edgeEffect')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'edgeEffect'
        },
      })
      done();
    })

    /**
     * 测试组件'edgeEffect'支持设置包含单个子组件为'None'且获取属性正确
     */
    it('ArkUI_Tabs_060', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'edgeEffect')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'edgeEffect'
        },
      })
      done();
    })


    /**
     * 测试组件width且获取属性正确
     */
    it('ArkUI_Tabs_Comp_0001', 0, async (done: Function) => {
      await titleSearch('基础属性', 'width');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Tabs',
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
        id: 'Tabs',
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
    it('ArkUI_Tabs_Comp_0002', 0, async (done: Function) => {
      await titleSearch('基础属性', 'height');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Tabs',
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
        id: 'Tabs',
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
    it('ArkUI_Tabs_Comp_0003', 0, async (done: Function) => {
      await titleSearch('基础属性', 'padding');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        // id: 'Tabs',
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
        id: 'Tabs',
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
    it('ArkUI_Tabs_Comp_0004', 0, async (done: Function) => {
      await titleSearch('基础属性', 'margin');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Tabs',
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
        id: 'Tabs',
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
    it('ArkUI_Tabs_Comp_0005', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')))
      await toggle[0].click()
      await driver.delayMs(3500);
      done();
    })
    /**
     * 测试组件constraintSize.minWidth且获取属性正确
     */
    it('ArkUI_Tabs_Comp_0006', 0, async (done: Function) => {
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
        id: 'Tabs',
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
        id: 'Tabs',
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
    it('ArkUI_Tabs_Comp_0007', 0, async (done: Function) => {
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
        id: 'Tabs',
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
        id: 'Tabs',
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
    it('ArkUI_Tabs_Comp_0008', 0, async (done: Function) => {
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
        id: 'Tabs',
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
        id: 'Tabs',
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
    it('ArkUI_Tabs_Comp_0009', 0, async (done: Function) => {
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
        id: 'Tabs',
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
        id: 'Tabs',
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
    it('ArkUI_Tabs_Comp_0010', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')));
      if (await toggle[0].isChecked() === true) {
        await toggle[0].click()
      }
      await driver.delayMs(3500);

      done();
    })
    /**
     * 测试开启position
     */
    it('ArkUI_Tabs_Comp_0011', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'position');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')))
      await toggle[0].click()
      await driver.delayMs(3500);
      done();
    })
    /**
     * 测试组件position.top且获取属性正确
     */
    it('ArkUI_Tabs_Comp_0012', 0, async (done: Function) => {
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
    it('ArkUI_Tabs_Comp_0013', 0, async (done: Function) => {
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
    it('ArkUI_Tabs_Comp_0014', 0, async (done: Function) => {
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
    it('ArkUI_Tabs_Comp_0015', 0, async (done: Function) => {
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
    it('ArkUI_Tabs_Comp_0016', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'position');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')));
      if (await toggle[0].isChecked() === true) {
        await toggle[0].click()
      }
      await driver.delayMs(3500);

      done();
    })
    /**
     * 测试开启markAnchor
     */
    it('ArkUI_Tabs_Comp_0017', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'markAnchor');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('markAnchor')))
      await toggle[0].click()
      await driver.delayMs(3500);
      done();
    })
    /**
     * 测试组件markAnchor.x且获取属性正确
     */
    it('ArkUI_Tabs_Comp_0018', 0, async (done: Function) => {
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
        id: 'Tabs',
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
        id: 'Tabs',
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
    it('ArkUI_Tabs_Comp_0019', 0, async (done: Function) => {
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
        id: 'Tabs',
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
        id: 'Tabs',
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
    it('ArkUI_Tabs_Comp_0020', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'markAnchor');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('markAnchor')));
      if (await toggle[0].isChecked() === true) {
        await toggle[0].click()
      }
      await driver.delayMs(3500);

      done();
    })
    /**
     * 测试开启offset
     */
    it('ArkUI_Tabs_Comp_0021', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'offset');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('offset')))
      await toggle[0].click()
      await driver.delayMs(3500);
      done();
    })
    /**
     * 测试组件offset.x且获取属性正确
     */
    it('ArkUI_Tabs_Comp_0022', 0, async (done: Function) => {
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
        id: 'Tabs',
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
        id: 'Tabs',
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
    it('ArkUI_Tabs_Comp_0023', 0, async (done: Function) => {
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
        id: 'Tabs',
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
        id: 'Tabs',
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
    it('ArkUI_Tabs_Comp_0024', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'offset');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('offset')));
      if (await toggle[0].isChecked() === true) {
        await toggle[0].click()
      }
      await driver.delayMs(3500);

      done();
    })
    /**
     * 测试组件borderStyle
     */
    it('ArkUI_Tabs_Comp_0025', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderStyle');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderStyle', JsonType.value)
        ],
        assertEqual: 'BorderStyle.Dotted'
      })
      done();
    })
    it('ArkUI_Tabs_Comp_0026', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderStyle');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderStyle')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 1,
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderStyle', JsonType.value)
        ],
        assertEqual: 'BorderStyle.Dashed'
      })
      done();
    })
    it('ArkUI_Tabs_Comp_0027', 0, async (done: Function) => {
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
        id: 'Tabs',
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
    it('ArkUI_Tabs_Comp_0028', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderWidth');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Tabs',
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
        id: 'Tabs',
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
    it('ArkUI_Tabs_Comp_0029', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderColor');
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })
      done();
    })
    it('ArkUI_Tabs_Comp_0030', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 1,
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })
      done();
    })

  })
}