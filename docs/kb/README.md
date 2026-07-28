# ArkUI KB

> 更新时间：2026-07-28
> 主题数：98
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

| ID | 主题 | 新版 KB | 状态 |
|----|------|---------|------|
| LayoutFramework | 布局框架 | `docs/kb/architecture/layout-framework.md` | 已重建，旧 KB 已移除 |
| LayoutAttributes | 基础布局属性 | `docs/kb/capabilities/layout-attributes.md` | 新建 |
| SafeArea | 安全区域机制 | `docs/kb/capabilities/safe-area.md` | 已合并重建，两份旧 KB 已移除 |
| Blank | 空白填充组件 | `docs/kb/components/basic/blank.md` | 新建 |
| Divider | 分隔线组件 | `docs/kb/components/basic/divider.md` | 新建 |
| Column | 纵向布局组件 | `docs/kb/components/container/column.md` | 新建 |
| ColumnSplit | 纵向分割布局组件 | `docs/kb/components/container/column_split.md` | 新建（Spec 待补） |
| Flex | 弹性布局组件（含 Wrap） | `docs/kb/components/container/flex.md` | 已重建，旧 KB 已移除 |
| GridCol | 响应式栅格列组件 | `docs/kb/components/container/grid_col.md` | 新建 |
| GridRow | 响应式栅格行组件 | `docs/kb/components/container/grid_row.md` | 新建 |
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
| SideBarContainer | 侧边栏容器组件 | `docs/kb/components/container/side_bar_container.md` | 新建 |
| NavDestination | 导航目标页组件 | `docs/kb/components/container/navdestination.md` | 新建 |
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
| Router | 路由管理 | `docs/kb/api/router.md` | 新建（不推荐，推荐 Navigation） |
| StateMgmtV1Core | V1 状态管理核心逻辑 | `docs/kb/architecture/state_management/v1_core.md` | 已注册 |
| StateMgmtV2Core | V2 状态管理核心逻辑 | `docs/kb/architecture/state_management/v2_core.md` | 已注册 |
| StateMgmtV1Decorators | V1 状态管理装饰器 | `docs/kb/architecture/state_management/v1_decorators.md` | 已注册 |
| StateMgmtV2Decorators | V2 状态管理装饰器 | `docs/kb/architecture/state_management/v2_decorators.md` | 已注册 |
| WindowMechanism | 窗口机制 | `docs/kb/architecture/window-mechanism.md` | 新建 |
| DFXLogging | DFX 日志 | `docs/kb/architecture/dfx/logging.md` | 新建 |
| DFXMemoryManagement | DFX 内存管理 | `docs/kb/architecture/dfx/memory-management.md` | 新建 |
| DFXTrace | DFX Trace 打点 | `docs/kb/architecture/dfx/trace.md` | 新建 |
| DFXDumpMechanism | DFX Dump 机制 | `docs/kb/architecture/dfx/dump-mechanism.md` | 新建 |
| DFXLayoutBoundaryDisplay | DFX 布局边界显示 | `docs/kb/architecture/dfx/layout-boundary-display.md` | 新建 |
| UIContext | UI 上下文 | `docs/kb/capabilities/ui-context.md` | 新建 |
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
| ResourceAccess | 资源访问 | `kb/architecture/resource-access.md` | 新建 |
| ThemeLayeredAccess | 主题分层访问 | `kb/architecture/theme-layered-access.md` | 新建 |
| ThemeFramework | Theme框架 | `kb/architecture/theme-framework.md` | 新建 |
| ResourceDynamicSwitching | 资源动态切换 | `kb/architecture/resource-dynamic-switching.md` | 新建 |
| SubwindowMechanism | 子窗机制 | `kb/architecture/subwindow-mechanism.md` | 新建 |
| VisualEffectAttributes | 视效属性 | `kb/capabilities/visual-effect-attributes.md` | 新建 |
| ModalAttributes | 模态属性 | `kb/capabilities/modal-attributes.md` | 新建 |
| BasicUnits | 基础单位 | `kb/capabilities/basic-units.md` | 新建 |
| ContentModifierForm | 表单类组件自定义内容 | `kb/capabilities/content-modifier-form.md` | 新建 |
| ContentModifierDisplay | 信息展示类组件自定义内容 | `kb/capabilities/content-modifier-display.md` | 新建 |
| UIAppearance | 色彩模式管理 | `kb/capabilities/ui-appearance.md` | 新建 |
| NamedRouter | 命名路由 | `kb/api/named-router.md` | 新建 |
| Rating | 评分组件 | `kb/components/input-form/rating.md` | 新建 |
| AlertDialog | 警告弹窗 | `kb/components/overlay/alert_dialog.md` | 新建 |
| ActionSheet | 列表选择弹窗 | `kb/components/overlay/action_sheet.md` | 新建 |
| ContextMenu | 上下文菜单接口 | `kb/components/overlay/context_menu.md` | 新建 |
| bindContentCover | 全模态弹窗属性 | `kb/components/overlay/bind_content_cover.md` | 新建 |
| WithTheme | 主题作用域组件 | `kb/components/container/with_theme.md` | 新建 |
| NavDestination | 导航目标页组件 | `kb/components/container/navdestination.md` | 新建 |

## 检索

```bash
python3 docs/validate_context.py
python3 docs/kb_search.py Text
python3 docs/kb_search.py Text --field name
python3 -m json.tool docs/context_registry.json > /dev/null
```
