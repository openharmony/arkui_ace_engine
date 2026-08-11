/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

typedef enum {
    %CPP_PREFIX%ARKUI_DIRTY_FLAG_MEASURE = 0b1,
    %CPP_PREFIX%ARKUI_DIRTY_FLAG_LAYOUT = 0b10,
    // mark the node need to do attribute diff to drive update.
    %CPP_PREFIX%ARKUI_DIRTY_FLAG_ATTRIBUTE_DIFF = 0b100,
    %CPP_PREFIX%ARKUI_DIRTY_FLAG_MEASURE_SELF = 0b1000,
    %CPP_PREFIX%ARKUI_DIRTY_FLAG_MEASURE_SELF_AND_PARENT = 0b10000,
    %CPP_PREFIX%ARKUI_DIRTY_FLAG_MEASURE_BY_CHILD_REQUEST = 0b100000,
    %CPP_PREFIX%ARKUI_DIRTY_FLAG_RENDER = 0b1000000,
    %CPP_PREFIX%ARKUI_DIRTY_FLAG_MEASURE_SELF_AND_CHILD = 0b1000000000,
    %CPP_PREFIX%ARKUI_DIRTY_FLAG_MEASURE_SELF_WHEN_ADD_CHILD = 0b10000000000,
} %CPP_PREFIX%ArkUIDirtyFlag;

union %CPP_PREFIX%Ark_EventCallbackArg {
    Ark_Int32 i32;
    Ark_Int32 u32;
    Ark_Int32 f32;
};

typedef union %CPP_PREFIX%Ark_EventCallbackArg %CPP_PREFIX%Ark_EventCallbackArg;

typedef struct %CPP_PREFIX%Ark_APICallbackMethod {
    Ark_Int32 (*CallInt) (Ark_VMContext vmContext, Ark_Int32 methodId, Ark_Int32 numArgs, %CPP_PREFIX%Ark_EventCallbackArg* args);
} %CPP_PREFIX%Ark_APICallbackMethod;

typedef struct %CPP_PREFIX%ArkUIBasicNodeAPI {
    Ark_Int32 version;

    /// Tree operations.
    Ark_NodeHandle (*createNode)(%CPP_PREFIX%Ark_NodeType type,
                                 Ark_Int32 id, Ark_Int32 flags);

    Ark_NodeHandle (*getNodeByViewStack)();
    void (*disposeNode)(Ark_NodeHandle node);

    void (*dumpTreeNode)(Ark_NodeHandle node);

    Ark_Int32 (*addChild)(Ark_NodeHandle parent,
                          Ark_NodeHandle child);
    void (*removeChild)(Ark_NodeHandle parent,
                        Ark_NodeHandle child);
    Ark_Int32 (*insertChildAfter)(Ark_NodeHandle parent,
                                  Ark_NodeHandle child, Ark_NodeHandle sibling);
    Ark_Int32 (*insertChildBefore)(Ark_NodeHandle parent,
                                   Ark_NodeHandle child,
                                   Ark_NodeHandle sibling);
    Ark_Int32 (*insertChildAt)(Ark_NodeHandle parent,
                               Ark_NodeHandle child,
                               Ark_Int32 position);

    // Commit attributes updates for node.
    void (*applyModifierFinish)(Ark_NodeHandle nodePtr);
    // the flag can combine different flag like Ark_DIRTY_FLAG_MEASURE | Ark_DIRTY_FLAG_RENDER
    void (*markDirty)(Ark_NodeHandle nodePtr,
                      Ark_UInt32 dirtyFlag);
    Ark_Boolean (*isBuilderNode)(Ark_NodeHandle node);

    Ark_Float32 (*convertLengthMetricsUnit)(Ark_Float32 value,
                                            Ark_Int32 originUnit,
                                            Ark_Int32 targetUnit);
} %CPP_PREFIX%ArkUIBasicNodeAPI;

typedef void (*Ark_VsyncCallback)(Ark_PipelineContext);

typedef struct %CPP_PREFIX%ArkUIExtendedNodeAPI {
    Ark_Int32 version;

    Ark_Float32 (*getDensity) (Ark_Int32 deviceId);
    Ark_Float32 (*getFontScale) (Ark_Int32 deviceId);
    Ark_Float32 (*getDesignWidthScale) (Ark_Int32 deviceId);

    // Improve: remove!
    void (*setCallbackMethod)(%CPP_PREFIX%Ark_APICallbackMethod* method);

    // the custom node is not set in create.
    void (*setCustomMethodFlag)(Ark_NodeHandle node,
                                Ark_Int32 flag);
    Ark_Int32 (*getCustomMethodFlag)(Ark_NodeHandle node);

    // setCustomCallback is without the context
    void (*setCustomCallback) (Ark_VMContext  vmContext,
                               Ark_NodeHandle node,
                               Ark_Int32 callbackId);
    void (*setCustomNodeDestroyCallback)(void (*destroy)(Ark_NodeHandle nodeId));
    // make void instead return type Ark_Int32
    Ark_Int32 (*measureLayoutAndDraw) (Ark_VMContext  vmContext,
                                       Ark_NodeHandle node);
    Ark_Int32 (*measureNode) (Ark_VMContext  vmContext,
                              Ark_NodeHandle node,
                              Ark_Float32* data);
    Ark_Int32 (*layoutNode) (Ark_VMContext  vmContext,
                             Ark_NodeHandle node,
                             Ark_Float32 (*data)[2]);
    Ark_Int32 (*drawNode) (Ark_VMContext  vmContext,
                           Ark_NodeHandle node,
                           Ark_Float32* data);
    void (*setAttachNodePtr) (Ark_NodeHandle node,
                              void* value);
    void* (*getAttachNodePtr) (Ark_NodeHandle node);

    // may be better to use int in px unit
    void (*setMeasureWidth)(Ark_NodeHandle node,
                            Ark_Int32 value);
    Ark_Int32 (*getMeasureWidth)(Ark_NodeHandle node);
    void (*setMeasureHeight)(Ark_NodeHandle node,
                             Ark_Int32 value);
    Ark_Int32 (*getMeasureHeight)(Ark_NodeHandle node);
    void (*setX)(Ark_NodeHandle node, Ark_Int32 value);
    Ark_Int32 (*getX)(Ark_NodeHandle node);
    void (*setY)(Ark_NodeHandle node,
                 Ark_Int32 value);
    Ark_Int32 (*getY)(Ark_NodeHandle node);

    void (*getLayoutConstraint)(Ark_NodeHandle node,
                                Ark_Int32* value);
    void (*setAlignment)(Ark_NodeHandle node,
                         Ark_Int32 value);
    Ark_Int32 (*getAlignment)(Ark_NodeHandle node);

    Ark_Int32 (*indexerChecker) (Ark_VMContext  vmContext,
                                 Ark_NodeHandle node);
    void (*setRangeUpdater)(Ark_NodeHandle node,
                            Ark_Int32 updatedId);
    void (*setLazyItemIndexer) (Ark_VMContext  vmContext,
                                Ark_NodeHandle node,
                                Ark_Int32 indexerId);

    /// Vsync support
    Ark_PipelineContext (*getPipelineContext)(Ark_NodeHandle node);
    void (*setVsyncCallback)(Ark_PipelineContext pipelineContext,
                             Ark_VsyncCallback callback);
    void (*setChildTotalCount)(Ark_NodeHandle node,
                               Ark_Int32 totalCount);

    /// Error reporting.
    void (*showCrash)(Ark_CharPtr message);
} %CPP_PREFIX%ArkUIExtendedNodeAPI;

/**
 * An API to control an implementation. When making changes modifying binary
 * layout, i.e. adding new events - increase ARKUI_NODE_API_VERSION above for binary
 * layout checks.
 */
typedef struct %CPP_PREFIX%ArkUIFullNodeAPI {
    Ark_Int32 version;
    const %CPP_PREFIX%ArkUINodeModifiers* (*getNodeModifiers)();
    const %CPP_PREFIX%ArkUIAccessors* (*getAccessors)();
    const %CPP_PREFIX%ArkUIGraphicsAPI* (*getGraphicsAPI)();
} %CPP_PREFIX%ArkUIFullNodeAPI;
