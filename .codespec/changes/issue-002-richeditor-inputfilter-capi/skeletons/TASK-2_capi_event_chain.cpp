/*
 * TASK-2: CAPI 事件链路 — 7 个文件的修改/新增骨架
 * 关联 AC: AC-4, AC-5, AC-6
 * 参考: TextInput onInputFilterError 链路 (node_text_input_modifier.cpp:3800 的 lambda 构造)
 *       RichEditor SetRichEditorNapiOnDidChange (行2006-2024) 的事件注册格式
 * 关键约束 (design.md D-3): 事件 kind 使用 TEXT_INPUT 而非 RICH_EDITOR
 */

// =====================================================================
// 1. interfaces/native/native_node.h — 追加事件枚举值
//    插入位置: NODE_TEXT_EDITOR_ON_DID_CHANGE (行11259) 之后
// =====================================================================

    /**
     * @brief Defines the event triggered when input characters are filtered out
     * by the input filter regex pattern of this text editor.
     *
     * The filtered-out characters can be obtained via
     * {@link OH_ArkUI_NodeEvent_GetStringAsyncEvent}.\n
     * {@link ArkUI_StringAsyncEvent.pStr}: the filtered-out characters (UTF-8).\n
     *
     * @since 26.0.0
     */
    NODE_TEXT_EDITOR_ON_INPUT_FILTER_ERROR,  // 值 = 22009 (紧跟 22008)


// =====================================================================
// 2. frameworks/core/interfaces/arkoala/arkoala_api.h — 追加子类型枚举 + 事件函数指针
// =====================================================================

// --- ArkUIEventSubKind 枚举追加 (行1768 ON_RICH_EDITOR_ON_DID_CHANGE 之后) ---
    ON_RICH_EDITOR_ON_INPUT_FILTER_ERROR,  // 值 = 67009 (紧跟 67008)

// --- ArkUIRichEditorModifier 结构体追加 2 个事件函数指针 ---
//    插入位置: 属性函数指针组之后 (或与 set/resetRichEditorOn* 事件函数同类)
    void (*setRichEditorOnInputFilterError)(ArkUINodeHandle node, void* extraParam);
    void (*resetRichEditorOnInputFilterError)(ArkUINodeHandle node);


// =====================================================================
// 3. interfaces/native/node/event_converter.cpp — 3 处追加
// =====================================================================

// --- ConvertOriginEventType 追加 (参考 NODE_TEXT_EDITOR_ON_SELECTION_CHANGE 格式，行489附近) ---
        case NODE_TEXT_EDITOR_ON_INPUT_FILTER_ERROR:
            return ON_RICH_EDITOR_ON_INPUT_FILTER_ERROR;

// --- ConvertToNodeEventType 追加 (参考 ON_RICH_EDITOR_ON_SELECTION_CHANGE 格式，行863附近) ---
        case ON_RICH_EDITOR_ON_INPUT_FILTER_ERROR:
            return NODE_TEXT_EDITOR_ON_INPUT_FILTER_ERROR;

// --- IsStringEvent 追加 (当前函数不含 NODE_TEXT_EDITOR_ 条目，行888附近) ---
        case NODE_TEXT_EDITOR_ON_INPUT_FILTER_ERROR:
            return true;


// =====================================================================
// 4. frameworks/core/components_ng/pattern/rich_editor/bridge/rich_editor_dynamic_modifier.cpp
//    追加事件桥接函数 + handler数组 + modifier初始化
// =====================================================================

// --- 事件桥接函数 (关键: design.md D-3 — kind=TEXT_INPUT, subKind=67009) ---
//    参考: SetRichEditorNapiOnDidChange (行2006-2024) 格式
//    但数据提取方式参考 TextInput 的 onInputFilterError: 使用 textInputEvent.nativeStringPtr

void SetOnRichEditorNapiOnInputFilterError(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onInputFilterError = [extraParam](const std::u16string& str) {
        // 关键: 事件 kind 使用 TEXT_INPUT (而非 RICH_EDITOR)
        // 因为 OH_ArkUI_NodeEvent_GetStringAsyncEvent 读取 textInputEvent 联合体成员
        ArkUINodeEvent event;
        std::string utf8Str = UtfUtils::Str16DebugToStr8(str);
        event.kind = TEXT_INPUT;  // ← design.md D-3: 必须用 TEXT_INPUT
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.textInputEvent.subKind = ON_RICH_EDITOR_ON_INPUT_FILTER_ERROR;  // ← 67009
        event.textInputEvent.nativeStringPtr = reinterpret_cast<intptr_t>(utf8Str.c_str());
        SendArkUISyncEvent(&event);
    };
    RichEditorModelNG::SetOnInputFilterError(frameNode, std::move(onInputFilterError));
}

void ResetOnRichEditorNapiOnInputFilterError(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::ResetOnInputFilterError(frameNode);
}

// --- GetEventSetHandler 数组追加索引 9 (当前0-8，行2035-2045) ---
//    在索引 8 (SetRichEditorNapiOnDidChange, 行2044) 之后追加:
    NG::SetOnRichEditorNapiOnInputFilterError,  // 索引 9

// --- GetEventResetHandler 数组追加索引 9 (当前0-8) ---
    NG::ResetOnRichEditorNapiOnInputFilterError,  // 索引 9

// --- GetRichEditorDynamicModifier 结构体初始化追加 2 条 (行2187之后) ---
    .setRichEditorOnInputFilterError = SetOnRichEditorNapiOnInputFilterError,
    .resetRichEditorOnInputFilterError = ResetOnRichEditorNapiOnInputFilterError,
// 注意: 第二个结构体 (L2285附近) 也需要同样追加


// =====================================================================
// 5. frameworks/core/components_ng/pattern/rich_editor/rich_editor_model.h
//    追加事件相关虚方法 (2个)
// =====================================================================

    virtual void SetOnInputFilterError(std::function<void(const std::u16string&)>&& func) {};
    virtual void ResetOnInputFilterError() {}


// =====================================================================
// 6. frameworks/core/components_ng/pattern/rich_editor/rich_editor_model_ng.h/.cpp
//    追加事件 override + static 声明 + 实现
// =====================================================================

// --- rich_editor_model_ng.h 追加 ---
    void SetOnInputFilterError(std::function<void(const std::u16string&)>&& func) override;
    void ResetOnInputFilterError() override;
    static void SetOnInputFilterError(FrameNode* frameNode,
        std::function<void(const std::u16string&)>&& func);
    static void ResetOnInputFilterError(FrameNode* frameNode);

// --- rich_editor_model_ng.cpp 实现 (参考 TextFieldModelNG::SetInputFilterError, L2430) ---
void RichEditorModelNG::SetOnInputFilterError(std::function<void(const std::u16string&)>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNode()
        ->GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnInputFilterError(std::move(func));
}

void RichEditorModelNG::ResetOnInputFilterError()
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNode()
        ->GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnInputFilterError(nullptr);
}

void RichEditorModelNG::SetOnInputFilterError(FrameNode* frameNode,
    std::function<void(const std::u16string&)>&& func)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnInputFilterError(std::move(func));
}

void RichEditorModelNG::ResetOnInputFilterError(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnInputFilterError(nullptr);
}


// =====================================================================
// 7. frameworks/core/components_ng/pattern/rich_editor/rich_editor_event_hub.h/.cpp
//    追加 3 个方法 + 1 个成员 (参考 TextFieldEventHub, L134-146)
// =====================================================================

// --- rich_editor_event_hub.h 追加 (public 段，行329 HasOnStyledStringDidChange 之后) ---
    void SetOnInputFilterError(std::function<void(const std::u16string&)>&& func)
    {
        onInputFilterError_ = std::move(func);
    }
    void FireOnInputFilterError(const std::u16string& value) const
    {
        if (onInputFilterError_) {
            TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "On filter error size %{public}zu",
                UtfUtils::Str16DebugToStr8(value).size());
            onInputFilterError_(value);
        }
    }
    void ResetOnInputFilterError()
    {
        onInputFilterError_ = nullptr;
    }

// --- rich_editor_event_hub.h 追加 (private 段，行350 onStyledStringDidChange_ 之后) ---
    std::function<void(const std::u16string&)> onInputFilterError_;

// --- rich_editor_event_hub.cpp: Set/Fire/ResetOnInputFilterError ---
//    注意: Set 和 Fire 已在 .h 中 inline 实现（参考 TextFieldEventHub 的 inline 模式）
//    如果项目规范要求 .cpp 中实现，则需移至 .cpp:
//
// void RichEditorEventHub::SetOnInputFilterError(std::function<void(const std::u16string&)>&& func)
// {
//     onInputFilterError_ = std::move(func);
// }
//
// void RichEditorEventHub::FireOnInputFilterError(const std::u16string& value) const
// {
//     if (onInputFilterError_) {
//         TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "On filter error size %{public}zu",
//             UtfUtils::Str16DebugToStr8(value).size());
//         onInputFilterError_(value);
//     }
// }
//
// void RichEditorEventHub::ResetOnInputFilterError()
// {
//     onInputFilterError_ = nullptr;
// }
