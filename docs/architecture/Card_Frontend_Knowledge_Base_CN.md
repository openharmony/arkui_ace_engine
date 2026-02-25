# Card Frontend 深入知识库

> **文档定位**：本文档是对 `card_frontend/CLAUDE.md` 的深入补充，专注于设计决策、实现原理、问题排查等高级内容
> **快速参考**：请参考 [CardFrontend/CLAUDE.md](../../frameworks/bridge/card_frontend/CLAUDE.md)
> **版本**：v1.0 | **更新**：2026-02-03

---

## 目录

1. [设计决策分析](#1-设计决策分析)
2. [实现原理深挖](#2-实现原理深挖)
3. [问题排查手册](#3-问题排查手册)
4. [跨组件交互](#4-跨组件交互)
5. [性能优化](#5-性能优化)

---

## 1. 设计决策分析

### 1.1 为什么需要独立的 Card Frontend？

**背景**：OpenHarmony 的卡片（Widget/Form）是一种轻量级UI组件，需要在多种场景下渲染（桌面、锁屏、搜索等）

**决策**：创建独立的 `CardFrontend` 子系统

**源码位置**：`card_frontend.h:32-230`

**设计理由**：

| 优点 | 说明 |
|------|------|
| **轻量化** | 卡片不需要完整应用的所有能力（路由、页面栈等） |
| **独立生命周期** | 卡片可以独立于主应用加载和销毁 |
| **数据隔离** | 卡片数据与主应用数据分离，安全性更高 |
| **多种解析模式** | 支持 JSON（JS风格）和 ArkTS 字节码两种格式 |
| **资源优化** | 卡片有独立的资源管理和加载机制 |

**与普通 Frontend 的区别**：

```
┌─────────────────────────────────────────────────────────┐
│  普通 Frontend (DeclarativeFrontend/JSFrontend)          │
│  - 完整应用生命周期                                       │
│  - 页面路由管理                                          │
│  - 多页面栈                                              │
│  - 完整的状态管理                                        │
└─────────────────────────────────────────────────────────┘
                            vs
┌─────────────────────────────────────────────────────────┐
│  Card Frontend (CardFrontend/FormFrontendDeclarative)    │
│  - 单页面渲染                                            │
│  - 简化的生命周期                                        │
│  - 独立的数据更新机制                                    │
│  - 特殊的事件处理（跨进程通信）                          │
└─────────────────────────────────────────────────────────┘
```

---

### 1.2 为什么同时支持 JSON 和 ArkTS 字节码？

**背景**：OpenHarmony 卡片发展经历了从 JSON 描述到 ArkTS 编写的演进

**决策**：同时支持 `JsCardParser`（JSON）和 `CardFrontendDeclarative`（ArkTS）

**源码位置**：
- JSON 解析：`js_card_parser.cpp:1984-2005`
- ArkTS 加载：`card_frontend_declarative.cpp:81-108`

**设计理由**：

| 特性 | JSON 卡片 | ArkTS 卡片 |
|------|-----------|------------|
| **文件格式** | `.json` | `.abc` (字节码) |
| **性能** | 解析较慢 | 预编译，加载快 |
| **表达能力** | 有限 | 完整 ArkTS 能力 |
| **维护性** | 简单 | 需编译 |
| **兼容性** | 旧版卡片 | 新版卡片 |

**统一接口设计**：

```cpp
// 两种卡片都通过相同的基类接口加载
UIContentErrorCode RunPage(const std::string& url, const std::string& params) override;
```

---

### 1.3 为什么需要 Delegate 模式？

**背景**：卡片渲染需要与 PipelineContext、JsEngine、PageRouter 等多个组件交互

**决策**：使用 `CardFrontendDelegate` 和 `CardFrontendDelegateDeclarative` 作为委托

**源码位置**：`card_frontend_delegate.h:26-47`

**设计理由**：

```
┌─────────────────────────────────────────────────────────┐
│  Frontend（业务层）                                      │
│  - 负责 API 暴露                                         │
│  - 处理生命周期回调                                      │
│  - 任务调度（线程切换）                                  │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  Delegate（执行层）                                      │
│  - 管理 Page/JsAcePage                                  │
│  - 触发事件处理                                          │
│  - 更新页面数据                                          │
│  - 管理无障碍                                            │
└─────────────────────────────────────────────────────────┘
```

**职责分离**：

| 职责 | Frontend | Delegate |
|------|----------|----------|
| 任务调度 | ✅ | ❌ |
| 生命周期管理 | ✅ | ❌ |
| 页面创建 | ❌ | ✅ |
| 事件触发 | ❌ | ✅ |
| 数据更新 | 部分 | ✅ |

---

### 1.4 为什么 eTS Card 使用 UI 线程而非 JS 线程？

**背景**：普通应用的 JS 操作在 JS 线程执行

**决策**：eTS Card（声明式卡片）将操作发布到 UI 线程

**源码位置**：`card_frontend_declarative.cpp:48`

```cpp
taskExecutor_->PostTask(
    [...] { /* card loading logic */ },
    TaskExecutor::TaskType::UI, "ArkUICardFrontendRunCard");
```

**设计理由**：

| 因素 | 说明 |
|------|------|
| **共享 JS 引擎** | 卡片与主应用共享 JS 引擎，避免竞争 |
| **减少线程切换** | UI 操作直接在 UI 线程，性能更好 |
| **简化同步** | 不需要跨线程同步状态 |
| **架构一致性** | 与 NG 组件架构一致 |

**与普通应用的对比**：

```cpp
// 普通应用：在 JS 线程执行
taskExecutor_->PostTask(
    [...] { /* logic */ },
    TaskExecutor::TaskType::JS, "TaskName");

// eTS Card：在 UI 线程执行
taskExecutor_->PostTask(
    [...] { /* logic */ },
    TaskExecutor::TaskType::UI, "ArkUICardFrontendRunCard");
```

---

### 1.5 为什么需要 FormFrontend 与 CardFrontend 的区分？

**背景**：卡片在不同场景有不同的渲染需求

**决策**：`CardFrontend` 用于服务卡片，`FormFrontendDeclarative` 用于动态组件

**源码位置**：`form_frontend_declarative.h:35-170`

**区别对比**：

| 特性 | CardFrontend | FormFrontendDeclarative |
|------|--------------|-------------------------|
| **继承** | `Frontend` | `DeclarativeFrontend` |
| **文件类型** | `.json` 或 `.abc` | `.abc` |
| **使用场景** | 桌面卡片 | 动态组件 |
| **入口** | `RunPage()` | `RunDynamicPage()` |
| **权限** | 服务卡片权限 | 动态组件权限 |
| **独立性** | 独立进程 | 可嵌入主应用 |

**UIContentType 判断**：

```cpp
// Source: form_frontend_declarative.cpp:58-63
auto uiContentType = container->GetUIContentType();
if (uiContentType == UIContentType::DYNAMIC_COMPONENT) {
    return InnerRunDynamicPage(url, params, entryPoint);
}
return InnerRunCardPage(url, params, entryPoint);
```

---

## 2. 实现原理深挖

### 2.1 JSON 卡片解析流程

**JsCardParser 初始化**：

```
┌─────────────────────────────────────────────────────────┐
│ 1. 解析 JSON 文件                                        │
│                                                          │
│    auto rootBody = ParseFileData(pageContent);          │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│ 2. 提取 JSON 结构                                        │
│                                                          │
│    rootJson_ = rootBody_->GetValue("template");         │
│    styleJson_ = rootBody_->GetValue("styles");          │
│    eventJson_ = rootBody_->GetValue("actions");         │
│    dataJson_ = rootBody_->GetValue("data");             │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│ 3. 版本适配处理                                          │
│                                                          │
│    ParseVersionAndUpdateData();                         │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│ 4. 加载资源                                              │
│                                                          │
│    LoadImageInfo();                                     │
│    LoadMediaQueryStyle();                               │
└─────────────────────────────────────────────────────────┘
```

**源码位置**：`js_card_parser.cpp:1984-2005`

---

### 2.2 DOM 节点创建流程

**CreateDomNode 实现**：

**源码位置**：`js_card_parser.cpp:1649-1741`

```cpp
void JsCardParser::CreateDomNode(const RefPtr<JsAcePage>& page,
    const std::unique_ptr<JsonValue>& rootJson, int32_t parentId,
    const std::unique_ptr<JsonValue>& dataJson,
    const std::unique_ptr<JsonValue>& actionJson,
    const std::unique_ptr<JsonValue>& styleJson,
    const std::unique_ptr<JsonValue>& propsJson, bool isNewNode)
{
    // 1. 分配节点 ID
    int32_t nodeId = parentId < 0 ? DOM_ROOT_NODE_ID_BASE : nodeId_++;

    // 2. 处理自定义组件
    if (rootBody_->Contains(type)) {
        auto customJson = rootBody_->GetValue(type);
        // 更新 props，递归创建
        CreateDomNode(page, customJsonTemplate, parentId, ...);
        return;
    }

    // 3. 创建命令
    auto command = Referenced::MakeRefPtr<JsCommandAddDomElement>(
        type, nodeId, parentId);

    // 4. 解析属性、样式、事件
    ParseAttributes(rootJson, nodeId, attrs, command, dataJson, propsJson);
    ParseStyles(rootJson, nodeId, styles, styleJson);
    ParseEvents(rootJson, actionJson, events, page, nodeId);

    // 5. 递归创建子节点
    auto childList = rootJson->GetValue("children");
    if (childList && childList->IsValid()) {
        auto child = childList->GetChild();
        while (child && child->IsValid()) {
            CreateDomNode(page, child, nodeId, ...);
            child = child->GetNext();
        }
    }
}
```

---

### 2.3 变量解析机制

**变量语法支持**：

| 语法 | 说明 | 示例 |
|------|------|------|
| `{{value}}` | 简单变量 | `{{title}}` |
| `$f(...)` | 多变量拼接 | `$f('Hello {{name}}, age {{age}}')` |
| `$r('...')` | 资源引用 | `$r('app.media.icon')` |
| `$t('...')` | 国际化 | `$t('strings.title')` |
| `$tc(...)` | 复数形式 | `$tc('strings.plurals', 2)` |
| `{{a ? b : c}}` | 三元表达式 | `{{flag ? 'yes' : 'no'}}` |
| `{{a && b}}` | 逻辑与 | `{{flag1 && flag2}}` |
| `{{a \|\| b}}` | 逻辑或 | `{{flag1 \|\| flag2}}` |
| `{{!a}}` | 逻辑非 | `{{!flag}}` |

**变量解析流程**：

**源码位置**：`js_card_parser.cpp:1354-1370`

```cpp
void JsCardParser::ParseVariable(std::string& value,
    const std::unique_ptr<JsonValue>& dataJson,
    const std::unique_ptr<JsonValue>& propsJson)
{
    // 1. 提取变量名：{{value}} → value
    auto variable = value.substr(2, value.size() - 4);

    // 2. 尝试多种解析方式
    if (GetAndParseProps(variable, propsJson) ||
        ParseComplexExpression(variable, dataJson) ||
        GetVariable(variable, dataJson) ||
        ParseSpecialVariable(variable) ||
        ParseTernaryExpression(variable, propsJson) ||
        ParseLogicalExpression(variable, propsJson)) {
        value = variable;  // 解析成功，替换原值
    }
}
```

**复杂表达式解析**（支持数组索引和点操作符）：

**源码位置**：`js_card_parser.cpp:1184-1259`

```cpp
bool JsCardParser::ParseArrayExpression(
    const std::string& expression,
    std::stack<std::string>& keyStack,
    const std::unique_ptr<JsonValue>& json)
{
    // 解析: list[0].name
    //         ^^^  ^ ^^^^
    //         点操作 索引 点操作
    std::string tmpKey;
    for (char i : expression) {
        switch (i) {
            case '[':
                // 处理点操作符
                ParsePointOperator(tmpKey, keyStack, dataJson);
                break;
            case ']':
                // 处理数组索引
                if (StringUtils::IsNumber(tmpKey)) {
                    GetIndexValue(tmpKey, keyStack);
                }
                break;
        }
    }
}
```

---

### 2.4 Repeat（循环）节点处理

**Repeat 节点创建**：

**源码位置**：`js_card_parser.cpp:1743-1776`

```cpp
void JsCardParser::CreateRepeatDomNode(
    const RefPtr<JsAcePage>& page,
    const std::unique_ptr<JsonValue>& rootJson,
    int32_t parentId)
{
    isRepeat_ = true;

    // 1. 获取循环数据
    auto repeatValue = rootJson->GetValue("repeat");
    if (repeatValue->IsString()) {
        // 简单形式: {{list}}
        GetRepeatData(repeatValue, key);
        ProcessRepeatNode(page, rootJson, key, parentId, false, repeatValue);
    } else {
        // 对象形式: {"exp": {{list}}, "key":"index", "value": "item"}
        auto expValue = repeatValue->GetValue("exp");
        GetRepeatData(expValue, key);
        ParseRepeatIndexItem(repeatValue);  // 解析 key/value 别名
        ProcessRepeatNode(page, rootJson, key, parentId, true, expValue);
    }

    isRepeat_ = false;
}
```

**Repeat 数据更新**（增量更新）：

**源码位置**：`js_card_parser.cpp:1866-1923`

```cpp
void JsCardParser::ProcessRepeatNode(...)
{
    if (parsingStatus_ == ParsingStatus::CREATE) {
        // 创建阶段：为每个数组项创建节点
        for (auto i = 0; i < repeatValue->GetArraySize(); i++) {
            SetRepeatItemValue(i, repeatValue, hasKeyValue);
            CreateDomNode(page, rootJson, parentId);
        }
        // 记录节点映射
        listIdMap_[numberOfForNode_] = {idArray_, idArray_.size()};
    } else if (parsingStatus_ == ParsingStatus::UPDATE) {
        // 更新阶段：增量更新
        auto lastSize = array.size() / factor;
        auto updateSize = std::min(lastSize, repeatValue->GetArraySize());

        // 1. 更新现有节点
        for (auto i = 0; i < updateSize; ++i) {
            SetRepeatItemValue(i, repeatValue, hasKeyValue);
            UpdateDomNode(page, rootJson, parentId, array);
        }

        // 2. 新增节点
        if (repeatValue->GetArraySize() > lastSize) {
            for (auto i = lastSize; i < repeatValue->GetArraySize(); ++i) {
                SetRepeatItemValue(i, repeatValue, hasKeyValue);
                CreateDomNode(page, rootJson, parentId, true);
            }
        }

        // 3. 删除多余节点
        if (lastSize > repeatValue->GetArraySize()) {
            for (int32_t i = array.size() - factor; i >= repeatValue->GetArraySize() * factor; i -= factor) {
                page->PushCommand(Referenced::MakeRefPtr<JsCommandRemoveDomElement>(nodeId));
            }
        }
    }
}
```

**内置循环变量**：

| 变量 | 说明 |
|------|------|
| `$idx` | 当前索引（从 0 开始） |
| `$item` | 当前项数据 |

---

### 2.5 事件处理机制

**JSON 卡片事件流程**：

```
用户点击
    ↓
CardEventHandler::HandleAsyncEvent(eventMarker, param)
    ↓
CardFrontendDelegate::FireCardEvent(eventMarker, params)
    ↓
获取节点事件动作
    ↓
替换 $event.* 为实际参数
    ↓
PipelineContext::OnActionEvent(action)
    ↓
发送到无障碍服务（如果启用）
```

**源码位置**：`card_frontend_delegate.cpp:28-69`

```cpp
void CardFrontendDelegate::FireCardEvent(
    const EventMarker& eventMarker, const std::string& params)
{
    auto nodeId = StringToInt(eventMarker.GetData().eventId);
    auto action = page_->GetNodeEventAction(nodeId, eventMarker.GetData().eventType);

    auto routerAction = JsonUtil::ParseJsonString(action);
    auto paramsJson = JsonUtil::ParseJsonString(params);

    // 替换 $event.* 参数
    auto paramsInfo = routerAction->GetValue("params");
    auto child = paramsInfo->GetChild();
    while (child->IsValid()) {
        auto value = child->GetString();
        if (StartWith(value, "$event.")) {
            // $event.name → paramsJson->GetValue("name")
            paramsInfo->Replace(key.c_str(), paramsJson->GetValue(value.substr(7)));
        }
    }

    context->OnActionEvent(routerAction->ToString());
    context->SendEventToAccessibility(accessibilityEvent);
}
```

**声明式卡片事件流程**：

```
用户交互
    ↓
CardEventHandlerDeclarative::HandleAsyncEvent(eventMarker)
    ↓
CardFrontendDelegateDeclarative::FireCardAction(action)
    ↓
PostTask 到 UI 线程
    ↓
PipelineContext::OnActionEvent(action)
```

---

### 2.6 数据更新机制

**JSON 卡片数据更新**：

**源码位置**：`card_frontend.cpp:275-283`

```cpp
void CardFrontend::UpdatePageData(const std::string& dataList)
{
    CHECK_RUN_ON(JS);
    if (!delegate_ || !parseJsCard_) {
        return;
    }
    parseJsCard_->UpdatePageData(dataList, delegate_->GetPage());
}
```

**JsCardParser 数据更新**：

**源码位置**：`js_card_parser.cpp:1150-1176`

```cpp
void JsCardParser::UpdatePageData(const std::string& dataList,
    const RefPtr<JsAcePage>& page)
{
    // 1. 解析新数据
    const auto& rootData = JsonUtil::ParseJsonString(dataList);

    // 2. 更新 dataJson 和 repeatJson
    auto data = rootData->GetChild();
    while (data && data->IsValid()) {
        auto key = data->GetKey();
        dataJson_->Replace(key.c_str(), data);
        repeatJson_->Replace(key.c_str(), data);
        data = data->GetNext();
    }

    // 3. 设置更新状态并触发 DOM 更新
    SetUpdateStatus(page);
}
```

**声明式卡片数据更新**：

**源码位置**：`card_frontend_delegate_declarative.cpp:57-79`

```cpp
void CardFrontendDelegateDeclarative::UpdatePageData(const std::string& dataList)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (updateCardData_) {
        // 直接调用回调
        updateCardData_(dataList);
    } else {
        // 暂存数据，等待回调设置
        cardData_ = dataList;
    }
}

void CardFrontendDelegateDeclarative::SetUpdateCardDataCallback(
    UpdateCardDataCallback&& callback)
{
    std::lock_guard<std::mutex> lock(mutex_);
    updateCardData_ = std::move(callback);
}
```

---

### 2.7 资源管理

**图片资源加载**：

**源码位置**：`js_card_parser.cpp:789-822`

```cpp
void JsCardParser::GetResImageUrl(std::string& value)
{
    // $r('app.media.icon') → icon

    // 1. 提取资源路径
    auto splitStr = value.substr(4, value.size() - 6);

    // 2. 查找缓存
    auto iter = imageUrlMap_.find(splitStr + theme);
    if (iter != imageUrlMap_.end()) {
        value = iter->second;
        return;
    }

    // 3. 构建资源文件路径
    auto jsonFile = "resources/res-" + theme + "-" + GetDeviceDpi(density_) + ".json";

    // 4. 加载资源
    LoadResImageUrl(jsonFile, splitStr, imagePath);

    // 5. 缓存结果
    imageUrlMap_[splitStr + theme] = imagePath;
}
```

**资源文件查找顺序**：

```
1. resources/res-{dpi}.json
2. resources/res-dark-{dpi}.json (暗色模式)
3. resources/res-dark-defaults.json
4. resources/res-defaults.json
```

**国际化资源加载**：

**源码位置**：`js_card_parser.cpp:824-860`

```cpp
bool JsCardParser::GetI18nData(std::string& value)
{
    // $t('strings.title') → title

    // 1. 获取所有 i18n 文件
    assetManager->GetAssetList(I18N_FOLDER, files);

    // 2. 获取当前语言
    auto localeTag = AceApplicationInfo::GetInstance().GetLocaleTag();

    // 3. 获取回退语言列表
    auto priorityFileName = AceResConfig::GetLocaleFallback(localeTag, fileNameList);

    // 4. 按优先级查找
    for (const auto& fileName : priorityFileName) {
        auto filePath = "i18n/" + fileName + ".json";
        if (GetAssetContentImpl(assetManager, filePath, content)) {
            auto result = GetJsonValue(keys, fileData);
            if (result && result->IsValid()) {
                value = result->GetString();
                return true;
            }
        }
    }
}
```

**MediaQuery 支持**：

**源码位置**：`js_card_parser.cpp:1087-1123`

```cpp
void JsCardParser::LoadMediaQueryStyle()
{
    auto media = styleJson_->GetValue("@MEDIA");
    auto mediaChild = media->GetChild();
    while (mediaChild && mediaChild->IsValid()) {
        auto condition = mediaChild->GetString("condition", "");

        // 按条件存储样式
        mediaQueryStyles_[condition] = std::move(mediaQueryStyle);
        mediaChild = mediaChild->GetNext();
    }
}

void JsCardParser::SelectMediaQueryStyle(
    const std::string& styleClass,
    std::vector<std::pair<std::string, std::string>>& styles)
{
    const auto& mediaFeature = mediaQueryer_.GetMediaFeature();
    for (const auto& iter : mediaQueryStyles_) {
        if (mediaQueryer_.MatchCondition(iter.first, mediaFeature)) {
            SelectStyle(styleClass, iter.second, styles);
        }
    }
}
```

---

### 2.8 自定义组件支持

**自定义组件解析**：

**源码位置**：`js_card_parser.cpp:1681-1706`

```cpp
// 检查是否为自定义组件
if (rootBody_->Contains(type)) {
    auto customJson = rootBody_->GetValue(type);
    auto customJsonTemplate = customJson->GetValue("template");
    auto customJsonData = customJson->GetValue("data");
    auto customJsonProps = customJson->GetValue("props");
    auto customJsonStyle = customJson->GetValue("styles");

    // 更新自定义组件的 props
    auto attrList = rootJson->GetValue("attr");
    auto attr = attrList->GetChild();
    while (attr && attr->IsValid()) {
        auto key = attr->GetKey();
        auto value = attr->GetString();
        UpdateProps(key, value, customJsonProps);
        attr = attr->GetNext();
    }

    // 递归解析自定义组件
    ParseStyles(rootJson, nodeId, customStyles_, styleJson);
    CreateDomNode(page, customJsonTemplate, parentId,
        customJsonData, customJsonActions, customJsonStyle, customJsonProps);
    return;
}
```

---

### 2.9 Block 节点处理

**Block 节点**：条件渲染容器，根据 `shown` 属性控制子节点显示

**源码位置**：`js_card_parser.cpp:2012-2033`

```cpp
void JsCardParser::CreateBlockNode(
    const RefPtr<JsAcePage>& page,
    const std::unique_ptr<JsonValue>& rootJson,
    int32_t parentId)
{
    auto blockChild = rootJson->GetValue("children");

    // 获取 shown 属性
    bool shouldShow = true;
    bool hasShownAttr = false;
    GetBoolValue(rootJson, "shown", shouldShow, hasShownAttr);

    const char* value = shouldShow ? "true" : "false";

    if (blockChild && blockChild->IsValid()) {
        auto child = blockChild->GetChild();
        while (child && child->IsValid()) {
            // 设置 blockValue，子节点可以通过 {{blockValue}} 获取
            if (child->Contains(BLOCK_VALUE)) {
                child->Replace(BLOCK_VALUE, value);
            } else {
                child->Put(BLOCK_VALUE, value);
            }

            // 递归创建子节点
            parsingStatus_ == ParsingStatus::UPDATE
                ? UpdateDomNode(page, child, parentId)
                : CreateDomNode(page, child, parentId);
            child = child->GetNext();
        }
    }
}
```

---

## 3. 问题排查手册

### 3.1 卡片不显示

**症状**：调用 `RunPage` 后卡片不显示

**诊断流程**：

```
开始
  ↓
卡片文件路径是否正确？
  ├─ 否 → 检查 GetFormSrcPath() 返回值
  │        检查文件扩展名（.json/.abc）
  │
  ├─ 是 → 资源是否加载成功？
  │        ├─ 否 → 检查 AssetManager
  │        │        检查 HAP 包路径
  │        │
  │        └─ 是 → DOM 节点是否创建？
  │                 ├─ 否 → 检查 JSON 格式
  │                 │        检查 JsCardParser::Initialize()
  │                 │
  │                 └─ 是 → Pipeline 是否推送页面？
  │                          检查 OnPageLoaded 是否执行
  │                          检查 CanPushPage()
```

**常见原因与解决方案**：

| 原因 | 现象 | 解决方案 |
|------|------|----------|
| 文件路径错误 | 日志显示 "path url is empty" | 检查 `GetFormSrcPath()` 逻辑 |
| JSON 格式错误 | 解析失败 | 验证 JSON 格式，检查 template/actions/styles/data 结构 |
| 资源未找到 | 图片/文本不显示 | 检查 resources 目录结构 |
| Pipeline 未推送 | OnPageLoaded 执行但无显示 | 检查 `CanPushPage()` 返回值 |

---

### 3.2 数据更新不生效

**症状**：调用 `UpdateData` 后卡片内容不变

**可能原因**：

| 原因 | 说明 | 解决方案 |
|------|------|----------|
| 未设置回调 | 声明式卡片需要设置 `UpdateCardDataCallback` | 调用 `SetUpdateCardDataCallback()` |
| 数据格式错误 | dataList 不是有效的 JSON | 验证数据格式 |
| 变量名不匹配 | JSON 中的变量名与数据键名不一致 | 检查 `{{variable}}` 与数据键名 |
| 线程问题 | 在错误的线程调用更新 | 确保在 JS/UI 线程执行 |

**调试代码**：

```cpp
// 检查数据更新回调
delegate_->SetUpdateCardDataCallback([](const std::string& data) {
    TAG_LOGI(AceLogTag::ACE_FORM, "Update data: %{public}s", data.c_str());
    // 实际更新逻辑
});
```

---

### 3.3 事件不响应

**症状**：点击卡片按钮无响应

**诊断流程**：

```
开始
  ↓
事件是否注册？
  ├─ 否 → 检查 ParseEvents 是否执行
  │        检查 eventJson 结构
  │
  ├─ 是 → nodeId 是否正确？
  │        ├─ 否 → 检查节点 ID 生成逻辑
  │        │        检查 IsRepeat 状态
  │        │
  │        └─ 是 → action 是否有效？
  │                 检查 eventJson 中 action 定义
  │                 检查方法名是否匹配
```

**常见问题**：

| 问题 | 原因 | 解决方案 |
|------|------|----------|
| 事件未注册 | eventJson 中未定义 | 在 JSON 的 actions 中添加事件定义 |
| nodeId 不匹配 | Repeat 节点的 nodeId 变化 | 使用 `listIdMap_` 跟踪节点 ID |
| 参数未传递 | `$event.*` 未正确替换 | 检查 FireCardEvent 中的参数替换逻辑 |

---

### 3.4 样式不生效

**症状**：设置的样式未应用到组件

**可能原因**：

| 原因 | 检查方法 | 解决方案 |
|------|----------|----------|
| styleJson 未加载 | 检查 `styleJson_->IsValid()` | 确保 JSON 包含 styles 节点 |
| 类名不匹配 | 检查 classList 与 styleJson 中的类名 | 确保类名一致（包括 `.` 前缀） |
| 优先级问题 | 检查样式应用顺序 | 内联样式 > id 样式 > class 样式 |
| MediaQuery 不匹配 | 检查 `mediaQueryer_.MatchCondition()` | 验证媒体查询条件 |

**样式应用顺序**：

```
1. classList 样式
2. id 样式
3. MediaQuery 样式
4. 内联样式（inline style）
```

---

### 3.5 性能问题：大量节点导致卡顿

**场景**：卡片包含大量节点（如长列表）

**优化策略**：

1. **使用 Repeat 而非手动创建**：

```json
{
  "type": "list",
  "repeat": "{{items}}",
  "children": [...]
}
```

2. **条件渲染**：

```json
{
  "type": "block",
  "attr": { "shown": "{{isVisible}}" },
  "children": [...]
}
```

3. **减少 DOM 深度**：扁平化节点结构

4. **延迟加载**：按需加载非关键内容

---

### 3.6 内存泄漏排查

**检查点**：

| 组件 | 检查方法 |
|------|----------|
| JsCardParser | 检查 `imageUrlMap_`、`mediaQueryStyles_` 清理 |
| CardFrontendDelegate | 检查 `page_` 引用释放 |
| CardEventHandler | 检查事件回调解绑 |

**Destroy 流程**：

```cpp
// Source: card_frontend.cpp:40-47
void CardFrontend::Destroy()
{
    CHECK_RUN_ON(JS);
    parseJsCard_.Reset();        // 释放解析器
    delegate_.Reset();           // 释放委托
    eventHandler_.Reset();       // 释放事件处理器
}
```

---

## 4. 跨组件交互

### 4.1 CardFrontend 与 PipelineContext 的关系

**依赖关系**：`CardFrontend` 持有 `PipelineContext` 的弱引用

**源码位置**：`card_frontend.h:211`

```cpp
Framework::PipelineContextHolder holder_;  // Pipeline 上下文持有者
```

**交互方式**：

| 操作 | 方向 | 方法 |
|------|------|------|
| 推送页面 | Frontend → Pipeline | `PipelineContext::PushPage()` |
| 触发动作 | Frontend → Pipeline | `PipelineContext::OnActionEvent()` |
| 调度更新 | Frontend → Pipeline | `PipelineContext::ScheduleUpdate()` |
| 系统事件 | Pipeline → Frontend | 通过 EventHandler 回调 |

---

### 4.2 CardFrontend 与 JsEngine 的关系

**共享引擎**：声明式卡片与主应用共享 JS 引擎

**源码位置**：`card_frontend_declarative.cpp:80-103`

```cpp
void CardFrontendDeclarative::SetLoadCardCallBack(...)
{
    const auto& loadCallback = [...](const std::string& url, ...) -> bool {
        // 使用主应用的 JS 引擎
        auto jsEngine = outSidefrontend->GetJsEngine();
        return jsEngine->LoadCard(url, cardId, entryPoint);
    };
    delegate_->SetLoadCardCallBack(loadCallback);
}
```

**好处**：
- 减少内存占用
- 共享运行时状态
- 统一的垃圾回收

---

### 4.3 CardFrontend 与 Container 的关系

**Container 注册**：卡片需要在 Container 中注册

**源码位置**：`card_frontend_declarative.cpp:100-105`

```cpp
auto container = Container::Current();
container->SetCardFrontend(AceType::WeakClaim(this), cardId_);
```

**卡片查找**：

```cpp
// 其他组件可以通过 Container 查找卡片
auto container = Container::Current();
auto cardFrontend = container->GetCardFrontend(cardId_);
```

---

### 4.4 CardFrontend 与 AccessibilityManager 的关系

**无障碍支持**：卡片支持无障碍功能

**源码位置**：`card_frontend_delegate.cpp:64-68`

```cpp
// 发送事件到无障碍服务
AccessibilityEvent accessibilityEvent;
accessibilityEvent.nodeId = nodeId;
accessibilityEvent.eventType = eventMarker.GetData().eventType;
context->SendEventToAccessibility(accessibilityEvent);
```

---

### 4.5 不同 Frontend 类型的对比

| 类型 | 基类 | 用途 | 文件类型 |
|------|------|------|----------|
| `CardFrontend` | `Frontend` | JSON 卡片 | .json |
| `CardFrontendDeclarative` | `CardFrontend` | 声明式卡片 | .abc |
| `FormFrontendDeclarative` | `DeclarativeFrontend` | 动态组件 | .abc |
| `DeclarativeFrontend` | `Frontend` | 普通应用 | .abc |
| `JsFrontend` | `Frontend` | JS 应用 | .js |

---

## 5. 性能优化

### 5.1 资源缓存策略

**图片缓存**：

**源码位置**：`js_card_parser.h:220`

```cpp
std::unordered_map<std::string, std::string> imageUrlMap_;
```

**缓存策略**：

```
┌─────────────────────────────────────────────────────────┐
│  图片资源缓存                                            │
│                                                          │
│  Key: "app.media.icon" + theme ("light"/"dark")         │
│  Value: 实际图片路径                                     │
│                                                          │
│  查找流程：                                              │
│  1. 检查缓存 → 命中则直接返回                            │
│  2. 未命中 → 加载资源文件                                │
│  3. 解析 JSON → 获取图片路径                            │
│  4. 存入缓存 → 返回结果                                 │
└─────────────────────────────────────────────────────────┘
```

---

### 5.2 数据更新优化

**增量更新**：Repeat 节点只更新变化的部分

**源码位置**：`js_card_parser.cpp:1886-1920`

**更新策略**：

| 场景 | 策略 |
|------|------|
| 数据量相同 | 更新现有节点 |
| 数据量增加 | 更新现有 + 创建新节点 |
| 数据量减少 | 更新现有 + 删除多余节点 |

**节点复用**：通过 `listIdMap_` 和 `singleLoopMap_` 跟踪节点

```cpp
// 节点映射: numberOfForNode → (nodeIdArray, totalSize)
std::unordered_map<int32_t, std::pair<std::vector<int32_t>, int32_t>> listIdMap_;

// 单轮循环节点数: numberOfForNode → nodesPerLoop
std::unordered_map<int32_t, int32_t> singleLoopMap_;
```

---

### 5.3 解析优化

**版本适配**：API 版本相关的数据处理

**源码位置**：`js_card_parser.cpp:1947-1982`

```cpp
void JsCardParser::ParseVersionAndUpdateData()
{
    auto versionJson = rootBody_->GetValue("apiVersion");
    VersionData versionData;

    // 收集所有版本补丁
    while (child && child->IsValid()) {
        auto key = child->GetKey();  // API 版本号
        auto value = child->GetString();  // 补丁数据
        versionData.AddRecord(key, value);
    }

    // 获取适用于当前系统的补丁
    auto versionPatch = versionData.GetVersionPatch();
    for (const auto& patchInfo : versionPatch) {
        // 应用补丁到 dataJson
    }
}
```

**版本匹配逻辑**：

```cpp
std::vector<std::string> VersionData::GetVersionPatch()
{
    int32_t sysApiVersion = SystemProperties::GetApiVersion();
    // 返回所有 API 版本 <= 系统版本的补丁
    for (const auto& record : records_) {
        if (record.first <= sysApiVersion) {
            result.emplace_back(record.second);
        }
    }
    // 按版本号从小到大排序
    std::reverse(result.begin(), result.end());
}
```

---

### 5.4 线程优化

**任务调度**：

| 操作 | JSON 卡片线程 | 声明式卡片线程 |
|------|---------------|---------------|
| Initialize | JS | JS |
| RunPage | JS (posted) | UI (posted) |
| LoadPage | JS | - |
| ParsePage | JS | - |
| OnPageLoaded | UI (posted) | UI (posted) |
| UpdateData | JS (posted) | UI (posted) |
| FireCardEvent | UI (posted) | UI (posted) |

**eTS Card 的 UI 线程优化**：

```cpp
// 声明式卡片直接在 UI 线程执行，减少线程切换
taskExecutor_->PostTask(
    [...] { /* logic */ },
    TaskExecutor::TaskType::UI, "ArkUICardFrontendRunCard");
```

---

### 5.5 内存占用优化

**单个卡片内存**：

| 组件 | 内存占用（估算） |
|------|------------------|
| CardFrontend | ~1 KB |
| CardFrontendDelegate | ~0.5 KB |
| JsCardParser | ~5-10 KB (取决于复杂度) |
| JsAcePage | ~2 KB |
| DOM 节点 (每节点) | ~0.2 KB |

**优化建议**：
1. 限制卡片节点数量（建议 < 100 个节点）
2. 使用 LazyForEach 模式（通过 Repeat）
3. 及时清理不再使用的资源

---

## 附录

### 相关文件清单

| 文件 | 行数 | 主要功能 |
|------|------|----------|
| `card_frontend.h` | ~277 | CardFrontend 类定义 |
| `card_frontend.cpp` | ~347 | CardFrontend 实现 |
| `card_frontend_declarative.h` | ~165 | CardFrontendDeclarative 类定义 |
| `card_frontend_declarative.cpp` | ~241 | CardFrontendDeclarative 实现 |
| `card_frontend_delegate.h` | ~51 | CardFrontendDelegate 类定义 |
| `card_frontend_delegate.cpp` | ~96 | CardFrontendDelegate 实现 |
| `card_frontend_delegate_declarative.h` | ~93 | CardFrontendDelegateDeclarative 类定义 |
| `card_frontend_delegate_declarative.cpp` | ~77 | CardFrontendDelegateDeclarative 实现 |
| `form_frontend_declarative.h` | ~173 | FormFrontendDeclarative 类定义 |
| `form_frontend_declarative.cpp` | ~178 | FormFrontendDeclarative 实现 |
| `form_frontend_delegate_declarative.h` | ~136 | FormFrontendDelegateDeclarative 类定义 |
| `form_frontend_delegate_declarative.cpp` | ~93 | FormFrontendDelegateDeclarative 实现 |
| `js_card_parser.h` | ~238 | JsCardParser 类定义 |
| `js_card_parser.cpp` | ~2062 | JsCardParser 实现 |

### 调试命令

```bash
# 查看卡片组件信息
hidumper -s WindowManagerService -a '-a ComponentTree'

# 查看卡片日志
hilog -T ACE_FORM

# 查看系统 API 版本
param get const.product.software.version
```

### 参考文档

- **快速参考**: [CardFrontend/CLAUDE.md](../../frameworks/bridge/card_frontend/CLAUDE.md)
- **相关**: [DeclarativeFrontend 文档](../../frameworks/bridge/declarative_frontend/)
- **相关**: [JsFrontend 文档](../../frameworks/bridge/js_frontend/)
- **基础**: [core/common/frontend.h](../../frameworks/core/common/frontend.h)

---

**文档版本历史**

| 版本 | 日期 | 更新内容 |
|-----|------|---------|
| v1.0 | 2026-02-03 | 初始版本，完整覆盖 Card Frontend 架构、实现原理、问题排查、性能优化 |
