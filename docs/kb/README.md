# ArkUI KB

> 更新时间：2026-08-04
> 主题数：228
> 适用范围：`OpenHarmony/foundation/arkui/ace_engine/docs/kb`

`docs/kb/` 是新版知识库专区。新版 KB 只作为 Agent 上下文导航页，行为事实以源码、SDK/API 声明、测试和 Spec 为准。

## 目录约束

```text
docs/kb/
├── components/      # 对外 UI 组件
├── capabilities/    # 通用能力
├── architecture/    # 引擎架构和框架机制
├── api/             # SDK、C API、NAPI、API 范式
├── syntax/          # ArkTS 声明式语法专题
├── issues/          # 历史典型问题与排查经验
└── _generated/      # 可再生成索引页
```

组件 KB 按 `docs/kb/components/<category>/<name>.md` 放置，例如 Text 试点页为 `docs/kb/components/basic/text.md`。

## 编写规则

- 新增 KB 必须同步 `docs/context_registry.json`。
- KB 迁移到新版路径后，同步删除对应旧 KB 文件，不再通过 `legacy_kb` 保留旧入口。
- KB 保留定位、源码/API/测试/Spec 路由、调试入口和常见问题定位。
- KB 不长期维护完整 API 行为矩阵、AC/BR/FR/ER/RC 或大段调用链复述。
- 代码级结论必须能从真实源码或 SDK 声明验证，未验证内容标注为“推测”。

## 当前主题

### 知识型 KB

| ID | 主题 | 新版 KB | 状态 |
|----|------|---------|------|
| LayoutFramework | 布局框架 | `docs/kb/architecture/layout-framework.md` | 已重建，旧 KB 已移除 |
| LayoutAttributes | 基础布局属性 | `docs/kb/capabilities/layout-attributes.md` | 新建 |
| SafeArea | 安全区域机制 | `docs/kb/capabilities/safe-area.md` | 已合并重建，两份旧 KB 已移除 |
| PixelRounding | 像素取整能力 | `docs/kb/capabilities/pixel-rounding.md` | 新建（Spec 待补） |
| Blank | 空白填充组件 | `docs/kb/components/basic/blank.md` | 新建 |
| Divider | 分隔线组件 | `docs/kb/components/basic/divider.md` | 新建 |
| Column | 纵向布局组件 | `docs/kb/components/container/column.md` | 新建 |
| ColumnSplit | 纵向分割布局组件 | `docs/kb/components/container/column_split.md` | 新建（Spec 待补） |
| Flex | 弹性布局组件（含 Wrap） | `docs/kb/components/container/flex.md` | 已重建，旧 KB 已移除 |
| GridCol | 响应式栅格列组件 | `docs/kb/components/container/grid_col.md` | 新建 |
| GridRow | 响应式栅格行组件 | `docs/kb/components/container/grid_row.md` | 新建 |
| Grid | 滚动型网格布局组件 | `docs/kb/components/container/grid.md` | 已迁移，旧 KB 已移除 |
| GridItem | 网格项组件 | `docs/kb/components/container/grid_item.md` | 新建 |
| RelativeContainer | 相对布局容器组件 | `docs/kb/components/container/relative_container.md` | 新建 |
| Row | 横向布局组件 | `docs/kb/components/container/row.md` | 新建 |
| RowSplit | 横向分割布局组件 | `docs/kb/components/container/row_split.md` | 新建（Spec 待补） |
| Stack | 层叠布局组件 | `docs/kb/components/container/stack.md` | 新建 |
| FolderStack | 折叠屏层叠布局组件 | `docs/kb/components/container/folder_stack.md` | 新建 |
| DynamicLayout | 动态布局组件 | `docs/kb/components/container/dynamic_layout.md` | 新建 |
| Shape | Shape 类绘制组件 | `docs/kb/components/shape/shape.md` | 新建（Spec 待补） |
| Canvas | 画布组件 | `docs/kb/components/shape/canvas.md` | 新建（Spec 待补） |
| OffscreenCanvas | 离屏画布对象 | `docs/kb/components/shape/offscreen_canvas.md` | 新建（Spec 待补） |
| Text | 文本组件 | `docs/kb/components/basic/text.md` | 已迁移，旧 KB 已移除 |
| TextArea | 多行文本输入组件 | `docs/kb/components/basic/text_area.md` | 已迁移，旧 KB 已移除 |
| Marquee | 跑马灯组件 | `docs/kb/components/basic/marquee.md` | 已迁移，旧 KB 已移除 |
| Search | 搜索框组件 | `docs/kb/components/basic/search.md` | 已迁移，旧 KB 已移除 |
| Span | 文本片段组件 | `docs/kb/components/basic/span.md` | 新建（无旧 KB） |
| ImageSpan | 图片片段组件 | `docs/kb/components/basic/image_span.md` | 新建（无旧 KB） |
| SymbolSpan | 符号片段组件 | `docs/kb/components/basic/symbol_span.md` | 新建（无旧 KB） |
| ContainerSpan | 容器片段组件 | `docs/kb/components/basic/container_span.md` | 新建（无旧 KB） |
| RichEditor | 富文本编辑器组件 | `docs/kb/components/basic/rich_editor.md` | 已迁移，旧 KB 已移除 |
| SymbolGlyph | 符号字形组件 | `docs/kb/components/basic/symbol-glyph.md` | 新建；补齐 Spec 路由（复用 TextPattern） |
| TextInput | 文本输入组件 | `docs/kb/components/basic/text-input.md` | 已迁移，旧 KB 已移除；共享 TextFieldPattern |
| Hyperlink | 超链接组件 | `docs/kb/components/basic/hyperlink.md` | 已迁移，旧 KB 已移除；独立 HyperlinkPattern(继承 TextPattern) |
| StyledString | 属性字符串 | `docs/kb/capabilities/styled-string.md` | 新建；非组件，common_capability/api |
| TextShortcuts | 文本快捷键能力 | `docs/kb/capabilities/text-shortcuts.md` | 新建；框架内部能力(无公共 API)，补齐 Spec 路由 |
| InputMethodInteraction | 输入法交互能力 | `docs/kb/capabilities/input-method-interaction.md` | 新建；框架内部能力，输入框↔键盘交互(IME 弹出收起/避让/输入处理契约/公共 API)；特性名由键盘控制改 |
| Image | 图片组件 | `docs/kb/components/media/image.md` | 已迁移，旧 KB 已移除 |
| ImageAnimator | 图片动画组件 | `docs/kb/components/media/image_animator.md` | 已迁移，旧 KB 已移除 |
| Video | 视频组件 | `docs/kb/components/media/video.md` | 新建（无旧 KB） |
| DrawableDescriptor | 图片资源描述能力 | `docs/kb/capabilities/drawable_descriptor.md` | 新增 |
| ImageLoading | 图片加载机制 | `docs/kb/capabilities/image-loading.md` | 新建 |
| SVG | SVG 解析能力 | `docs/kb/capabilities/svg.md` | 已迁移，旧 KB 已移除 |
| BackgroundImage | 背景图片通用属性 | `docs/kb/capabilities/background-image.md` | 新建 |
| ImageAnalyzer | Image 分析能力 | `docs/kb/capabilities/image-analyzer.md` | 新建 |
| Toggle | 开关组件 | `docs/kb/components/selector/toggle.md` | 已迁移，旧 KB 已移除 |
| Navigation | 导航容器组件 | `docs/kb/components/container/navigation.md` | 新建 |
| Tabs | 标签页容器组件 | `docs/kb/components/container/tabs.md` | 新建 |
| Swiper | 轮播容器组件 | `docs/kb/components/container/swiper.md` | 新建 |
| WaterFlow | 瀑布流组件 | `docs/kb/components/container/waterflow.md` | 已迁移，旧 KB 已移除；补齐 05-03-10 Spec 路由 |
| PlaceholderComponent | 占位组件（概念入口，转跳 05-16-01/02） | `docs/kb/capabilities/placeholder_component.md` | 新建 |
| NodeAdapter | NodeAdapter 命令式懒渲染适配器 | `docs/kb/capabilities/node_adapter.md` | 新建 |
| SameLayerRendering | 同层渲染（纹理导出生产者，FuncID 04-18-01） | `docs/kb/capabilities/same-layer-rendering.md` | 新建 |
| ComponentReuseFramework | 组件复用框架（引擎 C++） | `docs/kb/architecture/component_reuse_framework.md` | 新建 |
| AbilityComponent | AbilityComponent 跨进程嵌入组件（已废弃） | `docs/kb/components/embedded/ability_component.md` | 新建 |
| NodeContainer | NodeContainer 自定义占位组件 | `docs/kb/components/custom-node/node_container.md` | 新建 |
| ContentSlot | ContentSlot 自定义占位组件 | `docs/kb/components/custom-node/content_slot.md` | 新建 |
| RenderControl | 渲染控制语法（if/else + ForEach + 共享框架） | `docs/kb/syntax/render_control.md` | 迁移自旧 `ForEach` KB |
| LazyForEach | LazyForEach 懒加载循环渲染 | `docs/kb/syntax/lazy_for_each.md` | 已迁移，旧 KB 已移除 |
| Repeat | Repeat 循环渲染与虚拟滚动（含 RepeatVirtualScroll） | `docs/kb/syntax/repeat.md` | 已迁移，旧 KB 已移除 |
| SideBarContainer | 侧边栏容器组件 | `docs/kb/components/container/side_bar_container.md` | 新建 |
| NavDestination | 导航目标页组件 | `docs/kb/components/container/navdestination.md` | 新建 |
| Scroll | 滚动容器组件 | `docs/kb/components/container/scroll.md` | 已迁移，旧 KB 已移除 |
| List | 列表容器组件（含 ListItem/ListItemGroup） | `docs/kb/components/container/list.md` | 已迁移，旧 KB 已移除 |
| Refresh | 下拉刷新容器组件 | `docs/kb/components/container/refresh.md` | 已迁移，旧 KB 已移除 |
| ScrollBar | 独立滚动条组件 | `docs/kb/components/container/scroll_bar.md` | 已迁移，旧 KB 已移除 |
| Slider | 滑动选择器组件 | `docs/kb/components/input-form/slider.md` | 新建（无旧 KB） |
| TextPicker | 文本选择器组件 | `docs/kb/components/selector/text_picker.md` | 已迁移，旧 KB 已移除 |
| DatePicker | 日期选择器组件 | `docs/kb/components/selector/date_picker.md` | 已迁移，旧 KB 已移除 |
| TimePicker | 时间选择器组件 | `docs/kb/components/selector/time_picker.md` | 已迁移，旧 KB 已移除 |
| CalendarPickerDialog | 日历选择弹窗组件 | `docs/kb/components/selector/calendar_picker_dialog.md` | 新建 |
| DatePickerDialog | 日期选择弹窗组件 | `docs/kb/components/selector/date_picker_dialog.md` | 新建 |
| TimePickerDialog | 时间选择弹窗组件 | `docs/kb/components/selector/time_picker_dialog.md` | 新建 |
| TextPickerDialog | 文本选择弹窗组件 | `docs/kb/components/selector/text_picker_dialog.md` | 新建 |
| UIPickerComponent | UI选择器容器组件 | `docs/kb/components/selector/ui_picker_component.md` | 已迁移，旧 KB 已移除 |
| AlphabetIndexer | 字母索引组件 | `docs/kb/components/data_display/alphabet_indexer.md` | 新建 |
| MediaQuery | 媒体查询能力 | `docs/kb/api/mediaquery.md` | 新建（Spec 待补） |
| Router | 路由管理 | `docs/kb/api/router.md` | 新建（不推荐，推荐 Navigation） |
| StateMgmtV1Core | V1 状态管理核心逻辑 | `docs/kb/frontend/state_management/v1_core.md` | 已注册 |
| StateMgmtV2Core | V2 状态管理核心逻辑 | `docs/kb/frontend/state_management/v2_core.md` | 已注册 |
| StateMgmtV1Decorators | V1 状态管理装饰器 | `docs/kb/frontend/state_management/v1_decorators.md` | 已注册 |
| StateMgmtV2Decorators | V2 状态管理装饰器 | `docs/kb/frontend/state_management/v2_decorators.md` | 已注册 |
| StateMgmt | 状态管理总览 | `docs/kb/frontend/state_management.md` | 已注册 |
| StateMgmtStorage | 状态管理存储体系 | `docs/kb/frontend/state_management/storage.md` | 已注册 |
| StateMgmtInfrastructure | 状态管理基础设施 | `docs/kb/frontend/state_management/infrastructure.md` | 已注册 |
| StateMgmtCppBindings | 状态管理 C++ 绑定 | `docs/kb/frontend/state_management/cpp_bindings.md` | 已注册 |
| StateMgmtCustomComponent | 状态管理自定义组件机制 | `docs/kb/frontend/state_management/custom_component.md` | 已注册 |
| StateMgmtInterop | 状态管理 Interop 桥接 | `docs/kb/frontend/state_management/interop_bridge.md` | 已注册 |
| StateMgmtStaticV1Core | 静态 V1 状态管理核心逻辑 | `docs/kb/frontend/state_management/static_v1_core.md` | 新建 |
| StateMgmtStaticV1Decorators | 静态 V1 装饰器与数据对象 | `docs/kb/frontend/state_management/static_v1_decorators.md` | 新建 |
| StateMgmtStaticV2Core | 静态 V2 状态管理核心逻辑 | `docs/kb/frontend/state_management/static_v2_core.md` | 新建 |
| StateMgmtStaticV2Decorators | 静态 V2 装饰器与数据对象 | `docs/kb/frontend/state_management/static_v2_decorators.md` | 新建 |
| StateMgmtStaticStorage | 静态存储体系 | `docs/kb/frontend/state_management/static_storage.md` | 新建 |
| StateMgmtStaticInterop | 静态 Interop 桥接 | `docs/kb/frontend/state_management/static_interop_bridge.md` | 新建 |
| StateMgmtStaticCustomComponent | 静态自定义组件状态相关 | `docs/kb/frontend/state_management/static_custom_component.md` | 新建 |
| WindowMechanism | 窗口机制 | `docs/kb/architecture/window-mechanism.md` | 新建 |
| PreviewPlatformAdaptation | 预览器平台适配 | `docs/kb/architecture/preview-platform-adaptation.md` | 新建 |
| CustomMeasureLayout | 自定义测量/布局 | `docs/kb/capabilities/custom-measure-layout.md` | 新建；关联 Spec `07-03-05` |
| DFXLogging | DFX 日志 | `docs/kb/architecture/dfx/logging.md` | 新建 |
| DFXMemoryManagement | DFX 内存管理 | `docs/kb/architecture/dfx/memory-management.md` | 新建 |
| DFXTrace | DFX Trace 打点 | `docs/kb/architecture/dfx/trace.md` | 新建 |
| DFXDumpMechanism | DFX Dump 机制 | `docs/kb/architecture/dfx/dump-mechanism.md` | 新建 |
| DFXLayoutBoundaryDisplay | DFX 布局边界显示 | `docs/kb/architecture/dfx/layout-boundary-display.md` | 新建 |
| UIContext | UI 上下文 | `docs/kb/capabilities/ui-context.md` | 新建 |
| ScrollCommonCapability | 滚动公共能力 | `docs/kb/capabilities/scroll-common-capability.md` | 已重建，旧 Scroll KB 已移除；补齐 05-03-01 Spec 路由 |
| Menu | 菜单组件 | `docs/kb/components/overlay/menu.md` | 已迁移，旧 KB 已移除；补齐 Spec 路由 |
| Dialog | 弹窗组件 | `docs/kb/components/overlay/dialog.md` | 新建；补齐 Spec 路由 |
| Toast | 提示组件 | `docs/kb/components/overlay/toast.md` | 新建；补齐 Spec 路由 |
| Select | 选择器组件 | `docs/kb/components/overlay/select.md` | 新建；补齐 Spec 路由 |
| bindPopup | 气泡弹窗属性 | `docs/kb/components/overlay/bind_popup.md` | 新建；补齐 Spec 路由 |
| PopupAdvanced | Popup 高级组件 | `docs/kb/components/overlay/popup_advanced.md` | 新建；补齐 Spec 路由 |
| Sheet | 半模态弹窗组件 | `docs/kb/components/overlay/sheet.md` | 已迁移，旧 KB 已移除 |
| bindTips | 提示气泡属性 | `docs/kb/components/overlay/bind_tips.md` | 新建 |
| Button | 按钮组件 | `docs/kb/components/basic/button.md` | 新建；补齐 Spec 路由 |
| Radio | 单选组件 | `docs/kb/components/selector/radio.md` | 新建；补齐 Spec 路由 |
| Checkbox | 多选组件 | `docs/kb/components/selector/checkbox.md` | 新建；补齐 Spec 路由 |
| ArcSlider | 圆弧滑动选择器组件 | `docs/kb/components/selector/arc_slider.md` | 新建；补齐 Spec 路由 |
| ArcButton | 圆弧按钮组件 | `docs/kb/components/selector/arc_button.md` | 新建；补齐 Spec 路由 |
| AnimationFramework | 动效框架 | `docs/kb/capabilities/animation_framework.md` | 新建 |
| PropertyAnimation | 属性动画 | `docs/kb/capabilities/property_animation.md` | 新建 |
| ExplicitAnimation | 显式动画 | `docs/kb/capabilities/explicit_animation.md` | 新建 |
| KeyframeAnimation | 关键帧动画 | `docs/kb/capabilities/keyframe_animation.md` | 新建 |
| TransitionAnimation | 转场动画 | `docs/kb/capabilities/transition_animation.md` | 新建 |
| SharedTransition | 共享元素动画 | `docs/kb/capabilities/shared_transition.md` | 新建 |
| GeometryTransition | 组件共享元素动画 | `docs/kb/capabilities/geometry_transition.md` | 新建 |
| MotionPath | 路径动画 | `docs/kb/capabilities/motion_path.md` | 新建 |
| PhysicsAnimation | 物理动画 | `docs/kb/capabilities/physics_animation.md` | 新建 |
| AnimationInterface | 动画接口 | `docs/kb/capabilities/animation_interface.md` | 新建 |
| DragFramework | 拖拽框架 | `docs/kb/architecture/drag-framework.md` | 新建（独立主题） |
| DragCapability | 通用拖拽能力 | `docs/kb/capabilities/drag-capability.md` | 新建（独立主题） |
| ResourceAccess | 资源访问 | `docs/kb/architecture/resource-access.md` | 新建 |
| ThemeLayeredAccess | 主题分层访问 | `docs/kb/architecture/theme-layered-access.md` | 新建 |
| ThemeFramework | Theme框架 | `docs/kb/architecture/theme-framework.md` | 新建 |
| ResourceDynamicSwitching | 资源动态切换 | `docs/kb/architecture/resource-dynamic-switching.md` | 新建 |
| SubwindowMechanism | 子窗机制 | `docs/kb/architecture/subwindow-mechanism.md` | 新建 |
| VisualEffectAttributes | 视效属性 | `docs/kb/capabilities/visual-effect-attributes.md` | 新建 |
| ModalAttributes | 模态属性 | `docs/kb/capabilities/modal-attributes.md` | 新建 |
| BasicUnits | 基础单位 | `docs/kb/capabilities/basic-units.md` | 新建 |
| ContentModifierForm | 表单类组件自定义内容 | `docs/kb/capabilities/content-modifier-form.md` | 新建 |
| ContentModifierDisplay | 信息展示类组件自定义内容 | `docs/kb/capabilities/content-modifier-display.md` | 新建 |
| UIAppearance | 色彩模式管理 | `docs/kb/capabilities/ui-appearance.md` | 新建 |
| NamedRouter | 命名路由 | `docs/kb/api/named-router.md` | 新建 |
| Rating | 评分组件 | `docs/kb/components/input-form/rating.md` | 新建 |
| AlertDialog | 警告弹窗 | `docs/kb/components/overlay/alert_dialog.md` | 新建 |
| ActionSheet | 列表选择弹窗 | `docs/kb/components/overlay/action_sheet.md` | 新建 |
| ContextMenu | 上下文菜单接口 | `docs/kb/components/overlay/context_menu.md` | 新建 |
| bindContentCover | 全模态弹窗属性 | `docs/kb/components/overlay/bind_content_cover.md` | 新建 |
| WithTheme | 主题作用域组件 | `docs/kb/components/container/with_theme.md` | 新建 |
| TextCommonAttributes | 文本通用属性 | `docs/kb/capabilities/text-common-attributes.md` | 新建 |
| FontRegistration | 字体注册 | `docs/kb/capabilities/font-registration.md` | 新建 |
| TextMeasurement | 文本测量 | `docs/kb/capabilities/text-measurement.md` | 新建 |
| TextSelection | 文本选择 | `docs/kb/capabilities/text-selection.md` | 新建 |
| TextInteraction | 文本交互 | `docs/kb/capabilities/text-interaction.md` | 新建 |
| AutoFill | 自动补全能力（AutoFill） | `docs/kb/capabilities/autofill.md` | 新建 |
| AbilityContext | Ability上下文 | `docs/kb/capabilities/ability-context.md` | 新建 |
| FrameCallback | Frame回调接口 | `docs/kb/capabilities/frame-callback.md` | 新建 |
| basic-attributes | 基础属性 | `docs/kb/capabilities/basic-attributes.md` | 新建 |
| style-attributes | 样式属性（stateStyles + attributeModifier） | `docs/kb/capabilities/style-attributes.md` | 新建 |
| multi-instance-management | 多实例管理 | `docs/kb/architecture/multi-instance-management.md` | 新建 |
| OverlayCapability | 浮层能力 | `docs/kb/capabilities/overlay-capability.md` | 新建 |
| InteractionAttributes | 交互属性 | `docs/kb/capabilities/interaction-attributes.md` | 新建 |
| ComponentScreenshot | 组件截图 | `docs/kb/capabilities/component-screenshot.md` | 新建 |
| FrameNode | FrameNode 节点 | `docs/kb/capabilities/frame_node.md` | 新建 |
| RenderNode | RenderNode 绘制节点 | `docs/kb/capabilities/render_node.md` | 新建 |
| BuilderNode | BuilderNode 构建节点 | `docs/kb/capabilities/builder_node.md` | 新建 |
| ComponentContent | ComponentContent 组件内容 | `docs/kb/capabilities/component_content.md` | 新建 |
| TypedFrameNode | TypedFrameNode 类型化节点 | `docs/kb/capabilities/typed_frame_node.md` | 新建 |
| ComponentModifier | 组件 Modifier 类体系 | `docs/kb/capabilities/component_modifier.md` | 新建 |
| DrawModifier | 自定义绘制回调 Modifier | `docs/kb/capabilities/draw_modifier.md` | 新建 |
| AttributeModifier | 动态属性 Modifier 通路 | `docs/kb/capabilities/attribute_modifier.md` | 新建 |
| CustomProperty | 自定义属性 | `docs/kb/capabilities/custom_property.md` | 新建 |
| InteractionNormalization | 交互归一化 | `docs/kb/capabilities/interaction-normalization.md` | 新建；覆盖 04-04-11 多源点击、滑动/平移、缩放/旋转归一化 |
| StylusCapability | 手写笔能力 | `docs/kb/capabilities/stylus-capability.md` | 新建；覆盖 04-04-08 的 4 个 Feat |
| ComponentRelatedEvents | 组件相关事件 | `docs/kb/capabilities/component-related-events.md` | 新建；覆盖 04-04-09 的 2 个 Feat |
| VisibleAreaMechanism | 可见区域机制 | `docs/kb/capabilities/visible-area-mechanism.md` | 新建；覆盖 04-04-10 的 2 个 Feat |
| FocusMechanism | 焦点机制 | `docs/kb/capabilities/focus-mechanism.md` | 新建；覆盖 04-09-01 的 6 个 Feat |
| ComponentUtils | ComponentUtils | `docs/kb/capabilities/component-utils.md` | 新建；覆盖 04-11-01 的 2 个 Feat |
| Accessibility | 无障碍能力 | `docs/kb/architecture/accessibility.md` | 已迁移，旧 KB 已移除 |
| PluginComponent | 插件嵌入组件 | `docs/kb/components/container/plugin_component.md` | 新建 |
| UIExtensionComponent | UIExtension嵌入组件 | `docs/kb/components/container/ui_extension_component.md` | 新建 |
| EmbeddedComponent | 嵌入式组件 | `docs/kb/components/container/embedded_component.md` | 新建 |
| IsolatedComponent | 隔离式组件 | `docs/kb/components/container/isolated_component.md` | 新建 |
| SecurityUIExtensionComponent | 安全UIExtension组件 | `docs/kb/components/container/security_ui_extension_component.md` | 新建 |
| DynamicComponent | 动态组件 | `docs/kb/components/container/dynamic_component.md` | 新建 |
| XComponent | XComponent组件 | `docs/kb/components/platform/x_component.md` | 新建（无旧 KB） |
| Inspector | 组件树 Inspector | `docs/kb/capabilities/inspector.md` | 新建（Spec 待补） |
| InspectorLayoutCallback | 布局回调(inspector) | `docs/kb/capabilities/inspector-layout-callback.md` | 新建（Spec 待补） |
| WindowToolbar | 窗口工具栏 | `docs/kb/capabilities/window-toolbar.md` | 新建（Spec 待补） |
| AtomicServiceAppBar | 元服务 AppBar | `docs/kb/capabilities/atomic-service-appbar.md` | 新建（Spec 待补） |
| RenderTreeSync | 渲染树同步 | `docs/kb/architecture/render-tree-sync.md` | 新建 |

| TouchEvents | 触摸事件 | `docs/kb/capabilities/touch-events.md` | 新建 |
| KeyEvents | 按键事件 | `docs/kb/capabilities/key-events.md` | 新建 |
| EventDispatchIntercept | 事件分发和拦截 | `docs/kb/capabilities/event-dispatch-intercept.md` | 新建 |
| ComponentShortcuts | 组件组合键 | `docs/kb/capabilities/component-shortcuts.md` | 新建（独立功能 ID） |
| MouseEvents | 鼠标事件（含鼠标指针） | `docs/kb/capabilities/mouse-events.md` | 新建 |
| GestureCapability | 手势能力 | `docs/kb/capabilities/gesture-capability.md` | 新建 |
| GestureModifier | 手势 Modifier | `docs/kb/capabilities/gesture-modifier.md` | 新建（独立功能 ID） |
| EventBaseFramework | 事件基础框架 | `docs/kb/architecture/event-base-framework.md` | 新建 |

### 问题型 KB

| ID | 主题 | 新版 KB | 状态 |
|----|------|---------|------|
| NestedScrollOffsetNoResponse | 嵌套滚动偏移量不响应 | `docs/kb/issues/interaction/nested-scroll-offset-no-response.md` | 新建 |
| ScrollerNaNOffsetValidation | Scroller 非法数值偏移校验 | `docs/kb/issues/compatibility/scroller-nan-offset-validation.md` | 新建 |
| CustomSpanControllerLifecycle | CustomSpan 控制器生命周期 | `docs/kb/issues/text/custom-span-controller-lifecycle.md` | 新建 |
| KeyboardAvoidTimingChange | 键盘避让执行顺序变化 | `docs/kb/issues/layout/keyboard-avoid-timing-change.md` | 新建 |
| ResourceAdapterInstanceIdMismatch | 资源适配器实例ID缓存不匹配 | `docs/kb/issues/rendering/resource-adapter-instance-id-mismatch.md` | 新建 |
| AboutToDisappearUnmountBlockedOnReuse | aboutToDisappear下树屏蔽与组件复用冲突 | `docs/kb/issues/lifecycle/about-to-disappear-unmount-blocked-on-reuse.md` | 新建 |
| MenuSwipeMisrecognizedAsClick | Menu滑动误判为点击关闭 | `docs/kb/issues/interaction/menu-swipe-misrecognized-as-click.md` | 新建 |
| UIContextInstanceIdLeak | UIContext 实例 ID 泄漏 | `docs/kb/issues/lifecycle/uicontext-instance-id-leak.md` | 新建 |
| RenderNodeMemoryLeak | RenderNode 内存泄漏 | `docs/kb/issues/performance/rendernode-memory-leak.md` | 新建 |
| IsPendingStateRenderTreeDiff | 同帧下树重新上树 isPendingState_ 状态错乱 | `docs/kb/issues/lifecycle/ispending-state-render-tree-diff.md` | 新建 |

## 检索

```bash
python3 docs/validate_context.py
python3 docs/kb_search.py Text
python3 docs/kb_search.py Text --field name
python3 -m json.tool docs/context_registry.json > /dev/null
```
