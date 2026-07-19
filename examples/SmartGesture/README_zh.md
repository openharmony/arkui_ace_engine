# 智慧手势控制器

## 介绍

本示例为[SmartGestureController](https://gitcode.com/openharmony/docs/blob/master/zh-cn/application-dev/reference/apis-arkui/arkts-apis-uicontext-smartgesturecontroller.md)的配套示例工程。

本示例展示了智慧手势控制器的使能、监听、选中态控制以及动态决策智慧手势行为的完整能力，覆盖敲一敲和划一划两种交互方式在不同UI场景下的适配方案。

## 效果预览

| 首页                          | Case1: 长页面Scroll + Button   |
|-----------------------------|-----------------------------|
| Case2: 长列表List              | Case3: 单页面 + 多组件            |
| Case4: Swiper + Button      |                             |

### 使用说明

1. **手势类型与场景匹配**:   
   触发组件点击：用敲一敲（TAP），通过ClickActionProposal执行点击。  
   切换选中组件：用划一划（SLIDE_FORWARD），通过SelectActionProposal切换选中焦点。  
   滚动容器内容：用划一划（SLIDE_FORWARD），通过ScrollActionProposal滚动指定距离。  
   翻页切换页面：用划一划（SLIDE_FORWARD），通过PageSwitchActionProposal切换Swiper页面。  
   返回上一页面：用BackPressActionProposal模拟返回键。  
   拒绝本次手势：用NoneActionProposal不执行任何操作。
2. **关键注意事项**：  
   启用手势：调用enableSmartTapAndSlideGestures(true)开启智慧手势，关闭后组件侧smartGestureShortcut配置仍保留但不响应。  
   注册监听：通过registerMonitor注册回调，按后注册先执行的顺序触发，返回GestureHandlingResolution(true)即消费本次手势，后续回调不再执行。  
   选中控制：requestSelected请求选中组件（组件需满足可见、可响应智慧手势、绑定onClick三个条件），clearSelected清空当前选中。
3. **特殊场景适配**：  
   长页面滚动 + 按钮：Case1演示划一划先滚动到按钮区域，再划一划选中按钮，敲一敲触发点击。  
   长列表选中：Case2演示划一划选中ListItem，敲一敲触发点击。  
   单页面多组件：Case3演示在同一页面中对Text、Button、Toggle、Slider分别进行选中与点击操作。
   Swiper翻页 + 按钮：Case4演示划一划翻页切换Swiper页面，敲一敲触发页面内按钮点击。

## 工程目录

```
entry/src/main/ets/
└── pages
    └── Index.ets                 // 首页导航
    └── Case1.ets                 // 长页面Scroll + Button场景
    └── Case2.ets                 // 长列表List场景
    └── Case3.ets                 // 单页面 + 多组件场景
    └── Case4.ets                 // Swiper + Button场景
```

### 具体实现

1. **智慧手势使能与监听注册**：在aboutToAppear中调用controller.enableSmartTapAndSlideGestures(true)开启手势，调用controller.registerMonitor(callback)注册监听回调；在aboutToDisappear中调用controller.clearMonitors()清空回调并调用enableSmartTapAndSlideGestures(false)关闭手势。
2. **Monitor回调动态决策**：回调接收BaseGestureHandlingProposal参数，通过proposal.action判断手势动作类型（CLICK/SELECT/SCROLL_FORWARD/PAGE_FORWARD/BACK_PRESS/NONE），根据业务需求构造对应的ActionProposal（如ClickActionProposal(node)、ScrollActionProposal(node, distance)），设置到GestureHandlingResolution的selectedProposal属性返回，实现对系统默认动作的自定义覆写。
3. **组件标记与节点定位**：交互组件通过.smartGestureShortcut({ action: GestureShortcut.PRIMARY, enabled: true, selectable: true })标记为智慧手势目标，通过.id()设置组件标识，在Monitor回调中通过this.getUIContext().getFrameNodeById(id)获取FrameNode用于构造ActionProposal。
4. **选中态手动控制**：通过controller.requestSelected(id)手动请求选中指定组件，通过controller.clearSelected()清空选中态，适用于需要跨页面选中或精确控制选中焦点的场景。

## 相关权限

不涉及

## 依赖

不涉及

## 约束和限制

1.本示例仅支持标准系统上运行, 支持设备：RK3568。

2.本示例为Stage模型，支持API26版本SDK，版本号：7.0.0.24，镜像版本号：OpenHarmony_7.0.0.24。

3.本示例需要使用DevEco Studio 6.1.1 Release (Build Version: 6.1.1.280， built on May 26, 2026)及以上版本才可编译运行。

## 下载

如需单独下载本工程，执行如下命令：
```
git init
git config core.sparsecheckout true
echo code/DocsSample/ArkUISample/SmartGesture > .git/info/sparse-checkout
git remote add origin https://gitcode.com/openharmony/applications_app_samples.git
git pull origin master
```