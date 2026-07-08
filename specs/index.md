# ArkUI 特性规格索引

> 本文件是 ArkUI ace_engine 特性规格（Spec）体系的总入口。所有功能域和特性必须在此注册后才能生成规格文档。

## 功能域层级树

### 一级域（L1）

| 编号 | 目录名（英文 slug） | 中文名 | 说明 |
|------|---------------------|--------|------|
| 01 | `01-architecture` | 架构通用设计 | 编译构建、目录结构、部件化、兼容性设计、架构优化 |
| 02 | `02-cross-platform` | 跨平台适配层 | 多平台适配、平台抽象、渲染后端适配 |
| 03 | `03-engine-framework` | 引擎框架层 | 渲染管线、动效、资源主题、事件框架、窗口、多实例、无障碍、DFX |
| 04 | `04-common-capability` | 通用能力层 | 通用属性、通用事件、自定义扩展、自定义节点、路由、焦点、输入交互等通用能力 |
| 05 | `05-ui-components` | 组件层 | 布局、导航、滚动容器、表单、选择、弹窗、文本、图片、绘制等组件 |
| 06 | `06-common-interface` | 通用接口层 | 前端桥接、Inner 接口、其它范式接入 |
| 07 | `07-frontend` | 前端层 | ArkTS 高级组件、状态管理、自定义组件、生成式 UI |
| 08 | `08-ndk` | NDK | Node C-API、XComponent C-API 等 NDK 接口 |
| 09 | `09-developer-tools` | 开发者工具 | 预览器、工具链、开发者文档、Sample、ComponentTest |
| 10 | `10-product-customization` | 产品化定制 | 穿戴等产品化定制能力 |

### 二级域（L2）→ 三级域（L3）→ 功能域

| L1 | L2 | L3 | FuncID | 目录路径 | design.md | 特性数 |
|----|----|----|--------|----------|-----------|--------|
| 01 架构通用设计 | 01 架构设计 | 01 编译构建 | `01-01-01` | `01-architecture/01-architecture-design/01-build-system/` | [design.md](01-architecture/01-architecture-design/01-build-system/design.md) | 1 |
| 01 架构通用设计 | 01 架构设计 | 02 目录结构 | `01-01-02` | `01-architecture/01-architecture-design/02-directory-structure/` | *待补充* | 0 |
| 01 架构通用设计 | 01 架构设计 | 03 部件化 | `01-01-03` | `01-architecture/01-architecture-design/03-modularization/` | *待补充* | 0 |
| 01 架构通用设计 | 02 架构优化 | 01 产品化解耦 | `01-02-01` | `01-architecture/02-architecture-optimization/01-product-decoupling/` | *待补充* | 0 |
| 02 跨平台适配层 | 01 跨平台适配层 | 01 OH平台适配 | `02-01-01` | `02-cross-platform/01-platform-adapter/01-oh-platform-adapter/` | *待补充* | 0 |
| 02 跨平台适配层 | 01 跨平台适配层 | 02 Android平台适配 | `02-01-02` | `02-cross-platform/01-platform-adapter/02-android-platform-adapter/` | *待补充* | 0 |
| 02 跨平台适配层 | 01 跨平台适配层 | 03 iOS平台适配 | `02-01-03` | `02-cross-platform/01-platform-adapter/03-ios-platform-adapter/` | *待补充* | 0 |
| 02 跨平台适配层 | 01 跨平台适配层 | 04 预览器平台适配 | `02-01-04` | `02-cross-platform/01-platform-adapter/04-previewer-platform-adapter/` | *待补充* | 0 |
| 02 跨平台适配层 | 02 渲染后端适配 | 01 渲染后端适配 | `02-02-01` | `02-cross-platform/02-render-backend-adapter/01-render-backend-adapter/` | *待补充* | 0 |
| 03 引擎框架层 | 01 渲染管线 | 01 渲染管线 | `03-01-01` | `03-engine-framework/01-render-pipeline/01-basic-render-pipeline/` | [design.md](03-engine-framework/01-render-pipeline/01-basic-render-pipeline/design.md) | 1 |
| 03 引擎框架层 | 01 渲染管线 | 02 多级渲染管线 | `03-01-02` | `03-engine-framework/01-render-pipeline/02-multi-level-render-pipeline/` | *待补充* | 0 |
| 03 引擎框架层 | 02 动效能力 | 01 动效框架 | `03-02-01` | `03-engine-framework/02-animation-capability/01-animation-framework/` | *待补充* | 0 |
| 03 引擎框架层 | 02 动效能力 | 02 属性动画 | `03-02-02` | `03-engine-framework/02-animation-capability/02-property-animation/` | *待补充* | 0 |
| 03 引擎框架层 | 02 动效能力 | 03 显式动画 | `03-02-03` | `03-engine-framework/02-animation-capability/03-explicit-animation/` | *待补充* | 0 |
| 03 引擎框架层 | 02 动效能力 | 04 关键帧动画 | `03-02-04` | `03-engine-framework/02-animation-capability/04-keyframe-animation/` | *待补充* | 0 |
| 03 引擎框架层 | 02 动效能力 | 05 转场动画 | `03-02-05` | `03-engine-framework/02-animation-capability/05-transition-animation/` | *待补充* | 0 |
| 03 引擎框架层 | 02 动效能力 | 06 共享元素动画 | `03-02-06` | `03-engine-framework/02-animation-capability/06-shared-transition/` | *待补充* | 0 |
| 03 引擎框架层 | 02 动效能力 | 07 组件共享元素动画 | `03-02-07` | `03-engine-framework/02-animation-capability/07-geometry-transition/` | *待补充* | 0 |
| 03 引擎框架层 | 02 动效能力 | 08 路径动画 | `03-02-08` | `03-engine-framework/02-animation-capability/08-motion-path/` | *待补充* | 0 |
| 03 引擎框架层 | 02 动效能力 | 09 物理动画 | `03-02-09` | `03-engine-framework/02-animation-capability/09-physics-animation/` | *待补充* | 0 |
| 03 引擎框架层 | 02 动效能力 | 10 动画接口 | `03-02-10` | `03-engine-framework/02-animation-capability/10-animation-interface/` | *待补充* | 0 |
| 03 引擎框架层 | 03 资源主题 | 01 资源访问 | `03-03-01` | `03-engine-framework/03-resource-theme/01-resource-access/` | *待补充* | 0 |
| 03 引擎框架层 | 03 资源主题 | 02 主题分层访问 | `03-03-02` | `03-engine-framework/03-resource-theme/02-theme-layered-access/` | *待补充* | 0 |
| 03 引擎框架层 | 03 资源主题 | 03 Theme框架 | `03-03-03` | `03-engine-framework/03-resource-theme/03-theme-framework/` | *待补充* | 0 |
| 03 引擎框架层 | 03 资源主题 | 04 资源动态切换 | `03-03-04` | `03-engine-framework/03-resource-theme/04-resource-dynamic-switching/` | *待补充* | 0 |
| 03 引擎框架层 | 04 事件框架 | 01 事件基础框架 | `03-04-01` | `03-engine-framework/04-event-framework/01-event-base-framework/` | *待补充* | 0 |
| 03 引擎框架层 | 04 事件框架 | 02 拖拽框架 | `03-04-02` | `03-engine-framework/04-event-framework/02-drag-framework/` | *待补充* | 0 |
| 03 引擎框架层 | 05 窗口机制 | 01 窗口机制 | `03-05-01` | `03-engine-framework/05-window-mechanism/01-window-mechanism/` | *待补充* | 0 |
| 03 引擎框架层 | 05 窗口机制 | 02 子窗机制 | `03-05-02` | `03-engine-framework/05-window-mechanism/02-subwindow-mechanism/` | *待补充* | 0 |
| 03 引擎框架层 | 06 多实例管理 | 01 多实例管理 | `03-06-01` | `03-engine-framework/06-multi-instance-management/01-multi-instance-management/` | *待补充* | 0 |
| 03 引擎框架层 | 07 无障碍机制 | 01 无障碍能力 | `03-07-01` | `03-engine-framework/07-accessibility-mechanism/01-accessibility-capability/` | *待补充* | 0 |
| 03 引擎框架层 | 07 无障碍机制 | 02 Inspector | `03-07-02` | `03-engine-framework/07-accessibility-mechanism/02-inspector/` | *待补充* | 0 |
| 03 引擎框架层 | 08 DFX | 01 日志 | `03-08-01` | `03-engine-framework/08-dfx/01-logging/` | *待补充* | 0 |
| 03 引擎框架层 | 08 DFX | 02 内存管理 | `03-08-02` | `03-engine-framework/08-dfx/02-memory-management/` | *待补充* | 0 |
| 03 引擎框架层 | 08 DFX | 03 Trace打点 | `03-08-03` | `03-engine-framework/08-dfx/03-trace/` | *待补充* | 0 |
| 03 引擎框架层 | 08 DFX | 04 Dump机制 | `03-08-04` | `03-engine-framework/08-dfx/04-dump-mechanism/` | *待补充* | 0 |
| 03 引擎框架层 | 08 DFX | 05 Benchmark | `03-08-05` | `03-engine-framework/08-dfx/05-benchmark/` | *待补充* | 0 |
| 03 引擎框架层 | 08 DFX | 06 布局边界显示 | `03-08-06` | `03-engine-framework/08-dfx/06-layout-boundary-display/` | *待补充* | 0 |
| 04 通用能力层 | 01 图片加载能力 | 01 图片加载机制 | `04-01-01` | `04-common-capability/01-image-loading/01-image-loading-mechanism/` | [design.md](04-common-capability/01-image-loading/01-image-loading-mechanism/design.md) | 1 |
| 04 通用能力层 | 01 图片加载能力 | 02 Svg解析 | `04-01-02` | `04-common-capability/01-image-loading/02-svg-parsing/` | *待补充* | 0 |
| 04 通用能力层 | 01 图片加载能力 | 03 DrawableDescriptor 能力 | `04-01-03` | `04-common-capability/01-image-loading/03-drawable-descriptor/` | [design.md](04-common-capability/01-image-loading/03-drawable-descriptor/design.md) | 1 |
| 04 通用能力层 | 02 安全区机制 | 01 安全区机制 | `04-02-01` | `04-common-capability/02-safe-area/01-safe-area-mechanism/` | *待补充* | 0 |
| 04 通用能力层 | 03 通用属性 | 01 布局属性 | `04-03-01` | `04-common-capability/03-common-attributes/01-layout-attributes/` | [design.md](04-common-capability/03-common-attributes/01-layout-attributes/design.md) | 3 |
| 04 通用能力层 | 03 通用属性 | 02 视效属性 | `04-03-02` | `04-common-capability/03-common-attributes/02-visual-effect-attributes/` | [design.md](04-common-capability/03-common-attributes/02-visual-effect-attributes/design.md) | 1 |
| 04 通用能力层 | 03 通用属性 | 03 基础属性 | `04-03-03` | `04-common-capability/03-common-attributes/03-basic-attributes/` | *待补充* | 0 |
| 04 通用能力层 | 03 通用属性 | 04 交互属性 | `04-03-04` | `04-common-capability/03-common-attributes/04-interaction-attributes/` | *待补充* | 0 |
| 04 通用能力层 | 03 通用属性 | 05 弹窗类属性 | `04-03-05` | `04-common-capability/03-common-attributes/05-popup-attributes/` | *待补充* | 0 |
| 04 通用能力层 | 03 通用属性 | 06 模态属性 | `04-03-06` | `04-common-capability/03-common-attributes/06-modal-attributes/` | *待补充* | 0 |
| 04 通用能力层 | 03 通用属性 | 07 样式属性 | `04-03-07` | `04-common-capability/03-common-attributes/07-style-attributes/` | *待补充* | 0 |
| 04 通用能力层 | 03 通用属性 | 08 基础单位 | `04-03-08` | `04-common-capability/03-common-attributes/08-basic-units/` | *待补充* | 0 |
| 04 通用能力层 | 03 通用属性 | 09 无障碍属性 | `04-03-09` | `04-common-capability/03-common-attributes/09-accessibility-attributes/` | *待补充* | 0 |
| 04 通用能力层 | 03 通用属性 | 10 图片相关属性 | `04-03-10` | `04-common-capability/03-common-attributes/10-image-related-attributes/` | *待补充* | 0 |
| 04 通用能力层 | 03 通用属性 | 11 文本通用属性 | `04-03-11` | `04-common-capability/03-common-attributes/11-text-common-attributes/` | *待补充* | 0 |
| 04 通用能力层 | 04 通用事件 | 01 触摸事件 | `04-04-01` | `04-common-capability/04-common-events/01-touch-events/` | *待补充* | 0 |
| 04 通用能力层 | 04 通用事件 | 02 按键事件 | `04-04-02` | `04-common-capability/04-common-events/02-key-events/` | *待补充* | 0 |
| 04 通用能力层 | 04 通用事件 | 03 事件分发和拦截 | `04-04-03` | `04-common-capability/04-common-events/03-event-dispatch-intercept/` | *待补充* | 0 |
| 04 通用能力层 | 04 通用事件 | 04 组件组合键 | `04-04-04` | `04-common-capability/04-common-events/04-component-shortcuts/` | *待补充* | 0 |
| 04 通用能力层 | 04 通用事件 | 05 鼠标事件 | `04-04-05` | `04-common-capability/04-common-events/05-mouse-events/` | *待补充* | 0 |
| 04 通用能力层 | 04 通用事件 | 06 手势能力 | `04-04-06` | `04-common-capability/04-common-events/06-gesture-capability/` | [design.md](04-common-capability/04-common-events/06-gesture-capability/design.md) | 5 |
| 04 通用能力层 | 04 通用事件 | 07 拖拽能力 | `04-04-07` | `04-common-capability/04-common-events/07-drag-capability/` | *待补充* | 0 |
| 04 通用能力层 | 04 通用事件 | 08 手写笔能力 | `04-04-08` | `04-common-capability/04-common-events/08-stylus-capability/` | *待补充* | 0 |
| 04 通用能力层 | 04 通用事件 | 09 组件相关事件 | `04-04-09` | `04-common-capability/04-common-events/09-component-related-events/` | *待补充* | 0 |
| 04 通用能力层 | 04 通用事件 | 10 可见区域机制 | `04-04-10` | `04-common-capability/04-common-events/10-visible-area-mechanism/` | *待补充* | 0 |
| 04 通用能力层 | 04 通用事件 | 11 交互归一化 | `04-04-11` | `04-common-capability/04-common-events/11-interaction-normalization/` | *待补充* | 0 |
| 04 通用能力层 | 05 自定义扩展能力 | 01 动态绘制属性 | `04-05-01` | `04-common-capability/05-custom-extension/01-draw-modifier/` | *待补充* | 0 |
| 04 通用能力层 | 05 自定义扩展能力 | 02 动态属性 | `04-05-02` | `04-common-capability/05-custom-extension/02-dynamic-attributes/` | *待补充* | 0 |
| 04 通用能力层 | 05 自定义扩展能力 | 03 自定义内容 -（表单类组件） | `04-05-03` | `04-common-capability/05-custom-extension/03-content-modifier-form/` | *待补充* | 0 |
| 04 通用能力层 | 05 自定义扩展能力 | 04 自定义内容 -（信息展示类） | `04-05-04` | `04-common-capability/05-custom-extension/04-content-modifier-display/` | *待补充* | 0 |
| 04 通用能力层 | 05 自定义扩展能力 | 05 自定义属性 | `04-05-05` | `04-common-capability/05-custom-extension/05-custom-property/` | *待补充* | 0 |
| 04 通用能力层 | 05 自定义扩展能力 | 06 组件Modifier | `04-05-06` | `04-common-capability/05-custom-extension/06-component-modifier/` | *待补充* | 0 |
| 04 通用能力层 | 06 自定义节点能力 | 01 占位组件 | `04-06-01` | `04-common-capability/06-custom-node/01-placeholder-component/` | *待补充* | 0 |
| 04 通用能力层 | 06 自定义节点能力 | 02 FrameNode | `04-06-02` | `04-common-capability/06-custom-node/02-frame-node/` | *待补充* | 0 |
| 04 通用能力层 | 06 自定义节点能力 | 03 RenderNode | `04-06-03` | `04-common-capability/06-custom-node/03-render-node/` | *待补充* | 0 |
| 04 通用能力层 | 06 自定义节点能力 | 04 BuilderNode | `04-06-04` | `04-common-capability/06-custom-node/04-builder-node/` | *待补充* | 0 |
| 04 通用能力层 | 06 自定义节点能力 | 05 ComponentContent | `04-06-05` | `04-common-capability/06-custom-node/05-component-content/` | *待补充* | 0 |
| 04 通用能力层 | 06 自定义节点能力 | 06 NodeAdapter | `04-06-06` | `04-common-capability/06-custom-node/06-node-adapter/` | *待补充* | 0 |
| 04 通用能力层 | 06 自定义节点能力 | 07 TypedFrameNode | `04-06-07` | `04-common-capability/06-custom-node/07-typed-frame-node/` | *待补充* | 0 |
| 04 通用能力层 | 07 迁移恢复 | 01 分布式路由迁移能力 | `04-07-01` | `04-common-capability/07-migration-recovery/01-distributed-router-migration/` | *待补充* | 0 |
| 04 通用能力层 | 07 迁移恢复 | 02 路由栈恢复 | `04-07-02` | `04-common-capability/07-migration-recovery/02-router-stack-recovery/` | *待补充* | 0 |
| 04 通用能力层 | 07 迁移恢复 | 03 组件迁移机制 | `04-07-03` | `04-common-capability/07-migration-recovery/03-component-migration/` | *待补充* | 0 |
| 04 通用能力层 | 08 根视图 | 01 窗口工具栏 | `04-08-01` | `04-common-capability/08-root-view/01-window-toolbar/` | *待补充* | 0 |
| 04 通用能力层 | 08 根视图 | 02 元服务AppBar | `04-08-02` | `04-common-capability/08-root-view/02-atomic-service-appbar/` | *待补充* | 0 |
| 04 通用能力层 | 08 根视图 | 03 浮层能力 | `04-08-03` | `04-common-capability/08-root-view/03-overlay-capability/` | *待补充* | 0 |
| 04 通用能力层 | 09 焦点框架 | 01 焦点机制 | `04-09-01` | `04-common-capability/09-focus-framework/01-focus-mechanism/` | *待补充* | 0 |
| 04 通用能力层 | 10 组件截图 | 01 离屏截图 | `04-10-01` | `04-common-capability/10-component-screenshot/01-offscreen-screenshot/` | *待补充* | 0 |
| 04 通用能力层 | 11 组件信息获取 | 01 ComponentUtils | `04-11-01` | `04-common-capability/11-component-info/01-component-utils/` | *待补充* | 0 |
| 04 通用能力层 | 11 组件信息获取 | 02 无感监听（observer） | `04-11-02` | `04-common-capability/11-component-info/02-observer/` | *待补充* | 0 |
| 04 通用能力层 | 11 组件信息获取 | 03 布局回调（inspector） | `04-11-03` | `04-common-capability/11-component-info/03-inspector-layout-callback/` | *待补充* | 0 |
| 04 通用能力层 | 12 UI上下文 | 01 UIContext接口 | `04-12-01` | `04-common-capability/12-ui-context/01-ui-context-interface/` | *待补充* | 0 |
| 04 通用能力层 | 12 UI上下文 | 02 Ability上下文 | `04-12-02` | `04-common-capability/12-ui-context/02-ability-context/` | *待补充* | 0 |
| 04 通用能力层 | 12 UI上下文 | 03 Frame回调接口 | `04-12-03` | `04-common-capability/12-ui-context/03-frame-callback/` | *待补充* | 0 |
| 04 通用能力层 | 13 字体文本 | 01 字体注册 | `04-13-01` | `04-common-capability/13-font-text/01-font-registration/` | *待补充* | 0 |
| 04 通用能力层 | 13 字体文本 | 02 文本测量 | `04-13-02` | `04-common-capability/13-font-text/02-text-measurement/` | *待补充* | 0 |
| 04 通用能力层 | 14 输入交互 | 01 文本选择 | `04-14-01` | `04-common-capability/14-input-interaction/01-text-selection/` | *待补充* | 0 |
| 04 通用能力层 | 14 输入交互 | 02 文本快捷键 | `04-14-02` | `04-common-capability/14-input-interaction/02-text-shortcuts/` | *待补充* | 0 |
| 04 通用能力层 | 14 输入交互 | 03 文本交互 | `04-14-03` | `04-common-capability/14-input-interaction/03-text-interaction/` | *待补充* | 0 |
| 04 通用能力层 | 14 输入交互 | 04 键盘控制 | `04-14-04` | `04-common-capability/14-input-interaction/04-keyboard-control/` | *待补充* | 0 |
| 04 通用能力层 | 14 输入交互 | 05 自动补全能力（AutoFill） | `04-14-05` | `04-common-capability/14-input-interaction/05-autofill/` | *待补充* | 0 |
| 04 通用能力层 | 15 路由机制 | 01 路由管理 | `04-15-01` | `04-common-capability/15-router-mechanism/01-router-management/` | *待补充* | 0 |
| 04 通用能力层 | 15 路由机制 | 03 命名路由 | `04-15-03` | `04-common-capability/15-router-mechanism/03-named-router/` | *待补充* | 0 |
| 04 通用能力层 | 16 UIAppearance | 01 UIAppearance | `04-16-01` | `04-common-capability/16-ui-appearance/01-ui-appearance/` | *待补充* | 0 |
| 04 通用能力层 | 17 嵌入显示能力 | 01 UIExtension机制 | `04-17-01` | `04-common-capability/17-embedded-display/01-ui-extension/` | *待补充* | 0 |
| 04 通用能力层 | 17 嵌入显示能力 | 02 IsolateComponent机制 | `04-17-02` | `04-common-capability/17-embedded-display/02-isolate-component/` | *待补充* | 0 |
| 04 通用能力层 | 17 嵌入显示能力 | 03 From卡片机制 | `04-17-03` | `04-common-capability/17-embedded-display/03-form-card/` | *待补充* | 0 |
| 04 通用能力层 | 17 嵌入显示能力 | 04 PluginComponent机制 | `04-17-04` | `04-common-capability/17-embedded-display/04-plugin-component/` | *待补充* | 0 |
| 04 通用能力层 | 18 端侧渲染 | 01 同层渲染机制 | `04-18-01` | `04-common-capability/18-on-device-rendering/01-same-layer-rendering/` | *待补充* | 0 |
| 04 通用能力层 | 19 组件复用 | 01 组件复用框架 | `04-19-01` | `04-common-capability/19-component-reuse/01-component-reuse-framework/` | *待补充* | 0 |
| 04 通用能力层 | 20 媒体查询能力 | 01 MediaQuery | `04-20-01` | `04-common-capability/20-media-query/01-media-query/` | *待补充* | 0 |
| 04 通用能力层 | 21 适老化 | 01 大字体 | `04-21-01` | `04-common-capability/21-aging-adaptation/01-large-font/` | *待补充* | 0 |
| 04 通用能力层 | 22 国际化能力 | 01 多语言能力 | `04-22-01` | `04-common-capability/22-internationalization/01-multilingual/` | *待补充* | 0 |
| 04 通用能力层 | 22 国际化能力 | 02 镜像能力 | `04-22-02` | `04-common-capability/22-internationalization/02-mirroring/` | *待补充* | 0 |
| 04 通用能力层 | 23 AI能力 | 01 Image分析能力 | `04-23-01` | `04-common-capability/23-ai-capability/01-image-analysis/` | *待补充* | 0 |
| 04 通用能力层 | 24 布局通用能力 | 01 像素取整能力 | `04-24-01` | `04-common-capability/24-layout-common-capability/01-pixel-rounding/` | *待补充* | 0 |
| 04 通用能力层 | 25 热重载能力 | 01 热重载机制 | `04-25-01` | `04-common-capability/25-hot-reload/01-hot-reload-mechanism/` | *待补充* | 0 |
| 05 组件层 | 01 布局类组件 | 01 Blank | `05-01-01` | `05-ui-components/01-layout-components/01-blank/` | [design.md](05-ui-components/01-layout-components/01-blank/design.md) | 1 |
| 05 组件层 | 01 布局类组件 | 02 Divider | `05-01-02` | `05-ui-components/01-layout-components/02-divider/` | [design.md](05-ui-components/01-layout-components/02-divider/design.md) | 1 |
| 05 组件层 | 01 布局类组件 | 03 Column | `05-01-03` | `05-ui-components/01-layout-components/03-column/` | *待补充* | 0 |
| 05 组件层 | 01 布局类组件 | 04 ColumnSplit | `05-01-04` | `05-ui-components/01-layout-components/04-column-split/` | *待补充* | 0 |
| 05 组件层 | 01 布局类组件 | 05 Flex | `05-01-05` | `05-ui-components/01-layout-components/05-flex/` | *待补充* | 0 |
| 05 组件层 | 01 布局类组件 | 06 GridCol | `05-01-06` | `05-ui-components/01-layout-components/06-grid-col/` | *待补充* | 0 |
| 05 组件层 | 01 布局类组件 | 07 GridRow | `05-01-07` | `05-ui-components/01-layout-components/07-grid-row/` | *待补充* | 0 |
| 05 组件层 | 01 布局类组件 | 08 RelativeContainer | `05-01-08` | `05-ui-components/01-layout-components/08-relative-container/` | *待补充* | 0 |
| 05 组件层 | 01 布局类组件 | 09 Row | `05-01-09` | `05-ui-components/01-layout-components/09-row/` | *待补充* | 0 |
| 05 组件层 | 01 布局类组件 | 10 RowSplit | `05-01-10` | `05-ui-components/01-layout-components/10-row-split/` | *待补充* | 0 |
| 05 组件层 | 01 布局类组件 | 11 Stack | `05-01-11` | `05-ui-components/01-layout-components/11-stack/` | *待补充* | 0 |
| 05 组件层 | 01 布局类组件 | 12 FolderStack | `05-01-12` | `05-ui-components/01-layout-components/12-folder-stack/` | *待补充* | 0 |
| 05 组件层 | 01 布局类组件 | 13 DynamicLayout | `05-01-13` | `05-ui-components/01-layout-components/13-dynamic-layout/` | *待补充* | 0 |
| 05 组件层 | 02 导航类组件 | 01 Navigation | `05-02-01` | `05-ui-components/02-navigation-components/01-navigation/` | [design.md](05-ui-components/02-navigation-components/01-navigation/design.md) | 7 |
| 05 组件层 | 02 导航类组件 | 02 NavRouter | `05-02-02` | `05-ui-components/02-navigation-components/02-nav-router/` | *待补充* | 0 |
| 05 组件层 | 02 导航类组件 | 03 NavDestination | `05-02-03` | `05-ui-components/02-navigation-components/03-nav-destination/` | *待补充* | 0 |
| 05 组件层 | 02 导航类组件 | 04 Stepper/SetpperItem | `05-02-04` | `05-ui-components/02-navigation-components/04-stepper-stepper-item/` | *待补充* | 0 |
| 05 组件层 | 02 导航类组件 | 05 Navigator | `05-02-05` | `05-ui-components/02-navigation-components/05-navigator/` | *待补充* | 0 |
| 05 组件层 | 02 导航类组件 | 06 SideBarContainer | `05-02-06` | `05-ui-components/02-navigation-components/06-sidebar-container/` | [design.md](05-ui-components/02-navigation-components/06-sidebar-container/design.md) | 1 |
| 05 组件层 | 03 滚动容器类组件 | 01 滚动公共能力 | `05-03-01` | `05-ui-components/03-scroll-container-components/01-scroll-common-capability/` | *待补充* | 0 |
| 05 组件层 | 03 滚动容器类组件 | 02 AlaphabetIndexer | `05-03-02` | `05-ui-components/03-scroll-container-components/02-alphabet-indexer/` | *待补充* | 0 |
| 05 组件层 | 03 滚动容器类组件 | 03 ScrollBar | `05-03-03` | `05-ui-components/03-scroll-container-components/03-scroll-bar/` | *待补充* | 0 |
| 05 组件层 | 03 滚动容器类组件 | 04 Grid/GridItem | `05-03-04` | `05-ui-components/03-scroll-container-components/04-grid-grid-item/` | *待补充* | 0 |
| 05 组件层 | 03 滚动容器类组件 | 05 List/ListItem/ListItemGroup | `05-03-05` | `05-ui-components/03-scroll-container-components/05-list-list-item-list-item-group/` | *待补充* | 0 |
| 05 组件层 | 03 滚动容器类组件 | 06 Refresh | `05-03-06` | `05-ui-components/03-scroll-container-components/06-refresh/` | *待补充* | 0 |
| 05 组件层 | 03 滚动容器类组件 | 07 Scroll | `05-03-07` | `05-ui-components/03-scroll-container-components/07-scroll/` | *待补充* | 0 |
| 05 组件层 | 03 滚动容器类组件 | 08 Swiper | `05-03-08` | `05-ui-components/03-scroll-container-components/08-swiper/` | [design.md](05-ui-components/03-scroll-container-components/08-swiper/design.md) | 6 |
| 05 组件层 | 03 滚动容器类组件 | 09 Tabs/TabContent | `05-03-09` | `05-ui-components/03-scroll-container-components/09-tabs-tab-content/` | [design.md](05-ui-components/03-scroll-container-components/09-tabs-tab-content/design.md) | 6 |
| 05 组件层 | 03 滚动容器类组件 | 10 WaterFlow/FlowItem | `05-03-10` | `05-ui-components/03-scroll-container-components/10-water-flow-flow-item/` | *待补充* | 0 |
| 05 组件层 | 04 输入表单类 | 01 Button | `05-04-01` | `05-ui-components/04-input-form-components/01-button/` | *待补充* | 0 |
| 05 组件层 | 04 输入表单类 | 02 Checkbox/CheckboxGroup | `05-04-02` | `05-ui-components/04-input-form-components/02-checkbox-checkbox-group/` | *待补充* | 0 |
| 05 组件层 | 04 输入表单类 | 03 Rating | `05-04-03` | `05-ui-components/04-input-form-components/03-rating/` | *待补充* | 0 |
| 05 组件层 | 04 输入表单类 | 04 Radio | `05-04-04` | `05-ui-components/04-input-form-components/04-radio/` | *待补充* | 0 |
| 05 组件层 | 04 输入表单类 | 05 Slider | `05-04-05` | `05-ui-components/04-input-form-components/05-slider/` | *待补充* | 0 |
| 05 组件层 | 04 输入表单类 | 06 Toggle | `05-04-06` | `05-ui-components/04-input-form-components/06-toggle/` | [design.md](05-ui-components/04-input-form-components/06-toggle/design.md) | 1 |
| 05 组件层 | 05 选择类组件 | 01 Calendar/CalendarPicker | `05-05-01` | `05-ui-components/05-picker-components/01-calendar-calendar-picker/` | *待补充* | 0 |
| 05 组件层 | 05 选择类组件 | 02 DatePicker | `05-05-02` | `05-ui-components/05-picker-components/02-date-picker/` | *待补充* | 0 |
| 05 组件层 | 05 选择类组件 | 03 TextPicker | `05-05-03` | `05-ui-components/05-picker-components/03-text-picker/` | *待补充* | 0 |
| 05 组件层 | 05 选择类组件 | 04 TimePicker | `05-05-04` | `05-ui-components/05-picker-components/04-time-picker/` | *待补充* | 0 |
| 05 组件层 | 05 选择类组件 | 05 Select | `05-05-05` | `05-ui-components/05-picker-components/05-select/` | *待补充* | 0 |
| 05 组件层 | 05 选择类组件 | 06 Picker | `05-05-06` | `05-ui-components/05-picker-components/06-picker/` | *待补充* | 0 |
| 05 组件层 | 06 弹窗类组件 | 01 Menu/MenuItem/MenuItemGroup | `05-06-01` | `05-ui-components/06-popup-components/01-menu-menu-item-menu-item-group/` | *待补充* | 0 |
| 05 组件层 | 06 弹窗类组件 | 02 警告弹窗 | `05-06-02` | `05-ui-components/06-popup-components/02-alert-dialog/` | *待补充* | 0 |
| 05 组件层 | 06 弹窗类组件 | 03 列表选择弹窗 | `05-06-03` | `05-ui-components/06-popup-components/03-list-selection-dialog/` | *待补充* | 0 |
| 05 组件层 | 06 弹窗类组件 | 04 自定义弹窗 | `05-06-04` | `05-ui-components/06-popup-components/04-custom-dialog/` | *待补充* | 0 |
| 05 组件层 | 06 弹窗类组件 | 05 CalendarPickerDialog | `05-06-05` | `05-ui-components/06-popup-components/05-calendar-picker-dialog/` | *待补充* | 0 |
| 05 组件层 | 06 弹窗类组件 | 06 DatePickerDialog | `05-06-06` | `05-ui-components/06-popup-components/06-date-picker-dialog/` | *待补充* | 0 |
| 05 组件层 | 06 弹窗类组件 | 07 TimePickerDialog | `05-06-07` | `05-ui-components/06-popup-components/07-time-picker-dialog/` | *待补充* | 0 |
| 05 组件层 | 06 弹窗类组件 | 08 TextPickerDialog | `05-06-08` | `05-ui-components/06-popup-components/08-text-picker-dialog/` | *待补充* | 0 |
| 05 组件层 | 06 弹窗类组件 | 09 ContextMenu接口 | `05-06-09` | `05-ui-components/06-popup-components/09-context-menu/` | *待补充* | 0 |
| 05 组件层 | 06 弹窗类组件 | 10 promptAction接口 | `05-06-10` | `05-ui-components/06-popup-components/10-prompt-action/` | *待补充* | 0 |
| 05 组件层 | 06 弹窗类组件 | 11 popup弹窗 | `05-06-11` | `05-ui-components/06-popup-components/11-popup/` | *待补充* | 0 |
| 05 组件层 | 07 模态类组件 | 01 半模态弹窗 | `05-07-01` | `05-ui-components/07-modal-components/01-sheet-modal/` | *待补充* | 0 |
| 05 组件层 | 07 模态类组件 | 02 全模态弹窗 | `05-07-02` | `05-ui-components/07-modal-components/02-full-modal/` | *待补充* | 0 |
| 05 组件层 | 07 模态类组件 | 03 Panel | `05-07-03` | `05-ui-components/07-modal-components/03-panel/` | *待补充* | 0 |
| 05 组件层 | 08 图片类组件 | 01 Image | `05-08-01` | `05-ui-components/08-image-components/01-image/` | [design.md](05-ui-components/08-image-components/01-image/design.md) | 5 |
| 05 组件层 | 08 图片类组件 | 02 ImageAnimator | `05-08-02` | `05-ui-components/08-image-components/02-image-animator/` | *待补充* | 0 |
| 05 组件层 | 08 图片类组件 | 03 MediaCachedImage | `05-08-03` | `05-ui-components/08-image-components/03-media-cached-image/` | *待补充* | 0 |
| 05 组件层 | 09 文本类组件 | 01 Marquee | `05-09-01` | `05-ui-components/09-text-components/01-marquee/` | *待补充* | 0 |
| 05 组件层 | 09 文本类组件 | 02 RichEditor | `05-09-02` | `05-ui-components/09-text-components/02-rich-editor/` | *待补充* | 0 |
| 05 组件层 | 09 文本类组件 | 03 Search | `05-09-03` | `05-ui-components/09-text-components/03-search/` | *待补充* | 0 |
| 05 组件层 | 09 文本类组件 | 04 Text | `05-09-04` | `05-ui-components/09-text-components/04-text/` | [design.md](05-ui-components/09-text-components/04-text/design.md) | 8 |
| 05 组件层 | 09 文本类组件 | 05 TextArea | `05-09-05` | `05-ui-components/09-text-components/05-text-area/` | *待补充* | 0 |
| 05 组件层 | 09 文本类组件 | 06 Span类 | `05-09-06` | `05-ui-components/09-text-components/06-span-components/` | *待补充* | 0 |
| 05 组件层 | 09 文本类组件 | 07 SymbolGlyph | `05-09-07` | `05-ui-components/09-text-components/07-symbol-glyph/` | *待补充* | 0 |
| 05 组件层 | 09 文本类组件 | 08 TextInput | `05-09-08` | `05-ui-components/09-text-components/08-text-input/` | *待补充* | 0 |
| 05 组件层 | 09 文本类组件 | 09 HyperLink | `05-09-09` | `05-ui-components/09-text-components/09-hyperlink/` | *待补充* | 0 |
| 05 组件层 | 09 文本类组件 | 10 属性字符串 | `05-09-10` | `05-ui-components/09-text-components/10-attributed-string/` | *待补充* | 0 |
| 05 组件层 | 10 信息展示类组件 | 01 DataPanel | `05-10-01` | `05-ui-components/10-information-display-components/01-data-panel/` | *待补充* | 0 |
| 05 组件层 | 10 信息展示类组件 | 02 Gauge | `05-10-02` | `05-ui-components/10-information-display-components/02-gauge/` | *待补充* | 0 |
| 05 组件层 | 10 信息展示类组件 | 03 LoadingProgress | `05-10-03` | `05-ui-components/10-information-display-components/03-loading-progress/` | *待补充* | 0 |
| 05 组件层 | 10 信息展示类组件 | 04 PatternLock | `05-10-04` | `05-ui-components/10-information-display-components/04-pattern-lock/` | *待补充* | 0 |
| 05 组件层 | 10 信息展示类组件 | 05 Progress | `05-10-05` | `05-ui-components/10-information-display-components/05-progress/` | *待补充* | 0 |
| 05 组件层 | 10 信息展示类组件 | 06 QRCode | `05-10-06` | `05-ui-components/10-information-display-components/06-qr-code/` | *待补充* | 0 |
| 05 组件层 | 10 信息展示类组件 | 07 TextClock | `05-10-07` | `05-ui-components/10-information-display-components/07-text-clock/` | *待补充* | 0 |
| 05 组件层 | 10 信息展示类组件 | 08 TextTimer | `05-10-08` | `05-ui-components/10-information-display-components/08-text-timer/` | *待补充* | 0 |
| 05 组件层 | 10 信息展示类组件 | 09 Badge | `05-10-09` | `05-ui-components/10-information-display-components/09-badge/` | *待补充* | 0 |
| 05 组件层 | 10 信息展示类组件 | 10 Counter | `05-10-10` | `05-ui-components/10-information-display-components/10-counter/` | *待补充* | 0 |
| 05 组件层 | 11 卡片框架组件 | 01 FormComponent | `05-11-01` | `05-ui-components/11-card-framework-components/01-form-component/` | *待补充* | 0 |
| 05 组件层 | 11 卡片框架组件 | 02 FormLink | `05-11-02` | `05-ui-components/11-card-framework-components/02-form-link/` | *待补充* | 0 |
| 05 组件层 | 12 显示嵌入组件 | 01 PluginComponent | `05-12-01` | `05-ui-components/12-embedded-display-components/01-plugin-component/` | *待补充* | 0 |
| 05 组件层 | 12 显示嵌入组件 | 02 AbilityComponent | `05-12-02` | `05-ui-components/12-embedded-display-components/02-ability-component/` | *待补充* | 0 |
| 05 组件层 | 12 显示嵌入组件 | 03 UIExtensionComponent | `05-12-03` | `05-ui-components/12-embedded-display-components/03-ui-extension-component/` | *待补充* | 0 |
| 05 组件层 | 12 显示嵌入组件 | 04 EmbeddedComponent | `05-12-04` | `05-ui-components/12-embedded-display-components/04-embedded-component/` | *待补充* | 0 |
| 05 组件层 | 12 显示嵌入组件 | 05 IsolatedComponent | `05-12-05` | `05-ui-components/12-embedded-display-components/05-isolated-component/` | *待补充* | 0 |
| 05 组件层 | 12 显示嵌入组件 | 06 SecurityUIExtensionComponent | `05-12-06` | `05-ui-components/12-embedded-display-components/06-security-ui-extension-component/` | *待补充* | 0 |
| 05 组件层 | 12 显示嵌入组件 | 07 DynamicComponent | `05-12-07` | `05-ui-components/12-embedded-display-components/07-dynamic-component/` | *待补充* | 0 |
| 05 组件层 | 13 平台类组件 | 01 XComponent | `05-13-01` | `05-ui-components/13-platform-components/01-xcomponent/` | *待补充* | 0 |
| 05 组件层 | 13 平台类组件 | 02 Video | `05-13-02` | `05-ui-components/13-platform-components/02-video/` | *待补充* | 0 |
| 05 组件层 | 14 绘制类组件 | 01 Shape相关 | `05-14-01` | `05-ui-components/14-drawing-components/01-shape/` | *待补充* | 0 |
| 05 组件层 | 14 绘制类组件 | 02 Canvas | `05-14-02` | `05-ui-components/14-drawing-components/02-canvas/` | *待补充* | 0 |
| 05 组件层 | 14 绘制类组件 | 03 OffscreenCanvas | `05-14-03` | `05-ui-components/14-drawing-components/03-offscreen-canvas/` | *待补充* | 0 |
| 05 组件层 | 15 主题组件 | 01 WithTheme | `05-15-01` | `05-ui-components/15-theme-components/01-with-theme/` | *待补充* | 0 |
| 05 组件层 | 16 自定义占位组件 | 01 NodeContainer | `05-16-01` | `05-ui-components/16-custom-placeholder-components/01-node-container/` | *待补充* | 0 |
| 05 组件层 | 16 自定义占位组件 | 02 ContentSlot | `05-16-02` | `05-ui-components/16-custom-placeholder-components/02-content-slot/` | *待补充* | 0 |
| 06 通用接口层 | 01 前端桥接 | 01 跨语言封装 | `06-01-01` | `06-common-interface/01-frontend-bridge/01-cross-language-wrapper/` | *待补充* | 0 |
| 06 通用接口层 | 01 前端桥接 | 02 JS引擎管理 | `06-01-02` | `06-common-interface/01-frontend-bridge/02-js-engine-management/` | *待补充* | 0 |
| 06 通用接口层 | 01 前端桥接 | 03 IDL工具 | `06-01-03` | `06-common-interface/01-frontend-bridge/03-idl-tool/` | *待补充* | 0 |
| 06 通用接口层 | 02 Inner接口 | 01 Inner-组件能力接口 | `06-02-01` | `06-common-interface/02-inner-interface/01-inner-component-interface/` | *待补充* | 0 |
| 06 通用接口层 | 02 Inner接口 | 02 Inner-基础能力接口 | `06-02-02` | `06-common-interface/02-inner-interface/02-inner-basic-interface/` | *待补充* | 0 |
| 06 通用接口层 | 03 其它范式接入 | 01 类Web范式 | `06-03-01` | `06-common-interface/03-paradigm-integration/01-web-like-paradigm/` | *待补充* | 0 |
| 06 通用接口层 | 03 其它范式接入 | 02 ArkTS卡片 | `06-03-02` | `06-common-interface/03-paradigm-integration/02-arkts-card/` | *待补充* | 0 |
| 06 通用接口层 | 03 其它范式接入 | 03 JS卡片 | `06-03-03` | `06-common-interface/03-paradigm-integration/03-js-card/` | *待补充* | 0 |
| 06 通用接口层 | 03 其它范式接入 | 04 FA模型 | `06-03-04` | `06-common-interface/03-paradigm-integration/04-fa-model/` | *待补充* | 0 |
| 06 通用接口层 | 03 其它范式接入 | 05 仓颉接入层 | `06-03-05` | `06-common-interface/03-paradigm-integration/05-cangjie-integration/` | *待补充* | 0 |
| 07 前端层 | 01 ArkTS高级组件 | 01 Chip | `07-01-01` | `07-frontend/01-arkts-advanced-components/01-chip/` | *待补充* | 0 |
| 07 前端层 | 01 ArkTS高级组件 | 02 ChipGroup | `07-01-02` | `07-frontend/01-arkts-advanced-components/02-chip-group/` | *待补充* | 0 |
| 07 前端层 | 01 ArkTS高级组件 | 03 ComposeListItem | `07-01-03` | `07-frontend/01-arkts-advanced-components/03-compose-list-item/` | *待补充* | 0 |
| 07 前端层 | 01 ArkTS高级组件 | 04 ComposeTitleBar | `07-01-04` | `07-frontend/01-arkts-advanced-components/04-compose-title-bar/` | *待补充* | 0 |
| 07 前端层 | 01 ArkTS高级组件 | 05 Counter | `07-01-05` | `07-frontend/01-arkts-advanced-components/05-counter/` | *待补充* | 0 |
| 07 前端层 | 01 ArkTS高级组件 | 06 Dialog | `07-01-06` | `07-frontend/01-arkts-advanced-components/06-dialog/` | *待补充* | 0 |
| 07 前端层 | 01 ArkTS高级组件 | 07 DownloadFileButton | `07-01-07` | `07-frontend/01-arkts-advanced-components/07-download-file-button/` | *待补充* | 0 |
| 07 前端层 | 01 ArkTS高级组件 | 08 EditableTitleBar | `07-01-08` | `07-frontend/01-arkts-advanced-components/08-editable-title-bar/` | *待补充* | 0 |
| 07 前端层 | 01 ArkTS高级组件 | 09 ExceptionPrompt | `07-01-09` | `07-frontend/01-arkts-advanced-components/09-exception-prompt/` | *待补充* | 0 |
| 07 前端层 | 01 ArkTS高级组件 | 10 Filter | `07-01-10` | `07-frontend/01-arkts-advanced-components/10-filter/` | *待补充* | 0 |
| 07 前端层 | 01 ArkTS高级组件 | 11 FormMenu | `07-01-11` | `07-frontend/01-arkts-advanced-components/11-form-menu/` | *待补充* | 0 |
| 07 前端层 | 01 ArkTS高级组件 | 12 ProgressButton | `07-01-12` | `07-frontend/01-arkts-advanced-components/12-progress-button/` | *待补充* | 0 |
| 07 前端层 | 01 ArkTS高级组件 | 13 FullScreenLaunchComponent | `07-01-13` | `07-frontend/01-arkts-advanced-components/13-full-screen-launch-component/` | *待补充* | 0 |
| 07 前端层 | 01 ArkTS高级组件 | 14 GridObjectSortComponent | `07-01-14` | `07-frontend/01-arkts-advanced-components/14-grid-object-sort-component/` | *待补充* | 0 |
| 07 前端层 | 01 ArkTS高级组件 | 15 ProgressButton | `07-01-15` | `07-frontend/01-arkts-advanced-components/15-progress-button/` | *待补充* | 0 |
| 07 前端层 | 01 ArkTS高级组件 | 16 Popup | `07-01-16` | `07-frontend/01-arkts-advanced-components/16-popup/` | *待补充* | 0 |
| 07 前端层 | 01 ArkTS高级组件 | 17 SegmentButton | `07-01-17` | `07-frontend/01-arkts-advanced-components/17-segment-button/` | *待补充* | 0 |
| 07 前端层 | 01 ArkTS高级组件 | 18 SelectionMenu | `07-01-18` | `07-frontend/01-arkts-advanced-components/18-selection-menu/` | *待补充* | 0 |
| 07 前端层 | 01 ArkTS高级组件 | 19 SelectTitleBar | `07-01-19` | `07-frontend/01-arkts-advanced-components/19-select-title-bar/` | *待补充* | 0 |
| 07 前端层 | 01 ArkTS高级组件 | 20 SplitLayout | `07-01-20` | `07-frontend/01-arkts-advanced-components/20-split-layout/` | *待补充* | 0 |
| 07 前端层 | 01 ArkTS高级组件 | 21 SubHeader | `07-01-21` | `07-frontend/01-arkts-advanced-components/21-sub-header/` | *待补充* | 0 |
| 07 前端层 | 01 ArkTS高级组件 | 22 SwipeRefresher | `07-01-22` | `07-frontend/01-arkts-advanced-components/22-swipe-refresher/` | *待补充* | 0 |
| 07 前端层 | 01 ArkTS高级组件 | 23 TabTitleBar | `07-01-23` | `07-frontend/01-arkts-advanced-components/23-tab-title-bar/` | *待补充* | 0 |
| 07 前端层 | 01 ArkTS高级组件 | 24 ToolBar | `07-01-24` | `07-frontend/01-arkts-advanced-components/24-tool-bar/` | *待补充* | 0 |
| 07 前端层 | 01 ArkTS高级组件 | 25 TreeView | `07-01-25` | `07-frontend/01-arkts-advanced-components/25-tree-view/` | *待补充* | 0 |
| 07 前端层 | 01 ArkTS高级组件 | 26 FoldSplitContainer | `07-01-26` | `07-frontend/01-arkts-advanced-components/26-fold-split-container/` | *待补充* | 0 |
| 07 前端层 | 02 状态管理框架 | 01 组件状态管理 | `07-02-01` | `07-frontend/02-state-management/01-component-state-management/` | *待补充* | 0 |
| 07 前端层 | 02 状态管理框架 | 02 应用状态管理 | `07-02-02` | `07-frontend/02-state-management/02-application-state-management/` | *待补充* | 0 |
| 07 前端层 | 02 状态管理框架 | 03 数据同步 | `07-02-03` | `07-frontend/02-state-management/03-data-synchronization/` | *待补充* | 0 |
| 07 前端层 | 02 状态管理框架 | 04 状态管理V2 | `07-02-04` | `07-frontend/02-state-management/04-state-management-v2/` | *待补充* | 0 |
| 07 前端层 | 02 状态管理框架 | 05 ArkTS静态化 | `07-02-05` | `07-frontend/02-state-management/05-arkts-staticization/` | *待补充* | 0 |
| 07 前端层 | 03 自定义组件 | 01 组件化 | `07-03-01` | `07-frontend/03-custom-components/01-componentization/` | *待补充* | 0 |
| 07 前端层 | 03 自定义组件 | 02 页面生命周期 | `07-03-02` | `07-frontend/03-custom-components/02-page-lifecycle/` | *待补充* | 0 |
| 07 前端层 | 03 自定义组件 | 03 组件扩展 | `07-03-03` | `07-frontend/03-custom-components/03-component-extension/` | *待补充* | 0 |
| 07 前端层 | 03 自定义组件 | 04 渲染控制语法 | `07-03-04` | `07-frontend/03-custom-components/04-render-control-syntax/` | *待补充* | 0 |
| 07 前端层 | 03 自定义组件 | 05 LazyForEach | `07-03-05` | `07-frontend/03-custom-components/05-lazy-foreach/` | *待补充* | 0 |
| 07 前端层 | 03 自定义组件 | 06 自定义测量/布局 | `07-03-06` | `07-frontend/03-custom-components/06-custom-measure-layout/` | *待补充* | 0 |
| 07 前端层 | 03 自定义组件 | 07 组件复用前端 | `07-03-07` | `07-frontend/03-custom-components/07-frontend-component-reuse/` | *待补充* | 0 |
| 07 前端层 | 04 生成式UI | 01 A2UI标准协议 | `07-04-01` | `07-frontend/04-generative-ui/01-a2ui-standard-protocol/` | *待补充* | 0 |
| 07 前端层 | 04 生成式UI | 02 A2UI扩展协议 | `07-04-02` | `07-frontend/04-generative-ui/02-a2ui-extension-protocol/` | *待补充* | 0 |
| 07 前端层 | 04 生成式UI | 03 A2UI高级垂域组件 | `07-04-03` | `07-frontend/04-generative-ui/03-a2ui-advanced-domain-components/` | *待补充* | 0 |
| 08 NDK | 01 Node C-API | 01 基础机制NativeModule | `08-01-01` | `08-ndk/01-node-c-api/01-native-module-base/` | *待补充* | 0 |
| 08 NDK | 01 Node C-API | 02 组件API | `08-01-02` | `08-ndk/01-node-c-api/02-component-api/` | *待补充* | 0 |
| 08 NDK | 01 Node C-API | 03 动效NativeAnimate | `08-01-03` | `08-ndk/01-node-c-api/03-native-animate/` | *待补充* | 0 |
| 08 NDK | 01 Node C-API | 04 视效接口 | `08-01-04` | `08-ndk/01-node-c-api/04-visual-effect-api/` | *待补充* | 0 |
| 08 NDK | 01 Node C-API | 05 事件EventModule | `08-01-05` | `08-ndk/01-node-c-api/05-event-module/` | *待补充* | 0 |
| 08 NDK | 01 Node C-API | 06 弹窗NativeDialog | `08-01-06` | `08-ndk/01-node-c-api/06-native-dialog/` | *待补充* | 0 |
| 08 NDK | 01 Node C-API | 07 手势NativeGesture | `08-01-07` | `08-ndk/01-node-c-api/07-native-gesture/` | *待补充* | 0 |
| 08 NDK | 01 Node C-API | 08 文本StyledString | `08-01-08` | `08-ndk/01-node-c-api/08-styled-string/` | *待补充* | 0 |
| 08 NDK | 01 Node C-API | 09 绘制DrawableDescriptor | `08-01-09` | `08-ndk/01-node-c-api/09-drawable-descriptor/` | *待补充* | 0 |
| 08 NDK | 01 Node C-API | 10 组件扩展 | `08-01-10` | `08-ndk/01-node-c-api/10-component-extension/` | *待补充* | 0 |
| 08 NDK | 01 Node C-API | 11 布局接口 | `08-01-11` | `08-ndk/01-node-c-api/11-layout-api/` | *待补充* | 0 |
| 08 NDK | 02 XComponent C-API | 01 Native XComponent | `08-02-01` | `08-ndk/02-xcomponent-c-api/01-native-xcomponent/` | *待补充* | 0 |
| 09 开发者工具 | 01 预览器 | 01 组件预览 | `09-01-01` | `09-developer-tools/01-previewer/01-component-preview/` | *待补充* | 0 |
| 09 开发者工具 | 01 预览器 | 02 基础预览 | `09-01-02` | `09-developer-tools/01-previewer/02-basic-preview/` | *待补充* | 0 |
| 09 开发者工具 | 01 预览器 | 03 动态预览 | `09-01-03` | `09-developer-tools/01-previewer/03-dynamic-preview/` | *待补充* | 0 |
| 09 开发者工具 | 01 预览器 | 04 热加载 | `09-01-04` | `09-developer-tools/01-previewer/04-hot-reload/` | *待补充* | 0 |
| 09 开发者工具 | 02 工具链 | 01 工具链 | `09-02-01` | `09-developer-tools/02-toolchain/01-toolchain/` | *待补充* | 0 |
| 09 开发者工具 | 03 开发者文档 | 01 入门指南文档 | `09-03-01` | `09-developer-tools/03-developer-docs/01-getting-started-docs/` | *待补充* | 0 |
| 09 开发者工具 | 03 开发者文档 | 02 API指南文档 | `09-03-02` | `09-developer-tools/03-developer-docs/02-api-guide-docs/` | *待补充* | 0 |
| 09 开发者工具 | 04 Sample应用 | 01 能力示范sample | `09-04-01` | `09-developer-tools/04-sample-apps/01-capability-sample/` | *待补充* | 0 |
| 09 开发者工具 | 05 ComponnetTest | 01 ComponnetTest测试框架 | `09-05-01` | `09-developer-tools/05-component-test/01-component-test-framework/` | *待补充* | 0 |
| 10 产品化定制 | 01 穿戴 | 01 弧形组件 | `10-01-01` | `10-product-customization/01-wearable/01-arc-component/` | *待补充* | 0 |

> 新增功能域时请在此表中按编号顺序添加行；未创建的设计文档以 `待补充` 标记。

---

## 已注册特性清单

### 01-01-01 编译构建

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|
| Feat-01 | BUILD.gn 结构 | [Feat-01-build-gn-structure-spec.md](01-architecture/01-architecture-design/01-build-system/Feat-01-build-gn-structure-spec.md) | Baselined |

### 01-01-02 目录结构

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 01-01-03 部件化

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 01-02-01 产品化解耦

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 02-01-01 OH平台适配

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 02-01-02 Android平台适配

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 02-01-03 iOS平台适配

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 02-01-04 预览器平台适配

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 02-02-01 渲染后端适配

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 03-01-01 渲染管线

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|
| Feat-01 | 渲染主流程 | [Feat-01-render-main-flow-spec.md](03-engine-framework/01-render-pipeline/01-basic-render-pipeline/Feat-01-render-main-flow-spec.md) | Baselined |

### 03-01-02 多级渲染管线

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 03-02-01 动效框架

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 03-02-02 属性动画

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 03-02-03 显式动画

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 03-02-04 关键帧动画

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 03-02-05 转场动画

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 03-02-06 共享元素动画

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 03-02-07 组件共享元素动画

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 03-02-08 路径动画

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 03-02-09 物理动画

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 03-02-10 动画接口

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 03-03-01 资源访问

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 03-03-02 主题分层访问

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 03-03-03 Theme框架

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 03-03-04 资源动态切换

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 03-04-01 事件基础框架

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 03-04-02 拖拽框架

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 03-05-01 窗口机制

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 03-05-02 子窗机制

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 03-06-01 多实例管理

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 03-07-01 无障碍能力

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 03-07-02 Inspector

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 03-08-01 日志

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 03-08-02 内存管理

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 03-08-03 Trace打点

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 03-08-04 Dump机制

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 03-08-05 Benchmark

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 03-08-06 布局边界显示

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-01-01 图片加载机制

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|
| Feat-01 | 图片加载机制 | [Feat-01-image-loading-mechanism-spec.md](04-common-capability/01-image-loading/01-image-loading-mechanism/Feat-01-image-loading-mechanism-spec.md) | Baselined |

### 04-01-02 Svg解析

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-01-03 DrawableDescriptor 能力

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|
| Feat-01 | DrawableDescriptor 能力 (TS + C API) | [Feat-01-drawable-descriptor-spec.md](04-common-capability/01-image-loading/03-drawable-descriptor/Feat-01-drawable-descriptor-spec.md) | Baselined |

### 04-02-01 安全区机制

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-03-01 布局属性

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|
| Feat-01 | 尺寸属性 (width/height/size/constraintSize/padding/margin) | [Feat-01-size-properties-spec.md](04-common-capability/03-common-attributes/01-layout-attributes/Feat-01-size-properties-spec.md) | Baselined |
| Feat-02 | 位置属性 (position/offset/markAnchor/align/direction) | [Feat-02-position-properties-spec.md](04-common-capability/03-common-attributes/01-layout-attributes/Feat-02-position-properties-spec.md) | Baselined |
| Feat-03 | Flex 相关属性 (flexGrow/flexShrink/flexBasis/alignSelf/layoutWeight/displayPriority) | [Feat-03-flex-properties-spec.md](04-common-capability/03-common-attributes/01-layout-attributes/Feat-03-flex-properties-spec.md) | Baselined |

### 04-03-02 视效属性

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|
| Feat-01 | 图像效果 | [Feat-01-image-effects-spec.md](04-common-capability/03-common-attributes/02-visual-effect-attributes/Feat-01-image-effects-spec.md) | Baselined |

### 04-03-03 基础属性

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-03-04 交互属性

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-03-05 弹窗类属性

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-03-06 模态属性

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-03-07 样式属性

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-03-08 基础单位

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-03-09 无障碍属性

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-03-10 图片相关属性

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-03-11 文本通用属性

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-04-01 触摸事件

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-04-02 按键事件

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-04-03 事件分发和拦截

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-04-04 组件组合键

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-04-05 鼠标事件

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-04-06 手势能力

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|
| Feat-01 | 基础手势 (Tap/LongPress/Pan/Pinch/Rotation/Swipe) | [Feat-01-basic-gestures-spec.md](04-common-capability/04-common-events/06-gesture-capability/Feat-01-basic-gestures-spec.md) | Baselined |
| Feat-02 | 组合手势 (GestureGroup: Sequential/Parallel/Exclusive) | [Feat-02-gesture-group-spec.md](04-common-capability/04-common-events/06-gesture-capability/Feat-02-gesture-group-spec.md) | Baselined |
| Feat-03 | 手势判定 (GestureReferee: 手势仲裁机制) | [Feat-03-gesture-referee-spec.md](04-common-capability/04-common-events/06-gesture-capability/Feat-03-gesture-referee-spec.md) | Baselined |
| Feat-04 | 手势拦截 (Touch Intercept / responseLink / hitTestBehavior) | [Feat-04-gesture-intercept-spec.md](04-common-capability/04-common-events/06-gesture-capability/Feat-04-gesture-intercept-spec.md) | Baselined |
| Feat-05 | 手势识别异常恢复增强 | [Feat-05-gesture-recognizer-recovery-spec.md](04-common-capability/04-common-events/06-gesture-capability/Feat-05-gesture-recognizer-recovery-spec.md) | Draft |

### 04-04-07 拖拽能力

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-04-08 手写笔能力

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-04-09 组件相关事件

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-04-10 可见区域机制

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-04-11 交互归一化

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-05-01 动态绘制属性

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-05-02 动态属性

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-05-03 自定义内容 -（表单类组件）

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-05-04 自定义内容 -（信息展示类）

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-05-05 自定义属性

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-05-06 组件Modifier

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-06-01 占位组件

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-06-02 FrameNode

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-06-03 RenderNode

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-06-04 BuilderNode

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-06-05 ComponentContent

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-06-06 NodeAdapter

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-06-07 TypedFrameNode

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-07-01 分布式路由迁移能力

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-07-02 路由栈恢复

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-07-03 组件迁移机制

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-08-01 窗口工具栏

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-08-02 元服务AppBar

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-08-03 浮层能力

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-09-01 焦点机制

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-10-01 离屏截图

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-11-01 ComponentUtils

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-11-02 无感监听（observer）

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-11-03 布局回调（inspector）

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-12-01 UIContext接口

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-12-02 Ability上下文

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-12-03 Frame回调接口

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-13-01 字体注册

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-13-02 文本测量

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-14-01 文本选择

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-14-02 文本快捷键

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-14-03 文本交互

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-14-04 键盘控制

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-14-05 自动补全能力（AutoFill）

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-15-01 路由管理

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-15-03 命名路由

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-16-01 UIAppearance

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-17-01 UIExtension机制

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-17-02 IsolateComponent机制

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-17-03 From卡片机制

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-17-04 PluginComponent机制

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-18-01 同层渲染机制

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-19-01 组件复用框架

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-20-01 MediaQuery

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-21-01 大字体

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-22-01 多语言能力

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-22-02 镜像能力

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-23-01 Image分析能力

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-24-01 像素取整能力

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-25-01 热重载机制

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-01-01 Blank

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|
| Feat-01 | Blank 组件 | [Feat-01-blank-component-spec.md](05-ui-components/01-layout-components/01-blank/Feat-01-blank-component-spec.md) | Baselined |

### 05-01-02 Divider

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|
| Feat-01 | Divider 组件全量规格 | [Feat-01-divider-spec.md](05-ui-components/01-layout-components/02-divider/Feat-01-divider-spec.md) | Baselined |

### 05-01-03 Column

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-01-04 ColumnSplit

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-01-05 Flex

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-01-06 GridCol

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-01-07 GridRow

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-01-08 RelativeContainer

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-01-09 Row

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-01-10 RowSplit

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-01-11 Stack

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-01-12 FolderStack

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-01-13 DynamicLayout

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-02-01 Navigation

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|
| Feat-01 | 创建与布局模式 | [Feat-01-navigation-creation-layout-mode-spec.md](05-ui-components/02-navigation-components/01-navigation/Feat-01-navigation-creation-layout-mode-spec.md) | Baselined |
| Feat-02 | 标题栏配置 | [Feat-02-navigation-title-bar-spec.md](05-ui-components/02-navigation-components/01-navigation/Feat-02-navigation-title-bar-spec.md) | Baselined |
| Feat-03 | 工具栏配置 | [Feat-03-navigation-toolbar-spec.md](05-ui-components/02-navigation-components/01-navigation/Feat-03-navigation-toolbar-spec.md) | Baselined |
| Feat-04 | 路由栈管理 | [Feat-04-navigation-route-stack-spec.md](05-ui-components/02-navigation-components/01-navigation/Feat-04-navigation-route-stack-spec.md) | Baselined |
| Feat-05 | 转场动画与自定义过渡 | [Feat-05-navigation-transition-spec.md](05-ui-components/02-navigation-components/01-navigation/Feat-05-navigation-transition-spec.md) | Baselined |
| Feat-06 | 系统栏/安全区/分栏/恢复 | [Feat-06-navigation-system-bar-split-recovery-spec.md](05-ui-components/02-navigation-components/01-navigation/Feat-06-navigation-system-bar-split-recovery-spec.md) | Baselined |
| Feat-07 | 事件回调与Modifier | [Feat-07-navigation-events-modifier-spec.md](05-ui-components/02-navigation-components/01-navigation/Feat-07-navigation-events-modifier-spec.md) | Baselined |

### 05-02-02 NavRouter

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-02-03 NavDestination

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-02-04 Stepper/SetpperItem

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-02-05 Navigator

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-02-06 SideBarContainer

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|
| Feat-01 | 全量规格 | [Feat-01-side-bar-container-full-spec.md](05-ui-components/02-navigation-components/06-sidebar-container/Feat-01-side-bar-container-full-spec.md) | Baselined |

### 05-03-01 滚动公共能力

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-03-02 AlaphabetIndexer

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-03-03 ScrollBar

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-03-04 Grid/GridItem

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-03-05 List/ListItem/ListItemGroup

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-03-06 Refresh

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-03-07 Scroll

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-03-08 Swiper

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|
| Feat-01 | 创建与布局属性 | [Feat-01-swiper-creation-layout-spec.md](05-ui-components/03-scroll-container-components/08-swiper/Feat-01-swiper-creation-layout-spec.md) | Baselined |
| Feat-02 | 自动播放与指示器 | [Feat-02-swiper-autoplay-indicator-spec.md](05-ui-components/03-scroll-container-components/08-swiper/Feat-02-swiper-autoplay-indicator-spec.md) | Baselined |
| Feat-03 | 动画与过渡 | [Feat-03-swiper-animation-transition-spec.md](05-ui-components/03-scroll-container-components/08-swiper/Feat-03-swiper-animation-transition-spec.md) | Baselined |
| Feat-04 | 交互与控制器 | [Feat-04-swiper-interaction-controller-spec.md](05-ui-components/03-scroll-container-components/08-swiper/Feat-04-swiper-interaction-controller-spec.md) | Baselined |
| Feat-05 | 事件回调 | [Feat-05-swiper-events-spec.md](05-ui-components/03-scroll-container-components/08-swiper/Feat-05-swiper-events-spec.md) | Baselined |
| Feat-06 | C API 全量规格 | [Feat-06-swiper-capi-spec.md](05-ui-components/03-scroll-container-components/08-swiper/Feat-06-swiper-capi-spec.md) | Baselined |

### 05-03-09 Tabs/TabContent

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|
| Feat-01 | 创建与基础属性 | [Feat-01-tabs-creation-basic-properties-spec.md](05-ui-components/03-scroll-container-components/09-tabs-tab-content/Feat-01-tabs-creation-basic-properties-spec.md) | Baselined |
| Feat-02 | 标签栏样式 | [Feat-02-tabs-bar-style-spec.md](05-ui-components/03-scroll-container-components/09-tabs-tab-content/Feat-02-tabs-bar-style-spec.md) | Baselined |
| Feat-03 | 侧边栏模式 | [Feat-03-tabs-sidebar-mode-spec.md](05-ui-components/03-scroll-container-components/09-tabs-tab-content/Feat-03-tabs-sidebar-mode-spec.md) | Baselined |
| Feat-04 | 动画与自定义过渡 | [Feat-04-tabs-animation-transition-spec.md](05-ui-components/03-scroll-container-components/09-tabs-tab-content/Feat-04-tabs-animation-transition-spec.md) | Baselined |
| Feat-05 | 事件回调 | [Feat-05-tabs-events-spec.md](05-ui-components/03-scroll-container-components/09-tabs-tab-content/Feat-05-tabs-events-spec.md) | Baselined |
| Feat-06 | 缓存与滚动控制 | [Feat-06-tabs-cache-scroll-spec.md](05-ui-components/03-scroll-container-components/09-tabs-tab-content/Feat-06-tabs-cache-scroll-spec.md) | Baselined |

### 05-03-10 WaterFlow/FlowItem

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-04-01 Button

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-04-02 Checkbox/CheckboxGroup

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-04-03 Rating

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-04-04 Radio

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-04-05 Slider

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-04-06 Toggle

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|
| Feat-01 | Toggle 组件全量规格 | [Feat-01-toggle-spec.md](05-ui-components/04-input-form-components/06-toggle/Feat-01-toggle-spec.md) | Baselined |

### 05-05-01 Calendar/CalendarPicker

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-05-02 DatePicker

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-05-03 TextPicker

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-05-04 TimePicker

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-05-05 Select

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-05-06 Picker

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-06-01 Menu/MenuItem/MenuItemGroup

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-06-02 警告弹窗

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-06-03 列表选择弹窗

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-06-04 自定义弹窗

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-06-05 CalendarPickerDialog

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-06-06 DatePickerDialog

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-06-07 TimePickerDialog

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-06-08 TextPickerDialog

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-06-09 ContextMenu接口

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-06-10 promptAction接口

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-06-11 popup弹窗

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-07-01 半模态弹窗

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-07-02 全模态弹窗

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-07-03 Panel

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-08-01 Image

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|
| Feat-01 | 核心显示属性 | [Feat-01-image-core-display-spec.md](05-ui-components/08-image-components/01-image/Feat-01-image-core-display-spec.md) | Baselined |
| Feat-02 | 颜色与效果 | [Feat-02-image-color-effects-spec.md](05-ui-components/08-image-components/01-image/Feat-02-image-color-effects-spec.md) | Baselined |
| Feat-03 | 高级功能 | [Feat-03-image-advanced-spec.md](05-ui-components/08-image-components/01-image/Feat-03-image-advanced-spec.md) | Baselined |
| Feat-04 | 事件回调 | [Feat-04-image-events-spec.md](05-ui-components/08-image-components/01-image/Feat-04-image-events-spec.md) | Baselined |
| Feat-05 | Image 组件基础内存优化 | [Feat-05-image-base-memory-opt-spec.md](05-ui-components/08-image-components/01-image/Feat-05-image-base-memory-opt-spec.md) | Draft |

### 05-08-02 ImageAnimator

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-08-03 MediaCachedImage

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-09-01 Marquee

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-09-02 RichEditor

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-09-03 Search

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-09-04 Text

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|
| Feat-01 | 字体属性与自适应字体 | [Feat-01-font-properties-spec.md](05-ui-components/09-text-components/04-text/Feat-01-font-properties-spec.md) | Baselined |
| Feat-02 | 行/段落布局 | [Feat-02-line-paragraph-layout-spec.md](05-ui-components/09-text-components/04-text/Feat-02-line-paragraph-layout-spec.md) | Baselined |
| Feat-03 | 溢出与截断 | [Feat-03-overflow-truncation-spec.md](05-ui-components/09-text-components/04-text/Feat-03-overflow-truncation-spec.md) | Baselined |
| Feat-04 | 装饰与样式 (decoration/textShadow/textCase/shaderStyle/contentTransition/marqueeOptions) | [Feat-04-decoration-styles-spec.md](05-ui-components/09-text-components/04-text/Feat-04-decoration-styles-spec.md) | Baselined |
| Feat-05 | 选择与复制 | [Feat-05-selection-copy-spec.md](05-ui-components/09-text-components/04-text/Feat-05-selection-copy-spec.md) | Baselined |
| Feat-06 | 系统能力（数据检测、隐私、震感） | [Feat-06-system-capabilities-spec.md](05-ui-components/09-text-components/04-text/Feat-06-system-capabilities-spec.md) | Baselined |
| Feat-07 | 事件回调 (onCopy/onWillCopy/onTextSelectionChange/onMarqueeStateChange) | [Feat-07-event-callbacks-spec.md](05-ui-components/09-text-components/04-text/Feat-07-event-callbacks-spec.md) | Baselined |
| Feat-08 | Text 尾部缩进 | *待补充* | 待补充 |

### 05-09-05 TextArea

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-09-06 Span类

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-09-07 SymbolGlyph

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-09-08 TextInput

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-09-09 HyperLink

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-09-10 属性字符串

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-10-01 DataPanel

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-10-02 Gauge

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-10-03 LoadingProgress

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-10-04 PatternLock

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-10-05 Progress

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-10-06 QRCode

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-10-07 TextClock

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-10-08 TextTimer

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-10-09 Badge

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-10-10 Counter

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-11-01 FormComponent

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-11-02 FormLink

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-12-01 PluginComponent

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-12-02 AbilityComponent

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-12-03 UIExtensionComponent

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-12-04 EmbeddedComponent

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-12-05 IsolatedComponent

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-12-06 SecurityUIExtensionComponent

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-12-07 DynamicComponent

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-13-01 XComponent

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-13-02 Video

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-14-01 Shape相关

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-14-02 Canvas

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-14-03 OffscreenCanvas

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-15-01 WithTheme

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-16-01 NodeContainer

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 05-16-02 ContentSlot

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 06-01-01 跨语言封装

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 06-01-02 JS引擎管理

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 06-01-03 IDL工具

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 06-02-01 Inner-组件能力接口

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 06-02-02 Inner-基础能力接口

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 06-03-01 类Web范式

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 06-03-02 ArkTS卡片

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 06-03-03 JS卡片

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 06-03-04 FA模型

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 06-03-05 仓颉接入层

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 07-01-01 Chip

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 07-01-02 ChipGroup

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 07-01-03 ComposeListItem

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 07-01-04 ComposeTitleBar

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 07-01-05 Counter

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 07-01-06 Dialog

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 07-01-07 DownloadFileButton

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 07-01-08 EditableTitleBar

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 07-01-09 ExceptionPrompt

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 07-01-10 Filter

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 07-01-11 FormMenu

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 07-01-12 ProgressButton

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 07-01-13 FullScreenLaunchComponent

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 07-01-14 GridObjectSortComponent

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 07-01-15 ProgressButton

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 07-01-16 Popup

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 07-01-17 SegmentButton

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 07-01-18 SelectionMenu

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 07-01-19 SelectTitleBar

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 07-01-20 SplitLayout

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 07-01-21 SubHeader

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 07-01-22 SwipeRefresher

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 07-01-23 TabTitleBar

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 07-01-24 ToolBar

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 07-01-25 TreeView

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 07-01-26 FoldSplitContainer

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 07-02-01 组件状态管理

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 07-02-02 应用状态管理

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 07-02-03 数据同步

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 07-02-04 状态管理V2

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 07-02-05 ArkTS静态化

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 07-03-01 组件化

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 07-03-02 页面生命周期

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 07-03-03 组件扩展

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 07-03-04 渲染控制语法

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 07-03-05 LazyForEach

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 07-03-06 自定义测量/布局

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 07-03-07 组件复用前端

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 07-04-01 A2UI标准协议

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 07-04-02 A2UI扩展协议

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 07-04-03 A2UI高级垂域组件

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 08-01-01 基础机制NativeModule

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 08-01-02 组件API

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 08-01-03 动效NativeAnimate

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 08-01-04 视效接口

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 08-01-05 事件EventModule

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 08-01-06 弹窗NativeDialog

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 08-01-07 手势NativeGesture

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 08-01-08 文本StyledString

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 08-01-09 绘制DrawableDescriptor

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 08-01-10 组件扩展

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 08-01-11 布局接口

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 08-02-01 Native XComponent

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 09-01-01 组件预览

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 09-01-02 基础预览

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 09-01-03 动态预览

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 09-01-04 热加载

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 09-02-01 工具链

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 09-03-01 入门指南文档

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 09-03-02 API指南文档

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 09-04-01 能力示范sample

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 09-05-01 ComponnetTest测试框架

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 10-01-01 弧形组件

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

---

## 注册规则

1. **新增功能域**：在 `registry/functions.yaml` 中添加 FuncID 记录；如 `design.md` 尚未创建，`design` 字段置空；重新生成 `index.md`。
2. **新增特性**：仅在具体规格补录开始、功能点/特性范围明确后，在 `registry/features.yaml` 中追加 FeatID 记录，包含 FuncID、FeatID、特性名称、Spec 文件、状态（`待补充`/`Draft`/`Baselined`/`Deprecated`）。
3. **排序规则**：功能域按 FuncID 数值升序排列（`03-01-01` < `04-03-01` < `05-01-01`）；同一功能域内 FeatID 按 `Feat-01, Feat-02, ...` 顺序递增。
4. **状态流转**：待补充 → Draft → Baselined（经评审通过后）→ Deprecated（被新特性替代）。
5. **目录命名**：使用英文 slug（小写 + 短横线分隔），编号使用两位数字（`01-`, `02-`, ...）。
6. **FeatID 编号**：同一功能域内从 `Feat-01` 顺序递增；历史功能域导入时不根据 Excel `一级功能点` 自动生成 FeatID。

---

## 术语表

### 规格文档结构

| 缩写 | 全称 | 中文 | 说明 |
|------|------|------|------|
| **US** | User Story | 用户故事 | 以“作为...我想要...以便...”格式描述用户需求。每个 US 包含多个 AC |
| **AC** | Acceptance Criterion | 验收标准 | 每个 US 下的可验证行为描述。编号格式 `AC-<US号>.<序号>`，如 `AC-1.3` |
| **BR** | Business Rule | 业务规则 | 领域语义约束，描述跨多个 US 的业务级规则 |
| **FR** | Functional Rule | 功能规则 | 具体行为规则，描述单个可观察的功能行为 |
| **ER** | Exception/Exemption Rule | 异常/豁免规则 | 边界条件、异常输入的处理规则 |
| **RC** | Recovery Contract | 恢复契约 | 错误恢复路径和重置行为的契约描述 |

### 设计文档结构

| 缩写 | 全称 | 中文 | 说明 |
|------|------|------|------|
| **ADR** | Architecture Decision Record | 架构决策记录 | 记录关键设计决策，包含问题、推荐方案、替代方案、取舍理由、影响。格式：基线用 `ADR-N`（首个特性），后续特性用 `ADR-FX-N`（如 `ADR-F3-1`） |
| **FuncID** | Functional Domain ID | 功能域编号 | 3 段数字标识（如 `04-03-01`），唯一标识一个功能域 |
| **FeatID** | Feature ID | 特性编号 | `Feat-NN` 格式，功能域内唯一 |

### 验证/测试

| 缩写 | 全称 | 中文 | 说明 |
|------|------|------|------|
| **XTS** | X Test Suite | 兼容性测试套件 | OpenHarmony 兼容性测试，位于 `test/xts/` 目录 |
| **Gherkin** | — | Gherkin 语法 | 行为驱动开发（BDD）的场景描述语言：`Given/When/Then` |
| **VM** | Verification Mapping | 验证映射 | 每个 AC 到验证手段的映射表 |

---

## 文件命名规范

| 文件类型 | 命名格式 | 示例 |
|----------|----------|------|
| 设计文档 | `design.md` | `04-common-capability/03-common-attributes/01-layout-attributes/design.md` |
| 特性规格 | `Feat-NN-<name>-spec.md` | `04-common-capability/03-common-attributes/01-layout-attributes/Feat-03-flex-properties-spec.md` |
| 索引文件 | `index.md` | `index.md`（本文件） |

## 流程关联

```
新特性补录流程:
  1. 在 registry/functions.yaml 中确认/创建 FuncID
  2. 具体规格补录开始、功能点/特性范围明确后，在 registry/features.yaml 中追加 FeatID 记录；未生成规格时状态为待补充
  3. 创建 <func-domain>/ 目录（如不存在）
  4. 生成/更新 design.md，并将 functions.yaml 的 design 字段从空值改为路径
  5. 生成 Feat-NN-<name>-spec.md，并将 features.yaml 的 spec 字段从空值改为路径
  6. 更新 features.yaml 特性状态为 Draft 或 Baselined
  7. 运行 tools/generate_index.py 重新生成 index.md
```
