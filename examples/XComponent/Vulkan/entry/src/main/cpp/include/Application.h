/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef __APPLICATION__
#define __APPLICATION__

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <ace/xcomponent/native_interface_xcomponent.h>
#include <native_window/external_window.h>
#include <vulkan/vulkan.h>
#include <native_vsync/native_vsync.h>
#include <rawfile/raw_file.h>
#include <rawfile/raw_file_manager.h>
#include <hilog/log.h>

#include <vulkan/vulkan_core.h>
#include <vector>
#include <functional>
#include "Camera.h"

#include "InfPlaneRenderer.h"
class InfPlaneRenderer;

uint32_t clamp(uint32_t input, uint32_t min, uint32_t max);

class Application
{
public:
    Application();
    ~Application();

    void Run(OHNativeWindow *inputWindow, NativeResourceManager* nativeResourceManager);
    OHNativeWindow* GetWindow();
    void MainLoop();
    
    void YawPitchTo(double x, double y);
    double GetYaw();
    double GetPitch();
    void GetFront(double& x, double& y, double& z);
    void WindowSizeChange(double width, double height, int orientation);
    void DispatchController(double x, double y, double size, double op);
private:
    void InitWindow(OHNativeWindow *inputWindow);
    void InitVulkan();
    void CreateSurface();
    void CleanUp();

    void CreateInstance();

    void PickPhysicalDevice();

    bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
    uint32_t DeviceSuitable(VkPhysicalDevice device);

    void CreateLogicalDevice();
    VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR ChooseSwapPresentMode (const std::vector<VkPresentModeKHR> availablePresentModes);
    VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
    void CreateSwapChain();
    void CreateImageViews();
    void CreateGraphicsPipeline();
    static std::vector<char> ReadFile(const std::string fileName);
    VkShaderModule CreateShaderModule(const std::vector<char>& code);
    void CreateRenderPass();
    void CreateFramebuffers();
    void CreateCommandPool();
    void CreateDepthResources();
    void CreateCommandBuffers();
    void RecordCommandBuffer(uint32_t imageIndex);
    void DrawFrame();
    void CreateSyncObjects();
    void CleanSwapChain();
    void RecreateSwapChain();
    void CreateVertexBuffer(); // VBO
    void CreateIndexBuffer(); // EBO

    void CreateUniformBuffers(); // uniform
    void UpdateUniformBuffer(uint32_t currentImage);
    void CreateDescriptorPool();
    void CreateDescriptorSets();

    void CreateImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
    VkCommandBuffer BeginSingleTimeCommands();

    VkImageView CreateImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags = VK_IMAGE_ASPECT_COLOR_BIT);

    void EndSingleTimeCommands(VkCommandBuffer& commandBuffer);
    void TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
    void CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

    uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory); // VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT
    void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

    void CreateDescriptorSetLayout();
    VkFormat FindDepthFormat();
    VkFormat FindSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

    static void NotifyFrameBufferResized(OHNativeWindow* window, int width, int height);

    static void OnKey(OHNativeWindow* window, int key, int scancode, int action, int mods);
    static void OnMouse(OHNativeWindow* window, int button, int action, int mods);
    static void OnCursorMove(OHNativeWindow* window, double xpos, double ypos);
    static void OnScroll(OHNativeWindow* window, double xoffset, double yoffset);

    void ProcessKey();

    uint32_t windowWidth = 0;
    uint32_t windowHeight = 0;
    uint32_t windowOrientation = 0;
    OHNativeWindow* window = nullptr;
    VkInstance instance;
    VkSurfaceKHR surface;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;
    VkQueue graphicsQueue;
    VkQueue presentQueue;
    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    std::vector<VkImageView> swapChainImageViews;
    VkRenderPass renderPass;
    VkPipeline graphicsPipeline;
    VkDescriptorSetLayout descriptorSetLayout;
    VkPipelineLayout pipelineLayout;
    std::vector<VkFramebuffer> swapChainFramebuffers;
    VkCommandPool commandPool;
    std::vector<VkCommandBuffer> commandBuffers;
    
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;

    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformBuffersMemory;
    std::vector<void*> uniformBuffersMapped;

    
    VkImage depthImage;
    VkDeviceMemory depthImageMemory;
    VkImageView depthImageView;

    VkDescriptorPool descriptorPool;
    std::vector<VkDescriptorSet> descriptorSets;

    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;

    uint32_t currentFrame = 0;
    const uint32_t maxFrame = 2;

    static bool framebufferResized;

    const std::vector<const char*> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };
    
    bool needDraw = true;
    static bool listenCursorMove;
    static double lastCurPosx;
    static double lastCurPosy;
    bool cameraMove = false;
    static double xPos;
    static double yPos;
    static std::function<void(Application* app)> cameraMoveFunc;
    static Camera ca;
    InfPlaneRenderer* infPlaneRenderer = nullptr;
    static NativeResourceManager* nativeResourceManager;
    
    friend  class InfPlaneRenderer;
}; // Application

struct UniformBufferObject {
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;
    glm::mat4 inverseView;
};

struct UniformLight {
    glm::vec4 lightPos;
    glm::vec4 lightColor;
};

struct UniformMaterial {
    glm::vec4 ambi;
    glm::vec4 diff;
    glm::vec4 spec;
};

struct UniformInput {
    UniformBufferObject ubo;
    UniformLight ul;
    UniformMaterial um;
};

#endif // __APPLICATION__
