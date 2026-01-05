#ifndef RENDER_SERVICE_CLIENT_CORE_MODIFIER_NG_CUSTOM_RS_CUSTOM_MODIFIER_H
#define RENDER_SERVICE_CLIENT_CORE_MODIFIER_NG_CUSTOM_RS_CUSTOM_MODIFIER_H

// #include "command/rs_node_command.h"
// #include "modifier_ng/rs_modifier_ng.h"
// #include "pipeline/rs_draw_cmd_list.h"
#include "draw/canvas.h"
#include "render_service_client/core/modifier_ng/rs_modifier_ng.h"
namespace OHOS::Rosen {
// class RSNode;
namespace ModifierNG {
struct RSDrawingContext {
    Drawing::Canvas* canvas;
    float width;
    float height;
};

// class RSC_EXPORT RSCustomModifierHelper {
// public:
//     static RSDrawingContext CreateDrawingContext(std::shared_ptr<RSNode> node);
//     static std::shared_ptr<Drawing::DrawCmdList> FinishDrawing(RSDrawingContext& ctx);
// };

class RSCustomModifier : public RSModifier {
public:
    RSCustomModifier() = default;
    virtual ~RSCustomModifier() = default;

    virtual void Draw(RSDrawingContext& context) const = 0;

    void SetNoNeedUICaptured(bool noNeedUICaptured)
    {
        noNeedUICaptured_ = noNeedUICaptured;
    }

    bool IsCustom() const override
    {
        return true;
    }

    // int16_t GetIndex() const
    // {
    //     return 0;
    // }

    // void SetIndex(int16_t index)
    // {
    //     Setter<RSProperty, int16_t>(RSPropertyType::CUSTOM_INDEX, index);
    // }

protected:
    // std::shared_ptr<RSRenderModifier> CreateRenderModifier() override
    // {
    //     return nullptr;
    // }

    virtual RSPropertyType GetInnerPropertyType() const
    {
        return RSPropertyType::CUSTOM;
    }

    // void UpdateToRender() override
    // {
    // }

private:
    bool lastDrawCmdListEmpty_ = false;
    bool noNeedUICaptured_ = false;

    // friend class OHOS::Rosen::RSNode;
};
} // namespace ModifierNG
} // namespace OHOS::Rosen
#endif // RENDER_SERVICE_CLIENT_CORE_MODIFIER_NG_CUSTOM_RS_CUSTOM_MODIFIER_H
