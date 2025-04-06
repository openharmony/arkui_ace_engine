import { describe, beforeAll, beforeEach, afterEach, afterAll, it, expect } from '@ohos/hypium'
import { abilityDelegatorRegistry, Driver, ON, Component } from '@kit.TestKit';
import { Point } from '@ohos.UiTest';
import {
  buttonClick,
  getToggle,
  radioClick,
  Search,
  searchParentBlock,
  Slide,
  sliderDrag,
  titleSearch,
  ToggleClick
} from '../../utils';


const TAG = 'BindMenuBootcamp001'

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export default function BindMenuBootcampTest() {
  describe('BindMenuBootcampTest', () => {
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

        await driver.delayMs(3500);
        console.info(TAG + 'BindMenuBootcamp001' + ' begin');

        let ListItemGroup :Component[] = await driver.findComponents(ON.type('ListItemGroup'))
        let width:Point = await ListItemGroup[0].getBoundsCenter()
        let width2:Point = await ListItemGroup[5].getBoundsCenter()
        await driver.swipe(width.x, width2.y, width.x, width.y, 500)
        await driver.delayMs(2000);

        let atomDisplays:Component = await driver.findComponent(ON.text('弹窗'));
        await atomDisplays.click();
        await driver.delayMs(2000);
        await driver.swipe(width.x, width2.y, width.x, width.y, 500)


        let ListItemGroup1 :Component[] = await driver.findComponents(ON.type('ListItem'))
        let width3:Point = await ListItemGroup1[0].getBoundsCenter()
        let width4:Point = await ListItemGroup1[5].getBoundsCenter()
        await driver.swipe(width3.x, width4.y, width3.x, width3.y, 500)
        await driver.delayMs(2000);



        let scrollSearch: Component = await driver.findComponent(ON.text('菜单/Menu'))
        await scrollSearch.click()
        await driver.delayMs(1000);

        let Buttons: Component[] = await driver.findComponents(ON.type('Button'));
        await Buttons[1].click()
        await driver.delayMs(1000);

      } catch (err) {

        console.info(`beforeAll error: ${JSON.stringify(err)}`);

      }
      console.info(`beforeAll end`);
      done();
    })


    /**
     * 测试组件selected支持设置菜单项是否选中为允许
     */
    it('ArkUI_MenuItem_001', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'selected')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    /**
     * 测试组件selected支持设置菜单项是否选中为禁止
     */
    it('ArkUI_MenuItem_002', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'selected')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件SelectIcon支持设置菜单项被选中的图标为1号
     */
    it('ArkUI_MenuItem_003', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'SelectIcon')
      await buttonClick({
        buttonClickObj: 0,
      })
      done();
    })

    /**
     * 测试组件SelectIcon支持设置菜单项被选中的图标为2号
     */
    it('ArkUI_MenuItem_004', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'SelectIcon')
      await buttonClick({
        buttonClickObj: 1,
      })
      done();
    })

    /**
     * 测试组件SelectIcon支持设置菜单项被选中的图标为3号
     */
    it('ArkUI_MenuItem_005', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'SelectIcon')
      await buttonClick({
        buttonClickObj: 2,
      })
      done();
    })

    /**
     * 测试组件SelectIcon支持设置菜单项被选中的图标为4号
     */
    it('ArkUI_MenuItem_006', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'SelectIcon')
      await buttonClick({
        buttonClickObj: 3,
      })
      done();
    })

    /**
     * 测试组件SelectIcon支持设置菜单项被选中的图标为5号
     */
    it('ArkUI_MenuItem_007', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'SelectIcon')
      await buttonClick({
        buttonClickObj: 4,
      })
      done();
    })

    /**
     * 测试组件SelectIcon支持设置菜单项被选中的图标为6号
     */
    it('ArkUI_MenuItem_008', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'SelectIcon')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件contentFont.size支持设置菜单项中内容信息的字体尺寸
     */
    it('ArkUI_MenuItem_009', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'contentFont.size')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'contentFont.size'
        }
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'contentFont.size'
        }
      })
      done();
    })

    /**
     * 测试组件contentFont.weight支持设置菜单项中内容信息的字体粗细为Lighter
     */
    it('ArkUI_MenuItem_010', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'contentFont.weight')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    /**
     * 测试组件contentFont.weight支持设置菜单项中内容信息的字体粗细为Normal
     */
    it('ArkUI_MenuItem_011', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'contentFont.weight')
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })

    /**
     * 测试组件contentFont.weight支持设置菜单项中内容信息的字体粗细为Regular
     */
    it('ArkUI_MenuItem_012', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'contentFont.weight')
      await radioClick({
        radioClickObj: 2,
      })
      done();
    })

    /**
     * 测试组件contentFont.weight支持设置菜单项中内容信息的字体粗细为Medium
     */
    it('ArkUI_MenuItem_013', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'contentFont.weight')
      await radioClick({
        radioClickObj: 3,
      })
      done();
    })

    /**
     * 测试组件contentFont.weight支持设置菜单项中内容信息的字体粗细为Bold
     */
    it('ArkUI_MenuItem_014', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'contentFont.weight')
      await radioClick({
        radioClickObj: 4,
      })
      done();
    })

    /**
     * 测试组件contentFont.weight支持设置菜单项中内容信息的字体粗细为Bolder
     */
    it('ArkUI_MenuItem_015', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'contentFont.weight')
      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件contentFont.style支持设置菜单项中内容信息的字体样式为Normal
     */
    it('ArkUI_MenuItem_016', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'contentFont.style')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    /**
     * 测试组件contentFont.style支持设置菜单项中内容信息的字体样式为Italic
     */
    it('ArkUI_MenuItem_017', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'contentFont.style')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件contentFontColor支持设置菜单项中内容信息的字体颜色1号色
     */
    it('ArkUI_MenuItem_018', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'contentFontColor')
      await buttonClick({
        buttonClickObj: 0,
      })
      done();
    })

    /**
     * 测试组件contentFontColor支持设置菜单项中内容信息的字体颜色2号色
     */
    it('ArkUI_MenuItem_019', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'contentFontColor')
      await buttonClick({
        buttonClickObj: 1,
      })
      done();
    })

    /**
     * 测试组件contentFontColor支持设置菜单项中内容信息的字体颜色3号色
     */
    it('ArkUI_MenuItem_020', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'contentFontColor')
      await buttonClick({
        buttonClickObj: 2,
      })
      done();
    })

    /**
     * 测试组件contentFontColor支持设置菜单项中内容信息的字体颜色4号色
     */
    it('ArkUI_MenuItem_021', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'contentFontColor')
      await buttonClick({
        buttonClickObj: 3,
      })
      done();
    })

    /**
     * 测试组件contentFontColor支持设置菜单项中内容信息的字体颜色5号色
     */
    it('ArkUI_MenuItem_022', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'contentFontColor')
      await buttonClick({
        buttonClickObj: 4,
      })
      done();
    })

    /**
     * 测试组件contentFontColor支持设置菜单项中内容信息的字体颜色6号色
     */
    it('ArkUI_MenuItem_023', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'contentFontColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件labelFontColor支持设置菜单项中标签信息的字体颜色1号色
     */
    it('ArkUI_MenuItem_024', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'labelFontColor')
      await buttonClick({
        buttonClickObj: 0,
      })
      done();
    })

    /**
     * 测试组件labelFontColor支持设置菜单项中标签信息的字体颜色2号色
     */
    it('ArkUI_MenuItem_025', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'labelFontColor')
      await buttonClick({
        buttonClickObj: 1,
      })
      done();
    })

    /**
     * 测试组件labelFontColor支持设置菜单项中标签信息的字体颜色3号色
     */
    it('ArkUI_MenuItem_026', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'labelFontColor')
      await buttonClick({
        buttonClickObj: 2,
      })
      done();
    })

    /**
     * 测试组件labelFontColor支持设置菜单项中标签信息的字体颜色4号色
     */
    it('ArkUI_MenuItem_027', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'labelFontColor')
      await buttonClick({
        buttonClickObj: 3,
      })
      done();
    })

    /**
     * 测试组件labelFontColor支持设置菜单项中标签信息的字体颜色5号色
     */
    it('ArkUI_MenuItem_028', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'labelFontColor')
      await buttonClick({
        buttonClickObj: 4,
      })
      done();
    })

    /**
     * 测试组件labelFontColor支持设置菜单项中标签信息的字体颜色6号色
     */
    it('ArkUI_MenuItem_029', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'labelFontColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件labelFont.size支持设置菜单项中标签信息的字体尺寸
     */
    it('ArkUI_MenuItem_030', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'labelFont.size')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'labelFont.size'
        }
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'labelFont.size'
        }
      })
      done();
    })

    /**
     * 测试组件labelFont.weight支持设置菜单项中标签信息的字体字体粗细为Lighter
     */
    it('ArkUI_MenuItem_031', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'labelFont.weight')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    /**
     * 测试组件labelFont.weight支持设置菜单项中标签信息的字体字体粗细为Normal
     */
    it('ArkUI_MenuItem_032', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'labelFont.weight')
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })

    /**
     * 测试组件labelFont.weight支持设置菜单项中标签信息的字体字体粗细为Regular
     */
    it('ArkUI_MenuItem_033', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'labelFont.weight')
      await radioClick({
        radioClickObj: 2,
      })
      done();
    })

    /**
     * 测试组件labelFont.weight支持设置菜单项中标签信息的字体字体粗细为Medium
     */
    it('ArkUI_MenuItem_034', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'labelFont.weight')
      await radioClick({
        radioClickObj: 3,
      })
      done();
    })

    /**
     * 测试组件labelFont.weight支持设置菜单项中标签信息的字体字体粗细为Bold
     */
    it('ArkUI_MenuItem_035', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'labelFont.weight')
      await radioClick({
        radioClickObj: 4,
      })
      done();
    })

    /**
     * 测试组件labelFont.weight支持设置菜单项中标签信息的字体字体粗细为Bolder
     */
    it('ArkUI_MenuItem_036', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'labelFont.weight')
      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件labelFont.style支持设置菜单项中标签信息的字体字体样式为Normal
     */
    it('ArkUI_MenuItem_037', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'labelFont.style')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    /**
     * 测试组件labelFont.style支持设置菜单项中标签信息的字体字体样式为Italic
     */
    it('ArkUI_MenuItem_038', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'labelFont.style')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件是否可用菜单设置为允许
     */
    it('ArkUI_MenuItem_039', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', '是否可用菜单')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: '是否可用菜单'
        }
      })
      done();
    })

    /**
     * 测试组件是否可用菜单设置为禁止
     */
    it('ArkUI_MenuItem_040', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', '是否可用菜单')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: '是否可用菜单',
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件是否允许显示二级菜单设置为允许
     */
    it('ArkUI_MenuItem_041', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', '是否允许显示二级菜单')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: '是否允许显示二级菜单'
        }
      })
      done();
    })

    /**
     * 测试组件是否允许显示二级菜单设置为禁止
     */
    it('ArkUI_MenuItem_042', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', '是否允许显示二级菜单')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: '是否允许显示二级菜单',
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件是否显示前缀图标设置被选中的前缀图标为1号
     */
    it('ArkUI_MenuItem_043', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', '是否显示前缀图标')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: '是否显示前缀图标'
        }
      })
      done();
    })

    /**
     * 测试组件是否显示前缀图标设置被选中的前缀图标为2号
     */
    it('ArkUI_MenuItem_044', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', '是否显示前缀图标')
      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: '是否显示前缀图标'
        }
      })
      done();
    })

    /**
     * 测试组件是否显示前缀图标设置被选中的前缀图标为3号
     */
    it('ArkUI_MenuItem_045', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', '是否显示前缀图标')
      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: '是否显示前缀图标'
        }
      })
      done();
    })

    /**
     * 测试组件是否显示前缀图标设置被选中的前缀图标为4号
     */
    it('ArkUI_MenuItem_046', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', '是否显示前缀图标')
      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: '是否显示前缀图标'
        }
      })
      done();
    })

    /**
     * 测试组件是否显示前缀图标设置被选中的前缀图标为5号
     */
    it('ArkUI_MenuItem_047', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', '是否显示前缀图标')
      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: '是否显示前缀图标'
        }
      })
      done();
    })

    /**
     *测试组件是否显示前缀图标设置被选中的前缀图标为6号
     */
    it('ArkUI_MenuItem_048', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', '是否显示前缀图标')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: '是否显示前缀图标',
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件是否显示后缀图标设置被选中的后缀图标为1号
     */
    it('ArkUI_MenuItem_049', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', '是否显示后缀图标')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: '是否显示后缀图标'
        }
      })
      done();
    })

    /**
     * 测试组件是否显示前缀图标设置被选中的后缀图标为2号
     */
    it('ArkUI_MenuItem_050', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', '是否显示后缀图标')
      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: '是否显示后缀图标'
        }
      })
      done();
    })

    /**
     * 测试组件是否显示前缀图标设置被选中的后缀图标为3号
     */
    it('ArkUI_MenuItem_051', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', '是否显示后缀图标')
      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: '是否显示后缀图标'
        }
      })
      done();
    })

    /**
     * 测试组件是否显示前缀图标设置被选中的后缀图标为4号
     */
    it('ArkUI_MenuItem_052', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', '是否显示后缀图标')
      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: '是否显示后缀图标'
        }
      })
      done();
    })

    /**
     * 测试组件是否显示前缀图标设置被选中的后缀图标为5号
     */
    it('ArkUI_MenuItem_053', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', '是否显示后缀图标')
      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: '是否显示后缀图标'
        }
      })
      done();
    })

    /**
     *测试组件是否显示前缀图标设置被选中的后缀图标为6号
     */
    it('ArkUI_MenuItem_054', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', '是否显示后缀图标')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: '是否显示后缀图标',
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件width且获取属性正确
     */
    it('ArkUI_MenuItem_Comp_0001', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'width');
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
     * 测试组件height且获取属性正确
     */
    it('ArkUI_MenuItem_Comp_0002', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'height');
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
     * 测试组件padding且获取属性正确
     */
    it('ArkUI_MenuItem_Comp_0003', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'padding');
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
     * 测试组件margin且获取属性正确
     */
    it('ArkUI_MenuItem_Comp_0004', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'margin');
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
     * 测试开启constraintSize
     */
    it('ArkUI_MenuItem_Comp_0005', 0, async (done: Function) => {
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
    it('ArkUI_MenuItem_Comp_0006', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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
     * 测试组件constraintSize.minHeight且获取属性正确
     */
    it('ArkUI_MenuItem_Comp_0007', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })


  })
}