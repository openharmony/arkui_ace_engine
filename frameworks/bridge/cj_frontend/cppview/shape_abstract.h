/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_SHAPE_ABSTRACT_H
#define FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_SHAPE_ABSTRACT_H

#include "bridge/cj_frontend/cppview/interactable_view.h"
#include "bridge/cj_frontend/cppview/view_abstract.h"

namespace OHOS::Ace::Framework {

class ACE_EXPORT NativeShapeAbstract : public OHOS::FFI::FFIData {
public:
    NativeShapeAbstract();
    ~NativeShapeAbstract() override;
    const RefPtr<BasicShape>& GetBasicShape() const
    {
        return basicShape_;
    }

    void SetBasicShape(const RefPtr<BasicShape>& basicShape)
    {
        basicShape_ = basicShape;
    }

    void SetWidth(const Dimension& value);
    void SetHeight(const Dimension& value);
    void SetSize(const Dimension& width, const Dimension& height);
    void SetOffset(const Dimension& x, const Dimension& y);
    void SetFill(const Color& color);

protected:
    RefPtr<BasicShape> basicShape_;
};

class ACE_EXPORT NativeCircle : public NativeShapeAbstract {
public:
    NativeCircle(const Dimension& width, const Dimension& height);
    ~NativeCircle() override;
};

class ACE_EXPORT NativeEllipse : public NativeShapeAbstract {
public:
    NativeEllipse(const Dimension& width, const Dimension& height);
    ~NativeEllipse() override;
};

class ACE_EXPORT NativeRect : public NativeShapeAbstract {
public:
    NativeRect(const Dimension& width, const Dimension& height);
    ~NativeRect() override;
    void SetRadiusWidth(const Dimension& value);
    void SetRadiusHeight(const Dimension& value);
    void SetRadius(const Dimension& value);
};

class ACE_EXPORT NativePath : public NativeShapeAbstract {
public:
    explicit NativePath(const std::string& pathCmd);
    ~NativePath() override;
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_SHAPE_ABSTRACT_H
