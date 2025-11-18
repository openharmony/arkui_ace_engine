# ArkUI Layout Sample

## 项目简介

本项目基于HarmonyOS ArkUI框架，展示了ArkUI中多种布局组件布局约束的使用方法。项目包括了Native C++实现和ArkTS的编码实现，为开发者提供了多种布局学习资源。
工程中涉及接口文档：
1. [提供NativeModule公共的类型定义](https://gitcode.com/openharmony/docs/blob/master/zh-cn/application-dev/reference/apis-arkui/capi-native-type-h.md)。
2. [提供NativeNode接口的类型定义](https://gitcode.com/openharmony/docs/blob/master/zh-cn/application-dev/reference/apis-arkui/capi-native-node-h.md)。

## 效果预览
<img src="./screenshot/operate_sample.gif" width="300" height="600">

## 项目结构
```
LayoutSample/
├── AppScope/                           # 应用全局配置
│   ├── app.json5                      # 应用配置文件
│   └── resources/                     # 全局资源文件
├── entry/                             # 主模块
│   ├── src/main/
│   │   ├── cpp/                       # Native C++代码
│   │   │   ├── examples/              # 布局示例实现
│   │   │   │   ├── alignRuleOptionExample.h      # 对齐规则示例
│   │   │   │   ├── barrierOptionExample.h        # 障碍物布局示例
│   │   │   │   ├── columnExample.h               # 列布局示例
│   │   │   │   ├── flexExample.h                 # Flex布局示例
│   │   │   │   ├── guidelineOptionExample.h      # 引导线示例
│   │   │   │   ├── itemAlignmentExample.h        # 项目对齐示例
│   │   │   │   ├── layoutConstraintExample.h     # 布局约束示例
│   │   │   │   ├── layoutPolicyExample.h         # 布局策略示例
│   │   │   │   ├── layoutPositionExample.h       # 布局位置示例
│   │   │   │   ├── listChildrenMainSizeExample.h # 列表子元素主尺寸示例
│   │   │   │   ├── pixelRoundExample.h           # 像素舍入示例
│   │   │   │   ├── positionEdgesExample.h        # 位置边缘示例
│   │   │   │   ├── refreshOffsetChangeExample.h  # 刷新偏移事件示例
│   │   │   │   ├── relativeLayoutChainExample.h  # 相对布局链示例
│   │   │   │   ├── rowExample.h                  # 行布局示例
│   │   │   │   ├── safeAreaExample.h             # 安全区域示例
│   │   │   │   ├── stackExample.h                # 堆叠布局示例
│   │   │   │   └── LayoutConstants.h             # 布局常量定义
│   │   │   ├── nodes/                 # ArkUI节点封装
│   │   │   │   └── ArkUIBaseNode.h    # 基础节点类
│   │   │   ├── NativeEntry.h          # Native入口头文件
│   │   │   ├── NativeEntry.cpp        # Native入口实现
│   │   │   └── napi_init.cpp          # NAPI初始化
│   │   ├── ets/                       # ArkTS代码
│   │   │   ├── entryability/          # 应用入口
│   │   │   │   └── EntryAbility.ets   # 主Ability
│   │   │   ├── models/                # 数据模型
│   │   │   │   └── NavigationItem.ts  # 导航项模型
│   │   │   └── pages/                 # 页面文件
│   │   │       ├── Index.ets          # 主页面
│   │   │       ├── native.ets         # Native测试页面
│   │   │       ├── node.ets           # Node测试页面
│   │   │       ├── nativeTest/        # Native测试示例页面
│   │   │       └── nodeTest/          # Node测试示例页面
│   │   ├── resources/                 # 资源文件
│   │   └── module.json5               # 模块配置文件
│   ├── build-profile.json5            # 构建配置
│   └── oh-package.json5               # 包配置文件
├── build-profile.json5                # 项目构建配置
├── oh-package.json5                   # 项目包配置
└── README.md                          # 项目说明文档
```
## 功能特性

### 1. 布局组件示例
- **Flex布局**: 弹性盒子布局，支持主轴和交叉轴对齐
- **Stack布局**: 堆叠布局，子组件按层级叠放
- **Row布局**: 水平线性布局
- **Column布局**: 垂直线性布局
- **RelativeContainer**: 相对布局容器

### 2. 布局约束和规则
- **LayoutConstraint**: 布局约束设置和获取
- **AlignRuleOption**: 相对布局对齐规则配置
- **GuidelineOption**: 引导线配置，辅助布局对齐
- **BarrierOption**: 障碍物配置，创建虚拟边界
- **RelativeLayoutChain**: 相对布局链，实现组件间的链式约束

### 3. 布局属性和策略
- **LayoutPosition**: 布局位置设置和获取
- **LayoutPolicy**: 布局策略（WrapContent、FixAtIdealSize等）
- **PositionEdges**: 位置边缘设置
- **PixelRound**: 像素取整处理
- **SafeArea**: 安全区域处理

### 4. 高级功能
- **ListChildrenMainSize**: 列表子元素主尺寸控制
- **ItemAlignment**: 项目对齐方式设置
- **RefreshOffsetEvent**: 刷新偏移事件处理

## 技术架构

### 1. 混合开发架构
- **ArkTS层**: 提供UI界面和用户交互
- **Native C++层**: 实现核心布局逻辑和性能优化
- **NAPI桥接**: 连接ArkTS和C++层，实现数据传递

### 2. 核心组件
- **NativeEntry**: Native层入口管理类，负责组件生命周期
- **ArkUIBaseNode**: 基础节点类，封装ArkUI原生节点操作
- **NodeContent**: 内容容器，用于承载Native组件

### 3. 设计模式
- **工厂模式**: 用于创建不同类型的布局示例
- **单例模式**: NativeEntry采用单例模式管理全局状态
- **模板方法模式**: 统一的创建和销毁流程

## 开发环境要求

- **HarmonyOS SDK**: 6.0.0(49) 或更高版本
- **DevEco Studio**: 最新版本
- **编译器**: BiSheng (用于Native编译)
- **目标设备**: 支持HarmonyOS的移动设备

## 构建和运行

### 1. 环境准备
```bash
# 确保已安装DevEco Studio和HarmonyOS开发工具包
# 配置好开发环境和设备连接
```

### 2. 项目构建
```bash
# 连接HarmonyOS设备或启动模拟器
# 点击构建按钮进行构建
```

### 3. 安装运行
```bash
# 连接HarmonyOS设备或启动模拟器
# 点击运行按钮安装并运行应用
```

## 使用说明

### 1. 应用导航
- 启动应用后，主页面显示两个主要入口：
  - **NativeType测试**: 展示Native C++实现的布局示例
  - **Node测试**: 展示ArkTS Node API实现的布局示例

### 2. Native测试示例
包含以下测试页面：
- `layoutConstraintTest`: 布局约束测试
- `alignRuleOptionExample`: 对齐规则示例
- `guidelineOptionExample`: 引导线示例
- `barrierOptionExample`: 障碍物示例
- `listChildrenMainSizeExample`: 列表子元素主尺寸示例
- `itemAlignmentExample`: 项目对齐示例
- `relativeLayoutChainExample`: 相对布局链示例
- `positionEdgesExample`: 位置边缘示例
- `pixelRoundExample`: 像素舍入示例

### 3. Node测试示例
包含以下测试页面：
- `flex测试`: Flex布局测试
- `stack测试`: Stack布局测试
- `row测试`: Row布局测试
- `column测试`: Column布局测试
- `layoutPosition测试`: 布局位置测试
- `safeArea测试`: 安全区域测试
- `refreshOffsetEvent测试`: 刷新偏移事件测试
- `layoutPolicy测试`: 布局策略测试

## 代码示例

### 1. Native C++布局示例
```cpp
// 创建布局约束示例
std::shared_ptr<ArkUIBaseNode> CreateLayoutConstraintExample()
{
    auto column = std::make_shared<ArkUIColumnNode>();
    auto child = std::make_shared<ArkUIColumnNode>();
    child->SetWidth(Sizes::EXTRA_LARGE);
    child->SetHeight(Sizes::EXTRA_LARGE);
    
    // 应用布局约束
    auto values = column->layoutConstraintExample(child);
    auto constraint = values.first;
    auto size = values.second;
    
    // 显示约束信息
    auto sizeText = std::make_shared<ArkUITextNode>();
    sizeText->SetTextContent("Width : " + std::to_string(size.width) + 
                            " Height : " + std::to_string(size.height));
    
    column->AddChild(sizeText);
    child->SetBackgroundColor(Colors::LIGHT_BLUE);
    return column;
}
```

### 2. ArkTS页面示例
```typescript
@Entry
@Component
struct layoutConstraintTest {
  private rootSlot = new NodeContent();

  aboutToAppear(): void {
    // 创建Native组件
    nativeNode.CreateLayoutConstraintNativeRoot(this.rootSlot)
  }

  aboutToDisappear(): void {
    // 销毁Native组件
    nativeNode.DestroyLayoutConstraintNativeRoot()
  }

  build() {
    Column() {
      Row() {
        // 绑定Native内容
        ContentSlot(this.rootSlot)
      }.layoutWeight(1)
    }
    .width('100%')
    .height('100%')
  }
}
```

## 学习要点

### 1. 布局基础概念
- **约束系统**: 了解HarmonyOS的布局约束机制
- **测量和布局**: 掌握组件的测量和布局流程
- **坐标系统**: 了解屏幕坐标和组件坐标的关系

### 2. 性能优化
- **Native实现**: 关键布局逻辑使用C++实现，提升性能
- **内存管理**: 合理的组件生命周期管理
- **渲染优化**: 减少不必要的重绘和重排

### 3. 开发实践
- **混合开发**: ArkTS + Native C++的开发模式
- **组件封装**: 可复用的布局组件设计
- **调试技巧**: 布局问题的调试和定位方法

## 常见问题

### 1. 编译问题
- 确保Native编译环境配置正确
- 检查CMakeLists.txt配置是否正确
- 验证SDK版本兼容性

### 2. 运行问题
- 检查设备连接和权限设置
- 确认应用签名配置
- 查看日志输出定位问题

### 3. 布局问题
- 理解不同布局组件的特性和限制
- 注意约束冲突和优先级
- 合理使用布局策略

## 扩展开发

### 1. 添加新的布局示例
1. 在`cpp/examples/`目录下创建新的示例头文件
2. 实现布局逻辑和UI展示
3. 在`NativeEntry.cpp`中注册新的NAPI接口
4. 创建对应的ArkTS测试页面

### 2. 自定义布局组件
1. 继承`ArkUIBaseNode`创建自定义节点类
2. 实现特定的布局算法
3. 封装为可复用的组件